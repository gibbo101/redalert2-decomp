# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete original Process with admitted overlays and actual crushing markers."""
from original_process_preparation_scatter import ProcessPreparationScatterOracle,OVERLAY_TABLE,OVERLAY_TYPE
from original_unit_scatter_world import *
from verify_process_overlay import verify,RANGES,TABLES
from unicorn.x86_const import UC_X86_REG_EBX,UC_X86_REG_ESI,UC_X86_REG_EIP,UC_X86_REG_ESP
class ProcessOverlayOracle(ProcessPreparationScatterOracle):
 ranges=RANGES;tables=TABLES;inspection_verify=staticmethod(verify)
 def prepare_join(self,c):
  super().prepare_join(c)
  cell,index,crushable,wall,owner,typeIndex264,af4,initial,velocity=c['candidate_overlay']
  self.u.mem_write(OVERLAY_TYPE,bytes(0x400));self.put(0xa35dec,OVERLAY_TABLE)
  for i in range(2):self.put(OVERLAY_TABLE+4*i,OVERLAY_TYPE)
  self.put(CELLS[cell]+0x44,index);self.put(CELLS[cell]+0x50,owner)
  self.u.mem_write(OVERLAY_TYPE+0x1fd,bytes([crushable]));self.u.mem_write(OVERLAY_TYPE+0x278,bytes([wall]))
  self.put(OVERLAY_TYPE+0x264,typeIndex264)
  self.u.mem_write(TYPES[c['type_indexes'][0]]+0xaf4,bytes([af4]))
  self.u.mem_write(self.root_actor+0x59f,bytes([initial]));self.put(self.root_actor+0x28c,velocity)
  self.crushing_ability=False
 def checked_call(self,root,args=(),ecx=0,edx=0,**kw):
  if root==0x4a05f0:kw['inputs']=[*kw['inputs'],(0xa35dec,4)]
  return super().checked_call(root,args,ecx,edx,**kw)
 def event(self,*values):
  super().event(*values)
  if values and values[0]=='process-return':
   super().event('overlay-state',self.byte(self.root_actor+0x59f),self.word(self.root_actor+0x28c))
 def admission_code(self,a,ecx,arg):
  if a==0x70333d:
   self.counts['actual.overlay_admission']+=1;return
  return super().admission_code(a,ecx,arg)
 def code(self,u,a,n,ctx):
  if not self.active or self.geometry_active or self.direction_active or a==STOP:return super().code(u,a,n,ctx)
  if a==0x703331:
   p=u.reg_read(UC_X86_REG_EBX);self.emit('a','o',self.cid(p),signed(self.word(p+0x44)))
  if a==0x476cff:raise AssertionError('Entered unjoined nonzero overlay27A Cell entry')
  if self.next_return and a in (0x70521d,0x705245):
   p=u.reg_read(UC_X86_REG_ESI);upper=a==0x70521d
   self.emit('a','S',self.cid(p),int(upper),self.word(p+(0x128 if upper else 0x124))&31)
   self.counts['actual.nextCell_warning_empty']+=1
  if a==0x6d7910 and self.word(u.reg_read(UC_X86_REG_ESP))==0x4a1a74:
   self.crushing_ability=True;self.emit('a','b',0,17)
  if self.crushing_ability and a in (0x7133a0,0x713420):self.emit('a','v',0,1 if a==0x7133a0 else 2)
  if a==0x4a1a74:self.crushing_ability=False
  if a in (0x4a1a39,0x4a1a4e):
   assert (a,n) in self.allowed;self.instructions.add(a);self.counts[hex(a)]+=1;return
  if a in (0x4a3575,0x4a3fd9,0x4a3548):self.counts[hex(a)]+=1
  return super().code(u,a,n,ctx)
 def store(self,u,access,p,n,v,ctx):
  if self.active and u.reg_read(UC_X86_REG_EIP) in (0x4a1a85,0x4a1aa4):
   ip=u.reg_read(UC_X86_REG_EIP);off,size=(0x59f,1) if ip==0x4a1a85 else (0x28c,4)
   assert (p,n)==(self.root_actor+off,size)
   value=v&((1<<(8*n))-1);self.emit('v','A',off,value)
   self.expected[p-ARENA:p-ARENA+n]=value.to_bytes(n,'little');self.writes[hex(ip)]+=1
   self.counts['store.'+hex(off)]+=1;return
  return super().store(u,access,p,n,v,ctx)
