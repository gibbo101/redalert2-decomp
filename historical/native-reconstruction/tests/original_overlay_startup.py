# SPDX-License-Identifier: GPL-3.0-or-later
"""Execute complete nonlazy startup with explicit CRT/cache/release services."""
import struct
from collections import Counter
from original_presentation import PresentationOracle,STOP
from verify_overlay_startup import verify,RANGES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EIP
BASE=0x4300000;SIZE=0x4000;TYPE=BASE;SCENARIO=BASE+0x1000;IMAGE1=BASE+0x2000;IMAGE2=BASE+0x2100
class OverlayStartupOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(BASE,SIZE);self.active=False;self.counts=Counter();self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.write)
 def va(self,a):return a
 def word(self,p):return int.from_bytes(self.u.mem_read(p,4),'little')
 def string(self,p):return bytes(self.u.mem_read(p,256)).split(b'\0')[0].decode('ascii')
 def ret(self,n,value=0):
  sp=self.u.reg_read(UC_X86_REG_ESP);self.u.reg_write(UC_X86_REG_EAX,value);self.u.reg_write(UC_X86_REG_EIP,self.word(sp));self.u.reg_write(UC_X86_REG_ESP,sp+4+n)
 def handle(self,p):
  assert p in (0,IMAGE1,IMAGE2);return {0:0,IMAGE1:1,IMAGE2:2}[p]
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  if 0x5d7630<=a and a+n<=0x5d7801:
   if a==0x5d7630:self.counts['roots']+=1
   return
  sp=u.reg_read(UC_X86_REG_ESP);caller=self.word(sp);ecx=u.reg_read(UC_X86_REG_ECX)
  if a==0x7820f4:
   assert caller==0x5d7684;out,fmt,src=[self.word(sp+i*4) for i in range(1,4)];assert fmt==0x7e8110 and src==TYPE+0x1c8
   value=(self.string(src)+'A').encode();u.mem_write(out,value+b'\0');self.ret(0,len(value));self.counts['arctic_names']+=1;return
  if a==0x7823d0:
   assert caller==0x5d76ac;out,src,count=[self.word(sp+i*4) for i in range(1,4)];assert count==24;value=self.string(src).encode()[:count];u.mem_write(out,value+b'\0'*(count-len(value)));self.ret(0,out);return
  if a==0x7831f0:
   assert caller in (0x5d76f3,0x5d7729);out,drive,directory,name,ext=[self.word(sp+i*4) for i in range(1,6)];assert drive==directory==0 and name==TYPE+0x1c8
   extension=self.string(ext);assert extension in ('TEM','SNO','URB','.SHP');u.mem_write(out,(self.string(name)+(extension if extension.startswith('.') else '.'+extension)).encode()+b'\0');self.ret(0);self.counts['makepath']+=1;return
  if a==0x781d3b:
   assert caller==0x5d77ac;self.trace.extend(('F',str(self.handle(self.word(sp+4)))));self.counts['release']+=1;self.ret(0);return
  if a==0x5956c0:
   assert caller==0x5d77c9;self.trace.extend(('L',self.string(ecx),str(self.success)));self.counts['cache']+=1;self.ret(0,IMAGE2 if self.success else 0);return
  raise AssertionError(('Uninspected startup instruction',hex(a)))
 def write(self,u,access,p,n,value,_):
  if not self.active or not BASE<=p<BASE+SIZE:return
  off=p-TYPE;assert (off,n) in ((0xa4,4),(0xa8,1),(0x1bc,4),(0x1e2,1),(0x1e0,1),*[(0x1c8+i,4) for i in range(0,24,4)])
  v=self.handle(value) if off==0xa4 else value&((1<<(8*n))-1);self.trace.extend(map(str,('S',off,n,v)));self.expected[p-BASE:p-BASE+n]=(value&((1<<(n*8))-1)).to_bytes(n,'little');self.counts['stores']+=1
 def run(self,theater,theaterFlag,newFlag,arctic,inUse,initial,owned,success,width,height,maximum,repeat,name):
  u=self.u;u.mem_write(BASE,b'\xa5'*SIZE);self.put(TYPE+0xa4,IMAGE1 if initial else 0);self.put(TYPE+0x1bc,maximum)
  for off,v in ((0xa8,owned),(0x1fc,theaterFlag),(0x207,newFlag),(0x1e1,arctic),(0x1e2,inUse)):u.mem_write(TYPE+off,bytes([v]))
  u.mem_write(TYPE+0x1c8,name.encode()+b'\0'*(25-len(name)));self.put(SCENARIO+0x838,theater);self.put(0xa3d290,SCENARIO);u.mem_write(IMAGE1,b'\1'*16);u.mem_write(IMAGE2,struct.pack('<Hhh',0,width,height)+b'\0'*10);self.expected=bytearray(u.mem_read(BASE,SIZE));self.trace=[];self.success=success
  for _ in range(repeat):
   self.active=True
   try:self.checked_call(0x5d7630,ecx=TYPE,writes=[(TYPE+0xa4,4),(TYPE+0xa8,1),(TYPE+0x1bc,4),(TYPE+0x1c8,25),(TYPE+0x1e2,1)],inputs=[*RANGES.items(),(0xa3d290,4),(SCENARIO,0x900),(IMAGE1,0x200),(0x79abac,312),(0x7e8110,4),(0x7ced14,5)])
   finally:self.active=False
   self.trace.extend(map(str,('R',self.handle(self.word(TYPE+0xa4)),u.mem_read(TYPE+0xa8,1)[0],self.word(TYPE+0x1bc),u.mem_read(TYPE+0x1e2,1)[0],self.string(TYPE+0x1c8))))
  assert bytes(u.mem_read(BASE,SIZE))==self.expected;return self.trace
