# SPDX-License-Identifier: GPL-3.0-or-later
"""Original4754B0 ->52C230, real depth/alpha/stock/cache children, supplied getter."""
import struct,hashlib
from collections import Counter
from original_presentation import PresentationOracle,ARG,STOP
from verify_terrain_depth_pass import RANGES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_ESP,UC_X86_REG_ECX,UC_X86_REG_EAX,UC_X86_REG_EIP
BASE=0x1600000;SIZE=0x400000
DEST=BASE;ZS=BASE+0x200;AS=BASE+0x300;Z=BASE+0x400;A=BASE+0x500;CVT=BASE+0x600;TYPE=BASE+0x1000;VT=TYPE+0x400;CELL=TYPE+0x800
HEADER=0x16e0000;COLOR=0x1700000;ZDATA=0x1780000;ADATA=0x1800000;ENTRY=0x1900000;GET=0x1101000
N=96*96*2
class TerrainDepthOracle(PresentationOracle):
 def va(self,a):return a
 def __init__(self,exe,blob):
  super().__init__(exe,allow_patched=True);self.u.mem_map(BASE,SIZE);self.blob=blob;self.active=False;self.counts=Counter();self.stores=0;self.cold=True
  self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.write)
 def word(self,p):return int.from_bytes(self.u.mem_read(p,4),'little')
 def signed(self,v):return (v+2**31)%2**32-2**31
 def event(self,*v):self.trace.extend(map(str,v))
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  assert a==GET or any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected terrain instruction',hex(a))
  if a in RANGES or a in (0x52c8cf,0x52cf48):self.counts[hex(a)]+=1
  if a==0x41e537:raise AssertionError('Entered unsupported cache free')
  sp=u.reg_read(UC_X86_REG_ESP);receiver=u.reg_read(UC_X86_REG_ECX)
  if a==0x52c230:
   args=[self.signed(self.word(sp+4+4*i)) for i in range(17)]
   assert args[:3]==[0 if self.f[9] else CVT,0,DEST] and args[9:]==[self.f[11],self.f[12],1,0,0,1,0,0]
   self.event('C',*args[3:])
  if a==0x41e3e0:self.event('A',self.word(sp+4))
  if a==0x41e510:self.event('R')
  if a==GET:
   self.event('H');u.reg_write(UC_X86_REG_EAX,0 if self.f[10] else HEADER);u.reg_write(UC_X86_REG_EIP,self.word(sp));u.reg_write(UC_X86_REG_ESP,sp+4);return
  if a==0x4113b0 and receiver==DEST:self.event('B',self.signed(self.word(DEST+16)))
  if a==0x4113c0 and receiver==DEST:self.event('P',192)
  if a==0x411370 and receiver==DEST:self.event('L',self.signed(self.word(sp+4)),self.signed(self.word(sp+8)))
  if a==0x4112f0 and receiver==DEST:self.event('U')
  if a in (0x776340,0x411230):self.event('Z' if a==0x776340 else 'Q',self.signed(self.word(sp+4)),self.signed(self.word(sp+8)))
 def write(self,u,access,p,n,v,_):
  if not self.active:return
  if ZDATA<=p<ZDATA+N:
   assert n==2 and (v&65535)==65535,(self.f,hex(p),n,hex(v),hex(u.reg_read(UC_X86_REG_EIP)));v&=65535;self.event('W',p-ZDATA,n,v);self.stores+=1
  if p==ENTRY+0x20004:self.event('T',self.signed(v))
  if p in (DEST+12,ZS+12,AS+12):self.event('K',(DEST,ZS,AS).index(p-12),self.signed(v))
  if BASE<=p and p+n<=BASE+SIZE:self.expected[p-BASE:p-BASE+n]=int(v&((1<<(8*n))-1)).to_bytes(n,'little')
 def run(self,f):
  # x,y,clip4,depth scroll,viewportY,bpp,null converter,null header,level,brightness,retained refs,bypass
  self.f=f;x,y,cx,cy,cw,ch,offset,vy,bpp,nullc,nullh,level,brightness,refs,bypass=f;self.trace=[]
  self.u.mem_write(BASE,b'\xa5'*SIZE)
  for obj,ptr,fmt in ((DEST,COLOR,bpp),(ZS,ZDATA,2),(AS,ADATA,2)):
   for off,value in ((0,0x79aef8),(4,96),(8,96),(12,0),(16,fmt),(20,ptr),(24,N)):self.put(obj+off,value)
  for obj,surf,ptr,delta in ((Z,ZS,ZDATA,offset),(A,AS,ADATA,0)):
   for off,value in ((0x10,delta),(0x14,surf),(0x18,ptr),(0x1c,ptr+N),(0x20,N),(0x24,32768),(0x28,96)):self.put(obj+off,value)
  for p,v in ((0x839c6c,Z),(0x8315b4,A),(0x839634,vy),(0x83995c,DEST),(0x83239c,TYPE+0x600),(TYPE+0x600,0 if nullc else CVT),(0xa40cd4,TYPE+0x604),(TYPE+0x604,TYPE),(TYPE,VT),(VT+0x9c,GET),(CVT+0x16c,53),(CVT+0x170,ENTRY),(0x83c5e8,1),(0x83c5dc,TYPE+0x608),(TYPE+0x608,ENTRY),(ENTRY+0x20000,53),(ENTRY+0x20004,refs)):self.put(p,v)
  self.u.mem_write(CELL+0x10c,struct.pack('<h',brightness));self.u.mem_write(CELL+0x11b,struct.pack('<b',level))
  self.u.mem_write(HEADER,self.blob);cols,rows=struct.unpack_from('<II',self.blob)
  for i in range(cols*rows):
   p=struct.unpack_from('<I',self.blob,16+4*i)[0]
   if p:self.put(HEADER+16+4*i,HEADER+p)
  for ptr in (COLOR,ZDATA,ADATA):self.u.mem_write(ptr,bytes((i*29+0x34)&255 for i in range(N)))
  self.u.mem_write(0xa6e395,bytes([0 if self.cold else 1]));self.cold=False;self.u.mem_write(0xa6e394,bytes([bypass]));self.put(0x852fd0,0xffff)
  self.u.mem_write(ARG,struct.pack('<6i',x,y,cx,cy,cw,ch));self.expected=bytearray(self.u.mem_read(BASE,SIZE));self.active=True
  scratch=[(0xa52f08,0x6a),(0xa52594,1800),(0xa53398,108000),(0xa6cf68,3600),(0xa6e395,1)]
  writes=[(ZDATA,N),(DEST+12,4),(ZS+12,4),(AS+12,4),(ENTRY+0x20004,4),*scratch]
  inputs=[*RANGES.items(),(0x79aef8,136),(VT,0xa0),(HEADER,len(self.blob)),(COLOR,N),(ADATA,N),(ARG,24),(CELL,0x120),(0x7a4a28,1800)]
  try:self.checked_call(0x4754b0,[ARG,ARG+8],CELL,writes=writes,inputs=inputs)
  finally:self.active=False
  assert bytes(self.u.mem_read(BASE,SIZE))==self.expected,'Unrelated terrain arena mutation'
  return self.trace+['F',*(str(self.signed(self.word(p))) for p in (DEST+12,ZS+12,AS+12,ENTRY+0x20004)),*(hashlib.sha256(bytes(self.u.mem_read(p,N))).hexdigest() for p in (COLOR,ZDATA,ADATA))]
