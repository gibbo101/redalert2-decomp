# SPDX-License-Identifier: GPL-3.0-or-later
"""Whole-generation provenance, immutable publication and current-runner checks."""
import argparse
import copy
import json
import os
from pathlib import Path
import subprocess
import sys
import tempfile
from types import SimpleNamespace
import unittest
from unittest.mock import patch

import original_results as cache
from presentation_evidence import validate_receipt


class PythonClosureTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        for folder in ('tests', 'tools'):
            (self.root/folder).mkdir()
        for name in ('original_results', 'run_evidence', 'inspection_reuse'):
            (self.root/f'tools/{name}.py').write_text('# infrastructure\n')
        self.driver = self.root/'tests/compare_fixture.py'
        self.driver.write_text('def generate():\n import helper_a\n')
        (self.root/'tools/helper_a.py').write_text('VALUE = 1\n')
        cache.source_imports.cache_clear()
        self.addCleanup(cache.source_imports.cache_clear)

    def closure(self):
        return cache.python_closure(self.driver, {}, self.root)

    def test_repeated_closure_reuses_parsing_but_not_returned_identities(self):
        with patch.object(cache.ast, 'parse', wraps=cache.ast.parse) as parse:
            first = self.closure()
            calls = parse.call_count
            self.assertEqual(calls, len(first))
            first['tools/helper_a.py'] = 'caller mutation'
            second = self.closure()
            self.assertEqual(parse.call_count, calls)
            self.assertEqual(second['tools/helper_a.py'], cache.hash_file(self.root/'tools/helper_a.py'))
            with patch.object(cache, 'source_imports', cache.source_imports.__wrapped__):
                self.assertEqual(second, self.closure())

    def test_same_size_timestamp_preserving_edit_rechecks_bytes_and_nested_imports(self):
        first = self.closure()
        stat = self.driver.stat()
        self.driver.write_text('def generate():\n import helper_b\n')
        os.utime(self.driver, ns=(stat.st_atime_ns, stat.st_mtime_ns))
        (self.root/'tools/helper_b.py').write_text('from nested import VALUE\n')
        (self.root/'tools/nested.py').write_text('VALUE = 2\n')
        second = self.closure()
        self.assertNotEqual(first['tests/compare_fixture.py'], second['tests/compare_fixture.py'])
        self.assertNotIn('tools/helper_a.py', second)
        self.assertIn('tools/helper_b.py', second)
        self.assertIn('tools/nested.py', second)

    def test_newly_resolvable_import_and_removed_dependency_are_not_cached(self):
        self.driver.write_text('import optional_helper\n')
        first = self.closure()
        helper = self.root/'tools/optional_helper.py'
        helper.write_text('VALUE = 3\n')
        self.assertIn('tools/optional_helper.py', self.closure())
        helper.unlink()
        self.assertEqual(first, self.closure())

    def test_invalid_source_is_reparsed_with_its_filename_and_recovers(self):
        self.closure()
        self.driver.write_text('def broken(\n')
        with patch.object(cache.ast, 'parse', wraps=cache.ast.parse) as parse:
            for _ in range(2):
                with self.assertRaises(SyntaxError) as error:
                    self.closure()
                self.assertEqual(error.exception.filename, 'tests/compare_fixture.py')
            self.assertEqual(parse.call_count, 2)
        self.driver.write_text('import helper_a\n')
        self.assertIn('tools/helper_a.py', self.closure())


class OriginalResultsTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory(dir=cache.ROOT/'build')
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        for directory in ('tests', 'tools', 'src', 'private'):
            (self.root/directory).mkdir()
        self.driver = self.root/'tests/compare_ground_drive_stores.py'
        self.driver.write_text('def generate():\n import original_fixture\n')
        (self.root/'tests/original_fixture.py').write_text('SEED = 17\n')
        for name in ('original_results', 'run_evidence', 'inspection_reuse'):
            (self.root/('tools/'+name+'.py')).write_text('# tool\n')
        (self.root/'src/movement.cpp').write_text('// native\n')
        self.exe = self.root/'private/game/game.exe'
        self.exe.parent.mkdir()
        self.exe.write_bytes(b'exact executable')
        self.input = self.root/'private/inputs.bin'
        self.input.write_bytes(b'ordered inputs')
        self.runner = self.root/'build/runner.py'
        self.runner.parent.mkdir()
        self.runner.write_text('print("native-one")\n')
        self.current = {'sources': {'src/movement.cpp': 'native-one',
                                   'tests/original_fixture.py': 'original-one'},
                        'inspection': {'profile': 'test', 'nested': [1, 2]}, 'data': 'data-one'}
        self.runtime = {'interpreter': 'python-one', 'jit': 'unicorn-one', 'env': {'seed': 0}}
        self.addCleanup(patch.stopall)
        patch.object(cache, 'ROOT', self.root).start()
        # The default argument of python_closure is intentionally explicit here.
        closure = cache.python_closure
        patch.object(cache, 'python_closure', side_effect=lambda d, i: closure(d, i, self.root)).start()
        patch.object(cache, 'runtime_identity', side_effect=lambda: {
            **copy.deepcopy(self.runtime), 'environment_value_sha256': cache.environment_identity()}).start()
        patch('presentation_evidence.ROOT', self.root).start()
        patch.object(Path, 'cwd', return_value=self.root).start()
        self.counter = 0
        self.original_calls = 0
        self.native_calls = []

    def args(self, mode='use', enabled=True):
        self.counter += 1
        return argparse.Namespace(exe=self.exe, native=self.runner, rules=self.input,
            output=self.root/f'private/run-{self.counter}', expectations=None, report=None,
            original_cache=self.root/'private/cache' if enabled else None,
            original_cache_mode=mode, original_cache_require_hit=False, pilot=False)

    @staticmethod
    def validator(e, r, f, current):
        validate_receipt(e, r, f)
        if e['evidence']['identities'] != current:
            raise ValueError('legacy mixed identity differs')
        if not e.get('commands') or not len(e['commands']) == len(e['expected']) == len(e['labels']):
            raise ValueError('incomplete sequence')

    def run_generation(self, args=None, current=None, drift=False):
        args = args or self.args()
        current = current or self.current
        reuse = cache.OriginalResults(args, current, self.driver)
        if args.expectations:
            source = args.expectations
            e = json.loads(source.read_text()); r = json.loads((source.parent/'report.json').read_text())
            reuse.validate(self.validator, e, r, cache.hash_file(source), current)
            report = args.report
        else:
            self.original_calls += 1
            source = args.output/'expected.json'; report = args.output/'report.json'
            # Stateful sequence stays in one envelope: ordered commands/outputs,
            # callback ordering and final RNG state must never be split into calls.
            e = {'commands': ['initialize 17', 'step 0', 'step 1'],
                 'expected': [['state', 17], ['callback-A', 21], ['callback-B', 33 if drift else 32]],
                 'labels': ['seed', 'first', 'later']}
        proc = subprocess.run([sys.executable, '-B', str(args.native)], capture_output=True, text=True, check=True)
        self.native_calls.append(proc.stdout.strip())
        result = {'identities': current, 'native_sha256': cache.hash_file(args.native),
                  'evidence_mode': 'cached-original-replay' if args.expectations else 'fresh-original',
                  'original_instructions_executed': not bool(args.expectations),
                  'original_instructions_modified': False, **reuse.report_fields()}
        report.parent.mkdir(parents=True)
        if not args.expectations:
            e['evidence'] = result.copy()
            source.write_text(json.dumps(e))
        result['expectations_sha256'] = cache.hash_file(source)
        report.write_text(json.dumps(result))
        reuse.finish(source, report, self.validator)
        return reuse, report

    def test_hit_preserves_sequence_and_always_runs_current_native(self):
        first, origin = self.run_generation()
        frozen = {p.name: p.read_bytes() for p in first.entry.iterdir()}
        self.runner.write_text('print("native-two")\n')
        changed = copy.deepcopy(self.current); changed['sources']['src/movement.cpp'] = 'native-two'
        hit, replay = self.run_generation(current=changed)
        self.assertEqual((first.state, hit.state), ('miss', 'hit'))
        self.assertEqual(self.original_calls, 1)
        self.assertEqual(self.native_calls, ['native-one', 'native-two'])
        result = json.loads(replay.read_text())
        self.assertFalse(result['original_instructions_executed'])
        self.assertEqual(result['identities'], changed)
        self.assertEqual(result['original_result_reuse']['origin_files'], first.read_entry()[1])
        self.assertEqual(frozen, {p.name: p.read_bytes() for p in first.entry.iterdir()})
        self.assertEqual(json.loads(origin.read_text())['evidence_mode'], 'fresh-original')

    def test_no_cache_keeps_legacy_strict_validation(self):
        reuse, _ = self.run_generation(self.args(enabled=False))
        self.assertFalse(reuse.enabled)
        e = {'evidence': {'identities': {'old': True}, 'evidence_mode': 'fresh-original'}}
        r = {**e['evidence'], 'expectations_sha256': 'hash'}
        with self.assertRaisesRegex(ValueError, 'mixed identity'):
            reuse.validate(self.validator, e, r, 'hash', self.current)
        self.assertFalse((self.root/'private/cache').exists())

    def test_scatter_nested_native_changes_reuse_but_authored_inputs_invalidate(self):
        self.driver = self.driver.with_name('compare_owned_scatter_world.py')
        self.driver.write_text('def generate():\n import original_fixture\n')
        disc = self.root/'private/disc-allied/game.exe'
        disc.parent.mkdir(); disc.write_bytes(b'retained disc inspection input')
        current = {'runtime': copy.deepcopy(self.current), 'authored_inputs_sha256': 'fixture-one',
                   'python_sources': {'tests/original_fixture.py': 'original-one'}}
        first, _ = self.run_generation(current=current)
        frozen = {p.name: p.read_bytes() for p in first.entry.iterdir()}
        self.runner.write_text('print("scatter-current-native")\n')
        changed = copy.deepcopy(current)
        changed['runtime']['sources']['src/movement.cpp'] = 'native-two'
        required = self.args(); required.original_cache_require_hit = True
        hit, report = self.run_generation(required, changed)
        self.assertEqual((first.state, hit.state, self.original_calls), ('miss', 'hit', 1))
        self.assertEqual(self.native_calls, ['native-one', 'scatter-current-native'])
        self.assertEqual(json.loads(report.read_text())['identities'], changed)
        self.assertEqual(frozen, {p.name: p.read_bytes() for p in first.entry.iterdir()})
        for field in ('authored_inputs_sha256', 'python_sources'):
            invalid = copy.deepcopy(changed)
            invalid[field] = 'changed' if field != 'python_sources' else {'tests/original_fixture.py': 'changed'}
            args = self.args(); args.original_cache_require_hit = True
            with self.subTest(field=field), self.assertRaisesRegex(ValueError, 'cold key'):
                cache.OriginalResults(args, invalid, self.driver)
            self.assertFalse(args.output.exists())
        disc.write_bytes(b'changed retained disc')
        args = self.args(); args.original_cache_require_hit = True
        with self.assertRaisesRegex(ValueError, 'cold key'):
            cache.OriginalResults(args, changed, self.driver)
        self.assertEqual(self.original_calls, 1)

    def test_process_comparison_runner_rebuild_reuses_originals_and_is_guarded(self):
        self.driver = self.driver.with_name('compare_borrowed_process_scatter.py')
        self.driver.write_text('def generate():\n import original_fixture\n')
        legacy = self.runner.with_name('legacy.py');legacy.write_text('legacy-one')
        first_args = self.args();first_args.legacy_native = legacy
        initial = dict(self.current, legacy_native_sha256=cache.hash_file(legacy))
        first, _ = self.run_generation(first_args, initial)
        legacy.write_text('legacy-two')
        self.runner.write_text('print("native-two")\n')
        next_args = self.args();next_args.legacy_native = legacy
        current = dict(self.current, legacy_native_sha256=cache.hash_file(legacy))
        current['sources'] = dict(current['sources'], **{'src/movement.cpp': 'rebuilt'})
        hit, report = self.run_generation(next_args, current)
        self.assertEqual((first.state, hit.state, self.original_calls), ('miss', 'hit', 1))
        self.assertEqual(json.loads(report.read_text())['identities'], current)
        legacy.write_text('changed-during-run')
        with self.assertRaisesRegex(ValueError, 'runner changed'):
            hit.check_unchanged()

    def test_process_input_scope_changes_do_not_reuse_originals(self):
        self.driver = self.driver.with_name('compare_borrowed_process_scatter.py')
        self.driver.write_text('def generate():\n import original_fixture\n')
        legacy = self.runner.with_name('legacy.py');legacy.write_text('legacy')
        for limit in (4, 5):
            args = self.args();args.legacy_native = legacy;args.pilot_limit = limit
            reuse, _ = self.run_generation(args)
            self.assertEqual(reuse.state, 'miss')
        self.assertEqual(self.original_calls, 2)

    def test_cross_invocation_context_keeps_key_and_immutable_origin(self):
        with patch.dict(os.environ, {'CODEX_TOOL_CALL_ID': 'origin-command', 'CODEX_SANDBOX': 'host'}):
            first, _ = self.run_generation()
            origin_context = cache.invocation_context()
        frozen = {p.name: p.read_bytes() for p in first.entry.iterdir()}
        self.runner.write_text('print("native-current-context")\n')
        changed = copy.deepcopy(self.current); changed['sources']['src/movement.cpp'] = 'native-changed'
        with patch.dict(os.environ, {'CODEX_TOOL_CALL_ID': 'replay-command', 'CODEX_SANDBOX': 'restricted'}):
            args = self.args(); args.original_cache_require_hit = True
            hit, report = self.run_generation(args, current=changed)
            metadata = json.loads(report.read_text())['original_result_reuse']
            self.assertEqual(metadata['invocation_context'], cache.invocation_context())
        self.assertEqual((first.state, hit.state), ('miss', 'hit'))
        self.assertEqual(first.key, hit.key)
        self.assertEqual(self.original_calls, 1)
        self.assertEqual(self.native_calls, ['native-one', 'native-current-context'])
        self.assertTrue(metadata['require_hit'])
        self.assertIs(metadata['invocation_context_in_original_key'], False)
        self.assertNotEqual(metadata['invocation_context'], origin_context)
        original = json.loads((first.entry/'expected.json').read_text())
        self.assertEqual(original['evidence']['original_result_reuse']['invocation_context'], origin_context)
        self.assertEqual(frozen, {p.name: p.read_bytes() for p in first.entry.iterdir()})

    def test_only_two_reviewed_environment_variables_leave_original_key(self):
        self.assertEqual(cache.INVOCATION_ONLY_ENV, {'CODEX_TOOL_CALL_ID', 'CODEX_SANDBOX'})
        for key in ('RA2_ORIGINAL_INPUT', 'CODEX_ORACLE_INPUT'):
            with self.subTest(key=key), patch.dict(os.environ, {key: 'original-input'}):
                first = cache.OriginalResults(self.args(), self.current, self.driver)
                os.environ[key] = 'changed-input'
                second = cache.OriginalResults(self.args(), self.current, self.driver)
                self.assertNotEqual(first.key, second.key)

    def test_context_absence_empty_and_values_are_hashed_and_distinct(self):
        with patch.dict(os.environ, clear=True):
            absent = cache.invocation_context()
            self.assertEqual(set(absent['environment_value_sha256']), cache.INVOCATION_ONLY_ENV)
            self.assertTrue(all(v is None for v in absent['environment_value_sha256'].values()))
            os.environ['CODEX_TOOL_CALL_ID'] = ''
            empty = cache.invocation_context()
            os.environ['CODEX_TOOL_CALL_ID'] = 'private-invocation-value'
            present = cache.invocation_context()
            self.assertNotEqual(absent, empty)
            self.assertNotEqual(empty, present)
            self.assertNotIn('private-invocation-value', json.dumps(present))
            self.assertEqual(cache.environment_identity(), {})
            for context in (absent, empty, present):cache.validate_invocation_context(context)

    def test_invocation_context_drift_fails_even_though_key_inputs_match(self):
        for key in sorted(cache.INVOCATION_ONLY_ENV):
            with self.subTest(key=key), patch.dict(os.environ, {key: 'initial'}):
                reuse = cache.OriginalResults(self.args(), self.current, self.driver)
                provenance = reuse.provenance
                os.environ[key] = 'changed'
                self.assertEqual(reuse.snapshot(), provenance)
                with self.assertRaisesRegex(ValueError, 'context changed during'):
                    reuse.check_unchanged()
                del os.environ[key]
                with self.assertRaisesRegex(ValueError, 'context changed during'):
                    reuse.report_fields()
                os.environ[key] = 'initial'
                reuse.check_unchanged()

    def test_require_hit_cold_refuses_before_original_or_native_execution(self):
        args = self.args(); args.original_cache_require_hit = True
        with self.assertRaisesRegex(ValueError, 'hit required; cold key'):
            self.run_generation(args)
        self.assertEqual(self.original_calls, 0)
        self.assertEqual(self.native_calls, [])
        self.assertFalse(args.output.exists())
        self.assertFalse(args.original_cache.exists())

    def test_require_hit_rejects_disabled_and_refresh_before_runtime_inspection(self):
        for args in (self.args(enabled=False), self.args(mode='refresh')):
            args.original_cache_require_hit = True
            with self.subTest(args=args), \
                    patch.object(cache, 'runtime_identity', side_effect=AssertionError('unused')), \
                    self.assertRaisesRegex(ValueError, 'requires'):
                cache.OriginalResults(args, self.current, self.driver)

    def test_origin_invocation_metadata_is_required_and_shape_checked(self):
        first, _ = self.run_generation()
        frozen = {p.name: p.read_bytes() for p in first.entry.iterdir()}
        for invalid in (None, {}, {'environment_value_sha256': {}},
                        {'environment_value_sha256': {k: 'unhashed' for k in cache.INVOCATION_ONLY_ENV}}):
            e = json.loads(frozen['expected.json'])
            e['evidence']['original_result_reuse']['invocation_context'] = invalid
            (first.entry/'expected.json').write_text(json.dumps(e))
            r = {**e['evidence'], 'expectations_sha256': cache.hash_file(first.entry/'expected.json')}
            (first.entry/'report.json').write_text(json.dumps(r))
            manifest = json.loads(frozen['manifest.json'])
            manifest['files'] = {name: cache.hash_file(first.entry/name) for name in manifest['files']}
            (first.entry/'manifest.json').write_text(json.dumps(manifest))
            with self.subTest(invalid=invalid), self.assertRaisesRegex(ValueError, 'invocation metadata'):
                cache.OriginalResults(self.args(), self.current, self.driver)
            for name, data in frozen.items():(first.entry/name).write_bytes(data)

    def test_current_report_cannot_inherit_origin_context(self):
        first, _ = self.run_generation()
        with patch.dict(os.environ, {'CODEX_TOOL_CALL_ID': 'current-report'}):
            hit, report = self.run_generation()
            result = json.loads(report.read_text())
            result['original_result_reuse']['invocation_context'] = first.invocation_context
            report.write_text(json.dumps(result))
            with self.assertRaisesRegex(ValueError, 'Current invocation context'):
                hit.finish(hit.entry/'expected.json', report, self.validator)

    def test_v1_manifest_is_not_imported_or_rewritten(self):
        self.assertEqual(cache.FORMAT, 'ra2-whole-original-generation-v2')
        first, _ = self.run_generation()
        manifest_path = first.entry/'manifest.json'
        manifest = json.loads(manifest_path.read_text());manifest['format'] = 'ra2-whole-original-generation-v1'
        manifest_path.write_text(json.dumps(manifest))
        frozen = {p.name: p.read_bytes() for p in first.entry.iterdir()}
        with self.assertRaisesRegex(ValueError, 'provenance/key'):
            cache.OriginalResults(self.args(), self.current, self.driver)
        self.assertEqual(frozen, {p.name: p.read_bytes() for p in first.entry.iterdir()})

    def test_off_does_not_fingerprint_runtime_or_inputs(self):
        with patch.object(cache, 'runtime_identity', side_effect=AssertionError('unused')), \
                patch.object(cache, 'invocation_context', side_effect=AssertionError('unused')):
            self.run_generation(self.args(enabled=False))

    def test_strict_replay_does_not_inherit_origins_cache_annotation(self):
        reuse = cache.OriginalResults(self.args(enabled=False), self.current, self.driver)
        result = {'evidence_mode': 'cached-original-replay',
                  'original_result_reuse': {'state': 'miss', 'original_execution_performed': True}}
        reuse.annotate(result)
        self.assertNotIn('original_result_reuse', result)
        self.assertEqual(result['evidence_mode'], 'cached-original-replay')

    def test_refresh_executes_originals_and_never_replaces_entry(self):
        first, _ = self.run_generation()
        frozen = {p.name: p.read_bytes() for p in first.entry.iterdir()}
        fresh, report = self.run_generation(self.args('refresh'))
        self.assertEqual((fresh.state, self.original_calls), ('refresh', 2))
        self.assertTrue(json.loads(report.read_text())['original_instructions_executed'])
        self.assertEqual(frozen, {p.name: p.read_bytes() for p in first.entry.iterdir()})
        with self.assertRaisesRegex(ValueError, 'control differs'):
            self.run_generation(self.args('refresh'), drift=True)
        self.assertEqual(frozen, {p.name: p.read_bytes() for p in first.entry.iterdir()})

    def test_each_original_dependency_invalidates(self):
        first, _ = self.run_generation()
        mutations = (
            (self.exe, b'changed executable'), (self.input, b'changed data/order/seed'),
            (self.root/'tests/original_fixture.py', b'SEED = 18\n'),
            (self.root/'tools/original_results.py', b'# changed policy\n'))
        for path, data in mutations:
            old = path.read_bytes(); path.write_bytes(data)
            try:
                with self.subTest(path=path):
                    miss = cache.OriginalResults(self.args(), self.current, self.driver)
                    self.assertEqual(miss.state, 'miss'); self.assertNotEqual(miss.key, first.key)
            finally:
                path.write_bytes(old)
        for key in ('interpreter', 'jit', 'env'):
            old = self.runtime[key]; self.runtime[key] = 'changed'
            try:
                with self.subTest(runtime=key):
                    self.assertEqual(cache.OriginalResults(self.args(), self.current, self.driver).state, 'miss')
            finally:
                self.runtime[key] = old
        for field in ('inspection', 'data'):
            changed = copy.deepcopy(self.current); changed[field] = 'changed'
            self.assertEqual(cache.OriginalResults(self.args(), changed, self.driver).state, 'miss')
        args = self.args(); args.pilot = True
        self.assertEqual(cache.OriginalResults(args, self.current, self.driver).state, 'miss')

    def test_corrupt_or_partial_entries_fail_closed(self):
        first, _ = self.run_generation()
        for name in ('manifest.json', 'expected.json', 'report.json'):
            path = first.entry/name; original = path.read_bytes()
            for data in (b'{}', b'partial invalid JSON'):
                path.write_bytes(data)
                with self.subTest(name=name, data=data), self.assertRaises((ValueError, KeyError)):
                    cache.OriginalResults(self.args(), self.current, self.driver)
            path.unlink()
            with self.assertRaises((ValueError, FileNotFoundError)):
                cache.OriginalResults(self.args(), self.current, self.driver)
            path.write_bytes(original)

    def test_native_failure_never_publishes(self):
        self.runner.write_text('raise RuntimeError("bad native")\n')
        with self.assertRaises(subprocess.CalledProcessError):self.run_generation()
        self.assertFalse((self.root/'private/cache').exists())

    def test_hit_still_fails_with_broken_current_runner(self):
        first, _ = self.run_generation()
        frozen = {p.name: p.read_bytes() for p in first.entry.iterdir()}
        self.runner.write_text('raise RuntimeError("regression")\n')
        with self.assertRaises(subprocess.CalledProcessError):self.run_generation()
        self.assertEqual(self.original_calls, 1)
        self.assertEqual(frozen, {p.name: p.read_bytes() for p in first.entry.iterdir()})

    def test_extra_input_producer_is_part_of_original_provenance(self):
        # A separate producer cannot hide under the excluded --native identity.
        # Real native-generated-input families remain unsupported until reviewed.
        producer = self.root/'private/input-producer'; producer.write_bytes(b'producer-one')
        args = self.args(); args.input_producer = producer
        first = cache.OriginalResults(args, self.current, self.driver)
        producer.write_bytes(b'producer-two')
        args = self.args(); args.input_producer = producer
        self.assertNotEqual(first.key, cache.OriginalResults(args, self.current, self.driver).key)

    def test_symlink_entry_manifest_and_content_refused(self):
        first, _ = self.run_generation()
        for name in ('manifest.json', 'expected.json', 'report.json'):
            path = first.entry/name; data = path.read_bytes()
            target = self.root/('private/borrowed-'+name); target.write_bytes(data)
            path.unlink(); path.symlink_to(target)
            with self.subTest(name=name), self.assertRaisesRegex(ValueError, 'Symlink'):
                cache.OriginalResults(self.args(), self.current, self.driver)
            path.unlink(); path.write_bytes(data)

    def test_publication_failure_leaves_no_partial_entry(self):
        with patch.object(cache.os, 'rename', side_effect=OSError('interrupted publication')):
            with self.assertRaisesRegex(OSError, 'publication'):self.run_generation()
        self.assertEqual(list((self.root/'private/cache').iterdir()), [])

    def test_changes_during_invocation_fail(self):
        reuse = cache.OriginalResults(self.args(), self.current, self.driver)
        for path in (self.runner, self.input, self.root/'tests/original_fixture.py'):
            old = path.read_bytes(); path.write_bytes(b'changed')
            with self.subTest(path=path), self.assertRaisesRegex(ValueError, 'changed during'):
                reuse.check_unchanged()
            path.write_bytes(old)

    def test_replay_cannot_substitute_receipt_or_current_identity(self):
        first, _ = self.run_generation()
        hit = cache.OriginalResults(self.args(), self.current, self.driver)
        e, r = copy.deepcopy(first.read_entry()[0]); e['expected'][0] = ['forged']
        with self.assertRaisesRegex(ValueError, 'origin/current'):
            hit.validate(self.validator, e, r, hit.hashes['expected.json'], self.current)
        e, r = first.read_entry()[0]
        current = copy.deepcopy(self.current); current['sources']['src/movement.cpp'] = 'late edit'
        with self.assertRaisesRegex(ValueError, 'origin/current'):
            hit.validate(self.validator, e, r, hit.hashes['expected.json'], current)

    def test_scope_and_destination_guards(self):
        for kind in ('legacy', 'old_output', 'nested_output', 'symlink', 'unsupported'):
            args = self.args(); driver = self.driver
            if kind == 'legacy':args.expectations = self.input
            elif kind == 'old_output':args.output.mkdir()
            elif kind == 'nested_output':args.output = args.original_cache/'output'
            elif kind == 'symlink':
                link = self.root/'private/link'; link.symlink_to(self.input); args.rules = link
            elif kind == 'unsupported':
                driver = self.root/'tests/compare_terrain_runtime.py'; driver.write_text('# native input helper\n')
            with self.subTest(kind=kind), self.assertRaises(ValueError):
                cache.OriginalResults(args, self.current, driver)

    def test_native_sources_only_projection_keeps_all_other_identities(self):
        current = copy.deepcopy(self.current)
        current['sources'].update({'CMakeLists.txt': 'cmake', 'tests/helper.cmake': 'cmake'})
        current['seeds'] = [False, 0, -1]
        original = cache.original_identity(current)
        self.assertEqual(original['sources'], {'tests/original_fixture.py': 'original-one'})
        self.assertEqual(original['seeds'], [False, 0, -1])
        self.assertEqual(original['inspection'], current['inspection'])
        self.assertEqual(cache.original_identity({'input_sha256': 'native-data'}), {'input_sha256': 'native-data'})

    def test_runtime_requires_fixed_hash_seed_and_no_bytecode(self):
        with patch.dict(os.environ, {'PYTHONHASHSEED': 'random'}):
            # Use the real implementation, not setUp's lightweight test snapshot.
            with self.assertRaisesRegex(ValueError, 'PYTHONHASHSEED'):
                REAL_RUNTIME_IDENTITY()
        with patch.dict(os.environ, {'PYTHONHASHSEED': '0'}), \
                patch.object(cache.sys, 'flags', SimpleNamespace(hash_randomization=1)):
            with self.assertRaisesRegex(ValueError, 'PYTHONHASHSEED'):
                REAL_RUNTIME_IDENTITY()

    def test_parser_is_opt_in_and_refresh_requires_store(self):
        parser = argparse.ArgumentParser(); cache.add_arguments(parser)
        args = parser.parse_args([])
        self.assertIsNone(args.original_cache)
        self.assertFalse(args.original_cache_require_hit)
        self.assertTrue(parser.parse_args(['--original-cache-require-hit']).original_cache_require_hit)
        args = self.args(mode='refresh', enabled=False)
        with self.assertRaisesRegex(ValueError, 'requires'):cache.OriginalResults(args, self.current, self.driver)


REAL_RUNTIME_IDENTITY = cache.runtime_identity

if __name__ == '__main__':unittest.main()
