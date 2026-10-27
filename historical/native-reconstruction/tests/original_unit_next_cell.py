# SPDX-License-Identifier: GPL-3.0-or-later
"""Unchanged next-Cell early paths with complete root/arena/stack audits."""
import struct
from original_presentation import PresentationOracle,STACK,STOP
from verify_unit_next_cell import verify,RANGES,DISPATCH
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_ECX,UC_X86_REG_ESP
ARENA=0x2600000;SIZE=0x10000;ACTOR=ARENA;TYPE=ARENA+0x2000;ARG=ARENA+0x4000
CELLS=[ARENA+0x5000,ARENA+0x5200,0xa6f9f8];SLOTS=0x2700000
LOCATIONS={'target_lookup':0x705172,'coordinate_query':0x705196,'current_lookup':0x7051d4,
 'ability':0x705204,'primary_test':0x705245,'elevated_test':0x70521d,'early_exit':0x7053df}
class UnitNextCellOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True)
  self.u.mem_map(ARENA,SIZE);self.u.mem_map(SLOTS,0x100000);self.active=False
  self.events=[];self.entries={hex(a):0 for a in RANGES};self.instructions=set();self.locations={k:0 for k in LOCATIONS};self.stores=0
  self.u.hook_add(UC_HOOK_CODE,self.code)
 def va(self,a):return a
 def word(self,p):return int.from_bytes(self.u.mem_read(p,4),'little')
 def event(self,k,a=0,b=0,c=0):self.events.extend(map(str,(k,a,b,c)))
 def code(self,u,a,n,ctx):
  if not self.active or a==STOP:return
  assert any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),f'Uninspected next-Cell instruction {a:#x}/{n}'
  assert a not in (0x70522a,0x705252,0x705256,0x6d7931),f'Unsupported next-Cell branch {a:#x}'
  self.instructions.add(a)
  if a in RANGES:self.entries[hex(a)]+=1
  for k,p in LOCATIONS.items():
   if a==p:self.locations[k]+=1
  sp=u.reg_read(UC_X86_REG_ESP);ecx=u.reg_read(UC_X86_REG_ECX)
  if a==0x548070:self.event('L',*struct.unpack('<hh',u.mem_read(self.word(sp+4),4)))
  elif a==0x5d4e40:assert ecx==ACTOR;self.event('C',0)
  elif a==0x6d7910:assert ecx==ACTOR and self.word(sp+4)==17;self.event('b',0,17)
  elif a in (0x7133a0,0x713420):assert ecx==ACTOR+0x118;self.event('v',0,1 if a==0x7133a0 else 2)
  elif a in (0x70521d,0x705245):
   # ESI holds the actual retained target, even when current lookup aliases fallback.
   from unicorn.x86_const import UC_X86_REG_ESI
   p=u.reg_read(UC_X86_REG_ESI);e=int(a==0x70521d)
   self.event('S',CELLS.index(p),e,self.word(p+(0x128 if e else 0x124))&31)
 def run(self,slots,cells,actor,steps):
  u=self.u;u.mem_write(ARENA,b'\xa5'*SIZE);u.mem_write(SLOTS,bytes(0x100000));u.mem_write(CELLS[2],b'\xa5'*0x148)
  self.put(0x832618,SLOTS);self.put(ACTOR,0x7addf8);self.put(ACTOR+0x5ac,TYPE);u.mem_write(ACTOR+0x118,bytes(8))
  x,y,z,bridge,crusher=actor;u.mem_write(ACTOR+0x88,struct.pack('<iii',x,y,z));u.mem_write(ACTOR+0x79,bytes([bridge]));u.mem_write(TYPE+0xaf3,bytes([crusher]))
  for i,index in enumerate(slots):
   if index!=-1:self.put(SLOTS+4*index,CELLS[i])
  for p,row in zip(CELLS,cells):
   x,y,level,flags,occ,eocc,head,ehead=row
   u.mem_write(p+0x24,struct.pack('<hh',x,y));u.mem_write(p+0x11b,bytes([level&255]))
   for off,v in ((0x140,flags),(0x124,occ),(0x128,eocc),(0xe4,head),(0xe8,ehead)):self.put(p+off,v)
  self.events=[]
  ranges=[*RANGES.items(),*[(0x7addf8+off,4) for off in DISPATCH],(0x79a708,8),(0x79a6f8,8),(0x832618,4),(SLOTS,0x100000)]
  for x,y,warning in steps:
   u.mem_write(ARG,struct.pack('<hh',x,y));before=bytes(u.mem_read(ARENA,SIZE));fb=bytes(u.mem_read(CELLS[2],0x148))
   def writes(u,access,p,n,v,ctx):
    if p==CELLS[2]+0x24:assert n==4;self.event('F',*struct.unpack('<hh',struct.pack('<I',v&0xffffffff)));self.stores+=1
   hook=u.hook_add(UC_HOOK_MEM_WRITE,writes);self.active=True
   try:self.checked_call(0x705160,[ARG,warning],ACTOR,writes=[(CELLS[2]+0x24,4)],inputs=ranges)
   finally:self.active=False;u.hook_del(hook)
   assert bytes(u.mem_read(ARENA,SIZE))==before,'Next-Cell changed actor/type/ordinary Cell arena'
   after=bytearray(u.mem_read(CELLS[2],0x148));after[0x24:0x28]=fb[0x24:0x28];assert bytes(after)==fb,'Next-Cell changed fallback attributes'
   self.event('z',*struct.unpack('<hh',u.mem_read(CELLS[2]+0x24,4)))
  return self.events
