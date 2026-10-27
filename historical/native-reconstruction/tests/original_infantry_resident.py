# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete unchanged503190 friendly E1 lists on the existing guarded arena."""
from original_infantry_permission import InfantryPermissionOracle
from original_unit_admission import OBJECTS,TYPES,LOCOS,HOUSES
from original_presentation import STOP
from verify_infantry_resident import RANGES,verify
from unicorn.x86_const import UC_X86_REG_ECX,UC_X86_REG_ESP
class InfantryResidentOracle(InfantryPermissionOracle):
 def __init__(self,exe):
  super().__init__(exe);self.inspection=verify(exe.read_bytes());self.resident_missions=0;self.moving_calls=0;self.ally_calls=0
 def prepare_motion(self):
  super().prepare_motion()
  for i,p in enumerate(OBJECTS):
   self.put(p,0x7a3540);self.put(p+0x5a8,TYPES[i]);self.put(p+0x564,LOCOS[i]+4)
   self.u.mem_write(LOCOS[i]+4,(0x7aead8).to_bytes(4,'little'));self.u.mem_write(LOCOS[i]+0x34,bytes([self.resident_options[i]]))
  for off,v in zip((0xc10,0xc11,0xc14),self.resident_options[5:]):self.u.mem_write(TYPES[0]+off,bytes([v]))
  self.object_kinds=[15]*5
 def extra_inputs(self):
  return [*super().extra_inputs(),*RANGES.items(),(0x7a3540+0x2c,4),(0x7a3540+0x3c,4),(0x7aead8+0x10,4),(0x503a40,31)]
 def code(self,u,a,n,ctx):
  if not self.active or a==STOP:return
  sp=u.reg_read(UC_X86_REG_ESP);ecx=u.reg_read(UC_X86_REG_ECX)
  if 0x50345b<=a<0x5038cb:
   # Every admitted instruction executes unchanged. Reject paths outside scope.
   assert not (0x503465<=a<0x5034a0 or 0x50353c<=a<0x5035db or 0x5035eb<=a<0x503603 or 0x503613<=a<0x50363e or 0x50364e<=a<0x50370f or 0x50371f<=a<0x503735 or 0x503749<=a<0x50380c or 0x50382c<=a<0x5038a3),('Unsupported resident path',hex(a))
   self.instructions.add(a);return
  if any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()):
   self.instructions.add(a)
   if a==0x594770:self.resident_missions+=1;self.event('M',OBJECTS.index(ecx))
   elif a==0x509800:self.event('K',OBJECTS.index(ecx),15)
   elif a==0x4e5580:
    self.ally_calls+=1;resident=self.word(sp+4);self.event('h',HOUSES.index(ecx),HOUSES.index(self.word(resident+0x1b4)))
   elif a==0x71dea0:
    self.moving_calls+=1;i=LOCOS.index(self.word(sp+4)-4);self.event('v',i,self.resident_options[i])
   return
  return super().code(u,a,n,ctx)
 def run_resident(self,options,parsed):
  self.resident_options=options;return self.run_permission(*parsed)
