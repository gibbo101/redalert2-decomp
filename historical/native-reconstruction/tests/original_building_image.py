# SPDX-License-Identifier: GPL-3.0-or-later
"""Unmodified complete Building getters/theater/fallback/timing; explicit file/CRT services."""
from collections import Counter
import struct
from original_presentation import PresentationOracle,STOP
from verify_building_image import verify,RANGES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_READ,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EIP
BASE=0x4300000;SIZE=0x10000;TYPE=BASE+0x1000;SCENARIO=BASE+0x4000;RULES=BASE+0x6000;IMAGES=[0,BASE+0x9000,BASE+0x9100,BASE+0x9200]
class BuildingImageOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(BASE,SIZE);self.active=False;self.counts=Counter()
  self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_READ,self.read);self.u.hook_add(UC_HOOK_MEM_WRITE,self.write)
 def va(self,a):return a
 def word(self,p):return int.from_bytes(self.u.mem_read(p,4),'little')
 def signed(self,v):return (v+2**31)%2**32-2**31
 def string(self,p):return bytes(self.u.mem_read(p,256)).split(b'\0')[0].decode('ascii')
 def handle(self,p):return IMAGES.index(p)
 def ret(self,pop,value=0):
  sp=self.u.reg_read(UC_X86_REG_ESP);self.u.reg_write(UC_X86_REG_EAX,value);self.u.reg_write(UC_X86_REG_EIP,self.word(sp));self.u.reg_write(UC_X86_REG_ESP,sp+4+pop)
 def mutation_write(self,p,b):
  self.u.mem_write(p,b);self.expected[p-BASE:p-BASE+len(b)]=b
 def mutate(self,point):
  if self.mutated or not self.mode:return
  if self.mode in (1,2,3) and point!=1 or self.mode==4 and point!=2 or self.mode==5 and point!=3:return
  self.mutated=True;self.trace+=['M',str(self.mode)]
  def integer(off,v):self.mutation_write(TYPE+off,struct.pack('<I',v&0xffffffff))
  if self.mode==1:
   self.mutation_write(TYPE+0x13eb,b'CTRETRY.SHP\0');self.mutation_write(TYPE+0xbf4,b'CTRETRY\0')
  if self.mode==2:self.mutation_write(TYPE+0x1351,b'\xff');integer(0x137c,2147483647)
  if self.mode in (3,4):integer(0xa4,IMAGES[3]);integer(0xb98,IMAGES[3])
  if self.mode==5:self.mutation_write(TYPE+0x1351,b'\x80');integer(0x137c,-2)
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  if any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()):
   if a in RANGES:self.counts[hex(a)]+=1
   return
  sp=u.reg_read(UC_X86_REG_ESP);arg=lambda i:self.word(sp+4+4*i);ecx=u.reg_read(UC_X86_REG_ECX);caller=self.word(sp)
  if a==0x7831f0:
   out,drive,directory,name,ext=[arg(i) for i in range(5)];assert drive==directory==0 and name==TYPE+0xbf4 and self.string(ext)=='.SHP'
   u.mem_write(out,(self.string(name)+'.SHP').encode()+b'\0');self.counts['makepath']+=1;self.ret(0);return
  if a==0x7823d0:
   out,source,n=[arg(i) for i in range(3)];assert source==TYPE+0x13eb and n==19
   value=self.string(source).encode()[:n].ljust(n,b'\0');u.mem_write(out,value);self.counts['strncpy']+=1;self.ret(0,out);return
  if a==0x468f50:
   id=len(self.files);assert id in (0,1);self.files[ecx]=id;self.trace+=['C',str(id),self.string(arg(0))];self.counts['construct']+=1;self.ret(4,ecx);return
  if a==0x4691a0:
   assert ecx in self.files and self.files[ecx]==0 and arg(0)==0;self.trace+=['K','0','0'];self.counts['cache']+=1;self.ret(4);return
  if a==0x495230:
   id=self.files[ecx];result=self.first if self.loads%2==0 else self.second;self.loads+=1;self.trace+=['L',str(id),str(result)];self.mutate(1);self.counts['load']+=1;self.ret(0,IMAGES[result]);return
  if a in (0x438410,0x42f350):
   file=ecx-(0x54 if a==0x438410 else 0);id=self.files[file];phase=1 if a==0x438410 else 2;self.trace+=['D',str(id),str(phase)];self.mutate(2);self.counts['cleanup']+=1;self.ret(0);return
  raise AssertionError(('Uninspected Building image instruction',hex(a),hex(caller)))
 def read(self,u,access,p,n,v,_):
  if not self.active:return
  if p==RULES+0x1178:assert n==8;self.trace+=['T']
  for i,image in enumerate(IMAGES[1:],1):
   if p==image+6:assert n==2;self.trace+=['H',str(i),str(struct.unpack('<h',u.mem_read(p,2))[0])];self.mutate(3)
 def write(self,u,access,p,n,v,_):
  if not self.active or not BASE<=p<BASE+SIZE:return
  off=p-TYPE;assert (off,n) in ((0xa4,4),(0xb98,4),(0xa8,1),(0xb9c,1),(0xc8c,4),(0xc90,4),(0xc94,4)),(hex(p),n)
  if off in (0xa4,0xb98):self.trace+=['P',str(off),str(self.handle(v))]
  else:self.trace+=['S',str(off),str(n),str(self.signed(v) if n==4 else v&255)]
  self.expected[p-BASE:p-BASE+n]=(v&((1<<(n*8))-1)).to_bytes(n,'little');self.counts['stores']+=1
 def run(self,f):
  op,self.mode,theater,p,secondary,owned,dp,ds,b9c,f1351,c137c,start,count,duration,self.first,self.second,frames,repeat,bits,name=f
  self.trace=[];self.mutated=False;self.u.mem_write(BASE,b'\x5a'*SIZE)
  for off,v in ((0xa4,IMAGES[p]),(0xb98,IMAGES[secondary]),(0x137c,c137c),(0xc8c,start),(0xc90,count),(0xc94,duration)):self.put(TYPE+off,v)
  for off,v in ((0xa8,owned),(0x13e0,dp),(0x13e1,ds),(0xb9c,b9c),(0x1351,f1351)):self.u.mem_write(TYPE+off,bytes([v]))
  self.u.mem_write(TYPE+0x13eb,name.encode()+b'\0');self.u.mem_write(TYPE+0xbf4,name.encode()+b'\0');self.put(SCENARIO+0x838,theater);self.put(0xa3d290,SCENARIO);self.put(0x839848,RULES);self.u.mem_write(RULES+0x1178,struct.pack('<Q',bits))
  for image in IMAGES[1:]:self.u.mem_write(image+6,struct.pack('<h',frames))
  self.expected=bytearray(self.u.mem_read(BASE,SIZE));allowed=[(TYPE+off,n) for off,n in ((0xa4,4),(0xb98,4),(0xa8,1),(0xb9c,1),(0xc8c,4),(0xc90,4),(0xc94,4))]
  for _ in range(repeat):
   self.files={};self.loads=0;self.active=True
   try:self.checked_call(0x458ce0 if op==0 else 0x45e790,ecx=TYPE,writes=allowed,inputs=[*RANGES.items(),(0x79b608,8),(0x79abac,312),(0x7ced14,5)])
   finally:self.active=False
   self.trace+=['R',str(self.handle(self.u.reg_read(UC_X86_REG_EAX)))];assert self.u.mem_read(BASE,SIZE)==self.expected,'Unrelated Building image arena bytes changed'
  self.trace+=['F',str(self.handle(self.word(TYPE+0xa4))),str(self.handle(self.word(TYPE+0xb98))),str(self.u.mem_read(TYPE+0xa8,1)[0]),str(self.u.mem_read(TYPE+0xb9c,1)[0]),str(self.u.mem_read(TYPE+0x1351,1)[0]),str(self.signed(self.word(TYPE+0x137c))),str(self.signed(self.word(TYPE+0xc8c))),str(self.signed(self.word(TYPE+0xc90))),str(self.signed(self.word(TYPE+0xc94)))]
  return self.trace
