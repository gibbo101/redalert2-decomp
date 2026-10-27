# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete original Advance with actual admission; no Process execution."""
from collections import Counter
from original_moving_resident_process import MovingResidentProcessOracle
from original_movement import UNIT,LOCO,STOP,STACK
from original_ground_drive_gate_process import ARENA,SIZE
from original_map_floor_height import FALLBACK,PLANES
from verify_ground_drive_stores import STORE_SITES,FIELDS
from verify_advance_admission import verify
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_EIP

class AdvanceAdmissionOracle(MovingResidentProcessOracle):
 allowed_advance_results=(0,2,7)
 def __init__(self,exe):
  super().__init__(exe);self.advance_inspection=verify(exe.read_bytes())
  self.actual_roots=Counter();self.drive_stores=Counter();self.branch_returns=Counter()
  self.default_continuations=0;self.default_index_stores=0;self.pending_default=None;self.suppress=0
 def call(self,a,args=(),this=LOCO,budget=100000):
  # Reuse authored setup and complete state projection only. The inherited
  # fixture's disc Process request is replaced by the *root* Advance request,
  # translated by the exact profile to actual 4A1000. No guest code is patched.
  if getattr(self,'active',False):
   assert a==0x4a01c0
   old_actor=bytes(self.u.mem_read(UNIT,0x1000));old_drive=bytes(self.u.mem_read(LOCO,0x100))
   old_arena=bytes(self.u.mem_read(ARENA,SIZE))
   value=super().call(0x4a0bd0,[self.suppress],LOCO,budget)
   assert value&255==0 and self.pending_default is None
   for p,n,old,mutable in ((UNIT,0x1000,old_actor,((0x74,1),(0x88,12),(0x2e0,24),(0x468,8),(0x5a0,2))),
    (LOCO,0x100,old_drive,((0x40,16),(0x58,8),(0x63,1)))):
    after=bytearray(self.u.mem_read(p,n))
    for off,size in mutable:after[off:off+size]=old[off:off+size]
    assert bytes(after)==old,('Advance changed protected record',hex(p))
   assert bytes(self.u.mem_read(ARENA,SIZE))==old_arena,'Advance changed supplied resident/type/House arena'
   return value
  return super().call(a,args,this,budget)
 def observe(self,u,a,n,ctx):
  if getattr(self,'active',False) and a!=STOP:
   assert not 0x4a05f0<=a<0x4a0bbb and not 0x4a2670<=a<0x4a4725,'Process/preparation entered Advance-only proof'
   if a==0x4a1000:self.actual_roots[hex(a)]+=1
   if a==0x4a1c9f:
    code=u.reg_read(UC_X86_REG_EAX);assert code in self.allowed_advance_results
    self.branch_returns[code]+=1
    if code==7:
     assert self.pending_default is None
     self.pending_default=(self.get(LOCO+0x5c),bytes(u.mem_read(LOCO+0x40,12)),self.get(LOCO+0x58),bytes(u.mem_read(UNIT+0x4d0,96)))
   if self.pending_default and a==0x4a1caf:raise AssertionError('Result7 entered rejected-switch case')
   if self.pending_default and a==0x4a1f8d:
    index,head,track,queue=self.pending_default
    assert (self.get(LOCO+0x5c),bytes(u.mem_read(LOCO+0x40,12)),self.get(LOCO+0x58),bytes(u.mem_read(UNIT+0x4d0,96)))==(index,head,track,queue)
    self.default_continuations+=1
  super().observe(u,a,n,ctx)
 def store(self,u,access,a,n,v,ctx):
  if getattr(self,'active',False):
   allowed=((STACK-0x2000,STACK+8),(UNIT+0x74,UNIT+0x75),(UNIT+0x88,UNIT+0x94),
    (UNIT+0x2e0,UNIT+0x2f8),(UNIT+0x468,UNIT+0x470),(UNIT+0x5a0,UNIT+0x5a2),
    (LOCO+0x40,LOCO+0x50),(LOCO+0x58,LOCO+0x60),(LOCO+0x63,LOCO+0x64),
    (0x850bb8,0x850bb9),(0x850ba8,0x850bb0),(0x850bd0,0x850bd8),(PLANES,PLANES+800),(FALLBACK+0x24,FALLBACK+0x28))
   assert any(lo<=a and a+n<=hi for lo,hi in allowed),('Non-Advance write',hex(a),n)
  super().store(u,access,a,n,v,ctx)
  if not getattr(self,'active',False) or a-LOCO not in FIELDS:return
  ip=u.reg_read(UC_X86_REG_EIP);assert STORE_SITES.get(ip)==(a-LOCO,n),(hex(ip),hex(a),n)
  self.drive_stores[hex(ip)]+=1;self.event('L',a-LOCO,v&((1<<(8*n))-1))
  if self.pending_default and ip==0x4a1f98:
   assert v==self.pending_default[0]+1
   self.default_index_stores+=1;self.pending_default=None
 def run(self,*args):
  self.suppress=args[0][7]
  # Legacy parser/setup permits only suppress0; the new parser restores it.
  result=super().run(*args)
  assert self.actual_roots['0x4a1000']==self.roots
  assert not self.next_calls and not self.preparationArguments and not self.defaultPathfinderCalls
  return result
