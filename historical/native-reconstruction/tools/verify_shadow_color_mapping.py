#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Inspect exact-engine HSV/remap and shadow mappings without executing originals.

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
from shadow_color_profiles import PATCHED_ADDRESSES
from inspect_patch import write_report

RANGES = {
    0x4FE400: 277,
    0x65A4F0: 253,
    0x70CAC0: 3290,
    0x4A00D0: 178,
    0x53B160: 240,
    0x70BDC0: 337,
    0x70E670: 659,
    0x487170: 94,
    0x75F770: 80,
    0x5FAB10: 26,
    0x58CBA0: 92,
    0x58CC00: 263,
    0x619BC0: 30,
    0x619C90: 59,
    0x61A3F0: 266,
}
TABLES = {
    'player ramp angles': (0x7940E0, 32),
    'projection midpoint': (0x7998CC, 8),
    'heading step': (0x788090, 8),
    'flat pose zero': (0x785708, 8),
    'pose threshold': (0x788170, 8),
    'packed step scale': (0x7860AC, 4),
    'coordinate rounding': (0x7998D4, 4),
    'axis rotation one': (0x7867F8, 4),
    'quaternion zero': (0x786610, 8),
    'quaternion half angle': (0x788D80, 4),
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
    dispatch=[]
    for pe, surface, shadow, drive in ((disc,0x785EF8,0x78939C,0x78B4D4),
                                      (patched,0x79AEF8,0x79E39C,0x7A04CC)):
        def selected(a):return a if pe is disc else PATCHED_ADDRESSES[a]
        for table,name,offset in ((surface,b'.?AVBSurface@@\0',0),
                                  (shadow,b'.?AV?$BlitTransDarkenZRead@G@@\0',0),
                                  (drive,b'.?AVDriveLocomotionClass@@\0',4)):
            locator=struct.unpack('<I',read(pe,table-4,4))[0]
            values=struct.unpack('<5I',read(pe,locator,20))
            if values[1]!=offset or read(pe,values[3]+8,len(name))!=name:
                raise ValueError('Shadow/color RTTI identity differs')
        for table,slot,target in ((surface,10,0x75F770),(shadow,1,0x487170),(drive,10,0x4A00D0)):
            actual=struct.unpack('<I',read(pe,table+4*slot,4))[0]
            if actual!=selected(target):raise ValueError('Shadow/color dispatch slot differs')
            dispatch.append({'profile':'allied-disc' if pe is disc else 'supplied-ra2-1006',
                             'table':hex(table),'slot':slot,'target':hex(actual)})
    return {'disc_sha256':EXPECTED,'patched_sha256':PATCHED_EXPECTED,
            'scope':'Explicit HSV/remap prefix, shadow init/pose/queue/plot/span ranges, consumed data and actual dispatch. Execution, nonflat/actor/frame/lifetime parity and runtime promotion are separate.',
            'ranges':records,'data':tables,'dispatch':dispatch,
            'original_bytes_modified':False,'original_instructions_executed':False}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--disc', required=True, type=Path)
    parser.add_argument('--patched', required=True, type=Path)
    parser.add_argument('--output', type=Path)
    args = parser.parse_args()
    report = verify(args.disc.read_bytes(), args.patched.read_bytes())
    report['tool_sha256'] = hashlib.sha256(Path(__file__).read_bytes()).hexdigest()
    report['profile_sha256'] = hashlib.sha256((Path(__file__).resolve().parents[1]/'tests/shadow_color_profiles.py').read_bytes()).hexdigest()
    if args.output:
        for source in (args.disc.resolve(), args.patched.resolve()):
            if args.output.resolve().is_relative_to(source.parent):
                raise ValueError('Report must be outside either source installation')
        write_report(args.patched, args.output, report)
    print(f"Verified {len(report['ranges'])} shadow/color ranges / "
          f"{sum(r['instructions'] for r in report['ranges'])} instructions, "
          'referenced data and actual pixel/shadow/Drive slots; no execution.')

if __name__ == '__main__':
    main()
