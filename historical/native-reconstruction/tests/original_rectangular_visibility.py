# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete rectangle parent; actual numerical children, named map/draw services."""
import struct
from collections import Counter
from original_presentation import PresentationOracle,STOP,STACK
from verify_rectangular_visibility import RANGES,SERVICES
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_ECX,UC_X86_REG_EDX,UC_X86_REG_ESP,UC_X86_REG_EAX,UC_X86_REG_EIP
BASE=0x4b00000;SIZE=0x10000;TACTICAL=BASE+0x1000;CELL=BASE+0x3000;INPUT=BASE+0x4000
class RectangularVisibilityOracle(PresentationOracle):
 def __init__(self,exe):
  super().__init__(exe,allow_patched=True);self.u.mem_map(BASE,SIZE);self.active=False;self.counts=Counter();self.u.hook_add(UC_HOOK_CODE,self.code)
 def va(self,a):return a
 def word(self,p):return int.from_bytes(self.u.mem_read(p,4),'little')
 def signed(self,n):return (n+2**31)%2**32-2**31
 def values(self,p,n):return [self.signed(self.word(p+4*i)) for i in range(n)]
 def ints(self,p,v):self.u.mem_write(p,struct.pack('<'+'I'*len(v),*[x&0xffffffff for x in v]))
 def event(self,k,a=0,b=0,c=0,d=0):self.trace.extend(map(str,(k,a,b,c,d)))
 def mutate(self,point):
  if not self.f[0] or self.mutated or point!={1:1,2:2,3:3,4:4,5:5,6:6,7:1}[self.f[0]]:return
  self.mutated=True;self.event(9,self.f[0])
  if self.f[0]==1:self.ints(INPUT+8,[-240,-255])
  if self.f[0] in (2,3,5):self.ints(TACTICAL+0xb0,[17,-23]);self.ints(0x839630,[9,11,180,140]);self.ints(INPUT,[7,8,95,75])
  if self.f[0] in (2,7):self.put(0xb263d8,0)
  if self.f[0]==4:self.ints(INPUT,[1,2,3,4]);self.u.mem_write(CELL+0x24,struct.pack('<2h',-7,13))
  if self.f[0]==6:self.ints(INPUT,[31,32,33,34])
  self.expected=bytes(self.u.mem_read(BASE,SIZE))
 def ret(self,sp,args,result=0):
  self.u.reg_write(UC_X86_REG_EAX,result&0xffffffff);self.u.reg_write(UC_X86_REG_EIP,self.word(sp));self.u.reg_write(UC_X86_REG_ESP,sp+4+4*args)
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  assert a in SERVICES or any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected rectangular visibility instruction',hex(a))
  if a in RANGES:self.counts[hex(a)]+=1
  sp=u.reg_read(UC_X86_REG_ESP)
  if a==0x548000:
   assert u.reg_read(UC_X86_REG_ECX)==0x8324e0;self.event(1,*self.values(self.word(sp+4),3));self.counts['coordinate']+=1;self.mutate(1);self.ret(sp,1,CELL)
  if a==0x54aab0:
   x,y=struct.unpack('<2h',u.mem_read(self.word(sp+4),4));self.event(3,x,y,self.f[2]&255);self.counts['permission']+=1;self.mutate(2);self.ret(sp,1,self.f[2])
  if a==0x548070:
   x,y=struct.unpack('<2h',u.mem_read(self.word(sp+4),4));i=(x*3+y*7)%3;self.event(4,x,y,i);self.counts['lookup']+=1;self.mutate(3);self.ret(sp,1,CELL+64*(i+1))
  if a==0x6a27a0:self.event(5,*self.values(self.word(sp+8),3));self.mutate(5)
  if a==0x475520:
   i=(u.reg_read(UC_X86_REG_ECX)-CELL)//64-1;p,q=self.values(sp+4,2);assert STACK-0x2000<=p<STACK and STACK-0x2000<=q<STACK
   self.event(6,i,*self.values(p,2));self.event(7,*self.values(q,4));self.counts['draw']+=1;self.mutate(4);self.ret(sp,2)
  if a==0x41f5e0:
   assert u.reg_read(UC_X86_REG_ECX)==INPUT;self.event(8,*self.values(INPUT,4));self.counts['animation']+=1;self.mutate(6);self.ret(sp,0)
  if a==0x6a7932:self.event(2,int(bool(self.word(0xb263d8))))
 def run(self,f):
  self.f=f;self.trace=[];self.mutated=False;self.u.mem_write(BASE,b'\x5a'*SIZE)
  self.ints(TACTICAL+0xb0,f[9:11]);self.ints(INPUT,f[5:9]);self.ints(0x839630,f[11:15]);self.u.mem_write(CELL+0x24,struct.pack('<2h',*f[3:5]));self.ints(TACTICAL+0xde4,f[15:]);self.put(0xb263d8,f[1]);self.u.mem_write(0xabe490,struct.pack('<d',.125));self.expected=bytes(self.u.mem_read(BASE,SIZE));self.active=True
  try:self.checked_call(0x6a7820,[INPUT],TACTICAL,inputs=[*RANGES.items(),(0xabe490,8)])
  finally:self.active=False
  assert bytes(self.u.mem_read(BASE,SIZE))==self.expected,'Unrelated rectangle arena changed'
  final=[*self.values(TACTICAL+0xb0,2),*self.values(0x839630,4),*self.values(INPUT,4),*struct.unpack('<2h',self.u.mem_read(CELL+0x24,4)),int(bool(self.word(0xb263d8))),int(self.mutated)]
  return self.trace+['F',*map(str,final)]
