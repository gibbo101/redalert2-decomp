#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin base GetBool, its locale-zero helpers and selected type INI associations."""
import argparse,hashlib,struct
from pathlib import Path
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_terrain_visibility import PATCHED_EXPECTED,write_report
COMPLETE={0x50f410:0x180,0x493fc0:0x1c9,0x494190:0x37,
          0x510dd0:0x97,0x7829d3:0x6f}
PARENTS={0x70ab40:0x7dd,0x6daf60:0x3173,0x5d7810:0x3bf,
         0x70a600:0x1d4,0x6d9b40:0xb91,0x5d57f0:0x287}
# Each row: field offset, key string, read/call blocks, separate store, ctor store.
FIELDS=(
    (0xba6,'Harvester',((0x70abb6,0x14),),(0x70abd0,6),0x70a63f),
    (0x206,'Voxel',((0x5d7b50,0x17),),(0x5d7b6b,6),0x5d58fa),
    (0xaab,'Turret',((0x6dc024,6),(0x6dc030,0xe)),(0x6dc05b,6),0x6da31f),
    (0xaf2,'HunterSeeker',((0x6dd0ea,0x14),),(0x6dd0fe,6),0x6da3e8),
    (0xb1a,'BalloonHover',((0x6dd186,0x14),),(0x6dd1ae,6),0x6da472))
KEY_POINTERS=(0x7f1a28,0x7e8114,0x7f7d28,0x7f77ac,0x7f7774)
def verify(data):
    if hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact supplied engine required')
    pe=pefile.PE(data=data)
    if pe.OPTIONAL_HEADER.ImageBase!=0x400000 or pe.FILE_HEADER.Machine!=0x14c:raise ValueError('PE layout differs')
    im=pe.get_memory_mapped_image();cs=Cs(CS_ARCH_X86,CS_MODE_32);cs.detail=True
    ranges={};boundaries=set();instructions={}
    for start,size in {**COMPLETE,**PARENTS}.items():
        blob=im[start-0x400000:start-0x400000+size];ins=list(cs.disasm(blob,start))
        if sum(i.size for i in ins)!=size or ins[-1].mnemonic!='ret':raise ValueError('Incomplete metadata range '+hex(start))
        boundaries.update(i.address for i in ins);boundaries.add(start+size)
        instructions.update((i.address,i) for i in ins)
        ranges[hex(start)]={'bytes':size,'instructions':len(ins),'sha256':hashlib.sha256(blob).hexdigest(),
                            'complete_callable_test':start in COMPLETE}
    fields={}
    for (offset,key,reads,store,ctor),pointer in zip(FIELDS,KEY_POINTERS):
        raw=im[pointer-0x400000:].split(b'\0',1)[0]
        if raw!=key.encode('ascii'):raise ValueError('Type INI string differs')
        selected={}
        for start,size in (*reads,store,(ctor,6)):
            if start not in boundaries or start+size not in boundaries:raise ValueError('Unaligned metadata block')
            blob=im[start-0x400000:start-0x400000+size]
            selected[hex(start)]={'bytes':size,'sha256':hashlib.sha256(blob).hexdigest()}
        read_ins=[i for start,size in reads for i in cs.disasm(im[start-0x400000:start-0x400000+size],start)]
        if not any(i.mnemonic=='push' and i.op_str==hex(pointer) for i in read_ins):raise ValueError('INI key push differs')
        if not any(i.mnemonic=='call' and i.op_str=='0x50f410' for i in read_ins):raise ValueError('INI boolean target differs')
        for start in (reads[0][0],store[0],ctor):
            i=instructions[start]
            memory=[o for o in i.operands if o.type==3]
            if i.mnemonic!='mov' or len(memory)!=1 or memory[0].mem.disp!=offset or memory[0].size!=1:
                raise ValueError('Type byte association differs')
        fields[key]={'offset':hex(offset),'key_pointer':hex(pointer),'blocks':selected}
    for table,size in ((0x50f590,12),(0x50f59c,42),(0x7d5504,1024)):
        blob=im[table-0x400000:table-0x400000+size]
        ranges[hex(table)]={'bytes':size,'sha256':hashlib.sha256(blob).hexdigest(),'data':True}
    for vtable,target in ((0x7ae328,0x70ab40),(0x7ad080,0x6daf60),(0x7a76f8,0x5d7810)):
        if struct.unpack_from('<I',im,vtable+0x64-0x400000)[0]!=target:raise ValueError('Type ReadINI slot differs')
    return {'ranges':ranges,'fields':fields,
            'scope':'Complete GetBool/CRC/key/uppercase inspected; executed decoded indexes use hot entries and locale zero. Parent INI loaders/ctors inspected aligned; selected read/call/store/default blocks execute with supplied live registers. No full INI text parsing, cold search/sort, type construction, model loading or full actor proof.'}
if __name__=='__main__':
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--output',type=Path)
    a=p.parse_args();r=verify(a.exe.read_bytes())
    if a.output:
        if a.output.exists():raise ValueError('Inspection already exists')
        write_report(a.exe,a.output,r)
    print(f'{len(COMPLETE)} complete helpers / {len(PARENTS)} aligned parents / {len(FIELDS)} type fields: PASS')
