#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin the one-guest prepared movement -> posed complete Unit drawing boundary."""
import hashlib,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_ground_unit_height import verify as height
from verify_prepared_drive_state import verify as movement,RANGES

def verify(disc,data):
 result={'height':height(disc,data),'movement':movement(data)}
 pe=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32)
 a,n=0x6ffc14,0x1bb;raw=pe.get_data(a-0x400000,n);ins=list(cs.disasm(raw,a));by={i.address:i for i in ins}
 if sum(i.size for i in ins)!=n or ins[-1].address!=0x6ffdcd:raise ValueError('Incomplete posed part span')
 for address,operand in ((0x6ffc1f,'0x4b8be0'),(0x6ffc4f,'0x4b8be0'),(0x6ffc7f,'0x5909a0'),
   (0x6ffd17,'0x5900f0'),(0x6ffd27,'0x4b8be0'),(0x6ffd55,'0x590880'),(0x6ffd66,'0x5900f0')):
  if by[address].mnemonic!='call' or by[address].op_str!=operand:raise ValueError('Posed Unit consumer differs')
 result['posed_part_span']={'start':hex(a),'bytes':n,'instructions':len(ins),'sha256':hashlib.sha256(raw).hexdigest()}
 result['scope']='One guest: shared finalized Cells, stock numeric/matrix/quaternion setup, SetHeight/Unlimbo and complete ordinary Process; live actor/Facing/stored-ramp body, separate current-Cell shadow and repeated relative heights feed complete Unit/cache/raster/staging/depth/RGB565 drawing. Initial actor/type/routes/speeds/rocking and Mark/admission/occupation/mission, camera/contact/palettes/planes supplied. No startup/cache lifecycle/runtime/full-frame claim.'
 return result
