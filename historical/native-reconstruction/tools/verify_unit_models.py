#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin complete base ordinary model root, actual kind/count/section leaves."""
import argparse,hashlib,struct
from pathlib import Path
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_terrain_visibility import PATCHED_EXPECTED,write_report
RANGES={0x5d6730:0xb77,0x70b5e0:6,0x6df680:14,0x719860:0x22}
STRINGS={0x7cfe60:'.VXL',0x7cfe54:'.HVA',0x7e80e4:'%sTUR',0x7e80f8:'%sBARL'}
def verify(data):
    if hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact supplied engine required')
    pe=pefile.PE(data=data)
    if pe.OPTIONAL_HEADER.ImageBase!=0x400000 or pe.FILE_HEADER.Machine!=0x14c:raise ValueError('PE layout differs')
    im=pe.get_memory_mapped_image();cs=Cs(CS_ARCH_X86,CS_MODE_32);ranges={}
    for start,size in RANGES.items():
        b=im[start-0x400000:start-0x400000+size];ins=list(cs.disasm(b,start))
        if sum(i.size for i in ins)!=size or ins[-1].mnemonic!='ret':raise ValueError('Incomplete model range '+hex(start))
        ranges[hex(start)]={'bytes':size,'instructions':len(ins),'sha256':hashlib.sha256(b).hexdigest()}
    for p,s in STRINGS.items():
        if im[p-0x400000:].split(b'\0',1)[0]!=s.encode():raise ValueError('Model name string differs')
    if struct.unpack_from('<I',im,0x7ae328+0x2c-0x400000)[0]!=0x70b5e0:raise ValueError('Actual UnitType kind slot differs')
    return {'ranges':ranges,'strings':{hex(p):s for p,s in STRINGS.items()},'unit_type_kind_slot':'0x70b5e0',
            'scope':'Complete original model root executes bounded UnitType/nonzero Turret/TurretCount=0 branch. Actual kind, multiple-turret and VXL section getter leaves execute. Image-base/part records, descriptor arrays, error bytes and caches are supplied; CRT name building, files, allocators, VXL/HVA construction/destruction/association are services. No original file parsing, type/actor construction, resource ownership, numbered/alternate models or runtime integration.'}
if __name__=='__main__':
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--output',type=Path);a=p.parse_args();r=verify(a.exe.read_bytes())
    if a.output:
        if a.output.exists():raise ValueError('Inspection exists')
        write_report(a.exe,a.output,r)
    print(f'{len(r["ranges"])} complete model ranges / {sum(x["instructions"] for x in r["ranges"].values())} instructions: PASS')
