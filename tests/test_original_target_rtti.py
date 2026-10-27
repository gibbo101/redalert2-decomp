"""Synthetic RTTI graph and explicit compiler-option acceptance tests."""
from pathlib import Path
import struct
import sys
from types import SimpleNamespace
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools/original_target'))
from canonical import compiler_arguments  # noqa: E402
from compile_candidates import trial_options  # noqa: E402
from verify_manifest import Audit  # noqa: E402

TD = '??_R0?AVFixture@@@8'
BCD = '??_R1A@?0A@EA@Fixture@@8'
BCA = '??_R2Fixture@@8'
CHD = '??_R3Fixture@@8'
COL = '??_R4Fixture@@6B@'
VT = '??_7Fixture@@6B@'
TYPE_INFO = '??_7type_info@@6B@'
METHOD = '?Run@Fixture@@QAEXXZ'
BASE = 0x400000
FLAGS = 0x40001040  # initialized read-only COMDAT


class Fixture:
    """A one-class RTTI graph with the real MSVC pointer-field positions.

    Use the audit's actual graph traversal/relocation/byte comparison. Only
    the PE input loader and normalized COFF containers are synthetic.
    """
    def __init__(self):
        self.memory = bytearray(0x3000)
        self.addresses = {TD: 0x401000, BCD: 0x401040, BCA: 0x401080,
                          CHD: 0x4010A0, COL: 0x4010C0, VT: 0x401104}
        self.coff = SimpleNamespace(sections=[], symbols={})
        self.symbols = {}
        for name in [TD, BCD, BCA, CHD, COL, VT, TYPE_INFO, METHOD]:
            index = len(self.symbols)
            self.symbols[name] = index
            self.coff.symbols[index] = dict(name=name, storage=2, section=0, value=0)
        self.add(TD, struct.pack('<II', 0, 0) + b'.?AVFixture@@\0', [(0, TYPE_INFO)])
        self.add(BCD, struct.pack('<6I', 0, 0, 0, 0xFFFFFFFF, 0, 0), [(0, TD)])
        self.add(BCA, bytes(4), [(0, BCD)])
        self.add(CHD, struct.pack('<4I', 0, 0, 1, 0), [(12, BCA)])
        self.add(COL, bytes(20), [(12, TD), (16, CHD)])
        self.add(VT, bytes(8), [(0, COL), (4, METHOD)], value=4)
        all_addresses = dict(self.addresses, **{TYPE_INFO: 0x401200, METHOD: 0x402000})
        for name, address in self.addresses.items():
            section = self.section(name)
            data = bytearray(section['data'])
            for offset, target, _ in section['relocs']:
                struct.pack_into('<I', data, offset, all_addresses[self.coff.symbols[target]['name']])
            self.write(address - (4 if name == VT else 0), data)
        self.candidates = {'fixture': {'references': {VT: self.addresses[VT],
                                                     TYPE_INFO: 0x401200, METHOD: 0x402000}}}
        self.audit = Audit.__new__(Audit)
        self.audit.base = BASE
        self.audit.original = self.original
        initialized = SimpleNamespace(Characteristics=0x40, VirtualAddress=0x1000,
                                      SizeOfRawData=0x1000, Misc_VirtualSize=0x1000,
                                      get_data=lambda: bytes(self.memory[0x1000:0x2000]))
        code = SimpleNamespace(Characteristics=0x20)
        self.audit.pe = SimpleNamespace(sections=[initialized], get_section_by_rva=lambda rva:
                                       initialized if 0x1000 <= rva < 0x2000 else
                                       code if 0x2000 <= rva < 0x3000 else None)
        self.audit.document = lambda _: {'vtables': [{'vtable': '%08x' % self.addresses[VT]}]}

    def add(self, name, data, relocations, value=0):
        if name not in self.symbols:
            index = len(self.symbols)
            self.symbols[name] = index
            self.coff.symbols[index] = dict(name=name, storage=2, section=0, value=0)
        self.coff.sections.append(dict(name='.rdata', flags=FLAGS, data=bytes(data),
                                       relocs=[(offset, self.symbols[target], 6)
                                               for offset, target in relocations]))
        self.coff.symbols[self.symbols[name]].update(section=len(self.coff.sections), value=value)

    def section(self, name):
        return self.coff.sections[self.coff.symbols[self.symbols[name]]['section'] - 1]

    def write(self, address, data):
        start = address - BASE
        self.memory[start:start + len(data)] = data

    def original(self, address, count):
        start = address - BASE
        if count <= 0 or start < 0x1000 or start + count > 0x3000:
            raise ValueError('Synthetic original range outside initialized backing')
        return bytes(self.memory[start:start + count])

    def accepts(self, name):
        index = self.coff.symbols[self.symbols[name]]['section']
        return self.audit.original_duplicate(self.coff, index, self.section(name), self.candidates)


class RTTIGraphTests(unittest.TestCase):
    def test_vtable_root_binds_complete_graph_and_compares_all_sections(self):
        f = Fixture()
        layout = f.audit.rtti_layout(f.coff, f.candidates)
        self.assertEqual(layout, {n: a for n, a in f.addresses.items() if n != VT})
        for name in f.addresses:
            with self.subTest(name=name):
                self.assertTrue(f.accepts(name))
        self.assertEqual(f.audit.rtti_original_copies[VT], f.addresses[VT])
        self.assertEqual(f.audit.rtti_original_copies[TD], f.addresses[TD])

    def test_contradictory_original_graph_refuses_shared_descriptor(self):
        f = Fixture()
        f.write(0x401300, f.original(f.addresses[TD], len(f.section(TD)['data'])))
        f.write(f.addresses[BCD], struct.pack('<I', 0x401300))
        self.assertNotIn(TD, f.audit.rtti_layout(f.coff, f.candidates))
        self.assertFalse(f.accepts(TD))
        self.assertFalse(f.accepts(COL))

    def test_unreachable_descriptor_refuses_even_when_original_bytes_exist(self):
        f = Fixture()
        orphan = '??_R0?AVOrphan@@@8'
        data = struct.pack('<II', 0, 0) + b'.?AVOrphan@@\0'
        f.add(orphan, data, [(0, TYPE_INFO)])
        f.write(0x401340, struct.pack('<I', 0x401200) + data[4:])
        self.assertNotIn(orphan, f.audit.rtti_layout(f.coff, f.candidates))
        self.assertFalse(f.accepts(orphan))

    def test_mismatching_hierarchy_attributes_refuse(self):
        f = Fixture()
        section = f.section(CHD)
        changed = bytearray(section['data'])
        struct.pack_into('<I', changed, 4, 1)
        section['data'] = bytes(changed)
        self.assertEqual(f.audit.rtti_layout(f.coff, f.candidates)[CHD], f.addresses[CHD])
        self.assertFalse(f.accepts(CHD))

    def test_mismatching_type_name_and_locator_offset_refuse(self):
        for name, offset in [(TD, 8), (COL, 4)]:
            with self.subTest(name=name):
                f = Fixture()
                section = f.section(name)
                changed = bytearray(section['data'])
                changed[offset] ^= 1
                section['data'] = bytes(changed)
                self.assertFalse(f.accepts(name))

    def test_graph_pointer_into_code_refuses(self):
        f = Fixture()
        f.write(f.addresses[COL] + 12, struct.pack('<I', 0x402000))
        self.assertNotIn(TD, f.audit.rtti_layout(f.coff, f.candidates))
        self.assertFalse(f.accepts(COL))

    def test_descriptor_scan_uses_original_names_and_refuses_ambiguous_name(self):
        f = Fixture()
        self.assertEqual(f.audit.original_type_descriptors()[TD], f.addresses[TD])
        g = Fixture()
        g.write(0x401300, g.original(g.addresses[TD], len(g.section(TD)['data'])))
        self.assertNotIn(TD, g.audit.original_type_descriptors())
        self.assertEqual(g.audit.original_type_descriptors()[TYPE_INFO], 0x401200)


class RTTICompilerFlagsTests(unittest.TestCase):
    def test_explicit_gr_replaces_disabled_flag_once_without_mutating_options(self):
        options = ['/O2', '/Ob2', '/G5', '/Gy', '/GR']
        before = list(options)
        args = compiler_arguments(options)
        self.assertEqual(args.count('/GR'), 1)
        self.assertNotIn('/GR-', args)
        self.assertEqual(options, before)
        self.assertEqual([a for a in args if a not in ['/GR', '/GR-']],
                         [a for a in compiler_arguments(options[:-1]) if a not in ['/GR', '/GR-']])

    def test_default_trials_remain_disabled_and_gr_requires_explicit_request(self):
        self.assertTrue(all('/GR' not in options for options in trial_options({})))
        for options in trial_options({}):
            self.assertEqual(compiler_arguments(options).count('/GR-'), 1)
            self.assertNotIn('/GR', compiler_arguments(options))
        explicit = [['/O2', '/Ob2', '/G5', '/Gy', '/GR']]
        self.assertEqual(trial_options({'compiler_trial_options': explicit}), explicit)


if __name__ == '__main__':
    unittest.main()
