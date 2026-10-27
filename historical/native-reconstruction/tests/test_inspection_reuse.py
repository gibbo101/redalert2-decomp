# SPDX-License-Identifier: GPL-3.0-or-later
from collections import Counter
from contextlib import contextmanager
from pathlib import Path
import struct
import sys
import tempfile
import types
import unittest
from unittest.mock import patch

from inspection_reuse import InspectionReuse
from run_evidence import check_identities, driver_sources, input_identities, option, source_identities


class InspectionReuseTests(unittest.TestCase):
    @contextmanager
    def histogram_inspector(self, body=None):
        with tempfile.TemporaryDirectory() as directory:
            owner = types.ModuleType('verify_histogram_fixture')
            owner.__file__ = str(Path(directory)/'verify_histogram_fixture.py')
            exec('def verify(data, salt=0):\n import pefile\n' + (body or
                 ' counts = pefile.Counter(bytearray(data))\n counts[255] += salt\n return counts\n'),
                 owner.__dict__)
            pe = types.ModuleType('pefile')
            pe.Counter = Counter
            with patch.dict(sys.modules, {'pefile': pe, owner.__name__: owner}):
                original = owner.verify
                with InspectionReuse() as reuse:
                    reuse.install_loaded_verifiers(directory)
                    yield reuse, owner, pe
                self.assertIs(pe.Counter, Counter)
                self.assertIs(owner.verify, original)

    def test_byte_counts_share_work_without_sharing_mutations(self):
        with self.histogram_inspector() as (reuse, owner, pe):
            first = owner.verify(b'aba', 1)
            first[97] = 999
            self.assertEqual(owner.verify(b'aba', 2), Counter({97: 2, 98: 1, 255: 2}))
            changed = Counter(b'changed')
            changed[255] = 0
            self.assertEqual(owner.verify(b'changed', 0), changed)
            self.assertEqual((reuse.stats['byte_histogram_hits'],
                              reuse.stats['byte_histogram_misses']), (1, 2))

    def test_byte_count_keys_snapshot_mutable_parser_buffers(self):
        body = (' buffer = bytearray(data)\n first = pefile.Counter(buffer)\n'
                ' buffer[0] = 99\n second = pefile.Counter(buffer)\n'
                ' return first, second, pefile.Counter(bytearray(data))\n')
        with self.histogram_inspector(body) as (reuse, owner, pe):
            self.assertEqual(owner.verify(b'ab'), (Counter(b'ab'), Counter(b'cb'), Counter(b'ab')))
            self.assertEqual((reuse.stats['byte_histogram_hits'],
                              reuse.stats['byte_histogram_misses']), (1, 2))

    def test_noninspection_counter_calls_and_generic_inputs_stay_uncached(self):
        body = (' pefile.Counter([1, 1, 2])\n pefile.Counter({1: 3})\n'
                ' pefile.Counter(letters=2)\n return pefile.Counter(data)\n')
        with self.histogram_inspector(body) as (reuse, owner, pe):
            self.assertEqual(pe.Counter(bytearray(b'outside')), Counter(b'outside'))
            self.assertEqual(pe.Counter(a=2), Counter(a=2))
            self.assertEqual(reuse.stats['byte_histogram_misses'], 0)
            self.assertEqual(owner.verify(b'ab'), Counter(b'ab'))
            self.assertEqual(reuse.stats['byte_histogram_misses'], 1)
            pe.Counter(bytearray(b'ab'))
            self.assertEqual(reuse.stats['byte_histogram_hits'], 0)

    def test_failed_inspection_restores_counter_scope_and_binding(self):
        body = ' pefile.Counter(data)\n raise ValueError("inspection failed")\n'
        with self.assertRaisesRegex(ValueError, 'inspection failed'):
            with self.histogram_inspector(body) as (reuse, owner, pe):
                try:
                    owner.verify(b'ab')
                except ValueError:
                    pe.Counter(b'ab')  # Failed inspector no longer enables reuse.
                    self.assertEqual(reuse.stats['byte_histogram_hits'], 0)
                    raise
        self.assertIs(pe.Counter, Counter)

    def test_byte_histograms_end_with_the_invocation(self):
        for _ in range(2):
            with self.histogram_inspector() as (reuse, owner, pe):
                owner.verify(b'ab')
                self.assertEqual((reuse.stats['byte_histogram_hits'],
                                  reuse.stats['byte_histogram_misses']), (0, 1))

    def test_unrecognized_pe_counter_binding_is_preserved(self):
        with self.histogram_inspector() as (reuse, owner, pe):
            reuse.restore()
            alternative = lambda data: Counter(data)
            pe.Counter = alternative
            reuse.install_loaded_verifiers(Path(owner.__file__).parent)
            owner.verify(b'ab')
            self.assertIs(pe.Counter, alternative)
            self.assertEqual(reuse.stats['byte_histogram_misses'], 0)
            pe.Counter = Counter

    def test_histogram_control_preserves_verifier_reuse(self):
        with self.histogram_inspector() as (setup, owner, pe):
            setup.restore()
            with InspectionReuse(byte_histograms=False) as reuse:
                reuse.install_loaded_verifiers(Path(owner.__file__).parent)
                self.assertIs(pe.Counter, Counter)
                self.assertEqual(owner.verify(b'ab'), owner.verify(b'ab'))
                self.assertEqual((reuse.stats['misses'], reuse.stats['hits']), (1, 1))
                self.assertEqual(reuse.stats['byte_histogram_misses'], 0)

    def test_unchanged_hit_changed_binary_and_scalar_miss(self):
        calls = []
        reuse = InspectionReuse()
        wrapped = reuse.wrap(lambda data, offset=0: calls.append((data, offset)) or {'data': data})
        self.assertEqual(wrapped(b'one', offset=4), wrapped(b'one', offset=4))
        wrapped(b'two', offset=4)
        wrapped(b'one', offset=8)
        self.assertEqual(len(calls), 3)
        self.assertEqual((reuse.stats['hits'], reuse.stats['misses']), (1, 3))

    def test_defensive_copies_on_insert_and_every_hit(self):
        source = {'nested': [1, {'value': 2}]}
        reuse = InspectionReuse()
        wrapped = reuse.wrap(lambda data: source)
        first = wrapped(b'binary')
        first['nested'][1]['value'] = 99
        source['nested'][0] = 88
        second = wrapped(b'binary')
        self.assertEqual(second, {'nested': [1, {'value': 2}]})
        second['nested'].append(77)
        self.assertEqual(wrapped(b'binary'), {'nested': [1, {'value': 2}]})

    def test_mutable_inputs_and_subclasses_bypass(self):
        class MutableInt(int):
            pass
        reuse = InspectionReuse()
        calls = []
        wrapped = reuse.wrap(lambda data: calls.append(data) or data)
        for value in (bytearray(b'bytes'), [1], {'key': 1}, Path('file'), MutableInt(1)):
            self.assertIs(wrapped(value), value)
            self.assertIs(wrapped(value), value)
        self.assertEqual((len(calls), reuse.stats['bypasses'], reuse.stats['hits']), (10, 10, 0))

    def test_types_and_float_bits_do_not_alias(self):
        reuse = InspectionReuse()
        wrapped = reuse.wrap(lambda value: type(value).__name__ + ':' + repr(value))
        values = (1, True, 1.0, 0.0, -0.0, '1', b'1', None,
                  struct.unpack('!d', bytes.fromhex('7ff8000000000001'))[0],
                  struct.unpack('!d', bytes.fromhex('7ff8000000000002'))[0])
        for value in values:
            self.assertEqual(wrapped(value), wrapped(value))
        self.assertEqual(reuse.stats['misses'], len(values))
        self.assertEqual(reuse.stats['hits'], len(values))

    def test_exceptions_are_not_cached(self):
        reuse = InspectionReuse()
        def fail(data):
            raise ValueError('changed binary')
        wrapped = reuse.wrap(fail)
        for _ in range(2):
            with self.assertRaisesRegex(ValueError, 'changed binary'):
                wrapped(b'bad')
        self.assertEqual((reuse.stats['misses'], reuse.stats['hits']), (2, 0))

    def test_aliases_share_cache_and_restore_including_late_import(self):
        with tempfile.TemporaryDirectory() as directory:
            owner = types.ModuleType('verify_inspection_reuse_fixture')
            owner.__file__ = str(Path(directory) / 'verify_inspection_reuse_fixture.py')
            exec('def verify(data):\n return {"data": data}\n', owner.__dict__)
            original = owner.verify
            alias = types.ModuleType('inspection_reuse_alias_fixture')
            alias.borrowed = original
            sys.modules[owner.__name__] = owner
            sys.modules[alias.__name__] = alias
            try:
                with InspectionReuse() as reuse:
                    reuse.install_loaded_verifiers(directory)
                    self.assertIs(owner.verify, alias.borrowed)
                    owner.verify(b'bytes')
                    alias.borrowed(b'bytes')
                    alias.late = owner.verify
                    self.assertEqual((reuse.stats['misses'], reuse.stats['hits']), (1, 1))
                self.assertIs(owner.verify, original)
                self.assertIs(alias.borrowed, original)
                self.assertIs(alias.late, original)
            finally:
                del sys.modules[owner.__name__]
                del sys.modules[alias.__name__]

    def test_cache_does_not_survive_a_new_invocation(self):
        calls = []
        function = lambda value: calls.append(value) or value
        for _ in range(2):
            reuse = InspectionReuse()
            reuse.wrap(function)(b'bytes')
        self.assertEqual(len(calls), 2)

    def test_wrapping_twice_does_not_create_a_second_cache(self):
        reuse = InspectionReuse()
        original = lambda data: {'data': data}
        wrapped = reuse.wrap(original)
        self.assertIs(reuse.wrap(original), wrapped)
        self.assertIs(reuse.wrap(wrapped), wrapped)
        self.assertEqual(reuse.stats['functions'], 1)

    def test_execution_and_unrelated_verifiers_are_not_installed(self):
        with tempfile.TemporaryDirectory() as directory:
            modules = []
            for name, filename in (('original_reuse_scope_fixture', 'original_fixture.py'),
                                   ('unrelated_reuse_scope_fixture', 'unrelated.py')):
                module = types.ModuleType(name)
                module.__file__ = str(Path(directory) / filename)
                exec('def verify(data):\n return data\ndef execute(data):\n return data\n', module.__dict__)
                modules.append((module, module.verify, module.execute))
                sys.modules[name] = module
            try:
                with InspectionReuse() as reuse:
                    reuse.install_loaded_verifiers(directory)
                    for module, verify, execute in modules:
                        self.assertIs(module.verify, verify)
                        self.assertIs(module.execute, execute)
                    self.assertEqual(reuse.stats['functions'], 0)
            finally:
                for module, _, _ in modules:
                    del sys.modules[module.__name__]

    def test_cached_and_uncached_inspection_values_match(self):
        def inspect(data, offset=0):
            if not data:
                raise ValueError('empty binary')
            return {'bytes': list(data), 'offset': offset, 'nested': [{'size': len(data)}]}
        reuse = InspectionReuse()
        wrapped = reuse.wrap(inspect)
        for data, offset in ((b'first', 0), (b'first', 0), (b'changed', 3)):
            self.assertEqual(inspect(data, offset), wrapped(data, offset))
        for function in (inspect, wrapped):
            with self.assertRaisesRegex(ValueError, 'empty binary'):
                function(b'')

    def test_source_cmake_runner_and_binary_identity_guards(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            (root / 'tools').mkdir()
            files = [root / 'CMakeLists.txt', root / 'tools/verify_fixture.py']
            for file in files:
                file.write_text('original')
            baseline = source_identities(root)
            for file in files:
                file.write_text('changed')
                with self.assertRaisesRegex(ValueError, 'CMake'):
                    check_identities(baseline, source_identities(root))
                file.write_text('original')
            exe, native = root / 'game.exe', root / 'native'
            exe.write_bytes(b'binary'); native.write_bytes(b'runner')
            arguments = ['--exe', str(exe), '--native', str(native)]
            baseline = input_identities(arguments)
            for file in (exe, native):
                old = file.read_bytes(); file.write_bytes(b'changed')
                with self.assertRaisesRegex(ValueError, 'runner'):
                    check_identities(baseline, input_identities(arguments))
                file.write_bytes(old)

    def test_explicit_options_and_receipt_identity_required(self):
        for args in ([], ['--exe', 'a', '--exe=b'], ['--exe']):
            with self.assertRaises(ValueError):
                option(args, '--exe', required=True)
        self.assertEqual(option(['--exe=a'], '--exe'), Path('a').resolve())
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            for name in ('exe', 'native', 'expected.json', 'report.json'):
                (root / name).write_text(name)
            args = ['--exe', str(root / 'exe'), '--native', str(root / 'native'),
                    '--expectations', str(root / 'expected.json')]
            with self.assertRaisesRegex(ValueError, 'report'):
                input_identities(args)
            args += ['--report', str(root / 'new.json')]
            before = input_identities(args)
            (root / 'report.json').write_text('changed receipt')
            with self.assertRaises(ValueError):
                check_identities(before, input_identities(args))

    def test_driver_closure_allows_unrelated_edits_but_guards_consumed_sources(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            for name in ('src', 'tools', 'tests'):
                (root/name).mkdir()
            files = {'tests/compare_fixture.py': 'import original_fixture\n',
                     'tests/original_fixture.py': 'def call():\n import helper_fixture\n',
                     'tools/helper_fixture.py': '# original helper\n',
                     'src/runner.cpp': '#include "dependency.hpp"\n',
                     'src/dependency.hpp': '// header\n',
                     'src/unrelated.cpp': '// unrelated\n',
                     'CMakeLists.txt': '# unrelated build\n'}
            for name in ('original_results', 'run_evidence', 'inspection_reuse'):
                files['tools/'+name+'.py'] = '# infrastructure\n'
            for name, value in files.items():
                (root/name).write_text(value)
            driver = root/'tests/compare_fixture.py'
            module = types.SimpleNamespace(SOURCES=('src/runner.cpp',))
            paths = driver_sources(driver, module, root)
            before = source_identities(root, paths)
            for name in ('src/unrelated.cpp', 'CMakeLists.txt'):
                (root/name).write_text('changed unrelated')
            check_identities(before, source_identities(root, paths))
            for name in paths:
                old = (root/name).read_bytes()
                (root/name).write_bytes(old+b'\n# changed')
                with self.assertRaises(ValueError):
                    check_identities(before, source_identities(root, paths))
                (root/name).write_bytes(old)
            self.assertIsNone(driver_sources(driver, types.SimpleNamespace(), root))

    def test_secondary_runner_and_explicit_data_guarded(self):
        with tempfile.TemporaryDirectory() as directory:
            files = [Path(directory)/name for name in ('exe', 'native', 'legacy', 'data')]
            for path in files:
                path.write_text(path.name)
            args = [v for pair in zip(('--exe', '--native', '--legacy-native', '--geometry-data'), map(str, files)) for v in pair]
            before = input_identities(args)
            for path in files:
                old = path.read_bytes();path.write_bytes(b'changed')
                with self.assertRaises(ValueError):
                    check_identities(before, input_identities(args))
                path.write_bytes(old)

    def test_prepared_map_data_identity_is_guarded(self):
        with tempfile.TemporaryDirectory() as directory:
            files = [Path(directory)/name for name in ('exe', 'native', 'map-data')]
            for path in files:
                path.write_text(path.name)
            args = [v for pair in zip(('--exe', '--native', '--map-data'), map(str, files)) for v in pair]
            before = input_identities(args)
            files[-1].write_bytes(b'changed floor planes')
            with self.assertRaises(ValueError):
                check_identities(before, input_identities(args))


if __name__ == '__main__':
    unittest.main()
