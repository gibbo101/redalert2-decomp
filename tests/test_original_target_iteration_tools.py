"""Synthetic checks for the scratch iteration tools (no game bytes, no compiler)."""
from datetime import datetime, timezone
from pathlib import Path
import struct
import sys
import tempfile
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools/original_target'))
import capstone
import class_inventory
import diff_candidate as diff
from inventory import Inventory
import seed_candidate as seed
import promote_sweep
import repair_bodies
import status

DECODER = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)


class DiffScoringTests(unittest.TestCase):
    def test_address_names_bind_only_declared_address_forms(self):
        self.assertEqual(diff.address_from_name('?FUN_00402000@@YIXPAX@Z'), 0x402000)
        self.assertEqual(diff.address_from_name('_DAT_00830b50'), 0x830b50)
        self.assertEqual(diff.address_from_name('_data_402190_4022c0'), 0x4022c0)
        self.assertEqual(diff.address_from_name('_s_Warning__deadlock_00801318'), 0x801318)
        # An owner suffix names the caller, not the callee: never guess from it.
        self.assertIsNone(diff.address_from_name('?target@Call_402190_0@@QAEIXZ'))

    def test_relocations_resolve_absolute_and_relative_and_leave_unknowns_wild(self):
        raw = bytes.fromhex('e800000000') + bytes.fromhex('a100000000')
        symbols = {0: dict(name='?FUN_00401100@@YAXXZ'), 1: dict(name='_mystery')}
        data, unresolved = diff.resolve(raw, [(1, 0, 20), (6, 1, 6)], symbols, 0x401000, {})
        self.assertEqual(struct.unpack_from('<i', data, 1)[0], 0x401100 - (0x401000 + 5))
        self.assertEqual(unresolved, {6: '_mystery'})
        rows = diff.disassemble(DECODER, data, 0x401000, unresolved)
        self.assertEqual(rows[1]['text'], 'mov ?_mystery')
        self.assertEqual(rows[1]['loose'], 'mov A')

    def test_identical_code_scores_100_and_register_swaps_keep_shape(self):
        original = diff.disassemble(DECODER, bytes.fromhex('8b4104c3'), 0x401000)   # mov eax,[ecx+4]; ret
        same = diff.disassemble(DECODER, bytes.fromhex('8b4104c3'), 0x401000)
        swapped = diff.disassemble(DECODER, bytes.fromhex('8b4204c3'), 0x401000)    # mov eax,[edx+4]; ret
        self.assertEqual(diff.score(original, same)[0]['score'], 100.0)
        result, pairs = diff.score(original, swapped)
        self.assertEqual(result['score'], 50.0)
        self.assertEqual(result['shape_score'], 100.0)
        self.assertEqual(result['first_difference'], 0)
        self.assertEqual([p[0] for p in pairs], ['|', ' '])

    def test_alignment_nops_are_split_from_the_body_only_beyond_its_length(self):
        self.assertEqual(diff.split_padding(bytes.fromhex('c3909090'), 1), (b'\xc3', 3))
        # A NOP inside the original body length is code, not padding.
        self.assertEqual(diff.split_padding(bytes.fromhex('90c390'), 2), (bytes.fromhex('90c3'), 1))


class SeedTests(unittest.TestCase):
    def inventory(self, root, exports):
        (root / 'decompiled').mkdir(parents=True)
        (root / 'functions.jsonl').write_text('')
        for entry, text in exports.items():
            (root / 'decompiled' / ('%08x.c' % entry)).write_text(text)
        return Inventory([root])

    def test_thiscall_owner_and_callees_become_members_with_casts(self):
        with tempfile.TemporaryDirectory() as temp:
            inventory = self.inventory(Path(temp), {
                0x401000: 'void __thiscall FUN_00401000(int param_1,int param_2)\n\n{\n'
                          '  int iVar1;\n  iVar1 = FUN_00402000(param_1 + 4,&param_2);\n'
                          '  *(int *)(param_1 + 8) = iVar1 + DAT_00830b50;\n  return;\n}\n',
                0x402000: 'int * __thiscall FUN_00402000(void *this,short *param_1)\n\n{\n  return 0;\n}\n'})
            text = seed.seed(0x401000, inventory, {0x402000: 'src/recovered/x.cpp'})
        self.assertIn('struct Owner_00401000 { void FUN_00401000(int param_2); };', text)
        self.assertIn('int param_1 = (int)this;', text)
        self.assertIn('struct Callee_00402000 { undefined4 FUN_00402000(short *param_1); };', text)
        self.assertIn('((Callee_00402000*)(param_1 + 4))->FUN_00402000((short *)(&param_2))', text)
        self.assertIn('extern "C" undefined4 DAT_00830b50;', text)
        self.assertIn('//   FUN_00402000 -> src/recovered/x.cpp', text)
        self.assertIn('#include "shared/ghidra_types.hpp"', text)

    def test_arity_mismatch_becomes_an_overload_and_void_results_used_become_values(self):
        with tempfile.TemporaryDirectory() as temp:
            inventory = self.inventory(Path(temp), {
                0x401000: 'int __cdecl FUN_00401000(void)\n\n{\n  int iVar1;\n'
                          '  iVar1 = FUN_00403000(1,2);\n  return iVar1;\n}\n',
                0x403000: 'void __stdcall FUN_00403000(int param_1)\n\n{\n  return;\n}\n'})
            text = seed.seed(0x401000, inventory, {})
        self.assertIn('extern undefined4 __stdcall FUN_00403000(int, int);', text)
        self.assertIn('iVar1 = (int)(FUN_00403000((int)(1), (int)(2)));', text)

    def test_original_ret_n_fixes_convention_and_stack_parameters(self):
        fit = seed.fit_convention
        self.assertEqual(fit('__cdecl', ['int a'], 8, False), ('__stdcall', ['int a', 'int unused_1']))
        self.assertEqual(fit('__stdcall', ['int a'], 0, False), ('__cdecl', ['int a']))
        self.assertEqual(fit('__thiscall', ['void *this', 'double d'], 8, True), ('__thiscall', ['void *this', 'double d']))
        self.assertEqual(fit('__thiscall', ['void *this'], 4, True), ('__thiscall', ['void *this', 'int unused_0']))
        self.assertEqual(fit('__cdecl', ['int a'], None, False), ('__cdecl', ['int a']))

    def test_ghidra_nonnegative_tests_become_ge_zero(self):
        n = seed.nonnegative_tests
        self.assertEqual(n('if (-1 < iVar1) {'), 'if (iVar1 >= 0) {')
        self.assertEqual(n('if ((-1 < *(int *)(p + 4)) && (b)) {'), 'if ((*(int *)(p + 4) >= 0) && (b)) {')
        self.assertEqual(n('z = f(-1 < q, 2);'), 'z = f(q >= 0, 2);')
        self.assertEqual(n('x = y-1 < z;'), 'x = y-1 < z;')      # subtraction, not a -1 literal

    def test_partial_fields_and_assignments_are_spelled_for_cplusplus(self):
        body = '{\n  uint uVar1;\n  short sVar2;\n  uVar1 = (int *)0x10;\n  sVar2 = local_14._2_2_;\n}'
        body = seed.PARTIAL.sub(lambda m: '(*(%s*)((char*)&%s + %s))' % (
            seed.PARTIAL_TYPES[m.group(3)], m.group(1), m.group(2)), body)
        body = seed.cast_assignments(body, [])
        self.assertIn('uVar1 = (uint)((int *)0x10);', body)
        self.assertIn('sVar2 = (short)((*(ushort*)((char*)&local_14 + 2)));', body)


class ClassInventoryTests(unittest.TestCase):
    def test_runs_split_at_each_stored_vtable_address(self):
        entries = {0x401000, 0x401010, 0x401020}
        data = struct.pack('<6I', 0, 0x401000, 0x401010, 0x401020, 0x401000, 7)
        runs = list(class_inventory.pointer_runs(data, 0x7a0000, entries))
        self.assertEqual(runs, [(0x7a0004, [0x401000, 0x401010, 0x401020, 0x401000])])
        split = list(class_inventory.split_runs(runs, {0x7a0004: [1], 0x7a000c: [2]}))
        self.assertEqual(split, [(0x7a0004, [0x401000, 0x401010]), (0x7a000c, [0x401020, 0x401000])])

    def test_rtti_type_names_demangle_scopes_templates_and_values(self):
        d = class_inventory.demangle_type
        self.assertEqual(d('.?AVBuildingClass@@'), 'BuildingClass')
        self.assertEqual(d('.?AVFoo@Bar@@'), 'Bar::Foo')
        self.assertEqual(d('.?AV?$DynamicVectorClass@PAVAnimTypeClass@@@@'), 'DynamicVectorClass<AnimTypeClass *>')
        self.assertEqual(d('.?AV?$A@H$00@@'), 'A<int, 1>')
        self.assertEqual(d('.?AVbroken'), '.?AVbroken')   # unparseable names stay verbatim

    def test_rtti_locator_supplies_name_offset_and_ordered_bases(self):
        image = {}
        def put(va, data): image.update({va + i: b for i, b in enumerate(data)})
        def name(va, text): put(va, struct.pack('<II', 0, 0) + text.encode() + b'\0')
        name(0x7c0000, '.?AVDerived@@'); name(0x7c0100, '.?AVBase@@')
        put(0x7b0000, struct.pack('<5I', 0, 0, 0, 0x7c0000, 0x7b0100))          # locator
        put(0x7b0100, struct.pack('<4I', 0, 0, 2, 0x7b0200))                    # hierarchy
        put(0x7b0200, struct.pack('<2I', 0x7b0300, 0x7b0400))                   # base array
        put(0x7b0300, struct.pack('<IIiii', 0x7c0000, 1, 0, -1, 0))
        put(0x7b0400, struct.pack('<IIiii', 0x7c0100, 0, 0, -1, 0))
        put(0x7a0000 - 4, struct.pack('<I', 0x7b0000))
        read = lambda va, n: bytes(image.get(va + i, 0) for i in range(n))
        self.assertEqual(class_inventory.rtti(read, 0x7a0000),
                         dict(name='Derived', offset=0, bases=[('Base', 0)], multiple=False, virtual=False))

    def test_only_memory_immediate_stores_count_as_vptr_writes(self):
        # mov dword ptr [esi], 0x7a0004 ; push 0x7a0004 (not a store)
        text = bytes.fromhex('c70604007a00') + bytes.fromhex('6804007a00')
        self.assertEqual(class_inventory.store_sites(DECODER, text, 0x401000, 0x7a0004), [0x401000])


class PromotionTests(unittest.TestCase):
    def test_references_bind_unique_address_prefixes_and_source_refs(self):
        text = ('extern void __fastcall FUN_00473000(int);\nextern "C" undefined4 DAT_00851a70;\n'
                'extern "C" char s_text_007cf360[];\nextern "C" undefined4 _DAT_0079b620;\n'
                'extern "C" undefined4 __cdecl operator_new(...);  // @ref _operator_new=00782017\n')
        self.assertEqual(promote_sweep.references(text, 0x401000, {}), {
            '?FUN_00473000@': 0x473000, '_DAT_00851a70': 0x851a70, '_s_text_007cf360': 0x7cf360,
            '__DAT_0079b620': 0x79b620, '_operator_new': 0x782017})

    def test_padding_requires_a_whole_gap_of_original_nops(self):
        image = {0x401010: b'\x90' * 6, 0x401020: b'\x90\x90\xcc'}
        original = lambda va, n: image[va][:n]
        gaps = {0x401010: dict(start='00401010', length=6), 0x401020: dict(start='00401020', length=3)}
        self.assertEqual(promote_sweep.gap_padding(original, gaps, 0x401010)[0], '90' * 6)
        self.assertEqual(promote_sweep.gap_padding(original, gaps, 0x401020), ('', None))
        self.assertEqual(promote_sweep.gap_padding(original, gaps, 0x401030), ('', None))


class UnreferencedEntryTests(unittest.TestCase):
    def test_aligned_body_after_padding_or_ret_is_entry_evidence(self):
        import compile_candidates as cc
        class Image:
            def __init__(self, data): self.data = data
            def original(self, va, n): return bytes(self.data.get(va + i, 0) for i in range(n))
        body = bytes.fromhex('8b4104c3')                      # mov eax,[ecx+4]; ret
        def bound(entry): return dict(entry='%08x' % entry, ranges=[dict(bytes_hex=body.hex())])
        padded = Image({0x401009 + i: 0x90 for i in range(7)})
        gaps = {0x401009: dict(start='00401009', length=7)}
        self.assertTrue(cc.aligned_unreferenced_entry(padded, bound(0x401010), gaps))
        after_ret = Image({0x40100f: 0xc3})
        self.assertTrue(cc.aligned_unreferenced_entry(after_ret, bound(0x401010), {}))
        self.assertFalse(cc.aligned_unreferenced_entry(after_ret, bound(0x401014), {}))   # unaligned
        self.assertFalse(cc.aligned_unreferenced_entry(Image({}), bound(0x401010), {}))  # no evidence before

    def test_switch_tables_after_mov_edi_edi_fill(self):
        import compile_candidates as cc
        class Image:
            def __init__(self, data): self.data = data
            def original(self, va, n): return bytes(self.data.get(va + i, 0) for i in range(n))
        after_ret = Image({0x40100f: 0xc3})
        def body(fill):
            # mov eax,[esp+4]; cmp eax,1; ja ret; jmp [eax*4+table]; ret 4; fill; two-entry table
            table_offset = 19 + len(fill)
            code = bytes.fromhex('8b442404' '83f801' '7707' 'ff2485') + \
                struct.pack('<I', 0x401010 + table_offset) + bytes.fromhex('c20400')
            table = struct.pack('<II', 0x401010 + 16, 0x401010 + 16)
            return dict(entry='00401010', ranges=[dict(bytes_hex=(code + fill + table).hex())])
        self.assertTrue(cc.aligned_unreferenced_entry(after_ret, body(bytes.fromhex('9090908bff')), {}))
        self.assertTrue(cc.aligned_unreferenced_entry(after_ret, body(bytes.fromhex('9090909090')), {}))
        # 8B FF that does not end at a 4-aligned table is code, not alignment fill.
        self.assertFalse(cc.aligned_unreferenced_entry(after_ret, body(bytes.fromhex('8bff')), {}))

    def test_entry_after_an_accepted_regions_switch_tables(self):
        import compile_candidates as cc
        class Image:
            def __init__(self, data): self.data = data
            def original(self, va, n): return bytes(self.data.get(va + i, 0) for i in range(n))
        # The predecessor's index table ends right at the entry (no padding, no ret).
        after_table = Image({0x401010 - 5 + i: b for i, b in enumerate(bytes.fromhex('0404040400'))})
        body = bytes.fromhex('8b4104c3')                      # mov eax,[ecx+4]; ret
        bound = dict(entry='00401010', ranges=[dict(bytes_hex=body.hex())])
        catalog = dict(regions=[dict(entry=0x400f80, full_extent_bytes=0x90)])   # ends at 0x401010
        ends = cc.accepted_region_ends(catalog)
        self.assertTrue(cc.aligned_unreferenced_entry(after_table, bound, {}, ends))
        # Refused: no accepted region ends there (none recorded, or one ending
        # before unexplained bytes).
        self.assertFalse(cc.aligned_unreferenced_entry(after_table, bound, {}))
        short = cc.accepted_region_ends(dict(regions=[dict(entry=0x400f80, full_extent_bytes=0x8c)]))
        self.assertFalse(cc.aligned_unreferenced_entry(after_table, bound, {}, short))
        # The candidate's own end still has to be a complete ret/jmp body.
        open_body = dict(entry='00401010', ranges=[dict(bytes_hex=bytes.fromhex('8b4104').hex())])
        self.assertFalse(cc.aligned_unreferenced_entry(after_table, open_body, {}, ends))


class BodyRepairTests(unittest.TestCase):
    def test_split_after_wrong_noreturn_call_merges_when_gap_is_code(self):
        call = b'\xe8' + struct.pack('<i', 0x500000 - (0x401000 + 5))       # call 0x500000
        first = dict(start='00401000', end_inclusive='00401004', bytes_hex=call.hex())
        second = dict(start='00401008', end_inclusive='00401008', bytes_hex='c3')
        row = dict(entry='00401000', contiguous=False, ranges=[first, second])
        image = {0x401005: bytes.fromhex('83c404')}                         # add esp, 4
        original = lambda va, n: image[va][:n]
        found = repair_bodies.repairs([row], {0x500000}, original, DECODER)
        self.assertEqual(found, [dict(entry='00401000', start='00401000', end_inclusive='00401008')])
        self.assertEqual(repair_bodies.repairs([row], {0x600000}, original, DECODER), [])   # other callee


class StatusTests(unittest.TestCase):
    def test_render_reports_scaffold_and_hourly_rate(self):
        catalog = dict(regions=[dict(body_bytes=100, padding_bytes=4, population='p1')])
        start = datetime(2026, 10, 20, 12, tzinfo=timezone.utc)
        rows = [dict(commit='a', time=start, subject='', regions=0, body=0, padding=0),
                dict(commit='b', time=start.replace(hour=14), subject='', regions=1, body=100, padding=4)]
        text = status.render(catalog, 1000, rows)
        self.assertIn('| Original .text scaffold bytes | 896 |', text)
        self.assertIn('| `b` |', text)
        self.assertIn('| +100 | 50 |', text)
        self.assertTrue(text.startswith(status.BEGIN) and text.endswith(status.END))


if __name__ == '__main__':
    unittest.main()
