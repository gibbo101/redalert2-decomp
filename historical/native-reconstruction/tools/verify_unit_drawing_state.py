#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin complete Facing initializers, Unit status/flag leaves and scoped defaults."""
import argparse,hashlib,struct
from pathlib import Path
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from capstone.x86_const import X86_REG_EBX,X86_REG_BX,X86_REG_BL,X86_REG_BH
from verify_unit_type_visibility import verify as parent_verify,CONSTRUCTORS
from verify_terrain_visibility import write_report
COMPLETE={0x4b89d0:0x1c,0x4b89f0:0x34,0x41b390:0x35,0x6d6df0:7,0x6d6e00:7}
# Only these aligned parent blocks execute, with ESI supplied by the fixture.
BLOCKS={0x6c0cdb:2,0x6c0da5:0x12,0x6c0e3e:6,0x6c0ec8:12,
        0x6c0f98:0x23,0x4c293f:2,0x4c2973:6,0x6fa41d:2,0x6fa44a:6}
def verify(data):
    parent=parent_verify(data);im=pefile.PE(data=data).get_memory_mapped_image()
    cs=Cs(CS_ARCH_X86,CS_MODE_32);cs.detail=True;ranges={};ins={};boundaries=set()
    for start,size in {**CONSTRUCTORS,**COMPLETE}.items():
        b=im[start-0x400000:start-0x400000+size];decoded=list(cs.disasm(b,start))
        if sum(i.size for i in decoded)!=size or decoded[-1].mnemonic!='ret':raise ValueError('Incomplete Unit drawing-state range')
        ins.update((i.address,i) for i in decoded);boundaries.update(i.address for i in decoded);boundaries.add(start+size)
        if start in COMPLETE:ranges[hex(start)]={'bytes':size,'instructions':len(decoded),'sha256':hashlib.sha256(b).hexdigest()}
    # No explicit EBX reassignment lies between the selected zero setup and stores.
    for start,end in ((0x6c0cdd,0x6c0fbb),(0x4c2941,0x4c2979),(0x6fa41f,0x6fa450)):
        relevant=[i for a,i in ins.items() if start<=a<end]
        if any({X86_REG_EBX,X86_REG_BX,X86_REG_BL,X86_REG_BH}.intersection(i.regs_access()[1]) for i in relevant):
            raise ValueError('Constructor EBX assignment differs')
    blocks={}
    for start,size in BLOCKS.items():
        if start not in boundaries or start+size not in boundaries:raise ValueError('Unaligned Unit drawing-state block')
        b=im[start-0x400000:start-0x400000+size]
        blocks[hex(start)]={'bytes':size,'instructions':len(list(cs.disasm(b,start))),'sha256':hashlib.sha256(b).hexdigest()}
    for offset,target in ((0x32c,0x41b390),(0x1bc,0x6d6df0),(0x1c0,0x6d6e00)):
        if struct.unpack_from('<I',im,0x7addf8+offset-0x400000)[0]!=target:raise ValueError('Unit status/flag dispatch differs')
    return {'parent_inspection':parent,'ranges':ranges,'blocks':blocks,
        'scope':'Complete Facing constructors, signed-positive Unit status timer and flag byte leaves. Nine scoped parent constructor blocks execute, including actual three Facing constructors, with supplied ESI and current-frame global. Full construction/ownership, post-load state, neutral barrel-pitch establishment, drawing children/runtime and frame parity remain open. EBX preservation across omitted children is an ABI boundary.'}
if __name__=='__main__':
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--output',type=Path);a=p.parse_args();r=verify(a.exe.read_bytes())
    if a.output:
        if a.output.exists():raise ValueError('Inspection exists')
        write_report(a.exe,a.output,r)
    print(f'{len(r["ranges"])} complete routines / {len(r["blocks"])} aligned Unit drawing-state blocks: PASS')
