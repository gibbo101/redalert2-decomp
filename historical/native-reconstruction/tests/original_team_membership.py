# SPDX-License-Identifier: GPL-3.0-or-later
"""Unmodified AddMember, group, Tag, ordinary anchor, null distance and expiration."""
from collections import Counter
from original_presentation import PresentationOracle,STOP
from verify_team_membership import RANGES,SERVICES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EIP
BASE=0x5500000;SIZE=0x10000;TEAM=BASE+0x1000;OLD=BASE+0x1200;FEET=tuple(BASE+0x2000+i*0x1000 for i in range(3));TYPE=BASE+0x5000;TASK=BASE+0x6000;TAG=BASE+0x7000;OLDTAG=BASE+0x7200;SCRIPT=BASE+0x7400;SCRATCH=BASE+0x7600;CELL=BASE+0x7800;HOUSE=BASE+0x8000;VT=BASE+0x9000
class TeamMembershipOracle(PresentationOracle):
 def __init__(self,exe):
  super().__init__(exe,allow_patched=True);self.u.mem_map(BASE,SIZE);self.active=False;self.counts=Counter();self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.write)
 def va(self,a):return a
 def word(self,p):return int.from_bytes(self.u.mem_read(p,4),'little')
 def signed(self,p):return (self.word(p)+2**31)%2**32-2**31
 def pid(self,p):
  values={0:0,TEAM:1,OLD:2,**{a:10+i for i,a in enumerate(FEET)},TAG:30,OLDTAG:31,CELL:40,TYPE:50,HOUSE:60,SCRIPT:70}
  assert p in values,('Unknown membership pointer',hex(p));return values[p]
 def event(self,k,a=0,b=0,c=0,d=0,e=0):self.trace.extend(map(str,(k,a,b,c,d,e)))
 def supplied(self,p,v,n=4):
  raw=(v&((1<<(8*n))-1)).to_bytes(n,'little');self.u.mem_write(p,raw);self.expected[p-BASE:p-BASE+n]=raw
 def mutate(self,where):
  if self.mutated or self.f[29]!=where:return
  self.mutated=1;self.event(3,where)
  if where==1:self.supplied(TEAM+0x84+4*self.f[3],0xfffffffe)
  if where==2:self.supplied(TEAM+0x70,OLDTAG)
  if where==3:self.supplied(TEAM+0x34,CELL);self.supplied(TYPE+0xed,128,1)
  if where==4:self.supplied(TEAM+0x54,FEET[2])
 def ret(self,sp,n,v):
  self.u.reg_write(UC_X86_REG_EAX,v&0xffffffff);self.u.reg_write(UC_X86_REG_EIP,self.word(sp));self.u.reg_write(UC_X86_REG_ESP,sp+4+n)
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  assert a in SERVICES or any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected membership instruction',hex(a))
  if a in RANGES:self.counts[hex(a)]+=1
  if a==0x6b98d9:self.counts['normal_anchor']+=1
  assert a!=0x6b964c,'Unjoined Script10 anchor branch entered'
  sp=u.reg_read(UC_X86_REG_ESP);ecx=u.reg_read(UC_X86_REG_ECX);f=self.f
  if a==0x6b8dc0:
   assert ecx==TEAM;foot=self.word(sp+4);self.event(2,1,self.pid(foot),f[2],f[3]);self.put(self.word(sp+8),f[3]);self.mutate(1);self.ret(sp,8,f[2])
  elif a==0x6b8fb0:
   foot=self.word(sp+4);assert ecx==OLD;self.event(2,2,self.pid(foot),self.signed(sp+8),self.word(sp+12));self.supplied(foot+0x4c4,0);self.supplied(foot+0x4c8,0);self.ret(sp,12,1)
  elif a==0x668870:
   assert ecx==SCRIPT;self.event(2,6,0,f[18]);self.supplied(SCRATCH,f[18]);self.ret(sp,4,SCRATCH)
  elif a==SERVICES[4]:self.event(2,5,self.pid(ecx),f[21]);self.ret(sp,0,f[21])
  elif a==SERVICES[5]:self.event(2,3,self.pid(ecx));self.mutate(2);self.ret(sp,0,TYPE)
  elif a==SERVICES[6]:self.event(2,4,self.pid(ecx),f[14]);self.mutate(3);self.ret(sp,0,f[14])
  elif a==SERVICES[7]:self.event(2,7,self.pid(ecx),f[20]);self.ret(sp,0,f[20])
  elif a==0x548000:
   assert ecx==0x8324e0;p=self.word(sp+4);self.event(2,8,self.signed(p),self.signed(p+4),self.signed(p+8));self.mutate(4);self.ret(sp,4,CELL)
  elif a==SERVICES[8]:
   self.event(2,9,self.pid(ecx),self.pid(self.word(sp+4)),self.signed(sp+8),self.signed(sp+12));self.event(2,10,self.signed(sp+16),self.signed(sp+20),f[28]);self.ret(sp,20,f[28])
 def write(self,u,access,p,n,v,_):
  if not self.active or not BASE<=p<BASE+SIZE:return
  value=v&((1<<(8*n))-1)
  matches=[(TEAM,1,156),*((a,10+i,0x600) for i,a in enumerate(FEET)),(TAG,30,56),(OLDTAG,31,56)]
  match=next(((start,identity) for start,identity,size in matches if start<=p<p+n<=start+size),None)
  assert match is not None,('Unexpected membership arena store',hex(p),n)
  start,identity=match;off=p-start
  if identity==1 and off in (0x24,0x28,0x2c,0x34,0x38,0x54,0x70) or 10<=identity<=12 and off in (0x34,0x4c4,0x4c8):value=self.pid(value)
  self.event(1,identity,off,n,value);self.expected[p-BASE:p-BASE+n]=(v&((1<<(8*n))-1)).to_bytes(n,'little')
 def run(self,f):
  self.f=f;self.trace=[];self.mutated=0;u=self.u;u.mem_write(BASE,b'\x5a'*SIZE)
  for off,value in ((0x24,TYPE),(0x28,SCRIPT),(0x2c,HOUSE),(0x30,0),(0x34,CELL if f[6]==1 else FEET[0] if f[6]==2 else 0),(0x38,FEET[0] if f[6]==2 else 0),(0x3c,0),(0x40,0),(0x44,0),(0x48,f[15]),(0x4c,f[16]),(0x54,FEET[f[5]-1] if f[5] else 0),(0x70,TAG if f[7] else 0)):self.put(TEAM+off,value)
  u.mem_write(TEAM+0x7d,b'\1\0');self.put(TYPE+0x9c,f[8]);self.put(TYPE+0xdc,TASK if f[10] else 0);self.put(TASK+0x98,f[9]);self.put(TYPE+0x52c,f[12])
  for off,value in ((0xb3,f[11]),(0xed,f[13]),(0xa7,f[19]),(0xada,f[27])):u.mem_write(TYPE+off,bytes([value]))
  for i,a in enumerate(FEET):
   for off,value in ((0,VT),(0x34,OLDTAG),(0x4c4,OLD if i==0 and f[4] else 0),(0x4c8,FEET[i+1] if i<2 else 0),(0x1ac,123),(0x6c,f[23])):self.put(a+off,value)
   for off,value in ((0x579,f[25] if i==0 else int(i==1)),(0x37a,1),(0x7d,f[22]),(0x76,f[24]),(0x32d,f[26])):u.mem_write(a+off,bytes([value]))
   coords=( (-2147483648+17 if i else 2147483647-11),(2147483647-7 if i else -2147483648+13),104) if f[32] else (-257+i*770,511-i*640,104+i*104)
   for j,x in enumerate(coords):self.put(a+0x88+j*4,x)
  for i in range(6):self.put(TEAM+0x84+4*i,f[17])
  self.put(TAG+0x2c,0);self.put(OLDTAG+0x2c,10);self.put(0xa40774,0)
  for off,value in ((0x2c,SERVICES[4]),(0x80,SERVICES[5]),(0x2a0,SERVICES[6]),(0x46c,SERVICES[7]),(0x194,SERVICES[8])):self.put(VT+off,value)
  self.expected=bytearray(u.mem_read(BASE,SIZE));self.active=True;result=[-1]*3
  def call(root,args):
   self.checked_call(root,args,TEAM,writes=[(TEAM,156),*((a,0x600) for a in FEET),(TAG,56),(OLDTAG,56)],inputs=[*RANGES.items(),(VT,0x480),(0xa40774,4)])
   return u.reg_read(UC_X86_REG_EAX)&255
  try:
   if f[0]==0:result[0]=call(0x6b8cc0,[FEET[0] if f[1] else 0])
   if f[0]==1:call(0x6b9610,[TEAM+0x34,TEAM+0x38])
   if f[0]==2:
    subjects=(TAG,self.word(TEAM+0x54),CELL,SCRIPT,HOUSE,TYPE,FEET[0],OLDTAG);call(0x6b9590,[subjects[f[31]],f[30]])
   if f[0]==3:
    for i in range(3):result[i]=call(0x6b8cc0,[FEET[i] if f[1] else 0])
  finally:self.active=False
  assert bytes(u.mem_read(BASE,SIZE))==self.expected,'Unrelated membership arena changed'
  final=[*result,self.mutated,self.word(TEAM+0x48),self.word(TEAM+0x4c),*[self.pid(self.word(TEAM+off)) for off in (0x54,0x34,0x38,0x70,0x28,0x2c,0x24)],*u.mem_read(TEAM+0x7d,2),*[self.word(TEAM+0x84+4*i) for i in range(6)],self.signed(TAG+0x2c),self.signed(OLDTAG+0x2c)]
  for a in FEET:final.extend([*[self.pid(self.word(a+off)) for off in (0x4c4,0x4c8,0x34)],self.word(a+0x1ac),*u.mem_read(a+0x579,1),*u.mem_read(a+0x37a,1)])
  final.extend([*u.mem_read(TYPE+0xed,1),*u.mem_read(TYPE+0xb3,1)])
  return self.trace+['F',*map(str,final)]
