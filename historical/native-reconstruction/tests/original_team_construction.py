# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete Team and base constructors; named effect children supplied."""
from collections import Counter
import struct
from original_presentation import PresentationOracle,STOP
from verify_team_construction import RANGES,REG,VTABLES,SERVICES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EIP
BASE=0x5100000;SIZE=0x20000;RECORD=BASE+0x1000;TYPES=(BASE+0x2000,BASE+0x2200);HOUSE=BASE+0x3000
TAGTYPES=(BASE+0x4000,BASE+0x4100);SCRIPTTYPES=(BASE+0x4200,BASE+0x4300)
CELL=BASE+0x5000;TAG=BASE+0x6000;SCRIPT=BASE+0x6100;OTHERTAG=BASE+0x6200;OTHERSCRIPT=BASE+0x6300;OBJECTTAG=BASE+0x6400;VT=BASE+0x7000
SLOTS=tuple(BASE+0x8000+0x100*i for i in range(5));ALT=tuple(BASE+0x9000+0x100*i for i in range(5))
PRIOR=tuple(BASE+0xa000+256*i for i in range(8))
PROFILES=((2,6,1,3),(2,2,0,3),(2,2,1,0),(2,2,128,3),(0,0,0,3),(2,2,1,2147483647))
class TeamConstructionOracle(PresentationOracle):
 def __init__(self,exe):
  super().__init__(exe,allow_patched=True);self.u.mem_map(BASE,SIZE);self.active=False;self.counts=Counter();self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.write)
 def va(self,a):return a
 def word(self,p):return int.from_bytes(self.u.mem_read(p,4),'little')
 def pid(self,p):
  values=(0,RECORD,*TYPES,HOUSE,*TAGTYPES,*SCRIPTTYPES,CELL,TAG,SCRIPT,OTHERTAG,OTHERSCRIPT,OBJECTTAG,*PRIOR)
  if p in values:return values.index(p)
  if p in REG:return 31+REG.index(p)
  raise AssertionError(('Unknown Team pointer',hex(p)))
 def event(self,k,a=0,b=0,c=0,d=0,e=0):self.trace.extend(map(str,(k,a,b,c,d,e)))
 def write_fixture(self,p,value):
  self.put(p,value)
  if BASE<=p<BASE+SIZE:self.expected[p-BASE:p-BASE+4]=(value&0xffffffff).to_bytes(4,'little')
 def mutate(self,where):
  if self.mutated or self.f[16]!=where:return
  self.mutated=True;self.event(8,where)
  if where==1:self.put(0xa40d2c,-2)
  if where==2:self.put(REG[0]+4,ALT[0])
  if where in (3,4,5):self.write_fixture(RECORD+0x24,TYPES[1])
  if where==6:self.put(REG[self.resizing]+16,1)
  if where==7:self.put(0xac0050,self.f[7])
 def ret(self,sp,n,value=0):
  self.u.reg_write(UC_X86_REG_EAX,value&0xffffffff);self.u.reg_write(UC_X86_REG_EIP,self.word(sp));self.u.reg_write(UC_X86_REG_ESP,sp+4+n)
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  assert a in SERVICES or any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected Team constructor instruction',hex(a))
  if a in RANGES:self.counts[hex(a)]+=1
  sp=u.reg_read(UC_X86_REG_ESP);ecx=u.reg_read(UC_X86_REG_ECX)
  if a==0x6bfa90:
   self.waypoint+=1;self.event(2,self.pid(ecx),self.waypoint)
   if self.waypoint==1:self.mutate(3);self.mutate(7)
   out=self.word(sp+4);self.put(out,self.f[7 if self.waypoint==1 else 8]);self.ret(sp,4,out)
  elif a==0x548070:
   assert ecx==0x8324e0;self.event(3,self.word(self.word(sp+4)));self.ret(sp,4,CELL)
  elif a==0x782017:
   size=self.word(sp+4);assert size in (56,48);tag=size==56;p=(TAG if tag else SCRIPT) if self.f[11]&(1 if tag else 2) else 0
   self.event(4,size,self.pid(p))
   if tag:self.mutate(4)
   self.ret(sp,0,p)
  elif a in (0x6b3870,0x668730):
   tag=a==0x6b3870;result=(0,TAG,OTHERTAG)[self.f[12]] if tag else (0,SCRIPT,OTHERSCRIPT)[self.f[13]]
   self.event(5 if tag else 6,self.pid(ecx),self.pid(self.word(sp+4)),self.pid(result))
   if tag:self.mutate(5)
   self.ret(sp,4,result)
  elif a==SERVICES[-1]:
   i=REG.index(ecx);cap=self.word(sp+4);zero=self.word(sp+8);self.resizing=i
   self.event(7,31+i,(cap+2**31)%2**32-2**31,zero,self.f[15])
   if self.f[15]&255:
    raw=bytes(u.mem_read(self.word(REG[i]+4),32));u.mem_write(ALT[i],raw);self.expected[ALT[i]-BASE:ALT[i]-BASE+32]=raw
    self.put(REG[i]+4,ALT[i]);self.put(REG[i]+8,cap);u.mem_write(REG[i]+13,b'\1')
   self.mutate(6);self.ret(sp,8,self.f[15])
 def write(self,u,access,p,n,v,_):
  if not self.active:return
  value=v&((1<<(n*8))-1)
  if p in tuple(r+16 for r in REG):
   i=tuple(r+16 for r in REG).index(p);self.event(1,31+i,16,n,value)
   if i==0:self.mutate(2)
   return
  if not BASE<=p<BASE+SIZE:return
  if RECORD<=p<RECORD+156:
   off=p-RECORD
   if off in (0,4,8,12):value=VTABLES.index(value)
   elif off in (0x24,0x28,0x2c,0x34,0x70):value=self.pid(value)
   self.event(1,1,off,n,value)
   if off==0x50:self.mutate(1)
  elif p in (TYPES[0]+0xd4,TYPES[1]+0xd4):self.event(1,self.pid(p-0xd4),0xd4,n,value)
  elif p==HOUSE+0x555c:self.event(1,4,0x555c,n,value)
  else:
   match=next(((i,b) for i in range(5) for b in (SLOTS[i],ALT[i]) if b<=p<b+32),None);assert match is not None,('Unexpected Team arena write',hex(p),n)
   i,b=match;self.event(1,31+i,0x100+p-b,n,self.pid(value))
  self.expected[p-BASE:p-BASE+n]=(v&((1<<(n*8))-1)).to_bytes(n,'little')
 def run(self,f):
  self.f=f;self.trace=[];self.mutated=False;self.waypoint=0;u=self.u;u.mem_write(BASE,b'\x5a'*SIZE)
  self.put(VT+8,SERVICES[-1]);self.put(0xa40d2c,f[4]);self.put(0xac0050,0x7fff7fff)
  for i,t in enumerate(TYPES):
   u.mem_write(t+0xee,bytes([f[2] if i==0 else 0]));self.put(t+0xd4,f[3] if i==0 else -1);self.put(t+0xc8,TAGTYPES[i] if i or f[9] else 0);self.put(t+0xd8,SCRIPTTYPES[i] if i or f[10] else 0)
  self.put(HOUSE+0x555c,-1);u.mem_write(RECORD+0x14,bytes([f[6]]))
  for i,r in enumerate(REG):
   count,cap,allocated,growth=((6 if i==1 else 2 if i==2 else 0),4 if i==2 else 8,1,10) if f[14]==6 else PROFILES[(f[14]+i)%6]
   for off,value in ((0,VT),(4,SLOTS[i]),(8,cap),(16,count),(20,growth)):self.put(r+off,value)
   u.mem_write(r+13,bytes([allocated]));values=list(PRIOR)
   if f[14]==6 and i==1:values[5]=OBJECTTAG
   if f[14]==6 and i==2:values[:2]=PRIOR[6:]
   u.mem_write(SLOTS[i],struct.pack('<8I',*values));u.mem_write(ALT[i],b'\0'*32)
  self.expected=bytearray(u.mem_read(BASE,SIZE));self.active=True
  try:
   self.checked_call(0x6b7430,[TYPES[0] if f[0] else 0,HOUSE if f[1] else 0,f[5]],RECORD,writes=[(RECORD,156),(TYPES[0]+0xd4,4),(TYPES[1]+0xd4,4),(HOUSE+0x555c,4),*((r+4,20) for r in REG),*((b,32) for b in SLOTS+ALT),(0xa40d2c,4),(0xac0050,4)],inputs=[*RANGES.items(),(VT,16)])
   result=self.pid(u.reg_read(UC_X86_REG_EAX))
   if f[17]:
    subjects=(0,OBJECTTAG,self.word(RECORD+0x70) or OBJECTTAG,TYPES[0],HOUSE,SCRIPT,CELL,OTHERTAG)
    self.checked_call(0x6b9590,[subjects[f[17]],257],RECORD,writes=[(RECORD,156)],inputs=[*RANGES.items()])
  finally:self.active=False
  assert bytes(u.mem_read(BASE,SIZE))==self.expected,'Unrelated Team arena changed'
  final=[result,int(self.mutated),self.word(0xa40d2c),self.word(0xac0050),self.word(TYPES[0]+0xd4),self.word(TYPES[1]+0xd4),self.word(HOUSE+0x555c)]
  for i,r in enumerate(REG):
   b=self.word(r+4);final.extend([self.word(r+16),self.word(r+8),*u.mem_read(r+13,1),int(b==ALT[i]),*[self.pid(self.word(b+j*4)) for j in range(8)]])
  for off in (0x10,0x14,0x18,0x1c,0x20,0x24,0x28,0x2c,0x30,0x34,0x38,0x3c,0x40,0x44,0x48,0x4c,0x50,0x54,0x58,0x60,0x64,0x6c,0x70):
   v=u.mem_read(RECORD+off,1)[0] if off in (0x14,0x20) else self.word(RECORD+off)
   final.append(self.pid(v) if off in (0x24,0x28,0x2c,0x34,0x70) else v)
  final.extend(u.mem_read(RECORD+0x74,16));final.extend(self.word(RECORD+0x84+4*i) for i in range(6))
  return self.trace+['F',*map(str,final)]
