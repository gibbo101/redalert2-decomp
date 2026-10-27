# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete observer/base constructors; CRT/resize/atexit services supplied."""
import struct
from original_presentation import PresentationOracle,STOP
from verify_team_observer_construction import verify,RANGES,REG,VTABLES
from verify_team_observer_weight import verify as verify_weight,RANGES as WEIGHT_RANGES,CONSTANTS
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EIP,UC_X86_REG_FPCW
BASE=0x6700000;SIZE=0x5000;RECORD=BASE+0x100;NAME=BASE+0x500;OTHER=BASE+0x700;TYPES=(BASE+0x800,BASE+0x900)
SLOTS=(BASE+0x1000,BASE+0x1200);ALT=(BASE+0x2000,BASE+0x2200)
EMPTY=0x839d4c;RESIZE=0x4d61b0
SERVICES=(0x7820f4,0x7823d0,0x78298a,RESIZE)
PROFILES=((2,6,1,3),(2,2,0,3),(2,2,128,0),(0,0,0,3),(2,2,128,3),(2,2,1,2147483647))
class TeamObserverConstructionOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());verify_weight(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(BASE,SIZE);self.active=False;self.calls={};self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.write)
 def va(self,a):return a
 def word(self,a):return int.from_bytes(self.u.mem_read(a,4),'little')
 def pid(self,p):
  d={0:0,RECORD:1,OTHER:2,EMPTY:20,TYPES[0]:31,TYPES[1]:32,REG[0]:91,REG[1]:92};assert p in d,hex(p);return d[p]
 def event(self,k,owner=0,off=0,n=0,v=0):self.trace.extend(map(str,(k,owner,off,n,v)))
 def change(self,a,raw):
  self.u.mem_write(a,raw)
  if BASE<=a<a+len(raw)<=BASE+SIZE:self.expected[a-BASE:a-BASE+len(raw)]=raw
  else:
   r=next(r for r in REG if r<=a<a+len(raw)<=r+24);self.globalExpected[r][a-r:a-r+len(raw)]=raw
 def change_word(self,a,v):self.change(a,struct.pack('<I',v&0xffffffff))
 def mutate(self,where):
  if self.mutated or self.f[4]!=where:return
  self.mutated=1
  if where==1:self.change(NAME,b'changed\0'+bytes(56))
  if where==2:self.change_word(REG[0]+4,ALT[0])
  if where==4:self.change(RECORD+0x24,b'Z')
 def write(self,u,access,a,n,v,_):
  if not self.active:return
  v&=(1<<(8*n))-1
  if any(r<=a<a+n<=r+24 for r in REG):
   r=next(r for r in REG if r<=a<a+n<=r+24);off=a-r
   self.globalExpected[r][off:off+n]=v.to_bytes(n,'little')
   value=14 if off==0 else self.pid(v) if off==4 else v
   self.event(1,self.pid(r),off,n,value)
   if r==REG[0] and off==16:self.mutate(2)
   return
  if not BASE<=a<a+n<=BASE+SIZE:return
  if RECORD<=a<a+n<=RECORD+0x110:
   off=a-RECORD;value=VTABLES.index(v) if off in (0,4,8,12) else self.pid(v) if off in (0x60,0xd8,0xdc,0xe0) else v;owner=1
   self.event(1,owner,off,n,value)
   if off==0x10:self.mutate(1)
   if off==0x3c:self.mutate(4)
  else:
   i,b=next((i,b) for i in range(2) for b in (SLOTS[i],ALT[i]) if b<=a<a+n<=b+32);assert n==4
   self.event(1,91+i,0x100+a-b,n,self.pid(v))
  self.expected[a-BASE:a-BASE+n]=v.to_bytes(n,'little')
 def ret(self,sp,pop,value=0):
  self.u.reg_write(UC_X86_REG_EAX,value&0xffffffff);self.u.reg_write(UC_X86_REG_EIP,self.word(sp));self.u.reg_write(UC_X86_REG_ESP,sp+4+pop)
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  ranges=dict(RANGES,**{})|WEIGHT_RANGES
  assert a in SERVICES or any(lo<=a and a+n<=lo+size for lo,size in ranges.items()),('Uninspected observer construction instruction',hex(a))
  if a in ranges:self.calls[hex(a)]=self.calls.get(hex(a),0)+1
  if a in WEIGHT_RANGES:u.reg_write(UC_X86_REG_FPCW,0xe7f if self.f[9] else 0x27f)
  sp=u.reg_read(UC_X86_REG_ESP)
  if a==0x7820f4:
   assert self.word(sp+8)==0x7ce280 and self.word(sp+12)==RECORD
   self.event(2,1);u.mem_write(self.word(sp+4),b'supplied-null-name\0');self.ret(sp,0,18)
  elif a==0x7823d0:
   dest,source,count=(self.word(sp+off) for off in (4,8,12));assert count in (24,48)
   raw=bytearray();ended=False
   for i in range(count):
    v=0 if ended else u.mem_read(source+i,1)[0];ended=ended or v==0;raw.append(v)
   u.mem_write(dest,bytes(raw));self.ret(sp,0,dest)
  elif a==0x78298a:
   assert self.word(sp+4)==0x4d2dd0;self.event(5);self.ret(sp,0)
  elif a==RESIZE:
   obj=u.reg_read(UC_X86_REG_ECX);i=REG.index(obj);cap=self.word(sp+4);assert self.word(sp+8)==0
   self.event(4,91+i,cap,0,self.f[3]&0xffffffff)
   if self.f[3]&255:
    old=self.word(obj+4);raw=bytes(u.mem_read(old,32)) if old else bytes(32)
    self.change(ALT[i],raw);self.change_word(obj+4,ALT[i]);self.change_word(obj+8,cap);self.change(obj+13,b'\1')
   if not self.mutated and self.f[4]==3:self.mutated=1;self.change_word(obj+16,1)
   self.ret(sp,8,self.f[3])
 def run(self,f):
  self.f=f;self.trace=[];self.mutated=0;u=self.u;u.mem_write(BASE,b'\x5a'*SIZE)
  lengths=(0,0,1,23,24,49,0,0);name=bytes(ord('a')+i%26 for i in range(lengths[f[0]]))+b'\0';u.mem_write(NAME,name)
  u.mem_write(RECORD+0x14,bytes([f[5]]))
  for off in (0x60,0xd8,0xdc,0xe0):self.put(RECORD+off,OTHER)
  for i,r in enumerate(REG):
   count,cap,allocated,growth=PROFILES[f[1+i]]
   for off,v in ((0,0x7a20a4),(4,SLOTS[i]),(8,cap),(16,count),(20,growth)):self.put(r+off,v)
   u.mem_write(r+12,bytes([90,allocated]));u.mem_write(SLOTS[i],struct.pack('<8I',*[OTHER]*8));u.mem_write(ALT[i],bytes(32))
  self.expected=bytearray(u.mem_read(BASE,SIZE));self.globalExpected={r:bytearray(u.mem_read(r,24)) for r in REG};self.active=True
  inputs=[*RANGES.items(),*WEIGHT_RANGES.items(),*((a,8) for a in CONSTANTS),(0x7a20a4,24)]
  writes=[(BASE,SIZE),*((r,24) for r in REG)]
  try:
   if f[8]:self.checked_call(0x4d2d90,writes=writes,inputs=inputs)
   source=0 if f[0]==0 else RECORD+0x24 if f[0]==6 else RECORD+0x64 if f[0]==7 else NAME
   self.checked_call(0x41c5c0,[source],RECORD,writes=writes,inputs=inputs);assert u.reg_read(UC_X86_REG_EAX)==RECORD
   self.checked_call(0x41df90,[0 if f[6]==0 else TYPES[f[6]-1]],RECORD,writes=writes,inputs=inputs)
   if f[7]:
    for a,v in ((0xb8,1.),(0xc0,-1.),(0xc8,.5)):self.change(BASE+0x3000+a,struct.pack('<d',v))
    self.put(0x839848,BASE+0x3000)
    self.checked_call(0x41dfb0 if f[7]==1 else 0x41e070,ecx=RECORD,writes=writes,inputs=inputs+[(0x839848,4)])
    assert u.reg_read(UC_X86_REG_FPCW)==(0xe7f if f[9] else 0x27f)
  finally:self.active=False
  assert bytes(u.mem_read(BASE,SIZE))==self.expected,'Unrelated observer construction arena changed'
  assert all(bytes(u.mem_read(r,24))==bytes(self.globalExpected[r]) for r in REG),'Unrelated registry fields changed'
  result=[self.mutated,self.word(RECORD+0x10),u.mem_read(RECORD+0x14,1)[0],self.word(RECORD+0x18),self.word(RECORD+0x1c),u.mem_read(RECORD+0x20,1)[0],u.mem_read(RECORD+0x3d,1)[0],self.pid(self.word(RECORD+0x60)),*u.mem_read(RECORD+0x24,25),*u.mem_read(RECORD+0x64,49)]
  result.extend(self.word(RECORD+off) if off!=0xa4 else u.mem_read(RECORD+off,1)[0] for off in (0x98,0x9c,0xa0,0xa4,0xa8,0xac,0xb0))
  result.extend(int.from_bytes(u.mem_read(RECORD+off,8),'little') for off in (0xb8,0xc0,0xc8));result.extend(u.mem_read(RECORD+0xd0,5));result.extend(self.pid(self.word(RECORD+off)) for off in (0xd8,0xdc,0xe0));result.extend(self.word(RECORD+0xe4+4*i) for i in range(8));result.extend(self.word(RECORD+off) for off in (0x104,0x108))
  for r in REG:
   backing=self.word(r+4);result.extend([self.word(r+16),self.word(r+8),u.mem_read(r+12,1)[0],u.mem_read(r+13,1)[0],self.word(r+20),*[self.pid(self.word(backing+4*j)) if backing else 0 for j in range(8)]])
  return self.trace+['F',*map(str,result)]
