# SPDX-License-Identifier: GPL-3.0-or-later
import struct
from collections import Counter
from original_presentation import PresentationOracle,STOP
from verify_actor_radar_color import verify,RANGES
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP
ARENA=0x3900000;SIZE=0x50000;ACTOR=ARENA+0x100;HOUSES=[ARENA+0x1000+i*0x16000 for i in range(3)]
class ActorRadarColorOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(ARENA,SIZE);self.active=False;self.counts=Counter();self.u.hook_add(UC_HOOK_CODE,self.code)
 def va(self,a):return a
 def word(self,p):return int.from_bytes(self.u.mem_read(p,4),'little')
 def hid(self,p):return -1 if not p else HOUSES.index(p)
 def change(self,p,v):
  self.put(p,v)
  if ARENA<=p<ARENA+SIZE:self.expected[p-ARENA:p-ARENA+4]=struct.pack('<I',v&0xffffffff)
  else:assert p==0xa35db4;self.expectedCurrent=v
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  assert any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected radar actor instruction',hex(a))
  if a in RANGES:self.counts[hex(a)]+=1
  if a==0x4e5540:
   self.saved=(u.reg_read(UC_X86_REG_ECX),self.word(u.reg_read(UC_X86_REG_ESP)+4))
  if a==0x509284:
   self.trace+=list(map(str,('H',self.hid(self.saved[0]),self.hid(self.saved[1]),u.reg_read(UC_X86_REG_EAX)&255)))
   if self.changed or not self.mutation:return
   self.changed=True;m=self.mutation
   if m&1:self.change(ACTOR+0x1b4,HOUSES[2])
   if m&2:self.change(0xa35db4,HOUSES[2])
   if m&4:self.change(ACTOR+0x410,HOUSES[2])
   if m&8:self.change(HOUSES[2]+0x30,0xffffffff);self.change(HOUSES[0]+0x5674,self.word(HOUSES[0]+0x5674)^0xffffffff)
 def run(self,f):
  kind,flag,owner,current,alternate=f[:5];indices=f[5:8];masks=f[8:11];argument,self.mutation=f[11:];u=self.u;u.mem_write(ARENA,b'\xa5'*SIZE)
  self.put(ACTOR+0x170,flag);self.put(ACTOR+0x1b4,HOUSES[owner]);self.put(ACTOR+0x410,0 if alternate<0 else HOUSES[alternate]);self.put(0xa35db4,0 if current<0 else HOUSES[current])
  for i,h in enumerate(HOUSES):self.put(h+0x30,indices[i]);self.put(h+0x5674,masks[i])
  self.expected=bytearray(u.mem_read(ARENA,SIZE));self.expectedCurrent=self.word(0xa35db4);self.trace=[];self.changed=False;self.active=True
  try:
   self.checked_call(0x41b410,[],ACTOR,inputs=RANGES.items());self.trace+=['A',str(u.reg_read(UC_X86_REG_EAX)&255)]
   for i in range(2):self.checked_call(0x41b2e0 if kind else 0x509270,[argument],ACTOR,inputs=RANGES.items());self.trace+=['C',str(self.hid(u.reg_read(UC_X86_REG_EAX)))]
  finally:self.active=False
  assert bytes(u.mem_read(ARENA,SIZE))==self.expected and self.word(0xa35db4)==self.expectedCurrent
  self.trace+=list(map(str,('R',self.hid(self.word(ACTOR+0x1b4)),self.hid(self.word(0xa35db4)),self.hid(self.word(ACTOR+0x410)),int(self.changed))))
  self.trace += [str(int.from_bytes(u.mem_read(h+0x30,4),'little',signed=True)) for h in HOUSES]+[str(self.word(h+0x5674)) for h in HOUSES];return self.trace
