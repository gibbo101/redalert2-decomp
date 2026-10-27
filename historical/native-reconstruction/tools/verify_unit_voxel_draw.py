#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin complete supplied-base Unit voxel root and selected nested healthy helpers."""
import argparse,hashlib,struct
from pathlib import Path
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_terrain_visibility import PATCHED_EXPECTED,write_report
RANGES={0x6ff690:0xf15,0x4a0050:1189,0x4a0500:0xb2,0x53d030:0x9f,
        0x53d0d0:0xf0,0x53d1c0:0x28,0x53d4e0:5,0x705020:7,
        0x6df680:14,0x717f90:21,0x718d60:28,0x58fe10:22,0x591180:508,
        0x5900f0:0x81,0x590180:0x29,0x590060:43,0x590880:156,0x5909a0:156,
        0x4b8be0:153,0x4ba480:66,0x4ba4d0:73,0x70a350:0x97,0x70a3f0:0x1b,
        0x4c9880:0xa4,0x4c9a40:205,0x53d4d0:16,0x77f110:0x3d,0x6a2970:0x3c}
TAILS={0x6d83e0:15,0x6c12c0:8}
UNIT_SLOTS={0x80:0x6c12c0,0x84:0x705020,0x3d4:0x6d8ce0,0xc8:0x709bb0,
            0x3d8:0x4c9880,0x3f8:0x6d79d0,0x32c:0x41b390,0x4e0:0x6ff3e0,
            0x1b0:0x5d4810,0x54:0x4cce70}
DRIVE_SLOTS={0x20:0x53d4e0,0x24:0x4a0050,0x28:0x4a0500,0x2c:0x53d4d0,0x30:0x53d1c0}
def verify(data):
    if hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact supplied engine required')
    pe=pefile.PE(data=data)
    if pe.OPTIONAL_HEADER.ImageBase!=0x400000 or pe.FILE_HEADER.Machine!=0x14c:raise ValueError('PE layout differs')
    im=pe.get_memory_mapped_image();cs=Cs(CS_ARCH_X86,CS_MODE_32);ranges={}
    for start,size in {**RANGES,**TAILS}.items():
        blob=im[start-0x400000:start-0x400000+size];ins=list(cs.disasm(blob,start))
        if sum(i.size for i in ins)!=size or ins[-1].mnemonic!=('jmp' if start in TAILS else 'ret'):
            raise ValueError(f'Incomplete Unit voxel range {start:#x}')
        ranges[hex(start)]={'bytes':size,'instructions':len(ins),'sha256':hashlib.sha256(blob).hexdigest()}
    for table,slots in ((0x7addf8,UNIT_SLOTS),(0x7a04cc,DRIVE_SLOTS)):
        for offset,target in slots.items():
            if struct.unpack_from('<I',im,table+offset-0x400000)[0]!=target:raise ValueError('Unit/Drive dispatch differs')
    instructions={i.address:i for start,size in RANGES.items()
                  for i in cs.disasm(im[start-0x400000:start-0x400000+size],start)}
    for address,operand in ((0x6ffd21,'ecx, [ebp + 0x2c8]'),(0x6ffd27,'0x4b8be0'),
                            (0x6ffd3f,'edx, 8'),(0x6ffd4a,'qword ptr [0x79d090]'),
                            (0x6ffd50,''),(0x6ffd52,'dword ptr [esp]'),(0x6ffd55,'0x590880')):
        if instructions[address].op_str!=operand:raise ValueError('Barrel pitch association differs')
    tables={hex(p):hashlib.sha256(im[p-0x400000:p-0x400000+n]).hexdigest()
            for p,n in ((0x801dc4,40960),(0x7d8048,8),(0x79d090,8),(0x7d8964,4))}
    return {'ranges':ranges,'tables':tables,'unit_slots':{hex(k):hex(v) for k,v in UNIT_SLOTS.items()},
            'drive_slots':{hex(k):hex(v) for k,v in DRIVE_SLOTS.items()},
            'scope':'Complete Unit voxel root, executed healthy flat Track/single turret/zero offset/supplied barrel facing/original-visible/height zero/no status/add14/bridge/clip-height path. Actual Drive poses, Facing, nonneutral barrel rotation, matrix, independent hot/empty part prechecks and Foot wrappers execute. Visibility, map cell, height, brightness/status, surface and final Techno draws remain supplied. Steady barrel facing, camera, ramp-zero identity and initialized dirty template are fixture inputs. No original raster pixels, pitch-driven invalidation, pool, startup/ownership, alternate/multiple turrets or whole-frame parity.'}
if __name__=='__main__':
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--output',type=Path)
    a=p.parse_args();result=verify(a.exe.read_bytes())
    if a.output:
        if a.output.exists():raise ValueError('Inspection exists')
        write_report(a.exe,a.output,result)
    print(f'{len(result["ranges"])} complete Unit voxel/helper ranges / {sum(r["instructions"] for r in result["ranges"].values())} instructions: PASS')
