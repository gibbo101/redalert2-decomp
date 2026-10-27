# SPDX-License-Identifier: GPL-3.0-or-later
"""Execute original device Lock/Unlock with isolated platform results."""
import struct
from collections import Counter
from original_presentation import PresentationOracle,STOP
from verify_device_surface_pixels import verify,RANGES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EIP
BASE=0x3900000;SIZE=0x10000;OBJECT=BASE+0x100;DESC=BASE+0x1000;DEVICE=BASE+0x2000;TABLE=BASE+0x3000;LOST=BASE+0x4000;RESTORE=LOST+0x100;LOCK=LOST+0x200;UNLOCK=LOST+0x300
class DeviceSurfacePixelsOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(BASE,SIZE);self.active=False;self.counts=Counter();self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.write)
 def va(self,a):return a
 def word(self,p):return struct.unpack('<I',self.u.mem_read(p,4))[0]
 def emit(self,*v):self.trace.extend(map(str,v))
 def ret(self,args,result=0):
  sp=self.u.reg_read(UC_X86_REG_ESP);self.u.reg_write(UC_X86_REG_EAX,result);self.u.reg_write(UC_X86_REG_ESP,sp+4+args);self.u.reg_write(UC_X86_REG_EIP,self.word(sp))
 def code(self,u,a,n,ctx):
  if not self.active or a==STOP:return
  sp=u.reg_read(UC_X86_REG_ESP)
  if a==LOST:
   assert self.word(sp+4)==DEVICE;value=0 if self.status==0 else 1 if self.status==1 else 0x887601c2 if self.status==2 or self.statusCalls==0 else 0
   self.statusCalls+=1;self.emit('H',value);self.counts['status']+=1;self.ret(4,value);return
  if a==RESTORE:assert self.word(sp+4)==DEVICE;self.emit('T',self.restore);self.counts['restore']+=1;self.ret(4,self.restore);return
  if a==LOCK:
   assert [self.word(sp+4*i) for i in (1,2,4,5)]==[DEVICE,0,1,0];d=self.word(sp+12);assert self.word(d)==108 and bytes(u.mem_read(d+4,104))==bytes(104)
   self.emit('K',1,self.failed);self.counts['platform_lock']+=1
   if not self.failed:
    for off,v in ((16,self.pitch),(36,DEVICE+self.offset),(84,self.bits),(104,self.caps)):self.put(d+off,v)
   self.ret(20,self.failed);return
  if a==UNLOCK:assert self.word(sp+4)==DEVICE;self.emit('N',self.word(sp+8));self.counts['platform_unlock']+=1;self.ret(8,0x80004005);return
  assert any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected device pixel',hex(a))
  if a in RANGES:
   assert u.reg_read(UC_X86_REG_ECX)==OBJECT;self.counts[hex(a)]+=1
 def write(self,u,access,p,n,value,ctx):
  if not self.active or not BASE<=p<BASE+SIZE:return
  value&=(1<<(8*n))-1
  if OBJECT<=p and p+n<=OBJECT+36:
   off=p-OBJECT;assert (off,n) in ((12,4),(16,4),(20,4),(25,1));self.emit('O',off,n,value)
  else:assert DESC<=p and p+n<=DESC+108 and n==4;self.emit('B',p-DESC,n,value)
  self.expected[p-BASE:p-BASE+n]=value.to_bytes(n,'little')
 def run(self,f):
  enabled,secondary,present,count,x,y,self.status,self.restore,self.failed,self.bits,self.caps,self.pitch,self.offset,initialBytes,operations=f;u=self.u;u.mem_write(BASE,b'\xa5'*SIZE)
  for p,v in ((OBJECT,0x7a0be4),(OBJECT+12,count),(OBJECT+16,initialBytes),(OBJECT+20,DEVICE+self.offset),(OBJECT+28,DEVICE if present else 0),(OBJECT+32,DESC),(DESC+16,self.pitch),(DEVICE,TABLE),(TABLE+0x60,LOST),(TABLE+0x6c,RESTORE),(TABLE+0x64,LOCK),(TABLE+0x80,UNLOCK)):self.put(p,v)
  u.mem_write(OBJECT+25,b'\x07');u.mem_write(0x851cb0,bytes([enabled]));u.mem_write(0xa40d28,bytes([secondary]));self.trace=[];self.statusCalls=0
  for op in operations:
   self.emit('I',0 if op=='L' else 1);self.expected=bytearray(u.mem_read(BASE,SIZE));self.active=True
   try:self.checked_call(0x4aac80 if op=='L' else 0x4aae40,[x,y] if op=='L' else [],OBJECT,writes=[(OBJECT,36),(DESC,108)],inputs=[*RANGES.items(),(0x7a0be4,136),(0x851cb0,1),(0xa40d28,1),(DEVICE,4),(TABLE,132)])
   finally:self.active=False
   assert bytes(u.mem_read(BASE,SIZE))==self.expected
   result=u.reg_read(UC_X86_REG_EAX);result=result if op=='L' else result&255
   self.emit('R',result,(self.word(OBJECT+12)+2**31)%2**32-2**31,self.word(OBJECT+16),self.word(OBJECT+20),u.mem_read(OBJECT+25,1)[0])
  self.emit('F',*[self.word(DESC+i*4) for i in range(27)]);return self.trace
