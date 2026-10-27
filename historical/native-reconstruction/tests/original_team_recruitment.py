# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete-to-return E1 recruitment with actual group/distance/null-target clear."""
from collections import Counter
from original_presentation import PresentationOracle,STOP
from verify_team_recruitment import RANGES,SERVICES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EIP
BASE=0x5600000;SIZE=0x18000;TEAM=BASE+0x1000;TYPE=BASE+0x2000;TASK=BASE+0x4000;FEET=tuple(BASE+0x5000+i*0x1000 for i in range(3));ANCHOR=BASE+0x8000;VT=BASE+0x9000;TYPEVT=BASE+0xa000;REGISTRY=BASE+0xb000;SCRATCH=BASE+0xc000;E1TYPE=BASE+0xd000
class TeamRecruitmentOracle(PresentationOracle):
 def __init__(self,exe):
  super().__init__(exe,allow_patched=True);self.u.mem_map(BASE,SIZE);self.active=False;self.counts=Counter();self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.write)
 def va(self,a):return a
 def word(self,a):return int.from_bytes(self.u.mem_read(a,4),'little')
 def signed(self,a):return (self.word(a)+2**31)%2**32-2**31
 def index(self,a):assert a in FEET;return FEET.index(a)
 def event(self,k,a=0,b=0,c=0,d=0,e=0):self.trace.extend(map(str,(k,a,b,c,d,e)))
 def supplied(self,a,v,n=4):
  raw=(v&((1<<(8*n))-1)).to_bytes(n,'little');self.u.mem_write(a,raw)
  if BASE<=a<BASE+SIZE:self.expected[a-BASE:a-BASE+n]=raw
 def mutate(self,where):
  if self.mutated or self.f[18]!=where:return
  self.mutated=where;self.event(7,where)
  if where==1:self.put(0xa35e58,1)
  if where==2:self.supplied(FEET[1]+0x1ac,self.f[4]);self.supplied(TYPE+0xa8,128,1)
  if where==3:self.put(0xa35e58,3)
 def ret(self,sp,n,v):
  self.u.reg_write(UC_X86_REG_EAX,v&0xffffffff);self.u.reg_write(UC_X86_REG_EIP,self.word(sp));self.u.reg_write(UC_X86_REG_ESP,sp+4+n)
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  assert a in SERVICES or any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected recruiting instruction',hex(a))
  if a in RANGES:self.counts[hex(a)]+=1
  assert a not in (0x6b937d,0x6b942b),'Other registry recruitment unjoined'
  sp=u.reg_read(UC_X86_REG_ESP);ecx=u.reg_read(UC_X86_REG_ECX);f=self.f
  if a==0x5d4e40:self.event(1,99 if ecx==ANCHOR else self.index(ecx))
  elif a==0x6bfa60:assert ecx==TYPE;self.event(3)
  elif a==0x502470:assert self.word(sp+4)==0;self.event(6,self.index(ecx))
  elif a==0x6bfa90:
   assert ecx==TYPE;self.event(2,self.waypoints);p=f[16] if self.waypoints else f[15];self.waypoints+=1;out=self.word(sp+4);self.put(out,p);self.ret(sp,4,out)
  elif a==SERVICES[3]:assert ecx==E1TYPE;self.event(4,f[19]);self.ret(sp,0,f[19])
  elif a==0x6b8dc0:
   assert ecx==TEAM;i=self.index(self.word(sp+4));slot=self.word(sp+8);self.event(5,i,self.signed(slot),f[9+i],f[12]);self.put(slot,f[12]);self.admissionCalls+=1;self.mutate(1 if self.admissionCalls==1 else 3);self.ret(sp,8,f[9+i])
  elif a==0x6b8cc0:
   assert ecx==TEAM;self.selected=self.index(self.word(sp+4));self.addCalls+=1;self.event(9,self.selected,f[17]);self.mutate(2);self.ret(sp,4,f[17])
 def write(self,u,access,a,n,v,_):
  if not self.active or not BASE<=a<BASE+SIZE:return
  i=next((i for i,p in enumerate(FEET) if p<=a<a+n<=p+0x600),None);assert i is not None,('Unexpected recruiting store',hex(a),n)
  off=a-FEET[i];assert (off,n) in ((0x4d0,4),(0x404,1),(0x57e,1));value=(v+2**31)%2**32-2**31 if n==4 else v
  self.event(8,i,off,value);self.expected[a-BASE:a-BASE+n]=(v&((1<<(8*n))-1)).to_bytes(n,'little')
 def run(self,f):
  self.f=f;self.trace=[];self.waypoints=0;self.mutated=0;self.admissionCalls=0;self.addCalls=0;self.selected=-1;u=self.u;u.mem_write(BASE,b'\x5a'*SIZE)
  for off,v in ((0x24,TYPE),(0x34,ANCHOR if f[14] else 0)):self.put(TEAM+off,v)
  for i in range(6):self.put(TEAM+0x84+4*i,f[3]);self.put(TASK+0xa4+8*i,f[2]);self.put(TASK+0xa8+8*i,E1TYPE)
  self.put(E1TYPE,TYPEVT);self.put(TYPE+0xdc,TASK if f[21] else 0);self.put(TYPE+0x9c,f[4]);self.put(TASK+0x98,f[20]);u.mem_write(TYPE+0xa8,bytes([f[5]]));u.mem_write(E1TYPE+0xc0c,bytes([f[22]]));u.mem_write(E1TYPE+0xc12,bytes([f[23]]))
  self.put(TYPE+0xdc,TASK)
  self.put(TYPEVT+0x2c,SERVICES[3]);self.put(VT+0x48,0x5d4e40);self.put(VT+0x370,0x502470)
  for i,p in enumerate(FEET):
   self.put(REGISTRY+4*i,p)
   for off,v in ((0,VT),(0x1ac,f[6+i]),(0x228,0),(0x494,0),(0x5a8,E1TYPE),(0x5ac,f[25]),(0x6c,f[24]),(0x4d0,17)):self.put(p+off,v)
   u.mem_write(p+0x404,b'\x80');u.mem_write(p+0x57e,b'\xff')
   position=(256*(i+1),128*(i+1),208+i*104)
   if f[13]==1:position=(512,256,0)
   if f[13]==2:position=((46341,0,0),(1,1,0),(65536,65535,0))[i]
   if f[13]==3:position=((2147483647,-2147483648,0),(-2147483648,2147483647,0),(0,0,0))[i]
   for j,v in enumerate(position):self.put(p+0x88+j*4,v)
  self.put(ANCHOR,VT)
  for j,v in enumerate((1024,-512,307)):self.put(ANCHOR+0x88+j*4,v)
  for j,v in enumerate((-2147483648,2147483647,99) if f[27] else (0,0,0)):self.put(0xac0070+j*4,v)
  self.put(0xac0050,0x7fff7fff);self.put(0xa35e4c,REGISTRY);self.put(0xa35e58,f[1]);self.expected=bytearray(u.mem_read(BASE,SIZE));self.active=True
  try:
   root,args,owner=(0x502470,[0],FEET[0]) if f[26] else (0x6b91c0,[f[0]],TEAM)
   self.checked_call(root,args,owner,writes=[(p,0x600) for p in FEET],inputs=[*RANGES.items(),(VT,0x480),(TYPEVT,0x40),(0x6b954c,56)])
   result=0 if f[26] else u.reg_read(UC_X86_REG_EAX)
  finally:self.active=False
  assert bytes(u.mem_read(BASE,SIZE))==self.expected,'Unrelated recruitment arena changed'
  final=[result,self.selected,self.signed(0xa35e58),*u.mem_read(TYPE+0xa8,1),self.mutated,self.admissionCalls,self.waypoints,self.addCalls]
  for p in FEET:final.extend([self.signed(p+0x1ac),self.signed(p+0x4d0),*u.mem_read(p+0x404,1),*u.mem_read(p+0x57e,1)])
  return self.trace+['F',*map(str,final)]
