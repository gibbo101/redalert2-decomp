#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Inspect exact-engine lit shadow-key key and index mappings without executing originals.

Complete range/operand checks and actual dispatch are inspection evidence.
Executed healthy outputs are recorded separately; alternate status, lifetime,
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
from shadow_key_profiles import PATCHED_ADDRESSES
from inspect_patch import write_report

RANGES = {
    0x006F4327: 31,
    0x006F4D03: 198,
    0x006FF65A: 30,
    0x004C94F0: 205,
    0x0053B250: 40,
    0x0053B570: 5,
    0x006F5086: 47,
    0x00482D00: 19,
    0x006D03D8: 26,
    0x006D2524: 26,
    0x0046C000: 95,
    0x00482CC0: 57,
    0x006D25A6: 46,
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
    names=[]
    for i in range(8):
        a,b=(struct.unpack('<I',read(pe,va+i*4,4))[0] for pe,va in
             ((disc,0x7BE9DC),(patched,PATCHED_ADDRESSES[0x7BE9DC])))
        if PATCHED_ADDRESSES[a]!=b:raise ValueError('SpeedType table association differs')
        text=read(disc,a,80).split(b'\0')[0]
        if text!=read(patched,b,80).split(b'\0')[0]:raise ValueError('SpeedType enum name differs')
        names.append(text.decode('ascii'))
    if names!=['Foot','Track','Wheel','Hover','Winged','Float','Amphibious','FloatBeach']:
        raise ValueError('SpeedType enum index/name order differs')
    data_records.append({'disc_va':hex(0x7BE9DC),'patched_va':hex(PATCHED_ADDRESSES[0x7BE9DC]),
                         'ordered_names':names,'entries':8})
    for va in (0x7E1938,0x7BCAC0,0x7E0FF4):
        text=read(disc,va,80).split(b'\0')[0]+b'\0'
        if read(patched,PATCHED_ADDRESSES[va],len(text))!=text:raise ValueError('Shadow type INI string differs')
        data_records.append({'disc_va':hex(va),'patched_va':hex(PATCHED_ADDRESSES[va]),
                             'bytes':len(text),'sha256':hashlib.sha256(text).hexdigest()})
    dispatch=[]
    for pe in (disc,patched):
        selected=lambda a:a if pe is disc else PATCHED_ADDRESSES[a]
        table=selected(0x78B4D4);locator=struct.unpack('<I',read(pe,table-4,4))[0]
        values=struct.unpack('<5I',read(pe,locator,20));name=b'.?AVDriveLocomotionClass@@\0'
        if values[1]!=4 or read(pe,values[3]+8,len(name))!=name:raise ValueError('Drive shadow interface RTTI differs')
        slots=[]
        for offset,target in ((0x20,0x53B570),(0x28,0x4A00D0),(0x30,0x53B250)):
            actual=struct.unpack('<I',read(pe,table+offset,4))[0]
            if actual!=selected(target):raise ValueError('Actual Drive shadow slot differs')
            slots.append({'offset':hex(offset),'target':hex(actual)})
        rows=list(decoder.disasm(read(pe,selected(0x46C000),95),selected(0x46C000)))
        parser=next(i for i in rows if i.address-selected(0x46C000)==0x42)
        if parser.mnemonic!='call' or parser.operands[0].imm!=selected(0x482CC0):raise ValueError('Actual SpeedType parser caller differs')
        rows=list(decoder.disasm(read(pe,selected(0x6F5086),47),selected(0x6F5086)))
        if rows[-1].mnemonic!='call' or rows[-1].operands[0].imm!=selected(0x4C94F0):raise ValueError('Actual Unit Foot shadow caller differs')
        dispatch.append({'profile':'allied-disc' if pe is disc else 'supplied-ra2-1006',
                         'drive_interface':hex(table),'slots':slots,'enum_parser_target':hex(parser.operands[0].imm),
                         'unit_foot_caller':hex(rows[-1].address)})
    return {'disc_sha256':EXPECTED,'patched_sha256':PATCHED_EXPECTED,
            'scope':'Actual Unit seed/type/default/model selection blocks, complete Foot/Drive point/predicate and inspected enum/INI associations/callers. Executed flat domain excludes full Unit/INI initialization, nonflat/status/airborne, original compressed pool/lifetime, whole actor/frame and runtime promotion.',
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
    report['profile_sha256'] = hashlib.sha256((Path(__file__).resolve().parents[1]/'tests/shadow_key_profiles.py').read_bytes()).hexdigest()
    if args.output:
        for source in (args.disc.resolve(), args.patched.resolve()):
            if args.output.resolve().is_relative_to(source.parent):
                raise ValueError('Report must be outside either source installation')
        write_report(args.patched, args.output, report)
    print(f"Verified {len(report['ranges'])} shadow-key ranges / "
          f"{sum(r['instructions'] for r in report['ranges'])} instructions, "
          'enum names, INI association and actual Unit/Drive/Foot dispatch; no execution.')

if __name__ == '__main__':
    main()
