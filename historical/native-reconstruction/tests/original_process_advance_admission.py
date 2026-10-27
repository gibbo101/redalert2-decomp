# SPDX-License-Identifier: GPL-3.0-or-later
"""Actual complete Process root, retaining Advance's result7 continuation."""
from collections import Counter
from original_moving_resident_process import MovingResidentProcessOracle
from original_movement import UNIT,LOCO,STOP
from verify_ground_drive_stores import STORE_SITES,FIELDS
from verify_process_advance_admission import verify,CALLERS
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_EIP,UC_X86_REG_ESP

class ProcessAdvanceAdmissionOracle(MovingResidentProcessOracle):
 allowed_advance_results=(0,2,7)
 def __init__(self,exe):
  super().__init__(exe);self.process_inspection=verify(exe.read_bytes())
  self.actual_roots=Counter();self.advance_callers=Counter();self.drive_stores=Counter()
  self.branch_returns=Counter();self.result7_callers=Counter();self.measurements=[]
  self.default_continuations=0;self.default_index_stores=0;self.pending_default=None;self.advance_caller=None
 def observe(self,u,a,n,ctx):
  if getattr(self,'active',False) and a!=STOP:
   if a==0x4a05f0:self.actual_roots[hex(a)]+=1
   if a==0x4a1000:
    caller=self.get(u.reg_read(UC_X86_REG_ESP));assert caller in CALLERS,hex(caller)
    self.advance_caller=caller;self.advance_callers[hex(caller)]+=1
   if a in CALLERS:
    assert self.pending_default is None and self.advance_caller==a
    self.advance_caller=None
   if a in (0x7037fb,0x703879):self.measurements.append([hex(a),u.reg_read(UC_X86_REG_EAX)])
   if a==0x4a1c9f:
    code=u.reg_read(UC_X86_REG_EAX);assert code in self.allowed_advance_results
    self.branch_returns[code]+=1
    if code==7:
     assert self.pending_default is None and self.advance_caller in CALLERS
     self.result7_callers[hex(self.advance_caller)]+=1
     self.pending_default=(self.get(LOCO+0x5c),bytes(u.mem_read(LOCO+0x40,12)),self.get(LOCO+0x58),bytes(u.mem_read(UNIT+0x4d0,96)))
   if self.pending_default and a==0x4a1caf:raise AssertionError('Result7 entered rejected-switch case')
   if self.pending_default and a==0x4a1f8d:
    assert (self.get(LOCO+0x5c),bytes(u.mem_read(LOCO+0x40,12)),self.get(LOCO+0x58),bytes(u.mem_read(UNIT+0x4d0,96)))==self.pending_default
    self.default_continuations+=1
  super().observe(u,a,n,ctx)
 def store(self,u,access,a,n,v,ctx):
  super().store(u,access,a,n,v,ctx)
  if not getattr(self,'active',False) or a-LOCO not in FIELDS:return
  ip=u.reg_read(UC_X86_REG_EIP)
  if not 0x4a1000<=ip<0x4a2649:return
  assert STORE_SITES.get(ip)==(a-LOCO,n),(hex(ip),hex(a),n)
  self.drive_stores[hex(ip)]+=1;self.event('d',a-LOCO,v&((1<<(8*n))-1))
  if self.pending_default and ip==0x4a1f98:
   assert v==self.pending_default[0]+1
   self.default_index_stores+=1;self.pending_default=None
 def run(self,*args):
  result=super().run(*args)
  assert self.pending_default is None and self.advance_caller is None
  assert self.actual_roots['0x4a05f0']==self.roots
  return result
