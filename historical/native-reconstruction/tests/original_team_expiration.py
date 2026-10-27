# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete original Team34 dispatch; explicit supplied selection/RTTI/recipients."""
from original_presentation import PresentationOracle,STOP
from verify_team_expiration import verify,RANGES,TABLES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_EIP,UC_X86_REG_ESP
BASE=0x6800000;SIZE=0x10000;TEAM=BASE+0x1000;OTHER=BASE+0x1100;REC=tuple(BASE+0x2000+i*0x100 for i in range(4));SLOTS=BASE+0x3000;ALT=BASE+0x3100;VT=BASE+0x4000;STUB=BASE+0x5000
GLOBALS=(0x833680,0x833684);REG=0xac0c18
class TeamExpirationOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(BASE,SIZE);self.active=False;self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.write)
 def va(self,a):return a
 def word(self,a):return int.from_bytes(self.u.mem_read(a,4),'little')
 def pid(self,p):
  d={0:0,TEAM:1,OTHER:2,GLOBALS[0]:30,GLOBALS[1]:31,**{p:10+i for i,p in enumerate(REC)}};assert p in d,hex(p);return d[p]
 def event(self,k,a=0,b=0,c=0,d=0,e=0):self.trace.extend(map(str,(k,a,b,c,d,e)))
 def change(self,p,v,n=4):
  raw=(v&((1<<(8*n))-1)).to_bytes(n,'little');self.u.mem_write(p,raw)
  if BASE<=p<p+n<=BASE+SIZE:self.expected[p-BASE:p-BASE+n]=raw
 def mutate(self,where):
  if self.mutated or self.f[6]!=where:return
  self.mutated=1;self.event(9,where)
  if where==1:self.change(GLOBALS[0],TEAM);self.change(GLOBALS[1],OTHER);self.change(REG+16,4)
  if where==2:self.change(REG+4,ALT);self.change(REG+16,4);self.change(TEAM+0x14,255,1)
  if where==3:self.change(REG+16,0)
  if where==4:self.change(REG+4,ALT);self.change(REG+16,4)
  if where==5:self.change(SLOTS+4,REC[3])
 def write(self,u,access,a,n,v,_):
  if not self.active:return
  if a in GLOBALS:assert n==4 and v==0;self.event(1,self.pid(a),0,4,0);return
  if BASE<=a<a+n<=BASE+SIZE:raise AssertionError(('Unexpected Team expiration store',hex(a),n))
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  if any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()):return
  sp=u.reg_read(UC_X86_REG_ESP);obj=u.reg_read(UC_X86_REG_ECX);arg=lambda i:self.word(sp+4+i*4);pop=0
  if a==0x498f10:
   assert obj==0x8324e0 and arg(0)==0;self.event(2);self.mutate(1);pop=4
  elif a==0x783ce4:
   assert [arg(i) for i in range(5)]==[TEAM,0,0x7ce240,0x7ce260,0];self.event(3,1);self.mutate(2)
  elif a==STUB:
   assert obj in REC and arg(0)==TEAM and arg(1)==self.f[4]&0xffffffff;self.event(4,self.pid(obj),1,arg(1));self.mutate(3);self.mutate(4);self.mutate(5);pop=8
  else:raise AssertionError(('Uninspected Team expiration instruction',hex(a)))
  u.reg_write(UC_X86_REG_EAX,0);u.reg_write(UC_X86_REG_EIP,self.word(sp));u.reg_write(UC_X86_REG_ESP,sp+4+pop)
 def run(self,f):
  self.f=f;self.trace=[];self.mutated=0;u=self.u;u.mem_write(BASE,b'\x5a'*SIZE);self.put(TEAM,0x7ac950);u.mem_write(TEAM+0x14,bytes([f[2]]))
  for a,v in zip(GLOBALS,f[:2]):self.put(a,(0,TEAM,OTHER)[v])
  for i,p in enumerate(REC):self.put(p,VT);self.put(SLOTS+4*i,p);self.put(ALT+4*i,REC[3-i])
  self.put(VT+0x28,STUB);self.put(REG+4,SLOTS);self.put(REG+16,f[3]);self.expected=bytearray(u.mem_read(BASE,SIZE));self.active=True
  try:
   for _ in range(f[5]):self.checked_call(0x6ecb90,ecx=TEAM,edx=f[4],writes=[*( (a,4) for a in GLOBALS)],inputs=[*RANGES.items(),*TABLES.items(),(VT,44)])
  finally:self.active=False
  assert u.mem_read(BASE,SIZE)==self.expected,'Team expiration changed unrelated arena'
  final=[self.mutated,*[self.pid(self.word(a)) for a in GLOBALS],u.mem_read(TEAM+0x14,1)[0],self.word(REG+16)]
  for p in (SLOTS,ALT):final.extend(self.pid(self.word(p+4*i)) for i in range(4))
  return self.trace+['F',*map(str,final)]
