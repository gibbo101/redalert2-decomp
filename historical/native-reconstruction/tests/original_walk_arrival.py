# SPDX-License-Identifier: GPL-3.0-or-later
"""Actual complete Walk arrival roots; retain original committed-path oracle."""
import struct
from original_walk_movement import WalkMovementOracle,ARENA,SIZE,ACTOR,WALK,OLD,NEW
from original_presentation import STOP
from verify_walk_arrival import verify,RANGES,SERVICES,EXTRA
from verify_walk_movement import TABLES
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP
class WalkArrivalOracle(WalkMovementOracle):
 def __init__(self,exe):
  super().__init__(exe);self.inspection=verify(exe.read_bytes())
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  assert a in SERVICES or any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected arrival instruction',hex(a))
  assert not (0x71e25e<=a<0x71f077 or 0x71f63d<=a<0x71f874),('Unjoined arrival child',hex(a))
  sp=u.reg_read(UC_X86_REG_ESP);ecx=u.reg_read(UC_X86_REG_ECX);policy=self.v[58]
  if a==0x4c2df0:
   self.counts[hex(a)]+=1;assert ecx==ACTOR
   percent=struct.unpack('<d',u.mem_read(sp+4,8))[0];assert percent in (0.,1.);self.trace('V',int(percent));return
  if a in (0x5084a0,0x508410):
   assert ecx==ACTOR;point=self.ints(self.ints(sp+4,1)[0],3);self.event('U' if a==0x5084a0 else 'O',*point)
   self.counts['release' if a==0x5084a0 else 'occupy']+=1
   if a==0x5084a0:
    if policy&64:self.put(ACTOR+0x4d0,-1)
    if policy&128:
     self.put(ACTOR+0x88,self.ints(ACTOR+0x88,1)[0]+5);self.put(ACTOR+0x90,self.ints(ACTOR+0x90,1)[0]+7)
   elif policy&256:u.mem_write(ACTOR+0x74,bytes([u.mem_read(ACTOR+0x74,1)[0]^128]))
   self.ret(4,1);return
  if a==0x500aa0:
   assert ecx==ACTOR and self.ints(sp+4,1)[0]==2;self.event('J',2);self.counts['notification']+=1
   if policy&1:u.mem_write(ACTOR+0x7d,b'\0')
   if policy&2:u.mem_write(ACTOR+0x76,b'\xff')
   if policy&4:u.mem_write(ACTOR+0x7a,b'\x80')
   if policy&8:
    for offset,value in ((0x7d,1),(0x76,0),(0x7a,0)):u.mem_write(ACTOR+offset,bytes([value]))
   if policy&16:self.put(ACTOR+0x90,self.ints(ACTOR+0x90,1)[0]+15)
   if policy&32:u.mem_write(WALK+0x1c,bytes(u.mem_read(ACTOR+0x88,12)))
   self.ret(4);return
  if a==0x501ce0:
   assert ecx==ACTOR and self.ints(sp+4,2)==(0,1);self.event('G',0,1);self.counts['completion']+=1;self.ret(8);return
  if a==0x508750:assert ecx==ACTOR;self.event('X');self.counts['reset']+=1;self.ret(0);return
  if a==0x4ca6f0:self.counts[hex(a)]+=1;assert ecx==ACTOR;self.trace('P');return
  if a in EXTRA:self.counts[hex(a)]+=1
  if any(lo<=a and a+n<=lo+size for lo,size in EXTRA.items()) or 0x71f0d3<=a<0x71f2d6:return
  super().code(u,a,n,_)
 def store(self,u,access,p,n,value,_):
  if not self.active:return
  if p==ACTOR+0x450 or ACTOR+0x4d0<=p<ACTOR+0x530:
   assert n==4;self.trace('A',p-ACTOR,value&0xffffffff);self.counts['arrival_stores']+=1
  elif WALK+0x1c<=p<WALK+0x34:
   assert n==4;self.trace('L',p-WALK,value&0xffffffff);self.counts['arrival_stores']+=1
  else:super().store(u,access,p,n,value,_)
 def run_arrival(self,v):
  self.v=v;u=self.u;u.mem_write(ARENA,b'\xa5'*SIZE)
  self.put(ACTOR,0x7a3540);self.put(ACTOR+0x564,WALK+4);u.mem_write(ACTOR+0x574,b'\xff')
  self.put(WALK+4,0x7aead8);self.put(WALK+0xc,ACTOR)
  for off,values in ((0x88,v[:3]),(0x2e0,[v[20],v[21],v[22],0x13579bdf,v[23],256]),(0x3fc,[v[7]]),(0x4d0,v[25:49])):
   for i,val in enumerate(values):self.put(ACTOR+off+4*i,val)
  for off,i in ((0x74,8),(0x79,9),(0x5a1,10),(0x57a,11),(0x7d,54),(0x76,55),(0x7a,56)):u.mem_write(ACTOR+off,bytes([v[i]]))
  u.mem_write(ACTOR+0x468,struct.pack('<d',.375));u.mem_write(ACTOR+0x450,struct.pack('<hh',*v[52:54]))
  for i,val in enumerate((*v[49:52],*v[3:6])):self.put(WALK+0x1c+4*i,val)
  u.mem_write(WALK+0x34,bytes([v[12],173,197]));u.mem_write(0xaf9060,bytes(12));u.mem_write(0x865f20,bytes(12))
  self.put(0xa40d2c,v[24]);self.put(0xa72f30,v[14]);self.put(0xaf9098,v[57])
  for cell,level,flags in ((OLD,v[15],v[17]),(NEW,v[16],v[18])):
   u.mem_write(cell+0x11b,bytes([level&255]));self.put(cell+0x140,flags)
  writes=[(ACTOR+off,n) for off,n in ((0x74,1),(0x76,1),(0x79,2),(0x7d,1),(0x88,12),(0x2e0,0x14),(0x450,4),(0x468,8),(0x4d0,96),(0x57a,1),(0x5a1,1))]+[(WALK+0x1c,27)]
  inputs=[];cursor=ARENA
  for lo,n in sorted(writes):
   if cursor<lo:inputs.append((cursor,lo-cursor))
   cursor=lo+n
  inputs.append((cursor,ARENA+SIZE-cursor));inputs+=list(RANGES.items())+list(TABLES.items())
  inputs += [(0xaf9060,12),(0x865f20,12),(0xaf9098,4),(0xa40d2c,4),(0xa72f30,4)]
  self.events=[];self.lookups=0;self.active=True
  try:self.checked_call(0x71dff0,[WALK+4],writes=writes,inputs=inputs)
  finally:self.active=False
  self.event('R',u.reg_read(UC_X86_REG_EAX)&255,'Z',*self.ints(ACTOR+0x88,3),u.mem_read(ACTOR+0x74,1)[0],u.mem_read(ACTOR+0x79,1)[0],
   u.mem_read(ACTOR+0x5a1,1)[0],u.mem_read(ACTOR+0x57a,1)[0],struct.unpack('<Q',u.mem_read(ACTOR+0x468,8))[0],
   self.word(ACTOR+0x2e0),self.word(ACTOR+0x2e4),self.ints(ACTOR+0x2e8,1)[0],self.ints(ACTOR+0x2f0,1)[0],self.word(ACTOR+0x2f4),
   *u.mem_read(WALK+0x34,3),*self.ints(WALK+0x1c,6),*struct.unpack('<hh',u.mem_read(ACTOR+0x450,4)),
   u.mem_read(ACTOR+0x7d,1)[0],u.mem_read(ACTOR+0x76,1)[0],u.mem_read(ACTOR+0x7a,1)[0],*self.ints(ACTOR+0x4d0,24))
  return self.events
