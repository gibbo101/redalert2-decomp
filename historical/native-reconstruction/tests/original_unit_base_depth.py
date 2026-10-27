# SPDX-License-Identifier: GPL-3.0-or-later
"""Real base-depth root on the same guest as real map/floor finalization."""
import hashlib,struct
from original_resident_map_floor import ResidentMapFloorOracle
from original_map_preparation import MAP,FALLBACK,CELLS,TYPES,SLOTS
from original_resident_map_finalization import OVERLAYS,OVERLAY_REG
from original_foot_lit import words
from original_presentation import STACK
from verify_resident_map_floor import RANGES as PARENT_RANGES
from verify_unit_base_depth import verify,RANGES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EAX
ACTOR=0x3c00000;TYPE=ACTOR+0x1000
class UnitBaseDepthOracle(ResidentMapFloorOracle):
 def __init__(self,exe):
  self.depth_queries=0;self.dimensions_calls=0;self.base_active=False
  super().__init__(exe);self.inspection=verify(exe.read_bytes());self.u.mem_map(ACTOR,0x10000)
  self.entries.update({hex(a):0 for a in RANGES if a not in PARENT_RANGES})
  for a in set(RANGES).difference(PARENT_RANGES):self.u.hook_add(UC_HOOK_CODE,self.code,begin=a,end=a)
 def block(self,u,a,n,ctx):
  from original_presentation import STOP
  if a in (STOP,0x4068f0):return
  if not any(p<=a and a+n<=p+size for p,size in RANGES.items()):raise AssertionError(f'Uninspected base-depth block {a:#x}/{n}')
 def code(self,u,a,n,ctx):
  if a in RANGES and a not in PARENT_RANGES:self.entries[hex(a)]+=1
  if self.base_active:
   if a in (0x5d4800,0x41b320,0x4b8be0):self.events.append({0x5d4800:401,0x41b320:402,0x4b8be0:403}[a])
   elif a==0x52b690:
    ecx=u.reg_read(UC_X86_REG_ECX);assert TYPES<=ecx<TYPES+self.type_count*1024 and (ecx-TYPES)%1024==0
    sub=words(u,u.reg_read(UC_X86_REG_ESP)+4,1)[0];self.events.extend([404,(ecx-TYPES)//1024,sub]);self.dimensions_calls+=1
  super().code(u,a,n,ctx)
 def run_depth(self,floor,queries):
  self.type_count=len(floor[7]);self.overlay_count=len(floor[9]);result=self.run_floor(*floor)
  self.u.mem_write(ACTOR,bytes(0x800));self.u.mem_write(TYPE,bytes(0xc00));self.put(ACTOR,0x7addf8);self.put(ACTOR+0x5ac,TYPE)
  for row in queries:
   x,y,z,desired,start,timer,duration,rate,tick,scale,current,neighbor,rock,scratch,default=row
   self.u.mem_write(ACTOR+0x88,struct.pack('<3i',x,y,z))
   for off,value in ((0,desired),(4,start),(8,timer),(16,duration),(20,rate)):self.put(ACTOR+0x2e0+off,value)
   self.put(0xa40d2c,tick);self.put(0xa52f00,default);self.u.mem_write(0xabe490,struct.pack('<Q',scale))
   self.u.mem_write(0x7f7124,struct.pack('<3i',current,neighbor,rock));self.put(STACK-0x2c,scratch)
   old_fallback=bytes(self.u.mem_read(FALLBACK,0x148));self.base_active=True
   def stores(u,access,p,n,v,ctx):
    if p==FALLBACK+0x24:assert n==4;self.events.extend([0xffffffff,0,v&0xffffffff])
   hook=self.u.hook_add(UC_HOOK_MEM_WRITE,stores)
   try:self.checked_call(0x6cfea0,ecx=ACTOR,writes=[(FALLBACK+0x24,4)],inputs=[
    (ACTOR,0x800),(TYPE,0xc00),(CELLS,self.count*512),(SLOTS,0x100000),(MAP+0x138,4),
    (TYPES,self.type_count*1024),(0x3200000,self.type_count*4096),(OVERLAYS,self.overlay_count*1024),(OVERLAY_REG,self.overlay_count*4+64),
    (0xa35dec,4),(0xa40cd4,4),(0xa52f00,4),(0xa40d2c,4),(0xabe490,8),(0x7f7124,12),(0x851a70,32)])
   finally:self.base_active=False;self.u.hook_del(hook)
   final=bytearray(self.u.mem_read(FALLBACK,0x148));final[0x24:0x28]=old_fallback[0x24:0x28];assert bytes(final)==old_fallback
   self.depth_queries+=1
   result.extend([str(u) for u in [self.u.reg_read(UC_X86_REG_EAX),words(self.u,STACK-0x2c,1)[0],words(self.u,FALLBACK+0x24,1)[0]]])
   result.append(hashlib.sha256(struct.pack('<'+'I'*len(self.events),*[v&0xffffffff for v in self.events])).hexdigest())
  return result
