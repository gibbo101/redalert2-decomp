# SPDX-License-Identifier: GPL-3.0-or-later
"""Execute actual471760 under complete Cell color/terrain/projection parents."""
from original_cell_radar_color import CellRadarColorOracle,TYPES
from original_presentation import STOP
from verify_cell_resident_search import HELPER
from unicorn.x86_const import UC_X86_REG_ECX,UC_X86_REG_ESP
RESIDENT=TYPES+0xb000;VTABLE=TYPES+0xb100;KIND=0x594770
class RadarResidentColorOracle(CellRadarColorOracle):
 def setup(self):
  super().setup();self.put(VTABLE+0x2c,KIND);self.put(RESIDENT,VTABLE);self.put(RESIDENT+0x30,0)
  for cell in self.ids:
   self.put(cell+0xe4,RESIDENT if self.profile[0] else 0);self.put(cell+0xe8,0)
  self.u.mem_write(0xa40958,b'\1');self.expected=bytearray(self.u.mem_read(__import__('original_radar_projection').BASE,__import__('original_radar_projection').SIZE));self.typeExpected=bytearray(self.u.mem_read(TYPES,0x10000))
 def code(self,u,a,n,ctx):
  if self.active and a!=STOP:
   if a==HELPER[0]:
    sp=u.reg_read(UC_X86_REG_ESP);assert u.reg_read(UC_X86_REG_ECX) in self.ids and [self.word(sp+4),self.word(sp+8)]==[36,0]
    self.emit('D',36,0);self.counts['actual_resident']+=1
   if HELPER[0]<=a and a+n<=HELPER[1]:return
   if a==KIND:
    assert u.reg_read(UC_X86_REG_ECX)==RESIDENT;self.counts['supplied_kind']+=1;self.ret(0,36);return
  super().code(u,a,n,ctx)
 def checked_call(self,*args,**kwargs):
  kwargs['inputs']=[*kwargs.get('inputs',[]),(HELPER[0],HELPER[1]-HELPER[0]),(0xa40958,1)]
  # Parent setup runs inside checked_call; global gate must already be stable
  # before its input snapshot is taken by PresentationOracle.
  self.u.mem_write(0xa40958,b'\1');super().checked_call(*args,**kwargs)
