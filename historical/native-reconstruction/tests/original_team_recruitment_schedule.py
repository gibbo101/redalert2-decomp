# SPDX-License-Identifier: GPL-3.0-or-later
"""Initial pre-ready Team AI: actual readiness/sum/House/member/null continuation."""
from collections import Counter
from original_presentation import PresentationOracle,STOP
from verify_team_recruitment_schedule import RANGES,SERVICES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EIP
BASE=0x5800000;SIZE=0x10000;TEAM=BASE+0x1000;TYPE=BASE+0x2000;TASK=BASE+0x3000;FOOT=BASE+0x4000;HOUSE=BASE+0x5000;RULES=BASE+0x6000;ANCHOR=BASE+0x8000;VT=BASE+0x9000;TVT=BASE+0xa000
class TeamRecruitmentScheduleOracle(PresentationOracle):
 def __init__(self,exe):
  super().__init__(exe,allow_patched=True);self.u.mem_map(BASE,SIZE);self.active=False;self.counts=Counter();self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.write)
 def va(self,a):return a
 def word(self,a):return int.from_bytes(self.u.mem_read(a,4),'little')
 def signed(self,a):return (self.word(a)+2**31)%2**32-2**31
 def event(self,k,a=0,b=0,c=0,d=0,e=0):self.trace.extend(map(str,(k,a,b,c,d,e)))
 def supplied(self,off,v,n=4):
  a=TEAM+off;raw=(v&((1<<(8*n))-1)).to_bytes(n,'little');self.u.mem_write(a,raw);self.expected[a-BASE:a-BASE+n]=raw
  self.event(1,off,int(bool(v)) if off in (0x34,0x38,0x54) else v&0xffffffff)
 def ret(self,sp,n,v=0):
  self.u.reg_write(UC_X86_REG_EAX,v&0xffffffff);self.u.reg_write(UC_X86_REG_EIP,self.word(sp));self.u.reg_write(UC_X86_REG_ESP,sp+4+n)
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  assert a in SERVICES or any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected Team AI instruction',hex(a))
  # These entries change the admitted path. Refuse rather than completing an
  # interior loop while omitting active Script/commands or empty expiration.
  assert a not in (0x6b7b28,0x6b7b4b,0x6b7c60,0x6ba1d1),('Unjoined Team AI path',hex(a))
  if a in RANGES:self.counts[hex(a)]+=1
  sp=u.reg_read(UC_X86_REG_ESP);ecx=u.reg_read(UC_X86_REG_ECX);f=self.f
  if a==0x6b8bb0:assert ecx==TEAM;self.event(8)
  if a==0x4f52f0:assert ecx==HOUSE;self.event(4)
  if a==0x6d6e00:assert ecx==FOOT;self.memberCalls+=1;self.event(5)
  if a==0x6ba1a0:assert ecx==TEAM;self.event(6)
  if a==0x6b9610:
   assert ecx==TEAM and [self.word(sp+4+i*4) for i in range(2)]==[TEAM+0x34,TEAM+0x38];self.anchorCalls+=1;self.event(2)
   head=self.word(TEAM+0x54);self.supplied(0x34,ANCHOR if head else 0);self.supplied(0x38,head);self.ret(sp,8)
  elif a==0x6b91c0:
   assert ecx==TEAM;slot=self.word(sp+4);assert 0<=slot<6;self.recruitCalls+=1;self.event(3,slot)
   if f[18]:
    self.supplied(0x84+4*slot,self.word(TEAM+0x84+4*slot)+1);self.supplied(0x48,self.word(TEAM+0x48)+1);self.supplied(0x54,FOOT);self.supplied(0x7e,1,1);self.supplied(0x7d,1,1)
   if not self.mutated and f[20]:
    self.mutated=True;count=0 if f[20]==1 else 1 if f[20]==2 else 6;self.put(TASK+0x9c,count);self.expected[TASK+0x9c-BASE:TASK+0xa0-BASE]=count.to_bytes(4,'little');self.event(9,count)
   self.ret(sp,4,f[18])
  elif a==SERVICES[2]:assert ecx==TEAM and self.word(sp+4)==1;self.destroyed+=1;self.event(7,1);self.ret(sp,4)
 def write(self,u,access,a,n,v,_):
  if not self.active or not BASE<=a<BASE+SIZE:return
  assert TEAM<=a<a+n<=TEAM+156,('Unexpected Team AI store',hex(a),n)
  off=a-TEAM;assert (n==1 and 0x74<=off<0x84) or (n==4 and off in (0x34,0x40));v&=(1<<(8*n))-1
  self.event(1,off,int(bool(v)) if off==0x34 else v);self.expected[a-BASE:a-BASE+n]=v.to_bytes(n,'little')
 def run(self,f):
  self.f=f;self.trace=[];self.anchorCalls=0;self.recruitCalls=0;self.memberCalls=0;self.destroyed=0;self.mutated=False;u=self.u;u.mem_write(BASE,b'\x5a'*SIZE)
  self.put(TEAM,TVT);self.put(TVT+0x20,SERVICES[2]);self.put(TEAM+0x24,TYPE);self.put(TEAM+0x2c,HOUSE);self.put(TYPE+0xdc,TASK);self.put(FOOT,VT);self.put(VT+0x1c0,0x6d6e00)
  for off,v in ((0x48,f[0]),(0x54,FOOT if f[1] else 0),(0x34,ANCHOR if f[2] else 0),(0x38,FOOT if f[2] else 0),(0x64,f[8]),(0x6c,f[9]),(0x50,f[10]),(0x3c,f[23]),(0x40,0)):self.put(TEAM+off,v)
  u.mem_write(TEAM+0x74,bytes(16))
  for off,index in ((0x7d,3),(0x78,4),(0x7a,5),(0x7b,6),(0x82,7)):u.mem_write(TEAM+off,bytes([f[index]]))
  self.put(TASK+0x9c,f[13]);u.mem_write(TYPE+0xab,b'\0');u.mem_write(TYPE+0xa7,b'\0');u.mem_write(FOOT+0x205,bytes([f[19]]))
  for i in range(6):self.put(TEAM+0x84+4*i,f[14]);self.put(TASK+0xa4+8*i,f[15])
  u.mem_write(HOUSE+0x134,bytes([f[16],f[17]]));self.put(0xa40d2c,f[11]);self.put(0xa3d298,f[12]);self.put(0x839848,RULES);self.put(RULES+0xe68,f[21]);self.put(0xac0050,0x7fff7fff)
  self.expected=bytearray(u.mem_read(BASE,SIZE));self.active=True
  try:self.checked_call(0x6ba1a0 if f[22] else 0x6b7ad0,[],TEAM,writes=[(TEAM,156),(TASK+0x9c,4)],inputs=[*RANGES.items(),(TYPE,0xe0),(FOOT,0x600),(VT,0x1c4),(TVT,0x24),(HOUSE,0x136),(RULES,0xe6c)])
  finally:self.active=False
  assert bytes(u.mem_read(BASE,SIZE))==self.expected,'Unrelated Team AI arena changed'
  final=[self.word(TEAM+0x48),int(bool(self.word(TEAM+0x54))),int(bool(self.word(TEAM+0x34))),int(bool(self.word(TEAM+0x38))),self.word(TEAM+0x40),self.anchorCalls,self.recruitCalls,self.memberCalls,self.destroyed,self.signed(TASK+0x9c),*u.mem_read(TEAM+0x74,16),*[self.word(TEAM+0x84+4*i) for i in range(6)]]
  return self.trace+['F',*map(str,final)]
