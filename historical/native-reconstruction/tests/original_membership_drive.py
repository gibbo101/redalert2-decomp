# SPDX-License-Identifier: GPL-3.0-or-later
"""One guest: map finalization, complete Process and actual mutable Unit effects."""
import hashlib,struct
from original_prepared_drive_state import PreparedDriveStateOracle
from original_ground_drive_process import GroundDriveProcessOracle
from original_movement import UNIT,TYPE,LOCO,VT,TYPVT,RULES,COUNTRY,STOP
from original_map_preparation import CELLS,SLOTS,MAP,FALLBACK,BUFF4,BUFF10,SCENARIO
from original_map_floor_height import PLANES
from original_unit_discovery import UnitDiscoveryOracle
from original_unit_membership import GLOBALS
from original_presentation import STOP as PRESENTATION_STOP
from verify_membership_drive import verify,RANGES
from verify_unit_membership import DISPATCH
from verify_unit_discovery import DISPATCH as DISCOVERY,NUMERIC
from unicorn.x86_const import UC_X86_REG_ECX,UC_X86_REG_ESP
HOUSE=0x4000000;TACTICAL=0x4010000
FIELDS={0x38:4,0xec:4,0x11a:1,0x11b:1,0x11c:1,0x11d:1,0x4c:4,0xe4:4,0xe8:4,0x124:4,0x128:4}
class MembershipDriveOracle(PreparedDriveStateOracle):
 def va(self,a):return a if a==0x4c2e60 else super().va(a)
 def __init__(self,exe):
  super().__init__(exe);self.inspection=verify(exe.read_bytes());self.u.mem_map(HOUSE,0x20000)
  for slot,target in {**DISPATCH,**DISCOVERY}.items():
   if slot==0x7ae328+0x90:self.put(TYPVT+0x90,target)
   elif 0x7addf8<=slot<0x7ae328:self.put(VT+slot-0x7addf8,target)
  self.put(VT+0xe8,0x707980);self.put(VT+0xec,0x7079e0)
  self.hooks[0x78298a]=(0,lambda:0,'supplied atexit')
  self.all_entries={hex(a):0 for a in RANGES};self.effect_stores=0;self.actual_marks=0;self.actual_recalculations=0;self.eligible_unmarks=0
 def prepare_map(self,f):
  result=super().prepare_map(f);self.map_config=f;self.prepared.capacity=(f[5][0]+f[5][1]+1)**2
  self.presentation.inputs=[*RANGES.items(),(0xb2af94,4)];self.presentation.selected_stores=0;self.put(0xb2af94,0)
  self.numeric_active=True
  try:UnitDiscoveryOracle.stock_visibility(self.presentation,0)
  finally:self.numeric_active=False
  return result
 def observe(self,u,a,n,ctx):
  if not (self.active or self.numeric_active):return super().observe(u,a,n,ctx)
  if a in self.hooks:
   if self.hooks[a][2]=='supplied atexit':return
   return GroundDriveProcessOracle.observe(self,u,a,n,ctx)
  if a in (STOP,PRESENTATION_STOP):return
  assert any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),f'Uninspected membership Process {a:#x}/{n}'
  if hex(a) in self.all_entries:self.all_entries[hex(a)]+=1
  if not self.active:return
  if hex(a) in self.entries:self.entries[hex(a)]+=1
  if a in (0x548000,0x55a280):self.event('C' if a==0x548000 else 'F',*struct.unpack('<3i',u.mem_read(self.arg(0),12)))
  elif a==0x548070:self.event('W',*struct.unpack('<2h',u.mem_read(self.arg(0),4)))
  elif a==0x475d60:self.event('T',*struct.unpack('<2h',u.mem_read(u.reg_read(UC_X86_REG_ECX)+0x24,4)))
  elif a==0x4a062b:self.put(u.reg_read(UC_X86_REG_ESP)+0x14,7)
  elif a==0x4a2670:self.put(u.reg_read(UC_X86_REG_ESP)-0x14,7)
  if a==0x4c2e60:self.actual_marks+=1
  elif a==0x472540:self.actual_recalculations+=1
  elif a==0x4a16b5:self.eligible_unmarks+=1
 def cell_id(self,p):
  if p==FALLBACK:return self.prepared.count
  assert CELLS<=p<CELLS+self.prepared.count*512 and (p-CELLS)%512==0,hex(p)
  return (p-CELLS)//512
 def actor_id(self,p):
  assert p in (0,UNIT),hex(p)
  return 0 if p else 0xffffffff
 def extra_arenas(self):return []
 def store(self,u,access,a,n,v,ctx):
  if not self.active:return super().store(u,access,a,n,v,ctx)
  mask=(1<<(8*n))-1;value=v&mask
  if CELLS<=a<CELLS+self.prepared.count*512 or FALLBACK<=a<FALLBACK+0x148:
   cp=FALLBACK if FALLBACK<=a<FALLBACK+0x148 else CELLS+((a-CELLS)//512)*512;off=a-cp
   assert (off==0x24 and cp==FALLBACK and n==4) or FIELDS.get(off)==n,(hex(a),n)
   if off in (0xe4,0xe8):value=self.actor_id(value)
   self.event('w','c',self.cell_id(cp),off,value);self.effect_stores+=1;return
  if BUFF4<=a<BUFF4+self.prepared.capacity*4 or BUFF10<=a<BUFF10+self.prepared.capacity*10:
   stride=4 if a<BUFF10 else 10;offset=a-(BUFF4 if a<BUFF10 else BUFF10)
   assert n==1 and offset%stride in ((0,1) if stride==4 else (8,));self.event('w','b' if stride==4 else 'd',0,offset,value);self.effect_stores+=1;return
  if a in GLOBALS:
   off,width=GLOBALS[a];assert n==width;self.event('w','g',0,off,value);self.effect_stores+=1;return
  if a==TACTICAL+0xd7d:assert n==1;self.event('w','t',0,0,value);self.effect_stores+=1;return
  if a in (UNIT+0x30,UNIT+0x75,UNIT+0x373,UNIT+0x374,UNIT+0xa0,UNIT+0xa4):
   assert n==(4 if a in (UNIT+0x30,UNIT+0xa0) else 1)
   if a==UNIT+0x30:value=self.actor_id(value)
   self.event('w','a',0,a-UNIT,value);self.effect_stores+=1;return
  if HOUSE<=a<HOUSE+0x6000:
   assert a in (HOUSE+0x13c,HOUSE+0x5668,HOUSE+0x5669) and n==1;self.event('w','h',0,a-HOUSE,value);self.effect_stores+=1;return
  return super().store(u,access,a,n,v,ctx)
 def begin_actor(self,v,route,numeric):
  # Supplied initially empty memberships, not original actor construction.
  for cp in [*[CELLS+i*512 for i in range(self.prepared.count)],FALLBACK]:
   for off in (0xe4,0xe8,0x124,0x128):self.put(cp+off,0)
   self.put(cp+0x12c,8)
  for p,(off,n) in GLOBALS.items():self.put(p,0 if n==1 else 0xa5a5a5a5,'B' if n==1 else 'I')
  self.u.mem_write(HOUSE,bytes(0x10000));self.put(HOUSE+0x34,COUNTRY);self.put(HOUSE+0x134,1,'B')
  for off,value,fmt in ((0x30,0,'I'),(0x75,0,'B'),(0x76,0,'B'),(0x370,0,'B'),(0x372,0,'B'),(0x373,0,'B'),(0x374,0,'B'),(0x98,2,'I'),(0xa0,-1,'I'),(0xa4,255,'B'),(0x34,0,'I'),(0x1b4,HOUSE,'I')):self.put(UNIT+off,value,fmt)
  self.put(TYPE+0x205,1,'B');self.put(TYPE+0x598,17);self.put(0x83996c,TACTICAL);self.put(TACTICAL+0xd7d,0,'B');self.put(MAP+0xc,2);self.put(MAP+0x1154,255,'B')
  self.put(0xa3d298,1);self.put(0xa3d548,0);self.put(0xa35db4,HOUSE);self.put(0xa40774,1);self.put(0xad057c,128)
  super().begin_actor(v,route,numeric);self.put(RULES+0x584,self.map_config[5][4],'B')
  self.active=True
  try:self.call(0x4c2e60,[1],this=UNIT)
  finally:self.active=False
 def map_inputs(self):
  # Cell records mutate; type/image/registry/pointer associations remain fixed.
  return [(a,n) for a,n in super().map_inputs() if a!=CELLS]
 def run_joined(self,v,route,numeric):
  assert self.map_ready
  self.begin_actor(v,route,numeric)
  immutable=[*self.map_inputs(),*RANGES.items(),(VT,0x800),(TYPVT,0x100),(TYPE,0x1000),(RULES,0x2000),(0xaf8608,21*48),(0xaf6618,21*16)]
  before=[bytes(self.u.mem_read(a,n)) for a,n in immutable]
  arenas=[(UNIT,0x1000,[(0x30,4),(0x74,2),(0x88,12),(0xa0,4),(0xa4,1),(0x2e0,24),(0x373,2),(0x450,4),(0x468,8),(0x4d0,108),(0x57a,2),(0x5a0,2)]),(LOCO,0x100,[(0x1c,24),(0x34,49)]),(HOUSE,0x10000,[(0x13c,1),(0x5668,2)]),(FALLBACK,0x148,[(0x24,4),*FIELDS.items()])]
  arenas.extend((CELLS+i*512,512,list(FIELDS.items())) for i in range(self.prepared.count))
  arenas.extend(self.extra_arenas())
  arena_before=[bytes(self.u.mem_read(a,n)) for a,n,fields in arenas]
  tick,steps=v[9:11]
  from original_ground_drive_advance import div
  for j in range(steps):
   current=((tick+j+2**31)%2**32)-2**31;self.put(0xa40d2c,current);self.active=True
   try:value=self.call(0x4a01c0,[LOCO+4],this=0);self.roots+=1
   finally:self.active=False
   x,y,_=struct.unpack('<3i',self.u.mem_read(UNIT+0x88,12));slot=(div(y)*512+div(x))&0xffffffff;p=self.get(SLOTS+slot*4) if slot<262144 else 0;p=p or FALLBACK
   self.coverage['stored_vs_current_Cell_ramp_lag']+=self.get(LOCO+0x1c)!=self.get(p+0x11c,'B')
   self.coverage['distinct_stored_previous_current_ramps']+=self.get(LOCO+0x1c)!=self.get(LOCO+0x20)
   self.state_event(value);self.poses(current,v[14],v[15])
  assert all(bytes(self.u.mem_read(a,n))==old for (a,n),old in zip(immutable,before))
  for (a,n,fields),old in zip(arenas,arena_before):
   after=bytearray(self.u.mem_read(a,n))
   for off,size in fields:after[off:off+size]=old[off:off+size]
   assert bytes(after)==old,f'Unselected joined arena changed {a:#x}'
  for p,n in ((BUFF4,self.prepared.capacity*4),(BUFF10,self.prepared.capacity*10)):assert bytes(self.u.mem_read(p+n,64))==b'\xa7'*64
  state=bytes(self.u.mem_read(0x850bb8,1))+bytes(self.u.mem_read(0x850ba8,8))+bytes(self.u.mem_read(0x850bd0,8))+bytes(self.u.mem_read(PLANES,800))+bytes(self.u.mem_read(FALLBACK+0x24,4))
  self.event('H',hashlib.sha256(state).hexdigest());result=self.events
  selected=[]
  for cp in [*[CELLS+i*512 for i in range(self.prepared.count)],FALLBACK]:
   values=[self.get(cp+off,'B' if off in (0x11a,0x11b,0x11c,0x11d) else 'I') for off in (0x38,0xec,0x11a,0x11b,0x11c,0x11d,0x4c,0xe4,0xe8,0x124,0x128)]
   for j in (7,8):values[j]=self.actor_id(values[j])
   selected.extend(values)
  result.extend(map(str,['map',hashlib.sha256(struct.pack('<'+'I'*len(selected),*selected)).hexdigest(),hashlib.sha256(self.u.mem_read(BUFF4,self.prepared.capacity*4)).hexdigest(),hashlib.sha256(self.u.mem_read(BUFF10,self.prepared.capacity*10)).hexdigest(),-1 if self.get(UNIT+0x30)==0 else self.actor_id(self.get(UNIT+0x30)),self.get(UNIT+0x75,'B'),self.get(UNIT+0x373,'B'),self.get(UNIT+0x374,'B'),self.get(HOUSE+0x13c,'B'),self.get(HOUSE+0x5668,'B'),self.get(HOUSE+0x5669,'B')]))
  return result
