# SPDX-License-Identifier: GPL-3.0-or-later
"""Unchanged complete E1 discovery -> Tag -> Trigger -> event7 mismatch."""
from collections import Counter
from original_presentation import PresentationOracle,STOP
from verify_tagged_infantry_discovery import RANGES,TABLES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP
BASE=0x5d00000;SIZE=0x30000;HOUSES=(BASE+0x1000,BASE+0x7000);ACTOR=BASE+0xe000
TAG=BASE+0x13000;TAGTYPE=BASE+0x14000;TRIGGER=BASE+0x15000;TRIGGERTYPE=BASE+0x16000;EVENT=BASE+0x17000;COUNTRY=BASE+0x18000;COUNTRIES=(BASE+0x19000,BASE+0x19200);SLOTS=BASE+0x1a000
class TaggedInfantryDiscoveryOracle(PresentationOracle):
 def __init__(self,exe):
  super().__init__(exe,allow_patched=True);self.u.mem_map(BASE,SIZE);self.active=False;self.counts=Counter();self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.write)
 def va(self,a):return a
 def word(self,p):return int.from_bytes(self.u.mem_read(p,4),'little')
 def event(self,k,a=0,b=0,c=0,d=0,e=0):self.trace.extend(str(v&0xffffffff) for v in (k,a,b,c,d,e))
 def hid(self,p):return 0 if not p else HOUSES.index(p)+1
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  assert any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected tagged discovery',hex(a))
  assert a not in (0x6ed830,0x6ed990,0x5d4430,0x47a460),'Mismatched event must not fire/destroy/detach'
  if a in RANGES:self.counts[hex(a)]+=1
  ecx=u.reg_read(UC_X86_REG_ECX);sp=u.reg_read(UC_X86_REG_ESP);arg=lambda i:self.word(sp+4+4*i)
  if a in (0x6c2440,0x5d4230):assert ecx==ACTOR;self.event(1 if a==0x6c2440 else 2,self.hid(arg(0)))
  elif a==0x4f52f0:self.event(3,self.hid(ecx))
  elif a==0x594770:assert ecx==ACTOR;self.event(4)
  elif a==0x594cb0:assert ecx==ACTOR and arg(1)==0;self.event(9,arg(0))
  elif a==0x6b3df0:assert ecx==TAG and [arg(i) for i in range(5)]==[4,ACTOR,0x7fff7fff,0,0];self.event(5,4)
  elif a==0x6ed740:assert ecx==TRIGGER
  elif a==0x4ed760:assert ecx==(self.f[18]&0xffffffff);self.event(7,ecx)
  elif a==0x6e6050:
   resolved=HOUSES[0] if self.f[18]==13 else HOUSES[1] if self.f[18]==19 else 0
   assert ecx==EVENT and [arg(i) for i in range(4)]==[4,resolved,ACTOR,TRIGGER+0x30] and arg(5)==0;self.event(8,4)
 def write(self,u,access,p,n,v,_):
  if not self.active:return
  value=v&((1<<(8*n))-1);subject=None;off=0
  if p==TAG+0x35:assert n==1;subject=30;off=0x35
  elif p in (ACTOR+0x373,ACTOR+0x374,ACTOR+0xa0,ACTOR+0xa4):assert n==(4 if p==ACTOR+0xa0 else 1);subject=0;off=p-ACTOR
  for i,h in enumerate(HOUSES):
   if p in (h+0x13c,h+0x5668,h+0x5669):assert n==1;subject=i+1;off=p-h
  if subject is None:
   assert not BASE<=p<p+n<=BASE+SIZE,('Unexpected tagged discovery store',hex(p),n)
   return
  self.event(6,subject,off,value);self.expected[p-BASE:p-BASE+n]=value.to_bytes(n,'little')
 def run(self,f):
  self.f=f;u=self.u;u.mem_write(BASE,b'\x5a'*SIZE)
  self.put(ACTOR,0x7a3540);self.put(ACTOR+0x1b4,HOUSES[f[3]]);self.put(ACTOR+0x34,TAG if f[11] else 0);u.mem_write(ACTOR+0x372,bytes(f[5:8]));self.put(ACTOR+0x98,f[8]);self.put(ACTOR+0xa0,f[9]);u.mem_write(ACTOR+0xa4,bytes([f[10]]))
  for i,h in enumerate(HOUSES):
   self.put(h+0x34,COUNTRIES[i]);self.put(COUNTRIES[i]+0xb8,13+6*i);self.put(SLOTS+4*i,h);u.mem_write(h+0x134,bytes(f[16:18]));u.mem_write(h+0x13c,b'\x80');u.mem_write(h+0x5668,b'\x81\x82')
  self.put(TAG+0x24,TAGTYPE);self.put(TAGTYPE+0x9c,f[15]);self.put(TAG+0x28,TRIGGER);self.put(TAG+0x2c,4);u.mem_write(TAG+0x35,bytes([f[12]]))
  self.put(TRIGGER+0x24,TRIGGERTYPE);self.put(TRIGGER+0x28,0);u.mem_write(TRIGGER+0x40,bytes([f[13]]));u.mem_write(TRIGGER+0x2c,bytes([f[14]]));self.put(TRIGGER+0x3c,0);self.put(TRIGGER+0x30,-1);self.put(TRIGGER+0x34,-91);self.put(TRIGGER+0x38,0)
  self.put(TRIGGERTYPE+0xa4,COUNTRY);self.put(TRIGGERTYPE+0xac,EVENT);self.put(TRIGGERTYPE+0xb0,0);self.put(COUNTRY+0xb4,f[18]);self.put(EVENT+0x2c,7);self.put(EVENT+0x34,1);self.put(EVENT+0x28,0)
  for p,v in ((0xa3229c,SLOTS),(0xa322a8,2),(0xac0148,0x7fff7fff),(0xa3d298,f[0]),(0xa40774,f[1]),(0xa35db4,HOUSES[f[2]])):self.put(p,v)
  u.mem_write(0xa40d13,b'\0');self.trace=[];self.expected=bytearray(u.mem_read(BASE,SIZE));self.active=True
  try:
   for _ in range(2):
    self.checked_call(0x6c2440,[0 if f[4]==-1 else HOUSES[f[4]]],ACTOR,writes=[(BASE,SIZE)],inputs=[*RANGES.items(),*TABLES.items(),(0x7a3540,0x1d4),*[(p,4) for p in (0xa3229c,0xa322a8,0xac0148,0xa3d298,0xa40774,0xa35db4)],(0xa40d13,1)])
    self.event(10,u.reg_read(UC_X86_REG_EAX)&255)
  finally:self.active=False
  assert bytes(u.mem_read(BASE,SIZE))==self.expected,'Unrelated tagged discovery owner changed'
  final=[*u.mem_read(ACTOR+0x373,2),self.word(ACTOR+0xa0),u.mem_read(ACTOR+0xa4,1)[0]]
  for h in HOUSES:final.extend((u.mem_read(h+0x13c,1)[0],*u.mem_read(h+0x5668,2)))
  final.extend((u.mem_read(TAG+0x35,1)[0],self.word(TAG+0x2c),self.word(TRIGGER+0x3c)))
  return self.trace+['F',*map(str,final)]
