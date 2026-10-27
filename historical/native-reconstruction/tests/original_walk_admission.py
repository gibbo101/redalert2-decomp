# SPDX-License-Identifier: GPL-3.0-or-later
"""Actual Infantry admission inside unchanged complete queued Walk Process."""
import struct
from original_walk_queued import WalkQueuedOracle
from original_walk_head import WALK
from original_infantry_subcell import ARENA,ACTOR,HOUSE,CELLS
from original_presentation import STOP
from verify_walk_admission import verify,EXTRA
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_EDX,UC_X86_REG_ESP,UC_X86_REG_EIP
TYPE=ARENA+0x3000
class WalkAdmissionOracle(WalkQueuedOracle):
 def __init__(self,exe):
  self.joined_ready=False;self.in_admission=False;super().__init__(exe)
  self.inspection=verify(exe.read_bytes());self.joined_ready=True;self.active=True
  try:self.checked_call(0x491620,writes=[(0x851a70,32)],inputs=list(EXTRA.items()))
  finally:self.active=False
  assert struct.unpack('<16h',self.u.mem_read(0x851a70,32))==(0,-1,1,-1,1,0,1,1,0,1,-1,1,-1,0,-1,-1)
 def checked_call(self,root,*args,**kwargs):
  if self.joined_ready and root==0x71dff0:
   if self.prepare_join:
    u=self.u;o=self.options;self.put(ACTOR+0x5a8,TYPE);self.put(TYPE+0x5a4,o[2]);self.put(ACTOR+0x30,0)
    u.mem_write(ACTOR+0x32d,bytes([o[0]]));u.mem_write(ACTOR+0x370,bytes([o[1]]));self.put(0xa40774,o[3])
    self.put(0x8661cc,0);self.put(0x8661d8,0)
    u.mem_write(0x850ea0,struct.pack('<108I',*[o[4]]*108))
    for i,c in enumerate(CELLS):
     self.put(c+0x24,(100+i)|(100<<16));u.mem_write(c+0x116,struct.pack('<h',-1));u.mem_write(c+0x11c,bytes([o[9+i]]))
     for off,val in ((0xec,o[5+i]),(0xe4,ACTOR if o[7+i]==0 else 0),(0xe8,ACTOR if o[7+i]==0 else 0)):self.put(c+off,val)
    self.prepare_join=False
   kwargs['inputs']=[*kwargs['inputs'],*EXTRA.items(),(0x851a70,32),(0x850ea0,432),(0xa40774,4),(0x8661cc,16),
    (0x7a3540+0x194,8),(0x79a738,4)]
  return super().checked_call(root,*args,**kwargs)
 def trace_admission(self,k,a=0,b=0,c=0):self.event(k,a,b,c)
 def code(self,u,a,n,ctx):
  if not self.joined_ready or not self.active or a==STOP:return super().code(u,a,n,ctx)
  sp=u.reg_read(UC_X86_REG_ESP);ecx=u.reg_read(UC_X86_REG_ECX)
  if a==0x503190:
   target,direction,level,zero,one=self.ints(sp+4,5);assert ecx==ACTOR and target in CELLS and (zero,one)==(0,1)
   self.event('I',CELLS.index(target),direction,level,zero,one);self.counts['actual_admission']+=1;self.in_admission=True
  if self.in_admission and a==0x548070:
   assert ecx==0x8324e0;point=struct.unpack('<hh',u.mem_read(self.word(sp+4),4))
   assert 0<=point[0]<512 and 0<=point[1]<512,('Diagnostic admission map out of range',point)
   self.trace_admission('L',*point);self.counts['admission_map']+=1;self.ret(4,CELLS[(point[0]^point[1])&1]);return
  if any(lo<=a and a+n<=lo+size for lo,size in EXTRA.items()):
   assert not (0x50334d<=a<0x50337c or 0x50338a<=a<0x503425 or 0x50345b<=a<0x5038cb or
    0x5038d7<=a<0x503947 or 0x5039fb<=a<0x503a1e),('Unjoined Infantry child',hex(a))
   if a in EXTRA:self.counts[hex(a)]+=1
   if a==0x47a130:self.registry_cell=CELLS.index(ecx)
   elif a in (0x47a152,0x47a155):
    assert u.reg_read(UC_X86_REG_EAX)==0;self.trace_admission('r',self.registry_cell,-1)
   elif a==0x476ac0:self.trace_admission('N',CELLS.index(ecx),self.ints(sp+4,1)[0])
   elif a==0x4c8730:
    target,direction,_,__,previous=self.ints(sp+4,5);assert ecx==ACTOR and previous==0
    self.trace_admission('H',CELLS.index(target),direction,-1)
   elif a==0x503974:
    index=u.reg_read(UC_X86_REG_EDX);assert index<108
    self.trace_admission('S',index,self.ints(0x850ea0+4*index,1)[0]);self.counts['admission_speed']+=1
   elif a==0x4e5500:
    assert ecx==HOUSE;owner=self.ints(sp+4,1)[0];assert owner==self.ints(HOUSE+0x30,1)[0]
    self.trace_admission('i',0,owner);self.counts['admission_house']+=1
   elif a==0x503a3a:
    result=u.reg_read(UC_X86_REG_EAX);self.trace_admission('a',result);assert result==0,('Unjoined nonzero continuation',result)
    self.in_admission=False
   return
  return super().code(u,a,n,ctx)
 def store(self,u,access,p,n,value,ctx):
  if self.active and self.joined_ready and u.reg_read(UC_X86_REG_EIP) in (0x4c87c4,0x4c892c,0x4c889f):
   self.trace_admission('W',1 if n==1 else 0,n,value if value<2**31 else value-2**32);return
  return super().store(u,access,p,n,value,ctx)
 def run_joined(self,v,options):
  self.options=options;self.prepare_join=True;self.in_admission=False;return self.run_queued(v)
