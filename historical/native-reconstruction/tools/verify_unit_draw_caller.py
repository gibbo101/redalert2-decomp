#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Inspect exact supplied-1.006 Unit DrawIt caller and screen registration."""
import argparse,hashlib,struct
from pathlib import Path
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_terrain_visibility import PATCHED_EXPECTED,write_report
RANGES={0x700e70:0x52e,0x6aa510:0x8b,0x5d4810:0x4f,
        0x548000:0x68,0x548070:0x38,0x41b320:0x3d,
        0x6ff350:0x8c,0x5d34e0:0x1f6,0x41fdf0:0x121,0x41b270:45,0x6e2fe0:0x17,0x70a2d0:6}
SLOTS={0x2c:0x70a2d0,0xa8:0x41b270,0xfc:0x6ff350,0x10c:0x700e70,0x1a0:0x41b320,0x1b0:0x5d4810,
       0x64:0x4c8fa0,0x54:0x4cce70,0x3d4:0x6d8ce0,0xc8:0x709bb0,
       0x4d8:0x6ff690,0x4dc:0x7005b0}
def verify(data):
    if hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact supplied 1.006 engine required')
    pe=pefile.PE(data=data)
    if pe.OPTIONAL_HEADER.ImageBase!=0x400000 or pe.FILE_HEADER.Machine!=0x14c:raise ValueError('PE layout differs')
    im=pe.get_memory_mapped_image();cs=Cs(CS_ARCH_X86,CS_MODE_32);ranges={}
    for start,size in RANGES.items():
        b=im[start-0x400000:start-0x400000+size];ins=list(cs.disasm(b,start))
        if sum(i.size for i in ins)!=size or ins[-1].mnemonic!='ret':raise ValueError('Incomplete caller inspection')
        ranges[hex(start)]={'bytes':size,'instructions':len(ins),'sha256':hashlib.sha256(b).hexdigest()}
    for slot,target in SLOTS.items():
        if struct.unpack_from('<I',im,0x7addf8+slot-0x400000)[0]!=target:raise ValueError('Unit dispatch differs')
    return {'executable_sha256':PATCHED_EXPECTED,'ranges':ranges,'slots':{hex(k):hex(v) for k,v in SLOTS.items()},
            'scope':'Complete inspected Unit caller, registry, height and map getters. Executed ordinary caller only; layer/ground/predicates/alternate selection/final draws/Foot decoration supplied. No full rendering, lifecycle or frame parity.'}
if __name__=='__main__':
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--output',type=Path)
    a=p.parse_args();r=verify(a.exe.read_bytes())
    if a.output:
        if a.output.exists():raise ValueError('Inspection output already exists')
        write_report(a.exe,a.output,r)
    print(f'{len(r["ranges"])} complete Unit caller ranges / {sum(v["instructions"] for v in r["ranges"].values())} instructions: PASS')
