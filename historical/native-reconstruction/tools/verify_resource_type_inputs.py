#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin complete base resource construction/INI/numeric-list roots and dispatch."""
import hashlib,struct
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_terrain_visibility import PATCHED_EXPECTED
RANGES={0x6e89a0:0x1be,0x6e8d30:0x29d,0x6e8ff0:0xaa}
BASE_RANGES={0x410580:0x154,0x4107e0:0x124}
KEYS={0x7f84f4:'Spread',0x7f84e0:'SpreadPercentage',0x7f84d8:'Growth',
 0x7f84c4:'GrowthPercentage',0x7f84bc:'Value',0x7cfd44:'Power',0x7d13d8:'Color',
 0x7f84b4:'Debris',0x7cfddc:'Image',0x7f84fc:'Tiberiums'}
def verify(data):
    if hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact supplied engine required')
    pe=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ranges={}
    if pe.OPTIONAL_HEADER.ImageBase!=0x400000 or pe.FILE_HEADER.Machine!=0x14c:raise ValueError('PE layout differs')
    for a,size in {**RANGES,**BASE_RANGES}.items():
        b=pe.get_data(a-0x400000,size);ins=list(cs.disasm(b,a))
        if sum(i.size for i in ins)!=size or ins[-1].mnemonic!='ret':raise ValueError('Incomplete resource range '+hex(a))
        ranges[hex(a)]={'bytes':size,'instructions':len(ins),'sha256':hashlib.sha256(b).hexdigest(),
          'execution':'actual' if a in RANGES else 'inspection-only'}
    for a,s in {**KEYS,0x7ce9c0:','}.items():
        if pe.get_data(a-0x400000,len(s)+1)!=s.encode()+b'\0':raise ValueError('Resource string differs')
    table=pe.get_data(0x6e8fd0-0x400000,24)
    if struct.unpack('<6I',table)!=(0x6e8fb3,0x6e8f87,0x6e8f87,0x6e8f33,0x6e8f5f,0x6e8f73):raise ValueError('Resource Image switch differs')
    if struct.unpack('<I',pe.get_data(0x7ad8b0+0x64-0x400000,4))[0]!=0x6e8d30:raise ValueError('Resource INI dispatch differs')
    if struct.unpack('<I',pe.get_data(0x7a3b3c+12-0x400000,4))[0]!=0x50b110:raise ValueError('Resource vector clear dispatch differs')
    return {'ranges':ranges,'keys':{hex(a):s for a,s in KEYS.items()},'image_switch_sha256':hashlib.sha256(table).hexdigest(),
      'scope':'Complete resource subtype construction/INI and numeric-key Tiberiums list with actual nested construction/INI dispatch. Base AbstractType construction/INI, parser/CRT/token/animation/vector/heap/growth services supplied. No full original base defaults/parser/startup, resource growth/spread, runtime or frame claim.'}
