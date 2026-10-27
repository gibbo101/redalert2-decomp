# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete original DSurface startup; allocation/device results supplied."""
from collections import Counter
import struct
from original_presentation import PresentationOracle,STOP
from verify_surface_startup import verify,RANGES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_EIP,UC_X86_REG_ESP
BASE=0x3900000;SIZE=0x10000;OBJECT=BASE+0x100;DESC=BASE+0x1000;DEVICE=BASE+0x2000;SURFACE=BASE+0x2100;TABLE=BASE+0x3000;CREATE=BASE+0x4000;DESCRIBE=CREATE+0x100
class SurfaceStartupOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(BASE,SIZE);self.active=False;self.counts=Counter();self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.write)
 def va(self,a):return a
 def ret(self,args,result=0):
  sp=self.u.reg_read(UC_X86_REG_ESP);self.u.reg_write(UC_X86_REG_EAX,result);self.u.reg_write(UC_X86_REG_ESP,sp+4+args);self.u.reg_write(UC_X86_REG_EIP,self.word(sp))
 def word(self,p):return struct.unpack('<I',self.u.mem_read(p,4))[0]
 def emit(self,*v):self.trace.extend(map(str,v))
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  sp=u.reg_read(UC_X86_REG_ESP)
  if a==0x782017:
   assert self.word(sp+4)==108;self.emit('A',108);self.counts['supplied_allocation']+=1;self.ret(0,DESC if self.f[4] else 0);return
  if a==CREATE:
   assert [self.word(sp+i*4) for i in range(1,5)]==[DEVICE,DESC,OBJECT+28,0]
   self.emit('C',*[self.word(DESC+o) for o in (0,4,8,12,104)]);self.counts['supplied_create']+=1
   self.record(OBJECT+28,4,SURFACE if self.f[5] else 0);self.ret(16,0x80004005);return # HRESULT deliberately ignored by original.
  if a==DESCRIBE:
   assert [self.word(sp+4),self.word(sp+8)]==[SURFACE,DESC]
   self.emit('G',1);self.counts['supplied_describe']+=1;self.record(DESC+84,4,self.f[6]);self.record(DESC+104,4,self.f[7]);self.ret(8,0x80004005);return
  assert 0x4aa4a0<=a and a+n<=0x4aa59d,('Uninspected startup instruction',hex(a))
  if a==0x4aa4a0:self.counts['root']+=1
 def record(self,p,n,value):
  raw=int(value&((1<<(8*n))-1)).to_bytes(n,'little');self.u.mem_write(p,raw);self.write(self.u,0,p,n,value,None)
 def write(self,u,access,p,n,value,_):
  if not self.active or not BASE<=p<BASE+SIZE:return
  value&=(1<<(8*n))-1
  if OBJECT<=p and p+n<=OBJECT+36:
   off=p-OBJECT;v={0:3,28:int(value!=0),32:2 if value else 0}.get(off,value);self.emit('O',off,n,v)
  else:assert DESC<=p and p+n<=DESC+108 and n==4;self.emit('D',p-DESC,n,value)
  self.expected[p-BASE:p-BASE+n]=value.to_bytes(n,'little')
 def run(self,f):
  self.f=f;u=self.u;u.mem_write(BASE,b'\xa5'*SIZE)
  self.put(DEVICE,TABLE);self.put(SURFACE,TABLE);self.put(TABLE+24,CREATE);self.put(TABLE+88,DESCRIBE)
  self.put(0x8523cc,DEVICE);u.mem_write(0x852fd7,bytes([f[3]]));self.trace=[];self.expected=bytearray(u.mem_read(BASE,SIZE));self.active=True
  try:self.checked_call(0x4aa4a0,f[:3],OBJECT,writes=[(OBJECT,36),(DESC,108)],inputs=[(0x4aa4a0,0xfd),(0x8523cc,4),(0x852fd7,1),(DEVICE,4),(SURFACE,4),(TABLE,108)])
  finally:self.active=False
  assert u.reg_read(UC_X86_REG_EAX)==OBJECT and bytes(u.mem_read(BASE,SIZE))==self.expected
  signed=lambda v:(v+2**31)%2**32-2**31
  self.emit('R',signed(self.word(OBJECT+4)),signed(self.word(OBJECT+8)),signed(self.word(OBJECT+12)),self.word(OBJECT+16),self.word(OBJECT+20),*u.mem_read(OBJECT+24,2),int(self.word(OBJECT+28)!=0),int(self.word(OBJECT+32)!=0),*[self.word(DESC+o) for o in range(0,108,4)])
  return self.trace
