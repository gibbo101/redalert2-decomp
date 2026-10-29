"""Only exact typed SDK locals lose Ghidra's synthetic named-half spelling."""
from pathlib import Path
import sys
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools/original_target'))
import seed_candidate as seed


class LargeIntegerMemberArtifacts(unittest.TestCase):
    def convert(self, operations, declaration='LARGE_INTEGER value;', params=()):
        text = '{\n  ' + declaration + '\n  ' + operations + '\n}'
        return text, seed.large_integer_member_artifacts(text, params)

    def test_two_halves_preserve_signedness_and_order(self):
        _, result = self.convert('*out = value.s.HighPart; return value.s.LowPart;')
        self.assertIn('*out = value.HighPart; return value.LowPart;', result)

    def test_store_load_and_address_keep_original_storage(self):
        _, result = self.convert('query((LARGE_INTEGER *)&value); value.s.LowPart = other; use(value.s.HighPart);')
        self.assertIn('query((LARGE_INTEGER *)&value); value.LowPart = other; use(value.HighPart);', result)

    def test_raw_byte_view_and_native_member_are_unchanged(self):
        _, result = self.convert('use(*(uint *)((char *)&value + 0)); use(value.QuadPart); use(value.s.LowPart);')
        self.assertIn('use(*(uint *)((char *)&value + 0)); use(value.QuadPart); use(value.LowPart);', result)

    def test_only_qualified_local_member_tokens_change(self):
        _, result = self.convert('use(obj . value.s.LowPart); use(ptr -> value.s.HighPart); use(ns :: value.s.LowPart); return value.s.LowPart;')
        self.assertIn('obj . value.s.LowPart', result)
        self.assertIn('ptr -> value.s.HighPart', result)
        self.assertIn('ns :: value.s.LowPart', result)
        self.assertIn('return value.LowPart;', result)

    def test_comments_and_literals_are_not_members(self):
        _, result = self.convert('use("value.s.LowPart"); /* value.s.HighPart */ return value . s . LowPart;')
        self.assertIn('"value.s.LowPart"', result)
        self.assertIn('/* value.s.HighPart */', result)
        self.assertIn('return value.LowPart;', result)

    def test_nonlocals_pointers_arrays_aliases_and_qualifiers_stay_unresolved(self):
        for declaration in ('', 'int value;', 'LARGE_INTEGER *value;', 'LARGE_INTEGER value[2];',
                            'PLARGE_INTEGER value;', 'const LARGE_INTEGER value;',
                            'volatile LARGE_INTEGER value;', 'Other::LARGE_INTEGER value;'):
            with self.subTest(declaration=declaration):
                original, result = self.convert('use(value.s.LowPart);', declaration)
                self.assertEqual(result, original)

    def test_parameter_and_local_name_collision_refuses(self):
        original, result = self.convert('use(value.s.LowPart);', params=('int value',))
        self.assertEqual(result, original)

    def test_complex_parameter_collision_does_not_depend_on_name_parser(self):
        for parameter in ('void (*value)(void)', 'void (__stdcall * const value)(int)', 'Other::Type &value'):
            original, result = self.convert('use(value.s.LowPart);', params=(parameter,))
            self.assertEqual(result, original)

    def test_comments_inside_selector_refuse_without_erasing_text(self):
        original, result = self.convert('use(value . /* retained */ s . LowPart); use(value.s.HighPart);')
        self.assertEqual(result, original)

    def test_nested_or_duplicate_declaration_refuses(self):
        for shadow in ('int value;', 'Other::Record value;', 'int (*value)(void);', 'Other::Record &value = other;'):
            with self.subTest(shadow=shadow):
                original, result = self.convert('{ ' + shadow + ' use(value.s.LowPart); } use(value.s.LowPart);')
                self.assertEqual(result, original)

    def test_authored_record_alias_namespace_or_macro_refuses(self):
        for own in ('typedef int LARGE_INTEGER;', 'union LARGE_INTEGER { int own; };',
                    'struct { struct { int LowPart; } s; } value;',
                    'namespace N { int value; }', '#define value other\n',
                    '#define s replacement\n', 'using N::LARGE_INTEGER;'):
            with self.subTest(own=own):
                original, result = self.convert(own + ' use(value.s.LowPart);')
                self.assertEqual(result, original)

    def test_sdk_dependency_identifier_owns_its_spelling(self):
        for name in ('LARGE_INTEGER', 'DWORD', 'LONG'):
            with self.subTest(name=name):
                original, result = self.convert('int ' + name + '; use(value.s.LowPart);')
                self.assertEqual(result, original)

    def test_unknown_uses_fields_calls_and_initializers_refuse(self):
        for operation in ('use(value);', 'value = other;', 'use(value.s.Other);', 'value();', 'int *p = &value;'):
            with self.subTest(operation=operation):
                original, result = self.convert(operation + ' use(value.s.LowPart);')
                # An ordinary unary address is safe; other unclassified uses refuse.
                if operation == 'int *p = &value;':
                    self.assertIn('use(value.LowPart)', result)
                else:
                    self.assertEqual(result, original)

    def test_mixed_declarators_refuse(self):
        original, result = self.convert('use(value.s.LowPart);', 'LARGE_INTEGER value, other;')
        self.assertEqual(result, original)

    def test_inner_scope_sdk_local_is_not_eligible(self):
        original = '{\n if (ok) {\n  LARGE_INTEGER value;\n  use(value.s.LowPart);\n }\n}'
        self.assertEqual(seed.large_integer_member_artifacts(original), original)

    def test_raw_string_and_line_splice_refuse_before_masking(self):
        for operation in ('use(R"tag(value.s.LowPart)tag"); use(value.s.LowPart);',
                          'use(va\\\nlue.s.LowPart); use(value.s.LowPart);'):
            original, result = self.convert(operation)
            self.assertEqual(result, original)

    def test_digraph_directive_refuses_before_masking(self):
        original, result = self.convert('%:define s other\nuse(value.s.LowPart);')
        self.assertEqual(result, original)

    def test_trigraph_directive_refuses_before_masking(self):
        original, result = self.convert('??=define s other\nuse(value.s.LowPart);')
        self.assertEqual(result, original)

    def test_trigraph_comment_splice_refuses_before_masking(self):
        original, result = self.convert('// comment??/\nvalue.s.HighPart = 1; use(value.s.LowPart);')
        self.assertEqual(result, original)

    def test_independent_unshadowed_local_can_still_change(self):
        original = '{\n LARGE_INTEGER good;\n LARGE_INTEGER bad;\n use(bad);\n use(good.s.LowPart);\n use(bad.s.HighPart);\n}'
        result = seed.large_integer_member_artifacts(original)
        self.assertIn('use(good.LowPart)', result)
        self.assertIn('use(bad.s.HighPart)', result)


if __name__ == '__main__':
    unittest.main()
