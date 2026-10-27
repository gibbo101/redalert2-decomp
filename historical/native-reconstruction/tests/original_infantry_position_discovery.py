# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete original Infantry position/discovery in a shared guest owner graph."""
import struct
from original_infantry_position_effects_e1 import InfantryPositionEffectsE1Oracle,ACTOR,HOUSE
from verify_infantry_position_discovery import verify,CHILDREN
from unicorn.x86_const import UC_X86_REG_ECX,UC_X86_REG_ESP

class InfantryPositionDiscoveryOracle(InfantryPositionEffectsE1Oracle):
 def __init__(self,exe):
  super().__init__(exe);self.inspection=verify(exe.read_bytes());self.in_discovery=False
 def code(self,u,a,n,ctx):
  if not self.active:return
  if a==0x6c2c22:self.in_discovery=False
  if a==0x6c2440:
   assert u.reg_read(UC_X86_REG_ECX)==ACTOR and self.word(u.reg_read(UC_X86_REG_ESP)+4)==HOUSE
   self.in_discovery=True;self.trace.extend(('d','0'));self.counts['discovery']+=1
  if self.in_discovery:
   if not any(lo<=a and a+n<=lo+size for lo,size in CHILDREN.items()):raise AssertionError(('Uninspected discovery child',hex(a)))
   if a==0x5d4230:self.trace.extend(('b','0'))
   elif a==0x4f52f0:self.trace.extend(('h','0'))
   elif a==0x594770:self.trace.extend(('g','0'))
   elif a==0x594cb0:
    assert self.word(u.reg_read(UC_X86_REG_ESP)+4)==15 and self.word(u.reg_read(UC_X86_REG_ESP)+8)==0
    self.trace.extend(('q','15'));self.counts['queue']+=1
   return
  super().code(u,a,n,ctx)
 def store(self,u,access,p,n,value,ctx):
  super().store(u,access,p,n,value,ctx)
  if not self.active:return
  if p in (ACTOR+0x373,ACTOR+0xa0,ACTOR+0xa4,HOUSE+0x13c,HOUSE+0x5668,HOUSE+0x5669):
   assert n==(4 if p==ACTOR+0xa0 else 1)
   who,off=(0,p-ACTOR) if ACTOR<=p<ACTOR+0x700 else (1,p-HOUSE)
   self.trace.extend(map(str,('W',who,off,value&((1<<(8*n))-1))))
 def checked_call(self,*args,**kwargs):
  f=self.fixture;u=self.u
  u.mem_write(ACTOR+0x373,bytes([f['discovered']]));u.mem_write(ACTOR+0x372,bytes([f['field372']]))
  self.put(ACTOR+0x98,f['mission']);self.put(ACTOR+0xa0,-1);u.mem_write(ACTOR+0xa4,b'\xff')
  u.mem_write(self.expected_cell+0x12c,bytes([f['revealed']]))
  u.mem_write(HOUSE+0x134,bytes([f['human']]));u.mem_write(HOUSE+0x135,b'\0')
  for off in (0x13c,0x5668,0x5669):u.mem_write(HOUSE+off,b'\0')
  self.put(0xa35db4,HOUSE);self.put(0xa3d298,0);self.put(0xa40774,f['loading'])
  kwargs['writes'] += [(ACTOR+0x373,1),(ACTOR+0xa0,4),(ACTOR+0xa4,1),(HOUSE+0x13c,1),(HOUSE+0x5668,2)]
  return super().checked_call(*args,**kwargs)
 def run(self,f):
  self.fixture=f;self.in_discovery=False;result=super().run(f)
  # Parent observer exposes actual current Mission instead of fixture's old constant2.
  result.extend(('Y',str(self.u.mem_read(ACTOR+0x373,1)[0]),str(self.signed(self.word(ACTOR+0xa0))),str(self.u.mem_read(ACTOR+0xa4,1)[0]),str(self.u.mem_read(HOUSE+0x13c,1)[0]),*map(str,self.u.mem_read(HOUSE+0x5668,2))))
  return result
