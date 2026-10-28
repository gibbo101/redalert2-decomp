"""Scratch pointer/storage hypotheses and portable sweep reporting contracts."""
import json
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools/original_target'))
import seed_candidate as seed
import sweep_seeds as sweep


class PointerRecoveryTests(unittest.TestCase):
    def test_stored_pointer_uses_local_pointee_type(self):
        body = '{\n  short *p;\n  p = DAT_00801000;\n  return *p;\n}'
        text, types = seed.recover_global_pointers(body)
        self.assertEqual(types, {'DAT_00801000': 'short *'})
        self.assertEqual(text, body)

    def test_address_of_storage_is_not_a_stored_pointer(self):
        body = '{\n  int *p;\n  p = &DAT_00801000;\n  return DAT_00801000 * 3;\n}'
        self.assertEqual(seed.recover_global_pointers(body), (body, {}))

    def test_pointer_store_is_not_pointer_load_evidence(self):
        body = '{\n  uint *p;\n  *p = DAT_00801000;\n  *(uint *)p = DAT_00801004;\n}'
        self.assertEqual(seed.recover_global_pointers(body), (body, {}))

    def test_multiplication_is_not_unary_indirection(self):
        body = '{\n  int n;\n  n = 3 * DAT_00801000;\n  return n * DAT_00801004;\n}'
        self.assertEqual(seed.recover_global_pointers(body), (body, {}))

    def test_direct_indirection_and_subscript_are_pointer_evidence(self):
        _, types = seed.recover_global_pointers('{\n  return *DAT_00801000 + DAT_00801004[2];\n}')
        self.assertEqual(types, {'DAT_00801000': 'undefined4 *', 'DAT_00801004': 'undefined4 *'})

    def test_function_pointer_is_not_a_data_pointee(self):
        _, types = seed.recover_global_pointers('{\n  return (*DAT_00801000)();\n}')
        self.assertEqual(types, {'DAT_00801000': 'code *'})

    def test_conflicting_pointee_hypotheses_remain_width_only(self):
        body = '{\n  int *p;\n  short *q;\n  p = DAT_00801000;\n  q = DAT_00801000;\n}'
        self.assertEqual(seed.recover_global_pointers(body)[1], {'DAT_00801000': 'undefined4 *'})

    def test_raw_byte_offsets_do_not_acquire_element_scaling(self):
        body = '{\n  int *p;\n  p = DAT_00801000;\n  return *(short *)(DAT_00801000 + 6) + *DAT_00801000 + 1;\n}'
        text, _ = seed.recover_global_pointers(body)
        self.assertIn('((uint)DAT_00801000 + 6)', text)
        self.assertIn('*DAT_00801000 + 1', text)

    def test_literals_and_comments_are_not_access_evidence(self):
        body = '{\n  /* *DAT_00801000 */\n  use("DAT_00801004[2]");\n}'
        self.assertEqual(seed.recover_global_pointers(body), (body, {}))

    def test_shared_pointer_declaration_supplies_existing_owner_type(self):
        with tempfile.TemporaryDirectory() as temp:
            root = Path(temp)
            (root / 'fixture.hpp').write_bytes(b'class KnownOwner { int field; };\n'
                b'extern KnownOwner *Owner; // 0x00801000\n')
            known = seed.shared_pointer_types(root)
            self.assertEqual(known[0x801000]['forward'], 'class KnownOwner;')
            body, types = seed.recover_global_pointers('{\n return *(int *)(DAT_00801000 + 4);\n}', shared=known)
            self.assertEqual(types['DAT_00801000'], 'KnownOwner *')
            self.assertIn('(uint)DAT_00801000 + 4', body)

    def test_conflicting_shared_declarations_are_not_guessed(self):
        with tempfile.TemporaryDirectory() as temp:
            root = Path(temp)
            (root / 'fixture.hpp').write_bytes(b'class A {};\nclass B {};\n'
                b'extern A *First; // 0x00801000\nextern B *Second; // 0x00801000\n')
            self.assertNotIn(0x801000, seed.shared_pointer_types(root))


class StoreBoundaryTests(unittest.TestCase):
    def test_explicit_store_type_wins_over_address_variable_type(self):
        body = '{\n  char *p;\n  *(uint *)p = &DAT_00801000;\n}'
        text = seed.cast_storage_boundaries(body)
        self.assertIn('*(uint *)p = (uint)(&DAT_00801000);', text)
        self.assertNotIn('(char *)(&DAT_', text)

    def test_multiline_partial_store_preserves_one_evaluation(self):
        body = '{\n  undefined8 x;\n  (*(uint*)((char*)&x + 0)) =\n    pointer_source();\n}'
        text = seed.cast_storage_boundaries(body)
        self.assertIn('(uint)(pointer_source())', text)
        self.assertEqual(text.count('pointer_source()'), 1)

    def test_for_initializer_and_increment_clauses_are_converted(self):
        body = '{\n  int *p;\n  for (p = source(); p != 0; p = next()) { use(p); }\n}'
        text = seed.cast_storage_boundaries(body)
        self.assertIn('p = (int *)(source())', text)
        self.assertIn('p = (int *)(next())', text)
        self.assertEqual(text.count('source()'), 1)
        self.assertEqual(text.count('next()'), 1)

    def test_array_store_uses_element_width(self):
        body = '{\n  uint a[4];\n  a[2] = pointer_source();\n}'
        self.assertIn('a[2] = (uint)(pointer_source());', seed.cast_storage_boundaries(body))

    def test_double_pointer_store_uses_one_pointee_level(self):
        body = '{\n  byte **p;\n  *p = source();\n}'
        self.assertIn('*p = (byte *)(source());', seed.cast_storage_boundaries(body))

    def test_aggregate_and_compound_assignments_are_left_alone(self):
        body = '{\n  CoordStruct point;\n  int n;\n  point = other;\n  n += get();\n}'
        self.assertEqual(seed.cast_storage_boundaries(body), body)

    def test_return_dereference_is_not_a_variable_declaration(self):
        body = '{\n  short *p;\n  p = source();\n  return *p;\n}'
        self.assertEqual(seed.variable_types(body)['p'], 'short *')
        self.assertIn('p = (short *)(source());', seed.cast_assignments(body, []))

    def test_masked_long_lines_do_not_become_declarations(self):
        body = '{\n  use("' + 'x' * 50000 + '");\n  int *p;\n  return *p;\n}'
        self.assertEqual(seed.variable_types(body), {'p': 'int *'})

    def test_incompatible_pointer_equality_compares_address_bits_once(self):
        body = '{\n  int *p;\n  short *q;\n  return p != q;\n}'
        self.assertIn('(uint)p != (uint)q', seed.pointer_equality_boundaries(body))
        self.assertEqual(seed.pointer_equality_boundaries(body.replace('!=', '<')), body.replace('!=', '<'))

    def test_equality_does_not_cast_an_address_inside_a_loaded_value(self):
        for expression in ('*p == value', '(uint)p == value', 'value == p[0]'):
            body = '{\n  int *p;\n  uint value;\n  return '+expression+';\n}'
            self.assertEqual(seed.pointer_equality_boundaries(body), body)

    def test_incompatible_null_pointer_view_keeps_address_comparison(self):
        body = '{\n  uint *p;\n  return p == (ushort *)0x0;\n}'
        self.assertIn('(uint)p == 0x0', seed.pointer_equality_boundaries(body))

    def test_zero_and_sign_extension_keep_width_and_single_evaluation(self):
        self.assertEqual(seed.extend_artifacts('ZEXT48(get())'), '((ulonglong)(uint)(get()))')
        self.assertEqual(seed.extend_artifacts('SEXT18(get())'), '((longlong)(signed char)(get()))')
        with self.assertRaisesRegex(ValueError, 'width'):
            seed.extend_artifacts('ZEXT84(get())')

    def test_recursive_free_call_keeps_declared_parameter_conversions(self):
        text, _ = seed.declare_callee('{ return FUN_00401000(pointer); }', 'FUN_00401000',
                                    ('uint', '__cdecl', ['uint value']))
        self.assertIn('FUN_00401000((uint)(pointer))', text)

    def test_pointer_return_conversion_evaluates_value_once(self):
        text = seed.return_boundaries('{ return call(); }', 'char *')
        self.assertIn('return (char *)(call());', text)
        self.assertEqual(text.count('call()'), 1)

    def test_return_conversion_does_not_narrow_wide_or_aggregate_values(self):
        body = '{ return get(); }'
        self.assertEqual(seed.return_boundaries(body, 'ulonglong'), body)
        self.assertEqual(seed.return_boundaries(body, 'CoordStruct'), body)


class SweepReportingTests(unittest.TestCase):
    def test_size_bucket_boundaries_and_compiled_score_refusal(self):
        rows = [dict(length=255, score=100, byte_exact=True), dict(length=256, score=75),
                dict(length=1023, status='compile-failed'), dict(length=1024, status='score-refused'),
                dict(length=4095, score=0), dict(length=4096, status='seed-failed')]
        summary = sweep.size_summary(dict(enumerate(rows)))
        self.assertEqual([r['attempted'] for r in summary], [1, 2, 2, 1])
        self.assertEqual([r['compiled'] for r in summary], [1, 1, 2, 0])
        self.assertEqual([r['exact'] for r in summary], [1, 0, 0, 0])
        self.assertEqual([r['score_at_least_75'] for r in summary], [1, 1, 0, 0])

    def test_queue_and_json_report_agree_and_use_lf(self):
        with tempfile.TemporaryDirectory() as temp:
            root = Path(temp)
            rows = {'00401000': dict(entry='00401000', length=4096, compiled=True, score=76)}
            sweep.write_queue(root, rows)
            self.assertNotIn(b'\r', (root / 'queue.md').read_bytes())
            summary = json.loads((root / 'summary.json').read_text())['size_buckets']
            self.assertEqual(summary[-1]['compiled'], 1)
            self.assertIn('| >=4 KB | 1 | 1 | 0 | 1 |', (root / 'queue.md').read_text())


class NativeCompilerTests(unittest.TestCase):
    def config(self, root):
        return dict(compiler_directory=str(root / 'compiler with spaces'), lock=str(root / 'compiler.lock'),
                    parallel_sessions=1)

    def test_native_command_keeps_paths_and_environment_separate(self):
        with tempfile.TemporaryDirectory() as temp:
            root = Path(temp)
            (root / '00401000.cpp').write_text('synthetic')
            with patch('subprocess.run', return_value=subprocess.CompletedProcess([], 1)) as run:
                self.assertEqual(sweep.compile_native_batch(self.config(root), [0x401000], root, ['/O2']), [])
            args, kwargs = run.call_args
            self.assertEqual(args[0][0], str(root / 'compiler with spaces/CL.EXE'))
            self.assertEqual(args[0][-1], str(root / '00401000.cpp'))
            self.assertNotIn('CL', kwargs['env'])
            self.assertEqual(kwargs['timeout'], 180)

    def test_timeout_removes_only_the_partial_unit_object(self):
        with tempfile.TemporaryDirectory() as temp:
            root = Path(temp)
            unrelated = root / 'other.obj'; unrelated.write_bytes(b'untouched')
            def timeout(*args, **kwargs):
                (root / '00401000.obj').write_bytes(b'partial')
                raise subprocess.TimeoutExpired(args[0], 0.01)
            with patch('subprocess.run', side_effect=timeout):
                hung = sweep.compile_native_batch(self.config(root), [0x401000], root, ['/O2'], timeout=0.01)
            self.assertEqual(hung, [0x401000])
            self.assertFalse((root / '00401000.obj').exists())
            self.assertEqual(unrelated.read_bytes(), b'untouched')


if __name__ == '__main__':
    unittest.main()
