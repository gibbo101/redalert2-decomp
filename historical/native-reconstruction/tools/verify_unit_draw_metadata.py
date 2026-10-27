#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin selected base depth/split field associations and scoped default setup."""
import argparse,hashlib
from pathlib import Path
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from capstone.x86_const import X86_REG_ECX,X86_REG_EBX,X86_REG_BL,X86_REG_BX,X86_REG_CL,X86_REG_CX,X86_REG_CH,X86_REG_BH
from verify_unit_metadata import verify as verify_parent
from verify_terrain_visibility import write_report
FIELDS=((0xb5c,'ZFudgeCliff',0x7f74f8,0x6dd5ed,0x6dd601),
        (0xb60,'ZFudgeColumn',0x7f74e8,0x6dd607,0x6dd61b),
        (0xb64,'ZFudgeTunnel',0x7f74d8,0x6dd621,0x6dd635),
        (0xb68,'ZFudgeBridge',0x7f74c8,0x6dd63b,0x6dd655),
        (0xbae,'TooBigToFitUnderBridge',0x7f938c,0x70ac5e,0x70ac8f))
BLOCKS={0x6dd5ed:0x6e,0x70ac5e:0x1d,0x70ac8f:6,
        0x6d9b55:2,0x6da211:5,0x6da522:0x1c,0x70a619:2,0x70a673:6}
def verify(data):
    parent=verify_parent(data);im=pefile.PE(data=data).get_memory_mapped_image()
    cs=Cs(CS_ARCH_X86,CS_MODE_32);cs.detail=True;instructions={};bounds=set()
    from verify_unit_metadata import PARENTS
    for start,size in PARENTS.items():
        ins=list(cs.disasm(im[start-0x400000:start-0x400000+size],start))
        instructions.update((i.address,i) for i in ins);bounds.update(i.address for i in ins);bounds.add(start+size)
    fields={}
    for off,key,pointer,read,store in FIELDS:
        if im[pointer-0x400000:].split(b'\0',1)[0]!=key.encode():raise ValueError('Draw metadata key differs')
        for address in (read,store):
            i=instructions[address];mem=[o for o in i.operands if o.type==3]
            if i.mnemonic!='mov' or len(mem)!=1 or mem[0].mem.disp!=off or mem[0].size!=(1 if off==0xbae else 4):raise ValueError('Draw metadata field differs')
        selected=[i for a,i in instructions.items() if read<=a<(0x70ac7b if off==0xbae else store)]
        if not any(i.mnemonic=='push' and i.op_str==hex(pointer) for i in selected):raise ValueError('Draw metadata key push differs')
        if not any(i.mnemonic=='call' and i.op_str==('0x50f410' if off==0xbae else '0x50d7f0') for i in selected):raise ValueError('Draw metadata getter differs')
        fields[key]={'offset':hex(off),'key_pointer':hex(pointer),'read':hex(read),'store':hex(store)}
    blocks={}
    for start,size in BLOCKS.items():
        if start not in bounds or start+size not in bounds:raise ValueError('Unaligned draw metadata block')
        b=im[start-0x400000:start-0x400000+size]
        blocks[hex(start)]={'bytes':size,'instructions':len(list(cs.disasm(b,start))),'sha256':hashlib.sha256(b).hexdigest()}
    # ECX is 10 through the actual straight-line depth defaults. EBX was zeroed
    # before constructor service calls; its preservation there is an ABI boundary.
    if instructions[0x6da211].op_str!='ecx, 0xa' or instructions[0x6d9b55].op_str!='ebx, ebx' or instructions[0x70a619].op_str!='ebx, ebx':raise ValueError('Default register setup differs')
    for start,end,regs in ((0x6da216,0x6da53e,{X86_REG_ECX,X86_REG_CX,X86_REG_CL,X86_REG_CH}),
                           (0x70a61b,0x70a679,{X86_REG_EBX,X86_REG_BX,X86_REG_BL,X86_REG_BH})):
        for a,i in instructions.items():
            if start<=a<end and (i.mnemonic.startswith(('j','ret','call')) or regs.intersection(i.regs_access()[1])):raise ValueError('Default straight-line dataflow differs')
    for a,i in instructions.items():
        if 0x6d9b57<=a<0x6da53e and {X86_REG_EBX,X86_REG_BX,X86_REG_BL,X86_REG_BH}.intersection(i.regs_access()[1]):raise ValueError('Default EBX assignment differs')
    return {'parent_inspection':parent,'fields':fields,'blocks':blocks,
            'scope':'Selected original ZFudge integer read/call/store blocks with read-only GetInt service; actual GetBool for TooBigToFitUnderBridge including one unrelated +0xBA9 byte store on supplied ZF. Scoped register setup/default stores, not whole constructors; EBX preservation across omitted constructor calls is an ABI boundary. Decoded INI indexes and owned text are supplied; original integer/text parsing, full type construction, model association, split drawing and runtime wiring remain open.'}
if __name__=='__main__':
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--output',type=Path);a=p.parse_args();r=verify(a.exe.read_bytes())
    if a.output:
        if a.output.exists():raise ValueError('Inspection already exists')
        write_report(a.exe,a.output,r)
    print(f'{len(r["fields"])} base draw fields / {len(r["blocks"])} aligned scoped blocks: PASS')
