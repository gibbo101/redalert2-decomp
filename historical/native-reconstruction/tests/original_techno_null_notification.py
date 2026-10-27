# SPDX-License-Identifier: GPL-3.0-or-later
"""Unchanged null-attacker E1 -> actual Tag/Trigger/event7 mismatch -> map."""
from collections import Counter
from original_presentation import PresentationOracle,STOP
from verify_techno_null_notification import RANGES,TABLES,TYPE80,COST84,SERVICES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EIP
BASE=0x5d00000;SIZE=0x30000;HOUSES=(BASE+0x1000,BASE+0x7000);ACTOR=BASE+0xe000;TYPE=BASE+0xf000;VT=BASE+0x10000;TVT=BASE+0x11000
TAG=BASE+0x13000;TAGTYPE=BASE+0x14000;TRIGGER=BASE+0x15000;TRIGGERTYPE=BASE+0x16000;EVENT=BASE+0x17000;COUNTRY=BASE+0x18000;MAP=0x8324e0
class TechnoNullNotificationOracle(PresentationOracle):
 def __init__(self,exe):
  super().__init__(exe,allow_patched=True);self.u.mem_map(BASE,SIZE);self.active=False;self.counts=Counter();self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.write)
 def va(self,a):return a
 def word(self,p):return int.from_bytes(self.u.mem_read(p,4),'little')
 def event(self,k,a=0,b=0,c=0,d=0,e=0):self.trace.extend(str(v&0xffffffff) for v in (k,a,b,c,d,e))
 def ret(self,value=0,argc=0):
  u=self.u;sp=u.reg_read(UC_X86_REG_ESP);u.reg_write(UC_X86_REG_EAX,value&0xffffffff);u.reg_write(UC_X86_REG_EIP,self.word(sp));u.reg_write(UC_X86_REG_ESP,sp+4+argc*4)
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  assert a in SERVICES or any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected null notification',hex(a))
  assert a not in (0x6ed830,0x6ed990,0x5d4430,0x47a460),'Mismatched event must not fire/destroy/detach'
  if a in RANGES:self.counts[hex(a)]+=1
  ecx=u.reg_read(UC_X86_REG_ECX);sp=u.reg_read(UC_X86_REG_ESP);arg=lambda i:self.word(sp+4+4*i);f=self.f
  if a==TYPE80:assert ecx==ACTOR;self.event(1);self.ret(TYPE)
  elif a==COST84:assert ecx==TYPE and arg(0)==HOUSES[f[13]];self.event(2,f[13]+1);self.ret(f[12],1)
  elif a==0x509800:assert ecx==ACTOR;self.event(3)
  elif a==0x6b3df0:
   assert ecx==TAG and arg(0) in (48,29) and [arg(i) for i in range(1,5)]==[ACTOR,0x7fff7fff,0,0];self.event(4,arg(0))
  elif a==0x6ed740:assert ecx==TRIGGER
  elif a==0x4ed760:assert ecx==0xfffffff7;self.event(7,ecx)
  elif a==0x6e6050:
   assert ecx==EVENT;self.event(8,arg(0))
   if f[0]==0:assert arg(0) in (48,29) and arg(1)==0 and arg(2)==ACTOR and arg(3)==TRIGGER+0x30
   else:assert arg(0)==(f[12]&0xffffffff)
  elif a==0x6331a0:assert ecx==MAP;self.event(9)
  elif a==0x6331e0:assert ecx==MAP;self.event(10,arg(0))
 def write(self,u,access,p,n,v,_):
  if not self.active:return
  v&=(1<<(8*n))-1
  subject=None;off=0
  if p==TAG+0x35:assert n==1;subject=30;off=0x35
  for i,h in enumerate(HOUSES):
   if p==h+0x5360:assert n==4;subject=i+1;off=0x5360
  if p in (MAP+0x14d5,MAP+0x14d6):assert n==1;subject=40;off=p-MAP
  if subject is None:
   assert not BASE<=p<p+n<=BASE+SIZE and not MAP+0x14a8<=p<p+n<=MAP+0x14d8,('Unexpected null notification store',hex(p),n)
   return
  self.event(5,subject,off,v)
  for base,raw in self.expected.items():
   if base<=p<p+n<=base+len(raw):raw[p-base:p-base+n]=v.to_bytes(n,'little');return
  raise AssertionError('Store not owned')
 def run(self,f):
  self.f=f;u=self.u;u.mem_write(BASE,b'\x5a'*SIZE);u.mem_write(MAP+0x14a8,b'\xa5'*0x30)
  self.put(ACTOR,VT);self.put(VT+0x80,TYPE80);self.put(VT+0x2c,0x509800);self.put(TYPE,TVT);self.put(TVT+0x84,COST84);self.put(ACTOR+0x1b4,HOUSES[f[13]]);self.put(ACTOR+0x34,TAG if f[2] else 0);u.mem_write(ACTOR+0x7d,bytes([f[1]]))
  for h in HOUSES:self.put(h+0x5360,f[7])
  self.put(TAG+0x24,TAGTYPE);self.put(TAGTYPE+0x9c,f[6]);self.put(TAG+0x28,TRIGGER);self.put(TAG+0x2c,4);u.mem_write(TAG+0x35,bytes([f[3]]))
  self.put(TRIGGER+0x24,TRIGGERTYPE);self.put(TRIGGER+0x28,0);u.mem_write(TRIGGER+0x40,bytes([f[4]]));u.mem_write(TRIGGER+0x2c,bytes([f[5]]));self.put(TRIGGER+0x3c,0);self.put(TRIGGER+0x30,-1);self.put(TRIGGER+0x34,-91);self.put(TRIGGER+0x38,0)
  self.put(TRIGGERTYPE+0xa4,COUNTRY);self.put(TRIGGERTYPE+0xac,EVENT);self.put(TRIGGERTYPE+0xb0,0);self.put(COUNTRY+0xb4,-9);self.put(EVENT+0x2c,7);self.put(EVENT+0x34,1);self.put(EVENT+0x28,0)
  self.put(0xa3229c,COUNTRY+0x100);self.put(0xa322a8,0);self.put(0xac0148,0x7fff7fff);self.put(0xa40d2c,0);u.mem_write(0xa40d13,bytes([f[1]]));self.put(MAP+0x14ac,f[8]);self.put(MAP+0x14a8,f[9]);u.mem_write(MAP+0x14d5,bytes(f[10:12]))
  self.trace=[];self.expected={BASE:bytearray(u.mem_read(BASE,SIZE)),MAP+0x14a8:bytearray(u.mem_read(MAP+0x14a8,0x30))};self.active=True
  root=(0x6ced90,0x6331e0,0x6e6050,0x6331a0)[f[0]];args=([0],[f[12]],[f[12],0,0,TRIGGER+0x30,BASE+0x19000,0],[])[f[0]];receiver=(ACTOR,MAP,EVENT,MAP)[f[0]]
  try:self.checked_call(root,args,receiver,writes=[(BASE,SIZE),(MAP+0x14d5,2)],inputs=[*RANGES.items(),*TABLES.items(),(0xa3229c,4),(0xa322a8,4),(0xac0148,4),(0xa40d2c,4),(0xa40d13,1),(MAP+0x14a8,8)])
  finally:self.active=False
  for base,raw in self.expected.items():assert bytes(u.mem_read(base,len(raw)))==raw,'Unrelated null notification owner changed'
  result=u.reg_read(UC_X86_REG_EAX)&255 if f[0] in (2,3) else 0
  return self.trace+['F',*map(str,(result,*(self.word(h+0x5360) for h in HOUSES),u.mem_read(TAG+0x35,1)[0],*u.mem_read(MAP+0x14d5,2),self.word(TRIGGER+0x3c)))]
