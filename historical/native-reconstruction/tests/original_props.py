# SPDX-License-Identifier: GPL-3.0-or-later
"""Original healthy ordinary props through raw/RLE SHP and Terrain callers."""
import struct
from original_scenery import SceneryOracle
class PropsOracle(SceneryOracle):
 def __init__(self,exe,palette,*,allow_patched=False):
  super().__init__(exe,palette,allow_patched=allow_patched)
  self.raw_body_blitter=struct.unpack('<I',self.u.mem_read(self.cvt+0xbc,4))[0]
  self.raw_shadow_blitter=struct.unpack('<I',self.u.mem_read(self.cvt+0x54,4))[0]
  for obj,vt,methods in [(self.raw_body_blitter,0x78918c,(0x48cef0,0x489000,0x4890f0)),
                         (self.raw_shadow_blitter,0x7892fc,(0x48ca50,0x4878c0,0x487930))]:
   assert struct.unpack('<I',self.u.mem_read(obj,4))[0]==self.va(vt)
   assert struct.unpack('<3I',self.u.mem_read(self.va(vt),12))==tuple(self.va(p) for p in methods)
 def raw_fixture(self):
  # Supplied palettes/alpha data for primitive-surface cases. Actual original
  # converters are used without these redirects in owned I cases.
  self.put(self.raw_body_blitter+4,0x1900000);self.put(self.raw_body_blitter+8,self.alpha_map)
  self.put(self.raw_shadow_blitter+4,0x7bef)
 def scene(self,*args,**kwargs):
  self.raw_fixture();return super().scene(*args,**kwargs)
 def draw(self,*args,**kwargs):
  if kwargs.get('cvt') is None:self.raw_fixture()
  return super().draw(*args,**kwargs)
