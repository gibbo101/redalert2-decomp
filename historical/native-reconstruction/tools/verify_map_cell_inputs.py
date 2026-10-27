#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin base decoded map-cell reader, selected Cell initialization and TMP consumers."""
import hashlib,struct
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_terrain_visibility import PATCHED_EXPECTED
RANGES={0x54e1e0:0x120,0x529550:0x39,0x470f10:0x1b8,0x40ff10:0x47,0x5293d0:0x26,
        0x40ffd0:0x25,0x529300:0x38,0x52b690:0x55,0x52b6f0:0x31}
def verify(data):
    if hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact supplied engine required')
    pe=pefile.PE(data=data)
    if pe.OPTIONAL_HEADER.ImageBase!=0x400000 or pe.FILE_HEADER.Machine!=0x14c:raise ValueError('PE layout differs')
    cs=Cs(CS_ARCH_X86,CS_MODE_32);ranges={}
    for start,size in RANGES.items():
        b=pe.get_data(start-0x400000,size);ins=list(cs.disasm(b,start))
        if sum(i.size for i in ins)!=size or ins[-1].mnemonic!='ret':raise ValueError('Incomplete map input range '+hex(start))
        ranges[hex(start)]={'bytes':size,'instructions':len(ins),'sha256':hashlib.sha256(b).hexdigest()}
    # Actual base tile image slot, independent of the YR header layout.
    slot=struct.unpack('<I',pe.get_data(0x7a51a8-0x400000+0x9c,4))[0]
    if slot!=0x5293d0:raise ValueError('Base tile image slot differs')
    return {'ranges':ranges,'tile_image_slot':hex(slot),'land_table_sha256':hashlib.sha256(pe.get_data(0x7de4ec-0x400000,64)).hexdigest(),
      'scope':'Complete IsoMapPack5 reader on supplied decoded stream and map pointer table, actual signed tile-index remap and complete Cell/Abstract constructors and null-scenario registration. Compare selected map/depth field projection and ordered selected stores, not full Cell construction. Actual loaded/null TMP getter and land/ramp/dimension consumers use supplied resident pointer headers. No stream/decompression/TMP relocation/theater shift construction/recalculation/overlay/bridge/tube registration, heap ownership, runtime initialization or full-frame parity.'}
