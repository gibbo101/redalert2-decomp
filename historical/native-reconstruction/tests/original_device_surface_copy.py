# SPDX-License-Identifier: GPL-3.0-or-later
"""Unchanged device copy through its actual software-source fallback."""
import struct
from original_device_surface_pixels import DeviceSurfacePixelsOracle,BASE,SIZE,OBJECT,DESC,DEVICE,TABLE
from original_presentation import STOP
from verify_device_surface_copy import verify,RANGES,VT,TABLES,DATA_RANGES
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP
SOURCE=BASE+0x300;RECTS=BASE+0x500;BUFFERS=(BASE+0x6000,BASE+0x9000)
class DeviceSurfaceCopyOracle(DeviceSurfacePixelsOracle):
 def __init__(self,exe):self.copyInspection=verify(exe.read_bytes());super().__init__(exe)
 def code(self,u,a,n,ctx):
  if not self.active or a==STOP:return
  tags={0x411290:'R',0x4113b0:'B',0x4113c0:'P',0x4112c0:'W',0x411370:'K',0x4112f0:'U',0x4aac80:'K',0x4aae40:'U',0x4aac60:'B',0x4aac70:'P'}
  if a in tags:
   j=(OBJECT,SOURCE).index(u.reg_read(UC_X86_REG_ECX));x=y=0
   if tags[a]=='K':x,y=struct.unpack('<2i',u.mem_read(u.reg_read(UC_X86_REG_ESP)+4,8))
   self.emit('Q',j,tags[a],x,y)
  if a==0x411310:assert u.reg_read(UC_X86_REG_ECX)==SOURCE;self.emit('V',0)
  from verify_device_surface_pixels import RANGES as DEVICE_RANGES
  if a in (BASE+0x4000,BASE+0x4100,BASE+0x4200,BASE+0x4300) or any(lo<=a and a+n<=lo+size for lo,size in DEVICE_RANGES.items()):return super().code(u,a,n,ctx)
  assert any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected device copy instruction',hex(a))
  if a in RANGES:self.counts[hex(a)]+=1
 def write(self,u,access,p,n,value,ctx):
  if not self.active or not BASE<=p<BASE+SIZE:return
  value&=(1<<(8*n))-1
  if p==SOURCE+12:assert n==4;self.emit('L',(value+2**31)%2**32-2**31)
  elif any(b<=p and p+n<=b+2048 for b in BUFFERS):
   j=next(i for i,b in enumerate(BUFFERS) if b<=p and p+n<=b+2048);assert n in (1,2,4);self.emit('S',j,p-BUFFERS[j],n,value)
  else:return super().write(u,access,p,n,value,ctx)
  self.expected[p-BASE:p-BASE+n]=value.to_bytes(n,'little')
 def run(self,f):
  enabled,secondary,count,status,restore,failed,bpp,w,h,sw,sh,sbpp=f[:12];dr=f[12:16];sr=f[16:20];first,second=f[20:22]
  super().run([enabled,secondary,1,count,0,0,status,restore,failed,bpp*8,0x2040,w*bpp,0x4080,bpp,'']);self.trace=[];u=self.u
  for p,v in ((OBJECT+4,w),(OBJECT+8,h),(SOURCE,VT),(SOURCE+4,sw),(SOURCE+8,sh),(SOURCE+12,0),(SOURCE+16,sbpp),(SOURCE+20,BUFFERS[1]+128),(0x8315b4,0),(0x839c6c,0)):self.put(p,v)
  u.mem_write(RECTS,struct.pack('<8i',*dr,*sr))
  for j,b in enumerate(BUFFERS):u.mem_write(b,bytes(0 if i%7==0 else (i*29+0x34+j*41)&255 for i in range(2048)))
  self.expected=bytearray(u.mem_read(BASE,SIZE));self.active=True
  try:self.checked_call(0x4aaf80,[RECTS,SOURCE,RECTS+16,first,second],OBJECT,writes=[(OBJECT,36),(SOURCE+12,4),(DESC,108),*[(b,2048) for b in BUFFERS]],inputs=[*RANGES.items(),(0x7a0be4,136),(VT,136),(DEVICE,4),(TABLE,132),(RECTS,32),(0x851cb0,1),(0xa40d28,1),(0x8315b4,4),(0x839c6c,4),*[(a,len(v)*4) for a,v in TABLES.items()],*DATA_RANGES.items()])
  finally:self.active=False
  assert bytes(u.mem_read(BASE,SIZE))==self.expected
  self.emit('R',u.reg_read(UC_X86_REG_EAX)&255,(self.word(OBJECT+12)+2**31)%2**32-2**31,self.word(OBJECT+16),self.word(OBJECT+20),u.mem_read(OBJECT+25,1)[0],(self.word(SOURCE+12)+2**31)%2**32-2**31)
  self.emit('F',*[self.word(DESC+i*4) for i in range(27)]);self.emit('P')
  for b in BUFFERS:
   digest=14695981039346656037
   for byte in u.mem_read(b,2048):digest=((digest^byte)*1099511628211)&(2**64-1)
   self.emit(digest)
  return self.trace
