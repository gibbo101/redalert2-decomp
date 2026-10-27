# SPDX-License-Identifier: GPL-3.0-or-later
"""Distinct original actors execute Process on one graphics guest and shared map.

The original arenas and code are never copied to the other actor's address.
Only initial records, numeric/padding inputs and named services are supplied.
"""
import struct
from collections import Counter
from original_owned_unit_world import AttachedResident, UNIT, LOCO, PARKED, PARKED_LOCO
from original_owned_unit_world import (HOUSE,TACTICAL,FIELDS,GLOBALS,TYPE,VT,RULES,
    CELLS,FALLBACK,BUFF4,BUFF10,PLANES,PresentationOracle,TYPE_KIND,RANGES)
from original_owned_unit_admission import EXCLUDED
from verify_moving_unit_admission import EXTRA,TABLES
from verify_ground_drive_stores import STORE_SITES,FIELDS as DRIVE_FIELDS
from original_owned_unit_world import OwnedUnitWorldOracle
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_ESP,UC_X86_REG_EIP,UC_X86_REG_EAX,UC_X86_REG_ECX

ACTORS=(UNIT,PARKED)
DRIVES=(LOCO,PARKED_LOCO)
CODE={**RANGES,**TYPE_KIND,**EXTRA,0x6d6df0:7,0x6d6e00:7}
ACTOR_WRITES=((0x30,4),(0x74,2),(0x88,12),(0xa0,5),(0x2e0,24),
    (0x373,2),(0x450,4),(0x468,8),(0x4d0,108),(0x558,12),(0x57a,2),(0x5a0,2))
DRIVE_WRITES=((0x1c,24),(0x34,49))

class AttachedProcesses(AttachedResident):
 allowed_advance_results=(0,2)
 code_ranges=CODE
 excluded_branches=tuple(x for x in EXCLUDED if x not in (0x70371e,0x703748))
 unsupported_entries=(0x4a373b,0x4a4234,0x476920,0x4a3ab5)
 def __init__(self,owner):
  self.actor=None;self.process_counts=Counter();self.root_entries=Counter()
  self.admissions=Counter();self.path_options=Counter();self.wait_stores=Counter()
  self.padding=((19,-23,31),(-29,37,-41));self.prepare=[];self.drive_store_sites=Counter()
  super().__init__(owner)
  self.owner.allowed=sorted(set(self.owner.allowed+[(a,a+n) for a,n in self.code_ranges.items()]),reverse=True)
 def actor_fields(self,id):return ACTOR_WRITES if self.installing or id==self.actor else ((0x30,4),)
 def drive_fields(self,id):return DRIVE_WRITES if self.installing or id==self.actor else ()
 def extra_call_writes(self):return ()
 def extra_call_inputs(self):return ()
 def actor_store_guard(self,id,off,n,ip):
  assert self.installing or id==self.actor or off==0x30,('inactive actor write',id,hex(off))
  if off in (0x558,0x55c,0x560):
   assert n==4 and ip=={0x558:0x4a367d,0x55c:0x4a3683,0x560:0x4a3686}[off]
   self.wait_stores[id]+=1
 def drive_store_guard(self,id,off,n,ip):
  assert self.installing or id==self.actor,('inactive Drive write',id,hex(DRIVES[id]+off))
 def observe(self,u,a,n,ctx):
  if not self.active:return
  if a in self.hooks:
   assert self.phase is None,('supplied service inside decision',hex(a))
   return
  # Presentation STOP is not executed by emu_start.
  assert any(lo<=a and a+n<=lo+size for lo,size in self.code_ranges.items()),('uninspected',hex(a),n)
  assert a not in self.excluded_branches,hex(a)
  assert a not in self.unsupported_entries,('unsupported',hex(a))
  self.instructions.add(a)
  sp=u.reg_read(UC_X86_REG_ESP)
  if a==0x4a05f0:
   assert self.arg(0)==DRIVES[self.actor]+4
   self.root_entries[self.actor]+=1
  if self.phase and a==self.return_to:
   result=u.reg_read(UC_X86_REG_EAX)
   if self.phase=='D':
    assert result in (0,2,3,6,7),result
    if a==0x4a1c9f:assert result in self.allowed_advance_results,('unsupported Advance',result)
    self.admissions[(self.actor,a,result)]+=1
   self.event('decision',self.actor,self.phase,hex(a),result)
   self.phase=None
  if a in (0x55acd0,0x703040,0x705160):
   assert self.phase is None
   if a==0x55acd0:
    assert u.reg_read(UC_X86_REG_ECX)==0x8324e0 and self.arg(0)==ACTORS[self.actor]
   else:
    assert u.reg_read(UC_X86_REG_ECX)==ACTORS[self.actor],('decision actor',hex(a),hex(u.reg_read(UC_X86_REG_ECX)))
   self.phase={0x55acd0:'G',0x703040:'D',0x705160:'N'}[a];self.return_to=self.get(sp)
  if a==0x4a2670:
   caller=self.get(sp);flag=self.arg(1);third=self.arg(2)
   assert caller in (0x4a0739,0x4a0b75,0x4a4518,0x4a41df)
   assert flag==(0 if caller==0x4a4518 else 1)
   assert third==int(caller==0x4a41df)
   self.prepare.append(caller);self.put(sp-0x14,7)
  if a in (0x4a0739,0x4a0b75,0x4a4518,0x4a41df):assert self.prepare.pop()==a
  if a in (0x4a3732,0x4a422b):
   first=a==0x4a3732;self.put(sp+(0x48 if first else 0x54),self.padding[self.actor][0 if first else 1])
  if a==0x4a367f:self.put(sp+0x54,self.padding[self.actor][2])
  if a in (0x4a3c2b,0x4a44fe):self.put(sp+0x54,7)
  if a==0x4a062b:self.put(sp+0x14,7)
  if a==0x49fc30:self.put(sp-12,7)
  if a==0x4c2e60:self.actual_marks+=1
  if a==0x472540:self.actual_recalculations+=1
  if a in (0x548000,0x55a280):self.event('query',self.actor,hex(a),*struct.unpack('<3i',u.mem_read(self.arg(0),12)))
  if a==0x548070:self.event('query',self.actor,hex(a),*struct.unpack('<2h',u.mem_read(self.arg(0),4)))
 def pathfinder(self):
  caller=self.get(self.u.reg_read(UC_X86_REG_ESP))
  option=self.arg(2) if caller==0x4a3a0a else -1
  self.path_options[(self.actor,option)]+=1
  self.event('pathfinder',self.actor,option)
  return 0
 def notify(self):self.event('notify',self.actor,self.arg(0));return 0
 def post(self):self.event('post',self.actor);return 0
 def accessible(self):self.event('accessible',self.actor);return 0
 def mission(self):self.event('mission',self.actor,self.arg(0),self.arg(1));return 0
 def store(self,u,access,a,n,v,ctx):
  if not self.active:return
  for id,p in enumerate(ACTORS):
   if p<=a<p+0x1000:
    off=a-p
    self.actor_store_guard(id,off,n,u.reg_read(UC_X86_REG_EIP))
    self.event('write-actor',id,off,n,v&((1<<(8*n))-1));return
  for id,p in enumerate(DRIVES):
   if p<=a<p+0x100:
    off=a-p;ip=u.reg_read(UC_X86_REG_EIP)
    self.drive_store_guard(id,off,n,ip)
    if 0x4a1000<=ip<0x4a2649 and off in DRIVE_FIELDS:
     assert STORE_SITES.get(ip)==(off,n),('Uninspected Advance Drive store',hex(ip),off,n)
     self.drive_store_sites[hex(ip)]+=1
    self.event('write-Drive',id,off,n,v&((1<<(8*n))-1));return
  # Shared Cell/list/occupation/buffer/House/floor logging from accepted fixture.
  return super().store(u,access,a,n,v,ctx)
 def call(self,a,args=(),this=LOCO,budget=100000):
  writes=[];arenas=[]
  for id,(p,l) in enumerate(zip(ACTORS,DRIVES)):
   af=self.actor_fields(id);lf=self.drive_fields(id)
   writes.extend((p+off,n) for off,n in af);writes.extend((l+off,n) for off,n in lf)
   arenas.extend(((p,bytes(self.u.mem_read(p,0x1000)),af),(l,bytes(self.u.mem_read(l,0x100)),lf)))
  writes.extend(((HOUSE+0x13c,1),(HOUSE+0x5668,2),(TACTICAL+0xd7d,1),(FALLBACK+0x24,4),
   (0x850bb8,1),(0x850ba8,8),(0x850bd0,8),(PLANES,800)))
  writes.extend((p,n) for p,(off,n) in GLOBALS.items())
  for cp in [*[CELLS+i*512 for i in range(self.prepared.count)],FALLBACK]:writes.extend((cp+off,n) for off,n in FIELDS.items())
  writes.extend(((BUFF4,self.prepared.capacity*4),(BUFF10,self.prepared.capacity*10)))
  writes.extend(self.extra_call_writes())
  immutable=[*self.code_ranges.items(),*TABLES.items(),*self.extra_call_inputs(),(TYPE,0xc00),(VT,0x600),(RULES,0x2000),*self.owner.map_inputs(),
   (0x851a70,32),(0x851ac0,64),(0x8661d8,4),(0xa40774,4),(0x850ea0,12*9*4),
   (0xaf8608,21*48),(0xaf6618,21*16),(0x7a04cc,0xb0)]
  immutable=[(p,n) for p,n in immutable if p!=CELLS]
  was=self.active;self.active=True
  try:
   PresentationOracle.checked_call(self.owner,a,args,this,writes=writes,inputs=immutable)
   assert not self.prepare and self.phase is None
   for p,old,fields in arenas:
    after=bytearray(self.u.mem_read(p,len(old)))
    for off,n in fields:after[off:off+n]=old[off:off+n]
    assert after==old,('unselected arena',hex(p))
   return self.u.reg_read(UC_X86_REG_EAX)
  finally:self.active=was
 def advance_actor(self,id,tick):
  assert id in (0,1) and self.actor is None
  self.actor=id;self.events=[];self.tick=tick;self.put(0xa40d2c,tick)
  try:
   result=self.call(0x4a01c0,[DRIVES[id]+4],this=0)
   self.process_counts[id]+=1;self.event('result',id,result&255)
   return self.events.copy()
  finally:self.actor=None

class OwnedUnitProcessesOracle(OwnedUnitWorldOracle):
 movement_type=AttachedProcesses
 def process_snapshot(self):
  result=self.movement.snapshot()
  for id,p in enumerate(ACTORS):
   result.extend(['wait-state',id,*struct.unpack('<3i',self.u.mem_read(p+0x558,12))])
  return result
