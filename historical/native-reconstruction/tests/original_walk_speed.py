# SPDX-License-Identifier: GPL-3.0-or-later
"""Actual speed and Infantry admission inside the same complete queued Process."""
import struct
from original_walk_admission import WalkAdmissionOracle,TYPE
from original_infantry_subcell import ARENA,ACTOR,HOUSE
from original_presentation import STOP
from verify_infantry_speed import RANGES,TABLES
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP
COUNTRY=ARENA+0x2400;RULES=ARENA+0x3800
class WalkSpeedOracle(WalkAdmissionOracle):
 def __init__(self,exe):
  self.speed_ready=False;self.in_speed=False;super().__init__(exe);self.speed_ready=True
 def checked_call(self,root,*args,**kwargs):
  if self.speed_ready and root==0x71dff0:
   if self.prepare_speed:
    u=self.u;o=self.speed_options
    for p,value in ((TYPE,0x7a3a78),(TYPE+0x5a0,self.speed_base),(HOUSE+0x34,COUNTRY),(0x839848,RULES)):self.put(p,value)
    u.mem_write(COUNTRY+0x128,struct.pack('<I',o[0]))
    for p,value in ((ACTOR+0x470,o[1]),(ACTOR+0x118,o[2]),(RULES+0x598,o[3])):u.mem_write(p,struct.pack('<Q',value))
    for p,value in ((ACTOR+0x5c3,o[4]),(TYPE+0xc0b,o[5]),(TYPE+0x26c,o[6]),(TYPE+0x27e,o[7])):u.mem_write(p,bytes([value]))
    self.prepare_speed=False
   kwargs['inputs']=[*kwargs['inputs'],*RANGES.items(),*TABLES.items(),(0x839848,4)]
  return super().checked_call(root,*args,**kwargs)
 def code(self,u,a,n,ctx):
  if not self.speed_ready or not self.active or a==STOP:return super().code(u,a,n,ctx)
  if a==0x508980:
   assert u.reg_read(UC_X86_REG_ECX)==ACTOR;self.trace('S');self.in_speed=True;self.counts['actual_speed']+=1
  if not self.in_speed:return super().code(u,a,n,ctx)
  assert any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected joined speed instruction',hex(a))
  if a in RANGES:self.counts[hex(a)]+=1
  sp=u.reg_read(UC_X86_REG_ESP);ecx=u.reg_read(UC_X86_REG_ECX)
  if a==0x6c12c0:assert ecx==ACTOR;self.event('t',0)
  elif a==0x4f5a20:assert ecx==HOUSE and self.word(sp+4)==TYPE;self.event('h',0)
  elif a==0x6d7910:assert ecx==ACTOR and self.word(sp+4)==0;self.event('b',0)
  elif a==0x7133a0:assert ecx==ACTOR+0x118;self.event('v',0)
  elif a==0x713420:assert ecx==ACTOR+0x118;self.event('e',0)
  elif a==0x4c9b65:self.event('r',0)
  elif a==0x509800:assert ecx==ACTOR;self.event('k',0)
  elif a in (0x77f135,0x77f14c):
   x=u.reg_read(UC_X86_REG_EAX);self.event('c',x if x<2**31 else x-2**32)
  if a in (0x5089bb,0x5089c8):self.in_speed=False
 def run_speed_join(self,v,options,speed):
  self.speed_options=speed;self.speed_base=v[8];self.prepare_speed=True;self.in_speed=False;return self.run_joined(v,options)
