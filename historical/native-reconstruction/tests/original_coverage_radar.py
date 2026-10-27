# SPDX-License-Identifier: GPL-3.0-or-later
"""Unmodified coverage parents call actual nonzero refresh on one Map object."""
import struct
from original_radar_actor_pixels import RadarActorPixelsOracle,ACTORVT
from original_surface_radar_pixel import TYPES
from original_surface_radar_pixel import ARENA,SIZE,ACTORS,HOUSES,signed
from original_radar_discovery import MAP,CELL,CELLS,FALLBACK
from original_presentation import STOP,STACK
from verify_coverage_radar import verify,RANGES,STOCK
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP
class CoverageRadarOracle(RadarActorPixelsOracle):
 context=MAP
 def __init__(self,exe):verify(exe.read_bytes());super().__init__(exe)
 def change(self,p,v):
  if self.context<=p<self.context+0x1500:
   self.put(p,v)
   if hasattr(self,'mapExpected'):self.mapExpected[p-self.context:p-self.context+4]=struct.pack('<I',v&0xffffffff)
  else:super().change(p,v)
 def prepare_map(self):
  for i,vt in enumerate(ACTORVT):self.change(vt+0x30c,0x450360 if i else 0x6cd6e0)
  kind=int(self.actorFixture[2]==1 or self.actorFixture[2]>=2 and self.actorFixture[2]&1)
  for off,value,n in ((0x530,self.coverageFixture[4],1),(0x54c,0,4),(0x3fc,0,4),(0x6c,1,4),(0x59c,0,1)):
   raw=value.to_bytes(n,'little');p=ACTORS[0]+off;self.u.mem_write(p,raw);self.expected[p-ARENA:p-ARENA+n]=raw
  for off,value,n in ((0xade,self.coverageFixture[3]&255,1),(0x1217,0,1),(0xc6c,0,4),(0x11fe,0,1),(0x1206,0,1)):
   raw=value.to_bytes(n,'little');p=TYPES+off;self.u.mem_write(p,raw);self.expected[p-ARENA:p-ARENA+n]=raw
  for p in CELLS:
   for off,value in ((0x130,self.coverageFixture[10]),(0x134,self.coverageFixture[11])):self.put(p+off,value)
  self.cellsExpected=bytearray(self.u.mem_read(CELL,0x10000));self.fallbackExpected=bytearray(self.u.mem_read(FALLBACK,0x148))
 def audit_map(self,before,fallback):
  assert bytes(self.u.mem_read(CELL,0x10000))==self.cellsExpected
  assert bytes(self.u.mem_read(FALLBACK,0x148))==self.fallbackExpected
 def checked_call(self,root,args=(),ecx=0,**kw):
  f=self.coverageFixture;u=self.u
  for off,value,n in ((0x1fd,f[1],1),(0x200,f[2],4),(0x88,f[5],4),(0x8c,f[6],4),(0x90,f[7],4),(0x1b4,HOUSES[f[12]],4)):
   raw=int(value&((1<<(8*n))-1)).to_bytes(n,'little');u.mem_write(ACTORS[0]+off,raw);self.expected[ACTORS[0]+off-ARENA:ACTORS[0]+off-ARENA+n]=raw
  for i,h in enumerate(HOUSES):
   for off,value in ((0x13d,f[8]),(0x566a,f[9]),(0x188,255-i)):
    u.mem_write(h+off,bytes([value]));self.expected[h+off-ARENA]=value
  u.mem_write(0xabe490,struct.pack('<d',.125));self.mapExpected=bytearray(u.mem_read(MAP,0x1500))
  kw['writes']=[*kw.get('writes',()),(ACTORS[0]+0x1fd,1),(ACTORS[0]+0x200,4),*[(h+0x188,1) for h in HOUSES],*[(p+0x12c,20) for p in CELLS]]
  kw['inputs']=[*kw.get('inputs',()),*RANGES.items(),*STOCK.items(),(0xabe490,8)]
  # The coverage parent calls Map8324E0 directly; the radar context lives there,
  # rather than redirecting ECX at the refresh boundary or copying its records.
  u.mem_write(STACK-0x1000,bytes(0x1000))
  super().checked_call(0x6c83f0 if f[0] else 0x6c86f0,[],ACTORS[0],**kw)
  assert bytes(u.mem_read(MAP+0x1208,0x1500-0x1208))==self.mapExpected[0x1208:]
  assert not self.coveragePending
 def write(self,u,access,p,n,value,ctx):
  if not self.active:return
  raw=int(value&((1<<(8*n))-1)).to_bytes(n,'little')
  if MAP+0x1208<=p<MAP+0x1218:
   assert n==4;self.mapExpected[p-MAP:p-MAP+4]=raw;self.emit('D',(p-MAP-0x1208)//4,signed(value&0xffffffff));return
  for i,c in enumerate(CELLS):
   if c<=p<c+0x148:
    off=p-c
    if off==0x24:
     assert i==3 and n==4;self.fallbackExpected[off:off+4]=raw;self.emit('f',*struct.unpack('<hh',raw));return
    assert off in (0x12c,0x130,0x134,0x13c) and n==4
    if i==3:self.fallbackExpected[off:off+4]=raw
    else:self.cellsExpected[p-CELL:p-CELL+4]=raw
    self.emit('u','C',off,signed(value&0xffffffff));return
  if p in (ACTORS[0]+0x1fd,ACTORS[0]+0x200) or any(p==h+0x188 for h in HOUSES):
   actor=ACTORS[0]<=p<ACTORS[0]+0x800;off=p-ACTORS[0] if actor else 0x188
   assert n==(4 if off==0x200 else 1);self.expected[p-ARENA:p-ARENA+n]=raw;self.emit('u','A' if actor else 'H',off,signed(value&0xffffffff) if n==4 else value&255);return
  super().write(u,access,p,n,value,ctx)
 def code(self,u,a,n,ctx):
  if not self.active or a==STOP:return
  sp=u.reg_read(UC_X86_REG_ESP);ecx=u.reg_read(UC_X86_REG_ECX)
  if a in self.coveragePending:
   kind,arg=self.coveragePending.pop(a);v=u.reg_read(UC_X86_REG_EAX)
   if kind=='a':self.emit('a',int.from_bytes(u.mem_read(v+0xade,1),'little',signed=True))
   else:self.emit(kind,*arg,signed(v) if kind=='z' else v&255)
  if a in (0x4f52b0,0x4e5540) and self.coveragePhase:
   args=(self.hid(ecx),) if a==0x4f52b0 else (self.hid(ecx),self.hid(self.word(sp+4)))
   self.coveragePending[self.word(sp)]=('l' if a==0x4f52b0 else 'b',args)
   self.counts['coverage_'+hex(a)]+=1;return
  if a==0x634030:self.coveragePhase=False
  if a in (0x6c12c0,0x6c7430) and self.coveragePhase:
   if a==0x6c12c0:
    self.coveragePending[self.word(sp)]=('a',());self.counts['coverage_type']+=1;return
   self.emit('o',self.hid(self.word(ecx+0x1b4)));self.counts['coverage_owner']+=1;return
  if a==0x6a2970:self.coveragePending[self.word(sp)]=('z',(signed(ecx),))
  if a in (0x450360,0x6cd6e0):self.coveragePending[self.word(sp)]=('p',());self.counts['coverage_permission_'+hex(a)]+=1
  if self.coveragePhase and any(lo<=a and a+n<=lo+size for lo,size in STOCK.items()):return
  if a==0x4e09a0:
   assert ecx==MAP;self.emit('d',signed(self.word(sp+4)));self.counts['supplied_redraw']+=1;self.ret(args=4);return
  if any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()):
   if a in (0x6c83f0,0x6c86f0):self.coveragePhase=True
   if a in RANGES:self.counts['coverage_'+hex(a)]+=1
   if a==0x548070:
    # Shared query is logged by the existing discovery hook.
    pass
   elif self.coveragePhase and a!=0x77f110:return
   elif 0x6c83f0<=a<0x6c83f0+0x2f1 or 0x6c86f0<=a<0x6c86f0+0x2ce or 0x6a2970<=a<0x6a29ac:return
  super().code(u,a,n,ctx)
 def run(self,f):
  self.coverageFixture=f[60:];self.coveragePending={};self.coveragePhase=True
  row=super().run(f[:60]);at=row.index('R');del row[at+10:at+12]
  self.emit('Q',self.u.mem_read(ACTORS[0]+0x1fd,1)[0],signed(self.word(ACTORS[0]+0x200)),*[self.u.mem_read(h+0x188,1)[0] for h in HOUSES])
  for p in CELLS:
   for off in (0x12c,0x130,0x134,0x13c):self.emit(signed(self.word(p+off)))
  return self.trace
