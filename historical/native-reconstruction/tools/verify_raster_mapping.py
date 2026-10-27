#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Inspect exact-engine voxel loader/pose/raster mappings without executing originals.

The complete range/operand checks and data identities below are inspection evidence.
Executed stock outputs are recorded separately; malformed-loader, alternate
dispatch, actor boundaries and runtime promotion remain excluded.
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
from raster_profiles import PATCHED_ADDRESSES
from inspect_patch import write_report

RANGES = {
    0x70DBC0: 1762,
    0x70BC30: 387,
    0x70BF20: 503,
    0x70C340: 545,
    0x49FC20: 1189,
    0x6F4744: 112,
    0x70C7B0: 19,
    0x70C7D0: 19,
    0x70D6DE: 54,
    0x58DE30: 508,
    0x58CD10: 43,
    0x70CA10: 167,
    0x70BB30: 245,
    0x70E3A0: 711,
    0x4B9FA0: 66,
    0x4B9FF0: 73,
    0x58D410: 158,
    0x58D530: 156,
    0x58D650: 156,
    0x58E030: 120,
    0x58E0D0: 181,
    0x58D980: 113,
    0x53B0C0: 159,
    0x58CA90: 33,
    0x58CAC0: 22,
    0x70E2C0: 34,
    0x70C730: 3,
    0x784180: 154,
    0x7842A0: 155,
    0x40AED0: 97,
    0x510D29: 12,
}
TABLES = {
    'traversal': (0x7E36B0, 288),
    'trig': (0x7EA0E4, 40960),
    'trig scales': (0x7C3128, 8),
    'heading step': (0x788090, 8),
    'degree scale': (0x7998C0, 8),
    'degree 45': (0x785710, 8),
    'degree 60': (0x785718, 8),
    'default light angle': (0x785CF0, 4),
    'float zero': (0x785738, 4),
    'double zero': (0x785708, 8),
    'pose threshold': (0x788170, 8),
    'projection midpoint': (0x7998C8, 8),
    'projection scale': (0x7998D4, 4),
    'packed step scale': (0x7860AC, 4),
    'crop coefficient': (0x788D80, 4),
}


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
            if (a.address-old_va != b.address-new_va or (a.mnemonic != b.mnemonic and not (a.address == 0x70DE06 and a.mnemonic == "jl" and b.mnemonic == "jb"))
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
            if a.address == 0x70DE06:
                if a.bytes[0] != 0x7C or b.bytes[0] != 0x72:
                    raise ValueError("Unexpected VXL loop opcode")
                masked_a[0] = masked_b[0] = 0
                differences.append({"offset": a.address-old_va, "kind": "VXL loop jl to jb; stock success domain only"})
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
    # Actual generator dispatch operand selects both lit assembly paths.
    dispatch = []
    for index in (4, 5):
        a = struct.unpack('<I', read(disc, 0x7E3630+4*index, 4))[0]
        b = struct.unpack('<I', read(patched, 0x7F9DE0+4*index, 4))[0]
        if PATCHED_ADDRESSES.get(a) != b or a not in RANGES:
            raise ValueError('Lit raster dispatch target differs')
        dispatch.append({'index': index, 'disc_va': hex(a), 'patched_va': hex(b)})
    # Independently inspect the existing Drive RTTI/interface table's Draw_Matrix
    # slot, distinguishing it from the similar Ship prefix.
    for pe, table, target in ((disc, 0x78B4D4, 0x49FC20), (patched, 0x7A04CC, 0x4A0050)):
        locator = struct.unpack('<I', read(pe, table-4, 4))[0]
        values = struct.unpack('<5I', read(pe, locator, 20))
        name = b'.?AVDriveLocomotionClass@@\x00'
        if values[1] != 4 or read(pe, values[3]+8, len(name)) != name:
            raise ValueError('Drive interface RTTI differs')
        if struct.unpack('<I', read(pe, table+9*4, 4))[0] != target:
            raise ValueError('Drive Draw_Matrix interface identity differs')
    return {'disc_sha256': EXPECTED, 'patched_sha256': PATCHED_EXPECTED,
            'scope': 'Explicit bounded loader/pose/raster ranges and data; execution and full actor/frame parity are separate',
            'ranges': records, 'data': tables, 'dispatch': dispatch, 'loader_branch_difference': 'jl to jb at optional embedded-palette pointer loop; UseContainedPalette=0 skips it',
            'original_bytes_modified': False, 'original_instructions_executed': False}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--disc', required=True, type=Path)
    parser.add_argument('--patched', required=True, type=Path)
    parser.add_argument('--output', type=Path)
    args = parser.parse_args()
    report = verify(args.disc.read_bytes(), args.patched.read_bytes())
    report['tool_sha256'] = hashlib.sha256(Path(__file__).read_bytes()).hexdigest()
    report['profile_sha256'] = hashlib.sha256((Path(__file__).resolve().parents[1]/'tests/raster_profiles.py').read_bytes()).hexdigest()
    if args.output:
        for source in (args.disc.resolve(), args.patched.resolve()):
            if args.output.resolve().is_relative_to(source.parent):
                raise ValueError('Report must be outside either source installation')
        write_report(args.patched, args.output, report)
    print(f"Verified {len(report['ranges'])} raster ranges / "
          f"{sum(r['instructions'] for r in report['ranges'])} instructions, "
          'referenced data and two lit dispatch entries; no execution.')

if __name__ == '__main__':
    main()
