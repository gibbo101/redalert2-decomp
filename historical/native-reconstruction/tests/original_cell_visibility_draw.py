# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete475520/474260/474510 plus actual alpha addressing; mask/loader are supplied."""
import struct,hashlib
from collections import Counter
from original_presentation import PresentationOracle,STOP
from verify_cell_visibility_draw import RANGES,SERVICES,VT
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EAX,UC_X86_REG_EIP
BASE=0x4a00000;SIZE=0x60000;CELL=BASE+0x100;ALPHA=BASE+0x400;SURFACE=BASE+0x500;INPUT=BASE+0x600;SCENARIO=BASE+0x700;HOUSE=BASE+0x800;IMAGES=(BASE+0x1000,BASE+0x18000);BUFFER=BASE+0x30000
PIXELS=(0,1,63,126,127,128,254,255);DEST=(0,1,63,126,127,128,65535)
def synthetic(f,variant):
 d=bytearray(8+16*24+f[15]*f[16]);struct.pack_into('<h',d,6,16)
 for i in range(16):struct.pack_into('<4h',d,8+24*i,*f[13:17]);struct.pack_into('<I',d,28+24*i,392)
 for i in range(f[15]*f[16]):d[392+i]=PIXELS[(i+3*variant)%len(PIXELS)]
 return bytes(d)
class VisibilityDrawOracle(PresentationOracle):
 def __init__(self,exe,assets):
  super().__init__(exe,allow_patched=True);self.u.mem_map(BASE,SIZE);self.active=False;self.counts=Counter();self.assets=assets
  self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.write)
 def va(self,a):return a
 def word(self,p):return int.from_bytes(self.u.mem_read(p,4),'little')
 def signed(self,n):return (n+2**31)%2**32-2**31
 def values(self,p,n):return [self.signed(self.word(p+4*i)) for i in range(n)]
 def ints(self,p,v):self.u.mem_write(p,struct.pack('<'+'I'*len(v),*[x&0xffffffff for x in v]))
 def event(self,k,a=0,b=0,c=0,d=0):self.trace.extend(map(str,(k,a,b,c,d)))
 def mutate(self,point):
  if self.f[5]!=point or self.mutated:return
  self.mutated=True;self.event(9,point);self.put(SCENARIO,self.word(SCENARIO)^0x1000);self.u.mem_write(HOUSE+0x13d,bytes([self.f[2]^1]));self.u.mem_write(CELL+0x24,struct.pack('<2h',-7,13));self.expected=bytearray(self.u.mem_read(BASE,SIZE))
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  assert a in SERVICES or any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected visibility draw instruction',hex(a))
  if a in RANGES:self.counts[hex(a)]+=1
  sp=u.reg_read(UC_X86_REG_ESP)
  if a in (0x474260,0x474510):
   p,q,frame=self.values(sp+4,3);assert (p,q)==(INPUT,INPUT+16);self.event(1,int(a==0x474510),frame)
   if a==0x474260:self.mutate(2)
  if a==0x6a8d40:
   p,mode=self.values(sp+4,2);assert p==CELL+0x24 and mode in (0,1);x,y=struct.unpack('<2h',u.mem_read(p,4));self.event(2,mode,x,y);self.counts['supplied-mask']+=1
   if not mode:self.mutate(1)
   u.reg_write(UC_X86_REG_EAX,self.f[3+mode]&0xffffffff);u.reg_write(UC_X86_REG_EIP,self.word(sp));u.reg_write(UC_X86_REG_ESP,sp+12)
  if a==0x5956c0:
   name={0x7d2c78:0,0x7d2c70:1}[u.reg_read(UC_X86_REG_ECX)];self.event(3,name,int.from_bytes(u.mem_read(0x850c45,1),'little'),int.from_bytes(u.mem_read(0x850c46,1),'little'));self.counts['supplied-loader']+=1;self.mutate(3)
   u.reg_write(UC_X86_REG_EAX,IMAGES[name]);u.reg_write(UC_X86_REG_EIP,self.word(sp));u.reg_write(UC_X86_REG_ESP,sp+4)
  if a==0x411230:self.event(4,*self.values(sp+4,2));self.mutate(4)
 def write(self,u,access,p,n,v,_):
  if not self.active or not BASE<=p<BASE+SIZE:return
  if p in (CELL+0x120,CELL+0x121):self.event(7,p-CELL,v&255)
  elif p==SURFACE+12:self.event(6,self.signed(v))
  else:assert BUFFER<=p and p+n<=BUFFER+8192 and n==2;self.event(5,p-BUFFER,n,v&65535)
  self.expected[p-BASE:p-BASE+n]=(v&((1<<(8*n))-1)).to_bytes(n,'little')
 def run(self,f):
  self.f=f;self.trace=[];self.mutated=False;u=self.u;u.mem_write(BASE,b'\x5a'*SIZE)
  for i,p in enumerate(IMAGES):u.mem_write(p,self.assets[i] if f[22] else synthetic(f,i))
  for i in range(4096):u.mem_write(BUFFER+2*i,struct.pack('<H',DEST[i%7]))
  self.put(0xa3d290,SCENARIO);self.put(SCENARIO,f[1]);self.put(0xa35db4,HOUSE);u.mem_write(HOUSE+0x13d,bytes([f[2]]));self.put(0x83996c,BASE+0x900)
  self.put(0x8315b4,ALPHA);self.put(0x839634,f[19]);self.put(0x79dad0,f[20]);self.put(0x850bc0,0);self.put(0x850bc4,0);self.put(0x850bc8,0);self.put(0x850bcc,0)
  u.mem_write(0x850c45,bytes([f[21],f[21]]));self.put(0x850c1c,IMAGES[0]);self.put(0x850c18,IMAGES[1]);self.put(0x850bf0,IMAGES[1])
  self.ints(SURFACE,[VT,f[18],64,0,2,BUFFER]);
  for off,v in ((0x10,f[17]),(0x14,SURFACE),(0x18,BUFFER),(0x1c,BUFFER+8192),(0x20,8192),(0x28,f[18])):self.put(ALPHA+off,v)
  u.mem_write(CELL+0x24,struct.pack('<2h',3,5));u.mem_write(CELL+0x120,b'\xab\xcd');self.ints(INPUT,f[7:9]);self.ints(INPUT+16,f[9:13]);self.expected=bytearray(u.mem_read(BASE,SIZE));self.active=True
  entry=(0x475520,0x474260,0x474510)[f[0]];args=[INPUT,INPUT+16]+([] if not f[0] else [f[6]])
  try:self.checked_call(entry,args,CELL,writes=[(CELL+0x120,2),(SURFACE+12,4),(BUFFER,8192),(0x850c45,2),(0x850c18,8),(0x850bf0,4)],inputs=[*RANGES.items(),(VT,136)])
  finally:self.active=False
  assert bytes(u.mem_read(BASE,SIZE))==self.expected,'Unrelated visibility draw arena changed'
  final=[*u.mem_read(CELL+0x120,2),*struct.unpack('<2h',u.mem_read(CELL+0x24,4)),self.word(SCENARIO),*u.mem_read(HOUSE+0x13d,1),*u.mem_read(0x850c45,2),self.word(SURFACE+12)]
  return self.trace+['F',*map(str,final),hashlib.sha256(bytes(u.mem_read(BUFFER,8192))).hexdigest()]
