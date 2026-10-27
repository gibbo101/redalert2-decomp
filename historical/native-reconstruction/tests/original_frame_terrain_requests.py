# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete6A3EF0; height, terrain/animation/rectangle draws and alpha are named services."""
import struct
from collections import Counter
from original_presentation import PresentationOracle,STOP,STACK
from verify_frame_terrain_requests import RANGES,SERVICES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_READ
from unicorn.x86_const import UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EAX,UC_X86_REG_EIP,UC_X86_REG_EDX
BASE=0x4900000;SIZE=0x10000;TACTICAL=BASE+0x1000;CELLS=BASE+0x3000;REGIONS=(BASE+0x4000,BASE+0x4100);INPUT=BASE+0x5000;ALPHA=BASE+0x6000
class FrameTerrainOracle(PresentationOracle):
 def __init__(self,exe):
  super().__init__(exe,allow_patched=True);self.u.mem_map(BASE,SIZE);self.active=False;self.counts=Counter()
  self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_READ,self.read)
 def va(self,a):return a
 def word(self,p):return int.from_bytes(self.u.mem_read(p,4),'little')
 def signed(self,v):return (v+2**31)%2**32-2**31
 def ints(self,p,v):self.u.mem_write(p,struct.pack('<'+'I'*len(v),*[x&0xffffffff for x in v]))
 def values(self,p,n):return [self.signed(self.word(p+4*i)) for i in range(n)]
 def event(self,k,a=0,b=0,c=0,d=0):self.trace.extend(map(str,(k,a,b,c,d)))
 def mutate(self,point):
  m=self.mode
  if not m or self.mutated or point!={1:1,2:1,3:2,4:3,5:3,6:5,7:6,8:6,9:2,10:5,11:4,12:6}[m]:return
  self.mutated=True;self.event(15,m)
  if m in (1,4):self.put(TACTICAL+0xe0,0)
  if m==2:self.put(TACTICAL+0xe0,3);self.ints(TACTICAL+0xe8,[CELLS+128,CELLS+64])
  if m==3:self.put(0xb263d8,0)
  if m==5:self.ints(TACTICAL+0xb0,[17,-23]);self.ints(0x839630,[9,11,180,140]);self.ints(INPUT+16,[7,8,19,20])
  if m==6:self.put(0xabe5c0,3)
  if m==7:self.put(0xabe5b4,REGIONS[1]);self.put(0xabe5c0,0)
  if m==8:self.put(0xabe5b4,REGIONS[1])
  if m==9:self.put(TACTICAL+0xe4,CELLS+128)
  if m==10:self.ints(INPUT+16,[21,22,23,24])
  if m==11:self.put(0xabe5c0,3);self.put(0xabe5b4,REGIONS[1])
  if m==12:self.ints(0x839630,[11,13,100,90])
  self.expected=bytes(self.u.mem_read(BASE,SIZE))
 def read(self,u,access,p,n,v,_):
  if not self.active:return
  if p==TACTICAL+0xe0:self.event(1,self.signed(self.word(p)))
  if TACTICAL+0xe4<=p<TACTICAL+0xf0:self.event(2,(p-TACTICAL-0xe4)//4,(self.word(p)-CELLS)//64)
  if any(p==CELLS+64*i+0x24 for i in range(3)):
   self.center=(p-CELLS-0x24)//64;x,y=struct.unpack('<2h',u.mem_read(p,4));self.event(3,self.center,x,y)
  if p==0xb263d8:self.event(6,int(bool(self.word(p))))
  if p==0xabe5c0:self.event(11,self.signed(self.word(p)))
  if p==0xabe5b4:self.event(12,REGIONS.index(self.word(p)))
  for base in REGIONS:
   if base<=p<base+60 and (p-base)%20==16:self.event(13,(p-base)//20,int.from_bytes(u.mem_read(p,1),'little'))
 def ret(self,sp,args):
  self.u.reg_write(UC_X86_REG_EAX,0x123 if args==1 and self.service==0x4706c0 else 0);self.u.reg_write(UC_X86_REG_EIP,self.word(sp));self.u.reg_write(UC_X86_REG_ESP,sp+4+4*args)
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  assert a in SERVICES or any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected frame terrain instruction',hex(a))
  if a in RANGES:self.counts[hex(a)]+=1
  sp=u.reg_read(UC_X86_REG_ESP);self.service=a
  if a==0x4706c0:
   assert u.reg_read(UC_X86_REG_ECX)==CELLS+64*self.center;self.event(4,self.center);self.counts['height']+=1;self.mutate(1);self.ret(sp,1)
  if a==0x6a27a0:
   assert u.reg_read(UC_X86_REG_ECX)==TACTICAL;self.event(5,*self.values(self.word(sp+8),3));self.mutate(2)
  if a==0x475520:
   cell=(u.reg_read(UC_X86_REG_ECX)-CELLS)//64;p,q=self.values(sp+4,2);assert q==INPUT+32
   self.event(7,cell,*self.values(p,2),1);self.event(8,*self.values(q,4));self.counts['terrain']+=1;self.mutate(3);self.ret(sp,2)
  if a==0x41f1c0:
   p=u.reg_read(UC_X86_REG_ECX);q=u.reg_read(UC_X86_REG_EDX);assert q==INPUT+32
   self.event(9,*self.values(p,2),1);self.event(8,*self.values(q,4));self.counts['animation']+=1;self.mutate(4);self.ret(sp,0)
  if a==0x6a7820:
   assert u.reg_read(UC_X86_REG_ECX)==TACTICAL;p=self.word(sp+4)
   kind={0x839630:0,INPUT:1,INPUT+16:2}.get(p,3);assert kind!=3 or STACK-0x2000<=p<STACK
   self.event(10,kind);self.event(8,*self.values(p,4));self.counts['rectangle']+=1;self.mutate(5);self.ret(sp,1)
  if a==0x4110b0:
   assert u.reg_read(UC_X86_REG_ECX)==ALPHA;self.event(14,*self.values(sp+4,4));self.counts['alpha']+=1;self.mutate(6);self.ret(sp,4)
 def run(self,f):
  self.mode,count,dirty,full=f[:4];self.trace=[];self.mutated=False;self.u.mem_write(BASE,b'\x5a'*SIZE)
  self.ints(TACTICAL+0xb0,f[4:6]);self.put(TACTICAL+0xe0,count);self.ints(TACTICAL+0xe4,[CELLS+64*i for i in f[22:25]])
  for i in range(3):self.u.mem_write(CELLS+64*i+0x24,struct.pack('<2h',*f[25+2*i:27+2*i]))
  for base,order in zip(REGIONS,((0,1,2),(2,1,0))):
   for j,i in enumerate(order):self.ints(base+20*j,f[31+5*i:36+5*i])
  self.ints(INPUT,f[10:22]);self.ints(0x839630,f[6:10]);self.put(0xabe5c0,dirty);self.put(0xabe5b4,REGIONS[0]);self.put(0x8315b4,ALPHA);self.put(0xb263d8,f[46]);self.u.mem_write(0xabe490,struct.pack('<d',.125))
  self.expected=bytes(self.u.mem_read(BASE,SIZE));self.active=True
  try:self.checked_call(0x6a3ef0,[INPUT,INPUT+16,INPUT+32,full],TACTICAL,inputs=[*RANGES.items(),(0xabe490,8)])
  finally:self.active=False
  assert bytes(self.u.mem_read(BASE,SIZE))==self.expected,'Unrelated frame terrain arena changed'
  final=[self.signed(self.word(TACTICAL+0xe0)),self.signed(self.word(0xabe5c0)),REGIONS.index(self.word(0xabe5b4)),*self.values(TACTICAL+0xb0,2),*self.values(0x839630,4),*self.values(INPUT,12),*[(self.word(TACTICAL+0xe4+4*i)-CELLS)//64 for i in range(3)]]
  for i in range(3):final.extend(struct.unpack('<2h',self.u.mem_read(CELLS+64*i+0x24,4)))
  final.append(int(bool(self.word(0xb263d8))))
  for base in REGIONS:final.extend(self.values(base,15))
  return self.trace+['F',*map(str,final)]
