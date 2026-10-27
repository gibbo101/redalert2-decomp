# SPDX-License-Identifier: GPL-3.0-or-later
"""Unmodified complete508530 -> 6C1380 ordinary Infantry null-target path."""
import struct
from collections import Counter
from original_presentation import PresentationOracle,STOP
from verify_infantry_weapon_selection import verify,RANGES,HELPERS
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ESP

ARENA=0x3d00000;SIZE=0x100000;ACTOR=ARENA+0x1000;TYPE=ARENA+0x3000
NORMAL=(ARENA+0x8000,ARENA+0x9000);ELITE=(ARENA+0xa000,ARENA+0xb000)
class InfantryWeaponSelectionOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True)
  self.u.mem_map(ARENA,SIZE);self.active=False;self.trace=[];self.counts=Counter();self.u.hook_add(UC_HOOK_CODE,self.code)
 def va(self,a):return a
 def word(self,p):return struct.unpack('<I',self.u.mem_read(p,4))[0]
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  allowed={**RANGES,**HELPERS}
  if not any(lo<=a<lo+size for lo,size in allowed.items()):
   raise AssertionError(('Uninspected Infantry weapon-selection instruction',hex(a),'from',hex(self.word(u.reg_read(UC_X86_REG_ESP)))))
  if a in RANGES:self.counts[hex(a)]+=1
  if a==0x506950:self.trace.append('T');self.counts['type']+=1
  elif a==0x6d8540:self.counts['weapon']+=1
  elif a==0x713420:self.counts['elite']+=1
  elif a==0x6df5c0:self.counts['normal-slot']+=1
  elif a==0x6df5e0:self.counts['elite-slot']+=1
  elif a==0x594770:self.trace.extend(('M',str(self.word(ACTOR+0x98))));self.counts['mission']+=1
  elif a==0x509800:self.counts['kind']+=1
 def run(self,f):
  u=self.u;u.mem_write(ARENA,bytes(SIZE));u.mem_write(ACTOR,bytes(0x700));u.mem_write(TYPE,bytes(0xc00))
  self.put(ACTOR,0x7a3540);self.put(ACTOR+0x5a8,TYPE);self.put(ACTOR+0x5ac,f['state']);self.put(ACTOR+0x10c,-1)
  u.mem_write(ACTOR+0x118,struct.pack('<Q',f['rank']));self.put(ACTOR+0x98,f['mission']);self.put(TYPE+0x704,0)
  for index,present in enumerate((f['normalPrimary'],f['normalSecondary'])):self.put(TYPE+0x74c+index*28,NORMAL[index] if present else 0)
  for index,present in enumerate((f['elitePrimary'],f['eliteSecondary'])):self.put(TYPE+0x8f4+index*28,ELITE[index] if present else 0)
  u.mem_write(NORMAL[1]+0x112,bytes([f['normalNever']]));u.mem_write(NORMAL[1]+0x126,bytes([f['normalArea']]))
  u.mem_write(ELITE[1]+0x112,bytes([f['eliteNever']]));u.mem_write(ELITE[1]+0x126,bytes([f['eliteArea']]))
  self.trace=[];self.active=True
  try:self.checked_call(0x508530,[0],ACTOR,writes=[],inputs=[(ACTOR,0x700),(TYPE,0xc00),(NORMAL[0],0x200),(NORMAL[1],0x200),(ELITE[0],0x200),(ELITE[1],0x200)]);result=u.reg_read(UC_X86_REG_EAX)
  finally:self.active=False
  self.trace.extend(('R',str(result if result<2**31 else result-2**32)));return self.trace
