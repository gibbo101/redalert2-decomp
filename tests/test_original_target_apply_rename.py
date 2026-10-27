"""Synthetic rename-batch contracts; no target bytes or compiler required."""
from pathlib import Path
import re
import sys
import unittest

REPOSITORY = next(parent for parent in Path(__file__).resolve().parents
                  if (parent / 'tools/original_target/apply_rename.py').is_file())
sys.path.insert(0, str(REPOSITORY / 'tools/original_target'))
import apply_rename
import random
from verify_manifest import prefix_bound_values

OLD, NEW = '?Get@Owner@@QAEHH@Z', '?Get@Owner@@QAEH_N@Z'


def region(population, symbol, references, relocations=(), source='src/recovered/a/B_00401000.cpp'):
    return dict(population=population, symbol=symbol, symbol_prefix=symbol, references=references,
                relocations=[dict(symbol=s) for s in relocations], source=source)


class ApplyRenameTests(unittest.TestCase):
    def test_rewrite_applies_rules_then_longest_names_first(self):
        spec = dict(rules=[(re.compile(r'(Get\(int \w+, )int'), r'\1bool')],
                    renames={OLD: NEW, '?Get@Owner@@': '?Fetch@Owner@@'})
        text = 'int Get(int a, int b);\n// @ref ?Get@Owner@@QAEHH@Z=00401000\n'
        self.assertEqual(apply_rename.rewrite(text, spec),
                         'int Get(int a, bool b);\n// @ref ?Get@Owner@@QAEH_N@Z=00401000\n')

    def test_leftover_ignores_old_names_inside_new_ones(self):
        renames = {'?A@@YAXXZ': '?A@@YAXXZ_extra'}
        self.assertEqual(apply_rename.leftover('x ?A@@YAXXZ_extra y', renames), [])
        self.assertEqual(apply_rename.leftover('x ?A@@YAXXZ y', renames), ['?A@@YAXXZ'])

    def test_catalog_rename_is_exact_and_marks_only_users(self):
        shared = {OLD: 1, '?Other@@YAXXZ': 2}
        untouched = {'?Unrelated@@YAXXZ': 3, OLD + 'x': 4}
        catalog = dict(regions=[region('population-1', '?F@@YAXXZ', shared, [OLD]),
                                region('population-1', OLD, shared),
                                region('population-2', '?G@@YAXXZ', untouched)])
        affected = apply_rename.rename_catalog(catalog, {OLD: NEW}, {}, {})
        self.assertEqual(affected, {'population-1'})
        first, second, third = catalog['regions']
        self.assertIs(first['references'], second['references'])
        self.assertEqual(first['references'], {NEW: 1, '?Other@@YAXXZ': 2})
        self.assertEqual((second['symbol'], second['symbol_prefix']), (NEW, NEW))
        self.assertEqual(third['references'], untouched)
        self.assertEqual(first['relocations'], [dict(symbol=NEW)])

    def test_rename_onto_an_existing_binding_at_another_address_refuses(self):
        catalog = dict(regions=[region('population-1', '?F@@YAXXZ', {OLD: 1, NEW: 2})])
        with self.assertRaises(SystemExit):
            apply_rename.rename_catalog(catalog, {OLD: NEW}, {}, {})

    def test_changed_and_moved_sources_mark_their_population(self):
        old, new = 'src/recovered/a/Old_00401000.cpp', 'src/recovered/a/New_00401000.cpp'
        row = dict(region('population-3', '?F@@YAXXZ', {}, source=old), semantic_name='Old_00401000')
        catalog = dict(regions=[row])
        self.assertEqual(apply_rename.rename_catalog(catalog, {}, {new: b''}, {old: new}), {'population-3'})
        self.assertEqual((row['source'], row['semantic_name']), (new, 'New_00401000'))

    def test_prefix_lookup_equals_the_full_table_scan(self):
        generator = random.Random(7)
        alphabet = '?@AB_'
        for _ in range(2000):
            table = {''.join(generator.choice(alphabet) for _ in range(generator.randint(0, 6))): generator.randint(0, 3)
                     for _ in range(generator.randint(0, 12))}
            name = ''.join(generator.choice(alphabet) for _ in range(generator.randint(0, 8)))
            scan = {v for n, v in table.items() if name == n or (n.startswith('?') and name.startswith(n))}
            self.assertEqual(prefix_bound_values(table, name), scan)


if __name__ == '__main__':
    unittest.main()
