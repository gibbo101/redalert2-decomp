# SPDX-License-Identifier: GPL-3.0-or-later
import struct
from collections import Counter
from original_presentation import PresentationOracle,STOP
from verify_surface_clip import verify,RANGES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX
ARENA=0x3900000;SIZE=0x1000
class SurfaceClipOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(ARENA,SIZE);self.active=False;self.counts=Counter();self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.write)
 def va(self,a):return a
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  assert any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected clip instruction',hex(a))
  if a in RANGES:self.counts[hex(a)]+=1
 def write(self,u,access,p,n,value,_):
  if not self.active or not ARENA<=p<ARENA+SIZE:return
  offset=p-ARENA;assert n==4 and offset%4==0 and offset//16 in (0,2)
  value=value&0xffffffff;self.trace+=['S',str(offset//32),str(offset%16//4),str(value if value<2**31 else value-2**32)]
  self.expected[offset:offset+n]=value.to_bytes(n,'little')
 def run(self,f):
  u=self.u;u.mem_write(ARENA,b'\xa5'*SIZE);u.mem_write(ARENA,struct.pack('<16i',*f));self.expected=bytearray(u.mem_read(ARENA,SIZE));self.trace=[];self.active=True
  try:self.checked_call(0x775190,[ARENA+32,ARENA+48],ARENA,ARENA+16,writes=[(ARENA,16),(ARENA+32,16)],inputs=[*RANGES.items(),(ARENA+16,16),(ARENA+48,16)])
  finally:self.active=False
  assert bytes(u.mem_read(ARENA,SIZE))==self.expected
  return self.trace+['R',str(u.reg_read(UC_X86_REG_EAX)&255),*map(str,struct.unpack('<16i',u.mem_read(ARENA,64)))]
