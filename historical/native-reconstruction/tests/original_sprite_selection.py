# SPDX-License-Identifier: GPL-3.0-or-later
"""Unmodified complete6D1480 with supplied virtual children and audited field reads."""
from original_presentation import PresentationOracle,STOP
from verify_sprite_selection import verify,ENTRY,SIZE
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_READ
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EIP
BASE=0x4a00000;ARENA=0x60000;ACTOR=BASE+0x100;VT=BASE+0x800;HOUSES=[BASE+0x1000,BASE+0x20000];TYPE=BASE+0x40000;TABLE=BASE+0x42000;BACKINGS=[BASE+0x43000+i*0x100 for i in range(3)];SCHEMES=[BASE+0x45000+i*0x400 for i in range(9)];CONVERTERS=[BASE+0x48000+i*0x100 for i in range(9)];STUB=BASE+0x50000
class SpriteSelectionOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(BASE,ARENA);self.active=False
  self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_READ,self.read)
 def va(self,a):return a
 def word(self,p):return int.from_bytes(self.u.mem_read(p,4),'little')
 def signed(self,v):return (v+2**31)%2**32-2**31
 def event(self,*v):self.trace.extend(map(str,v))
 def change(self,p,v):
  self.put(p,v)
  if BASE<=p<BASE+ARENA:self.expected[p-BASE:p-BASE+4]=(v&0xffffffff).to_bytes(4,'little')
  else:self.globals[p]=v
 def ret(self,pop,value):
  sp=self.u.reg_read(UC_X86_REG_ESP);self.u.reg_write(UC_X86_REG_EAX,value&0xffffffff);self.u.reg_write(UC_X86_REG_EIP,self.word(sp));self.u.reg_write(UC_X86_REG_ESP,sp+4+pop)
 def code(self,u,a,n,_):
  if not self.active or a==STOP or ENTRY<=a<ENTRY+SIZE:return
  assert u.reg_read(UC_X86_REG_ECX)==ACTOR
  arg=lambda:self.word(u.reg_read(UC_X86_REG_ESP)+4)
  if a==STUB:
   self.event(2,0x80,1)
   if self.mutation==1:self.change(ACTOR+0x1b4,HOUSES[1]);self.change(TYPE+0xb8c,TABLE)
   self.ret(0,TYPE);return
  if a==STUB+16:
   assert arg()==HOUSES[1];self.event(2,0x3d4,self.pred)
   if self.mutation==2:self.change(HOUSES[0]+0x15f40,2);self.change(0xab6efc,BACKINGS[2])
   self.ret(4,self.pred);return
  if a==STUB+32:
   assert arg()==1;h=self.second if self.calls else self.first;self.calls+=1;self.event(2,0xcc,h)
   if self.mutation==3 and self.calls==1:self.change(HOUSES[0]+0x15f40,2);self.change(0xab6efc,BACKINGS[2])
   if self.mutation==4 and self.calls==2:self.change(HOUSES[1]+0x15f40,0);self.change(0xab6efc,BACKINGS[2])
   self.ret(4,HOUSES[h-1] if h else 0);return
  raise AssertionError(('Uninspected selection instruction',hex(a)))
 def read(self,u,access,p,n,v,_):
  if not self.active or not ENTRY<=u.reg_read(UC_X86_REG_EIP)<ENTRY+SIZE:return
  value=self.word(p)
  if p==ACTOR+0x1b4:self.event(1,0x1b4,HOUSES.index(value)+1)
  elif p==TYPE+0xb8c:self.event(1,0xb8c,3 if value else 0)
  elif p in [h+0x15f40 for h in HOUSES]:self.event(1,0x15f40,self.signed(value))
  elif p==TABLE+4:assert value==BACKINGS[1];self.event(1,4,5)
  elif p==0xa35db4:assert value==HOUSES[1];self.event(1,p,2)
  elif p==0xab6efc:self.event(1,p,4+BACKINGS.index(value))
  elif any(b<=p<b+12 for b in BACKINGS):
   b=next(b for b in BACKINGS if b<=p<b+12);index=(p-b)//4;self.event(1,(4+BACKINGS.index(b))*100+index,8+SCHEMES.index(value))
  elif p in [s+0x30c for s in SCHEMES]:self.event(1,0x30c,15+CONVERTERS.index(value) if value else 0)
 def run(self,cmd):
  over,own,self.pred,self.first,self.second,alt,self.mutation,null=cmd;self.trace=[];self.calls=0
  self.u.mem_write(BASE,b'\x5a'*ARENA);self.put(ACTOR,VT);self.put(VT+0x80,STUB);self.put(VT+0x3d4,STUB+16);self.put(VT+0xcc,STUB+32)
  self.put(ACTOR+0x1b4,HOUSES[0]);self.put(TYPE+0xb8c,TABLE if over else 0);self.put(TABLE+4,BACKINGS[1]);self.put(HOUSES[0]+0x15f40,own);self.put(HOUSES[1]+0x15f40,alt)
  for b in range(3):
   for i in range(3):self.put(BACKINGS[b]+i*4,SCHEMES[b*3+i]);self.put(SCHEMES[b*3+i]+0x30c,0 if null else CONVERTERS[b*3+i])
  self.put(0xa35db4,HOUSES[1]);self.put(0xab6efc,BACKINGS[0]);self.expected=bytearray(self.u.mem_read(BASE,ARENA));self.globals={0xa35db4:HOUSES[1],0xab6efc:BACKINGS[0]}
  self.active=True
  try:self.checked_call(ENTRY,ecx=ACTOR,inputs=[(ENTRY,SIZE),(VT,0x400)])
  except Exception as error:raise AssertionError((cmd,hex(self.u.reg_read(UC_X86_REG_EIP)),self.trace)) from error
  finally:self.active=False
  assert self.u.mem_read(BASE,ARENA)==self.expected,'Unrelated selection arena changed'
  for p,v in self.globals.items():assert self.word(p)==v,'Unrelated global changed'
  result=self.u.reg_read(UC_X86_REG_EAX);self.trace+=['F',str(15+CONVERTERS.index(result) if result else 0),str(self.calls),str(HOUSES.index(self.word(ACTOR+0x1b4))+1),str(self.signed(self.word(HOUSES[0]+0x15f40))),str(self.signed(self.word(HOUSES[1]+0x15f40))),str(4+BACKINGS.index(self.word(0xab6efc)))];return self.trace
