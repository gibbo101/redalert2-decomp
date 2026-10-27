# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete Foot depth on the guest's own finalized Cell/TMP records."""
import hashlib,struct
from original_unit_base_depth import UnitBaseDepthOracle,ACTOR,TYPE
from original_map_preparation import MAP,FALLBACK,CELLS,TYPES,SLOTS
from original_resident_map_finalization import OVERLAYS,OVERLAY_REG
from original_foot_lit import words
from original_presentation import STOP
from verify_unit_base_depth import RANGES as PARENT_RANGES
from verify_prepared_foot_depth import RANGES,verify
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_ECX,UC_X86_REG_EAX
LOCO=ACTOR+0x2000
PREDICATES=(0x6cf9d0,0x6cfb60,0x6cfda0,0x6cf670,0x6cf820)
class PreparedFootDepthOracle(UnitBaseDepthOracle):
 def __init__(self,exe):
  self.foot_active=False;self.foot_calls=self.gradient_calls=self.cell_predicates=0
  super().__init__(exe);self.inspection=verify(exe.read_bytes())
  self.entries.update({hex(a):0 for a in RANGES if a not in PARENT_RANGES})
  for a in set(RANGES).difference(PARENT_RANGES):self.u.hook_add(UC_HOOK_CODE,self.code,begin=a,end=a)
 def block(self,u,a,n,ctx):
  if a in (STOP,0x4068f0):return
  if not any(p<=a and a+n<=p+size for p,size in RANGES.items()):raise AssertionError(f'Uninspected prepared Foot block {a:#x}/{n}')
 def code(self,u,a,n,ctx):
  if a in RANGES and a not in PARENT_RANGES:self.entries[hex(a)]+=1
  if self.foot_active:
   if a in PREDICATES:self.events.append(410+PREDICATES.index(a))
   elif a in (0x6c12c0,0x4a4830,0x4a4840,0x6cfea0):self.events.append({0x6c12c0:420,0x4a4830:421,0x4a4840:422,0x6cfea0:424}[a])
   elif a==0x479cc0:
    p=u.reg_read(UC_X86_REG_ECX);assert p==FALLBACK or CELLS<=p<CELLS+self.count*512
    self.events.extend([423,words(u,p+0x24,1)[0]]);self.cell_predicates+=1
  super().code(u,a,n,ctx)
 def run_foot(self,floor,queries):
  result=self.run_depth(floor,[])
  for row in queries:
   x,y,z,desired,start,timer,duration,rate,tick,scale,current,neighbor,rock,scratch,default,drive,tilebase,ix,iy,b60,b64,b5c,b68=row
   self.u.mem_write(ACTOR+0x88,struct.pack('<3i',x,y,z))
   for off,value in ((0,desired),(4,start),(8,timer),(16,duration),(20,rate)):self.put(ACTOR+0x2e0+off,value)
   self.put(ACTOR+0x564,LOCO+4 if drive else 0);self.put(LOCO+4,0x7a04cc)
   for off,value in ((0xb60,b60),(0xb64,b64),(0xb5c,b5c),(0xb68,b68)):self.put(TYPE+off,value)
   self.put(0xa40d2c,tick);self.put(0xa52f00,default);self.u.mem_write(0xabe490,struct.pack('<Q',scale))
   self.u.mem_write(0x7f7124,struct.pack('<3i',current,neighbor,rock));self.put(0xa52c74,tilebase);self.put(0xac0148,(ix&65535)|((iy&65535)<<16))
   old=bytes(self.u.mem_read(FALLBACK,0x148));self.base_active=self.foot_active=True
   def stores(u,access,p,n,v,ctx):
    if p==FALLBACK+0x24:assert n==4;self.events.extend([0xffffffff,0,v&0xffffffff])
   hook=self.u.hook_add(UC_HOOK_MEM_WRITE,stores)
   inputs=[(ACTOR,0x3000),(CELLS,self.count*512),(SLOTS,0x100000),(MAP+0x138,4),
    (TYPES,self.type_count*1024),(0x3200000,self.type_count*4096),(OVERLAYS,self.overlay_count*1024),(OVERLAY_REG,self.overlay_count*4+64),
    (0xa35dec,4),(0xa40cd4,4),(0xa52f00,4),(0xa40d2c,4),(0xabe490,8),(0x7f7124,12),(0x851a70,32),(0xa52c74,4),(0x8661d8,4),(0xac0148,4)]
   try:
    self.checked_call(0x4c9930,ecx=ACTOR,writes=[(FALLBACK+0x24,4)],inputs=inputs);depth=self.u.reg_read(UC_X86_REG_EAX);self.foot_calls+=1
    self.checked_call(0x4c9a10,ecx=ACTOR,inputs=inputs);gradient=self.u.reg_read(UC_X86_REG_EAX);self.gradient_calls+=1
   finally:self.base_active=self.foot_active=False;self.u.hook_del(hook)
   final=bytearray(self.u.mem_read(FALLBACK,0x148));final[0x24:0x28]=old[0x24:0x28];assert bytes(final)==old
   result.extend(map(str,[depth,gradient,words(self.u,FALLBACK+0x24,1)[0]]))
   result.append(hashlib.sha256(struct.pack('<'+'I'*len(self.events),*[v&0xffffffff for v in self.events])).hexdigest())
  return result
