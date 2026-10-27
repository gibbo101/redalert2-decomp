"""Synthetic reference-binding contracts; no target bytes or compiler required."""
from pathlib import Path
import itertools
import sys
import unittest

REPOSITORY = next(parent for parent in Path(__file__).resolve().parents
                  if (parent / 'tools/original_target/accept_sources.py').is_file())
sys.path.insert(0, str(REPOSITORY / 'tools/original_target'))
import accept_sources


class ReferenceBindingTests(unittest.TestCase):
    # The replay runner supplies either frozen implementation here. A normal
    # unittest run exercises the repository's current production implementation.
    bind_implementation = staticmethod(accept_sources.bind)

    def bind(self, text, known):
        return self.bind_implementation(text, known)

    def test_word_visibility_keeps_each_matching_symbol_and_order(self):
        known = {'?Read@First@@QAEHXZ': 1, '?Write@First@@QAEXXZ': 2,
                 '?Read@Second@@QBEHXZ': 3, '_Plain': 4}
        self.assertEqual(list(self.bind('Read Plain', known).items()),
                         [('?Read@First@@QAEHXZ', 1), ('?Read@Second@@QBEHXZ', 3), ('_Plain', 4)])
        self.assertEqual(self.bind('ReadMore Plainly', known), {})

    def test_prefixes_collapse_only_at_the_same_address(self):
        known = {'?Read@Owner@@': 1, '?Read@Owner@@QAEHXZ': 1,
                 '?Read@Owner@@QBEHXZ': 2}
        self.assertEqual(list(self.bind('Read', known).items()),
                         [('?Read@Owner@@QAEHXZ', 1), ('?Read@Owner@@QBEHXZ', 2)])
        different = {'?Read@Owner@@': 1, '?Read@Owner@@QAEHXZ': 2}
        self.assertEqual(self.bind('Read', different), different)

    def test_longest_prefix_survives_independent_of_binding_order(self):
        names = ['?Read', '?Read@', '?Read@Owner@@', '?Read@Owner@@QAEHXZ']
        for order in itertools.permutations(names):
            with self.subTest(order=order):
                self.assertEqual(self.bind('Read', {name: 1 for name in order}),
                                 {'?Read@Owner@@QAEHXZ': 1})

    def test_ordinary_symbols_are_never_removed_as_mangled_prefixes(self):
        known = {'_Plain': 1, '_PlainExtra': 1}
        self.assertEqual(self.bind('Plain PlainExtra', known), known)

    def test_compiler_helpers_are_bound_but_unused_imports_are_not(self):
        known = {'__ftol': 1, '??2@YAPAXI@Z': 2, '??3@YAXPAX@Z': 3,
                 '_atexit': 4, '__imp__Imported@4': 5}
        expected = {name: value for name, value in known.items() if name != '__imp__Imported@4'}
        self.assertEqual(self.bind('', known), expected)
        self.assertEqual(self.bind('Imported', known), known)

    def test_deleting_destructor_alias_preserves_an_explicit_binding(self):
        known = {'??_GFixture@@UAEPAXI@Z': 1}
        self.assertEqual(self.bind('Fixture', known),
                         {'??_GFixture@@UAEPAXI@Z': 1, '??_EFixture@@UAEPAXI@Z': 1})
        known['??_EFixture@@UAEPAXI@Z'] = 2
        self.assertEqual(self.bind('Fixture', known), known)

    def test_nonidentifier_spelling_keeps_existing_boundary_rules(self):
        known = {'??0?$Box@H@@': 1, '??_7?$Box@H@@6B@': 2}
        self.assertEqual(self.bind('x?$Box', known), known)
        self.assertEqual(self.bind('?$Box', known), {})

    def test_seed_overwrites_keep_original_insertion_positions(self):
        text = ('FUN_00402000 DAT_00401000 Read Plain New\n'
                '// @ref _Plain=0x11\n'
                '// @ref ?Read@Owner@@=0x12\n'
                '// @ref _SeedOnly=0x13\n')
        known = {'_New': 0x60, '_Plain': 0x21, '?Read@Owner@@': 0x22,
                 '?Read@Owner@@QAEHXZ': 0x22}
        self.assertEqual(list(self.bind(text, known).items()), [
            ('_DAT_00401000', 0x401000), ('?FUN_00402000@', 0x402000),
            ('_Plain', 0x21), ('_SeedOnly', 0x13), ('_New', 0x60),
            ('?Read@Owner@@QAEHXZ', 0x22)])

    def test_branched_prefix_chains_preserve_survivor_order(self):
        items = [('?Read@B@@Full', 7), ('?Read@', 7), ('?Read@A@@', 7),
                 ('?Read@A@@Full', 7), ('?Read@B@@', 7),
                 ('?Read@A@@Other', 7), ('?Read@Z@@', 8),
                 ('?Read@Z@@Full', 9), ('?ReadMore', 7)]
        survivors = {'?Read@B@@Full', '?Read@A@@Full', '?Read@A@@Other',
                     '?Read@Z@@', '?Read@Z@@Full', '?ReadMore'}
        for ordered in (items, items[::-1], items[::2] + items[1::2]):
            with self.subTest(order=ordered):
                self.assertEqual(list(self.bind('Read ReadMore', dict(ordered)).items()),
                                 [(name, address) for name, address in ordered if name in survivors])

    def test_deleting_aliases_append_in_scalar_order_without_moving_explicit_alias(self):
        scalar_fixture = '??_GFixture@@UAEPAXI@Z'
        scalar_other = '??_GOther@@UAEPAXI@Z'
        vector_fixture = '??_EFixture@@UAEPAXI@Z'
        vector_other = '??_EOther@@UAEPAXI@Z'
        known = {scalar_other: 3, '_Plain': 2, scalar_fixture: 1}
        self.assertEqual(list(self.bind('Fixture Other Plain', known).items()),
                         [(scalar_other, 3), ('_Plain', 2), (scalar_fixture, 1),
                          (vector_other, 3), (vector_fixture, 1)])
        known[vector_fixture] = 4
        text = '// @ref %s=0x9\nFixture Other Plain' % vector_fixture
        self.assertEqual(list(self.bind(text, known).items()),
                         [(vector_fixture, 4), (scalar_other, 3), ('_Plain', 2),
                          (scalar_fixture, 1), (vector_other, 3)])


if __name__ == '__main__':
    unittest.main()
