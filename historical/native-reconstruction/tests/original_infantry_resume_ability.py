# SPDX-License-Identifier: GPL-3.0-or-later
"""Actual ability, promotion, Type and QueueMission children under complete503C00."""
import struct
from original_walk_mission_resume import WalkMissionResumeOracle
from original_infantry_mission_resume import BASE,ACTOR,VT,TYPE
from original_presentation import STOP
from verify_infantry_resume_ability import verify,EXTRA,RANGES,TABLES
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_ESI
TYPE2=BASE+0xa000
class InfantryResumeAbilityOracle(WalkMissionResumeOracle):
 def __init__(self,exe):verify(exe.read_bytes());super().__init__(exe)
 def fixture_bytes(self,p,b):self.u.mem_write(p,b);self.expected[p-BASE:p-BASE+len(b)]=b
 def ability_event(self,kind,type=0,off=0):
  self.event(kind,type,off);self.ability_queries+=1
  if self.ability_queries==self.at and self.mutation:
   if self.mutation==1:self.fixture_bytes(ACTOR+0x118,struct.pack('<d',1.5))
   if self.mutation==2:self.fixture(ACTOR+0x5a8,TYPE2)
   if self.mutation==3:
    for offset in (0x26c+self.index,0x27e+self.index):self.fixture_bytes(TYPE+offset,bytes([self.u.mem_read(TYPE+offset,1)[0]^255]))
   self.event(32,self.mutation,self.at)
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  if any(lo<=a and a+n<=lo+size for lo,size in EXTRA.items()):
   if a in EXTRA:self.counts[hex(a)]+=1
   if a==0x6d7910:
    sp=u.reg_read(UC_X86_REG_ESP);assert u.reg_read(UC_X86_REG_ECX)==ACTOR and self.word(sp+4)==self.index;self.event(26,self.index)
   elif a==0x7133a0:assert u.reg_read(UC_X86_REG_ECX)==ACTOR+0x118;self.ability_event(27)
   elif a==0x713420:assert u.reg_read(UC_X86_REG_ECX)==ACTOR+0x118;self.ability_event(28)
   elif a==0x6c12c0:assert u.reg_read(UC_X86_REG_ECX)==ACTOR;self.ability_event(29)
   elif a==0x6d793b:
    p=u.reg_read(UC_X86_REG_EAX);assert p in (TYPE,TYPE2);self.ability_event(31,int(p==TYPE2))
   elif a in (0x6d794c,0x6d796a,0x6d7975):
    p=u.reg_read(UC_X86_REG_ESI);assert p in (TYPE,TYPE2);off=(0x27e if a==0x6d7975 else 0x26c)+self.index;self.ability_event(30,int(p==TYPE2),off)
   elif a==0x594cb0:
    sp=u.reg_read(UC_X86_REG_ESP);self.chosen=self.word(sp+4);assert self.word(sp+8)==0;self.event(19,self.chosen)
   return
  super().code(u,a,n,_)
 def write(self,u,access,p,n,v,_):
  if self.active and p in (ACTOR+0xa0,ACTOR+0xa4):
   assert n==(4 if p==ACTOR+0xa0 else 1);v&=(1<<(n*8))-1;self.expected[p-BASE:p-BASE+n]=v.to_bytes(n,'little');self.event(33,p-ACTOR,v);return
  super().write(u,access,p,n,v,_)
 def checked_call(self,a,args=(),ecx=0,edx=0,*,writes=(),inputs=()):
  assert a==0x503c00
  self.fixture(VT+0x80,0x6c12c0);self.fixture(VT+0x84,0x506950);self.fixture(VT+0x1d0,0x594cb0)
  self.fixture_bytes(ACTOR+0x118,struct.pack('<Q',self.vet));self.fixture_bytes(ACTOR+0xa4,b'\x80')
  for p,values in ((TYPE,(self.vbyte,self.ebyte)),(TYPE2,(self.vbyte^255,self.ebyte^255))):
   for off,value in zip((0x26c+self.index,0x27e+self.index),values):self.fixture_bytes(p+off,bytes([value]))
  if self.direct:a=0x6d7910;args=[self.index]
  # The two Type ability bytes and actual Type pointer/veterancy may mutate in
  # diagnostic callbacks. The whole arena still has exact final-state auditing.
  lo,hi=0x26c+self.index,0x27e+self.index
  inputs=[(p,n) for p,n in inputs if p!=TYPE]+[(p,n) for p,n in EXTRA.items()]+[(0x79a6f8,8),(TYPE,lo),(TYPE+lo+1,hi-lo-1),(TYPE+hi+1,0xd00-hi-1),(TYPE2,0xd00)]
  return super().checked_call(a,args,ecx,edx,writes=[*writes,(ACTOR+0xa0,5)],inputs=inputs)
 def run(self,f):
  self.direct=f[0]==5;self.index,self.vet,self.vbyte,self.ebyte,self.mutation,self.at=f[29:];self.ability_queries=0
  base=f[:29].copy();base[0]=0
  row=super().run(base)
  vet=int.from_bytes(self.u.mem_read(ACTOR+0x118,8),'little')
  return row+['A',str(vet&0xffffffff),str(vet>>32),str(int(self.word(ACTOR+0x5a8)==TYPE2)),*[str(self.u.mem_read(p+off,1)[0]) for p in (TYPE,TYPE2) for off in (0x26c+self.index,0x27e+self.index)],str(self.word(ACTOR+0xa0)),str(self.u.mem_read(ACTOR+0xa4,1)[0])]
