# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete original grid/threat/Object Cell/coordinate map on one guest."""
import struct
from original_house_actor_threat import HouseActorThreatOracle
from original_house_threat import VTABLE,ARENA
from original_presentation import STOP
from verify_house_actor_threat_cells import verify,EXTRA
from unicorn.x86_const import UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EAX
MAP=0x8324e0;FALLBACK=0xa6f9f8;TABLE=0x2400000;ALT_TABLE=TABLE+0x100000;CELLS=TABLE+0x200000
class HouseActorThreatCellsOracle(HouseActorThreatOracle):
 def __init__(self,exe):
  verify(exe.read_bytes());super().__init__(exe);self.u.mem_map(TABLE,0x201000)
 def change(self,p,v,n=4):
  if p in [VTABLE+0x400*i+0x1a4 for i in (1,2,3)]:v=0x5d51e0
  super().change(p,v,n)
 def cid(self,p):
  if p==FALLBACK:return -1
  i=(p-CELLS)//512;assert 0<=i<3 and p==CELLS+512*i;return i
 def mutate_map(self):
  if self.mapChanged or not self.f['mapMutation']:return
  self.mapChanged=True;m=self.f['mapMutation']
  if m==1:
   p=self.ap(self.mapActor);self.change(p+0x88,160*256);self.change(p+0x8c,160*256);self.change(p+0x90,-123)
  elif m==2:self.put(MAP+0x13c,262144);self.expectedMap[4:8]=struct.pack('<I',262144)
  elif m==3:self.put(MAP+0x138,ALT_TABLE);self.expectedMap[0:4]=struct.pack('<I',ALT_TABLE)
 def code(self,u,a,n,unused):
  if not self.active or a==STOP:return
  if any(lo<=a and a+n<=lo+size for lo,size in EXTRA.items()):
   if a in EXTRA:self.counts[hex(a)]+=1
   if a==0x5d51e0:
    self.mapActor=self.aid(u.reg_read(UC_X86_REG_ECX));self.trace.extend(map(str,('E',self.mapActor,a)))
   if a==0x548000:
    p=self.word(u.reg_read(UC_X86_REG_ESP)+4);self.trace.extend(map(str,('L',self.mapActor,*struct.unpack('<iii',u.mem_read(p,12)))))
   if a==0x54805f:
    self.trace.extend(map(str,('B',self.word(FALLBACK+0x24))));self.mapStores+=1;self.mutate_map()
   if a in (0x548047,0x548065):self.trace.extend(map(str,('C',self.cid(u.reg_read(UC_X86_REG_EAX)))))
   return
  super().code(u,a,n,unused)
 def checked_call(self,address,args,actor,**kwargs):
  f=self.f;u=self.u;u.mem_write(TABLE,bytes(0x200000));u.mem_write(CELLS,b'\xa5'*0x1000)
  for i,(index,x,y) in enumerate(f['mapCells']):
   p=CELLS+512*i;self.put(p+0x24,(x&65535)|((y&65535)<<16))
   if index>=0:self.put(TABLE+index*4,p);self.put(ALT_TABLE+index*4,CELLS+512*((i+1)%3))
  self.put(MAP+0x138,TABLE);self.put(MAP+0x13c,f['mapCount']);self.expectedMap=bytearray(u.mem_read(MAP+0x138,8))
  u.mem_write(FALLBACK,b'\xa7'*0x148);self.put(FALLBACK+0x24,(f['fx']&65535)|((f['fy']&65535)<<16));oldFallback=bytes(u.mem_read(FALLBACK,0x148))
  for i,point in enumerate(f['coordinates'],1):
   for j,value in enumerate(point):self.change(self.ap(i)+0x88+4*j,value)
  self.mapActor=0;self.mapStores=0;self.mapChanged=False
  kwargs['inputs']=[*kwargs['inputs'],*EXTRA.items(),(TABLE,0x201000)]
  kwargs['writes']=[*kwargs['writes'],(FALLBACK+0x24,4)]
  super().checked_call(address,args,actor,**kwargs)
  assert bytes(u.mem_read(MAP+0x138,8))==self.expectedMap
  after=bytearray(u.mem_read(FALLBACK,0x148));after[0x24:0x28]=oldFallback[0x24:0x28];assert after==oldFallback
 def run(self,f):
  row=super().run(f);row.extend(map(str,('F',*struct.unpack('<hh',self.u.mem_read(FALLBACK+0x24,4)),self.word(MAP+0x13c),int(self.word(MAP+0x138)==ALT_TABLE),int(self.mapChanged))))
  for i in (1,2,3):row.extend(map(str,struct.unpack('<iii',self.u.mem_read(self.ap(i)+0x88,12))))
  return row
