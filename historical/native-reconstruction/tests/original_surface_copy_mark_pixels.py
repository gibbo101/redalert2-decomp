# SPDX-License-Identifier: GPL-3.0-or-later
"""Actual copy and mark pixels in the same complete refresh parent."""
import struct
from original_surface_mark_pixels import SurfaceMarkPixelsOracle,PIXELS
from original_surface_refresh_marks import ARENA,SURF,VT,PARENT_RECTS
from original_presentation import STOP
from verify_surface_copy_mark_pixels import verify
from verify_surface_copy import RANGES as COPY,TABLES,DATA_RANGES
from verify_surface_mark_pixels import RANGES as MARK
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP
class SurfaceCopyMarkPixelsOracle(SurfaceMarkPixelsOracle):
 def __init__(self,exe):verify(exe.read_bytes());super().__init__(exe)
 def checked_call(self,root,args=(),ecx=0,**kw):
  self.change(VT+8,0x774f00);self.put(0x8315b4,0);self.put(0x839c6c,0)
  kw['inputs']=[*kw.get('inputs',()),*COPY.items(),*[(a,len(v)*4) for a,v in TABLES.items()],*DATA_RANGES.items(),(0x8315b4,4),(0x839c6c,4)]
  super().checked_call(root,args,ecx,**kw)
 def write(self,u,access,p,n,value,ctx):
  if self.active:
   who=next((i for i,b in enumerate(PIXELS) if b<=p and p+n<=b+2048),None)
   if who is not None:
    assert n in (1,2,4);v=value&((1<<(8*n))-1);self.expected[p-ARENA:p-ARENA+n]=v.to_bytes(n,'little');self.emit('S',who,p-PIXELS[who],n,v);return
  super().write(u,access,p,n,value,ctx)
 def code(self,u,a,n,ctx):
  if not self.active or a==STOP:return
  if a in self.pending:
   kind,who=self.pending.pop(a);value=u.reg_read(UC_X86_REG_EAX);value=value if value<2**31 else value-2**32
   if kind!='G':self.emit(kind,who,value);self.mutate(1 if kind=='H' else (2 if self.widths==1 else 3))
  if a==0x774f00:
   sp=u.reg_read(UC_X86_REG_ESP);who=self.sid(u.reg_read(UC_X86_REG_ECX));dst,src,rect,z,one=[self.word(sp+i*4) for i in range(1,6)];assert (dst,rect)==(PARENT_RECTS[1],PARENT_RECTS[0]);self.emit('C',who,*struct.unpack('<4i',u.mem_read(dst,16)),self.sid(src),*struct.unpack('<4i',u.mem_read(rect,16)),z,one);self.mutate(9)
  if any(lo<=a and a+n<=lo+size for lo,size in COPY.items()) and not any(lo<=a and a+n<=lo+size for lo,size in MARK.items()):
   if a in COPY:self.counts[hex(a)]+=1
   return
  super().code(u,a,n,ctx)
