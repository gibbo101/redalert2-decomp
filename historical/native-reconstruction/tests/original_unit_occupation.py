# SPDX-License-Identifier: GPL-3.0-or-later
"""Unmodified Unit occupation roots, actual shared map/floor and audited stores."""
import hashlib,struct
from original_map_floor_height import MapFloorHeightOracle,CELL,INPUT,SLOTS,FALLBACK,MAP,PLANES,packed
from original_presentation import STOP
from original_foot_lit import words,ints,signed
from verify_unit_occupation import verify,RANGES,COMPLETE
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_EDI
OTHER=CELL+0x400
THRESHOLD=0xad057c
def divided(n):return n//256 if n>=0 else -((-n)//256)
def index(x,y):return (divided(y)*512+divided(x))&0xffffffff
class UnitOccupationOracle(MapFloorHeightOracle):
 def __init__(self,exe):
  super().__init__(exe);self.inspection=verify(exe.read_bytes());self.active=False
  self.entries.update({hex(a):0 for a in COMPLETE});self.occupation_stores=0;self.diagnostic_stores=0
  self.floor_queries=0;self.map_queries=0;self.elevated_marks=0;self.elevated_unmarks=0
  for a in COMPLETE:self.u.hook_add(UC_HOOK_CODE,self.code,begin=a,end=a)
  self.u.hook_add(UC_HOOK_CODE,self.observe)
 def block(self,u,a,n,ctx):
  if a!=STOP and not any(p<=a and a+n<=p+size for p,size in RANGES.items()):raise AssertionError(f'Uninspected Unit occupation block {a:#x}/{n}')
 def event(self,*v):self.events.extend(map(str,v))
 def identity(self,p):return (CELL,OTHER,FALLBACK).index(p)
 def observe(self,u,a,n,ctx):
  if not self.active:return
  if a==0x548000:self.map_queries+=1;self.event('C',*ints(u,INPUT,3))
  elif a==0x55a280:
   self.floor_queries+=1;self.event('F',*ints(u,INPUT,3))
   if self.mutation&1:
    x,y,z=ints(u,INPUT,3);u.mem_write(INPUT,packed([x+256,y,z+17]));self.diagnostic_stores+=3
  elif a in (0x70799e,0x7079fe):
   self.event('H',signed(u.reg_read(UC_X86_REG_EAX)))
   if self.mutation&2:
    cell=u.reg_read(UC_X86_REG_EDI);self.put(cell+0x140,words(u,cell+0x140,1)[0]^0x100)
    self.put(THRESHOLD,words(u,THRESHOLD,1)[0]+0x40000000)
    self.put(INPUT+8,words(u,INPUT+8,1)[0]^0x80000000);self.diagnostic_stores+=3
 def run_occupation(self,initial,planes,rows):
  self.u.mem_write(CELL,b'\xa5'*0x10000);self.u.mem_write(FALLBACK,b'\xa5'*0x148)
  self.u.mem_write(SLOTS,bytes(0x100000));self.put(MAP+0x138,SLOTS);self.put(MAP+0x13c,262144)
  self.u.mem_write(0x850bb8,b'\0');self.u.mem_write(0x850ba8,struct.pack('<d',0));self.u.mem_write(0x850bd0,struct.pack('<d',0));self.u.mem_write(PLANES,struct.pack('<100Q',*planes))
  self.put(FALLBACK+0x24,(-7&65535)|(5<<16))
  for p,g,e in zip((CELL,OTHER,FALLBACK),initial[::2],initial[1::2]):self.u.mem_write(p+0x124,packed([g,e]))
  self.events=[];previous=[]
  for row in rows:
   op,x,y,z,resident,level,ramp,other_level,other_ramp,flevel,framp,flags,other_flags,fflags,threshold,self.mutation,current=row
   for slot in previous:self.put(SLOTS+slot*4,0)
   previous=[]
   for bit,p,xx in ((1,CELL,x),(2,OTHER,signed(x+256))):
    slot=index(xx,y)
    if resident&bit and slot<262144:self.put(SLOTS+slot*4,p);previous.append(slot)
   for p,l,r,f,xx in ((CELL,level,ramp,flags,x),(OTHER,other_level,other_ramp,other_flags,signed(x+256)),(FALLBACK,flevel,framp,fflags,None)):
    self.u.mem_write(p+0x11b,bytes([l&255,r]));self.put(p+0x140,f)
    if xx is not None:self.put(p+0x24,(divided(xx)&65535)|((divided(y)&65535)<<16))
   self.put(THRESHOLD,threshold);self.put(0x850c40,current);self.u.mem_write(INPUT,packed([x,y,z]))
   arena=bytes(self.u.mem_read(CELL,0x10000));fb=bytes(self.u.mem_read(FALLBACK,0x148))
   def stores(u,access,p,n,val,ctx):
    if p==FALLBACK+0x24:assert n==4;self.event('P',val&0xffffffff)
    for cell in (CELL,OTHER,FALLBACK):
     if cell+0x124<=p<cell+0x12c:
      assert p in (cell+0x124,cell+0x128) and n==4
      self.occupation_stores+=1;self.event('W',self.identity(cell),p-cell,val&0xffffffff)
      if p==cell+0x128:
       if op:self.elevated_marks+=1
       else:self.elevated_unmarks+=1
   hook=self.u.hook_add(UC_HOOK_MEM_WRITE,stores);self.active=True
   writes=[(0x850bb8,1),(0x850ba8,8),(0x850bd0,8),(PLANES,800),(FALLBACK+0x24,4)]
   for cell in (CELL,OTHER,FALLBACK):writes.extend([(cell+0x124,8)])
   # These mutations are fixture services at named instruction boundaries;
   # all their destinations are separately counted and masked, never instructions.
   if self.mutation:writes.extend([(INPUT,12),(THRESHOLD,4),*[(p+0x140,4) for p in (CELL,OTHER,FALLBACK)]])
   inputs=[(SLOTS,0x100000),(MAP+0x138,8),(0x850c40,4)]
   if not self.mutation:inputs.extend([(INPUT,12),(THRESHOLD,4)])
   try:self.checked_call(0x707980 if op else 0x7079e0,[INPUT],0xdeadbeef,writes=writes,inputs=inputs)
   finally:self.active=False;self.u.hook_del(hook)
   after=bytearray(self.u.mem_read(CELL,0x10000))
   masks=[(CELL+0x124,8),(OTHER+0x124,8)]
   if self.mutation:masks.extend([(INPUT,12),(CELL+0x140,4),(OTHER+0x140,4)])
   for p,n in masks:k=p-CELL;after[k:k+n]=arena[k:k+n]
   assert bytes(after)==arena,'Unit occupation arena changed outside declared fields'
   after=bytearray(self.u.mem_read(FALLBACK,0x148))
   for p,n in [(0x24,4),(0x124,8),*([(0x140,4)] if self.mutation else [])]:after[p:p+n]=fb[p:p+n]
   assert bytes(after)==fb,'Unit occupation fallback changed outside declared fields'
   self.event('S',*[n for p in (CELL,OTHER,FALLBACK) for n in (*words(self.u,p+0x124,2),words(self.u,p+0x140,1)[0])],
    *ints(self.u,INPUT,3),signed(words(self.u,THRESHOLD,1)[0]),hashlib.sha256(self.state()).hexdigest())
  return self.events
