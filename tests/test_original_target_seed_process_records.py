"""Explicit documented Win32 records retain complete layouts and type ownership."""
from pathlib import Path
import sys
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools/original_target'))
import seed_candidate as seed


class ProcessRecordTypes(unittest.TestCase):
    def test_startup_tag_and_alias(self):
        for kind in ('_STARTUPINFOA', 'STARTUPINFOA', 'LPSTARTUPINFOA'):
            with self.subTest(kind=kind):
                text = seed.sdk_preamble('{}', (kind + ' value',))
                self.assertIn('struct _STARTUPINFOA {', text)
                self.assertIn('WORD wShowWindow, cbReserved2;', text)
                self.assertIn('LPBYTE lpReserved2;', text)
                self.assertIn('HANDLE hStdInput, hStdOutput, hStdError;', text)
                self.assertNotIn('struct STARTUPINFOA;', text)

    def test_process_tag_pointer_and_result(self):
        for kind in ('_PROCESS_INFORMATION', 'PROCESS_INFORMATION', 'PPROCESS_INFORMATION', 'LPPROCESS_INFORMATION'):
            with self.subTest(kind=kind):
                text = seed.sdk_preamble('{}', result=kind)
                self.assertIn('struct _PROCESS_INFORMATION {', text)
                self.assertIn('DWORD dwProcessId, dwThreadId;', text)
                self.assertNotIn('struct PROCESS_INFORMATION;', text)

    def test_codepage_tag_alias_and_pointer(self):
        for kind in ('_cpinfo', 'CPINFO', 'LPCPINFO'):
            with self.subTest(kind=kind):
                text = seed.sdk_preamble('{ ' + kind + ' value; }')
                self.assertIn('struct _cpinfo {', text)
                self.assertIn('BYTE DefaultChar[2];', text)
                self.assertIn('BYTE LeadByte[12];', text)

    def test_import_prototype_dependencies(self):
        text = seed.sdk_preamble('extern void f(LPSTARTUPINFOA, LPPROCESS_INFORMATION, LPCPINFO);')
        self.assertIn('struct _STARTUPINFOA {', text)
        self.assertIn('struct _PROCESS_INFORMATION {', text)
        self.assertIn('struct _cpinfo {', text)

    def test_scalar_sdk_aliases(self):
        self.assertIn('typedef DWORD LCTYPE;', seed.sdk_preamble('{ LCTYPE flags; }'))
        self.assertIn('typedef WCHAR OLECHAR;', seed.sdk_preamble('{}', ('OLECHAR *name',)))

    def test_unrelated_seed_stays_identical(self):
        self.assertEqual(seed.sdk_preamble('{ int ordinary; }'), seed.SDK_PREAMBLE)

    def test_comments_literals_and_larger_names_do_not_trigger(self):
        self.assertEqual(seed.sdk_preamble('{ use("_STARTUPINFOA CPINFO LCTYPE OLECHAR"); /* _cpinfo */ }'), seed.SDK_PREAMBLE)
        self.assertEqual(seed.sdk_preamble('{ int my_STARTUPINFOA; }'), seed.SDK_PREAMBLE)

    def test_authored_alias_blocks_coupled_record(self):
        for body in ('{ typedef int _STARTUPINFOA; }', '{ typedef int STARTUPINFOA; }', '{ typedef int LPSTARTUPINFOA; }'):
            with self.subTest(body=body):
                self.assertNotIn('struct _STARTUPINFOA {', seed.sdk_preamble(body, ('LPSTARTUPINFOA value',)))

    def test_authored_record_and_forward_declaration_block(self):
        for body in ('{ struct _PROCESS_INFORMATION { int own; }; }', '{ struct _PROCESS_INFORMATION; }'):
            self.assertNotIn('struct _PROCESS_INFORMATION {', seed.sdk_preamble(body, ('LPPROCESS_INFORMATION value',)))

    def test_record_identifier_and_macro_shadows_block_group(self):
        for body in ('{ int _cpinfo; }', '#define CPINFO custom\n{}', '{ CPINFO(); }'):
            self.assertNotIn('struct _cpinfo {', seed.sdk_preamble(body, ('LPCPINFO value',)))

    def test_scalar_alias_shadows_remain_owned(self):
        for name in ('LCTYPE', 'OLECHAR'):
            self.assertEqual(seed.sdk_preamble('{ int ' + name + '; }'), seed.SDK_PREAMBLE)
            self.assertEqual(seed.sdk_preamble('#define ' + name + ' other\n{}'), seed.SDK_PREAMBLE)

    def test_one_record_conflict_does_not_erase_other_groups(self):
        text = seed.sdk_preamble('{ typedef int CPINFO; }', ('LPSTARTUPINFOA startup', 'LPCPINFO codepage'))
        self.assertIn('struct _STARTUPINFOA {', text)
        self.assertNotIn('struct _cpinfo {', text)

    def test_unknown_unicode_and_game_records_remain_incomplete(self):
        text = seed.sdk_preamble('{ _STARTUPINFOW wide; GameProcess game; }')
        self.assertEqual(text, seed.SDK_PREAMBLE)

    def test_no_sdk_include_macro_helper_or_global_guard(self):
        text = seed.sdk_preamble('{ STARTUPINFOA startup; CPINFO codepage; }')
        for forbidden in ('#include', '#define', '__forceinline', '__asm'):
            self.assertNotIn(forbidden, text)


if __name__ == '__main__':
    unittest.main()
