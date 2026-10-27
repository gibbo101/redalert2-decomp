#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin complete exact-base overlay reader and its selected actual children."""
import hashlib,struct
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_terrain_visibility import PATCHED_EXPECTED
RANGES={0x5db670:0x3b7,0x54aab0:0x45,0x548070:0x38,0x49f430:0x20,
 0x4113b0:4,0x4113c0:0xe,0x4112c0:4,0x5dd150:0x10f,0x6ecf10:0x11c}
def verify(data):
    if hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact supplied engine required')
    pe=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ranges={}
    if pe.OPTIONAL_HEADER.ImageBase!=0x400000 or pe.FILE_HEADER.Machine!=0x14c:raise ValueError('PE layout differs')
    for start,size in RANGES.items():
        blob=pe.get_data(start-0x400000,size);ins=list(cs.disasm(blob,start))
        if sum(i.size for i in ins)!=size or ins[-1].mnemonic!='ret':raise ValueError('Incomplete overlay reader range '+hex(start))
        ranges[hex(start)]={'bytes':size,'instructions':len(ins),'sha256':hashlib.sha256(blob).hexdigest()}
    for vt,slots in {0x79aef8:{0x70:0x4113b0,0x74:0x4113c0,0x7c:0x4112c0},0x7a7a08:{0x9c:0x5dd150}}.items():
        for slot,target in slots.items():
            if struct.unpack('<I',pe.get_data(vt+slot-0x400000,4))[0]!=target:raise ValueError('Overlay reader dispatch differs')
    for p,s in {0x7e8b54:'OverlayPack',0x7e8b44:'OverlayDataPack'}.items():
        if pe.get_data(p-0x400000,len(s)+1)!=s.encode()+b'\0':raise ValueError('Overlay pack name differs')
    return {'ranges':ranges,'scope':'Complete overlay map parent; actual full-map permission, lookup, resident/no-demand image getter, buffer dimensions and empty transient cleanup. Decoded streams, section/buffer/filter/heap services and temporary Overlay construction/placement side effects supplied. No original compression/INI, base/type startup, complete Overlay construction/Unlimbo, ownership/lifetime, runtime or whole-frame claim.'}
