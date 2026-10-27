# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete original6D7C80 with explicit mutable named Foot services."""
from collections import Counter
from original_presentation import PresentationOracle,STOP
from verify_techno_reference_cleanup import RANGES,SERVICES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESI,UC_X86_REG_EBP,UC_X86_REG_ESP,UC_X86_REG_EIP
BASE=0x5f00000;SIZE=0x20000;SUBJECT=BASE+0x100;OTHER=BASE+0x200;VT=BASE+0x1000;SLOTS=BASE+0x2000;ALT=BASE+0x2100;TEAMS=BASE+0x2200
FEET=tuple(BASE+0x4000+i*0x1000 for i in range(4));TEAM=tuple(BASE+0x8000+i*0x100 for i in range(4))
FC=0xa40c30;FB=0xa40c24;TC=0x866188;TB=0x86617c
class TechnoReferenceCleanupOracle(PresentationOracle):
 def __init__(self,exe):
  super().__init__(exe,allow_patched=True);self.u.mem_map(BASE,SIZE);self.active=False;self.counts=Counter();self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.write)
 def va(self,a):return a
 def word(self,p):return int.from_bytes(self.u.mem_read(p,4),'little')
 def pid(self,p):
  if not p:return 0
  if p==SUBJECT:return 1
  if p==OTHER:return 2
  if p in FEET:return 10+FEET.index(p)
  if p in TEAM:return 20+TEAM.index(p)
  raise AssertionError(hex(p))
 def event(self,k,a=0,b=0,c=0,d=0):self.trace.extend(map(str,(k,a&0xffffffff,b&0xffffffff,c&0xffffffff,d&0xffffffff)))
 def fixture(self,p,v,n=4):
  raw=(v&((1<<(8*n))-1)).to_bytes(n,'little');self.u.mem_write(p,raw)
  if BASE<=p<BASE+SIZE:self.expected[p-BASE:p-BASE+n]=raw
 def ret(self,sp,n,v=0):
  self.u.reg_write(UC_X86_REG_EAX,v);self.u.reg_write(UC_X86_REG_EIP,self.word(sp));self.u.reg_write(UC_X86_REG_ESP,sp+4+n)
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  assert a in SERVICES or any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),hex(a)
  if a in RANGES or a in SERVICES:self.counts[hex(a)]+=1
  sp=u.reg_read(UC_X86_REG_ESP);foot=u.reg_read(UC_X86_REG_ECX)
  if a==0x6d7c9d:self.event(6,u.reg_read(UC_X86_REG_EBP),self.pid(u.reg_read(UC_X86_REG_ESI)))
  if a in (0x6d7c9d,0x6d7cd0):
   p=u.reg_read(UC_X86_REG_ESI);self.event(5,self.pid(p),self.pid(self.word(p+0x228)))
  if a==0x6d7cbb:
   p=u.reg_read(UC_X86_REG_ESI);self.event(8,self.pid(p),self.word(p+0x98))
  if a==0x6d7cfc:self.event(7,u.reg_read(UC_X86_REG_ECX),self.pid(u.reg_read(UC_X86_REG_EAX)))
  if a==SERVICES[0]:
   assert foot in FEET;self.event(2,self.pid(foot));mode=self.f[6]
   if mode==1:self.fixture(foot+0x228,0)
   if mode==2:self.fixture(foot+0x90,2);self.fixture(foot+0x98,25)
   if mode==3:self.fixture(FB,ALT);self.fixture(FC,0);self.fixture(TC,2)
   if mode==4:self.fixture(foot+0x228,OTHER)
   if mode==5:self.fixture(TC,0xffffffff)
   self.ret(sp,0)
  elif a==SERVICES[1]:assert foot in FEET;value=self.word(foot+0x90);self.event(3,self.pid(foot),value);self.ret(sp,0,value)
  elif a==SERVICES[2]:assert foot in FEET and self.word(sp+4)==0;self.event(4,self.pid(foot));self.fixture(foot+0x228,0);self.ret(sp,4)
 def write(self,u,access,p,n,v,_):
  if not self.active:return
  raw=(v&((1<<(8*n))-1)).to_bytes(n,'little')
  if BASE<=p and p+n<=BASE+SIZE:self.expected[p-BASE:p-BASE+n]=raw
  for foot in FEET:
   if p in (foot+0xa8,foot+0x5ba):self.event(1,self.pid(foot),p-foot)
  for team in TEAM:
   if p in (team+0x3c,team+0x40):self.event(1,self.pid(team),p-team)
 def run(self,f):
  self.f=f;u=self.u;u.mem_write(BASE,b'\x5a'*SIZE);subject=SUBJECT if f[2] else 0
  for off,service in zip((0x1e0,0x2c,0x370),SERVICES):self.put(VT+off,service)
  for i,p in enumerate(FEET):
   for off,v in ((0,VT),(0x228,subject if f[3]>>i&1 else OTHER),(0x90,2 if f[4]>>i&1 else 15),(0x98,25 if f[5]>>i&1 else 5),(0xa8,0x89abcdef)):self.put(p+off,v)
   u.mem_write(p+0x5ba,b'\x80');self.put(SLOTS+4*i,FEET[i%2 if f[7] else i]);self.put(ALT+4*i,FEET[3-i]);self.put(TEAMS+4*i,TEAM[i%2 if f[9] else i])
  for i,p in enumerate(TEAM):
   self.put(p+0x3c,subject if f[8]>>(2*i)&1 else OTHER);self.put(p+0x40,subject if f[8]>>(2*i+1)&1 else OTHER)
  for p,v in ((FC,f[0]),(FB,SLOTS),(TC,f[1]),(TB,TEAMS)):self.put(p,v)
  self.expected=bytearray(u.mem_read(BASE,SIZE));self.trace=[];self.active=True
  try:self.checked_call(0x6d7c80,ecx=subject,writes=[*[(p+0xa8,4) for p in FEET],*[(p+0x5ba,1) for p in FEET],*[(p+0x3c,8) for p in TEAM]],inputs=[*RANGES.items(),(VT,0x380),(TB,4),(SLOTS,16),(ALT,16),(TEAMS,16)])
  finally:self.active=False
  assert bytes(u.mem_read(BASE,SIZE))==self.expected,'Unrelated reference arena changed'
  final=[self.word(FC),self.word(TC),int(self.word(FB)==ALT)]
  for p in FEET:final.extend((self.pid(self.word(p+0x228)),self.word(p+0x90),self.word(p+0x98),self.word(p+0xa8),int(u.mem_read(p+0x5ba,1)[0])))
  for p in TEAM:final.extend((self.pid(self.word(p+0x3c)),self.pid(self.word(p+0x40))))
  return self.trace+['F',*map(str,final)]
