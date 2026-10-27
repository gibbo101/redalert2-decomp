# SPDX-License-Identifier: GPL-3.0-or-later
"""Unchanged E1 transfer parent/wrapper with actual accounting/null children."""
from collections import Counter
from original_presentation import PresentationOracle,STOP
from verify_techno_house_transfer import RANGES,TABLES,VIRTUAL,COST,INDEX,SERVICES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EIP
BASE=0x5c00000;SIZE=0x30000;HOUSES=(BASE+0x1000,BASE+0x7000);ACTOR=BASE+0xe000;TYPE=BASE+0xf000;VT=BASE+0x10000;TVT=BASE+0x11000;COUNTER=BASE+0x12000;DATA=BASE+0x18000;CELL=BASE+0x20000
class TechnoHouseTransferOracle(PresentationOracle):
 def __init__(self,exe):
  super().__init__(exe,allow_patched=True);self.u.mem_map(BASE,SIZE);self.active=False;self.counts=Counter();self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.write)
 def va(self,a):return a
 def word(self,a):return int.from_bytes(self.u.mem_read(a,4),'little')
 def hid(self,p):return HOUSES.index(p)+1 if p else 0
 def event(self,k,a=0,b=0,c=0,d=0,e=0):self.trace.extend(map(str,(k,a,b,c,d,e)))
 def ret(self,value=0,argc=0):
  u=self.u;sp=u.reg_read(UC_X86_REG_ESP);u.reg_write(UC_X86_REG_EAX,value&0xffffffff);u.reg_write(UC_X86_REG_EIP,self.word(sp));u.reg_write(UC_X86_REG_ESP,sp+4+argc*4)
 def change(self,a,v,n=4):
  raw=(v&((1<<(n*8))-1)).to_bytes(n,'little');self.u.mem_write(a,raw);self.expected[a-BASE:a-BASE+n]=raw
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  assert a in SERVICES or any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected transfer instruction',hex(a))
  assert a!=0x6155f3, 'Non-null controller path unjoined'
  if a in RANGES:self.counts[hex(a)]+=1
  sp=u.reg_read(UC_X86_REG_ESP);ecx=u.reg_read(UC_X86_REG_ECX);f=self.f
  arg=lambda i:self.word(sp+4+4*i)
  if a in (0x4ed440,0x4ed610):
   assert arg(0)==ACTOR and arg(1)==int(a==0x4ed610);self.event(10,0 if a==0x4ed440 else 1,self.hid(ecx),arg(1))
  elif a in (0x4ea800,0x4ea970):assert arg(0)==ACTOR;self.event(10,2 if a==0x4ea800 else 3,self.hid(ecx))
  elif a==0x6155e0:assert ecx==ACTOR;self.event(10,4)
  elif a==0x67c150:assert ecx==0x8324e0 and arg(0)==ACTOR;self.event(10,5)
  elif a==0x509800:assert ecx==ACTOR;self.event(5)
  elif a==0x6c7420:assert ecx==ACTOR;self.event(7,self.hid(self.word(ACTOR+0x1b4)))
  elif a==0x636e10:assert ecx==ACTOR and arg(0)==0;self.event(8)
  elif a==0x6cd940:assert ecx==ACTOR and arg(0)==HOUSES[f[1]-1];self.event(11,arg(1))
  elif a==INDEX:assert ecx==TYPE;self.event(4);self.ret(3)
  elif a==COST:assert ecx==TYPE;self.event(12,self.hid(arg(0)));self.ret(f[2],1)
  elif a==0x6d7c80:
   assert ecx==ACTOR;self.event(13)
   if f[11]:self.change(ACTOR+0x76,0 if f[4] else 255,1);self.event(9,10,0x76,0 if f[4] else 255)
   self.ret()
  elif a in (0x548000,0x548070):
   assert ecx==0x8324e0;p=arg(0)
   if a==0x548000:assert [self.word(p+i*4) for i in range(3)]==[256,512,104];self.event(14,0,256,512,104)
   else:assert self.word(p)==0x0059003f;self.event(14,1,0x0059003f)
   self.ret(CELL if f[6] else 0,1)
  elif a==0x476b20:assert ecx==CELL;self.event(15,arg(0),arg(1));self.ret(0,2)
  elif a in VIRTUAL.values():
   off=next(k for k,v in VIRTUAL.items() if v==a);assert ecx==ACTOR
   if off in (0x370,0xdc):assert arg(0)==0;self.event(16,off);self.ret(0,1)
   elif off in (0x410,0x414):assert [arg(0),arg(1)]==[0,1];self.event(16,off,0,1);self.ret(0,2)
   elif off==0x80:self.event(3);self.ret(TYPE)
   elif off==0x11c:self.event(16,off,arg(0));self.ret(0,1)
   elif off==0x2a0:self.event(16,off);self.ret(f[9])
   elif off in (0x424,0x420):self.event(16,off);self.ret()
   elif off==0x54:self.event(16,off);self.ret(f[8])
   elif off==0x1a0:self.event(16,off);self.u.mem_write(arg(0),(0x1234fedc).to_bytes(4,'little'));self.ret(arg(0),1)
 def write(self,u,access,a,n,v,_):
  if not self.active or not BASE<=a<a+n<=BASE+SIZE:return
  v&=(1<<(8*n))-1
  if ACTOR<=a<a+n<=ACTOR+0x600:
   off=a-ACTOR;assert (off==0x1b4 and n==4) or (off in (0x372,0x324) and n==1) or (off in (0x400,0x454) and n==4)
   self.event(1,10,off,self.hid(v) if off==0x1b4 else v)
  elif any(p<=a<a+n<=p+0x6000 for p in HOUSES):
   p=next(p for p in HOUSES if p<=a<p+0x6000);off=a-p;assert n==4 and (off in (0x234,0x5418,0x53b8) or 0x5310<=off<0x5390 or 0xa70<=off<0xaf0);self.event(1,self.hid(p),off,v)
  elif DATA<=a<a+n<=DATA+512:
   relative=a-DATA;house=relative//256+1;which=(relative%256)//128;index=(relative%128)//4;assert n==4;self.event(1,house,0x5480 if which else 0x5440,v,index)
  else:raise AssertionError(('Unexpected transfer store',hex(a),n))
  self.expected[a-BASE:a-BASE+n]=v.to_bytes(n,'little')
 def run(self,f):
  self.f=f;u=self.u;u.mem_write(BASE,b'\x5a'*SIZE)
  for off,target in VIRTUAL.items():self.put(VT+off,target)
  for off,target in ((0x2c,0x509800),(0x38,0x6c7420)):self.put(VT+off,target)
  self.put(TVT+0x84,COST);self.put(TVT+0x40,INDEX);self.put(TYPE,TVT);u.mem_write(TYPE+0x202,b'\0');self.put(ACTOR,VT);self.put(ACTOR+0x1b4,HOUSES[0]);self.put(ACTOR+0x400,f[3]);self.put(ACTOR+0x408,0);self.put(ACTOR+0xd0,0);self.put(ACTOR+0xcc,DATA+0x400);self.put(DATA+0x400,0);self.put(ACTOR+0x454,0x0059003f)
  for off,v in ((0x76,f[4]),(0x14,f[5]),(0x372,255),(0x324,1),(0x5c1,0)):u.mem_write(ACTOR+off,bytes([v]))
  for i,v in enumerate((256,512,104)):self.put(ACTOR+0x88+i*4,v)
  for i,p in enumerate(HOUSES):
   self.put(p+0x30,i);self.put(p+0x34,TYPE+0x100+i*0x100);self.put(TYPE+0x100+i*0x100+0xb8,13+i);self.put(p+0x234,f[10]);self.put(p+0x5418,f[10]);self.put(p+0x53b8,-777);self.put(p+0x1270,32)
   for j in range(32):self.put(p+0x5310+4*j,f[10]+j);self.put(p+0xa70+4*j,f[10]+j)
   for k,off in enumerate((0x5440,0x5480)):
    self.put(p+off,COUNTER);self.put(p+off+4,DATA+i*256+k*128);self.put(p+off+8,32)
    for j in range(32):self.put(DATA+i*256+k*128+j*4,f[10]+j)
  self.put(0xa35db4,HOUSES[f[7]-1] if f[7] else 0);u.mem_write(0x8324e0+0x4ee1,b'\0');self.trace=[];self.expected=bytearray(u.mem_read(BASE,SIZE));self.active=True
  try:self.checked_call(0x4ca7d0 if f[0] else 0x6cd940,[HOUSES[f[1]-1],f[12]],ACTOR,writes=[(BASE,SIZE)],inputs=[*RANGES.items(),*TABLES.items(),(0xa35db4,4),(0x8324e0+0x4ee1,1)])
  finally:self.active=False
  assert bytes(u.mem_read(BASE,SIZE))==self.expected,'Unrelated transfer arena changed'
  final=[u.reg_read(UC_X86_REG_EAX)&255,self.hid(self.word(ACTOR+0x1b4)),u.mem_read(ACTOR+0x372,1)[0],self.word(ACTOR+0x400),u.mem_read(ACTOR+0x324,1)[0],self.word(ACTOR+0x454),u.mem_read(ACTOR+0x76,1)[0]]
  for i,p in enumerate(HOUSES):
   final.extend((self.word(p+0x5418),self.word(p+0x53b8)))
   for base in (p+0x5310,DATA+i*256,DATA+i*256+128,p+0xa70):final.extend(self.word(base+4*j) for j in range(32))
  return self.trace+['F',*map(str,final)]
