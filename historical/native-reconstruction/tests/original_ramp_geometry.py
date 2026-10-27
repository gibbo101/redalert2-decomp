# SPDX-License-Identifier: GPL-3.0-or-later
"""Original stock numeric chains and table leaves, unchanged and guarded."""
import struct
from original_presentation import PresentationOracle,STOP,STACK
from verify_ramp_geometry import (verify,RANGES,SHADOW_ROOTS,CELL_ROOTS,
 SHADOW_GLOBALS,CELL_GLOBALS,CONSTANTS,TABLES)
from verify_voxel_ramp_shadow import OUTPUTS,TABLE
from unicorn import UC_HOOK_BLOCK,UC_HOOK_CODE,UC_HOOK_MEM_WRITE
class RampGeometryOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True)
  self.entries={hex(a):0 for a in RANGES};self.global_stores=0;self.matrix_stores=0
  self.u.hook_add(UC_HOOK_BLOCK,self.block)
  for a in RANGES:self.u.hook_add(UC_HOOK_CODE,self.entry,begin=a,end=a)
  self.inputs=list(RANGES.items())+[(a,8) for a in CONSTANTS]+list(TABLES.items())+[(0xb2af94,4)]
  self.put(0xb2af94,0) # Explicit initial CRT flag; no startup/CRT-global recovery.
 def va(self,a):return a
 def block(self,u,a,n,ctx):
  if a!=STOP and not any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()):
   raise AssertionError(f'Uninspected geometry block {a:#x}/{n}')
 def entry(self,u,a,n,ctx):self.entries[hex(a)]+=1
 def stock(self,seed):
  globals={**SHADOW_GLOBALS,**CELL_GLOBALS};stores=[];matrices=[]
  for a,n in globals.items():self.u.mem_write(a,bytes([(seed*71+0xa7)&255])*n)
  self.u.mem_write(TABLE,bytes((i*13+seed*71)&255 for i in range(21*48)))
  def store(u,access,a,n,v,ctx):
   if a in globals:
    assert n==globals[a];stores.append((a,n,v&((1<<(n*8))-1)))
   elif TABLE<=a<TABLE+21*48:
    assert n==4 and (a-TABLE)%4==0;matrices.append((a,v&0xffffffff))
  hook=self.u.hook_add(UC_HOOK_MEM_WRITE,store)
  try:
   for roots,outputs in ((SHADOW_ROOTS,SHADOW_GLOBALS),(CELL_ROOTS,CELL_GLOBALS)):
    for root,(a,n) in zip(roots,outputs.items()):
     self.checked_call(root,writes=[(a,n)],inputs=self.inputs+[(p,size) for p,size in globals.items() if p!=a])
   assert len(stores)==20 and [a for a,n,v in stores]==list(globals)
   assert all(int.from_bytes(self.u.mem_read(a,n),'little')==v for a,n,v in stores)
   self.put(0x839aac,0)
   self.checked_call(0x718060,writes=OUTPUTS,inputs=self.inputs+list(globals.items())+[(0x839aac,4)])
  finally:self.u.hook_del(hook)
  assert len(matrices)==252 and len({a for a,v in matrices})==252
  assert all(int.from_bytes(self.u.mem_read(a,4),'little')==v for a,v in matrices)
  self.global_stores+=len(stores);self.matrix_stores+=len(matrices)
  # Preserve the two distinct global chains, rather than assuming aliasing.
  values=[]
  for outputs in (SHADOW_GLOBALS,CELL_GLOBALS):
   values.extend(str(int.from_bytes(self.u.mem_read(a,n),'little')) for a,n in outputs.items())
  return values+list(map(str,struct.unpack('<252I',self.u.mem_read(TABLE,21*48))))
 def leaf(self,kind,value):
  args=struct.unpack('<2I',struct.pack('<d',value))
  from unicorn.x86_const import (UC_X86_REG_FP0,UC_X86_REG_FPSW,UC_X86_REG_FPTAG,
   UC_X86_REG_ESP,UC_X86_REG_EBX,UC_X86_REG_ESI,UC_X86_REG_EDI,UC_X86_REG_EBP)
  self.u.reg_write(UC_X86_REG_FPTAG,0xffff);self.u.reg_write(UC_X86_REG_FPSW,0)
  # These cdecl leaves retain both argument dwords; arctangent overwrites the
  # first with its float sign copy. The shared callee-clean root helper does not
  # describe that ABI, so check the actual caller/return boundary here.
  guard=b'\xa7'*64;self.u.mem_write(STACK+12,guard)
  preserved={UC_X86_REG_EBX:0x12345678,UC_X86_REG_ESI:0x23456789,
   UC_X86_REG_EDI:0x3456789a,UC_X86_REG_EBP:0x456789ab}
  before=[bytes(self.u.mem_read(a,n)) for a,n in self.inputs]
  for reg,v in preserved.items():self.u.reg_write(reg,v)
  def store(u,access,a,n,v,ctx):
   if not (STACK-0x2000<=a and a+n<=STACK) and not (STACK+4<=a and a+n<=STACK+12):
    raise AssertionError(f'Unexpected table leaf write {a:#x}/{n}')
  hook=self.u.hook_add(UC_HOOK_MEM_WRITE,store)
  try:self.call(0x4ba520 if kind=='T' else 0x4ba5b0,args)
  finally:self.u.hook_del(hook)
  assert self.u.reg_read(UC_X86_REG_ESP)==STACK+4
  assert bytes(self.u.mem_read(STACK,4))==struct.pack('<I',STOP)
  assert bytes(self.u.mem_read(STACK+12,64))==guard
  assert all(self.u.reg_read(reg)==v for reg,v in preserved.items())
  assert all(bytes(self.u.mem_read(a,n))==old for (a,n),old in zip(self.inputs,before))
  self.audit_calls+=1
  # Both leaves return exact float32 table values widened to x87. Decode the
  # exposed 80-bit ST0 without executing a synthetic guest instruction.
  top=(self.u.reg_read(UC_X86_REG_FPSW)>>11)&7
  mantissa,exponent=self.u.reg_read(UC_X86_REG_FP0+top)
  import math
  result=math.ldexp(mantissa, (exponent&0x7fff)-16383-63)
  if exponent&0x8000:result=-result
  self.u.reg_write(UC_X86_REG_FPTAG,0xffff) # Harness consumes the observed return.
  return [str(struct.unpack('<Q',struct.pack('<d',result))[0])]
