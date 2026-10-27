# SPDX-License-Identifier: GPL-3.0-or-later
"""Actual unchanged Walk query/predicate/reference/zero-percentage under full resume roots."""
import struct
from original_infantry_mission_resume import InfantryMissionResumeOracle,BASE,SIZE,ACTOR,VT,TYPE,HOUSE,RULES,TOKEN
from original_presentation import STOP
from verify_infantry_mission_resume import RANGES as PARENTS
from verify_walk_mission_resume import verify,RANGES,TABLES,SERVICES
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP
WALK=BASE+0x8000;EXTRA={a:n for a,n in RANGES.items() if a not in PARENTS}
class WalkMissionResumeOracle(InfantryMissionResumeOracle):
 def __init__(self,exe):
  verify(exe.read_bytes());super().__init__(exe);self.u.mem_map(0x3c7000,0x1000)
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  assert a in SERVICES or any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),hex(a)
  if a in EXTRA:self.counts[hex(a)]+=1
  sp=u.reg_read(UC_X86_REG_ESP)
  if a in (0x3c7594,0x3c757c):
   assert self.word(sp+4)==WALK+0x14;v=self.word(WALK+0x14)+(1 if a==0x3c7594 else -1);assert 0<v<0x80000000
   self.fixture(WALK+0x14,v);self.event(21,0,v);self.ret(sp,4,v);return
  if a==0x454c70:
   assert self.word(self.word(sp+4))==WALK+4 and not self.word(u.reg_read(UC_X86_REG_ECX));self.event(7)
  elif a==0x4c8b00:
   self.event(11)
   if self.f[22]==2:self.fixture(ACTOR+0x494,TOKEN)
  elif a==0x4c6f95:
   self.event(22,0,1)
   if self.f[28]==2:self.u.mem_write(WALK+0x34,b'\xff');self.expected[WALK+0x34-BASE]=255
  elif a==0x71dea0:self.event(23,0,u.mem_read(WALK+0x34,1)[0])
  elif a==0x71fbb3:self.event(24,0x38,int(bool(self.word(WALK+0x38))))
  elif a==0x71fbba:self.event(24,0x35,u.mem_read(WALK+0x35,1)[0])
  elif a==0x4c2df0:
   assert not self.word(sp+4) and not self.word(sp+8);self.event(8)
   if self.f[28]==3:self.fixture(0xa6eb14,self.word(0xa6eb14)+11);self.fixture(WALK+0x14,self.word(WALK+0x14)+7)
  elif a==0x4c2e33 and self.f[28]==1:self.fixture(ACTOR+0x468,0xabcdef01)
  if a in (0x4c6f95,) or any(lo<=a and a+n<=lo+size for lo,size in EXTRA.items()) or a in SERVICES and a not in (0x4c8b00,0x4f52f0,0x6d7910,0x6000110,0x6000120):return
  super().code(u,a,n,_)
 def write(self,u,access,p,n,v,_):
  if not self.active:return
  if p==0xa6eb14:
   assert n==4;self.event(20,0,v);self.expectedGlobal=v&0xffffffff;return
  if p in (ACTOR+0x468,ACTOR+0x46c):
   assert n==4;self.expected[p-BASE:p-BASE+4]=(v&0xffffffff).to_bytes(4,'little');self.event(25,p-ACTOR,v);return
  super().write(u,access,p,n,v,_)
 def run(self,f):
  self.f=f;u=self.u;u.mem_write(BASE,b'\x5a'*SIZE)
  for off,v in ((0x2c,0x509800),(0x438,0x4cdaa0),(0x16c,0x594770),(0x45c,0x4cdd70),(0x3c8,0x6d1460),(0x4c8,0x4c2df0),(0x28c,0x6000110),(0x1d0,0x6000120)):self.put(VT+off,v)
  for off,v in ((0,VT),(0x98,f[1]),(0xa0,f[2]),(0x4b4,f[3]),(0x488,f[5]),(0x4ac,0),(0xa8,f[6]),(0x418,f[7]),(0x228,TOKEN if f[9] else 0),(0x494,TOKEN if f[10] else 0),(0x4c4,TOKEN if f[11] else 0),(0x1b4,HOUSE),(0x5a8,TYPE),(0x408,0),(0x564,WALK+4),(0x1b0,0)):self.put(ACTOR+off,v)
  u.mem_write(ACTOR+0x59d,bytes([f[4]]));u.mem_write(ACTOR+0x577,b'\0');self.put(HOUSE+0x194,f[13]);self.put(RULES+0x10a8,f[14]);self.put(0x839848,RULES)
  for off,v in ((0xc11,f[16]),(0xc14,f[17]),(0xb00,f[19])):u.mem_write(TYPE+off,bytes([v]))
  for m in range(-1,29):
   u.mem_write(0xa403b0+m*32+5,bytes([f[20]]));u.mem_write(0xa403b0+m*32+7,bytes([f[21]]))
  for off,v in ((0,0x7aeba0),(4,0x7aead8),(0x18,0x7aeab4),(0x14,f[26]),(0x38,TOKEN if f[24] else 0)):self.put(WALK+off,v)
  u.mem_write(WALK+0x34,bytes([f[23]]));u.mem_write(WALK+0x35,bytes([f[25]]));self.put(0xa6eb14,f[27]);u.mem_write(ACTOR+0x468,struct.pack('<Q',0x3fe400001234abcd))
  self.expected=bytearray(u.mem_read(BASE,SIZE));self.expectedGlobal=f[27]&0xffffffff;self.trace=[];self.chosen=-999;self.queries=0;self.active=True
  root=0x71fba0 if f[0]==4 else 0x6d48f0 if f[0]==2 else 0x4c6f10 if f[0]==1 else 0x503c00
  args=[WALK+0x18] if f[0]==4 else [0,f[8]]
  try:self.checked_call(root,args,ACTOR,writes=[(ACTOR+0x59d,1),(ACTOR+0x468,8),(0xa6eb14,4)],inputs=[*RANGES.items(),*TABLES.items(),(VT,0x500),(TYPE,0xd00),(HOUSE,0x200),(RULES,0x1200),(0x839848,4),(0xa40390,30*32)])
  finally:self.active=False
  assert bytes(u.mem_read(BASE,SIZE))==self.expected,'Unrelated Walk resume arena changed'
  assert self.word(0xa6eb14)==self.expectedGlobal
  return self.trace+['F',str(u.reg_read(UC_X86_REG_EAX)&255),str(u.mem_read(ACTOR+0x59d,1)[0]),str(self.word(ACTOR+0x98)),str(self.chosen&0xffffffff),str(int(bool(self.word(ACTOR+0x494)))),str(int(bool(self.word(ACTOR+0x4c4)))),str(self.word(0xa6eb14)),str(self.word(WALK+0x14)),str(self.word(ACTOR+0x468)),str(self.word(ACTOR+0x46c)),str(u.mem_read(WALK+0x34,1)[0])]
