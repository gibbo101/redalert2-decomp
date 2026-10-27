#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin stock numeric roots, complete table leaves and bounded original CRT regions."""
import hashlib,struct,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from compare_original import PATCHED_EXPECTED
from verify_voxel_ramp_shadow import RANGES as SHADOW_RANGES,verify as verify_shadow
SHADOW_ROOTS={0x717ce0:40,0x717d10:19,0x717d30:19,0x717d50:19,
 0x717d70:19,0x717d90:19,0x717db0:49,0x717df0:33,0x717e20:44,0x717e50:39}
CELL_ROOTS={0x470490:40,0x4704c0:19,0x4704e0:19,0x470500:19,
 0x470520:19,0x470540:19,0x470560:49,0x4705a0:33,0x4705d0:44,0x470600:39}
LEAVES={0x4ba520:44,0x4ba5b0:66}
# Whole inspected regions, including alternate branches. Only the fixed positive
# 256^2 path executes. Error dispatch outside these regions must be rejected.
CRT={0x7821b0:0x21d,0x787620:0x2c,0x787665:0x43,0x7876be:13,0x787709:0xa3}
RANGES={**SHADOW_ROOTS,**CELL_ROOTS,**LEAVES,**CRT,**SHADOW_RANGES}
SHADOW_GLOBALS={0xaf7388:8,0xaf8600:8,0xaf8530:8,0xaf7928:8,0xaf7390:8,
 0xaf7368:8,0xaf89f8:4,0xaf7398:8,0xaf77a0:8,0xaf85f8:4}
CELL_GLOBALS={0x850be0:8,0x850c38:8,0x850c28:8,0x850c20:8,0x850be8:8,
 0x850bb0:8,0x850c40:4,0x850bf8:8,0x850c10:8,0x850c30:4}
CONSTANTS={0x79a6f8:2.,0x79a700:256.,0x79a708:1.,0x79a710:45.,
 0x79a718:60.,0x79a720:90.,0x79a728:.5,0x79a730:1/256,
 0x7aea20:60.,0x7aea28:0.017453292519943295,
 0x79dac0:60.,0x79dac8:0.017453292519943295,0x7a0f80:651.8986469044033}
TABLES={0x80fde4:4096*4,0x813df4:4097*4,0x817df8:4,0x7a0f8c:4}
def verify(data):
 if hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact supplied engine required')
 p=pefile.PE(data=data);shadow=verify_shadow(data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ranges={}
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(cs.disasm(raw,a))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!=('jmp' if a==0x787709 else 'ret'):
   raise ValueError('Geometry inspected range boundary differs')
  ranges[hex(a)]={'bytes':n,'instructions':len(ins),'sha256':hashlib.sha256(raw).hexdigest(),
   'kind':'bounded_CRT_region' if a in CRT else 'complete_root_or_leaf'}
 for a,value in CONSTANTS.items():
  if p.get_data(a-0x400000,8)!=struct.pack('<d',value):raise ValueError('Geometry constant differs')
 return {'ranges':ranges,'constants':{hex(a):n for a,n in CONSTANTS.items()},
  'tables':{hex(a):{'bytes':n,'sha256':hashlib.sha256(p.get_data(a-0x400000,n)).hexdigest()} for a,n in TABLES.items()},
  'shadow_inspection':shadow,
  'scope':'Two distinct stock ten-root numeric chains, actual fixed 256^2 CRT path, table sqrt/tan/atan and all 21 final shadow matrices. 53-bit/toward-zero entry, CRT flag zero and output storage supplied. Final values and selected original writes compared/audited; no full startup ordering, general CRT pow, actor/Drive/runtime/frame claim.'}
