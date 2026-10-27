# SPDX-License-Identifier: GPL-3.0-or-later
"""Unchanged Cell -> distinct Unit -> nearby search and destinations."""
import struct
from original_cell_unit_scatter_world import CellUnitScatterWorldOracle,OBJECTS,TYPES,CELLS
from original_unit_nearby_scatter import UnitNearbyScatterOracle
from original_unit_scatter_world import STATE,POINT
from unicorn.x86_const import UC_X86_REG_ECX
from verify_cell_nearby_scatter import verify,RANGES,TABLES
class CellNearbyScatterOracle(CellUnitScatterWorldOracle,UnitNearbyScatterOracle):
 ranges=RANGES;tables=TABLES;inspection_verify=staticmethod(verify)
 def prepare_join(self,c):
  self.zero_audit=None
  CellUnitScatterWorldOracle.prepare_join(self,c)
  UnitNearbyScatterOracle.prepare_join(self,c)
  for i,(p,t) in enumerate(zip(OBJECTS,TYPES)):
   self.put(t+0x5a4,c['speed_types'][i])
   for off in (0x418,0x5ac):self.put(p+off,TYPES[c['type_indexes'][i]])
  self.u.mem_write(0x850ea0,struct.pack('<108I',*c['nearby_speeds']))
 def code(self,u,a,n,ctx):
  if self.active and a==0x7072d0 and self.context=='c':
   p=u.reg_read(UC_X86_REG_ECX)
   self.zero_audit=(p,bytes(u.mem_read(STATE,1012)),bytes(u.mem_read(p+0xa0,5))) if self.coord(POINT)==(0,0,0) else None
  if self.active and a==0x476a89 and self.zero_audit:
   p,rng,mission=self.zero_audit;assert p==self.actor and bytes(u.mem_read(STATE,1012))==rng and bytes(u.mem_read(p+0xa0,5))==mission
   self.counts['zero_dispatch_no_RNG_or_queue']+=1;self.zero_audit=None
  if self.active and a==0x5502e0:
   actor=self.oid(self.actor);self.c['speed_type']=self.c['speed_types'][self.c['type_indexes'][actor]]
   self.counts['nearby.actor.'+str(actor)]+=1
  return super().code(u,a,n,ctx)
 def append_join_state(self,c):
  CellUnitScatterWorldOracle.append_join_state(self,c)
  assert not self.nearby_pending and self.nearby_return is None
  self.event('nearby-retained',c['dimension1'])
  for i,p in enumerate(OBJECTS):self.event(self.word(TYPES[i]+0x5a4),TYPES.index(self.word(p+0x5ac)))
  for p in CELLS:
   self.event(*self.cell(p+0x24),struct.unpack('<b',self.u.mem_read(p+0x11b,1))[0],self.byte(p+0x11c),self.word(p+0x140),self.word(p+0xec),self.word(p+0x124),self.word(p+0x128))
