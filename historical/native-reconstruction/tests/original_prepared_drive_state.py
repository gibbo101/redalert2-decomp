# SPDX-License-Identifier: GPL-3.0-or-later
"""Actual finalized map, Process, height/ramp writers and both Drive poses in one guest."""
import hashlib,struct
from original_ground_drive_process import GroundDriveProcessOracle
from original_ground_drive_advance import SLOTS as OLD_SLOTS,CELLS as OLD_CELLS,div
from original_movement import UNIT,TYPE,LOCO,VT,RULES
from original_prepared_unit_world import AttachedMap
from original_ground_unit_world import AttachedGeometry
from original_map_preparation import MAP,FALLBACK,CELLS,TYPES,REGISTRY,SLOTS
from original_resident_map_preparation import IMAGES
from original_resident_map_finalization import OVERLAYS,OVERLAY_REG
from original_presentation import PresentationOracle,STOP
from original_map_floor_height import PLANES
from verify_prepared_drive_state import RANGES
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EAX

OUT=0x1121000;KEY=OUT+64
class AttachedPresentation(PresentationOracle):
 def __init__(self,owner):self.u=owner.u;self.audit_calls=self.audit_blocks=0
 def va(self,a):return a

class PreparedDriveStateOracle(GroundDriveProcessOracle):
 def __init__(self,exe):
  self.pose_active=False;self.initializing=False;self.numeric_active=False;self.pose_calls=0;self.initializations=0
  super().__init__(exe)
  # The older movement fixture's synthetic map arenas are unused here. Replace
  # only these private allocations with the disjoint prepared-map arena layout.
  self.u.mem_unmap(OLD_SLOTS,0x100000);self.u.mem_unmap(OLD_CELLS,0x10000)
  self.prepared=AttachedMap(self);self.presentation=AttachedPresentation(self)
  self.numeric=AttachedGeometry(self.presentation)
  self.all_entries={hex(a):0 for a in RANGES}
  self.coverage={'different_body_shadow_matrices':0,'stored_vs_current_Cell_ramp_lag':0,
   'distinct_stored_previous_current_ramps':0,'positive_relative_height':0,'negative_relative_height':0}
  self.map_ready=False;self.prepared_hash=None
  self.u.hook_add(UC_HOOK_CODE,self.force_padding,begin=0x49fc30,end=0x49fc30)
 def va(self,a):
  return a if a in (0x5d4860,0x4a05c0) else super().va(a)
 def hook(self,u,a,n,ctx):
  # Named movement services have no role during map/numeric setup or poses.
  if getattr(self,'active',False):super().hook(u,a,n,ctx)
 def observe(self,u,a,n,ctx):
  if self.active:
   if a in self.hooks:
    super().observe(u,a,n,ctx);return
   if a in (0x548000,0x548070):
    if a==0x548000:x,y,_=struct.unpack('<3i',u.mem_read(self.arg(0),12));x,y=div(x),div(y)
    else:x,y=struct.unpack('<2h',u.mem_read(self.arg(0),4))
    slot=(y*512+x)&0xffffffff
    p=self.get(SLOTS+slot*4) if slot<262144 else 0
    self.check_cell(p or FALLBACK)
   if self.initializing:
    from original_movement import STOP as MOVEMENT_STOP
    assert a==MOVEMENT_STOP or any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),f'Uninspected prepared placement {a:#x}/{n}'
    if a in (0x548000,0x55a280):self.event('C' if a==0x548000 else 'F',*struct.unpack('<3i',u.mem_read(self.arg(0),12)))
   else:super().observe(u,a,n,ctx)
  elif self.pose_active:
   if a==STOP:return
   assert any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),f'Uninspected joined Drive pose {a:#x}/{n}'
   if a==0x705020:self.event('t')
   elif a==0x4b8be0:self.event('f')
   elif a==0x548000:self.event('c')
  elif self.numeric_active:
   assert a==STOP or any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),f'Uninspected joined numeric setup {a:#x}/{n}'
  else:return
  if hex(a) in self.all_entries:self.all_entries[hex(a)]+=1
 def store(self,u,access,a,n,v,ctx):
  if self.active:super().store(u,access,a,n,v,ctx)
  elif self.pose_active and a==KEY:
   assert n==4;self.event('k',v&0xffffffff)
 def check_cell(self,p):
  assert self.get(p+0x44,'i')==-1,'Prepared movement profile refuses overlay Cells'
 def prepare_map(self,f):
  assert f[4]==104
  self.map_ready=False;result=self.prepared.prepare(f)
  self.put(MAP+0x13c,262144)
  # Both original numeric chains and complete stock matrix/quaternion setup run
  # on this same guest. No final prepared state is imported from another guest.
  self.numeric_active=True
  try:self.numeric.stock(0)
  finally:self.numeric_active=False
  self.map_ready=True
  return result
 def map_inputs(self):
  p=self.prepared
  return [(CELLS,p.count*512),(SLOTS,0x100000),(TYPES,p.type_count*1024),
   (IMAGES,p.type_count*4096),(REGISTRY,p.type_count*4+64),
   (OVERLAYS,p.overlay_count*1024),(OVERLAY_REG,p.overlay_count*4+64),(MAP+0x138,8)]
 def begin_actor(self,v,route,numeric):
  x,y,z,dx,dy,dz,heading,rot,speed,tick,steps,marked,effect,mode,present,key=v
  percentage,landSpeed,uphill,downhill=numeric
  self.mark_effect=effect;self.events=[]
  self.u.mem_write(UNIT+0x88,struct.pack('<3i',x,y,z))
  for off,n,fmt in ((0x74,marked,'B'),(0x79,0,'B'),(0x7d,1,'B'),(0x494,0,'I'),(0x468,1.,'d'),(0x5a0,7,'B'),(0x5a1,9,'B'),(0x450,0,'I'),(0x57a,0,'B'),(0x57b,0,'B')):self.put(UNIT+off,n,fmt)
  self.u.mem_write(UNIT+0x280,bytes(8))
  self.u.mem_write(UNIT+0x2e0,struct.pack('<IIiiiI',heading,heading,0,0,0,rot*256))
  self.u.mem_write(UNIT+0x4d0,struct.pack('<24i',*route));self.u.mem_write(UNIT+0x530,struct.pack('<iii',-1,7,0))
  self.u.mem_write(LOCO+0x1c,bytes(24));self.u.mem_write(LOCO+0x34,struct.pack('<3i',dx,dy,dz));self.u.mem_write(LOCO+0x40,bytes(12))
  for off,n,fmt in ((0x4c,0,'I'),(0x50,percentage,'d'),(0x58,-1,'I'),(0x5c,0,'I'),(0x60,0,'B'),(0x61,0,'B'),(0x62,0,'B'),(0x63,0,'B')):self.put(LOCO+off,n,fmt)
  for off,n,fmt in ((0xb59,0,'B'),(0xaa0,0,'B'),(0xba4,0,'B'),(0x5a0,speed,'I'),(0x330,30.5,'d'),(0x338,24.25,'d')):self.put(TYPE+off,n,fmt)
  self.put(0x839848,RULES);self.put(RULES+0x13c8,0.,'d');self.put(RULES+0x690,uphill,'d');self.put(RULES+0x698,downhill,'d')
  for land in range(12):self.put(0x850ea0+4*(land*9+1),landSpeed*(1.-land/16.),'f')
  self.put(0xa40d2c,tick);self.put(0xa72f30,416)
  self.active=self.initializing=True
  try:
   self.call(0x5d4860,[0],this=UNIT)
   # Explicit opaque padding at the Force child boundary, as in the separate
   # writer proof. Initialization has no original caller/startup-order claim.
   self.call(0x4a05c0,[LOCO+4],this=0)
  finally:self.active=self.initializing=False
  self.initializations+=1
 def force_padding(self,u,a,n,ctx):
  if self.active:self.put(u.reg_read(UC_X86_REG_ESP)-12,7)
 def state_event(self,result):
  self.event('S',result&255,*struct.unpack('<3i',self.u.mem_read(UNIT+0x88,12)),*struct.unpack('<3i',self.u.mem_read(LOCO+0x40,12)),
   self.get(LOCO+0x58,'i'),self.get(LOCO+0x5c,'i'),self.get(LOCO+0x4c,'i'),self.get(LOCO+0x63,'B'),
   self.get(UNIT+0x74,'B'),self.get(UNIT+0x5a0,'B'),self.get(UNIT+0x5a1,'B'),
   self.get(UNIT+0x2e0,'H'),self.get(UNIT+0x2e4,'H'),self.get(UNIT+0x2e8,'i'),self.get(UNIT+0x2f0,'i'),self.get(UNIT+0x2f4,'H'),
   self.get(LOCO+0x62,'B'),self.get(UNIT+0x450),self.get(UNIT+0x57b,'B'),self.get(LOCO+0x50,'Q'),self.get(UNIT+0x468,'Q'),
   *struct.unpack('<6i',self.u.mem_read(LOCO+0x1c,24)),*struct.unpack('<3i',self.u.mem_read(UNIT+0x530,12)),*struct.unpack('<24i',self.u.mem_read(UNIT+0x4d0,96)))
 def poses(self,tick,present,key):
  table=bytes(self.u.mem_read(VT,0x800))
  self.put(VT+0x80,0x6c12c0);self.put(VT+0x84,0x705020)
  immutable=[*self.map_inputs(),(UNIT,0x1000),(TYPE,0x1000),(LOCO,0x100),(VT,0x800),
   (0xaf8608,21*48),(0xaf6618,21*16),(0x850c40,4),(0xa40d2c,4)]
  self.pose_active=True;matrices=[]
  try:
   for name,root in (('body',0x4a0050),('shadow',0x4a0500)):
    self.event(name);self.put(KEY,key)
    self.presentation.checked_call(root,[LOCO+4,OUT,KEY if present else 0],
     writes=[(OUT,48),(KEY,4),(FALLBACK+0x24,4)],inputs=immutable)
    assert self.u.reg_read(UC_X86_REG_EAX)==OUT
    self.event('matrix',*struct.unpack('<12I',self.u.mem_read(OUT,48)),self.get(KEY))
    matrices.append(bytes(self.u.mem_read(OUT,48)))
    self.pose_calls+=1
   self.presentation.checked_call(0x5d4810,ecx=UNIT,
    writes=[(FALLBACK+0x24,4),(0x850bb8,1),(0x850ba8,8),(0x850bd0,8),(PLANES,800)],inputs=immutable)
   relative=self.get_register_signed();self.event('relative',relative)
   self.coverage['different_body_shadow_matrices']+=matrices[0]!=matrices[1]
   self.coverage['positive_relative_height']+=relative>0;self.coverage['negative_relative_height']+=relative<0
  finally:self.pose_active=False;self.u.mem_write(VT,table)
 def get_register_signed(self):
  n=self.u.reg_read(UC_X86_REG_EAX);return n-2**32 if n>=2**31 else n
 def run_prepared(self,v,route,numeric):
  assert self.map_ready
  immutable=[*self.map_inputs(),*[(a,n) for a,n in RANGES.items()],(0xaf8608,21*48),(0xaf6618,21*16)]
  before=[bytes(self.u.mem_read(a,n)) for a,n in immutable]
  self.begin_actor(v,route,numeric)
  arena_inputs=[(VT,0x800),(TYPE,0x1000),(RULES,0x2000)]
  old_inputs=[bytes(self.u.mem_read(a,n)) for a,n in arena_inputs]
  actor_before=bytes(self.u.mem_read(UNIT,0x1000));loco_before=bytes(self.u.mem_read(LOCO,0x100));fb_before=bytes(self.u.mem_read(FALLBACK,0x148))
  tick,steps=v[9:11]
  for j in range(steps):
   current=((tick+j+2**31)%2**32)-2**31;self.put(0xa40d2c,current);self.active=True
   try:value=self.call(0x4a01c0,[LOCO+4],this=0);self.roots+=1
   finally:self.active=False
   x,y,_=struct.unpack('<3i',self.u.mem_read(UNIT+0x88,12));slot=(div(y)*512+div(x))&0xffffffff
   p=self.get(SLOTS+slot*4) if slot<262144 else 0;p=p or FALLBACK
   self.coverage['stored_vs_current_Cell_ramp_lag']+=self.get(LOCO+0x1c)!=self.get(p+0x11c,'B')
   self.coverage['distinct_stored_previous_current_ramps']+=self.get(LOCO+0x1c)!=self.get(LOCO+0x20)
   self.state_event(value);self.poses(current,v[14],v[15])
  assert all(bytes(self.u.mem_read(a,n))==old for (a,n),old in zip(immutable,before))
  assert all(bytes(self.u.mem_read(a,n))==old for (a,n),old in zip(arena_inputs,old_inputs))
  for a,n,old,mutable in ((UNIT,0x1000,actor_before,[(0x74,1),(0x88,12),(0x2e0,24),(0x450,4),(0x468,8),(0x4d0,108),(0x57a,2),(0x5a0,2)]),
   (LOCO,0x100,loco_before,[(0x1c,24),(0x34,49)]),(FALLBACK,0x148,fb_before,[(0x24,4)])):
   after=bytearray(self.u.mem_read(a,n))
   for off,size in mutable:after[off:off+size]=old[off:off+size]
   assert after==old,hex(a)
  state=bytes(self.u.mem_read(0x850bb8,1))+bytes(self.u.mem_read(0x850ba8,8))+bytes(self.u.mem_read(0x850bd0,8))+bytes(self.u.mem_read(PLANES,800))+bytes(self.u.mem_read(FALLBACK+0x24,4))
  self.event('H',hashlib.sha256(state).hexdigest());return self.events
