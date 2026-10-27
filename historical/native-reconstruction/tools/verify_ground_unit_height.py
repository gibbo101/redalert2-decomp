#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin the ordinary Unit's positive/nonpositive relative-height shadow paths."""
import hashlib,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_ground_unit_world import verify as ground
def verify(disc,data):
 result={'ground':ground(disc,data)}
 p=pefile.PE(data=data);c=Cs(CS_ARCH_X86,CS_MODE_32)
 start,size=0x700415,0x170
 blob=p.get_data(start-0x400000,size);ins=list(c.disasm(blob,start));by={i.address:i for i in ins}
 if sum(i.size for i in ins)!=size or ins[-1].address!=0x700580 or ins[-1].mnemonic!='call':raise ValueError('Incomplete height shadow branches')
 operands={0x70041a:('call','dword ptr [edx + 0x1b0]'),0x700422:('jg','0x70042e'),
  0x700424:('or','dword ptr [esp + 0x14], 0x80000000'),0x70042e:('mov','dword ptr [esp + 0x14], 0xffffffff'),
  0x70043b:('call','dword ptr [eax + 0x1b0]'),0x700449:('jle','0x7004e6'),
  0x700481:('call','dword ptr [ecx + 0x30]'),0x700484:('mov','eax, dword ptr [eax + 4]'),
  0x700489:('inc','eax'),0x700491:('call','dword ptr [ecx + 0x30]'),
  0x700494:('mov','eax, dword ptr [eax]'),0x7004ad:('call','0x717f90'),0x7004bb:('call','0x591180'),
  0x700518:('call','dword ptr [edx + 0x30]'),0x70051b:('mov','ecx, dword ptr [eax + 4]'),
  0x700527:('call','dword ptr [edx + 0x30]'),0x70052a:('mov','ecx, dword ptr [eax]'),
  0x700543:('call','0x717f90'),0x700551:('call','0x591180'),0x700580:('call','0x4c9a40')}
 for a,want in operands.items():
  if a not in by or (by[a].mnemonic,by[a].op_str)!=want:raise ValueError('Unit height/shadow operand differs')
 result['height_shadow_branch']={'start':hex(start),'bytes':size,'instructions':len(ins),'sha256':hashlib.sha256(blob).hexdigest(),
  'operands':{hex(a):list(v) for a,v in operands.items()}}
 result['scope']='Complete ground Unit/shadow world drawing with actual relative floor height, positive/nonpositive key and stencil origin decisions. Lit locomotor state flat/settled; actor absolute Z and initial records supplied. No movement/body-ramp/startup/runtime/frame proof.'
 return result
