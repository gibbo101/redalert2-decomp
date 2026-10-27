#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Inspect supplied-1.006 Terrain eligibility, crop bounds and actual dispatch.

Only the exact supplied patched engine is accepted; there is no disc relocation.
Full byte ranges stay private. This metadata check is not executed parity.
"""
import argparse
import hashlib
import struct
from pathlib import Path
import sys
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'tests'))
from compare_original import PATCHED_EXPECTED, write_report
RANGES={0x41fdf0:0x121,0x6e4430:0x140,0x6e4910:0x1db,0x6e2fe0:0x17,
        0x5d27b0:0x12,0x6e4900:7,0x41c300:7,0x41b270:45,0x5d4e40:33}
SLOTS={0x7ad3cc:{0x48:0x5d4e40,0x84:0x6e4900,0xa8:0x41b270,0xfc:0x6e4430,
                  0x10c:0x6e3990,0x124:0x6e4910},0x7ad5e0:{0x9c:0x41c300}}
def verify(data):
    if hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact supplied 1.006 executable required')
    pe=pefile.PE(data=data)
    if pe.OPTIONAL_HEADER.ImageBase!=0x400000 or pe.FILE_HEADER.Machine!=0x14c:raise ValueError('Unsupported PE layout')
    image=pe.get_memory_mapped_image();u=lambda a:struct.unpack_from('<I',image,a-0x400000)[0]
    cs=Cs(CS_ARCH_X86,CS_MODE_32);ranges={}
    for start,size in RANGES.items():
        blob=image[start-0x400000:start-0x400000+size];instructions=list(cs.disasm(blob,start))
        if sum(i.size for i in instructions)!=size:raise ValueError('Incomplete instruction range')
        if instructions[-1].mnemonic not in ('ret','jmp'):raise ValueError('Missing terminal instruction')
        ranges[hex(start)]={'bytes':size,'instructions':len(instructions),'sha256':hashlib.sha256(blob).hexdigest()}
    for vt,slots in SLOTS.items():
        for slot,target in slots.items():
            if u(vt+slot)!=target:raise ValueError('Actual virtual dispatch differs')
        td=u(u(vt-4)+12)
        name=image[td-0x400000+8:td-0x400000+80].split(b'\0')[0]
        expected=b'.?AVTerrainClass@@' if vt==0x7ad3cc else b'.?AVTerrainTypeClass@@'
        if name!=expected:raise ValueError('Actual Terrain RTTI differs')
    if image[0xac0358-0x400000:0xac0368-0x400000]!=bytes(16):raise ValueError('Empty rectangle initial data differs')
    return {'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','ranges':ranges,
            'virtual_slots':{hex(k):{hex(s):hex(t) for s,t in v.items()} for k,v in SLOTS.items()},
            'scope':'Complete inspected ranges and actual Terrain/type dispatch; no executed parity or traversal claim.'}
if __name__=='__main__':
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--output',type=Path)
    a=p.parse_args();result=verify(a.exe.read_bytes())
    if a.output:
        if a.output.exists():raise ValueError('Inspection output already exists')
        write_report(a.exe,a.output,result)
    print(f'{len(result["ranges"])} complete Terrain visibility ranges / {sum(r["instructions"] for r in result["ranges"].values())} instructions: PASS')
