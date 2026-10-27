# SPDX-License-Identifier: GPL-3.0-or-later
"""Unmodified stock pixel writer and all entered stock children."""
import struct,hashlib
from collections import Counter
from original_presentation import PresentationOracle,STOP
from verify_surface_pixel import verify,RANGES,VT
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX
ARENA=0x3900000;SIZE=0x10000;OBJ=ARENA+0x100;POINT=ARENA+0x200;BUFFER=ARENA+0x2000
def signed(v):return v if v<2**31 else v-2**32
class SurfacePixelOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(ARENA,SIZE);self.active=False;self.counts=Counter();self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.write)
 def va(self,a):return a
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  assert any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected pixel instruction',hex(a))
  if a in RANGES:self.counts[hex(a)]+=1
 def write(self,u,access,p,n,value,_):
  if not self.active or not ARENA<=p<ARENA+SIZE:return
  if p==OBJ+12:assert n==4;self.trace+=['L',str(signed(value&0xffffffff))]
  else:assert BUFFER<=p and p+n<=BUFFER+2048 and n in (1,2);self.trace+=list(map(str,('S',p-BUFFER,n,value&((1<<(8*n))-1))))
  self.expected[p-ARENA:p-ARENA+n]=int(value&((1<<(8*n))-1)).to_bytes(n,'little')
 def run(self,f):
  width,height,bpp,offset,lock,x,y,color,allocation,words=f;u=self.u;u.mem_write(ARENA,b'\xa5'*SIZE)
  for off,value in ((0,VT),(4,width),(8,height),(12,lock),(16,bpp),(20,BUFFER+offset if allocation else 0)):self.put(OBJ+off,value)
  u.mem_write(POINT,struct.pack('<2i',x,y));u.mem_write(BUFFER,bytes((i*29+0x34)&255 for i in range(2048)));self.expected=bytearray(u.mem_read(ARENA,SIZE));self.trace=[];self.active=True
  try:self.checked_call(0x774220,[POINT,color],OBJ,writes=[(OBJ+12,4),(BUFFER,2048)],inputs=[*RANGES.items(),(VT,136),(POINT,8)])
  finally:self.active=False
  assert bytes(u.mem_read(ARENA,SIZE))==self.expected
  return self.trace+['R',str(u.reg_read(UC_X86_REG_EAX)&255),str(struct.unpack('<i',u.mem_read(OBJ+12,4))[0]),hashlib.sha256(bytes(u.mem_read(BUFFER,2048))).hexdigest()]
