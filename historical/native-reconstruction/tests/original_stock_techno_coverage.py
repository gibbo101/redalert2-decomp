# SPDX-License-Identifier: GPL-3.0-or-later
"""Actual stock coverage virtual dispatch and existing complete availability."""
import struct
from original_techno_coverage_world import TechnoCoverageWorldOracle,ACTUAL as WORLD_ACTUAL
from original_techno_coverage import ARENA,SIZE,ACTOR,TYPE,signed
from original_presentation import STOP
from original_land_characteristics import push_double
from verify_stock_techno_coverage import verify,RANGES,EXTRA
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP
VT=ARENA+0x18000;ALT_TYPE=ARENA+0x14000
class StockTechnoCoverageOracle(TechnoCoverageWorldOracle):
 def __init__(self,exe):verify(exe.read_bytes());super().__init__(exe)
 def checked_call(self,root,args,ecx,**kw):
  u=self.u;s=self.stock;self.powerChanged=False;self.stockPending={}
  # The parent world installs fixtures first; our stock fields must precede its
  # arena snapshot and original execution, so install inside a one-call hook.
  self.put(ACTOR,VT)
  for off,a in {0x30c:0x450360 if s[0]==6 else 0x6cd6e0,0x80:0x6c12c0,0x84:0x453c60 if s[0]==6 else 0x506950,0x3c:0x6c7430}.items():self.put(VT+off,a)
  for off,v in [(0x6c,s[1]),(0x54c,s[3]),(0x3fc,s[4]),(0x418,TYPE),(0x5a8,TYPE)]:self.put(ACTOR+off,v)
  for off,v in [(0x530,s[2]),(0x59c,s[5])]:u.mem_write(ACTOR+off,bytes([v]))
  for t in (TYPE,ALT_TYPE):
   for off,v in [(0x1217,s[6]),(0x11fe,s[8]),(0x1206,s[9] if t==TYPE else 1)]:u.mem_write(t+off,bytes([v]))
   self.put(t+0xc6c,s[7]);u.mem_write(t+0xade,bytes([(self.f[3] if t==TYPE else s[11])&255]))
  # World setup resnapshots arena after these writes, preserving all padding.
  immutable=[(a,bytes(u.mem_read(a,n))) for a,n in EXTRA.items()]+[(0x79a708,bytes(u.mem_read(0x79a708,8)))];kw['inputs']=RANGES.items();super().checked_call(root,args,ecx,**kw)
  assert all(bytes(u.mem_read(a,len(b)))==b for a,b in immutable)
 def code(self,u,a,n,ctx):
  if not self.active or a==STOP:return
  sp=u.reg_read(UC_X86_REG_ESP);ecx=u.reg_read(UC_X86_REG_ECX)
  if a in self.stockPending:
   leaf=self.stockPending.pop(a);result=u.reg_read(UC_X86_REG_EAX)
   if leaf=='P':self.emit('E','P',result&255);self.mutate(1)
   elif leaf=='T':self.emit('E','T',struct.unpack('<b',u.mem_read(result+0xade,1))[0]);self.mutate(2)
   else:self.emit('E','O',self.hid(result));self.mutate(4)
  if a==0x4e8330:
   self.counts['supplied_house_power']+=1;self.emit('G',self.hid(ecx))
   if self.stock[10]:
    self.powerChanged=True;self.change(ACTOR+0x418,ALT_TYPE);self.change(ACTOR+0x54c,2);self.change(ACTOR+0x1b4,self.hp(2))
   push_double(u,self.powerBits);self.ret();return
  if a in EXTRA:
   self.counts[hex(a)]+=1
   if a in (0x450360,0x6cd6e0):self.stockPending[self.word(sp)]='P'
   elif a==0x6c12c0:self.stockPending[self.word(sp)]='T'
   elif a==0x6c7430:self.stockPending[self.word(sp)]='O'
   return
  if any(lo<=a and a+n<=lo+size for lo,size in EXTRA.items()):return
  super().code(u,a,n,ctx)
 def run(self,f):
  self.stock=f['stock'];self.powerBits=f['power'];row=super().run(f['world']);assert not self.stockPending
  self.emit('V',signed(self.word(ACTOR+0x54c)),int(self.word(ACTOR+0x418)==ALT_TYPE),int(self.powerChanged));return self.trace
