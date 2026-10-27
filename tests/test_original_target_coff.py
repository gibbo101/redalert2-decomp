"""Synthetic object-format rejection tests; fixtures contain no game payload."""
import pathlib
import struct
import sys
import unittest

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parents[1] / 'tools' / 'original_target'))
from coff import Coff


def object_fixture(payload=b'abcd', relocation=None):
    table_end = 60
    relocations = b'' if relocation is None else struct.pack('<IIH', *relocation)
    symbols_at = table_end + len(payload) + len(relocations)
    header = struct.pack('<HHIIIHH', 0x14c, 1, 0, symbols_at, 1, 0, 0)
    section = struct.pack('<8sIIIIIIHHI', b'.text', 0, 0, len(payload), table_end,
                          table_end + len(payload) if relocations else 0, 0,
                          int(bool(relocations)), 0, 0x60100020)
    symbol = struct.pack('<8sIhHBB', b'_fixture', 0, 1, 0x20, 2, 0)
    return header + section + payload + relocations + symbol + struct.pack('<I', 4)


def symbols_fixture(symbols, payload=b'abcdefghijkl'):
    """Short-name symbols: name, offset, section, type, auxiliary extent."""
    records = bytearray()
    count = 0
    for name, offset, section, typ, size in symbols:
        records.extend(struct.pack('<8sIhHBB', name, offset, section, typ, 2, bool(size)))
        count += 1
        if size:
            auxiliary = bytearray(18)
            struct.pack_into('<I', auxiliary, 4, size)
            records.extend(auxiliary)
            count += 1
    header = struct.pack('<HHIIIHH', 0x14c, 1, 0, 60 + len(payload), count, 0, 0)
    section = struct.pack('<8sIIIIIIHHI', b'.text', 0, 0, len(payload), 60, 0, 0, 0, 0, 0x60100020)
    return header + section + payload + records + struct.pack('<I', 4)


class CoffRejections(unittest.TestCase):
    def test_complete_symbol_extent(self):
        symbol, section, first, last = Coff(object_fixture()).function('_fixture')
        self.assertEqual((first, last, section['data']), (0, 4, b'abcd'))

    def test_all_truncated_prefixes_refuse(self):
        data = object_fixture()
        for end in range(len(data)):
            with self.subTest(end=end), self.assertRaises((ValueError, struct.error)):
                Coff(data[:end])

    def test_auxiliary_symbol_overflow_refuses(self):
        data = bytearray(object_fixture())
        data[-5] = 1
        with self.assertRaisesRegex(ValueError, 'auxiliary'):
            Coff(data)

    def test_relocation_outside_section_refuses(self):
        with self.assertRaisesRegex(ValueError, 'relocation'):
            Coff(object_fixture(relocation=(1, 0, 20)))

    def test_relocation_to_unknown_symbol_refuses(self):
        with self.assertRaisesRegex(ValueError, 'relocation'):
            Coff(object_fixture(relocation=(0, 1, 20)))

    def test_unbacked_code_refuses_without_allocating(self):
        data = bytearray(object_fixture())
        struct.pack_into('<I', data, 36, 0xffffffff)
        struct.pack_into('<I', data, 40, 0)
        with self.assertRaisesRegex(ValueError, 'no file backing'):
            Coff(data)

    def test_symbol_section_outside_table_refuses(self):
        data = bytearray(object_fixture())
        struct.pack_into('<h', data, 64 + 12, 2)
        with self.assertRaisesRegex(ValueError, 'symbol section'):
            Coff(data)

    def test_unordered_offsets_and_aliases_keep_next_strictly_later_extent(self):
        coff = Coff(symbols_fixture([
            (b'_late', 8, 1, 0x20, 0), (b'_alias', 0, 1, 0x20, 0),
            (b'_early', 0, 1, 0x20, 0), (b'_mid', 4, 1, 0x20, 0)]))
        for prefix, extent in [('_early', (0, 4)), ('_alias', (0, 4)),
                               ('_mid', (4, 8)), ('_late', (8, 12))]:
            with self.subTest(prefix=prefix):
                self.assertEqual(coff.function(prefix)[2:], extent)

    def test_unique_exact_name_wins_over_longer_prefix_matches(self):
        coff = Coff(symbols_fixture([
            (b'_foo', 0, 1, 0x20, 0), (b'_foobar', 4, 1, 0x20, 0)]))
        symbol, _, start, end = coff.function('_foo')
        self.assertEqual((symbol['name'], start, end), ('_foo', 0, 4))

    def test_ambiguous_prefix_and_duplicate_names_refuse(self):
        for prefix, names in [('_fo', (b'_foo', b'_foobar')),
                              ('_foo', (b'_foo', b'_foo'))]:
            coff = Coff(symbols_fixture([(name, 0, 1, 0x20, 0) for name in names]))
            with self.subTest(prefix=prefix, names=names), self.assertRaisesRegex(ValueError, 'ambiguous/missing'):
                coff.function(prefix)
            with self.assertRaisesRegex(ValueError, 'ambiguous/missing'):
                coff.function('_absent')

    def test_undefined_and_nonfunction_prefix_matches_do_not_compete(self):
        coff = Coff(symbols_fixture([
            (b'_only', 0, 1, 0x20, 0), (b'_only', 0, 0, 0x20, 0),
            (b'_onlyD', 0, 1, 0, 0)]))
        self.assertEqual(coff.function('_only')[2:], (0, 12))

    def test_auxiliary_extent_takes_precedence_and_still_checks_backing(self):
        for size in (3, 13):
            coff = Coff(symbols_fixture([
                (b'_sized', 0, 1, 0x20, size), (b'_next', 2, 1, 0x20, 0)]))
            if size == 3:
                self.assertEqual(coff.function('_sized')[2:], (0, 3))
            else:
                with self.assertRaisesRegex(ValueError, 'function extent'):
                    coff.function('_sized')

    def test_later_out_of_backing_symbol_does_not_extend_current_extent(self):
        coff = Coff(symbols_fixture([
            (b'_valid', 0, 1, 0x20, 0), (b'_beyond', 100, 1, 0x20, 0)]))
        self.assertEqual(coff.function('_valid')[2:], (0, 12))
        with self.assertRaisesRegex(ValueError, 'function extent'):
            coff.function('_beyond')


if __name__ == '__main__':
    unittest.main()
