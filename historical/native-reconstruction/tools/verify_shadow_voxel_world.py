#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin complete fresh shadow renderer and nested shadow parent/pixel children."""
import argparse,hashlib,struct,sys
from pathlib import Path
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'tests'))
from verify_cached_voxel_shadow import verify as cached_verify
from verify_shadow_color_mapping import verify as shadow_verify
# Earlier shadow inspection ends at the masked branch's first return. Include
# the complete plotter here, including the out-of-line no-stencil loop/return.
RANGES={0x6d2810:0x1b8,0x6c12c0:8,0x705020:7,0x719c10:0x345}
def verify(disc,data):
    cached=cached_verify(disc,data);shadow=shadow_verify(disc,data)
    pe=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ranges={}
    for a,n in RANGES.items():
        b=pe.get_data(a-0x400000,n);ins=list(cs.disasm(b,a))
        if sum(i.size for i in ins)!=n or ins[-1].mnemonic!=('jmp' if a==0x6c12c0 else 'ret'):raise ValueError('Incomplete shadow render root')
        ranges[hex(a)]={'bytes':n,'instructions':len(ins),'sha256':hashlib.sha256(b).hexdigest()}
    if struct.unpack('<I',pe.get_data(0x7addf8+0x80-0x400000,4))[0]!=0x6c12c0:raise ValueError('Actual Unit type slot differs')
    if struct.unpack('<I',pe.get_data(0x7addf8+0x84-0x400000,4))[0]!=0x705020:raise ValueError('Actual Unit type leaf slot differs')
    for a,target in ((0x6d2335,'0x6d2810'),(0x6d2360,'0x69a1d0'),(0x6d24cd,'0x6d21e0'),
                     (0x6d22ce,'0x6d29d0'),(0x6d28f0,'0x717360'),(0x6d28f9,'0x7178e0')):
        i=next(cs.disasm(pe.get_data(a-0x400000,16),a))
        if i.mnemonic!='call' or i.op_str!=target:raise ValueError('Nested shadow child differs '+hex(a))
    for a,op in ((0x6d2816,'eax, eax'),(0x6d28c0,'eax, [esp + 0x94]'),
                 (0x6d28cc,'ecx, [esp + 0x68]'),(0x6d28d2,'edx, 0x839a70'),
                 (0x6d288b,'cl, byte ptr [eax + 0xb46]')):
        if next(cs.disasm(pe.get_data(a-0x400000,16),a)).op_str!=op:raise ValueError('Shadow HVA/model/camera input differs '+hex(a))
    return {'cached':cached,'shadow':shadow,'ranges':ranges,
            'scope':'Complete successful healthy Unit shadow parent with actual fresh HVA/projection/mask, pool snapshot, recursive cache hit and compressed/raw world pixels. One loaded section/identity global/no half scale/gradient 2/zero Z-shape. Actor/type/HVA/stencil/planes/converter records and sufficient pool/successful heap remain supplied. No actor construction/alternate status/ownership/eviction/lifetime/runtime/frame parity.'}
if __name__=='__main__':
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--disc',type=Path,default=Path('private/disc-allied/game.exe'));a=p.parse_args()
    verify(a.disc.read_bytes(),a.exe.read_bytes());print('Complete shadow cache/render/pixel inspection: PASS')
