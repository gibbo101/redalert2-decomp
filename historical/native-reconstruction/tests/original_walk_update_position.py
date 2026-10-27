# SPDX-License-Identifier: GPL-3.0-or-later
"""Research-only complete Walk Process invoking the complete E1 position chain.

The accepted standalone oracles are inherited without changing their sources.
Only named Walk leaves and the parent's already declared leaves are supplied.
Post-child mutations are diagnostic probes, never claimed as game behavior.
"""
import struct
from original_infantry_update_position_effects_e1 import (
 InfantryUpdatePositionEffectsE1Oracle, ACTOR, LOCOMOTOR, CURRENT, ARENA, SIZE)
from original_presentation import STOP
from verify_walk_arrival import verify as verify_arrival, RANGES, SERVICES
from verify_walk_movement import TABLES
from verify_walk_update_position_schedule import verify as verify_schedule
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_ECX, UC_X86_REG_ESP

WALK = LOCOMOTOR - 4
LATE = {0x71f19f:0x7d, 0x71f1aa:0x76, 0x71f1b5:0x7a}

class WalkUpdatePositionOracle(InfantryUpdatePositionEffectsE1Oracle):
 def __init__(self, exe):
  super().__init__(exe)
  data=exe.read_bytes()
  self.join_inspection=dict(arrival=verify_arrival(data),schedule=verify_schedule(data))
  self.joined=False

 def checked_call(self, address, args=(), ecx=0, edx=0, *, writes=(), inputs=()):
  # The inherited run prepares the whole child graph; replace only its root.
  if not self.joined:
   return super().checked_call(address,args,ecx,edx,writes=writes,inputs=inputs)
  assert address==0x500aa0 and args==[2] and ecx==ACTOR
  u=self.u
  self.put(ACTOR+0x564,LOCOMOTOR);self.put(LOCOMOTOR,0x7aead8);self.put(WALK+0xc,ACTOR)
  u.mem_write(ACTOR+0x574,b'\xff');u.mem_write(ACTOR+0x74,b'\1')
  u.mem_write(ACTOR+0x76,b'\0');u.mem_write(ACTOR+0x7a,b'\0')
  self.put(ACTOR+0x88,self.current[0]-self.distance)
  for off,value in zip((0x2e0,0x2e4,0x2e8,0x2ec,0x2f0,0x2f4),(0,0,37,0x13579bdf,0,256)):self.put(ACTOR+off,value)
  self.put(ACTOR+0x3fc,0);u.mem_write(ACTOR+0x468,struct.pack('<d',.375))
  self.put(ACTOR+0x450,0x12345678)
  for i in range(24):self.put(ACTOR+0x4d0+4*i,-1 if i==0 else 100+i)
  for i,v in enumerate((*self.target,*self.current)):self.put(WALK+0x1c+4*i,v)
  u.mem_write(WALK+0x34,bytes((1,173,197)))
  u.mem_write(0xaf9060,bytes(12));u.mem_write(0x865f20,bytes(12))
  self.put(0xaf9098,104);self.put(0xa72f30,104)
  extra=[(ACTOR+o,n) for o,n in ((0x74,1),(0x76,1),(0x79,2),(0x7d,1),(0x88,12),(0x2e0,20),(0x450,4),(0x468,8),(0x4d0,96),(0x57a,1),(0x5a1,1))]+[(WALK+0x1c,27)]
  writes=[*writes,*extra]
  # Audit every nonmutable byte of the shared arena, not just selected fields.
  spans=sorted((p,p+n) for p,n in writes if ARENA<=p<ARENA+SIZE)
  immutable=[];cursor=ARENA
  for lo,hi in spans:
   if cursor<lo:immutable.append((cursor,lo-cursor))
   cursor=max(cursor,hi)
  if cursor<ARENA+SIZE:immutable.append((cursor,ARENA+SIZE-cursor))
  inputs=[(p,n) for p,n in inputs if not ARENA<=p<ARENA+SIZE]
  inputs.extend(immutable);inputs.extend(RANGES.items());inputs.extend(TABLES.items())
  inputs.extend(((0xaf9060,12),(0x865f20,12),(0xaf9098,4),(0xa72f30,4)))
  self.in_child=False;self.walk_events=[];self.late=[];self.callback_count=0
  super().checked_call(0x71dff0,[LOCOMOTOR],writes=writes,inputs=inputs)
  self.walk_result=dict(result=u.reg_read(UC_X86_REG_EAX)&255,position=self.point(ACTOR+0x88),
   route=[self.signed(self.word(ACTOR+0x4d0+i*4)) for i in range(24)],
   head=self.point(WALK+0x28),destination=self.point(WALK+0x1c),
   moving=list(u.mem_read(WALK+0x34,3)),flags=[u.mem_read(ACTOR+o,1)[0] for o in (0x7d,0x76,0x7a)],
   callbacks=self.callback_count,late=self.late,events=self.walk_events)

 def code(self,u,a,n,ctx):
  if not self.active or not self.joined or a==STOP:return super().code(u,a,n,ctx)
  sp=u.reg_read(UC_X86_REG_ESP);ecx=u.reg_read(UC_X86_REG_ECX)
  if a==0x500aa0:
   assert not self.in_child and ecx==ACTOR and self.word(sp)==0x71f19c and self.word(sp+4)==2
   assert self.point(ACTOR+0x88)==self.current
   assert self.point(WALK+0x28)==(0,0,0)
   assert u.mem_read(ACTOR+0x74,1)==b'\0'
   self.callback_count+=1;self.walk_events.append('child');self.in_child=True
  if a==0x71f19c:
   assert self.in_child;self.in_child=False;self.walk_events.append('return')
   # Explicit supplied post-return diagnostic, separate from original child effects.
   for off,value in zip((0x7d,0x76,0x7a),self.late_flags):u.mem_write(ACTOR+off,bytes([value]))
  if self.in_child:return super().code(u,a,n,ctx)
  if a in LATE:self.late.append([hex(a),u.mem_read(ACTOR+LATE[a],1)[0]])
  assert a in SERVICES or any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected joined Walk instruction',hex(a))
  assert not (0x71e25e<=a<0x71f077 or 0x71f63d<=a<0x71f874),('Unsupported joined Walk branch',hex(a))
  if a in RANGES:self.counts['walk.'+hex(a)]+=1
  if a==0x508980:assert ecx==ACTOR;self.ret(0,1)
  elif a==0x4c2e60:
   assert ecx==ACTOR;kind=self.word(sp+4);assert kind in (0,1)
   self.walk_events.append('mark'+str(kind));u.mem_write(ACTOR+0x74,bytes([kind]));self.ret(4,1)
  elif a==0x55a280:
   assert ecx==0x8324e0;self.ret(4,self.current[2])
  elif a==0x548070:
   assert ecx==0x8324e0;self.ret(4,CURRENT)
  elif a in (0x5084a0,0x508410):
   assert ecx==ACTOR;self.walk_events.append('release' if a==0x5084a0 else 'occupy');self.ret(4,1)
  elif a==0x501ce0:assert ecx==ACTOR;self.walk_events.append('completion');self.ret(8)
  elif a==0x508750:assert ecx==ACTOR;self.walk_events.append('reset');self.ret(0)

 def run_joined(self,f,*,distance=16,late_flags=(1,0,0)):
  if distance not in (0,1,16):raise ValueError('Joined fixture requires selected-head arrival distance <=16')
  if late_flags not in ((1,0,0),(0,0,0),(1,255,0),(1,0,128)):
   raise ValueError('Unsupported diagnostic late flags')
  if f['onMap']!=1 or (f['x'],f['y'],f['z'],f['tx'],f['ty'],f['tz'])!=(15040,22976,208,59,89,2):
   raise ValueError('Joined child requires the bounded on-map arrival scene')
  self.distance=distance;self.late_flags=late_flags;self.joined=True
  try:child=super().run(f)
  finally:self.joined=False
  assert self.callback_count==1
  expected=[['0x71f19f',late_flags[0]]]
  if late_flags[0]:
   expected.append(['0x71f1aa',late_flags[1]])
   if not late_flags[1]:expected.append(['0x71f1b5',late_flags[2]])
  assert self.late==expected,(self.late,expected)
  return dict(child=child,walk=self.walk_result)
