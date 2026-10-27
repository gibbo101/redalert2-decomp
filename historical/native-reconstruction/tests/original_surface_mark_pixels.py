# SPDX-License-Identifier: GPL-3.0-or-later
"""Actual stock pixel stores below complete mark rebuild and refresh parent."""
import hashlib,struct
from original_surface_refresh_marks import SurfaceRefreshMarksOracle,ARENA,SURF,VT,SIZE
from original_presentation import STOP
from verify_surface_mark_pixels import verify,RANGES
from verify_surface_pixel import RANGES as PIXEL
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP
PIXELS=(ARENA+0x66000,ARENA+0x68000)
class SurfaceMarkPixelsOracle(SurfaceRefreshMarksOracle):
 def __init__(self,exe):verify(exe.read_bytes());super().__init__(exe)
 def checked_call(self,root,args=(),ecx=0,**kw):
  bpp,offset,lock=self.pixelFixture
  for i in (0,1):
   for off,v in ((12,lock),(16,bpp if i==0 else 3-bpp),(20,PIXELS[i]+offset)):self.change(SURF+i*0x100+off,v)
   data=bytes((j*29+0x34+i*37)&255 for j in range(2048));self.u.mem_write(PIXELS[i],data);self.expected[PIXELS[i]-ARENA:PIXELS[i]-ARENA+2048]=data
  for off,a in {0x24:0x774220,0x5c:0x411370,0x60:0x4112f0,0x70:0x4113b0,0x74:0x4113c0}.items():self.change(VT+off,a)
  kw['writes']=[*kw.get('writes',()),*[(SURF+i*0x100+12,4) for i in (0,1)],*[(p,2048) for p in PIXELS]];kw['inputs']=[*kw.get('inputs',()),*RANGES.items()];super().checked_call(root,args,ecx,**kw)
 def write(self,u,access,p,n,value,ctx):
  if self.active:
   who=next((i for i in (0,1) if p==SURF+i*0x100+12),None)
   if who is not None:
    assert n==4;v=value&0xffffffff;self.expected[p-ARENA:p-ARENA+4]=v.to_bytes(4,'little');self.emit('L',who,v if v<2**31 else v-2**32);return
   who=next((i for i,b in enumerate(PIXELS) if b<=p and p+n<=b+2048),None)
   if who is not None:
    assert n in (1,2);v=value&((1<<(8*n))-1);self.expected[p-ARENA:p-ARENA+n]=v.to_bytes(n,'little');self.emit('S',who,p-PIXELS[who],n,v);return
  super().write(u,access,p,n,value,ctx)
 def code(self,u,a,n,ctx):
  if not self.active or a==STOP:return
  # The stock pitch helper returns from virtual width at4113C8, inside a
  # newly inspected child rather than the older mark parent's instruction set.
  if a==0x4113c8 and a in self.pending:
   kind,who=self.pending.pop(a);assert kind=='W';value=u.reg_read(UC_X86_REG_EAX);self.emit(kind,who,value if value<2**31 else value-2**32);self.mutate(2 if self.widths==1 else 3)
  if a==0x774220:
   sp=u.reg_read(UC_X86_REG_ESP);who=self.sid(u.reg_read(UC_X86_REG_ECX));point=self.word(sp+4);self.emit('P',who,self.eid(point-4),*struct.unpack('<2i',u.mem_read(point,8)),self.word(sp+8));self.mutate(8)
  if any(lo<=a and a+n<=lo+size for lo,size in PIXEL.items()) and a!=0x4112c0:
   if a in PIXEL:self.counts[hex(a)]+=1
   return
  super().code(u,a,n,ctx)
 def run(self,f):
  self.pixelFixture=f[14:];row=super().run(f[:14]);self.emit('Z',*[int.from_bytes(self.u.mem_read(SURF+i*0x100+12,4),'little',signed=True) for i in (0,1)],*[hashlib.sha256(bytes(self.u.mem_read(p,2048))).hexdigest() for p in PIXELS]);return self.trace
