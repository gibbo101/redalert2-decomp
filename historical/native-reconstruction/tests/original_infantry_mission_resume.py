# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete resume roots; explicit supplied named children, never an original Walk proof."""
from collections import Counter
from original_presentation import PresentationOracle,STOP
from verify_infantry_mission_resume import RANGES,SERVICES,verify
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EIP
BASE=0x5f00000;SIZE=0x20000;ACTOR=BASE;VT=BASE+0x1000;TYPE=BASE+0x2000;HOUSE=BASE+0x4000;RULES=BASE+0x5000;TOKEN=BASE+0x7000;LOCO=BASE+0x7100
class InfantryMissionResumeOracle(PresentationOracle):
 def __init__(self,exe):
  verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(BASE,SIZE);self.u.mem_map(0x6000000,0x1000);self.active=False;self.counts=Counter();self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.write)
 def va(self,a):return a
 def word(self,a):return int.from_bytes(self.u.mem_read(a,4),'little')
 def event(self,k,x=0,y=0):self.trace.extend(map(str,(k,x&0xffffffff,y&0xffffffff)))
 def fixture(self,a,v):
  self.put(a,v)
  if BASE<=a<BASE+SIZE:self.expected[a-BASE:a-BASE+4]=(v&0xffffffff).to_bytes(4,'little')
 def ret(self,sp,n,v=0):
  self.u.reg_write(UC_X86_REG_EAX,v&0xffffffff);self.u.reg_write(UC_X86_REG_EIP,self.word(sp));self.u.reg_write(UC_X86_REG_ESP,sp+4+n)
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  assert a in SERVICES or any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),hex(a)
  if a in SERVICES or a in RANGES:self.counts[hex(a)]+=1
  sp=u.reg_read(UC_X86_REG_ESP);ecx=u.reg_read(UC_X86_REG_ECX);f=self.f
  if a==0x4c6f10:
   assert ecx==ACTOR and self.word(sp+4)==0 and self.word(sp+8)==f[8]&0xffffffff;self.event(2,0,f[8])
   if f[0]==3:self.ret(sp,8,0x123480ff)
  elif a==0x6d48f0:
   if f[0]!=2:self.event(3)
  elif a==0x4cdd70:self.event(4,self.word(ACTOR+0x4b4))
  elif a==0x6d1460:self.event(5,1)
  elif a==0x615360:assert not self.word(ACTOR+0x408);self.event(6)
  elif a==0x454c70:
   assert self.word(self.word(sp+4))==LOCO and not self.word(ecx);self.event(7);self.ret(sp,4,0x80004002)
  elif a==0x6000100:
   assert self.word(sp+4)==0 and self.word(sp+8)==0;self.event(8);self.ret(sp,8)
  elif a==0x4cdaa0:self.event(9,int(self.word(ACTOR+0x4b4)!=0xffffffff))
  elif a==0x594770:
   m=self.word(ACTOR+0x98);value=self.word(ACTOR+0xa0) if m==0xffffffff else m;self.event(10,value);self.queries+=1
   if f[22]==1 and self.queries==2:
    # Return the queried pre-mutation value while updating the live raw field.
    self.fixture(ACTOR+0x98,8);self.ret(sp,0,value)
  elif a==0x4c8b00:
   self.event(11)
   if f[22]==2:self.fixture(ACTOR+0x494,TOKEN)
   self.ret(sp,0)
  elif a==0x5950d0:
   # The two parent reads query5950D0 independently at known call sites.
   off=5 if self.word(sp)==0x503cfc else 7;raw=self.word(ACTOR+0x98);self.event(12,raw,off)
   if f[22]==3 and off==5:
    self.fixture(ACTOR+0x98,11);self.ret(sp,0,0xa403b0+((raw<<5)&0xffffffff))
  elif a==0x4f52f0:assert ecx==HOUSE;self.event(13,f[12]);self.ret(sp,0,f[12])
  elif a==0x503d3e:self.event(14,self.word(HOUSE+0x194))
  elif a==0x503d44:self.event(15,self.word(RULES+0x10a8))
  elif a==0x6000110:self.event(16,f[15]);self.ret(sp,0,f[15])
  elif a in (0x503d72,0x503d7c,0x503da9):
   off={0x503d72:0xc11,0x503d7c:0xc14,0x503da9:0xb00}[a];self.event(17,off,u.mem_read(TYPE+off,1)[0])
  elif a==0x6d7910:
   assert self.word(sp+4)==16;self.event(18,16,f[18])
   if f[22]==4:self.fixture(ACTOR+0x4c4,0)
   self.ret(sp,4,f[18])
  elif a==0x6000120:
   m=self.word(sp+4);flag=self.word(sp+8);assert flag==0;self.event(19,m,flag);self.chosen=m;self.ret(sp,8)
 def write(self,u,access,p,n,v,_):
  if not self.active:return
  if BASE<=p<p+n<=BASE+SIZE:
   assert p==ACTOR+0x59d and n==1
   self.expected[p-BASE:p-BASE+n]=bytes([v]);self.event(1,0x59d,v)
 def run(self,f):
  self.f=f;u=self.u;u.mem_write(BASE,b'\x5a'*SIZE)
  for off,v in ((0x2c,0x509800),(0x438,0x4cdaa0),(0x16c,0x594770),(0x45c,0x4cdd70),(0x3c8,0x6d1460),(0x4c8,0x6000100),(0x28c,0x6000110),(0x1d0,0x6000120)):self.put(VT+off,v)
  for off,v in ((0,VT),(0x98,f[1]),(0xa0,f[2]),(0x4b4,f[3]),(0x488,f[5]),(0xa8,f[6]),(0x418,f[7]),(0x228,TOKEN if f[9] else 0),(0x494,TOKEN if f[10] else 0),(0x4c4,TOKEN if f[11] else 0),(0x1b4,HOUSE),(0x5a8,TYPE),(0x408,0),(0x564,LOCO),(0x1b0,0)):self.put(ACTOR+off,v)
  u.mem_write(ACTOR+0x59d,bytes([f[4]]));u.mem_write(ACTOR+0x577,b'\0');self.put(HOUSE+0x194,f[13]);self.put(RULES+0x10a8,f[14]);self.put(0x839848,RULES)
  for off,v in ((0xc11,f[16]),(0xc14,f[17]),(0xb00,f[19])):u.mem_write(TYPE+off,bytes([v]))
  for m in range(-1,29):
   u.mem_write(0xa403b0+m*32+5,bytes([f[20]]));u.mem_write(0xa403b0+m*32+7,bytes([f[21]]))
  self.expected=bytearray(u.mem_read(BASE,SIZE));self.trace=[];self.chosen=-999;self.queries=0;self.active=True
  root=0x6d48f0 if f[0]==2 else 0x4c6f10 if f[0]==1 else 0x503c00
  try:self.checked_call(root,[0,f[8]],ACTOR,writes=[(ACTOR+0x59d,1)],inputs=[*RANGES.items(),(VT,0x500),(TYPE,0xd00),(HOUSE,0x200),(RULES,0x1200),(0x839848,4),(0xa40390,30*32)])
  finally:self.active=False
  assert bytes(u.mem_read(BASE,SIZE))==self.expected,'Unrelated resume arena changed'
  return self.trace+['F',str(u.reg_read(UC_X86_REG_EAX)&255),str(u.mem_read(ACTOR+0x59d,1)[0]),str(self.word(ACTOR+0x98)),str(self.chosen&0xffffffff),str(int(bool(self.word(ACTOR+0x494)))),str(int(bool(self.word(ACTOR+0x4c4))))]
