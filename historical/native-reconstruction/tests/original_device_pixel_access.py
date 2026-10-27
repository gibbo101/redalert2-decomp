# SPDX-License-Identifier: GPL-3.0-or-later
"""Original inherited pixels compose the same device owners as direct locks."""
import struct
from original_device_surface_pixels import DeviceSurfacePixelsOracle,BASE,SIZE,OBJECT,DESC,DEVICE,TABLE
from original_presentation import STOP
from verify_device_pixel_access import verify,RANGES
from unicorn.x86_const import UC_X86_REG_EAX
POINT=BASE+0x500
class DevicePixelAccessOracle(DeviceSurfacePixelsOracle):
 def __init__(self,exe):self.pixelInspection=verify(exe.read_bytes());super().__init__(exe)
 def code(self,u,a,n,ctx):
  if self.active and a!=STOP and any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()):
   if a in RANGES:self.counts[hex(a)]+=1
   return
  return super().code(u,a,n,ctx)
 def write(self,u,access,p,n,value,ctx):
  if self.active and DEVICE<=p and p+n<=DEVICE+2048:
   assert n in (1,2);value&=(1<<(8*n))-1;self.emit('C',p-DEVICE,n,value);self.expected[p-BASE:p-BASE+n]=value.to_bytes(n,'little');return
  return super().write(u,access,p,n,value,ctx)
 def run(self,f):
  setup=f.copy();setup[-1]='';super().run(setup);self.trace=[];u=self.u
  u.mem_write(DEVICE,bytes((i*29+0x34)&255 for i in range(2048)));self.put(DEVICE,TABLE)
  operations=f[-1];x,y=f[4:6];u.mem_write(POINT,struct.pack('<2i',x,y))
  for op in operations:
   self.emit('I','LUSG'.index(op));self.expected=bytearray(u.mem_read(BASE,SIZE));self.active=True
   root,args=(0x4aac80,[x,y]) if op=='L' else (0x4aae40,[]) if op=='U' else (0x774220,[POINT,0xdead1234]) if op=='S' else (0x7741d0,[POINT])
   from verify_device_surface_pixels import RANGES as DEVICE_RANGES
   try:self.checked_call(root,args,OBJECT,writes=[(OBJECT,36),(DESC,108),(DEVICE,2048)],inputs=[*RANGES.items(),*DEVICE_RANGES.items(),(0x7a0be4,136),(0x851cb0,1),(0xa40d28,1),(DEVICE,4),(TABLE,132),(POINT,8)])
   finally:self.active=False
   assert bytes(u.mem_read(BASE,SIZE))==self.expected
   result=u.reg_read(UC_X86_REG_EAX);result=result&255 if op in 'US' else result
   self.emit('R',result,(self.word(OBJECT+12)+2**31)%2**32-2**31,self.word(OBJECT+16),self.word(OBJECT+20),u.mem_read(OBJECT+25,1)[0])
  self.emit('F',*[self.word(DESC+i*4) for i in range(27)])
  digest=14695981039346656037
  for b in u.mem_read(DEVICE,2048):digest=((digest^b)*1099511628211)&(2**64-1)
  self.emit('P',digest);return self.trace
