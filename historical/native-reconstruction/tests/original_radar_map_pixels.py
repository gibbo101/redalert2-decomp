# SPDX-License-Identifier: GPL-3.0-or-later
"""Unmodified radar parent and actual floor/discovery on one Cell arena."""
import hashlib,struct
from original_radar_discovery_pixels import RadarDiscoveryPixelsOracle
from original_surface_radar_pixels import SurfaceRadarPixelsOracle
from original_radar_discovery import CELL,SLOTS,FALLBACK,MAP,CELLS,shorts
from original_presentation import STOP
from verify_map_floor_height import RANGES as FLOOR
from verify_radar_map_pixels import verify
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP
PLANES=0x7d27e8
class RadarMapPixelsOracle(RadarDiscoveryPixelsOracle):
 def __init__(self,exe):verify(exe.read_bytes());super().__init__(exe);self.lazyStores=0
 def prepare_map(self):pass
 def audit_map(self,before,fallback):
  assert bytes(self.u.mem_read(CELL,0x10000))==before
  after=bytearray(self.u.mem_read(FALLBACK,0x148));after[0x24:0x28]=fallback[0x24:0x28];assert bytes(after)==fallback
 def checked_call(self,root,args=(),ecx=0,**kw):
  divisor,flags,count=self.discoveryFixture;current,lazy,*fields=self.floorFixture;u=self.u
  u.mem_write(CELL,b'\xa5'*0x10000);u.mem_write(SLOTS,bytes(0x100000));u.mem_write(FALLBACK,b'\xa5'*0x148);self.put(MAP+0x138,SLOTS);self.put(MAP+0x13c,262144);self.put(0xa6fc30,divisor);u.mem_write(0x851a7c,struct.pack('<hh',1,1))
  self.put(0x850c40,current);u.mem_write(0x850bb8,bytes([lazy]));u.mem_write(0x850ba8,struct.pack('<d',73));u.mem_write(0x850bd0,struct.pack('<d',.25));u.mem_write(PLANES,struct.pack('<100d',1,*([0]*99)))
  for i,(p,(slot,x,y,flag,value)) in enumerate(zip(CELLS,[(0,3,4,flags,count),(513,1,1,0,1),(1026,-1,0,8,-1),(-1,-7,5,flags,count)])):
   self.put(p+0x24,(x&65535)|((y&65535)<<16));self.put(p+0x12c,flag);self.put(p+0x140,0);self.put(p+0x13c,value);u.mem_write(p+0x11b,bytes([fields[2*i]&255,fields[2*i+1]]))
   if slot!=-1:self.put(SLOTS+4*slot,p)
  self.prepare_map()
  before=bytes(u.mem_read(CELL,0x10000));fallback=bytes(u.mem_read(FALLBACK,0x148))
  kw['writes']=[*kw.get('writes',()),(FALLBACK+0x24,4),(0x850bb8,1),(0x850ba8,8),(0x850bd0,8),(PLANES,800)]
  kw['inputs']=[*kw.get('inputs',()),*FLOOR.items(),(SLOTS,0x100000),(MAP+0x138,8),(0xa6fc30,4),(0x851a7c,4)]
  # Invoke pixel preparation without the older discovery fixture reinitializing
  # the same Cell arena. Its discovery hooks still execute unchanged children.
  SurfaceRadarPixelsOracle.checked_call(self,root,args,ecx,**kw)
  self.audit_map(before,fallback)
 def write(self,u,access,p,n,v,ctx):
  if self.active and (p in (0x850bb8,0x850ba8,0x850bac,0x850bd0,0x850bd4) or PLANES<=p<PLANES+800):
   assert (p==0x850bb8 and n==1) or (p!=0x850bb8 and n in (4,8) and p%4==0);self.lazyStores+=1;return
  super().write(u,access,p,n,v,ctx)
 def code(self,u,a,n,ctx):
  if not self.active or a==STOP:return
  if a in self.floorPending:self.floorPending.remove(a);self.emit('t',(u.reg_read(UC_X86_REG_EAX) if u.reg_read(UC_X86_REG_EAX)<2**31 else u.reg_read(UC_X86_REG_EAX)-2**32))
  sp=u.reg_read(UC_X86_REG_ESP)
  if a==0x55a280:
   assert u.reg_read(UC_X86_REG_ECX)==MAP;self.mapaddr=self.word(sp+4);self.emit('F',*[int.from_bytes(u.mem_read(self.mapaddr+4*i,4),'little',signed=True) for i in range(3)]);self.mutate(2);self.floorCalls+=1
   if self.floorCalls==self.floorFixture[-2]:self.put(0x850c40,self.floorFixture[-1]);self.emit('g',self.floorFixture[-1])
   self.floorPending.add(self.word(sp))
  if a in (0x56830e,0x568399):
   p=u.reg_read(UC_X86_REG_EAX);self.emit('c',*shorts(u,p+0x24),int.from_bytes(u.mem_read(p+0x13c,4),'little',signed=True));return
  if a==0x476ac0:
   self.counts[hex(a)]+=1;self.emit('n',*shorts(u,u.reg_read(UC_X86_REG_ECX)+0x24),self.word(sp+4));assert self.word(sp+4)==3;return
  if any(lo<=a and a+n<=lo+size for lo,size in FLOOR.items()):
   if a in FLOOR:self.counts[hex(a)]+=1
   return
  super().code(u,a,n,ctx)
 def run(self,f):
  self.floorFixture=f[39:];self.floorPending=set();self.floorCalls=0;super().run(f[:39]);assert not self.floorPending
  data=bytes(self.u.mem_read(0x850bb8,1))+bytes(self.u.mem_read(0x850ba8,8))+bytes(self.u.mem_read(0x850bd0,8))+bytes(self.u.mem_read(PLANES,800))
  self.emit('O',int.from_bytes(self.u.mem_read(0x850c40,4),'little',signed=True),hashlib.sha256(data).hexdigest());return self.trace
