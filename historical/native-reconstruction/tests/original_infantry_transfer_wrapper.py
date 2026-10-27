# SPDX-License-Identifier: GPL-3.0-or-later
"""Unchanged wrapper/query/relative-height/Cell getters; supplied base/floor probes."""
from collections import Counter
import struct
from original_presentation import PresentationOracle,STOP
from verify_infantry_transfer_wrapper import verify,RANGES,SERVICES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EIP
BASE=0x6100000;SIZE=0x10000;ACTOR=BASE+0x1000;OUT=BASE+0x2000;NEXT=BASE+0x3000
LEVEL=0xa72f40;BRIDGE=0xa72f30
class InfantryTransferWrapperOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True)
  self.u.mem_map(BASE,SIZE);self.active=False;self.counts=Counter()
  self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.write)
 def va(self,a):return a
 def word(self,a):return int.from_bytes(self.u.mem_read(a,4),'little')
 def event(self,*v):self.trace.extend(map(str,v))
 def change(self,a,v,n=4):
  raw=(v&((1<<(8*n))-1)).to_bytes(n,'little');self.u.mem_write(a,raw)
  if BASE<=a<a+n<=BASE+SIZE:self.expected[a-BASE:a-BASE+n]=raw
 def mutate(self,mode):
  if not mode:return
  self.event('D',mode)
  if mode in (1,7):self.change(ACTOR+0x90,-123456789)
  if mode in (2,7):self.change(ACTOR+0x79,0 if self.f[2] else 255,1)
  if mode in (3,7):self.change(BRIDGE,-2147483648)
  if mode in (4,7):self.change(LEVEL,-2147483648)
  if mode in (5,7,8):self.change(ACTOR+0x88,-257);self.change(ACTOR+0x8c,2147483647)
  if mode in (6,7,8):self.change(ACTOR+0x74,0,1)
 def ret(self,v=0,argc=0):
  sp=self.u.reg_read(UC_X86_REG_ESP);self.u.reg_write(UC_X86_REG_EAX,v&0xffffffff)
  self.u.reg_write(UC_X86_REG_EIP,self.word(sp));self.u.reg_write(UC_X86_REG_ESP,sp+4+4*argc)
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  assert a in SERVICES or any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected wrapper instruction',hex(a))
  if a in RANGES:self.counts[hex(a)]+=1
  sp=u.reg_read(UC_X86_REG_ESP);ecx=u.reg_read(UC_X86_REG_ECX)
  if a==0x6cd940:
   assert ecx==ACTOR and self.word(sp+4)==NEXT and self.word(sp+8)==1
   self.event('B',1)
   if self.f[10]==8:self.mutate(8)
   self.ret(self.f[9],2)
  elif a==0x5d4810:assert ecx==ACTOR;self.event('H')
  elif a==0x55a280:
   assert ecx==0x8324e0
   point=struct.unpack('<3i',u.mem_read(self.word(sp+4),12));assert point==tuple(self.f[3:6])
   self.event('P',*point)
   if self.f[10]!=8:self.mutate(self.f[10])
   self.ret(self.f[6],1)
  elif a==0x41b320:assert ecx==ACTOR;self.event('C')
 def write(self,u,access,a,n,v,_):
  if not self.active or not BASE<=a<a+n<=BASE+SIZE:return
  assert n==4 and a in (ACTOR+0x454,OUT),('Unexpected wrapper arena store',hex(u.reg_read(UC_X86_REG_EIP)),hex(a),n)
  self.expected[a-BASE:a-BASE+n]=(v&0xffffffff).to_bytes(n,'little')
  if a==ACTOR+0x454:self.event('W',v&0xffffffff)
 def run(self,f):
  self.f=f;u=self.u;u.mem_write(BASE,b'\xa5'*SIZE);self.put(ACTOR,0x7a3540)
  for off,v in zip((0x88,0x8c,0x90),f[3:6]):self.put(ACTOR+off,v)
  u.mem_write(ACTOR+0x74,bytes([f[1]]));u.mem_write(ACTOR+0x79,bytes([f[2]]));self.put(ACTOR+0x454,0x0059003f)
  self.put(LEVEL,f[7]);self.put(BRIDGE,f[8]);self.trace=[];self.expected=bytearray(u.mem_read(BASE,SIZE));self.active=True
  a,args={0:(0x4cce70,[]),1:(0x5d4810,[]),2:(0x4ca7d0,[NEXT,-77]),3:(0x41b320,[OUT])}[f[0]]
  try:self.checked_call(a,args,ACTOR,writes=[(ACTOR+0x454,4),(OUT,4)],inputs=[*RANGES.items(),(0x7a3540,0x37c)])
  finally:self.active=False
  assert bytes(u.mem_read(BASE,SIZE))==self.expected,'Unrelated wrapper arena changed'
  assert self.word(LEVEL)==(((-2147483648) if f[10] in (4,7) and 'P' in self.trace else f[7])&0xffffffff)
  assert self.word(BRIDGE)==(((-2147483648) if f[10] in (3,7) and 'P' in self.trace else f[8])&0xffffffff)
  result=self.word(OUT) if f[0]==3 else u.reg_read(UC_X86_REG_EAX)&(0xffffffff if f[0]==1 else 255)
  if f[0]==3:assert u.reg_read(UC_X86_REG_EAX)==OUT
  return self.trace+['F',str(result),str(self.word(ACTOR+0x454)),*[str(self.word(ACTOR+off)) for off in (0x88,0x8c,0x90)],str(u.mem_read(ACTOR+0x74,1)[0]),str(u.mem_read(ACTOR+0x79,1)[0]),str(self.word(LEVEL)),str(self.word(BRIDGE))]
