# SPDX-License-Identifier: GPL-3.0-or-later
"""Unmodified complete layer roots and nested actual coordinate/floor/map queries."""
import struct
from collections import Counter
from original_presentation import PresentationOracle,STOP,STACK
from verify_foot_layer import verify,RANGES,TABLES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_EIP,UC_X86_REG_ESP
ARENA=0x2800000;SIZE=0x10000;ACTOR=ARENA+0x1000;DRIVE=ARENA+0x3000
CELLS=ARENA+0x4000;POOL=ARENA+0x7000;ENTRIES=ARENA+0x8000
SLOTS=0x2900000;FALLBACK=0xa6f9f8;PLANES=0x7d27e8;MAP=0x8324e0
def signed(v):return (v+0x80000000)%0x100000000-0x80000000
def pack(*v):return struct.pack('<'+'I'*len(v),*[n&0xffffffff for n in v])
class FootLayerOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True)
  self.u.mem_map(ARENA,SIZE);self.u.mem_map(SLOTS,0x100000)
  self.active=False;self.counts=Counter();self.instructions=set();self.writes=Counter()
  self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.store)
  self.checked_call(0x49f600,writes=[(0x852998,12)],inputs=[*RANGES.items(),*TABLES.items()])
  self.checked_call(0x4c2870,writes=[(0x865f20,12)],inputs=[*RANGES.items(),*TABLES.items()])
  assert bytes(self.u.mem_read(0x852998,12))==bytes(self.u.mem_read(0x865f20,12))==bytes(12)
 def va(self,a):return a
 def word(self,p):return int.from_bytes(self.u.mem_read(p,4),'little')
 def coord(self,p):return struct.unpack('<3i',self.u.mem_read(p,12))
 def byte(self,p):return self.u.mem_read(p,1)[0]
 def event(self,*v):self.events.extend(map(str,v))
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  assert any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected layer instruction',hex(a))
  self.instructions.add(a)
  if a in RANGES:self.counts[hex(a)]+=1
  sp=u.reg_read(UC_X86_REG_ESP)
  if a in (0x5d52ff,0x5d535d,0x5d539f):self.event('B',self.byte(ACTOR+0x79))
  elif a==0x4ca6f0:
   assert u.reg_read(UC_X86_REG_ECX)==ACTOR and self.word(sp+8)==self.action[1]&0xffffffff
   self.event('C',self.action[1]);self.counts['index.'+str(self.index)]+=1
  elif a==0x49fdb0:
   assert self.word(sp+4)==DRIVE+4;self.event('H')
   self.counts['head.'+str(self.coord(DRIVE+0x40)!= (0,0,0))]+=1
  elif a==0x5d4e40:assert u.reg_read(UC_X86_REG_ECX)==ACTOR;self.event('O')
  elif a==0x5d530d:self.event('P',*self.coord(u.reg_read(UC_X86_REG_EAX)))
  elif a==0x55a280:
   self.query=self.coord(self.word(sp+4));self.event('F',*self.query)
  elif a==0x4706c0:
   self.counts['ramp.'+str(self.byte(u.reg_read(UC_X86_REG_ECX)+0x11c))]+=1
  elif a in (0x5d5330,0x5d535b):
   self.event('V',signed(u.reg_read(UC_X86_REG_EAX)))
   if a==0x5d5330:
    if self.action[5]>=0:
     # Explicit diagnostic boundary mutation, not an original instruction/effect.
     u.mem_write(ACTOR+0x79,bytes([self.action[5]]));self.expected[0x1079]=self.action[5]
     self.event('X',self.action[5]);self.counts['diagnostic_bridge_mutation']+=1
    self.event('A',*self.coord(ACTOR+0x88))
  elif a in (0x5d5364,0x5d539a):self.event('T',signed(self.word(0xa72f40)))
  elif a==0x548000:self.query=self.coord(self.word(sp+4));self.event('M',*self.query)
  elif a==0x5d5383:self.event('m',self.word(u.reg_read(UC_X86_REG_EAX)+0x140))
  if a in (0x5d5391,0x5d53b2,0x5d53bd):self.counts['return.'+hex(a)]+=1
 def store(self,u,access,p,n,v,_):
  if not self.active:return
  a=u.reg_read(UC_X86_REG_EIP);value=v&((1<<(8*n))-1)
  if p==FALLBACK+0x24:
   assert (a,n) in ((0x548059,4),(0x55a2e3,4))
   x,y=self.query[:2];want=(int(x/256)&65535)|((int(y/256)&65535)<<16)
   assert value==want;self.event('W',value)
  elif p in (0x850bb8,0x850ba8,0x850bac,0x850bd0,0x850bd4) or PLANES<=p and p+n<=PLANES+800:
   assert 0x4706c0<=a<0x470e7b and n in (1,4,8)
  elif ARENA<=p and p+n<=ARENA+SIZE:raise AssertionError(('Unexpected layer arena store',hex(a),hex(p),n))
  self.writes[hex(a)]+=1
 def run(self,c):
  u=self.u;u.mem_write(ARENA,b'\xa5'*SIZE);u.mem_write(SLOTS,bytes(0x100000));self.events=[];self.index=c['index']
  self.put(ACTOR,0x7addf8);self.put(ACTOR+0x564,DRIVE+4);u.mem_write(ACTOR+0x574,bytes([c['index']&255]));u.mem_write(ACTOR+0x88,pack(*c['position']))
  self.put(DRIVE+4,0x7a04cc);self.put(DRIVE+12,ACTOR);u.mem_write(DRIVE+0x40,pack(*c['head']))
  self.put(0x8661cc,POOL)
  for i in range(128):
   self.put(POOL+4*i,ENTRIES+0x40*i);u.mem_write(ENTRIES+0x40*i+0x28,struct.pack('<2h',c['poolx'],c['pooly']))
  for i,(slot,level,ramp,flags) in enumerate(c['cells']):
   p=CELLS+0x200*i;self.put(SLOTS+4*slot,p);u.mem_write(p+0x11b,bytes([level&255,ramp]));self.put(p+0x140,flags)
  u.mem_write(FALLBACK,b'\xa5'*0x148);u.mem_write(FALLBACK+0x24,struct.pack('<2h',-7,5));u.mem_write(FALLBACK+0x11b,bytes([c['flevel']&255,c['framp']]));self.put(FALLBACK+0x140,c['fflags'])
  self.put(MAP+0x138,SLOTS);self.put(MAP+0x13c,262144)
  u.mem_write(0x850bb8,b'\0');u.mem_write(0x850ba8,bytes(8));u.mem_write(0x850bd0,bytes(8));u.mem_write(PLANES,struct.pack('<100d',1.,*([0.]*99)))
  for self.action in c['actions']:
   mode,flag,bridge,height,threshold,mutation=self.action
   u.mem_write(ACTOR+0x79,bytes([bridge]));self.put(0x850c40,height);self.put(0xa72f40,threshold)
   self.expected=bytearray(u.mem_read(ARENA,SIZE));old=bytes(u.mem_read(FALLBACK,0x148));self.active=True
   try:self.checked_call(0x4cc4b0 if mode else 0x5d52f0,[flag],ACTOR,
    writes=[(0x850bb8,1),(0x850ba8,8),(0x850bd0,8),(PLANES,800),(FALLBACK+0x24,4)],
    inputs=[*RANGES.items(),*TABLES.items(),(SLOTS,0x100000),(MAP+0x138,8),(0x850c40,4),(0xa72f40,4),(0x8661cc,4),(0x852998,12),(0x865f20,12)])
   finally:self.active=False
   result=u.reg_read(UC_X86_REG_EAX)&255;self.event('R',result);self.counts['result.'+str(result)]+=1
   assert bytes(u.mem_read(ARENA,SIZE))==bytes(self.expected),'Whole layer arena changed'
   current=bytearray(u.mem_read(FALLBACK,0x148));current[0x24:0x28]=old[0x24:0x28];assert bytes(current)==old
  self.event('state',self.byte(ACTOR+0x79),*struct.unpack('<2h',u.mem_read(FALLBACK+0x24,4)),self.byte(0x850bb8),*struct.unpack('<Q',u.mem_read(0x850ba8,8)),*struct.unpack('<Q',u.mem_read(0x850bd0,8)),*struct.unpack('<100Q',u.mem_read(PLANES,800)))
  return self.events
