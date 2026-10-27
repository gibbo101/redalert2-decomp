# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete Object Unlimbo parent, real inline alpha block; named child services."""
import struct
from collections import Counter
from original_presentation import PresentationOracle,STOP,STACK
from verify_object_unlimbo import RANGES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_ECX,UC_X86_REG_EAX,UC_X86_REG_ESP,UC_X86_REG_EIP
BASE=0x4e00000;SIZE=0x10000;OBJ=BASE;TYPE=BASE+0x1000;LATE=BASE+0x1400;IMAGE=BASE+0x2000;FIRSTIMAGE=BASE+0x2100;TACT=BASE+0x3000;VT=BASE+0x4000;TVT=BASE+0x5000;INPUT=BASE+0x6000;CELL=BASE+0x7000;RECORD=BASE+0x8000;COORD=BASE+0x9000
S={name:0x1100500+32*i for i,name in enumerate(('permission','type','adjust','location','mark','layer','kind','aux','coords'))}
SERVICES=set(S.values())|{0x548000,0x499a40,0x53e330,0x6a29d0,0x782017,0x41ebe0,0x6a3020}
def signed(v):return (v+2**31)%2**32-2**31
class ObjectUnlimboOracle(PresentationOracle):
 def __init__(self,exe):
  super().__init__(exe,allow_patched=True);self.u.mem_map(BASE,SIZE);self.active=False;self.counts=Counter();self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.write)
 def va(self,a):return a
 def word(self,p):return int.from_bytes(self.u.mem_read(p,4),'little')
 def ints(self,p,v):self.u.mem_write(p,struct.pack('<'+'I'*len(v),*[x&0xffffffff for x in v]))
 def event(self,k,a=0,b=0,c=0,d=0,e=0):self.trace.extend(map(str,(k,a,b,c,d,e)))
 def mutate(self,at):
  if self.mutated or self.f[18]!=at:return
  self.mutated=True;self.event(18,at)
  if at==1:self.put(0xa40774,1)
  if at==2:self.u.mem_write(OBJ+0x7d,b'\0')
  if at==3:self.u.mem_write(TYPE+0x204,b'\x80');self.put(TYPE+0xac,FIRSTIMAGE)
  if at==4:self.ints(TACT+0xb0,[100,-100])
  if at in (5,6):self.ints(TACT+0xb0,[-123,77]);self.u.mem_write(IMAGE+2,struct.pack('<2h',-7,11));self.put(0xa40774,0 if self.word(0xa40774) else 1)
  self.expected=bytearray(self.u.mem_read(BASE,SIZE))
 def ret(self,sp,n,value=0):
  self.u.reg_write(UC_X86_REG_EAX,value&0xffffffff);self.u.reg_write(UC_X86_REG_EIP,self.word(sp));self.u.reg_write(UC_X86_REG_ESP,sp+4+4*n)
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  assert a in SERVICES or any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected Object Unlimbo instruction',hex(a))
  if a==0x5d3890:self.counts['parent']+=1
  if a not in SERVICES:return
  self.counts[hex(a)]+=1;sp=u.reg_read(UC_X86_REG_ESP);ecx=u.reg_read(UC_X86_REG_ECX);args=lambda count:[signed(self.word(sp+4+4*i)) for i in range(count)]
  if a==0x548000:
   assert ecx==0x8324e0;ptr=self.word(sp+4);self.event(1,*struct.unpack('<3i',u.mem_read(ptr,12)));self.ret(sp,1,CELL)
  elif a==S['permission']:
   assert ecx==OBJ and self.word(sp+4)==CELL;self.event(2,*args(5)[1:]);self.mutate(1);self.ret(sp,5,self.f[6])
  elif a==S['type']:
   assert ecx==OBJ;self.types+=1;self.event(3,self.types);self.ret(sp,0,(TYPE if self.f[9] else 0) if self.types==1 else LATE)
  elif a==S['adjust']:
   assert ecx==TYPE;out,ptr=[self.word(sp+4+4*i) for i in range(2)];x,y,z=struct.unpack('<3i',u.mem_read(ptr,12));self.event(4,x,y,z);self.ints(out,[x+7,y-9,z+3]);self.ret(sp,2,out)
  elif a==S['location']:
   assert ecx==OBJ;self.event(5,*struct.unpack('<3i',u.mem_read(self.word(sp+4),12)));self.mutate(2);self.ret(sp,1)
  elif a==S['mark']:
   assert ecx==OBJ;self.event(6,*args(1));self.ret(sp,1,self.f[7])
  elif a==S['layer']:
   assert ecx==OBJ;self.event(7);self.ret(sp,0,self.f[8])
  elif a==0x499a40:
   assert ecx==0x8324e0 and self.word(sp+4)==OBJ;self.event(8);self.mutate(3);self.ret(sp,1)
  elif a==S['kind']:
   assert ecx==OBJ;self.kinds+=1;self.event(9,self.kinds);self.ret(sp,0,self.f[12 if self.kinds==1 else 13])
  elif a==S['aux']:
   assert ecx==VT and self.word(sp+4)==OBJ+4;self.event(10);self.ret(sp,1,self.f[15])
  elif a==0x53e330:
   assert ecx==0x832470 and self.word(sp+4)==OBJ;self.event(11,signed(self.word(sp+8)));self.ret(sp,2)
  elif a==S['coords']:
   assert ecx==OBJ;self.event(12);out=self.word(sp+4);self.ints(out,[self.f[21],self.f[22],31]);self.ret(sp,1,out)
  elif a==0x6a29d0:
   assert ecx==TACT;ptr=self.word(sp+4);out=self.word(sp+8);self.event(13,*struct.unpack('<3i',u.mem_read(ptr,12)));self.ints(out,self.f[21:23]);self.mutate(4);self.ret(sp,2,out)
  elif a==0x782017:
   self.event(14,*args(1));self.mutate(5);self.ret(sp,0,RECORD if self.f[17] else 0)
  elif a==0x41ebe0:
   assert ecx==RECORD and self.word(sp+4)==OBJ;self.event(15,*args(3)[1:]);self.mutate(6);self.ret(sp,3,RECORD)
  elif a==0x6a3020:
   assert ecx==TACT;self.event(16,*args(5));self.ret(sp,5)
 def write(self,u,access,p,n,v,_):
  if not self.active or not BASE<=p<BASE+SIZE:return
  assert p in (OBJ+0x76,OBJ+0x75) and n==1,('Unexpected parent store',hex(p),n)
  self.event(17,p-OBJ,v&255);self.expected[p-BASE:p-BASE+n]=bytes([v&255])
 def run(self,f):
  self.f=f;self.types=0;self.kinds=0;self.mutated=False;self.trace=[];self.u.mem_write(BASE,b'\x5a'*SIZE);u=self.u
  self.put(OBJ,VT);self.put(OBJ+4,VT);self.put(TYPE,TVT);self.put(LATE,TVT)
  for off,name in ((0x194,'permission'),(0x84,'type'),(0x19c,'location'),(0x11c,'mark'),(0x74,'layer'),(0x2c,'kind'),(0x10,'aux'),(0x48,'coords')):self.put(VT+off,S[name])
  self.put(TVT+0x6c,S['adjust']);self.put(TYPE+0xac,FIRSTIMAGE if f[16] else 0);self.put(LATE+0xac,IMAGE);u.mem_write(TYPE+0x204,bytes([f[10]]));u.mem_write(TYPE+0x281,bytes([f[11]]));u.mem_write(LATE+0x20a,b'\0')
  u.mem_write(IMAGE+2,struct.pack('<2h',f[19],f[20]));u.mem_write(FIRSTIMAGE+2,struct.pack('<2h',123,321))
  self.ints(TACT+0xb0,f[23:25]);self.ints(INPUT,[f[21],f[22],31]);self.put(0x83996c,TACT);self.put(0xa40774,f[5]);self.put(0xa3d298,f[14]);u.mem_write(0xa40958,bytes([f[0]]))
  for off,v in ((0x76,f[1]),(0x74,f[2]),(0x75,f[3]),(0x7d,f[4])):u.mem_write(OBJ+off,bytes([v]))
  self.expected=bytearray(u.mem_read(BASE,SIZE));self.active=True
  try:self.checked_call(0x5d3890,[INPUT,0xdeadbeef],OBJ,writes=[(OBJ+0x75,2)],inputs=[*RANGES.items(),(VT,0x1a0),(TVT,0x80),(INPUT,12)])
  finally:self.active=False
  assert self.expected==u.mem_read(BASE,SIZE),'Unrelated parent arena mutation'
  self.trace.extend(['F',str(u.reg_read(UC_X86_REG_EAX)&255),*[str(u.mem_read(OBJ+off,1)[0]) for off in (0x76,0x75,0x74,0x7d)],str(signed(self.word(0xa40774))),str(self.types),str(self.kinds),str(int(self.mutated))])
  return self.trace
