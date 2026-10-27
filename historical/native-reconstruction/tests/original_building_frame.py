# SPDX-License-Identifier: GPL-3.0-or-later
"""Unmodified complete Building frame selector and actual ratio/mission children."""
import struct
from collections import Counter
from original_presentation import PresentationOracle,STOP
from verify_building_frame import verify,RANGES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_READ
from unicorn.x86_const import UC_X86_REG_ECX,UC_X86_REG_EAX,UC_X86_REG_ESP,UC_X86_REG_EIP
BASE=0x4600000;SIZE=0x10000;ACTOR=BASE+0x1000;TYPES=[BASE+0x3000,BASE+0x5000];RULES=BASE+0x7000
class BuildingFrameOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(BASE,SIZE);self.active=False;self.counts=Counter()
  self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_READ,self.read)
 def va(self,a):return a
 def word(self,p):return int.from_bytes(self.u.mem_read(p,4),'little')
 def signed(self,v):return (v+2**31)%2**32-2**31
 def event(self,subject,off,value):self.trace.extend(map(str,(subject,off,value)))
 def write(self,p,data):self.u.mem_write(p,data);self.expected[p-BASE:p-BASE+len(data)]=data
 def ints(self,p,values):self.u.mem_write(p,struct.pack('<'+'I'*len(values),*[x&0xffffffff for x in values]))
 def mutate(self,child):
  mode=self.mode
  if self.mutated or not mode:return
  if mode in (1,5) and child!=0 or mode in (2,3,4) and child!=1:return
  self.mutated=True;self.event(4,child,mode)
  def put(p,v):self.write(p,struct.pack('<I',v&0xffffffff))
  if mode in (1,5):put(ACTOR+0x418,TYPES[1]);put(ACTOR+0x42c,-2**31 if mode==5 else 2);put(ACTOR+0xe0,999)
  elif mode in (2,3):put(ACTOR+0x418,TYPES[1]);put(ACTOR+0x42c,1 if mode==2 else 2);put(ACTOR+0x6c,0)
  elif mode==4:put(self.word(ACTOR+0x418)+0x137c,2**31-1);self.write(RULES+0x1368,struct.pack('<Q',0x7ff8000000000000))
 def read(self,u,access,p,n,value,_):
  if not self.active:return
  # Only parent scalar loads; health and mission children execute in their own
  # verified ranges and emit entry/service events separately.
  pc=u.reg_read(UC_X86_REG_EIP)
  if not 0x43be20<=pc<0x43bfb1:return
  if p-ACTOR in (0xe0,0x42c,0x4ec,0x4f0,0x564):self.event(0,p-ACTOR,self.signed(self.word(p)))
  for t in TYPES:
   off=p-t
   if off in (0x1359,0x135a,0x1351,0x121e):self.event(1,off,u.mem_read(p,1)[0])
   elif off==0x137c or 0xc8c<=off<=0xccc and off%4==0:self.event(1,off,self.signed(self.word(p)))
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  if a in RANGES:
   self.counts[hex(a)]+=1
   if a==0x594770:self.event(3,0,0);self.mutate(0)
   if a==0x5d4540:self.event(3,1,0)
  if any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()):return
  if a==self.type84:
   assert u.reg_read(UC_X86_REG_ECX)==ACTOR;self.event(3,2,0);self.counts['type84']+=1;self.mutate(1)
   sp=u.reg_read(UC_X86_REG_ESP);u.reg_write(UC_X86_REG_EAX,self.word(ACTOR+0x418));u.reg_write(UC_X86_REG_EIP,self.word(sp));u.reg_write(UC_X86_REG_ESP,sp+4);return
  raise AssertionError(('Uninspected Building frame instruction',hex(a)))
 def run(self,f):
  self.mode=f[0];self.mutated=False;self.trace=[];self.u.mem_write(BASE,b'\x5a'*SIZE);self.put(ACTOR,0x79cbbc);self.type84=self.word(0x79cbbc+0x84)
  self.put(ACTOR+0x418,TYPES[0]);self.put(ACTOR+0x42c,f[5]);self.put(ACTOR+0xe0,f[6]);self.put(ACTOR+0x4ec,f[7]);self.put(ACTOR+0x4f0,f[8]);self.put(ACTOR+0x564,f[9]);self.put(ACTOR+0x98,f[10]);self.put(ACTOR+0xa0,f[11]);self.put(ACTOR+0x6c,f[12]);self.put(0x839848,RULES)
  self.u.mem_write(RULES+0x1368,struct.pack('<QQ',f[27],f[28]))
  for id,t in enumerate(TYPES):
   for off,v in zip((0x1359,0x135a,0x1351,0x121e),f[1:5]):self.u.mem_write(t+off,bytes([v]))
   self.put(t+0xa0,100 if id else f[13]);self.put(t+0x137c,(f[14]+id)&0xffffffff)
   self.ints(t+0xc8c,[17,23,0] if id else [f[15],f[16],0])
   for i in range(5):self.ints(t+0xc98+i*12,[i*11,100+i,0] if id else [f[17+2*i],f[18+2*i],0])
  self.expected=bytearray(self.u.mem_read(BASE,SIZE));self.active=True
  try:self.checked_call(0x43be20,ecx=ACTOR,inputs=[*RANGES.items(),(0x79cbbc,0x1c0)])
  finally:self.active=False
  assert self.u.mem_read(BASE,SIZE)==self.expected,'Unrelated Building frame arena changed'
  self.trace.append('F');t=self.word(ACTOR+0x418)
  self.trace.extend(map(str,[self.signed(self.u.reg_read(UC_X86_REG_EAX)),TYPES.index(t),self.signed(self.word(ACTOR+0x42c)),self.signed(self.word(ACTOR+0xe0)),self.signed(self.word(ACTOR+0x6c)),self.signed(self.word(t+0x137c))]))
  return self.trace
