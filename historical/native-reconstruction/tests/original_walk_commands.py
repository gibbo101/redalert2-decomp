# SPDX-License-Identifier: GPL-3.0-or-later
"""Unchanged complete Walk commands with actual Infantry guards/reset."""
import struct
from collections import Counter
from original_presentation import PresentationOracle,STOP
from verify_walk_commands import verify,RANGES,TABLES,SERVICES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EIP
ARENA=0x2a00000;SIZE=0x4000;ACTOR=ARENA;WALK=ARENA+0x1000;CELL=ARENA+0x2000
class WalkCommandHooks:
 def command_code(self,u,a,n):
  assert a in SERVICES or any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected Walk command instruction',hex(a))
  if a in RANGES:self.counts['command_'+hex(a)]+=1
  sp=u.reg_read(UC_X86_REG_ESP);ecx=u.reg_read(UC_X86_REG_ECX)
  if a in (0x6d8e80,0x6d6df0,0x6d6e00):
   assert ecx==self.command_actor;self.command_trace('g',{0x6d8e80:0x324,0x6d6df0:0x1bc,0x6d6e00:0x1c0}[a])
  elif a==0x548000:
   assert ecx==0x8324e0;point=struct.unpack('<3i',u.mem_read(self.word(sp+4),12));self.command_trace('B',*point)
   self.command_ret(4,self.command_lookup(point))
  elif a==0x6a29b0:assert ecx==60;self.command_trace('h',60)
  elif a==0x508750:assert ecx==self.command_actor;self.command_trace('X')
  elif a==0x504740:
   assert ecx==self.command_actor and struct.unpack('<3i',u.mem_read(sp+4,12))==(27,0,0)
   self.command_trace('N',27);self.command_animation();self.command_ret(12)
 def command_store(self,p,n,value):
  if self.command_walk+0x1c<=p<self.command_walk+0x37:
   assert n==(4 if p<self.command_walk+0x34 else 1);self.command_trace('L',p-self.command_walk,value&((1<<(8*n))-1))
  elif p==self.command_actor+0x5cc:
   assert n==1;self.command_trace('A',0x5cc,value&255)
 def command_trace(self,k,x=0,y=0,z=0):self.events.extend(map(str,(k,x,y,z)))
 def command_ret(self,n,value=0):
  sp=self.u.reg_read(UC_X86_REG_ESP);target=self.word(sp)
  self.u.reg_write(UC_X86_REG_EAX,value&0xffffffff);self.u.reg_write(UC_X86_REG_ESP,sp+4+n);self.u.reg_write(UC_X86_REG_EIP,target)
 def invoke_command(self,op,point,inputs,writes):
  assert op in (0,1,2);root=(0x71e020,0x71e110,0x71e1a0)[op]
  args=[self.command_walk+4,*point] if op!=1 else [self.command_walk+4]
  self.in_command=True
  try:PresentationOracle.checked_call(self,root,args,writes=writes,inputs=inputs)
  finally:self.in_command=False
  self.command_trace('R',op)
class WalkCommandsOracle(WalkCommandHooks,PresentationOracle):
 def va(self,a):return a
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(ARENA,SIZE)
  self.command_actor=ACTOR;self.command_walk=WALK;self.in_command=False;self.counts=Counter()
  self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.store)
 def word(self,p):return struct.unpack('<I',self.u.mem_read(p,4))[0]
 def code(self,u,a,n,ctx):
  if self.in_command and a!=STOP:self.command_code(u,a,n)
 def store(self,u,access,p,n,value,ctx):
  if self.in_command:self.command_store(p,n,value)
 def command_lookup(self,point):
  m=self.mask
  if m&1:
   for off,delta in ((0x1c,257),(0x24,7)):self.put(WALK+off,self.word(WALK+off)+delta)
  if m&2:self.put(CELL+0x140,self.word(CELL+0x140)^256)
  if m&4:self.u.mem_write(0xabe520,struct.pack('<d',1.25))
  if m&8:self.u.mem_write(WALK+0x34,b'\xad');self.u.mem_write(WALK+0x36,b'\xc5')
  return CELL
 def command_animation(self):
  if self.mask&16:
   for i,value in enumerate((7,9,11)):self.put(WALK+0x28+4*i,value)
   self.u.mem_write(WALK+0x34,b'\xff');self.u.mem_write(WALK+0x36,b'\x11');self.u.mem_write(ACTOR+0x5cc,b'\x80')
 def run_commands(self,v,ops):
  self.events=[];u=self.u;u.mem_write(ARENA,b'\xa5'*SIZE);self.mask=v[18]
  for p,value in ((ACTOR,0x7a3540),(WALK+4,0x7aead8),(WALK+0xc,ACTOR),(ACTOR+0x3fc,v[9]),(CELL+0x140,v[13])):self.put(p,value)
  for i,value in enumerate(v[:6]):self.put(WALK+0x1c+4*i,value)
  u.mem_write(WALK+0x34,bytes(v[6:9]));u.mem_write(ACTOR+0x204,bytes(v[10:12]));u.mem_write(ACTOR+0x5cc,bytes([v[12]]))
  u.mem_write(0xabe520,struct.pack('<Q',v[14]));u.mem_write(0xaf9060,struct.pack('<3I',*v[15:18]))
  writes=[(WALK+0x1c,27),(ACTOR+0x5cc,1),(CELL+0x140,4),(0xabe520,8)]
  inputs=[];cursor=ARENA
  for p,n in sorted(writes[:3]):
   if cursor<p:inputs.append((cursor,p-cursor))
   cursor=p+n
  inputs.append((cursor,ARENA+SIZE-cursor));inputs+=list(RANGES.items())+list(TABLES.items())+[(0xaf9060,12)]
  for op,point in ops:self.invoke_command(op,point,inputs,writes)
  s=lambda x:x if x<2**31 else x-2**32
  self.events+=['Z',*map(str,[*[s(self.word(WALK+0x1c+4*i)) for i in range(6)],*u.mem_read(WALK+0x34,3),s(self.word(ACTOR+0x3fc)),
   *u.mem_read(ACTOR+0x204,2),u.mem_read(ACTOR+0x5cc,1)[0],self.word(CELL+0x140),struct.unpack('<Q',u.mem_read(0xabe520,8))[0]])]
  return self.events
