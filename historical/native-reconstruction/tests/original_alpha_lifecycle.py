# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete lifecycle parents/base/find; Type, vector allocation and free supplied."""
import struct,hashlib
from collections import Counter
from original_presentation import PresentationOracle,STOP
from verify_alpha_lifecycle import RANGES,SERVICES,VTABLES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EAX,UC_X86_REG_EIP
BASE=0x4d00000;SIZE=0x20000;RECORDS=BASE+0x1000;OBJECTS=BASE+0x2000;TYPE=BASE+0x3000;IMAGE=BASE+0x4000;VT=BASE+0x5000;OBJECTVT=BASE+0x6000;SLOTS=(BASE+0x7000,BASE+0x8000);ALT=(BASE+0x9000,BASE+0xa000);REG=(0x83c648,0xac0d60)
def layout(n):return ((1,2,1,2),(0,1,0,2),(1,0,2,0),(2,1,2,1))[n]*4
class AlphaLifecycleOracle(PresentationOracle):
 def __init__(self,exe):
  super().__init__(exe,allow_patched=True);self.u.mem_map(BASE,SIZE);self.active=False;self.counts=Counter();self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.write)
 def va(self,a):return a
 def word(self,p):return int.from_bytes(self.u.mem_read(p,4),'little')
 def signed(self,n):return (n+2**31)%2**32-2**31
 def ints(self,p,v):self.u.mem_write(p,struct.pack('<'+'I'*len(v),*[x&0xffffffff for x in v]))
 def pid(self,p):
  if not p:return 0
  if p in [RECORDS+256*i for i in range(3)]:return 1+(p-RECORDS)//256
  if p in [OBJECTS+256*i for i in range(3)]:return 11+(p-OBJECTS)//256
  if p==IMAGE:return 21
  if p in REG:return 31+REG.index(p)
  raise AssertionError(('Unknown lifecycle pointer',hex(p)))
 def event(self,k,a=0,b=0,c=0,d=0):self.trace.extend(map(str,(k,a,b,c,d)))
 def mutate(self,where):
  mode=self.f[13]
  if not mode or self.mutated or where!={1:1,2:2,3:3,4:4,5:5}[mode]:return
  self.mutated=True;self.event(9,mode)
  if mode==1:self.put(REG[1]+8,0);self.put(REG[1]+20,3)
  if mode==2:self.put(REG[self.resizing]+16,1)
  if mode==3:self.put(REG[0]+4,ALT[0]);self.put(REG[0]+16,2)
  if mode==4:self.put(REG[0]+4,ALT[0]);self.put(REG[0]+16,1)
  if mode==5:self.put(REG[0]+4,ALT[0])
  self.expected=bytearray(self.u.mem_read(BASE,SIZE))
 def ret(self,sp,args,result=0):
  self.u.reg_write(UC_X86_REG_EAX,result&0xffffffff);self.u.reg_write(UC_X86_REG_EIP,self.word(sp));self.u.reg_write(UC_X86_REG_ESP,sp+4+4*args)
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  assert a in SERVICES or any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected alpha lifecycle instruction',hex(a))
  if a in RANGES:self.counts[hex(a)]+=1
  sp=u.reg_read(UC_X86_REG_ESP)
  if a==SERVICES[0]:
   obj=u.reg_read(UC_X86_REG_ECX);self.event(1,self.pid(obj));self.counts['supplied-type']+=1;self.mutate(1);self.ret(sp,0,TYPE)
  if a==SERVICES[1]:
   which=REG.index(u.reg_read(UC_X86_REG_ECX));cap=self.word(sp+4);zero=self.word(sp+8);self.resizing=which;self.event(2,31+which,self.signed(cap),zero,self.f[12]);self.counts['supplied-resize']+=1
   if self.f[12]&255:
    old=self.word(REG[which]+4);u.mem_write(ALT[which],bytes(u.mem_read(old,64)));self.put(REG[which]+4,ALT[which]);self.put(REG[which]+8,cap);u.mem_write(REG[which]+13,b'\1')
   self.mutate(2);self.expected=bytearray(u.mem_read(BASE,SIZE));self.ret(sp,2,self.f[12])
  if a==0x41fd20:self.event(3,31+REG.index(u.reg_read(UC_X86_REG_ECX)));self.mutate(3)
  if a==0x41f9c0:self.mutate(4)
  if a==0x781d3b:
   p=self.word(sp+4);i=self.pid(p);self.event(5,i);self.freed[i-1]+=1;self.counts['supplied-free']+=1;self.ret(sp,0)
 def write(self,u,access,p,n,v,_):
  if not self.active:return
  if p==0x84c684:self.event(6,-1,v&255);return
  if 0x83c670<=p<0x84c670:self.event(6,p-0x83c670,v&255);return
  if p in (REG[0]+16,REG[1]+16):
   self.event(4,31+int(p==REG[1]+16),16,v&0xffffffff)
   if p==REG[0]+16:self.mutate(5)
   return
  if not BASE<=p<BASE+SIZE:return
  value=v&((1<<(n*8))-1)
  if RECORDS<=p<RECORDS+3*256:
   i=(p-RECORDS)//256;off=(p-RECORDS)%256
   if off in (0,4,8,12):self.event(4,i+1,off,VTABLES.index(value))
   elif off in (0x24,0x38):self.event(4,i+1,off,0,self.pid(value))
   else:self.event(4,i+1,off,value)
  else:
   which=next((i for i in range(2) if SLOTS[i]<=p<SLOTS[i]+64 or ALT[i]<=p<ALT[i]+64),None);assert which is not None,(hex(p),n,self.f)
   base=ALT[which] if p>=ALT[which] else SLOTS[which];self.event(4,31+which,0x100+p-base,0,self.pid(value))
  self.expected[p-BASE:p-BASE+n]=value.to_bytes(n,'little')
 def run(self,f):
  self.f=f;self.trace=[];self.mutated=False;self.freed=[0,0,0];self.u.mem_write(BASE,b'\x5a'*SIZE);u=self.u
  u.mem_write(0x84c684,bytes([f[1]]));u.mem_write(0x83c670,bytes((i*7+3)%256 for i in range(65536)))
  self.put(VT+8,SERVICES[1]);self.put(VT+16,0x41fd20);self.put(OBJECTVT+0x84,SERVICES[0]);self.put(TYPE+0xac,IMAGE);u.mem_write(IMAGE,struct.pack('<H2hH',0,f[14],f[15],1))
  for i in range(3):
   r=RECORDS+i*256;self.ints(r,VTABLES[:4]);self.put(r+0x24,0 if f[19] and i==0 else OBJECTS+256*i);self.put(OBJECTS+256*i,OBJECTVT);self.put(r+0x38,IMAGE);u.mem_write(r+0x3c,bytes([128 if f[18]&(1<<i) else 0]));u.mem_write(r+0x14,bytes([f[2]]))
  for i in range(2):
   self.ints(REG[i],[VT,SLOTS[i],f[5+4*i],0,f[4+4*i],f[7+4*i]]);u.mem_write(REG[i]+13,bytes([f[6+4*i]]));self.ints(SLOTS[i],[RECORDS+256*n for n in (layout(f[17]) if i==0 else layout(f[17])[::-1])]);self.ints(ALT[i],[RECORDS+256*n for n in (2,0,1,0)*4])
  self.expected=bytearray(u.mem_read(BASE,SIZE));self.active=True
  def call(a,args=(),ecx=RECORDS):
   self.checked_call(a,args,ecx,writes=[(RECORDS,768),(SLOTS[0],64),(SLOTS[1],64),(ALT[0],64),(ALT[1],64),(REG[0]+16,4),(REG[1]+16,4),(0x84c684,1),(0x83c670,65536)],inputs=[*RANGES.items(),(VT,32),(OBJECTVT,136),(TYPE,256),(IMAGE,8)])
   if a in (0x41ebe0,0x41ed70,0x41f9c0):self.event(8,self.pid(self.u.reg_read(UC_X86_REG_EAX)))
  try:
   if f[0] in (0,5):call(0x41ebe0,[OBJECTS,17,-23])
   if f[0]==1:call(0x41ed70)
   if f[0] in (2,5):call(0x41f0f0,[OBJECTS if f[3]==1 else 0 if f[3]==2 else OBJECTS+256,f[16]])
   if f[0]==3:call(0x41f9c0,[f[16]])
   if f[0] in (4,5):call(0x41f110,ecx=0)
  finally:self.active=False
  assert bytes(u.mem_read(BASE,SIZE))==self.expected,'Unrelated lifecycle arena changed'
  final=[int(self.mutated),*self.freed,*u.mem_read(0x84c684,1)]
  for i in range(2):
   backing=self.word(REG[i]+4);final.extend([self.word(REG[i]+16),self.word(REG[i]+8),int(backing==ALT[i]),*u.mem_read(REG[i]+13,1),self.word(REG[i]+20),*[self.pid(self.word(backing+4*j)) for j in range(16)]])
  for i in range(3):
   r=RECORDS+i*256;final.extend([self.word(r+0x10),*u.mem_read(r+0x14,1),self.word(r+0x18),self.word(r+0x1c),*u.mem_read(r+0x20,1),self.pid(self.word(r+0x24)),*[self.word(r+o) for o in (0x28,0x2c,0x30,0x34)],self.pid(self.word(r+0x38)),*u.mem_read(r+0x3c,1)])
  return self.trace+['F',*map(str,final),hashlib.sha256(bytes(u.mem_read(0x83c670,65536))).hexdigest()]
