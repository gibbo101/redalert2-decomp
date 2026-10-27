# SPDX-License-Identifier: GPL-3.0-or-later
"""Unmodified caller/setter prefix and complete base4717B0 traversal."""
import struct
from collections import Counter
from original_presentation import PresentationOracle,STACK,STOP
from verify_cell_resident_kind6 import verify,PREFIX,HELPER,CALLERS
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import (UC_X86_REG_EAX,UC_X86_REG_EBX,UC_X86_REG_EBP,
 UC_X86_REG_ECX,UC_X86_REG_EDI,UC_X86_REG_EIP,UC_X86_REG_ESI,UC_X86_REG_ESP)

ARENA=0x3d00000;SIZE=0x10000;CELL=ARENA+0x100;VTABLE=ARENA+0x400
RESIDENTS=[ARENA+0x1000+i*0x100 for i in range(32)]
STUBS=(0x6e8510,0x6e7eb0);KIND=0x594770
def pack(value):return struct.pack('<I',value&0xffffffff)
class CellResidentKind6Oracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(ARENA,SIZE)
  self.active='';self.trace=[];self.kinds=[];self.counts=Counter();self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.write)
 def va(self,address):return address
 def word(self,address):return struct.unpack('<I',self.u.mem_read(address,4))[0]
 def resident(self,p):return RESIDENTS.index(p) if p in RESIDENTS else -1
 def ret(self,n,value=0):
  sp=self.u.reg_read(UC_X86_REG_ESP);self.u.reg_write(UC_X86_REG_EAX,value&0xffffffff)
  self.u.reg_write(UC_X86_REG_EIP,self.word(sp));self.u.reg_write(UC_X86_REG_ESP,sp+4+n)
 def write(self,u,access,p,n,value,_):
  if self.active=='caller':
   if not (STACK-0x2000<=p and p+n<=STACK+0x100) and (p,n)!=(0xa40958,1):raise AssertionError(('Unexpected setter-prefix write',hex(p),n))
   if (p,n)==(0xa40958,1):self.trace.extend(('W',str(value&255)));self.counts['setter_store']+=1
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  if self.active=='caller':
   if a in STUBS:self.counts['supplied.'+hex(a)]+=1;self.ret(4,0x12345678);return
   if a==PREFIX[1]:
    sp=u.reg_read(UC_X86_REG_ESP)
    for reg,off in ((UC_X86_REG_EDI,0),(UC_X86_REG_ESI,4),(UC_X86_REG_EBP,8),(UC_X86_REG_EBX,12)):u.reg_write(reg,self.word(sp+off))
    u.reg_write(UC_X86_REG_EAX,1);u.reg_write(UC_X86_REG_EIP,self.word(sp+0x120));u.reg_write(UC_X86_REG_ESP,sp+0x124);return
   if any(lo<=a<hi for lo,hi in (PREFIX,self.current_caller)):return
   raise AssertionError(('Uninspected setter caller instruction',hex(a)))
  if a==KIND:
   i=self.resident(u.reg_read(UC_X86_REG_ECX));assert i>=0
   self.trace.extend(('K',str(i),str(self.kinds[i])));self.counts['kind']+=1;self.ret(0,self.kinds[i]);return
  if HELPER[0]<=a<HELPER[1]:
   if a==HELPER[0]:self.counts[hex(HELPER[0])]+=1
   if a==0x4717d0:
    i=self.resident(u.reg_read(UC_X86_REG_ESI));next_=self.word(RESIDENTS[i]+0x30);self.trace.extend(('N',str(i),str(self.resident(next_))));self.counts['next']+=1
   return
  raise AssertionError(('Uninspected Cell resident instruction',hex(a)))
 def initialize(self,mode):
  self.current_caller=CALLERS[mode-1];start,end=self.current_caller
  preserved={UC_X86_REG_EBX:0x12345678,UC_X86_REG_ESI:0x23456789,UC_X86_REG_EDI:0x3456789a,UC_X86_REG_EBP:0x456789ab}
  for reg,value in preserved.items():self.u.reg_write(reg,value)
  self.u.reg_write(UC_X86_REG_ESP,STACK);self.u.reg_write(UC_X86_REG_ECX,0x87654321);self.u.mem_write(0x7d3338,b'\xa5');self.put(0xa3d290,ARENA+0x8000)
  self.active='caller'
  try:u=self.u;u.emu_start(start,end,count=100)
  finally:self.active=''
  if u.reg_read(UC_X86_REG_EIP)!=end:raise AssertionError('Setter caller did not reach boundary')
  if any(u.reg_read(reg)!=value for reg,value in preserved.items()):raise AssertionError('Setter prefix changed callee-saved register')
  self.counts['caller'+str(mode)]+=1
 def run(self,initial,mode,kinds):
  u=self.u;u.mem_write(ARENA,bytes(SIZE));u.mem_write(0xa40958,bytes([initial]));self.trace=[];self.kinds=kinds
  if mode:self.initialize(mode)
  self.trace.extend(('S',str(u.mem_read(0xa40958,1)[0])))
  self.put(CELL+0xe4,RESIDENTS[0] if kinds else 0);self.put(VTABLE+0x2c,KIND)
  for i,kind in enumerate(kinds):
   self.put(RESIDENTS[i],VTABLE);self.put(RESIDENTS[i]+0x30,RESIDENTS[i+1] if i+1<len(kinds) else 0)
  self.active='helper'
  try:self.checked_call(HELPER[0],ecx=CELL,writes=[],inputs=[(0xa40958,1),(CELL,0xe8),(VTABLE,0x30),*[(RESIDENTS[i],0x34) for i in range(len(kinds))]])
  finally:self.active=''
  result=self.resident(u.reg_read(UC_X86_REG_EAX));self.trace.extend(('R',str(result)))
  return self.trace
