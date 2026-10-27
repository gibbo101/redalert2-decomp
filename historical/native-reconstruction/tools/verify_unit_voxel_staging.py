#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Inspect complete Unit/cache/pixel nesting and actual byte staging cleanup."""
import argparse,hashlib,struct,sys
from pathlib import Path
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'tests'))
from verify_foot_voxel_staging import verify as foot_verify
from verify_map_light_mapping import verify as fill_verify
# Map-light already inspects complete Fill/intersection/rectangle construction.
# The small origin getter is inspected here through its final RET.
RANGES={0x435560:0x11}
def verify(disc,data):
    foot=foot_verify(disc,data);fill=fill_verify(disc,data)
    pe=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ranges={}
    for a,size in RANGES.items():
        b=pe.get_data(a-0x400000,size);ins=list(cs.disasm(b,a))
        if sum(i.size for i in ins)!=size or ins[-1].mnemonic!='ret':raise ValueError('Incomplete staging helper '+hex(a))
        ranges[hex(a)]={'bytes':size,'instructions':len(ins),'sha256':hashlib.sha256(b).hexdigest()}
    for offset,target in ((0x78,0x411290),(0x14,0x774390)):
        if struct.unpack('<I',pe.get_data(0x79aef8+offset-0x400000,4))[0]!=target:raise ValueError('Staging surface dispatch differs')
    # These are the complete Unit root's Foot, final, shadow and cleanup calls.
    instructions=list(cs.disasm(pe.get_data(0x6ff690-0x400000,0xf15),0x6ff690))
    calls=[[hex(i.address),i.mnemonic,i.op_str] for i in instructions if i.mnemonic=='call']
    return {'foot':foot,'fill':fill,'ranges':ranges,'unit_calls':calls,
            'scope':'Complete healthy flat one-frame Unit root with actual Foot/Drive, Techno cache, raster/staging/snapshot/cached children, independent body/turret/barrel indexes, bounds and saved-dirty byte Fill. Camera/template/type/actor records, visibility/map/height/predicate, final world surface and shadow remain supplied. No ownership/eviction/failure/status/alternate actor/runtime/frame parity.'}
if __name__=='__main__':
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--disc',type=Path,default=Path('private/disc-allied/game.exe'));a=p.parse_args()
    r=verify(a.disc.read_bytes(),a.exe.read_bytes());print('Unit/cache/pixels/bounds/byte cleanup inspection: PASS')
