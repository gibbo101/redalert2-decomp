#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Inspect exact base overlay construction, list, resolver and INI roots."""
import hashlib,struct
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_terrain_visibility import PATCHED_EXPECTED
RANGES={0x5dc5a0:0x152,0x5dcaa0:0x2a1,0x5dcf70:0x83,0x64c010:0x6a,0x40ffd0:0x25}
# Complete base roots are inspected only, never entered by this oracle. Their
# key/store associations supply vocabulary, not executed base defaulting proof.
BASE_RANGES={0x5d57f0:0x287,0x5d7810:0x3bf}
KEYS={0x7e8c44:'Land',0x7e81a0:'Strength',0x7d0fa8:'Wall',0x7cdcd0:'Tiberium',
 0x7e8c3c:'Crate',0x7e8c2c:'CrateTrigger',0x7e8c20:'Explodes',0x7e8c14:'Overrides',
 0x7e8c08:'CellAnim',0x7e8bf8:'DamageLevels',0x7ceeac:'DemandLoad',
 0x7e8be4:'NoUseTileLandType',0x7e8bd0:'IsVeinholeMonster',0x7cee50:'IsVeins',
 0x7e8bc0:'ChainReaction',0x7e8bb4:'DrawFlat',0x7e8bac:'IsARock',0x7e8ba0:'IsRubble'}
def verify(data):
    if hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact supplied engine required')
    pe=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ranges={}
    if pe.OPTIONAL_HEADER.ImageBase!=0x400000 or pe.FILE_HEADER.Machine!=0x14c:raise ValueError('PE layout differs')
    for start,size in {**RANGES,**BASE_RANGES}.items():
        blob=pe.get_data(start-0x400000,size);ins=list(cs.disasm(blob,start))
        if sum(i.size for i in ins)!=size or ins[-1].mnemonic!='ret':raise ValueError('Incomplete overlay input range '+hex(start))
        ranges[hex(start)]={'bytes':size,'instructions':len(ins),'sha256':hashlib.sha256(blob).hexdigest(),
          'execution':'actual' if start in RANGES else 'inspection-only'}
    for a,text in {**KEYS,0x7cdecc:'<none>',0x7ce0ec:'none',0x7ced14:'.SHP',0x7eebfc:'OverlayTypes',
      0x7e8200:'Crushable',0x7e81c4:'RadarInvisible',0x7e81b8:'Selectable',
      0x7e8188:'Insignificant',0x7d3824:'Armor'}.items():
        if pe.get_data(a-0x400000,len(text)+1)!=text.encode()+b'\0':raise ValueError('Overlay key differs')
    if struct.unpack('<I',pe.get_data(0x7a908c-0x400000,4))[0]!=0x7eebfc:raise ValueError('Overlay section pointer differs')
    if struct.unpack('<I',pe.get_data(0x7a7a08-0x400000+0x64,4))[0]!=0x5dcaa0:raise ValueError('Overlay INI slot differs')
    return {'ranges':ranges,'keys':{hex(a):s for a,s in KEYS.items()},
      'scope':'Complete overlay constructor/resolver/list/INI roots with actual identity child (loading=0). Base ObjectType constructor/INI and CRT comparison, decoded INI results, image/animation/file/path/heap/growth services supplied. Ordered selected stores and full selected state/registry tail compared. No original parser, base defaults/full construction, startup, map loading, ownership/lifetime, runtime or frame claim.'}
