# SPDX-License-Identifier: GPL-3.0-or-later
import struct
from original_presentation import PresentationOracle,STOP,STACK
from verify_tactical_viewport import verify,RANGES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_ECX,UC_X86_REG_EDX,UC_X86_REG_EAX,UC_X86_REG_EIP,UC_X86_REG_ESP
BASE=0x3f00000;SIZE=0x4000;OBJ=BASE
FIELDS=(0xb0,0xb4,0xd80,0xd84,0xd88,0xd8c)
def signed(v):return (v+2**31)%2**32-2**31
class TacticalViewportOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(BASE,SIZE);self.active=False
  self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.write)
 def va(self,p):return p
 def word(self,p):return struct.unpack('<I',self.u.mem_read(p,4))[0]
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  if a==0x591380:
   assert u.reg_read(UC_X86_REG_EDX)==OBJ+0xde4
   sp=u.reg_read(UC_X86_REG_ESP);p=self.word(sp+4);self.trace.extend(['I',*map(str,struct.unpack('<3I',u.mem_read(p,12)))])
   out=u.reg_read(UC_X86_REG_ECX);assert STACK-0x2000<=out and out+12<=STACK
   u.mem_write(out,struct.pack('<3I',*self.output));self.put(0xabe568,self.late[0]);self.put(0xabe56c,self.late[1])
   self.trace.extend(['L',*map(str,self.late)])
   u.reg_write(UC_X86_REG_EAX,out);u.reg_write(UC_X86_REG_EIP,self.word(sp));u.reg_write(UC_X86_REG_ESP,sp+8);return
  assert any(p<=a and a+n<=p+s for p,s in RANGES.items()),('Uninspected viewport instruction',hex(a))
 def write(self,u,access,p,n,v,_):
  if self.active and BASE<=p<BASE+SIZE:
   assert n==4 and p-OBJ in FIELDS
   self.trace.extend(['S',str(p-OBJ),str(signed(v))])
 def run(self,f):
  x,y,w,h,*rest=f;self.output=rest[:3];self.late=rest[3:];self.trace=[];self.u.mem_write(BASE,bytes([0x5a])*SIZE)
  self.put(OBJ+0xd64,x);self.put(OBJ+0xd68,y);self.put(0xabe568,w);self.put(0xabe56c,h)
  before=bytes(self.u.mem_read(BASE,SIZE));self.active=True
  try:self.checked_call(0x6a9170,ecx=OBJ,writes=[(OBJ+p,4) for p in FIELDS],inputs=[*RANGES.items(),(OBJ+0xd64,8)])
  finally:self.active=False
  after=bytearray(self.u.mem_read(BASE,SIZE))
  for p in FIELDS:after[p:p+4]=before[p:p+4]
  assert after==before,'Viewport changed unrelated arena bytes'
  self.trace.extend(['Z',*[str(signed(self.word(OBJ+p))) for p in FIELDS]])
  return self.trace
