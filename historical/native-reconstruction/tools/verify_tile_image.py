#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin original lazy TMP load, actual color-ramp builder and resident consumers."""
import hashlib,struct
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_terrain_visibility import PATCHED_EXPECTED
from verify_map_cell_inputs import RANGES as INPUT_RANGES
RANGES={0x52b560:0xe7,0x52e3d0:0x284,0x63cc80:0x163,0x63cdf0:0x122,0x77f110:0x3d,
 **{a:INPUT_RANGES[a] for a in (0x5293d0,0x529300,0x52b690,0x52b6f0)}}
def verify(data):
    if hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact supplied engine required')
    pe=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ranges={}
    if pe.OPTIONAL_HEADER.ImageBase!=0x400000 or pe.FILE_HEADER.Machine!=0x14c:raise ValueError('PE layout differs')
    for start,size in RANGES.items():
        raw=pe.get_data(start-0x400000,size);ins=list(cs.disasm(raw,start))
        if sum(i.size for i in ins)!=size or ins[-1].mnemonic!='ret':raise ValueError('Incomplete tile image range '+hex(start))
        ranges[hex(start)]={'bytes':size,'instructions':len(ins),'sha256':hashlib.sha256(raw).hexdigest()}
    slot=struct.unpack('<I',pe.get_data(0x7a51a8+0x9c-0x400000,4))[0]
    if slot!=0x5293d0:raise ValueError('Tile image slot differs')
    constants={0x7a5134:bytes.fromhex('3333b33f'),0x7a5288:bytes.fromhex('555555555555b53f'),
      0x79b7f8:struct.pack('<f',1),0x79b0a8:struct.pack('<f',255),0x79a738:struct.pack('<d',0),0x7d8964:struct.pack('<I',0xe7f)}
    for a,raw in constants.items():
        if pe.get_data(a-0x400000,len(raw))!=raw:raise ValueError('Tile color constant differs')
    return {'ranges':ranges,'tile_image_slot':hex(slot),'constants':{hex(a):raw.hex() for a,raw in constants.items()},
      'scope':'Complete lazy TMP load, actual color-ramp builder/scale/interpolation/FTOL and resident metadata consumers. Successful supplied file/heap/vector storage and clear; local relative offsets, dimensions 0..255, at most 16384 sub-tiles, no growth/failure. Compare normalized image reference offsets, selected type/image metadata, all color-ramp words and actual land/ramp/dimension outputs. No theater filename/variant/map-load order/ownership/lifetime/runtime/full-frame claim.'}
