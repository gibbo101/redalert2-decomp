import unittest
from pathlib import Path
import sys
from unittest.mock import patch
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools/original_target'))
import seed_candidate as experiment


class BoundaryTests(unittest.TestCase):
    def convert(self, expression, declarations='int *p;\n  int *a;'):
        body = '{\n  ' + declarations + '\n  return ' + expression + ';\n}'
        return experiment.full_pointer_equality(body)

    def test_loaded_int_keeps_dereference(self):
        self.assertIn('*(int *)(a + 3) == (uint)(p)', self.convert('*(int *)(a + 3) == p'))
    def test_loaded_array_value_keeps_subscript(self):
        self.assertIn('(uint)(p) != a[4]', self.convert('p != a[4]'))
    def test_loaded_pointer_cast_wraps_the_entire_value(self):
        self.assertIn('(uint)((uint *)a[3]) == (uint)(&p)', self.convert('(uint *)a[3] == &p'))
    def test_read_width_and_evaluation_count_are_preserved(self):
        text = self.convert('*(uint *)(a++) == p')
        self.assertIn('*(uint *)(a++) == (uint)(p)', text)
        self.assertEqual(text.count('a++'), 1)
    def test_sdk_pointer_null_cast_against_stored_dword(self):
        text = self.convert('value != (HWND)0x0', 'undefined4 value;')
        self.assertIn('value != (uint)((HWND)0x0)', text)
    def test_index_through_loaded_pointer_keeps_both_reads(self):
        text = self.convert('(*(int **)(a + 7))[0x6d] == p')
        self.assertIn('(*(int **)(a + 7))[0x6d] == (uint)(p)', text)
    def test_outer_boolean_and_assignment_boundaries(self):
        body = '{\n  int *p;\n  int *a;\n  int result;\n  result = a[1] != 0 && p == a[2] || a[3] == 0;\n}'
        self.assertIn('a[1] != 0 && (uint)(p) == a[2] || a[3] == 0', experiment.full_pointer_equality(body))
    def test_same_type_bare_pointers_are_unchanged(self):
        self.assertIn('return p == a;', self.convert('p == a'))
    def test_scalar_loaded_value_comparison_is_unchanged(self):
        self.assertIn('return *p == value;', self.convert('*p == value', 'int *p;\n  int value;'))
    def test_existing_uint_view_is_not_rewritten(self):
        self.assertIn('return (uint)p == value;', self.convert('(uint)p == value', 'int *p;\n  uint value;'))
    def test_float_wide_small_and_unknown_values_are_refused(self):
        for expression in ('*(float *)a == p', '*(longlong *)a == p', '*(char *)a == p', 'unknown(a) == p', 'a[0]+1 == p'):
            with self.subTest(expression=expression):
                self.assertIn('return ' + expression + ';', self.convert(expression))
    def test_relational_and_chained_comparisons_are_unchanged(self):
        for expression in ('p < a[0]', 'p == value == a', 'p != value != a'):
            with self.subTest(expression=expression):
                self.assertIn('return ' + expression + ';', self.convert(expression, 'int *p;\n  int *a;\n  int value;'))
    def test_comments_and_strings_are_untouched(self):
        body = '{\n  int *p;\n  int *a;\n  // p == a[0]\n  use("p == a[1]");\n}'
        self.assertEqual(experiment.full_pointer_equality(body), body)
    def test_known_import_alias_references_only(self):
        body = '{ use(ShowWindow_exref); use(Unknown_exref); use("ShowWindow_exref"); }'
        self.assertEqual(experiment.normalize_import_exrefs(body, {'ShowWindow':{}}),
                         '{ use(ShowWindow); use(Unknown_exref); use("ShowWindow_exref"); }')
    def test_address_only_import_gets_recorded_declaration_and_binding(self):
        fact = dict(name='KnownAPI',convention='__stdcall',signature='int __stdcall KnownAPI(int value)',iat='0079a000')
        with patch.object(experiment, '_IMPORTS', [{'KnownAPI':fact}]):
            body = experiment.normalize_import_exrefs('{ use(KnownAPI_exref); }')
            self.assertEqual(experiment.imported_calls(body), {'KnownAPI':fact})
            changed, declaration = experiment.declare_import(body,'KnownAPI',fact)
        self.assertEqual(changed, '{ use(KnownAPI); }')
        self.assertIn('__declspec(dllimport)',declaration)
        self.assertIn('__imp__KnownAPI@4=0079a000',declaration)
    def test_address_only_unknown_import_abi_still_refuses(self):
        with self.assertRaisesRegex(ValueError, 'signature/convention unavailable'):
            experiment.declare_import('{ use(KnownAPI); }','KnownAPI',dict(name='KnownAPI',iat='0079a000'))
    def test_import_mentions_in_strings_and_comments_add_no_declaration(self):
        with patch.object(experiment,'_IMPORTS',[{'KnownAPI':{}}]):
            self.assertEqual(experiment.imported_calls('{ use("KnownAPI"); /* KnownAPI */ }'),{})
    def test_integrated_boundary_fix_uses_global_pointer_facts(self):
        body = '{\n  int *values;\n  return values[3] == DAT_00801000;\n}'
        text = experiment.pointer_equality_boundaries(body,globals_={'DAT_00801000':'Owner *'})
        self.assertIn('values[3] == (uint)(DAT_00801000)',text)
    def test_integrated_bare_float_and_wide_equalities_remain_unmodified(self):
        for kind in ('float','double','longlong','ulonglong','unsigned __int64'):
            with self.subTest(kind=kind):
                body='{\n  '+kind+' value;\n  int *pointer;\n  return value == pointer;\n}'
                self.assertEqual(experiment.pointer_equality_boundaries(body),body)


if __name__ == '__main__':
    unittest.main(verbosity=2)
