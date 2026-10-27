# SPDX-License-Identifier: GPL-3.0-or-later
import struct
from original_surface_radar_pixels import SurfaceRadarPixelsOracle
from original_radar_discovery import CELL,SLOTS,FALLBACK,MAP,CELLS,shorts
from original_presentation import STOP
from verify_radar_discovery import RANGES
from verify_radar_discovery_pixels import verify
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP
class RadarDiscoveryPixelsOracle(SurfaceRadarPixelsOracle):
 def __init__(self,exe):
  verify(exe.read_bytes());super().__init__(exe);self.u.mem_map(CELL,0x10000);self.u.mem_map(SLOTS,0x100000)
 def checked_call(self,root,args=(),ecx=0,**kw):
  divisor,flags,count=self.discoveryFixture;u=self.u;u.mem_write(CELL,b'\xa5'*0x10000);u.mem_write(SLOTS,bytes(0x100000));u.mem_write(FALLBACK,b'\xa5'*0x148);self.put(MAP+0x138,SLOTS);self.put(0xa6fc30,divisor);u.mem_write(0x851a7c,struct.pack('<hh',1,1))
  for p,(slot,x,y,flag,value) in zip(CELLS,[(0,3,4,flags,count),(513,1,1,0,1),(1026,-1,0,8,-1),(-1,-7,5,flags,count)]):
   self.put(p+0x24,(x&65535)|((y&65535)<<16));self.put(p+0x12c,flag);self.put(p+0x140,0);self.put(p+0x13c,value)
   if slot!=-1:self.put(SLOTS+4*slot,p)
  before=bytes(u.mem_read(CELL,0x10000));fallback=bytes(u.mem_read(FALLBACK,0x148))
  kw['writes']=[*kw.get('writes',()),(FALLBACK+0x24,4)];kw['inputs']=[*kw.get('inputs',()),*RANGES.items(),(SLOTS,0x100000),(MAP+0x138,4),(0xa6fc30,4),(0x851a7c,4)]
  super().checked_call(root,args,ecx,**kw)
  assert bytes(u.mem_read(CELL,0x10000))==before
  after=bytearray(u.mem_read(FALLBACK,0x148));after[0x24:0x28]=fallback[0x24:0x28];assert bytes(after)==fallback
 def write(self,u,access,p,n,v,ctx):
  if self.active and p==FALLBACK+0x24:
   assert n==4;self.emit('f',*struct.unpack('<hh',struct.pack('<I',v&0xffffffff)));return
  super().write(u,access,p,n,v,ctx)
 def code(self,u,a,n,ctx):
  if not self.active or a==STOP:return
  if a in self.discoveryPending:
   which,point=self.discoveryPending.pop(a);self.emit('I' if which else 'H',*point,u.reg_read(UC_X86_REG_EAX)&255);self.mutate(4 if which else 3)
  if any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()):
   sp=u.reg_read(UC_X86_REG_ESP)
   if a in (0x568140,0x568280):
    assert u.reg_read(UC_X86_REG_ECX)==MAP and self.word(sp+4)==self.mapaddr;self.discoveryPending[self.word(sp)]=(int(a==0x568280),tuple(int.from_bytes(u.mem_read(self.mapaddr+4*i,4),'little',signed=True) for i in range(3)))
   if a in RANGES:self.counts[hex(a)]+=1
   if a in (0x5682df,0x56836a,0x56819f,0x56822b):self.emit('i',*shorts(u,sp+0x10))
   elif a in (0x56830e,0x568399):
    p=u.reg_read(UC_X86_REG_EAX);self.emit('c',CELLS.index(p),int.from_bytes(u.mem_read(p+0x13c,4),'little',signed=True))
   elif a==0x476ac0:self.emit('n',CELLS.index(u.reg_read(UC_X86_REG_ECX)),self.word(sp+4));assert self.word(sp+4)==3
   elif a==0x548070:self.emit('w',*shorts(u,self.word(sp+4)))
   return
  super().code(u,a,n,ctx)
 def run(self,f):
  self.discoveryFixture=f[36:];self.discoveryPending={};super().run(f[:36]);assert not self.discoveryPending;self.emit('Y',*shorts(self.u,FALLBACK+0x24));return self.trace
