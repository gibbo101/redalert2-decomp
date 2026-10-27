# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete unchanged ordinary Process with terrain children and supplied routes."""
import hashlib,struct
from original_ground_drive_advance import GroundDriveAdvanceOracle,SLOTS,CELLS,div
from original_movement import UNIT,TYPE,LOCO,VT,STACK,STOP,RULES
from original_map_floor_height import MAP,FALLBACK,PLANES,packed
from verify_ground_drive_process import verify,RANGES
from unicorn.x86_const import UC_X86_REG_ESP,UC_X86_REG_ECX,UC_X86_REG_FPCW
class GroundDriveProcessOracle(GroundDriveAdvanceOracle):
 def __init__(self,exe):
  super().__init__(exe);self.inspection=verify(exe.read_bytes());self.entries={hex(a):0 for a in RANGES}
  for off,a in ((0x48,0x5d4e40),(0x1a4,0x5d51e0),(0x1b8,0x5d4800)):self.put(VT+off,a)
  self.virtual(0x194,20,self.admit,'supplied empty admission')
  self.virtual(0x4b8,8,self.mark_next,'supplied next Cell')
  self.virtual(0xe8,4,self.occupation,'supplied occupation mark')
  self.virtual(0x2ac,4,self.accessible,'supplied inaccessible route')
  self.virtual(0x410,8,self.mission,'supplied mission transition')
  self.hooks[0x55acd0]=(8,self.reserve,'supplied reservation')
  self.hooks[0x4c3000]=(12,self.pathfinder,'supplied failed pathfinder')
 def admit(self):
  self.event('D',*struct.unpack('<hh',self.u.mem_read(self.arg(0)+0x24,4)),self.arg(1),self.arg(2));return 0
 def mark_next(self):self.event('K',*struct.unpack('<hh',self.u.mem_read(self.arg(0),4)));return 0
 def occupation(self):self.event('E',*struct.unpack('<iii',self.u.mem_read(self.arg(0),12)));return 0
 def reserve(self):self.event('R',*struct.unpack('<hh',self.u.mem_read(self.arg(1),4)));return 1
 def pathfinder(self):self.event('B');return 0
 def accessible(self):self.event('J');return 0
 def mission(self):self.event('V',self.arg(0),self.arg(1));return 0
 def observe(self,u,a,n,ctx):
  if not self.active:return
  if a in self.hooks:
   allowed=('unit type','type class ID','unit class ID','non-veteran ability predicate','jumpjet predicate',
    'supplied Mark','supplied occupation unmark','supplied notification','supplied post-Cell','immobilized A','immobilized B',
    'disabled A','disabled B','eligible mover','supplied empty admission','supplied next Cell','supplied occupation mark',
    'supplied inaccessible route','supplied mission transition','supplied reservation','supplied failed pathfinder','empty-cell occupation','mission move','object type')
   assert self.hooks[a][2] in allowed,self.hooks[a][2];return
  if a==STOP:return
  assert any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),f'Uninspected Process instruction {a:#x}/{n}'
  if a in RANGES:self.entries[hex(a)]+=1
  if a in (0x548000,0x55a280):self.event('C' if a==0x548000 else 'F',*struct.unpack('<iii',u.mem_read(self.arg(0),12)))
  elif a==0x548070:self.event('W',*struct.unpack('<hh',u.mem_read(self.arg(0),4)))
  elif a==0x475d60:self.event('T',*struct.unpack('<hh',u.mem_read(u.reg_read(UC_X86_REG_ECX)+0x24,4)))
  # Explicit opaque temporary padding, supplied at the parent/child boundary.
  elif a==0x4a062b:self.put(u.reg_read(UC_X86_REG_ESP)+0x14,7)
  elif a==0x4a2670:self.put(u.reg_read(UC_X86_REG_ESP)-0x14,7)
 def store(self,u,access,a,n,v,ctx):
  if not self.active:return
  allowed=[(STACK-0x2000,STACK+8),(UNIT+0x74,UNIT+0x75),(UNIT+0x88,UNIT+0x94),
   (UNIT+0x2e0,UNIT+0x2f8),(UNIT+0x450,UNIT+0x454),(UNIT+0x468,UNIT+0x470),
   (UNIT+0x4d0,UNIT+0x53c),(UNIT+0x57a,UNIT+0x57c),(UNIT+0x5a0,UNIT+0x5a2),
   (LOCO+0x1c,LOCO+0x34),(LOCO+0x34,LOCO+0x65),
   (0x850bb8,0x850bb9),(0x850ba8,0x850bb0),(0x850bd0,0x850bd8),(PLANES,PLANES+800),(FALLBACK+0x24,FALLBACK+0x28)]
  assert any(lo<=a and a+n<=hi for lo,hi in allowed),f'Unexpected Process write {a:#x}/{n}'
  if a in (UNIT+0x74,UNIT+0x88,UNIT+0x8c,UNIT+0x90,UNIT+0x450,UNIT+0x5a0,UNIT+0x5a1):
   self.stores+=1;self.event('A',a-UNIT,v&((1<<(n*8))-1))
  if LOCO+0x1c<=a<LOCO+0x34:self.event('L',a-LOCO,v&0xffffffff)
 def run(self,v,extra,route,numeric,planes):
  track,index,acc,driving,speed,tick,steps,suppress,marked,self.mark_effect,hx,hy,hz,x,y,z,level,ramp,pattern,resident,mode=v
  heading,rot,initialRamp,dest=extra;percentage,landSpeed,uphill,downhill=numeric
  self.u.mem_write(SLOTS,bytes(0x100000));self.u.mem_write(CELLS,b'\xa5'*0x10000)
  self.u.mem_write(FALLBACK,bytes(0x148));self.put(FALLBACK+0x44,-1);self.put(FALLBACK+0x24,(-7&65535)|(5<<16))
  self.u.mem_write(FALLBACK+0x11b,bytes([level&255,ramp]));self.put(FALLBACK+0xec,3)
  for dy in range(-4,5):
   for dx in range(-4,5):
    cx,cy=div(hx)+dx,div(hy)+dy;slot=cy*512+cx
    if resident and 0<=slot<262144:
     a=CELLS+((dy+4)*9+dx+4)*0x200;self.u.mem_write(a,bytes(0x148));self.put(a+0x44,-1)
     self.put(a+0x116,-1,'h');self.put(a+0x24,(cx&65535)|((cy&65535)<<16))
     self.u.mem_write(a+0x11b,bytes([(level+3*int(bool(pattern) and dx>=0))&255,(ramp+(abs(dx)+abs(dy) if pattern else 0))%21]))
     self.put(a+0xec,(abs(dx)+abs(dy))%12 if pattern else 0);self.put(SLOTS+4*slot,a)
  self.put(MAP+0x138,SLOTS);self.put(MAP+0x13c,262144);self.put(0x850c40,104);self.put(0xa72f30,416)
  self.u.mem_write(0x850bb8,b'\0');self.u.mem_write(0x850ba8,bytes(8));self.u.mem_write(0x850bd0,bytes(8));self.u.mem_write(PLANES,struct.pack('<100Q',*planes))
  self.u.mem_write(UNIT+0x88,packed([x,y,z]));self.put(UNIT+0x74,marked,'B');self.put(UNIT+0x79,0,'B');self.put(UNIT+0x7d,1,'B')
  self.put(UNIT+0x494,0);self.put(UNIT+0x4d0,-1);self.put(TYPE+0xb59,0,'B');self.put(TYPE+0x5a0,speed)
  self.put(TYPE+0xaa0,0,'B')
  self.put(UNIT+0x468,1.,'d');self.put(UNIT+0x5a0,7,'B');self.put(UNIT+0x5a1,9,'B')
  self.u.mem_write(UNIT+0x2e0,struct.pack('<IIiiiI',0,0,0,0,0,1280))
  self.u.mem_write(LOCO+0x34,bytes(12));self.u.mem_write(LOCO+0x40,packed([hx,hy,hz]))
  self.put(LOCO+0x58,track);self.put(LOCO+0x5c,index);self.put(LOCO+0x4c,acc);self.put(LOCO+0x63,driving,'B')
  self.put(LOCO+0x60,0,'B');self.put(LOCO+0x62,0,'B');self.put(LOCO+0x50,percentage,'d')
  self.u.mem_write(LOCO+0x40,bytes(12) if track==-1 else packed([hx,hy,hz]))
  self.u.mem_write(LOCO+0x34,packed([hx,hy,hz]) if dest else bytes(12))
  self.u.mem_write(UNIT+0x4d0,struct.pack('<24i',*route));self.put(UNIT+0x57a,0,'B');self.put(UNIT+0x57b,0,'B');self.put(UNIT+0x450,0)
  self.u.mem_write(UNIT+0x530,struct.pack('<iii',-1,7,0))
  self.u.mem_write(UNIT+0x2e0,struct.pack('<IIiiiI',heading,heading,0,0,0,rot*256))
  self.u.mem_write(LOCO+0x1c,struct.pack('<6i',initialRamp,initialRamp,99,7,2,2))
  self.put(TYPE+0xba4,0,'B');self.put(LOCO+0x61,0,'B')
  self.put(RULES+0x13c8,0.,'d');self.put(RULES+0x690,uphill,'d');self.put(RULES+0x698,downhill,'d')
  for land in range(12):self.put(0x850ea0+4*(land*9+1),landSpeed*(1.-land/16.),'f')
  immutable=[*RANGES.items(),(VT,0x800),(TYPE,0x1000),(RULES,0x2000),(SLOTS,0x100000),(CELLS,0x10000),(MAP+0x138,8),(0x850ea0,12*9*4)]
  before=[bytes(self.u.mem_read(a,n)) for a,n in immutable]
  actor_before=bytes(self.u.mem_read(UNIT,0x1000));loco_before=bytes(self.u.mem_read(LOCO,0x100));fb_before=bytes(self.u.mem_read(FALLBACK,0x148))
  self.events=[];self.active=True
  try:
   for j in range(steps):
    current=((tick+j+2**31)%2**32)-2**31;self.put(0xa40d2c,current);self.u.reg_write(UC_X86_REG_FPCW,0xe7f)
    value=self.call(0x4a01c0,[LOCO+4],this=0);self.roots+=1
    self.event('S',value&255,*struct.unpack('<iii',self.u.mem_read(UNIT+0x88,12)),*struct.unpack('<iii',self.u.mem_read(LOCO+0x40,12)),
     self.get(LOCO+0x58,'i'),self.get(LOCO+0x5c,'i'),self.get(LOCO+0x4c,'i'),self.get(LOCO+0x63,'B'),
     self.get(UNIT+0x74,'B'),self.get(UNIT+0x5a0,'B'),self.get(UNIT+0x5a1,'B'),
     self.get(UNIT+0x2e0,'H'),self.get(UNIT+0x2e4,'H'),self.get(UNIT+0x2e8,'i'),self.get(UNIT+0x2f0,'i'),self.get(UNIT+0x2f4,'H'),
     self.get(LOCO+0x62,'B'),self.get(UNIT+0x450),self.get(UNIT+0x57b,'B'),self.get(LOCO+0x50,'Q'),self.get(UNIT+0x468,'Q'),
     *struct.unpack('<6i',self.u.mem_read(LOCO+0x1c,24)),*struct.unpack('<3i',self.u.mem_read(UNIT+0x530,12)),
     *struct.unpack('<24i',self.u.mem_read(UNIT+0x4d0,96)))
  finally:self.active=False
  assert all(bytes(self.u.mem_read(a,n))==old for (a,n),old in zip(immutable,before))
  for a,n,old,mutable in ((UNIT,0x1000,actor_before,[(0x74,1),(0x88,12),(0x2e0,24),(0x450,4),(0x468,8),(0x4d0,108),(0x57a,2),(0x5a0,2)]),
   (LOCO,0x100,loco_before,[(0x1c,24),(0x34,49)]),(FALLBACK,0x148,fb_before,[(0x24,4)])):
   after=bytearray(self.u.mem_read(a,n))
   for off,size in mutable:after[off:off+size]=old[off:off+size]
   assert after==old,hex(a)
  state=bytes(self.u.mem_read(0x850bb8,1))+bytes(self.u.mem_read(0x850ba8,8))+bytes(self.u.mem_read(0x850bd0,8))+bytes(self.u.mem_read(PLANES,800))+bytes(self.u.mem_read(FALLBACK+0x24,4))
  self.event('H',hashlib.sha256(state).hexdigest());return self.events
