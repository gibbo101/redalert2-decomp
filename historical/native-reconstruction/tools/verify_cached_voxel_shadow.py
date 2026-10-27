#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin complete cached shadow span and actual depth-read selector on exact base."""
import argparse,hashlib,struct,sys
from pathlib import Path
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'tests'))
from verify_unit_voxel_world import verify as world_verify
def verify(disc,data):
    inherited=world_verify(disc,data);pe=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32)
    a,n=0x489d90,0xcb;b=pe.get_data(a-0x400000,n);ins=list(cs.disasm(b,a))
    if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Incomplete cached shadow span')
    if struct.unpack('<I',pe.get_data(0x79e0e4-0x400000,4))[0]!=a:raise ValueError('RLE shadow span slot differs')
    locator=struct.unpack('<I',pe.get_data(0x79e0dc-0x400000,4))[0]
    name=struct.unpack('<5I',pe.get_data(locator-0x400000,20))[3]+8
    expected=b'.?AV?$RLEBlitTransDarkenZRead@G@@\0'
    if pe.get_data(name-0x400000,len(expected))!=expected:raise ValueError('RLE shadow RTTI differs')
    if struct.unpack('<I',pe.get_data(0x7d3a78-0x400000,4))[0]!=0x3000:raise ValueError('Depth-read selector mask differs')
    for a,op in ((0x485e0a,'eax, dword ptr [esi + 0xf0]'),(0x489e16,'eax, byte ptr [ecx]')):
        if next(cs.disasm(pe.get_data(a-0x400000,16),a)).op_str!=op:raise ValueError('Cached shadow association differs')
    return {'world':inherited,'ranges':{'0x489d90':{'bytes':n,'instructions':len(ins),'sha256':hashlib.sha256(b).hexdigest()}},
            'scope':'Complete cached healthy Unit world shadow child, actual compressed depth-read span/selector, gradient 2 and checked zero Z-shape. Supplied pool/planes/actor scalar/house converter records; no parent/render/ownership/alternate Z-shape/runtime/frame parity.'}
if __name__=='__main__':
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--disc',type=Path,default=Path('private/disc-allied/game.exe'));a=p.parse_args()
    verify(a.disc.read_bytes(),a.exe.read_bytes());print('Cached Unit/world shadow inspection: PASS')
