#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Inspect exact-engine healthy Terrain/SHP/type mappings without executing originals.

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
from scenery_profiles import PATCHED_ADDRESSES
from inspect_patch import write_report

RANGES = {
    0x006D8B00: 427,
    0x0049EAB3: 1189,
    0x00434F80: 1137,
    0x00485B40: 676,
    0x0048BC60: 415,
    0x0048A4A0: 221,
    0x00489000: 225,
    0x004878C0: 109,
    0x006DA7A0: 57,
    0x006DA5D0: 174,
    0x0076E780: 145,
    0x005CCD40: 7,
    0x0049F000: 32,
    0x005CACF0: 18,
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
    # These reordered regions are not opcode parity. Exact reviewed fingerprints
    # and the shared body define a complete wrapper inspection boundary.
    changed = [{'disc_va': 4844160, 'disc_bytes': 51, 'patched_va': 4845216, 'patched_bytes': 62, 'disc_sha256': '2b452ffa7a2bdece38b3039e4b7c4a0ddcd1002ea3e8dfcfe7f8562dcf83b35a', 'patched_sha256': '8821c3f5532eccbbe802923b29240aa4850d186337a5d02a9c591470ccf7956a', 'reviewed_change': 'valid prologue equivalence; patched null-shape early return'}, {'disc_va': 4845400, 'disc_bytes': 24, 'patched_va': 4846467, 'patched_bytes': 24, 'disc_sha256': '8ef729d39726a9ddf49b47e0f28b01fa454786c4a39cda02d10415e87d25985a', 'patched_sha256': 'bb1342955259deb2bb0f65babcf5469a91b162179fc59ed6f6fca340275deb2c', 'reviewed_change': 'EBX pop delayed; temporary-surface destructor pointer compensates by four bytes'}]
    for row in changed:
        for pe, prefix in ((disc,'disc'),(patched,'patched')):
            if hashlib.sha256(read(pe,row[prefix+'_va'],row[prefix+'_bytes'])).hexdigest()!=row[prefix+'_sha256']:
                raise ValueError('Reviewed SHP wrapper region differs')
    # Actual theater extension selection consumes the inline three-byte extension.
    data_records=[]
    for i,name in enumerate((b'TEM\0',b'SNO\0',b'URB\0')):
        old=0x785BAC+i*104;new=PATCHED_ADDRESSES[0x785BAC]+i*104
        if read(disc,old,4)!=name or read(patched,new,4)!=name:raise ValueError('Theater extension differs')
        data_records.append({'disc_va':hex(old),'patched_va':hex(new),'extension':name[:-1].decode('ascii')})
    dispatch=[]
    for pe in (disc,patched):
        selected=lambda a:a if pe is disc else PATCHED_ADDRESSES[a]
        for table,expected_name,slots in (
            (0x79827C,b'.?AVTerrainClass@@\0',((0x68,0x5CACF0),(0x10C,0x6D8B00),(0x1A0,0x41B320),(0x1B8,0x5CCD40))),
            (0x798490,b'.?AVTerrainTypeClass@@\0',((0x64,0x6DA7A0),)),
            (0x788FA8,b'.?AV?$RLEBlitTransXlatAlphaZReadWrite@G@@\0',((4,0x48BC60),)),
            (0x789074,b'.?AV?$RLEBlitTransDarkenZReadWrite@G@@\0',((4,0x48A4A0),)),
            (0x78918C,b'.?AV?$BlitTransXlatAlphaZReadWrite@G@@\0',((4,0x489000),)),
            (0x7892FC,b'.?AV?$BlitTransDarkenZReadWrite@G@@\0',((4,0x4878C0),))):
            t=selected(table);locator=struct.unpack('<I',read(pe,t-4,4))[0]
            values=struct.unpack('<5I',read(pe,locator,20))
            name=read(pe,values[3]+8,180).split(b'\0')[0]+b'\0'
            if values[1]!=0 or name!=expected_name:raise ValueError('Actual scenery RTTI differs: '+hex(table)+' '+repr(name))
            for offset,target in slots:
                actual=struct.unpack('<I',read(pe,t+offset,4))[0]
                if actual!=selected(target):raise ValueError('Actual scenery dispatch differs')
                dispatch.append({'profile':'allied-disc' if pe is disc else 'supplied-ra2-1006',
                                 'table':hex(t),'offset':hex(offset),'target':hex(actual),'class':name[:-1].decode('ascii')})
        rows=list(decoder.disasm(read(pe,selected(0x6D8B00),RANGES[0x6D8B00]),selected(0x6D8B00)))
        shape_calls=[i for i in rows if i.mnemonic=='call' and i.operands[0].type==X86_OP_IMM and i.operands[0].imm==selected(0x49EA80)]
        if len(shape_calls)!=2:raise ValueError('Actual Terrain body/shadow wrapper callers differ')
        dispatch.append({'profile':'allied-disc' if pe is disc else 'supplied-ra2-1006','terrain_shape_callers':[hex(i.address) for i in shape_calls]})
    return {'disc_sha256':EXPECTED,'patched_sha256':PATCHED_EXPECTED,
            'scope':'Complete healthy Terrain, shared valid SHP body with separately inspected changed prologue/cleanup, compressed BSurface/selector and selected raw/RLE body/shadow spans; strength prefix and complete reload/makepath; actual Terrain/converter dispatch. Null-shape difference is inspection only. Original file/heap/type/lifetime, alternate actors/flags and whole-frame parity remain excluded.',
            'ranges':records,'reviewed_wrapper_changes':changed,'data':data_records,'dispatch':dispatch,
            'original_bytes_modified':False,'original_instructions_executed':False}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--disc', required=True, type=Path)
    parser.add_argument('--patched', required=True, type=Path)
    parser.add_argument('--output', type=Path)
    args = parser.parse_args()
    report = verify(args.disc.read_bytes(), args.patched.read_bytes())
    report['tool_sha256'] = hashlib.sha256(Path(__file__).read_bytes()).hexdigest()
    report['profile_sha256'] = hashlib.sha256((Path(__file__).resolve().parents[1]/'tests/scenery_profiles.py').read_bytes()).hexdigest()
    if args.output:
        for source in (args.disc.resolve(), args.patched.resolve()):
            if args.output.resolve().is_relative_to(source.parent):
                raise ValueError('Report must be outside either source installation')
        write_report(args.patched, args.output, report)
    print(f"Verified {len(report['ranges'])} scenery ranges / "
          f"{sum(r['instructions'] for r in report['ranges'])} instructions, "
          'reviewed SHP changes, theater extensions and actual Terrain/span dispatch; no execution.')

if __name__ == '__main__':
    main()
