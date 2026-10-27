# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete Tag/Trigger/Script/base/reset instructions; heap/resize and timer scratch supplied."""
from collections import Counter
import struct
from original_presentation import PresentationOracle,STOP
from verify_mission_construction import RANGES,REG,VTABLES,SERVICES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EIP
BASE=0x5300000;SIZE=0x20000;TAG=BASE+0x1000;TRIGGERS=(BASE+0x2000,BASE+0x2200,BASE+0x2400);SCRIPT=BASE+0x3000
TAGTYPES=(BASE+0x4000,BASE+0x4200);TYPES=(BASE+0x4400,BASE+0x4600);SCRIPTTYPE=BASE+0x4800;LINK=BASE+0x4900;SCENE=BASE+0x5000;EVENTS=(BASE+0x6000,BASE+0x6100);VT=BASE+0x7000
SLOTS=tuple(BASE+0x8000+256*i for i in range(5));ALT=tuple(BASE+0x9000+256*i for i in range(5));PRIOR=tuple(BASE+0xa000+256*i for i in range(16))
PROFILES=((1,16,1,10),(1,1,0,10),(1,1,1,0),(1,1,128,10),(0,0,0,10))
class MissionConstructionOracle(PresentationOracle):
 def __init__(self,exe):
  super().__init__(exe,allow_patched=True);self.u.mem_map(BASE,SIZE);self.active=False;self.counts=Counter();self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.write)
 def va(self,a):return a
 def word(self,p):return int.from_bytes(self.u.mem_read(p,4),'little')
 def pid(self,p):
  values=(0,TAG,*TRIGGERS,SCRIPT,*TAGTYPES,*TYPES,SCRIPTTYPE,LINK)
  if p in values:return values.index(p)
  if p in REG:return 31+REG.index(p)
  if p in PRIOR:return 41+PRIOR.index(p)
  raise AssertionError(('Unknown mission construction pointer',hex(p)))
 def event(self,k,a=0,b=0,c=0,d=0,e=0):self.trace.extend(map(str,(k,a,b,c,d,e)))
 def supplied(self,p,v,n=4):
  raw=(v&((1<<(8*n))-1)).to_bytes(n,'little');self.u.mem_write(p,raw)
  if BASE<=p<BASE+SIZE:self.expected[p-BASE:p-BASE+n]=raw
 def mutate(self,where):
  if self.mutated or self.f[12]!=where:return
  self.mutated=True;self.event(4,where)
  if where==1:self.supplied(SCENE+0x60c,2);self.supplied(TYPES[0]+0x9e,0,1)
  if where==2:self.supplied(TAG+0x28,TRIGGERS[2])
  if where==3:self.supplied(TYPES[0]+0xa8,0)
  if where==4:self.supplied(TAG+0x24,TAGTYPES[1])
  if where==5:self.put(REG[self.resizing]+16,1)
 def ret(self,sp,n,value=0):
  self.u.reg_write(UC_X86_REG_EAX,value&0xffffffff);self.u.reg_write(UC_X86_REG_EIP,self.word(sp));self.u.reg_write(UC_X86_REG_ESP,sp+4+n)
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  assert a in SERVICES or any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected mission constructor instruction',hex(a))
  if a in RANGES:self.counts[hex(a)]+=1
  sp=u.reg_read(UC_X86_REG_ESP);ecx=u.reg_read(UC_X86_REG_ECX)
  if a==0x6ed680:
   # Explicit uninitialized timer-padding input; original reset instructions run.
   self.put(sp-8,self.f[13]);self.counts['supplied_timer_scratch']+=1
  elif a==0x782017:
   assert self.word(sp+4)==68 and self.allocations<2
   p=TRIGGERS[self.allocations];self.allocations+=1;self.event(2,68,self.pid(p));self.mutate(2);self.mutate(3);self.mutate(4);self.ret(sp,0,p)
  elif a==SERVICES[1]:
   i=REG.index(ecx);self.resizing=i;cap=self.word(sp+4);zero=self.word(sp+8)
   self.event(3,31+i,(cap+2**31)%2**32-2**31,zero,self.f[11])
   if self.f[11]&255:
    raw=bytes(u.mem_read(self.word(REG[i]+4),64));u.mem_write(ALT[i],raw);self.expected[ALT[i]-BASE:ALT[i]-BASE+64]=raw
    self.put(REG[i]+4,ALT[i]);self.put(REG[i]+8,cap);u.mem_write(REG[i]+13,b'\1')
   self.mutate(1);self.mutate(5);self.ret(sp,8,self.f[11])
 def write(self,u,access,p,n,v,_):
  if not self.active:return
  value=v&((1<<(8*n))-1)
  if p in tuple(r+16 for r in REG):self.event(1,31+tuple(r+16 for r in REG).index(p),16,n,value);return
  if not BASE<=p<BASE+SIZE:return
  match=next(((identity,p-start) for start,identity,size in ((TAG,1,56),*((t,2+i,68) for i,t in enumerate(TRIGGERS)),(SCRIPT,5,48)) if start<=p<start+size),None)
  if match:
   identity,off=match
   if off in (0,4,8,12):value=VTABLES.index(value)
   elif (identity==1 and off in (0x24,0x28,0x30)) or (2<=identity<=4 and off in (0x24,0x28)) or (identity==5 and off==0x24):value=self.pid(value)
   self.event(1,identity,off,n,value)
  else:
   match=next(((i,b) for i in range(5) for b in (SLOTS[i],ALT[i]) if b<=p<b+64),None);assert match is not None,('Unexpected mission constructor arena write',hex(p),n)
   i,b=match;self.event(1,31+i,0x100+p-b,n,self.pid(value))
  self.expected[p-BASE:p-BASE+n]=(v&((1<<(8*n))-1)).to_bytes(n,'little')
 def run(self,f):
  self.f=f;self.trace=[];self.mutated=False;self.allocations=0;u=self.u;u.mem_write(BASE,b'\x5a'*SIZE)
  self.put(0xa40d2c,f[8]);self.put(0xa3d290,SCENE);self.put(SCENE+0x60c,f[3]);self.put(0xabfe28,0 if f[10]==5 else LINK);self.put(VT+8,SERVICES[1])
  for i,t in enumerate(TYPES):
   for j in range(4):u.mem_write(t+0x9c+j,bytes([f[5] if f[4]&(1<<j) else 0]))
   self.put(t+0xa8,TYPES[1] if i==0 and f[2]==2 else 0);self.put(t+0xac,EVENTS[i]);self.put(EVENTS[i]+0x28,0);self.put(EVENTS[i]+0x2c,f[6]);self.put(EVENTS[i]+0x34,f[7])
  self.put(TAGTYPES[0]+0xa0,TYPES[0] if f[2] else 0);self.put(TAGTYPES[1]+0xa0,0)
  for r in (TAG,*TRIGGERS,SCRIPT):u.mem_write(r+0x14,bytes([f[9]]));self.put(r+0x24,0);self.put(r+0x28,0)
  self.put(TAG+0x2c,0);self.put(TAG+0x30,0);u.mem_write(TAG+0x34,b'\0\0');self.put(SCRIPT+0x2c,-1)
  for t in TRIGGERS:
   u.mem_write(t+0x2c,b'\0');u.mem_write(t+0x40,b'\1');self.put(t+0x30,0);self.put(t+0x38,0);self.put(t+0x3c,0)
  for i,r in enumerate(REG):
   count,cap,allocated,growth=((1,7,6,5,0)[i],16,1,10) if f[10]==5 else PROFILES[(f[10]+i)%5]
   for off,val in ((0,VT),(4,SLOTS[i]),(8,cap),(16,count),(20,growth)):self.put(r+off,val)
   u.mem_write(r+13,bytes([allocated]));u.mem_write(SLOTS[i],struct.pack('<16I',*PRIOR));u.mem_write(ALT[i],b'\0'*64)
  self.expected=bytearray(u.mem_read(BASE,SIZE));self.active=True
  def call(a,args,this):
   self.checked_call(a,args,this,writes=[(TAG,56),*((t,68) for t in TRIGGERS),(SCRIPT,48),*((r+4,20) for r in REG),*((b,64) for b in SLOTS+ALT),(TYPES[0]+0x9c,4),(TYPES[0]+0xa8,4),(SCENE+0x60c,4)],inputs=[*RANGES.items(),(VT,16),(0xa40d2c,4),(0xa3d290,4),(0xabfe28,4)])
   assert u.reg_read(UC_X86_REG_EAX)==this,'Mission constructor return identity differs'
  try:
   if f[0]==0:call(0x668730,[SCRIPTTYPE if f[1] else 0],SCRIPT)
   if f[0]==1:call(0x6ed220,[TYPES[0] if f[1] else 0],TRIGGERS[0])
   if f[0] in (2,3):call(0x6b3870,[TAGTYPES[0] if f[1] else 0],TAG)
   if f[0]==3:call(0x668730,[SCRIPTTYPE if f[1] else 0],SCRIPT)
  finally:self.active=False
  assert bytes(u.mem_read(BASE,SIZE))==self.expected,'Unrelated mission construction arena changed'
  final=[int(self.mutated),self.allocations,self.word(SCENE+0x60c),int(bool(self.word(TYPES[0]+0xa8))),*u.mem_read(TYPES[0]+0x9c,4)]
  for i,r in enumerate(REG):
   b=self.word(r+4);final.extend([self.word(r+16),self.word(r+8),*u.mem_read(r+13,1),int(b==ALT[i]),*[self.pid(self.word(b+j*4)) for j in range(16)]])
  def base(r):return [self.word(r+0x10),*u.mem_read(r+0x14,1),self.word(r+0x18),self.word(r+0x1c),*u.mem_read(r+0x20,1)]
  final.extend(base(TAG)+[self.pid(self.word(TAG+0x24)),self.pid(self.word(TAG+0x28)),self.word(TAG+0x2c),self.pid(self.word(TAG+0x30)),*u.mem_read(TAG+0x34,2)])
  for t in TRIGGERS:final.extend(base(t)+[self.pid(self.word(t+0x24)),self.pid(self.word(t+0x28)),*u.mem_read(t+0x2c,1),*u.mem_read(t+0x40,1),self.word(t+0x30),self.word(t+0x34),self.word(t+0x38),self.word(t+0x3c)])
  final.extend(base(SCRIPT)+[self.pid(self.word(SCRIPT+0x24)),self.word(SCRIPT+0x28),self.word(SCRIPT+0x2c)])
  return self.trace+['F',*map(str,final)]
