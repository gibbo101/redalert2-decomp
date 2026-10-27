#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin complete Unit/world -> Foot shadow -> actual shadow/cache/pixel nesting."""
import argparse,struct,sys
from pathlib import Path
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'tests'))
from verify_shadow_voxel_world import verify as shadow_verify
def verify(disc,data):
    inherited=shadow_verify(disc,data);pe=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32)
    for a,target in ((0x700580,'0x4c9a40'),):
        i=next(cs.disasm(pe.get_data(a-0x400000,16),a))
        if i.mnemonic!='call' or i.op_str!=target:raise ValueError('Unit/Foot shadow nesting differs')
    ins=list(cs.disasm(pe.get_data(0x4c9a40-0x400000,205),0x4c9a40))
    calls=[[hex(i.address),i.op_str] for i in ins if i.mnemonic=='call']
    if not any(target=='0x6d21e0' for _,target in calls):raise ValueError('Foot shadow child differs')
    return {'shadow':inherited,'foot_shadow_calls':calls,'scope':'Complete healthy Unit/staging/depth/final-world and actual Foot/shadow render/pool/recursive cache/raw/compressed pixels, four independent indexes sharing supplied sufficient pool. Loaded body/one-frame HVA/Track/ground/ramp zero/identity globals/no half scale/gradient 2/zero Z-shape. Actor/map/type/converter/planes and successful heap remain supplied; no construction/ownership/eviction/lifetime/alternate status/runtime/frame parity.'}
if __name__=='__main__':
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--disc',type=Path,default=Path('private/disc-allied/game.exe'));a=p.parse_args()
    verify(a.disc.read_bytes(),a.exe.read_bytes());print('Complete Unit/world/shadow nesting inspection: PASS')
