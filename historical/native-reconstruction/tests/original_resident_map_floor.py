# SPDX-License-Identifier: GPL-3.0-or-later
"""Execute real floor height inside the real shared map finalization guest."""
import hashlib,struct
from original_resident_map_finalization import ResidentMapFinalizationOracle
from original_map_preparation import CELLS
from original_foot_lit import words
from original_presentation import STOP
from verify_resident_map_finalization import RANGES as PARENT_RANGES
from verify_resident_map_floor import RANGES,verify
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_ECX,UC_X86_REG_ESP
PLANES=0x7d27e8
class ResidentMapFloorOracle(ResidentMapFinalizationOracle):
 def __init__(self,exe):
  self.floor_calls=self.flag_stores=self.plane_stores=0;self.floor_samples=[]
  super().__init__(exe);self.inspection=verify(exe.read_bytes())
  self.entries.update({hex(a):0 for a in RANGES if a not in PARENT_RANGES})
  for a in set(RANGES).difference(PARENT_RANGES,{0x4706c0}):self.u.hook_add(UC_HOOK_CODE,self.code,begin=a,end=a)
 def block(self,u,a,n,ctx):
  if a in (STOP,0x4068f0):return
  if not any(p<=a and a+n<=p+size for p,size in RANGES.items()):raise AssertionError(f'Uninspected floor-parent block {a:#x}/{n}')
 def code(self,u,a,n,ctx):
  if a not in PARENT_RANGES and a in RANGES:self.entries[hex(a)]+=1
  if a==0x4706c0:
   cell=u.reg_read(UC_X86_REG_ECX);assert cell==CELLS+self.owner_cell*512
   ptr=words(u,u.reg_read(UC_X86_REG_ESP)+4,1)[0]
   self.events.extend([317,self.owner_cell,*words(u,ptr,2)])
   self.floor_calls+=1
   self.floor_samples.append([self.owner_cell,*bytes(u.mem_read(cell+0x11b,2))])
   return # Observe only: the actual Cell floor instructions execute unchanged.
  super().code(u,a,n,ctx)
 def checked_call(self,a,args=(),ecx=0,edx=0,*,writes=(),inputs=()):
  if a==0x54b2e0:
   flags,h,scale,planes,current=self.floor_input
   self.u.mem_write(0x850bb8,bytes([flags]));self.u.mem_write(0x850ba8,struct.pack('<Q',h))
   self.u.mem_write(0x850bd0,struct.pack('<Q',scale));self.u.mem_write(PLANES,struct.pack('<100Q',*planes));self.put(0x850c40,current)
   writes=[*writes,(0x850bb8,1),(0x850ba8,8),(0x850bd0,8),(PLANES,800)]
   inputs=[*inputs,(0x850c40,4),*[(p,8) for p in (0x79a728,0x79a730,0x79b610,0x79c9b0)],(0x7d8964,4)]
  return super().checked_call(a,args,ecx,edx,writes=writes,inputs=inputs)
 def run_floor(self,flags,h,scale,planes,current,*parent):
  self.floor_input=flags,h,scale,planes,current
  def stores(u,access,p,n,v,ctx):
   if p==0x850bb8:assert n==1;self.flag_stores+=1
   elif PLANES<=p<PLANES+800:assert n in (4,8) and (p-PLANES)%4==0;self.plane_stores+=1
  hook=self.u.hook_add(UC_HOOK_MEM_WRITE,stores)
  try:result=super().run(*parent)
  finally:self.u.hook_del(hook)
  state=bytes(self.u.mem_read(0x850bb8,1))+bytes(self.u.mem_read(0x850ba8,8))+bytes(self.u.mem_read(0x850bd0,8))+bytes(self.u.mem_read(PLANES,800))
  result.append(hashlib.sha256(state).hexdigest())
  return result
