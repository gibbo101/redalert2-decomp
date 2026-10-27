# SPDX-License-Identifier: GPL-3.0-or-later
"""Actual moving Unit admission through bounded complete Process wait callers."""
import struct
from original_ground_drive_resident_process import GroundDriveResidentProcessOracle
from original_ground_drive_admission_process import GroundDriveAdmissionProcessOracle
from original_ground_drive_gate_process import ARENA,OBJECTS,TYPES
from original_movement import UNIT,LOCO,RULES,STOP
from verify_ground_drive_admission_process import RANGES as BASE
from verify_moving_unit_admission import EXTRA,TABLES,verify as motion_verify
from unicorn.x86_const import UC_X86_REG_ESP,UC_X86_REG_EIP,UC_X86_REG_EAX

class MovingResidentProcessOracle(GroundDriveResidentProcessOracle):
 admission_ranges={**BASE,**EXTRA}
 allowed_advance_results=(0,2)
 excluded_admission=tuple(a for a in GroundDriveAdmissionProcessOracle.excluded_admission if a not in (0x70371e,0x703748))
 preparation_callers={**GroundDriveResidentProcessOracle.preparation_callers,0x4a41df:1}
 def __init__(self,exe):
  super().__init__(exe);self.motion_inspection=motion_verify(exe.read_bytes());self.returns[2]=0
  self.pathfinderOptions=[];self.preparationArguments=[];self.waitStores=0;self.defaultPathfinderCalls=0
  self.moving_Process_callers={};self.waitBranches={hex(a):0 for a in (0x4a365c,0x4a3689,0x4a36b5,0x4a36e6,0x4a39c8,0x4a3a98,0x4a3c75,0x4a41d4)}
 def pathfinder(self):
  if self.get(self.u.reg_read(UC_X86_REG_ESP))==0x4a3a0a:
   option=self.arg(2);assert option in (1,2),option
   self.pathfinderOptions.append(option);self.event('b',option)
  else:self.defaultPathfinderCalls+=1
  return super().pathfinder()
 def after_actor_sample(self):
  self.event('w',*struct.unpack('<3i',self.u.mem_read(UNIT+0x558,12)))
 def extra_actor_writes(self):return ((0x558,12),)
 def setup_gate(self,h,houses,objects,updates):
  super().setup_gate(h,houses,objects,updates)
  self.put(UNIT+0x2e8,-1) # Explicit supplied settled Facing for signed clocks.
  for i,m in enumerate(self.motion,1):
   p=OBJECTS[i];t=TYPES[i];l=ARENA+0x8000+i*0x100
   assert objects[i-1][0]==1
   self.u.mem_write(p+0x88,struct.pack('<3i',*m[:3]));self.u.mem_write(l+0x30,struct.pack('<6i',*m[3:9]))
   self.u.mem_write(p+0x2e0,struct.pack('<IIiiii',m[9],m[10],m[11],7,m[12],m[13]))
   self.put(p+0x5a0,m[14],'B');self.put(p+0x4d0,m[15]);self.put(l+0x54,m[16]);self.put(l+0x58,m[17]);self.put(l+0x5c,m[18],'B')
  flag,start,padding,duration,ruleDuration,temporary,retryStart,retryPad,retryRemaining=self.waitInputs
  self.put(UNIT+0x5a1,flag,'B');self.u.mem_write(UNIT+0x558,struct.pack('<3i',start,padding,duration))
  self.u.mem_write(UNIT+0x530,struct.pack('<3i',retryStart,retryPad,retryRemaining));self.put(RULES+0x13d0,ruleDuration)
  self.extra_inputs.extend((p,n,bytes(self.u.mem_read(p,n))) for p,n in [*TABLES.items(),(0x7a04cc+0xa4,4)])
  self.stationary_inputs=[(a,n,bytes(self.u.mem_read(a,n))) for i in range(1,5)
   for a,n in ((OBJECTS[i],0x1000),(TYPES[i],0x2000),(ARENA+0x8000+i*0x100,0x100))]
 def observe(self,u,a,n,ctx):
  if not self.active or a==STOP:return
  assert a!=0x4a3ab5,'Moving wait sound branch remains unsupported'
  if hex(a) in self.waitBranches:self.waitBranches[hex(a)]+=1
  if self.phase=='admit' and a==self.return_to and u.reg_read(UC_X86_REG_EAX)==2:
   caller=hex(self.prepare_stack[-1]) if self.prepare_stack else 'Advance'
   self.moving_Process_callers[caller]=self.moving_Process_callers.get(caller,0)+1
  if a==0x4a367f:self.put(u.reg_read(UC_X86_REG_ESP)+0x54,self.waitInputs[5])
  if a==0x4a2670:
   caller=self.get(u.reg_read(UC_X86_REG_ESP));third=self.arg(2)
   assert third==(1 if caller==0x4a41df else 0),(hex(caller),third)
   self.preparationArguments.append((hex(caller),self.arg(1),third))
  super().observe(u,a,n,ctx)
 def store(self,u,access,a,n,v,ctx):
  if self.active and a in (UNIT+0x558,UNIT+0x55c,UNIT+0x560):
   assert n==4 and u.reg_read(UC_X86_REG_EIP)=={UNIT+0x558:0x4a367d,UNIT+0x55c:0x4a3683,UNIT+0x560:0x4a3686}[a]
   self.event('A',a-UNIT,v&0xffffffff);self.waitStores+=1;return
  super().store(u,access,a,n,v,ctx)
 def run(self,*args):
  args,self.motion,self.waitInputs=args[:-2],args[-2],args[-1]
  self.preparationArguments=[];result=super().run(*args)
  return result
