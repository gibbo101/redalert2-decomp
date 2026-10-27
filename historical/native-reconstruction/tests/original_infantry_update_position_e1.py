# SPDX-License-Identifier: GPL-3.0-or-later
"""Unmodified complete500AA0 on the bounded ordinary-E1 argument-2 path."""
import struct
from collections import Counter
from original_presentation import PresentationOracle,STACK,STOP
from verify_infantry_update_position_e1 import verify,START,END,HELPERS
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_EDI,UC_X86_REG_EIP,UC_X86_REG_ESP
ARENA=0x3900000;SIZE=0x10000;ACTOR=ARENA+0x1000;TYPE=ARENA+0x2000;TARGET=ARENA+0x4000
LOCOMOTOR=ARENA+0x5000;CURRENT=ARENA+0x6000;TARGET_CELL=ARENA+0x7000
SERVICES={0x548000,0x5d51e0,0x47ba50,0x594c50,0x6d5e90,0x6d5c30,0x54a550,0x4c7220}
def pack(*v):return struct.pack('<'+'I'*len(v),*[x&0xffffffff for x in v])
class InfantryUpdatePositionE1Oracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(ARENA,SIZE);self.active=False;self.counts=Counter();self.u.hook_add(UC_HOOK_CODE,self.code)
 def va(self,a):return a
 def word(self,p):return struct.unpack('<I',self.u.mem_read(p,4))[0]
 def signed(self,v):return v if v<2**31 else v-2**32
 def ret(self,n,value=0):
  u=self.u;sp=u.reg_read(UC_X86_REG_ESP);u.reg_write(UC_X86_REG_EAX,value&0xffffffff);u.reg_write(UC_X86_REG_EIP,self.word(sp));u.reg_write(UC_X86_REG_ESP,sp+4+n)
 def point(self,p):return tuple(struct.unpack('<iii',self.u.mem_read(p,12)))
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  if a==0x501bfd:self.trace.extend(('V','1',str(self.word(u.reg_read(UC_X86_REG_EDI)+0xec))));return
  if START<=a<END:return
  if any(lo<=a<lo+size for lo,size in HELPERS.items()):
   if a==0x594770:self.trace.extend(('m',str(self.signed(self.word(ACTOR+0x98)))));self.counts['mission']+=1
   elif a==0x4717b0:self.trace.extend(('6',str(1 if u.reg_read(UC_X86_REG_ECX)==CURRENT else 2)))
   elif a in (0x473e30,0x473e80):self.trace.extend(('1' if a==0x473e30 else '2',str(1 if u.reg_read(UC_X86_REG_ECX)==CURRENT else 2),str(self.word(u.reg_read(UC_X86_REG_ESP)+4)&255)))
   elif a==0x47cf80:self.trace.extend(('K','11'))
   elif a==0x71dea0:self.trace.extend(('L','1'))
   return
  if a not in SERVICES:raise AssertionError(('Uninspected Infantry E1 update child',hex(a),'from',hex(self.word(u.reg_read(UC_X86_REG_ESP)))))
  self.counts['supplied.'+hex(a)]+=1;sp=u.reg_read(UC_X86_REG_ESP)
  if a==0x548000:
   q=self.point(self.word(sp+4));self.trace.extend(('C',*map(str,q)));self.ret(4,CURRENT if q==self.current else TARGET_CELL);return
  if a==0x5d51e0:self.ret(0,CURRENT);return
  if a==0x47ba50:
   out=self.word(sp+4);u.mem_write(out,pack(*self.target));self.trace.extend(('T',*map(str,self.target)));self.ret(4,out);return
  if a==0x594c50:self.trace.append('M');self.ret(0);return
  if a in (0x6d5e90,0x6d5c30):
   self.trace.extend(('R' if a==0x6d5e90 else 'A',*[str(self.word(sp+4+i*4)) for i in range(4)]));self.ret(16);return
  if a==0x54a550:
   q=self.point(self.word(sp+4));self.trace.extend(('P',*map(str,q),str(self.word(sp+8)),str(self.signed(self.word(sp+12))),str(self.word(sp+16))));self.ret(16);return
  self.trace.extend(('U',str(self.signed(self.word(sp+4)))));self.ret(4)
 def run(self,f):
  u=self.u;u.mem_write(ARENA,bytes(SIZE));self.current=(f['x'],f['y'],f['z']);self.target=(f['tx'],f['ty'],f['tz'])
  self.put(ACTOR,0x7a3540);u.mem_write(ACTOR+0x88,pack(*self.current));self.put(ACTOR+0x98,2);self.put(ACTOR+0xa0,f['queued']);self.put(ACTOR+0x494,TARGET);self.put(ACTOR+0x5a8,TYPE);self.put(ACTOR+0x564,LOCOMOTOR);self.put(ACTOR+0x1f4,f['range'])
  u.mem_write(ACTOR+0x79,bytes([f['bridge']]));u.mem_write(ACTOR+0x7d,bytes([f['onMap']]));self.put(TARGET,0x79db04);self.put(LOCOMOTOR,0x7aead8);u.mem_write(LOCOMOTOR+0x30,b'\1');self.put(CURRENT+0xec,7);self.put(TARGET_CELL+0xec,9);self.put(CURRENT+0xe4,0);self.put(TARGET_CELL+0xe4,0);self.put(0xa40958,1)
  self.trace=[];self.active=True
  try:self.checked_call(START,[2],ACTOR,writes=[],inputs=[(ACTOR,0x600),(TYPE,0xd00),(TARGET,0x100),(LOCOMOTOR,0x100),(CURRENT,0x200),(TARGET_CELL,0x200)])
  finally:self.active=False
  self.counts[hex(START)]+=1;return self.trace
