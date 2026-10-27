#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact supplied-1.006 Unit wrapper and ordinary Object draw gate inspection."""
import argparse
import hashlib
from pathlib import Path
import struct
from verify_dynamic_traversal import verify as verify_traversal
from verify_terrain_visibility import PATCHED_EXPECTED,write_report
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
def verify(data):
    inherited=verify_traversal(data);pe=pefile.PE(data=data);im=pe.get_memory_mapped_image()
    cs=Cs(CS_ARCH_X86,CS_MODE_32);ranges={}
    for a,n in [(0x6ff350,0x8c),(0x5d34e0,0x1f6)]:
        b=im[a-0x400000:a-0x400000+n];ins=list(cs.disasm(b,a))
        if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Incomplete Unit eligibility range')
        ranges[hex(a)]={'bytes':n,'instructions':len(ins),'sha256':hashlib.sha256(b).hexdigest()}
    for slot,target in [(0xa8,0x41b270),(0x10c,0x700e70)]:
        if struct.unpack_from('<I',im,0x7addf8+slot-0x400000)[0]!=target:raise ValueError('Actual Unit render dispatch differs')
    return {'executable_sha256':PATCHED_EXPECTED,'ranges':ranges,'inherited_traversal':inherited,
            'scope':'Complete Unit wrapper and Object draw gate inspected; executed Unit +0x370=0 path. Actual Unit coordinates and type leaf execute. Tactical projection and final DrawIt are services. Special Unit state and non-Unit Object profiles excluded.'}
if __name__=='__main__':
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--output',type=Path)
    a=p.parse_args();result=verify(a.exe.read_bytes())
    if a.output:
        if a.output.exists():raise ValueError('Inspection output already exists')
        write_report(a.exe,a.output,result)
    print(f'{len(result["ranges"])} Unit eligibility ranges / {sum(v["instructions"] for v in result["ranges"].values())} instructions: PASS')
