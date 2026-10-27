# SPDX-License-Identifier: GPL-3.0-or-later
"""Unmodified action17 branch with an explicit Reveal Around Waypoint child."""
import struct
from collections import Counter
from original_presentation import PresentationOracle,STOP
from verify_mission_reveal_action import verify,RANGES,TABLES
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_EIP,UC_X86_REG_ESP
ARENA=0x3000000;SIZE=0x10000;ACTION=ARENA+0x100;OBJECT=ARENA+0x1000;TRIGGER=ARENA+0x3000;PACKED=ARENA+0x4000
class MissionRevealActionOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(ARENA,SIZE);self.active=False;self.counts=Counter();self.u.hook_add(UC_HOOK_CODE,self.code)
 def va(self,a):return a
 def word(self,p):return struct.unpack('<I',self.u.mem_read(p,4))[0]
 def ret(self,n,value=0):
  u=self.u;sp=u.reg_read(UC_X86_REG_ESP);target=self.word(sp);u.reg_write(UC_X86_REG_ESP,sp+4+n);u.reg_write(UC_X86_REG_EAX,value&0xffffffff);u.reg_write(UC_X86_REG_EIP,target)
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  if a==0x6b0670:
   sp=u.reg_read(UC_X86_REG_ESP);self.trace.extend(('C',str(u.reg_read(UC_X86_REG_ECX)),str(self.word(sp+4)),str(self.word(sp+8)),str(self.word(sp+12)),str(self.word(sp+16))))
   self.counts['supplied_reveal']+=1;self.ret(16,self.f['result']);return
  assert any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected Mission Reveal instruction',hex(a))
  if a in RANGES:self.counts[hex(a)]+=1
 def run(self,f):
  self.f=f;u=self.u;u.mem_write(ARENA,b'\xa5'*SIZE);self.put(ACTION+0x2c,17);u.mem_write(OBJECT+0x7d,bytes([1 if f['object']==2 else 0]));before=bytes(u.mem_read(ARENA,SIZE));self.trace=[];self.active=True
  try:self.checked_call(0x6adae0,[f['first'],OBJECT if f['object'] else 0,f['third'],f['fourth']],ACTION,inputs=[*RANGES.items(),*TABLES.items(),(ACTION,0x100),(OBJECT,0x100)])
  finally:self.active=False
  assert bytes(u.mem_read(ARENA,SIZE))==before
  self.trace.extend(('R',str(u.reg_read(UC_X86_REG_EAX)&255)));return self.trace
