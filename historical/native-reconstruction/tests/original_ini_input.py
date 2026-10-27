# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete line/buffer/forward routines; upstream reads and memcpy supplied."""
import struct
from original_presentation import PresentationOracle,STOP,STACK
from verify_ini_input import verify,RANGES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EIP
BASE=0x6b00000;SIZE=0x10000;PIPE=BASE+0x100;SOURCES=(BASE+0x500,BASE+0x600);VTABLE=BASE+0x800;READ=BASE+0x900;OUT=BASE+0x1000;BUFFER=BASE+0x2000;ALT=BASE+0x2100;EOF=BASE+0x2200;COPY=0x783290
class IniInputOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(BASE,SIZE);self.active=False;self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.write)
 def va(self,a):return a
 def word(self,a):return int.from_bytes(self.u.mem_read(a,4),'little')
 def event(self,k,a=0,b=0,c=0):self.trace.extend(map(str,(k,a,b,c)))
 def change(self,a,raw):
  self.u.mem_write(a,raw)
  if BASE<=a<a+len(raw)<=BASE+SIZE:self.expected[a-BASE:a-BASE+len(raw)]=raw
 def change_word(self,a,v):self.change(a,struct.pack('<I',v&0xffffffff))
 def mutate(self,where):
  if self.mutated or self.f[9]!=where:return
  self.mutated=1;self.event(5,where)
  if where==1:self.change_word(PIPE+4,SOURCES[1])
  if where==2:self.change_word(PIPE+0xc,ALT)
  if where==3:self.change_word(PIPE+0x18,2);self.change_word(PIPE+0x1c,3)
  if where==4:self.change_word(PIPE+0x1c,99)
  if where==5:self.change_word(PIPE+0x18,3)
  if where==6:self.change_word(PIPE+0x10,2)
 def write(self,u,access,a,n,v,_):
  if not self.active or not BASE<=a<a+n<=BASE+SIZE:return
  v&=(1<<(8*n))-1;self.expected[a-BASE:a-BASE+n]=v.to_bytes(n,'little')
  if (a,n) in ((PIPE+0x18,4),(PIPE+0x1c,4)):
   off=a-PIPE;self.event(3,off,v)
   if off==0x18 and self.copying:self.pending=4
   if off==0x1c and not self.copying:self.pending=5
  elif (OUT<=a<a+n<=OUT+520 or a==self.eof) and n==1:
   flag=u.reg_read(UC_X86_REG_EIP)==0x6396dd;self.event(4,int(flag),0 if flag else a-OUT,v)
  else:raise AssertionError(('Unexpected INI input arena write',hex(a),n))
 def ret(self,sp,pop,value):
  self.u.reg_write(UC_X86_REG_EAX,value&0xffffffff);self.u.reg_write(UC_X86_REG_EIP,self.word(sp));self.u.reg_write(UC_X86_REG_ESP,sp+4+pop)
 def code(self,u,a,n,_):
  if not self.active:return
  if self.pending:where=self.pending;self.pending=0;self.mutate(where)
  if a==STOP:return
  assert a in (READ,COPY) or any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected INI input instruction',hex(a))
  sp=u.reg_read(UC_X86_REG_ESP);obj=u.reg_read(UC_X86_REG_ECX)
  if a==READ:
   source=self.word(PIPE+4) if obj==PIPE else obj;assert source in SOURCES
   dest,requested=(self.word(sp+off) for off in (4,8));signed=requested if requested<2**31 else requested-2**32;self.copying=False;self.calls+=1
   count=0 if signed<=0 else min(signed,self.f[4],len(self.f[0])-self.position);returned=count
   if self.calls==1 and self.f[8]==1:count=0;returned=-1
   elif self.calls==1 and self.f[8]==2:returned=2
   elif self.f[8]==3:count=0;returned=0
   assert count<=64 and (dest in (OUT,BUFFER,ALT) or STACK-0x2000<=dest<=dest+count<=STACK),('Unexpected upstream output',hex(dest),count)
   self.change(dest,self.f[0][self.position:self.position+count]);self.position+=count;self.event(1,SOURCES.index(source)+1,requested,returned&0xffffffff)
   self.mutate(1);self.mutate(2);self.mutate(3);self.mutate(6);self.ret(sp,8,returned)
  elif a==COPY:
   dest,source,count=(self.word(sp+off) for off in (4,8,12));assert count<=64
   sourceOffset=next((100+i if source==BUFFER+i else 200+i for i in range(64) if source in (BUFFER+i,ALT+i)),None);assert sourceOffset is not None
   assert OUT<=dest<dest+count<=OUT+520 or STACK-0x2000<=dest<=dest+count<=STACK
   assert source+count<=(BUFFER+64 if source<ALT else ALT+64)
   self.event(2,dest-OUT if OUT<=dest<OUT+520 else 1000,sourceOffset,count);self.change(dest,bytes(u.mem_read(source,count)));self.copying=True;self.ret(sp,0,dest)
 def run(self,f):
  self.f=f;self.trace=[];self.mutated=0;self.position=0;self.calls=0;self.copying=False;self.pending=0;u=self.u;u.mem_write(BASE,b'\xa5'*SIZE)
  self.eof=0 if f[7]==-1 else OUT if f[7]==-2 else OUT+519 if f[7]==-3 else EOF
  u.mem_write(EOF,bytes((f[7]&255,)));u.mem_write(BUFFER,bytes(range(0x40,0x80)));u.mem_write(ALT,bytes((0xd0+i)&255 for i in range(64)))
  self.put(VTABLE+8,READ)
  for p in SOURCES:self.put(p,VTABLE)
  self.put(PIPE,VTABLE if f[1]==0 else 0x7a3bbc);self.put(PIPE+4,SOURCES[0]);self.put(PIPE+0xc,BUFFER);self.put(PIPE+0x10,f[3]);self.put(PIPE+0x18,f[5]);self.put(PIPE+0x1c,f[6])
  self.expected=bytearray(u.mem_read(BASE,SIZE));self.active=True
  inputs=[*RANGES.items(),(0x7a3bbc,12),(VTABLE+8,4),*[(p,4) for p in SOURCES]]
  try:
   for _ in range(f[10]):
    mode=f[1]
    if mode<=1:self.checked_call(0x639670,[f[2],self.eof],PIPE,OUT,writes=[(BASE,SIZE)],inputs=inputs)
    else:self.checked_call(0x494760 if mode==2 else 0x69b0a0,[OUT,f[2]],PIPE,writes=[(BASE,SIZE)],inputs=inputs)
    self.event(6,u.reg_read(UC_X86_REG_EAX))
  finally:self.active=False
  assert bytes(u.mem_read(BASE,SIZE))==self.expected,'Unrelated INI input arena changed'
  result=[self.mutated,SOURCES.index(self.word(PIPE+4))+1,1 if self.word(PIPE+0xc)==BUFFER else 2,self.word(PIPE+0x10),self.word(PIPE+0x18),self.word(PIPE+0x1c),self.position,self.calls,u.mem_read(self.eof,1)[0] if self.eof else 256,*u.mem_read(OUT,520),*u.mem_read(BUFFER,64),*u.mem_read(ALT,64)]
  return self.trace+['F',*map(str,result)]
