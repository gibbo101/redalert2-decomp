#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin complete Foot depth/gradient, cell predicates and selected healthy base."""
import argparse,hashlib,struct
from pathlib import Path
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_terrain_visibility import PATCHED_EXPECTED,write_report
RANGES={0x4c9930:0xdf,0x4c9a10:0x30,0x4a4830:5,0x4a4840:13,
        0x53d4b0:8,0x6cf670:0x1a4,0x6cf820:0x1a4,0x6cf9d0:0x181,
        0x6cfb60:0x23c,0x6cfda0:0x100,0x479cc0:0x2b,0x41b320:0x3d,
        0x705020:7,0x491620:172,0x6cfea0:1645,0x5d4800:7,
        0x70a2d0:6,0x4b8be0:153,0x6a2970:60}
TAILS={0x6c12c0:8}
def verify(data):
    if hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact supplied engine required')
    pe=pefile.PE(data=data)
    if pe.OPTIONAL_HEADER.ImageBase!=0x400000 or pe.FILE_HEADER.Machine!=0x14c:raise ValueError('PE layout differs')
    im=pe.get_memory_mapped_image();cs=Cs(CS_ARCH_X86,CS_MODE_32);ranges={}
    for start,size in {**RANGES,**TAILS}.items():
        b=im[start-0x400000:start-0x400000+size];ins=list(cs.disasm(b,start))
        if sum(i.size for i in ins)!=size or ins[-1].mnemonic!=('jmp' if start in TAILS else 'ret'):
            raise ValueError(f'Incomplete Foot depth range {start:#x}')
        ranges[hex(start)]={'bytes':size,'instructions':len(ins),'sha256':hashlib.sha256(b).hexdigest()}
    slots={0x80:0x6c12c0,0x1a0:0x41b320,0x1b8:0x5d4800,0x2c:0x70a2d0,0x2c0:0x4c9930,0x2c4:0x4c9a10}
    for table,mapping in ((0x7addf8,slots),(0x7a04cc,{0x38:0x4a4830,0x3c:0x4a4840})):
        for off,target in mapping.items():
            if struct.unpack_from('<I',im,table+off-0x400000)[0]!=target:raise ValueError('Foot depth dispatch differs')
    return {'ranges':ranges,'unit_slots':{hex(k):hex(v) for k,v in slots.items()},
            'scope':'Complete Foot depth/gradient and five cell predicates with actual coordinate/type/Drive/cell leaves. Neighbor initializer executes. Map lookup/records, type factors, tile base, invalid coordinate and cell type count are supplied. Ordinary nested actual base depth uses healthy height zero, flat/ramp-zero records and zero tile dimensions service; surface nesting uses initialized house planes. No original map/type construction, alternate base depth, ownership, runtime wiring or whole-frame parity.'}
if __name__=='__main__':
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--output',type=Path)
    a=p.parse_args();r=verify(a.exe.read_bytes())
    if a.output:
        if a.output.exists():raise ValueError('Inspection exists')
        write_report(a.exe,a.output,r)
    print(f'{len(r["ranges"])} complete Foot depth/helper ranges / {sum(v["instructions"] for v in r["ranges"].values())} instructions: PASS')
