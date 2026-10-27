# SPDX-License-Identifier: GPL-3.0-or-later
"""Actual decisions and Mark effects on the same finalized original Cells."""
import struct
from original_membership_drive import MembershipDriveOracle,CELLS,FALLBACK,HOUSE
from original_movement import UNIT,TYPE,LOCO,VT,STOP
from verify_owned_unit_admission import verify,RANGES
from verify_membership_drive import RANGES as MEMBERSHIP
from verify_unit_admission import DISPATCH
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EIP
EXCLUDED=(0x7030c5,0x7032bf,0x70333d,0x70347d,0x7034d6,0x703506,0x7035c0,
 0x7035ef,0x703601,0x703623,0x703649,0x70371e,0x703748,0x7039df,0x703a23,0x703b7a,
 0x6d7931,0x6d8563,0x70522a,0x705252,0x705256)
class OwnedUnitAdmissionOracle(MembershipDriveOracle):
 admission_codes=(0,3,7)
 def __init__(self,exe):
  super().__init__(exe);self.inspection=verify(exe.read_bytes())
  for off,target in DISPATCH[0x7addf8].items():self.put(VT+off,target)
  self.put(VT+0x4b8,0x705160);self.hooks.pop(0x55acd0);self.hooks.pop(0x6d7910,None)
  self.all_entries={hex(a):0 for a in RANGES};self.instructions=set();self.phase=None
  self.admission_returns={};self.callers={};self.next_calls=0;self.gate_returns={};self.preparation_stores=0
  self.actual_actor57a_checks=0;self.supplied_retry_words=0;self.self_skips=0
 def begin_actor(self,v,route,numeric):
  super().begin_actor(v,route,numeric)
  for off,value,fmt in ((0x14,5,'B'),(0x1b0,0,'I'),(0x1b8,0,'I'),(0x588,0,'I'),(0xcc,0,'I'),(0xd0,0,'I'),(0x10c,0,'I')):self.put(UNIT+off,value,fmt)
  self.u.mem_write(UNIT+0x118,bytes(8))
  for off,value,fmt in ((0xb94,-1,'I'),(0x704,0,'I'),(0x74c,0,'I'),(0xaf3,self.crusher,'B')):self.put(TYPE+off,value,fmt)
  self.put(HOUSE+0x30,0);self.put(HOUSE+0x5674,0);self.put(0x8661d8,0)
  self.u.mem_write(0x851a70,struct.pack('<16h',0,-1,1,-1,1,0,1,1,0,1,-1,1,-1,0,-1,-1))
  for cp in [*[CELLS+i*512 for i in range(self.prepared.count)],FALLBACK]:
   self.put(cp+0x116,-1,'h');self.put(cp+0x54,-1);self.put(cp+0x58,-1)
  # The inherited arena audit covers actor/type/House/Cells/dispatch. Protect
  # the newly entered code and supplied direction/registry/loading inputs too.
  self.owned_inputs=[(a,n,bytes(self.u.mem_read(a,n))) for a,n in RANGES.items() if a not in MEMBERSHIP]
  self.owned_inputs += [(a,n,bytes(self.u.mem_read(a,n))) for a,n in
   ((0x851a70,32),(0x8661d8,4),(0xa40774,4))]
 def state_event(self,result):
  super().state_event(result);self.event('a','s',self.get(UNIT+0x57a,'B'));self.actual_actor57a_checks+=1
 def observe(self,u,a,n,ctx):
  if not self.active or a==STOP:return super().observe(u,a,n,ctx)
  if a not in self.hooks:self.instructions.add(a)
  if a in (0x4a3c2b,0x4a44fe):self.put(u.reg_read(UC_X86_REG_ESP)+0x54,7);self.supplied_retry_words+=1
  if self.phase and a==self.return_to:
   result=u.reg_read(UC_X86_REG_EAX)
   if self.phase=='D':
    assert result in self.admission_codes,result
    if a==0x4a1c9f:assert result==0,'Nonzero Advance result remains outside this join'
    self.admission_returns[result]=self.admission_returns.get(result,0)+1
    self.callers[a]=self.callers.get(a,0)+1;self.event('a','d',result,0,0)
   elif self.phase=='G':
    result&=255;assert result in (0,1);self.gate_returns[result]=self.gate_returns.get(result,0)+1;self.event('a','g',result,0,0)
   self.phase=None
  if a in (0x55acd0,0x703040,0x705160):
   assert self.phase is None
   self.phase={0x55acd0:'G',0x703040:'D',0x705160:'N'}[a]
   self.return_to=self.get(u.reg_read(UC_X86_REG_ESP))
   if self.phase=='D':self.event('a','D',self.cell_id(self.arg(0)),self.arg(1),struct.unpack('<i',struct.pack('<I',self.arg(2)))[0])
   else:
    if self.phase=='N':assert self.arg(1)==1;self.next_calls+=1
    self.event('a',self.phase,*struct.unpack('<hh',u.mem_read(self.arg(1 if self.phase=='G' else 0),4)),0)
  if self.phase:
   assert a not in self.hooks,('Supplied service entered inside actual decision',hex(a))
   assert any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),f'Uninspected owned decision {a:#x}/{n}'
   assert a not in EXCLUDED,hex(a)
   self.instructions.add(a)
   if a in RANGES:self.all_entries[hex(a)]+=1
   if a==0x548070:self.event('W',*struct.unpack('<hh',u.mem_read(self.arg(0),4)))
   if a==0x703a95:self.self_skips+=1
   return
  if any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()) and not any(lo<=a and a+n<=lo+size for lo,size in MEMBERSHIP.items()):
   assert a not in EXCLUDED,hex(a)
   if a in RANGES:self.all_entries[hex(a)]+=1
   return
  return super().observe(u,a,n,ctx)
 def store(self,u,access,a,n,v,ctx):
  if self.active and 0x4a2670<=u.reg_read(UC_X86_REG_EIP)<0x4a4725:
   if UNIT+0x4d0<=a<UNIT+0x53c or a in (UNIT+0x57a,UNIT+0x57b):self.event('A',a-UNIT,v&0xffffffff);self.preparation_stores+=1
   if a-LOCO in (0x40,0x44,0x48,0x58,0x5c,0x63):self.event('a','L',a-LOCO,v&0xffffffff);self.preparation_stores+=1
  return super().store(u,access,a,n,v,ctx)
 def run_owned(self,v,route,numeric,crusher):
  self.crusher=crusher;result=super().run_joined(v,route,numeric)
  assert self.phase is None
  assert all(bytes(self.u.mem_read(a,n))==before for a,n,before in self.owned_inputs),'Owned decision immutable input changed'
  return result
