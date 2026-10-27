# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete unmodified vehicle override plus inherited Foot Team-subject roots."""
from original_team_foot_expiration import TeamFootExpirationOracle
from original_mission_typed_tag_expiration import ACTOR,STUBS,POINTERS
from verify_team_vehicle_expiration import verify,RANGES
from original_presentation import STACK
from unicorn.x86_const import UC_X86_REG_EIP
class TeamVehicleExpirationOracle(TeamFootExpirationOracle):
 def __init__(self,exe):
  self.vehicle_inspection=verify(exe.read_bytes());super().__init__(exe)
 def checked_call(self,address,args=(),ecx=0,edx=0,**kw):
  assert address==0x4c8460
  field=0x5b4 if self.f['vehicle'] else 0x5b0
  if not self.vehicle_seeded:
   self.put(ACTOR+field,POINTERS[self.f['derived']]);self.put(ACTOR+0x5ac,POINTERS[self.f['link']]);self.vehicle_seeded=True
  # The derived wrapper adds two saved registers, two arguments and a return
  # address before Foot's existing scratch slot. Preserve supplied scratch
  # semantics at its actual deeper caller-stack location.
  self.put(STACK-68,self.f['scratch'])
  kw['inputs']=[*kw['inputs'],*RANGES.items()]
  return super().checked_call(0x41adb0 if self.f['vehicle'] else 0x707e90,args,ecx,edx,**kw)
 def store(self,u,access,p,n,value,unused):
  if self.active and p in (ACTOR+0x5b0,ACTOR+0x5b4,ACTOR+0x5ac):
   pc=u.reg_read(UC_X86_REG_EIP);assert n==4 and value==0 and any(a<=pc<a+size for a,size in RANGES.items())
   self.stores[hex(pc)]+=1;self.trace.extend(('W','4',str(p-ACTOR),'0'));self.expected[p-ACTOR:p-ACTOR+4]=bytes(4);return
  return super().store(u,access,p,n,value,unused)
 def code(self,u,a,n,unused):
  if self.active and any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()):
   if a in RANGES:self.counts[hex(a)]+=1
   return
  super().code(u,a,n,unused)
  if self.active and a==STUBS+5*16 and self.f['mutation']:
   p=POINTERS[1 if self.f['mutation']==1 else 9];self.put(ACTOR+(0x5b4 if self.f['vehicle'] else 0x5b0),p);self.put(ACTOR+0x5ac,p)
 def run(self,f):
  self.vehicle_seeded=False;result=super().run(f)
  result.extend(('VEHICLE',str(self.identity(self.word(ACTOR+(0x5b4 if f['vehicle'] else 0x5b0)))),str(self.identity(self.word(ACTOR+0x5ac)))))
  return result
