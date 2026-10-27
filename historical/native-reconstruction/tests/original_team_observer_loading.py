# SPDX-License-Identifier: GPL-3.0-or-later
"""Unchanged full observer parser/Team lookup/TaskForce/trim/FTOL, named CRT inputs."""
import struct,re,math
from original_presentation import PresentationOracle,STOP,STACK
from original_fp_return import push_double
from verify_team_observer_loading import verify,RANGES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE,UC_HOOK_MEM_READ
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EIP,UC_X86_REG_FPSW,UC_X86_REG_FPTAG,UC_X86_REG_FPCW
BASE=0x6800000;SIZE=0x10000;ACTOR=BASE+0x100;INI=BASE+0x400;TEAMS=tuple(BASE+0x1000+0x200*i for i in range(3));OBJECTS=tuple(BASE+0x2000+0x100*i for i in range(4));TECH=tuple(BASE+0x3000+0x800*i for i in range(3));TASK=(BASE+0x5000,BASE+0x5200);BACK=BASE+0x6000;ALT=BASE+0x6100;OBACK=tuple(BASE+0x6200+0x100*i for i in range(4))
SERVICES=(0x50e9a0,0x782ec2,0x7823d0,0x4f94d0,0x50a070,0x70a890,0x41be60,0x4583d0,0x782dfd,0x782f66,0x782be1,0x782fbd)
OBJECT_BACK=(0xa40354,0xa35d4c,0xa3d27c,0xa35cdc)
LEVELS=((5,-1,20),(20,-1,5),(-1,20,-1),(-2147483648,0,2147483647),(1,2,3),(-1,-1,-1))
def hash_text(b):
 result=2166136261
 for c in b.split(b'\0')[0]:result=((result^c)*16777619)&0xffffffff
 return result
def integer(b):
 m=re.match(rb'[\t\n\v\f\r ]*[+-]?[0-9]+',b);return int(m[0])&0xffffffff if m else 0
def hex_integer(b):
 m=re.match(rb'[\t\n\v\f\r ]*([+-]?)([0-9a-fA-F]+)',b)
 return ((-1 if m[1]==b'-' else 1)*int(m[2],16))&0xffffffff if m else 0
def trim_buffer(raw,capacity):
 src=raw.split(b'\0')[0];out=bytearray(src[:capacity-1].ljust(capacity,b'\0'));out[-1]=0
 first=0
 while out[first] and out[first]<=32:first+=1
 end=first
 while out[end]:end+=1
 if first:out[:end-first+1]=out[first:end+1]
 end=out.index(0)
 while end>0 and out[first] and out[end-1]<=32:out[end-1]=0;end-=1
 return out
class TeamObserverLoadingOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(BASE,SIZE);self.active=False;self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.write);self.u.hook_add(UC_HOOK_MEM_READ,self.read)
 def va(self,a):return a
 def word(self,a):return int.from_bytes(self.u.mem_read(a,4),'little')
 def text(self,a):
  if not a:return b''
  out=bytearray()
  for i in range(1024):
   v=self.u.mem_read(a+i,1)[0]
   if not v:return bytes(out)
   out.append(v)
  raise AssertionError('Unbounded original text')
 def event(self,k,a=0,b=0,c=0):self.trace.extend(map(str,(k,a,b,c)))
 def pid(self,p):
  d={0:0,**{p:i+1 for i,p in enumerate(TEAMS)},**{p:i+11 for i,p in enumerate(OBJECTS)},**{p:i+21 for i,p in enumerate(TECH)}};assert p in d,hex(p);return d[p]
 def change(self,a,raw):
  self.u.mem_write(a,raw)
  if BASE<=a<a+len(raw)<=BASE+SIZE:self.expected[a-BASE:a-BASE+len(raw)]=raw
  else:self.globals[a]=bytes(raw)
 def change_word(self,a,v):self.change(a,struct.pack('<I',v&0xffffffff))
 def mutate(self,where):
  if self.mutated or self.f[5]!=where:return
  self.mutated=1;self.event(13,where)
  if where==1:self.change_word(0xa40c4c,ALT)
  if where==2:
   for p in TASK:self.change_word(p+0x9c,1)
   self.change_word(0xa3d298,0);self.change_word(TECH[1]+0x55c,42)
  if where==3:self.change_word(ACTOR+0xdc,TEAMS[1]);self.change_word(ACTOR+0xe0,TEAMS[0]);self.change_word(ACTOR+0xb0,123)
  if where==4:self.change_word(ACTOR+0xdc,TEAMS[1])
 def read(self,u,access,a,n,v,_):
  if not self.active:return
  if a in tuple(p+0x55c for p in TECH):
   assert n==4;self.event(10,self.pid(a-0x55c),self.word(a));self.mutate(2);self.mutate(4)
 def write(self,u,access,a,n,v,_):
  if not self.active or not BASE<=a<a+n<=BASE+SIZE:return
  assert ACTOR<=a<a+n<=ACTOR+0x110,('Unexpected observer loader arena write',hex(a),n)
  off=a-ACTOR;v&=(1<<(8*n))-1;self.event(1,off,n,self.pid(v) if off in (0xd8,0xdc,0xe0) else v)
  self.expected[a-BASE:a-BASE+n]=v.to_bytes(n,'little')
  if off==0xb8 and n==8:self.mutate(3)
 def ret(self,sp,pop,value=0):
  self.u.reg_write(UC_X86_REG_EAX,value&0xffffffff);self.u.reg_write(UC_X86_REG_EIP,self.word(sp));self.u.reg_write(UC_X86_REG_ESP,sp+4+pop)
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  assert a in SERVICES or any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected observer loader instruction',hex(a))
  sp=u.reg_read(UC_X86_REG_ESP);obj=u.reg_read(UC_X86_REG_ECX)
  if a==0x781f20:
   first,second=(self.text(self.word(sp+off)) for off in (4,8));self.event(2,hash_text(first),hash_text(second))
   if 0x6bf260<=self.word(sp)<0x6bf2c1:self.mutate(1)
  elif a==0x6bf260:self.event(12,hash_text(self.text(obj)))
  elif a==0x6b7140:self.event(11,TASK.index(obj))
  elif a==0x50e9a0:
   assert obj==INI;section,key,fallback,out,cap=(self.word(sp+off) for off in (4,8,12,16,20));assert self.text(section)==b'AITriggerTypes' and self.text(key)==b'observer' and not self.text(fallback) and cap==512 and STACK-0x2000<=out<out+cap<=STACK
   self.event(3,hash_text(self.text(key)));value=b'' if self.f[0] is None else self.f[0];buf=trim_buffer(value,512);u.mem_write(out,bytes(buf));self.ret(sp,20,buf.index(0))
  elif a==0x782ec2:
   source=self.word(sp+4);assert self.text(self.word(sp+8))==b','
   if source:self.cursor=source
   while self.cursor and u.mem_read(self.cursor,1)==b',':self.cursor+=1
   if not self.cursor or u.mem_read(self.cursor,1)==b'\0':self.ret(sp,0);return
   start=self.cursor
   while u.mem_read(self.cursor,1) not in (b',',b'\0'):self.cursor+=1
   if u.mem_read(self.cursor,1)==b',':u.mem_write(self.cursor,b'\0');self.cursor+=1
   self.ret(sp,0,start)
  elif a==0x7823d0:
   dest,source,cap=(self.word(sp+off) for off in (4,8,12));assert cap in (24,48) and source and STACK-0x2000<=dest<dest+cap<=STACK;raw=self.text(source)[:cap];u.mem_write(dest,raw.ljust(cap,b'\0'));self.ret(sp,0,dest)
  elif a==0x4f94d0:
   value=self.f[4]&0xffffffff;self.event(6,hash_text(self.text(obj)),value);self.ret(sp,0,value)
  elif a in SERVICES[4:8]:
   kind=SERVICES[4:8].index(a);index=0 if self.f[3]==kind else 0xffffffff;self.event(7,kind,hash_text(self.text(obj)),index);self.ret(sp,0,index)
  elif a==0x782dfd:
   token=self.text(self.word(sp+4));value=integer(token);self.event(4,hash_text(token),value);self.ret(sp,0,value)
  elif a==0x782f66:
   token=self.text(self.word(sp+4));match=re.match(rb'[\t\n\v\f\r ]*[+-]?(?:(?:[0-9]+(?:\.[0-9]*)?|\.[0-9]+)(?:[eE][+-]?[0-9]+)?|inf(?:inity)?|nan)',token,re.I);value=float(match[0].decode('ascii')) if match else 0.;bits=struct.unpack('<Q',struct.pack('<d',value))[0];self.event(5,hash_text(token),bits);push_double(u,bits);self.ret(sp,0)
  elif a==0x782be1:
   arg=self.word(sp+4);c=arg if arg<2**31 else arg-2**32;value=int(c in (9,10,11,12,13,32));self.event(8,arg,value);self.ret(sp,0,value)
  elif a==0x782fbd:
   source,end,base=(self.word(sp+off) for off in (4,8,12));assert base==16 and STACK-0x2000<=end<end+4<=STACK;token=self.text(source);value=hex_integer(token);self.event(9,hash_text(token),value);self.put(end,source+len(token));self.ret(sp,0,value)
 def run(self,f):
  self.f=f;self.trace=[];self.mutated=0;self.cursor=0;u=self.u;u.mem_write(BASE,b'\x5a'*SIZE)
  u.mem_write(ACTOR+0x24,b'observer\0');u.mem_write(ACTOR+0x64,b'Q'*48+b'\0')
  for off,value in ((0x98,-7),(0xa0,44),(0xa8,-3),(0xac,55),(0xb0,66),(0x104,7),(0x108,11),(0xdc,TEAMS[0]),(0xe0,TEAMS[1]),(0xd8,OBJECTS[3])):self.put(ACTOR+off,value)
  for off,value in ((0xb8,23.75),(0xc0,-2.5),(0xc8,99.25)):u.mem_write(ACTOR+off,struct.pack('<d',value))
  u.mem_write(ACTOR+0xd0,bytes((128,129,130,131,132)));u.mem_write(ACTOR+0xe4,struct.pack('<8I',*[0xaabbccdd]*8))
  for i,p in enumerate(TEAMS):
   u.mem_write(p+0x24,(b'ALPHA',b'beta',b'alias')[i]+b'\0');u.mem_write(p+0x64,(b'first team',b'second team',b'ALPHA')[i]+b'\0');self.put(p+0xdc,TASK[1 if i==1 else 0])
  self.put(0xa40c4c,ALT if f[6]==1 else BACK);self.put(0xa40c58,0 if f[6]==2 else -1 if f[6]==3 else 1 if f[6]==4 else 3);self.put(0xa3d298,f[1]);self.put(0xb2b098,0)
  for i,p in enumerate(TEAMS):self.put(BACK+4*i,p);self.put(ALT+4*i,TEAMS[(1,0,2)[i]])
  for i,p in enumerate(TASK):self.put(p+0x9c,0 if f[2]==6 else (-1 if i==0 else -2147483648) if f[2]==7 else (1 if i==0 else 3) if f[2]==8 else 3 if i==0 else 2);[self.put(p+0xa8+8*j,t) for j,t in enumerate(TECH)]
  for p,value in zip(TECH,LEVELS[f[2]%6]):self.put(p+0x55c,value)
  for i,p in enumerate(OBJECT_BACK):self.put(p,OBACK[i]);self.put(OBACK[i],OBJECTS[i])
  self.expected=bytearray(u.mem_read(BASE,SIZE));self.globals={p:bytes(u.mem_read(p,4)) for p in (0xa40c4c,0xa40c58,0xa3d298,0xb2b098,*OBJECT_BACK)};u.reg_write(UC_X86_REG_FPSW,0);u.reg_write(UC_X86_REG_FPTAG,0xffff);self.active=True
  inputs=[*RANGES.items(),(0x7d8964,4),(0x79b748,4),(0x7ceacc,8)];writes=[(BASE,SIZE),(0xa40c4c,4),(0xa3d298,4)]
  try:
   for _ in range(f[7]):self.checked_call(0x41d7e0,[INI],ACTOR,writes=writes,inputs=inputs)
  finally:self.active=False
  assert bytes(u.mem_read(BASE,SIZE))==self.expected,'Unrelated observer parser arena changed'
  assert all(bytes(u.mem_read(p,len(v)))==v for p,v in self.globals.items()),'Unrelated observer parser global changed'
  assert (u.reg_read(UC_X86_REG_FPSW)>>11)&7==0 and u.reg_read(UC_X86_REG_FPTAG)==0xffff
  result=[u.reg_read(UC_X86_REG_EAX)&255,self.mutated,*u.mem_read(ACTOR+0x64,49),*[self.word(ACTOR+off) for off in (0x98,0xa0,0xa8,0xac,0xb0)],*[int.from_bytes(u.mem_read(ACTOR+off,8),'little') for off in (0xb8,0xc0,0xc8)],*u.mem_read(ACTOR+0xd0,5),*[self.pid(self.word(ACTOR+off)) for off in (0xd8,0xdc,0xe0)],*[self.word(ACTOR+0xe4+4*i) for i in range(8)],self.word(ACTOR+0x104),self.word(ACTOR+0x108),*[self.word(p+0x9c) for p in TASK],self.word(0xa3d298),*[self.word(p+0x55c) for p in TECH],self.word(0xa40c58),*[self.pid(self.word(self.word(0xa40c4c)+4*i)) for i in range(3)]]
  return self.trace+['F',*map(str,result)]
