#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin the ground Unit consumer, initialized Drive pose and actual floor queries."""
import hashlib,struct,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_unit_voxel_shadow_world import verify as shadow
from verify_prepared_unit_world import verify as prepared
from verify_drive_shadow_pose import verify as drive,RANGES as DRIVE_RANGES
from verify_map_floor_height import verify as floor,RANGES as FLOOR_RANGES
RANGES={**DRIVE_RANGES,**FLOOR_RANGES}
def verify(disc,data):
 result={'shadow':shadow(disc,data),'prepared':prepared(disc,data),'drive':drive(data),'floor':floor(data)}
 p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32)
 calls={0x700274:'dword ptr [ecx + 0x28]',0x70033f:'dword ptr [eax + 0x1b0]',
  0x7003dc:'dword ptr [eax + 0x54]',0x70041a:'dword ptr [edx + 0x1b0]',0x70043b:'dword ptr [eax + 0x1b0]'}
 for a,target in calls.items():
  i=next(cs.disasm(p.get_data(a-0x400000,8),a))
  if i.mnemonic!='call' or i.op_str!=target:raise ValueError('Ground Unit virtual consumer differs')
 if p.get_data(0x7addf8+0x1b0-0x400000,4)!=struct.pack('<I',0x5d4810):raise ValueError('Unit relative-height dispatch differs')
 result['virtual_consumers']={hex(a):v for a,v in calls.items()}
 result['scope']='Complete ordinary ground Track Unit drawing on shared finalized Cells, actual stock numeric/matrix initialization, current-ramp shadow pose, repeated actual floor-relative height and complete lit/shadow pixels/cache/pool/cleanup. Lit locomotor records remain flat/settled; relative height <=0, no bridge/add14/type alternate, sufficient pool. Actor placement/update, full startup/runtime/frame parity excluded; earlier flat guards unchanged.'
 return result
