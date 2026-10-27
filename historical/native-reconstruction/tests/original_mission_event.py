# SPDX-License-Identifier: GPL-3.0-or-later
"""Unchanged original complete event roots; no instruction patches/stub calls."""
import struct
from collections import Counter
from original_presentation import PresentationOracle,STOP
from verify_mission_event import verify,RANGES
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX
ARENA=0x2800000;SIZE=0x4000;EVENT=ARENA;TIMER=ARENA+0x100;HOUSE_LIST=ARENA+0x200
def signed(v):return v if v<0x80000000 else v-0x100000000
class MissionEventOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True)
  self.u.mem_map(ARENA,SIZE);self.active=False;self.counts=Counter();self.u.hook_add(UC_HOOK_CODE,self.code)
 def va(self,a):return a
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  assert any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected mission instruction',hex(a))
  if a in (0x6e6050,0x6e60b8,0x6e61c3,0x6e6256,0x6e66a5,0x6e66f9):self.counts[hex(a)]+=1
  if a==0x4ed760:self.events.extend(('H',str(signed(u.reg_read(UC_X86_REG_ECX)))));self.counts['house_lookup']+=1
  if a==0x4ed78c:
   ptr=u.reg_read(UC_X86_REG_EAX);self.events.extend(('I',str(self.houses.index(ptr) if ptr else -1)))
 def run(self,kind,value,pulse,suppress,frame,start,remaining,houses):
  u=self.u;u.mem_write(ARENA,b'\xa5'*SIZE);self.put(EVENT+0x2c,kind);self.put(EVENT+0x34,value)
  self.put(TIMER,start);self.put(TIMER+8,remaining);self.put(0xa40d2c,frame);u.mem_write(0xa40d13,bytes([suppress]))
  self.houses=[ARENA+0x400+i*0x100 for i in range(len(houses))]
  for i,(ptr,country) in enumerate(zip(self.houses,houses)):
   self.put(HOUSE_LIST+4*i,ptr);self.put(ptr+0x34,ARENA+0x2000+i*0x100);self.put(ARENA+0x2000+i*0x100+0xb8,country)
  self.put(0xa3229c,HOUSE_LIST);self.put(0xa322a8,len(houses));self.events=[];self.active=True
  try:self.checked_call(0x6e6050,[pulse,0,0,TIMER,ARENA+0x180,0],EVENT,
   inputs=[(ARENA,SIZE),(0xa40d2c,4),(0xa40d13,1),(0xa3229c,4),(0xa322a8,4)])
  finally:self.active=False
  self.counts['kind'+str(kind)]+=1;self.events.extend(('R',str(u.reg_read(UC_X86_REG_EAX)&255)))
  return self.events
