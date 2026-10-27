# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete unchanged queued Process roots sharing the actual head/Cell arena."""
import struct
from original_walk_head import WalkHeadOracle,WALK
from original_infantry_subcell import ARENA,SIZE,ACTOR,HOUSE,CELLS,SCENARIO,STATE
from original_presentation import STOP
from verify_walk_queued import verify,RANGES,TABLES,SERVICES
from verify_walk_head import RANGES as HEAD
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP
def div256(n):return n//256 if n>=0 else -((-n)//256)
def identity(p):return (div256(p[0])^div256(p[1]))&1
class WalkQueuedOracle(WalkHeadOracle):
 def __init__(self,exe):
  self.queued_ready=False;super().__init__(exe);self.inspection=verify(exe.read_bytes());self.queued_ready=True
  self.active=True
  try:self.checked_call(0x4916d0,writes=[(0x851ac0,64)],inputs=list(RANGES.items())+list(TABLES.items()))
  finally:self.active=False
  assert self.ints(0x851ac0,16)==(0,-256,256,-256,256,0,256,256,0,256,-256,256,-256,0,-256,-256)
 def trace(self,c,x=0,y=0,z=0):self.event(c,x,y,z)
 def mutate(self):
  v=self.v;m=v[17]
  if m&1:
   for off,delta in ((0x88,257),(0x8c,-513),(0x90,7)):self.put(ACTOR+off,self.word(ACTOR+off)+delta)
  if m&2:self.u.mem_write(ACTOR+0x79,bytes([self.u.mem_read(ACTOR+0x79,1)[0]^128]))
  if m&4:
   for c in CELLS:self.u.mem_write(c+0x11b,bytes([(self.u.mem_read(c+0x11b,1)[0]+1)&255]))
  if m&8:
   for c in CELLS:self.put(c+0x140,self.word(c+0x140)^256)
  if m&16:self.put(ACTOR+0x4d0,7)
  if m&32:self.u.mem_write(ACTOR+0x7d,b'\0')
  if m&64:
   for c in CELLS:self.put(c+0x124,self.word(c+0x124)^0x1c);self.put(c+0x128,self.word(c+0x128)^0x1c)
  if m&128:self.put(ACTOR+0x98,-1);self.put(ACTOR+0xa0,8)
  if m&256:self.u.mem_write(WALK+0x1c,bytes(12))
 def code(self,u,a,n,_):
  if not self.queued_ready:return super().code(u,a,n,_)
  if not self.active or a==STOP:return
  assert a in SERVICES or any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected queued Walk instruction',hex(a))
  assert not (0x71e28a<=a<0x71e65f or 0x71e675<=a<0x71e8fc or 0x71e9fd<=a<0x71ef70),('Unjoined queued branch',hex(a))
  sp=u.reg_read(UC_X86_REG_ESP);ecx=u.reg_read(UC_X86_REG_ECX)
  if a==0x548000:
   assert ecx==0x8324e0;p=self.word(sp+4);point=self.ints(p,3);i=identity(point)
   self.event('N',i,self.tag(p),*point);self.lookups+=1;self.counts['coordinate_lookup']+=1
   if self.lookups==self.v[18]:self.mutate()
   self.ret(4,CELLS[i]);return
  if a==0x55a280:
   assert ecx==0x8324e0;p=self.word(sp+4);self.event('F',self.tag(p),*self.ints(p,3));self.ret(4,self.v[9]);return
  if a==0x548070:
   assert ecx==0x8324e0;p=self.word(sp+4);point=struct.unpack('<hh',u.mem_read(p,4));i=(point[0]^point[1])&1
   self.event('B',*point);self.ret(4,CELLS[i]);return
  if a==0x503190:
   target,direction,level,zero,one=self.ints(sp+4,5);assert ecx==ACTOR and target in CELLS and (zero,one)==(0,1)
   self.event('I',CELLS.index(target),direction,level,zero,one);self.counts['admission']+=1;self.ret(20,0);return
  if a==0x4c2e60:
   assert ecx==ACTOR;kind=self.ints(sp+4,1)[0];self.event('K',kind);self.ret(4,1);return
  if a==0x508980:assert ecx==ACTOR;self.trace('S');self.counts['speed']+=1;self.ret(0,self.v[8]);return
  if a==0x47bb30:assert ecx in CELLS;self.event('Dirt',CELLS.index(ecx));self.ret(0,0);return
  if a==0x500aa0:assert ecx==ACTOR and self.ints(sp+4,1)==(2,);self.event('J',2);self.ret(4,0);return
  if a==0x501ce0:assert ecx==ACTOR and self.ints(sp+4,2)==(0,1);self.event('G',0,1);self.ret(8,0);return
  if a==0x508750:assert ecx==ACTOR;self.event('X');self.ret(0,0);return
  if a==0x5d4e40:assert ecx==ACTOR;self.trace('C')
  elif a==0x4c2df0:
   assert ecx==ACTOR;value=struct.unpack('<d',u.mem_read(sp+4,8))[0];assert value in (0.,1.);self.trace('V',int(value))
  elif a==0x71e170:assert self.word(sp+4)==WALK+4;self.trace('T',struct.unpack('<H',u.mem_read(sp+8,2))[0])
  elif a==0x41b320:assert ecx==ACTOR;self.trace('Q')
  elif a==0x4ca6f0:assert ecx==ACTOR;self.trace('P')
  # Reuse the complete head oracle's actual mission, occupation, selector and
  # RNG audits. Map/floor services above retain one shared logical Cell identity.
  if any(lo<=a and a+n<=lo+size for lo,size in HEAD.items()):return super().code(u,a,n,_)
  if a in RANGES:self.counts[hex(a)]+=1
 def store(self,u,access,p,n,value,_):
  if not self.active:return
  if not self.queued_ready:return super().store(u,access,p,n,value,_)
  widths={0x74:1,0x79:1,0x88:4,0x8c:4,0x90:4,0x468:4,0x46c:4,0x57a:1,0x57b:1,0x5a1:1,0x450:4}
  if p-ACTOR in widths or ACTOR+0x4d0<=p<ACTOR+0x530:
   assert n==widths.get(p-ACTOR,4);self.trace('A',p-ACTOR,value&((1<<(n*8))-1));return
  if WALK+0x1c<=p<WALK+0x37:
   assert n==(4 if p<WALK+0x34 else 1);self.trace('L',p-WALK,value&((1<<(n*8))-1));return
  super().store(u,access,p,n,value,_)
 def run_queued(self,v):
  self.v=v;u=self.u;u.mem_write(ARENA,b'\xa5'*SIZE);self.events=[]
  for off,value in ((ACTOR,0x7a3540),(ACTOR+0x1b4,HOUSE),(ACTOR+0x494,0),(ACTOR+0x564,WALK+4),
   (WALK+4,0x7aead8),(WALK+0xc,ACTOR),(ACTOR+0x3fc,v[16]),(ACTOR+0x98,v[32]),(ACTOR+0xa0,v[33]),
   (HOUSE+0x30,v[31]),(0xa3d290,SCENARIO),(0xa40d2c,0),(0xa72f30,v[10]),(0xaf9098,v[11]),(0xa41120,v[12]),(0x850c30,v[10])):self.put(off,value)
  for off,values in ((ACTOR+0x88,v[:3]),(WALK+0x1c,(*v[3:6],0,0,0)),(ACTOR+0x2e0,(0x1234,0x2345,-1,0x13579bdf,7,256)),(ACTOR+0x4d0,(v[6],*range(101,124)))):
   for i,value in enumerate(values):self.put(off+4*i,value)
  for off,value in ((0x74,128),(0x79,v[13]),(0x7d,v[14]),(0x76,0),(0x7a,0),(0x574,255),(0x57a,173),(0x57b,197),(0x5a1,255)):u.mem_write(ACTOR+off,bytes([value]))
  self.put(ACTOR+0x450,0x12345678);u.mem_write(ACTOR+0x468,struct.pack('<d',float(v[34])))
  u.mem_write(WALK+0x34,bytes([v[15],173,197]))
  for p in (0xaf9060,0x850c00,0x865f20):u.mem_write(p,bytes(12))
  seed=0x71e220;table=[]
  for _ in range(250):seed=(seed*1664525+1013904223)&0xffffffff;table.append(seed)
  u.mem_write(STATE,b'\0\xa5\xa5\xa5'+struct.pack('<ii250I',0,103,*table))
  for i,c in enumerate(CELLS):
   for off,value in zip((0x124,0x128,0x140,0x54,0x58),v[21+5*i:26+5*i]):self.put(c+off,value)
   self.put(c+0x44,-1);u.mem_write(c+0x11b,bytes([v[19+i]&255]))
  writes=[(ACTOR+off,n) for off,n in ((0x74,1),(0x79,1),(0x7d,1),(0x88,12),(0x98,4),(0xa0,4),(0x2e0,20),(0x450,4),(0x468,8),(0x4d0,96),(0x57a,2),(0x5a1,1))]+[(WALK+0x1c,27),(STATE+4,1008)]+[(c+off,n) for c in CELLS for off,n in ((0x54,8),(0x11b,1),(0x124,8),(0x140,4))]
  inputs=[];cursor=ARENA
  for lo,n in sorted(writes):
   if cursor<lo:inputs.append((cursor,lo-cursor))
   cursor=lo+n
  inputs.append((cursor,ARENA+SIZE-cursor));inputs+=list(RANGES.items())+list(TABLES.items())
  inputs += [(0x851ac0,64),(0x850e50,60),(0xaf9060,12),(0x850c00,12),(0x865f20,12),(0xa3d290,4),(0xa72f30,4),(0xaf9098,4),(0xa41120,4),(0x850c30,4)]
  for tick in range(v[7]):
   self.put(0xa40d2c,tick);self.lookups=0;self.active=True
   try:self.checked_call(0x71dff0,[WALK+4],writes=writes,inputs=inputs+[(0xa40d2c,4)])
   finally:self.active=False
   self.event('R',u.reg_read(UC_X86_REG_EAX)&255,'P',*self.ints(ACTOR+0x88,3),*self.ints(WALK+0x1c,6),*u.mem_read(WALK+0x34,3),
    *[u.mem_read(ACTOR+off,1)[0] for off in (0x74,0x79,0x7d,0x57a,0x57b,0x5a1)],struct.unpack('<Q',u.mem_read(ACTOR+0x468,8))[0],
    *[struct.unpack('<H',u.mem_read(ACTOR+off,2))[0] for off in (0x2e0,0x2e4)],self.ints(ACTOR+0x2e8,1)[0],self.ints(ACTOR+0x2f0,1)[0],*self.ints(ACTOR+0x4d0,24))
  self.event('Z')
  for c in CELLS:self.event(self.word(c+0x124),self.word(c+0x128),self.word(c+0x140),*self.ints(c+0x54,2),struct.unpack('<b',u.mem_read(c+0x11b,1))[0])
  self.event('rng',*self.ints(STATE+4,2),*struct.unpack('<250I',u.mem_read(STATE+12,1000)))
  return self.events
