# SPDX-License-Identifier: GPL-3.0-or-later
"""Execute unchanged coordinate Cell lookup with guarded supplied table/storage."""
import struct
from original_presentation import PresentationOracle,ARG,STOP
from original_foot_lit import words
from verify_map_coordinate_cell import verify,ROOT,SIZE
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX
MAP=0x8324e0;FALLBACK=0xa6f9f8;TABLE=0x2400000;CELLS=0x2500000
class MapCoordinateCellOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True)
  self.u.mem_map(TABLE,0x110000);self.writes=0
  self.u.hook_add(UC_HOOK_CODE,self.code)
 def va(self,a):return a
 def code(self,u,a,n,ctx):
  if a!=STOP and not ROOT<=a<a+n<=ROOT+SIZE:raise AssertionError('Uninspected coordinate lookup instruction')
 def run(self,count,indexes,queries):
  self.u.mem_write(TABLE,bytes(0x100000));self.put(MAP+0x138,TABLE);self.put(MAP+0x13c,count)
  for i,index in enumerate(indexes):
   p=CELLS+i*512;self.u.mem_write(p,b'\xa5'*512);self.put(p+0x24,((i*29-32768)&65535)|(((i*31+32700)&65535)<<16));self.put(TABLE+index*4,p)
  self.u.mem_write(FALLBACK,b'\xa7'*0x148);self.put(FALLBACK+0x24,(-30000&65535)|(29000<<16));old=bytes(self.u.mem_read(FALLBACK,0x148));result=[]
  def store(u,access,p,n,v,ctx):
   if p==FALLBACK+0x24:assert n==4;self.writes+=1
  hook=self.u.hook_add(UC_HOOK_MEM_WRITE,store)
  try:
   for x,y,z in queries:
    self.u.mem_write(ARG,struct.pack('<3i',x,y,z));before=self.writes
    self.checked_call(ROOT,[ARG],MAP,writes=[(FALLBACK+0x24,4)],inputs=[(ARG,12),(MAP+0x138,8),(TABLE,0x100000),(CELLS,len(indexes)*512)])
    p=self.u.reg_read(UC_X86_REG_EAX);index=-1 if p==FALLBACK else (p-CELLS)//512
    assert p==FALLBACK or 0<=index<len(indexes) and p==CELLS+index*512
    result.extend(map(str,[index,words(self.u,p+0x24,1)[0],words(self.u,FALLBACK+0x24,1)[0],self.writes-before]))
  finally:self.u.hook_del(hook)
  final=bytearray(self.u.mem_read(FALLBACK,0x148));final[0x24:0x28]=old[0x24:0x28];assert bytes(final)==old
  return result
