# SPDX-License-Identifier: GPL-3.0-or-later
"""Unchanged complete observer callbacks, no supplied arithmetic children."""
import struct
from original_presentation import PresentationOracle,STOP
from verify_team_observer_weight import verify,RANGES,CONSTANTS
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_FPCW,UC_X86_REG_FPSW
BASE=0x6600000;SIZE=0x3000;ACTOR=BASE+0x100;RULES=BASE+0x1000
class TeamObserverWeightOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(BASE,SIZE);self.active=False;self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.write)
 def va(self,a):return a
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  assert any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected observer instruction',hex(a))
  if a==self.entry:u.reg_write(UC_X86_REG_FPCW,0xe7f if self.f[1] else 0x27f)
 def change(self,a,raw):
  self.u.mem_write(a,raw);self.expected[a-BASE:a-BASE+len(raw)]=raw
 def write(self,u,access,a,n,v,_):
  if not self.active or not BASE<=a<a+n<=BASE+SIZE:return
  off=a-ACTOR;assert (off,n) in ((0xb8,8),(0xb8,4),(0xbc,4),(0x104,4),(0x108,4)),(hex(a),n)
  v&=(1<<(8*n))-1;self.trace.extend(map(str,(off,n,v)));self.expected[a-BASE:a-BASE+n]=v.to_bytes(n,'little')
  if self.mutated:return
  m=self.f[11]
  if n==8 and m==1:
   self.mutated=1;self.change(ACTOR+0x104,struct.pack('<i',2147483647));self.change(ACTOR+0x108,struct.pack('<i',123))
  if n==8 and m==2:
   self.mutated=1;self.change(ACTOR+0xc0,struct.pack('<d',41.25));self.change(ACTOR+0xc8,struct.pack('<d',-12.5))
  if n==4 and off==0xb8 and m==3:
   self.mutated=1;self.change(ACTOR+0xc0,struct.pack('<d',7.125));self.change(ACTOR+0xc8,struct.pack('<d',-3.75))
 def run(self,f):
  self.f=f;self.trace=[];self.mutated=0;u=self.u;u.mem_write(BASE,b'\x5a'*SIZE)
  for a,v in zip((ACTOR+0xb8,ACTOR+0xc0,ACTOR+0xc8,RULES+0xb8,RULES+0xc0,RULES+0xc8),f[4:10]):u.mem_write(a,struct.pack('<Q',v))
  self.put(ACTOR+0x104,f[3]);self.put(ACTOR+0x108,f[2]);self.put(0x839848,ACTOR if f[10] else RULES)
  self.expected=bytearray(u.mem_read(BASE,SIZE));self.entry=0x41dfb0 if f[0] else 0x41e070;self.active=True
  try:
   for _ in range(f[12]):
    top=u.reg_read(UC_X86_REG_FPSW)&0x3800
    self.checked_call(self.entry,ecx=ACTOR,writes=[(BASE,SIZE)],inputs=[*RANGES.items(),*((a,8) for a in CONSTANTS),(0x839848,4)])
    assert u.reg_read(UC_X86_REG_FPCW)==(0xe7f if f[1] else 0x27f) and u.reg_read(UC_X86_REG_FPSW)&0x3800==top
  finally:self.active=False
  assert bytes(u.mem_read(BASE,SIZE))==self.expected,'Unrelated observer arena changed'
  words=[int.from_bytes(u.mem_read(ACTOR+off,n),'little') for off,n in ((0xb8,8),(0xc0,8),(0xc8,8),(0x104,4),(0x108,4))]
  return self.trace+['F',*map(str,words),str(self.mutated)]
