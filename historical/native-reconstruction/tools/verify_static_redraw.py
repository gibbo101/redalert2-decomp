#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin the complete patched static request caller and nested static dispatch."""
import argparse
import hashlib
from pathlib import Path
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_static_terrain import verify as verify_static
from verify_terrain_visibility import PATCHED_EXPECTED,write_report
RANGES={0x6a4350:0x246,0x41b630:0x19,0x6a27a0:0xc8,
        0x6a20e0:0x28,0x6a2170:0x13,0x6a2440:0x34}
def verify(data):
    inherited=verify_static(data);im=pefile.PE(data=data).get_memory_mapped_image();cs=Cs(CS_ARCH_X86,CS_MODE_32);records={}
    for a,n in RANGES.items():
        b=im[a-0x400000:a-0x400000+n];ins=list(cs.disasm(b,a))
        if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Incomplete static request range')
        records[hex(a)]={'bytes':n,'instructions':len(ins),'sha256':hashlib.sha256(b).hexdigest()}
    for a in [0x6a4449,0x6a451e,0x6a4543,0x6a456a,0x6a4587]:
        ins=list(cs.disasm(im[a-0x400000:a-0x400000+5],a))
        if len(ins)!=1 or ins[0].mnemonic!='call' or ins[0].op_str!='0x6a9e10':raise ValueError('Static scan caller link differs')
    return {'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','ranges':records,
            'inherited_static':inherited,'scope':'Complete static request caller, coordinate initializer and actual world projection/initializers. Nested complete Terrain static scan/eligibility execute. Render bounds, tactical projection and final Terrain drawing are services. No outer frame scheduler or runtime parity.'}
if __name__=='__main__':
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--output',type=Path)
    a=p.parse_args();r=verify(a.exe.read_bytes())
    if a.output:
        if a.output.exists():raise ValueError('Inspection output already exists')
        write_report(a.exe,a.output,r)
    print(f'{len(r["ranges"])} complete static request ranges / {sum(v["instructions"] for v in r["ranges"].values())} instructions: PASS')
