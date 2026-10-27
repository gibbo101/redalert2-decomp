# SPDX-License-Identifier: GPL-3.0-or-later
"""Unmodified complete destination roots in a bounded ordinary Cell profile."""
import struct
from collections import Counter
from original_presentation import PresentationOracle,STOP,STACK
from verify_unit_destination import verify,RANGES,TABLES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_EIP,UC_X86_REG_ECX,UC_X86_REG_ESP
ARENA=0x2800000;SIZE=0x10000;ACTOR=ARENA+0x1000;TYPE=ARENA+0x3000
DRIVE=ARENA+0x4000;CELLS=ARENA+0x5000;RULES=ARENA+0x6000;BUFFER=ARENA+0x8000
SLOTS=0x2900000;FALLBACK=0xa6f9f8;PLANES=0x7d27e8
INC=0x3c7594;DEC=0x3c757c;DISPOSE=0x781d3b
def signed(v):return (v+0x80000000)%0x100000000-0x80000000
def pack(*v):return struct.pack('<'+'I'*len(v),*[n&0xffffffff for n in v])
class UnitDestinationOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True)
  self.u.mem_map(ARENA,SIZE);self.u.mem_map(SLOTS,0x100000);self.u.mem_map(0x3c7000,0x1000)
  self.active=False;self.counts=Counter();self.instructions=set();self.writes=Counter()
  self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.store)
 def va(self,a):return a
 def word(self,p):return int.from_bytes(self.u.mem_read(p,4),'little')
 def coord(self,p):return struct.unpack('<3i',self.u.mem_read(p,12))
 def byte(self,p):return self.u.mem_read(p,1)[0]
 def event(self,*v):self.events.extend(map(str,v))
 def target(self,i):return CELLS+(i-1)*0x200 if i else 0
 def target_id(self,p):
  assert p in (0,CELLS,CELLS+0x200);return 0 if not p else 1+(p-CELLS)//0x200
 def ret(self,n,value=0):
  sp=self.u.reg_read(UC_X86_REG_ESP);target=self.word(sp)
  self.u.reg_write(UC_X86_REG_EAX,value&0xffffffff);self.u.reg_write(UC_X86_REG_ESP,sp+4+n);self.u.reg_write(UC_X86_REG_EIP,target)
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  sp=u.reg_read(UC_X86_REG_ESP)
  if a in (INC,DEC):
   p=self.word(sp+4);assert p==DRIVE+0x14
   value=(self.word(p)+(1 if a==INC else -1))&0xffffffff;assert 0<value<0x80000000
   u.mem_write(p,pack(value));self.expected[p-ARENA:p-ARENA+4]=pack(value)
   self.event('I',0,0,value);self.counts['atomic_inc' if a==INC else 'atomic_dec']+=1;self.ret(4,value);return
  if a==DISPOSE:
   assert self.word(sp+4)==BUFFER and self.word(ACTOR+0x488)==0
   self.event('H',0,0,1);self.counts['supplied_disposal']+=1;self.ret(0);return
  assert any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected destination instruction',hex(a))
  self.instructions.add(a)
  if a in RANGES:self.counts[hex(a)]+=1
  if a==0x4c8030:
   self.current_target=self.word(sp+4);self.current_padding=self.action[4]
   # Caller scratch supplied at child entry; actual output Y can overwrite it.
   u.mem_write(sp-0x18,pack(self.current_padding))
  elif a==0x594770:self.event('M',0,0,signed(self.word(ACTOR+0xa0) if self.word(ACTOR+0x98)==0xffffffff else self.word(ACTOR+0x98)))
  elif a in (0x47cf80,0x70a2d0):self.event('k',0,0,11 if a==0x47cf80 else 1)
  elif a==0x4a47f0:self.event('G',0,0,0)
  elif a==0x4a4c40:self.event('r',0,0,0)
  elif a in (0x49fca7,0x49fcf9,0x49fd03):
   value=u.reg_read(UC_X86_REG_EAX)&255;self.event('v',0,0,value);self.counts['IsMoving.'+str(value)]+=1
  elif a==0x53d230:self.event('P',0,0,self.byte(DRIVE+0x10))
  elif a in (0x49fe30,0x49fef0):self.event('m',0,0,a)
  elif a==0x705020:self.event('T',0,0,0)
  elif a in (0x49fe41,0x49fe54,0x49fe67,0x49fe76):
   off={0x49fe41:0x324,0x49fe54:0x328,0x49fe67:0x1bc,0x49fe76:0x1c0}[a];value=u.reg_read(UC_X86_REG_EAX)&255
   self.event('b',off,0,value);self.counts['guard.'+hex(off)+'.'+str(value)]+=1
  elif a==0x4706c0:self.counts['floor.ramp.'+str(self.byte(u.reg_read(UC_X86_REG_ECX)+0x11c))]+=1
  elif a==0x410290:assert self.word(sp+8)==ACTOR
  elif a==0x4102ba:
   point=self.coord(u.reg_read(UC_X86_REG_EAX));self.current_padding=point[1]
   self.observed_point=point
   self.event('Q',*point)
  elif a==0x548000:self.event('L',*self.coord(self.word(sp+4)))
 def store(self,u,access,p,n,v,_):
  if not self.active:return
  a=u.reg_read(UC_X86_REG_EIP);value=v&((1<<(8*n))-1)
  if p==0xa6eb14:
   assert n==4 and a in (0x53d25f,0x53d280)
   assert value==(self.word(p)+(1 if a==0x53d25f else -1))&0xffffffff
   self.event('C',0,0,value)
  elif p==FALLBACK+0x24:
   assert n==4 and 0x548000<=a<0x548068
   self.event('f',0,0,value)
  if p in (0x850bb8,0x850ba8,0x850bac,0x850bd0,0x850bd4) or PLANES<=p and p+n<=PLANES+800:
   assert 0x4706c0<=a<0x470e7b and n in (1,4,8)
  if ARENA<=p and p+n<=ARENA+SIZE:
   fields={0x705491:(0x190,1,0),0x70581c:(0x4d0,4,0xffffffff),
    0x4cde39:(0x488,4,0),0x4cde4e:(0x47c,4,0),0x4cde51:(0x485,1,0),0x4cde54:(0x480,4,0),
    0x4c8041:(0x490,4,0),0x4c8047:(0x494,4,self.current_target),
    0x4c8119:(0x598,1,0),0x4c81c4:(0x494,4,0),0x4c81ca:(0x5a1,1,0),
    0x4c81ea:(0x558,4,self.action[3]&0xffffffff),0x4c81f0:(0x55c,4,self.current_padding&0xffffffff),
    0x4c81f3:(0x560,4,self.delay&0xffffffff),0x4c8207:(0x530,4,self.action[3]&0xffffffff),
    0x4c820a:(0x534,4,self.current_padding&0xffffffff),0x4c820d:(0x538,4,0)}
   if a in fields:
    off,size,want=fields[a];assert (p,n,value)==(ACTOR+off,size,want),(hex(a),hex(p),n,value,fields[a])
    observed=self.target_id(value) if off==0x494 else value
    self.event('a',off,n,observed)
   elif a in (0x49fe89,0x49fe8c,0x49fe8f,0x49ffa0,0x49ffa7,0x49ffb0):
    off={0x49fe89:0x34,0x49fe8c:0x38,0x49fe8f:0x3c,0x49ffa0:0x34,0x49ffa7:0x38,0x49ffb0:0x3c}[a]
    assert (p,n)==(DRIVE+off,4)
    if a>=0x49ffa0:assert value==0
    else:assert value==self.observed_point[(off-0x34)//4]&0xffffffff
    self.event('d',off,n,value)
   elif a==0x49ff94:
    old=struct.unpack('<d',u.mem_read(DRIVE+0x50,8))[0];want=min(old,0.30000001192092896)
    assert (p,n,value)==(DRIVE+0x50,8,struct.unpack('<Q',struct.pack('<d',want))[0])
    self.event('d',0x50,8,signed64(value))
   else:raise AssertionError(('Unexpected destination arena store',hex(a),hex(p),n))
   self.expected[p-ARENA:p-ARENA+n]=int(value).to_bytes(n,'little');self.writes[hex(a)]+=1
 def run(self,c):
  u=self.u;u.mem_write(ARENA,b'\xa5'*SIZE);u.mem_write(SLOTS,bytes(0x100000));self.events=[];self.delay=c['delay']
  for off,value in ((0,0x7addf8),(0x5ac,TYPE),(0x564,DRIVE+4),(0xcc,ARENA+0x9000),(0xd0,0),
   (0x98,c['mission']),(0xa0,c['queued']),(0x490,c['field490']),(0x494,self.target(c['initial_target'])),
   (0x25c,0),(0x5c0,c['field5c0']),(0x3fc,c['field3fc']),(0x58c,c['guard_start']),(0x594,c['guard_remaining']),
   (0x478,0x7a177c),(0x47c,BUFFER if c['buffer'] else 0),(0x480,c['capacity']),(0x488,c['count'])):self.put(ACTOR+off,value)
  self.put(ARENA+0x9000,0)
  for off,key in ((0x190,'forced'),(0x598,'suspended'),(0x5a1,'reached'),(0x485,'owned'),(0x5c8,'field5c8')):
   u.mem_write(ACTOR+off,bytes([c[key]]))
  for address,key in ((0x6d6df0,'disabled1bc'),(0x6d6e00,'disabled1c0')):
   raw=bytes(u.mem_read(address,7));off=int.from_bytes(raw[2:6],'little');u.mem_write(ACTOR+off,bytes([c[key]]))
  u.mem_write(ACTOR+0x88,pack(*c['position']));u.mem_write(ACTOR+0x4d0,pack(*c['queue']))
  for off in (0x530,0x558):u.mem_write(ACTOR+off,pack(123,-91,17))
  for off in (0xb1a,0xaf5,0xae0,0xaa0):u.mem_write(TYPE+off,b'\0')
  self.put(TYPE+0x3bc,0)
  for off,value in ((0,0x7a0594),(4,0x7a04cc),(0x18,0x7a04a8),(0x14,c['references']),(0xc,ACTOR)):self.put(DRIVE+off,value)
  u.mem_write(DRIVE+0x10,bytes([c['powered']]))
  u.mem_write(DRIVE+0x34,pack(*c['destination']));u.mem_write(DRIVE+0x40,pack(*c['head']));u.mem_write(DRIVE+0x50,struct.pack('<Q',c['percentage_bits']))
  self.put(DRIVE+0x4c,33);self.put(DRIVE+0x58,2);self.put(DRIVE+0x5c,9);u.mem_write(DRIVE+0x63,b'\x01')
  for i,row in enumerate(c['cells']):
   x,y,level,ramp,flags,present=row;p=CELLS+i*0x200
   self.put(p,0x79db04);u.mem_write(p+0x24,struct.pack('<2h',x,y));u.mem_write(p+0x11b,bytes([level&255,ramp]));self.put(p+0x140,flags)
   index=int((y*256+128)/256)*512+int((x*256+128)/256)
   if present and 0<=index<262144:self.put(SLOTS+4*index,p)
  u.mem_write(FALLBACK,b'\xa5'*0x148);u.mem_write(FALLBACK+0x24,struct.pack('<2h',-7,5));self.put(FALLBACK+0x140,c['fallback_flags'])
  self.put(0x8324e0+0x138,SLOTS);self.put(0x8324e0+0x13c,262144)
  self.put(0xa6eb14,c['global_references']);self.put(0x839848,RULES);self.put(RULES+0x13d0,c['delay'])
  u.mem_write(0x852998,bytes(12));self.put(0x850c40,c['height']);u.mem_write(0x850bb8,b'\0');u.mem_write(0x850ba8,bytes(8));u.mem_write(0x850bd0,bytes(8));u.mem_write(PLANES,struct.pack('<100d',1.,*([0.]*99)))
  self.expected=bytearray(u.mem_read(ARENA,SIZE));self.active=True
  try:
   for self.action in c['actions']:
    mode,target,flag,tick,padding=self.action;self.put(0xa40d2c,tick);self.current_target=self.target(target);self.current_padding=padding
    self.checked_call(0x7053f0 if mode else 0x4c8030,[self.current_target,flag],ACTOR,
     writes=[(ARENA,SIZE),(0xa6eb14,4),(FALLBACK+0x24,4),(0x850bb8,1),(0x850ba8,8),(0x850bd0,8),(PLANES,800)],
     inputs=[*RANGES.items(),*TABLES.items(),(SLOTS,0x100000),(0x8324e0+0x138,8),(0x852998,12),(0x839848,4),(0x850c40,4),(0xa40d2c,4)])
    assert bytes(u.mem_read(ARENA,SIZE))==bytes(self.expected),'Whole destination arena differs'
  finally:self.active=False
  self.event('state',self.byte(ACTOR+0x190),signed(self.word(ACTOR+0x490)),self.target_id(self.word(ACTOR+0x494)),self.byte(ACTOR+0x598),self.byte(ACTOR+0x5a1),
   int(self.word(ACTOR+0x47c)!=0),signed(self.word(ACTOR+0x480)),signed(self.word(ACTOR+0x488)),self.byte(ACTOR+0x485),
   *self.coord(DRIVE+0x34),struct.unpack('<Q',u.mem_read(DRIVE+0x50,8))[0],self.word(0xa6eb14),self.word(DRIVE+0x14),
   *struct.unpack('<24i',u.mem_read(ACTOR+0x4d0,96)),*self.coord(ACTOR+0x530),*self.coord(ACTOR+0x558),
   *struct.unpack('<2h',u.mem_read(FALLBACK+0x24,4)),self.byte(0x850bb8),*struct.unpack('<Q',u.mem_read(0x850ba8,8)),*struct.unpack('<Q',u.mem_read(0x850bd0,8)),*struct.unpack('<100Q',u.mem_read(PLANES,800)))
  self.event('retained',*self.coord(DRIVE+0x40),signed(self.word(DRIVE+0x58)),signed(self.word(DRIVE+0x5c)),signed(self.word(DRIVE+0x4c)),self.byte(DRIVE+0x63),*self.coord(ACTOR+0x88))
  return self.events
def signed64(v):return (v+0x8000000000000000)%0x10000000000000000-0x8000000000000000
