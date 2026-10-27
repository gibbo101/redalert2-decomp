# SPDX-License-Identifier: GPL-3.0-or-later
"""Actual setters/floor children and two scoped original Advance placement blocks."""
import hashlib,struct
from original_actor_ground_state import ActorGroundStateOracle,VTABLE,MARK,LOCO
from original_map_floor_height import CELL,INPUT,ACTOR,SLOTS,FALLBACK,MAP,PLANES,packed
from original_presentation import PresentationOracle,STACK,STOP
from original_foot_lit import words,ints,ret
from verify_ground_movement_placement import verify,RANGES,COMPLETE
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import (UC_X86_REG_ESP,UC_X86_REG_EIP,UC_X86_REG_EAX,UC_X86_REG_EBX,
 UC_X86_REG_ECX,UC_X86_REG_EDX,UC_X86_REG_EBP,UC_X86_REG_ESI,UC_X86_REG_EDI,UC_X86_REG_FPCW)
class GroundMovementPlacementOracle(ActorGroundStateOracle):
 # This family has no Force/Process temporary timer. Use the base complete-call
 # setup rather than the state-writer fixture's extra opaque-padding injection.
 call=PresentationOracle.call
 def __init__(self,exe):
  super().__init__(exe);self.inspection=verify(exe.read_bytes())
  for a in COMPLETE:
   self.entries[hex(a)]=0;self.u.hook_add(UC_HOOK_CODE,self.code,begin=a,end=a)
  self.blocks=0;self.location_roots=0;self.actual_stores=0;self.Mark_calls=0
 def block(self,u,a,n,ctx):
  if a not in (STOP,MARK,0x4a263a) and not any(p<=a and a+n<=p+size for p,size in RANGES.items()):
   raise AssertionError(f'Uninspected movement placement block {a:#x}/{n}')
 def observe(self,u,a,n,ctx):
  if not self.active:return
  sp=u.reg_read(UC_X86_REG_ESP)
  if a==0x4a263a:
   assert self.operation==2;u.emu_stop()
  elif a==MARK:
   assert u.reg_read(UC_X86_REG_ECX)==ACTOR;kind=words(u,sp+4,1)[0];assert kind in (0,1)
   bridge=u.mem_read(ACTOR+0x79,1)[0];flag=u.mem_read(ACTOR+0x74,1)[0]
   self.event('M',kind,*ints(u,ACTOR+0x88,3),bridge,flag);self.Mark_calls+=1
   if self.mutation&1:u.mem_write(ACTOR+0x74,bytes([kind]))
   if not kind and self.mutation&2:
    x,y,z=ints(u,ACTOR+0x88,3);u.mem_write(ACTOR+0x88,packed([x+17,y-19,z+23]))
    u.mem_write(ACTOR+0x79,bytes([bridge^255]));u.mem_write(ACTOR+0x7d,bytes([u.mem_read(ACTOR+0x7d,1)[0]^255]))
   if not kind and self.mutation&4:
    x,y,z=ints(u,INPUT,3);u.mem_write(INPUT,packed([x+256,y-256,z+31]))
   if kind and self.mutation&8:self.put(ACTOR+0x90,words(u,ACTOR+0x90,1)[0]+1)
   ret(u,4,1)
  elif a==0x55a280:self.event('F',*ints(u,words(u,sp+4,1)[0],3));self.height_calls+=1
  elif a==0x548000:self.event('C',*ints(u,words(u,sp+4,1)[0],3));self.map_calls+=1
 def placement_block(self,op,writes,inputs):
  self.u.mem_write(STACK,b'\xa7'*0x200);self.u.mem_write(STACK-0x2100,b'\xa7'*0x100)
  regs={UC_X86_REG_EBX:ACTOR,UC_X86_REG_ECX:ACTOR,UC_X86_REG_EDX:ACTOR+0x88,
   UC_X86_REG_EBP:LOCO,UC_X86_REG_ESI:INPUT,UC_X86_REG_EDI:0x3456789a}
  for r,v in regs.items():self.u.reg_write(r,v)
  self.put(LOCO+0xc,ACTOR)
  if op==2:self.u.mem_write(STACK+0x48,bytes(self.u.mem_read(INPUT,12)))
  self.u.reg_write(UC_X86_REG_ESP,STACK);self.u.reg_write(UC_X86_REG_FPCW,0xe7f)
  before=[bytes(self.u.mem_read(p,n)) for p,n in inputs]
  scratch=bytes(self.u.mem_read(STACK,0x200))
  allowed=[(STACK-0x2000,STACK),*[(p,p+n) for p,n in writes]]
  scratch_writes=[(STACK+0x13,1),(STACK+0x36,2),(STACK+0x64,4)] if op==1 else []
  allowed.extend((p,p+n) for p,n in scratch_writes)
  def audit(u,access,p,n,v,ctx):assert any(lo<=p and p+n<=hi for lo,hi in allowed),(hex(p),n)
  h=self.u.hook_add(UC_HOOK_MEM_WRITE,audit)
  start,end=(0x4a2054,0x4a2112) if op==1 else (0x4a1ab0,0x4a1afb)
  try:self.u.emu_start(start,end,count=10000)
  finally:self.u.hook_del(h)
  exit_=self.u.reg_read(UC_X86_REG_EIP);assert exit_ in ((end,) if op==1 else (end,0x4a263a))
  assert self.u.reg_read(UC_X86_REG_ESP)==STACK and self.u.reg_read(UC_X86_REG_EBP)==LOCO
  assert self.u.reg_read(UC_X86_REG_ESI)==INPUT
  after=bytearray(self.u.mem_read(STACK,0x200))
  for p,n in scratch_writes:after[p-STACK:p-STACK+n]=scratch[p-STACK:p-STACK+n]
  assert bytes(after)==scratch and bytes(self.u.mem_read(STACK-0x2100,0x100))==b'\xa7'*0x100
  assert all(bytes(self.u.mem_read(p,n))==old for (p,n),old in zip(inputs,before))
  self.blocks+=1
 def place(self,v,planes):
  op,onmap,marked,bridge,bh,x,y,z,nx,ny,nz,resident,level,ramp,fl,fr,self.mutation,mode=v;self.operation=op
  self.u.mem_write(CELL,b'\xa5'*0x10000);self.u.mem_write(FALLBACK,b'\xa5'*0x148)
  self.u.mem_write(SLOTS,bytes(0x100000));self.put(MAP+0x138,SLOTS);self.put(MAP+0x13c,262144)
  self.put(0x850c40,104);self.put(0xa72f30,bh)
  self.u.mem_write(0x850bb8,b'\0');self.u.mem_write(0x850ba8,struct.pack('<d',0));self.u.mem_write(0x850bd0,struct.pack('<d',0));self.u.mem_write(PLANES,struct.pack('<100Q',*planes))
  self.put(ACTOR,VTABLE);self.put(VTABLE+0x11c,MARK);self.put(VTABLE+0x19c,0x4ca160);self.put(VTABLE+0x1b4,0x5d4860)
  self.u.mem_write(ACTOR+0x88,packed([x,y,z]));self.u.mem_write(ACTOR+0x74,bytes([marked]));self.u.mem_write(ACTOR+0x79,bytes([bridge]));self.u.mem_write(ACTOR+0x7d,bytes([onmap]))
  self.u.mem_write(INPUT,packed([nx,ny,nz]));self.u.mem_write(CELL+0x11b,bytes([level&255,ramp]));self.u.mem_write(FALLBACK+0x11b,bytes([fl&255,fr]));self.put(FALLBACK+0x24,(-7&65535)|(5<<16))
  def div(n):return n//256 if n>=0 else -((-n)//256)
  index=(div(ny)*512+div(nx))&0xffffffff
  if resident and index<262144:self.put(SLOTS+4*index,CELL)
  arena=bytes(self.u.mem_read(CELL,0x10000));fallback=bytes(self.u.mem_read(FALLBACK,0x148));self.events=[]
  def stores(u,access,p,n,val,ctx):
   if p in (ACTOR+0x74,ACTOR+0x88,ACTOR+0x8c,ACTOR+0x90):
    assert n==(1 if p==ACTOR+0x74 else 4);self.actual_stores+=1;self.event('A',p-ACTOR,val&((1<<(8*n))-1))
  h=self.u.hook_add(UC_HOOK_MEM_WRITE,stores);self.active=True
  writes=[(ACTOR+0x74,1),(ACTOR+0x88,12),(0x850bb8,1),(0x850ba8,8),(0x850bd0,8),(PLANES,800),(FALLBACK+0x24,4)]
  inputs=[*RANGES.items(),(CELL,0x148),(SLOTS,0x100000),(MAP+0x138,8),(0x850c40,4),(0xa72f30,4),(VTABLE,0x200)]
  try:
   if op==0:self.checked_call(0x4ca160,[INPUT],ACTOR,writes=writes,inputs=inputs);self.location_roots+=1
   else:self.placement_block(op,writes,inputs)
  finally:self.active=False;self.u.hook_del(h)
  after=bytearray(self.u.mem_read(CELL,0x10000))
  for p,n in ((ACTOR+0x74,1),(ACTOR+0x79,1),(ACTOR+0x7d,1),(ACTOR+0x88,12),(INPUT,12),(LOCO+0xc,4)):
   k=p-CELL;after[k:k+n]=arena[k:k+n]
  assert bytes(after)==arena
  fb=bytearray(self.u.mem_read(FALLBACK,0x148));fb[0x24:0x28]=fallback[0x24:0x28];assert bytes(fb)==fallback
  self.event('S',*ints(self.u,ACTOR+0x88,3),self.u.mem_read(ACTOR+0x74,1)[0],self.u.mem_read(ACTOR+0x79,1)[0],self.u.mem_read(ACTOR+0x7d,1)[0],
   *ints(self.u,INPUT,3),hashlib.sha256(self.state()).hexdigest())
  return self.events
