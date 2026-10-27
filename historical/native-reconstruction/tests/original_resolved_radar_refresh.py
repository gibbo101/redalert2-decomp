# SPDX-License-Identifier: GPL-3.0-or-later
"""Actual scheme lookup below stock actor/copy/mark/pixel refresh."""
from original_stock_radar_refresh import StockRadarRefreshOracle
from original_surface_mark_pixels import PIXELS
from original_surface_refresh_marks import SCHEMES,REGISTRIES,ARENA
from verify_scheme_resolver import RANGES as RESOLVER
from verify_resolved_radar_refresh import verify
from original_presentation import STOP
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ESI,UC_X86_REG_ESP
NAMES=ARENA+0x6c000
assert all(NAMES+0x400<=p or p+2048<=NAMES for p in PIXELS)
class ResolvedRadarRefreshOracle(StockRadarRefreshOracle):
 def __init__(self,exe):verify(exe.read_bytes());super().__init__(exe)
 def cid(self,p):assert p in [SCHEMES+i*0x400 for i in range(3)];return (p-SCHEMES)//0x400
 def change(self,p,v):
  if p in (0xab6f08,0xb2b098):self.put(p,v);self.resolverGlobals[p]=v&0xffffffff;return
  super().change(p,v)
 def checked_call(self,root,args=(),ecx=0,**kw):
  pattern,at,mask=self.resolverFixture;self.resolverGlobals={};self.change(0xab6f08,3);self.change(0xb2b098,0)
  for i,name in enumerate((b'LightGrey',b'Other' if pattern else b'LightGrey',b'LightGrey')):
   # Authored fixture strings; no original allocation or initialization claim.
   raw=name+b'\0';self.u.mem_write(NAMES+i*0x100,raw);self.expected[NAMES+i*0x100-ARENA:NAMES+i*0x100-ARENA+len(raw)]=raw
   self.change(SCHEMES+i*0x400+0x304,NAMES+i*0x100);self.change(SCHEMES+i*0x400+0x310,0 if i==0 else 1)
  # Stable alternate name used by a diagnostic pointer mutation.
  self.u.mem_write(NAMES+0x300,b'Other\0');self.expected[NAMES+0x300-ARENA:NAMES+0x306-ARENA]=b'Other\0'
  kw['inputs']=[*kw.get('inputs',()),*RESOLVER.items(),(0x7ebfc4,10)];super().checked_call(root,args,ecx,**kw)
 def resolver_mutate(self,stage,index):
  pattern,at,mask=self.resolverFixture;bits=mask&7 if stage==1 else mask>>3&7
  if self.resolverChanged or not bits or at!=index:return
  self.resolverChanged=True
  if bits&1:self.change(0xab6efc,REGISTRIES[1])
  if bits&2:self.change(SCHEMES+0x400+0x310,0xffffffff)
  if bits&4:self.change(SCHEMES+0x400+0x304,NAMES+0x300)
 def code(self,u,a,n,ctx):
  if not self.active or a==STOP:return
  if a in self.resolverPending:
   self.resolverPending.remove(a);self.emit('K',self.cid(u.reg_read(UC_X86_REG_EAX)));self.mutate(7)
  if a==0x663d30:self.resolverPending.add(self.word(u.reg_read(UC_X86_REG_ESP)))
  if a==0x663d4a:self.savedScheme=u.reg_read(UC_X86_REG_EAX)
  if a==0x663d57:
   i=u.reg_read(UC_X86_REG_ESI);v=u.reg_read(UC_X86_REG_EAX);self.emit('T',i,self.cid(self.savedScheme),v if v<2**31 else v-2**32);self.resolver_mutate(1,i)
  if a==0x663d66:self.savedCategoryScheme=self.word(u.reg_read(UC_X86_REG_EAX)+u.reg_read(UC_X86_REG_ESI)*4);self.savedCategory=self.word(self.savedCategoryScheme+0x310)
  if a==0x663d6c:
   i=u.reg_read(UC_X86_REG_ESI);v=self.savedCategory;self.emit('U',i,self.cid(self.savedCategoryScheme),v if v<2**31 else v-2**32);self.resolver_mutate(2,i)
  if any(lo<=a and a+n<=lo+size for lo,size in RESOLVER.items()):
   assert a!=0x781f73
   if a in RESOLVER:self.counts[hex(a)]+=1
   return
  super().code(u,a,n,ctx)
 def run(self,f):
  self.resolverFixture=f[22:];self.resolverChanged=False;self.resolverPending=set();row=super().run(f[:22]);assert not self.resolverPending and all(self.word(p)==v for p,v in self.resolverGlobals.items())
  self.emit('Q',self.word(0xab6f08),int(self.resolverChanged))
  for i in range(3):self.emit(int(bytes(self.u.mem_read(self.word(SCHEMES+i*0x400+0x304),10))==b'LightGrey\0'))
  for i in range(3):v=self.word(SCHEMES+i*0x400+0x310);self.emit(v if v<2**31 else v-2**32)
  return self.trace
