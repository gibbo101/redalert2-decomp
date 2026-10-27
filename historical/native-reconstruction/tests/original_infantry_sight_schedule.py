# SPDX-License-Identifier: GPL-3.0-or-later
"""Unmodified argument-2 Infantry sight-scheduling interior block."""
import struct
from collections import Counter
from original_presentation import PresentationOracle,STACK
from verify_infantry_sight_schedule import verify,START,END
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_ECX,UC_X86_REG_EDX,UC_X86_REG_EIP,UC_X86_REG_ESP,UC_X86_REG_ESI
ARENA=0x3700000;SIZE=0x10000;ACTOR=ARENA+0x1000;VTABLE=ARENA+0x4000
SERVICES={0x594c50:'M',0x6d5e90:'R',0x6d5c30:'A',0x54a550:'P'}
class InfantrySightScheduleOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(ARENA,SIZE);self.active=False;self.counts=Counter();self.u.hook_add(UC_HOOK_CODE,self.code)
 def va(self,a):return a
 def word(self,p):return struct.unpack('<I',self.u.mem_read(p,4))[0]
 def signed(self,v):return v if v<2**31 else v-2**32
 def ret(self,n=0):
  u=self.u;sp=u.reg_read(UC_X86_REG_ESP);u.reg_write(UC_X86_REG_EIP,self.word(sp));u.reg_write(UC_X86_REG_ESP,sp+4+n)
 def code(self,u,a,n,_):
  if not self.active:return
  if a==END:return
  if a in SERVICES:
   sp=u.reg_read(UC_X86_REG_ESP);kind=SERVICES[a];self.counts['supplied.'+kind]+=1
   if kind=='M':self.trace.append('M');self.ret();return
   if kind in ('R','A'):
    self.trace.extend((kind,*[str(self.word(sp+4+i*4)) for i in range(4)]));self.ret(16);return
   point=self.word(sp+4);self.trace.extend(('P',*[str(self.signed(self.word(point+i*4))) for i in range(3)],str(self.word(sp+8)),str(self.signed(self.word(sp+12))),str(self.word(sp+16))));self.ret(16);return
  assert START<=a<END,('Uninspected Infantry sight scheduler instruction',hex(a))
 def run(self,f):
  u=self.u;u.mem_write(ARENA,b'\xa5'*SIZE);self.put(ACTOR,VTABLE);self.put(VTABLE+0x1d4,0x594c50);self.put(VTABLE+0x418,0x6d5c30);self.put(VTABLE+0x41c,0x6d5e90)
  u.mem_write(ACTOR+0x88,struct.pack('<iii',f['x'],f['y'],f['z']));self.put(ACTOR+0x1f4,f['range']);u.mem_write(STACK,b'\xa7'*0x100)
  self.trace=[];self.active=True;u.reg_write(UC_X86_REG_ESI,ACTOR);u.reg_write(UC_X86_REG_ESP,STACK);u.reg_write(UC_X86_REG_EIP,START)
  try:u.emu_start(START,END,count=100)
  finally:self.active=False
  if u.reg_read(UC_X86_REG_EIP)!=END or u.reg_read(UC_X86_REG_ESP)!=STACK:raise AssertionError('Infantry sight scheduler interior ABI differs')
  self.counts[hex(START)]+=1;return self.trace
