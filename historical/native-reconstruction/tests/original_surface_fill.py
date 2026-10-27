# SPDX-License-Identifier: GPL-3.0-or-later
"""Actual software rectangle fill over actual BSurface vtable, no API stubs."""
import struct,hashlib
from collections import Counter
from original_presentation import PresentationOracle,STOP
from verify_surface_fill import verify,RANGES,VT
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX
ARENA=0x3900000;SIZE=0x10000;OBJ=ARENA+0x100;CLIP=ARENA+0x200;RECT=ARENA+0x220;BUFFER=ARENA+0x2000
class SurfaceFillOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(ARENA,SIZE);self.active=False;self.counts=Counter();self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.write)
 def va(self,a):return a
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  assert any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected surface fill instruction',hex(a))
  if a in RANGES:self.counts[hex(a)]+=1
 def write(self,u,access,p,n,value,_):
  if self.active and BUFFER<=p<BUFFER+2048:
   assert n in (1,2,4) and p+n<=BUFFER+2048
   self.trace.extend(struct.pack('<III',p-BUFFER,n,value&((1<<(n*8))-1)))
 def run(self,f):
  u=self.u;u.mem_write(ARENA,b'\xa5'*SIZE)
  for off,value in ((0,VT),(4,f['width']),(8,f['height']),(12,f['lock']),(16,f['bpp']),(20,BUFFER+f['offset'])):self.put(OBJ+off,value)
  u.mem_write(CLIP,struct.pack('<4i',*f['clip']));u.mem_write(RECT,struct.pack('<4i',*f['rect']));u.mem_write(BUFFER,bytes((i*29+0x34)&255 for i in range(2048)))
  before=bytes(u.mem_read(ARENA,SIZE));self.trace=bytearray();self.active=True
  try:self.checked_call(0x774390 if f['op']=='F' else 0x7743c0,[RECT,f['color']] if f['op']=='F' else [CLIP,RECT,f['color']],OBJ,writes=[(OBJ+12,4),(BUFFER,2048)],inputs=[*RANGES.items(),(VT,136),(CLIP,16),(RECT,16)])
  finally:self.active=False
  after=bytearray(u.mem_read(ARENA,SIZE))
  for p,n in ((OBJ+12,4),(BUFFER,2048)):after[p-ARENA:p-ARENA+n]=before[p-ARENA:p-ARENA+n]
  assert after==before,'Fill changed unrelated arena/input/padding'
  return ['R',str(u.reg_read(UC_X86_REG_EAX)&255),'B',hashlib.sha256(bytes(u.mem_read(BUFFER,2048))).hexdigest(),'T',hashlib.sha256(self.trace).hexdigest(),'L',str(struct.unpack('<i',u.mem_read(OBJ+12,4))[0])]
