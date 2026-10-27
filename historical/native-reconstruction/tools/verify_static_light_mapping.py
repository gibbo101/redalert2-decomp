#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Inspect exact-engine static-source and terrain-converter mappings without executing originals.

Complete range/operand checks and actual dispatch are inspection evidence.
Executed ordinary outputs are recorded separately; alternate light, lifetime,
actor integration and runtime promotion are excluded.
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
from static_light_profiles import PATCHED_ADDRESSES
from inspect_patch import write_report

RANGES = {
    0x5352D0: 194,
    0x5355D0: 24,
    0x5355F0: 24,
    0x535660: 605,
    0x478CF0: 836,
    0x5276A0: 369,
    0x536630: 194,
    0x45A1D0: 17,
    0x442B3F: 151,
    0x443E10: 84,
    0x4585B0: 14,
    0x4585C0: 61,
    0x40FF10: 71,
    0x5453B0: 64,
    0x5453F0: 32,
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
    data_records=[]
    for va,size in ((0x7882E0,8),(0x787570,8),(0x7BAC08,4),(0x7BAC60,4)):
        a,b=read(disc,va,size),read(patched,PATCHED_ADDRESSES[va],size)
        if a!=b:raise ValueError('Static-light constant/foundation input differs')
        data_records.append({'disc_va':hex(va),'patched_va':hex(PATCHED_ADDRESSES[va]),
                             'bytes':size,'sha256':hashlib.sha256(a).hexdigest()})
    dispatch=[]
    for pe in (disc,patched):
        selected=lambda a:a if pe is disc else PATCHED_ADDRESSES[a]
        for table,class_name in ((0x787BBC,b'.?AVBuildingClass@@\0'),
                                 (0x790548,b'.?AVLightSourceClass@@\0')):
            table=selected(table)
            locator=struct.unpack('<I',read(pe,table-4,4))[0]
            values=struct.unpack('<5I',read(pe,locator,20))
            if values[1]!=0 or read(pe,values[3]+8,len(class_name))!=class_name:
                raise ValueError('Static-source RTTI identity differs')
            record={'profile':'allied-disc' if pe is disc else 'supplied-ra2-1006',
                    'table':hex(table),'class':class_name[:-1].decode('ascii')}
            if class_name==b'.?AVBuildingClass@@\0':
                actual=struct.unpack('<I',read(pe,table+0x48,4))[0]
                if actual!=selected(0x443E10):raise ValueError('Building coordinate getter dispatch differs')
                record.update(slot=18,target=hex(actual))
            dispatch.append(record)
    return {'disc_sha256':EXPECTED,'patched_sha256':PATCHED_EXPECTED,
            'scope':'Explicit type numeric block, complete source constructor and immediate update including cell-installation tail, terrain converter decisions and actual building coordinate dispatch. Full INI parsing, deferred updates, converter construction/lifetime, whole actor/frame parity and runtime promotion are excluded.',
            'ranges':records,'data':data_records,'dispatch':dispatch,
            'original_bytes_modified':False,'original_instructions_executed':False}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--disc', required=True, type=Path)
    parser.add_argument('--patched', required=True, type=Path)
    parser.add_argument('--output', type=Path)
    args = parser.parse_args()
    report = verify(args.disc.read_bytes(), args.patched.read_bytes())
    report['tool_sha256'] = hashlib.sha256(Path(__file__).read_bytes()).hexdigest()
    report['profile_sha256'] = hashlib.sha256((Path(__file__).resolve().parents[1]/'tests/static_light_profiles.py').read_bytes()).hexdigest()
    if args.output:
        for source in (args.disc.resolve(), args.patched.resolve()):
            if args.output.resolve().is_relative_to(source.parent):
                raise ValueError('Report must be outside either source installation')
        write_report(args.patched, args.output, report)
    print(f"Verified {len(report['ranges'])} static-light ranges / "
          f"{sum(r['instructions'] for r in report['ranges'])} instructions, "
          'two numeric constants, 1x1 dimensions and actual Building/LightSource metadata; no execution.')

if __name__ == '__main__':
    main()
