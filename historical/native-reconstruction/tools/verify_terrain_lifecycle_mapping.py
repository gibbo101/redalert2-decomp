#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Inspect exact-engine ordinary Terrain occupation/lifecycle and layer mappings.

Complete ranges, operands, actual RTTI/dispatch and foundation metadata are
inspection evidence. Executed parity is a separate bounded fixture claim.
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
from terrain_lifecycle_profiles import PATCHED_ADDRESSES
from inspect_patch import write_report

RANGES = {
    0x00405D50: 312,
    0x00405FE0: 131,
    0x0040CD40: 176,
    0x0040CDF0: 38,
    0x00410240: 3,
    0x0041B270: 45,
    0x0041B2D0: 5,
    0x0041B320: 61,
    0x00423E10: 5,
    0x00423E20: 3,
    0x0042AD30: 22,
    0x00469E80: 103,
    0x00473730: 489,
    0x00473920: 263,
    0x00491400: 172,
    0x004996D0: 77,
    0x00499720: 203,
    0x0049E820: 23,
    0x0049E840: 24,
    0x005329B0: 124,
    0x00532A90: 140,
    0x00545340: 104,
    0x005453B0: 56,
    0x00547EB0: 1012,
    0x005482B0: 871,
    0x005CB0F0: 5,
    0x005CB100: 55,
    0x005CB1C0: 1,
    0x005CB330: 117,
    0x005CBC20: 24,
    0x005CBC40: 389,
    0x005CBDD0: 824,
    0x005CC150: 155,
    0x005CC6A0: 206,
    0x005CC770: 14,
    0x005CC9B0: 117,
    0x005CCA30: 1,
    0x005CCD50: 79,
    0x005CD020: 38,
    0x005CD380: 33,
    0x005CD700: 29,
    0x005CD950: 34,
    0x005CD990: 54,
    0x00697EC0: 306,
    0x006D8950: 111,
    0x006D89C0: 147,
    0x006D8A60: 147,
    0x006D8E20: 217,
    0x006D9290: 314,
    0x006D9940: 294,
    0x006D9A70: 7,
    0x006D9C70: 6,
    0x006D9ED0: 1277,
    0x006DA740: 79,
    0x006DA858: 59,
    0x006DA9C0: 97,
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
    dispatch = []
    foundation_names = ('1x1', '2x1', '1x2', '2x2', '2x3', '3x2', '3x3', '3x5',
                        '4x2', '3x3Refinery', '1x3', '3x1', '4x3', '1x4', '1x5',
                        '2x6', '2x5', '5x3', '4x4', '3x4', '6x4', '0x0')
    metadata = []
    for pe in (disc, patched):
        selected = lambda a: a if pe is disc else PATCHED_ADDRESSES[a]
        profile = 'allied-disc' if pe is disc else 'supplied-ra2-1006'
        for table, name, slots in (
            (0x79827C, b'.?AVTerrainClass@@\0', (
                (0x2C,0x6D9C70),(0x3C,0x410240),(0x48,0x5CD380),(0x54,0x5CD950),
                (0x6C,0x5CB0F0),(0x74,0x5CB100),(0x84,0x6D9A70),(0xC8,0x41B2D0),
                (0xD0,0x6D9290),(0xD4,0x6D9940),(0xD8,0x5CC150),(0xE8,0x6D8A60),
                (0xEC,0x6D89C0),(0x100,0x5CC9B0),(0x114,0x5CB1C0),(0x11C,0x6D8950),
                (0x12C,0x5CBC20),(0x144,0x5CB330),(0x180,0x5CC770),(0x194,0x6D8E20),
                (0x198,0x423E10),(0x19C,0x5CD700),(0x1A0,0x41B320),
                (0x1B0,0x5CCD50),(0x1B8,0x5CCD40),(0x1BC,0x423E20))),
            (0x798490, b'.?AVTerrainTypeClass@@\0', ((0x6C,0x6DA9C0),(0x90,0x6DA740))),
            (0x789870, b'.?AVLayerClass@@\0', ((8,0x40CD40),(0x10,0x40CDF0)))):
            t = selected(table)
            locator = struct.unpack('<I', read(pe,t-4,4))[0]
            values = struct.unpack('<5I',read(pe,locator,20))
            actual_name = read(pe,values[3]+8,180).split(b'\0')[0]+b'\0'
            if values[1] != 0 or actual_name != name:
                raise ValueError('Actual lifecycle RTTI differs: '+repr(actual_name))
            for offset, target in slots:
                actual = struct.unpack('<I',read(pe,t+offset,4))[0]
                if actual != selected(target):raise ValueError('Actual lifecycle dispatch differs')
                dispatch.append({'profile':profile,'table':hex(t),'offset':hex(offset),'target':hex(actual)})
        for index, name in enumerate(foundation_names):
            ptr, value = struct.unpack('<2I',read(pe,selected(0x7BC950)+index*8,8))
            text = read(pe,ptr,40).split(b'\0')[0].decode('ascii')
            if value != index or text != name:raise ValueError('Foundation enum differs')
            if pe is patched:
                old_ptr = struct.unpack('<I',read(disc,0x7BC950+index*8,4))[0]
                if PATCHED_ADDRESSES[old_ptr] != ptr:raise ValueError('Foundation string mapping differs')
            metadata.append({'profile':profile,'index':index,'name':name,'pointer':hex(ptr)})
        if read(pe,selected(0x7BBB14),11)!=b'Foundation\0':raise ValueError('Foundation key differs')
        # Verify the real foundation loader/call/store and not a misaligned probe.
        loader = list(decoder.disasm(read(pe,selected(0x6DA858),59),selected(0x6DA858)))
        call = next(i for i in loader if i.address == selected(0x6DA858)+24)
        if call.mnemonic != 'call' or call.operands[0].imm != selected(0x469E80):
            raise ValueError('Actual Foundation INI helper caller differs')
        adjust = list(decoder.disasm(read(pe,selected(0x6DA9C0),97),selected(0x6DA9C0)))
        returns = [i.address+i.size for i in adjust if i.mnemonic == 'call']
        if returns != [selected(0x6DA9EA),selected(0x6DAA01)]:
            raise ValueError('Type ground-service return addresses differ')
        insert = list(decoder.disasm(read(pe,selected(0x5329B0),124),selected(0x5329B0)))
        if not any(i.address==selected(0x5329B0)+16 and i.mnemonic=='call'
                   and i.operands[0].imm==selected(0x532A90) for i in insert):
            raise ValueError('Actual sorted insertion caller differs')
    return {'disc_sha256':EXPECTED,'patched_sha256':PATCHED_EXPECTED,
            'ranges':records,'dispatch':dispatch,'foundation_metadata':metadata,
            'scope':'Ordinary Terrain occupation/Mark, ground Unlimbo/Limbo and layer operations; complete selected ranges/operands, actual Terrain/type/Layer slots and foundation association. Supplied services, skipped resources/status branches and full actor/frame behavior are outside executed parity.',
            'original_bytes_modified':False,'original_instructions_executed':False}


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--disc',required=True,type=Path)
    parser.add_argument('--patched',required=True,type=Path)
    parser.add_argument('--output',type=Path)
    args=parser.parse_args()
    report=verify(args.disc.read_bytes(),args.patched.read_bytes())
    report['tool_sha256']=hashlib.sha256(Path(__file__).read_bytes()).hexdigest()
    report['profile_sha256']=hashlib.sha256((Path(__file__).resolve().parents[1]/'tests/terrain_lifecycle_profiles.py').read_bytes()).hexdigest()
    if args.output:
        for source in (args.disc.resolve(),args.patched.resolve()):
            if args.output.resolve().is_relative_to(source.parent):raise ValueError('Report must be outside source installations')
        write_report(args.patched,args.output,report)
    print(f"Verified {len(report['ranges'])} terrain/lifecycle ranges / "
          f"{sum(r['instructions'] for r in report['ranges'])} instructions, actual dispatch and foundation association; no execution.")

if __name__=='__main__':main()
