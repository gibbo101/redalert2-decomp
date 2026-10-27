# SPDX-License-Identifier: GPL-3.0-or-later
"""Actual44C5A0 tail dispatcher joined to complete demand getters."""
import struct
from original_building_image import BuildingImageOracle,BASE,TYPE
from verify_building_image_selection import verify,ADDRESS,SIZE
from unicorn.x86_const import UC_X86_REG_ECX
ACTOR=BASE+0x8000
class BuildingImageSelectionOracle(BuildingImageOracle):
 def __init__(self,exe):
  super().__init__(exe);self.inspection=verify(exe.read_bytes())
 def run(self,f):
  self.stage,self.flag=f[:2]
  return super().run(f[2:])
 def checked_call(self,address,*args,**kwargs):
  assert address in (0x458ce0,0x45e790)
  for off,value,n in ((0x42c,self.stage,4),(0x5b4,self.flag,1),(0x418,TYPE,4)):
   self.mutation_write(ACTOR+off,(value&((1<<(n*8))-1)).to_bytes(n,'little'))
  self.mutation_write(TYPE,struct.pack('<I',0x79d1f8))
  kwargs['ecx']=ACTOR
  kwargs['inputs']=[*kwargs['inputs'],(ADDRESS,SIZE),(0x79d1f8+0x9c,4),(0x79d1f8+0xc0,4)]
  return super().checked_call(ADDRESS,*args,**kwargs)
 def code(self,u,a,n,context):
  if self.active and ADDRESS<=a and a+n<=ADDRESS+SIZE:
   if a==ADDRESS:self.counts[hex(a)]+=1
   return
  if self.active and a in (0x458ce0,0x45e790):assert u.reg_read(UC_X86_REG_ECX)==TYPE,'Tail receiver differs'
  return super().code(u,a,n,context)
 def read(self,u,access,p,n,v,context):
  if self.active and p in (ACTOR+0x42c,ACTOR+0x5b4,ACTOR+0x418):
   off=p-ACTOR;assert n==(1 if off==0x5b4 else 4)
   value=int.from_bytes(u.mem_read(p,n),'little');value=self.signed(value) if off==0x42c else (1 if off==0x418 else value)
   self.trace+=['Q',str(off),str(value)]
  return super().read(u,access,p,n,v,context)
