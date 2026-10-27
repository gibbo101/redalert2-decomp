# SPDX-License-Identifier: GPL-3.0-or-later
"""Attach explicitly bound ordinary movement services to the graphics guest.

This fixture reuses our earlier service/event contract, with disjoint arenas and
no second Unicorn instance or final-state transfer. Original instructions are
unchanged. It never calls the older movement fixture's hard-coded arena setup.
"""
import struct
from original_voxel_part import ACTOR as UNIT,VT
from original_unit_voxel_world import HOUSE
from collections import deque
from original_foot_voxel_staging import TYPE,LOCO
from original_map_preparation import MAP,FALLBACK,SLOTS
from original_map_floor_height import PLANES
from original_presentation import PresentationOracle,STACK,STOP
from original_foot_lit import ret
from verify_prepared_drive_state import RANGES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_ESP,UC_X86_REG_ECX,UC_X86_REG_EIP
RULES=0x1c01000;TYPVT=0x1c04000;STUB=0x1c00000;COUNTRY=0x1c05000
class AttachedMovement:
 def __init__(self,owner):
  self.owner=owner;self.u=owner.u;self.active=False;self.hooks={};self.events=[];self.tick=0;self.ready=False;self.mark_effect=0;self.trace=deque(maxlen=24)
  self.entries={hex(a):0 for a in RANGES};self.roots=0;self.initializations=0
  self.u.mem_map(STUB,0x6000);self.u.hook_add(UC_HOOK_CODE,self.observe);self.u.hook_add(UC_HOOK_MEM_WRITE,self.store)
 def put(self,a,v,fmt='I'):self.u.mem_write(a,struct.pack('<'+fmt,v&0xffffffff if fmt=='I' else v))
 def get(self,a,fmt='I'):return struct.unpack('<'+fmt,self.u.mem_read(a,struct.calcsize(fmt)))[0]
 def arg(self,n):return self.get(self.u.reg_read(UC_X86_REG_ESP)+4+4*n)
 def event(self,*v):self.events.extend(map(str,v))
 def bind(self,a,n,fn):self.hooks[a]=(n,fn)
 def virtual(self,off,n,fn,vt=VT):
  p=STUB+16*len(self.hooks);self.put(vt+off,p);self.bind(p,n,fn)
 def mark(self):
  kind=self.arg(0);assert kind in (0,1)
  self.event('M',kind,*struct.unpack('<3i',self.u.mem_read(UNIT+0x88,12)),self.get(UNIT+0x79,'B'),self.get(UNIT+0x74,'B'))
  if self.mark_effect:self.put(UNIT+0x74,kind,'B')
  return 1
 def unmark(self):self.event('U',*struct.unpack('<3i',self.u.mem_read(self.arg(0),12)));return 0
 def notify(self):self.event('N',self.arg(0));return 0
 def post(self):self.event('P');return 0
 def admit(self):self.event('D',*struct.unpack('<2h',self.u.mem_read(self.arg(0)+0x24,4)),self.arg(1),self.arg(2));return 0
 def mark_next(self):self.event('K',*struct.unpack('<2h',self.u.mem_read(self.arg(0),4)));return 0
 def occupation(self):self.event('E',*struct.unpack('<3i',self.u.mem_read(self.arg(0),12)));return 0
 def reserve(self):self.event('R',*struct.unpack('<2h',self.u.mem_read(self.arg(1),4)));return 1
 def pathfinder(self):self.event('B');return 0
 def accessible(self):self.event('J');return 0
 def mission(self):self.event('V',self.arg(0),self.arg(1));return 0
 def observe(self,u,a,n,ctx):
  if not self.active:return
  self.trace.append(a)
  if a in self.hooks:
   count,fn=self.hooks[a];ret(u,count,fn());return
  assert a==STOP or any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),f'Uninspected attached movement {a:#x}/{n}'
  if hex(a) in self.entries:self.entries[hex(a)]+=1
  if a in (0x548000,0x55a280):self.event('C' if a==0x548000 else 'F',*struct.unpack('<3i',u.mem_read(self.arg(0),12)))
  elif a==0x548070:self.event('W',*struct.unpack('<2h',u.mem_read(self.arg(0),4)))
  elif a==0x475d60:self.event('T',*struct.unpack('<2h',u.mem_read(u.reg_read(UC_X86_REG_ECX)+0x24,4)))
  elif a==0x4a062b:self.put(u.reg_read(UC_X86_REG_ESP)+0x14,7)
  elif a==0x4a2670:self.put(u.reg_read(UC_X86_REG_ESP)-0x14,7)
  elif a==0x49fc30:self.put(u.reg_read(UC_X86_REG_ESP)-12,7)
  if a in (0x548000,0x548070):
   if a==0x548000:
    x,y,_=struct.unpack('<3i',u.mem_read(self.arg(0),12));x=x//256 if x>=0 else -((-x)//256);y=y//256 if y>=0 else -((-y)//256)
   else:x,y=struct.unpack('<2h',u.mem_read(self.arg(0),4))
   slot=(y*512+x)&0xffffffff;p=self.get(SLOTS+4*slot) if slot<262144 else 0
   assert self.get((p or FALLBACK)+0x44,'i')==-1,'Movement refuses overlay Cells'
 def store(self,u,access,a,n,v,ctx):
  if not self.active:return
  if a in (UNIT+0x74,UNIT+0x88,UNIT+0x8c,UNIT+0x90,UNIT+0x450,UNIT+0x5a0,UNIT+0x5a1):self.event('A',a-UNIT,v&((1<<(n*8))-1))
  if LOCO+0x1c<=a<LOCO+0x34:self.event('L',a-LOCO,v&0xffffffff)
 def call(self,a,args=(),ecx=0):
  inputs=[*self.owner.map_inputs(),(TYPE,0xc00),(VT,0x600),(TYPVT,0x100),(RULES,0x2000),(0xaf8608,21*48),(0xaf6618,21*16),(0x850ea0,12*9*4)]
  writes=[(UNIT+0x74,1),(UNIT+0x88,12),(UNIT+0x2e0,24),(UNIT+0x450,4),(UNIT+0x468,8),(UNIT+0x4d0,108),(UNIT+0x57a,2),(UNIT+0x5a0,2),
   (LOCO+0x1c,24),(LOCO+0x34,49),(0x850bb8,1),(0x850ba8,8),(0x850bd0,8),(PLANES,800),(FALLBACK+0x24,4)]
  actor=bytes(self.u.mem_read(UNIT,0x1000));loco=bytes(self.u.mem_read(LOCO,0x100));fb=bytes(self.u.mem_read(FALLBACK,0x148))
  self.active=True
  try:PresentationOracle.checked_call(self.owner,a,args,ecx,writes=writes,inputs=inputs)
  except Exception:
   print('Attached movement stopped',hex(self.u.reg_read(UC_X86_REG_EIP)),list(map(hex,self.trace)),flush=True);raise
  finally:self.active=False
  for p,old,mutable in ((UNIT,actor,[(0x74,1),(0x88,12),(0x2e0,24),(0x450,4),(0x468,8),(0x4d0,108),(0x57a,2),(0x5a0,2)]),
    (LOCO,loco,[(0x1c,24),(0x34,49)]),(FALLBACK,fb,[(0x24,4)])):
   now=bytearray(self.u.mem_read(p,len(old)))
   for off,size in mutable:now[off:off+size]=old[off:off+size]
   assert now==old,hex(p)
 def begin(self,v,route,numeric):
  x,y,z,dx,dy,dz,heading,rot,speed,tick,steps,marked,effect,mode,present,key=v
  assert present==1 and key==0 # Unit owns the actual pose seeds in this join.
  assert self.get(MAP+0x138)==SLOTS and self.get(MAP+0x13c)==262144
  self.events=[];self.ready=False;self.tick=tick;self.speed=speed;self.mark_effect=effect
  self.u.mem_write(UNIT,bytes(0x1000));self.u.mem_write(VT,bytes(self.u.mem_read(0x7addf8,0x600)))
  indexes=[bytes(self.u.mem_read(TYPE+o,20)) for o in (0x214,0x228,0x250,0x23c)]
  self.u.mem_write(TYPE,bytes(0xc00));self.u.mem_write(LOCO,bytes(0x100));self.hooks={}
  for off,b in zip((0x214,0x228,0x250,0x23c),indexes):self.u.mem_write(TYPE+off,b)
  for p,val in ((UNIT,VT),(UNIT+0x5ac,TYPE),(UNIT+0x1b4,HOUSE),(HOUSE+0x34,COUNTRY),(TYPE,TYPVT),(LOCO,0x7a0594),(LOCO+4,0x7a04cc),(LOCO+8,UNIT),(LOCO+12,UNIT),(UNIT+0x564,LOCO+4),
   (TYPE+0xa0,400),(UNIT+0x6c,400),(TYPE+0x5a0,speed),(TYPE+0x5a4,1),(UNIT+0x5b4,-1),(UNIT+0x154,-1),(0x839848,RULES),(0xa40d2c,tick),(0xa72f30,416)):self.put(p,val)
  for off,a in ((0x48,0x5d4e40),(0x80,0x6c12c0),(0x84,0x705020),(0x19c,0x4ca160),(0x1a0,0x41b320),(0x1a4,0x5d51e0),(0x1b4,0x5d4860),(0x1b8,0x5d4800),(0x338,0x6d8e90),(0x4bc,0x4c9b10),(0x4c8,0x4c2df0)):self.put(VT+off,a)
  for off,count,value in ((0x2c,0,1),(0xbc,0,0),(0x1bc,0,0),(0x1c0,0,0),(0x324,0,0),(0x328,0,0),(0x27c,0,1),(0x16c,0,2)):
   self.virtual(off,count,lambda value=value:value)
  self.virtual(0x2c,0,lambda:40,TYPVT)
  for off,count,fn in ((0x11c,4,self.mark),(0xec,4,self.unmark),(0x174,4,self.notify),(0x490,0,self.post),(0x194,20,self.admit),(0x4b8,8,self.mark_next),(0xe8,4,self.occupation),(0x2ac,4,self.accessible),(0x410,8,self.mission)):self.virtual(off,count,fn)
  for a,count,fn in ((0x55acd0,8,self.reserve),(0x4c3000,12,self.pathfinder),(0x6d7910,4,lambda:0),(0x476cc0,4,lambda:1)):self.bind(a,count,fn)
  for p,val in ((UNIT+0x74,marked),(UNIT+0x7d,1),(UNIT+0x5a0,7),(UNIT+0x5a1,9),(LOCO+0x10,1),(LOCO+0x65,1),(TYPE+0xaab,1)):self.put(p,val,'B')
  self.u.mem_write(UNIT+0x88,struct.pack('<3i',x,y,z));self.u.mem_write(UNIT+0x2e0,struct.pack('<IIiiiI',heading,heading,0,0,0,rot*256))
  self.u.mem_write(UNIT+0x4d0,struct.pack('<24i',*route));self.u.mem_write(UNIT+0x530,struct.pack('<3i',-1,7,0))
  self.u.mem_write(LOCO+0x34,struct.pack('<3i',dx,dy,dz));self.put(LOCO+0x58,-1)
  percentage,land,up,down=numeric
  for p,val in ((UNIT+0x468,1.),(UNIT+0x470,1.),(LOCO+0x50,percentage),(TYPE+0x330,30.5),(TYPE+0x338,24.25),(RULES+0x690,up),(RULES+0x698,down),(RULES+0x13c8,0.)):self.put(p,val,'d')
  self.put(COUNTRY+0x12c,1.,'f');self.put(RULES+0x1368,.5,'d')
  for i in range(12):self.put(0x850ea0+4*(i*9+1),land*(1.-i/16.),'f')
  self.call(0x5d4860,[0],UNIT);self.call(0x4a05c0,[LOCO+4]);self.initializations+=1;self.ready=True
  self.advance(steps,first=True)
  return self.events
 def advance(self,steps,first=False):
  assert self.ready
  if not first:self.events=[]
  for j in range(steps):
   if not first or j:self.tick=((self.tick+1+2**31)%2**32)-2**31
   self.put(0xa40d2c,self.tick);self.call(0x4a05f0,[LOCO+4]);self.roots+=1;self.state_event()
  return self.events
 def state_event(self):
  self.event('S',*struct.unpack('<3i',self.u.mem_read(UNIT+0x88,12)),*struct.unpack('<3i',self.u.mem_read(LOCO+0x40,12)),
   self.get(LOCO+0x58,'i'),self.get(LOCO+0x5c,'i'),self.get(LOCO+0x4c,'i'),self.get(LOCO+0x63,'B'),self.get(UNIT+0x74,'B'),self.get(UNIT+0x5a0,'B'),self.get(UNIT+0x5a1,'B'),
   self.get(UNIT+0x2e0,'H'),self.get(UNIT+0x2e4,'H'),self.get(UNIT+0x2e8,'i'),self.get(UNIT+0x2f0,'i'),self.get(UNIT+0x2f4,'H'),self.get(LOCO+0x62,'B'),self.get(UNIT+0x450),self.get(UNIT+0x57b,'B'),
   self.get(LOCO+0x50,'Q'),self.get(UNIT+0x468,'Q'),*struct.unpack('<6i',self.u.mem_read(LOCO+0x1c,24)),*struct.unpack('<3i',self.u.mem_read(UNIT+0x530,12)),*struct.unpack('<24i',self.u.mem_read(UNIT+0x4d0,96)))
