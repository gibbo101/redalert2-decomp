# SPDX-License-Identifier: GPL-3.0-or-later
"""Stock actor colors below actual copy/mark/pixel refresh."""
import struct
from original_surface_copy_mark_pixels import SurfaceCopyMarkPixelsOracle
from original_surface_refresh_marks import ACTORS,HOUSES,ENTRIES,VT
from verify_stock_radar_refresh import verify
from verify_actor_radar_color import RANGES as ACTOR
from original_presentation import STOP
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP
NEW=[ACTORS+0x1000+i*0x800 for i in range(4)];TABLES=[VT+0x400,VT+0x600]
class StockRadarRefreshOracle(SurfaceCopyMarkPixelsOracle):
 def __init__(self,exe):verify(exe.read_bytes());self.aliases=False;super().__init__(exe)
 def aid(self,p):
  if p in NEW:return NEW.index(p)
  return super().aid(p)
 def word(self,p):
  if self.aliases and p in [ACTORS+i*0x400+0x1b4 for i in range(4)]:p=NEW[(p-ACTORS-0x1b4)//0x400]+0x1b4
  return super().word(p)
 def change(self,p,v):
  if self.aliases and p in [ACTORS+i*0x400+0x1b4 for i in range(4)]:p=NEW[(p-ACTORS-0x1b4)//0x400]+0x1b4
  if self.aliases and p in [ENTRIES+i*16 for i in range(16)] and v in [ACTORS+i*0x400 for i in range(4)]:v=NEW[(v-ACTORS)//0x400]
  if p==0xa35db4:self.put(p,v);self.expectedCurrent=v;return
  super().change(p,v)
 def checked_call(self,root,args=(),ecx=0,**kw):
  current,alternate,pattern,mask,mutation=self.radarFixture
  for k,vt in enumerate(TABLES):self.change(vt+0xc0,0x41b410);self.change(vt+0xcc,0x41b2e0 if k else 0x509270)
  for i,p in enumerate(NEW):
   kind=int(pattern==1 or pattern>=2 and (i+pattern)&1)
   for off,v in ((0,TABLES[kind]),(0x170,self.f[4]),(0x1b4,self.word(ACTORS+i*0x400+0x1b4)),(0x410,0 if alternate<0 else HOUSES+alternate*0x16000)):self.change(p+off,v)
  for i in range(16):self.change(ENTRIES+i*16,NEW[self.aid(self.word(ENTRIES+i*16))])
  for i in range(3):self.change(HOUSES+i*0x16000+0x30,i);self.change(HOUSES+i*0x16000+0x5674,mask)
  self.change(0xa35db4,0 if current<0 else HOUSES+current*0x16000);self.aliases=True
  kw['inputs']=[*kw.get('inputs',()),*ACTOR.items()];super().checked_call(root,args,ecx,**kw)
 def code(self,u,a,n,ctx):
  if not self.active or a==STOP:return
  sp=u.reg_read(UC_X86_REG_ESP);ecx=u.reg_read(UC_X86_REG_ECX)
  if a in self.radarPending:
   kind,who,argument=self.radarPending.pop(a);value=u.reg_read(UC_X86_REG_EAX)
   if kind=='A':self.ccs=0;self.emit('A',who,value&255);self.mutate(4)
   else:self.ccs+=1;self.emit('O',who,argument,self.hid(value));self.mutate(5 if self.ccs%2 else 6)
  if a==0x41b410:self.radarPending[self.word(sp)]=('A',self.aid(ecx),0)
  if a in (0x509270,0x41b2e0):self.radarActor=ecx;self.radarPending[self.word(sp)]=('O',self.aid(ecx),self.word(sp+4))
  if a==0x4e5540:self.savedAlliance=(ecx,self.word(sp+4))
  if a==0x509284:
   self.emit('J',self.aid(self.radarActor),self.hid(self.savedAlliance[0]),self.hid(self.savedAlliance[1]),u.reg_read(UC_X86_REG_EAX)&255)
   mutation=self.radarFixture[-1]
   if mutation and not self.radarChanged:
    self.radarChanged=True
    if mutation&1:self.change(self.radarActor+0x1b4,HOUSES+2*0x16000)
    if mutation&2:self.change(0xa35db4,HOUSES+2*0x16000)
    if mutation&4:self.change(self.radarActor+0x410,HOUSES+2*0x16000)
    if mutation&8:self.change(HOUSES+2*0x16000+0x30,0xffffffff);self.change(HOUSES+0x5674,self.word(HOUSES+0x5674)^0xffffffff)
  if any(lo<=a and a+n<=lo+size for lo,size in ACTOR.items()):
   if a in ACTOR:self.counts[hex(a)]+=1
   return
  super().code(u,a,n,ctx)
 def run(self,f):
  self.radarFixture=f[17:];self.aliases=False;self.radarPending={};self.radarChanged=False;row=super().run(f[:17]);assert not self.radarPending and self.word(0xa35db4)==self.expectedCurrent
  self.emit('Y',self.hid(self.word(0xa35db4)),int(self.radarChanged))
  pattern=self.radarFixture[2]
  for i,p in enumerate(NEW):self.emit(int(pattern==1 or pattern>=2 and (i+pattern)&1),self.word(p+0x170)&255,self.hid(self.word(p+0x410)))
  for i in range(3):p=HOUSES+i*0x16000;v=self.word(p+0x30);self.emit(v if v<2**31 else v-2**32,self.word(p+0x5674))
  return self.trace
