# SPDX-License-Identifier: GPL-3.0-or-later
"""Unmodified complete base Techno old-sight removal."""
import struct
from collections import Counter
from original_presentation import PresentationOracle,STOP
from verify_techno_sight_removal import verify,START,SIZE
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_ECX,UC_X86_REG_EIP,UC_X86_REG_ESP
ARENA=0x3710000;TOTAL=0x5000;ACTOR=ARENA;OWNER=ARENA+0x1000;COUNTRY=ARENA+0x2000;HOUSE2=ARENA+0x3000
class TechnoSightRemovalOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(ARENA,TOTAL);self.active=False;self.counts=Counter();self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.store)
 def va(self,a):return a
 def word(self,p):return struct.unpack('<I',self.u.mem_read(p,4))[0]
 def signed(self,v):return v if v<2**31 else v-2**32
 def ret(self,n=0):
  u=self.u;sp=u.reg_read(UC_X86_REG_ESP);target=self.word(sp);u.reg_write(UC_X86_REG_ESP,sp+4+n);u.reg_write(UC_X86_REG_EIP,target)
 def house(self,p):assert p in (OWNER,HOUSE2);return 1 if p==OWNER else 2
 def store(self,u,access,p,n,value,_):
  if self.active and p==ACTOR+0x1e4:self.trace.extend(('A',str(value&0xff)))
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  if a==0x54a110:
   sp=u.reg_read(UC_X86_REG_ESP);args=struct.unpack('<8I',u.mem_read(sp+4,32));x,y,z=struct.unpack('<iii',u.mem_read(args[0],12));self.trace.extend(('C',str(x),str(y),str(z),str(self.signed(args[1])),str(self.house(args[2])),*[str(v) for v in args[3:]]));self.counts['supplied.reveal54A110']+=1;self.ret(32);return
  assert START<=a<START+SIZE,('Uninspected Techno sight-removal instruction',hex(a))
  if a==START:self.counts[hex(START)]+=1
 def run(self,f):
  u=self.u;u.mem_write(ARENA,b'\xa5'*TOTAL);self.put(ACTOR+0x1b4,OWNER);self.put(OWNER+0x34,COUNTRY);u.mem_write(ACTOR+0x32d,bytes([f['enabled']]));u.mem_write(COUNTRY+0x1a6,bytes([f['countryFlag']]));u.mem_write(ACTOR+0x1e4,bytes([f['active']]));u.mem_write(ACTOR+0x1e8,struct.pack('<iiii',f['x'],f['y'],f['z'],f['range']))
  before=bytearray(u.mem_read(ARENA,TOTAL));self.trace=[];self.active=True
  writes=[(ACTOR+0x1e4,1)];inputs=[(START,SIZE),(ACTOR,0x1e4),(ACTOR+0x1e5,3),(ACTOR+0x1f8,0x208),(OWNER,0x1000),(COUNTRY,0x1000),(HOUSE2,0x1000)]
  try:self.checked_call(START,[f['arg1'],f['arg2'],f['arg3'],HOUSE2 if f['house'] else 0],ecx=ACTOR,writes=writes,inputs=inputs)
  finally:self.active=False
  after=bytearray(u.mem_read(ARENA,TOTAL));before[0x1e4]=after[0x1e4];assert after==before;self.trace.extend(('S',str(u.mem_read(ACTOR+0x1e4,1)[0])));return self.trace
