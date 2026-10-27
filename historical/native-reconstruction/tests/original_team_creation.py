# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete TeamType factory, optionally entered through actual action4."""
import struct
from collections import Counter
from original_presentation import PresentationOracle,STOP
from verify_team_creation import RANGES,TABLES
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EIP
BASE=0x4f00000;SIZE=0x10000;TYPE=BASE+0x1000;HOUSE1=BASE+0x2000;HOUSE2=BASE+0x3000;RECORD=BASE+0x4000;OTHER=BASE+0x5000;ACTION=BASE+0x6000
SERVICES=(0x4068f0,0x4f35f0,0x782017,0x6b7430)
def signed(v):return (v+2**31)%2**32-2**31
class TeamCreationOracle(PresentationOracle):
 def __init__(self,exe):
  super().__init__(exe,allow_patched=True);self.u.mem_map(BASE,SIZE);self.active=False;self.counts=Counter();self.u.hook_add(UC_HOOK_CODE,self.code)
 def va(self,a):return a
 def word(self,p):return int.from_bytes(self.u.mem_read(p,4),'little')
 def pid(self,p):
  assert p in (0,HOUSE1,HOUSE2,RECORD,OTHER),hex(p)
  return (0,HOUSE1,HOUSE2,RECORD,OTHER).index(p)
 def event(self,k,a=0,b=0,c=0,d=0,e=0):self.trace.extend(map(str,(k,a,b,c,d,e)))
 def mutate(self,at):
  if self.mutated or self.f[9]!=at:return
  self.mutated=True;self.event(6,at)
  if at==1:self.put(0xa40774,0);self.put(TYPE+0xc0,HOUSE2);self.put(TYPE+0xb8,0)
  if at==2:self.put(TYPE+0xb8,-2147483647)
  if at==3:self.put(TYPE+0xc0,HOUSE2)
  if at==4:self.put(0xa40774,0xffffffff)
  if at==5:self.put(0xa40774,0)
  self.expected=bytes(self.u.mem_read(BASE,SIZE))
 def ret(self,sp,n,value=0):
  self.u.reg_write(UC_X86_REG_EAX,value&0xffffffff);self.u.reg_write(UC_X86_REG_EIP,self.word(sp));self.u.reg_write(UC_X86_REG_ESP,sp+4+n)
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  assert a in SERVICES or any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected team creation instruction',hex(a))
  if a in RANGES:self.counts[hex(a)]+=1
  if a in (0x6becc8,0x6bed07):self.event(7,self.pid(u.reg_read(UC_X86_REG_EAX)))
  if a==0x6becb2:self.counts['limit_session_branch']+=1
  sp=u.reg_read(UC_X86_REG_ESP);ecx=u.reg_read(UC_X86_REG_ECX)
  if a==0x4068f0:
   self.logs+=1
   if self.logs==1:assert self.word(sp+4)==0x7f6e64;self.event(1,self.word(0xa40774));self.mutate(1)
   else:assert self.word(sp+4)==0x7f6e40 and self.word(sp+8)==TYPE+0x64;self.event(2);self.mutate(3)
   self.ret(sp,0)
  elif a==0x4f35f0:
   self.event(3,self.pid(ecx));assert self.word(sp+4)==TYPE;self.mutate(2);self.ret(sp,4,self.f[10])
  elif a==0x782017:
   self.event(4,self.word(sp+4));self.mutate(4);self.ret(sp,0,RECORD if self.f[7] else 0)
  elif a==0x6b7430:
   assert ecx==RECORD and self.word(sp+4)==TYPE;self.event(5,3,self.pid(self.word(sp+8)),self.word(sp+12));self.mutate(5);self.ret(sp,12,(0,RECORD,OTHER)[self.f[8]])
 def run(self,f):
  self.f=f;self.logs=0;self.mutated=False;self.trace=[];u=self.u;u.mem_write(BASE,b'\x5a'*SIZE)
  self.put(TYPE+0xc0,(0,HOUSE1,HOUSE2)[f[5]]);self.put(TYPE+0xb8,f[3]);self.put(TYPE+0xd4,f[4]);u.mem_write(TYPE+0x64,b'fixture\0');self.put(0xa40774,f[1]);self.put(0xa3d298,f[2]);self.put(ACTION+0x2c,4);self.put(ACTION+0x30,TYPE)
  self.expected=bytes(u.mem_read(BASE,SIZE));self.active=True;before_limits=self.counts['limit_session_branch']
  try:
   if f[0]:self.checked_call(0x6adae0,[0,0,ACTION+0x100,ACTION+0x80],ACTION,writes=[(0xa40774,4)],inputs=[*RANGES.items(),*TABLES.items(),(ACTION,0x100)])
   else:self.checked_call(0x6bec80,[(0,HOUSE1,HOUSE2)[f[6]]],TYPE,writes=[],inputs=[*RANGES.items(),(ACTION,0x100)])
  finally:self.active=False
  if f[0] and f[1]==0 and f[9]!=1:assert before_limits==self.counts['limit_session_branch'],'Action4 loading1 unexpectedly entered limits'
  assert self.expected==u.mem_read(BASE,SIZE),'Team factory mutated unrelated arena'
  result=(u.reg_read(UC_X86_REG_EAX)&255) if f[0] else self.pid(u.reg_read(UC_X86_REG_EAX))
  self.trace.extend(['F',str(result),str(self.word(0xa40774)),str(signed(self.word(TYPE+0xb8))),str(signed(self.word(TYPE+0xd4))),str(self.pid(self.word(TYPE+0xc0))),str(int(self.mutated))]);return self.trace
