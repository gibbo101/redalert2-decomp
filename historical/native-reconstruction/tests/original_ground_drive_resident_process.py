# SPDX-License-Identifier: GPL-3.0-or-later
"""Actual stationary Unit admission and result-6 retry in complete Process."""
from original_ground_drive_admission_process import GroundDriveAdmissionProcessOracle
from original_ground_drive_gate_process import OBJECTS,TYPES,ARENA
from original_movement import UNIT,LOCO,STOP
from verify_ground_drive_resident_process import verify
from unicorn.x86_const import UC_X86_REG_ESP,UC_X86_REG_EAX

class GroundDriveResidentProcessOracle(GroundDriveAdmissionProcessOracle):
 preparation_callers={0x4a0739:1,0x4a0b75:1,0x4a4518:0}
 def __init__(self,exe):
  super().__init__(exe);self.inspection=verify(exe.read_bytes());self.returns[6]=0
  self.preparation_flags={};self.resident_loads={'first':0,'second':0};self.stationary_checks=0
  self.resident_paths={hex(a):0 for a in (0x4a371a,0x4a420f)}
  self.prepare_stack=[];self.resident_Process_callers={}
  self.nonzero_head_first_retries=0
 def setup_gate(self,h,houses,objects,updates):
  super().setup_gate(h,houses,objects,updates)
  self.stationary_inputs=[]
  for i,row in enumerate(objects,1):
   if row[0]!=1:continue
   p=OBJECTS[i];t=TYPES[i];loco=ARENA+0x8000+i*0x100
   self.put(p,0x7addf8);self.put(p+0x5ac,t);self.put(p+0x564,loco)
   self.u.mem_write(p+0x118,bytes(8));self.u.mem_write(p+0x2e0,bytes(24))
   self.put(p+0x14,self.resident_flags,'B');self.put(p+0x10c,0);self.put(p+0x588,0)
   self.put(t+0xb94,-1);self.put(t+0x5a4,1)
   self.put(loco,0x7a04cc);self.u.mem_write(loco+0x30,bytes(24));self.put(loco+8,p)
   self.stationary_inputs.extend((a,n,bytes(self.u.mem_read(a,n))) for a,n in ((p,0x1000),(t,0x2000),(loco,0x100)))
   self.stationary_checks+=1
 def observe(self,u,a,n,ctx):
  if not self.active or a==STOP:return
  if a==0x4a2670:
   caller=self.get(u.reg_read(UC_X86_REG_ESP));flag=self.arg(1)
   assert caller in self.preparation_callers,(hex(caller),flag)
   assert flag==self.preparation_callers[caller],(hex(caller),flag)
   key=f'{caller:#x}:{flag}';self.preparation_flags[key]=self.preparation_flags.get(key,0)+1
   self.prepare_stack.append(caller)
  elif a in self.preparation_callers:
   assert self.prepare_stack.pop()==a
  if self.phase=='admit' and a==self.return_to:
   self.admission_caller_returns.setdefault(hex(a),dict.fromkeys(self.returns,0))
   if u.reg_read(UC_X86_REG_EAX)==6:
    caller=hex(self.prepare_stack[-1]);self.resident_Process_callers[caller]=self.resident_Process_callers.get(caller,0)+1
  if a in (0x4a3732,0x4a422b):
   first=a==0x4a3732;self.put(u.reg_read(UC_X86_REG_ESP)+(0x48 if first else 0x54),self.retry_padding[0 if first else 1])
   self.resident_loads['first' if first else 'second']+=1
  if hex(a) in self.resident_paths:self.resident_paths[hex(a)]+=1
  if a==0x4a371a and bytes(u.mem_read(LOCO+0x40,12))!=bytes(12):self.nonzero_head_first_retries+=1
  assert a not in (0x4a373b,0x4a4234,0x476920),'Scatter/close-enough excluded from flag-1 profile'
  super().observe(u,a,n,ctx)
 def run(self,*args):
  self.retry_padding=args[-3:-1];self.resident_flags=args[-1];result=super().run(*args[:-3])
  assert not self.prepare_stack
  assert all(bytes(self.u.mem_read(a,n))==old for a,n,old in self.stationary_inputs),'Stationary resident changed'
  return result
