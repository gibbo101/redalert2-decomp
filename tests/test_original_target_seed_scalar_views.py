"""Merged storage keeps its bits; only evidenced primitive memory views change."""
from pathlib import Path
import sys
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]/'tools/original_target'))
import seed_candidate as seed


class ScalarAddressViewTests(unittest.TestCase):
    def body(self, use, kind='undefined4', assignment='slot = (int *)source;'):
        return '{\n  '+kind+' slot;\n  '+assignment+'\n  '+use+'\n}'

    def test_vtable_load_keeps_merged_slot_and_call_order(self):
        body = self.body('(**(code **)(*slot + 12))(slot);')
        text,notes = seed.scalar_address_views(body)
        self.assertIn('undefined4 slot;',text)
        self.assertIn('(**(code **)(*(int *)slot + 12))(slot);',text)
        self.assertEqual(len(notes),1)
        self.assertIn('original-load/type proof still required',notes[0])

    def test_subscript_keeps_index_evaluation_and_element_width(self):
        text,_ = seed.scalar_address_views(self.body('result = slot[index++];'))
        self.assertIn('result = ((int *)slot)[index++];',text)
        self.assertEqual(text.count('index++'),1)

    def test_packed_partial_write_numeric_lifetime_and_out_address_unchanged(self):
        body = self.body('slot._2_2_ = high;\n  use(&slot);\n  slot = slot + 1;\n  result = *slot;')
        text,_ = seed.scalar_address_views(body)
        self.assertIn('slot._2_2_ = high;',text)
        self.assertIn('use(&slot);',text)
        self.assertIn('slot = slot + 1;',text)
        self.assertIn('result = *(int *)slot;',text)

    def test_signedness_of_explicit_pointee_is_retained(self):
        body = self.body('result = *slot;',assignment='slot = (unsigned int *)source;')
        self.assertIn('*(unsigned int *)slot;',seed.scalar_address_views(body)[0])

    def test_no_pointer_assignment_evidence_refuses(self):
        body = self.body('result = *slot;',assignment='slot = source;')
        self.assertEqual(seed.scalar_address_views(body),(body,[]))

    def test_conflicting_signed_unsigned_views_refuse(self):
        body = self.body('result = *slot;',assignment='slot = (int *)a; slot = (uint *)b;')
        self.assertEqual(seed.scalar_address_views(body),(body,[]))

    def test_narrow_wide_aggregate_void_and_const_views_refuse(self):
        for kind in ['char','short','double','undefined8','Owner','void','const int']:
            with self.subTest(kind=kind):
                body = self.body('result = *slot;',assignment='slot = ('+kind+' *)source;')
                self.assertEqual(seed.scalar_address_views(body),(body,[]))

    def test_non_dword_storage_is_not_retyped(self):
        for kind in ['char','short','double','ulonglong','int *']:
            with self.subTest(kind=kind):
                body = self.body('result = *slot;',kind=kind)
                self.assertEqual(seed.scalar_address_views(body),(body,[]))

    def test_existing_casted_load_does_not_gain_another_view(self):
        body = self.body('result = *(int *)slot;')
        self.assertEqual(seed.scalar_address_views(body),(body,[]))

    def test_multiple_dereference_does_not_guess_another_pointer_level(self):
        body = self.body('result = **slot;')
        self.assertEqual(seed.scalar_address_views(body),(body,[]))

    def test_pointer_to_pointer_assignment_refuses_primitive_view(self):
        body = self.body('result = *slot;',assignment='slot = (int **)source;')
        self.assertEqual(seed.scalar_address_views(body),(body,[]))

    def test_pointer_store_is_not_a_slot_assignment_hint(self):
        body = self.body('result = *slot;',assignment='*slot = (int *)source;')
        self.assertEqual(seed.scalar_address_views(body),(body,[]))

    def test_binary_multiplication_is_not_a_memory_load(self):
        body = self.body('result = count * slot;')
        self.assertEqual(seed.scalar_address_views(body),(body,[]))

    def test_multiplication_followed_by_unary_load_preserves_both(self):
        text,_ = seed.scalar_address_views(self.body('result = count * *slot;'))
        self.assertIn('result = count * *(int *)slot;',text)

    def test_member_and_qualified_names_are_not_local_memory_views(self):
        body = self.body('result = *obj.slot + *obj->slot + *Type::slot;')
        self.assertEqual(seed.scalar_address_views(body),(body,[]))

    def test_comments_and_literals_supply_no_hints_or_loads(self):
        body = self.body('use("*slot slot[0]"); /* *slot */',assignment='// slot = (int *)source;')
        self.assertEqual(seed.scalar_address_views(body),(body,[]))

    def test_duplicate_shadowed_declarations_and_parameter_names_refuse(self):
        body = self.body('result = *slot;\n  {\n    undefined4 slot;\n  }')
        self.assertEqual(seed.scalar_address_views(body),(body,[]))
        body = self.body('result = *slot;')
        self.assertEqual(seed.scalar_address_views(body,['undefined4 slot']),(body,[]))

    def test_array_declaration_is_not_scalar_storage(self):
        body = '{\n  undefined4 slot[8];\n  slot = (int *)source;\n  result = slot[1];\n}'
        self.assertEqual(seed.scalar_address_views(body),(body,[]))

    def test_integer_update_and_load_are_each_evaluated_once(self):
        text,_ = seed.scalar_address_views(self.body('result = *slot++;'))
        self.assertIn('result = *(int *)slot++;',text)
        self.assertEqual(text.count('slot++'),1)
        self.assertIn('undefined4 slot;',text)

    def test_idempotent_and_unrelated_slot_unchanged(self):
        text,_ = seed.scalar_address_views(self.body('result = *slot;'))
        self.assertEqual(seed.scalar_address_views(text),(text,[]))
        body = '{\n  undefined4 slot;\n  result = slot + 4;\n}'
        self.assertEqual(seed.scalar_address_views(body),(body,[]))


if __name__ == '__main__':
    unittest.main()
