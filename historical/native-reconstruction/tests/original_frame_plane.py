# SPDX-License-Identifier: GPL-3.0-or-later
import struct,hashlib
from collections import Counter
from original_presentation import PresentationOracle,STOP
from verify_frame_plane import RANGES,VT
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_ECX,UC_X86_REG_ESP
BASE=0x4800000;SIZE=0x10000;OBJ=BASE+0x100;SURF=BASE+0x200;BUFFER=BASE+0x2000
class FramePlaneOracle(PresentationOracle):
 def va(self,a):return a
 def __init__(self,exe):
  super().__init__(exe,allow_patched=True);self.u.mem_map(BASE,SIZE);self.active=False;self.counts=Counter();self.pixel_stores=0;self.field_stores=0
  self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.write)
 def word(self,p):return int.from_bytes(self.u.mem_read(p,4),'little')
 def signed(self,v):return (v+2**31)%2**32-2**31
 def event(self,k,a=0,b=0,c=0,d=0,e=0):self.trace.extend(map(str,(k,a,b,c,d,e)))
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  assert any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected frame plane instruction',hex(a))
  if a in RANGES:self.counts[hex(a)]+=1
  if a==0x774390:
   sp=u.reg_read(UC_X86_REG_ESP);r=self.word(sp+4);self.event(1,*(self.signed(self.word(r+4*i)) for i in range(4)),self.word(sp+8))
 def write(self,u,access,p,n,v,_):
  if not self.active or not BASE<=p<BASE+SIZE:return
  value=v&((1<<(8*n))-1)
  if BUFFER<=p and p+n<=BUFFER+2048:self.event(2,p-BUFFER,n,value);self.pixel_stores+=1
  elif p in (OBJ+0x10,OBJ+0x24):self.event(3,p-OBJ,self.signed(value));self.field_stores+=1
  else:assert p==SURF+12;self.event(4,self.signed(value))
  self.expected[p-BASE:p-BASE+n]=value.to_bytes(n,'little')
 def run(self,f):
  op,w,h,begin,initial,base,dx,dy,color,lock,words=f;self.u.mem_write(BASE,b'\xa5'*SIZE);self.trace=[]
  for off,value in ((0,VT),(4,w),(8,h),(12,lock),(16,2),(20,BUFFER+begin)):self.put(SURF+off,value)
  for off,value in ((0x10,initial),(0x14,SURF),(0x18,BUFFER+begin),(0x1c,BUFFER+begin+w*h*2),(0x20,w*h*2),(0x24,base),(0x28,w),(0x2c,h)):self.put(OBJ+off,value)
  self.u.mem_write(BUFFER,bytes((i*29+0x34)&255 for i in range(2048)));self.expected=bytearray(self.u.mem_read(BASE,SIZE));self.active=True
  try:self.checked_call((0x775d60,0x410c50,0x776160,0x411050)[op],[dx,dy,color] if op<2 else [color],OBJ,writes=[(OBJ+0x10,4),(OBJ+0x24,4),(SURF+12,4),(BUFFER,2048)],inputs=[*RANGES.items(),(VT,136)])
  finally:self.active=False
  assert bytes(self.u.mem_read(BASE,SIZE))==self.expected,'Unrelated frame plane arena changed'
  return self.trace+['F',*(str(self.signed(self.word(p))) for p in (OBJ+0x10,OBJ+0x24,SURF+12)),hashlib.sha256(bytes(self.u.mem_read(BUFFER,2048))).hexdigest()]
