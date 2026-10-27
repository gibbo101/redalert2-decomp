# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete original overlay demand loader on checked file/CRT services."""
from collections import Counter
from original_presentation import PresentationOracle,STACK,STOP
from verify_overlay_image import verify,RANGES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EIP
BASE=0x4200000;SIZE=0x4000;TYPE=BASE;SCENARIO=BASE+0x1000;IMAGE1=BASE+0x2000;IMAGE2=BASE+0x2100
class OverlayImageOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(BASE,SIZE);self.active=False;self.counts=Counter();self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.write)
 def va(self,a):return a
 def word(self,p):return int.from_bytes(self.u.mem_read(p,4),'little')
 def string(self,p):return bytes(self.u.mem_read(p,256)).split(b'\0')[0].decode('ascii')
 def ret(self,n,value=0):
  sp=self.u.reg_read(UC_X86_REG_ESP);self.u.reg_write(UC_X86_REG_EAX,value);self.u.reg_write(UC_X86_REG_EIP,self.word(sp));self.u.reg_write(UC_X86_REG_ESP,sp+4+n)
 def handle(self,p):assert p in (0,IMAGE1,IMAGE2);return {0:0,IMAGE1:1,IMAGE2:2}[p]
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  if any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()):
   if a==0x5dd150:self.counts['roots']+=1
   if a==0x5d7bd0:self.counts['new_theater']+=1
   return
  sp=u.reg_read(UC_X86_REG_ESP);caller=self.word(sp);ecx=u.reg_read(UC_X86_REG_ECX)
  if a==0x7831f0:
   assert caller in (0x5dd1bf,0x5dd1e8);out,drive,directory,name,ext=[self.word(sp+i*4) for i in range(1,6)];assert drive==directory==0 and name==TYPE+0x1c8
   extension=self.string(ext);assert extension in ('TEM','SNO','URB','.SHP');filename=self.string(name)+(extension if extension.startswith('.') else '.'+extension)
   u.mem_write(out,filename.encode()+b'\0');self.ret(0);self.counts['makepath']+=1;return
  if a==0x468f50:
   assert caller==0x5dd20e;self.fileObject=ecx;self.filename=self.string(self.word(sp+4));self.trace.extend(('C',self.filename));self.counts['construct']+=1;self.ret(4,ecx);return
  if a==0x495230:
   assert caller==0x5dd217 and ecx==self.fileObject;self.trace.extend(('L',str(self.success)));self.counts['load']+=1;self.ret(0,IMAGE2 if self.success else 0);return
  if a in (0x438410,0x42f350):
   assert caller=={0x438410:0x5dd243,0x42f350:0x5dd254}[a] and ecx==self.fileObject+(0x54 if a==0x438410 else 0);self.trace.extend(('D','1' if a==0x438410 else '2'));self.counts['cleanup']+=1;self.ret(0);return
  raise AssertionError(('Uninspected overlay image instruction',hex(a)))
 def write(self,u,access,p,n,value,_):
  if not self.active or not BASE<=p<BASE+SIZE:return
  assert (p,n) in ((TYPE+0xa4,4),(TYPE+0xa8,1));v=self.handle(value) if n==4 else value&255;self.trace.extend(map(str,('S',p-TYPE,n,v)));self.expected[p-BASE:p-BASE+n]=(value&((1<<(n*8))-1)).to_bytes(n,'little');self.counts['stores']+=1
 def run(self,theater,demand,theaterFlag,newFlag,initial,owned,success,repeat,name):
  u=self.u;u.mem_write(BASE,b'\xa5'*SIZE);self.put(TYPE+0xa4,IMAGE1 if initial else 0);u.mem_write(TYPE+0xa8,bytes([owned]));u.mem_write(TYPE+0x27f,bytes([demand]));u.mem_write(TYPE+0x1fc,bytes([theaterFlag]));u.mem_write(TYPE+0x207,bytes([newFlag]));u.mem_write(TYPE+0x1c8,name.encode()+b'\0');self.put(SCENARIO+0x838,theater);self.put(0xa3d290,SCENARIO);u.mem_write(IMAGE1,b'\1'*16);u.mem_write(IMAGE2,b'\2'*16);self.expected=bytearray(u.mem_read(BASE,SIZE));self.trace=[];self.success=success
  for _ in range(repeat):
   self.active=True
   try:self.checked_call(0x5dd150,ecx=TYPE,writes=[(TYPE+0xa4,4),(TYPE+0xa8,1)],inputs=[*RANGES.items(),(0xa3d290,4),(0x79abac,312)])
   finally:self.active=False
   result=self.handle(u.reg_read(UC_X86_REG_EAX));self.trace.extend(map(str,('R',result,self.handle(self.word(TYPE+0xa4)),u.mem_read(TYPE+0xa8,1)[0],result)))
  assert bytes(u.mem_read(BASE,SIZE))==self.expected;return self.trace
