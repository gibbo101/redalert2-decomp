import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools/original_target'))
import seed_candidate as seed


class CastIndirectionTests(unittest.TestCase):
    def test_pointer_cast_followed_by_load_preserves_the_load(self):
        body = '{\n  (**(code **)*DAT_00801000)(1);\n}'
        changed, globals_ = seed.recover_global_pointers(body)
        self.assertEqual(changed, body)
        self.assertEqual(globals_['DAT_00801000'], 'undefined4 *')

    def test_scalar_cast_applies_to_the_loaded_value(self):
        body = '{\n  return (uint)*DAT_00801000 + 4;\n}'
        changed, globals_ = seed.recover_global_pointers(body)
        self.assertIn('(uint)*DAT_00801000 + 4', changed)
        self.assertNotIn('*(uint)DAT_00801000', changed)
        self.assertEqual(globals_['DAT_00801000'], 'undefined4 *')

    def test_casted_load_through_incrementing_pointer_evaluates_it_once(self):
        text = '(code **)*DAT_00801000++'
        self.assertTrue(seed.unary_operator(text, text.index('*DAT')))
        body = '{\n  return (uint)*DAT_00801000++;\n}'
        changed, _ = seed.recover_global_pointers(body)
        self.assertEqual(changed.count('DAT_00801000++'), 1)
        self.assertNotIn('*(uint)DAT', changed)

    def test_namespace_and_const_pointer_casts_are_unary(self):
        for text in ('(Owner *)*DAT', '(const Owner **)*DAT', '(outer::Owner *)*DAT', '(unsigned long)*DAT'):
            with self.subTest(text=text):
                self.assertTrue(seed.unary_operator(text, text.index('*DAT')))

    def test_parenthesized_values_and_call_results_remain_multiplication(self):
        for text in ('(value)*DAT', '(value + 1)*DAT', 'f()*DAT', 'f(uint)*DAT',
                     'sizeof(uint)*DAT', '(callback)(uint)*DAT', 'array[index]*DAT'):
            with self.subTest(text=text):
                self.assertFalse(seed.unary_operator(text, text.index('*DAT')))

    def test_typed_pointer_as_integer_in_binary_multiplication_still_casts(self):
        body = '{\n  int *pointer;\n  pointer = DAT_00801000;\n  return (value) * DAT_00801000;\n}'
        changed, _ = seed.recover_global_pointers(body)
        self.assertIn('(value) * (uint)DAT_00801000', changed)

    def test_ambiguous_unknown_scalar_typedef_stays_unresolved(self):
        text = '(unknown_name)*DAT'
        self.assertFalse(seed.unary_operator(text, text.index('*DAT')))

    def test_original_precedence_in_nested_casted_load_is_unchanged(self):
        body = '{\n  return (uint)*(uint **)*DAT_00801000;\n}'
        changed, _ = seed.recover_global_pointers(body)
        self.assertEqual(changed, body)


class OpaqueGlobalOffsetTests(unittest.TestCase):
    facts = {'PTR_DAT_00801000': 'void *'}

    def test_raw_byte_field_offset_keeps_the_explicit_word_load(self):
        body = 'return *(ushort *)(PTR_DAT_00801000 + 24);'
        self.assertEqual(seed.cast_void_global_offsets(body, self.facts),
                         'return *(ushort *)((uint)PTR_DAT_00801000 + 24);')

    def test_pointer_store_retains_both_pointer_load_and_destination_width(self):
        body = '*(void **)(PTR_DAT_00801000 + 4) = value;'
        self.assertEqual(seed.cast_void_global_offsets(body, self.facts),
                         '*(void **)((uint)PTR_DAT_00801000 + 4) = value;')

    def test_subtraction_uses_address_bits_once(self):
        body = 'return *(int *)(PTR_DAT_00801000 - 0x10);'
        self.assertIn('(uint)PTR_DAT_00801000 - 0x10', seed.cast_void_global_offsets(body, self.facts))

    def test_address_of_storage_and_unknown_dereference_are_not_cast(self):
        for body in ('return &PTR_DAT_00801000 + 4;', 'return *PTR_DAT_00801000 + 4;'):
            with self.subTest(body=body):
                self.assertEqual(seed.cast_void_global_offsets(body, self.facts), body)

    def test_existing_integer_view_is_unchanged(self):
        for kind in ('uint', 'int', 'unsigned int'):
            body = 'return (' + kind + ')PTR_DAT_00801000 + 4;'
            self.assertEqual(seed.cast_void_global_offsets(body, self.facts), body)

    def test_real_pointee_stride_is_preserved(self):
        body = 'return *(PTR_DAT_00801000 + 4);'
        self.assertEqual(seed.cast_void_global_offsets(body, {'PTR_DAT_00801000': 'int *'}), body)

    def test_indexing_variable_offsets_and_pointer_differences_remain_unresolved(self):
        for body in ('return PTR_DAT_00801000[index];', 'return PTR_DAT_00801000 + index;',
                     'return PTR_DAT_00801000 - other;', 'return PTR_DAT_00801000 + 4.5;',
                     'return PTR_DAT_00801000 + 4e2;', 'PTR_DAT_00801000 += 4;'):
            with self.subTest(body=body):
                self.assertEqual(seed.cast_void_global_offsets(body, self.facts), body)

    def test_comments_and_strings_do_not_change(self):
        body = '// PTR_DAT_00801000 + 4\nuse("PTR_DAT_00801000 + 4");'
        self.assertEqual(seed.cast_void_global_offsets(body, self.facts), body)


if __name__ == '__main__':
    unittest.main()
