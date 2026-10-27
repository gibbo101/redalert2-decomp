#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin complete LAT, empty-cell passability, map permission and actual children."""
import hashlib,struct
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_map_cell_inputs import verify as input_verify
RANGES={0x471d10:0x78a,0x478f40:0x1a9,0x55a660:0xd7,0x548070:0x38,
        0x42add0:0x29,0x5293d0:0x26,0x5293a0:0x2b}
LAT_GLOBALS=(0xa52ee0,0xa6cb74,0xa52f84,0xa52c70,0xa52590,0xa52ef8,0xa52ef4,0xa6dd0c,0xa52c68,0xa52ea8,0xa6e018,0xa6e0e8,0xa6cf4c,0xa52c60,0xa6e0e0)
def verify(data):
    inherited=input_verify(data);pe=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ranges={}
    for a,n in RANGES.items():
        b=pe.get_data(a-0x400000,n);ins=list(cs.disasm(b,a))
        if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Incomplete Cell child range '+hex(a))
        ranges[hex(a)]={'bytes':n,'instructions':len(ins),'sha256':hashlib.sha256(b).hexdigest()}
    if struct.unpack('<d',pe.get_data(0x79c518-0x400000,8))[0]!=0.01:raise ValueError('Cell passability threshold differs')
    return {'inputs':inherited,'ranges':ranges,'scope':'Complete LAT and complete passability on no-overlay/no-occupant cells, actual permission/lookup/word-add/resident getter children. Supplied tile-set globals, direction offsets, geometry, cell pointer/type/image tables and float32 land speeds. Lazy loading, registry/theater construction, overlays/occupants, ownership, runtime association and whole-frame parity excluded.'}
