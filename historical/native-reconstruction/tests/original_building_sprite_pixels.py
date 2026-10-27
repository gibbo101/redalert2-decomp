# SPDX-License-Identifier: GPL-3.0-or-later
"""Ordinary SHP wrapper with null optional depth image and nonzero unused tails."""
import struct
from original_props import PropsOracle
from original_presentation import ARG
class BuildingSpritePixelsOracle(PropsOracle):
 def draw(self,blob,frame,w,h,location,clip,flags,z,gradient,brightness,colors,depth,alpha,palette):
  self.raw_fixture()
  self.blit(w,h,[0],1,1,[0,0,1,1],[0,0],[0,0,w,h],-1,1000,colors,depth,alpha,palette)
  self.put(self.body_blitter+4,0x1900000);self.put(self.body_blitter+8,self.alpha_map)
  shape=0x1b90000;self.u.mem_write(shape,blob);self.u.mem_write(ARG,struct.pack('<6i',*location,*clip))
  writes,inputs=self.draw_contract(w,h,blob,self.cvt)
  # Complete original wrapper consumes the actual caller words. With optional
  # image null, frame3 and offsets198/446 do not select a depth-image owner.
  self.checked_scenery(0x49ea80,[shape,frame,ARG,ARG+8,flags,0,z,gradient,brightness,0,3,198,446],0x1600000,self.cvt,writes=writes,inputs=inputs)
  return [list(struct.unpack('<'+str(w*h)+'H',self.u.mem_read(addr,w*h*2))) for addr in (0x1700000,0x1780000)]
