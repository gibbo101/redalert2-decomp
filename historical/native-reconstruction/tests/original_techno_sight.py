# SPDX-License-Identifier: GPL-3.0-or-later
"""Unmodified base Techno sight with actual type/timer/FTOL children."""
import struct
from collections import Counter
from original_presentation import PresentationOracle,STOP
from verify_techno_sight import verify,RANGES,TABLES
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import (UC_X86_REG_EAX,UC_X86_REG_EBX,UC_X86_REG_ECX,
    UC_X86_REG_EDX,UC_X86_REG_EIP,UC_X86_REG_ESP,UC_X86_REG_ESI)

ARENA=0x3300000;SIZE=0x9000;ACTOR=ARENA;OWNER=ARENA+0x1000
COUNTRY=ARENA+0x2000;TYPE=ARENA+0x3000;RULES=ARENA+0x5000;HOUSE2=ARENA+0x7000

def signed(v):return v if v<2**31 else v-2**32
class TechnoSightOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True)
  self.u.mem_map(ARENA,SIZE);self.active=False;self.counts=Counter();self.u.hook_add(UC_HOOK_CODE,self.code)
 def va(self,a):return a
 def word(self,p):return struct.unpack('<I',self.u.mem_read(p,4))[0]
 def ret(self,n,value=0):
  u=self.u;sp=u.reg_read(UC_X86_REG_ESP);target=self.word(sp)
  u.reg_write(UC_X86_REG_ESP,sp+4+n);u.reg_write(UC_X86_REG_EAX,value&0xffffffff);u.reg_write(UC_X86_REG_EIP,target)
 def house_id(self,p):
  assert p in (OWNER,HOUSE2);return 1 if p==OWNER else 2
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  if a==0x54a110:
   assert u.reg_read(UC_X86_REG_ECX)==0x8324e0
   sp=u.reg_read(UC_X86_REG_ESP);args=struct.unpack('<8I',u.mem_read(sp+4,32));point=args[0]
   x,y,z=struct.unpack('<iii',u.mem_read(point,12))
   self.trace.extend(('C',str(x),str(y),str(z),str(signed(args[1])),str(self.house_id(args[2])),
    str(args[3]),str(args[4]),str(args[5]),str(args[6]),str(args[7])))
   self.counts['supplied.reveal54A110']+=1;self.ret(32);return
  assert any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected Techno sight instruction',hex(a))
  if a in RANGES:self.counts[hex(a)]+=1
  if a==0x6d5c97:self.trace.extend(('H',str(struct.unpack('<b',bytes([u.reg_read(UC_X86_REG_EAX)&255]))[0])))
  elif a==0x6c12c0:self.trace.append('T')
  elif a in (0x77f135,0x77f14c):self.trace.extend(('F',str(signed(u.reg_read(UC_X86_REG_EAX)))))
  elif a==0x7133a0:self.trace.append('V')
  elif a==0x713420:self.trace.append('E')
  elif a==0x6d5d3c:self.trace.append('M')
  elif a==0x6d5d81:self.trace.extend(('A','1'))
  elif a==0x6d5d88:self.trace.extend(('X',str(signed(u.reg_read(UC_X86_REG_EAX)))))
  elif a==0x6d5d8a:self.trace.extend(('R',str(signed(u.reg_read(UC_X86_REG_EBX)))))
  elif a==0x6d5d93:self.trace.extend(('Y',str(signed(u.reg_read(UC_X86_REG_EAX)))))
  elif a==0x6d5d99:self.trace.extend(('Z',str(signed(u.reg_read(UC_X86_REG_EDX)))))
 def run(self,f):
  u=self.u;u.mem_write(ARENA,b'\xa5'*SIZE)
  self.put(ACTOR,0x7addf8);self.put(ACTOR+0x1b4,OWNER);self.put(OWNER+0x34,COUNTRY);self.put(ACTOR+0x5ac,TYPE);self.put(0x839848,RULES)
  u.mem_write(ACTOR+0x32d,bytes([f['enabled']]));u.mem_write(COUNTRY+0x1a6,bytes([f['countryFlag']]))
  u.mem_write(ACTOR+0x88,struct.pack('<iii',f['x'],f['y'],f['z']));u.mem_write(ACTOR+0x118,struct.pack('<Q',f['timerBits']))
  u.mem_write(ACTOR+0x378,struct.pack('<b',f['increase']));u.mem_write(ACTOR+0x1e4,bytes([f['active']]))
  u.mem_write(ACTOR+0x1e8,struct.pack('<iii',f['lastX'],f['lastY'],f['lastZ']));u.mem_write(ACTOR+0x1f4,struct.pack('<i',f['lastRange']))
  u.mem_write(TYPE+0x271,bytes([f['veteran']]));u.mem_write(TYPE+0x283,bytes([f['elite']]));u.mem_write(TYPE+0x530,struct.pack('<i',f['sight']))
  u.mem_write(RULES+0x5a0,struct.pack('<Q',f['multiplierBits']));u.mem_write(RULES+0x1324,struct.pack('<i',f['divisor']))
  before=bytearray(u.mem_read(ARENA,SIZE));self.trace=[];self.active=True
  writes=[(ACTOR+0x378,1),(ACTOR+0x1e4,1),(ACTOR+0x1e8,12),(ACTOR+0x1f4,4)]
  inputs=[*RANGES.items(),*TABLES.items(),(0x839848,4),(ACTOR,0x1e4),(ACTOR+0x1e5,3),(ACTOR+0x1f8,0x180),(ACTOR+0x379,0x237),(OWNER,0x2000),(TYPE,0x1000),(RULES,0x2000),(HOUSE2,0x1000)]
  try:self.checked_call(0x6d5c30,[f['arg1'],f['arg2'],f['arg3'],HOUSE2 if f['house'] else 0],ecx=ACTOR,writes=writes,inputs=inputs)
  finally:self.active=False
  after=bytearray(u.mem_read(ARENA,SIZE))
  for p,n in writes:before[p-ARENA:p-ARENA+n]=after[p-ARENA:p-ARENA+n]
  assert after==before
  inc=struct.unpack('<b',u.mem_read(ACTOR+0x378,1))[0];active=u.mem_read(ACTOR+0x1e4,1)[0]
  x,y,z=struct.unpack('<iii',u.mem_read(ACTOR+0x1e8,12));r=struct.unpack('<i',u.mem_read(ACTOR+0x1f4,4))[0]
  self.trace.extend(('S',str(inc),str(active),str(x),str(y),str(z),str(r)))
  return self.trace
