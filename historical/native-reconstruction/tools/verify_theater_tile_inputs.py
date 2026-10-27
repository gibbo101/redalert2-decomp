#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Inspect complete exact-base theater root and selected tile constructor."""
import hashlib,struct
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_terrain_visibility import PATCHED_EXPECTED
RANGES={0x529870:0x1a6a,0x528ee0:0x23d}
DEPTH_GLOBALS=(0xa52ee0,0xa6cb74,0xa52f84,0xa52c70,0xa52590,0xa52ef8,0xa52ef4,
 0xa6dd0c,0xa52c68,0xa52ea8,0xa6e018,0xa6e0e8,0xa6cf4c,0xa52c60,0xa6e0e0,0xa52c74)
KEYS=('WaterBridge','ShorePieces','ClearToRoughLat','ClearToSandLat','ClearToGreenLat',
 'ClearToPaveLat','MiscPaveTile','PavedRoads','Medians','RampSmooth','RampBase',
 'RoughTile','SandTile','GreenTile','PaveTile','BridgeSet')
def verify(data):
    if hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact supplied engine required')
    pe=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ranges={}
    for start,size in RANGES.items():
        raw=pe.get_data(start-0x400000,size);ins=list(cs.disasm(raw,start))
        if sum(i.size for i in ins)!=size or ins[-1].mnemonic!='ret':raise ValueError('Incomplete theater input range')
        ranges[hex(start)]={'bytes':size,'instructions':len(ins),'sha256':hashlib.sha256(raw).hexdigest()}
    slot=struct.unpack('<I',pe.get_data(0x7a51a8-0x400000+0x9c,4))[0]
    if slot!=0x5293d0:raise ValueError('Tile image slot differs')
    return {'ranges':ranges,'tile_image_slot':hex(slot),'selected_depth_globals':list(map(hex,DEPTH_GLOBALS)),
      'scope':'Complete theater root and tile constructor execute with supplied INI results, base type constructor, file/heap/graphics/timer/vector services. Every TMP/alternate absent, no tile animation section, sufficient supplied vector capacity. Compare sixteen set-base globals, set-start/shift tables and selected type projection. No original INI parsing, file/archive loading, loaded TMP relocation, alternate images, complete construction, allocation/ownership, original map initialization or runtime/frame claim.'}
