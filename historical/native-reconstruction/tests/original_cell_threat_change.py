# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete original Cell threat parent/children, ordered writes and private arena audit."""
import struct
from collections import Counter
from original_presentation import PresentationOracle,STOP
from verify_cell_threat_change import verify,RANGES,TABLES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX
BASE=0x5f00000;SIZE=0x60000;CELL=BASE+0x100;POINT=BASE+0x200;SLOTS=BASE+0x300;ALT=BASE+0x400
HOUSES=tuple(BASE+0x1000+i*0x18000 for i in range(3));GLOBALS=(0xa322a8,0xa3229c,0xa3d298)
class CellThreatChangeOracle(PresentationOracle):
 def __init__(self,exe):
  verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(BASE,SIZE);self.active=False;self.counts=Counter();self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.write)
 def va(self,a):return a
 def word(self,p):return int.from_bytes(self.u.mem_read(p,4),'little')
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  assert any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),hex(a)
  if a in RANGES:self.counts[hex(a)]+=1
 def write(self,u,access,p,n,v,_):
  if not self.active:return
  assert n==4
  for i,h in enumerate(HOUSES):
   if h+0x56d0<=p<h+0x56d0+0x4204*4:
    assert (p-h-0x56d0)%4==0;self.trace.extend(map(str,(i,(p-h-0x56d0)//4,v&0xffffffff)))
    raw=(v&0xffffffff).to_bytes(4,'little');self.expected[p-BASE:p-BASE+4]=raw
    self.writes+=1
    if self.writes==1 and self.f[10]:
     self.put(0xa3229c,ALT);self.expectedGlobals[0xa3229c]=ALT.to_bytes(4,'little')
     if self.f[10]==1:
      self.put(0xa322a8,1);self.expectedGlobals[0xa322a8]=bytes([1,0,0,0]);self.put(CELL+0x24,100|(100<<16));self.expected[CELL+0x24-BASE:CELL+0x28-BASE]=struct.pack('<hh',100,100)
    return
  # Stack writes are checked by checked_call, all other writes refuse.
 def run(self,f):
  self.f=f;self.writes=0;u=self.u;u.mem_write(BASE,b'\x5a'*SIZE)
  u.mem_write(CELL+0x24,struct.pack('<hh',f[1] if f[0]==0 else 0,f[2]));u.mem_write(POINT,bytes(4))
  for i,h in enumerate(HOUSES):
   self.put(h+0x30,f[11+4*i]);u.mem_write(h+0x134,bytes(f[12+4*i:14+4*i]));self.put(h+0x5674,f[14+4*i]);u.mem_write(h+0x56d0,struct.pack('<I',f[9]&0xffffffff)*0x4204)
  for i in range(4):self.put(SLOTS+4*i,0 if f[7]>>i&1 else HOUSES[0 if f[8] else i%3])
  for i,h in enumerate((HOUSES[2],HOUSES[0],0,HOUSES[1])):self.put(ALT+4*i,h)
  for p,v in zip(GLOBALS,(f[6],SLOTS,f[5])):self.put(p,v)
  # Caller-supplied stencil profile: stock or authored aliases. Original code is unchanged.
  self.u.mem_write(0x7d9fa0,struct.pack('<18i',*f[23:]));self.expected=bytearray(u.mem_read(BASE,SIZE));self.trace=[];self.active=True
  address=(0x476b20,0x4e5dc0,0x4e5500,0x4f52f0)[f[0]];args=([f[3],f[4]],[f[1],f[4]],[f[3]],[])[f[0]]
  self.expectedGlobals={p:bytes(u.mem_read(p,4)) for p in GLOBALS}
  try:self.checked_call(address,args,CELL if f[0]==0 else HOUSES[0],writes=[(h+0x56d0,0x4204*4) for h in HOUSES],inputs=[*RANGES.items(),*TABLES.items(),*[(p,4) for p in GLOBALS if not f[10] or p==0xa3d298]])
  finally:self.active=False
  assert bytes(u.mem_read(BASE,SIZE))==self.expected,'Unrelated Cell threat arena changed'
  assert all(bytes(u.mem_read(p,4))==v for p,v in self.expectedGlobals.items())
  result=(u.reg_read(UC_X86_REG_EAX)&255) if f[0] in (2,3) else 0
  self.trace.extend(map(str,('R',result)))
  for h in HOUSES:
   grid=struct.unpack('<'+str(0x4204)+'I',u.mem_read(h+0x56d0,0x4204*4));changes=[(i,v) for i,v in enumerate(grid) if v!=f[9]&0xffffffff];self.trace.extend(map(str,('G',len(changes))))
   for i,v in changes:self.trace.extend(map(str,(i,v)))
  xy=struct.unpack('<hh',u.mem_read(CELL+0x24,4));self.trace.extend(map(str,('D',self.word(0xa322a8),int(self.word(0xa3229c)==ALT),*[v&0xffffffff for v in xy])))
  return self.trace
