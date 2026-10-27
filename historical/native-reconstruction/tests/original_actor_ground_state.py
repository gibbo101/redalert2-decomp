# SPDX-License-Identifier: GPL-3.0-or-later
"""Unchanged height/ramp writers; actual map/Cell children, supplied Mark."""
import hashlib,struct
from original_map_floor_height import MapFloorHeightOracle,CELL,INPUT,ACTOR,SLOTS,FALLBACK,MAP,PLANES,packed
from original_presentation import STACK,STOP
from original_foot_lit import words,ints,signed,ret
from verify_actor_ground_state import verify,RANGES,COMPLETE
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_ESP,UC_X86_REG_ECX,UC_X86_REG_EAX,UC_X86_REG_ESI,UC_X86_REG_EDI,UC_X86_REG_EBX,UC_X86_REG_EBP,UC_X86_REG_EIP
LOCO=CELL+0x3000;VTABLE=CELL+0x4000;MARK=0x4c2e60
class ActorGroundStateOracle(MapFloorHeightOracle):
 def __init__(self,exe):
  super().__init__(exe);self.inspection=verify(exe.read_bytes());self.active=False
  self.entries.update({hex(a):0 for a in COMPLETE});self.entries[hex(0x4a05f0)]=0
  for a in (*COMPLETE,0x4a05f0):self.u.hook_add(UC_HOOK_CODE,self.code,begin=a,end=a)
  self.u.hook_add(UC_HOOK_CODE,self.observe)
  self.scalar_writes=0;self.supplied_writes=0;self.prefixes=0;self.height_calls=0;self.map_calls=0
 def block(self,u,a,n,ctx):
  if a not in (STOP,MARK) and not any(p<=a and a+n<=p+size for p,size in RANGES.items()):
   raise AssertionError(f'Uninspected ground state block {a:#x}/{n}')
 def event(self,*v):self.events.extend(map(str,v))
 def move(self):
  x,y,z=ints(self.u,ACTOR+0x88,3);self.u.mem_write(ACTOR+0x88,packed([x+256,y-256,z+17]));self.supplied_writes+=3
 def observe(self,u,a,n,ctx):
  if not self.active:return
  sp=u.reg_read(UC_X86_REG_ESP)
  if a==0x49fc30:
   # The nested getter uses this caller's old stack. Supply the otherwise
   # indeterminate temporary padding at the Force child boundary, not before
   # Unlimbo's getter overwrites it. This is an explicit fixture stack input.
   self.put(sp-12,self.temporary);self.supplied_writes+=1
  elif a==MARK:
   assert u.reg_read(UC_X86_REG_ECX)==ACTOR
   kind=words(u,sp+4,1)[0];assert kind in (0,1)
   bridge=u.mem_read(ACTOR+0x79,1)[0];marked=u.mem_read(ACTOR+0x74,1)[0]
   self.event('M',kind,*ints(u,ACTOR+0x88,3),bridge,marked)
   if not kind and self.mutation&1:
    self.move();u.mem_write(ACTOR+0x79,bytes([bridge^255]));u.mem_write(ACTOR+0x74,b'\0');self.supplied_writes+=2
   if kind and self.mutation&2:self.put(ACTOR+0x90,words(u,ACTOR+0x90,1)[0]+1);self.supplied_writes+=1
   ret(u,4,1)
  elif a==0x55a280:
   self.height_calls+=1;self.event('F',*ints(u,words(u,sp+4,1)[0],3))
  elif a==0x548000:
   self.map_calls+=1;self.cell_calls+=1;self.event('C',*ints(u,words(u,sp+4,1)[0],3))
  elif a==0x5d520f and self.mutation&4:self.move()
  elif a==0x4a05db:self.event('R',u.reg_read(UC_X86_REG_ECX))
  elif a==0x4a0611:self.event('R',u.reg_read(UC_X86_REG_ECX))
 def call(self,address,args=(),ecx=0,edx=0,budget=4000000):
  # Both originals copy a temporary padding word without initializing it.
  self.put(STACK-(32 if address==0x4a05c0 else 12),self.temporary)
  super().call(address,args,ecx,edx,budget)
 def prefix(self,writes,inputs):
  guard=b'\xa7'*64;self.u.mem_write(STACK,packed([STOP,LOCO]));self.u.mem_write(STACK+8,guard)
  self.put(STACK-12,self.temporary)
  regs={UC_X86_REG_EBX:0x12345678,UC_X86_REG_ESI:0x23456789,UC_X86_REG_EDI:0x3456789a,UC_X86_REG_EBP:0x456789ab}
  for r,v in regs.items():self.u.reg_write(r,v)
  self.u.reg_write(UC_X86_REG_ESP,STACK);before=[bytes(self.u.mem_read(p,n)) for p,n in inputs]
  allowed=[(STACK-0x2000,STACK),*[(p,p+n) for p,n in writes]]
  def audit(u,access,p,n,v,ctx):assert any(lo<=p and p+n<=hi for lo,hi in allowed),(hex(p),n)
  h=self.u.hook_add(UC_HOOK_MEM_WRITE,audit)
  try:self.u.emu_start(0x4a05f0,0x4a064a,count=10000)
  finally:self.u.hook_del(h)
  assert self.u.reg_read(UC_X86_REG_EIP)==0x4a064a and self.u.reg_read(UC_X86_REG_ESP)==STACK-32
  assert self.u.reg_read(UC_X86_REG_ESI)==LOCO and self.u.reg_read(UC_X86_REG_EDI)==LOCO-4
  assert words(self.u,STACK,2)==[STOP,LOCO] and bytes(self.u.mem_read(STACK+8,64))==guard
  assert words(self.u,STACK-32,4)==[regs[UC_X86_REG_EDI],regs[UC_X86_REG_ESI],regs[UC_X86_REG_EBP],regs[UC_X86_REG_EBX]]
  assert all(bytes(self.u.mem_read(p,n))==old for (p,n),old in zip(inputs,before))
  self.prefixes+=1
 def run_ground(self,v,planes):
  op,tick,height,bridge,marked,bridge_height,x,y,z,resident,level,ramp,flevel,framp,current,previous,start,padding,remaining,duration,self.temporary,self.mutation,mode=v
  self.u.mem_write(CELL,b'\xa5'*0x10000);self.u.mem_write(FALLBACK,b'\xa5'*0x148)
  self.u.mem_write(SLOTS,bytes(0x100000));self.put(MAP+0x138,SLOTS);self.put(MAP+0x13c,262144)
  self.put(0x850c40,104);self.put(0xa72f30,bridge_height);self.put(0xa40d2c,tick)
  self.u.mem_write(0x850bb8,b'\0');self.u.mem_write(0x850ba8,struct.pack('<d',0));self.u.mem_write(0x850bd0,struct.pack('<d',0));self.u.mem_write(PLANES,struct.pack('<100Q',*planes))
  self.put(ACTOR,VTABLE);self.put(VTABLE+0x11c,MARK);self.put(VTABLE+0x1a4,0x5d51e0)
  self.u.mem_write(ACTOR+0x88,packed([x,y,z]));self.u.mem_write(ACTOR+0x74,bytes([marked]));self.u.mem_write(ACTOR+0x79,bytes([bridge]))
  self.put(LOCO,0x7a04cc);self.put(LOCO+8,ACTOR)
  for off,n in zip((0x18,0x1c,0x20,0x24,0x28,0x2c),(current,previous,start,padding,remaining,duration)):self.put(LOCO+off,n)
  self.u.mem_write(CELL+0x11b,bytes([level&255,ramp]));self.u.mem_write(FALLBACK+0x11b,bytes([flevel&255,framp]));self.put(FALLBACK+0x24,(-7&65535)|(5<<16))
  def divided(n):return n//256 if n>=0 else -((-n)//256)
  index=(divided(y)*512+divided(x))&0xffffffff
  if resident and index<262144:self.put(SLOTS+index*4,CELL)
  arena=bytes(self.u.mem_read(CELL,0x10000));fallback=bytes(self.u.mem_read(FALLBACK,0x148));self.events=[];self.cell_calls=0
  def stores(u,access,p,n,val,ctx):
   if p==ACTOR+0x90:assert n==4;self.scalar_writes+=1;self.event('A',0x90,val&0xffffffff)
   elif LOCO+0x18<=p<LOCO+0x30:assert n==4;self.scalar_writes+=1;self.event('D',p-LOCO,val&0xffffffff)
  h=self.u.hook_add(UC_HOOK_MEM_WRITE,stores);self.active=True
  writes=[(ACTOR,0x100),(LOCO+0x18,24),(0x850bb8,1),(0x850ba8,8),(0x850bd0,8),(PLANES,800),(FALLBACK+0x24,4)]
  inputs=[(CELL,0x148),(SLOTS,0x100000),(MAP+0x138,8),(0x850c40,4),(0xa72f30,4),(0xa40d2c,4),(VTABLE,0x200)]
  try:
   if op==0 or op>=4:self.checked_call(0x5d4860,[height],ACTOR,writes=writes,inputs=inputs)
   if op==1:self.checked_call(0x49fc30,[LOCO,height],writes=writes,inputs=inputs)
   elif op in (2,4):self.checked_call(0x4a05c0,[LOCO],writes=writes,inputs=inputs)
   elif op in (3,5):self.prefix(writes,inputs)
  finally:self.active=False;self.u.hook_del(h)
  after=bytearray(self.u.mem_read(CELL,0x10000))
  for p,n in [(ACTOR+0x88,12),(ACTOR+0x74,1),(ACTOR+0x79,1),(LOCO+0x18,24)]:
   k=p-CELL;after[k:k+n]=arena[k:k+n]
  assert bytes(after)==arena,'Ground arena changed outside declared state'
  fb=bytearray(self.u.mem_read(FALLBACK,0x148));fb[0x24:0x28]=fallback[0x24:0x28];assert bytes(fb)==fallback
  self.event('S',*ints(self.u,ACTOR+0x88,3),self.u.mem_read(ACTOR+0x79,1)[0],self.u.mem_read(ACTOR+0x74,1)[0],
   *ints(self.u,LOCO+0x18,6),hashlib.sha256(self.state()).hexdigest())
  return self.events
