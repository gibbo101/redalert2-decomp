#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Inspect exact complete Foot/cache/raster/snapshot/cached-staging nesting."""
import argparse,hashlib,sys
from pathlib import Path
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'tests'))
from verify_voxel_snapshot import verify as snapshot_verify
from verify_foot_lit_draw import verify as foot_verify
from verify_raster_mapping import verify as raster_verify
from verify_unit_voxel_draw import verify as unit_verify
from verify_presentation_mapping import verify as presentation_verify
from raster_profiles import PATCHED_ADDRESSES
RANGES={0x41b390:0x35,0x6d79d0:0x31,0x781d46:0x154,0x781e9a:0x4e,0x781ee8:0x2c,0x6d98d0:0x22}
# Complete out-of-line voxel span bodies, ending in a jump back to their
# inspected outer traversal. These are not callable routines ending in RET.
SPAN_RANGES={0x784220:(0x798ca0,0x69),0x784340:(0x798dc0,0x69)}
def verify(disc,data):
    snapshot=snapshot_verify(disc,data);foot=foot_verify(data);raster=raster_verify(disc,data);unit=unit_verify(data)
    presentation=presentation_verify(disc,data)
    pe=pefile.PE(data=data);old_pe=pefile.PE(data=disc);im=pe.get_memory_mapped_image();cs=Cs(CS_ARCH_X86,CS_MODE_32);ranges={}
    for a,size in RANGES.items():
        b=im[a-0x400000:a-0x400000+size];ins=list(cs.disasm(b,a))
        if sum(i.size for i in ins)!=size or ins[-1].mnemonic!='ret':raise ValueError('Incomplete nested cache range '+hex(a))
        ranges[hex(a)]={'bytes':size,'instructions':len(ins),'sha256':hashlib.sha256(b).hexdigest()}
    spans={}
    for old,(a,size) in SPAN_RANGES.items():
        b=pe.get_data(a-0x400000,size);before=list(cs.disasm(old_pe.get_data(old-0x400000,size),old));after=list(cs.disasm(b,a))
        if (sum(i.size for i in before)!=size or sum(i.size for i in after)!=size or
                len(before)!=len(after) or after[-1].mnemonic!='jmp'):
            raise ValueError('Incomplete out-of-line raster span '+hex(a))
        for x,y in zip(before,after):
            if x.mnemonic!=y.mnemonic or x.size!=y.size or x.address-old!=y.address-a:
                raise ValueError('Raster span instruction shape differs')
            expected=x.op_str
            for src,dst in sorted(PATCHED_ADDRESSES.items(),reverse=True):
                expected=expected.replace(hex(src),hex(dst))
            if x.mnemonic.startswith('j'):
                target=int(x.op_str,16);expected=hex(a+target-old)
            if expected!=y.op_str:raise ValueError('Raster span operand differs '+hex(y.address))
        spans[hex(a)]={'disc_va':hex(old),'bytes':size,'instructions':len(after),'sha256':hashlib.sha256(b).hexdigest()}
    for a,target in ((0x798c6b,'0x798ca0'),(0x798d8c,'0x798dc0')):
        i=next(cs.disasm(pe.get_data(a-0x400000,8),a))
        if i.mnemonic!='jns' or i.op_str!=target:raise ValueError('Raster span parent differs')
    for a,target in ((0x6d1ed7,'0x6d24e0'),(0x6d2020,'0x717040'),(0x6d202b,'0x69a1d0'),(0x6d1e8a,'0x6d29d0')):
        i=next(cs.disasm(pe.get_data(a-0x400000,16),a))
        if i.mnemonic!='call' or i.op_str!=target:raise ValueError('Nested cache child differs')
    return {'snapshot':snapshot,'foot':foot,'raster':raster,'unit':unit,'presentation':presentation,'ranges':ranges,'raster_spans':spans,
            'scope':'Actual Foot/Drive, complete healthy Techno cache root, actual raster/staging/pool/cached byte drawing and original signed qsort/search. Sufficient supplied pool and successful allocator; owner/house/scalar services and healthy actor/type/HVA/global records remain supplied. No allocation failure/eviction/status alternates/Unit root/runtime/whole-frame parity.'}
if __name__=='__main__':
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--disc',type=Path,default=Path('private/disc-allied/game.exe'));a=p.parse_args()
    r=verify(a.disc.read_bytes(),a.exe.read_bytes());print('Foot/cache/raster/snapshot/cached nesting inspection: PASS')
