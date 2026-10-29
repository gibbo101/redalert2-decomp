"""Only seeds using Windows wchar_t get their namespace-local two-byte alias."""
from pathlib import Path
import sys
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools/original_target'))
import seed_candidate as seed


class WindowsWideTypeTests(unittest.TestCase):
    def test_pointer_declaration_and_cast_need_the_alias(self):
        body = '{\n wchar_t *p;\n p=(wchar_t *)address;\n}'
        self.assertTrue(seed.sdk_preamble(body).endswith('typedef wchar16 wchar_t;'))

    def test_result_and_parameter_types_are_in_scope(self):
        self.assertTrue(seed.sdk_preamble('{}', result='wchar_t *').endswith('typedef wchar16 wchar_t;'))
        self.assertTrue(seed.sdk_preamble('{}', ['wchar_t *text']).endswith('typedef wchar16 wchar_t;'))

    def test_unaffected_seed_text_is_unchanged(self):
        self.assertEqual(seed.sdk_preamble('{ int value; }'), seed.SDK_PREAMBLE)

    def test_comments_and_literal_mentions_do_not_change_the_preamble(self):
        self.assertEqual(seed.sdk_preamble('{char *s="wchar_t"; /* wchar_t */}'), seed.SDK_PREAMBLE)

    def test_existing_typedef_is_preserved_without_another_alias(self):
        body = '{typedef unsigned short wchar_t; wchar_t *text;}'
        self.assertEqual(seed.sdk_preamble(body), seed.SDK_PREAMBLE)

    def test_parameter_and_local_identifiers_do_not_become_types(self):
        self.assertEqual(seed.sdk_preamble('{int wchar_t;}'), seed.SDK_PREAMBLE)
        self.assertEqual(seed.sdk_preamble('{}', ['int wchar_t']), seed.SDK_PREAMBLE)

    def test_two_seed_namespaces_each_receive_their_own_alias(self):
        a = seed.sdk_preamble('{wchar_t *a;}')
        b = seed.sdk_preamble('{wchar_t *b;}')
        self.assertEqual(a.count('typedef wchar16 wchar_t;'), 1)
        self.assertEqual(a, b)
        self.assertNotIn('_WCHAR_T_DEFINED', a)


if __name__ == '__main__':
    unittest.main()
