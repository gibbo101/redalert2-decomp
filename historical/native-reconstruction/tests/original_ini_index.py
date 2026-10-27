# SPDX-License-Identifier: GPL-3.0-or-later
"""Unchanged INI index roots; heap allocation/free and CRT sorting supplied."""
import struct
from original_presentation import PresentationOracle,STOP
from verify_ini_index import verify,RANGES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ESP,UC_X86_REG_EIP
BASE=0x6e00000;SIZE=0x10000;INDEX=BASE+0x100;QUERY=BASE+0x200;VALUE=BASE+0x204;DETACHED=BASE+0x300;BACKS=tuple(BASE+0x1000+i*0x1000 for i in range(4));OWNERS=tuple(BASE+0x8000+i*0x100 for i in range(4));ALLOC=0x782017;FREE=0x781d3b;SORT=0x781d46
class IniIndexOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(BASE,SIZE);self.active=False;self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.write)
 def va(self,a):return a
 def word(self,a):return int.from_bytes(self.u.mem_read(a,4),'little')
 def pid(self,p):
  if not p:return 0
  if p==DETACHED:return 500
  for i,b in enumerate(BACKS):
   if b<=p<b+32*8 and (p-b)%8==0:return 100+i*100+(p-b)//8
  raise AssertionError(('Unknown INI index identity',hex(p)))
 def valueid(self,p):assert p==0 or p in OWNERS,hex(p);return OWNERS.index(p)+1 if p else 0
 def event(self,k,a=0,b=0,c=0,d=0):self.trace.extend(map(str,(k,a,b,c,d)))
 def change(self,a,raw):self.u.mem_write(a,raw);self.expected[a-BASE:a-BASE+len(raw)]=raw
 def set(self,a,v):self.change(a,struct.pack('<I',v&0xffffffff))
 def mutate(self,where):
  if self.mutated or self.f[10]!=where:return
  self.mutated=1;self.event(6,where)
  if where==1:self.set(INDEX,BACKS[1]);self.set(INDEX+4,1);self.set(INDEX+8,3)
  if where==2:self.set(INDEX,BACKS[1]);self.set(INDEX+4,2);self.set(INDEX+8,-1)
  if where==3:self.set(INDEX,BACKS[1]);self.set(INDEX+4,2);self.set(QUERY,0x80000000)
  if where==4:self.set(INDEX,BACKS[1]);self.set(INDEX+4,1)
  if where==5:self.set(QUERY,0x80000000);self.set(VALUE,OWNERS[2]);self.set(BACKS[0]+4,OWNERS[3])
  if where==6:self.set(INDEX+8,-3)
  if where==7:self.set(INDEX+4,3)
  if where==8:self.set(INDEX+0x10,BACKS[1]+8);self.set(INDEX+4,1);self.set(QUERY,0)
  if where==9:self.set(INDEX+4,0x80000000)
 def write(self,u,access,a,n,v,_):
  if not self.active or not BASE<=a<a+n<=BASE+SIZE:return
  v&=(1<<(n*8))-1;self.expected[a-BASE:a-BASE+n]=v.to_bytes(n,'little');self.pending=[]
  if INDEX<=a<INDEX+20:
   off=a-INDEX;assert (off,n) in ((0,4),(4,4),(8,4),(12,1),(16,4))
   pointer=off in (0,16);self.event(1,off,0 if pointer else v,self.pid(v) if pointer else 0)
   if off==0:self.pending.append(6)
   if off==12 and v==0:self.pending.append(7)
   if off==16 and v==0:self.pending.append(8)
  else:
   b=next((b for b in BACKS if b<=a<b+32*8),None);assert b is not None and n==4,('Unexpected INI index write',hex(a),n)
   off=(a-b)%8;assert off in (0,4);self.event(2,self.pid(a-off),off,0 if off else v,self.valueid(v) if off else 0);self.pending=[4,5] if off==0 else [9]
 def ret(self,sp,pop,value):self.u.reg_write(UC_X86_REG_EAX,value&0xffffffff);self.u.reg_write(UC_X86_REG_EIP,self.word(sp));self.u.reg_write(UC_X86_REG_ESP,sp+4+pop)
 def code(self,u,a,n,_):
  if not self.active:return
  if self.pending:
   pending=self.pending;self.pending=[]
   for where in pending:self.mutate(where)
  if a==STOP:return
  assert a in (ALLOC,FREE,SORT) or any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected INI index instruction',hex(a))
  sp=u.reg_read(UC_X86_REG_ESP)
  if a==ALLOC:
   self.allocated+=1;size=self.word(sp+4);result=0 if self.f[9]==1 else self.word(INDEX) if self.f[9]==2 else BACKS[2 if self.allocated==1 else 3]
   assert result==0 or result in BACKS;self.event(3,size,self.pid(result));self.mutate(1);self.ret(sp,0,result)
  elif a==FREE:
   pointer=self.word(sp+4);assert pointer==0 or pointer in BACKS;self.freed+=1;self.event(4,self.pid(pointer));self.mutate(2);self.ret(sp,0,0)
  elif a==SORT:
   back,count,size,compare=(self.word(sp+off) for off in (4,8,12,16));assert back in BACKS and count<=32 and size==8 and compare==(0x511380 if self.f[0] else 0x511300)
   self.sorts+=1;self.event(5,self.pid(back),count);values=[bytes(u.mem_read(back+i*8,8)) for i in range(count)];values.sort(key=lambda b:int.from_bytes(b[:4],'little',signed=True));self.change(back,b''.join(values));self.mutate(3);self.ret(sp,0,0)
 def run(self,f):
  self.f=f;self.trace=[];self.mutated=0;self.allocated=0;self.freed=0;self.sorts=0;self.pending=[];u=self.u;u.mem_write(BASE,b'\xa5'*SIZE);self.fallback=0xb2b62c if f[0] else 0xb2b630
  hashes=((0,0x80000000,0x7fffffff,16),(0x80000000,0,16,0x7fffffff),(42,42,42,42),(0x7fffffff,16,0,0x80000000))[f[2]]
  for b in BACKS:
   for i in range(32):self.put(b+8*i,0xa5a5a5a5);self.put(b+8*i+4,0)
  for i,h in enumerate(hashes):self.put(BACKS[0]+i*8,h);self.put(BACKS[0]+i*8+4,OWNERS[i]);self.put(BACKS[1]+i*8,hashes[3-i]);self.put(BACKS[1]+i*8+4,OWNERS[3-i])
  self.put(QUERY,f[7]);self.put(VALUE,OWNERS[0]);self.put(DETACHED,f[7]);self.put(DETACHED+4,OWNERS[1]);self.put(self.fallback,OWNERS[3]);self.put(INDEX,BACKS[0]);self.put(INDEX+4,f[3]);self.put(INDEX+8,f[4]);u.mem_write(INDEX+0xc,bytes((f[5],)));self.put(INDEX+0x10,(0,BACKS[0],BACKS[0]+24,BACKS[1]+8,DETACHED)[f[6]])
  self.expected=bytearray(u.mem_read(BASE,SIZE));self.active=True;inputs=[*RANGES.items(),(self.fallback,4)];writes=[(BASE,SIZE)]
  try:
   for _ in range(f[11]):
    op=f[1];root=(0x510ce0,0x510d00,0x5111d0,(0x510ff0 if f[0] else 0x510dd0),(0x511090 if f[0] else 0x510e70),(0x511280 if f[0] else 0x511150))[op]
    args=[] if op==0 else [QUERY,VALUE] if op==1 else [f[8]] if op==2 else [QUERY]
    self.checked_call(root,args,INDEX,writes=writes,inputs=inputs);result=u.reg_read(UC_X86_REG_EAX);value=0
    if op==0:assert result==INDEX;result=1
    elif op in (1,2,3):result&=255
    elif op==4:value=self.valueid(self.word(result));result=999 if result==self.fallback else self.pid(result-4)
    else:result=self.pid(result)
    self.event(7,result,value)
  finally:self.active=False
  assert bytes(u.mem_read(BASE,SIZE))==self.expected,'Unrelated INI index arena changed'
  final=[self.pid(self.word(INDEX)),self.word(INDEX+4),self.word(INDEX+8),u.mem_read(INDEX+0xc,1)[0],self.pid(self.word(INDEX+0x10)),self.valueid(self.word(self.fallback)),self.word(QUERY),self.valueid(self.word(VALUE)),self.allocated,self.freed,self.sorts,self.mutated]
  for b in BACKS:
   for i in range(32):final.extend((self.word(b+i*8),self.valueid(self.word(b+i*8+4))))
  return self.trace+['F',*map(str,final+[self.word(DETACHED),self.valueid(self.word(DETACHED+4))])]
