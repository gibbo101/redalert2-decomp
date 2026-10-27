# SPDX-License-Identifier: GPL-3.0-or-later
"""Unchanged complete6B8DC0, with explicitly supplied child queries and mutations."""
from collections import Counter
from original_presentation import PresentationOracle,STOP
from verify_team_admission import RANGES,SERVICES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EIP
BASE=0x5400000;SIZE=0x10000;TEAM=BASE+0x1000;OLD=BASE+0x1200;FOOT=BASE+0x2000;TYPE=BASE+0x3000;OLDTYPE=BASE+0x3200;TASK=BASE+0x4000;AIR=BASE+0x5000;SCRIPT=BASE+0x6000;SCRATCH=BASE+0x6200;OUT=BASE+0x7000;VT=BASE+0x8000;HOUSE=BASE+0x9000;FOREIGN=BASE+0x9200;WANTED=BASE+0x9400;OTHER=BASE+0x9600
class TeamAdmissionOracle(PresentationOracle):
 def __init__(self,exe):
  super().__init__(exe,allow_patched=True);self.u.mem_map(BASE,SIZE);self.active=False;self.counts=Counter();self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.write)
 def va(self,a):return a
 def word(self,p):return int.from_bytes(self.u.mem_read(p,4),'little')
 def signed(self,p):return (self.word(p)+2**31)%2**32-2**31
 def event(self,k,v):self.trace.extend(map(str,(k,v)))
 def supplied(self,p,v,n=4):
  raw=(v&((1<<(8*n))-1)).to_bytes(n,'little');self.u.mem_write(p,raw);self.expected[p-BASE:p-BASE+n]=raw
 def mutate(self,where):
  if self.mutated or self.f[26]!=where:return
  self.mutated=1;self.event(12,where)
  if where==1:self.supplied(FOOT+0x6c,0);self.supplied(TYPE+0xa9,128,1);self.supplied(FOOT+0x37a,1,1)
  if where==2:self.supplied(TASK+0x9c,2);self.supplied(TASK+0xa8,OTHER);self.supplied(TASK+0xb0,WANTED)
  if where==3:self.supplied(FOOT+0x4c4,OLD);self.supplied(OLDTYPE+0xb4,self.f[19])
  if where==4:self.supplied(TASK+0xa4,self.f[25]+1);self.supplied(TEAM+0x84,self.f[24]+1)
 def ret(self,sp,n,v):
  self.u.reg_write(UC_X86_REG_EAX,v&0xffffffff);self.u.reg_write(UC_X86_REG_EIP,self.word(sp));self.u.reg_write(UC_X86_REG_ESP,sp+4+n)
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  assert a in SERVICES or any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected admission instruction',hex(a))
  if a in RANGES:self.counts[hex(a)]+=1;return
  if a==0x6b8eea:self.event(7,self.signed(OLDTYPE+0xb4))
  if a not in SERVICES:return
  sp=u.reg_read(UC_X86_REG_ESP);ecx=u.reg_read(UC_X86_REG_ECX);self.counts['supplied.'+hex(a)]+=1;f=self.f
  if a==0x636f10:assert ecx==FOOT;self.event(1,f[6]);self.mutate(1);self.ret(sp,0,f[6])
  elif a==SERVICES[3]:assert ecx==FOOT;self.kinds+=1;self.event(2,f[7]);self.ret(sp,0,f[7])
  elif a==SERVICES[4]:
   assert ecx==FOOT;value=f[10] if self.missions else f[9];self.missions+=1;self.event(3,value);self.ret(sp,0,value)
  elif a==0x594db0:self.event(4,(ecx+2**31)%2**32-2**31);self.event(5,f[11]);self.ret(sp,0,f[11])
  elif a==0x668870:
   assert ecx==SCRIPT;self.event(6,f[15]);self.mutate(3);self.supplied(SCRATCH,f[15]);self.ret(sp,4,SCRATCH)
  elif a==SERVICES[5]:
   assert ecx==FOOT;self.event(10,1);self.mutate(2);self.mutate(4);self.ret(sp,0,WANTED)
  elif a==SERVICES[6]:
   assert ecx==FOOT;self.event(8,self.word(sp+4));self.event(9,f[20]);self.supplied(SCRATCH,f[20]);self.ret(sp,4,SCRATCH)
 def write(self,u,access,p,n,v,_):
  if not self.active or not BASE<=p<BASE+SIZE:return
  assert p==OUT and n==4,('Unexpected admission arena store',hex(p),n)
  self.event(11,(v+2**31)%2**32-2**31);self.expected[p-BASE:p-BASE+n]=(v&0xffffffff).to_bytes(4,'little')
 def run(self,f):
  self.f=f;self.trace=[];self.kinds=0;self.missions=0;self.mutated=0;u=self.u;u.mem_write(BASE,b'\x5a'*SIZE)
  for p,v in ((TEAM+0x24,TYPE),(TEAM+0x28,SCRIPT if f[14] else 0),(TEAM+0x2c,HOUSE),(OLD+0x24,OLDTYPE),(OLDTYPE+0xb4,f[18]),(FOOT,VT),(FOOT+0x4c4,TEAM if f[0] else OLD if f[17] else 0),(FOOT+0x6c,f[2]),(FOOT+0x1b4,HOUSE if f[5] else FOREIGN),(FOOT+0x5ac,AIR),(FOOT+0x254,f[21]),(TYPE+0xb4,f[19]),(TYPE+0xdc,TASK),(TASK+0x9c,f[22]),(OUT,0x12345678),(VT+0x2c,SERVICES[3]),(VT+0x16c,SERVICES[4]),(VT+0x84,SERVICES[5]),(VT+0x39c,SERVICES[6])):self.put(p,v)
  for p,v in ((FOOT+0x7d,f[1]),(FOOT+0x76,f[4]),(FOOT+0x379,f[12]),(FOOT+0x37a,f[16]),(AIR+0xba3,f[8]),(TYPE+0xa9,f[13])):u.mem_write(p,bytes([v]))
  for i in range(6):self.put(TASK+0xa4+i*8,f[25]);self.put(TASK+0xa8+i*8,WANTED if i==f[23] else OTHER);self.put(TEAM+0x84+i*4,f[24])
  self.put(0xa40774,f[3]);self.expected=bytearray(u.mem_read(BASE,SIZE));self.active=True
  try:self.checked_call(0x6b8dc0,[FOOT,OUT],TEAM,writes=[(OUT,4)],inputs=[*RANGES.items(),(VT,0x3a0),(0xa40774,4)])
  finally:self.active=False
  assert bytes(u.mem_read(BASE,SIZE))==self.expected,'Unrelated admission arena changed'
  # Priority comparison is inline; synthesize only its read observation in the
  # trace at the actual branch entry (handled below), never execute a replacement.
  result=u.reg_read(UC_X86_REG_EAX)&255
  prior=self.word(FOOT+0x4c4)
  final=[result,self.signed(OUT),self.kinds,self.missions,self.mutated,self.signed(TASK+0x9c),*u.mem_read(TYPE+0xa9,1),self.signed(FOOT+0x6c),*u.mem_read(FOOT+0x37a,1),self.signed(OLDTYPE+0xb4),1 if prior==TEAM else 2 if prior==OLD else 0,self.signed(TASK+0xa4),self.word(TEAM+0x84)]
  return self.trace+['F',*map(str,final)]
