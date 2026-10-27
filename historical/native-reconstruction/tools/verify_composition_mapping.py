#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Inspect exact-engine world/TMP/unit composition mappings without executing originals.

Complete instruction-range/operand checks and consumed data identities are
inspection evidence. Executed ordinary outputs are recorded separately;
unexecuted branches, converter construction, actor integration and promotion are excluded.
"""
import argparse
import hashlib
from pathlib import Path
import struct
import sys

import pefile
from capstone import Cs, CS_ARCH_X86, CS_MODE_32
from capstone.x86_const import X86_OP_IMM, X86_OP_MEM

sys.path.insert(0, str(Path(__file__).resolve().parents[1]/'tests'))
from compare_original import EXPECTED, PATCHED_EXPECTED
from composition_profiles import PATCHED_ADDRESSES
from inspect_patch import write_report

RANGES = {
    0x411230: 52,
    0x6975D0: 40,
    0x697660: 19,
    0x697930: 52,
    0x697C90: 200,
    0x697E60: 60,
    0x41E40E: 103,
    0x485880: 1380,
    0x49EF70: 139,
    0x434A00: 1303,
    0x760730: 463,
    0x760950: 424,
    0x488650: 218,
    0x52A340: 6967,
    0x6F4A38: 287,
    0x6C52C0: 1645,
    0x4A4400: 5,
    0x4A4410: 13,
    0x53B540: 8,
    0x5CCD40: 7,
    0x435400: 32,
    0x435420: 17,
    0x7618E0: 52,
    0x4B9F30: 110,
    0x411370: 49,
    0x4112F0: 10,
    0x4113B0: 4,
    0x4113C0: 14,
    0x411290: 36,
    0x4112C0: 4,
    0x4112D0: 4,
    0x41E3E0: 46,
    0x41E477: 12,
    0x76D740: 541,
}
TABLES = {
    'projection numerator': (0x7856F8, 8),
    'projection exponent': (0x785700, 8),
    'degree 60': (0x785718, 8),
    'projection half': (0x785728, 8),
    'degree scale': (0x797260, 8),
    'gradient descriptors': (0x7B90F8, 72),
    'blitter masks': (0x7BEBA8, 8),
    'TMP row offsets': (0x78F998, 120),
    'TMP diamond': (0x78FA10, 1800),
    'unit depth constants': (0x7E09A4, 12),
}
SURFACE_METHODS = {23: 0x411370, 24: 0x4112F0, 28: 0x4113B0,
                   29: 0x4113C0, 30: 0x411290, 31: 0x4112C0, 32: 0x4112D0}


def verify(disc_data, patched_data):
    for data, digest in ((disc_data, EXPECTED), (patched_data, PATCHED_EXPECTED)):
        if hashlib.sha256(data).hexdigest() != digest:
            raise ValueError('Unsupported executable SHA-256')
    disc, patched = (pefile.PE(data=data) for data in (disc_data, patched_data))
    for pe in (disc, patched):
        if pe.FILE_HEADER.Machine != 0x14C or pe.OPTIONAL_HEADER.ImageBase != 0x400000:
            raise ValueError('Unexpected PE architecture/base')
    def read(pe, va, size):
        result = pe.get_data(va-0x400000, size)
        if len(result) != size:
            raise ValueError('Incomplete mapped range')
        return result
    decoder = Cs(CS_ARCH_X86, CS_MODE_32)
    decoder.detail = True
    records = []
    for old_va, size in RANGES.items():
        new_va = PATCHED_ADDRESSES[old_va]
        old, new = read(disc, old_va, size), read(patched, new_va, size)
        before, after = list(decoder.disasm(old, old_va)), list(decoder.disasm(new, new_va))
        if (sum(i.size for i in before) != size or sum(i.size for i in after) != size
                or len(before) != len(after)):
            raise ValueError(f'Incomplete instruction range {old_va:#x}')
        differences = []
        for a, b in zip(before, after):
            if (a.address-old_va != b.address-new_va or a.mnemonic != b.mnemonic
                    or a.size != b.size or len(a.operands) != len(b.operands)):
                raise ValueError(f'Instruction shape changed {a.address:#x}')
            masked_a, masked_b = bytearray(a.bytes), bytearray(b.bytes)
            for x, y in zip(a.operands, b.operands):
                if x.type != y.type:
                    raise ValueError('Operand type changed')
                if x.type == X86_OP_IMM:
                    v, w, offset, length = x.imm, y.imm, a.imm_offset, a.imm_size
                elif x.type == X86_OP_MEM:
                    if (x.mem.base, x.mem.index, x.mem.scale) != (y.mem.base, y.mem.index, y.mem.scale):
                        raise ValueError('Memory operand changed')
                    v, w, offset, length = x.mem.disp, y.mem.disp, a.disp_offset, a.disp_size
                else:
                    if x.reg != y.reg:
                        raise ValueError('Register operand changed')
                    continue
                if v != w:
                    if a.mnemonic.startswith('j') and old_va <= v < old_va+size:
                        if w-new_va != v-old_va:
                            raise ValueError('Internal branch changed')
                        kind = 'same relative branch'
                    elif PATCHED_ADDRESSES.get(v) == w:
                        kind = 'explicit address operand'
                    else:
                        raise ValueError(f'Unverified operand {a.address:#x}: {v:#x} -> {w:#x}')
                    differences.append({'offset': a.address-old_va, 'kind': kind})
                elif not (x.type == X86_OP_IMM and (a.mnemonic == 'call' or a.mnemonic.startswith('j'))):
                    continue
                if not length:
                    raise ValueError('Missing encoded operand')
                masked_a[offset:offset+length] = bytes(length)
                masked_b[offset:offset+length] = bytes(length)
            if masked_a != masked_b:
                raise ValueError(f'Unaccounted instruction bytes {a.address:#x}')
        records.append({'disc_va': hex(old_va), 'patched_va': hex(new_va), 'bytes': size,
                        'instructions': len(before), 'differences': differences,
                        'disc_sha256': hashlib.sha256(old).hexdigest(),
                        'patched_sha256': hashlib.sha256(new).hexdigest()})
    tables = []
    for name, (a, size) in TABLES.items():
        b = PATCHED_ADDRESSES[a]
        old, new = read(disc, a, size), read(patched, b, size)
        if old != new:
            raise ValueError('Data identity differs: '+name)
        tables.append({'name': name, 'disc_va': hex(a), 'patched_va': hex(b),
                       'bytes': size, 'sha256': hashlib.sha256(old).hexdigest()})
    # RTTI establishes actual BSurface/blitter classes; selected slot targets
    # establish methods used by the fixture, independently of address similarity.
    dispatch = []
    for pe, surface, blitter, drive in ((disc, 0x785EF8, 0x78920C, 0x78B4D4),
                                       (patched, 0x79AEF8, 0x79E20C, 0x7A04CC)):
        def selected(a):return a if pe is disc else PATCHED_ADDRESSES[a]
        for table, name, offset in ((surface, b'.?AVBSurface@@\0', 0),
                                    (blitter, b'.?AV?$BlitTransXlatAlphaZRead@G@@\0', 0),
                                    (drive, b'.?AVDriveLocomotionClass@@\0', 4)):
            locator = struct.unpack('<I', read(pe, table-4, 4))[0]
            values = struct.unpack('<5I', read(pe, locator, 20))
            if values[1] != offset or read(pe, values[3]+8, len(name)) != name:
                raise ValueError('Composition RTTI identity differs')
        for table, slots in ((surface, SURFACE_METHODS), (blitter, {1: 0x488650}),
                             (drive, {14: 0x4A4400, 15: 0x4A4410})):
            for slot, target in slots.items():
                actual = struct.unpack('<I', read(pe, table+4*slot, 4))[0]
                if actual != selected(target) or target not in RANGES:
                    raise ValueError('Composition vtable slot differs')
                dispatch.append({'profile': 'allied-disc' if pe is disc else 'supplied-ra2-1006',
                                 'table': hex(table), 'slot': slot, 'target': hex(actual)})
    return {'disc_sha256': EXPECTED, 'patched_sha256': PATCHED_EXPECTED,
            'scope': 'Explicit world/TMP/unit composition ranges, helper blocks, data and RTTI; execution and whole actor/frame parity are separate',
            'ranges': records, 'data': tables, 'dispatch': dispatch,
            'original_bytes_modified': False, 'original_instructions_executed': False}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--disc', required=True, type=Path)
    parser.add_argument('--patched', required=True, type=Path)
    parser.add_argument('--output', type=Path)
    args = parser.parse_args()
    report = verify(args.disc.read_bytes(), args.patched.read_bytes())
    report['tool_sha256'] = hashlib.sha256(Path(__file__).read_bytes()).hexdigest()
    report['profile_sha256'] = hashlib.sha256((Path(__file__).resolve().parents[1]/'tests/composition_profiles.py').read_bytes()).hexdigest()
    if args.output:
        for source in (args.disc.resolve(), args.patched.resolve()):
            if args.output.resolve().is_relative_to(source.parent):
                raise ValueError('Report must be outside either source installation')
        write_report(args.patched, args.output, report)
    print(f"Verified {len(report['ranges'])} composition ranges / "
          f"{sum(r['instructions'] for r in report['ranges'])} instructions, "
          'referenced data and actual surface/blitter/Drive slots; no execution.')

if __name__ == '__main__':
    main()
