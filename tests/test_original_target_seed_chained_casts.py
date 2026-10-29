"""C-style casts preserve a following memory load; calls still multiply."""
from pathlib import Path
import sys
import unittest

sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'tools/original_target'))
import seed_candidate as seed


class ChainedCastTests(unittest.TestCase):
    def unary(self,expression):
        return seed.unary_operator(expression,expression.index('*DAT'))

    def test_multiple_scalar_casts_precede_one_unary_load(self):
        self.assertTrue(self.unary('(int)(uint)*DAT'))
        self.assertTrue(self.unary('return (short)(int)(uint)*DAT'))

    def test_pointer_cast_after_integer_cast_keeps_underlying_load(self):
        self.assertTrue(self.unary('(uint)(code **)*DAT'))

    def test_known_floating_and_bool_casts_are_also_casts(self):
        self.assertTrue(self.unary('(double)(uint)*DAT'))
        self.assertTrue(self.unary('(bool)*DAT'))

    def test_parenthesized_expression_is_not_a_type_chain(self):
        for expression in ['(int)(0)*DAT','(int)(value)*DAT','((uint)value)*DAT']:
            with self.subTest(expression=expression):self.assertFalse(self.unary(expression))

    def test_calls_sizeof_and_function_style_casts_multiply(self):
        for expression in ['f(uint)*DAT','sizeof(uint)*DAT','uint(value)*DAT','(int)f(uint)*DAT']:
            with self.subTest(expression=expression):self.assertFalse(self.unary(expression))

    def test_called_parenthesized_or_subscripted_expression_is_not_cast(self):
        for expression in ['(fn)(uint)*DAT','array[0](uint)*DAT','(*fn)(uint)*DAT']:
            with self.subTest(expression=expression):self.assertFalse(self.unary(expression))

    def test_expression_result_with_nested_casts_still_multiplies(self):
        self.assertFalse(self.unary('f((int)(uint)value)*DAT'))
        self.assertFalse(self.unary('((int)(uint)value)*DAT'))

    def test_cast_chain_in_call_argument_or_conditional_is_unary(self):
        self.assertTrue(self.unary('f((int)(uint)*DAT'))
        self.assertTrue(self.unary('value ? (int)(uint)*DAT'))

    def test_cast_chain_after_binary_operator_is_unary(self):
        self.assertTrue(self.unary('value * (int)(uint)*DAT'))
        self.assertTrue(self.unary('value + (int)(uint)*DAT'))

    def test_unknown_scalar_type_does_not_guess_cast_vs_value(self):
        self.assertFalse(self.unary('(Unknown)(uint)*DAT'))

    def test_incomplete_or_function_pointer_declarator_is_conservative(self):
        self.assertFalse(self.unary('(uint*DAT'))
        self.assertFalse(self.unary('(int (*)(void))*DAT'))

    def test_opaque_record_pointer_cast_does_not_invent_a_layout(self):
        self.assertTrue(self.unary('(int)(UnknownOwner *)*DAT'))

    def test_global_pointer_recovery_keeps_load_and_numeric_casts(self):
        body='{\n  return (int)(uint)*DAT_00800000;\n}'
        changed,types=seed.recover_global_pointers(body)
        self.assertEqual(types,{'DAT_00800000':'undefined4 *'})
        self.assertEqual(changed,body)

    def test_explicit_narrow_pointer_view_preserves_pointee_width(self):
        body='{\n  ushort *p;\n  p = DAT_00800000;\n  return (int)(uint)*DAT_00800000;\n}'
        changed,types=seed.recover_global_pointers(body)
        self.assertEqual(types['DAT_00800000'],'ushort *')
        self.assertIn('return (int)(uint)*DAT_00800000;',changed)

    def test_multiplication_still_uses_stored_pointer_bits_once(self):
        body='{\n  use(*DAT_00800000);\n  return sizeof(uint)*DAT_00800000;\n}'
        changed,types=seed.recover_global_pointers(body)
        self.assertEqual(types['DAT_00800000'],'undefined4 *')
        self.assertIn('use(*DAT_00800000);',changed)
        self.assertIn('return sizeof(uint)*(uint)DAT_00800000;',changed)

    def test_local_merged_storage_uses_the_same_unary_decision(self):
        body='{\n  undefined4 slot;\n  slot = (int *)address;\n  return (short)(uint)*slot;\n}'
        text,notes=seed.scalar_address_views(body)
        self.assertIn('undefined4 slot;',text)
        self.assertIn('return (short)(uint)*(int *)slot;',text)
        self.assertEqual(len(notes),1)

    def test_code_view_ignores_comments_between_casts(self):
        body='{\n  return (int)/* note */(uint)*DAT_00800000;\n}'
        changed,types=seed.recover_global_pointers(body)
        self.assertEqual(changed,body)
        self.assertEqual(types['DAT_00800000'],'undefined4 *')

    def test_whitespace_and_long_cast_chains_do_not_change_reads(self):
        body='{\n  return (int) (unsigned int) (ushort) (uint) *DAT_00800000;\n}'
        changed,types=seed.recover_global_pointers(body)
        self.assertEqual(changed,body)
        self.assertEqual(types['DAT_00800000'],'undefined4 *')


if __name__=='__main__':unittest.main()
