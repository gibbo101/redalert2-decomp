# SPDX-License-Identifier: GPL-3.0-or-later
"""Actual coverage, House, projection/FTOL and packed lookup in one guest."""
import struct
from original_techno_coverage import TechnoCoverageOracle,ARENA,SIZE,HOUSE,ACTOR,CELLS,signed
from original_presentation import STOP
from verify_techno_coverage_world import verify,RANGES
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP
TABLE=0x4000000;FALLBACK=0xa6f9f8;MAP=0x8324e0;SCALE=0xabe490
ACTUAL={0x4f52b0,0x4e5540,0x6a2970,0x77f110,0x548070}
class TechnoCoverageWorldOracle(TechnoCoverageOracle):
 def __init__(self,exe):
  verify(exe.read_bytes());super().__init__(exe);self.u.mem_map(TABLE,0x100000)
 def checked_call(self,root,args,ecx,**kw):
  u=self.u;extra=self.extra
  self.put(0xa3d298,extra[0]);u.mem_write(SCALE,struct.pack('<Q',self.scale))
  for i in (1,2):
   h=self.hp(i);at=1+(i-1)*4;self.put(h+0x30,extra[at]);u.mem_write(h+0x134,bytes(extra[at+1:at+3]));self.put(h+0x5674,extra[at+3])
  self.expected=bytearray(u.mem_read(ARENA,SIZE));u.mem_write(TABLE,bytes(0x100000));self.put(TABLE,CELLS);self.tableExpected=bytearray(u.mem_read(TABLE,0x100000));self.put(MAP+0x138,TABLE)
  u.mem_write(FALLBACK,b'\xa7'*0x148);u.mem_write(FALLBACK+0x24,struct.pack('<2h',-30000,29000))
  for off,v in zip((0x12c,0x130,0x134,0x13c),self.f[15:19]):self.put(FALLBACK+off,v)
  self.fallbackExpected=bytearray(u.mem_read(FALLBACK,0x148));self.pending={}
  kw['inputs']=list(RANGES.items())+[(SCALE,8),(MAP+0x138,4),(0xa3d298,4)]
  kw['writes']+= [(FALLBACK+0x24,4),(FALLBACK+0x12c,20)]
  super().checked_call(root,args,ecx,**kw)
  assert bytes(u.mem_read(FALLBACK,0x148))==self.fallbackExpected and bytes(u.mem_read(TABLE,0x100000))==self.tableExpected
 def write(self,u,access,p,n,value,ctx):
  if not self.active:return
  if FALLBACK<=p<FALLBACK+0x148:
   off=p-FALLBACK;assert n==4 and off in (0x24,0x12c,0x130,0x134,0x13c);self.fallbackExpected[off:off+4]=struct.pack('<I',value&0xffffffff);self.emit('W','F' if off==0x24 else 'C',0 if off==0x24 else 2,off,signed(value&0xffffffff));return
  super().write(u,access,p,n,value,ctx)
 def code(self,u,a,n,ctx):
  if not self.active or a==STOP:return
  sp=u.reg_read(UC_X86_REG_ESP);ecx=u.reg_read(UC_X86_REG_ECX)
  if a in self.pending:
   leaf,arguments=self.pending.pop(a);result=u.reg_read(UC_X86_REG_EAX)
   if leaf==0x6a2970:self.emit('E','Z',*arguments,signed(result));self.mutate(3)
   elif leaf==0x4f52b0:self.emit('E','L',*arguments,result&255)
   elif leaf==0x4e5540:self.emit('E','B',*arguments,result&255)
   else:
    identity=2 if result==FALLBACK else (result-CELLS)//0x200;assert identity in (0,1,2) and result==(FALLBACK if identity==2 else CELLS+identity*0x200);self.emit('E','C',*arguments,identity);self.mutate(5)
  if a in ACTUAL:
   self.counts[hex(a)]+=1
   if a!=0x77f110:
    if a==0x6a2970:arguments=(signed(ecx),)
    elif a==0x4f52b0:arguments=(self.hid(ecx),)
    elif a==0x4e5540:arguments=(self.hid(ecx),self.hid(self.word(sp+4)))
    else:
     assert ecx==MAP;arguments=struct.unpack('<2h',u.mem_read(self.word(sp+4),4));index=arguments[1]*512+arguments[0]
     if self.f[19] and 0<=index<262144:
      value=CELLS+(self.queries%2)*0x200;self.put(TABLE+index*4,value);self.tableExpected[index*4:index*4+4]=struct.pack('<I',value)
     self.queries+=1
    self.pending[self.word(sp)]=(a,arguments)
   return
  if any(lo<=a and a+n<=lo+size for lo,size in RANGES.items() if lo not in (0x6c83f0,0x6c86f0)):return
  super().code(u,a,n,ctx)
 def run(self,f):
  self.scale=f['scale'];self.extra=f['houses'];row=super().run(f['base']);assert not self.pending
  for i,off in enumerate((0x12c,0x130,0x134,0x13c)):row[-4+i]=str(signed(self.word(FALLBACK+off)))
  self.emit('F',*struct.unpack('<2h',self.u.mem_read(FALLBACK+0x24,4)),self.queries)
  return self.trace
