"""Authored synthetic x86 guards and high-level pointer-switch lowering."""
from pathlib import Path
from types import SimpleNamespace
import struct
import sys
import unittest
from unittest.mock import patch

import capstone

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools/original_target'))
import seed_candidate as seed
from seed_switches import inspect_index_switch, UnsupportedSwitch

BASE, ENTRY, DISPATCH, TABLE, EXTERNAL = 0x10000000, 0x10001000, 0x10001005, 0x10001018, 0x10002000


class SyntheticAudit:
    """Tiny authored fixture; no original executable or copied code required."""
    def __init__(self):
        # CMP EAX,1; JA final RET; JMP [EAX*4+table]; two MOV-immediate/RET cases.
        code = b'\x83\xf8\x01\x77\x12\xff\x24\x85'+struct.pack('<I', TABLE)
        code += b'\xb8\x03\x00\x00\x00\xc3\xb8\x07\x00\x00\x00\xc3'
        self.data = bytearray(code+struct.pack('<II', ENTRY+12, ENTRY+18)+b'\x90'*16)
        self.base = BASE
        self.decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
        self.decoder.detail = True
        self.section = SimpleNamespace(Characteristics=0x60000020, VirtualAddress=ENTRY-BASE, SizeOfRawData=len(self.data))
        self.pe = SimpleNamespace(get_section_by_rva=lambda r: self.section)

    def original(self, address, length):
        return bytes(self.data[address-ENTRY:address-ENTRY+length])


class OriginalGuardTests(unittest.TestCase):
    def test_original_count_and_targets_come_from_real_guard_and_bytes(self):
        facts = inspect_index_switch(SyntheticAudit(), ENTRY, DISPATCH, TABLE)
        self.assertEqual(facts['targets'], [ENTRY+12, ENTRY+18])
        self.assertEqual(facts['original_code_bytes'], 24)
        self.assertEqual(facts['code_and_table_bytes'], 32)
        self.assertEqual(facts['guard_sites'], [(ENTRY, ENTRY+3)])

    def test_every_reentry_guard_is_checked(self):
        audit = SyntheticAudit()
        audit.data[18:24] = b'\x83\xf8\x01\x76\xee\xc3'
        facts = inspect_index_switch(audit, ENTRY, DISPATCH, TABLE)
        self.assertEqual(facts['guard_sites'], [(ENTRY, ENTRY+3), (ENTRY+18, ENTRY+21)])

    def test_disagreeing_reentry_guard_refuses(self):
        audit = SyntheticAudit()
        audit.data[18:24] = b'\x83\xf8\x00\x76\xee\xc3'
        with self.assertRaisesRegex(UnsupportedSwitch, 'disagree'):
            inspect_index_switch(audit, ENTRY, DISPATCH, TABLE)

    def test_writable_or_unreadable_table_refuses(self):
        for flags in (0xe0000020, 0x20000020):
            audit = SyntheticAudit();audit.section.Characteristics = flags
            with self.subTest(flags=flags), self.assertRaisesRegex(UnsupportedSwitch, 'read-only'):
                inspect_index_switch(audit, ENTRY, DISPATCH, TABLE)

    def test_table_must_have_initialized_backing(self):
        audit = SyntheticAudit();audit.section.SizeOfRawData = 24
        with self.assertRaisesRegex(UnsupportedSwitch, 'initialized'):
            inspect_index_switch(audit, ENTRY, DISPATCH, TABLE)

    def test_short_table_read_refuses(self):
        audit = SyntheticAudit();read = audit.original
        audit.original = lambda at, n: read(at, n)[:6] if at == TABLE else read(at, n)
        with self.assertRaisesRegex(UnsupportedSwitch, 'Truncated'):
            inspect_index_switch(audit, ENTRY, DISPATCH, TABLE)

    def test_mismatched_dispatch_table_label_refuses(self):
        with self.assertRaises(UnsupportedSwitch):
            inspect_index_switch(SyntheticAudit(), ENTRY, DISPATCH, TABLE+4)

    def test_non_dispatch_or_unaligned_table_refuses(self):
        for dispatch, table in ((ENTRY, TABLE), (DISPATCH, TABLE+1)):
            with self.subTest(dispatch=dispatch, table=table), self.assertRaises(UnsupportedSwitch):
                inspect_index_switch(SyntheticAudit(), ENTRY, dispatch, table)

    def test_guard_must_compare_the_actual_index_register(self):
        audit = SyntheticAudit();audit.data[1] = 0xf9  # CMP ECX,1 instead of EAX.
        with self.assertRaisesRegex(UnsupportedSwitch, 'index comparison'):
            inspect_index_switch(audit, ENTRY, DISPATCH, TABLE)

    def test_wrong_unsigned_branch_refuses(self):
        audit = SyntheticAudit();audit.data[3] = 0x76
        with self.assertRaisesRegex(UnsupportedSwitch, 'unsigned upper bound'):
            inspect_index_switch(audit, ENTRY, DISPATCH, TABLE)

    def test_guard_flags_cannot_be_bypassed(self):
        audit = SyntheticAudit();audit.data[24:28] = struct.pack('<I', ENTRY+3)
        with self.assertRaisesRegex(UnsupportedSwitch, 'bypassed'):
            inspect_index_switch(audit, ENTRY, DISPATCH, TABLE)

    def test_overlapping_case_decode_refuses(self):
        audit = SyntheticAudit();audit.data[28:32] = struct.pack('<I', ENTRY+13)
        with self.assertRaises(UnsupportedSwitch):
            inspect_index_switch(audit, ENTRY, DISPATCH, TABLE)

    def test_case_target_must_stay_in_local_code(self):
        audit = SyntheticAudit();audit.data[28:32] = struct.pack('<I', TABLE)
        with self.assertRaisesRegex(UnsupportedSwitch, 'outside'):
            inspect_index_switch(audit, ENTRY, DISPATCH, TABLE)

    def test_opaque_second_jump_refuses(self):
        audit = SyntheticAudit();audit.data[18:20] = b'\xff\xe3'
        with self.assertRaisesRegex(UnsupportedSwitch, 'opaque indirect'):
            inspect_index_switch(audit, ENTRY, DISPATCH, TABLE)

    def test_unbounded_guard_refuses(self):
        audit = SyntheticAudit();audit.data[2] = 0xff
        with self.assertRaisesRegex(UnsupportedSwitch, 'range'):
            inspect_index_switch(audit, ENTRY, DISPATCH, TABLE)

    def test_only_known_external_direct_tails_are_qualified(self):
        audit = SyntheticAudit();audit.data[18:23] = b'\xe9'+struct.pack('<i', EXTERNAL-(ENTRY+23))
        with self.assertRaisesRegex(UnsupportedSwitch, 'Unknown external'):
            inspect_index_switch(audit, ENTRY, DISPATCH, TABLE)
        facts = inspect_index_switch(audit, ENTRY, DISPATCH, TABLE, {EXTERNAL})
        self.assertEqual(facts['qualified_direct_tail_exits'], [(ENTRY+18, EXTERNAL)])
        self.assertIn('not followed', facts['scope'])


class SwitchLoweringTests(unittest.TestCase):
    def body(self, cases=None, index='index'):
        cases = cases if cases is not None else 'case (undefined *)0x1000100c: action(); break; case (undefined *)0x10001012: break;'
        return ('{\n  uint index;\n  switch((&switchD_10001005::switchdataD_10001018)['+index+']) {\n    '+cases+'\n  }\n}')

    def lower(self, body, targets=(ENTRY+12, ENTRY+18)):
        return seed.indexed_switch_artifacts(body, ENTRY, facts={(DISPATCH, TABLE): {'targets': list(targets)}})

    def test_integer_cases_preserve_original_table_index_order(self):
        text, notes = self.lower(self.body(), (ENTRY+18, ENTRY+12))
        self.assertIn('switch(index)', text)
        self.assertIn('case 1: action()', text)
        self.assertIn('case 0: break;', text)
        self.assertNotIn('switchdataD_', text)
        self.assertNotIn('(undefined *)', text)
        self.assertEqual(len(notes), 1)

    def test_shared_original_target_becomes_grouped_integer_cases(self):
        text, _ = self.lower(self.body('case (undefined *)0x1000100c: action();'), (ENTRY+12, ENTRY+12))
        self.assertIn('case 0: case 1: action();', text)

    def test_missing_extra_and_duplicate_case_addresses_refuse(self):
        for cases in ('case (undefined *)0x1000100c: break;',
                      'case (undefined *)0x1000100c: break; case (undefined *)0x10001012: break; case (undefined *)0x10001013: break;',
                      'case (undefined *)0x1000100c: break; case (undefined *)0x1000100c: break;'):
            body = self.body(cases)
            self.assertEqual(self.lower(body), (body, []))

    def test_integer_or_other_pointer_case_syntax_is_not_reinterpreted(self):
        for cases in ('case 0x1000100c: break;', 'case (code *)0x1000100c: break;'):
            body = self.body(cases)
            self.assertEqual(self.lower(body), (body, []))

    def test_unknown_or_side_effecting_selector_is_unchanged(self):
        for body in (self.body().replace('uint index;', 'Unknown index;'), self.body(index='index++')):
            self.assertEqual(self.lower(body), (body, []))

    def test_comments_and_literals_remain_unchanged(self):
        body = '{\n  /* '+self.body()+' */\n  use("switch((&switchD_10001005::switchdataD_10001018)[index])");\n}'
        self.assertEqual(self.lower(body), (body, []))

    def test_nested_unrelated_switch_cases_are_preserved(self):
        body = self.body('case (undefined *)0x1000100c: switch(index) { case 7: break; } break; case (undefined *)0x10001012: break;')
        text, _ = self.lower(body)
        self.assertIn('case 7: break;', text)
        self.assertIn('case 0: switch(index)', text)

    def test_unproved_original_switch_leaves_the_artifact(self):
        body = self.body()
        with patch.object(seed, 'original_index_switch', side_effect=UnsupportedSwitch('unknown original guard')):
            self.assertEqual(seed.indexed_switch_artifacts(body, ENTRY), (body, []))

    def test_wrong_original_target_failure_is_not_swallowed(self):
        with patch.object(seed, 'original_index_switch', side_effect=ValueError('Wrong supplied executable')):
            with self.assertRaisesRegex(ValueError, 'Wrong supplied'):
                seed.indexed_switch_artifacts(self.body(), ENTRY)

    def test_complete_seed_uses_high_level_cases_without_pointer_data(self):
        source = self.body('case (undefined *)0x1000100c: break; case (undefined *)0x10001012: break;')
        class FakeInventory:
            passes = []
            def decompiled(self, entry):return 'void __cdecl FUN_10001000(void)\n'+source
            def function(self, entry):return None, {'ranges': []}
        with patch.object(seed, 'original_index_switch', return_value={'targets': [ENTRY+12, ENTRY+18]}):
            text = seed.seed(ENTRY, FakeInventory(), {})
        self.assertIn('case 0:', text)
        self.assertIn('case 1:', text)
        self.assertIn('Original guarded switch', text)
        self.assertNotIn('switchdataD_', text)
        self.assertNotIn('extern "C" code', text)


if __name__ == '__main__':
    unittest.main()
