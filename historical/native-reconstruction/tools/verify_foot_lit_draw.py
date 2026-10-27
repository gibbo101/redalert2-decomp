#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Inspect exact patched Foot lit forwarding and actual Drive zero-offset slot."""
import argparse,hashlib,struct
from pathlib import Path
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_terrain_visibility import PATCHED_EXPECTED,write_report
RANGES={0x4c9880:0xa4,0x53d4d0:0x10,0x58fe10:0x16}
def verify(data):
    if hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact supplied engine required')
    pe=pefile.PE(data=data)
    if pe.OPTIONAL_HEADER.ImageBase!=0x400000 or pe.FILE_HEADER.Machine!=0x14c:raise ValueError('PE layout differs')
    im=pe.get_memory_mapped_image();cs=Cs(CS_ARCH_X86,CS_MODE_32);ranges={}
    for start,size in RANGES.items():
        blob=im[start-0x400000:start-0x400000+size];ins=list(cs.disasm(blob,start))
        if sum(i.size for i in ins)!=size or ins[-1].mnemonic!='ret':raise ValueError('Incomplete Foot lit range')
        ranges[hex(start)]={'bytes':size,'instructions':len(ins),'sha256':hashlib.sha256(blob).hexdigest()}
    for vtable,slot,target in ((0x7addf8,0x3d8,0x4c9880),(0x7a04cc,0x2c,0x53d4d0)):
        if struct.unpack_from('<I',im,vtable+slot-0x400000)[0]!=target:raise ValueError('Foot/Drive lit slot differs')
    return {'ranges':ranges,'unit_slot':{'0x3d8':'0x4c9880'},'drive_slot':{'0x2c':'0x53d4d0'},
            'scope':'Complete Foot lit wrapper and Drive zero point. Read-only offset/final-child services in forwarding tests; actual Drive offset and actual successful Techno cache child nested separately. No full Unit child, real compressed pool, ownership or frame parity.'}
if __name__=='__main__':
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--output',type=Path)
    a=p.parse_args();r=verify(a.exe.read_bytes())
    if a.output:
        if a.output.exists():raise ValueError('Inspection exists')
        write_report(a.exe,a.output,r)
    print(f'{len(RANGES)} complete Foot/Drive/copy ranges: PASS')
