# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete unmodified discovery queries on one shared map/Cell arena."""
import struct
from collections import Counter
from original_presentation import PresentationOracle,STOP
from verify_radar_discovery import verify,RANGES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP
CELL=0x2400000;INPUT=CELL+0x1000;SLOTS=0x2500000;FALLBACK=0xa6f9f8;MAP=0x8324e0
CELLS=[CELL,CELL+0x400,CELL+0x800,FALLBACK]
def shorts(u,p):return struct.unpack('<hh',u.mem_read(p,4))
class RadarDiscoveryOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(CELL,0x10000);self.u.mem_map(SLOTS,0x100000);self.counts=Counter();self.active=False
  self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.write)
 def va(self,a):return a
 def event(self,*v):self.trace.extend(map(str,v))
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  assert any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected discovery instruction',hex(a))
  if a in RANGES:self.counts[hex(a)]+=1
  sp=u.reg_read(UC_X86_REG_ESP)
  if a in (0x5682df,0x56836a,0x56819f,0x56822b):self.event('i',*shorts(u,sp+(0x10 if a<0x568280 else 0x10)))
  elif a in (0x56830e,0x568399):
   p=u.reg_read(UC_X86_REG_EAX);self.event('c',CELLS.index(p),struct.unpack('<i',u.mem_read(p+0x13c,4))[0])
  elif a==0x476ac0:
   d=struct.unpack('<I',u.mem_read(sp+4,4))[0];assert d==3;self.event('n',CELLS.index(u.reg_read(UC_X86_REG_ECX)),d)
  elif a==0x548070:self.event('w',*shorts(u,struct.unpack('<I',u.mem_read(sp+4,4))[0]))
 def write(self,u,access,p,n,value,_):
  if self.active and p==FALLBACK+0x24:
   assert n==4;self.event('f',*struct.unpack('<hh',struct.pack('<I',value&0xffffffff)))
 def run(self,f):
  divisor,x,y,z,order=f[:5];u=self.u;self.trace=[];u.mem_write(CELL,b'\xa5'*0x10000);u.mem_write(FALLBACK,b'\xa5'*0x148);u.mem_write(SLOTS,bytes(0x100000));self.put(MAP+0x138,SLOTS);self.put(0xa6fc30,divisor);u.mem_write(INPUT,struct.pack('<3i',x,y,z));u.mem_write(0x851a7c,struct.pack('<hh',1,1))
  for i,p in enumerate(CELLS):
   slot,cx,cy,flags,other,count=f[5+i*6:11+i*6];self.put(p+0x24,(cx&65535)|((cy&65535)<<16));self.put(p+0x12c,flags);self.put(p+0x140,other);self.put(p+0x13c,count)
   if slot!=-1:self.put(SLOTS+slot*4,p)
  before=bytes(u.mem_read(CELL,0x10000));fb=bytes(u.mem_read(FALLBACK,0x148))
  for entry in ([0x568280] if order==0 else [0x568140,0x568280] if order==1 else [0x568280,0x568140]):
   self.active=True
   try:self.checked_call(entry,[INPUT],MAP,writes=[(FALLBACK+0x24,4)],inputs=[*RANGES.items(),(SLOTS,0x100000),(INPUT,12),(MAP+0x138,4),(0xa6fc30,4),(0x851a7c,4)])
   finally:self.active=False
   self.event('R',u.reg_read(UC_X86_REG_EAX)&255,*shorts(u,FALLBACK+0x24))
  assert bytes(u.mem_read(CELL,0x10000))==before
  after=bytearray(u.mem_read(FALLBACK,0x148));after[0x24:0x28]=fb[0x24:0x28];assert bytes(after)==fb
  return self.trace
