# SPDX-License-Identifier: GPL-3.0-or-later
import struct
from original_surface_copy import SurfaceCopyOracle,ARENA,OBJECTS
from verify_surface_refresh_copy import verify
from verify_surface_refresh import RANGES as REFRESH
from original_presentation import STOP
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EIP
CONTEXT=ARENA+0xa000
class SurfaceRefreshCopyOracle(SurfaceCopyOracle):
 def __init__(self,exe):verify(exe.read_bytes());super().__init__(exe)
 def checked_call(self,root,args=(),ecx=0,edx=0,**kw):
  assert root==0x774f00
  same=int(args[1]==OBJECTS[0])
  for p,v in ((CONTEXT+0x1218,OBJECTS[0]),(CONTEXT+0x121c,OBJECTS[0 if same else 1])):
   self.put(p,v);self.expected[p-ARENA:p-ARENA+4]=struct.pack('<I',v)
  self.put(0xb263d8,0);kw['inputs']=[*kw['inputs'],*REFRESH.items(),(0xb263d8,4),(CONTEXT,0x1220)]
  return super().checked_call(0x634030,[],CONTEXT,**kw)
 def code(self,u,a,n,ctx):
  if not self.active or a==STOP:return
  if a==0x6324a0:
   assert u.reg_read(UC_X86_REG_ECX)==CONTEXT;self.trace+=['F'];self.counts['supplied_6324A0']+=1
   sp=u.reg_read(UC_X86_REG_ESP);u.reg_write(UC_X86_REG_EAX,0);u.reg_write(UC_X86_REG_EIP,int.from_bytes(u.mem_read(sp,4),'little'));u.reg_write(UC_X86_REG_ESP,sp+4);return
  if 0x634030<=a and a+n<=0x634030+REFRESH[0x634030]:
   if a==0x634030:self.counts[hex(a)]+=1
   return
  super().code(u,a,n,ctx)
 def run(self,f):
  row=super().run(f);assert row[-6]=='R';row[-5]='1';return row
