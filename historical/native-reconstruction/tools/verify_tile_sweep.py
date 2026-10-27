#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin complete usage/load sweep, map iterator and nested actual children."""
import hashlib
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_tile_variants import verify as verify_variant,RANGES as VARIANT_RANGES
from verify_tile_image import verify as verify_image,RANGES as IMAGE_RANGES
RANGES={0x52b2e0:0x27d,0x55a490:0xb2,0x55a550:0x33,**VARIANT_RANGES,
 **{p:IMAGE_RANGES[p] for p in (0x52b560,0x52e3d0,0x63cc80,0x63cdf0,0x77f110)}}
def verify(data):
    variant=verify_variant(data);image=verify_image(data);pe=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ranges={}
    for p,n in RANGES.items():
        raw=pe.get_data(p-0x400000,n);ins=list(cs.disasm(raw,p))
        if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Incomplete tile sweep range '+hex(p))
        ranges[hex(p)]={'bytes':n,'instructions':len(ins),'sha256':hashlib.sha256(raw).hexdigest()}
    return {'ranges':ranges,'variant_tables':variant['table_sha256'],'color_constants':image['constants'],'image_slot':image['tile_image_slot'],
      'scope':'Complete usage/load root, actual map iterator/reset, selector/RNG/GetImage/lazy loader/color children. Supplied Cell/type/pointer-table construction, original tables and initial RNG/cache, successful file/heap/vector storage, fixed timer and diagnostic services. Compare iterator visits/final cursor, ordered usage/releases/file requests, type/image/color state, new-load counts/bytes and full RNG/cache. No original file/archive/type/map construction, heap ownership/lifetime, RMG gameplay, broader initialization, runtime or whole-frame claim.'}
