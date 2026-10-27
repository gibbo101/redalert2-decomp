# SPDX-License-Identifier: GPL-3.0-or-later
"""One original guest owns preparation, resident Process and both complete draws.

Only initial records and named services are supplied. No final actor/map record
is transferred, and neither actor is executed at the other actor's address.
"""
import struct,hashlib
from collections import Counter,deque
from original_owned_unit_resident import OwnedUnitResidentOracle,PARKED,PARKED_LOCO
from original_membership_drive import HOUSE,TACTICAL,FIELDS
from original_unit_membership import GLOBALS
from original_unit_discovery import UnitDiscoveryOracle
from original_moving_unit_movement import RULES,TYPVT,COUNTRY
from original_foot_voxel_staging import TYPE,LOCO
from original_voxel_part import ACTOR as UNIT,VT
from original_shared_ground_world import SharedGroundWorldOracle
from original_cached_voxel_shadow import HOUSE_CONVERTER
from original_unit_voxel_world import CONTACTS
from original_map_preparation import CELLS,FALLBACK,BUFF4,BUFF10,MAP,SLOTS
from original_map_floor_height import PLANES
from original_prepared_drive_state import AttachedPresentation
from original_presentation import PresentationOracle,STACK,STOP
from original_foot_lit import ret
from verify_owned_unit_resident import RANGES
from verify_owned_unit_world import TYPE_KIND
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_ESP,UC_X86_REG_EIP,UC_X86_REG_EAX,UC_X86_REG_ECX
STUB=0x1d00000
class AttachedResident(OwnedUnitResidentOracle):
 def __init__(self,owner):
  # Bookkeeping and disjoint fixture storage only: never instantiate another Uc.
  self.owner=owner;self.u=owner.u;self.active=False;self.initializing=False;self.numeric_active=False;self.pose_active=False
  self.installing=False;self.parked_ready=False;self.hooks={};self.calls=Counter();self.trace=deque(maxlen=32)
  self.events=[];self.phase=None;self.instructions=set();self.roots=0;self.entries={hex(a):0 for a in RANGES};self.all_entries=dict(self.entries)
  self.admission_returns={};self.gate_returns={};self.callers={};self.next_calls=0;self.self_skips=0;self.preparation_stores=0
  self.actual_actor57a_checks=0;self.supplied_retry_words=0;self.actual_marks=0;self.actual_recalculations=0;self.eligible_unmarks=0
  self.effect_stores=0;self.stores=0;self.parked_stores=0;self.retry_loads={'first':0,'second':0};self.preparation_flags={}
  self.retry_padding=(19,-23);self.prepared=owner.prepared
  self.type_kind_calls=0
  self.u.mem_map(STUB,0x1000);self.u.mem_map(HOUSE,0x20000)
  owner.allowed=sorted(set(owner.allowed+[(a,a+n) for a,n in {**RANGES,**TYPE_KIND}.items()]),reverse=True)
  self.observer_hook=self.u.hook_add(UC_HOOK_CODE,self.observe);self.service_hook=self.u.hook_add(UC_HOOK_CODE,self.hook);self.store_hook=self.u.hook_add(UC_HOOK_MEM_WRITE,self.store)
 def observe(self,u,a,n,ctx):
  if self.active and a==0x49fc30:self.put(u.reg_read(UC_X86_REG_ESP)-12,7)
  if self.active and any(lo<=a and a+n<=lo+size for lo,size in TYPE_KIND.items()):
   assert u.reg_read(UC_X86_REG_ECX)==TYPE and self.get(u.reg_read(UC_X86_REG_ESP))==0x4f5a2c
   if a==0x70b5e5:
    assert u.reg_read(UC_X86_REG_EAX)==40;self.type_kind_calls+=1
   return
  if self.active and any(lo<=a and a+n<=lo+size for lo,size in {0x6d6df0:7,0x6d6e00:7}.items()):return
  return super().observe(u,a,n,ctx)
 def va(self,a):return a
 def hook(self,u,a,n,ctx):
  if self.active and a in self.hooks:
   count,fn,label=self.hooks[a];self.calls[label]+=1;ret(u,count,fn())
 def virtual(self,off,n,fn,label,vt=VT):
  p=STUB+16*len(self.hooks);self.put(vt+off,p);self.hooks[p]=(n,fn,label)
 def call(self,a,args=(),this=LOCO,budget=100000):
  # Full caller/register/write/input audits on the graphics guest's stack.
  writes=[(UNIT+0x30,4),(UNIT+0x74,2),(UNIT+0x88,12),(UNIT+0xa0,5),(UNIT+0x2e0,24),(UNIT+0x373,2),
   (UNIT+0x450,4),(UNIT+0x468,8),(UNIT+0x4d0,108),(UNIT+0x57a,2),(UNIT+0x5a0,2),(LOCO+0x1c,24),(LOCO+0x34,49),
   (PARKED+0x30,4),(PARKED+0x74,2),(PARKED+0x88,12),(PARKED+0xa0,5),(PARKED+0x373,2),(PARKED_LOCO+0x1c,24),
   (HOUSE+0x13c,1),(HOUSE+0x5668,2),(TACTICAL+0xd7d,1),(FALLBACK+0x24,4),(0x850bb8,1),(0x850ba8,8),(0x850bd0,8),(PLANES,800)]
  for p,(off,n) in GLOBALS.items():writes.append((p,n))
  for cp in [*[CELLS+i*512 for i in range(self.prepared.count)],FALLBACK]:writes.extend((cp+off,n) for off,n in FIELDS.items())
  writes.extend([(BUFF4,self.prepared.capacity*4),(BUFF10,self.prepared.capacity*10)])
  immutable=[*RANGES.items(),*TYPE_KIND.items(),(TYPE,0xc00),(VT,0x600),(RULES,0x2000),*self.owner.map_inputs()]
  immutable=[(p,n) for p,n in immutable if p!=CELLS]
  was=self.active;self.active=True
  try:
   PresentationOracle.checked_call(self.owner,a,args,this,writes=writes,inputs=immutable)
   return self.u.reg_read(UC_X86_REG_EAX)
  finally:self.active=was
 def store(self,u,access,a,n,v,ctx):
  if not self.active:return
  value=v&((1<<(n*8))-1)
  if 0x4a2670<=u.reg_read(UC_X86_REG_EIP)<0x4a4725:
   if UNIT+0x4d0<=a<UNIT+0x53c or a in (UNIT+0x57a,UNIT+0x57b):self.event('A',a-UNIT,value)
   if a-LOCO in (0x40,0x44,0x48,0x58,0x5c,0x63):self.event('a','L',a-LOCO,value)
  if CELLS<=a<CELLS+self.prepared.count*512 or FALLBACK<=a<FALLBACK+0x148:
   cp=FALLBACK if FALLBACK<=a<FALLBACK+0x148 else CELLS+((a-CELLS)//512)*512;off=a-cp
   assert (off==0x24 and cp==FALLBACK and n==4) or FIELDS.get(off)==n,(hex(a),n)
   if off in (0xe4,0xe8):value=self.actor_id(value)
   self.event('w','c',self.cell_id(cp),off,value);return
  if BUFF4<=a<BUFF4+self.prepared.capacity*4 or BUFF10<=a<BUFF10+self.prepared.capacity*10:
   stride=4 if a<BUFF10 else 10;offset=a-(BUFF4 if stride==4 else BUFF10)
   assert n==1 and offset%stride in ((0,1) if stride==4 else (8,));self.event('w','b' if stride==4 else 'd',0,offset,value);return
  if a in GLOBALS:off,width=GLOBALS[a];assert n==width;self.event('w','g',0,off,value);return
  if a==TACTICAL+0xd7d:self.event('w','t',0,0,value);return
  if HOUSE<=a<HOUSE+0x6000:assert a in (HOUSE+0x13c,HOUSE+0x5668,HOUSE+0x5669) and n==1;self.event('w','h',0,a-HOUSE,value);return
  for id,actor,drive in ((0,UNIT,LOCO),(1,PARKED,PARKED_LOCO)):
   if actor<=a<actor+0x1000:
    off=a-actor
    if off in (0x30,0x75,0x373,0x374,0xa0,0xa4):
     if off==0x30:value=self.actor_id(value)
     self.event('w','a',id,off,value)
    elif off in (0x74,0x88,0x8c,0x90,0x450,0x5a0,0x5a1):self.event('A',off,value) if id==0 else self.event('r','A',off,value)
    elif id==1:raise AssertionError(('Unexpected parked write',hex(a),n))
    if id==1 and not self.installing:assert off==0x30
    return
   if drive<=a<drive+0x100:
    if id:assert self.installing and 0x1c<=a-drive<0x34
    if a-drive<0x34:self.event('L',a-drive,value) if id==0 else self.event('r','L',a-drive,value)
    return
  # PresentationOracle audits the complete write set including stack.
 def begin(self,v,route,numeric,parked_at,parked_heading,turret):
  x,y,z,dx,dy,dz,heading,rot,speed,tick,steps,marked,effect,mode,present,key=v
  self.u.mem_write(HOUSE,bytes(0x10000))
  self.events=[];self.tick=tick;self.speed=speed;self.phase=None;self.installing=True
  self.hooks={}
  for actor,drive,at,h,t in ((UNIT,LOCO,(x,y,z),heading,turret[0]),(PARKED,PARKED_LOCO,parked_at,parked_heading,turret[1])):
   self.u.mem_write(actor,bytes(0x1000));self.u.mem_write(drive,bytes(0x100))
   for p,val in ((actor,VT),(actor+0x5ac,TYPE),(actor+0x1b4,HOUSE),(actor+0x154,-1),(actor+0x564,drive+4),
    (actor+0xcc,CONTACTS),(actor+0xa0,-1),(actor+0x98,2),(actor+0x6c,400),(actor+0x5b4,-1),(drive,0x7a0594),(drive+4,0x7a04cc),(drive+8,actor),(drive+12,actor),
    (drive+0x58,-1)):self.put(p,val)
   for off,val in ((0x14,5),(0x7d,1),(0xa4,255),(0x5a0,1)):self.put(actor+off,val,'B')
   self.u.mem_write(actor+0x88,struct.pack('<3i',*at))
   for off,h2 in ((0x2e0,h),(0x2f8,t),(0x2c8,14336)):self.u.mem_write(actor+off,struct.pack('<IIiiiI',h2,h2,0,0,0,rot*256))
   self.put(actor+0x468,1.,'d');self.put(actor+0x470,1.,'d');self.put(drive+0x50,numeric[0],'d')
   self.put(drive+0x10,1,'B');self.put(drive+0x65,1,'B')
   self.u.mem_write(actor+0x4d0,struct.pack('<24i',*([-1]*24)))
   self.put(actor+0x530,-1)
  self.u.mem_write(UNIT+0x4d0,struct.pack('<24i',*route));self.u.mem_write(UNIT+0x530,struct.pack('<3i',-1,7,0))
  self.u.mem_write(LOCO+0x34,struct.pack('<3i',dx,dy,dz))
  self.u.mem_write(VT,bytes(self.u.mem_read(0x7addf8,0x600)));self.put(TYPE,0x7ae328);self.put(VT+0x1cc,HOUSE_CONVERTER)
  for p,val,fmt in ((TYPE+0xb94,-1,'I'),(TYPE+0x5a0,speed,'I'),(TYPE+0xa0,400,'I'),(TYPE+0x205,1,'B'),(TYPE+0x598,17,'I'),
   (TYPE+0x5a4,1,'I'),(TYPE+0xaab,1,'B'),(TYPE+0xb59,0,'B'),(TYPE+0xaa0,0,'B'),(TYPE+0xba4,0,'B'),(TYPE+0xaf3,1,'B'),
   (0xa35db4,HOUSE,'I'),(0xa40774,1,'I'),(0xa3d298,1,'I'),(0xa3d548,0,'I'),(0xad057c,128,'I'),(MAP+0xc,2,'I'),(MAP+0x1154,255,'B'),
   (0x83996c,TACTICAL,'I'),(TACTICAL+0xd7d,0,'B'),(HOUSE+0x34,COUNTRY,'I'),(HOUSE+0x134,1,'B'),(COUNTRY+0x12c,1.,'f'),(0xa40d2c,tick,'I')):self.put(p,val,fmt)
  for off,val in ((0x704,0),(0x74c,0)):self.put(TYPE+off,val)
  self.put(0x839848,RULES);self.put(RULES+0x13c8,0.,'d');self.put(RULES+0x1368,.5,'d')
  self.u.mem_write(0x851a70,struct.pack('<16h',0,-1,1,-1,1,0,1,1,0,1,-1,1,-1,0,-1,-1))
  self.put(RULES+0x690,numeric[2],'d');self.put(RULES+0x698,numeric[3],'d');self.put(RULES+0x584,self.owner.map_config[5][4],'B')
  for i in range(12):self.put(0x850ea0+4*(i*9+1),numeric[1]*(1.-i/16.),'f')
  self.virtual(0x174,4,self.notify,'supplied notification');self.virtual(0x490,0,self.post,'supplied post-Cell')
  self.virtual(0x2ac,4,self.accessible,'supplied inaccessible route');self.virtual(0x410,8,self.mission,'supplied mission transition')
  for off,value,label in ((0x324,0,'disabled A'),(0x328,0,'disabled B'),(0x27c,1,'eligible mover')):
   self.hooks[self.get(VT+off)]=(0,lambda value=value:value,label)
  self.hooks[0x4c3000]=(12,self.pathfinder,'supplied failed pathfinder');self.hooks[0x78298a]=(0,lambda:0,'supplied atexit')
  self.hooks[0x476cc0]=(4,lambda:1,'empty-cell occupation')
  for cp in [*[CELLS+i*512 for i in range(self.prepared.count)],FALLBACK]:
   for off in (0xe4,0xe8,0x124,0x128):self.put(cp+off,0)
   self.put(cp+0x12c,8);self.put(cp+0x116,-1,'h');self.put(cp+0x54,-1);self.put(cp+0x58,-1)
  for p,(off,n) in GLOBALS.items():self.put(p,0 if n==1 else 0xa5a5a5a5,'B' if n==1 else 'I')
  self.initializing=True
  try:
   for actor,drive in ((PARKED,PARKED_LOCO),(UNIT,LOCO)):
    self.call(0x5d4860,[0],this=actor);self.call(0x4a05c0,[drive+4],this=0);self.call(0x4c2e60,[1],this=actor)
  finally:self.installing=self.initializing=False
  self.ready=True
 def advance(self,tick):
  self.events=[];self.tick=tick;self.put(0xa40d2c,tick);result=self.call(0x4a01c0,[LOCO+4],this=0);self.roots+=1
  self.event('S',result&255,*struct.unpack('<3i',self.u.mem_read(UNIT+0x88,12)),*struct.unpack('<6i',self.u.mem_read(LOCO+0x1c,24)))
  return self.events
 def snapshot(self):
  result=[]
  for id,actor,drive in ((0,UNIT,LOCO),(1,PARKED,PARKED_LOCO)):
   result.extend(['actor-state',id,*struct.unpack('<3i',self.u.mem_read(actor+0x88,12)),
    *struct.unpack('<3i',self.u.mem_read(drive+0x34,12)),*struct.unpack('<3i',self.u.mem_read(drive+0x40,12)),
    self.get(drive+0x58,'i'),self.get(drive+0x5c,'i'),self.get(drive+0x4c,'i'),self.get(drive+0x63,'B'),
    self.get(actor+0x74,'B'),self.get(actor+0x5a0,'B'),self.get(actor+0x5a1,'B'),
    self.get(actor+0x2e0,'H'),self.get(actor+0x2e4,'H'),self.get(actor+0x2e8,'i'),self.get(actor+0x2f0,'i'),self.get(actor+0x2f4,'H'),
    self.get(drive+0x62,'B'),self.get(actor+0x450),self.get(actor+0x57a,'B'),self.get(actor+0x57b,'B'),
    self.get(drive+0x50,'Q'),self.get(actor+0x468,'Q'),*struct.unpack('<6i',self.u.mem_read(drive+0x1c,24)),
    *struct.unpack('<3i',self.u.mem_read(actor+0x530,12)),*struct.unpack('<24i',self.u.mem_read(actor+0x4d0,96)),
    self.actor_id(self.get(actor+0x30)),self.get(actor+0x75,'B'),self.get(actor+0x373,'B'),self.get(actor+0x374,'B'),
    self.get(actor+0x98,'i'),self.get(actor+0xa0,'i'),self.get(actor+0xa4,'B'),
    self.get(actor+0x2f8,'H'),self.get(actor+0x2fc,'H'),self.get(actor+0x300,'i'),self.get(actor+0x308,'i'),self.get(actor+0x30c,'H')])
  selected=[]
  for cp in [*[CELLS+i*512 for i in range(self.prepared.count)],FALLBACK]:
   values=[self.get(cp+off,'B' if off in (0x11a,0x11b,0x11c,0x11d) else 'I') for off in (0x24,0x38,0xec,0x11a,0x11b,0x11c,0x11d,0x4c,0xe4,0xe8,0x124,0x128,0x12c,0x140)]
   for j in (8,9):values[j]=self.actor_id(values[j])
   selected.extend(values)
  packed=lambda v:struct.pack('<'+'I'*len(v),*v)
  foundation=[]
  for p,(off,n) in GLOBALS.items():foundation.append(self.get(p,'B' if n==1 else 'I'))
  lazy=bytes(self.u.mem_read(0x850bb8,1))+bytes(self.u.mem_read(0x850ba8,8))+bytes(self.u.mem_read(0x850bd0,8))+bytes(self.u.mem_read(PLANES,800))
  result.extend(['owned-map',hashlib.sha256(packed(selected)).hexdigest(),
   hashlib.sha256(self.u.mem_read(BUFF4,self.prepared.capacity*4)).hexdigest(),hashlib.sha256(self.u.mem_read(BUFF10,self.prepared.capacity*10)).hexdigest(),
   'foundation',*foundation,'House',*[self.get(HOUSE+off,'B') for off in (0x134,0x135,0x13c,0x13d,0x5668,0x5669)],
   'redraw',self.get(TACTICAL+0xd7d,'B'),'lazy',hashlib.sha256(lazy).hexdigest()])
  return result
class OwnedUnitWorldOracle(SharedGroundWorldOracle):
 movement_type=AttachedResident
 def __init__(self,*args):
  super().__init__(*args);self.movement=self.movement_type(self);self.viewer_house=HOUSE;self.owner_house=HOUSE
 def va(self,a):return a if a in RANGES else super().va(a)
 def prepare_map(self,f):
  result=super().prepare_map(f);self.map_config=f;self.prepared.capacity=(f[5][0]+f[5][1]+1)**2
  p=AttachedPresentation(self);p.inputs=list(RANGES.items())+[(0xb2af94,4)];p.selected_stores=0
  UnitDiscoveryOracle.stock_visibility(p,0)
  return result
 def bind_draw_associations(self):
  assert self.get_own(self.subject+0x1b4)==HOUSE and self.get_own(self.subject+0xcc)==CONTACTS
 def bind_draw_target(self,contact):
  # actor494 belongs to movement. Empty first-contact is a separate supplied
  # association, already initialized by reset_shared; drawing may not repair it.
  assert contact==0 and self.get_own(CONTACTS)==0
 def draw_shared(self,*args):
  # Guard before supplied draw binding too, not just the checked original call.
  targets=[self.get_own(p+0x494) for p in (UNIT,PARKED)]
  try:return super().draw_shared(*args)
  finally:assert [self.get_own(p+0x494) for p in (UNIT,PARKED)]==targets
 def get_own(self,p):return struct.unpack('<I',self.u.mem_read(p,4))[0]
 def initialize(self,v,route,numeric,parked,heading,turrets):
  self.reset_shared(0);self.movement.begin(v,route,numeric,parked,heading,turrets)
