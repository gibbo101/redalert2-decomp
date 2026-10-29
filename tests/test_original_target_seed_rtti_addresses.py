"""Original RTTI address labels do not require invented class definitions."""
import sys
import unittest
from pathlib import Path
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools/original_target'))
import seed_candidate as seed


class RTTIAddressTests(unittest.TestCase):
    def test_class_and_struct_names(self):
        self.assertEqual(seed.rtti_address_names({'??_R0?AVObjectClass@@@8': 0x801000,
                                                '??_R0?AUCell@@@8': 0x802000}),
                         {'ObjectClass': 0x801000, 'Cell': 0x802000})

    def test_namespace_order(self):
        self.assertEqual(seed.rtti_address_names({'??_R0?AVConflict@WorldDominationTour@@@8': 0x801000}),
                         {'WorldDominationTour::Conflict': 0x801000})

    def test_ambiguous_class_struct_name_does_not_bind(self):
        self.assertEqual(seed.rtti_address_names({'??_R0?AVThing@@@8': 0x801000,
                                                '??_R0?AUThing@@@8': 0x802000}), {})

    def test_unsupported_template_and_non_descriptor_do_not_bind(self):
        self.assertEqual(seed.rtti_address_names({'??_R0?AV?$VectorClass@H@@@8': 0x801000,
                                                '??_7type_info@@6B@': 0x802000}), {})

    def test_address_is_replaced_once_with_existing_dat_label(self):
        text = 'return f((uint)&ObjectClass::RTTI_Type_Descriptor);'
        result, notes = seed.rtti_address_labels(text, {'ObjectClass': 0x801000})
        self.assertEqual(result, 'return f((uint)&DAT_00801000);')
        self.assertEqual(len(notes), 1)

    def test_namespaced_address(self):
        result, _ = seed.rtti_address_labels('f(&WorldDominationTour::Conflict::RTTI_Type_Descriptor);',
                                             {'WorldDominationTour::Conflict': 0x801000})
        self.assertEqual(result, 'f(&DAT_00801000);')

    def test_repeated_address_keeps_both_evaluations_and_one_note(self):
        result, notes = seed.rtti_address_labels('f(&A::RTTI_Type_Descriptor, &A::RTTI_Type_Descriptor);', {'A': 0x801000})
        self.assertEqual(result.count('&DAT_00801000'), 2)
        self.assertEqual(len(notes), 1)

    def test_unknown_name_is_unchanged(self):
        text = 'f(&Unknown::RTTI_Type_Descriptor);'
        self.assertEqual(seed.rtti_address_labels(text, {}), (text, []))

    def test_direct_value_is_not_an_address(self):
        text = 'f(A::RTTI_Type_Descriptor);'
        self.assertEqual(seed.rtti_address_labels(text, {'A': 0x801000}), (text, []))

    def test_comments_and_literals_unchanged(self):
        text = '// &A::RTTI_Type_Descriptor\nchar *s="&A::RTTI_Type_Descriptor";'
        self.assertEqual(seed.rtti_address_labels(text, {'A': 0x801000}), (text, []))

    def test_pointer_arithmetic_and_member_or_index_access_remain_unsupported(self):
        for suffix in [' + 1;', ' - 1;', '[2];', '.field;', '->field;', '::other;']:
            with self.subTest(suffix=suffix):
                text = '&A::RTTI_Type_Descriptor' + suffix
                self.assertEqual(seed.rtti_address_labels(text, {'A': 0x801000}), (text, []))

    def test_parenthesized_address_arithmetic_is_not_retyped(self):
        text = '(&A::RTTI_Type_Descriptor) + 1;'
        self.assertEqual(seed.rtti_address_labels(text, {'A': 0x801000}), (text, []))

    def test_descriptor_dereference_and_sizeof_object_are_not_modeled(self):
        for text in ['* &A::RTTI_Type_Descriptor;', '*((&A::RTTI_Type_Descriptor));',
                     'sizeof *(&A::RTTI_Type_Descriptor);']:
            self.assertEqual(seed.rtti_address_labels(text, {'A': 0x801000}), (text, []))

    def test_logical_and_is_not_address_of(self):
        text = 'value && A::RTTI_Type_Descriptor;'
        self.assertEqual(seed.rtti_address_labels(text, {'A': 0x801000}), (text, []))

    def test_empty_input_does_not_open_private_target(self):
        with patch.object(seed, 'original_rtti_addresses', side_effect=AssertionError('unexpected target read')):
            self.assertEqual(seed.rtti_address_labels('return 0;'), ('return 0;', []))

    def test_invalid_target_addresses_are_not_used(self):
        for value in [None, True, -1, 0, 0x100000000]:
            self.assertEqual(seed.rtti_address_labels('f(&A::RTTI_Type_Descriptor);', {'A': value}),
                             ('f(&A::RTTI_Type_Descriptor);', []))

    def test_complete_seed_declares_address_storage_without_a_fake_class(self):
        class FakeInventory:
            passes = []

            def decompiled(self, entry):
                return 'void __cdecl FUN_00401000(void)\n{\n  void *p;\n  p = &A::RTTI_Type_Descriptor;\n}\n'

            def function(self, entry):
                return None, {'ranges': []}

        with patch.object(seed, 'original_rtti_addresses', return_value={'A': 0x801000}):
            text = seed.seed(0x401000, FakeInventory(), {})
        self.assertIn('extern "C" undefined4 DAT_00801000;', text)
        self.assertIn('&DAT_00801000', text)
        self.assertNotIn('A::RTTI_Type_Descriptor', text)
        self.assertNotIn('class A', text)


if __name__ == '__main__':
    unittest.main()
