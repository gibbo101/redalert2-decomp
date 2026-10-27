# SPDX-License-Identifier: GPL-3.0-or-later
"""Unmodified base visibility-mask calculation with synthetic result tables."""
import struct
from collections import Counter
from original_presentation import PresentationOracle,STOP
from verify_cell_visibility_mask import verify,RANGES,TABLE
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_EIP,UC_X86_REG_ESP
ARENA=0x3800000;SIZE=0x140000;POINT=ARENA;SLOTS=ARENA+0x10000;CELLS=ARENA+0x120000;FALLBACK=0xa6f9f8
OFFSETS=((0,0),(-1,-1),(0,-1),(1,-1),(-1,0),(1,0),(-1,1),(0,1),(1,1))
def signed(v):return v if v<2**31 else v-2**32
def w(v):return ((v+2**15)%2**16)-2**15
class CellVisibilityMaskOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(ARENA,SIZE);self.active=False;self.counts=Counter();self.u.hook_add(UC_HOOK_CODE,self.code)
 def va(self,a):return a
 def word(self,p):return struct.unpack('<I',self.u.mem_read(p,4))[0]
 def point(self,p):return struct.unpack('<hh',self.u.mem_read(p,4))
 def cid(self,p):
  if p==FALLBACK:return 9
  assert CELLS<=p<CELLS+9*0x200 and (p-CELLS)%0x200==0;return (p-CELLS)//0x200
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  assert any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected visibility-mask instruction',hex(a))
  if a in RANGES:self.counts[hex(a)]+=1
  if a==0x5480a5:
   p=self.point(self.word(u.reg_read(UC_X86_REG_ESP)+4));cell=u.reg_read(UC_X86_REG_EAX)
   if cell==FALLBACK:self.trace.extend(('B',str(p[0]),str(p[1])))
   self.trace.extend(('L',str(p[0]),str(p[1]),str(self.cid(cell))))
 def run(self,f):
  u=self.u;u.mem_write(ARENA,b'\xa5'*SIZE);u.mem_write(SLOTS,bytes(0x100000));u.mem_write(FALLBACK,b'\xa5'*0x148);u.mem_write(CELLS,b'\xa5'*(9*0x200));self.put(0x832618,SLOTS);u.mem_write(POINT,struct.pack('<hh',f['x'],f['y']))
  for i,(dx,dy) in enumerate(OFFSETS):
   px,py=w(f['x']+dx),w(f['y']+dy);index=py*512+px;slot=f['slots'][i]
   if slot>=0 and 0<=index<262144:self.put(SLOTS+index*4,CELLS+slot*0x200)
  for i in range(10):
   cell=FALLBACK if i==9 else CELLS+i*0x200;self.put(cell+0x12c,f['flags12c'][i]);self.put(cell+0x140,f['flags140'][i])
  table=bytes((i*37+f['seed']*13)&255 for i in range(256));u.mem_write(TABLE,table);before=bytearray(u.mem_read(ARENA,SIZE));before_fallback=bytearray(u.mem_read(FALLBACK,0x148));self.trace=[];self.active=True
  try:self.checked_call(0x6a8d40,[POINT,f['mode']],writes=[(FALLBACK+0x24,4)],inputs=[*RANGES.items(),(0x832618,4),(POINT,4),(SLOTS,0x100000),(CELLS,9*0x200),(TABLE,256),(FALLBACK,0x24),(FALLBACK+0x28,0x120)])
  finally:self.active=False
  result=signed(u.reg_read(UC_X86_REG_EAX));after=bytearray(u.mem_read(ARENA,SIZE));after_fallback=bytearray(u.mem_read(FALLBACK,0x148));before_fallback[0x24:0x28]=after_fallback[0x24:0x28];assert after==before and after_fallback==before_fallback
  self.trace.extend(('R',str(result),str(self.point(FALLBACK+0x24)[0]),str(self.point(FALLBACK+0x24)[1])));return self.trace
