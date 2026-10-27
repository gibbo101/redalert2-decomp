#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Inspect exact patched type selection, house helpers and scoped drawing fields."""
import argparse,hashlib,struct
from pathlib import Path
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_unit_draw_caller import verify as verify_caller
from verify_terrain_visibility import write_report
COMPLETE={0x6d8ce0:0xc3,0x4f52b0:0x34,0x4e5540:0x3f,0x47c300:0x14,
          0x709bb0:0x34,0x41b410:7,0x5d51e0:0x57}
CONSTRUCTORS={0x5d22e0:0x211,0x6c0cd0:0x5ef,0x4c2930:0x330,0x6fa400:0x3b4}
BLOCKS={0x5d232b:3,0x6c0dc9:12,0x6c0de6:22,0x6c0fc1:18,
        0x6c10b2:6,0x6c11a1:6,0x4c2b62:6,0x6fa432:6}
def verify(data):
    inherited=verify_caller(data);im=pefile.PE(data=data).get_memory_mapped_image();cs=Cs(CS_ARCH_X86,CS_MODE_32)
    ranges={};boundaries=set()
    for start,size in {**COMPLETE,**CONSTRUCTORS}.items():
        b=im[start-0x400000:start-0x400000+size];ins=list(cs.disasm(b,start))
        if sum(i.size for i in ins)!=size or ins[-1].mnemonic!='ret':raise ValueError('Incomplete type/constructor inspection')
        boundaries.update(i.address for i in ins);boundaries.add(start+size)
        ranges[hex(start)]={'bytes':size,'instructions':len(ins),'sha256':hashlib.sha256(b).hexdigest(),
                            'executed_complete':start in COMPLETE}
    blocks={}
    for start,size in BLOCKS.items():
        if start not in boundaries or start+size not in boundaries:raise ValueError('Unaligned constructor block')
        b=im[start-0x400000:start-0x400000+size]
        blocks[hex(start)]={'bytes':size,'sha256':hashlib.sha256(b).hexdigest()}
    for slot,target in {0xc0:0x41b410,0x1a4:0x5d51e0}.items():
        if struct.unpack_from('<I',im,0x7addf8+slot-0x400000)[0]!=target:raise ValueError('Type visibility slot differs')
    return {'inherited_caller':inherited,'ranges':ranges,'constructor_blocks':blocks,
            'scope':'Complete original type/house/alternate/cell functions and nested caller. Constructors inspected aligned; only eight field blocks execute with supplied registers, not full construction. Synthetic house/map storage. Timer/final draw/Foot decoration remain services; no fog, stock post-construction, runtime integration or frame parity.'}
if __name__=='__main__':
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--output',type=Path)
    a=p.parse_args();r=verify(a.exe.read_bytes())
    if a.output:
        if a.output.exists():raise ValueError('Inspection output exists')
        write_report(a.exe,a.output,r)
    print(f'{len(COMPLETE)} complete type/house routines; {len(CONSTRUCTORS)} inspected constructors / {len(BLOCKS)} executed scoped blocks: PASS')
