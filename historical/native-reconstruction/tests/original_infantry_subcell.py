# SPDX-License-Identifier: GPL-3.0-or-later
"""Unchanged base subcell roots with named map/floor effects and complete arena guards."""
import struct
from collections import Counter
from original_presentation import PresentationOracle,STOP
from verify_infantry_subcell import verify,RANGES,TABLES,SERVICES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_EIP,UC_X86_REG_ESP
ARENA=0x2800000;SIZE=0x4000;ACTOR=ARENA;HOUSE=ARENA+0x400
CELLS=(ARENA+0x1000,ARENA+0x1400);POINT=ARENA+0x2000;OUT=POINT+0x100
SCENARIO=ARENA+0x2800;STATE=SCENARIO+0x218
def signed(n):return n if n<0x80000000 else n-0x100000000
class InfantrySubcellOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True)
  self.u.mem_map(ARENA,SIZE);self.active=False;self.counts=Counter();self.events=[]
  self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.store)
  self.active=True
  try:self.checked_call(0x483390,writes=[(0x850e50,60)],inputs=list(RANGES.items())+list(TABLES.items()))
  finally:self.active=False
  self.offsets=self.ints(0x850e50,15)
 def va(self,a):return a
 def ints(self,p,n):return struct.unpack('<'+'i'*n,self.u.mem_read(p,4*n))
 def word(self,p):return self.ints(p,1)[0]&0xffffffff
 def event(self,*args):self.events.extend(map(str,args))
 def ret(self,n,value):
  sp=self.u.reg_read(UC_X86_REG_ESP);target=self.word(sp)
  self.u.reg_write(UC_X86_REG_EAX,value&0xffffffff);self.u.reg_write(UC_X86_REG_ESP,sp+4+n);self.u.reg_write(UC_X86_REG_EIP,target)
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  assert a in SERVICES or any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected subcell instruction',hex(a))
  assert not 0x47656e<=a<0x4765b9,('Unjoined building policy',hex(a))
  if a in RANGES:self.counts[hex(a)]+=1
  sp=u.reg_read(UC_X86_REG_ESP);ecx=u.reg_read(UC_X86_REG_ECX)
  if a==0x4ba410:self.event('Q',int(struct.unpack('<d',u.mem_read(sp+4,8))[0]))
  elif a==0x6388a0:assert ecx==STATE and self.ints(sp+4,2)==(0,3)
  elif a==0x63893e:self.event('D',u.reg_read(UC_X86_REG_EAX),*self.ints(STATE+4,2))
  elif a==0x6c7420:
   assert ecx==ACTOR and self.word(ACTOR+0x1b4)==HOUSE;self.event('H',self.ints(HOUSE+0x30,1)[0])
  elif a==0x548000:
   assert ecx==0x8324e0 and self.word(sp+4)==POINT
   self.event('N',self.lookupId,*self.ints(POINT,3));self.ret(4,CELLS[self.lookupId])
  elif a==0x55a280:
   assert ecx==0x8324e0 and self.word(sp+4)==POINT;self.event('F',*self.ints(POINT,3));self.counts['floor']+=1
   op,x,y,z,force,elevated,mutation,floor,threshold,house,height,cellId=self.step;c=CELLS[cellId]
   if mutation&1:self.put(POINT+8,self.word(POINT+8)+77)
   if mutation&2:self.put(POINT,self.word(POINT)+257);self.put(POINT+4,self.word(POINT+4)-513)
   if mutation&4:self.put(c+0x140,self.word(c+0x140)^0x100)
   if mutation&8:self.put(0xa41120,self.word(0xa41120)+37)
   if mutation&16:self.put(HOUSE+0x30,self.word(HOUSE+0x30)+5)
   if mutation&32:self.put(0x850c30,self.word(0x850c30)+11)
   if mutation&64:self.put(c+0x124,self.word(c+0x124)^0x1234561c);self.put(c+0x128,self.word(c+0x128)^0x9876541c)
   if mutation&128:self.put(c+0x54,-17);self.put(c+0x58,23)
   if mutation&256:self.lookupId=1-cellId
   self.ret(4,floor)
 def store(self,u,access,p,n,value,_):
  if not self.active:return
  for i,c in enumerate(CELLS):
   if p-c in (0x124,0x128,0x54,0x58):
    assert n==(1 if p-c>=0x124 else 4);self.event('C',i,p-c,n,value&((1<<(8*n))-1));self.counts['cell_store']+=1
 def run(self,disabled,first,second,seed,cells,steps):
  u=self.u;u.mem_write(ARENA,b'\xa5'*SIZE);self.put(ACTOR,0x7a3540);self.put(ACTOR+0x1b4,HOUSE)
  self.put(0xa3d290,SCENARIO);u.mem_write(0x850c00,bytes(12))
  table=[]
  for _ in range(250):seed=(seed*1664525+1013904223)&0xffffffff;table.append(seed)
  u.mem_write(STATE,bytes([disabled])+b'\xa5'*3+struct.pack('<ii250I',first,second,*table))
  for c,row in zip(CELLS,cells):
   for off,value in zip((0x124,0x128,0x140,0x54,0x58),row):self.put(c+off,value)
  self.events=[];self.event('I',*self.offsets)
  for step in steps:
   self.step=step;op,x,y,z,force,elevated,mutation,floor,threshold,house,height,cellId=step;self.lookupId=cellId
   for off,value in ((0xa41120,threshold),(HOUSE+0x30,house),(0x850c30,height),(POINT,x),(POINT+4,y),(POINT+8,z)):self.put(off,value)
   writes=[(OUT,12),(POINT,12),(HOUSE+0x30,4),(STATE+4,1008)]+[(c+off,n) for c in CELLS for off,n in ((0x54,8),(0x124,8),(0x140,4))]
   inputs=[];cursor=ARENA
   for lo,n in sorted(writes):
    if cursor<lo:inputs.append((cursor,lo-cursor))
    cursor=lo+n
   inputs.append((cursor,ARENA+SIZE-cursor));inputs+=list(RANGES.items())+list(TABLES.items())+[(0x850e50,60),(0x850c00,12),(0xa3d290,4)]
   self.active=True
   try:
    if op==0:self.checked_call(0x4763d0,ecx=POINT,writes=writes,inputs=inputs)
    elif op in (1,2):self.checked_call(0x508410 if op==1 else 0x5084a0,[POINT],ACTOR,writes=writes,inputs=inputs)
    else:self.checked_call(0x4764b0,[OUT,POINT,force,elevated],CELLS[cellId],writes=writes,inputs=inputs)
   finally:self.active=False
   self.event('R',op)
   if op==0:self.event(u.reg_read(UC_X86_REG_EAX))
   elif op==3:
    assert u.reg_read(UC_X86_REG_EAX)==OUT;self.event(*self.ints(OUT,3))
   self.event('P',*self.ints(POINT,3),self.ints(0xa41120,1)[0],self.ints(HOUSE+0x30,1)[0],self.ints(0x850c30,1)[0])
  self.event('Z')
  for c in CELLS:self.event(self.word(c+0x124),self.word(c+0x128),self.word(c+0x140),*self.ints(c+0x54,2))
  self.event('rng',disabled,*self.ints(STATE+4,2),*struct.unpack('<250I',u.mem_read(STATE+12,1000)))
  return self.events
