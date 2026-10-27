# SPDX-License-Identifier: GPL-3.0-or-later
"""Unmodified6328F0 + actual intersection/FTOL; dimension/queue probes explicit."""
import struct
from original_presentation import PresentationOracle,STOP
from verify_radar_cell_notification import verify,RANGES
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EIP
BASE=0x3f00000;SIZE=0x10000;MAP=BASE;SURFACE=BASE+0x3000;VT=BASE+0x4000;POINT=BASE+0x5000;STUB=BASE+0x6000
class RadarCellNotificationOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(BASE,SIZE);self.active=False;self.u.hook_add(UC_HOOK_CODE,self.code)
 def va(self,p):return p
 def word(self,p):return struct.unpack('<I',self.u.mem_read(p,4))[0]
 def ret(self,argc,value=0):
  sp=self.u.reg_read(UC_X86_REG_ESP);self.u.reg_write(UC_X86_REG_EAX,value&0xffffffff);self.u.reg_write(UC_X86_REG_EIP,self.word(sp));self.u.reg_write(UC_X86_REG_ESP,sp+4+argc*4)
 def emit(self,*v):self.trace.extend(map(str,v))
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  if a in (STUB,STUB+16):
   assert u.reg_read(UC_X86_REG_ECX)==SURFACE;value=self.width if a==STUB else self.height;self.emit('W' if a==STUB else 'H',value);self.ret(0,value);return
  if a==0x632620:
   assert u.reg_read(UC_X86_REG_ECX)==MAP;sp=u.reg_read(UC_X86_REG_ESP);point=self.word(sp+4);self.emit('Q',*struct.unpack('<2i',u.mem_read(point,8)));self.ret(1);return
  assert any(p<=a and a+n<=p+size for p,size in RANGES.items()),('Uninspected notification instruction',hex(a))
 def run(self,f):
  present,x,y,mw,ox,oy,rw,rh,scale,self.width,self.height=f
  self.u.mem_write(BASE,bytes(SIZE));self.put(MAP+0x1218,SURFACE if present else 0);self.put(SURFACE,VT);self.put(VT+0x7c,STUB);self.put(VT+0x80,STUB+16)
  for off,v in [(0x100,mw),(0x148c,ox),(0x1494,oy),(0x123c,rw),(0x1240,rh),(0x1484,scale)]:self.put(MAP+off,v)
  self.u.mem_write(POINT,struct.pack('<2h',x,y));self.trace=[];self.active=True
  try:self.checked_call(0x6328f0,[POINT],MAP,inputs=[*RANGES.items(),(BASE,SIZE)])
  finally:self.active=False
  return self.trace+['Z']
