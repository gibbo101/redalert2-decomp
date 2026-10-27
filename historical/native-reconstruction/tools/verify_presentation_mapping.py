#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Inspect exact-engine lighting/palette/depth mappings without executing originals.

The complete range/operand checks and data identities below are inspection evidence.
Executed original/native outputs are recorded separately; unexecuted optimized
palette branches, raster/actor boundaries and runtime promotion remain excluded.
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
from presentation_profiles import PATCHED_ADDRESSES
from inspect_patch import write_report

RANGES = {0x710480: 120, 0x710500: 391, 0x710740: 20, 0x536B30: 1135,
          0x487750: 121, 0x70F4C9: 51, 0x4B9F30: 110, 0x76A6B0: 61}
TABLES = {'normal counts': (0x7E37E4, 20), 'square-root mantissas': (0x80011C, 65536),
          'palette coefficient': (0x7905D0, 8), 'shade scale': (0x7998D8, 4),
          'float zero': (0x785738, 4), 'double zero': (0x786610, 8),
          'sqrt double constant': (0x788578, 8), 'conversion control word': (0x7C39F4, 2),
          'default affected mask': (0x7CA390, 256)}


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
    counts = struct.unpack('<5I', read(disc, 0x7E37E4, 20))
    if counts != (0, 16, 36, 64, 245):
        raise ValueError('Unexpected normal counts')
    normals = []
    for index, count in enumerate(counts):
        # The shade routines' actual indexed pointer/count operands select these
        # arrays, not an arbitrary matching byte sequence elsewhere in the PE.
        a = struct.unpack('<I', read(disc, 0x7E37D0+4*index, 4))[0]
        b = struct.unpack('<I', read(patched, 0x7F9F80+4*index, 4))[0]
        if count:
            old, new = read(disc, a, count*12), read(patched, b, count*12)
            if old != new:
                raise ValueError('Referenced normal array changed')
            normals.append({'encoding': index, 'count': count, 'disc_va': hex(a),
                            'patched_va': hex(b), 'sha256': hashlib.sha256(old).hexdigest()})
        elif a != 0 or b != 0:
            raise ValueError('Unexpected empty normal pointer')
    # All four optimized dispatch entries remain local to the checked palette
    # routine. Their callees were not executed and receive no parity claim.
    for a, b in zip(struct.unpack('<4I', read(disc, 0x536FA0, 16)),
                    struct.unpack('<4I', read(patched, 0x538F10, 16))):
        if not (0x536B30 <= a < 0x536B30+1135 and b-0x538AA0 == a-0x536B30):
            raise ValueError('Palette dispatch table changed')
    return {'disc_sha256': EXPECTED, 'patched_sha256': PATCHED_EXPECTED,
            'scope': 'Complete primitive ranges/explicit operands and referenced data only; execution/actor/raster/frame parity is separate',
            'ranges': records, 'data': tables, 'normals': normals,
            'original_bytes_modified': False, 'original_instructions_executed': False}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--disc', required=True, type=Path)
    parser.add_argument('--patched', required=True, type=Path)
    parser.add_argument('--output', type=Path)
    args = parser.parse_args()
    report = verify(args.disc.read_bytes(), args.patched.read_bytes())
    report['tool_sha256'] = hashlib.sha256(Path(__file__).read_bytes()).hexdigest()
    report['profile_sha256'] = hashlib.sha256((Path(__file__).resolve().parents[1]/'tests/presentation_profiles.py').read_bytes()).hexdigest()
    if args.output:
        for source in (args.disc.resolve(), args.patched.resolve()):
            if args.output.resolve().is_relative_to(source.parent):
                raise ValueError('Report must be outside either source installation')
        write_report(args.patched, args.output, report)
    print(f"Verified {len(report['ranges'])} presentation ranges / "
          f"{sum(r['instructions'] for r in report['ranges'])} instructions, "
          'nine constant/table ranges and four referenced normal arrays; no execution.')

if __name__ == '__main__':
    main()
