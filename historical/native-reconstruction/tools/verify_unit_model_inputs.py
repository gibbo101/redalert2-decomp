#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin model Image/count/offset associations and complete decoded-entry ReadString."""
import argparse,hashlib
from pathlib import Path
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from capstone.x86_const import X86_REG_EBX,X86_REG_BX,X86_REG_BL,X86_REG_BH
from verify_unit_metadata import verify as parent_verify,PARENTS
from verify_terrain_visibility import write_report
COMPLETE={0x50e9a0:0x194,0x6eef10:0x67,0x7823d0:0xfe,0x50d7f0:0x1d3}
BLOCKS={0x5d782d:6,0x5d7834:0x40,0x6db614:0x1a,0x6dd9b5:0x1d,
        0x5d5801:2,0x5d5888:6,0x5d5970:3,0x5d59af:0x28,
        0x6d9b55:2,0x6da16c:6,0x6da298:6}
def verify(data):
    parent=parent_verify(data);im=pefile.PE(data=data).get_memory_mapped_image();cs=Cs(CS_ARCH_X86,CS_MODE_32);cs.detail=True
    ranges={};ins={};boundaries=set()
    for start,size in {**PARENTS,**COMPLETE}.items():
        b=im[start-0x400000:start-0x400000+size];decoded=list(cs.disasm(b,start))
        if sum(i.size for i in decoded)!=size or decoded[-1].mnemonic!='ret':raise ValueError('Incomplete model input range '+hex(start))
        ins.update((i.address,i) for i in decoded);boundaries.update(i.address for i in decoded);boundaries.add(start+size)
        if start in COMPLETE:ranges[hex(start)]={'bytes':size,'instructions':len(decoded),'sha256':hashlib.sha256(b).hexdigest()}
    for p,key in ((0x7cfddc,'Image'),(0x7f7f08,'TurretCount'),(0x7f738c,'TurretOffset')):
        if im[p-0x400000:].split(b'\0',1)[0]!=key.encode():raise ValueError('Model input key differs')
    for a,operand in ((0x5d782d,'edx, [ebx + 0x1c8]'),(0x5d7855,'ebp, [ebx + 0x24]'),
                      (0x6db614,'edx, dword ptr [ebp + 0x704]'),(0x6db628,'dword ptr [ebp + 0x704], eax'),
                      (0x6dd9b5,'eax, dword ptr [ebp + 0x63c]'),(0x6dd9cc,'dword ptr [ebp + 0x63c], eax')):
        if ins[a].op_str!=operand:raise ValueError('Model input association differs')
    for a in (0x5d786f,0x6db623,0x6dd9c7):
        if ins[a].op_str!=('0x50e9a0' if a==0x5d786f else '0x50d7f0'):raise ValueError('Model getter target differs')
    for start,end in ((0x6d9b57,0x6da29e),(0x5d5803,0x5d59d7)):
        if any(start<=a<end and {X86_REG_EBX,X86_REG_BX,X86_REG_BL,X86_REG_BH}.intersection(i.regs_access()[1]) for a,i in ins.items()):
            raise ValueError('Constructor EBX assignment differs')
    blocks={}
    for start,size in BLOCKS.items():
        if start not in boundaries or start+size not in boundaries:raise ValueError('Unaligned model input block')
        b=im[start-0x400000:start-0x400000+size]
        blocks[hex(start)]={'bytes':size,'instructions':len(list(cs.disasm(b,start))),'sha256':hashlib.sha256(b).hexdigest()}
    return {'parent_inspection':parent,'ranges':ranges,'blocks':blocks,
        'scope':'Complete ReadString/byte trim/CRT strncpy on immutable decoded hot indexes and supplied fallback/output. Actual GetInt executes missing-entry fallback branches; present integer decoding is a read-only supplied service. Scoped Image copy/read and TurretCount/TurretOffset read/store/default blocks, with supplied live registers, not full type constructors or original INI text parsing. Constructor EBX preservation across omitted children is an ABI boundary. Native reader and stock decoded INI inputs do not prove archive/text/index construction or runtime integration.'}
if __name__=='__main__':
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--output',type=Path);a=p.parse_args();r=verify(a.exe.read_bytes())
    if a.output:
        if a.output.exists():raise ValueError('Inspection exists')
        write_report(a.exe,a.output,r)
    print(f'{len(r["ranges"])} complete routines / {len(r["blocks"])} aligned model input blocks: PASS')
