# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete unchanged Advance with actual placement/map/floor children."""
import hashlib,struct
from original_movement import Oracle,UNIT,TYPE,LOCO,VT,STACK,STOP
from original_map_floor_height import MAP,FALLBACK,PLANES,packed
from verify_ground_drive_advance import verify,RANGES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_ESP,UC_X86_REG_EAX,UC_X86_REG_FPCW
SLOTS=0x2500000;CELLS=0x2600000
def div(n):return n//256 if n>=0 else -((-n)//256)
class GroundDriveAdvanceOracle(Oracle):
 def __init__(self,exe):
  super().__init__(exe,allow_patched=True,audit_calls=True);self.inspection=verify(exe.read_bytes())
  self.u.mem_map(SLOTS,0x100000);self.u.mem_map(CELLS,0x10000)
  for a in (0x548000,0x548070,0x55a280):del self.hooks[a]
  for off,a in ((0x19c,0x4ca160),(0x1a0,0x41b320),(0x1b4,0x5d4860)):self.put(VT+off,a)
  self.virtual(0x11c,4,self.mark,'supplied Mark')
  self.virtual(0xec,4,self.unmark,'supplied occupation unmark')
  self.virtual(0x174,4,self.notify,'supplied notification')
  self.virtual(0x490,0,self.post,'supplied post-Cell')
  self.active=False;self.entries={hex(a):0 for a in RANGES};self.stores=0;self.roots=0;self.marks=0
  self.u.hook_add(UC_HOOK_CODE,self.observe);self.u.hook_add(UC_HOOK_MEM_WRITE,self.store)
 def event(self,*v):self.events.extend(map(str,v))
 def mark(self):
  kind=self.arg(0);assert kind in (0,1);self.marks+=1
  self.event('M',kind,*struct.unpack('<iii',self.u.mem_read(UNIT+0x88,12)),self.get(UNIT+0x79,'B'),self.get(UNIT+0x74,'B'))
  if self.mark_effect:self.put(UNIT+0x74,kind,'B')
  return 1
 def unmark(self):self.event('U',*struct.unpack('<iii',self.u.mem_read(self.arg(0),12)));return 0
 def notify(self):self.event('N',self.arg(0));return 0
 def post(self):self.event('P');return 0
 def observe(self,u,a,n,ctx):
  if not self.active:return
  if a in self.hooks:
   assert self.hooks[a][2] in ('unit type','type class ID','unit class ID','non-veteran ability predicate','jumpjet predicate','supplied Mark','supplied occupation unmark','supplied notification','supplied post-Cell'),self.hooks[a][2]
   return
  if a==STOP:return
  assert any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),f'Uninspected Advance instruction {a:#x}/{n}'
  if a in RANGES:self.entries[hex(a)]+=1
  if a in (0x548000,0x55a280):self.event('C' if a==0x548000 else 'F',*struct.unpack('<iii',u.mem_read(self.arg(0),12)))
  elif a==0x548070:self.event('W',*struct.unpack('<hh',u.mem_read(self.arg(0),4)))
 def store(self,u,access,a,n,v,ctx):
  if not self.active:return
  allowed=[(STACK-0x2000,STACK+8),(UNIT+0x74,UNIT+0x75),(UNIT+0x88,UNIT+0x94),
   (UNIT+0x2e0,UNIT+0x2f8),(UNIT+0x468,UNIT+0x470),(UNIT+0x5a0,UNIT+0x5a2),
   (LOCO+0x40,LOCO+0x4c),(LOCO+0x4c,LOCO+0x50),(LOCO+0x58,LOCO+0x60),(LOCO+0x63,LOCO+0x64),
   (0x850bb8,0x850bb9),(0x850ba8,0x850bb0),(0x850bd0,0x850bd8),(PLANES,PLANES+800),(FALLBACK+0x24,FALLBACK+0x28)]
  assert any(lo<=a and a+n<=hi for lo,hi in allowed),f'Unexpected Advance write {a:#x}/{n}'
  if a in (UNIT+0x74,UNIT+0x88,UNIT+0x8c,UNIT+0x90,UNIT+0x5a0,UNIT+0x5a1):
   assert n==(1 if a in (UNIT+0x74,UNIT+0x5a0,UNIT+0x5a1) else 4)
   self.stores+=1;self.event('A',a-UNIT,v&((1<<(n*8))-1))
 def run(self,v,percentage,planes):
  track,index,acc,driving,speed,tick,steps,suppress,marked,self.mark_effect,hx,hy,hz,x,y,z,level,ramp,pattern,resident,mode=v
  self.u.mem_write(SLOTS,bytes(0x100000));self.u.mem_write(CELLS,b'\xa5'*0x10000)
  self.u.mem_write(FALLBACK,bytes(0x148));self.put(FALLBACK+0x44,-1);self.put(FALLBACK+0x24,(-7&65535)|(5<<16))
  self.u.mem_write(FALLBACK+0x11b,bytes([level&255,ramp]))
  for dy in range(-4,5):
   for dx in range(-4,5):
    cx,cy=div(hx)+dx,div(hy)+dy;slot=cy*512+cx
    if resident and 0<=slot<262144:
     a=CELLS+((dy+4)*9+dx+4)*0x200;self.u.mem_write(a,bytes(0x148));self.put(a+0x44,-1)
     self.put(a+0x116,-1,'h');self.put(a+0x24,(cx&65535)|((cy&65535)<<16))
     self.u.mem_write(a+0x11b,bytes([(level+int(bool(pattern) and dx>=0))&255,(ramp+(abs(dx)+abs(dy) if pattern else 0))%21]))
     self.put(SLOTS+4*slot,a)
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
  immutable=[*RANGES.items(),(VT,0x800),(TYPE,0x1000),(SLOTS,0x100000),(CELLS,0x10000),(MAP+0x138,8)]
  before=[bytes(self.u.mem_read(a,n)) for a,n in immutable]
  actor_before=bytes(self.u.mem_read(UNIT,0x1000));loco_before=bytes(self.u.mem_read(LOCO,0x100));fb_before=bytes(self.u.mem_read(FALLBACK,0x148))
  self.events=[];self.active=True
  try:
   for j in range(steps):
    current=((tick+j+2**31)%2**32)-2**31;self.put(0xa40d2c,current);self.u.reg_write(UC_X86_REG_FPCW,0xe7f)
    value=self.call(0x4a0bd0,[suppress],this=LOCO);assert value&255==0;self.roots+=1
    self.event('S',*struct.unpack('<iii',self.u.mem_read(UNIT+0x88,12)),*struct.unpack('<iii',self.u.mem_read(LOCO+0x40,12)),
     self.get(LOCO+0x58,'i'),self.get(LOCO+0x5c,'i'),self.get(LOCO+0x4c,'i'),self.get(LOCO+0x63,'B'),
     self.get(UNIT+0x74,'B'),self.get(UNIT+0x79,'B'),self.get(UNIT+0x5a0,'B'),self.get(UNIT+0x5a1,'B'),
     self.get(UNIT+0x2e0,'H'),self.get(UNIT+0x2e4,'H'),self.get(UNIT+0x2e8,'i'),self.get(UNIT+0x2f0,'i'))
  finally:self.active=False
  assert all(bytes(self.u.mem_read(a,n))==old for (a,n),old in zip(immutable,before))
  for a,n,old,mutable in ((UNIT,0x1000,actor_before,[(0x74,1),(0x88,12),(0x2e0,24),(0x468,8),(0x5a0,2)]),
   (LOCO,0x100,loco_before,[(0x40,16),(0x58,8),(0x63,1)]),(FALLBACK,0x148,fb_before,[(0x24,4)])):
   after=bytearray(self.u.mem_read(a,n))
   for off,size in mutable:after[off:off+size]=old[off:off+size]
   assert after==old,hex(a)
  state=bytes(self.u.mem_read(0x850bb8,1))+bytes(self.u.mem_read(0x850ba8,8))+bytes(self.u.mem_read(0x850bd0,8))+bytes(self.u.mem_read(PLANES,800))+bytes(self.u.mem_read(FALLBACK+0x24,4))
  self.event('H',hashlib.sha256(state).hexdigest());return self.events
