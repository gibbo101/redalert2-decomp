# SPDX-License-Identifier: GPL-3.0-or-later
"""Unmodified complete readiness, TaskForce sum and Script cursor/query roots."""
from collections import Counter
from original_presentation import PresentationOracle,STOP
from verify_team_readiness import RANGES,SERVICES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EIP
BASE=0x5700000;SIZE=0x10000;TEAM=BASE+0x1000;TYPE=BASE+0x2000;TASK=BASE+0x3000;SCRIPT=BASE+0x4000;STYPE=BASE+0x5000;OUT=BASE+0x6000;TAGS=tuple(BASE+0x7000+i*0x100 for i in range(3));REGISTRY=BASE+0x8000;ALTERNATE=BASE+0x8200;VT=BASE+0x9000;CELL=BASE+0xa000
class TeamReadinessOracle(PresentationOracle):
 def __init__(self,exe):
  super().__init__(exe,allow_patched=True);self.u.mem_map(BASE,SIZE);self.active=False;self.counts=Counter();self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.write)
 def va(self,a):return a
 def word(self,a):return int.from_bytes(self.u.mem_read(a,4),'little')
 def signed(self,a):return (self.word(a)+2**31)%2**32-2**31
 def event(self,k,a=0,b=0,c=0,d=0,e=0):self.trace.extend(map(str,(k,a,b,c,d,e)))
 def ret(self,sp,n,v):
  self.u.reg_write(UC_X86_REG_EAX,v&0xffffffff);self.u.reg_write(UC_X86_REG_EIP,self.word(sp));self.u.reg_write(UC_X86_REG_ESP,sp+4+n)
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  assert a in SERVICES or any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected readiness instruction',hex(a))
  if a in RANGES:self.counts[hex(a)]+=1
  sp=u.reg_read(UC_X86_REG_ESP);ecx=u.reg_read(UC_X86_REG_ECX);f=self.f
  if a==0x6b3df0:
   assert ecx in TAGS;args=[self.word(sp+4+i*4) for i in range(5)];assert args==[23,0,0x7fff7fff,0,0];self.event(2,TAGS.index(ecx),*args[:3]);self.raises+=1
   if self.raises==1 and f[16]:
    self.event(3,f[16])
    if f[16]==1:self.put(0x866170,0)
    if f[16]==2:self.put(0x866170,1)
    if f[16]==3:self.put(0x866164,ALTERNATE)
   self.ret(sp,20,f[15])
  elif a==SERVICES[1]:assert ecx==TEAM and self.word(sp+4)==1;self.destroyed+=1;self.event(4,1);self.ret(sp,4,0)
 def write(self,u,access,a,n,v,_):
  if not self.active or not BASE<=a<BASE+SIZE:return
  v&=(1<<(8*n))-1
  if TEAM<=a<a+n<=TEAM+156:
   off=a-TEAM;assert (off==0x34 and n==4) or (0x74<=off<0x84 and n==1);self.event(1,off,n,v)
  elif a==SCRIPT+0x2c and n==4:self.event(5,0x2c,v)
  else:assert OUT<=a<a+n<=OUT+8,('Unexpected readiness arena write',hex(a),n)
  self.expected[a-BASE:a-BASE+n]=v.to_bytes(n,'little')
 def run(self,f):
  self.f=f;self.trace=[];self.raises=0;self.destroyed=0;u=self.u;u.mem_write(BASE,b'\x5a'*SIZE)
  self.put(TEAM,VT);self.put(VT+0x20,SERVICES[1]);self.put(TEAM+0x24,TYPE);self.put(TYPE+0xdc,TASK);self.put(TEAM+0x48,f[1]);self.put(TEAM+0x34,CELL if f[22] else 0);u.mem_write(TEAM+0x74,bytes(16))
  for off,index in ((0x7a,6),(0x78,7),(0x81,8),(0x7b,9),(0x79,10),(0x76,11),(0x7d,12),(0x7e,13)):u.mem_write(TEAM+off,bytes([f[index]]))
  u.mem_write(TYPE+0xab,bytes([f[4]]));u.mem_write(TYPE+0xa7,bytes([f[5]]));self.put(TASK+0x9c,f[2]);values=[]
  for i in range(6):
   value=(0 if i else 4) if f[3]==0 else (2147483647,1,-2147483648,-1,6,0)[i] if f[3]==1 else i-2 if f[3]==2 else f[24];values.append(value);self.put(TASK+0xa4+8*i,value)
  for i,p in enumerate(TAGS):self.put(REGISTRY+4*i,p);self.put(ALTERNATE+4*(2-i),p)
  self.put(0x866164,REGISTRY);self.put(0x866170,f[14]);self.put(0xac0050,0x7fff7fff)
  self.put(SCRIPT+0x24,0 if f[20] else STYPE);self.put(SCRIPT+0x2c,f[18]);self.put(STYPE+0xa0,f[19]);actions=((50,70),(20,13),(8,-1),(-2147483648,2147483647),(0,0),(10,7))
  for i,pair in enumerate(actions):
   for j,v in enumerate(pair):self.put(STYPE+0xa4+8*i+4*j,v)
  self.expected=bytearray(u.mem_read(BASE,SIZE));result=-1;answer=[-99,-99];self.active=True
  def call(root,args=(),owner=SCRIPT):
   self.checked_call(root,args,owner,writes=[(TEAM,156),(SCRIPT+0x2c,4),(OUT,8)],inputs=[*RANGES.items(),(TASK,0xe0),(TYPE,0xe0),(STYPE,0xd4),(VT,0x24)])
   return u.reg_read(UC_X86_REG_EAX)
  def operation(op):
   nonlocal result,answer
   roots=(0x668870,0x6688b0,0x668900,0x668920,0x668940);value=call(roots[op],[OUT] if op<2 else [])
   if op<2:answer=[self.signed(OUT),self.signed(OUT+4)];result=-1
   else:result=value&255
   self.event(6,op,result,*answer)
  try:
   if f[0]==0:result=call(0x6b8bb0,owner=TEAM)&255
   elif f[17]!=5:operation(f[17])
   else:
    operation(2)
    for _ in range(f[23]):
     operation(3);operation(4)
     if result:operation(0)
  finally:self.active=False
  assert bytes(u.mem_read(BASE,SIZE))==self.expected,'Unrelated readiness arena changed'
  total=(sum(values[:max(0,f[2])])+2**31)%2**32-2**31
  final=[result,int(bool(self.word(TEAM+0x34))),self.destroyed,self.raises,self.signed(0x866170),self.signed(SCRIPT+0x2c),self.signed(STYPE+0xa0),*answer,total,self.word(TEAM+0x48),*u.mem_read(TEAM+0x74,16)]
  return self.trace+['F',*map(str,final)]
