"""Preserved high bytes are storage, not a four-byte load at byte offset one."""
from pathlib import Path
import sys
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools/original_target'))
import seed_candidate as seed


class ByteUpdateTests(unittest.TestCase):
    def convert(self, statement, declarations='uint slot;', params=()):
        return seed.byte_update_artifacts('{\n  '+declarations+'\n  '+statement+'\n}', params)

    def test_uninitialized_high_bytes_are_not_read(self):
        text = self.convert('slot = CONCAT31(slot._1_3_,1);')
        self.assertIn('*(uchar *)&(slot) = (uchar)(1);', text)
        self.assertNotIn('CONCAT', text)
        self.assertNotIn('slot._1_3_', text)
        self.assertNotIn('uint *', text)

    def test_constant_array_element_uses_its_declared_slot(self):
        text = self.convert('slots[0] = CONCAT31(slots[0]._1_3_,1);', 'uint slots[2];')
        self.assertIn('*(uchar *)&(slots[0]) = (uchar)(1);', text)

    def test_pointer_representation_can_receive_a_byte_store(self):
        text = self.convert('slots[0] = (undefined **)CONCAT31(slots[0]._1_3_,flag);',
                            'undefined **slots[2];')
        self.assertIn('*(uchar *)&(slots[0]) = (uchar)(flag);', text)

    def test_parameter_slot_requires_a_declared_four_byte_type(self):
        text = self.convert('slot = CONCAT31(slot._1_3_,flag);', '', ['uint slot'])
        self.assertIn('*(uchar *)&(slot)', text)

    def test_low_mask_preserves_high_bytes_and_evaluates_the_load_once(self):
        text = self.convert('slot = CONCAT31(slot._1_3_,*(byte *)p >> 2) &\n    0xffffff01;')
        self.assertIn('(uchar)(*(byte *)p >> 2) & 0x01', text)
        self.assertEqual(text.count('*(byte *)p'), 1)

    def test_nested_scalar_casts_are_not_calls(self):
        text = self.convert('slot = CONCAT31(slot._1_3_,(char)((uint)*p >> 8)) & 0xffffff01;')
        self.assertIn('*(uchar *)&(slot)', text)

    def test_boolean_comparison_keeps_its_full_expression(self):
        text = self.convert("slot = CONCAT31(slot._1_3_,flag != '\\0');")
        self.assertIn('*(uchar *)&(slot)', text)
        self.assertIn("flag != '\\0'", text)

    def test_other_storage_widths_and_unknown_types_are_unchanged(self):
        for kind in ('short', 'byte', 'undefined3', 'ulonglong', 'float', 'double', 'Unknown'):
            with self.subTest(kind=kind):
                text = self.convert('slot = CONCAT31(slot._1_3_,1);', kind+' slot;')
                self.assertIn('CONCAT31', text)

    def test_const_and_volatile_slots_are_unchanged(self):
        for kind in ('const uint', 'volatile uint', 'volatile int *'):
            self.assertIn('CONCAT31', self.convert('slot = CONCAT31(slot._1_3_,1);', kind+' slot;'))

    def test_unknown_global_and_pointer_pointee_are_unchanged(self):
        self.assertIn('CONCAT31', self.convert('DAT_00801000 = CONCAT31(DAT_00801000._1_3_,1);'))
        self.assertIn('CONCAT31', self.convert('slot[0] = CONCAT31(slot[0]._1_3_,1);', 'uint *slot;'))

    def test_different_preserved_slot_is_unchanged(self):
        self.assertIn('CONCAT31', self.convert('slot = CONCAT31(other._1_3_,1);'))

    def test_dynamic_side_effecting_and_out_of_range_indices_are_unchanged(self):
        for index in ('i', 'i++', 'get()', '2'):
            text = self.convert('slots['+index+'] = CONCAT31(slots['+index+']._1_3_,1);', 'uint slots[2];')
            self.assertIn('CONCAT31', text)

    def test_masks_changing_high_bytes_and_other_suffixes_are_unchanged(self):
        for suffix in (' & 0xffff0001', ' | 1', ' >> 8', ' + 1', ' & 0x1ffffffff'):
            self.assertIn('CONCAT31', self.convert('slot = CONCAT31(slot._1_3_,1)'+suffix+';'))

    def test_used_assignment_result_is_unchanged(self):
        for statement in ('return slot = CONCAT31(slot._1_3_,1);',
                          'if (slot = CONCAT31(slot._1_3_,1)) use();',
                          'use(slot = CONCAT31(slot._1_3_,1));',
                          'slot = CONCAT31(slot._1_3_,1), use(slot);'):
            self.assertIn('CONCAT31', self.convert(statement))

    def test_line_break_does_not_hide_a_used_assignment(self):
        for prefix in ('return\n  ', 'result =\n  ', 'use(\n  ', 'if (\n  '):
            self.assertIn('CONCAT31', self.convert(prefix+'slot = CONCAT31(slot._1_3_,1);'))

    def test_effectful_low_expression_is_unchanged(self):
        for value in ('get()', '(*fn)()', '(fn)(x)', '++flag', 'flag++', 'flag = 1', '(a,b)'):
            self.assertIn('CONCAT31', self.convert('slot = CONCAT31(slot._1_3_,'+value+');'))

    def test_comments_and_literals_remain_untouched(self):
        body = '{\n  uint slot;\n  // slot = CONCAT31(slot._1_3_,1);\n  use("slot = CONCAT31(slot._1_3_,1);");\n}'
        self.assertEqual(seed.byte_update_artifacts(body), body)

    def test_indentation_and_multiple_updates_are_preserved(self):
        text = self.convert('slot = CONCAT31(slot._1_3_,1);\n  slot = CONCAT31(slot._1_3_,0);')
        self.assertEqual(text.count('  *(uchar *)&(slot)'), 2)

    def test_complete_seed_repairs_before_concat_and_storage_conversion(self):
        class FakeInventory:
            passes = []

            def decompiled(self, entry):
                return ('int __cdecl FUN_00401000(void)\n{\n  uint slots[2];\n'
                        '  slots[0] = CONCAT31(slots[0]._1_3_,1);\n  return slots[0];\n}\n')

            def function(self, entry):
                return None, {'ranges': []}

        text = seed.seed(0x401000, FakeInventory(), {})
        self.assertIn('*(uchar *)&(slots[0]) = (uchar)(1);', text)
        self.assertIn('return (int)(slots[0]);', text)
        self.assertNotIn('._1_3_', text)
        self.assertNotIn('CONCAT31', text)


if __name__ == '__main__':
    unittest.main()
