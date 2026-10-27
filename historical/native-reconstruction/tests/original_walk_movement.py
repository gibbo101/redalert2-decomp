# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete unchanged Walk Process roots with selected head, distance >=17.

Only the declared speed/Mark/floor/map/dirty services are supplied. Actual Walk
and Infantry dispatch tables, coordinates, numerics, Facing and setters execute.
"""
import struct
from collections import Counter
from original_presentation import PresentationOracle,STOP
from verify_walk_movement import verify,RANGES,SERVICES,TABLES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_ESP,UC_X86_REG_EIP,UC_X86_REG_EAX,UC_X86_REG_ECX
ARENA=0x2800000;SIZE=0x4000;ACTOR=ARENA;WALK=ARENA+0x1000;OLD=ARENA+0x2000;NEW=ARENA+0x2200
def signed(v):return v if v<0x80000000 else v-0x100000000
def div256(v):return v//256 if v>=0 else -((-v)//256)
class WalkMovementOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True)
  self.u.mem_map(ARENA,SIZE);self.active=False;self.counts=Counter()
  self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.store)
 def va(self,a):return a
 def ints(self,p,n):return struct.unpack('<'+'i'*n,self.u.mem_read(p,4*n))
 def word(self,p):return struct.unpack('<H',self.u.mem_read(p,2))[0]
 def event(self,*v):self.events.extend(map(str,v))
 def trace(self,c,x=0,y=0,z=0):self.event(c,x,y,z)
 def ret(self,n,value=0):
  sp=self.u.reg_read(UC_X86_REG_ESP);target=self.ints(sp,1)[0]
  self.u.reg_write(UC_X86_REG_EAX,value&0xffffffff);self.u.reg_write(UC_X86_REG_ESP,sp+4+n)
  self.u.reg_write(UC_X86_REG_EIP,target)
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  assert a in SERVICES or any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected Walk instruction',hex(a))
  if a in RANGES:self.counts[hex(a)]+=1
  # Refuse paths outside the committed-head slice even though the complete
  # Movement_AI bytes are inspected/fingerprinted.
  assert not (0x71e25e<=a<0x71f077 or 0x71f0d3<=a<0x71f2d6),('Unjoined Walk branch',hex(a))
  sp=u.reg_read(UC_X86_REG_ESP);ecx=u.reg_read(UC_X86_REG_ECX)
  if a==0x5d4e40:assert ecx==ACTOR;self.trace('C')
  elif a==0x4c2df0:
   assert ecx==ACTOR and bytes(u.mem_read(sp+4,8))==struct.pack('<d',1.)
   self.trace('V',1)
  elif a==0x71e170:
   assert self.ints(sp+4,1)[0]==WALK+4;self.trace('T',self.word(sp+8))
  elif a==0x41b320:assert ecx==ACTOR;self.trace('Q')
  elif a==0x508980:assert ecx==ACTOR;self.trace('S');self.ret(0,self.v[6])
  elif a==0x4c2e60:
   assert ecx==ACTOR;kind=self.ints(sp+4,1)[0];assert kind in (0,1)
   xyz=self.ints(ACTOR+0x88,3);bridge=u.mem_read(ACTOR+0x79,1)[0];marked=u.mem_read(ACTOR+0x74,1)[0]
   self.event('M',kind,*xyz,bridge,marked);self.counts['Mark']+=1
   if self.v[19]&1:u.mem_write(ACTOR+0x74,bytes([kind]))
   if not kind and self.v[19]&2:
    for off,val in zip((0x88,0x8c,0x90),(xyz[0]+3,xyz[1]-5,xyz[2]+7)):self.put(ACTOR+off,val)
    u.mem_write(ACTOR+0x79,bytes([bridge^128]))
   if kind and self.v[19]&4:self.put(ACTOR+0x90,self.ints(ACTOR+0x90,1)[0]+11)
   self.ret(4,1)
  elif a==0x55a280:
   assert ecx==0x8324e0;self.event('F',*self.ints(self.ints(sp+4,1)[0],3));self.ret(4,self.v[13])
  elif a==0x548070:
   assert ecx==0x8324e0;point=struct.unpack('<hh',u.mem_read(self.ints(sp+4,1)[0],4))
   self.event('B',*point);self.ret(4,OLD if self.lookups==0 else NEW);self.lookups+=1
  elif a==0x548000:
   assert ecx==0x8324e0;self.event('N',*self.ints(self.ints(sp+4,1)[0],3));self.ret(4,NEW)
  elif a==0x47bb30:assert ecx==NEW;self.event('D');self.counts['crossing']+=1;self.ret(0)
 def store(self,u,access,p,n,value,_):
  if not self.active:return
  actor={0x74:1,0x79:1,0x88:4,0x8c:4,0x90:4,0x468:4,0x46c:4,0x57a:1,0x5a1:1}
  if p-ACTOR in actor:
   assert n==actor[p-ACTOR];self.trace('A',p-ACTOR,value&((1<<(8*n))-1));self.counts['selected_stores']+=1
  elif p-WALK in (0x34,0x35,0x36):
   assert n==1;self.trace('L',p-WALK,value&255);self.counts['selected_stores']+=1
 def run(self,v):
  self.v=v;u=self.u;u.mem_write(ARENA,b'\xa5'*SIZE)
  self.put(ACTOR,0x7a3540);self.put(WALK+4,0x7aead8);self.put(WALK+0xc,ACTOR)
  for off,values in ((0x88,v[:3]),(0x2e0,[v[20],v[21],v[22],0x13579bdf,v[23],256]),(0x3fc,[v[7]])):
   for i,val in enumerate(values):self.put(ACTOR+off+4*i,val)
  for off,i in ((0x74,8),(0x79,9),(0x5a1,10),(0x57a,11)):u.mem_write(ACTOR+off,bytes([v[i]]))
  u.mem_write(ACTOR+0x468,struct.pack('<d',.375))
  for i,val in enumerate((17,23,31,*v[3:6])):self.put(WALK+0x1c+4*i,val)
  u.mem_write(WALK+0x34,bytes([v[12],173,197]));u.mem_write(0xaf9060,bytes(12))
  self.put(0xa40d2c,v[24]);self.put(0xa72f30,v[14])
  for cell,level,flags in ((OLD,v[15],v[17]),(NEW,v[16],v[18])):
   u.mem_write(cell+0x11b,bytes([level&255]));self.put(cell+0x140,flags)
  writes=[(ACTOR+off,n) for off,n in ((0x74,1),(0x79,1),(0x88,12),(0x2e0,0x14),(0x468,8),(0x57a,1),(0x5a1,1))]+[(WALK+0x34,3)]
  # Audit every other arena byte as immutable, including actual vtable pointers,
  # destination/head, Facing rate and raw padding outside the original stores.
  inputs=[];cursor=ARENA
  for lo,n in sorted(writes):
   if cursor<lo:inputs.append((cursor,lo-cursor))
   cursor=lo+n
  inputs.append((cursor,ARENA+SIZE-cursor));inputs+=list(RANGES.items())+list(TABLES.items())
  inputs += [(0xaf9060,12),(0xa40d2c,4),(0xa72f30,4)]
  self.events=[];self.lookups=0;self.active=True
  try:self.checked_call(0x71dff0,[WALK+4],writes=writes,inputs=inputs)
  finally:self.active=False
  self.event('R',u.reg_read(UC_X86_REG_EAX)&255,'Z',*self.ints(ACTOR+0x88,3),u.mem_read(ACTOR+0x74,1)[0],u.mem_read(ACTOR+0x79,1)[0],
   u.mem_read(ACTOR+0x5a1,1)[0],u.mem_read(ACTOR+0x57a,1)[0],struct.unpack('<Q',u.mem_read(ACTOR+0x468,8))[0],
   self.word(ACTOR+0x2e0),self.word(ACTOR+0x2e4),self.ints(ACTOR+0x2e8,1)[0],self.ints(ACTOR+0x2f0,1)[0],self.word(ACTOR+0x2f4),
   *u.mem_read(WALK+0x34,3),*self.ints(WALK+0x1c,6))
  return self.events
