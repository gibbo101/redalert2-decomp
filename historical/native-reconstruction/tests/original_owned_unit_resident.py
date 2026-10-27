# SPDX-License-Identifier: GPL-3.0-or-later
"""One guest, two actual Unit memberships and stationary admission through Process."""
import struct
from original_owned_unit_admission import OwnedUnitAdmissionOracle
from original_membership_drive import HOUSE
from original_movement import UNIT,TYPE,LOCO,STOP
from unicorn.x86_const import UC_X86_REG_ECX,UC_X86_REG_ESP
PARKED=0x4100000
PARKED_TYPE=PARKED+0x2000
PARKED_LOCO=PARKED+0x4000
class OwnedUnitResidentOracle(OwnedUnitAdmissionOracle):
 admission_codes=(0,3,6,7)
 def __init__(self,exe):
  self.installing=False;self.parked_ready=False
  super().__init__(exe);self.u.mem_map(PARKED,0x10000)
  self.parked_initializations=0;self.parked_stores=0;self.parked_stability_checks=0
  self.retry_loads={'first':0,'second':0};self.preparation_flags={}
 def actor_id(self,p):
  assert p in (0,UNIT,PARKED),hex(p)
  return {0:0xffffffff,UNIT:0,PARKED:1}[p]
 def extra_arenas(self):
  # After initialization only Next may change as the mover leaves a shared list.
  return [(PARKED,0x10000,[(0x30,4)])]
 def begin_actor(self,*args):
  self.installing=True;self.parked_ready=False
  try:super().begin_actor(*args)
  finally:self.installing=False
  assert self.parked_ready
 def call(self,a,args=(),this=LOCO,budget=100000):
  if self.installing and not self.parked_ready and a==0x4c2e60 and this==UNIT and list(args)==[1]:
   self.parked_ready=True;self.initialize_parked()
   inputs=[(p,n,bytes(self.u.mem_read(p,n))) for p,n in ((PARKED_TYPE,0x1000),(PARKED_LOCO,0x100))]
   if not self.parked_order:super().call(a,args,this=PARKED,budget=budget)
   result=super().call(a,args,this=this,budget=budget)
   if self.parked_order:super().call(a,args,this=PARKED,budget=budget)
   assert all(bytes(self.u.mem_read(p,n))==old for p,n,old in inputs),'Initial parked Mark changed type/Drive records'
   self.parked_initializations+=1
   return result
  return super().call(a,args,this=this,budget=budget)
 def initialize_parked(self):
  # Supplied initial records and associations. Every placement/Mark effect below
  # is produced by unchanged original instructions, not by transferring outputs.
  for dest,source,n in ((PARKED,UNIT,0x1000),(PARKED_TYPE,TYPE,0x1000),(PARKED_LOCO,LOCO,0x100)):
   self.u.mem_write(dest,bytes(self.u.mem_read(source,n)))
  for off,value,fmt in ((0,0x7addf8,'I'),(0x5ac,PARKED_TYPE,'I'),(0x564,PARKED_LOCO+4,'I'),
   (0x14,5,'B'),(0x30,0,'I'),(0x74,0,'B'),(0x75,0,'B'),(0x373,0,'B'),(0x374,0,'B'),
   (0xa0,-1,'I'),(0xa4,255,'B'),(0x1b4,HOUSE,'I')):self.put(PARKED+off,value,fmt)
  self.u.mem_write(PARKED+0x88,struct.pack('<3i',*self.parked_at))
  self.u.mem_write(PARKED+0x118,bytes(8))
  self.u.mem_write(PARKED+0x2e0,struct.pack('<IIiiiI',self.parked_heading,self.parked_heading,0,0,0,self.parked_rate))
  self.put(PARKED_TYPE,0x7ae328);self.put(PARKED_TYPE+0xb94,-1);self.put(PARKED_TYPE+0x704,0)
  self.put(PARKED_LOCO+8,PARKED);self.put(PARKED_LOCO+12,PARKED)
  self.u.mem_write(PARKED_LOCO+0x1c,bytes(24));self.u.mem_write(PARKED_LOCO+0x34,bytes(24))
  self.put(PARKED_LOCO+0x58,-1);self.put(PARKED_LOCO+0x63,0,'B')
  before=[(a,n,bytes(self.u.mem_read(a,n)),mutable) for a,n,mutable in
   ((PARKED,0x1000,[(0x74,1),(0x88,12)]),(PARKED_TYPE,0x1000,[]),(PARKED_LOCO,0x100,[(0x1c,24)]))]
  super().call(0x5d4860,[0],this=PARKED)
  super().call(0x4a05c0,[PARKED_LOCO+4],this=0)
  for a,n,old,mutable in before:
   after=bytearray(self.u.mem_read(a,n))
   for off,size in mutable:after[off:off+size]=old[off:off+size]
   assert after==old,('Unselected parked placement arena',hex(a))
 def observe(self,u,a,n,ctx):
  if self.active:
   if a==0x4a2670:
    caller=self.get(u.reg_read(UC_X86_REG_ESP));flag=self.arg(1)
    assert caller in (0x4a0739,0x4a0b75,0x4a4518)
    assert flag==(0 if caller==0x4a4518 else 1)
    key=f'{caller:#x}:{flag}';self.preparation_flags[key]=self.preparation_flags.get(key,0)+1
   if a in (0x4a3732,0x4a422b):
    first=a==0x4a3732;self.put(u.reg_read(UC_X86_REG_ESP)+(0x48 if first else 0x54),self.retry_padding[0 if first else 1])
    self.retry_loads['first' if first else 'second']+=1
   assert a not in (0x4a373b,0x4a4234,0x476920),'Flag-zero scatter/close-enough excluded'
  return super().observe(u,a,n,ctx)
 def store(self,u,access,a,n,v,ctx):
  if self.active and PARKED<=a<PARKED+0x1000:
   off=a-PARKED;assert off in (0x30,0x74,0x75,0x88,0x8c,0x90,0x373,0x374,0xa0,0xa4),(hex(a),n)
   if not self.installing:assert off==0x30,'Process wrote stationary actor beyond shared Next'
   assert n==(1 if off in (0x74,0x75,0x373,0x374,0xa4) else 4)
   value=v&((1<<(n*8))-1)
   if off==0x30:value=self.actor_id(value)
   self.event('r','A',off,value) if off in (0x74,0x88,0x8c,0x90) else self.event('w','a',1,off,value)
   self.parked_stores+=1;return
  if self.active and PARKED_LOCO<=a<PARKED_LOCO+0x100:
   assert self.installing,'Process wrote stationary Drive'
   off=a-PARKED_LOCO;assert off in (0x1c,0x20,0x24,0x28,0x2c,0x30) and n==4,(hex(a),n)
   self.event('r','L',off,v&0xffffffff);self.parked_stores+=1;return
  if self.active and PARKED<=a<PARKED+0x10000:raise AssertionError(('Unselected parked arena write',hex(a),n))
  return super().store(u,access,a,n,v,ctx)
 def run_resident(self,v,route,numeric,crusher,parked_at,heading,first,second,order):
  self.parked_at=parked_at;self.parked_heading=heading;self.retry_padding=(first,second);self.parked_order=order;self.parked_rate=v[7]*256
  result=super().run_owned(v,route,numeric,crusher)
  self.parked_stability_checks+=1
  result.extend(map(str,['parked',*struct.unpack('<3i',self.u.mem_read(PARKED+0x88,12)),self.get(PARKED+0x74,'B'),
   -1 if self.get(PARKED+0x30)==0 else self.actor_id(self.get(PARKED+0x30)),self.get(PARKED+0x75,'B'),self.get(PARKED+0x373,'B'),self.get(PARKED+0x374,'B')]))
  return result
