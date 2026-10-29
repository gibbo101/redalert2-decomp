"""Unsigned address ordering preserves complete expressions and typed loads."""
from pathlib import Path
import sys
import unittest

sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'tools/original_target'))
import seed_candidate as seed


class UnsignedOrderTests(unittest.TestCase):
    types={'u':'uint','s':'int','p':'ushort *','q':'int *','pp':'ushort **',
           'rows':'int','pitch':'int','width':'int','base':'void *','owner':'int',
           'wide':'ulonglong','fp':'double','small':'uchar','items':'uint *'}

    def category(self,expression):
        return seed.expression_category(seed.seed_expression_type(expression,self.types))

    def convert(self,expression):
        return seed.unsigned_pointer_ordering('{\n  return '+expression+';\n}',globals_=self.types)

    def test_unsigned_value_casts_complete_pointer_once(self):
        self.assertIn('u < (uint)(p)',self.convert('u < p'))
        self.assertIn('(uint)(p) >= u',self.convert('p >= u'))

    def test_all_relational_operators_keep_direction(self):
        for op in ['<','<=','>','>=']:
            with self.subTest(op=op):self.assertIn('u '+op+' (uint)(p)',self.convert('u '+op+' p'))

    def test_full_unsigned_arithmetic_has_ordinary_promotions(self):
        self.assertEqual(self.category('(uint)base + pitch * rows + width + 2'),'unsigned32')
        self.assertEqual(self.category('u + s'),'unsigned32')
        self.assertEqual(self.category('small + s'),'signed32')

    def test_pointer_loaded_from_owner_is_cast_after_the_load(self):
        text=self.convert('(uint)base + pitch * rows + width + 2 < *(ushort **)(owner+0x1c)')
        self.assertIn('< (uint)(*(ushort **)(owner+0x1c))',text)
        self.assertNotIn('*(uint)',text)

    def test_byte_pointer_load_keeps_its_pointer_storage_width(self):
        self.assertIn('(uint)(*(char **)(owner+4))',self.convert('u <= *(char **)(owner+4)'))

    def test_typed_pointer_arithmetic_keeps_element_stride(self):
        text=self.convert('u < p + rows')
        self.assertIn('u < (uint)(p + rows)',text)
        self.assertNotIn('(uint)p +',text)

    def test_signed_or_small_only_counterpart_is_not_assumed_unsigned(self):
        for expression in ['s < p','p > s','small < p','1 < p']:
            with self.subTest(expression=expression):self.assertIn('return '+expression+';',self.convert(expression))

    def test_wide_fp_and_unknown_operands_refuse(self):
        for expression in ['wide < p','fp < p','unknown < p','u + wide < p','u + fp < p','call() < p']:
            with self.subTest(expression=expression):self.assertIn('return '+expression+';',self.convert(expression))

    def test_explicit_unsigned_cast_retains_wrapped_signed_input(self):
        self.assertIn('(uint)s < (uint)(p)',self.convert('(uint)s < p'))
        self.assertEqual(self.category('(uint)-1'),'unsigned32')

    def test_shifts_use_promoted_left_type(self):
        self.assertEqual(self.category('u >> s'),'unsigned32')
        self.assertEqual(self.category('s >> u'),'signed32')
        self.assertEqual(self.category('u << 4'),'unsigned32')

    def test_wide_literal_does_not_silently_narrow_arithmetic(self):
        self.assertIsNone(self.category('u + 1ULL'))
        self.assertIsNone(self.category('2147483648'))
        self.assertEqual(self.category('0xffffffff'),'unsigned32')
        self.assertEqual(self.category('4294967295U'),'unsigned32')

    def test_both_pointer_operands_and_literal_null_stay_unchanged(self):
        for expression in ['p < q','p < 0U','0U >= p']:
            self.assertIn('return '+expression+';',self.convert(expression))

    def test_equality_operators_are_not_relational_sites(self):
        for expression in ['u == p','u != p']:
            self.assertIn('return '+expression+';',self.convert(expression))

    def test_shifts_are_not_mistaken_for_comparisons(self):
        self.assertIn('return u << 2;',self.convert('u << 2'))

    def test_index_side_effect_is_evaluated_once(self):
        text=self.convert('u < *(ushort **)(owner + items[rows++])')
        self.assertIn('(uint)(*(ushort **)(owner + items[rows++]))',text)
        self.assertEqual(text.count('rows++'),1)

    def test_pointer_post_increment_is_evaluated_once(self):
        text=self.convert('u < p++')
        self.assertIn('(uint)(p++)',text)
        self.assertEqual(text.count('p++'),1)

    def test_call_inside_explicit_pointer_load_keeps_single_call(self):
        text=self.convert('u < *(uint **)(advance())')
        self.assertIn('(uint)(*(uint **)(advance()))',text)
        self.assertEqual(text.count('advance()'),1)

    def test_narrow_array_values_promote_before_arithmetic(self):
        self.assertEqual(self.category('items[rows++]'),'unsigned32')
        self.assertEqual(self.category('p[rows] + s'),'signed32')

    def test_unknown_conditional_and_member_results_are_unmodified(self):
        for expression in ['(s ? u : s) < p','owner.value < p','owner->value < p']:
            self.assertIn('return '+expression+';',self.convert(expression))

    def test_boolean_boundaries_keep_independent_operands(self):
        text=self.convert('u < p && u >= q')
        self.assertIn('u < (uint)(p) && u >= (uint)(q)',text)

    def test_chain_comparisons_are_not_guessed(self):
        self.assertIn('return u < p < q;',self.convert('u < p < q'))

    def test_parenthesized_bitwise_math_preserves_precedence(self):
        text=self.convert('(u & 0xffffU) < p')
        self.assertIn('(u & 0xffffU) < (uint)(p)',text)

    def test_comments_and_strings_remain_untouched(self):
        body='{\n  use("u < p"); /* u > p */\n}'
        self.assertEqual(seed.unsigned_pointer_ordering(body,globals_=self.types),body)

    def test_existing_explicit_address_bits_cast_is_idempotent(self):
        text=self.convert('u < p')
        self.assertEqual(seed.unsigned_pointer_ordering(text,globals_=self.types),text)

    def test_global_and_parameter_type_facts_are_both_used(self):
        body='{\n  return value < DAT_00800000;\n}'
        text=seed.unsigned_pointer_ordering(body,['uint value'],{'DAT_00800000':'void *'})
        self.assertIn('value < (uint)(DAT_00800000)',text)


if __name__=='__main__':unittest.main()
