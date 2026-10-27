# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete ordinary wrapper with a borrowed, already normalized raw depth SHP."""
import struct
from original_props import PropsOracle
from original_presentation import ARG

class SpriteDepthPixelsOracle(PropsOracle):
 def draw_depth(self,blob,aux,aux_frame,offset,frame,w,h,location,clip,flags,z,gradient,brightness,colors,depth,alpha,palette):
  self.raw_fixture()
  self.blit(w,h,[0],1,1,[0,0,1,1],[0,0],[0,0,w,h],-1,1000,colors,depth,alpha,palette)
  self.put(self.body_blitter+4,0x1900000);self.put(self.body_blitter+8,self.alpha_map)
  shape=0x1b90000;other=0x1d00000
  self.u.mem_write(shape,blob);self.u.mem_write(other,aux);self.u.mem_write(ARG,struct.pack('<6i',*location,*clip))
  writes,inputs=self.draw_contract(w,h,blob,self.cvt)
  # Only fresh allocations may change; inherited guards check exact allocation
  # boundaries/canaries. Existing converter allocations remain immutable.
  writes.append((self.alloc,0x1600000-self.alloc));inputs.append((other,len(aux)))
  self.checked_scenery(0x49ea80,[shape,frame,ARG,ARG+8,flags,0,z,gradient,brightness,other,aux_frame,*offset],0x1600000,self.cvt,writes=writes,inputs=inputs)
  return [list(struct.unpack('<'+str(w*h)+'H',self.u.mem_read(addr,w*h*2))) for addr in (0x1700000,0x1780000)]
