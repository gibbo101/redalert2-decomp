#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin complete supplied-base final Unit surface wrapper and selected children."""
import argparse,hashlib,struct
from pathlib import Path
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_terrain_visibility import PATCHED_EXPECTED,write_report
RANGES={0x6ff3e0:0x29f,0x6d8c30:0xa3,0x4f52b0:0x34,0x6d6df0:7,
        0x6d6e00:7,0x41b410:7,0x485aa0:0x2b7,0x4c8fa0:0x43,
        0x6cf3c0:0x2ae,0x53d4c0:5,0x705020:7,0x411290:36,
        0x434b40:1303,0x7753b0:424,0x775190:463,0x776340:52,
        0x411370:49,0x4112f0:10,0x4113b0:4,0x4113c0:14,
        0x488870:218,0x411230:52}
TAILS={0x6c12c0:8}
SLOTS={0x64:0x4c8fa0,0x80:0x6c12c0,0xc0:0x41b410,0x1bc:0x6d6df0,
       0x1c0:0x6d6e00,0x2c0:0x4c9930,0x2c4:0x4c9a10,0x3d0:0x6d8c30,0x4e0:0x6ff3e0}
def verify(data):
    if hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact supplied engine required')
    pe=pefile.PE(data=data)
    if pe.OPTIONAL_HEADER.ImageBase!=0x400000 or pe.FILE_HEADER.Machine!=0x14c:raise ValueError('PE layout differs')
    im=pe.get_memory_mapped_image();cs=Cs(CS_ARCH_X86,CS_MODE_32);ranges={}
    for start,size in {**RANGES,**TAILS}.items():
        b=im[start-0x400000:start-0x400000+size];ins=list(cs.disasm(b,start))
        if sum(i.size for i in ins)!=size or ins[-1].mnemonic!=('jmp' if start in TAILS else 'ret'):
            raise ValueError(f'Incomplete Unit surface range {start:#x}')
        ranges[hex(start)]={'bytes':size,'instructions':len(ins),'sha256':hashlib.sha256(b).hexdigest()}
    for table,slots in ((0x7addf8,SLOTS),(0x7a04cc,{0x34:0x53d4c0}),
                        (0x79aef8,{0x78:0x411290}),(0x79e20c,{4:0x488870})):
        for offset,target in slots.items():
            if struct.unpack_from('<I',im,table+offset-0x400000)[0]!=target:raise ValueError('Surface dispatch differs')
    if struct.unpack_from('<4I',im,0x6ff680-0x400000)!=(0x6ff46d,0x6ff474,0x6ff474,0x6ff47b):raise ValueError('Layer jump table differs')
    if struct.unpack_from('<I',im,0x7d3a74-0x400000)[0]!=0x3000:raise ValueError('Blitter mask differs')
    tables={hex(p):hashlib.sha256(im[p-0x400000:p-0x400000+n]).hexdigest()
            for p,n in ((0x6ff680,16),(0x7d3a74,8),(0x7ce168,72))}
    return {'ranges':ranges,'tables':tables,'unit_slots':{hex(k):hex(v) for k,v in SLOTS.items()},
            'scope':'Complete Unit final surface wrapper, type +0xBAE zero. Actual flag/disguise/owner/initialized house selector and BSurface bounds; selected healthy zero-state actual Foot/Drive/Techno layer. Ordinary nested final surface/clipping/alpha/depth-read RGB565 span executes on supplied planes/palette. Layer overrides, layer-four extra, depth/gradient and storage/construction remain services/fixtures. Nonordinary blitter pixels, split alternate, ownership, scheduling, runtime wiring and whole-frame parity are not proved.'}
if __name__=='__main__':
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--output',type=Path)
    a=p.parse_args();r=verify(a.exe.read_bytes())
    if a.output:
        if a.output.exists():raise ValueError('Inspection exists')
        write_report(a.exe,a.output,r)
    print(f'{len(r["ranges"])} complete Unit surface/helper ranges / {sum(v["instructions"] for v in r["ranges"].values())} instructions: PASS')
