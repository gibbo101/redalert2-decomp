#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact patched dynamic caller/Unit dispatch inspection; not executed parity."""
import argparse
import hashlib
from pathlib import Path
import struct
from verify_terrain_visibility import verify as verify_visibility
from verify_terrain_visibility import PATCHED_EXPECTED,write_report
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
def verify(data):
    inherited=verify_visibility(data);pe=pefile.PE(data=data);im=pe.get_memory_mapped_image()
    cs=Cs(CS_ARCH_X86,CS_MODE_32);ranges={}
    # Complete caller, complete Unit behind routine (only Unit-type exit is
    # executed), Unit type leaf, and complete actual world-projection routine.
    for a,n in [(0x6a93f0,0xa18),(0x6c3b30,0x3cb),(0x70a2d0,6),(0x6a27a0,0xc8)]:
        b=im[a-0x400000:a-0x400000+n];ins=list(cs.disasm(b,a))
        if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Incomplete dynamic traversal range')
        ranges[hex(a)]={'bytes':n,'instructions':len(ins),'sha256':hashlib.sha256(b).hexdigest()}
    slots={0x2c:0x70a2d0,0x48:0x5d4e40,0x4c:0x4ca6f0,0xfc:0x6ff350,0x104:0x6c3b30,0x108:0x6c2c40}
    for slot,target in slots.items():
        if struct.unpack_from('<I',im,0x7addf8+slot-0x400000)[0]!=target:raise ValueError('Actual Unit dispatch differs')
    locator=struct.unpack_from('<I',im,0x7addf4-0x400000)[0]
    td=struct.unpack_from('<I',im,locator+12-0x400000)[0]
    if im[td+8-0x400000:td+8-0x400000+16]!=b'.?AVUnitClass@@\0':raise ValueError('Unit RTTI differs')
    return {'executable_sha256':PATCHED_EXPECTED,'ranges':ranges,'inherited_visibility':inherited,
            'unit_slots':{hex(k):hex(v) for k,v in slots.items()},
            'scope':'Complete caller inspected. Bounded execution covers Foot/Unit and Terrain, with empty auxiliary collection. Inverse camera, Foot secondary getter, map predicate, eligibility and extras are services. Unit DrawBehind executes its original type=1 no-op path. Other caller branches and constructors are not recovered.'}
if __name__=='__main__':
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--output',type=Path)
    a=p.parse_args();result=verify(a.exe.read_bytes())
    if a.output:
        if a.output.exists():raise ValueError('Inspection output already exists')
        write_report(a.exe,a.output,result)
    print(f'{len(result["ranges"])} dynamic traversal ranges / {sum(v["instructions"] for v in result["ranges"].values())} instructions: PASS')
