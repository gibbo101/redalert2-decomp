#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Inspect the two exact engines' bounded Drive/targeting/timing mappings.

Instruction structure/address operands are inspection evidence, not proof of
unexecuted branches. Track/bearing/sqrt data and Drive RTTI/vtable links are checked
separately. No original instructions execute here; runtime support stays disc-only.
"""
import argparse
import hashlib
from pathlib import Path
import struct
import sys

import pefile
from capstone import Cs, CS_ARCH_X86, CS_MODE_32
from capstone.x86_const import X86_OP_IMM, X86_OP_MEM
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tests'))
from compare_original import EXPECTED, PATCHED_EXPECTED
from movement_profiles import PATCHED_ADDRESSES
from inspect_patch import write_report

# Exact ends inspected locally, including all intervening original instructions.
RANGES = {
    0x491400: 172, 0x4914B0: 116, 0x49FA00: 181, 0x49FAC0: 200,
    0x4A01C0: 1483, 0x4A0BD0: 5705, 0x4A2240: 8373, 0x4A4310: 124,
    0x4C95C0: 166, 0x4C2910: 103, 0x6CE2B0: 22, 0x6F03D0: 544,
    0x716B20: 114, 0x76A6B0: 61, 0x5CAC70: 122, 0x4BA120: 178,
    0x53E660: 676, 0x68F980: 10, 0x4B9F30: 110,
    0x6D2021: 64, 0x4CF4C4: 7, 0x53DEF2: 36,
}
TABLES = {
    'transitions': (0x78B188, 0x7A0180, 768),
    'stop cap and nearby drive constants': (0x789A50, 0x79EA48, 24),
    'interpolation/arrival constants': (0x78B5C8, 0x7A05C0, 24),
    'bearing table and step': (0x7FC114, 0x813DF4, 16392),
    'bearing float half-pi': (0x78BF94, 0x7A0F8C, 8),
    'bearing double pi': (0x788158, 0x79D158, 8),
    'bearing double half-pi and scale': (0x786628, 0x79B628, 16),
    'square-root table': (0x80011C, 0x817DFC, 65536),
    'conversion control word': (0x7C39F4, 0x7D8964, 2),
}
TRACK_COUNTS = (24, 32, 55, 39, 62, 57)


def verify(disc_data, patched_data):
    for data, digest in ((disc_data, EXPECTED), (patched_data, PATCHED_EXPECTED)):
        if hashlib.sha256(data).hexdigest() != digest:
            raise ValueError('Unsupported executable SHA-256')
    disc, patched = (pefile.PE(data=data) for data in (disc_data, patched_data))
    for pe in (disc, patched):
        if pe.FILE_HEADER.Machine != 0x14C or pe.OPTIONAL_HEADER.ImageBase != 0x400000:
            raise ValueError('Unexpected PE architecture/base')
    def read(pe, va, size):
        result = pe.get_data(va - 0x400000, size)
        if len(result) != size:
            raise ValueError('Incomplete mapped range')
        return result
    decoder = Cs(CS_ARCH_X86, CS_MODE_32)
    decoder.detail = True
    relocations, records = {}, []
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
                    v, w = x.imm, y.imm
                    offset, length = a.imm_offset, a.imm_size
                elif x.type == X86_OP_MEM:
                    if (x.mem.base, x.mem.index, x.mem.scale) != (y.mem.base, y.mem.index, y.mem.scale):
                        raise ValueError('Memory operand changed')
                    v, w = x.mem.disp, y.mem.disp
                    offset, length = a.disp_offset, a.disp_size
                else:
                    if x.reg != y.reg:
                        raise ValueError('Register operand changed')
                    continue
                if v == w:
                    # An unchanged external call address still has a different
                    # relative encoding when the containing routine moves.
                    if x.type == X86_OP_IMM and (a.mnemonic == 'call' or a.mnemonic.startswith('j')):
                        masked_a[offset:offset+length] = bytes(length)
                        masked_b[offset:offset+length] = bytes(length)
                    continue
                kind = 'address operand'
                if a.mnemonic.startswith('j') and old_va <= v < old_va+size:
                    if w-new_va != v-old_va:
                        raise ValueError('Internal branch changed')
                    kind = 'same relative branch'
                elif (old_va == 0x53DEF2 and x.type == X86_OP_MEM
                      and v == 0x38 and w == 0x14):
                    kind = 'frame setup local stack slot'
                elif not (0x400000 <= v < 0xC00000 and 0x400000 <= w < 0xC00000):
                    raise ValueError(f'Non-address constant changed {a.address:#x}')
                else:
                    if v in relocations and relocations[v] != w:
                        raise ValueError('Inconsistent address operand')
                    if v in PATCHED_ADDRESSES and PATCHED_ADDRESSES[v] != w:
                        raise ValueError('Fixture profile disagrees with instruction operand')
                    relocations[v] = w
                if not length:
                    raise ValueError('Missing encoded operand')
                masked_a[offset:offset+length] = bytes(length)
                masked_b[offset:offset+length] = bytes(length)
                differences.append({'offset': a.address-old_va, 'kind': kind})
            if masked_a != masked_b:
                raise ValueError(f'Unaccounted instruction bytes {a.address:#x}')
        records.append({'disc_va': hex(old_va), 'patched_va': hex(new_va), 'bytes': size,
                        'instructions': len(before), 'differences': differences,
                        'disc_sha256': hashlib.sha256(old).hexdigest(),
                        'patched_sha256': hashlib.sha256(new).hexdigest()})
    data_records = []
    for name, (a, b, size) in TABLES.items():
        old, new = read(disc, a, size), read(patched, b, size)
        if old != new:
            raise ValueError('Data identity differs: '+name)
        data_records.append({'name': name, 'disc_va': hex(a), 'patched_va': hex(b),
                             'bytes': size, 'sha256': hashlib.sha256(old).hexdigest()})
    tracks = []
    for raw, count in enumerate(TRACK_COUNTS, 1):
        old = struct.unpack('<Iiii', read(disc, 0x78B0A8+16*raw, 16))
        new = struct.unpack('<Iiii', read(patched, 0x7A00A0+16*raw, 16))
        if old[1:] != new[1:]:
            raise ValueError('Raw descriptor indices changed')
        old_points, new_points = read(disc, old[0], count*12), read(patched, new[0], count*12)
        if old_points != new_points:
            raise ValueError('Track point data changed')
        if struct.unpack('<ii', old_points[-12:-4]) != (0, 0):
            raise ValueError('Track terminator changed')
        tracks.append({'raw': raw, 'disc_va': hex(old[0]), 'patched_va': hex(new[0]),
                       'points': count, 'indices': old[1:],
                       'sha256': hashlib.sha256(old_points).hexdigest()})
    # The interface vtable's preceding RTTI locator points to Drive, at offset +4.
    for pe, vt, descriptor in ((disc, 0x78B4D4, None), (patched, 0x7A04CC, 0x7D5F10)):
        locator = struct.unpack('<I', read(pe, vt-4, 4))[0]
        values = struct.unpack('<5I', read(pe, locator, 20))
        if values[1] != 4 or (descriptor is not None and values[3] != descriptor):
            raise ValueError('Drive interface RTTI linkage changed')
        type_name = b'.?AVDriveLocomotionClass@@\x00'
        if read(pe, values[3]+8, len(type_name)) != type_name:
            raise ValueError('Wrong locomotor interface')
        entries = struct.unpack('<20I', read(pe, vt, 80))
        wanted = (0x4A01C0, 0x49FA00, 0x49FAC0) if pe is disc else (0x4A05F0, 0x49FE30, 0x49FEF0)
        if entries[16:19] != wanted:
            raise ValueError('Wrong Drive process/command methods')
    return {'disc_sha256': EXPECTED, 'patched_sha256': PATCHED_EXPECTED,
            'scope': 'Bounded instruction structure/operands and table identity; executed differential evidence is separate; not all branches or whole engine parity',
            'ranges': records, 'data': data_records, 'tracks': tracks,
            'drive_rtti_and_interface_slots_verified': True,
            'original_instructions_executed': False, 'original_bytes_modified': False}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--disc', type=Path, required=True)
    parser.add_argument('--patched', type=Path, required=True)
    parser.add_argument('--output', type=Path)
    args = parser.parse_args()
    report = verify(args.disc.read_bytes(), args.patched.read_bytes())
    report['tool_sha256'] = hashlib.sha256(Path(__file__).read_bytes()).hexdigest()
    report['profile_sha256'] = hashlib.sha256((Path(__file__).resolve().parents[1]/'tests/movement_profiles.py').read_bytes()).hexdigest()
    if args.output:
        for source in (args.disc.resolve(), args.patched.resolve()):
            if args.output.resolve().is_relative_to(source.parent):
                raise ValueError('Report must be outside either source installation')
        write_report(args.patched, args.output, report)
    print(f"Verified {len(report['ranges'])} bounded ranges / {sum(r['instructions'] for r in report['ranges'])} instructions, "
          f"six Drive streams, timing/bearing/math data and Drive RTTI; no execution.")

if __name__ == '__main__':
    main()
