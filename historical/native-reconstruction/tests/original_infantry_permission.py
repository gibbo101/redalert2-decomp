# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete Infantry admission with actual direct permission and Foot override."""
import struct
from original_infantry_admission import InfantryAdmissionOracle
from original_unit_admission import OBJECTS,TYPES,CELLS,OUT
from verify_infantry_permission import RANGES
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_EIP,UC_X86_REG_ESP

class InfantryPermissionOracle(InfantryAdmissionOracle):
 def __init__(self,exe):
  super().__init__(exe);self.permissions=0;self.overrides=0;self.teams=0
 def prepare_motion(self):
  super().prepare_motion();train,flag,team,result,*shape=self.permission_options
  self.u.mem_write(TYPES[0]+0xaa0,bytes([train]));self.u.mem_write(OBJECTS[0]+0x32c,bytes([flag]))
  self.put(OBJECTS[0]+0x4c4,OUT+0x100 if team else 0)
  for offset,value in zip((0xf0,0xf8,0xfc,0x100,0x104),shape):self.put(0x8324e0+offset,value)
 def extra_inputs(self):
  return [*super().extra_inputs(),*RANGES.items(),(0x7a3540+0x80,8),(0x7a3540+0x16c,4),(0x7a3540+0x2f4,4),*[(0x8324e0+o,4) for o in (0xf0,0xf8,0xfc,0x100,0x104)]]
 def code(self,u,a,n,ctx):
  if not self.active:return
  sp=u.reg_read(UC_X86_REG_ESP);ecx=u.reg_read(UC_X86_REG_ECX)
  if 0x50334d<=a<0x50337c:self.instructions.add(a);return
  if a==0x6ba990:
   assert ecx==OUT+0x100;self.teams+=1;self.event('q',0,self.permission_options[3]);
   u.reg_write(UC_X86_REG_EAX,self.permission_options[3]);u.reg_write(UC_X86_REG_EIP,self.word(sp));u.reg_write(UC_X86_REG_ESP,sp+4);return
  if any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()):
   self.instructions.add(a)
   if a==0x55a740:
    assert ecx==0x8324e0 and self.word(sp+8)==1
    self.permissions+=1;self.event('B',CELLS.index(self.word(sp+4)),1)
   elif a==0x4c8ca0:
    assert ecx==OBJECTS[0];self.overrides+=1;self.event('b',0)
   return
  return super().code(u,a,n,ctx)
 def run_permission(self,options,parsed):
  self.permission_options=options
  return self.run_infantry(*parsed)
