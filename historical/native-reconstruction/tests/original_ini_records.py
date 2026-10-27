# SPDX-License-Identifier: GPL-3.0-or-later
"""Unchanged complete linked INI record routines; scalar free supplied."""
import struct
from original_presentation import PresentationOracle,STOP,STACK
from verify_ini_records import verify,RANGES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ESP,UC_X86_REG_EIP
BASE=0x6d00000;SIZE=0x10000;LIST=BASE+0x100;ENTRIES=tuple(BASE+0x200+i*0x80 for i in range(3));NODES=(LIST+4,LIST+0x10,*ENTRIES,BASE+0x500);STRINGS=tuple(BASE+0x1000+i*0x40 for i in range(4));FREE=0x781d3b
GRAPHS=((2,0,0,1,0,0,0,0,0,0,0,0),(3,0,0,4,4,1,2,3,0,0,0,0),(4,0,0,3,2,4,3,1,0,0,0,0),(0,0,0,0,4,6,0,3,0,0,0,0),(3,0,0,1,3,1,0,0,0,0,0,0),(3,0,0,1,4,6,3,3,0,0,0,0),(2,6,1,1,0,0,0,0,0,0,0,0),(3,6,6,6,6,6,6,6,6,6,0,0))
NODE_TAGS={0x11223344:0,0x79aafc:1,0x7a3b9c:2};LIST_TAGS={0x22334455:0,0x79aaf4:1,0x7a3bac:2}
class IniRecordOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(BASE,SIZE);self.active=False;self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.write)
 def va(self,a):return a
 def word(self,a):return int.from_bytes(self.u.mem_read(a,4),'little')
 def ptr(self,i):return NODES[i-1] if i else 0
 def pid(self,p):
  ids={0:0,LIST:9,**{p:i+1 for i,p in enumerate(NODES)},**{p:i+20 for i,p in enumerate(STRINGS)}};assert p in ids,hex(p);return ids[p]
 def event(self,k,owner=0,off=0,v=0,pointer=0):self.trace.extend(map(str,(k,owner,off,v,pointer)))
 def change(self,a,raw):
  self.u.mem_write(a,raw)
  if BASE<=a<a+len(raw)<=BASE+SIZE:self.expected[a-BASE:a-BASE+len(raw)]=raw
 def set(self,a,v):self.change(a,struct.pack('<I',v&0xffffffff))
 def mutate(self,where):
  if self.mutated or self.f[6]!=where:return
  self.mutated=1;self.event(3,0,where);primary=self.ptr(self.f[2])
  if where==1:self.set(primary+4,self.ptr(6));self.set(primary+8,self.ptr(5))
  if where==2:self.set(primary+4,self.ptr(4));self.set(primary+8,self.ptr(3))
  if where==3:self.set(primary+4,self.ptr(6))
  if where==4:self.set(NODES[0]+4,self.ptr(5));self.set(ENTRIES[0]+0xc,STRINGS[3])
  if where in (5,6):
   self.args=[STRINGS[3],STRINGS[2],STRINGS[1],STRINGS[0],17,(-18)&0xffffffff,19]
   if self.f[0]==6:
    for i,v in enumerate(self.args):self.set(STACK+4+i*4,v)
 def write(self,u,access,a,n,v,_):
  if not self.active or not BASE<=a<a+n<=BASE+SIZE:return
  assert n==4;v&=0xffffffff;self.expected[a-BASE:a-BASE+n]=v.to_bytes(n,'little')
  if a==LIST:self.event(1,9,0,LIST_TAGS[v])
  else:
   owner=next((p for p in NODES if p<=a<p+12),None)
   if owner is not None:
    off=a-owner;assert off in (0,4,8);self.event(1,self.pid(owner),off,NODE_TAGS[v] if off==0 else 0,0 if off==0 else self.pid(v))
   else:
    owner=next((p for p in ENTRIES if p+0xc<=a<p+0x28),None);assert owner is not None,hex(a);off=a-owner
    assert off in (0xc,0x10,0x14,0x18,0x1c,0x20,0x24);pointer=off<0x1c;self.event(1,self.pid(owner),off,0 if pointer else v,self.pid(v) if pointer else 0)
  self.stores+=1;self.pending=[1,5] if self.stores==1 else [2,6] if self.stores==4 else [3] if self.stores==7 else []
 def code(self,u,a,n,_):
  if not self.active:return
  if self.pending:
   pending=self.pending;self.pending=[]
   for where in pending:self.mutate(where)
  if a==STOP:return
  assert a==FREE or any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected INI record instruction',hex(a))
  if a==FREE:
   sp=u.reg_read(UC_X86_REG_ESP);owner=self.word(sp+4);assert owner in (*NODES,LIST);self.freed+=1;self.event(2,self.pid(owner));self.mutate(4)
   u.reg_write(UC_X86_REG_EAX,0);u.reg_write(UC_X86_REG_EIP,self.word(sp));u.reg_write(UC_X86_REG_ESP,sp+4)
 def run(self,f):
  self.f=f;self.trace=[];self.mutated=0;self.freed=0;self.stores=0;self.pending=[];u=self.u;u.mem_write(BASE,b'\xa5'*SIZE)
  self.put(LIST,0x22334455)
  for i,p in enumerate(NODES):self.put(p,0x11223344);self.put(p+4,self.ptr(GRAPHS[f[1]][i*2]));self.put(p+8,self.ptr(GRAPHS[f[1]][i*2+1]))
  for p,s in zip(STRINGS,(b'zeta',b'alpha',b'middle',b'value')):u.mem_write(p,s+b'\0')
  for i,p in enumerate(ENTRIES):
   self.put(p+0xc,STRINGS[i]);self.put(p+0x10,STRINGS[3]);self.put(p+0x14,STRINGS[2]);self.put(p+0x18,STRINGS[1])
  self.args=list(((*STRINGS,0xffffffff,0x80000000,0x7fffffff),(0,0,0,0,0,0,0),(STRINGS[3],STRINGS[2],STRINGS[1],STRINGS[0],0x80000000,128,(-128)&0xffffffff))[f[5]])
  self.expected=bytearray(u.mem_read(BASE,SIZE));self.active=True;inputs=[*RANGES.items(),*[(p,16) for p in STRINGS]];writes=[(BASE,SIZE)]
  try:
   for _ in range(f[7]):
    op=f[0];root=(0x40e160,0x40e180,0x40e1d0,0x490e80,0x510bb0,0x510c20,0x510b60)[op]
    owner=self.ptr(f[2]) if op<3 else LIST if op<6 else ENTRIES[0]
    args=[self.ptr(f[3])] if op==1 else [f[4]] if op in (2,5) else self.args.copy() if op==6 else []
    self.checked_call(root,args,owner,writes=writes,inputs=inputs)
    if op!=1:assert u.reg_read(UC_X86_REG_EAX)==owner
    self.event(4,0 if op==1 else self.pid(owner))
  finally:self.active=False
  assert bytes(u.mem_read(BASE,SIZE))==self.expected,'Unrelated INI record arena changed'
  final=[LIST_TAGS[self.word(LIST)]]
  for p in NODES:final.extend((self.pid(self.word(p+4)),self.pid(self.word(p+8)),NODE_TAGS[self.word(p)]))
  for p in ENTRIES:final.extend([self.pid(self.word(p+off)) for off in (0xc,0x10,0x14,0x18)]+[self.word(p+off) for off in (0x1c,0x20,0x24)])
  return self.trace+['F',*map(str,final+[self.mutated,self.freed]+[self.pid(v) if i<4 else v for i,v in enumerate(self.args)])]
