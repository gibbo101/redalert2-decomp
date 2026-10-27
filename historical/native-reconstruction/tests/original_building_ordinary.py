# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete original parent with explicit image/timer/partner/frame/pixel services."""
import struct
from collections import Counter
from original_presentation import PresentationOracle,STOP
from original_fp_return import push_double
from verify_building_ordinary import verify,RANGES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_READ,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_ECX,UC_X86_REG_EAX,UC_X86_REG_ESP,UC_X86_REG_EIP,UC_X86_REG_FPSW,UC_X86_REG_FPTAG
BASE=0x4700000;SIZE=0x20000;ACTOR=BASE+0x1000;TYPES=[BASE+0x4000,BASE+0x6000];CELL=BASE+0x9000;POINT=BASE+0xa000;CLIP=BASE+0xb000;PARTNER=BASE+0x11000;PARTNER_TYPE=BASE+0x13000;IMAGES=[0]+[BASE+0x15000+0x100*i for i in range(1,8)];ANIMS=BASE+0x17000;RULES=BASE+0x18000
class BuildingOrdinaryOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(BASE,SIZE);self.active=False;self.counts=Counter()
  self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_READ,self.read);self.u.hook_add(UC_HOOK_MEM_WRITE,self.store)
 def va(self,a):return a
 def word(self,p):return int.from_bytes(self.u.mem_read(p,4),'little')
 def signed(self,v):return (v+2**31)%2**32-2**31
 def event(self,k,a=0,b=0,c=0):self.trace.extend(map(str,(k,a,b,c)))
 def ints(self,p,v):self.u.mem_write(p,struct.pack('<'+'I'*len(v),*[n&0xffffffff for n in v]))
 def values(self,p,n):return [self.signed(self.word(p+4*i)) for i in range(n)]
 def write(self,p,data):self.u.mem_write(p,data);self.expected[p-BASE:p-BASE+len(data)]=data
 def change(self,p,value,n=4):self.write(p,(value%(1<<(8*n))).to_bytes(n,'little'))
 def ret(self,pop=0,value=0):
  sp=self.u.reg_read(UC_X86_REG_ESP);self.u.reg_write(UC_X86_REG_EAX,value&0xffffffff);self.u.reg_write(UC_X86_REG_EIP,self.word(sp));self.u.reg_write(UC_X86_REG_ESP,sp+4+pop)
 def mutate(self,mode):
  if self.mutated or self.f[0]!=mode:return
  self.mutated=True;self.event(8,mode);self.change(ACTOR+0x418,TYPES[1])
  if mode==1:self.change(ACTOR+0x42c,0)
  if mode==2:self.change(ACTOR+0x42c,1)
  if mode==3:self.change(PARTNER_TYPE+0xb44,0,1);self.change(PARTNER_TYPE+0xb1a,255,1)
  if mode==4:
   for p in IMAGES[1:]:self.change(p+6,-3,2)
   self.change(ACTOR+0x42c,2);self.count=-3
  if mode==5:self.change(CELL+0x10a,-32768,2);self.change(ACTOR+0x90,728)
  if mode==6:self.change(ACTOR+0x90,729)
  if mode==7:self.write(POINT,struct.pack('<ii',71,72));self.write(CLIP,struct.pack('<iiii',21,22,23,24));self.change(ACTOR+0x42c,2)
  if mode==8:self.change(TYPES[1]+0x137c,2**31-1);self.write(RULES+0x1368,struct.pack('<Q',0x7ff8000000000000))
 def read(self,u,access,p,n,value,_):
  if not self.active or not 0x43a5e0<=u.reg_read(UC_X86_REG_EIP)<0x43abc1:return
  if p==ACTOR+0x42c:self.event(1,1,0x42c,self.signed(self.word(p)))
  if ACTOR+0x454<=p<ACTOR+0x49c and n==4:
   i=(p-ACTOR-0x454)//4;self.animIndex=i;self.event(5,i,-1 if not self.word(p) else (self.word(p)-ANIMS)//0x200)
  if p==CELL+0x10a:self.event(1,1,0x10a,struct.unpack('<h',u.mem_read(p,2))[0])
  if p==0x85029c:self.event(1,4,0x85029c,self.signed(self.word(p)))
  if p in [i+6 for i in IMAGES[1:]]:self.event(1,2,6,struct.unpack('<h',u.mem_read(p,2))[0])
  if p-PARTNER_TYPE in (0xb44,0xb1a):self.event(1,3,p-PARTNER_TYPE,u.mem_read(p,1)[0])
  for t in TYPES:
   off=p-t
   if off in (0x11a0,0x11a8,0x11b0,0x11b8,0x11cc):self.event(2,off,IMAGES.index(self.word(p)))
   elif off in (0x1385,0x11d4,0x11e4,0x11e8,0x11fc,0x137c):self.event(1,0,off,int.from_bytes(u.mem_read(p,n),'little',signed=off!=0x1385))
 def store(self,u,access,p,n,value,_):
  if self.active and ANIMS<=p<ANIMS+0xc00:
   assert n==1 and (p-ANIMS)%0x200==0x17d;self.event(6,self.animIndex,value&255);self.expected[p-BASE]=value&255
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  sp=u.reg_read(UC_X86_REG_ESP);arg=lambda i:self.word(sp+4+4*i);receiver=u.reg_read(UC_X86_REG_ECX)
  if a in RANGES:
   self.counts[hex(a)]+=1
   if a==0x41b320:self.event(3,1);assert receiver==ACTOR
   if a==0x5d4800:self.event(3,14);self.mutate(6);assert receiver==ACTOR
  if any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()):return
  self.counts[hex(a)]+=1
  if a==0x44c5a0:
   assert receiver==ACTOR;i=self.imageCalls;self.imageCalls+=1;which=self.f[4 if i else 3];self.event(3,2,i,which);self.mutate(1);self.ret(value=IMAGES[which]);return
  if a==0x453c40:assert receiver==ACTOR;self.event(3,3,0,self.f[2]);self.ret(value=self.f[2]);return
  if a==0x594770:
   assert receiver==ACTOR;self.event(3,4,self.missionCalls,self.f[1]);self.missionCalls+=1
   if self.missionCalls==2:self.mutate(2)
   self.ret(value=self.f[1]);return
  if a==0x636e20:assert receiver==ACTOR and arg(0)==0;self.event(3,5,0,self.f[17]);self.ret(4,PARTNER if self.f[17] else 0);return
  if a==self.partner80:
   assert receiver==PARTNER;off=0xb44 if self.word(sp)==0x43a6ac else 0xb1a;self.event(3,6,off);self.mutate(3);self.ret(value=PARTNER_TYPE);return
  if a in (0x496a90,0x496ab0,0x496b30,0x496b50):
   assert receiver==ACTOR+0x2a8;self.event(3,7,a);self.mutate(9);bit=(0x496a90,0x496ab0,0x496b30,0x496b50).index(a);self.ret(value=128 if self.f[20]&(1<<bit) else 0);return
  if a in (0x496c70,0x5d4540):
   self.event(3,8 if a==0x496c70 else 9)
   assert receiver==ACTOR+(0x2a8 if a==0x496c70 else 0)
   if a==0x5d4540:self.mutate(8)
   push_double(u,self.f[39 if a==0x496c70 else 40]);self.ret();return
  if a==0x458940:assert arg(0)==0;self.event(3,10,0,self.f[22]);self.ret(4,self.f[22]);return
  if a==0x458930:
   value=self.f[23 if self.widthCalls else 21];self.event(3,11,self.widthCalls,value);self.widthCalls+=1;self.ret(value=value);return
  if a==0x43be20:
   assert receiver==ACTOR;value=self.f[26+min(self.frameCalls,2)];self.event(3,12,self.frameCalls,value)
   if self.frameCalls==0:self.mutate(4)
   self.frameCalls+=1;self.ret(value=value);return
  if a==0x548070:assert receiver==0x8324e0;self.event(3,13,self.signed(self.word(arg(0))));self.mutate(5);self.ret(4,CELL);return
  if a==0x6d1510:
   assert receiver==ACTOR and arg(2)==POINT and arg(3)==CLIP
   args=[arg(i) for i in range(15)];args[0]=IMAGES.index(args[0]);args[2:4]=[101,102]
   for i,v in enumerate(args):self.event(4,i,self.signed(v))
   for i,v in enumerate(self.values(POINT,2)+self.values(CLIP,4)):self.event(7,i,v)
   if self.drawCalls==0:self.mutate(7)
   self.drawCalls+=1;self.ret(60);return
  raise AssertionError(('Uninspected Building ordinary instruction',hex(a)))
 def run(self,f):
  self.f=f;self.count=f[25];self.trace=[];self.imageCalls=self.missionCalls=self.widthCalls=self.frameCalls=self.drawCalls=0;self.mutated=False;self.animIndex=-1
  self.u.mem_write(BASE,b'\x5a'*SIZE);self.put(ACTOR,0x79cbbc);self.put(ACTOR+0x418,TYPES[0]);self.put(ACTOR+0x42c,f[5]);self.ints(ACTOR+0x88,[f[31],f[32],f[29]]);self.ints(POINT,f[33:35]);self.ints(CLIP,f[35:39]);self.u.mem_write(CELL+0x10a,struct.pack('<h',f[30]));self.put(0x85029c,f[24]);self.put(0x839848,RULES);self.u.mem_write(RULES+0x1368,struct.pack('<Q',f[41]));self.u.mem_write(0xabe490,struct.pack('<Q',f[42]))
  self.put(PARTNER,0x79cbbc);self.partner80=self.word(0x79cbbc+0x80);self.u.mem_write(PARTNER_TYPE+0xb44,bytes([f[18]]));self.u.mem_write(PARTNER_TYPE+0xb1a,bytes([f[19]]))
  for p in IMAGES[1:]:self.u.mem_write(p+6,struct.pack('<h',f[25]))
  for i in range(6):self.u.mem_write(ANIMS+i*0x200+0x17d,b'\x80')
  for i in range(18):self.put(ACTOR+0x454+4*i,0 if i%3==1 else ANIMS+(i%6)*0x200)
  for id,t in enumerate(TYPES):
   self.u.mem_write(t+0x1385,bytes([f[6]]));self.put(t+0x11d4,f[7]+id*100);self.ints(t+0x11e4,[f[8]+id*20,f[9]-id*30]);self.u.mem_write(t+0x11fc,struct.pack('<H',(f[10]+id*3)&65535));self.put(t+0x137c,f[11]+id)
   for off,index in ((0x11a0,12),(0x11a8,13),(0x11b0,14),(0x11b8,15),(0x11cc,16)):
    image=f[index];self.put(t+off,IMAGES[image%7+1 if id and image else image])
  self.expected=bytearray(self.u.mem_read(BASE,SIZE));self.u.reg_write(UC_X86_REG_FPSW,0);self.u.reg_write(UC_X86_REG_FPTAG,0xffff);self.active=True
  try:self.checked_call(0x43a5e0,[POINT,CLIP],ACTOR,writes=[(ANIMS+i*0x200+0x17d,1) for i in range(6)],inputs=[*RANGES.items(),(0x79cbbc,0x1c0)])
  finally:self.active=False
  assert self.u.mem_read(BASE,SIZE)==self.expected,'Unrelated Building draw arena changed'
  self.trace.append('F');self.trace.extend(map(str,[TYPES.index(self.word(ACTOR+0x418)),self.signed(self.word(ACTOR+0x42c)),self.signed(self.word(ACTOR+0x90)),self.count,*self.values(POINT,2),*self.values(CLIP,4),*[self.u.mem_read(ANIMS+i*0x200+0x17d,1)[0] for i in range(6)]]));return self.trace
