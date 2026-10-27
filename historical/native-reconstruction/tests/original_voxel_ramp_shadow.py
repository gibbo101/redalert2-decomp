# SPDX-License-Identifier: GPL-3.0-or-later
"""Unchanged complete initializer; no child or instruction substitution."""
import struct
from original_presentation import PresentationOracle,STOP
from verify_voxel_ramp_shadow import verify,RANGES,TABLE,OUTPUTS
from unicorn import UC_HOOK_BLOCK,UC_HOOK_CODE,UC_HOOK_MEM_WRITE
class VoxelRampShadowOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True)
  self.entries={hex(a):0 for a in RANGES};self.table_stores=0
  self.u.hook_add(UC_HOOK_BLOCK,self.block)
  for a in RANGES:self.u.hook_add(UC_HOOK_CODE,self.entry,begin=a,end=a)
 def va(self,a):return a
 def block(self,u,a,n,ctx):
  if a!=STOP and not any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()):raise AssertionError(f'Uninspected initializer block {a:#x}')
 def entry(self,u,a,n,ctx):self.entries[hex(a)]+=1
 def run(self,axis,diagonal,seed):
  for a,v in ((0xaf7398,diagonal),(0xaf77a0,axis),(0xaf7390,0.),(0xaf7928,0.)):
   self.u.mem_write(a,struct.pack('<d',v))
  self.put(0x839aac,0)
  self.u.mem_write(TABLE,bytes((i*13+seed*71)&255 for i in range(21*48)))
  stores=[]
  def store(u,access,a,n,v,ctx):
   if TABLE<=a<TABLE+21*48:
    assert n==4 and (a-TABLE)%4==0;stores.append((a-TABLE,v&0xffffffff))
  hook=self.u.hook_add(UC_HOOK_MEM_WRITE,store)
  try:self.checked_call(0x718060,writes=OUTPUTS,
   inputs=[(a,8) for a in (0xaf7398,0xaf77a0,0xaf7390,0xaf7928)]+[(0x839aac,4)]+list(RANGES.items()))
  finally:self.u.hook_del(hook)
  assert len(stores)==252 and len({a for a,v in stores})==252
  values=list(struct.unpack('<252I',self.u.mem_read(TABLE,21*48)))
  assert all(values[a//4]==v for a,v in stores)
  self.table_stores+=len(stores)
  return list(map(str,values))
