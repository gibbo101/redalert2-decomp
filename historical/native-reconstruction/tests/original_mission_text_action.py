# SPDX-License-Identifier: GPL-3.0-or-later
"""Unmodified action11 branch with explicit color/localization/display children."""
import struct
from collections import Counter
from original_presentation import PresentationOracle,STOP
from verify_mission_text_action import verify,RANGES,TABLES
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_EDX,UC_X86_REG_EIP,UC_X86_REG_ESP
ARENA=0x2e00000;SIZE=0x10000;ACTION=ARENA+0x100;SCENARIO=ARENA+0x1000;RULES=ARENA+0x4000;TEXT=ARENA+0x8000
def signed(v):return v if v<2**31 else v-2**32
def encoded(raw):return raw.hex() if raw else '-'
class MissionTextActionOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(ARENA,SIZE);self.active=False;self.counts=Counter();self.u.hook_add(UC_HOOK_CODE,self.code)
 def va(self,a):return a
 def word(self,p):return struct.unpack('<I',self.u.mem_read(p,4))[0]
 def cstring(self,p,limit=128):
  raw=bytes(self.u.mem_read(p,limit));return raw[:raw.index(0)]
 def ret(self,n,value=0):
  u=self.u;sp=u.reg_read(UC_X86_REG_ESP);target=self.word(sp);u.reg_write(UC_X86_REG_ESP,sp+4+n);u.reg_write(UC_X86_REG_EAX,value&0xffffffff);u.reg_write(UC_X86_REG_EIP,target)
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  sp=u.reg_read(UC_X86_REG_ESP)
  if a==0x6715d0:
   selector=self.word(sp+4);assert u.reg_read(UC_X86_REG_ECX)==0xa3d298 and selector in (1,2)
   color=self.f['colors'][selector-1];self.trace.extend(('C',str(selector),str(color)));self.counts['supplied_color']+=1;self.ret(4,color);return
  if a==0x6f9ec0:
   assert u.reg_read(UC_X86_REG_ECX)==ACTION+0x54 and u.reg_read(UC_X86_REG_EDX)==0
   self.trace.extend(('L',encoded(self.cstring(ACTION+0x54,32)),'0',str(self.word(sp+4)),str(self.word(sp+8))))
   self.counts['supplied_localize']+=1;self.ret(8,TEXT);return
  if a==0x5b4da0:
   args=struct.unpack('<7I',u.mem_read(sp+4,28));assert u.reg_read(UC_X86_REG_ECX)==0xa3dc70 and args[2]==TEXT
   self.trace.extend(('M',str(signed(args[0])),str(signed(args[1])),encoded(self.cstring(TEXT)),str(signed(args[3])),str(signed(args[4])),str(args[5]),str(signed(args[6]))))
   self.counts['supplied_display']+=1;self.ret(28,0xa5a5a5a5);return
  assert any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected Mission text instruction',hex(a))
  if a in RANGES:self.counts[hex(a)]+=1
 def run(self,f):
  self.f=f;u=self.u;u.mem_write(ARENA,b'\xa5'*SIZE);u.mem_write(ACTION+0x54,b'\0'*32);u.mem_write(ACTION+0x54,f['key']+b'\0');u.mem_write(TEXT,f['localized']+b'\0')
  self.put(ACTION+0x2c,11);self.put(0xa3d290,SCENARIO);u.mem_write(SCENARIO+0x2239,bytes([f['alternate']]));self.put(0x839848,RULES);u.mem_write(RULES+0x1128,struct.pack('<Q',f['delayBits']))
  before=bytes(u.mem_read(ARENA,SIZE));self.trace=[];self.active=True
  try:self.checked_call(0x6adae0,[0,0,ACTION+0xc0,ACTION+0x80],ACTION,inputs=[*RANGES.items(),*TABLES.items(),(0x79b608,8),(0x7d8964,4),(0xa3d290,4),(0x839848,4),(ACTION,0x100),(SCENARIO+0x2239,1),(RULES+0x1128,8)])
  finally:self.active=False
  assert bytes(u.mem_read(ARENA,SIZE))==before
  self.trace.extend(('R',str(u.reg_read(UC_X86_REG_EAX)&255)));return self.trace
