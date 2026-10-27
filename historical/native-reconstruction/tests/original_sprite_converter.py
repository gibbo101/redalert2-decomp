# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete original wrapper fixed-word stores and pixels on two shared blitter owners."""
import struct
from original_props import PropsOracle
from original_presentation import ARG
from unicorn import UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EIP
class SpriteConverterOracle(PropsOracle):
 def run(self,cmd):
  fmt,nulls,clips,initial,gradient=cmd;second=0x1bd0000
  self.u.mem_write(second,bytes(self.u.mem_read(self.cvt,0x200)));converters=[self.cvt,second]
  self.put(converters[0]+0x17c,initial);self.put(converters[1]+0x17c,initial^0x12345678)
  self.raw_fixture();self.put(self.body_blitter+4,0x1900000);self.put(self.body_blitter+8,self.alpha_map)
  payload=b'\x2a' if fmt==1 else b'\x03\x00\x2a'
  blob=struct.pack('<4H',0,3,3,2)+struct.pack('<4H4I',0,0,1,1,fmt,0,0,56)*2+payload
  signed=lambda v:(v+2**31)%2**32-2**31
  result=[];stores=[]
  def written(u,access,p,n,v,ctx):
   if p in [c+0x17c for c in converters]:
    assert n==4 and u.reg_read(UC_X86_REG_EIP)==0x49eec4
    index=converters.index(p-0x17c);result.extend(['W',str(index),str(signed(v))]);stores.append(index)
  hook=self.u.hook_add(UC_HOOK_MEM_WRITE,written)
  try:
   for call in range(4):
    owner=call%2;cvt=converters[owner];absent=bool(nulls&(1<<call));flags=signed(initial^0xfedcba98) if absent else (0x6e00,0x6e01,0x4e00,0x4e01)[call]
    clip=(0,0,0,0) if clips&(1<<call) else (0,0,4,4)
    colors=[0x2222]*16;depth=[65535]*16;alpha=[128]*16;palette=[0x1234]*(53*256)
    before=len(stores)
    if absent:
     self.blit(4,4,[0],1,1,[0,0,1,1],[0,0],[0,0,4,4],-1,1000,colors,depth,alpha,palette)
     self.checked_scenery(0x49ea80,[0,call%2,0,0,flags,0,-3,gradient,1000,0,0,0,0],0x1600000,cvt,inputs=[(c,0x200) for c in converters])
     planes=[colors,depth]
    else:
     planes=self.draw(blob,call%2,4,4,(2,2),clip,flags,-3,0 if call%2 else gradient,1000,colors,depth,alpha,palette,cvt=cvt)
    assert len(stores)-before==(0 if absent else 1)
    result.extend(['R',*[str(signed(self.word(c+0x17c))) for c in converters],*[str(v) for plane in planes for v in plane]])
  finally:self.u.hook_del(hook)
  return result
 def word(self,p):return struct.unpack('<I',self.u.mem_read(p,4))[0]
