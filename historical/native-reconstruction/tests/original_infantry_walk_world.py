# SPDX-License-Identifier: GPL-3.0-or-later
"""Unmodified complete Infantry/Walk journeys with real shared map and membership."""
import hashlib,struct
from collections import Counter
from original_presentation import PresentationOracle,STOP,STACK
from verify_infantry_walk_world import verify,RANGES,TABLES,SERVICES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EIP
BASE=0x2800000;SIZE=0x20000;ACTOR=BASE;WALK=BASE+0x1000;TYPE=BASE+0x3000;HOUSE=BASE+0x5000
COUNTRY=BASE+0xb000;RULES=BASE+0xc000;SCENARIO=BASE+0xe000;STATE=SCENARIO+0x218
TACTICAL=BASE+0x10000;TARGET=BASE+0x12000;CELLS=[BASE+0x14000+i*0x400 for i in range(25)]+[0xa6f9f8]
SLOTS=BASE+SIZE;MAP=0x8324e0;PLANES=0x7d27e8
FOUNDATION={0xa72f0c:(0,1),0xa72f18:(4,4),0xa411a0:(8,1),0xa4117c:(12,4),0xa41180:(16,4)}
OFFSETS=((0,-1),(1,-1),(1,0),(1,1),(0,1),(-1,1),(-1,0),(-1,-1))
def pack(*v):return struct.pack('<'+'I'*len(v),*[x&0xffffffff for x in v])
class InfantryWalkWorldOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True)
  self.u.mem_map(BASE,SIZE+0x100000);self.u.mem_map(0x3c7000,0x1000)
  self.active=False;self.counts=Counter();self.events=[]
  self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.store)
  for root,writes in ((0x483390,[(0x850e50,60)]),(0x4916d0,[(0x851ac0,64)]),(0x491620,[(0x851a70,32)])):
   self.active=True
   try:self.checked_call(root,writes=writes,inputs=list(RANGES.items())+[(a,n) for a,n in TABLES.items() if a!=PLANES])
   finally:self.active=False
 def va(self,a):return a
 def word(self,p):return struct.unpack('<I',self.u.mem_read(p,4))[0]
 def ints(self,p,n):return struct.unpack('<'+'i'*n,self.u.mem_read(p,n*4))
 def byte(self,p):return self.u.mem_read(p,1)[0]
 def event(self,*v):self.events.extend(map(str,v))
 def ret(self,n,value=0):
  sp=self.u.reg_read(UC_X86_REG_ESP);self.u.reg_write(UC_X86_REG_EAX,value&0xffffffff)
  target=self.word(sp);self.u.reg_write(UC_X86_REG_ESP,sp+4+n);self.u.reg_write(UC_X86_REG_EIP,target)
 def cell(self,p):return CELLS.index(p)
 def store(self,u,access,p,n,value,ctx):
  if not self.active:return
  value&=(1<<(8*n))-1
  actor4=(0x30,0x88,0x8c,0x90,0x450,0x468,0x46c,0x490,0x494,0x530,0x534,0x538,0x53c,0x558,0x55c,0x560,0x5ac)
  actor1=(0x74,0x75,0x79,0x57a,0x57b,0x598,0x5a1,0x5cc)
  if p-ACTOR in actor4 or ACTOR+0x4d0<=p<ACTOR+0x530:
   off=p-ACTOR;assert n==4
   if off in (0x30,0x494):assert value in (0,ACTOR,TARGET);value=int(bool(value))
   self.event('W','A',0,off,n,value)
  elif p-ACTOR in actor1:
   assert n==1;self.event('W','A',0,p-ACTOR,n,value)
  elif p==WALK+0x14 or WALK+0x1c<=p<WALK+0x37:
   assert n==(1 if p>=WALK+0x34 else 4);self.event('W','L',0,p-WALK,n,value)
  elif p in FOUNDATION:
   off,width=FOUNDATION[p];assert n==width;self.event('W','G',0,off,n,value)
  elif p==0xa6eb14:assert n==4;self.event('W','G',1,0,n,value)
  elif p==TACTICAL+0xd7d:assert n==1;self.event('W','G',2,0,n,value)
  else:
   for i,c in enumerate(CELLS):
    if p-c in (0x24,0xe4,0xe8,0x124,0x128,0x54,0x58):
     off=p-c;assert n==(1 if off in (0x124,0x128) else 4)
     if off in (0xe4,0xe8):assert value in (0,ACTOR);value=int(bool(value))
     self.event('W','C',i,off,n,value);break
 def code(self,u,a,n,ctx):
  if not self.active or a==STOP:return
  assert a in SERVICES or any(p<=a and a+n<=p+size for p,size in RANGES.items()),('Uninspected Infantry world instruction',hex(a))
  if a in RANGES:self.counts[hex(a)]+=1
  # These are the existing bounded kernels' explicit entered-child exclusions.
  assert not (0x71e332<=a<0x71e63f or 0x71e675<=a<0x71e8fc or 0x71e9fd<=a<0x71ef70 or
   0x71f69f<=a<0x71f6f5 or 0x71f706<=a<0x71f752 or 0x71f760<=a<0x71f787 or
   0x47656e<=a<0x4765b9 or 0x476ce8<=a<0x478646 or 0x508b00<=a<0x508ce5),('Unsupported joined child',hex(a))
  sp=u.reg_read(UC_X86_REG_ESP);ecx=u.reg_read(UC_X86_REG_ECX)
  if a==0x71e220:u.mem_write(sp-8,pack(0x12345678)) # supplied original uninitialized local
  elif a==0x4c8030:u.mem_write(sp-0x18,pack(0x12345689))
  if a not in SERVICES:return
  self.counts['service_'+hex(a)]+=1
  if a==0x568140:assert ecx==MAP;self.ret(4,1)
  elif a in (0x5683c0,0x6c2440,0x504740):raise AssertionError(('Unexpected supplied service',hex(a)))
  elif a==0x472540:self.event('r',self.cell(ecx),self.ints(sp+4,1)[0]);self.ret(4)
  elif a==0x47bb30:self.event('d',self.cell(ecx));self.ret(0)
  elif a==0x500aa0:
   assert ecx==ACTOR and self.word(sp+4)==2;self.event('n',0,2)
   if self.v[8]:u.mem_write(ACTOR+{1:0x7a,2:0x7d,3:0x76}[self.v[8]],bytes([0 if self.v[8]==2 else 1]))
   self.ret(4)
  elif a==0x78298a:assert self.word(sp+4) in (0x5d44f0,0x50a060);self.ret(0)
  elif a==0x410290:
   assert ecx==TARGET and self.word(sp+8)==ACTOR;out=self.word(sp+4);u.mem_write(out,pack(*self.destination));self.ret(8,out)
  elif a==0x4c3000:
   assert ecx==ACTOR;point,zero,one=self.ints(sp+4,3);assert zero==one==0
   x,y=struct.unpack('<hh',pack(point));self.event('f',0,x,y,zero,one)
   for i in range(self.v[2]):u.mem_write(ACTOR+0x4d0+4*i,pack(self.v[0]));self.event('W','A',0,0x4d0+4*i,4,self.v[0])
   i=self.v[2];u.mem_write(ACTOR+0x4d0+4*i,pack(-1));self.event('W','A',0,0x4d0+4*i,4,0xffffffff);self.ret(12,1)
  elif a in (0x3c7594,0x3c757c):
   p=self.word(sp+4);assert p==WALK+0x14;v=self.word(p)+(1 if a==0x3c7594 else -1);u.mem_write(p,pack(v));self.event('W','L',0,0x14,4,v);self.ret(4,v)
 def execute(self,root,args=(),ecx=0):
  self.active=True
  try:self.checked_call(root,args,ecx,writes=self.writes,inputs=self.inputs)
  finally:self.active=False
 def run(self,v,planes):
  self.v=v;self.events=[];u=self.u;u.mem_write(BASE,b'\xa5'*(SIZE+0x100000));u.mem_write(SLOTS,bytes(0x100000))
  for p,n in ((ACTOR,0x600),(WALK,0x80),(TYPE,0xe00),(HOUSE,0x6000),(RULES,0x2000),(TACTICAL,0x1000)):u.mem_write(p,bytes(n))
  for i,c in enumerate(CELLS):
   u.mem_write(c,bytes(0x148));x,y=(49+i%5,70+i//5) if i<25 else (-7,5)
   self.put(c+0x24,(x&65535)|((y&65535)<<16));self.put(c+0x44,-1);self.put(c+0x54,-1);self.put(c+0x58,-1)
   self.put(c+0x124,0xaabbcc00);self.put(c+0x128,0x11223300);u.mem_write(c+0x116,struct.pack('<h',-1))
   if i<25:u.mem_write(c+0x11b,bytes([v[4]&255]));self.put(c+0x140,v[5]);self.put(SLOTS+(y*512+x)*4,c)
  p=(51*256+v[6],72*256+v[7],104*v[4]+(416 if v[5] else 0));dx,dy=OFFSETS[v[0]];self.destination=(p[0]+dx*256*v[2],p[1]+dy*256*v[2],p[2])
  for off,values in ((ACTOR+0x88,p),(ACTOR+0x2e0,(0x1234,0x2345,-1,0x13579bdf,7,256)),(ACTOR+0x4d0,(-1,*range(101,124))),(ACTOR+0x530,(-1,0,0)),(ACTOR+0x558,(31,37,41))):u.mem_write(off,pack(*values))
  for a,value in ((ACTOR,0x7a3540),(ACTOR+0x1b4,HOUSE),(ACTOR+0x5a8,TYPE),(ACTOR+0x564,WALK+4),(ACTOR+0x98,2),(ACTOR+0xa0,-1),
   (ACTOR+0x450,0x12345678),(ACTOR+0x53c,19),(ACTOR+0x490,19),(WALK,0x7aeba0),(WALK+4,0x7aead8),(WALK+0xc,ACTOR),(WALK+0x14,3),(WALK+0x18,0x7aeab4),
   (TYPE,0x7a3a78),(TYPE+0x5a0,v[1]),(TYPE+0x598,17),(HOUSE+0x34,COUNTRY),(TARGET,0x79db04),
   (MAP+0x138,SLOTS),(MAP+0x13c,262144),(MAP+0xc,2),(0x83996c,TACTICAL),(0xa3d290,SCENARIO),(0x839848,RULES),(RULES+0x13d0,8),
   (0x850c40,104),(0xa72f30,416),(0x850c30,416),(0xaf9098,104),(0xa41120,128),(0xad057c,128),(0xa3d298,0),(0xa40774,0),(0xa40d2c,0),(0xa6eb14,7),(0x8661cc,0),(0x8661d8,0)):self.put(a,value)
  # Session0 selects either human134/control135. Both proof owners are explicit.
  for a,value in ((ACTOR+0x79,int(bool(v[5]))),(ACTOR+0x7d,1),(ACTOR+0x574,255),(ACTOR+0x57a,173),(ACTOR+0x57b,197),(ACTOR+0x5a1,255),(ACTOR+0x5a0,1),(TYPE+0x205,1),(HOUSE+0x134,1),(MAP+0x1154,255)):u.mem_write(a,bytes([value]))
  for a,value in ((ACTOR+0x468,.375),(ACTOR+0x470,1.),(RULES+0x598,1.),(RULES+0x13c8,.01),(0xabe520,1.)):u.mem_write(a,struct.pack('<d',value))
  u.mem_write(COUNTRY+0x128,struct.pack('<f',1.));u.mem_write(0x850ea0,struct.pack('<108f',*[1.]*108))
  for a in (0x850c00,0xaf9060,0x865f20):u.mem_write(a,bytes(12))
  for a,(off,n) in FOUNDATION.items():u.mem_write(a,bytes(n))
  u.mem_write(0x850bb8,b'\0');u.mem_write(0x850ba8,bytes(8));u.mem_write(0x850bd0,bytes(8));u.mem_write(PLANES,struct.pack('<100Q',*planes))
  seed=0x71e220;table=[]
  for _ in range(250):seed=(seed*1664525+1013904223)&0xffffffff;table.append(seed)
  u.mem_write(STATE,b'\0\xa5\xa5\xa5'+pack(0,103,*table))
  self.writes=[(ACTOR+off,n) for off,n in ((0x30,4),(0x74,2),(0x76,1),(0x79,2),(0x7d,1),(0x88,12),(0x2e0,20),(0x450,4),(0x468,8),(0x490,8),(0x4d0,96),(0x530,16),(0x558,12),(0x57a,2),(0x598,1),(0x5a1,1),(0x5ac,4),(0x5cc,1))]
  self.writes += [(WALK+0x14,4),(WALK+0x1c,27),(STATE+4,1008),(TACTICAL+0xd7d,1),*[(a,n) for a,(_,n) in FOUNDATION.items()],(0xa6eb14,4),(0x850bb8,1),(0x850ba8,8),(0x850bd0,8),(PLANES,800)]
  self.writes += [(c+off,n) for c in CELLS for off,n in ((0x24,4),(0x54,8),(0xe4,8),(0x124,1),(0x128,1))]
  self.inputs=[];cursor=BASE
  for lo,n in sorted(self.writes):
   if not BASE<=lo<BASE+SIZE:continue
   if cursor<lo:self.inputs.append((cursor,lo-cursor))
   cursor=max(cursor,lo+n)
  if cursor<BASE+SIZE:self.inputs.append((cursor,BASE+SIZE-cursor))
  self.inputs += [(SLOTS,0x100000),*RANGES.items(),*[(a,n) for a,n in TABLES.items() if a!=PLANES],(0x850e50,60),(0x851ac0,64),(0x851a70,32),
   (MAP+0x138,8),(MAP+0xc,4),(MAP+0x1154,1),(0xa3d290,4),(0x839848,4),(0x83996c,4),(0xa3d298,4),(0xa40774,4),(0x850c40,4),(0xa72f30,4),(0x850c30,4),(0xaf9098,4),(0xa41120,4),(0xabe520,8),(0x850ea0,432),(0x8661cc,16)]
  self.execute(0x4c2e60,[1],ACTOR);u.mem_write(TARGET+4,pack(*p));self.execute(0x508410,[TARGET+4],ACTOR)
  self.execute(0x501ce0,[TARGET,1],ACTOR)
  for tick in range(v[3]):
   self.put(0xa40d2c,tick)
   if tick==v[9]:self.execute(0x501ce0,[0,1],ACTOR)
   self.execute(0x71dff0,[WALK+4]);self.event('P',u.reg_read(UC_X86_REG_EAX)&255,*self.ints(ACTOR+0x88,3),*self.ints(WALK+0x1c,6),
    *u.mem_read(WALK+0x34,3),*[self.byte(ACTOR+off) for off in (0x74,0x75,0x79,0x7d,0x76,0x7a,0x57a,0x57b,0x5a1)],
    struct.unpack('<Q',u.mem_read(ACTOR+0x468,8))[0],*[struct.unpack('<H',u.mem_read(ACTOR+off,2))[0] for off in (0x2e0,0x2e4)],
    self.ints(ACTOR+0x2e8,1)[0],self.ints(ACTOR+0x2f0,1)[0],int(bool(self.word(ACTOR+0x30))))
  self.event('Z',self.word(ACTOR+0x490),int(bool(self.word(ACTOR+0x494))),self.byte(ACTOR+0x598),self.byte(ACTOR+0x5cc),self.word(WALK+0x14),self.word(0xa6eb14),
   *self.ints(ACTOR+0x53c,1),*self.ints(ACTOR+0x5ac,1),*struct.unpack('<hh',u.mem_read(ACTOR+0x450,4)),self.byte(TACTICAL+0xd7d),*self.ints(ACTOR+0x530,3),*self.ints(ACTOR+0x558,3),*self.ints(ACTOR+0x4d0,24))
  for c in CELLS:self.event(int(bool(self.word(c+0xe4))),int(bool(self.word(c+0xe8))),self.word(c+0x124),self.word(c+0x128),*self.ints(c+0x54,2))
  state=bytes(u.mem_read(0x850bb8,1))+bytes(u.mem_read(0x850ba8,8))+bytes(u.mem_read(0x850bd0,8))+bytes(u.mem_read(PLANES,800))+bytes(u.mem_read(CELLS[-1]+0x24,4))
  self.event(self.byte(0xa72f0c),self.byte(0xa411a0),*struct.unpack('<hh',u.mem_read(0xa72f18,4)),*struct.unpack('<4h',u.mem_read(0xa4117c,8)),hashlib.sha256(state).hexdigest())
  self.event('rng',*self.ints(STATE+4,2),*struct.unpack('<250I',u.mem_read(STATE+12,1000)));return self.events
