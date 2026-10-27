# SPDX-License-Identifier: GPL-3.0-or-later
"""Unmodified viewport, affine point transform and FTOL on one shared arena."""
import struct
from original_presentation import PresentationOracle,STOP
from original_tactical_viewport import BASE,SIZE,OBJ,FIELDS,signed
from verify_tactical_viewport_matrix import verify,RANGES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_ECX,UC_X86_REG_EDX,UC_X86_REG_ESP
class TacticalViewportMatrixOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True)
  self.u.mem_map(BASE,SIZE);self.active=False;self.entries={hex(a):0 for a in RANGES}
  self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.write)
 def va(self,p):return p
 def word(self,p):return struct.unpack('<I',self.u.mem_read(p,4))[0]
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  assert any(p<=a and a+n<=p+s for p,s in RANGES.items()),('Uninspected joined viewport instruction',hex(a))
  if a in RANGES:self.entries[hex(a)]+=1
  if a==0x591380:
   assert u.reg_read(UC_X86_REG_EDX)==OBJ+0xde4
   sp=u.reg_read(UC_X86_REG_ESP);p=self.word(sp+4)
   self.trace.extend(['I',*map(str,struct.unpack('<3I',u.mem_read(p,12)))])
   self.output=u.reg_read(UC_X86_REG_ECX)
  if a==0x6a91f7:
   self.trace.extend(['O',*map(str,struct.unpack('<3I',u.mem_read(self.output,12)))])
 def write(self,u,access,p,n,v,_):
  if self.active and BASE<=p<BASE+SIZE:
   assert n==4 and p-OBJ in FIELDS
   self.trace.extend(['S',str(p-OBJ),str(signed(v))])
 def run(self,f):
  x,y,w,h,*matrix=f;self.trace=[];self.u.mem_write(BASE,bytes([0x5a])*SIZE)
  self.put(OBJ+0xd64,x);self.put(OBJ+0xd68,y);self.put(0xabe568,w);self.put(0xabe56c,h)
  self.u.mem_write(OBJ+0xde4,struct.pack('<12I',*matrix));before=bytes(self.u.mem_read(BASE,SIZE));self.active=True
  try:self.checked_call(0x6a9170,ecx=OBJ,writes=[(OBJ+p,4) for p in FIELDS],
   inputs=[*RANGES.items(),(OBJ+0xd64,8),(OBJ+0xde4,48),(0xabe568,8)])
  finally:self.active=False
  after=bytearray(self.u.mem_read(BASE,SIZE))
  for p in FIELDS:after[p:p+4]=before[p:p+4]
  assert after==before,'Joined viewport changed unrelated arena bytes'
  self.trace.extend(['Z',*[str(signed(self.word(OBJ+p))) for p in FIELDS]])
  return self.trace
