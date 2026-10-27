# SPDX-License-Identifier: GPL-3.0-or-later
"""Actual stock threat/type/kind/Building getter roots, no intercepted leaves."""
import struct
from collections import Counter
from original_presentation import PresentationOracle,STOP
from verify_techno_threat import verify,RANGES
from unicorn import UC_HOOK_CODE
ARENA=0x3000000;SIZE=0x8000;ACTOR=ARENA;TYPE=ARENA+0x1000;VT=ARENA+0x2000;RULES=ARENA+0x4000
class TechnoThreatOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(ARENA,SIZE);self.active=False;self.counts=Counter();self.u.hook_add(UC_HOOK_CODE,self.code)
 def va(self,a):return a
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  assert any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected Techno threat instruction',hex(a))
  if a in RANGES:self.counts[hex(a)]+=1
  if a==0x6c12c0:self.trace.extend(('E','128'))
  if a in (0x509800,0x453c40):self.trace.extend(('E','44'))
 def run(self,f):
  u=self.u;u.mem_write(ARENA,b'\xa5'*SIZE);self.put(ACTOR,VT);self.put(VT+0x80,0x6c12c0);self.put(VT+0x84,0x453c60 if f['kind']==6 else 0x506950);self.put(VT+0x2c,0x453c40 if f['kind']==6 else 0x509800)
  for off in (0x418,0x5a8):self.put(ACTOR+off,TYPE if f['present'] else 0)
  self.put(ACTOR+0x564,f['field']);self.put(TYPE+0x598,f['value']);self.put(RULES+0xbe8,f['multiplier']);self.put(0x839848,RULES)
  before=bytes(u.mem_read(ARENA,SIZE));glob=bytes(u.mem_read(0x839848,4));self.trace=[];self.active=True
  try:self.checked_call(0x4532f0 if f['root'] else 0x6d3e50,[],ACTOR,inputs=list(RANGES.items()))
  finally:self.active=False
  assert bytes(u.mem_read(ARENA,SIZE))==before and bytes(u.mem_read(0x839848,4))==glob
  from unicorn.x86_const import UC_X86_REG_EAX
  value=u.reg_read(UC_X86_REG_EAX);value=value if value<2**31 else value-2**32
  return self.trace+['R',str(value)]
