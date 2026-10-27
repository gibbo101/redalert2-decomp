#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin complete Unit/world drawing on the same guest's finalized map records."""
import hashlib
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_unit_voxel_world import verify as world
from verify_prepared_foot_depth import verify as prepared,RANGES as MAP_RANGES
LOOKUP=0x548000
LOOKUP_SIZE=0x68
def verify(disc,data):
 result={'world':world(disc,data),'prepared':prepared(data)}
 p=pefile.PE(data=data);raw=p.get_data(LOOKUP-0x400000,LOOKUP_SIZE);ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(raw,LOOKUP))
 if sum(i.size for i in ins)!=LOOKUP_SIZE or ins[-1].mnemonic!='ret' or ins[-1].op_str!='4':raise ValueError('Incomplete coordinate map lookup')
 result['coordinate_lookup']={'patched_va':hex(LOOKUP),'bytes':LOOKUP_SIZE,'instructions':len(ins),'sha256':hashlib.sha256(raw).hexdigest()}
 result['scope']='Complete healthy current-Cell-ramp-zero Track Unit/cache/raster/staging/pool/Foot/ordinary base/TMP/final RGB565 surface after actual shared map/floor finalization. Initial map/type/actor/absolute Z, neutral relative-height service, contact/house/planes/palettes/camera and shadow observation remain supplied. No placement/update, startup/ownership, shadow pixels, runtime or whole-frame claim.'
 return result
