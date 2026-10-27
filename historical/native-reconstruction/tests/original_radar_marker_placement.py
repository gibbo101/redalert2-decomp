# SPDX-License-Identifier: GPL-3.0-or-later
"""Unmodified631BA0/632620, stock getters/resize/FTOL; supplied heap only."""
import struct
from collections import Counter
from original_presentation import PresentationOracle,STOP
from verify_radar_marker_placement import verify,RANGES,DATA,TABLE
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EIP
BASE=0x3b00000;SIZE=0x20000;MAP=BASE;V=MAP+0x1258;POINT=BASE+0x2000;OUT=POINT+16
SURFACE=BASE+0x3000;OTHER=SURFACE+0x100;VT=BASE+0x4000;BITMAP=BASE+0x5000;POOL=BASE+0x6000;STRIDE=512
def signed(v):return (v+2**31)%2**32-2**31
def digest(data):
 h=14695981039346656037
 for b in data:h=((h^b)*1099511628211)&(2**64-1)
 return h
class RadarMarkerPlacementOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(BASE,SIZE);self.active=False;self.counts=Counter();self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.write)
 def va(self,a):return a
 def word(self,p):return struct.unpack('<I',self.u.mem_read(p,4))[0]
 def emit(self,*v):self.trace.extend(map(str,v))
 def supply(self,p,raw):
  self.u.mem_write(p,raw);self.expected[p-BASE:p-BASE+len(raw)]=raw
 def ret(self,result=0):
  sp=self.u.reg_read(UC_X86_REG_ESP);self.u.reg_write(UC_X86_REG_EAX,result);self.u.reg_write(UC_X86_REG_EIP,self.word(sp));self.u.reg_write(UC_X86_REG_ESP,sp+4)
 def identity(self,p):
  assert p==0 or POOL<=p<POOL+self.slots*STRIDE and (p-POOL)%STRIDE==0
  return 0 if not p else (p-POOL)//STRIDE+1
 def create(self):
  slot=self.slots;self.slots+=1;p=POOL+slot*STRIDE
  raw=b''.join(struct.pack('<II',1000+slot*100+k,2000+slot*100+k) for k in range(64))
  if self.active:self.supply(p,raw)
  else:self.u.mem_write(p,raw)
  return p
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  if a in self.pending:
   self.pending.remove(a);self.queries+=1
   if self.queries==self.f[18]:
    self.supply(MAP+0x1218,struct.pack('<I',OTHER));self.supply(POINT,struct.pack('<ii',2,1))
  if a in (0x4112c0,0x4112d0):
   owner=u.reg_read(UC_X86_REG_ECX);assert owner in (SURFACE,OTHER)
   self.emit('W' if a==0x4112c0 else 'H',int(owner==OTHER),signed(self.word(owner+(4 if a==0x4112c0 else 8))))
   self.pending.add(self.word(u.reg_read(UC_X86_REG_ESP)))
  if a==0x782017:
   size=self.word(u.reg_read(UC_X86_REG_ESP)+4);assert 0<size<=512 and size%8==0
   self.emit('A',size,self.f[14]);self.counts['allocations']+=1;self.ret(0 if self.f[14] else self.create());return
  if a==0x781d3b:self.emit('D',self.identity(self.word(u.reg_read(UC_X86_REG_ESP)+4)));self.counts['releases']+=1;self.ret();return
  assert any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected marker instruction',hex(a))
  if a in RANGES:self.counts[hex(a)]+=1
 def write(self,u,access,p,n,value,_):
  if not self.active or not BASE<=p<BASE+SIZE:return
  value&=(1<<(8*n))-1
  if V<=p and p+n<=V+24:
   off=p-V;assert (off,n) in ((4,4),(8,4),(12,1),(13,1),(16,4));self.emit('F',off,n,self.identity(value) if off==4 else value)
  elif BITMAP<=p and p+n<=BITMAP+1024:assert n==1;self.emit('B',p-BITMAP,value)
  elif p==MAP+0x14d5:assert n==1;self.emit('S',value)
  elif POOL<=p and p+n<=POOL+self.slots*STRIDE:
   slot,off=divmod(p-POOL,STRIDE);assert n==4;self.emit('P',slot+1,off,n,value)
  else:assert self.f[0]==0 and POINT<=p and p+n<=OUT+8 and n==4,('Unexpected marker store',hex(p),n)
  self.expected[p-BASE:p-BASE+n]=value.to_bytes(n,'little')
 def run(self,f):
  self.f=f;mode,bits,x,y,ox,oy,w,h,clamp,count,capacity,growth,owns,present,failed,repeats,step,alias,mutation=f
  u=self.u;u.mem_write(BASE,b'\xa5'*SIZE);self.slots=0;self.create();self.trace=[];self.queries=0;self.pending=set()
  for p,val in ((MAP+0x1484,bits),(MAP+0x148c,ox),(MAP+0x1494,oy),(MAP+0x14a0,w),(MAP+0x14a4,h),(MAP+0x1218,SURFACE),(MAP+0x1270,BITMAP+256),(V,TABLE),(V+4,POOL if present else 0),(V+8,capacity),(V+16,count),(V+20,growth),(SURFACE,VT),(SURFACE+4,w),(SURFACE+8,h),(OTHER,VT),(OTHER+4,7),(OTHER+8,6),(VT+0x7c,0x4112c0),(VT+0x80,0x4112d0)):self.put(p,val)
  u.mem_write(V+12,bytes([1,owns]));u.mem_write(MAP+0x14d5,b'\0');u.mem_write(POINT,struct.pack('<ii',x,y));u.mem_write(OUT,struct.pack('<ii',19,23));u.mem_write(BITMAP,bytes(1024))
  self.expected=bytearray(u.mem_read(BASE,SIZE));self.active=True
  try:
   if mode==0:
    out=POINT if alias else OUT
    self.checked_call(0x631ba0,[out,POINT,clamp],MAP,writes=[(out,8)],inputs=[*RANGES.items(),*DATA.items(),(MAP,0x1500)])
    assert u.reg_read(UC_X86_REG_EAX)==out
    self.emit('R',*struct.unpack('<ii',u.mem_read(out,8)),*struct.unpack('<ii',u.mem_read(POINT,8)))
   else:
    for i in range(repeats):
     self.emit('I',i)
     self.checked_call(0x632620,[POINT],MAP,writes=[(V,24),(MAP+0x14d5,1),(BITMAP,1024),(POOL,STRIDE*8)],inputs=[*RANGES.items(),*DATA.items(),(VT,0x84)])
     self.supply(POINT,struct.pack('<I',(self.word(POINT)+step)&0xffffffff))
    assert not self.pending
    self.emit('R',self.identity(self.word(V+4)),signed(self.word(V+8)),signed(self.word(V+16)),u.mem_read(V+12,1)[0],u.mem_read(V+13,1)[0],u.mem_read(MAP+0x14d5,1)[0],signed(self.word(POINT)),signed(self.word(POINT+4)),int(self.word(MAP+0x1218)==OTHER),digest(u.mem_read(BITMAP,1024)),*[digest(u.mem_read(POOL+i*STRIDE,STRIDE)) for i in range(self.slots)])
  finally:self.active=False
  assert bytes(u.mem_read(BASE,SIZE))==self.expected
  return self.trace
