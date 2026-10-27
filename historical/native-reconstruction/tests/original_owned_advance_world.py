# SPDX-License-Identifier: GPL-3.0-or-later
"""Actual result7 on distinct Process records and real shared mutable membership.

The original root call and all code/arena/write guards are inherited unchanged.
Only the explicitly supported admission policy differs from the legacy fixture.
"""
import struct
from collections import Counter
from original_owned_unit_processes import AttachedProcesses,OwnedUnitProcessesOracle,ACTORS,DRIVES
from original_map_preparation import FALLBACK
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ESP,UC_X86_REG_EIP

class AttachedAdvanceProcesses(AttachedProcesses):
 allowed_advance_results=(0,2,7)
 def __init__(self,owner):
  self.advance_targets=[];self.pending_target=None;self.pending_default=None
  self.default_continuations=Counter();self.default_stores=Counter();self.result7_callers=Counter()
  self.advance_caller=None;self.bearings=[];self.distances=[]
  super().__init__(owner)
 def observe(self,u,a,n,ctx):
  if self.active:
   if a==0x4a1000:
    self.advance_caller=self.get(u.reg_read(UC_X86_REG_ESP))
    assert self.advance_caller in (0x4a066b,0x4a0758,0x4a0ba3)
   if a==0x703040 and self.get(u.reg_read(UC_X86_REG_ESP))==0x4a1c9f:
    target=self.arg(0);point=struct.unpack('<2h',u.mem_read(target+0x24,4))
    members=[];p=self.get(target+0xe4)
    while p:
     assert p in ACTORS and p not in [ACTORS[i] for i in members]
     members.append(ACTORS.index(p));p=self.get(p+0x30)
    self.pending_target={'actor':self.actor,'target':point,'fallback':target==FALLBACK,
      'members':members,'member_locations':[list(struct.unpack('<3i',u.mem_read(ACTORS[i]+0x88,12))) for i in members]}
   if a==0x7037fb:self.bearings.append([self.actor,u.reg_read(UC_X86_REG_EAX)&65535])
   if a==0x703879:self.distances.append([self.actor,u.reg_read(UC_X86_REG_EAX)])
   if a==0x4a1c9f:
    code=u.reg_read(UC_X86_REG_EAX);assert self.pending_target is not None
    self.advance_targets.append({**self.pending_target,'result':code,'caller':hex(self.advance_caller)})
    self.pending_target=None
    if code==7:
     assert self.pending_default is None
     drive=DRIVES[self.actor]
     self.pending_default=(self.actor,self.get(drive+0x5c),bytes(u.mem_read(drive+0x40,12)),
       self.get(drive+0x58),bytes(u.mem_read(ACTORS[self.actor]+0x4d0,96)))
     self.result7_callers[(self.actor,self.advance_caller)]+=1
   if self.pending_default:
    assert a!=0x4a1caf,'Result7 entered rejected-switch case'
    if a==0x4a1f8d:
     id,index,head,track,queue=self.pending_default;drive=DRIVES[id]
     assert (self.get(drive+0x5c),bytes(u.mem_read(drive+0x40,12)),self.get(drive+0x58),
       bytes(u.mem_read(ACTORS[id]+0x4d0,96)))==(index,head,track,queue)
     self.default_continuations[id]+=1
  return super().observe(u,a,n,ctx)
 def store(self,u,access,a,n,v,ctx):
  super().store(u,access,a,n,v,ctx)
  if self.active and self.pending_default and u.reg_read(UC_X86_REG_EIP)==0x4a1f98:
   id,index,*_=self.pending_default
   assert a==DRIVES[id]+0x5c and n==4 and v==index+1
   self.default_stores[id]+=1;self.pending_default=None
 def advance_actor(self,id,tick):
  result=super().advance_actor(id,tick)
  assert self.pending_default is None and self.pending_target is None
  return result

class OwnedAdvanceWorldOracle(OwnedUnitProcessesOracle):
 movement_type=AttachedAdvanceProcesses
