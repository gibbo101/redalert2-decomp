# SPDX-License-Identifier: GPL-3.0-or-later
"""Unchanged complete Infantry speed on explicit original actor/type owners."""
import struct
from collections import Counter
from original_presentation import PresentationOracle,STOP
from verify_infantry_speed import verify,RANGES,TABLES
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP
ARENA=0x2900000;SIZE=0x6000;ACTOR=ARENA;TYPE=ARENA+0x1000;HOUSE=ARENA+0x2000;COUNTRY=ARENA+0x3000;RULES=ARENA+0x4000
def signed(n):return n if n<2**31 else n-2**32
class InfantrySpeedOracle(PresentationOracle):
 def va(self,a):return a
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(ARENA,SIZE)
  self.active=False;self.events=[];self.counts=Counter();self.u.hook_add(UC_HOOK_CODE,self.code)
 def emit(self,k,x=0):
  self.events.extend(map(str,(k,x)))
  if k=='c':return
  self.queries+=1
  if self.queries!=self.values[12]:return
  u=self.u;m=self.values[11]
  if m&1:self.put(TYPE+0x5a0,17);u.mem_write(COUNTRY+0x128,struct.pack('<f',.5))
  if m&2:u.mem_write(ACTOR+0x470,struct.pack('<d',1.75));u.mem_write(ACTOR+0x468,struct.pack('<d',.375))
  if m&4:u.mem_write(ACTOR+0x118,struct.pack('<d',1.5))
  if m&8:
   for p,mask in ((ACTOR+0x5c3,255),(TYPE+0xc0b,128)):u.mem_write(p,bytes([u.mem_read(p,1)[0]^mask]))
  if m&16:
   for p in (TYPE+0x26c,TYPE+0x27e):u.mem_write(p,bytes([u.mem_read(p,1)[0]^1]))
   u.mem_write(RULES+0x598,struct.pack('<d',2.25))
 def code(self,u,a,n,ctx):
  if not self.active or a==STOP:return
  assert any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected Infantry speed instruction',hex(a))
  if a in RANGES:self.counts[hex(a)]+=1
  ecx=u.reg_read(UC_X86_REG_ECX);sp=u.reg_read(UC_X86_REG_ESP)
  if a==0x6c12c0:assert ecx==ACTOR;self.emit('t')
  elif a==0x4f5a20:assert ecx==HOUSE and int.from_bytes(u.mem_read(sp+4,4),'little')==TYPE;self.emit('h')
  elif a==0x6d7910:assert ecx==ACTOR and u.mem_read(sp+4,4)==bytes(4);self.emit('b')
  elif a==0x7133a0:assert ecx==ACTOR+0x118;self.emit('v')
  elif a==0x713420:assert ecx==ACTOR+0x118;self.emit('e')
  elif a==0x4c9b65:self.emit('r')
  elif a==0x509800:assert ecx==ACTOR;self.emit('k')
  elif a in (0x77f135,0x77f14c):self.emit('c',signed(u.reg_read(UC_X86_REG_EAX)))
 def run_speed(self,v):
  self.values=v;u=self.u;u.mem_write(ARENA,b'\xa5'*SIZE);self.events=[]
  for p,value in ((ACTOR,0x7a3540),(ACTOR+0x5a8,TYPE),(ACTOR+0x1b4,HOUSE),(TYPE,0x7a3a78),(TYPE+0x5a0,v[0]),(HOUSE+0x34,COUNTRY),(0x839848,RULES)):
   self.put(p,value)
  for p,value in ((COUNTRY+0x128,v[1]),):u.mem_write(p,struct.pack('<I',value))
  for p,value in ((ACTOR+0x470,v[2]),(ACTOR+0x468,v[3]),(ACTOR+0x118,v[4]),(RULES+0x598,v[5])):u.mem_write(p,struct.pack('<Q',value))
  for p,value in ((ACTOR+0x5c3,v[7]),(TYPE+0xc0b,v[8]),(TYPE+0x26c,v[9]),(TYPE+0x27e,v[10])):u.mem_write(p,bytes([value]))
  writes=sorted([(TYPE+0x5a0,4),(COUNTRY+0x128,4),(ACTOR+0x470,8),(ACTOR+0x468,8),(ACTOR+0x118,8),(RULES+0x598,8),
   (ACTOR+0x5c3,1),(TYPE+0xc0b,1),(TYPE+0x26c,1),(TYPE+0x27e,1)])
  inputs=[];cursor=ARENA
  for p,n in writes:
   if cursor<p:inputs.append((cursor,p-cursor))
   cursor=p+n
  inputs.append((cursor,ARENA+SIZE-cursor));inputs+=list(RANGES.items())+list(TABLES.items())+[(0x839848,4)]
  for _ in range(v[6]):
   self.queries=0;self.active=True
   try:self.checked_call(0x508980,ecx=ACTOR,writes=writes,inputs=inputs)
   finally:self.active=False
   self.events.extend(('R',str(signed(u.reg_read(UC_X86_REG_EAX)))))
  self.events.append('Z')
  for p,fmt in ((TYPE+0x5a0,'I'),(COUNTRY+0x128,'I'),(ACTOR+0x470,'Q'),(ACTOR+0x468,'Q'),(ACTOR+0x118,'Q'),(RULES+0x598,'Q'),
   (ACTOR+0x5c3,'B'),(TYPE+0xc0b,'B'),(TYPE+0x26c,'B'),(TYPE+0x27e,'B')):self.events.append(str(struct.unpack('<'+fmt,u.mem_read(p,struct.calcsize(fmt)))[0]))
  return self.events
