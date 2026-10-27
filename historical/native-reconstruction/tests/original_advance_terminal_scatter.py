# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete unpatched Advance with actual terminal coordinates and clears."""
import struct
from original_advance_nearby_scatter import AdvanceNearbyScatterOracle
from original_advance_cell_scatter import AdvanceCellScatterOracle
from original_cell_unit_scatter_world import HEAP,HEAP_SIZE
from original_unit_scatter_world import ACTOR,DRIVE,ARENA,SIZE,CELLS,STOP,signed
from verify_advance_cell_scatter import GLOBALS
from verify_advance_terminal import STORES
from verify_advance_terminal_scatter import verify,RANGES,TABLES
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EIP
class AdvanceTerminalScatterOracle(AdvanceNearbyScatterOracle):
 ranges=RANGES;tables=TABLES;inspection_verify=staticmethod(verify)
 def __init__(self,exe):
  self.terminal_active=False;self.terminal_pending=[];super().__init__(exe)
 def prepare_join(self,c):
  super().prepare_join(c);self.terminal_active=False;self.terminal_pending=[]
  self.terminal_flags=list(c.get('terminal_flags',[1,0,0]))
  for off,v in zip((0x7d,0x76,0x7a),self.terminal_flags):self.u.mem_write(self.root_actor+off,bytes([v]))
 def effect(self,values):
  if values[0]<0:return
  for off,v in zip((0x7d,0x76,0x7a),values):
   self.u.mem_write(self.root_actor+off,bytes([v]));self.expected[self.root_actor-ARENA+off]=v
  self.emit('t','E',*values)
 def checked_call(self,root,args=(),ecx=0,edx=0,**kw):
  if root!=0x4a1000:return super().checked_call(root,args,ecx,edx,**kw)
  kw['writes']=[*kw['writes'],(HEAP,HEAP_SIZE)]
  kw['inputs']=[*kw['inputs'],*GLOBALS.items(),*[(0xa403b0+32*row[4],32) for row in self.c['objects']]]
  result=AdvanceCellScatterOracle.checked_call(self,root,args,ecx,edx,**kw)
  returned=self.u.reg_read(UC_X86_REG_EAX)&255;assert returned in (0,1)
  self.counts['root_return.'+str(returned)]+=1
  if self.c.get('terminal_record'):self.event('return',returned,self.byte(self.root_actor+0x7d),self.byte(self.root_actor+0x76),self.byte(self.root_actor+0x7a))
  assert not self.unit_stack and not self.pending and not self.terminal_pending and self.context=='s' and self._block_zero is None
  assert bytes(self.u.mem_read(HEAP,HEAP_SIZE))==bytes(self.heap_expected)
  self.event('scratch',self.word(self.block_sp+0x14))
  self.event('moving',self.byte(self.root_actor+0x74),self.byte(self.root_actor+0x5a0),self.word(self.root_actor+0x2e0)&65535,self.word(self.root_actor+0x2e4)&65535,signed(self.word(self.root_actor+0x2e8)),signed(self.word(self.root_actor+0x2f0)),self.word(self.root_actor+0x2f4)&65535,*struct.unpack('<Q',self.u.mem_read(self.root_actor+0x468,8)))
  self.terminal_active=False;return result
 def code(self,u,a,n,ctx):
  if not self.active or self.geometry_active or self.direction_active or a==STOP:return super().code(u,a,n,ctx)
  if a==0x4a2166:self.terminal_active=True;self.counts['terminal_entry']+=1
  if not self.terminal_active:return super().code(u,a,n,ctx)
  sp=u.reg_read(UC_X86_REG_ESP);ecx=u.reg_read(UC_X86_REG_ECX);arg=lambda i:self.word(sp+4+4*i)
  if self.terminal_pending and self.terminal_pending[-1][:2]==(a,sp):
   _,_,kind,out=self.terminal_pending.pop();assert u.reg_read(UC_X86_REG_EAX)==out
   self.emit('t',kind,*((*self.cell(out),0) if kind=='C' else self.coord(out)))
  if a in (0x6fe610,0x6fd630,0x4ca2b0):
   assert ecx==self.root_actor and self.context=='s'
   if a==0x6fe610:
    assert arg(0)==2;self.emit('v','N',2);self.effect(self.c.get('notify_flags',[-1]*3));self.ret(4,0)
   elif a==0x6fd630:
    assert [arg(0),arg(1)]==[0,1];value=self.c['mission_return'];self.emit('t','B',0,1,value);self.ret(8,value)
   else:
    self.emit('v','P');value=self.c.get('post_return',0)
    if self.c.get('terminal_record'):self.emit('t','P',value)
    self.effect(self.c.get('post_flags',[-1]*3));self.ret(0,value)
   self.counts['supplied.'+hex(a)]+=1;return
  assert (a,n) in self.allowed,('Uninspected terminal caller instruction',hex(a));self.instructions.add(a)
  if a in self.ranges:self.counts[hex(a)]+=1
  if a in (0x410290,0x4ca6f0,0x41b320):
   if a==0x410290:assert ecx in CELLS and arg(1)==self.root_actor;self.emit('t','Q',self.cid(ecx));kind='q';size=8
   elif a==0x4ca6f0:assert ecx==self.root_actor and arg(1)==self.root_actor;self.emit('t','U');kind='u';size=8
   else:assert ecx==self.root_actor;kind='C';size=4
   self.terminal_pending.append((self.word(sp),sp+4+size,kind,arg(0)))
  if a==0x594770:self.emit('t','M',signed(self.word(self.root_actor+0xa0) if self.word(self.root_actor+0x98)==0xffffffff else self.word(self.root_actor+0x98)))
  if a==0x4a21ed:self.counts['terminal_arrived']+=1
  if a==0x4a227a:self.counts['terminal_clears']+=1
 def store(self,u,access,p,n,v,ctx):
  a=u.reg_read(UC_X86_REG_EIP)
  if self.active and self.terminal_active and ARENA<=p and p+n<=ARENA+SIZE:
   owner,off,width=STORES[a];assert (p,n)==((self.root_drive if owner=='d' else self.root_actor)+off,width)
   value=v&((1<<(n*8))-1);self.emit('v','A' if owner=='a' else 'L',off,value)
   self.expected[p-ARENA:p-ARENA+n]=value.to_bytes(n,'little');self.counts['terminal_store.'+hex(a)]+=1;return
  return super().store(u,access,p,n,v,ctx)
