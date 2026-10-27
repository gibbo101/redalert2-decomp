# SPDX-License-Identifier: GPL-3.0-or-later
"""Full demand image policy inside original overlay/Cell/terrain/projection."""
from original_radar_overlay_color import RadarOverlayColorOracle
from original_cell_radar_color import TYPES,OVERLAY,ANIMATION
from original_presentation import STOP
from unicorn.x86_const import UC_X86_REG_ECX,UC_X86_REG_ESP
class RadarDemandColorOracle(RadarOverlayColorOracle):
 def string(self,p):return bytes(self.u.mem_read(p,256)).split(b'\0')[0].decode('ascii')
 def setup(self):
  super().setup();self.u.mem_write(OVERLAY+0x27f,b'\1');self.u.mem_write(OVERLAY+0x1fc,b'\1');self.u.mem_write(OVERLAY+0xa8,b'\0');self.u.mem_write(OVERLAY+0x1c8,b'LOBRDG10\0');self.typeExpected=bytearray(self.u.mem_read(TYPES,0x10000))
 def code(self,u,a,n,ctx):
  if self.active and a!=STOP:
   sp=u.reg_read(UC_X86_REG_ESP);ecx=u.reg_read(UC_X86_REG_ECX)
   if a==0x4068f0:self.counts['debug_noop']+=1;return
   if a==0x7831f0:
    assert self.word(sp)==0x5dd1bf;out,drive,directory,name,ext=[self.word(sp+i*4) for i in range(1,6)];assert drive==directory==0 and name==OVERLAY+0x1c8 and self.string(ext)=='TEM';u.mem_write(out,b'LOBRDG10.TEM\0');self.ret(0);return
   if a==0x468f50:
    assert self.word(sp)==0x5dd20e and self.string(self.word(sp+4))=='LOBRDG10.TEM';self.fileObject=ecx;self.emit('G',1);self.counts['file_construct']+=1;self.ret(4,ecx);return
   if a==0x495230:
    assert self.word(sp)==0x5dd217 and ecx==self.fileObject;self.emit('G',2);self.counts['file_load']+=1;self.ret(0,ANIMATION+0x500);return
   if a in (0x438410,0x42f350):
    assert self.word(sp)=={0x438410:0x5dd243,0x42f350:0x5dd254}[a] and ecx==self.fileObject+(0x54 if a==0x438410 else 0);self.emit('G',3 if a==0x438410 else 4);self.counts['file_cleanup']+=1;self.ret(0);return
  super().code(u,a,n,ctx)
 def write(self,u,access,p,n,value,ctx):
  if self.active and (p,n) in ((OVERLAY+0xa4,4),(OVERLAY+0xa8,1)):
   v=2 if n==4 else value&255;assert n!=4 or value==ANIMATION+0x500
   self.emit('X',p-OVERLAY,n,v);self.typeExpected[p-TYPES:p-TYPES+n]=(value&((1<<(n*8))-1)).to_bytes(n,'little');self.counts['image_stores']+=1;return
  super().write(u,access,p,n,value,ctx)
 def checked_call(self,*args,**kwargs):
  kwargs['writes']=[*kwargs.get('writes',[]),(OVERLAY+0xa4,4),(OVERLAY+0xa8,1)];super().checked_call(*args,**kwargs)
