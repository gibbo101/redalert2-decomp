#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin Foot predicates/wrappers joined to prepared Cells and actual Unit base."""
import struct,pefile
from verify_unit_base_depth import verify as parent,RANGES as PARENT_RANGES
from verify_foot_depth import verify as foot,RANGES as FOOT_RANGES,TAILS
RANGES={**PARENT_RANGES,**FOOT_RANGES,**TAILS}
def verify(data):
 p=parent(data);f=foot(data);im=pefile.PE(data=data).get_memory_mapped_image()
 for off,target in ((0x80,0x6c12c0),(0x84,0x705020)):
  if struct.unpack_from('<I',im,0x7addf8+off-0x400000)[0]!=target:raise ValueError('Prepared Foot type dispatch differs')
 return {'parent':p,'foot':f,'allowed_ranges':[hex(a) for a in RANGES],
  'scope':'Complete Foot depth/gradient, actual Drive/type/coordinate/five predicates and ordinary Unit base on same finalized map Cells/TMP. Nonbridge kind1/special-zero/nonharvester; empty tube registry; dimensions require available image. Actor/type/Facing/absolute Z/globals remain supplied; no actor placement/update, startup, Unit-world/runtime or full-frame claim.'}
