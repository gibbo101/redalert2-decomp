"""Known Windows interface names stay local and do not replace opaque types."""
from pathlib import Path
import sys
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools/original_target'))
import seed_candidate as seed


class SDKRecordTests(unittest.TestCase):
    def test_unrelated_seeds_keep_their_previous_text(self):
        self.assertEqual(seed.sdk_preamble('{ int value; return value; }'), seed.SDK_PREAMBLE)

    def test_literals_and_comments_are_not_type_use(self):
        self.assertEqual(seed.sdk_preamble('{use("tagPOINT ULONG _WIN32_FIND_DATAA"); /* ULONG */}'), seed.SDK_PREAMBLE)

    def test_point_tag_and_pointer_alias_share_one_record(self):
        text = seed.sdk_preamble('{tagPOINT point; point.x=1;}')
        self.assertIn('struct tagPOINT { LONG x, y; };\ntypedef tagPOINT POINT;', text)
        self.assertIn('typedef POINT *LPPOINT;', text)
        self.assertNotIn('struct POINT {', text)

    def test_elaborated_point_tag_in_signature(self):
        text = seed.sdk_preamble('{}', ['struct tagPOINT *point'])
        self.assertIn('struct tagPOINT {', text)

    def test_record_tag_and_typedef_are_complete(self):
        for kind in ('_WIN32_FIND_DATAA', 'WIN32_FIND_DATAA'):
            with self.subTest(kind=kind):
                text = seed.sdk_preamble('{'+kind+' find; find.dwFileAttributes=0;}')
                self.assertIn('struct _WIN32_FIND_DATAA {', text)
                self.assertIn('typedef _WIN32_FIND_DATAA WIN32_FIND_DATAA;', text)
                self.assertIn('CHAR cFileName[260], cAlternateFileName[14];', text)
                self.assertNotIn('struct WIN32_FIND_DATAA;', text)

    def test_record_pointer_signature_uses_same_type(self):
        for kind in ('PWIN32_FIND_DATAA', 'LPWIN32_FIND_DATAA'):
            self.assertIn('struct _WIN32_FIND_DATAA {', seed.sdk_preamble('{}', [kind+' find']))

    def test_callee_declaration_needs_the_record(self):
        text = seed.sdk_preamble('{return call();}\nextern WIN32_FIND_DATAA *call();')
        self.assertIn('struct _WIN32_FIND_DATAA {', text)

    def test_unsigned_long_spelling_keeps_windows_width(self):
        self.assertTrue(seed.sdk_preamble('{ULONG count;}').endswith('typedef unsigned long ULONG;'))
        self.assertTrue(seed.sdk_preamble('{}', result='ULONG').endswith('typedef unsigned long ULONG;'))

    def test_existing_authored_types_are_not_redefined(self):
        for body in ('{typedef int ULONG; ULONG value;}',
                     '{struct tagPOINT {short x,y;}; tagPOINT point;}',
                     '{struct _WIN32_FIND_DATAA {int custom;}; _WIN32_FIND_DATAA find;}'):
            self.assertEqual(seed.sdk_preamble(body), seed.SDK_PREAMBLE)

    def test_identifiers_do_not_turn_into_type_aliases(self):
        for kind in ('ULONG', 'tagPOINT', '_WIN32_FIND_DATAA'):
            self.assertEqual(seed.sdk_preamble('{int '+kind+';}'), seed.SDK_PREAMBLE)
            self.assertEqual(seed.sdk_preamble('{}', ['int '+kind]), seed.SDK_PREAMBLE)

    def test_macros_and_function_names_stay_unresolved(self):
        self.assertEqual(seed.sdk_preamble('#define ULONG custom\n{ULONG value;}'), seed.SDK_PREAMBLE)
        self.assertEqual(seed.sdk_preamble('{ULONG();}'), seed.SDK_PREAMBLE)

    def test_unknown_and_unicode_records_are_not_guessed(self):
        text = seed.sdk_preamble('{_WIN32_FIND_DATAW wide; UnknownRecord game;}')
        self.assertEqual(text, seed.SDK_PREAMBLE)
        self.assertNotIn('struct _WIN32_FIND_DATAW', text)

    def test_wide_character_alias_composes_with_point_record(self):
        text = seed.sdk_preamble('{tagPOINT point; wchar_t *text;}')
        self.assertIn('struct tagPOINT {', text)
        self.assertTrue(text.endswith('typedef wchar16 wchar_t;'))

    def test_separate_namespaces_receive_all_required_declarations(self):
        a = seed.sdk_preamble('{WIN32_FIND_DATAA find;}')
        b = seed.sdk_preamble('{WIN32_FIND_DATAA another;}')
        self.assertEqual(a, b)
        self.assertNotIn('#ifndef', a)


if __name__ == '__main__':
    unittest.main()
