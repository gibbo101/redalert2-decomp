"""Native Win32 CRT va_list declarations stay scoped to explicit type use."""
from pathlib import Path
import sys
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools/original_target'))
import seed_candidate as seed


class VaListTypes(unittest.TestCase):
    def test_import_prototype_dependency(self):
        declaration = ('extern "C" DWORD __stdcall FormatMessageA(DWORD, LPCVOID, DWORD, '
                       'DWORD, LPSTR, DWORD, va_list *);')
        self.assertIn('typedef char *va_list;', seed.sdk_preamble('{}\n' + declaration))

    def test_local_and_parameter_type(self):
        for body, params in (('{ va_list *arguments; }', ()), ('{}', ('va_list arguments',))):
            with self.subTest(body=body, params=params):
                self.assertEqual(seed.sdk_preamble(body, params).count('typedef char *va_list;'), 1)

    def test_result_type(self):
        self.assertIn('typedef char *va_list;', seed.sdk_preamble('{}', result='va_list'))

    def test_unrelated_seed_text_is_identical(self):
        self.assertEqual(seed.sdk_preamble('{ int ordinary; }'), seed.SDK_PREAMBLE)

    def test_comments_literals_and_larger_identifiers_do_not_trigger(self):
        for body in ('{ /* va_list */ use("va_list"); }', '{ int custom_va_list; }'):
            with self.subTest(body=body):
                self.assertEqual(seed.sdk_preamble(body), seed.SDK_PREAMBLE)

    def test_authored_types_remain_owned(self):
        for body in ('{ typedef int va_list; va_list value; }',
                     '{ struct va_list { int member; }; }', '{ struct va_list; }'):
            with self.subTest(body=body):
                self.assertEqual(seed.sdk_preamble(body), seed.SDK_PREAMBLE)

    def test_shadowing_identifiers_remain_owned(self):
        self.assertEqual(seed.sdk_preamble('{ int va_list; }'), seed.SDK_PREAMBLE)
        self.assertEqual(seed.sdk_preamble('{}', ('int va_list',)), seed.SDK_PREAMBLE)

    def test_macros_and_callable_names_remain_unresolved(self):
        for body in ('#define va_list other\n{ va_list value; }', '#undef va_list\n{}', '{ va_list(); }'):
            with self.subTest(body=body):
                self.assertEqual(seed.sdk_preamble(body), seed.SDK_PREAMBLE)

    def test_no_sdk_include_macro_or_helper_body(self):
        text = seed.sdk_preamble('{ va_list arguments; }')
        self.assertNotIn('#include', text)
        self.assertNotIn('#define', text)
        self.assertNotIn('__forceinline', text)
        self.assertNotIn('__asm', text)


if __name__ == '__main__':
    unittest.main()
