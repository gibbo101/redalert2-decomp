# SPDX-License-Identifier: GPL-3.0-or-later
"""Unchanged Type cost with actual House, E1 kind, base getter and FTOL."""
from collections import Counter
from original_presentation import PresentationOracle,STOP
from verify_techno_type_cost import RANGES,TABLES,KIND
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EIP
BASE=0x5e00000;SIZE=0x20000;HOUSE=BASE+0x1000;COUNTRY=BASE+0x7000;TYPE=BASE+0x8000;VT=BASE+0x9000
class TechnoTypeCostOracle(PresentationOracle):
 def __init__(self,exe):
  super().__init__(exe,allow_patched=True);self.u.mem_map(BASE,SIZE);self.active=False;self.counts=Counter();self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.write)
 def va(self,a):return a
 def word(self,p):return int.from_bytes(self.u.mem_read(p,4),'little')
 def event(self,k,v=0):self.trace.extend(map(str,(k,v&0xffffffff)))
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  assert a==KIND or any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected Type-cost instruction',hex(a))
  if a in RANGES:self.counts[hex(a)]+=1
  ecx=u.reg_read(UC_X86_REG_ECX);sp=u.reg_read(UC_X86_REG_ESP)
  if a==0x4f5960:assert ecx==HOUSE and self.word(sp+4)==TYPE;self.event(2)
  elif a in (0x50af60,KIND):
   assert ecx==TYPE;self.event(3,self.f[1]);self.kindCalls+=1
   if a==KIND:
    assert self.f[1]!=16;u.reg_write(UC_X86_REG_EAX,self.f[1]&0xffffffff);u.reg_write(UC_X86_REG_EIP,self.word(sp));u.reg_write(UC_X86_REG_ESP,sp+4)
  elif a==0x6dace0:assert ecx==TYPE;self.event(4,self.f[3]);self.baseCalls+=1
  elif a==0x77f110:self.event(6)
 def write(self,u,access,p,n,v,_):
  if self.active and u.reg_read(UC_X86_REG_EIP)==0x6dad46:
   assert n==4;self.factor=v&0xffffffff;self.event(5,self.factor)
 def run(self,f):
  self.f=f;u=self.u;u.mem_write(BASE,b'\x5a'*SIZE);self.put(TYPE,VT);self.put(VT+0x2c,0x50af60 if f[1]==16 else KIND);self.put(VT+0xac,0x6dace0);self.put(TYPE+0x550,f[3]);self.put(TYPE+0xba0,f[2]);self.put(HOUSE+0x34,COUNTRY)
  for off,v in zip((0x114,0x118,0x11c,0x120,0x124),f[4:]):self.put(COUNTRY+off,v)
  self.trace=[];self.factor=0;self.kindCalls=self.baseCalls=0;self.active=True
  try:self.checked_call(0x6dad30,[HOUSE if f[0] else 0],TYPE,inputs=[(BASE,SIZE),*RANGES.items(),*TABLES.items()])
  finally:self.active=False
  return self.trace+['F',*map(str,(u.reg_read(UC_X86_REG_EAX)&0xffffffff,self.factor,self.kindCalls,self.baseCalls))]
