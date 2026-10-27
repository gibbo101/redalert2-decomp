# SPDX-License-Identifier: GPL-3.0-or-later
"""Unmodified complete Process root and shared terminal/nearby child guest."""
import struct
from unicorn import UC_HOOK_MEM_READ
from unicorn.x86_const import *
from original_advance_terminal_scatter import AdvanceTerminalScatterOracle
from original_advance_cell_scatter import AdvanceCellScatterOracle
from original_cell_nearby_scatter import CellNearbyScatterOracle
from original_unit_scatter_world import *
from original_cell_unit_scatter_world import HEAP,HEAP_SIZE,RULES
from verify_advance_cell_scatter import GLOBALS
from verify_process_terminal_scatter import verify,RANGES,TABLES
from verify_ground_drive_process import RANGES as PROCESS
CALLERS=(0x4a066b,0x4a0758,0x4a0ba3)
class ProcessTerminalScatterOracle(AdvanceTerminalScatterOracle):
 ranges=RANGES;tables=TABLES;inspection_verify=staticmethod(verify)
 def __init__(self,exe):
  self.in_advance=False;super().__init__(exe);self.u.hook_add(UC_HOOK_MEM_READ,self.read)
 def prepare_join(self,c):
  super().prepare_join(c);u=self.u;self.in_advance=False;self.process_pending=None;self.gate_return=None;self.next_return=None
  self.put(self.root_drive+0x58,c['process_track']);u.mem_write(self.root_drive+0x61,b'\0');u.mem_write(self.root_drive+0x64,b'\0');u.mem_write(self.root_actor+0x5a1,bytes([c['process_wait_flag']]));u.mem_write(self.root_drive+0x62,bytes([c['process_rotating']]))
  # Explicit ordinary healthy inputs; inherited arena poison is not health.
  self.put(self.root_actor+0x6c,400);self.put(TYPES[self.c['type_indexes'][0]]+0xa0,400)
  u.mem_write(RULES+0x1368,struct.pack('<d',.5))
  u.mem_write(self.root_drive+0x1c,pack(c['process_ramp'],c['process_ramp'],99,7,2,2));self.put(self.root_actor+0x450,0);self.put(self.root_actor+0x238,0)
  for off in (0x57a,0x57b,0x325,0x32d):u.mem_write(self.root_actor+off,b'\0')
  u.mem_write(self.root_actor+0x468,struct.pack('<Q',c['process_percentage']))
  u.mem_write(self.root_actor+0x530,pack(*c['process_retry_timer']));u.mem_write(self.root_actor+0x558,pack(*c['process_wait_timer']))
  u.mem_write(RULES+0x13c8,bytes(8));u.mem_write(RULES+0x690,struct.pack('<2d',1.,1.2));self.put(RULES+0x13d0,c['process_wait_duration']);self.put(RULES+0x9c,0)
 def original_entry(self,c):
  self.context='s';self.last_scratch=c['scratch'];self.block_sp=STACK-0x11c;self.u.mem_write(STACK-0x2000,b'\xa7'*0x2000);self.put(self.block_sp+0x14,c['scratch'])
  self.event('geometry',*self.geometry_values);self.event('directions',*self.direction_values)
  return 0x4a05f0,[self.root_drive+4],0
 def checked_call(self,root,args=(),ecx=0,edx=0,**kw):
  if root!=0x4a05f0:return super().checked_call(root,args,ecx,edx,**kw)
  kw['writes']=[*kw['writes'],(HEAP,HEAP_SIZE)]
  kw['inputs']=[*kw['inputs'],*GLOBALS.items(),*[(0xa403b0+32*row[4],32) for row in self.c['objects']]]
  result=AdvanceCellScatterOracle.checked_call(self,root,args,ecx,edx,**kw)
  returned=self.u.reg_read(UC_X86_REG_EAX)&255;assert returned in (0,1)
  assert not self.in_advance and not self.terminal_active and not self.process_pending and self.gate_return is self.next_return is None
  assert not self.unit_stack and not self.pending and not self.terminal_pending and self.context=='s' and self._block_zero is None
  assert bytes(self.u.mem_read(HEAP,HEAP_SIZE))==bytes(self.heap_expected)
  self.counts['Process_return.'+str(returned)]+=1
  self.event('process-return',returned,*[self.byte(self.root_actor+off) for off in (0x7d,0x76,0x7a)])
  self.event('process-state',self.byte(self.root_drive+0x60),self.byte(self.root_drive+0x61),self.byte(self.root_drive+0x64),*struct.unpack('<6i',self.u.mem_read(self.root_drive+0x1c,24)),self.byte(self.root_drive+0x62),self.byte(self.root_actor+0x57b),self.byte(self.root_actor+0x57a),*self.cell(self.root_actor+0x450),*struct.unpack('<Q',self.u.mem_read(self.root_actor+0x468,8)))
  self.event('scratch',self.last_scratch);self.event('moving',self.byte(self.root_actor+0x74),self.byte(self.root_actor+0x5a0),self.word(self.root_actor+0x2e0)&65535,self.word(self.root_actor+0x2e4)&65535,signed(self.word(self.root_actor+0x2e8)),signed(self.word(self.root_actor+0x2f0)),self.word(self.root_actor+0x2f4)&65535,*struct.unpack('<Q',self.u.mem_read(self.root_actor+0x468,8)))
  return result
 def code(self,u,a,n,ctx):
  if not self.active or self.geometry_active or self.direction_active or a==STOP:return super().code(u,a,n,ctx)
  sp=u.reg_read(UC_X86_REG_ESP);ecx=u.reg_read(UC_X86_REG_ECX);arg=lambda i:self.word(sp+4+4*i)
  if a in CALLERS:
   assert self.in_advance and self.context=='s';caller=CALLERS.index(a);value=u.reg_read(UC_X86_REG_EAX)&255
   self.emit('p','c',caller,value,self.byte(self.root_actor+0x7d));self.counts[f'Advance_return.{caller}.{value}']+=1
   self.last_scratch=self.word(self.block_sp+0x14);self.in_advance=self.terminal_active=False
  if a==0x4a1000:
   assert not self.in_advance and ecx==self.root_drive and self.word(sp) in CALLERS
   assert sp-0xf4==self.block_sp
   # Each invocation owns a new uninitialized temporary frame. Supply its bytes
   # at this boundary, rather than treating dead preparation stack as game state.
   self.put(self.block_sp+0x14,self.c['scratch'])
   self.in_advance=True;caller=CALLERS.index(self.word(sp));self.emit('p','C',caller,arg(0));self.counts['Advance_caller.'+str(caller)]+=1
  if self.in_advance:return super().code(u,a,n,ctx)
  self.returned(a,sp)
  if self.process_pending and self.process_pending[:2]==(a,sp):
   _,_,out,kind=self.process_pending;self.process_pending=None;assert u.reg_read(UC_X86_REG_EAX)==out
   if kind=='C':self.emit('d','C',*self.cell(out),0)
  if self.gate_return==(a,sp):self.gate_return=None
  if self.next_return==(a,sp):self.next_return=None
  if a==0x6fe610:
   assert ecx==self.root_actor and arg(0)==0;self.emit('v','N',0);self.effect(self.c['notify_flags']);self.ret(4,0);self.counts['supplied.notify0']+=1;return
  if a==0x6fd630:
   assert ecx==self.root_actor and [arg(0),arg(1)]==[0,1];self.emit('t','B',0,1,self.c['mission_return']);self.ret(8,self.c['mission_return']);self.counts['supplied.mission414']+=1;return
  if a==0x4c3000:
   assert ecx==self.root_actor and arg(1)==0 and arg(2) in (0,1,2)
   if self.word(sp)==0x4a3a0a:self.emit('p','b',arg(2))
   self.emit('p','B');self.counts['supplied.failed_pathfinder']+=1;self.ret(12,0);return
  if a==0x4c2ef0:
   assert ecx==self.root_actor;self.emit('p','J');self.counts['supplied.accessibility']+=1;self.ret(4,0);return
  if a==0x707980:
   assert ecx==self.root_actor;self.emit('p','E',*self.coord(arg(0)));self.ret(4,0);return
  if a==0x4c2e60:
   assert ecx==self.root_actor;v=arg(0);assert v in (0,1);self.emit('v','M',v,self.byte(self.root_actor+0x74))
   if self.c['mark_effect']:u.mem_write(self.root_actor+0x74,bytes([v]));self.expected[self.root_actor-ARENA+0x74]=v
   self.ret(4,1);return
  if a==0x7053f0:
   assert ecx==self.root_actor and [arg(0),arg(1)]==[0,1]
   self.destination_target=self.current_target=0;self.current_padding=self.padding;self.enter('S',8,context='d');self.counts['Process_actual_Unit410']+=1
   assert (a,n) in self.allowed;self.instructions.add(a);return
  if self.context=='d':
   if a==0x49fef0:self.emit('d','m',0,0,a)
   elif a==0x705020:self.emit('d','T')
   else:return CellNearbyScatterOracle.code(self,u,a,n,ctx)
   assert (a,n) in self.allowed;self.instructions.add(a);return
  if self.context=='a':return CellNearbyScatterOracle.code(self,u,a,n,ctx)
  if a==0x4102ba:
   point=self.coord(u.reg_read(UC_X86_REG_EAX));self.current_padding=point[1];self.observed_point=point;self.emit('d','Q',*point)
  if a==0x41b320:
   self.process_pending=(self.word(sp),sp+8,arg(0),'C')
  if a==0x47cf80:self.emit('i','K',11)
  if a==0x594770 and not self.gate_return and not self.next_return:self.emit('p','M',signed(self.word(self.root_actor+0xa0) if self.word(self.root_actor+0x98)==0xffffffff else self.word(self.root_actor+0x98)))
  if a==0x475d60:self.emit('p','T',*self.cell(ecx+0x24),0)
  if a==0x4a062b:self.put(sp+0x14,self.c['process_padding'])
  if a==0x4a2670:
   self.put(sp-0x14,self.c['process_padding']);self.counts['preparation']+=1
  if a in (0x4a34f1,0x4a40ea):self.counts[f'preparation_admission.{a:x}.{u.reg_read(UC_X86_REG_EAX)&255}']+=1
  if a in (0x4a3732,0x4a422b):self.put(sp+(0x48 if a==0x4a3732 else 0x54),self.c['process_first_padding' if a==0x4a3732 else 'process_second_padding'])
  if a in (0x4a3c2b,0x4a44fe):self.put(sp+0x54,self.c['process_padding'])
  if a==0x4a367f:self.put(sp+0x54,self.c['process_wait_padding'])
  if a==0x4a28e2 or a==0x4a3f45:pass
  if a==0x4a0a9a:self.counts['Process_actual_Move_To']+=1
  if a==0x49fe30:
   self.enter('S',16,context='d');return CellNearbyScatterOracle.code(self,u,a,n,ctx)
  if a==0x55acd0:
   self.gate_return=(self.word(sp),sp+12);assert ecx==MAP
  if a==0x705160:
   self.next_return=(self.word(sp),sp+12);self.counts['actual_nextCell']+=1
  if self.next_return:
   if a==0x6d7910:self.emit('a','b',self.oid(self.root_actor),17,0)
   if a in (0x7133a0,0x713420):self.emit('a','v',self.oid(self.root_actor),1 if a==0x7133a0 else 2,0)
  if self.gate_return and a in (0x70a2d5,0x453c45):self.emit('a','K',self.oid(ecx),u.reg_read(UC_X86_REG_EAX),0)
  # Parent roots/ordinary pure helpers deliberately bypass Advance-only assertions.
  if any(lo<=a and a+n<=lo+size for lo,size in PROCESS.items()) and a not in (0x548000,0x548070,0x55a280,0x703040):
   assert (a,n) in self.allowed;self.instructions.add(a)
   if a in self.ranges:self.counts[hex(a)]+=1
   return
  if 0x705020<=a<0x705027 or 0x70a2d0<=a<0x70a2d6 or a in (0x47cf80,0x594770,0x41b320,0x4cd9b0,0x4cd9b2,0x4cd9b8) or self.gate_return and a in (0x70a2d0,0x70a2d5,0x453c40,0x453c45):
   assert (a,n) in self.allowed;self.instructions.add(a);return
  assert (a,n) in self.allowed,('Uninspected Process child',hex(a),hex(self.word(sp)),hex(ecx),self.context)
  return CellNearbyScatterOracle.code(self,u,a,n,ctx)
 def read(self,u,access,p,n,value,ctx):
  if not self.active or self.in_advance:return
  ip=u.reg_read(UC_X86_REG_EIP)
  if ip in (0x4a07a3,0x4a07ad):
   axis=int(ip==0x4a07ad);target=u.reg_read(UC_X86_REG_EBP)-0x24
   assert (p,n)==(target+0x24+2*axis,2);self.emit('i','W',axis,self.cid(target),struct.unpack('<h',u.mem_read(p,2))[0])
 def store(self,u,access,p,n,v,ctx):
  if not self.active or self.geometry_active or self.direction_active or self.in_advance:return super().store(u,access,p,n,v,ctx)
  ip=u.reg_read(UC_X86_REG_EIP);value=v&((1<<(8*n))-1)
  if ARENA<=p and p+n<=ARENA+SIZE:
   if self.context=='d' and ip in (0x4c81c4,0x49ffa0,0x49ffa7,0x49ffb0,0x49ff94):
    if ip==0x4c81c4:assert (p,n,value)==(self.root_actor+0x494,4,0);self.emit('d','a',0x494,4,0)
    else:
     off=p-self.root_drive;assert (off,n) in ((0x34,4),(0x38,4),(0x3c,4),(0x50,8))
     if n==4:assert value==0
     self.emit('d','d',off,n,value if value<1<<63 else value-(1<<64))
   elif ip in (0x4cd9b2,0x4cd9b8):
    off=0x490 if ip==0x4cd9b2 else 0x494;assert (p,n,value)==(self.root_actor+off,4,0);self.emit('d','a',off,4,value)
   elif 0x4a05f0<=ip<0x4a0bbb or 0x4a2670<=ip<0x4a4725 or 0x4c2df0<=ip<0x4c2e4c:
    if self.root_drive<=p<self.root_drive+0x100:
     off=p-self.root_drive;assert (0x1c<=off and off+n<=0x34) or (0x34<=off and off+n<=0x65)
     if off<0x34:self.emit('p','R',off,value,0)
     elif off!=0x50:self.emit('v','L',off,value,0)
    else:
     off=p-self.root_actor;assert (off,n) in ((0x450,4),(0x468,4),(0x46c,4),(0x530,4),(0x534,4),(0x538,4),(0x558,4),(0x55c,4),(0x560,4),(0x57a,1),(0x57b,1),(0x5a1,1)) or 0x4d0<=off and off+n<=0x530 or 0x2e0<=off and off+n<=0x2f8,(hex(ip),hex(p),n)
     if off in (0x468,0x46c):self.emit('p','A',off,value,0)
     elif not 0x2e0<=off<0x2f8:self.emit('v','A',off,value,0)
   else:return CellNearbyScatterOracle.store(self,u,access,p,n,v,ctx)
   self.expected[p-ARENA:p-ARENA+n]=value.to_bytes(n,'little');self.writes[hex(ip)]+=1;return
  return CellNearbyScatterOracle.store(self,u,access,p,n,v,ctx)
