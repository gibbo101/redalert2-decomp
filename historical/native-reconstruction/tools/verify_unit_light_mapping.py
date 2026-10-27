#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Inspect exact-engine ordinary unit-light and RGB565 converter mappings without executing originals.

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
from unit_light_profiles import PATCHED_ADDRESSES
from inspect_patch import write_report

RANGES = {
    0x63D76E: 17,
    0x41E3E0: 293,
    0x41B320: 61,
    0x6F5B21: 107,
    0x6CCDF0: 49,
    0x6F4013: 33,
    0x65A9A0: 97,
    0x65A4F0: 331,
    0x5368F0: 573,
    0x4838E0: 6145,
    0x6F59FB: 23,
    0x6F4C28: 108,
    0x519605: 39,
    0x63EE52: 46,
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
    for va,size in ((0x7882E0,8),(0x7940E0,32),(0x7DC228,256),(0x7CA390,256)):
        a,b=read(disc,va,size),read(patched,PATCHED_ADDRESSES[va],size)
        if a!=b:raise ValueError('Unit-light numeric/mask input differs')
        data_records.append({'disc_va':hex(va),'patched_va':hex(PATCHED_ADDRESSES[va]),
                             'bytes':size,'sha256':hashlib.sha256(a).hexdigest()})
    dispatch=[]
    for pe in (disc,patched):
        selected=lambda a:a if pe is disc else PATCHED_ADDRESSES[a]
        for old_table,class_name,slots in (
                (0x798C90,b'.?AVUnitClass@@\0',((104,0x41B320),)),
                (0x7905C4,b'.?AVLightConvertClass@@\0',((0,0x536FC0),)),
                (0x78920C,b'.?AV?$BlitTransXlatAlphaZRead@G@@\0',((1,0x488650),))):
            table=selected(old_table)
            locator=struct.unpack('<I',read(pe,table-4,4))[0]
            values=struct.unpack('<5I',read(pe,locator,20))
            if values[1]!=0 or read(pe,values[3]+8,len(class_name))!=class_name:
                raise ValueError('Unit-light RTTI identity differs: '+hex(table))
            for slot,target in slots:
                actual=struct.unpack('<I',read(pe,table+slot*4,4))[0]
                if actual!=selected(target):raise ValueError('Unit-light dispatch differs')
                dispatch.append({'profile':'allied-disc' if pe is disc else 'supplied-ra2-1006',
                                 'table':hex(table),'class':class_name[:-1].decode('ascii'),
                                 'slot':slot,'target':hex(actual)})
        rows=list(decoder.disasm(read(disc,0x4838E0,RANGES[0x4838E0]),0x4838E0))
        tables=sorted({op.imm for ins in rows for op in ins.operands
                       if op.type==X86_OP_IMM and 0x788F70<=op.imm<=0x78950C})
        for table in tables:
            def name_at(engine,va):
                locator=struct.unpack('<I',read(engine,va-4,4))[0]
                fields=struct.unpack('<5I',read(engine,locator,20))
                if fields[1]!=0:raise ValueError('Blitter RTTI object offset differs')
                return read(engine,fields[3]+8,200).split(b'\0',1)[0].decode('ascii')
            name=name_at(disc,table)
            if name_at(pe,selected(table))!=name:raise ValueError('Constructed blitter RTTI differs')
        dispatch.append({'profile':'allied-disc' if pe is disc else 'supplied-ra2-1006',
                         'constructed_blitter_tables':len(tables),'method_body_parity_claimed':False})
    return {'disc_sha256':EXPECTED,'patched_sha256':PATCHED_EXPECTED,
            'scope':'Explicit ExtraUnitLight/brightness/house blocks, complete coordinates/effects/scheme/LightConvert and full byte/word Convert initializer, inspected callers and actual dispatch. Unexecuted alternate/status/destructor/blitter methods, original heap/house/converter lifetime, full actor/frame and runtime promotion are excluded.',
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
    report['profile_sha256'] = hashlib.sha256((Path(__file__).resolve().parents[1]/'tests/unit_light_profiles.py').read_bytes()).hexdigest()
    if args.output:
        for source in (args.disc.resolve(), args.patched.resolve()):
            if args.output.resolve().is_relative_to(source.parent):
                raise ValueError('Report must be outside either source installation')
        write_report(args.patched, args.output, report)
    print(f"Verified {len(report['ranges'])} unit-light ranges / "
          f"{sum(r['instructions'] for r in report['ranges'])} instructions, "
          'numeric/mask inputs and actual Unit/LightConvert/ordinary-span metadata; no execution.')

if __name__ == '__main__':
    main()
