# SPDX-License-Identifier: GPL-3.0-or-later
"""Unchanged complete INI input lifetime roots; heap/virtual child supplied."""
import struct
from original_presentation import PresentationOracle,STOP
from verify_ini_input_lifetime import verify,RANGES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EIP
BASE=0x6c00000;SIZE=0x10000;BUFFER=BASE+0x100;PIPES=tuple(BASE+0x200+i*0x40 for i in range(4));MEMORY=(BASE+0x500,BASE+0x600);VTABLE=BASE+0x800;ATTACH=BASE+0x900;ALLOC=0x782017;FREE=0x781d3b
GRAPHS=((0,0,0,0,0,0,0,0),(2,0,0,1,0,0,0,0),(2,3,0,1,1,0,0,0),(2,3,0,4,1,0,2,0),(1,1,0,0,0,0,0,0),(0,2,1,3,2,0,0,0),(3,2,4,1,0,0,0,2),(4,4,1,3,2,2,3,1))
class IniInputLifetimeOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(BASE,SIZE);self.active=False;self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.write)
 def va(self,a):return a
 def word(self,a):return int.from_bytes(self.u.mem_read(a,4),'little')
 def ptr(self,i):return PIPES[i-1] if i else 0
 def pid(self,p):
  ids={0:0,**{p:i+1 for i,p in enumerate(PIPES)},**{p:i+10 for i,p in enumerate(MEMORY)}};assert p in ids,hex(p);return ids[p]
 def event(self,k,owner=0,off=0,v=0,pointer=0):self.trace.extend(map(str,(k,owner,off,v,pointer)))
 def change(self,a,raw):self.u.mem_write(a,raw);self.expected[a-BASE:a-BASE+len(raw)]=raw
 def set(self,a,v):self.change(a,struct.pack('<I',v&0xffffffff))
 def mutate(self,where):
  if self.mutated or self.f[7]!=where:return
  self.mutated=1;self.event(5,0,where)
  if where==1:self.set(BUFFER+4,99);self.change(BUFFER+8,b'\x80')
  if where==2:self.set(BUFFER,MEMORY[1]);self.set(BUFFER+4,-2);self.change(BUFFER+8,b'\xff')
  if where==3:
   self.set(PIPES[0]+4,PIPES[3]);self.set(PIPES[0]+8,PIPES[1])
   if self.f[5]:self.set(self.ptr(self.f[5])+8,PIPES[2])
  if where==4:self.set(PIPES[0]+4,PIPES[1]);self.set(PIPES[0]+8,PIPES[2]);self.set(BUFFER,MEMORY[1]);self.set(BUFFER+4,-7);self.change(BUFFER+8,b'\x80')
  if where==5:
   self.set(PIPES[0]+4,PIPES[3])
   if self.f[5]:self.set(self.ptr(self.f[5])+8,PIPES[2])
 def write(self,u,access,a,n,v,_):
  if not self.active or not BASE<=a<a+n<=BASE+SIZE:return
  v&=(1<<(n*8))-1;self.expected[a-BASE:a-BASE+n]=v.to_bytes(n,'little')
  if BUFFER<=a<BUFFER+9:
   off=a-BUFFER;assert (off,n) in ((0,4),(4,4),(8,1));self.event(1,9,off,0 if off==0 else v,self.pid(v) if off==0 else 0);self.pending=[4]
  else:
   p=next((p for p in PIPES if p<=a<p+12),None);assert p is not None and n==4
   off=a-p;assert off in (0,4,8)
   if off==0:assert v==0x79e9f8
   self.event(1,self.pid(p),off,1 if off==0 else 0,0 if off==0 else self.pid(v));self.pending=[4]+([5] if p==PIPES[0] and off==4 else [])
 def ret(self,sp,pop,value):self.u.reg_write(UC_X86_REG_EAX,value&0xffffffff);self.u.reg_write(UC_X86_REG_ESP,sp+4+pop);self.u.reg_write(UC_X86_REG_EIP,self.word(sp))
 def code(self,u,a,n,_):
  if not self.active:return
  if self.pending:
   pending=self.pending;self.pending=[]
   for where in pending:self.mutate(where)
  if a==STOP:return
  assert a in (ALLOC,FREE,ATTACH) or any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected INI lifetime instruction',hex(a))
  sp=u.reg_read(UC_X86_REG_ESP)
  if self.child:
   self.child=False;owner=u.reg_read(UC_X86_REG_ECX);arg=self.word(sp+4);assert owner in PIPES and (not arg or arg in PIPES);self.attached+=1;self.event(4,self.pid(owner),0,0,self.pid(arg));self.mutate(3)
   if not self.f[9]:self.ret(sp,4,0);return
   assert a==0x69b050
  if a in (0x69b036,0x69b06c):self.child=True
  if a==ALLOC:
   size=self.word(sp+4);self.allocated+=1;self.event(2,0,0,size,0 if self.f[4] else 10);self.mutate(1);self.ret(sp,0,0 if self.f[4] else MEMORY[0])
  if a==FREE:
   pointer=self.word(sp+4);self.freed+=1;self.event(3,0,0,0,self.pid(pointer));self.mutate(2);self.ret(sp,0,0)
 def run(self,f):
  self.f=f;self.trace=[];self.mutated=0;self.allocated=0;self.freed=0;self.attached=0;self.pending=[];self.child=False;u=self.u;u.mem_write(BASE,b'\xa5'*SIZE)
  self.put(BUFFER,MEMORY[f[3]-1] if f[3] else 0);self.put(BUFFER+4,f[1]);u.mem_write(BUFFER+8,bytes((f[2],)));self.put(VTABLE+4,0x69b050 if f[9] else ATTACH)
  for i,p in enumerate(PIPES):self.put(p,VTABLE);self.put(p+4,self.ptr(GRAPHS[f[6]][i*2]));self.put(p+8,self.ptr(GRAPHS[f[6]][i*2+1]))
  self.expected=bytearray(u.mem_read(BASE,SIZE));self.active=True;inputs=[*RANGES.items(),(VTABLE+4,4),(0x79e9fc,4)];writes=[(BASE,SIZE)]
  try:
   for _ in range(f[8]):
    op=f[0];a=(0x438380,0x438410,0x69b050,0x69b010)[op];args=[f[1]] if op==0 else [self.ptr(f[5])] if op==2 else []
    self.checked_call(a,args,BUFFER if op<2 else PIPES[0],writes=writes,inputs=inputs)
    if op==0:assert u.reg_read(UC_X86_REG_EAX)==BUFFER
    self.event(6,9 if op==0 else 0)
  finally:self.active=False
  assert bytes(u.mem_read(BASE,SIZE))==self.expected,'Unrelated INI lifetime arena changed'
  final=[self.pid(self.word(BUFFER)),self.word(BUFFER+4),u.mem_read(BUFFER+8,1)[0]]
  for p in PIPES:final.extend((self.pid(self.word(p+4)),self.pid(self.word(p+8)),int(self.word(p)==0x79e9f8)))
  return self.trace+['F',*map(str,final+[self.allocated,self.freed,self.attached,self.mutated])]
