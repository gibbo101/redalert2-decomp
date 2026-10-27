#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact patched Foot/Drive secondary getters and scoped constructor inputs."""
import argparse
import hashlib
from pathlib import Path
import struct
from verify_unit_visibility import verify as verify_visibility
from verify_terrain_visibility import PATCHED_EXPECTED,write_report
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
COMPLETE={0x4ca6f0:0xde,0x49fdb0:0x71,0x49f600:0x12,0x4c2870:0x12,0x40ff10:0x47}
BLOCKS={0x5d24e4:8,0x6c1287:0x13,0x4c2bfe:9,0x6c1063:6,0x4c2ace:7}
CALLS={0x6fa40e:0x4c2930,0x4c293a:0x6c0cd0,0x6c0cd6:0x636830,0x636833:0x594500,0x594503:0x5d22e0,0x5d22e4:0x40ff10}
def verify(data):
    inherited=verify_visibility(data);im=pefile.PE(data=data).get_memory_mapped_image();cs=Cs(CS_ARCH_X86,CS_MODE_32)
    records={}
    for a,n in {**COMPLETE,**BLOCKS}.items():
        b=im[a-0x400000:a-0x400000+n];ins=list(cs.disasm(b,a))
        if sum(i.size for i in ins)!=n or (a in COMPLETE and ins[-1].mnemonic!='ret'):raise ValueError('Incomplete actor inspection range')
        records[hex(a)]={'bytes':n,'instructions':len(ins),'sha256':hashlib.sha256(b).hexdigest(),'complete_routine':a in COMPLETE}
    for a,target in CALLS.items():
        ins=list(cs.disasm(im[a-0x400000:a-0x400000+5],a))
        if len(ins)!=1 or ins[0].mnemonic!='call' or ins[0].op_str!=hex(target):raise ValueError('Constructor chain differs')
    u=lambda a:struct.unpack_from('<I',im,a-0x400000)[0]
    if u(0x7a04cc+0x18)!=0x49fdb0:raise ValueError('Drive secondary getter slot differs')
    locator=u(0x7a04cc-4);td=u(locator+12)
    if u(locator+4)!=4 or im[td+8-0x400000:td+8-0x400000+len(b'.?AVDriveLocomotionClass@@\0')]!=b'.?AVDriveLocomotionClass@@\0':
        raise ValueError('Drive interface RTTI differs')
    ins=list(cs.disasm(im[0x6c0cdb-0x400000:0x6c1069-0x400000],0x6c0cdb))
    if ins[0].mnemonic!='xor' or ins[0].op_str!='ebx, ebx':raise ValueError('Constructor zero register differs')
    if any(i.mnemonic not in ('cmp','test','push') and i.op_str.startswith(('ebx,','bx,','bl,')) for i in ins[1:]):
        raise ValueError('Constructor zero register is overwritten')
    return {'executable_sha256':PATCHED_EXPECTED,'ranges':records,'constructor_calls':{hex(a):hex(b) for a,b in CALLS.items()},
            'inherited_visibility':inherited,'scope':'Complete Foot/Drive getters and sentinel/Abstract initializers, scoped constructor field stores and inspected call links. No complete Unit construction claim. Combined traversal executes actual nested getters/Unit eligibility; inverse camera, map, tactical projection, DrawIt and extras remain services.'}
if __name__=='__main__':
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--output',type=Path)
    a=p.parse_args();r=verify(a.exe.read_bytes())
    if a.output:
        if a.output.exists():raise ValueError('Inspection output already exists')
        write_report(a.exe,a.output,r)
    print(f'{len(COMPLETE)} complete routines + {len(BLOCKS)} scoped actor blocks: PASS')
