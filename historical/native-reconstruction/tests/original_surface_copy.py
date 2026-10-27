# SPDX-License-Identifier: GPL-3.0-or-later
import struct,hashlib
from collections import Counter
from original_presentation import PresentationOracle,STOP
from verify_surface_copy import verify,RANGES,TABLES,DATA_RANGES,VT
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP
ARENA=0x3900000;SIZE=0x10000;OBJECTS=[ARENA+0x100,ARENA+0x200];BUFFERS=[ARENA+0x2000,ARENA+0x5000];RECTS=ARENA+0x9000
def signed(v):return v if v<2**31 else v-2**32
class SurfaceCopyOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(ARENA,SIZE);self.active=False;self.counts=Counter();self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.write)
 def va(self,a):return a
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  assert any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected copy instruction',hex(a))
  if a in RANGES:self.counts[hex(a)]+=1
  tags={0x411290:'R',0x4113b0:'B',0x4113c0:'P',0x4112c0:'W',0x411370:'K',0x4112f0:'U'}
  if a in tags:
   owner=OBJECTS.index(u.reg_read(UC_X86_REG_ECX));x=y=0
   if tags[a]=='K':x,y=struct.unpack('<2i',u.mem_read(u.reg_read(UC_X86_REG_ESP)+4,8))
   self.trace+=list(map(str,('Q',owner,tags[a],x,y)))
 def write(self,u,access,p,n,value,_):
  if not self.active or not ARENA<=p<ARENA+SIZE:return
  value=value&((1<<(8*n))-1)
  if p in [o+12 for o in OBJECTS]:assert n==4;self.trace+=['L',str(OBJECTS.index(p-12)),str(signed(value))]
  else:
   owner=next((i for i,b in enumerate(BUFFERS) if b<=p and p+n<=b+8192),None);assert owner is not None and n in (1,2,4)
   self.trace+=list(map(str,('S',owner,p-BUFFERS[owner],n,value)))
  self.expected[p-ARENA:p-ARENA+n]=value.to_bytes(n,'little')
 def run(self,f):
  same,words=f[:2];u=self.u;u.mem_write(ARENA,b'\xa5'*SIZE)
  for j in range(2):
   width,height,bpp,offset,lock,present=f[2+6*j:8+6*j]
   for off,value in ((0,VT),(4,width),(8,height),(12,lock),(16,bpp),(20,BUFFERS[j]+offset if present else 0)):self.put(OBJECTS[j]+off,value)
   u.mem_write(BUFFERS[j],bytes(0 if i%7==0 else (i*29+0x34+j*41)&255 for i in range(8192)))
  u.mem_write(RECTS,struct.pack('<8i',*f[14:22]));self.put(0x8315b4,0);self.put(0x839c6c,0);self.expected=bytearray(u.mem_read(ARENA,SIZE));self.trace=[];self.active=True
  try:self.checked_call(0x774f00,[RECTS,OBJECTS[0 if same else 1],RECTS+16,*f[22:24]],OBJECTS[0],writes=[(o+12,4) for o in OBJECTS]+[(b,8192) for b in BUFFERS],inputs=[*RANGES.items(),(VT,136),(RECTS,32),(0x8315b4,4),(0x839c6c,4),*[(a,len(v)*4) for a,v in TABLES.items()],*DATA_RANGES.items()])
  finally:self.active=False
  assert bytes(u.mem_read(ARENA,SIZE))==self.expected
  out=self.trace+['R',str(u.reg_read(UC_X86_REG_EAX)&255)]
  for o,b in zip(OBJECTS,BUFFERS):out += [str(struct.unpack('<i',u.mem_read(o+12,4))[0]),hashlib.sha256(bytes(u.mem_read(b,8192))).hexdigest()]
  return out
