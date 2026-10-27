# SPDX-License-Identifier: GPL-3.0-or-later
"""Unmodified632700 and actual stock vector clear/resize/FTOL children."""
import struct
from collections import Counter
from original_presentation import PresentationOracle,STOP
from verify_radar_shape_buckets import verify,RANGES,DATA,TABLE
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EIP
BASE=0x3b00000;SIZE=0x400000;MAP=BASE;VECTORS=BASE+0x1274;POOL=BASE+0x10000;STRIDE=0x2000
def signed(v):return (v+2**31)%2**32-2**31
class RadarShapeBucketsOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(BASE,SIZE);self.active=False;self.counts=Counter();self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.write)
 def va(self,a):return a
 def word(self,p):return struct.unpack('<I',self.u.mem_read(p,4))[0]
 def emit(self,*v):self.trace.extend(map(str,v))
 def ret(self,result=0):
  sp=self.u.reg_read(UC_X86_REG_ESP);self.u.reg_write(UC_X86_REG_EAX,result);self.u.reg_write(UC_X86_REG_EIP,self.word(sp));self.u.reg_write(UC_X86_REG_ESP,sp+4)
 def create(self,slot):
  data=b''.join(struct.pack('<II',0x12340000+slot*1024+k,0x56780000+slot*1024+k) for k in range(1024));p=POOL+slot*STRIDE;self.u.mem_write(p,data)
  if self.active:self.expected[p-BASE:p-BASE+len(data)]=data
 def identity(self,p):
  assert p==0 or POOL<=p<POOL+self.slots*STRIDE and (p-POOL)%STRIDE==0
  return 0 if p==0 else (p-POOL)//STRIDE+1
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  sp=u.reg_read(UC_X86_REG_ESP)
  if a in (0x5b16e0,0x5b1b00):self.current=(u.reg_read(UC_X86_REG_ECX)-VECTORS)//24;assert 0<=self.current<22
  if a==0x782017:
   size=self.word(sp+4);assert 0<size<=8192 and size%8==0;self.emit('A',self.current,size,self.failed);self.counts['allocations']+=1
   p=0
   if not self.failed:p=POOL+self.slots*STRIDE;self.create(self.slots);self.slots+=1
   self.ret(p);return
  if a==0x781d3b:self.emit('D',self.current,self.identity(self.word(sp+4)));self.counts['releases']+=1;self.ret();return
  assert any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected radar shape instruction',hex(a))
  if a in RANGES:self.counts[hex(a)]+=1
 def write(self,u,access,p,n,value,_):
  if not self.active or not BASE<=p<BASE+SIZE:return
  value&=(1<<(8*n))-1
  if VECTORS<=p and p+n<=VECTORS+22*24:
   i,off=divmod(p-VECTORS,24);assert (off,n) in ((4,4),(8,4),(12,1),(13,1),(16,4));v=self.identity(value) if off==4 else value;self.emit('F',i,off,n,v)
  else:
   slot,off=divmod(p-POOL,STRIDE);assert 0<=slot<self.slots and off+n<=8192 and n==4;self.emit('P',slot+1,off,n,value)
  self.expected[p-BASE:p-BASE+n]=value.to_bytes(n,'little')
 def run(self,f):
  mode,bits,count,capacity,growth,owned,valid,present,self.failed,repeats,requested=f[:11];u=self.u;u.mem_write(BASE,b'\xa5'*SIZE);self.slots=22;self.current=0;self.trace=[]
  for i in range(22):
   self.create(i);p=VECTORS+i*24
   for off,v in ((0,TABLE),(4,POOL+i*STRIDE if present else 0),(8,capacity),(16,count),(20,growth)):self.put(p+off,v)
   u.mem_write(p+12,bytes([valid,owned]));
  self.put(MAP+0x1484,bits)
  # Authored dimension probes are explicit input data, never changed mid-call.
  u.mem_write(0x7cfc70,struct.pack('<44i',*f[11:]));self.expected=bytearray(u.mem_read(BASE,SIZE));self.active=True
  try:
   for iteration in range(repeats):
    self.emit('I',iteration);self.current=0;root,args,owner=(0x632700,[],MAP) if mode==0 else (0x5b1b00,[requested,0],VECTORS) if mode==1 else (0x5b16e0,[],VECTORS)
    self.checked_call(root,args,owner,writes=[(VECTORS,22*24),(POOL,SIZE-(POOL-BASE))],inputs=[*RANGES.items(),(TABLE,24),*DATA.items(),(MAP+0x1484,4)])
    if mode==1:self.emit('R',u.reg_read(UC_X86_REG_EAX)&255)
  finally:self.active=False
  assert bytes(u.mem_read(BASE,SIZE))==self.expected
  self.emit('V')
  for i in range(22):
   p=VECTORS+i*24;self.emit(self.identity(self.word(p+4)),signed(self.word(p+8)),signed(self.word(p+16)),u.mem_read(p+12,1)[0],u.mem_read(p+13,1)[0])
  self.emit('H')
  for i in range(self.slots):
   digest=14695981039346656037
   for byte in u.mem_read(POOL+i*STRIDE,8192):digest=((digest^byte)*1099511628211)&(2**64-1)
   self.emit(digest)
  return self.trace
