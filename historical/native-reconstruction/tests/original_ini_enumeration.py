# SPDX-License-Identifier: GPL-3.0-or-later
"""Unchanged INI count/key/cache/search plus actual CRC; CRT qsort supplied."""
import struct
from original_presentation import PresentationOracle,STOP
from verify_ini_enumeration import verify,RANGES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EIP
BASE=0x6a00000;SIZE=0x10000;INI=BASE+0x100;INDEX=INI+0x20;BACK=BASE+0x500;ALT=BASE+0x600;DETACHED=BASE+0x700;SECTIONS=tuple(BASE+0x1000+i*0x200 for i in range(4));NODES=tuple(tuple(BASE+0x3000+i*0x400+j*0x40 for j in range(4)) for i in range(4));NAMES=tuple(BASE+0x5000+i*0x100 for i in range(4));NAME=BASE+0x6000;CRC=BASE+0x8000;QUERY=BASE+0x8100;SORT=0x781d46;FALLBACK=0xb2b62c
class IniEnumerationOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(BASE,SIZE);self.active=False;self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.write)
 def va(self,a):return a
 def word(self,a):return int.from_bytes(self.u.mem_read(a,4),'little')
 def pid(self,p):
  d={0:0,DETACHED:301,**{BACK+8*i:101+i for i in range(4)},**{ALT+8*i:201+i for i in range(4)},**{p:1+i for i,p in enumerate(SECTIONS)}};assert p in d,hex(p);return d[p]
 def keyid(self,p):assert p==0 or p in NAMES,hex(p);return NAMES.index(p)+1 if p else 0
 def event(self,k,a=0,b=0,c=0):self.trace.extend(map(str,(k,a,b,c)))
 def change(self,a,raw):
  self.u.mem_write(a,raw)
  if BASE<=a<a+len(raw)<=BASE+SIZE:self.expected[a-BASE:a-BASE+len(raw)]=raw
  else:self.globals[a]=bytes(raw)
 def change_word(self,a,v):self.change(a,struct.pack('<I',v&0xffffffff))
 def mutate(self,where):
  if self.mutated or self.f[7]!=where:return
  self.mutated=1;self.event(3,where)
  if where==1:self.change_word(INDEX,ALT)
  if where==2:self.change_word(INDEX+4,1)
  if where==3:self.change_word(INDEX+0x10,ALT+16)
  if where==4:self.change_word(INDEX+4,0)
  if where==5:self.change(INDEX+0xc,b'\x80')
  if where==6:
   hot=self.word(INDEX+0x10)
   if hot:self.change_word(self.word(hot+4)+0x30,0xffffffff)
 def write(self,u,access,a,n,v,_):
  if not self.active or not BASE<=a<a+n<=BASE+SIZE:return
  assert (a,n) in ((INDEX+0x10,4),(INDEX+0xc,1)),('Unexpected INI arena write',hex(a),n)
  v&=(1<<(8*n))-1;self.expected[a-BASE:a-BASE+n]=v.to_bytes(n,'little');self.event(2,a-INDEX,v if n==1 else 0,self.pid(v) if n==4 else 0)
  if n==4 and v:self.pending=True
 def ret(self,sp,pop,value):
  self.u.reg_write(UC_X86_REG_EAX,value&0xffffffff);self.u.reg_write(UC_X86_REG_EIP,self.word(sp));self.u.reg_write(UC_X86_REG_ESP,sp+4+pop)
 def code(self,u,a,n,_):
  if not self.active:return
  if self.pending:
   self.pending=False;self.mutate(3);self.mutate(4);self.mutate(6)
  if a==STOP:return
  assert a==SORT or any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected INI instruction',hex(a))
  if a==SORT:
   sp=u.reg_read(UC_X86_REG_ESP);back,count,size,compare=(self.word(sp+off) for off in (4,8,12,16));assert back in (BACK,ALT) and count<=4 and size==8 and compare==0x511380;self.event(1,self.pid(back),count)
   values=[bytes(u.mem_read(back+i*8,8)) for i in range(count)];values.sort(key=lambda b:int.from_bytes(b[:4],'little',signed=True))
   self.change(back,b''.join(values));self.mutate(1);self.mutate(2);self.mutate(5);self.ret(sp,0,0)
 def crc(self,raw):
  # Separate complete root with a checked scratch-only write set. Parent CRC
  # calls use their actual stack scratch and are executed unchanged as well.
  before=bytes(self.u.mem_read(CRC,16));self.u.mem_write(CRC,bytes(16));active=self.active;self.active=False
  try:self.checked_call(0x493fc0,[NAME,len(raw.split(b'\0')[0])],CRC,writes=[(CRC,16)],inputs=[(NAME,len(raw)+1),(0x7d5504,1024),*[(a,n) for a,n in RANGES.items() if a in (0x493fc0,0x494190)]])
  finally:self.active=active
  result=self.u.reg_read(UC_X86_REG_EAX);self.u.mem_write(CRC,before);return result
 def run(self,f):
  self.f=f;self.trace=[];self.mutated=0;self.pending=False;u=self.u;u.mem_write(BASE,b'\x5a'*SIZE);raw=f[0] or b'';u.mem_write(NAME,raw+b'\0');query=self.crc(raw);self.put(QUERY,query)
  hashes=((query,0x80000000,0x7fffffff,0),(0x80000000,0,query,0x7fffffff),(query,)*4,(1,16,256,4096),(query,0x80000000,0x7fffffff,0),(query,0x80000000,0x7fffffff,0),(0xffffffff,0xfffffffe,0x80000000,0x80000001))
  entries=list(zip(hashes[f[1]],SECTIONS))
  if f[1] in (4,5):entries.sort(key=lambda e:e[0] if e[0]<2**31 else e[0]-2**32,reverse=f[1]==5)
  alternate=entries.copy();alternate[0],alternate[1]=alternate[1],alternate[0]
  for back,values in ((BACK,entries),(ALT,alternate)):
   for i,(h,p) in enumerate(values):self.put(back+i*8,h);self.put(back+i*8+4,p)
  self.put(DETACHED,query);self.put(DETACHED+4,SECTIONS[1]);self.put(INDEX,BACK);self.put(INDEX+4,f[2]);u.mem_write(INDEX+0xc,bytes((f[3],)));self.put(INDEX+0x10,(0,BACK,BACK+24,ALT+8,DETACHED)[f[4]]);self.put(FALLBACK,SECTIONS[3])
  for i,p in enumerate(NAMES):u.mem_write(p,(b'zeta',b'alpha',b'middle',b'sentinel')[i]+b'\0')
  for i,p in enumerate(SECTIONS):
   self.put(p+0x18,0 if f[5]==1 else NODES[i][0]);self.put(p+0x30,3+2*i)
   for j,node in enumerate(NODES[i]):
    self.put(node+4,0 if j==3 or f[5]==2 and j==0 else NODES[i][j+1]);self.put(node+8,0 if j==3 or f[5]==3 and j==0 else node);self.put(node+0xc,0 if f[5]==4 and j==1 else NAMES[j])
   if f[5]==5:
    for j,k in ((0,2),(2,1),(1,3)):self.put(NODES[i][j]+4,NODES[i][k])
  self.expected=bytearray(u.mem_read(BASE,SIZE));self.globals={FALLBACK:bytes(u.mem_read(FALLBACK,4))};self.active=True
  inputs=[*RANGES.items(),(NAME,len(raw)+1),(QUERY,4),(0x7d5504,1024)];writes=[(BASE,SIZE)]
  try:
   for _ in range(f[8]):
    op=f[9];name=0 if f[0] is None else NAME
    if op==0:self.checked_call(0x50cb00,[name],INI,writes=writes,inputs=inputs);result=u.reg_read(UC_X86_REG_EAX)
    elif op==1:self.checked_call(0x50ce00,[name,f[6]],INI,writes=writes,inputs=inputs);result=self.keyid(u.reg_read(UC_X86_REG_EAX))
    elif op==2:self.checked_call(0x511090,[QUERY],INDEX,writes=writes,inputs=inputs);result=self.pid(self.word(u.reg_read(UC_X86_REG_EAX)))
    elif op==3:self.checked_call(0x511280,[QUERY],INDEX,writes=writes,inputs=inputs);result=self.pid(u.reg_read(UC_X86_REG_EAX))
    elif op==4:self.checked_call(0x511260,[QUERY],INDEX,writes=writes,inputs=inputs);result=u.reg_read(UC_X86_REG_EAX)&255
    else:result=self.crc(raw)
    self.event(4,result)
  finally:self.active=False
  assert bytes(u.mem_read(BASE,SIZE))==self.expected,'Unrelated INI arena changed'
  assert all(bytes(u.mem_read(a,len(v)))==v for a,v in self.globals.items()),'Unrelated INI globals changed'
  result=[query,self.mutated,self.word(INDEX+4),u.mem_read(INDEX+0xc,1)[0],self.pid(self.word(INDEX+0x10)),self.pid(self.word(INDEX))]
  for back in (BACK,ALT):
   for i in range(4):result.extend((self.word(back+i*8),self.pid(self.word(back+i*8+4))))
  result.extend(self.word(p+0x30) for p in SECTIONS)
  return self.trace+['F',*map(str,result)]
