#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact supplied-1.006 static Terrain traversal and predicate inspection."""
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
    for a,n in [(0x6a9e10,0x13c),(0x5d4f10,11),(0x6e4b00,6)]:
        b=im[a-0x400000:a-0x400000+n];ins=list(cs.disasm(b,a))
        if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Incomplete static Terrain range')
        ranges[hex(a)]={'bytes':n,'instructions':len(ins),'sha256':hashlib.sha256(b).hexdigest()}
    for slot,target in [(0x2c,0x6e4b00),(0x44,0x5d4f10)]:
        if struct.unpack_from('<I',im,0x7ad3cc+slot-0x400000)[0]!=target:raise ValueError('Static Terrain dispatch differs')
    if im[0x7f822c-0x400000:0x7f822c-0x400000+11]!=b'IsAnimated\0':raise ValueError('Terrain type flag name differs')
    return {'executable_sha256':PATCHED_EXPECTED,'ranges':ranges,'inherited_visibility':inherited,
            'scope':'Complete static region scan and actual type/alive leaves. Dynamic traversal/type initialization are separate inspection leads, not executed claims.'}
if __name__=='__main__':
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--output',type=Path)
    a=p.parse_args();result=verify(a.exe.read_bytes())
    if a.output:
        if a.output.exists():raise ValueError('Inspection output already exists')
        write_report(a.exe,a.output,result)
    print(f'{len(result["ranges"])} complete static Terrain ranges / {sum(v["instructions"] for v in result["ranges"].values())} instructions: PASS')
