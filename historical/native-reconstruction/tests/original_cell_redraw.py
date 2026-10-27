# SPDX-License-Identifier: GPL-3.0-or-later
"""Unmodified complete sight redraw parent, explicit center and height probes."""
import struct
from original_presentation import PresentationOracle,STOP
from verify_cell_redraw import verify,RANGES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EIP
BASE=0x3e00000;SIZE=0x10000;OBJ=BASE;CELL=BASE+0x4000
class CellRedrawOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(BASE,SIZE);self.active=False;self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.write)
 def va(self,p):return p
 def word(self,p):return struct.unpack('<I',self.u.mem_read(p,4))[0]
 def ret(self,argc,value=0):
  sp=self.u.reg_read(UC_X86_REG_ESP);self.u.reg_write(UC_X86_REG_EAX,value&0xffffffff);self.u.reg_write(UC_X86_REG_EIP,self.word(sp));self.u.reg_write(UC_X86_REG_ESP,sp+4+argc*4)
 def emit(self,*v):self.trace.extend(map(str,v))
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  if a==0x475d60:
   assert u.reg_read(UC_X86_REG_ECX)==CELL;sp=u.reg_read(UC_X86_REG_ESP);out=self.word(sp+4);self.emit('C',*self.xyz);u.mem_write(out,struct.pack('<3i',*self.xyz));self.ret(1,out);return
  if a==0x6a2970:assert u.reg_read(UC_X86_REG_ECX)==0;self.emit('H',0);self.ret(0,self.height);return
  assert any(p<=a and a+n<=p+size for p,size in RANGES.items()),('Uninspected Cell redraw instruction',hex(a))
 def write(self,u,access,p,n,value,_):
  if not self.active or not BASE<=p<BASE+SIZE:return
  if p==CELL+0x5c:assert n==4;self.emit('F',signed(value));return
  if p==CELL+0x138:assert n==1;self.emit('R',value);return
  if p==OBJ+0xe0:assert n==4;self.emit('N',signed(value));return
  if p==OBJ+0xd7d:assert n==1;self.emit('D',value);return
  assert OBJ+0xe4<=p<OBJ+0xe4+800*4 and n==4 and (p-OBJ-0xe4)%4==0
  assert value==CELL;self.emit('Q',(p-OBJ-0xe4)//4,7)
 def run(self,f):
  loading,frame,last,flags,redraw,x,y,z,height,ox,oy,vx,vy,vw,vh,count,dirty=f
  self.u.mem_write(BASE,bytes(SIZE));self.xyz=(x,y,z);self.height=height;self.trace=[]
  for p,v in [(0x8324ec,loading),(0xa40d2c,frame),(CELL+0x5c,last),(CELL+0x12c,flags),(OBJ+0xb0,ox),(OBJ+0xb4,oy),(OBJ+0xe0,count),(0x839630,vx),(0x839634,vy),(0x839638,vw),(0x83963c,vh)]:self.put(p,v)
  self.u.mem_write(CELL+0x138,bytes([redraw]));self.u.mem_write(OBJ+0xd7d,bytes([dirty]))
  for i in range(800):self.put(OBJ+0xe4+i*4,1000+i)
  self.active=True
  try:self.checked_call(0x6aadd0,[CELL],OBJ,writes=[(CELL+0x5c,4),(CELL+0x138,1),(OBJ+0xe0,4),(OBJ+0xe4,3200),(OBJ+0xd7d,1)],inputs=[*RANGES.items(),(CELL+0x12c,4),(OBJ+0xb0,8)])
  finally:self.active=False
  cells=[self.word(OBJ+0xe4+i*4) for i in range(800)];cells=[7 if n==CELL else n for n in cells]
  self.emit('Z',signed(self.word(CELL+0x5c)),self.u.mem_read(CELL+0x138,1)[0],signed(self.word(OBJ+0xe0)),self.u.mem_read(OBJ+0xd7d,1)[0],*cells)
  return self.trace

def signed(v):return (v+2**31)%2**32-2**31
