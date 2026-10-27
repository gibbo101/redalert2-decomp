# SPDX-License-Identifier: GPL-3.0-or-later
"""Unmodified complete6C2990 through Cell-mask and actor-predicate exits."""
import struct
from collections import Counter
from original_presentation import PresentationOracle,STOP
from verify_position_cloak_effect import verify,RANGE,HELPERS
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_EIP,UC_X86_REG_ESP

ARENA=0x3a00000;SIZE=0x110000;ACTOR=ARENA+0x1000;HOUSE=ARENA+0x3000;CELL=ARENA+0x5000;SLOTS=ARENA+0x10000;MAP=0x8324e0
def pack(v):return struct.pack('<I',v&0xffffffff)
def word(v):
 q=v//256 if v>=0 else -((-v)//256)
 return ((q+0x8000)&0xffff)-0x8000
class PositionCloakEffectOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(ARENA,SIZE)
  self.active=False;self.predicate=0;self.predicate_calls=0;self.counts=Counter();self.u.hook_add(UC_HOOK_CODE,self.code)
 def va(self,a):return a
 def value(self,p):return struct.unpack('<I',self.u.mem_read(p,4))[0]
 def ret(self,n,value=0):
  u=self.u;sp=u.reg_read(UC_X86_REG_ESP);u.reg_write(UC_X86_REG_EAX,value&0xffffffff)
  u.reg_write(UC_X86_REG_EIP,self.value(sp));u.reg_write(UC_X86_REG_ESP,sp+4+n)
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  if a==0x6c9020:
   self.predicate_calls+=1;self.counts['predicate']+=1;self.ret(0,self.predicate);return
  allowed={RANGE[0]:RANGE[1]-RANGE[0],**HELPERS}
  if not any(start<=a<start+size for start,size in allowed.items()):
   raise AssertionError(('Uninspected position cloak-effect instruction',hex(a)))
  if a==RANGE[0]:self.counts['roots']+=1
  elif a==0x548070:self.counts['map']+=1
  elif a==0x47c2c0:self.counts['mask']+=1
 def run(self,f):
  u=self.u;u.mem_write(ARENA,bytes(SIZE));self.put(ACTOR,0x7a3540);u.mem_write(ACTOR+0x88,struct.pack('<iii',f['x'],f['y'],0))
  self.put(ACTOR+0x1b4,HOUSE);self.put(HOUSE+0x30,f['owner']);self.put(CELL+0x78,f['mask']);self.put(MAP+0x138,SLOTS)
  cx,cy=word(f['x']),word(f['y']);index=cy*512+cx
  if not (0<=index<262144):raise ValueError('Position cloak-effect fixture point outside map')
  self.put(SLOTS+index*4,CELL);self.predicate=f['predicate'];self.predicate_calls=0;self.active=True
  try:self.checked_call(RANGE[0],ecx=ACTOR,inputs=[(ACTOR,0x1b8),(HOUSE,0x40),(CELL,0x100)])
  finally:self.active=False
  bit=1<<(f['owner']&31);result=0 if not(f['mask']&bit) else 1
  expected_calls=1 if result else 0
  if self.predicate_calls!=expected_calls:raise AssertionError('Position cloak-effect call order differs')
  return ['R',str(result),str(cx),str(cy),str(self.predicate_calls)]
