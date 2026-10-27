# SPDX-License-Identifier: GPL-3.0-or-later
"""Both unchanged refresh branches on one prepared actor/map/surface world."""
import struct
from original_radar_actor_pixels import RadarActorPixelsOracle,SCHEMES
from original_surface_radar_pixel import ARENA,ACTORS,HOUSES,TABLES,ENTRIES,SURF,signed
from original_surface_radar_pixels import PIXELS
from original_presentation import PresentationOracle,STOP
from verify_radar_refresh import verify,COPY,MARK,TABLE_DATA,DATA_RANGES
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP
EXTRA=0x3a00000;BITMAP=EXTRA+0x1000;PALETTES=[EXTRA+0x2000,EXTRA+0x2400];DATA=[EXTRA+0x10000,EXTRA+0x20000]
class RadarRefreshOracle(RadarActorPixelsOracle):
 def __init__(self,exe):verify(exe.read_bytes());super().__init__(exe);self.u.mem_map(EXTRA,0x40000)
 def prepared_root(self,root,stage):return root
 def execute_prepared(self,root,args=(),ecx=0,**kw):
  start,stages,format,indexPattern,seed=self.refreshFixture;u=self.u
  for t in TABLES:self.change(t+8,0x774f00)
  self.change(self.context+0x1270,BITMAP+256)
  for i,h in enumerate(HOUSES):self.change(h+0x15f40,2-i if indexPattern else i)
  self.put(0x8315b4,0);self.put(0x839c6c,0)
  u.mem_write(BITMAP,bytes([seed])*512);self.bitmapExpected=bytearray(u.mem_read(BITMAP,512))
  for k in range(2):
   self.put(PALETTES[k]+4,1 if k else format);self.put(PALETTES[k]+0x174,DATA[k]);u.mem_write(DATA[k],bytes((i*17+k*41+3)&255 for i in range(65536)))
  for i,p in enumerate(SCHEMES):self.change(p+0x30c,PALETTES[int(i==1)])
  self.extraExpected=bytearray(u.mem_read(EXTRA,0x40000))
  kw['writes']=[*kw.get('writes',()),(BITMAP,512)]
  kw['inputs']=[*kw.get('inputs',()),*COPY.items(),*MARK.items(),(0x8315b4,4),(0x839c6c,4),*[(a,len(v)*4) for a,v in TABLE_DATA.items()],*DATA_RANGES.items()]
  for stage in range(stages):
   mode=start^stage;self.change(0xb263d8,mode);self.emit('step',mode);self.zeroPhase=not bool(mode)
   PresentationOracle.checked_call(self,self.prepared_root(root,stage),args,ecx,**kw)
  assert bytes(u.mem_read(EXTRA,0x40000))==self.extraExpected
 def write(self,u,access,p,n,value,ctx):
  if self.active:
   if BITMAP<=p and p+n<=BITMAP+512:
    assert n in (1,4);raw=int(value&((1<<(n*8))-1)).to_bytes(n,'little');self.extraExpected[p-EXTRA:p-EXTRA+n]=raw;self.emit('m',p-BITMAP,n,int.from_bytes(raw,'little'));return
   for i,b in enumerate(PIXELS):
    if b<=p and p+n<=b+2048:
     assert n in (1,2,4);raw=int(value&((1<<(n*8))-1)).to_bytes(n,'little');self.expected[p-ARENA:p-ARENA+n]=raw;self.emit('N',i,p-b,n,int.from_bytes(raw,'little'));return
  super().write(u,access,p,n,value,ctx)
 def code(self,u,a,n,ctx):
  if not self.active or a==STOP:return
  sp=u.reg_read(UC_X86_REG_ESP);ecx=u.reg_read(UC_X86_REG_ECX)
  if self.zeroPhase and a in self.pending:
   who=self.pending.pop(a);self.emit('G',who,signed(self.word(SURF+who*0x100+4)),signed(self.word(SURF+who*0x100+8)))
  if self.zeroPhase and a in self.actorPending:
   kind,who,arg=self.actorPending.pop(a);value=u.reg_read(UC_X86_REG_EAX)
   if kind=='C':self.emit('C',who,value&255)
   elif kind=='O':self.emit('O',who,self.hid(value))
   elif kind=='S':self.emit('r',self.cid(value),'S')
   else:raise AssertionError('Unexpected zero-mode actor return')
  if a==0x774f00:
   dr,source,sr,flag0,flag1=[self.word(sp+4*i) for i in range(1,6)];self.emit('copy',self.sid(ecx),*struct.unpack('<4i',u.mem_read(dr,16)),self.sid(source),*struct.unpack('<4i',u.mem_read(sr,16)),flag0,flag1)
  if self.zeroPhase and a==0x774220:
   p=self.word(sp+4);i=(p-4-ENTRIES)//16;assert 0<=i<3 and p==ENTRIES+i*16+4;self.emit('P',self.sid(ecx),i,*struct.unpack('<2i',u.mem_read(p,8)),self.word(sp+8))
   self.counts['mark_pixels']+=1;return
  # Shared stock pixel children execute normally, but mark point identities are
  # entries rather than the nonzero parent's stack point.
  if self.zeroPhase and any(lo<=a and a+n<=lo+size for lo,size in COPY.items()):
   if a in COPY:self.counts['zero_'+hex(a)]+=1
   if a==0x411290:self.pending[self.word(sp)]=self.sid(ecx)
   return
  if any(lo<=a and a+n<=lo+size for lo,size in MARK.items()):
   if a==0x6324a0:self.counts[hex(a)]+=1
   #6324A0 and its store loops need no substituted return/child result.
   if 0x6324a0<=a<0x6324a0+MARK[0x6324a0]:return
  super().code(u,a,n,ctx)
 def run(self,f):
  self.refreshFixture=f[60:];self.zeroPhase=False;row=super().run(f[:60]);at=row.index('R');del row[at+8:at+12]
  self.emit('U',*self.u.mem_read(BITMAP,512));return self.trace
