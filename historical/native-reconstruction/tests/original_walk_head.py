# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete unchanged ordinary head roots on shared original Infantry/Cell state."""
import struct
from original_infantry_subcell import InfantrySubcellOracle,ARENA,SIZE,ACTOR,HOUSE,CELLS,POINT,SCENARIO,STATE
from original_presentation import STOP,STACK
from verify_walk_head import verify,RANGES,TABLES,EXTRA
from unicorn.x86_const import UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EAX
WALK=ARENA+0x800
def identity(p):return ((p[0]>>8)^(p[1]>>8))&1
class WalkHeadOracle(InfantrySubcellOracle):
 def __init__(self,exe):
  self.ready=False;super().__init__(exe);self.inspection=verify(exe.read_bytes());self.ready=True
 def tag(self,p):return 'h' if p==WALK+0x28 else 'a' if p==ACTOR+0x88 else 'r' if p==POINT else 's'
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  if not self.ready:return super().code(u,a,n,_)
  sp=u.reg_read(UC_X86_REG_ESP);ecx=u.reg_read(UC_X86_REG_ECX)
  assert a in (0x548000,0x55a280) or any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected head instruction',hex(a))
  assert not(0x71f69f<=a<0x71f6f5 or 0x71f706<=a<0x71f752 or 0x71f760<=a<0x71f787),('Entered target child',hex(a))
  if any(lo<=a and a+n<=lo+size for lo,size in EXTRA.items()):
   if a in EXTRA:self.counts[hex(a)]+=1
   if a==0x71f590:assert ecx==WALK
   elif a==0x594770:
    assert ecx==ACTOR;m,q=self.ints(ACTOR+0x98,1)[0],self.ints(ACTOR+0xa0,1)[0];self.event('M',q if m==-1 else m)
   elif a==0x476cc0:
    assert ecx in CELLS and self.word(sp+4)==ACTOR;self.event('E',CELLS.index(ecx));assert self.ints(ecx+0x44,1)[0]==-1
   if 0x476ce8<=a<0x478646:raise AssertionError(('Entered overlay effects',hex(a)))
   return
  if a in (0x548000,0x55a280):
   assert ecx==0x8324e0;p=self.word(sp+4);point=self.ints(p,3)
   assert p in (POINT,WALK+0x28,ACTOR+0x88) or STACK-0x2000<=p<STACK
   if a==0x548000:
    i=identity(point);self.event('N',i,self.tag(p),*point);self.counts['lookup']+=1;self.ret(4,CELLS[i]);return
   self.event('F',self.tag(p),*point);self.floors+=1;self.counts['floor']+=1
   x,y,z,kind,trigger,mutation,floor,threshold,house,height,level,m,q=self.step
   if self.floors==trigger:
    if mutation&1:
     for off,delta in ((0x88,5),(0x8c,-7),(0x90,77)):self.put(ACTOR+off,self.word(ACTOR+off)+delta)
    if mutation&2:
     for off,delta in ((0,257),(4,-513),(8,11)):self.put(POINT+off,self.word(POINT+off)+delta)
    if mutation&4:
     for c in CELLS:self.put(c+0x140,self.word(c+0x140)^0x100)
    if mutation&8:self.put(0xa41120,self.word(0xa41120)+37)
    if mutation&16:self.put(HOUSE+0x30,self.word(HOUSE+0x30)+5)
    if mutation&32:self.put(0x850c30,self.word(0x850c30)+11)
    if mutation&64:self.put(0xaf9098,self.word(0xaf9098)+1)
    if mutation&128:
     for c in CELLS:self.put(c+0x124,self.word(c+0x124)^0x1234001c);self.put(c+0x128,self.word(c+0x128)^0x9876001c)
    if mutation&256:self.put(ACTOR+0x98,-1);self.put(ACTOR+0xa0,8)
    if mutation&512:
     for off,delta in ((0x28,257),(0x2c,-513),(0x30,11)):self.put(WALK+off,self.word(WALK+off)+delta)
   self.ret(4,floor);return
  super().code(u,a,n,_)
 def store(self,u,access,p,n,value,_):
  if self.active and WALK+0x28<=p<WALK+0x34:
   assert n==4;self.event('L',p-WALK,value&0xffffffff);self.counts['head_store']+=1
  else:super().store(u,access,p,n,value,_)
 def run_head(self,disabled,first,second,seed,position,head,cells,target,steps):
  u=self.u;u.mem_write(ARENA,b'\xa5'*SIZE);self.put(ACTOR,0x7a3540);self.put(ACTOR+0x1b4,HOUSE);self.put(ACTOR+0x494,ARENA+0x3000 if target else 0)
  self.put(WALK+4,0x7aead8);self.put(WALK+0xc,ACTOR)
  for off,values in ((ACTOR+0x88,position),(WALK+0x1c,(17,23,31,*head))):
   for i,value in enumerate(values):self.put(off+4*i,value)
  u.mem_write(WALK+0x34,bytes([173,197,255]));self.put(0xa3d290,SCENARIO);u.mem_write(0x850c00,bytes(12));u.mem_write(0xaf9060,bytes(12))
  table=[]
  for _ in range(250):seed=(seed*1664525+1013904223)&0xffffffff;table.append(seed)
  u.mem_write(STATE,bytes([disabled])+b'\xa5'*3+struct.pack('<ii250I',first,second,*table))
  for c,row in zip(CELLS,cells):
   for off,value in zip((0x124,0x128,0x140,0x54,0x58),row):self.put(c+off,value)
   self.put(c+0x44,-1)
  self.events=[]
  for step in steps:
   self.step=step;self.floors=0;x,y,z,kind,trigger,mutation,floor,threshold,house,height,level,m,q=step
   for p,value in ((POINT,x),(POINT+4,y),(POINT+8,z),(0xa41120,threshold),(HOUSE+0x30,house),(0x850c30,height),(0xaf9098,level),(ACTOR+0x98,m),(ACTOR+0xa0,q)):self.put(p,value)
   writes=[(POINT,12),(ACTOR+0x88,12),(ACTOR+0x98,4),(ACTOR+0xa0,4),(WALK+0x28,12),(HOUSE+0x30,4),(STATE+4,1008)]+[(c+off,n) for c in CELLS for off,n in ((0x54,8),(0x124,8),(0x140,4))]
   inputs=[];cursor=ARENA
   for lo,n in sorted(writes):
    if cursor<lo:inputs.append((cursor,lo-cursor))
    cursor=lo+n
   inputs.append((cursor,ARENA+SIZE-cursor));inputs+=list(RANGES.items())+list(TABLES.items())+[(0x850e50,60),(0x850c00,12),(0xaf9060,12),(0xa3d290,4)]
   point=(POINT,WALK+0x28,ACTOR+0x88)[kind];self.active=True
   try:self.checked_call(0x71f590,[point],WALK,writes=writes,inputs=inputs)
   finally:self.active=False
   self.event('R',u.reg_read(UC_X86_REG_EAX)&255,'P',*self.ints(ACTOR+0x88,3),*self.ints(POINT,3),*self.ints(WALK+0x28,3),self.ints(0xa41120,1)[0],self.ints(HOUSE+0x30,1)[0],self.ints(0x850c30,1)[0],self.ints(0xaf9098,1)[0],self.ints(ACTOR+0x98,1)[0],self.ints(ACTOR+0xa0,1)[0])
  self.event('Z')
  for c in CELLS:self.event(self.word(c+0x124),self.word(c+0x128),self.word(c+0x140),*self.ints(c+0x54,2))
  self.event('rng',disabled,*self.ints(STATE+4,2),*struct.unpack('<250I',u.mem_read(STATE+12,1000)))
  return self.events
