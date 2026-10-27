# SPDX-License-Identifier: GPL-3.0-or-later
import hashlib
from original_surface_radar_pixel import SurfaceRadarPixelOracle,ARENA,SURF,TABLES,CONTEXT
from verify_surface_radar_pixels import verify
from verify_surface_get_pixel import RANGES as PIXEL
from verify_surface_radar_pixel import RANGES as PARENT
from original_presentation import STOP
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_EBX,UC_X86_REG_ECX,UC_X86_REG_EDX,UC_X86_REG_ESP
PIXELS=[ARENA+0x69000,ARENA+0x6b000]
class SurfaceRadarPixelsOracle(SurfaceRadarPixelOracle):
 def __init__(self,exe):verify(exe.read_bytes());super().__init__(exe)
 def checked_call(self,root,args=(),ecx=0,**kw):
  bpp,offset,depth=self.pixelFixture
  for k in range(2):
   for off,value in ((12,depth),(16,bpp if k==0 else 3-bpp),(20,PIXELS[k]+offset)):self.change(SURF+k*0x100+off,value)
   data=bytes((i*29+0x34+k*37)&255 for i in range(2048));self.u.mem_write(PIXELS[k],data);self.expected[PIXELS[k]-ARENA:PIXELS[k]-ARENA+2048]=data
   for off,va in ((0x24,0x774220),(0x28,0x7741d0),(0x5c,0x411370),(0x60,0x4112f0),(0x70,0x4113b0),(0x74,0x4113c0)):self.change(TABLES[k]+off,va)
  kw['writes']=[*kw.get('writes',()),(SURF+12,4),(SURF+0x100+12,4),*[(p,2048) for p in PIXELS]];kw['inputs']=[*kw.get('inputs',()),*PIXEL.items()];super().checked_call(root,args,ecx,**kw)
 def write(self,u,access,p,n,value,ctx):
  if self.active:
   for k in range(2):
    if p==SURF+k*0x100+12:
     assert n==4;v=value&0xffffffff;self.expected[p-ARENA:p-ARENA+4]=v.to_bytes(4,'little');self.emit('K',k,v if v<2**31 else v-2**32);return
    if PIXELS[k]<=p and p+n<=PIXELS[k]+2048:
     assert n in (1,2);v=value&((1<<(8*n))-1);self.expected[p-ARENA:p-ARENA+n]=v.to_bytes(n,'little');self.emit('N',k,p-PIXELS[k],n,v);return
  super().write(u,access,p,n,value,ctx)
 def code(self,u,a,n,ctx):
  if not self.active or a==STOP:return
  if a in self.readPending:self.readPending.remove(a);self.emit('E',u.reg_read(UC_X86_REG_EAX))
  if a in (0x7741d0,0x774220):
   sp=u.reg_read(UC_X86_REG_ESP);ret=self.word(sp);receiver=u.reg_read(UC_X86_REG_ECX);p=self.word(sp+4);assert p==self.pointaddr;read=a==0x7741d0
   reg=UC_X86_REG_EAX if read or ret in (0x63229e,0x6323a8) else UC_X86_REG_EBX if ret==0x6323dc else UC_X86_REG_EDX
   table=u.reg_read(reg);assert table in TABLES,(hex(ret),hex(table));color=0 if read else self.word(sp+8);self.emit('V' if read else 'W',TABLES.index(table),self.sid(receiver),*[int.from_bytes(u.mem_read(p+i*4,4),'little',signed=True) for i in range(2)],color);self.mutate(11 if read else 12)
   if read:self.readPending.add(ret)
  if any(lo<=a and a+n<=lo+size for lo,size in PIXEL.items()) and not any(lo<=a and a+n<=lo+size for lo,size in PARENT.items()):
   if a in PIXEL:self.counts[hex(a)]+=1
   return
  super().code(u,a,n,ctx)
 def run(self,f):
  self.pixelFixture=f[33:];self.readPending=set();row=super().run(f[:33]);assert not self.readPending
  self.emit('Z',*[int.from_bytes(self.u.mem_read(SURF+k*0x100+12,4),'little',signed=True) for k in range(2)],*[hashlib.sha256(bytes(self.u.mem_read(p,2048))).hexdigest() for p in PIXELS]);return self.trace
