# SPDX-License-Identifier: GPL-3.0-or-later
"""Actual original result6 block, unmodified child tree, separately guarded entry."""
import struct
from original_cell_nearby_scatter import CellNearbyScatterOracle
from original_cell_unit_scatter_world import HEAP,HEAP_SIZE
from original_unit_scatter_world import ACTOR,DRIVE,DRIVES,OBJECTS,CELLS,STATE,ARENA,SIZE,MAP,POINT,STACK,pack,signed
from verify_advance_cell_scatter import verify,RANGES,TABLES,ROOTS,GLOBALS,CONSTANTS,BLOCK,END
from unicorn import UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_ESP,UC_X86_REG_ECX,UC_X86_REG_ESI,UC_X86_REG_EBP,UC_X86_REG_EIP,UC_X86_REG_FPCW
class AdvanceCellScatterOracle(CellNearbyScatterOracle):
 root_actor=ACTOR;root_drive=DRIVE
 ranges=RANGES;tables=TABLES;inspection_verify=staticmethod(verify)
 def __init__(self,exe):
  self.geometry_active=False;super().__init__(exe)
  self.geometry_stores=[];self.geometry_entries={hex(a):0 for a in ROOTS};self.geometry_active=True
  self.put(0xb2af94,0)
  for a,n in GLOBALS.items():self.u.mem_write(a,b'\xa5'*n)
  try:
   for root,(a,n) in zip(ROOTS,GLOBALS.items()):
    self.checked_call(root,writes=[(a,n)],inputs=[*RANGES.items(),*TABLES.items(),(0xb2af94,4),*[(p,size) for p,size in GLOBALS.items() if p!=a]])
  finally:self.geometry_active=False
  self.geometry_values=[str(int.from_bytes(self.u.mem_read(a,n),'little')) for a,n in GLOBALS.items()]
  assert self.word(0x8529d0)==104 and len(self.geometry_stores)==10
 def prepare_join(self,c):
  super().prepare_join(c);self._block_zero=None
 def original_entry(self,c):
  self.context='g';self.block_sp=STACK-0x200;u=self.u
  u.mem_write(self.block_sp-0x1e00,b'\xa7'*0x2000)
  u.mem_write(self.block_sp+0x18,pack(*c['candidate']));self.put(self.block_sp+0x14,c['scratch'])
  # Register/stack inputs are authored at this inspected interior boundary.
  u.reg_write(UC_X86_REG_ESP,self.block_sp);u.reg_write(UC_X86_REG_EBP,self.root_drive);u.reg_write(UC_X86_REG_ESI,self.root_drive+0x40)
  self.event('geometry',*self.geometry_values)
  return BLOCK,[],0
 def checked_call(self,root,args=(),ecx=0,edx=0,**kw):
  if root!=BLOCK:return super().checked_call(root,args,ecx,edx,**kw)
  u=self.u;before=[bytes(u.mem_read(p,n)) for p,n in kw['inputs']+list(GLOBALS.items())]
  caller=bytes(u.mem_read(self.block_sp+0x100,0x100));entry=bytes(u.mem_read(self.block_sp,0x100))
  allowed=[(self.block_sp-0x1e00,self.block_sp+0x100),*[(p,p+n) for p,n in kw['writes']],(HEAP,HEAP+HEAP_SIZE)]
  def audit(u,access,p,n,v,ctx):assert any(lo<=p and p+n<=hi for lo,hi in allowed),('Block write outside declared outputs',hex(p),n)
  hook=u.hook_add(UC_HOOK_MEM_WRITE,audit)
  try:u.reg_write(UC_X86_REG_FPCW,0xe7f);u.emu_start(BLOCK,END,count=4000000)
  finally:u.hook_del(hook)
  assert u.reg_read(UC_X86_REG_EIP)==END and u.reg_read(UC_X86_REG_ESP)==self.block_sp
  assert u.reg_read(UC_X86_REG_EBP)==self.root_drive and u.reg_read(UC_X86_REG_ESI)==self.root_drive+0x40
  assert bytes(u.mem_read(self.block_sp+0x100,0x100))==caller
  after=bytearray(u.mem_read(self.block_sp,0x100));after[0x14:0x15]=entry[0x14:0x15]
  after[0x5c:0x64]=entry[0x5c:0x64]
  assert bytes(after)==entry,'Block modified unrelated entry stack'
  assert all(bytes(u.mem_read(p,n))==old for (p,n),old in zip(kw['inputs']+list(GLOBALS.items()),before))
  assert not self.unit_stack and not self.pending and self.context=='c' and self._block_zero is None
  assert bytes(u.mem_read(HEAP,HEAP_SIZE))==bytes(self.heap_expected)
  self.event('scratch',self.word(self.block_sp+0x14));self.context='s';self.actor=self.root_actor;self.drive=self.root_drive;self.audit_calls+=1
 def code(self,u,a,n,ctx):
  if self.geometry_active:
   assert (a,n) in self.allowed or a==END,('Uninspected Drive geometry instruction',hex(a))
   if a in ROOTS:self.geometry_entries[hex(a)]+=1
   return
  if not self.active:return
  sp=u.reg_read(UC_X86_REG_ESP);ecx=u.reg_read(UC_X86_REG_ECX)
  if a==0x4a1f38:self.emit('g','P',*self.coord(self.root_actor+0x88))
  if a==0x476920:
   assert ecx==CELLS[self.c['cell']]
   assert [self.word(sp+4+i*4) for i in range(3)]==[0x852998,1,1]
   scratch=self.word(sp+16);self.emit('g','S',self.cid(ecx),scratch)
   self.context='c';self.capacity=self.buffer=self.successes=self.grows=0
  if a==0x7072d0 and self.context=='c':
   id=self.oid(ecx);assert self.word(sp)==0x476a89 and self.word(sp+4)==0x852998
   self._block_zero=(ecx,bytes(u.mem_read(STATE,1012)),bytes(u.mem_read(ecx+0xa0,5)))
   self.unit_stack.append((self.word(sp),sp+16,self.actor,self.drive,self.padding))
   self.actor=ecx;self.drive=DRIVES[id];self.padding=self.c['padding'] if not id else self.c['secondary'][id-1]['padding'];self.context='s'
   self.emit('c','S',id,self.word(sp+8),self.word(sp+12));self.emit('c','P',0,0,0);self.counts['dispatch.'+str(id)]+=1
  if a==0x476a89 and self._block_zero:
   p,rng,mission=self._block_zero;assert bytes(u.mem_read(STATE,1012))==rng and bytes(u.mem_read(p+0xa0,5))==mission
   self.counts['block_zero_preserves_rng_queue']+=1;self._block_zero=None
  return super().code(u,a,n,ctx)
 def store(self,u,access,p,n,v,ctx):
  a=u.reg_read(UC_X86_REG_EIP)
  if self.geometry_active:
   if p in GLOBALS:assert n==GLOBALS[p];self.geometry_stores.append((a,p,n,v&((1<<(8*n))-1)))
   return
  if self.active and p==self.block_sp+0x14:
   assert a in (0x4a1f50,0x4a1f68) and n==1
   self.emit('g','E',(self.word(p)&0xffffff00)|(v&255));self.counts['elevated.'+str(v&255)]+=1
  return super().store(u,access,p,n,v,ctx)
