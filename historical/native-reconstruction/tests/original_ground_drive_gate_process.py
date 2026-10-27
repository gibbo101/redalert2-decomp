# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete Process with unchanged original gate children in the same guest."""
import hashlib,struct
from original_ground_drive_process import GroundDriveProcessOracle
from original_ground_drive_advance import SLOTS,CELLS,div
from original_movement import UNIT,TYPE,LOCO,VT,STACK,STOP,RULES,COUNTRY
from original_map_floor_height import MAP,FALLBACK,PLANES,packed
from verify_ground_drive_gate_process import verify,RANGES
from verify_ground_drive_process import RANGES as PROCESS
from verify_movement_gate import RANGES as GATES,DISPATCH
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_EIP,UC_X86_REG_ESP,UC_X86_REG_FPCW
ARENA=0x2800000;SIZE=0x40000
OBJECTS=[UNIT,*[ARENA+i*0x1000 for i in range(1,5)]]
TYPES=[TYPE,*[ARENA+0x10000+i*0x2000 for i in range(1,5)]]
HOUSES=[ARENA+0x20000+i*0x6000 for i in range(3)]
def ptr(i):return 0 if i==-1 else OBJECTS[i]
def oid(p):return -1 if not p else OBJECTS.index(p)
def hid(p):return -1 if not p else HOUSES.index(p)
class GroundDriveGateProcessOracle(GroundDriveProcessOracle):
 def __init__(self,exe):
  super().__init__(exe);self.inspection=verify(exe.read_bytes());self.u.mem_map(ARENA,SIZE)
  del self.hooks[0x55acd0];self.put(VT+0x3c,0x6c7430)
  self.entries={hex(a):0 for a in RANGES};self.instructions=set();self.gate_returns={0:0,1:0}
  self.locations={hex(a):0 for a in (0x4a0734,0x4a0b70,0x4a3427,0x4a3433,0x4a34eb)}
  self.gate_stores=0;self.padding_stores=0;self.animation_changes=0;self.kind_returns={6:0,36:0};self.false_snapshots=0
 def extra_actor_writes(self):return ()
 def setup_gate(self,h,houses,objects,updates):
  self.gate_header=h;self.updates=updates;self.u.mem_write(ARENA,b'\xa5'*SIZE)
  self.put(UNIT+0x1b4,0 if h[7]==-1 else HOUSES[h[7]]);self.put(UNIT+0x30,ptr(h[8]))
  for p,(index,mask) in zip(HOUSES,houses):
   self.put(p+0x30,index);self.put(p+0x5674,mask);self.put(p+0x34,COUNTRY)
  for i,row in enumerate(objects,1):
   kind,next_,owner,gate,current,queued,a4,b18,b19,status,last,start,padding,remaining=row;p=OBJECTS[i]
   self.put(p,0x79cbbc if kind==6 else 0x7ad3cc);self.put(p+0x30,ptr(next_));self.put(p+0x1b4,0 if owner==-1 else HOUSES[owner]);self.put(p+0x418,TYPES[i])
   self.u.mem_write(TYPES[i]+0x1351,bytes([gate]));self.put(p+0x98,current);self.put(p+0xa0,queued);self.put(p+0xa4,a4,'B')
   self.u.mem_write(p+0x2c0,bytes([b18,b19]))
   for off,value in ((0xa8,status),(0xac,last),(0xb0,start),(0xb4,padding),(0xb8,remaining)):self.put(p+off,value)
  for slot,head in zip(h[2:4],h[4:6]):
   cell=self.get(SLOTS+slot*4) if slot!=-1 else 0
   if cell:self.put(cell+0xe4,ptr(head));self.put(cell+0xe8,ptr(4))
  self.put(FALLBACK+0xe4,ptr(h[6]));self.put(FALLBACK+0xe8,ptr(4));self.object_kinds=[1,*[r[0] for r in objects]]
 def protected(self):return b''.join(bytes(self.u.mem_read(p,n)) for p,n in ((UNIT+0x2e0,24),(UNIT+0x4d0,96),(LOCO+0x40,12),(LOCO+0x58,12)))
 def observe(self,u,a,n,ctx):
  if not self.active or a==STOP:return
  if a not in self.hooks:self.instructions.add(a)
  if hex(a) in self.locations:self.locations[hex(a)]+=1
  if a==0x4a3423:
   result=u.reg_read(UC_X86_REG_EAX)&255;assert result in (0,1);self.gate_returns[result]+=1;self.event('g','r',result)
  elif a==0x4a3427:
   assert self.protected()==self.gate_snapshot,'False gate changed Facing/route/head/track before return';self.false_snapshots+=1
  if not any(lo<=a and a+n<=lo+size for lo,size in GATES.items()):return super().observe(u,a,n,ctx)
  assert any(lo<=a and a+n<=lo+size for lo,size in GATES.items()),f'Uninspected gate instruction {a:#x}/{n}'
  if a in GATES:self.entries[hex(a)]+=1
  ecx=u.reg_read(UC_X86_REG_ECX);sp=u.reg_read(UC_X86_REG_ESP)
  if a==0x55acd0:self.gate_snapshot=self.protected();self.event('g','C',*struct.unpack('<hh',u.mem_read(self.arg(1),4)))
  elif a in (0x70a2d0,0x453c40,0x6e4b00):self.event('g','K',oid(ecx))
  elif a in (0x70a2d5,0x453c45,0x6e4b05):
   value=u.reg_read(UC_X86_REG_EAX);i=oid(ecx);assert value==self.object_kinds[i];self.kind_returns[value]+=1;self.event('g','V',i,value)
  elif a==0x4e5580:self.event('g','A',hid(ecx))
  elif a in (0x6c7430,0x410240):self.event('g','O',oid(ecx))
  elif a==0x44d7d0:self.event('g','G',oid(ecx))
  elif a==0x44d880:self.event('g','I',oid(ecx))
  elif a==0x594770:self.event('g','M',oid(ecx))
  elif a in (0x496ab0,0x496b50,0x496b30):self.event('g',{0x496ab0:'B',0x496b50:'C',0x496b30:'D'}[a],oid(ecx-0x2a8))
  elif a==0x594cb0:assert (self.arg(0),self.arg(1))==(24,0);self.event('g','Q',oid(ecx))
  elif a in (0x594710,0x594c50):
   self.event('g','S' if a==0x594710 else 'E',oid(ecx))
   if a==0x594710:assert self.arg(0)==0xffffffff
   self.put(sp-8,self.gate_header[0 if a==0x594710 else 1]);self.padding_stores+=1
 def store(self,u,access,a,n,v,ctx):
  if not self.active:return
  if ARENA<=a<ARENA+SIZE:
   i=next((i for i,p in enumerate(OBJECTS[1:],1) if p<=a<p+0x1000),None);assert i is not None,(hex(a),n)
   off=a-OBJECTS[i];assert (off,n) in ((0x98,4),(0xa0,4),(0xa4,1),(0xa8,4),(0xac,4),(0xb0,4),(0xb4,4),(0xb8,4)),(hex(a),n)
   self.event('g','W',i,off,n,v&0xffffffff);self.gate_stores+=1;return
  if a==FALLBACK+0x24 and u.reg_read(UC_X86_REG_EIP)==0x55acf8:
   assert n==4;self.event('g','F',*struct.unpack('<hh',struct.pack('<I',v&0xffffffff)));self.gate_stores+=1
  super().store(u,access,a,n,v,ctx)
 def run(self,v,extra,route,numeric,planes,h,houses,objects,updates):
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
  self.setup_gate(h,houses,objects,updates)
  immutable=[*RANGES.items(),*[(vt+off,4) for vt,rows in DISPATCH.items() for off in rows],(VT,0x800),(TYPE,0x1000),(RULES,0x2000),(SLOTS,0x100000),(CELLS,0x10000),(MAP+0x138,8),(0x850ea0,12*9*4)]
  before=[bytes(self.u.mem_read(a,n)) for a,n in immutable]
  actor_before=bytes(self.u.mem_read(UNIT,0x1000));loco_before=bytes(self.u.mem_read(LOCO,0x100));fb_before=bytes(self.u.mem_read(FALLBACK,0x148))
  gate_before=bytes(self.u.mem_read(ARENA,SIZE))
  self.events=[];self.active=True
  try:
   for j in range(steps):
    current=((tick+j+2**31)%2**32)-2**31;self.put(0xa40d2c,current);self.u.reg_write(UC_X86_REG_FPCW,0xe7f)
    for at,i,b18,b19 in updates:
     if at==j:self.u.mem_write(OBJECTS[i]+0x2c0,bytes([b18,b19]));self.animation_changes+=1;self.event('g','U',i,b18,b19)
    value=self.call(0x4a01c0,[LOCO+4],this=0);self.roots+=1
    self.event('S',value&255,*struct.unpack('<iii',self.u.mem_read(UNIT+0x88,12)),*struct.unpack('<iii',self.u.mem_read(LOCO+0x40,12)),
     self.get(LOCO+0x58,'i'),self.get(LOCO+0x5c,'i'),self.get(LOCO+0x4c,'i'),self.get(LOCO+0x63,'B'),
     self.get(UNIT+0x74,'B'),self.get(UNIT+0x5a0,'B'),self.get(UNIT+0x5a1,'B'),
     self.get(UNIT+0x2e0,'H'),self.get(UNIT+0x2e4,'H'),self.get(UNIT+0x2e8,'i'),self.get(UNIT+0x2f0,'i'),self.get(UNIT+0x2f4,'H'),
     self.get(LOCO+0x62,'B'),self.get(UNIT+0x450),self.get(UNIT+0x57b,'B'),self.get(LOCO+0x50,'Q'),self.get(UNIT+0x468,'Q'),
     *struct.unpack('<6i',self.u.mem_read(LOCO+0x1c,24)),*struct.unpack('<3i',self.u.mem_read(UNIT+0x530,12)),
     *struct.unpack('<24i',self.u.mem_read(UNIT+0x4d0,96)))
    self.event('g','R')
    for p in OBJECTS[1:]:self.event(self.get(p+0x98,'i'),self.get(p+0xa0,'i'),self.get(p+0xa4,'B'),*[self.get(p+off,'i') for off in (0xa8,0xac,0xb0,0xb4,0xb8)],*self.u.mem_read(p+0x2c0,2))
  finally:self.active=False
  assert all(bytes(self.u.mem_read(a,n))==old for (a,n),old in zip(immutable,before))
  for a,n,old,mutable in ((UNIT,0x1000,actor_before,[(0x74,1),(0x88,12),(0x2e0,24),(0x450,4),(0x468,8),(0x4d0,108),(0x57a,2),(0x5a0,2),*self.extra_actor_writes()]),
   (LOCO,0x100,loco_before,[(0x1c,24),(0x34,49)]),(FALLBACK,0x148,fb_before,[(0x24,4)])):
   after=bytearray(self.u.mem_read(a,n))
   for off,size in mutable:after[off:off+size]=old[off:off+size]
   assert after==old,hex(a)
  gate_after=bytearray(self.u.mem_read(ARENA,SIZE))
  for p in OBJECTS[1:]:
   for off,n in ((0x98,4),(0xa0,4),(0xa4,1),(0xa8,4),(0xac,4),(0xb0,4),(0xb4,4),(0xb8,4),(0x2c0,2)):
    at=p+off-ARENA;gate_after[at:at+n]=gate_before[at:at+n]
  assert bytes(gate_after)==gate_before,'Gate changed unselected object/type/House arena'
  state=bytes(self.u.mem_read(0x850bb8,1))+bytes(self.u.mem_read(0x850ba8,8))+bytes(self.u.mem_read(0x850bd0,8))+bytes(self.u.mem_read(PLANES,800))+bytes(self.u.mem_read(FALLBACK+0x24,4))
  self.event('H',hashlib.sha256(state).hexdigest());return self.events
