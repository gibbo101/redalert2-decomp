# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete original6A9F60 with actual intersection/RTTI; bounds/draw explicit."""
import struct
from collections import Counter
from original_presentation import PresentationOracle,STOP,STACK
from verify_building_static_scan import verify,RANGES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_READ,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_ECX,UC_X86_REG_EAX,UC_X86_REG_ESP,UC_X86_REG_EIP
BASE=0x4400000;SIZE=0x10000;ACTORS=[BASE+0x1000+i*0x1000 for i in range(3)];BACKINGS=[BASE+0x5000,BASE+0x5100];INPUT=BASE+0x6000
class BuildingStaticScanOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(BASE,SIZE);self.active=False;self.counts=Counter()
  self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_READ,self.read);self.u.hook_add(UC_HOOK_MEM_WRITE,self.write)
 def va(self,a):return a
 def word(self,p):return int.from_bytes(self.u.mem_read(p,4),'little')
 def signed(self,v):return (v+2**31)%2**32-2**31
 def ints(self,p,v):self.u.mem_write(p,struct.pack('<'+'I'*len(v),*[x&0xffffffff for x in v]))
 def values(self,p,n):return [self.signed(self.word(p+4*i)) for i in range(n)]
 def event(self,k,id=-1,field=-1,value=0):self.trace.extend(map(str,(k,id,field,value)))
 def ret(self,pop,value=0):
  sp=self.u.reg_read(UC_X86_REG_ESP);self.u.reg_write(UC_X86_REG_EAX,value);self.u.reg_write(UC_X86_REG_EIP,self.word(sp));self.u.reg_write(UC_X86_REG_ESP,sp+4+pop)
 def mutation_write(self,p,b):
  self.u.mem_write(p,b)
  if BASE<=p<BASE+SIZE:self.expected[p-BASE:p-BASE+len(b)]=b
 def mutate(self,point):
  m=self.mode
  if self.mutated or not m:return
  if m in (1,2,3,6) and point!=1 or m in (4,7) and point!=2 or m==5 and point!=3:return
  self.mutated=True;self.event(10,value=m)
  def ints(p,v):self.mutation_write(p,struct.pack('<'+'I'*len(v),*[x&0xffffffff for x in v]))
  if m in (1,4):self.put(0x8525b8,0)
  if m==2:self.put(0x8525b8,3);self.put(0x8525ac,BACKINGS[1])
  if m==3:ints(0x839630,[17,-23]);ints(INPUT+16,[9,-11,200,300])
  if m==5:self.mutation_write(ACTORS[0]+0x5b7,b'\x80');self.mutation_write(ACTORS[1]+0x5b7,b'\xff');self.u.mem_write(0xa40d13,b'\0')
  if m==6:self.mutation_write(ACTORS[1]+0x5b7,b'\xff');self.u.mem_write(0xa40d13,b'\0')
  if m==7:self.mutation_write(ACTORS[0]+0x75,b'\xff')
 def read(self,u,access,p,n,v,_):
  if not self.active:return
  if p==0x8525b8:self.event(1,value=self.signed(self.word(p)))
  if p==0x8525ac:self.event(2,value=BACKINGS.index(self.word(p)))
  if p==0xa40d13:self.event(5,value=u.mem_read(p,1)[0])
  if p in (0x839630,0x839634):self.event(6,field=p-0x839630,value=self.signed(self.word(p)))
  for i,a in enumerate(ACTORS):
   if p==a+0x5b7:self.event(4,i,value=u.mem_read(p,1)[0])
 def write(self,u,access,p,n,v,_):
  if not self.active or not BASE<=p<BASE+SIZE:return
  assert n==1 and p-0x75 in ACTORS,(hex(p),n);id=ACTORS.index(p-0x75);self.event(9,id,value=v&255);self.expected[p-BASE]=v&255
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  if a in RANGES:
   self.counts[hex(a)]+=1
   if a in (0x453c40,0x509800):
    id=ACTORS.index(u.reg_read(UC_X86_REG_ECX));self.event(3,id,value=6 if a==0x453c40 else 15);self.mutate(3)
  if any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()):return
  sp=u.reg_read(UC_X86_REG_ESP);arg=lambda i:self.word(sp+4+4*i);id=ACTORS.index(u.reg_read(UC_X86_REG_ECX))
  if a==0x450dd0:
   self.counts['bounds']+=1;self.event(7,id);self.ints(arg(0),self.rows[id][3:7]);self.mutate(1);self.ret(4,arg(0));return
  if a==self.draw_address:
   self.counts['draw']+=1
   assert STACK-0x2000<=arg(0)<STACK and self.values(arg(0),4)==self.values(INPUT+16,4),'Drawing must receive a separate live clip copy'
   for i,v in enumerate([*self.values(arg(0),4),self.signed(arg(1)),self.signed(arg(2))]):self.event(8,id,i,v)
   if self.mode==7:self.ints(arg(0),[21,22,23,24]) # Child-local mutation must not reach the caller input.
   self.mutate(2);self.ret(12);return
  raise AssertionError(('Uninspected Building static instruction',hex(a)))
 def run(self,f):
  force,self.mode,count,bypass,ox,oy,*_=f;self.rows=[f[17+i*7:24+i*7] for i in range(3)];self.trace=[];self.mutated=False;self.u.mem_write(BASE,b'\x5a'*SIZE)
  self.draw_address=self.word(0x79cbbc+0xfc)
  for a,row in zip(ACTORS,self.rows):self.put(a,0x79cbbc if row[0]==6 else 0x7a3540);self.u.mem_write(a+0x5b7,bytes([row[1]]));self.u.mem_write(a+0x75,bytes([row[2]]))
  self.ints(BACKINGS[0],[ACTORS[i] for i in f[14:17]]);self.ints(BACKINGS[1],list(reversed(ACTORS)));self.put(0x8525ac,BACKINGS[0]);self.put(0x8525b8,count);self.u.mem_write(0xa40d13,bytes([bypass]));self.ints(0x839630,[ox,oy]);self.ints(INPUT,f[6:14]);self.expected=bytearray(self.u.mem_read(BASE,SIZE));self.active=True
  try:self.checked_call(0x6a9f60,[force,INPUT,INPUT+16],writes=[(a+0x75,1) for a in ACTORS],inputs=[*RANGES.items(),(0x79cbbc,0x128),(0x7a3540,0x30)])
  finally:self.active=False
  assert self.u.mem_read(BASE,SIZE)==self.expected,'Unrelated Building static arena changed'
  self.trace.append('F')
  for a in ACTORS:self.trace.extend(map(str,[self.u.mem_read(a+0x5b7,1)[0],self.u.mem_read(a+0x75,1)[0]]))
  self.trace.extend(map(str,[self.signed(self.word(0x8525b8)),BACKINGS.index(self.word(0x8525ac)),*self.values(0x839630,2),*self.values(INPUT+16,4),self.u.mem_read(0xa40d13,1)[0]]))
  return self.trace
