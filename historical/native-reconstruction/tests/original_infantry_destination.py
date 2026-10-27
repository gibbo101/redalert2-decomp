# SPDX-License-Identifier: GPL-3.0-or-later
"""Unmodified complete Infantry/Foot destination roots with actual Walk children."""
import struct
from collections import Counter
from original_presentation import PresentationOracle,STOP
from original_walk_commands import WalkCommandHooks
from verify_walk_commands import RANGES as COMMANDS
from verify_infantry_destination import verify,RANGES,TABLES,SERVICES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EIP
ARENA=0x2b00000;SIZE=0x6000;ACTOR=ARENA;WALK=ARENA+0x1000;TYPE=ARENA+0x2000
HOUSE=ARENA+0x3000;TARGET=ARENA+0x4000;CELL=ARENA+0x5000;RULES=0x2c00000
def pack(*x):return struct.pack('<'+'I'*len(x),*[v&0xffffffff for v in x])
def signed(v):return (v+2**31)%2**32-2**31
class InfantryDestinationOracle(WalkCommandHooks,PresentationOracle):
 def va(self,a):return a
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True)
  self.u.mem_map(ARENA,SIZE);self.u.mem_map(RULES,0x2000);self.u.mem_map(0x3c7000,0x1000)
  self.command_actor=ACTOR;self.command_walk=WALK;self.active=False;self.counts=Counter();self.writes=Counter();self.instructions=set()
  self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.store)
 def word(self,p):return struct.unpack('<I',self.u.mem_read(p,4))[0]
 def byte(self,p):return self.u.mem_read(p,1)[0]
 def target(self,i):return TARGET+(i-1)*0x100 if i else 0
 def target_id(self,p):
  assert p in (0,TARGET,TARGET+0x100);return 0 if not p else (p-TARGET)//0x100+1
 def set(self,p,b):
  self.u.mem_write(p,b)
  if ARENA<=p and p+len(b)<=ARENA+SIZE:self.expected[p-ARENA:p-ARENA+len(b)]=b
 def bump(self,p,n):self.set(p,pack(self.word(p)+n))
 def event(self,k,x=0,y=0,z=0):
  self.events.extend(map(str,(k,x,y,z)))
  # Injected diagnostics at actual consumer boundaries, not game observations.
  if k=='G':
   if self.mask&1:self.set(ACTOR+0x494,pack(self.target(2)))
   if self.mask&2:self.set(ACTOR+0x598,bytes([self.byte(ACTOR+0x598)^128]))
  if k=='a' and x==0x558 and self.mask&8:
   self.bump(0xa40d2c,13);self.bump(RULES+0x13d0,17)
 def command_trace(self,k,x=0,y=0,z=0):self.event(k,x,y,z)
 def command_lookup(self,point):
  if self.mask&16:self.bump(WALK+0x24,7)
  return CELL
 def animation(self,k):
  self.event('N',k)
  if self.mask&32:
   for off,value in ((0x5c3,128),(0xc00,255)):
    base=ACTOR if off==0x5c3 else TYPE;self.set(base+off,bytes([self.byte(base+off)^value]))
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  assert a in SERVICES or any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected Infantry destination instruction',hex(a))
  self.instructions.add(a)
  if a in RANGES:self.counts[hex(a)]+=1
  sp=u.reg_read(UC_X86_REG_ESP);ecx=u.reg_read(UC_X86_REG_ECX)
  if a in (0x3c7594,0x3c757c):
   assert self.word(sp+4)==WALK+0x14;value=self.word(WALK+0x14)+(1 if a==0x3c7594 else -1)
   assert 0<value<0x80000000;self.set(WALK+0x14,pack(value));self.event('I',0,0,value);self.command_ret(4,value);return
  if a==0x4c8030:
   self.current_padding=self.action[3];u.mem_write(sp-0x18,pack(self.current_padding))
  elif a==0x4f52f0:
   assert ecx==HOUSE;human=self.byte(HOUSE+0x134)
   value=human if self.word(0xa3d298) else int(bool(human or self.byte(HOUSE+0x135)))
   self.event('H',0,0,value)
  elif a==0x71dea0:self.event('v',0,0,self.byte(WALK+0x34))
  elif a==0x594770:self.event('M',0,0,signed(self.word(ACTOR+(0xa0 if self.word(ACTOR+0x98)==0xffffffff else 0x98))))
  elif a==0x509800:self.event('k',0,0,15)
  elif a==0x71f900:self.event('G')
  elif a==0x410290:
   assert self.word(sp+8)==ACTOR;value=self.points[self.target_id(ecx)-1]
   self.current_padding=value[1];self.event('Q',*value)
   if self.mask&4:self.bump(0xa40d2c,7);self.bump(RULES+0x13d0,9)
   out=self.word(sp+4);u.mem_write(out,pack(*value));self.command_ret(8,out)
  elif a==0x504740:
   assert ecx==ACTOR;args=struct.unpack('<3i',u.mem_read(sp+4,12));assert args in ((7,0,0),(27,0,0));self.animation(args[0]);self.command_ret(12)
  elif a in SERVICES or any(lo<=a and a+n<=lo+size for lo,size in COMMANDS.items()):self.command_code(u,a,n)
 def store(self,u,access,p,n,value,_):
  if not self.active:return
  a=u.reg_read(UC_X86_REG_EIP);value&=(1<<(n*8))-1
  if p==0xa6eb14:
   assert n==4 and a in (0x53d25f,0x53d280);self.event('C',0,0,value);return
  if not ARENA<=p or p+n>ARENA+SIZE:return
  if ACTOR<=p<ACTOR+0x1000:
   off=p-ACTOR;assert (off,n) in ((0x490,4),(0x494,4),(0x598,1),(0x5a1,1),(0x4d0,4),(0x5cc,1),*[(x,4) for x in (0x530,0x534,0x538,0x558,0x55c,0x560)]),(hex(a),hex(p),n)
   if off==0x5cc:self.command_store(p,n,value)
   else:self.event('a',off,n,self.target_id(value) if off==0x494 else value)
  elif WALK<=p<WALK+0x1000:
   assert (p-WALK,n) in (*[(x,4) for x in (0x1c,0x20,0x24)],(0x34,1),(0x36,1)),(hex(a),hex(p),n)
   self.command_store(p,n,value)
  else:raise AssertionError(('Unexpected destination owner write',hex(a),hex(p),n))
  self.expected[p-ARENA:p-ARENA+n]=value.to_bytes(n,'little');self.writes[hex(a)]+=1
 def run(self,c):
  u=self.u;u.mem_write(ARENA,b'\xa5'*SIZE);self.events=[];self.mask=c['mask'];self.points=c['points']
  for p,value in ((ACTOR,0x7a3540),(ACTOR+0x1b4,HOUSE),(ACTOR+0x5a8,TYPE),(ACTOR+0x5ac,c['state']),
   (ACTOR+0x564,WALK+4),(ACTOR+0x98,c['mission']),(ACTOR+0xa0,c['queued']),(ACTOR+0x490,c['field']),
   (ACTOR+0x494,self.target(c['initial'])),(ACTOR+0x25c,0),(ACTOR+0x3fc,c['frozen']),
   (WALK,0x7aeba0),(WALK+4,0x7aead8),(WALK+0x18,0x7aeab4),(WALK+0xc,ACTOR),(WALK+0x14,c['refs']),
   (TARGET,0x79db04),(TARGET+0x100,0x79db04),(CELL+0x140,c['flags'])):self.put(p,value)
  for base,off,key in ((ACTOR,0x598,'suspended'),(ACTOR,0x5a1,'reached'),(ACTOR,0x5c3,'flag'),(ACTOR,0x5cc,'reset'),
   (ACTOR,0x204,'disabled'),(ACTOR,0x205,'disabled2'),(TYPE,0xb44,'jump'),(TYPE,0xc0d,'c0d'),(TYPE,0xc00,'c00'),
   (HOUSE,0x134,'human'),(HOUSE,0x135,'human2')):u.mem_write(base+off,bytes([c[key]]))
  for off,key in ((0x1c,'destination'),(0x28,'head')):u.mem_write(WALK+off,pack(*c[key]))
  u.mem_write(WALK+0x34,bytes([c[k] for k in ('moving','processing','really')]))
  for off,key in ((0x530,'retry'),(0x558,'wait'),(0x4d0,'route')):u.mem_write(ACTOR+off,pack(*c[key]))
  self.put(0xa6eb14,c['globalrefs']);self.put(0xa3d298,c['session']);self.put(0xa40d2c,c['tick']);self.put(0x839848,RULES);self.put(RULES+0x13d0,c['delay'])
  u.mem_write(0xabe520,struct.pack('<Q',c['scale']));u.mem_write(0x852998,bytes(12));u.mem_write(0xaf9060,bytes(12))
  self.expected=bytearray(u.mem_read(ARENA,SIZE));self.active=True
  try:
   for self.action in c['actions']:
    mode,target,flag,padding=self.action
    self.checked_call(0x501ce0 if mode else 0x4c8030,[self.target(target),flag],ACTOR,
     writes=[(ARENA,SIZE),(0xa6eb14,4),(0xa40d2c,4),(RULES+0x13d0,4)],
     inputs=[*RANGES.items(),*TABLES.items(),(0x852998,12),(0xaf9060,12),(0xa3d298,4),(0x839848,4),(0xabe520,8)])
    assert bytes(u.mem_read(ARENA,SIZE))==bytes(self.expected),'Whole Infantry destination arena differs';self.event('R',mode)
  finally:self.active=False
  self.events+=['Z',*map(str,[signed(self.word(ACTOR+0x490)),self.target_id(self.word(ACTOR+0x494)),self.byte(ACTOR+0x598),self.byte(ACTOR+0x5a1),
   self.word(0xa6eb14),self.word(WALK+0x14),self.byte(ACTOR+0x5c3),self.byte(TYPE+0xc00),self.byte(ACTOR+0x5cc),signed(self.word(0xa40d2c)),signed(self.word(RULES+0x13d0)),
   *struct.unpack('<24i',u.mem_read(ACTOR+0x4d0,96)),*struct.unpack('<3i',u.mem_read(ACTOR+0x530,12)),*struct.unpack('<3i',u.mem_read(ACTOR+0x558,12)),
   *struct.unpack('<6i',u.mem_read(WALK+0x1c,24)),*u.mem_read(WALK+0x34,3),self.word(CELL+0x140),struct.unpack('<Q',u.mem_read(0xabe520,8))[0]])]
  return self.events
