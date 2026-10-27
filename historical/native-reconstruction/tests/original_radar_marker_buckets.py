# SPDX-License-Identifier: GPL-3.0-or-later
"""Unmodified marker parents, stock vectors/kinds/rectangle/dirty/move children."""
import struct
from collections import Counter
from original_presentation import PresentationOracle,STOP
from verify_radar_marker_buckets import verify,RANGES,DATA,TABLE,POINT_TABLE
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EIP
BASE=0x3b00000;SIZE=0x30000;MAP=BASE;D=MAP+0x1258;ROOT=BASE+0x2000;BUCKETS=ROOT+0x100
ACTORS=BASE+0x4000;SURFACE=BASE+0x6000;OTHER=SURFACE+0x100;VT=BASE+0x6200;HOUSES=BASE+0x6400
BITMAP=BASE+0x7000;POOL=BASE+0x8000;DPOOL=BASE+0x18000;STRIDE=2048;DSTRIDE=1024
def signed(v):return (v+2**31)%2**32-2**31
def bucket(x,y):return (x-y*5)&255
def digest(data):
 h=14695981039346656037
 for b in data:h=((h^b)*1099511628211)&(2**64-1)
 return h
class RadarMarkerBucketsOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(BASE,SIZE);self.active=False;self.counts=Counter();self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.write)
 def va(self,a):return a
 def word(self,p):return struct.unpack('<I',self.u.mem_read(p,4))[0]
 def emit(self,*v):self.trace.extend(map(str,v))
 def actor(self,p):assert p in [ACTORS+i*0x800 for i in range(3)];return (p-ACTORS)//0x800
 def norm(self,p):return 101+self.actor(p) if p in [ACTORS+i*0x800 for i in range(3)] else p
 def identity(self,p,dirty=False):
  base,stride,slots=(DPOOL,DSTRIDE,self.dslots) if dirty else (POOL,STRIDE,self.slots)
  assert p==0 or base<=p<base+slots*stride and (p-base)%stride==0
  return 0 if not p else (p-base)//stride+1
 def supply(self,p,raw):
  self.u.mem_write(p,raw)
  if BASE<=p<p+len(raw)<=BASE+SIZE:self.expected[p-BASE:p-BASE+len(raw)]=raw
  elif p==0xa35db4:self.expectedHouse=struct.unpack('<I',raw)[0]
  else:raise AssertionError(('Unexpected marker supplied write',hex(p)))
 def create(self,dirty=False):
  slot=self.dslots if dirty else self.slots
  if dirty:
   self.dslots+=1;p=DPOOL+slot*DSTRIDE;raw=b''.join(struct.pack('<II',3000+slot*100+k,4000+slot*100+k) for k in range(128))
  else:
   self.slots+=1;p=POOL+slot*STRIDE;raw=b''.join(struct.pack('<4I',ACTORS+0x1000,1000+slot*100+k,2000+slot*100+k,0xdef000+slot*128+k) for k in range(128))
  if self.active:self.supply(p,raw)
  else:self.u.mem_write(p,raw)
  return p
 def ret(self,result=0):
  sp=self.u.reg_read(UC_X86_REG_ESP);self.u.reg_write(UC_X86_REG_EAX,result);self.u.reg_write(UC_X86_REG_EIP,self.word(sp));self.u.reg_write(UC_X86_REG_ESP,sp+4)
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  if a in self.pending:
   kind=self.pending.pop(a)
   if kind=='G' and self.f[16]==1:self.supply(MAP+0x1218,struct.pack('<I',OTHER))
   if kind=='G' and self.f[16]==3:self.supply(ACTORS+0x1b4,struct.pack('<I',HOUSES))
   if kind=='K' and self.f[16]==2:self.supply(0xa35db4,struct.pack('<I',HOUSES+0x100))
  sp=u.reg_read(UC_X86_REG_ESP);ecx=u.reg_read(UC_X86_REG_ECX)
  if a in (0x634e40,0x634bc0,0x634f50):self.vector=(ecx-BUCKETS)//24;assert 0<=self.vector<256
  elif a in (0x5b1b00,0x5b16e0):assert ecx==D;self.vector=-1
  if a==0x782017:
   dirty=self.vector==-1;size=self.word(sp+4);assert 0<size<=(1024 if dirty else 2048) and size%(8 if dirty else 16)==0
   fail=self.f[13 if dirty else 12];self.emit('a' if dirty else 'A',size,fail);self.counts['dirty_allocations' if dirty else 'marker_allocations']+=1
   self.ret(0 if fail else self.create(dirty));return
  if a==0x781d3b:
   dirty=self.vector==-1;self.emit('d' if dirty else 'D',self.identity(self.word(sp+4),dirty));self.counts['dirty_releases' if dirty else 'marker_releases']+=1;self.ret();return
  assert any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected bucket instruction',hex(a))
  if a in RANGES:self.counts[hex(a)]+=1
  if a==0x411290:
   assert ecx in (SURFACE,OTHER);self.emit('G',int(ecx==OTHER));self.pending[self.word(sp)]='G'
  elif a in (0x4112c0,0x4112d0):
   assert ecx in (SURFACE,OTHER);self.emit('W' if a==0x4112c0 else 'Y',int(ecx==OTHER),signed(self.word(ecx+(4 if a==0x4112c0 else 8))))
  elif a in (0x509800,0x453c40):self.emit('K',self.actor(ecx),6 if a==0x453c40 else 15);self.pending[self.word(sp)]='K'
  elif a==0x632620:
   point=self.word(sp+4);self.emit('Q',*struct.unpack('<ii',u.mem_read(point,8)))
 def write(self,u,access,p,n,value,_):
  if not self.active or not BASE<=p<BASE+SIZE:return
  value&=(1<<(8*n))-1
  if BUCKETS<=p and p+n<=BUCKETS+256*24:
   index,off=divmod(p-BUCKETS,24);assert (off,n) in ((4,4),(8,4),(12,1),(13,1),(16,4));self.emit('F',index,off,n,self.identity(value) if off==4 else value)
  elif D<=p and p+n<=D+24:
   off=p-D;assert (off,n) in ((4,4),(8,4),(12,1),(13,1),(16,4));self.emit('f',off,n,self.identity(value,True) if off==4 else value)
  elif POOL<=p and p+n<=POOL+self.slots*STRIDE:
   index,off=divmod(p-POOL,STRIDE);assert n==4;self.emit('P',index+1,off,self.norm(value))
  elif DPOOL<=p and p+n<=DPOOL+self.dslots*DSTRIDE:
   index,off=divmod(p-DPOOL,DSTRIDE);assert n==4;self.emit('p',index+1,off,n,value)
  elif BITMAP<=p and p+n<=BITMAP+1024:assert n==1;self.emit('b',p-BITMAP,value)
  elif p==MAP+0x14d5:assert n==1;self.emit('S',value)
  elif ACTORS<=p and p+n<=ACTORS+3*0x800:
   index,off=divmod(p-ACTORS,0x800);assert off in (0x1a0,0x1a4) and n==4;self.emit('O',index,off,value)
  else:raise AssertionError(('Unexpected marker arena store',hex(p),n))
  self.expected[p-BASE:p-BASE+n]=value.to_bytes(n,'little')
 def run(self,f):
  self.f=f;mode,x,y,w,h,count,capacity,growth,owns,valid,present,local,failed,dirtyFailed,actor,slot,mutation,repeats,requested=f
  u=self.u;u.mem_write(BASE,b'\xa5'*SIZE);self.slots=self.dslots=0;self.create();self.trace=[];self.pending={};self.vector=-1
  for i in range(256):
   for off,val in ((0,TABLE),(4,0),(8,0),(16,0),(20,10)):self.put(BUCKETS+i*24+off,val)
   u.mem_write(BUCKETS+i*24+12,b'\1\0')
  selected=BUCKETS+bucket(2,1)*24
  for off,val in ((4,POOL if present else 0),(8,capacity),(16,count),(20,growth)):self.put(selected+off,val)
  u.mem_write(selected+12,bytes([valid,owns]))
  for i in range(count):u.mem_write(POOL+i*16,struct.pack('<4I',ACTORS+(i%3)*0x800,2+i*5,1+i,0xabc000+i))
  for i in range(3):
   for off,val in ((0,0x79cbbc if i==2 else 0x7a3540),(0x1a0,91),(0x1a4,92),(0x1b4,HOUSES if local&(1<<i) else HOUSES+0x100)):self.put(ACTORS+i*0x800+off,val)
  for p,val in ((MAP+0x1218,SURFACE),(MAP+0x1254,ROOT),(ROOT,BUCKETS),(MAP+0x1270,BITMAP),(D,POINT_TABLE),(D+4,0),(D+8,0),(D+16,0),(D+20,10),(SURFACE,VT),(SURFACE+4,w),(SURFACE+8,h),(OTHER,VT),(OTHER+4,7),(OTHER+8,6),(VT+0x78,0x411290),(VT+0x7c,0x4112c0),(VT+0x80,0x4112d0)):self.put(p,val)
  u.mem_write(D+12,b'\1\0');u.mem_write(MAP+0x14d5,b'\0');u.mem_write(BITMAP,bytes(1024));self.put(0xa35db4,HOUSES);self.expectedHouse=HOUSES
  self.expected=bytearray(u.mem_read(BASE,SIZE));self.active=True
  inputs=[*RANGES.items(),*DATA.items(),(VT,0x84)]
  writes=[(BUCKETS,256*24),(D,24),(MAP+0x14d5,1),(POOL,STRIDE*16),(DPOOL,DSTRIDE*16),(BITMAP,1024),*[(ACTORS+i*0x800+0x1a0,8) for i in range(3)]]
  def call(root,args,owner=MAP):self.checked_call(root,args,owner,writes=writes,inputs=inputs)
  def insert(a):call(0x631910,[ACTORS+a*0x800,x,y])
  def remove(a):call(0x631af0,[ACTORS+a*0x800,x,y])
  target=ACTORS+actor*0x800;rx=x;ry=y
  if 0<=slot<count:target=ACTORS+(slot%3)*0x800;rx=2+slot*5;ry=1+slot
  try:
   for i in range(repeats):
    self.emit('I',i)
    if mode==0:insert(actor)
    elif mode==1:call(0x631af0,[target,rx,ry])
    elif mode==2:insert(0);insert(1);insert(0);remove(0);remove(0);insert(2);remove(1);remove(2)
    elif mode==3:call(0x634e40,[requested,0],selected);self.emit('T',u.reg_read(UC_X86_REG_EAX)&255)
    elif mode==4:call(0x634bc0,[],selected)
    else:
     #634F50 takes the same actor/x/y key, including a deliberately irrelevant trailer.
     key=BASE+0x1e000;self.supply(key,struct.pack('<4I',target,rx&0xffffffff,ry&0xffffffff,0x1234));call(0x634f50,[key],selected);self.emit('T',signed(u.reg_read(UC_X86_REG_EAX)))
  finally:self.active=False
  assert not self.pending and bytes(u.mem_read(BASE,SIZE))==self.expected and self.word(0xa35db4)==self.expectedHouse
  for i in range(256):
   p=BUCKETS+i*24
   if i==bucket(2,1) or self.word(p+4) or self.word(p+8) or self.word(p+16):self.emit('V',i,self.identity(self.word(p+4)),signed(self.word(p+8)),signed(self.word(p+16)),u.mem_read(p+12,1)[0],u.mem_read(p+13,1)[0])
  self.emit('R')
  for i in range(3):self.emit(signed(self.word(ACTORS+i*0x800+0x1a0)),signed(self.word(ACTORS+i*0x800+0x1a4)),int(self.word(ACTORS+i*0x800+0x1b4)!=HOUSES))
  self.emit(u.mem_read(MAP+0x14d5,1)[0],int(self.word(MAP+0x1218)==OTHER),int(self.word(0xa35db4)!=HOUSES),self.identity(self.word(D+4),True),signed(self.word(D+8)),signed(self.word(D+16)),u.mem_read(D+12,1)[0],u.mem_read(D+13,1)[0],digest(u.mem_read(BITMAP,1024)))
  self.emit('H',self.slots)
  for i in range(self.slots):
   words=struct.unpack('<512I',u.mem_read(POOL+i*STRIDE,STRIDE));self.emit(digest(struct.pack('<512I',*[self.norm(v) for v in words])))
  self.emit(self.dslots)
  for i in range(self.dslots):self.emit(digest(u.mem_read(DPOOL+i*DSTRIDE,DSTRIDE)))
  return self.trace
