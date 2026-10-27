# SPDX-License-Identifier: GPL-3.0-or-later
"""Full original constructor, selected registration suffix comparison only."""
import struct
from collections import Counter
from original_presentation import PresentationOracle,STOP
from verify_house_country_registration import RANGES,REG,SERVICES,BASE_SERVICE,RESIZE
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EIP
BASE=0x5f00000;SIZE=0x20000;RECORD=BASE+0x1000;SLOTS=BASE+0x3000;ALT=BASE+0x4000;VT=BASE+0x5000;NAME=BASE+0x6000
PRIOR=(BASE+0x7000,BASE+0x7100,BASE+0x7200)
class HouseCountryRegistrationOracle(PresentationOracle):
 def __init__(self,exe):
  super().__init__(exe,allow_patched=True);self.u.mem_map(BASE,SIZE);self.active=False;self.counts=Counter();self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.write)
 def va(self,a):return a
 def word(self,p):return int.from_bytes(self.u.mem_read(p,4),'little')
 def pid(self,p):
  values=(0,RECORD,*PRIOR)
  assert p in values,hex(p)
  return values.index(p)
 def event(self,k,a=0,b=0,c=0,d=0):self.trace.extend(map(str,(k,a&0xffffffff,b&0xffffffff,c&0xffffffff,d&0xffffffff)))
 def ret(self,sp,n,value):
  self.u.reg_write(UC_X86_REG_EAX,value&0xffffffff);self.u.reg_write(UC_X86_REG_EIP,self.word(sp));self.u.reg_write(UC_X86_REG_ESP,sp+4+n)
 def fixture(self,p,v):
  self.put(p,v)
  if BASE<=p<BASE+SIZE:self.expected[p-BASE:p-BASE+4]=(v&0xffffffff).to_bytes(4,'little')
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  assert a in SERVICES or any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected country constructor instruction',hex(a))
  if a in RANGES:self.counts[hex(a)]+=1
  sp=u.reg_read(UC_X86_REG_ESP);ecx=u.reg_read(UC_X86_REG_ECX)
  if a==0x4f9298:self.suffix=True
  if a==BASE_SERVICE:
   assert ecx==RECORD and self.word(sp+4)==NAME
   self.ret(sp,4,RECORD) # Explicit supplied AbstractType base, no prefix claim.
  elif a==RESIZE:
   assert ecx==REG and self.word(sp+8)==0
   cap=self.word(sp+4);self.event(2,cap,self.f[4],self.f[5],self.f[6]&0xffffffff)
   if self.f[5]:
    raw=bytes(u.mem_read(self.word(REG+4),32));u.mem_write(ALT,raw);self.expected[ALT-BASE:ALT-BASE+32]=raw;self.fixture(REG+4,ALT)
   if self.f[6]>=0:self.fixture(REG+16,self.f[6])
   # The supplied resize can replace backing/count even on low-byte failure.
   if self.f[4]&255:self.fixture(REG+8,cap)
   self.ret(sp,8,self.f[4])
 def write(self,u,access,p,n,v,_):
  if not self.active:return
  value=v&((1<<(8*n))-1)
  if BASE<=p and p+n<=BASE+SIZE:self.expected[p-BASE:p-BASE+n]=value.to_bytes(n,'little')
  if not self.suffix:return
  if p==REG+16:self.event(1,2,16,value)
  elif p in (RECORD+0xb8,RECORD+0xb4):self.event(1,1,p-RECORD,value)
  elif SLOTS<=p<SLOTS+32 or ALT<=p<ALT+32:
   backing=SLOTS if p<ALT else ALT;self.event(1,2,0x1000+p-backing,0,self.pid(value))
 def run(self,f):
  self.f=f;u=self.u;u.mem_write(BASE,b'\x5a'*SIZE);u.mem_write(NAME,b'Player\0');self.put(VT+8,RESIZE);self.put(0xa3d290,0)
  for off,v in ((0,VT),(4,SLOTS),(8,f[1]),(16,f[0]),(20,f[3])):self.put(REG+off,v)
  u.mem_write(REG+13,bytes([f[2]]))
  vals=[PRIOR[i%3] for i in range(8)]
  if f[7]>=0:vals[f[7]]=RECORD
  u.mem_write(SLOTS,struct.pack('<8I',*vals));u.mem_write(ALT,b'\0'*32)
  self.expected=bytearray(u.mem_read(BASE,SIZE));self.trace=[];self.suffix=False;self.active=True
  try:self.checked_call(0x4f90f0,[NAME],RECORD,writes=[(RECORD,0x1b0),(SLOTS,32),(ALT,32),(REG+4,20)],inputs=[*RANGES.items(),(VT,16),(NAME,7),(0xa3d290,4)])
  finally:self.active=False
  assert bytes(u.mem_read(BASE,SIZE))==self.expected,'Unrelated country arena changed'
  assert u.reg_read(UC_X86_REG_EAX)==RECORD
  b=self.word(REG+4)
  return self.trace+['F',*map(str,(self.word(RECORD+0xb8),self.word(RECORD+0xb4),self.word(REG+16),self.word(REG+8),int(b==ALT),*[self.pid(self.word(b+4*i)) for i in range(8)]))]
