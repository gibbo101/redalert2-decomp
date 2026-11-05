"""Scratch binding must not borrow VC6 per-translation-unit initializer names."""
from pathlib import Path
import json
import struct
import sys
import tempfile
import unittest
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools/original_target'))
import diff_candidate as diff


class CompilerLocalReferenceTests(unittest.TestCase):
    def catalog(self, *rows):
        return {'regions': list(rows)}

    def row(self, symbol, entry, **extra):
        return dict(symbol=symbol, entry=entry, **extra)

    def test_shared_initializer_spelling_is_not_an_address(self):
        rows = [self.row('_$E60', 0x401000), self.row('_$E60', 0x402000)]
        for order in (rows, rows[::-1]):
            refs = diff.canonical_references(self.catalog(*order))
            self.assertNotIn('_$E60', refs)
            self.assertIsNone(diff.lookup('_$E60', refs))

    def test_a_single_accepted_initializer_is_still_local(self):
        refs = diff.canonical_references(self.catalog(self.row('_$E214', 0x401000)))
        self.assertIsNone(diff.lookup('_$E214', refs))

    def test_observed_relocation_does_not_make_local_name_global(self):
        row = self.row('?Root@@YAXXZ', 0x401000,
                       relocations=[dict(symbol='_$E60', target=0x402000),
                                    dict(symbol='_Actual_Global', target=0x804000)])
        refs = diff.canonical_references(self.catalog(row))
        self.assertNotIn('_$E60', refs)
        self.assertEqual(diff.lookup('_Actual_Global', refs), 0x804000)
        self.assertEqual(diff.lookup('?Root@@YAXXZ', refs), 0x401000)

    def test_unrelated_and_address_bearing_names_keep_their_bindings(self):
        names = ['_Global_E60', '_$E60_extra', '?Named@Class@@QAEXXZ']
        refs = diff.canonical_references(self.catalog(*(self.row(n, 0x401000 + i * 16)
                                                        for i, n in enumerate(names))))
        for i, name in enumerate(names):
            self.assertEqual(diff.lookup(name, refs), 0x401000 + i * 16)
        self.assertEqual(diff.lookup('_FUN_00403000', refs), 0x403000)

    def test_unbound_local_call_stays_unresolved_instead_of_wrongly_scoring(self):
        refs = diff.canonical_references(self.catalog(self.row('_$E60', 0x402000)))
        code, missing = diff.resolve(bytes.fromhex('e800000000'), [(1, 0, 20)],
                                     {0: {'name': '_$E60'}}, 0x401000, refs)
        self.assertEqual(missing, {1: '_$E60'})
        self.assertEqual(code, bytes.fromhex('e800000000'))

    def test_verified_source_ref_can_bind_the_local_call(self):
        refs = diff.canonical_references(self.catalog(self.row('_$E60', 0x402000)))
        refs.update({name: int(value, 16) for name, value in
                     diff.SOURCE_REF.findall('// @ref _$E60=00403000')})
        code, missing = diff.resolve(bytes.fromhex('e800000000'), [(1, 0, 20)],
                                     {0: {'name': '_$E60'}}, 0x401000, refs)
        self.assertEqual(missing, {})
        self.assertEqual(struct.unpack_from('<i', code, 1)[0], 0x403000 - 0x401005)

    def test_recorded_symbol_fallback_does_not_reintroduce_local_name(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            (root / 'manifests').mkdir()
            (root / 'manifests/symbols.json').write_text(json.dumps({'symbols': [
                dict(mangled_prefix='_$E60', address='00402000'),
                dict(mangled_prefix='?Kept@@YAXXZ', address='00403000')]}))
            with patch.object(diff, '__file__', str(root / 'tools/original_target/diff_candidate.py')):
                refs = diff.known_references(self.catalog())
            self.assertNotIn('_$E60', refs)
            self.assertEqual(diff.lookup('?Kept@@YAXXZ', refs), 0x403000)


if __name__ == '__main__':
    unittest.main()
