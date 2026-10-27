# SPDX-License-Identifier: GPL-3.0-or-later
"""Original alpha passes and full65,536-store initialization; supplied Type/cache startup."""
import struct,hashlib
from collections import Counter
from original_presentation import PresentationOracle,STOP
from verify_alpha_animation import RANGES,VT,SERVICE
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EAX,UC_X86_REG_EIP,UC_X86_REG_EDX
BASE=0x4c00000;SIZE=0x20000;ALPHA=BASE+0x400;SURFACE=BASE+0x500;INPUT=BASE+0x600;TACTICAL=BASE+0x800;SLOTS=BASE+0x1000;SLOTS2=BASE+0x1100;RECORDS=BASE+0x2000;OBJECTS=BASE+0x3000;TYPE=BASE+0x4000;OBJECTVT=BASE+0x5000;IMAGES=(BASE+0x6000,BASE+0x8000);BUFFER=BASE+0x10000
PIXELS=(0,1,63,126,127,128,254,255);DEST=(0,1,63,126,127,128,254,255)
def synthetic(f,variant):
 d=bytearray(32+f[15]*f[16]);struct.pack_into('<h',d,6,f[4]);struct.pack_into('<4h',d,8,*f[13:17]);struct.pack_into('<I',d,28,32)
 for i in range(f[15]*f[16]):d[32+i]=PIXELS[(i+3*variant)%8]
 return bytes(d)
class AlphaAnimationOracle(PresentationOracle):
 def __init__(self,exe):
  super().__init__(exe,allow_patched=True);self.u.mem_map(BASE,SIZE);self.active=False;self.counts=Counter();self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.write)
  self.checked_call(0x41f950,writes=[(0x84c684,1),(0x83c670,65536)],inputs=list(RANGES.items()));self.table=bytes(self.u.mem_read(0x83c670,65536));self.audit_calls=0
 def va(self,a):return a
 def word(self,p):return int.from_bytes(self.u.mem_read(p,4),'little')
 def signed(self,n):return (n+2**31)%2**32-2**31
 def values(self,p,n):return [self.signed(self.word(p+4*i)) for i in range(n)]
 def ints(self,p,v):self.u.mem_write(p,struct.pack('<'+'I'*len(v),*[x&0xffffffff for x in v]))
 def event(self,k,a=0,b=0,c=0,d=0):self.trace.extend(map(str,(k,a,b,c,d)))
 def mutate(self,where):
  if self.mutated or not self.f[1] or (where==2)!=(self.f[1]==6):return
  self.mutated=True;m=self.f[1];self.event(9,m)
  if m==1:self.put(0x83c658,3)
  if m==2:self.put(0x83c658,1)
  if m==3:self.put(0x83c64c,SLOTS2)
  if m==4:self.put(SLOTS,RECORDS+256*2)
  if m in (5,6):self.ints(TACTICAL+0xb0,[17,-23]);self.ints(0x839630,[1,2]);self.ints(INPUT,[8,9,24,16])
  self.expected=bytearray(self.u.mem_read(BASE,SIZE))
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  assert a==SERVICE or any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected alpha instruction',hex(a))
  if a in RANGES:self.counts[hex(a)]+=1
  sp=u.reg_read(UC_X86_REG_ESP)
  if a==SERVICE:
   obj=u.reg_read(UC_X86_REG_ECX);assert obj in [OBJECTS+i*256 for i in range(3)];self.event(1,(obj-OBJECTS)//256);self.counts['supplied-type']+=1;self.mutate(1)
   u.reg_write(UC_X86_REG_EAX,TYPE);u.reg_write(UC_X86_REG_EIP,self.word(sp));u.reg_write(UC_X86_REG_ESP,sp+4)
  if a==0x411230:self.event(3,*self.values(sp+4,2));self.mutate(2)
 def write(self,u,access,p,n,v,_):
  if not self.active:return
  if p==0x84c684:self.event(6,65536,v&255);return
  if 0x83c670<=p<0x84c670:self.event(6,p-0x83c670,v&255);return
  if not BASE<=p<BASE+SIZE:return
  if p==SURFACE+12:self.event(4,self.signed(v))
  elif p in [RECORDS+i*256+0x38 for i in range(3)]:self.event(2,(p-RECORDS-0x38)//256,IMAGES.index(v))
  else:assert BUFFER<=p and p+n<=BUFFER+8192 and n==2,(hex(p),n,hex(v),self.f);self.event(5,p-BUFFER,n,v&65535)
  self.expected[p-BASE:p-BASE+n]=(v&((1<<(8*n))-1)).to_bytes(n,'little')
 def run(self,f):
  self.f=f;self.trace=[];self.mutated=False;u=self.u;u.mem_write(BASE,b'\x5a'*SIZE);u.mem_write(0x83c670,self.table);u.mem_write(0x84c684,b'\x80')
  for i,p in enumerate(IMAGES):u.mem_write(p,synthetic(f,i))
  u.mem_write(BUFFER,b''.join(struct.pack('<H',DEST[i%8]) for i in range(4096)))
  self.ints(SLOTS,[RECORDS+i*256 for i in range(3)]);self.ints(SLOTS2,[RECORDS+i*256 for i in (1,2,0)]);self.put(0x83c64c,SLOTS);self.put(0x83c658,f[25]);self.put(OBJECTVT+0x84,SERVICE);self.put(TYPE+0xac,IMAGES[0])
  for i in range(3):
   r=RECORDS+i*256;self.put(r+0x24,OBJECTS+i*256);self.put(OBJECTS+i*256,OBJECTVT);self.ints(r+0x28,[f[5]+4*i,*f[6:9]]);self.put(r+0x38,IMAGES[i%2] if i or f[2] else 0);u.mem_write(r+0x3c,bytes([f[3] if not i else int(i==2)]))
  self.ints(0x83c600,[0,0,0,0]);self.put(0x83996c,TACTICAL);self.ints(TACTICAL+0xb0,f[9:11]);self.ints(0x839630,f[11:13]);self.ints(INPUT,f[17:21]);self.ints(INPUT+16,f[21:23]);self.put(0x8315b4,ALPHA);self.ints(SURFACE,[VT,f[24],64,0,2,BUFFER])
  for off,v in ((0x10,f[23]),(0x14,SURFACE),(0x18,BUFFER),(0x1c,BUFFER+8192),(0x20,8192),(0x28,f[24])):self.put(ALPHA+off,v)
  self.expected=bytearray(u.mem_read(BASE,SIZE));self.active=True
  try:self.checked_call((0x41f5e0,0x41f1c0,0x41f950)[f[0]],ecx=INPUT+16 if f[0]==1 else INPUT,edx=INPUT,writes=[(BUFFER,8192),(SURFACE+12,4),(RECORDS,3*256),(0x83c670,65536),(0x84c684,1)],inputs=[*RANGES.items(),(VT,136),(0x79b850,1800),(OBJECTVT,136),(TYPE,256)])
  finally:self.active=False
  assert bytes(u.mem_read(BASE,SIZE))==self.expected,'Unrelated alpha arena changed'
  final=[self.word(0x83c658),int(self.word(0x83c64c)==SLOTS2),int(self.mutated),self.word(SURFACE+12),*self.values(INPUT,4),*self.values(TACTICAL+0xb0,2),*self.values(0x839630,2)]
  for i in range(3):final.append(-1 if not self.word(RECORDS+i*256+0x38) else IMAGES.index(self.word(RECORDS+i*256+0x38)))
  return self.trace+['F',*map(str,final),hashlib.sha256(bytes(u.mem_read(BUFFER,8192))).hexdigest(),hashlib.sha256(bytes(u.mem_read(0x83c670,65536))).hexdigest()]
