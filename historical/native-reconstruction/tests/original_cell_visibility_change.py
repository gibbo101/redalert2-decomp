# SPDX-License-Identifier: GPL-3.0-or-later
"""Unmodified ordinary Cell visibility path with supplied mask/effect children."""
import struct
from collections import Counter
from original_presentation import PresentationOracle,STOP
from verify_cell_visibility_change import verify,RANGES
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_EIP,UC_X86_REG_ESP,UC_X86_REG_ESI

ARENA=0x3600000;SIZE=0x140000;MAP=ARENA;POINT=ARENA+0x2000;RULES=ARENA+0x3000
SLOTS=ARENA+0x10000;CELL=ARENA+0x120000;FALLBACK=0xa6f9f8
def signed(v):return v if v<2**31 else v-2**32
class CellVisibilityChangeOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(ARENA,SIZE);self.active=False;self.counts=Counter();self.u.hook_add(UC_HOOK_CODE,self.code)
 def va(self,a):return a
 def word(self,p):return struct.unpack('<I',self.u.mem_read(p,4))[0]
 def point(self,p):return struct.unpack('<hh',self.u.mem_read(p,4))
 def ret(self,n,value=0):
  u=self.u;sp=u.reg_read(UC_X86_REG_ESP);target=self.word(sp);u.reg_write(UC_X86_REG_ESP,sp+4+n);u.reg_write(UC_X86_REG_EAX,value&0xffffffff);u.reg_write(UC_X86_REG_EIP,target)
 def cid(self,p):
  if p==CELL:return 0
  if p==FALLBACK:return 1
  raise AssertionError(('Unknown Cell',hex(p)))
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  sp=u.reg_read(UC_X86_REG_ESP);ecx=u.reg_read(UC_X86_REG_ECX)
  if a==0x6a8d40:
   p=self.point(self.word(sp+4));mode=self.word(sp+8);assert p==(self.f['x'],self.f['y']) and mode in (0,1);value=self.f['secondaryValue'] if mode else self.f['primaryValue'];self.trace.extend(('V',str(mode),str(value)));self.counts['supplied.visibility6A8D40']+=1;self.ret(8,value);return
  if a==0x6aadd0:
   cell=self.word(sp+4);self.trace.extend(('D',str(self.cid(cell))));self.counts['supplied.redraw6AADD0']+=1;self.ret(4);return
  if a==0x568520:
   cell=self.word(sp+4);house=signed(self.word(sp+8));notify=self.word(sp+12)&255;self.trace.extend(('R',str(self.cid(cell)),str(house),str(notify)));self.counts['supplied.discovery568520']+=1;self.ret(12);return
  if a==0x47be00:
   self.trace.extend(('X',str(self.cid(ecx))));self.counts['supplied.refresh47BE00']+=1;self.ret(0);return
  assert any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected Cell visibility instruction',hex(a))
  if a in RANGES:self.counts[hex(a)]+=1
  if a==0x499fce:
   cell=u.reg_read(UC_X86_REG_EAX);p=self.point(POINT)
   if cell==FALLBACK:self.trace.extend(('B',str(p[0]),str(p[1])))
   self.trace.extend(('L',str(p[0]),str(p[1]),str(self.cid(cell))))
  elif a==0x49a004:self.trace.extend(('G',str(self.cid(u.reg_read(UC_X86_REG_ESI))),str(signed(u.reg_read(UC_X86_REG_EAX)))))
  elif a==0x47c849:self.trace.extend(('C',str(self.cid(ecx)),'0'))
  elif a==0x47c85a:self.trace.extend(('C',str(self.cid(ecx)),str(signed(u.reg_read(UC_X86_REG_EAX)))))
  elif a==0x47c876:self.trace.extend(('F',str(self.cid(ecx)),str(signed(u.reg_read(UC_X86_REG_EAX)))))
  elif a==0x47c893:self.trace.extend(('G',str(self.cid(ecx)),str(signed(u.reg_read(UC_X86_REG_EAX)))))
  elif a==0x47c8ac:self.trace.extend(('C',str(self.cid(ecx)),'0'))
  elif a==0x47c8bd:self.trace.extend(('C',str(self.cid(ecx)),str(signed(u.reg_read(UC_X86_REG_EAX)))))
  elif a==0x47c8cf:self.trace.extend(('C',str(self.cid(ecx)),str(signed(u.reg_read(UC_X86_REG_EAX)))))
  elif a==0x47c8ec:self.trace.extend(('G',str(self.cid(ecx)),str(signed(u.reg_read(UC_X86_REG_EAX)))))
  elif a==0x49a03b:self.trace.extend(('P',str(self.cid(u.reg_read(UC_X86_REG_ESI))),str(u.reg_read(UC_X86_REG_EAX)&255)))
  elif a==0x49a052:self.trace.extend(('F',str(self.cid(u.reg_read(UC_X86_REG_ESI))),str(signed(u.reg_read(UC_X86_REG_EAX)))))
  elif a==0x49a074:self.trace.extend(('S',str(self.cid(u.reg_read(UC_X86_REG_ESI))),str(u.reg_read(UC_X86_REG_ECX)&255)))
  elif a==0x49a08d:
   cell=u.reg_read(UC_X86_REG_ESI);self.trace.extend(('G',str(self.cid(cell)),str(signed(self.word(cell+0x140)|1))))
 def run(self,f):
  self.f=f;u=self.u;u.mem_write(ARENA,b'\xa5'*SIZE);u.mem_write(SLOTS,bytes(0x100000));u.mem_write(FALLBACK,b'\xa5'*0x148);u.mem_write(CELL,b'\xa5'*0x148)
  self.put(MAP+0x138,SLOTS);self.put(0x83996c,MAP);self.put(0xa3d290,RULES);self.put(RULES,f['refreshRules']);u.mem_write(POINT,struct.pack('<hh',f['x'],f['y']))
  target=CELL if f['present'] else FALLBACK;index=f['y']*512+f['x']
  if f['present'] and 0<=index<262144:self.put(SLOTS+index*4,CELL)
  for cell in (CELL,FALLBACK):
   u.mem_write(cell+0x120,bytes([f['primary'],f['secondary']]));self.put(cell+0x12c,f['flags12c']);self.put(cell+0x130,f['counter']);self.put(cell+0x134,f['maximum']);self.put(cell+0x140,f['flags140'])
  before_arena=bytearray(u.mem_read(ARENA,SIZE));before_fallback=bytearray(u.mem_read(FALLBACK,0x148));self.trace=[];self.active=True
  writes=[(target+0x120,2),(target+0x12c,4),(target+0x130,4),(target+0x140,4)]
  if target==FALLBACK:writes.append((FALLBACK+0x24,4))
  inputs=[*RANGES.items(),(0x83996c,4),(0xa3d290,4),(MAP,0x200),(RULES,4),(POINT,4),(SLOTS,0x100000)]
  try:self.checked_call(0x62fca0,[POINT,f['house']&0xffffffff,f['finalArgument']],MAP,writes=writes,inputs=inputs)
  finally:self.active=False
  changed=u.reg_read(UC_X86_REG_EAX)&255;after_arena=bytearray(u.mem_read(ARENA,SIZE));after_fallback=bytearray(u.mem_read(FALLBACK,0x148))
  if target==CELL:
   for off,n in ((0x120,2),(0x12c,4),(0x130,4),(0x140,4)):before_arena[CELL-ARENA+off:CELL-ARENA+off+n]=after_arena[CELL-ARENA+off:CELL-ARENA+off+n]
  else:
   for off,n in ((0x24,4),(0x120,2),(0x12c,4),(0x130,4),(0x140,4)):before_fallback[off:off+n]=after_fallback[off:off+n]
  assert after_arena==before_arena and after_fallback==before_fallback
  cell=target;self.trace.extend(('Z',str(changed),str(u.mem_read(cell+0x120,1)[0]),str(u.mem_read(cell+0x121,1)[0]),str(signed(self.word(cell+0x12c))),str(signed(self.word(cell+0x130))),str(signed(self.word(cell+0x140))),str(self.point(FALLBACK+0x24)[0]),str(self.point(FALLBACK+0x24)[1])));return self.trace
