"""An unrepresentable original RET immediate must never be rounded into fake parameters."""
from pathlib import Path
import sys
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools/original_target'))
import seed_candidate as seed


class CleanupRefusals(unittest.TestCase):
    def test_non_word_cleanup_is_refused_in_every_generated_convention(self):
        for convention, params in [('', []), ('__cdecl', []), ('__stdcall', []),
                                   ('__fastcall', ['int ecx', 'int edx']), ('__thiscall', ['int *this'])]:
            for popped in (1, 3, 7, 0xF8C1):
                with self.subTest(convention=convention, popped=popped):
                    with self.assertRaisesRegex(ValueError, 'Non-DWORD return cleanup'):
                        seed.fit_convention(convention, params, popped, convention == '__thiscall')

    def test_representable_cleanup_keeps_existing_parameter_fit(self):
        self.assertEqual(seed.fit_convention('', [], 8, False), ('__stdcall', ['int unused_0', 'int unused_1']))
        self.assertEqual(seed.fit_convention('__thiscall', ['int *this', 'double value'], 8, True),
                         ('__thiscall', ['int *this', 'double value']))
        self.assertEqual(seed.fit_convention('__fastcall', ['int ecx', 'int edx', 'int stack'], 4, False),
                         ('__fastcall', ['int ecx', 'int edx', 'int stack']))

    def test_plain_and_unknown_returns_keep_existing_behavior(self):
        self.assertEqual(seed.fit_convention('__stdcall', ['int value'], 0, False), ('__cdecl', ['int value']))
        self.assertEqual(seed.fit_convention('__thiscall', ['int *this'], None, True), ('__thiscall', ['int *this']))

    def test_synthetic_non_word_immediate_is_not_altered(self):
        row = dict(ranges=[dict(start='00401000', bytes_hex='c20300')])
        self.assertEqual(seed.stack_cleanup(row), 3)


if __name__ == '__main__':
    unittest.main()
