# SPDX-License-Identifier: GPL-3.0-or-later
"""Execute unmodified complete471760 with authored shared resident records."""
from collections import Counter
from original_cell_resident_kind6 import ARENA,SIZE,CELL,VTABLE,RESIDENTS,KIND
from original_presentation import PresentationOracle,STOP
from verify_cell_resident_search import verify,HELPER
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESI,UC_X86_REG_ESP,UC_X86_REG_EIP
class CellResidentSearchOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(ARENA,SIZE);self.active=False;self.counts=Counter();self.u.hook_add(UC_HOOK_CODE,self.code)
 def va(self,a):return a
 def word(self,a):return int.from_bytes(self.u.mem_read(a,4),'little')
 def resident(self,p):return RESIDENTS.index(p) if p in RESIDENTS else -1
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  if a==KIND:
   i=self.resident(u.reg_read(UC_X86_REG_ECX));assert i>=0
   self.trace.extend(('K',str(i),str(self.kinds[i])));self.counts['kind']+=1
   sp=u.reg_read(UC_X86_REG_ESP);u.reg_write(UC_X86_REG_EAX,self.kinds[i]&0xffffffff);u.reg_write(UC_X86_REG_EIP,self.word(sp));u.reg_write(UC_X86_REG_ESP,sp+4);return
  assert HELPER[0]<=a and a+n<=HELPER[1],('Uninspected resident instruction',hex(a))
  if a==HELPER[0]:self.counts['roots']+=1
  if a==0x471794:
   i=self.resident(u.reg_read(UC_X86_REG_ESI));self.trace.extend(('N',str(i),str(self.resident(self.word(RESIDENTS[i]+0x30)))));self.counts['next']+=1
 def run(self,initial,selector,requested,split,kinds):
  u=self.u;u.mem_write(ARENA,b'\xa5'*SIZE);u.mem_write(0xa40958,bytes([initial]));self.trace=['S',str(initial)];self.kinds=kinds
  self.put(CELL+0xe4,RESIDENTS[0] if split else 0);self.put(CELL+0xe8,RESIDENTS[split] if split<len(kinds) else 0);self.put(VTABLE+0x2c,KIND)
  for i in range(len(kinds)):
   self.put(RESIDENTS[i],VTABLE);self.put(RESIDENTS[i]+0x30,RESIDENTS[i+1] if i+1<len(kinds) and i+1!=split else 0)
  self.active=True
  try:self.checked_call(HELPER[0],[requested,selector],CELL,writes=[],inputs=[HELPER[:1]+(HELPER[1]-HELPER[0],),(0xa40958,1),(ARENA,SIZE)])
  finally:self.active=False
  self.trace.extend(('R',str(self.resident(u.reg_read(UC_X86_REG_EAX)))));return self.trace
