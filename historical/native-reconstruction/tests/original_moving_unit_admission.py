# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete unchanged admission, including moving allied Unit decisions."""
import struct
from original_unit_admission import UnitAdmissionOracle,OBJECTS,LOCOS,RANGES as OLD,STOP
from verify_moving_unit_admission import verify,EXTRA,TABLES
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP
class MovingUnitAdmissionOracle(UnitAdmissionOracle):
 def __init__(self,exe):
  super().__init__(exe);self.moving_inspection=verify(exe.read_bytes());self.motion=None
  self.entries.update({hex(a):0 for a in EXTRA});self.moving_entries={hex(a):0 for a in (0x70371e,0x703748,0x703808,0x703895,0x7038d6,0x7038af)}
  self.distance_returns=[];self.bearing_returns=[];self.switch_returns={0:0,1:0}
 def prepare_motion(self):
  assert self.motion is not None
  for p,l,m in zip(OBJECTS,LOCOS,self.motion):
   self.u.mem_write(p+0x88,struct.pack('<3i',*m[:3]))
   self.u.mem_write(l+0x30,struct.pack('<6i',*m[3:9]))
   self.u.mem_write(p+0x2e0,struct.pack('<IIiiii',m[9],m[10],m[11],7,m[12],m[13]))
   self.u.mem_write(p+0x5a0,bytes([m[14]]));self.put(p+0x4d0,m[15])
   self.put(l+0x54,m[16]);self.put(l+0x58,m[17]);self.u.mem_write(l+0x5c,bytes([m[18]]))
 def extra_inputs(self):
  return [*EXTRA.items(),*TABLES.items(),(0x7addf8+0x48,4),(0x7a04cc+0xa4,4)]
 def code(self,u,a,n,ctx):
  if not self.active or a==STOP:return
  if hex(a) in self.moving_entries:self.moving_entries[hex(a)]+=1
  # These two entries were deliberately refused by the stationary ancestor.
  if a in (0x70371e,0x703748):self.instructions.add(a);return
  if any(lo<=a and a+n<=lo+size for lo,size in EXTRA.items()):
   self.instructions.add(a)
   if a in EXTRA:self.entries[hex(a)]+=1
   ecx=u.reg_read(UC_X86_REG_ECX);sp=u.reg_read(UC_X86_REG_ESP)
   if a==0x5d4e40:self.event('Q',OBJECTS.index(ecx))
   elif a==0x4a4ac0:self.pending_switch=LOCOS.index(self.word(sp+4));self.event('Y',self.pending_switch)
   return
  if a in (0x70375c,0x703777):
   actor=self.current_mover if a==0x70375c else self.current_resident
   heading=int.from_bytes(u.mem_read(u.reg_read(UC_X86_REG_EAX),2),'little');self.event('J',actor,heading)
  elif a==0x70374c:
   from unicorn.x86_const import UC_X86_REG_ESI
   self.current_resident=OBJECTS.index(u.reg_read(UC_X86_REG_ESI))
  elif a==0x7037fb:
   bearing=u.reg_read(UC_X86_REG_EAX)&65535;self.event('B',0,bearing);self.bearing_returns.append(bearing)
  elif a==0x703879:
   distance=u.reg_read(UC_X86_REG_EAX);distance=distance if distance<0x80000000 else distance-0x100000000
   self.event('Z',0,distance);self.distance_returns.append(distance)
  elif a==0x7038d2:
   value=u.reg_read(UC_X86_REG_EAX)&255;self.event('y',self.pending_switch,value);self.switch_returns[value]+=1
  return super().code(u,a,n,ctx)
 def checked_call(self,root,args=(),ecx=0,edx=0,**kw):
  if root==0x703040:self.current_mover=OBJECTS.index(ecx)
  return super().checked_call(root,args,ecx,edx,**kw)
