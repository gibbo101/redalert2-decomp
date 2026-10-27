# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete6A4100/coordinate/projection; scan is an explicit mutable service."""
import struct
from collections import Counter
from original_presentation import PresentationOracle,STOP,STACK
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_READ
from unicorn.x86_const import UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EAX,UC_X86_REG_EIP
BASE=0x4500000;SIZE=0x10000;TACTICAL=BASE+0x1000;CELLS=BASE+0x3000;REGIONS=(BASE+0x4000,BASE+0x4100);INPUT=BASE+0x5000
class BuildingRedrawRequestsOracle(PresentationOracle):
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
  if self.mutated or not m or (point==1)!=(m in (1,2,9)):return
  if m in (6,8) and self.phase!=2:return
  self.mutated=True;self.event(10,m)
  if m in (1,3):self.put(TACTICAL+0xe0,0)
  if m in (2,4):
   self.put(TACTICAL+0xe0,3);self.ints(TACTICAL+0xe8,[CELLS+128,CELLS+64])
  if m==5:self.ints(TACTICAL+0xb0,[17,-23]);self.ints(0x839630,[9,11,180,140]);self.ints(INPUT+16,[7,8,19,20])
  if m==6:self.put(0xabe5b4,REGIONS[1]);self.put(0xabe5c0,0)
  if m==7:self.put(0xabe5c0,3)
  if m==8:self.ints(REGIONS[0],[51,52,13,14])
  if m==9:self.u.mem_write(CELLS+0x24,struct.pack('<2h',9,-7));self.u.mem_write(CELLS+64+0x24,struct.pack('<2h',-11,13))
  if m==10:self.ints(INPUT+16,[21,22,23,24])
  self.expected=bytes(self.u.mem_read(BASE,SIZE))
 def read(self,u,access,p,n,v,_):
  if not self.active:return
  if p==TACTICAL+0xe0:self.event(1,self.signed(self.word(p)))
  if TACTICAL+0xe4<=p<TACTICAL+0xf0:self.event(2,(p-TACTICAL-0xe4)//4,(self.word(p)-CELLS)//64)
  if any(p==CELLS+64*i+0x24 for i in range(3)):
   i=(p-CELLS-0x24)//64;x,y=struct.unpack('<2h',u.mem_read(p,4));self.event(3,i,x,y)
  if p==0xabe5c0:self.event(5,self.signed(self.word(p)));self.phase=2
  if p==0xabe5b4:self.event(6,REGIONS.index(self.word(p)))
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  if a in (0x6a4100,0x41b630,0x6a27a0,0x41fdf0):self.counts[hex(a)]+=1
  sp=u.reg_read(UC_X86_REG_ESP)
  if a==0x6a27a0:
   assert u.reg_read(UC_X86_REG_ECX)==TACTICAL
   coords=self.values(self.word(sp+8),3);self.event(4,*coords);self.mutate(1)
  if a==0x6a9f60:
   self.counts['scan']+=1;force,p,q=struct.unpack('<3I',u.mem_read(sp+4,12));assert force==1 and u.reg_read(UC_X86_REG_ECX)==TACTICAL
   for r in (p,q):assert r==0x839630 or BASE<=r<BASE+SIZE or STACK-0x2000<=r<=STACK-16
   self.event(7,int(p==q),force);self.event(8,*self.values(p,4));self.event(9,*self.values(q,4));self.mutate(2)
   u.reg_write(UC_X86_REG_EAX,0);u.reg_write(UC_X86_REG_EIP,self.word(sp));u.reg_write(UC_X86_REG_ESP,sp+16)
 def run(self,f):
  self.mode,count,dirty,full=f[:4];self.trace=[];self.phase=1;self.mutated=False;self.u.mem_write(BASE,b'\x5a'*SIZE)
  self.ints(TACTICAL+0xb0,f[4:6]);self.put(TACTICAL+0xe0,count)
  self.ints(TACTICAL+0xe4,[CELLS+64*i for i in f[18:21]])
  for i in range(3):self.u.mem_write(CELLS+64*i+0x24,struct.pack('<2h',*f[21+2*i:23+2*i]))
  for backing,order in zip(REGIONS,((0,1,2),(2,1,0))):
   for j,i in enumerate(order):self.ints(backing+20*j,[*f[27+4*i:31+4*i],0xdeadbeef])
  self.ints(INPUT,f[10:18]);self.ints(0x839630,f[6:10]);self.put(0xabe5c0,dirty);self.put(0xabe5b4,REGIONS[0]);self.expected=bytes(self.u.mem_read(BASE,SIZE))
  # Z is always zero here; the separate projection scale remains supplied1/8.
  self.u.mem_write(0xabe490,struct.pack('<d',.125));self.active=True
  try:self.checked_call(0x6a4100,[INPUT,INPUT+16,full],TACTICAL,inputs=[(0x6a4100,0x246),(0x41b630,0x19),(0x6a27a0,0xc8),(0x41fdf0,289),(0xabe490,8)])
  finally:self.active=False
  assert bytes(self.u.mem_read(BASE,SIZE))==self.expected,'Unrelated redraw request arena changed'
  self.trace.append('F');self.trace.extend(map(str,[self.signed(self.word(TACTICAL+0xe0)),self.signed(self.word(0xabe5c0)),REGIONS.index(self.word(0xabe5b4)),*self.values(TACTICAL+0xb0,2),*self.values(0x839630,4),*self.values(INPUT,8)]))
  return self.trace
