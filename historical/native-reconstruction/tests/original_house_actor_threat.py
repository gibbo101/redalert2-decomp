# SPDX-License-Identifier: GPL-3.0-or-later
"""Original complete grid and stock threat/type/kind children on shared owners."""
from original_house_threat import HouseThreatOracle,VTABLE,ARENA
from original_presentation import STOP
from verify_house_actor_threat import verify,RANGES
from verify_techno_threat import RANGES as ACTOR_RANGES
from unicorn.x86_const import UC_X86_REG_ECX
TYPE=ARENA+0x6b000;RULES=ARENA+0x6c000
class HouseActorThreatOracle(HouseThreatOracle):
 def __init__(self,exe):
  verify(exe.read_bytes());super().__init__(exe)
 def code(self,u,a,n,unused):
  if not self.active or a==STOP:return
  if any(lo<=a and a+n<=lo+size for lo,size in ACTOR_RANGES.items()):
   if a in ACTOR_RANGES:
    self.counts[hex(a)]+=1
    if a!=0x4532f0:self.trace.extend(map(str,('E',self.aid(u.reg_read(UC_X86_REG_ECX)),a)))
   return
  super().code(u,a,n,unused)
 def checked_call(self,address,args,actor,**kwargs):
  assert address==0x4f3420
  for i,fields in enumerate(self.f['threats'],1):
   typeId,present,field=fields;p=self.ap(i);vt=VTABLE+0x400*i
   for off,value in [(0,vt),(0x418,TYPE+0x100*(typeId-1) if present else 0),(0x5a8,TYPE+0x100*(typeId-1) if present else 0),(0x564,field)]:self.change(p+off,value)
   kind=self.f['actors'][i-1][3]
   for off,value in [(0x2a0,0x6d3e50),(0x80,0x6c12c0),(0x84,0x453c60 if kind==6 else 0x506950),(0x2c,0x453c40 if kind==6 else 0x509800),(0x1a4,ARENA+0x68020)]:self.change(vt+off,value)
  for i,value in enumerate(self.f['types']):self.change(TYPE+0x100*i+0x598,value)
  self.change(RULES+0xbe8,self.f['rule']);self.put(0x839848,RULES);before=bytes(self.u.mem_read(0x839848,4))
  kwargs['inputs']=[*kwargs['inputs'],*ACTOR_RANGES.items()]
  super().checked_call(address,args,actor,**kwargs)
  assert bytes(self.u.mem_read(0x839848,4))==before
