# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete unchanged Drive body with actual stock tables and ramp-state children."""
import struct
from original_ramp_geometry import RampGeometryOracle
from original_presentation import STOP,STACK
from verify_drive_body_pose import verify,RANGES,EXTRA,TAILS,TABLES
from verify_actor_ground_state import COMPLETE
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import (UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP,
 UC_X86_REG_EBX,UC_X86_REG_ESI,UC_X86_REG_EDI,UC_X86_REG_EBP,UC_X86_REG_EIP)
ARENA=0x2600000;ACTOR=ARENA;LOCO=ARENA+0x1000;OUT=ARENA+0x2000;KEY=ARENA+0x2100
TYPE=ARENA+0x3000;VTABLE=0x7addf8;SLOTS=0x2700000;CELL=0x2800000;MAP=0x8324e0
class DriveBodyPoseOracle(RampGeometryOracle):
 def __init__(self,exe):
  super().__init__(exe);self.inspection=verify(exe.read_bytes());self.active=False
  for a in {**COMPLETE,**EXTRA,**TAILS,0x4a05f0:0}:
   if hex(a) not in self.entries:
    self.entries[hex(a)]=0;self.u.hook_add(UC_HOOK_CODE,self.entry,begin=a,end=a)
  self.u.hook_add(UC_HOOK_CODE,self.observe)
  self.u.mem_map(ARENA,0x5000);self.u.mem_map(SLOTS,0x101000)
  self.quaternion_stores=0
  def quaternion_store(u,access,p,n,value,ctx):
   if 0xaf6618<=p<0xaf6618+21*16:
    assert n==4 and (p-0xaf6618)%4==0;self.quaternion_stores+=1
  h=self.u.hook_add(UC_HOOK_MEM_WRITE,quaternion_store)
  try:self.stock(0)
  finally:self.u.hook_del(h)
  assert self.quaternion_stores==84
  self.quaternions=list(map(str,struct.unpack('<84I',self.u.mem_read(0xaf6618,21*16))))
  self.put(MAP+0x138,SLOTS);self.put(MAP+0x13c,262144);self.put(SLOTS+4*(72*512+51),CELL)
  self.inputs+=list(RANGES.items())+[(0x79d170,8),(0x79d090,8)]+list(TABLES.items())+[(0xaf8608,21*48),(0xaf6618,21*16)]
  self.prefixes=0;self.body_calls=0;self.key_writes=0;self.supplied_padding_writes=0
 def block(self,u,a,n,ctx):
  if a!=STOP and not any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()):
   raise AssertionError(f'Uninspected Drive body block {a:#x}/{n}')
 def observe(self,u,a,n,ctx):
  if not self.active:return
  if a==0x548000:
   assert u.reg_read(UC_X86_REG_ECX)==MAP;self.events.append('C')
  elif a==0x705020:
   assert u.reg_read(UC_X86_REG_ECX)==ACTOR;self.events.append('T')
  elif a==0x4b8be0:
   assert u.reg_read(UC_X86_REG_ECX)==ACTOR+0x2e0;self.events.append('F')
  elif a==0x49fc30:
   # Explicit supplied opaque padding at actual Force entry, after the getter.
   self.put(u.reg_read(UC_X86_REG_ESP)-12,0);self.supplied_padding_writes+=1
 def prefix(self,inputs):
  guard=b'\xa7'*64;self.u.mem_write(STACK,struct.pack('<2I',STOP,LOCO));self.u.mem_write(STACK+8,guard)
  self.put(STACK-12,0)
  regs={UC_X86_REG_EBX:0x12345678,UC_X86_REG_ESI:0x23456789,UC_X86_REG_EDI:0x3456789a,UC_X86_REG_EBP:0x456789ab}
  for r,v in regs.items():self.u.reg_write(r,v)
  self.u.reg_write(UC_X86_REG_ESP,STACK);before=[bytes(self.u.mem_read(p,n)) for p,n in inputs]
  def audit(u,access,p,n,v,ctx):
   assert STACK-0x2000<=p and p+n<=STACK or LOCO+0x18<=p and p+n<=LOCO+0x30,(hex(p),n)
  h=self.u.hook_add(UC_HOOK_MEM_WRITE,audit)
  try:self.u.emu_start(0x4a05f0,0x4a064a,count=10000)
  finally:self.u.hook_del(h)
  assert self.u.reg_read(UC_X86_REG_EIP)==0x4a064a and self.u.reg_read(UC_X86_REG_ESP)==STACK-32
  assert self.u.reg_read(UC_X86_REG_ESI)==LOCO and self.u.reg_read(UC_X86_REG_EDI)==LOCO-4
  assert bytes(self.u.mem_read(STACK,8))==struct.pack('<2I',STOP,LOCO)
  assert bytes(self.u.mem_read(STACK+8,64))==guard
  assert list(struct.unpack('<4I',self.u.mem_read(STACK-32,16)))==[regs[r] for r in (UC_X86_REG_EDI,UC_X86_REG_ESI,UC_X86_REG_EBP,UC_X86_REG_EBX)]
  assert all(bytes(self.u.mem_read(p,n))==old for (p,n),old in zip(inputs,before))
  self.prefixes+=1
 def pose(self,v):
  op,nextRamp,current,previous,start,remaining,duration,tick,rx,ry,dx,dy,desired,from_,fstart,fduration,rate,present,key,mode=v
  self.u.mem_write(ARENA,b'\xa5'*0x5000)
  self.put(ACTOR,VTABLE);self.put(ACTOR+0x5ac,TYPE);self.put(LOCO,0x7a04cc);self.put(LOCO+8,ACTOR)
  self.u.mem_write(ACTOR+0x88,struct.pack('<3i',51*256+128,72*256+128,416))
  self.u.mem_write(ACTOR+0x280,struct.pack('<2I',rx,ry));self.u.mem_write(TYPE+0x330,struct.pack('<2Q',dx,dy))
  for off,n in ((0x2e0,desired),(0x2e4,from_),(0x2e8,fstart),(0x2f0,fduration),(0x2f4,rate)):self.put(ACTOR+off,n)
  for off,n in zip((0x18,0x1c,0x20,0x24,0x28,0x2c),(current,previous,start,0,remaining,duration)):self.put(LOCO+off,n)
  self.put(0xa40d2c,tick);self.put(KEY,key);self.u.mem_write(CELL,b'\xa5'*0x200);self.u.mem_write(CELL+0x11c,bytes([nextRamp]))
  self.events=[];arena=bytes(self.u.mem_read(ARENA,0x5000))
  inputs=self.inputs+[(MAP+0x138,8),(CELL,0x200),(SLOTS,0x100000),(0xa40d2c,4),(VTABLE,0x600)]
  self.active=True
  try:
   if op==1:self.checked_call(0x4a05c0,[LOCO],writes=[(LOCO+0x18,24)],inputs=inputs)
   if op==2:self.prefix(inputs)
   state=struct.unpack('<6i',self.u.mem_read(LOCO+0x18,24))
   def store(u,access,p,n,value,ctx):
    if p==KEY:
     assert n==4;self.events.extend(['K',str(value&0xffffffff)]);self.key_writes+=1
   hook=self.u.hook_add(UC_HOOK_MEM_WRITE,store)
   try:self.checked_call(0x4a0050,[LOCO,OUT,KEY if present else 0],writes=[(OUT,48),(KEY,4)],inputs=inputs+[(LOCO,0x40),(ACTOR,0x800),(TYPE,0x400)])
   finally:self.u.hook_del(hook)
  finally:self.active=False
  assert self.u.reg_read(UC_X86_REG_EAX)==OUT
  after=bytearray(self.u.mem_read(ARENA,0x5000))
  for p,n in ((OUT,48),(KEY,4),(LOCO+0x18,24)):
   offset=p-ARENA;after[offset:offset+n]=arena[offset:offset+n]
  assert bytes(after)==arena,'Drive body arena changed'
  self.body_calls+=1
  return self.events+list(map(str,('S',state[0],state[1],state[2],state[4],state[5],
   *struct.unpack('<12I',self.u.mem_read(OUT,48)),int.from_bytes(self.u.mem_read(KEY,4),'little'))))
