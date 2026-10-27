# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete Cell parent with supplied child mutations of the late scenario input."""
import struct
from original_cell_visibility_change import (CellVisibilityChangeOracle,ARENA,SIZE,MAP,POINT,RULES,SLOTS,CELL,FALLBACK,signed)
from unicorn.x86_const import UC_X86_REG_ESP,UC_X86_REG_EDX,UC_X86_REG_EAX
from verify_cell_visibility_change import RANGES
RULES2=RULES+0x100
class CellVisibilityLiveFlagsOracle(CellVisibilityChangeOracle):
 def code(self,u,a,n,context):
  active=self.active
  sp=u.reg_read(UC_X86_REG_ESP)
  child=self.word(sp+4) if active and a in (0x6aadd0,0x568520) else None
  super().code(u,a,n,context)
  if not active:return
  stage={0x6aadd0:1,0x568520:2}.get(a)
  if stage and stage==self.f['stage']:
   f=self.f;self.mutated=True;self.trace.extend(('M',str(stage),str(f['rebind']),str(f['afterRules'])))
   if f['rebind']:self.put(0xa3d290,RULES2)
   else:self.put(RULES,f['afterRules'])
   flags=self.word(child+0x140)
   if f['cellMode']==1:flags&=~2
   elif f['cellMode']==2:flags|=2
   self.put(child+0x140,flags);self.trace.extend(('H',str(flags)))
  if a==0x49a0d2:
   self.trace.extend(('Q',str(u.reg_read(UC_X86_REG_EDX))));self.counts['late_flags_load']+=1
 def run(self,f):
  self.f=f;u=self.u;u.mem_write(ARENA,b'\xa5'*SIZE);u.mem_write(SLOTS,bytes(0x100000));u.mem_write(FALLBACK,b'\xa5'*0x148);u.mem_write(CELL,b'\xa5'*0x148)
  self.put(MAP+0x138,SLOTS);self.put(0x83996c,MAP);self.put(0xa3d290,RULES);self.put(RULES,f['refreshRules']);self.put(RULES2,f['afterRules']);self.mutated=False;u.mem_write(POINT,struct.pack('<hh',f['x'],f['y']))
  target=CELL if f['present'] else FALLBACK;index=f['y']*512+f['x']
  if f['present'] and 0<=index<262144:self.put(SLOTS+index*4,CELL)
  for cell in (CELL,FALLBACK):
   u.mem_write(cell+0x120,bytes([f['primary'],f['secondary']]));self.put(cell+0x12c,f['flags12c']);self.put(cell+0x130,f['counter']);self.put(cell+0x134,f['maximum']);self.put(cell+0x140,f['flags140'])
  before_arena=bytearray(u.mem_read(ARENA,SIZE));before_fallback=bytearray(u.mem_read(FALLBACK,0x148));self.trace=[];self.active=True
  writes=[(target+0x120,2),(target+0x12c,4),(target+0x130,4),(target+0x140,4)]
  if target==FALLBACK:writes.append((FALLBACK+0x24,4))
  inputs=[*RANGES.items(),(0x83996c,4),(MAP,0x200),(POINT,4),(SLOTS,0x100000)]
  try:self.checked_call(0x62fca0,[POINT,f['house']&0xffffffff,f['finalArgument']],MAP,writes=writes,inputs=inputs)
  finally:self.active=False
  changed=u.reg_read(UC_X86_REG_EAX)&255;after_arena=bytearray(u.mem_read(ARENA,SIZE));after_fallback=bytearray(u.mem_read(FALLBACK,0x148))
  if target==CELL:
   for off,n in ((0x120,2),(0x12c,4),(0x130,4),(0x140,4)):before_arena[CELL-ARENA+off:CELL-ARENA+off+n]=after_arena[CELL-ARENA+off:CELL-ARENA+off+n]
  else:
   for off,n in ((0x24,4),(0x120,2),(0x12c,4),(0x130,4),(0x140,4)):before_fallback[off:off+n]=after_fallback[off:off+n]
  if self.mutated and not f['rebind']:before_arena[RULES-ARENA:RULES-ARENA+4]=struct.pack('<I',f['afterRules'])
  assert after_arena==before_arena and after_fallback==before_fallback
  assert self.word(0xa3d290)==(RULES2 if self.mutated and f['rebind'] else RULES)
  assert self.word(RULES)==(f['afterRules'] if self.mutated and not f['rebind'] else f['refreshRules']) and self.word(RULES2)==f['afterRules']
  self.trace.extend(('Y',str(int(self.word(0xa3d290)==RULES2)),str(self.word(RULES)),str(self.word(RULES2))))
  cell=target;self.trace.extend(('Z',str(changed),str(u.mem_read(cell+0x120,1)[0]),str(u.mem_read(cell+0x121,1)[0]),str(signed(self.word(cell+0x12c))),str(signed(self.word(cell+0x130))),str(signed(self.word(cell+0x140))),str(self.point(FALLBACK+0x24)[0]),str(self.point(FALLBACK+0x24)[1])));return self.trace
