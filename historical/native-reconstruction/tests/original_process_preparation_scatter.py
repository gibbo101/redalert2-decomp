# SPDX-License-Identifier: GPL-3.0-or-later
"""Unmodified Process, successful supplied route output, actual preparation tree."""
from original_process_terminal_scatter import ProcessTerminalScatterOracle
from original_advance_cell_scatter import AdvanceCellScatterOracle
from original_cell_nearby_scatter import CellNearbyScatterOracle
from original_unit_scatter_world import *
from original_cell_unit_scatter_world import RULES
from verify_process_preparation_scatter import verify,RANGES,TABLES,EXTRA
from unicorn.x86_const import *
OVERLAY_TABLE,OVERLAY_TYPE=ARENA+0x3e800,ARENA+0x3ec00

class ProcessPreparationScatterOracle(ProcessTerminalScatterOracle):
 ranges=RANGES;tables=TABLES;inspection_verify=staticmethod(verify)
 def prepare_join(self,c):
  super().prepare_join(c);self.put(RULES+0x1380,c['close_enough']);self.put(self.root_actor+0x53c,c['route_counter'])
  self.route_resident=None;self.route_scatter=None
  if 'neighbor_overlay' in c:
   cell,flag=c['neighbor_overlay'];self.put(CELLS[cell]+0x44,0)
   self.put(0xa35dec,OVERLAY_TABLE);self.put(OVERLAY_TABLE,OVERLAY_TYPE)
   self.u.mem_write(OVERLAY_TYPE+0x1fd,bytes([flag]))
 def checked_call(self,root,args=(),ecx=0,edx=0,**kw):
  if root==0x4a05f0 and 'neighbor_overlay' in self.c:
   kw['inputs']=[*kw['inputs'],(0xa35dec,4)]
  return super().checked_call(root,args,ecx,edx,**kw)
 def event(self,*values):
  super().event(*values)
  if values and values[0]=='process-return':super().event('route-counter',signed(self.word(self.root_actor+0x53c)))
 def code(self,u,a,n,ctx):
  if not self.active or self.geometry_active or self.direction_active or a==STOP:return super().code(u,a,n,ctx)
  sp=u.reg_read(UC_X86_REG_ESP);ecx=u.reg_read(UC_X86_REG_ECX);arg=lambda i:self.word(sp+4+4*i)
  if a==0x4a1a39:
   assert self.word(u.reg_read(UC_X86_REG_EBX)+0x44)==0xffffffff,'Overlay traversal is outside neighbor proof'
   self.counts['Advance.overlay_absent']+=1
  if a==0x4a1a4e:raise AssertionError('Entered unjoined Advance curve64 overlay consumer')
  if 'neighbor_overlay' in self.c:
   if a==0x4a3fb0:
    assert self.cid(u.reg_read(UC_X86_REG_EAX))==self.c['neighbor_overlay'][0]
    self.counts['preparation.actual_overlay_neighbor']+=1
   if a==0x4a3fe3:
    self.counts['preparation.curve64.'+str(self.byte(self.root_drive+0x64))]+=1
  if self.route_resident==(a,sp):
   self.emit('r','r',self.oid(u.reg_read(UC_X86_REG_EAX)));self.route_resident=None
  if self.route_scatter and self.route_scatter[:2]==(a,sp):
   assert self.context=='c' and not self.unit_stack and not self.pending
   self.c['cell']=self.route_scatter[2];self.route_scatter=None;self.context='s'
  if a==0x4c3000:
   assert ecx==self.root_actor and self.word(sp)==0x4a28e7 and [arg(1),arg(2)]==[0,0]
   assert struct.unpack('<2h',pack(arg(0)))==tuple(v//256 if v>=0 else -((-v)//256) for v in self.coord(self.root_drive+0x34)[:2])
   self.emit('r','F',1)
   for i,value in enumerate(self.c['supplied_route']):
    self.put(self.root_actor+0x4d0+4*i,value);self.expected[self.root_actor-ARENA+0x4d0+4*i:self.root_actor-ARENA+0x4d4+4*i]=pack(value);self.emit('r','Q',i,value)
   self.counts['supplied.positive_pathfinder']+=1;self.ret(12,1);return
  if a==0x471660:
   assert self.cell(arg(0))==(0,0) and arg(2)==0
   self.emit('r','R',self.cid(ecx),arg(1)&255,-1);self.route_resident=(self.word(sp),sp+16);self.counts['actual.closest_resident']+=1
  if self.route_resident:
   if a==0x5d4e40:
    at=self.coord(ecx+0x88);self.emit('r','P',self.oid(ecx),*at[:2]);self.emit('r','p',self.oid(ecx),at[2])
   if any(lo<=a and a+n<=lo+size for lo,size in EXTRA.items()) or a==0x5d4e40:
    assert (a,n) in self.allowed;self.instructions.add(a);return
  if a==0x4e5580 and not self.in_advance and self.context=='s':self.emit('a','A',self.hid(ecx))
  if a==0x6c7430 and not self.in_advance and self.context=='s' and self.word(sp)==0x4e5590:self.emit('a','O',self.oid(ecx))
  if a==0x476920 and not self.in_advance:
   assert self.word(sp) in (0x4a32b4,0x4a3936,0x4a43fd) and [arg(0),arg(1),arg(2)]==[0x852998,1,1]
   self.route_scatter=(self.word(sp),sp+20,self.c['cell']);self.c['cell']=self.cid(ecx)
   self.emit('r','S',self.cid(ecx),arg(3)&255);self.context='c';self.capacity=self.buffer=self.successes=self.grows=0
   self.counts['preparation.Scatter.'+hex(self.word(sp))]+=1
   self.counts['preparation.elevated.'+str(arg(3)&255)]+=1
  if self.route_scatter and a in (0x7072d0,0x476a89):return AdvanceCellScatterOracle.code(self,u,a,n,ctx)
  if self.route_scatter:return CellNearbyScatterOracle.code(self,u,a,n,ctx)
  # Parent's Process routing deliberately uses the Cell oracle directly; pure
  # newly entered helpers still execute their inspected original instructions.
  if any(lo<=a and a+n<=lo+size for lo,size in EXTRA.items()):
   assert (a,n) in self.allowed;self.instructions.add(a);return
  return super().code(u,a,n,ctx)
 def store(self,u,access,p,n,v,ctx):
  if self.active and u.reg_read(UC_X86_REG_EIP)==0x4a32b7:
   assert (p,n,v)==(self.root_actor+0x53c,4,10);self.emit('v','A',0x53c,10)
   self.expected[p-ARENA:p-ARENA+n]=pack(v);self.writes['0x4a32b7']+=1;return
  return super().store(u,access,p,n,v,ctx)
