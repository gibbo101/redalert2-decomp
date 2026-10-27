#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin complete ordinary visibility/DrawIt -> Unit/world/shadow nesting."""
import argparse,sys,hashlib
from pathlib import Path
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'tests'))
from verify_unit_voxel_shadow_world import verify as child_verify
from verify_unit_draw_caller import verify as caller_verify
def verify(disc,data):
    child=child_verify(disc,data);caller=caller_verify(data)
    pe=pefile.PE(data=data);code=pe.get_data(0x5d4e40-0x400000,33)
    ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(code,0x5d4e40))
    if sum(i.size for i in ins)!=33 or ins[-1].mnemonic!='ret':raise ValueError('Coordinate copy inspection incomplete')
    return {'child':child,'caller':caller,'map_copy':{'0x5d4e40':{'bytes':33,'instructions':len(ins),'sha256':hashlib.sha256(code).hexdigest()}},
            'scope':'Complete ordinary original-visible Unit visibility/DrawIt caller with actual coordinate/map/height/registry and complete healthy Unit/staging/depth/final/shadow child. Healthy Track/ground/ramp-zero/loaded body/one-frame HVA, inactive timer, no add14/bridge/harvester/flag/alternate type. Projection, ground, type visibility, Foot decoration, cell/table/registry/house/planes/converter/camera construction and successful heap/sufficient pool remain supplied. No ownership/lifetime/runtime/frame parity.'}
if __name__=='__main__':
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--disc',type=Path,default=Path('private/disc-allied/game.exe'));a=p.parse_args()
    verify(a.disc.read_bytes(),a.exe.read_bytes());print('Complete Unit caller/world/shadow inspection: PASS')
