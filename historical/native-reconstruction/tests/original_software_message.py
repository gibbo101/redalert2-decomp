# SPDX-License-Identifier: GPL-3.0-or-later
"""Unmodified message chain with software display fill on the shared canvas."""
import struct
from original_mission_message import MissionMessageOracle
from original_font_text import SURFACEOBJ,VT
from original_font_glyph import FONT,SURFACE,STUB
from original_presentation import STOP
from verify_software_message import verify,EXTRA
from verify_surface_fill import RANGES as FILL
from unicorn.x86_const import UC_X86_REG_ECX,UC_X86_REG_ESP
class SoftwareMessageOracle(MissionMessageOracle):
 def __init__(self,exe):
  super().__init__(exe);self.inspection=verify(exe.read_bytes())
 def initialize_extra(self,f):
  super().initialize_extra(f);self.u.mem_write(0x7d6294,b'\0')
  # Diagnostic shared interface: real DSurface fill and ordinary bounds/pitch/
  # bpp getters, supplied lock/unlock. Not an original constructed surface.
  for off,target in ((0x14,0x4ab4f0),(0x70,0x4113b0),(0x74,0x4113c0),(0x78,0x411290),(0x7c,0x4112c0),(0x80,0x4112d0)):self.put(VT+off,target)
  for off,value in ((4,32),(8,24),(12,0),(16,2),(0x1c,1)):self.put(SURFACEOBJ+off,value)
 def extra_inputs(self):return [*super().extra_inputs(),*EXTRA.items(),*FILL.items(),(0x7d6294,1),(VT,0x84),(SURFACEOBJ,0x20)]
 def write(self,u,access,p,n,value,ctx):
  if self.active and SURFACE<=p<SURFACE+1536:
   assert n in (1,2,4) and p+n<=SURFACE+1536
   return # Prior isolated glyph/fill proofs retain ordered-store scope.
  super().write(u,access,p,n,value,ctx)
 def code(self,u,a,n,ctx):
  if not self.active or a==STOP:return
  assert not 0x4ab560<=a<0x4ab6fc,'Entered excluded hardware display fill'
  if a==STUB+16:
   assert u.reg_read(UC_X86_REG_ECX)==SURFACEOBJ
   sp=u.reg_read(UC_X86_REG_ESP);x,y=struct.unpack('<2i',u.mem_read(sp+4,8));assert 0<=x<32 and 0<=y<24
   self.event('L',bool(self.word(FONT+12)),self.word(FONT+16));self.counts['supplied.L']+=1;self.ret(8,SURFACE+x*2+y*64);return
  if a==0x4ab4f0:
   sp=u.reg_read(UC_X86_REG_ESP);self.fills.append((*struct.unpack('<4i',u.mem_read(self.word(sp+4),16)),self.word(sp+8)))
  if any(lo<=a and a+n<=lo+size for lo,size in {**EXTRA,**FILL}.items()):
   if a in EXTRA or a in FILL:self.counts[hex(a)]+=1
   return
  super().code(u,a,n,ctx)
