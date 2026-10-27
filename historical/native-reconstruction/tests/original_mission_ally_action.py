# SPDX-License-Identifier: GPL-3.0-or-later
"""Unmodified action37 branch with explicit House lookup/alliance children."""
import struct
from collections import Counter
from original_presentation import PresentationOracle,STOP
from verify_mission_ally_action import verify,RANGES,TABLES
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_EIP,UC_X86_REG_ESP
ARENA=0x3000000;SIZE=0x10000;ACTION=ARENA+0x100;CURRENT=ARENA+0x1000;TARGET=ARENA+0x2000;TRIGGER=ARENA+0x3000
def signed(v):return v if v<2**31 else v-2**32
class MissionAllyActionOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(ARENA,SIZE);self.active=False;self.counts=Counter();self.u.hook_add(UC_HOOK_CODE,self.code)
 def va(self,a):return a
 def word(self,p):return struct.unpack('<I',self.u.mem_read(p,4))[0]
 def ident(self,p):
  if p==0:return 0
  if p==CURRENT:return 1
  if p==TARGET:return 2
  raise AssertionError(('Foreign Mission ally identity',hex(p)))
 def ret(self,n,value=0):
  u=self.u;sp=u.reg_read(UC_X86_REG_ESP);target=self.word(sp);u.reg_write(UC_X86_REG_ESP,sp+4+n);u.reg_write(UC_X86_REG_EAX,value&0xffffffff);u.reg_write(UC_X86_REG_EIP,target)
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  sp=u.reg_read(UC_X86_REG_ESP)
  if a==0x4ed760:
   index=signed(u.reg_read(UC_X86_REG_ECX));resolved=(0,CURRENT,TARGET)[self.f['resolvedMode']]
   self.trace.extend(('F',str(index),str(self.ident(resolved))));self.counts['supplied_lookup']+=1;self.ret(0,resolved);return
  if a==0x4e5660:
   self.trace.extend(('A',str(self.ident(u.reg_read(UC_X86_REG_ECX))),str(self.ident(self.word(sp+4))),str(self.word(sp+8))))
   self.counts['supplied_make_ally']+=1;self.ret(8,0xa5a5a5a5);return
  assert any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected Mission ally instruction',hex(a))
  if a in RANGES:self.counts[hex(a)]+=1
 def run(self,f):
  self.f=f;u=self.u;u.mem_write(ARENA,b'\xa5'*SIZE);self.put(ACTION+0x2c,37);self.put(ACTION+0x74,f['value'])
  current=(0,CURRENT,TARGET)[f['currentMode']];before=bytes(u.mem_read(ARENA,SIZE));self.trace=[];self.active=True
  try:self.checked_call(0x6adae0,[current,0,TRIGGER,ACTION+0x80],ACTION,inputs=[*RANGES.items(),*TABLES.items(),(ACTION,0x100)])
  finally:self.active=False
  assert bytes(u.mem_read(ARENA,SIZE))==before
  self.trace.extend(('R',str(u.reg_read(UC_X86_REG_EAX)&255)));return self.trace
