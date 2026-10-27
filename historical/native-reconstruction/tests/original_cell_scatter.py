# SPDX-License-Identifier: GPL-3.0-or-later
"""Unchanged Cell root/children; explicitly supplied heap and member services."""
import struct
from collections import Counter
from original_presentation import PresentationOracle,STACK,STOP
from verify_cell_scatter import verify,RANGES,VTABLES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESI,UC_X86_REG_EDI,UC_X86_REG_ESP,UC_X86_REG_EIP
ARENA=0x2800000;SIZE=0x40000
ACTORS=[ARENA+i*0x1000 for i in range(32)]
TYPES=[ARENA+0x21000+i*0x1000 for i in range(2)]
HOUSES=[ARENA+0x26000+i*0x1000 for i in range(2)]
CELL=ARENA+0x29000;RULES=ARENA+0x2a000;POINT=ARENA+0x2f000;HEAP=ARENA+0x30000
def signed(n):return n if n<0x80000000 else n-0x100000000
def ptr(id):return 0 if id==-1 else ACTORS[id]
def oid(p):return -1 if not p else ACTORS.index(p)
def ret(u,pop,value=0):
 sp=u.reg_read(UC_X86_REG_ESP);target=int.from_bytes(u.mem_read(sp,4),'little')
 u.reg_write(UC_X86_REG_EAX,value&0xffffffff);u.reg_write(UC_X86_REG_ESP,sp+4+pop);u.reg_write(UC_X86_REG_EIP,target)

class CellScatterOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True)
  self.u.mem_map(ARENA,SIZE);self.active=False;self.instructions=set();self.entries=Counter();self.returns=Counter();self.snapshot_stores=0;self.service_counts=Counter()
  self.scatter_targets={int(row['0x15c'],16) for row in self.inspection['dispatch'].values()}
  self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.store)
 def va(self,a):return a
 def word(self,p):return int.from_bytes(self.u.mem_read(p,4),'little')
 def event(self,*v):self.events.extend(map(str,v))
 def supply(self,p,b):
  self.u.mem_write(p,b)
  if ARENA<=p and p+len(b)<=ARENA+SIZE:self.expected[p-ARENA:p-ARENA+len(b)]=b
 def value(self,p,v):self.supply(p,struct.pack('<I',v&0xffffffff))
 def member(self,id):return ACTORS[id]
 def mutate(self,mode,id):
  if mode==1:
   self.value(CELL+0xe4,0);self.value(CELL+0xe8,0)
   for p in ACTORS[:self.count]:self.value(p+0x30,0)
  elif mode==2:
   self.supply(RULES+0x1431,b'\0');self.value(HOUSES[0]+0x194,-2147483648);self.value(HOUSES[1]+0x194,2147483647)
   self.supply(TYPES[0]+0x26f,b'\0');self.supply(TYPES[0]+0x281,b'\0')
   if self.count:
    p=ACTORS[self.count-1];self.value(p+0x1b4,HOUSES[0]);self.supply(p+0x118,bytes(8))
  elif mode==3:self.value(ACTORS[id]+0x30,0)
  elif mode==4:self.supply(POINT,struct.pack('<3i',-2147483648,2147483647,-17))
  elif mode==5:self.supply(ACTORS[id]+0x118,struct.pack('<d',2.))
  self.event('d',mode,id)
 def code(self,u,a,n,ctx):
  if not self.active or a==STOP:return
  ecx=u.reg_read(UC_X86_REG_ECX);sp=u.reg_read(UC_X86_REG_ESP);arg=lambda i:self.word(sp+4+4*i)
  if a in (0x40cd40,0x781d3b) or a in self.scatter_targets:
   caller=self.word(sp)
   if a==0x40cd40:
    assert caller==0x4769e6 and STACK-0x2000<=ecx<STACK
    amount,zero=arg(0),arg(1);assert amount==self.capacity+10 and zero==0 and 0<amount<=40
    result=self.growth[self.grows%len(self.growth)];self.event('G',amount,result)
    if self.mutation==3 and not self.grows:
     first=oid(self.word(CELL+(0xe8 if self.layer else 0xe4)))
     if first!=-1:self.mutate(3,first)
    if self.mutation==5 and not self.grows and self.count:self.mutate(5,self.count-1)
    self.grows+=1
    if result&255:
     buffer=HEAP+self.successes*0x400;self.successes+=1
     count=self.word(ecx+16)
     if count:self.supply(buffer,bytes(u.mem_read(self.word(ecx+4),count*4)))
     self.put(ecx+4,buffer);self.put(ecx+8,amount);u.mem_write(ecx+13,b'\1')
     self.capacity=amount;self.buffer=buffer
    self.service_counts['growth']+=1;ret(u,8,result)
   elif a==0x781d3b:
    assert caller==0x476ab4 and arg(0)==self.buffer
    self.event('F',self.capacity,0);self.service_counts['release']+=1;ret(u,0)
   else:
    id=oid(ecx);assert caller==0x476a89 and arg(0)==POINT and id<self.count
    self.event('S',id,*struct.unpack('<3i',u.mem_read(POINT,12)),arg(1),arg(2))
    assert arg(1)==self.ignore_mission and arg(2)==self.ignore_destination
    if self.mutation in (1,2,4) and not self.scatters:self.mutate(self.mutation,id)
    self.scatters+=1;self.service_counts['scatter']+=1;ret(u,12)
   return
  assert any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected Cell scatter',hex(a),n)
  self.instructions.add(a)
  if a in RANGES:self.entries[hex(a)]+=1
  if a in (0x476930,0x476938,0x476980,0x476988):
   assert u.reg_read(UC_X86_REG_EDI)==CELL;self.event('H',0,int(a in (0x476930,0x476980)))
  elif a in (0x47696b,0x476a00):
   p=u.reg_read(UC_X86_REG_ESI);self.event('N',oid(p),oid(self.word(p+0x30)))
  elif a==0x40dc20:self.event('X',oid(ecx),0)
  elif a in (0x70a2d5,0x453c45,0x6e4b05):
   id=oid(ecx);kind=u.reg_read(UC_X86_REG_EAX);assert kind==self.kinds[id];self.event('K',id,kind);self.returns[('kind',kind)]+=1
  elif a in (0x7133a0,0x713420):self.event('V' if a==0x7133a0 else 'E',oid(ecx-0x118),0)
  elif a in (0x7133c3,0x7133c6,0x713434,0x713437):self.returns[('veteran' if a<0x713400 else 'elite',u.reg_read(UC_X86_REG_EAX))]+=1
  elif a==0x6d7910:assert arg(0)==3;self.event('B',oid(ecx),3)
  elif a in (0x6d795c,0x6d7985,0x6d798d):self.returns[('ability3',u.reg_read(UC_X86_REG_EAX)&255)]+=1
  elif a==0x6c12c0:self.event('T',oid(ecx),0)
  elif a in (0x705020,0x453c60):self.event('t',oid(ecx),TYPES.index(self.word(ecx+(0x5ac if a==0x705020 else 0x418))))
 def store(self,u,access,p,n,v,ctx):
  if not self.active or not(ARENA<=p<ARENA+SIZE):return
  assert u.reg_read(UC_X86_REG_EIP)==0x4769f9 and n==4 and self.buffer<=p<self.buffer+self.capacity*4
  id=oid(v&0xffffffff);index=(p-self.buffer)//4;self.event('W',index,id);self.snapshot_stores+=1
  self.expected[p-ARENA:p-ARENA+4]=struct.pack('<I',v&0xffffffff)
 def run(self,h,types,houses,members,call,growth):
  n,head0,head1,flag,threshold=h;self.count=n;self.kinds=[r[0] for r in members]
  x,y,z,self.ignore_mission,self.ignore_destination,self.layer,self.mutation=call
  u=self.u;u.mem_write(ARENA,b'\xa5'*SIZE);self.expected=bytearray(u.mem_read(ARENA,SIZE))
  self.value(0x839848,RULES);self.supply(RULES+0x1431,bytes([flag]));self.value(RULES+0x10b4,threshold)
  self.value(CELL+0xe4,ptr(head0));self.value(CELL+0xe8,ptr(head1));self.supply(POINT,struct.pack('<3i',x,y,z))
  for p,(v,e) in zip(TYPES,types):self.supply(p+0x26f,bytes([v]));self.supply(p+0x281,bytes([e]))
  for p,value in zip(HOUSES,houses):self.value(p+0x194,value)
  for p,(kind,next_,type_,owner,bits) in zip(ACTORS,members):
   for off,v in ((0,VTABLES[kind]),(0x30,ptr(next_)),(0x1b4,HOUSES[owner]),(0x418,TYPES[type_]),(0x5ac,TYPES[type_])):self.value(p+off,v)
   self.supply(p+0x118,struct.pack('<Q',bits))
  self.capacity=self.buffer=self.successes=self.grows=self.scatters=0;self.growth=growth;self.events=[]
  protected=[*RANGES.items(),(0x40dc4c,23),(0x79db7c,12),(0x79a708,8),(0x79a6f8,8),(0x839848,4)]
  protected += [(vt+off,4) for vt in VTABLES.values() for off in (0x2c,0x80,0x84,0x15c)]
  self.active=True
  try:self.checked_call(0x476920,[POINT,self.ignore_mission,self.ignore_destination,self.layer],CELL,writes=[(HEAP,0x10000)],inputs=protected)
  finally:self.active=False
  assert bytes(u.mem_read(ARENA,SIZE))==bytes(self.expected),'Unexpected complete Cell/actor/type/House/rules/heap arena change'
  self.event('state',u.mem_read(RULES+0x1431,1)[0],signed(self.word(RULES+0x10b4)),oid(self.word(CELL+0xe4)),oid(self.word(CELL+0xe8)),*struct.unpack('<3i',u.mem_read(POINT,12)))
  for id,p in enumerate(ACTORS[:n]):self.event(id,self.kinds[id],oid(self.word(p+0x30)),TYPES.index(self.word(p+0x5ac)),HOUSES.index(self.word(p+0x1b4)),struct.unpack('<Q',u.mem_read(p+0x118,8))[0])
  for id,p in enumerate(TYPES):self.event(id,u.mem_read(p+0x26f,1)[0],u.mem_read(p+0x281,1)[0])
  for id,p in enumerate(HOUSES):self.event(id,signed(self.word(p+0x194)))
  return self.events
