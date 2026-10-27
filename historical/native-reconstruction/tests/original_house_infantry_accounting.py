# SPDX-License-Identifier: GPL-3.0-or-later
"""Unchanged complete House E1 accounting with named Type/map/resize services."""
from collections import Counter
from original_presentation import PresentationOracle,STOP
from verify_house_infantry_accounting import RANGES,TABLES,SERVICES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EIP
BASE=0x5b00000;SIZE=0x20000;HOUSE=BASE+0x1000;ACTOR=BASE+0x7000;TYPE=BASE+0x8000;VT=BASE+0x9000;TVT=BASE+0xa000;CVT=BASE+0xb000;DATA=BASE+0xc000;ALT=BASE+0xd000
class HouseInfantryAccountingOracle(PresentationOracle):
 def __init__(self,exe):
  super().__init__(exe,allow_patched=True);self.u.mem_map(BASE,SIZE);self.active=False;self.counts=Counter();self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.write)
 def va(self,a):return a
 def word(self,a):return int.from_bytes(self.u.mem_read(a,4),'little')
 def event(self,k,a=0,b=0,c=0,d=0):self.trace.extend(map(str,(k,a,b,c,d)))
 def change(self,a,value,n=4):
  value&=(1<<(8*n))-1;raw=value.to_bytes(n,'little');self.u.mem_write(a,raw);self.expected[a-BASE:a-BASE+n]=raw
 def ret(self,value,argc=0):
  u=self.u;sp=u.reg_read(UC_X86_REG_ESP);u.reg_write(UC_X86_REG_EAX,value&0xffffffff);u.reg_write(UC_X86_REG_EIP,self.word(sp));u.reg_write(UC_X86_REG_ESP,sp+4+argc*4)
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  assert a in SERVICES or any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected House accounting',hex(a))
  if a in RANGES:self.counts[hex(a)]+=1
  sp=u.reg_read(UC_X86_REG_ESP);ecx=u.reg_read(UC_X86_REG_ECX);f=self.f
  if a==0x67c150:
   assert ecx==0x8324e0 and self.word(sp+4)==ACTOR;self.event(2);self.ret(0,1)
  elif a==SERVICES[1]:
   assert ecx==ACTOR;self.event(3)
   if f[10]==1 and not self.mutated:self.change(TYPE+0x202,1,1);self.event(9,5,0x202,1);self.mutated=True
   self.ret(TYPE)
  elif a==SERVICES[2]:assert ecx==TYPE;self.event(4,self.word(TYPE+0x40));self.ret(self.word(TYPE+0x40))
  elif a==0x509800:
   assert ecx==ACTOR;self.event(5)
   if f[10]==2 and not self.mutated:
    value=(f[3]+1)%16;self.change(TYPE+0x40,value);self.event(9,5,0x40,value);self.change(HOUSE+0x234,0xffffffff);self.event(9,1,0x234,0xffffffff);self.mutated=True
  elif a==SERVICES[3]:
   assert ecx==self.counter and self.word(sp+8)==0;requested=self.word(sp+4);assert requested==self.word(TYPE+0x40)+10
   self.event(6,requested,0,f[5]&0xffffffff)
   if f[5]&255 or f[10]==3:
    self.change(self.counter+8,requested);self.change(self.counter+4,ALT if f[10]==3 else DATA);self.event(9,self.counterId,8,requested);self.event(9,self.counterId,4,int(f[10]==3))
   self.ret(f[5],2)
 def write(self,u,access,a,n,v,_):
  if not self.active or not BASE<=a<a+n<=BASE+SIZE:return
  v&=(1<<(n*8))-1
  if a==ACTOR+0x324 and n==1:self.event(1,2,0x324,v)
  elif a==HOUSE+0x234 and n==4:self.event(1,1,0x234,v)
  elif HOUSE+0xa70<=a<a+n<=HOUSE+0xa70+32*4 and n==4:self.event(1,1,a-HOUSE,v)
  elif (DATA<=a<a+n<=DATA+128 or ALT<=a<a+n<=ALT+128) and n==4:self.event(1,self.counterId,a-(ALT if a>=ALT else DATA),v)
  else:raise AssertionError(('Unexpected House accounting store',hex(a),n))
  self.expected[a-BASE:a-BASE+n]=v.to_bytes(n,'little')
 def run(self,f):
  self.f=f;u=self.u;u.mem_write(BASE,b'\x5a'*SIZE);self.counter=HOUSE+(0x5480 if f[0]<2 else 0x5440);self.counterId=4 if f[0]<2 else 3
  self.put(ACTOR,VT);self.put(VT+0x80,SERVICES[1]);self.put(VT+0x2c,0x509800);self.put(TYPE,TVT);self.put(TVT+0x40,SERVICES[2]);self.put(TYPE+0x40,f[3]);u.mem_write(TYPE+0x202,bytes([f[1]]));u.mem_write(ACTOR+0x5c1,bytes([f[2]]));u.mem_write(ACTOR+0x324,bytes([f[11]]))
  self.put(HOUSE+0x234,f[7]);self.put(HOUSE+0x1270,f[9]);self.put(self.counter,CVT);self.put(CVT+8,SERVICES[3]);self.put(self.counter+8,f[4]);self.put(self.counter+4,DATA)
  for i in range(32):self.put(DATA+4*i,f[8]+i);self.put(ALT+4*i,~(f[8]+i));self.put(HOUSE+0xa70+4*i,f[8]+i)
  self.trace=[];self.mutated=False;self.expected=bytearray(u.mem_read(BASE,SIZE));self.active=True
  root=(0x4ed440,0x4ed610,0x4ea800,0x4ea970,0x491c50,0x491cb0)[f[0]];args=[ACTOR,f[6]] if f[0]<2 else [ACTOR] if f[0]<4 else [f[3]];ecx=HOUSE if f[0]<4 else self.counter
  try:self.checked_call(root,args,ecx,writes=[(BASE,SIZE)],inputs=[*RANGES.items(),*TABLES.items()])
  finally:self.active=False
  assert bytes(u.mem_read(BASE,SIZE))==self.expected,'Unrelated House accounting arena changed'
  self.trace+=['F',str(u.mem_read(ACTOR+0x324,1)[0]),str(self.word(HOUSE+0x234)),str(self.word(self.counter+8)),str(int(self.word(self.counter+4)==ALT)),str(self.word(TYPE+0x40)),str(u.mem_read(TYPE+0x202,1)[0])]
  for a in (DATA,ALT,HOUSE+0xa70):self.trace.extend(str(self.word(a+4*i)) for i in range(32))
  if f[0]>=4:self.trace+=['R',str(u.reg_read(UC_X86_REG_EAX))]
  return self.trace
