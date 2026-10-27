# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete unpatched Advance root, with one shared Cell/Unit child guest."""
import struct
from original_advance_cell_scatter import AdvanceCellScatterOracle
from original_cell_nearby_scatter import CellNearbyScatterOracle
from original_cell_unit_scatter_world import HEAP,HEAP_SIZE
from original_unit_scatter_world import ACTOR,DRIVE,DRIVES,OBJECTS,TYPES,HOUSES,ARENA,SIZE,STACK,STOP,pack,signed
from verify_advance_nearby_scatter import verify,RANGES,TABLES
from verify_ground_drive_stores import STORE_SITES
from verify_advance_cell_scatter import GLOBALS
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EIP
class AdvanceNearbyScatterOracle(AdvanceCellScatterOracle):
 ranges=RANGES;tables=TABLES;inspection_verify=staticmethod(verify)
 def __init__(self,exe):
  self.direction_active=False;self.direction_entries=0;super().__init__(exe);self.direction_active=True
  try:self.checked_call(0x4916d0,writes=[(0x851ac0,64)],inputs=[(0x4916d0,116)])
  finally:self.direction_active=False
  self.direction_values=struct.unpack('<16i',self.u.mem_read(0x851ac0,64))
 def prepare_join(self,c):
  super().prepare_join(c);self.block_sp=STACK-0xf4
  u=self.u
  for off,value in ((0xb59,0),(0xba4,0),(0xaa0,0)):u.mem_write(TYPES[c['type_indexes'][0]]+off,bytes([value]))
  self.put(TYPES[c['type_indexes'][0]]+0x5a0,c['speed']);self.put(TYPES[c['type_indexes'][0]],0x7ae328)
  for h in HOUSES:self.put(h+0x34,ARENA+0x3f800)
  self.put(ARENA+0x3f800+0x12c,0x3f800000);self.put(self.root_actor+0x5b4,-1);u.mem_write(self.root_actor+0x470,struct.pack('<d',1.))
  for off,value in ((0x74,c['marked']),(0x76,0),(0x7a,0),(0x7d,1)):u.mem_write(self.root_actor+off,bytes([value]))
  u.mem_write(self.root_actor+0x468,struct.pack('<d',1.))
  self.put(self.root_drive+0x4c,c['acc']);u.mem_write(self.root_drive+0x63,bytes([c['driving']]))
  u.mem_write(self.root_drive+0x62,b'\0');u.mem_write(self.root_drive+0x50,struct.pack('<Q',c['percentage']))
 def original_entry(self,c):
  self.context='s';self.block_sp=STACK-0xf4
  self.u.mem_write(STACK-0x2000,b'\xa7'*0x2000);self.put(self.block_sp+0x14,c['scratch'])
  self.event('geometry',*self.geometry_values);self.event('directions',*self.direction_values)
  return 0x4a1000,[c['suppress']],self.root_drive
 def checked_call(self,root,args=(),ecx=0,edx=0,**kw):
  if root!=0x4a1000:return super().checked_call(root,args,ecx,edx,**kw)
  kw['writes']=[*kw['writes'],(HEAP,HEAP_SIZE)]
  kw['inputs']=[*kw['inputs'],*GLOBALS.items(),*[(0xa403b0+32*row[4],32) for row in self.c['objects']]]
  result=super().checked_call(root,args,ecx,edx,**kw)
  assert self.u.reg_read(UC_X86_REG_EAX)&255==0
  assert not self.unit_stack and not self.pending and self.context=='s' and self._block_zero is None
  assert bytes(self.u.mem_read(HEAP,HEAP_SIZE))==bytes(self.heap_expected)
  self.event('scratch',self.word(self.block_sp+0x14))
  self.event('moving',self.byte(self.root_actor+0x74),self.byte(self.root_actor+0x5a0),self.word(self.root_actor+0x2e0)&65535,self.word(self.root_actor+0x2e4)&65535,signed(self.word(self.root_actor+0x2e8)),signed(self.word(self.root_actor+0x2f0)),self.word(self.root_actor+0x2f4)&65535,*struct.unpack('<Q',self.u.mem_read(self.root_actor+0x468,8)))
  return result
 def code(self,u,a,n,ctx):
  if self.direction_active:
   assert (a,n) in self.allowed
   if a==0x4916d0:self.direction_entries+=1
   return
  if self.geometry_active:return super().code(u,a,n,ctx)
  if not self.active or a==STOP:return
  assert not 0x4a05f0<=a<0x4a0bbb and not 0x4a2670<=a<0x4a4725,'Process/preparation entered Advance-only proof'
  sp=u.reg_read(UC_X86_REG_ESP);ecx=u.reg_read(UC_X86_REG_ECX);arg=lambda i:self.word(sp+4+4*i)
  if a==0x4a2174:raise AssertionError('Unjoined terminal target branch entered')
  if a==0x4a1c9f:
   result=u.reg_read(UC_X86_REG_EAX);assert result in (0,2,6,7);self.counts['Advance_admission.'+str(result)]+=1
  if a==0x4a1f8d:
   if self.context=='c':self.context='s';self.counts['Advance6_continuation']+=1
  # These are declared supplied boundaries, not substituted admission/movement.
  if a in (0x4c2e60,0x7079e0,0x6fe610,0x4ca2b0):
   assert ecx==self.root_actor and self.context=='s'
   if a==0x4c2e60:
    value=arg(0);assert value in (0,1);self.emit('v','M',value,self.byte(self.root_actor+0x74))
    if self.c['mark_effect']:
     u.mem_write(self.root_actor+0x74,bytes([value]));self.expected[self.root_actor-ARENA+0x74]=value
    self.ret(4,1)
   elif a==0x7079e0:self.event('v','U',*self.coord(arg(0)));self.ret(4,0)
   elif a==0x6fe610:self.emit('v','N',arg(0));self.ret(4,0)
   else:self.emit('v','P');self.ret(0,0)
   self.counts['supplied.'+hex(a)]+=1;return
  if self.context=='s' and not self.unit_stack and a in (0x705020,0x70a2d0):
   assert (a,n) in self.allowed;self.instructions.add(a);return
  return super().code(u,a,n,ctx)
 def store(self,u,access,p,n,v,ctx):
  if self.geometry_active:return super().store(u,access,p,n,v,ctx)
  if not self.active:return
  a=u.reg_read(UC_X86_REG_EIP);value=v&((1<<(n*8))-1)
  if p==self.block_sp+0x14:
   assert (a,n) in ((0x4a164f,2),(0x4a1f50,1),(0x4a1f68,1))
   raw=(self.word(p)&(0xffff0000 if n==2 else 0xffffff00))|value
   self.emit('g','I' if n==2 else 'E',raw);self.counts['scratch.'+hex(a)]+=1
  if self.context=='s' and ARENA<=p and p+n<=ARENA+SIZE:
   actor_fields=((0x74,1),(0x88,4),(0x8c,4),(0x90,4),(0x5a0,1),(0x5a1,1))
   if self.root_actor<=p<self.root_actor+0x1000:
    off=p-self.root_actor
    assert (off,n) in actor_fields or (0x2e0<=off and off+n<=0x2f8) or (0x468<=off and off+n<=0x470),(hex(a),hex(p),n)
    if (off,n) in actor_fields:self.emit('v','A',off,value)
    self.counts['actor_store.'+hex(a)]+=1
   elif self.root_drive<=p<self.root_drive+0x100:
    assert STORE_SITES.get(a)==(p-self.root_drive,n),(hex(a),hex(p),n)
    self.emit('v','L',p-self.root_drive,value);self.counts['drive_store.'+hex(a)]+=1
   else:raise AssertionError(('Unexpected Advance owner write',hex(a),hex(p),n))
   self.expected[p-ARENA:p-ARENA+n]=value.to_bytes(n,'little');return
  # Parent block observer assumes every +14 write is a byte. Caller word
  # production was audited above; forward to the unchanged Cell/Unit observer.
  return CellNearbyScatterOracle.store(self,u,access,p,n,v,ctx)
