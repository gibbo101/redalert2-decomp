#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin complete exact-base map geometry roots and inspected INI association."""
import hashlib,struct
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_terrain_visibility import PATCHED_EXPECTED
from verify_map_cell_inputs import RANGES as INPUT_RANGES
RANGES={0x5484e0:0x14d7,0x5499c0:0x118,0x549ae0:0x135,0x41fdf0:0x121,
 0x47a450:0xc,**{p:INPUT_RANGES[p] for p in (0x470f10,0x40ff10,0x40ffd0)}}
INSPECTED={0x49cfd0:0x936,0x630840:0x1b7,0x548490:0x43}
def verify(data):
    if hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact supplied engine required')
    pe=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ranges={};callers={}
    if pe.OPTIONAL_HEADER.ImageBase!=0x400000 or pe.FILE_HEADER.Machine!=0x14c:raise ValueError('PE layout differs')
    for group,out in ((RANGES,ranges),(INSPECTED,callers)):
        for start,size in group.items():
            raw=pe.get_data(start-0x400000,size);ins=list(cs.disasm(raw,start))
            if sum(i.size for i in ins)!=size or ins[-1].mnemonic!='ret':raise ValueError('Incomplete geometry range '+hex(start))
            out[hex(start)]={'bytes':size,'instructions':len(ins),'sha256':hashlib.sha256(raw).hexdigest()}
    vt=0x7a593c
    slots=struct.unpack('<2I',pe.get_data(vt+0x70-0x400000,8))
    if slots!=(0x5484e0,0x549ae0):raise ValueError('Map geometry slots differ')
    col=struct.unpack('<I',pe.get_data(vt-4-0x400000,4))[0]
    td=struct.unpack('<I',pe.get_data(col+12-0x400000,4))[0]
    if pe.get_data(td+8-0x400000,40).split(b'\0')[0]!=b'.?AVMapClass@@':raise ValueError('Map RTTI differs')
    def check(start,hexbytes):
        raw=bytes.fromhex(hexbytes)
        if pe.get_data(start-0x400000,len(raw))!=raw:raise ValueError('Inspected map caller differs')
    # INI Size caller: push rebuild=1, level=0, reuse=1, rectangle, slot+70.
    check(0x49d051,'8b450033db56538d8c248c00000056518bcdff5070')
    # LocalSize wrapper calls the actual setter before screen/radar work.
    raw=pe.get_data(0x630840-0x400000,0x1b8)
    if not any(i.mnemonic=='call' and i.op_str=='0x549ae0' for i in cs.disasm(raw,0x630840)):
        raise ValueError('LocalSize setter association differs')
    return {'ranges':ranges,'inspected_only_callers':callers,'map_vtable':hex(vt),'geometry_slots':list(map(hex,slots)),
      'scope':'Initial empty map pointer table, reuse=1, no actors, actual Cell/Abstract/null-scenario registration and packed position setter; optional actual buffer numeric/fill root. Successful supplied heap, zone/light/graphics/vector services. Complete SetVisibleRect with actual intersection and empty actor list. Selected Cell fields and ordered selected stores only; no full Cell constructor projection, original map INI/decompression, loaded theater, broader map preparation, ownership/lifetime, runtime or whole-frame parity. INI/screen/reset callers are inspection only.'}
