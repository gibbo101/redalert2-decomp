#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin supplied-patch redraw requests and complete dirty-region registration."""
import argparse
import hashlib
from pathlib import Path
import struct
import sys
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'tests'))
from compare_original import PATCHED_EXPECTED,write_report
RANGES={0x5d36e0:0x18,0x4e09a0:0x2e,0x55acc0:7,0x6a3020:0x3b2,
        0x45efe0:0xf0,0x41fdf0:0x121,0x6a22f0:0x3d,0x6e2fe0:0x17}
def verify(data):
    if hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact supplied 1.006 executable required')
    p=pefile.PE(data=data)
    if p.OPTIONAL_HEADER.ImageBase!=0x400000 or p.FILE_HEADER.Machine!=0x14c:raise ValueError('Unsupported PE layout')
    im=p.get_memory_mapped_image();cs=Cs(CS_ARCH_X86,CS_MODE_32);records={}
    for a,n in RANGES.items():
        b=im[a-0x400000:a-0x400000+n];ins=list(cs.disasm(b,a))
        if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Incomplete redraw inspection range')
        records[hex(a)]={'bytes':n,'instructions':len(ins),'sha256':hashlib.sha256(b).hexdigest()}
    u=lambda a:struct.unpack_from('<I',im,a-0x400000)[0]
    if any(u(vt+0x12c)!=0x5d36e0 for vt in [0x7addf8,0x7ad3cc]):raise ValueError('Actual actor redraw slots differ')
    if u(0x7ac4c4+8)!=0x6acbe0:raise ValueError('Actual region vector growth slot differs')
    return {'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','ranges':records,
            'object_redraw_slot':'0x12c','growth_slot':{'vtable':'0x7ac4c4','offset':8,'target':'0x6acbe0'},
            'scope':'Complete requests/counter, dirty-region registration, union/intersection and queue/empty initializers. Actual requests and rectangle helpers execute; vector allocation and atexit are services. No caller/frame scheduling or runtime integration.'}
if __name__=='__main__':
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--output',type=Path)
    a=p.parse_args();r=verify(a.exe.read_bytes())
    if a.output:
        if a.output.exists():raise ValueError('Inspection output already exists')
        write_report(a.exe,a.output,r)
    print(f'{len(r["ranges"])} complete redraw ranges / {sum(v["instructions"] for v in r["ranges"].values())} instructions: PASS')
