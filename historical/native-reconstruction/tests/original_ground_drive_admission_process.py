# SPDX-License-Identifier: GPL-3.0-or-later
"""Actual Unit admission/gate/next-Cell inside complete original Process."""
import struct
from original_ground_drive_gate_process import GroundDriveGateProcessOracle,OBJECTS,TYPES,HOUSES,oid
from original_ground_drive_advance import CELLS,SLOTS
from original_movement import UNIT,TYPE,LOCO,VT,STOP
from original_map_floor_height import FALLBACK
from verify_ground_drive_admission_process import verify,RANGES
from verify_ground_drive_gate_process import RANGES as OLD
from verify_unit_admission import DISPATCH
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EIP
class GroundDriveAdmissionProcessOracle(GroundDriveGateProcessOracle):
 admission_ranges=RANGES
 allowed_advance_results=(0,)
 excluded_admission=(0x7030c5,0x7032bf,0x70333d,0x70347d,0x7034d6,0x703506,0x7035c0,0x7035ef,0x703601,0x703623,0x703649,0x70371e,0x703748,0x7039df,0x703a23,0x703b7a,0x6d7931,0x6d8563,0x70522a,0x705252,0x705256)
 def __init__(self,exe):
  super().__init__(exe);self.inspection=verify(exe.read_bytes());self.phase=None;self.returns={0:0,3:0,7:0};self.next_calls=0;self.decision_stores=0
  self.entries={hex(a):0 for a in self.admission_ranges};self.kind_returns[1]=0
  self.gate_return_to=None;self.retry_gate_returns={0:0,1:0}
  self.supplied_retry_padding=0
  self.admission_caller_returns={};self.zero_head_speed_calls=0;self.actor_byte_checks=0
  for off,target in DISPATCH[0x7addf8].items():self.put(VT+off,target)
  self.put(VT+0x48,0x5d4e40);self.put(VT+0x4b8,0x705160)
  self.hooks.pop(0x6d7910,None)
  self.callers={hex(a):0 for a in (0x4a34eb,0x4a40e4,0x4a1c99,0x4a35f9,0x4a416f,0x4a4513,0x4a45a5)}
 def after_actor_sample(self):pass
 def event(self,*v):
  if v==('g','R'):
   super().event('a','s',self.get(UNIT+0x57a,'B'));self.actor_byte_checks+=1;self.after_actor_sample()
  super().event(*v)
 def cell_id(self,p):
  if not p:return -1
  if p==FALLBACK:return 81
  assert CELLS<=p<CELLS+81*0x200 and (p-CELLS)%0x200==0,hex(p)
  return (p-CELLS)//0x200
 def setup_gate(self,h,houses,objects,updates):
  super().setup_gate(h,houses,objects,updates)
  self.put(UNIT+0x14,5,'B');self.put(UNIT+0x1b0,0);self.put(UNIT+0x1b8,0);self.put(UNIT+0x98,2);self.put(UNIT+0xa0,7)
  self.u.mem_write(UNIT+0x118,bytes(8));self.put(UNIT+0x588,0);self.put(UNIT+0xcc,0);self.put(UNIT+0xd0,0);self.put(UNIT+0x10c,0)
  self.put(TYPE+0xb94,-1);self.put(TYPE+0x704,0);self.put(TYPE+0x74c,0);self.put(TYPE+0xaf3,self.crusher,'B')
  self.put(0x8661d8,0);self.put(0xa40774,1)
  self.u.mem_write(0x851a70,struct.pack('<16h',0,-1,1,-1,1,0,1,1,0,1,-1,1,-1,0,-1,-1))
  self.put(FALLBACK+0x116,-1,'h')
  for p in OBJECTS[1:]:
   self.put(p+0x14,1,'B');self.put(p+0x494,0);self.put(p+0x1b0,0);self.put(p+0x1b8,0);self.put(p+0xcc,0);self.put(p+0xd0,0)
  for t,row in zip(TYPES[1:],objects):
   self.u.mem_write(t,bytes(0x2000));self.put(t+0x1351,row[3],'B')
  self.extra_inputs=[*[(p,n,bytes(self.u.mem_read(p,n))) for p,n in self.admission_ranges.items() if p not in OLD],
   *[(vt+off,4,bytes(self.u.mem_read(vt+off,4))) for vt,row in DISPATCH.items() for off in row],
   (0x851a70,32,bytes(self.u.mem_read(0x851a70,32))),(0x8661d8,4,bytes(self.u.mem_read(0x8661d8,4))),(0xa40774,4,bytes(self.u.mem_read(0xa40774,4)))]
 def observe(self,u,a,n,ctx):
  if not self.active or a==STOP:return
  if a in (0x4a3c2b,0x4a44fe):
   # Uninitialized timer padding is an explicit supplied child-entry word.
   self.put(u.reg_read(UC_X86_REG_ESP)+0x54,7);self.supplied_retry_padding+=1
  if a==self.gate_return_to:
   if a!=0x4a3423:
    r=u.reg_read(UC_X86_REG_EAX)&255;assert r in (0,1);self.retry_gate_returns[r]+=1;self.event('g','r',r)
   self.gate_return_to=None
  if a==0x55acd0:
   assert self.gate_return_to is None;self.gate_return_to=self.get(u.reg_read(UC_X86_REG_ESP))
  if self.phase and a==self.return_to:
   if self.phase=='admit':
    r=u.reg_read(UC_X86_REG_EAX);assert r in self.returns,r;self.returns[r]+=1;self.event('a','r',r)
    if a==0x4a1c9f:assert r in self.allowed_advance_results,'Nonzero Advance switch admission is outside this proof'
    counts=self.admission_caller_returns.setdefault(hex(a),dict.fromkeys(self.returns,0));counts[r]+=1
   self.phase=None
  if a in (0x703040,0x705160):
   assert self.phase is None;self.phase='admit' if a==0x703040 else 'next';self.return_to=self.get(u.reg_read(UC_X86_REG_ESP))
   if self.phase=='admit':self.event('a','U',self.cell_id(self.arg(0)),self.arg(1),struct.unpack('<i',struct.pack('<I',self.arg(2)))[0])
   else:assert self.arg(1)==1;self.event('a','N',*struct.unpack('<hh',u.mem_read(self.arg(0),4)));self.next_calls+=1
  if hex(a) in self.callers:self.callers[hex(a)]+=1
  if a==0x4c2df0 and self.get(u.reg_read(UC_X86_REG_ESP))==0x4a4719:
   assert (self.arg(0),self.arg(1))==(0,0);self.zero_head_speed_calls+=1
  if self.phase:
   assert a not in self.hooks,('Service inside admitted original child',hex(a))
   assert any(lo<=a and a+n<=lo+size for lo,size in self.admission_ranges.items()),f'Uninspected admitted child {a:#x}/{n}'
   assert a not in self.excluded_admission,hex(a)
   self.instructions.add(a)
   if a in self.admission_ranges:self.entries[hex(a)]+=1
   if a==0x548070:self.event('W',*struct.unpack('<hh',u.mem_read(self.arg(0),4)))
   return
  if any(lo<=a and a+n<=lo+size for lo,size in self.admission_ranges.items()) and not any(lo<=a and a+n<=lo+size for lo,size in OLD.items()):
   self.instructions.add(a)
   if a in self.admission_ranges:self.entries[hex(a)]+=1
   return
  if u.reg_read(UC_X86_REG_ECX)==UNIT and a in (0x594770,0x70a2d0,0x70a2d5):
   self.instructions.add(a)
   if a in self.admission_ranges:self.entries[hex(a)]+=1
   return
  super().observe(u,a,n,ctx)
 def store(self,u,access,a,n,v,ctx):
  if self.active:
   ip=u.reg_read(UC_X86_REG_EIP)
   if self.phase and a==FALLBACK+0x24 and ip==0x54809f:self.event('a','F',*struct.unpack('<hh',struct.pack('<I',v&0xffffffff)))
   if 0x4a2670<=ip<0x4a4725:
    if UNIT+0x4d0<=a<UNIT+0x53c or a in (UNIT+0x57a,UNIT+0x57b):self.event('A',a-UNIT,v&0xffffffff);self.decision_stores+=1
    if a-LOCO in (0x40,0x44,0x48,0x58,0x5c,0x63):self.event('a','L',a-LOCO,v&0xffffffff);self.decision_stores+=1
  super().store(u,access,a,n,v,ctx)
 def run(self,*args):
  self.crusher=args[-1];result=super().run(*args[:-1]);assert self.phase is None and self.gate_return_to is None
  assert all(bytes(self.u.mem_read(p,n))==old for p,n,old in self.extra_inputs)
  return result
