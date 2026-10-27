# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete unchanged Infantry roots on the shared admission guest/world."""
import struct
from original_unit_admission import UnitAdmissionOracle,OBJECTS,TYPES,REGS,CELLS
from original_presentation import STOP
from verify_infantry_admission import verify,RANGES,EXTRA
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EDX
class InfantryAdmissionOracle(UnitAdmissionOracle):
 def __init__(self,exe):
  super().__init__(exe);self.inspection=verify(exe.read_bytes());self.infantry_calls=0;self.speed_loads=0
 def prepare_motion(self):
  p=OBJECTS[0];o=self.options;self.put(p,0x7a3540);self.put(p+0x5a8,TYPES[0]);self.put(TYPES[0]+0x5a4,o[2]);self.put(0xa40774,o[3])
  self.u.mem_write(p+0x32d,bytes([o[0]]));self.u.mem_write(p+0x370,bytes([o[1]]))
  for i,r in enumerate(REGS):self.put(r+0x24,(o[4+2*i]&65535)|((o[5+2*i]&65535)<<16))
  for i,c in enumerate(CELLS):self.put(c+0x44,o[10+i])
  # The existing fixture supplies one value per land; all nine columns remain
  # explicit original inputs, including the retained ninth column.
  for land,bits in enumerate(self.speeds):
   for column in range(9):self.put(0x850ea0+4*(land*9+column),bits)
 def extra_inputs(self):return [*EXTRA.items(),(0x7a3540+0x194,8)]
 def checked_call(self,root,*args,**kwargs):
  return super().checked_call(0x503190 if root==0x703040 else root,*args,**kwargs)
 def code(self,u,a,n,ctx):
  if not self.active or a==STOP:return
  if 0x503190<=a<0x503a3b:
   assert not (0x50334d<=a<0x50337c or 0x50338a<=a<0x503425 or 0x50345b<=a<0x5038cb or 0x5038d7<=a<0x503947 or 0x5039fb<=a<0x503a1e),('Unjoined Infantry child',hex(a))
   self.instructions.add(a)
   if a==0x503190:
    self.infantry_calls+=1;assert u.reg_read(UC_X86_REG_ECX)==OBJECTS[0]
   if a==0x503974:
    index=u.reg_read(UC_X86_REG_EDX);assert index<108
    bits=self.word(0x850ea0+4*index);self.event('S',index,bits if bits<2**31 else bits-2**32);self.speed_loads+=1
   return
  super().code(u,a,n,ctx)
 def run_infantry(self,options,parsed):
  self.options=options;self.speeds=parsed[2];return self.run(*parsed)
