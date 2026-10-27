# SPDX-License-Identifier: GPL-3.0-or-later
"""Unmodified complete height queries with actual nested Cell arithmetic."""
import hashlib,struct
from original_presentation import PresentationOracle,STACK,STOP
from original_foot_lit import words
from verify_map_floor_height import verify,RANGES
from unicorn import UC_HOOK_CODE,UC_HOOK_BLOCK,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX
CELL=0x2400000;INPUT=CELL+0x1000;OUT=CELL+0x1100;ACTOR=CELL+0x2000;SLOTS=0x2500000
FALLBACK=0xa6f9f8;MAP=0x8324e0;PLANES=0x7d27e8
def packed(v):return struct.pack('<'+'I'*len(v),*[n&0xffffffff for n in v])
class MapFloorHeightOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True)
  self.u.mem_map(CELL,0x10000);self.u.mem_map(SLOTS,0x100000)
  self.entries={hex(a):0 for a in RANGES};self.writes=self.flag_writes=self.fallback_writes=0
  self.u.hook_add(UC_HOOK_BLOCK,self.block)
  for a in RANGES:self.u.hook_add(UC_HOOK_CODE,self.code,begin=a,end=a)
 def va(self,a):return a
 def block(self,u,a,n,ctx):
  if a!=STOP and not any(p<=a and a+n<=p+size for p,size in RANGES.items()):raise AssertionError(f'Uninspected height block {a:#x}/{n}')
 def code(self,u,a,n,ctx):self.entries[hex(a)]+=1
 def state(self):
  return bytes(self.u.mem_read(0x850bb8,1))+bytes(self.u.mem_read(0x850ba8,8))+bytes(self.u.mem_read(0x850bd0,8))+bytes(self.u.mem_read(PLANES,800))+bytes(self.u.mem_read(FALLBACK+0x24,4))
 def run(self,mode,flags,h,scale,planes,rows):
  self.u.mem_write(0x850bb8,bytes([flags]));self.u.mem_write(0x850ba8,struct.pack('<Q',h));self.u.mem_write(0x850bd0,struct.pack('<Q',scale));self.u.mem_write(PLANES,struct.pack('<100Q',*planes))
  self.u.mem_write(CELL,b'\xa5'*0x148);self.u.mem_write(FALLBACK,b'\xa5'*0x148);self.put(FALLBACK+0x24,(-7&65535)|(5<<16));self.u.mem_write(ACTOR,b'\xa5'*0x100)
  self.u.mem_write(SLOTS,bytes(0x100000));self.put(MAP+0x138,SLOTS);self.put(MAP+0x13c,262144);last_slot=None;results=[]
  for row in rows:
   current,level,ramp,x,y,z,bridge,bridge_height,slot,present,flevel,framp=row
   if last_slot is not None:self.put(SLOTS+last_slot*4,0)
   self.put(SLOTS+slot*4,CELL if present else 0);last_slot=slot
   self.put(0x850c40,current);self.put(0xa72f30,bridge_height)
   self.u.mem_write(CELL+0x11b,bytes([level&255,ramp]));self.put(CELL+0x24,(x&65535)|((y&65535)<<16))
   self.u.mem_write(FALLBACK+0x11b,bytes([flevel&255,framp]));self.u.mem_write(INPUT,packed([x,y,z]));self.u.mem_write(OUT,b'\xa7'*12)
   self.u.mem_write(ACTOR+0x88,packed([x,y,z]));self.u.mem_write(ACTOR+0x79,bytes([bridge]))
   old_cell=bytes(self.u.mem_read(CELL,0x148));old_fallback=bytes(self.u.mem_read(FALLBACK,0x148));old_actor=bytes(self.u.mem_read(ACTOR,0x100))
   def stores(u,access,p,n,v,ctx):
    self.writes+=1
    if p==0x850bb8:assert n==1;self.flag_writes+=1
    elif p==FALLBACK+0x24:assert n==4;self.fallback_writes+=1
    elif PLANES<=p<PLANES+800:assert n in (4,8) and (p-PLANES)%4==0
   hook=self.u.hook_add(UC_HOOK_MEM_WRITE,stores)
   try:
    a,args,ecx={'H':(0x4706c0,[INPUT],CELL),'C':(0x47ba50,[OUT],CELL),'M':(0x55a280,[INPUT],MAP),'R':(0x5d4810,[],ACTOR)}[mode]
    self.checked_call(a,args,ecx,writes=[(0x850bb8,1),(0x850ba8,8),(0x850bd0,8),(PLANES,800),(FALLBACK+0x24,4),(OUT,12)],
     inputs=[(CELL,0x148),(INPUT,12),(ACTOR,0x100),(SLOTS,0x100000),(MAP+0x138,8),(0x850c40,4),(0xa72f30,4)])
   finally:self.u.hook_del(hook)
   assert bytes(self.u.mem_read(CELL,0x148))==old_cell and bytes(self.u.mem_read(ACTOR,0x100))==old_actor
   fallback=bytearray(self.u.mem_read(FALLBACK,0x148));fallback[0x24:0x28]=old_fallback[0x24:0x28];assert bytes(fallback)==old_fallback
   value=words(self.u,OUT,3) if mode=='C' else [self.u.reg_read(UC_X86_REG_EAX)]
   results.extend(map(str,value));results.append(hashlib.sha256(self.state()).hexdigest())
  return results
