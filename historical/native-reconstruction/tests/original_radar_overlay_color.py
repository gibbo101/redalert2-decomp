# SPDX-License-Identifier: GPL-3.0-or-later
"""Actual5DD000 under original Cell colors, terrain and projection."""
from original_radar_resident_color import RadarResidentColorOracle
from original_cell_radar_color import TYPES,OVERLAY,ANIMATION
from original_radar_projection import BASE,SIZE
from original_presentation import STOP
from verify_overlay_radar_color import RANGES
from unicorn.x86_const import UC_X86_REG_ECX,UC_X86_REG_ESP
VTABLE=TYPES+0xc000
class RadarOverlayColorOracle(RadarResidentColorOracle):
 def setup(self):
  super().setup();self.put(VTABLE+0x9c,0x5dd150);self.put(OVERLAY,VTABLE);self.put(OVERLAY+0x264,self.currentOverlay);self.put(OVERLAY+0xa4,0 if self.profile[13] else ANIMATION+0x500);self.u.mem_write(OVERLAY+0x27f,b'\0')
  self.typeExpected=bytearray(self.u.mem_read(TYPES,0x10000));self.expected=bytearray(self.u.mem_read(BASE,SIZE))
 def code(self,u,a,n,ctx):
  if self.active and a!=STOP:
   if a==0x5dd000:
    sp=u.reg_read(UC_X86_REG_ESP);assert u.reg_read(UC_X86_REG_ECX)==OVERLAY
    self.emit('O',self.currentOverlay,self.word(sp+8));self.counts['actual_overlay']+=1
   if a==0x5dd150:self.counts['overlay_getter']+=1
   if a in (0x5dd000,0x5dd150) or any(lo<=a and a+n<=lo+size for lo,size in RANGES.items() if lo in (0x5dd000,0x5dd150)):return
  super().code(u,a,n,ctx)
 def checked_call(self,*args,**kwargs):
  kwargs['inputs']=[*kwargs.get('inputs',[]),*RANGES.items()];super().checked_call(*args,**kwargs)
