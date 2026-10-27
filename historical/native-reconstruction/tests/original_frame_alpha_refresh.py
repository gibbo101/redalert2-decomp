# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete4110B0 and stock surface virtuals, including ordered stores."""
import struct,hashlib
from collections import Counter
from original_presentation import PresentationOracle,STOP
from verify_frame_alpha_refresh import RANGES,VT
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_READ,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_ECX,UC_X86_REG_ESP
BASE=0x4700000;SIZE=0x10000;OBJ=BASE+0x100;SURFACES=(BASE+0x200,BASE+0x300);BUFFER=BASE+0x2000
class FrameAlphaOracle(PresentationOracle):
 def __init__(self,exe):
  super().__init__(exe,allow_patched=True);self.u.mem_map(BASE,SIZE);self.active=False;self.counts=Counter()
  self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_READ,self.read);self.u.hook_add(UC_HOOK_MEM_WRITE,self.write)
 def va(self,a):return a
 def word(self,p):return int.from_bytes(self.u.mem_read(p,4),'little')
 def signed(self,v):return (v+2**31)%2**32-2**31
 def values(self,p,n):return [self.signed(self.word(p+4*i)) for i in range(n)]
 def event(self,k,a=0,b=0,c=0,d=0):self.trace.extend(map(str,(k,a,b,c,d)))
 def mutate(self,point):
  m=self.mode
  if self.mutated or not m or point!=(2 if m in (6,7) else 1):return
  self.mutated=True;self.event(10,m)
  if m in (1,6):self.put(OBJ+0x14,SURFACES[1])
  if m in (2,7):self.put(OBJ+0x10,2)
  if m==3:self.put(OBJ+0x28,0)
  if m==4:self.put(OBJ+0x1c,BUFFER+self.initial_begin+160);self.put(OBJ+0x20,160);self.put(OBJ+0x28,5)
  if m==5:self.put(SURFACES[0]+0x14,BUFFER+self.initial_offset+4);self.put(SURFACES[0]+4,12)
  # Authored service mutation, with exact arena audit below.
  self.expected=bytearray(self.u.mem_read(BASE,SIZE))
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  assert any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected alpha instruction',hex(a))
  if a in RANGES:self.counts[hex(a)]+=1
  if a not in (0x411370,0x4112f0,0x4113b0,0x4113c0,0x4112c0):return
  i=SURFACES.index(u.reg_read(UC_X86_REG_ECX));sp=u.reg_read(UC_X86_REG_ESP)
  if a==0x411370:self.event(2,i,*self.values(sp+4,2))
  if a==0x4112f0:self.event(7,i);self.mutate(2)
  if a==0x4113b0:self.event(4,i,self.signed(self.word(SURFACES[i]+16)))
  if a==0x4113c0:self.event(5,i)
  if a==0x4112c0:self.event(6,i,self.signed(self.word(SURFACES[i]+4)));self.mutate(1)
 def read(self,u,access,p,n,v,_):
  if not self.active:return
  if p==OBJ+0x14:self.event(1,SURFACES.index(self.word(p)))
  if p in (OBJ+0x10,OBJ+0x18,OBJ+0x1c,OBJ+0x20,OBJ+0x28):
   value=self.word(p);value=value-BUFFER if p in (OBJ+0x18,OBJ+0x1c) else value
   self.event(8,p-OBJ,self.signed(value))
 def write(self,u,access,p,n,v,_):
  if not self.active or not BASE<=p<BASE+SIZE:return
  if p in (SURFACES[0]+12,SURFACES[1]+12):self.event(3,SURFACES.index(p-12),self.signed(v))
  else:assert BUFFER<=p and p+n<=BUFFER+2048 and n in (2,4);self.event(9,p-BUFFER,n,v&((1<<(8*n))-1))
  self.expected[p-BASE:p-BASE+n]=int(v&((1<<(8*n))-1)).to_bytes(n,'little')
 def run(self,f):
  self.mode,width,bpp,offset,lock0,lock1,delta,begin,end,extent,stride,x,y,w,h,words=f
  self.initial_begin=begin;self.initial_offset=offset;self.trace=[];self.mutated=False;self.u.mem_write(BASE,b'\xa5'*SIZE)
  for i,lock in enumerate((lock0,lock1)):
   for off,value in ((0,VT),(4,width+2*i),(8,16),(12,lock),(16,bpp),(20,BUFFER+offset+4*i)):self.put(SURFACES[i]+off,value)
  for off,value in ((0x10,delta),(0x14,SURFACES[0]),(0x18,BUFFER+begin),(0x1c,BUFFER+end),(0x20,extent),(0x28,stride)):self.put(OBJ+off,value)
  self.u.mem_write(BUFFER,bytes((i*29+0x34)&255 for i in range(2048)));self.expected=bytearray(self.u.mem_read(BASE,SIZE));self.active=True
  try:self.checked_call(0x4110b0,[x,y,w,h],OBJ,writes=[(SURFACES[0]+12,4),(SURFACES[1]+12,4),(BUFFER,2048)],inputs=[*RANGES.items(),(VT,136)])
  finally:self.active=False
  assert bytes(self.u.mem_read(BASE,SIZE))==self.expected,'Unrelated alpha arena changed'
  final=[*(self.signed(self.word(s+12)) for s in SURFACES),SURFACES.index(self.word(OBJ+0x14)),self.signed(self.word(OBJ+0x10)),self.word(OBJ+0x18)-BUFFER,self.word(OBJ+0x1c)-BUFFER,self.signed(self.word(OBJ+0x20)),self.signed(self.word(OBJ+0x28)),*(self.signed(self.word(s+4)) for s in SURFACES),*(self.word(s+20)-BUFFER for s in SURFACES)]
  return self.trace+['F',*map(str,final),hashlib.sha256(bytes(self.u.mem_read(BUFFER,2048))).hexdigest()]
