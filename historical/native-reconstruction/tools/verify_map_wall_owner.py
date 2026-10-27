#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin complete wall owner, Cell-target distance and actual coordinate dispatch."""
import hashlib,struct
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_terrain_visibility import PATCHED_EXPECTED
from verify_tile_image import RANGES as IMAGE_RANGES
RANGES={0x4724a0:0x93,0x5d4c00:0xd5,0x47ba50:0x49,0x444080:0x54,
 0x458930:0xe,0x458940:0x3d,0x6c7420:0xa,0x47cf80:6,0x4ba410:0x6e,
 0x77f110:IMAGE_RANGES[0x77f110]}
def verify(data):
    if hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact supplied engine required')
    p=pefile.PE(data=data);im=p.get_memory_mapped_image();cs=Cs(CS_ARCH_X86,CS_MODE_32)
    if p.FILE_HEADER.Machine!=0x14c or p.OPTIONAL_HEADER.ImageBase!=0x400000:raise ValueError('Wall owner PE layout differs')
    ranges={}
    for a,n in RANGES.items():
        raw=p.get_data(a-0x400000,n);ins=list(cs.disasm(raw,a))
        if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Incomplete wall owner range '+hex(a))
        ranges[hex(a)]={'bytes':n,'instructions':len(ins),'sha256':hashlib.sha256(raw).hexdigest()}
    dispatch={0x79cbbc:{0x38:0x6c7420,0x48:0x444080},0x79db04:{0x2c:0x47cf80,0x48:0x47ba50}}
    for vt,slots in dispatch.items():
        locator=struct.unpack_from('<I',im,vt-4-0x400000)[0]
        base=struct.unpack_from('<I',im,locator+4-0x400000)[0]
        td=struct.unpack_from('<I',im,locator+12-0x400000)[0]
        name=b'.?AVBuildingClass@@\0' if vt==0x79cbbc else b'.?AVCellClass@@\0'
        if base or im[td+8-0x400000:td+8-0x400000+len(name)]!=name:raise ValueError('Wall owner RTTI differs')
        for off,target in slots.items():
            if struct.unpack_from('<I',im,vt+off-0x400000)[0]!=target:raise ValueError('Wall owner dispatch differs')
    return {'ranges':ranges,'dispatch':{hex(a):{hex(k):hex(v) for k,v in row.items()} for a,row in dispatch.items()},
      'foundation_tables_sha256':hashlib.sha256(p.get_data(0x7cfc70-0x400000,176)).hexdigest(),
      'sqrt_table_sha256':hashlib.sha256(p.get_data(0x817dfc-0x400000,65536)).hexdigest(),
      'scope':'Complete wall owner selection and Cell-target distance with actual Cell/Building coordinate, foundation, owner/kind, table sqrt and FTOL children, using supplied 53-bit/toward-zero caller FP mode. Terrain height is a supplied service; selected registry/house/type/initial Cell records supplied. Diagnostic selection-only cases supply distance explicitly. No null/building-target distance, height/ramp recovery, construction/startup/map-parent/runtime or frame parity.'}
