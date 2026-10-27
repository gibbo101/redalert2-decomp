# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete original Building eligibility with actual coordinate/project/math children."""
import struct
from collections import Counter
from original_presentation import PresentationOracle,STOP,STACK
from verify_building_visibility import verify,RANGES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_READ,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_ECX,UC_X86_REG_EAX,UC_X86_REG_ESP,UC_X86_REG_EIP
BASE=0x4500000;SIZE=0x10000;ACTOR=BASE+0x1000;INPUT=BASE+0x3000;TACTICAL=BASE+0x5000
class BuildingVisibilityOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(BASE,SIZE);self.active=False;self.counts=Counter()
  self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_READ,self.read);self.u.hook_add(UC_HOOK_MEM_WRITE,self.write)
 def va(self,a):return a
 def word(self,p):return int.from_bytes(self.u.mem_read(p,4),'little')
 def signed(self,v):return (v+2**31)%2**32-2**31
 def ints(self,p,v):self.u.mem_write(p,struct.pack('<'+'I'*len(v),*[x&0xffffffff for x in v]))
 def values(self,p,n):return [self.signed(self.word(p+4*i)) for i in range(n)]
 def event(self,k,field=-1,value=0,id=-1):self.trace.extend(map(str,(k,id,field,value)))
 def ret(self,pop,value=0):
  sp=self.u.reg_read(UC_X86_REG_ESP);self.u.reg_write(UC_X86_REG_EAX,value);self.u.reg_write(UC_X86_REG_EIP,self.word(sp));self.u.reg_write(UC_X86_REG_ESP,sp+4+pop)
 def mutation_write(self,p,b):
  self.u.mem_write(p,b)
  if BASE<=p<BASE+SIZE:self.expected[p-BASE:p-BASE+len(b)]=b
 def mutate(self,point):
  m=self.mode
  if self.mutated or not m:return
  if m in (1,3) and point!=1 or m in (2,5) and point!=2 or m==4 and point!=3:return
  self.mutated=True;self.event(10,value=m)
  def ints(p,v):self.mutation_write(p,struct.pack('<'+'I'*len(v),*[x&0xffffffff for x in v]))
  if m==1:ints(0x839630,[17,-23,200,300])
  if m==2:ints(0x839630,[9,-11,200,300]);ints(TACTICAL+0xb0,[7,-13])
  if m==3:ints(ACTOR+0x88,[512,256,728]);self.mutation_write(ACTOR+0x5b7,b'\xff')
  if m==5:self.mutation_write(ACTOR+0x5b7,b'\xff');self.mutation_write(ACTOR+0x76,b'\xff')
  if m==4:ints(self.clip,[21,22,23,24]);self.mutation_write(ACTOR+0x75,b'\xff')
 def read(self,u,access,p,n,v,_):
  if not self.active:return
  if p==0xa40d13:self.event(1,value=u.mem_read(p,1)[0])
  if p==0xb263d8:self.event(2,value=int(bool(self.word(p))))
  if p in (ACTOR+0x74,ACTOR+0x75,ACTOR+0x76,ACTOR+0x5b7):self.event(3,p-ACTOR,u.mem_read(p,1)[0])
 def write(self,u,access,p,n,v,_):
  if not self.active:return
  if p==ACTOR+0x75:
   assert n==1;self.event(4,0x75,v&255);self.expected[p-BASE]=v&255
  elif self.clip<=p<self.clip+16:
   assert n==4;self.event(4,p-self.clip,self.signed(v))
   if BASE<=p<BASE+SIZE:self.expected[p-BASE:p-BASE+4]=(v&0xffffffff).to_bytes(4,'little')
  elif self.point is not None and self.point<=p<self.point+8:
   assert n==4;self.event(8 if self.projecting else 4,p-self.point if self.projecting else p-self.point+16,self.signed(v))
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  sp=u.reg_read(UC_X86_REG_ESP);arg=lambda i:self.word(sp+4+4*i)
  if a in RANGES:
   self.counts[hex(a)]+=1
   if a==0x453c70:self.event(6);self.mutate(2)
   if a==0x6a29d0:self.event(7);self.point=arg(1);self.projecting=True
  if a==0x43a2f5:self.projecting=False
  if any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()):return
  if a==0x450dd0:
   assert u.reg_read(UC_X86_REG_ECX)==ACTOR;self.counts['bounds']+=1;self.event(5);self.ints(arg(0),self.bounds);self.mutate(1);self.ret(4,arg(0));return
  if a in self.draws:
   assert u.reg_read(UC_X86_REG_ECX)==ACTOR and arg(1)==self.clip;id=self.draws.index(a);self.counts['ordinary' if id==0 else 'special']+=1
   for i,v in enumerate([*self.values(arg(0),2),*self.values(arg(1),4)]):self.event(9,i,v,id)
   self.mutate(3)
   if self.mode==4:self.ints(arg(0),[71,72])
   self.ret(8);return
  raise AssertionError(('Uninspected Building visibility instruction',hex(a)))
 def run(self,f):
  force,special,self.mode,alias,bypass,context,marked,redraw,flag,hidden,*_=f;self.trace=[];self.mutated=False;self.point=None;self.projecting=False;self.bounds=f[18:22];self.u.mem_write(BASE,b'\x5a'*SIZE)
  self.draws=[self.word(0x79cbbc+off) for off in (0x10c,0x470)];self.put(ACTOR,0x79cbbc);self.u.mem_write(ACTOR+0x74,bytes([marked,redraw,flag]));self.u.mem_write(ACTOR+0x5b7,bytes([hidden]));self.ints(ACTOR+0x88,f[22:25]);self.ints(TACTICAL+0xb0,f[25:27]);self.put(0x83996c,TACTICAL);self.ints(0xabe568,f[27:29]);self.u.mem_write(0xabe490,struct.pack('<Q',f[29]));self.u.mem_write(0xa40d13,bytes([bypass]));self.put(0xb263d8,ACTOR if context else 0);self.ints(0x839630,f[10:14]);self.ints(INPUT,f[14:18]);self.clip=0x839630 if alias else INPUT
  self.expected=bytearray(self.u.mem_read(BASE,SIZE));self.active=True
  try:self.checked_call(0x43a200,[self.clip,force,special],ACTOR,writes=[(ACTOR+0x75,1),(self.clip,16)],inputs=[*RANGES.items(),(0x79cbbc,0x474),(0x79a728,8)])
  finally:self.active=False
  assert self.u.mem_read(BASE,SIZE)==self.expected,'Unrelated Building eligibility arena changed'
  self.event(11,value=self.u.reg_read(UC_X86_REG_EAX)&255);self.trace.append('F')
  self.trace.extend(map(str,[*self.u.mem_read(ACTOR+0x74,3),self.u.mem_read(ACTOR+0x5b7,1)[0],*self.values(self.clip,4),*self.values(0x839630,4),*self.values(ACTOR+0x88,3),*self.values(TACTICAL+0xb0,2)]))
  return self.trace
