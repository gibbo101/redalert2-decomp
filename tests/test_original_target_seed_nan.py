"""NaN value predicates need no function call or argument rounding store."""
from pathlib import Path
import math
import sys
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools/original_target'))
import seed_candidate as seed


class NaNArtifactTests(unittest.TestCase):
    def test_each_floating_scalar_kind_preserves_the_value_expression(self):
        for kind in ('float', 'double', 'float10', 'const float', 'const double', 'const float10'):
            with self.subTest(kind=kind):
                body = '{\n  '+kind+' value;\n  return NAN(value);\n}'
                self.assertEqual(seed.nan_artifacts(body), body.replace('NAN(value)', '(value != value)'))

    def test_value_parameters_are_supported(self):
        self.assertEqual(seed.nan_artifacts('{return NAN(value);}', ['double value']),
                         '{return (value != value);}')

    def test_two_predicates_keep_their_short_circuit_order(self):
        body = '{\n  float10 x;\n  float10 y;\n  return NAN(x) || NAN(y);\n}'
        self.assertIn('return (x != x) || (y != y);', seed.nan_artifacts(body))

    def test_comments_and_literals_are_preserved(self):
        body = '{\n double x; // NAN(x)\n char *s="NAN(x)";\n return NAN(x);\n}'
        changed = seed.nan_artifacts(body)
        self.assertIn('// NAN(x)', changed)
        self.assertIn('"NAN(x)"', changed)
        self.assertIn('return (x != x);', changed)

    def test_unknown_nonfloating_and_volatile_storage_are_not_retyped(self):
        for declaration in ('', 'int x;', 'ulonglong x;', 'volatile double x;', 'double *x;', 'double x[2];', 'extern double x;'):
            body = '{\n '+declaration+'\n return NAN(x);\n}'
            self.assertEqual(seed.nan_artifacts(body), body)

    def test_references_and_pointers_are_not_value_parameters(self):
        for param in ('double &x', 'double *x', 'volatile double x'):
            self.assertEqual(seed.nan_artifacts('{return NAN(x);}', [param]), '{return NAN(x);}')

    def test_effects_loads_casts_and_arithmetic_are_not_duplicated(self):
        for expression in ('next()', 'x++', '++x', '*p', 'values[0]', 'x+y', '(double)x', 'owner.x', '(x=0)'):
            body = '{\n double x;\n return NAN('+expression+');\n}'
            self.assertEqual(seed.nan_artifacts(body), body)

    def test_shadowed_declarations_are_ambiguous(self):
        body = '{\n double x;\n {int x; return NAN(x);}\n}'
        self.assertEqual(seed.nan_artifacts(body), body)

    def test_real_named_function_is_not_a_pcode_helper(self):
        body = '{\n double x;\n return NAN(x);\n}'
        self.assertEqual(seed.nan_artifacts(body, named_functions={'NAN': 0x10001000}), body)

    def test_comma_and_loop_shadowing_are_not_inferred(self):
        for declaration in ('int y,x;', 'int y=next(1,2),x;', 'for(int x=0;x<2;x++)'):
            body = '{\n double x;\n {'+declaration+'; return NAN(x);}\n}'
            self.assertEqual(seed.nan_artifacts(body), body)

    def test_local_function_declaration_is_not_a_predicate(self):
        body = '{\n double x;\n bool NAN(double);\n return NAN(x);\n}'
        self.assertEqual(seed.nan_artifacts(body), body)

    def test_function_pointer_parameter_is_not_a_predicate(self):
        body = '{\n double x;\n return NAN(x);\n}'
        self.assertEqual(seed.nan_artifacts(body, ['bool (*NAN)(double)']), body)

    def test_function_pointer_and_macro_names_are_not_intrinsics(self):
        body = '{\n double x;\n code *NAN;\n return NAN(x);\n}'
        self.assertEqual(seed.nan_artifacts(body), body)
        body = '#define NAN(x) other(x)\n{\n double x;\n return NAN(x);\n}'
        self.assertEqual(seed.nan_artifacts(body), body)

    def test_ordinary_ieee_values_have_the_nan_value_predicate(self):
        for value in (0.0, -0.0, 1.0, -2.0, float('inf'), -float('inf'), float('nan')):
            self.assertEqual(value != value, math.isnan(value))


if __name__ == '__main__':
    unittest.main()
