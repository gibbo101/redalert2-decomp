"""Template-instance vtable bindings from the original RTTI, and replaced
switch-table regions keeping their accepted extent (synthetic inputs)."""
from pathlib import Path
import struct
import sys
from types import SimpleNamespace
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools/original_target'))
from accept_sources import contradicted_vtables, restate_canonical_bounds  # noqa: E402
from verify_manifest import Audit  # noqa: E402

BASE = 0x400000
DYNAMIC = '??_7?$DynamicVectorClass@PAVThing@@@@6B@'
VECTOR = '??_7?$VectorClass@PAVThing@@@@6B@'
CONST = '??_7?$DynamicVectorClass@PBVThing@@@@6B@'
COM = '??_7Persist@@6B@'
SECONDARY = 0x401500
RESIZE = '?Resize@?$DynamicVectorClass@PAVThing@@@@UAE_NHPBQAVThing@@@Z'
DELETING = '??_E?$DynamicVectorClass@PAVThing@@@@UAEPAXI@Z'


class Image:
    """Original vtables of three template instances (two with identical
    slots, as VC6 emits for T * and T const *), a COM class and a secondary
    vtable, each preceded by its complete object locator."""
    def __init__(self):
        self.memory = bytearray(0x4000)
        self.tables = []
        self.vtables = {}
        for number, (name, slots, offset, bases) in enumerate([
                (DYNAMIC, [0x403100, 0x403200], 0, []),
                (VECTOR, [0x403300, 0x403400], 0, []),
                (CONST, [0x403500, 0x403600], 0, []),
                (COM, [0x403700], 0, [{'name': 'IUnknown', 'offset': 0}]),
                (DYNAMIC, [0x403800], 8, [])]):
            descriptor = 0x401000 + 0x80 * number
            locator = 0x401400 + 0x20 * number
            vtable = (0x401604 + 0x40 * number) if offset == 0 else SECONDARY
            self.put(descriptor + 8, b'.?AV' + name[4:-3].encode() + b'\0')
            self.put(locator, struct.pack('<5I', 0, offset, 0, descriptor, 0))
            self.put(vtable - 4, struct.pack('<I', locator))
            self.put(vtable, struct.pack('<%dI' % len(slots), *slots))
            self.tables.append({'vtable': '%08x' % vtable, 'object_offset': offset, 'bases': bases})
            if offset == 0:
                self.vtables[name] = vtable
        self.audit = Audit.__new__(Audit)
        self.audit.base = BASE
        self.audit.original = self.original
        self.audit.document = lambda _: {'vtables': self.tables}
        data = SimpleNamespace(Characteristics=0x40)
        code = SimpleNamespace(Characteristics=0x20)
        self.audit.pe = SimpleNamespace(get_section_by_rva=lambda rva: data if 0x1000 <= rva < 0x3000 else
                                        code if 0x3000 <= rva < 0x4000 else None)

    def put(self, va, data):
        self.memory[va - BASE:va - BASE + len(data)] = data

    def original(self, va, count):
        if va < BASE or va - BASE + count > len(self.memory):
            raise ValueError('outside')
        return bytes(self.memory[va - BASE:va - BASE + count])


def vtable_object(slot_names):
    """A /GR- COFF vtable COMDAT of DynamicVectorClass<Thing *> whose slots
    relocate to the given names (undefined externals)."""
    names = [DYNAMIC] + slot_names
    symbols = {i: dict(name=n, storage=2, section=1 if i == 0 else 0, value=0) for i, n in enumerate(names)}
    section = dict(name='.rdata', flags=0x40001040, data=bytes(4 * len(slot_names)),
                   relocs=[(4 * i, i + 1, 6) for i in range(len(slot_names))])
    return SimpleNamespace(sections=[section], symbols=symbols), section


class InstanceBindingTest(unittest.TestCase):
    def setUp(self):
        self.image = Image()
        self.audit = self.image.audit

    def test_each_instance_binds_to_its_own_original_copy(self):
        self.assertEqual(self.audit.rtti_binding(DYNAMIC), self.image.vtables[DYNAMIC])
        self.assertEqual(self.audit.rtti_binding(VECTOR), self.image.vtables[VECTOR])
        self.assertEqual(self.audit.rtti_binding(CONST), self.image.vtables[CONST])
        # The deleting destructor is slot 0 of the class's own vtable.
        self.assertEqual(self.audit.rtti_binding(DELETING), 0x403100)
        self.assertEqual(self.audit.rtti_binding('??_G?$VectorClass@PAVThing@@@@UAEPAXI@Z'), 0x403300)
        # Not for a COM class (slot 0 is QueryInterface), never from a secondary vtable.
        self.assertIsNone(self.audit.rtti_binding('??_GPersist@@UAEPAXI@Z'))
        self.assertNotIn(SECONDARY, [row[0] for row in self.audit.original_vtables().values()])
        self.assertIsNone(self.audit.rtti_binding('??_7Unknown@@6B@'))

    def test_a_name_found_twice_binds_nothing(self):
        self.image.tables.append(dict(self.image.tables[0]))
        self.image.put(0x401800, struct.pack('<I', 0x401400))
        self.image.tables[-1]['vtable'] = '00401804'
        self.assertIsNone(self.audit.rtti_binding(DYNAMIC))

    def test_unbound_vtable_binds_by_rtti_and_compares_every_slot(self):
        coff, section = vtable_object([DELETING, RESIZE])
        candidates = {'unit': {'references': {RESIZE: 0x403200}}}
        self.assertTrue(self.audit.original_duplicate(coff, 1, section, candidates))
        # The same slot bound to another original copy refuses.
        candidates = {'unit': {'references': {RESIZE: 0x403400}}}
        self.assertFalse(self.audit.original_duplicate(coff, 1, section, candidates))
        self.assertIn('bound 00403400, original 00403200', self.audit.vtable_mismatches[DYNAMIC])

    def test_misbound_vtable_refuses_and_names_the_original_class(self):
        coff, section = vtable_object([DELETING, RESIZE])
        candidates = {'unit': {'references': {DYNAMIC: self.image.vtables[VECTOR], RESIZE: 0x403200,
                                              DELETING: 0x403100}}}
        self.assertFalse(self.audit.original_duplicate(coff, 1, section, candidates))
        note = self.audit.vtable_mismatches[DYNAMIC]
        self.assertIn('names the vtable at %08x %s' % (self.image.vtables[VECTOR], VECTOR), note)
        self.assertIn('%s is %08x' % (DYNAMIC, self.image.vtables[DYNAMIC]), note)

    def test_deleting_destructor_kept_elsewhere_by_rtti(self):
        symbols = {0: dict(name='??_G?$DynamicVectorClass@PAVThing@@@@UAEPAXI@Z', storage=2, section=1, value=0)}
        section = dict(name='.text', flags=0x60001020, data=b'\xc3', relocs=[])
        coff = SimpleNamespace(sections=[section], symbols=symbols)
        self.assertTrue(self.audit.kept_elsewhere(coff, 1, section, {'unit': {'references': {}}}))
        symbols[0]['name'] = '??_GUnknown@@UAEPAXI@Z'
        self.assertFalse(self.audit.kept_elsewhere(coff, 1, section, {'unit': {'references': {}}}))

    def test_contradicting_reference_is_reported(self):
        stated = {DYNAMIC: '%08x' % self.image.vtables[VECTOR], CONST: '%08x' % self.image.vtables[CONST],
                  '??_7Invented@@6B@': '%08x' % self.image.vtables[VECTOR]}
        notes = contradicted_vtables(stated, self.audit)
        self.assertEqual(len(notes), 1)
        self.assertIn('places it at %08x' % self.image.vtables[DYNAMIC], notes[0])
        self.assertIn('is ' + VECTOR, notes[0])


class CanonicalBoundTest(unittest.TestCase):
    def test_switch_region_keeps_its_recorded_extent(self):
        existing = {0x401000: dict(body_bytes=120, switch_data_bytes=24, population='population-7'),
                    0x402000: dict(body_bytes=40, population='population-7')}
        plan = {'sources': [{'entry': '00401000'}, {'entry': '00402000'}, {'entry': '00403000'},
                            {'entry': '00401000', 'body_bytes': 96}]}
        self.assertEqual(restate_canonical_bounds(plan, existing), ['00401000'])
        first, plain, new, stated = plan['sources']
        self.assertEqual((first['body_bytes'], first['canonical_switch_data_bytes']), (120, 24))
        self.assertIn('population-7', first['bound_evidence'])
        self.assertNotIn('body_bytes', plain)
        self.assertNotIn('body_bytes', new)
        self.assertEqual(stated, {'entry': '00401000', 'body_bytes': 96})



class CompositeNameTest(unittest.TestCase):
    def test_composite_pass_of_another_plan_with_the_same_name_refuses(self):
        import json
        import tempfile
        import accept_sources
        with tempfile.TemporaryDirectory() as root:
            frozen = Path(root) / 'inventory'
            frozen.mkdir()
            (frozen / 'unassigned-executable.jsonl').write_text('')
            known = {0x401000: {'name': 'FUN_00401000', 'entry_references': [{'from': '00402000'}]}}
            inventory = SimpleNamespace(rows=lambda directory: known)
            audit = SimpleNamespace(original=lambda va, count: b'\xc3' * count)
            saved = accept_sources.PASSES, accept_sources.REPOSITORY
            accept_sources.PASSES, accept_sources.REPOSITORY = [frozen], Path(root)
            try:
                plan = {'name': 'unit', 'sources': [{'entry': '00401000', 'body_bytes': 16}]}
                target = accept_sources.composite_pass(plan, inventory, {}, {}, audit)
                rows = (target / 'functions.jsonl').read_text()
                # The same plan again reuses its own frozen pass.
                self.assertEqual(accept_sources.composite_pass(plan, inventory, {}, {}, audit), target)
                plan['sources'][0]['body_bytes'] = 32
                with self.assertRaises(SystemExit):
                    accept_sources.composite_pass(plan, inventory, {}, {}, audit)
                self.assertEqual((target / 'functions.jsonl').read_text(), rows)
                self.assertEqual(json.loads(rows)['ranges'][0]['length'], 16)
            finally:
                accept_sources.PASSES, accept_sources.REPOSITORY = saved


if __name__ == '__main__':
    unittest.main()
