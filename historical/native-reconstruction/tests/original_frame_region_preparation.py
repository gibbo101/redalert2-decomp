# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete6A33F0 with actual geometry children and named height/depth/terrain services."""
import struct
from collections import Counter
from original_presentation import PresentationOracle,STOP,STACK
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_READ,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EAX,UC_X86_REG_EIP
BASE=0x4500000;SIZE=0x10000;TACTICAL=BASE+0x1000;CELLS=BASE+0x3000;REGIONS=(BASE+0x4000,BASE+0x4100);INPUT=BASE+0x5000;DEPTH=BASE+0x6000
class FrameRegionOracle(PresentationOracle):
 def __init__(self,exe):
  super().__init__(exe,allow_patched=True);self.u.mem_map(BASE,SIZE);self.active=False;self.counts=Counter()
  self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_READ,self.read);self.u.hook_add(UC_HOOK_MEM_WRITE,self.write)
 def va(self,a):return a
 def word(self,p):return int.from_bytes(self.u.mem_read(p,4),'little')
 def signed(self,v):return (v+2**31)%2**32-2**31
 def ints(self,p,v):self.u.mem_write(p,struct.pack('<'+'I'*len(v),*[x&0xffffffff for x in v]))
 def values(self,p,n):return [self.signed(self.word(p+4*i)) for i in range(n)]
 def event(self,k,a=0,b=0,c=0,d=0):self.trace.extend(map(str,(k,a,b,c,d)))
 def mutate(self,point):
  m=self.mode
  if self.mutated or not m:return
  target=1 if m<=5 or m==11 else (2 if m<=8 else (3 if m==9 else 4))
  if point!=target:return
  self.mutated=True;self.event(14,m)
  if m in (1,11):self.put(0xabe5c0,0)
  if m==2:self.put(0xabe5c0,3)
  if m in (3,11):self.put(0xabe5b4,REGIONS[1])
  if m==4:self.ints(self.word(0xabe5b4),[51,52,13,14])
  if m==5:self.ints(0x839630,[9,11,180,140]);self.ints(TACTICAL+0xb0,[17,-23])
  if m==6:self.ints(TACTICAL+0xb0,[17,-23])
  if m==7:self.put(TACTICAL+0xe0,0)
  if m==8:self.put(TACTICAL+0xe0,3);self.ints(TACTICAL+0xe8,[CELLS+128,CELLS+64])
  if m==9:self.put(TACTICAL+0xe4,CELLS+128)
  if m==10:self.put(0xb263d8,0)
 def read(self,u,access,p,n,v,_):
  if not self.active:return
  if p==0xabe5c0:self.event(1,self.signed(self.word(p)))
  if p==0xabe5b4:self.event(2,REGIONS.index(self.word(p)))
  if p==TACTICAL+0xe0:self.event(6,self.signed(self.word(p)))
  if TACTICAL+0xe4<=p<TACTICAL+0xf0:self.event(7,(p-TACTICAL-0xe4)//4,(self.word(p)-CELLS)//64)
  if any(p==CELLS+64*i+0x24 for i in range(3)):
   self.center=(p-CELLS-0x24)//64;x,y=struct.unpack('<2h',u.mem_read(p,4));self.event(8,self.center,x,y)
  if p==0xb263d8:self.event(11,int(bool(self.word(p))));self.mutate(3)
 def write(self,u,access,p,n,v,_):
  if not self.active:return
  if p==0xabe5c0:self.event(4,self.signed(v))
  for base in REGIONS:
   if base<=p<base+60:
    assert n==4 and (p-base)%4==0;self.event(3,(p-base)//20,((p-base)%20)//4,self.signed(v))
 def service_return(self,sp,args,result=0):
  self.u.reg_write(UC_X86_REG_EAX,result);self.u.reg_write(UC_X86_REG_EIP,self.word(sp));self.u.reg_write(UC_X86_REG_ESP,sp+4+4*args)
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  if a in (0x6a33f0,0x475d60,0x47d040,0x453e40,0x6a27a0,0x41fdf0):self.counts[hex(a)]+=1
  sp=u.reg_read(UC_X86_REG_ESP)
  if a==0x4706c0:
   assert u.reg_read(UC_X86_REG_ECX)==CELLS+64*self.center;self.event(9,self.center);self.counts['height']+=1;self.service_return(sp,1,0x123)
  if a==0x6a27a0:
   assert u.reg_read(UC_X86_REG_ECX)==TACTICAL;self.event(10,*self.values(self.word(sp+8),3));self.mutate(2)
  if a==0x7761c0:
   assert u.reg_read(UC_X86_REG_ECX)==DEPTH;self.event(5,*self.values(sp+4,4));self.counts['depth']+=1;self.mutate(1);self.service_return(sp,4)
  if a==0x4754b0:
   cell=(u.reg_read(UC_X86_REG_ECX)-CELLS)//64;p,q=self.values(sp+4,2);assert q==INPUT
   self.event(12,cell,*self.values(p,2),1);self.event(13,*self.values(q,4));self.counts['terrain']+=1;self.mutate(4);self.service_return(sp,2)
 def run(self,f):
  self.mode,count,dirty,full=f[:4];self.trace=[];self.mutated=False;self.u.mem_write(BASE,b'\x5a'*SIZE)
  self.ints(TACTICAL+0xb0,f[4:6]);self.put(TACTICAL+0xe0,count);self.ints(TACTICAL+0xe4,[CELLS+64*i for i in f[16:19]])
  for i in range(3):self.u.mem_write(CELLS+64*i+0x24,struct.pack('<2h',*f[19+2*i:21+2*i]))
  for base,order in zip(REGIONS,((0,1,2),(2,1,0))):
   for j,i in enumerate(order):self.ints(base+20*j,[*f[25+4*i:29+4*i],17+i])
  self.ints(INPUT,f[12:16]);self.ints(0x839630,f[6:10]);self.put(0xabe5c0,dirty);self.put(0xabe5b4,REGIONS[0]);self.put(0x839c6c,DEPTH);self.put(0xb263d8,f[37]);self.u.mem_write(0xabe490,struct.pack('<d',.125))
  arena=bytes(self.u.mem_read(BASE,SIZE));self.active=True
  from verify_frame_region_preparation import RANGES
  try:self.checked_call(0x6a33f0,[full,f[10],f[11],INPUT],TACTICAL,writes=[(base,60) for base in REGIONS]+[(0xabe5c0,4)],inputs=[*RANGES.items(),(0xabe490,8),(INPUT,16)])
  finally:self.active=False
  after=bytes(self.u.mem_read(BASE,SIZE))
  # Only region bytes and explicit service mutations may change the arena.
  allowed=[(b-BASE,b-BASE+60) for b in REGIONS]+[(TACTICAL-BASE+0xb0,TACTICAL-BASE+0xb8),(TACTICAL-BASE+0xe0,TACTICAL-BASE+0xf0)]
  assert all(a==b or any(lo<=i<hi for lo,hi in allowed) for i,(a,b) in enumerate(zip(arena,after))),'Unrelated frame arena changed'
  final=[self.signed(self.word(TACTICAL+0xe0)),self.signed(self.word(0xabe5c0)),REGIONS.index(self.word(0xabe5b4)),*self.values(TACTICAL+0xb0,2),*self.values(0x839630,4),*[(self.word(TACTICAL+0xe4+4*i)-CELLS)//64 for i in range(3)]]
  for i in range(3):final.extend(struct.unpack('<2h',self.u.mem_read(CELLS+64*i+0x24,4)))
  final.append(int(bool(self.word(0xb263d8))))
  for base in REGIONS:final.extend(self.values(base,15))
  self.trace.extend(['F',*map(str,final)]);return self.trace
