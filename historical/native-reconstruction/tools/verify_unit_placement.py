#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin complete Techno Unlimbo/Facings and exact FireAngle field/default blocks."""
import argparse,hashlib,struct
from pathlib import Path
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_unit_model_inputs import verify as parent_verify
from verify_unit_metadata import PARENTS
from verify_terrain_visibility import write_report
COMPLETE={0x6c4610:0x2b5,0x4b8a30:0xdf,0x4b8b10:0xca,0x4b8be0:0x99,
          0x453eb0:0x1c,0x705020:7,0x70a2d0:6,0x4b89d0:0x1c,0x4b89f0:0x34}
TAILS={0x6c12c0:8}
BLOCKS={0x6d9d68:10,0x6dcfdf:0x1a}
SLOTS={0x2c:0x70a2d0,0x38:0x6c7420,0x80:0x6c12c0,0x84:0x705020,
       0x1a4:0x5d51e0,0x1d4:0x594c50,0x1e8:0x707a40,0x2a0:0x6d3e50,
       0x414:0x6fd630,0x418:0x6d5c30}
def verify(data):
    parent=parent_verify(data);im=pefile.PE(data=data).get_memory_mapped_image();cs=Cs(CS_ARCH_X86,CS_MODE_32)
    ranges={};instructions={};bounds=set()
    for start,size in {**PARENTS,**COMPLETE,**TAILS}.items():
        b=im[start-0x400000:start-0x400000+size];ins=list(cs.disasm(b,start))
        if sum(i.size for i in ins)!=size or ins[-1].mnemonic!=('jmp' if start in TAILS else 'ret'):raise ValueError('Incomplete placement/helper range '+hex(start))
        instructions.update((i.address,i) for i in ins);bounds.update(i.address for i in ins);bounds.add(start+size)
        if start in COMPLETE or start in TAILS:ranges[hex(start)]={'bytes':size,'instructions':len(ins),'sha256':hashlib.sha256(b).hexdigest()}
    if im[0x3f7834:].split(b'\0',1)[0]!=b'FireAngle':raise ValueError('FireAngle key differs')
    for a,op in ((0x6d9d68,'dword ptr [esi + 0x3a0], 8'),(0x6dcfdf,'ecx, dword ptr [ebp + 0x3a0]'),
                 (0x6dcfe6,'0x7f7834'),(0x6dcfee,'0x50d7f0'),(0x6dcff3,'dword ptr [ebp + 0x3a0], eax'),
                 (0x6c4743,'ch, byte ptr [eax + 0x3a0]')):
        if instructions[a].op_str!=op:raise ValueError('FireAngle association differs')
    blocks={}
    for start,size in BLOCKS.items():
        if start not in bounds or start+size not in bounds:raise ValueError('Unaligned FireAngle block')
        b=im[start-0x400000:start-0x400000+size];blocks[hex(start)]={'bytes':size,'sha256':hashlib.sha256(b).hexdigest()}
    for off,target in SLOTS.items():
        if struct.unpack_from('<I',im,0x7addf8+off-0x400000)[0]!=target:raise ValueError('Placement Unit dispatch differs')
    return {'parent_inspection':parent,'ranges':ranges,'blocks':blocks,
        'scope':'Complete Techno Unlimbo in Unit-kind-1 profile, actual Facing constructors/SetCurrent/SetDesired/current/timer and type/kind leaves. Stock case combines actual scoped FireAngle defaults/missing read and two Facing initializers with complete placement/pitch samples. Base Object placement result/post-state, map/house/cell/visibility effects are supplied services; present integer parsing is supplied. No full actor/type/map construction, outer Unit/Foot placement, pitch runtime integration or whole-frame parity.'}
if __name__=='__main__':
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--output',type=Path);a=p.parse_args();r=verify(a.exe.read_bytes())
    if a.output:
        if a.output.exists():raise ValueError('Inspection exists')
        write_report(a.exe,a.output,r)
    print(f'{len(r["ranges"])} complete placement/helper ranges / {len(r["blocks"])} FireAngle blocks: PASS')
