# SPDX-License-Identifier: GPL-3.0-or-later
"""Unchanged Cell damage with actual recursive wall and inclusive RNG children."""
from collections import Counter
import struct
from original_map_wall_update import *
from original_presentation import STOP
from verify_map_wall_damage import verify,RANGES
from unicorn.x86_const import UC_X86_REG_ESI
STATE=CELL+0x74000
class MapWallDamageOracle(MapWallUpdateOracle):
 def __init__(self,exe):
  super().__init__(exe);self.inspection=verify(exe.read_bytes());self.counts=Counter()
  self.damage_inputs=None
 def checked_call(self,root,args=(),ecx=0,edx=0,**kw):
  if root==0x475960:
   damage,levels,strength,force,disabled,seed=self.damage_inputs
   for i in range(256):
    self.put(TYPES+i*0x300+0x270,levels);self.put(TYPES+i*0x300+0x274,strength)
   self.put(0xa40774,force);self.put(0xa3d290,STATE-0x218)
   self.u.mem_write(STATE,pack([disabled,249,103,*[((seed+i*0x9e3779b9)&0xffffffff)^(0x12345678>>(i%13)) for i in range(250)]]))
   kw['writes']=[*kw['writes'],(STATE,1012)]
   kw['inputs']=[*kw['inputs'],(0xa40774,4),(0xa3d290,4)]
   root=0x475fe0;args=[damage]
  return super().checked_call(root,args,ecx,edx,**kw)
 def code(self,u,a,n,ctx):
  if a==STOP:return
  sp=u.reg_read(UC_X86_REG_ESP);receiver=u.reg_read(UC_X86_REG_ECX)
  if 0x475fe0<=a and a+n<=0x4763cf:
   if a in (0x475fe0,0x47604e,0x47616f,0x4761df,0x476223,0x4763b4,0x4763c3):self.counts[hex(a)]+=1
   if a==0x476068:
    overlay=u.reg_read(UC_X86_REG_EAX);shadow=u.reg_read(UC_X86_REG_ESI)
    self.events.extend([2,*words(u,overlay,4),*words(u,shadow,4)])
   return
  if 0x6388a0<=a and a+n<=0x63894d:
   if a==0x6388a0:
    assert receiver==STATE;self.events.extend([13,*words(u,sp+4,2)]);self.counts['random']+=1
   if a==0x63893e:
    self.events.extend([14,u.reg_read(UC_X86_REG_EAX),*words(u,STATE+4,2)]);self.counts['draw']+=1
   if a==0x638942:
    from unicorn.x86_const import UC_X86_REG_EDI
    if signed(u.reg_read(UC_X86_REG_EAX))>signed(u.reg_read(UC_X86_REG_EDI)):self.counts['rejected']+=1
   return
  if any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()):return super().code(u,a,n,ctx)
  caller=words(u,sp,1)[0]
  if not 0x475fe0<=caller<0x4763cf:return super().code(u,a,n,ctx)
  self.services+=1
  if a in (0x474eb0,0x475100):
   id=self.cell_id(receiver);kind=int(a==0x475100);output=words(u,sp+4,1)[0]
   assert STACK-0x2000<=output<STACK
   values=self.bounds(id,kind);self.events.extend([1,id,kind,*values]);u.mem_write(output,pack(values));ret(u,4,output)
  elif a==0x6a3020:
   assert receiver==TACTICAL and words(u,sp+20,1)==[0]
   self.events.extend([3,*words(u,sp+4,4)]);ret(u,20)
  elif a in (0x631570,0x54fb20,0x566340):
   assert receiver==0x8324e0;p=words(u,sp+4,1)[0];self.cell_id(p-0x24);q=words(u,p,1)[0]
   self.events.extend([4,q] if a==0x631570 else [10,0 if a==0x54fb20 else 2,q]);ret(u,4)
  elif a==0x548070:
   assert receiver==0x8324e0;p=words(u,sp+4,1)[0]
   # The fourth post-removal neighbor reuses the consumed root argument word.
   assert STACK-0x2000<=p<=STACK+4
   q=words(u,p,1)[0];id=self.query(q);self.events.extend([5,q,id]);ret(u,4,CELL+id*512)
  elif a==0x6ecb90:
   id=self.cell_id(receiver);assert u.reg_read(UC_X86_REG_EDX)&255==1
   self.events.extend([9,id]);ret(u,0)
  elif a==0x472540:
   id=self.cell_id(receiver);assert words(u,sp+4,1)==[0xffffffff];self.events.extend([8,id,0xffffffff])
   before=words(u,receiver+0x4c,1)[0];overlay=words(u,receiver+0x44,1)[0]
   value=before if self.recalc==0 else (before^((overlay+1)&7) if self.recalc==1 else (before^1 if self.recalc==2 else int(overlay!=0xffffffff)))
   self.put(receiver+0x4c,value);self.events.extend([12,id,0x4c,4,value]);ret(u,4)
  else:raise AssertionError('Uninspected damage child '+hex(a))
 def run_damage(self,prefix,v):
  self.damage_inputs=prefix;old=self.inspection
  self.inspection=old['wall']
  try:result=super().run('U',v)
  finally:self.inspection=old
  state=[self.u.mem_read(STATE,1)[0],*words(self.u,STATE+4,252)]
  return [str(self.u.reg_read(UC_X86_REG_EAX)),digest(state),*result]
