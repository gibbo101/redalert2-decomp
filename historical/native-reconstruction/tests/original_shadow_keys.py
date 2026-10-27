# SPDX-License-Identifier: GPL-3.0-or-later
"""Actual ordinary Unit seed/flat Drive matrix and complete Foot shadow forwarding."""
import struct
from original_staging import ShadowDispatchOracle
from original_presentation import STACK
from shadow_key_profiles import address
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import *

class ShadowKeysOracle(ShadowDispatchOracle):
 def __init__(self,exe,*,allow_patched=False):
  super().__init__(exe,allow_patched=allow_patched);self.services={};self.host_point_writes=0
 def va(self,disc_va):return address(self.profile,disc_va)
 def actor_inputs(self):
  return [(self.unit,0x800),(self.loco,0x100),(self.cell,0x180),(self.kind,0xc00),(self.lvtable,0x34)]
 @staticmethod
 def preserve_locals(before,after,outputs):
  a,b=bytearray(before),bytearray(after)
  for p,n in outputs:a[p:p+n]=b[p:p+n]
  if a!=b:raise AssertionError('Shadow-key unrelated caller locals changed')
 def supplied_point(self,p,values,*,block=False):
  lo,hi=(STACK+0x3c,STACK+0x44) if block else (STACK-0x2000,STACK)
  if not lo<=p or p+8>hi:raise AssertionError('Supplied shadow point outside caller output')
  self.u.mem_write(p,struct.pack('<2i',*values));self.host_point_writes+=1

 def prepare_actor(self,heading=0):
  self.unit=0x1100000;self.loco=0x1101000;self.cell=0x1103000;self.kind=0x1104000;self.lvtable=0x1105000
  self.u.mem_write(self.unit,bytes(0x800));self.u.mem_write(self.loco,bytes(0x100));self.u.mem_write(self.cell,bytes(0x180));self.u.mem_write(self.kind,bytes(0xc00))
  self.put(self.loco+4,self.lvtable);self.put(self.loco+12,self.unit);self.put(self.unit+0x564,self.loco+4);self.put(self.unit+0x5ac,self.kind)
  for offset in range(0,0x34,4):self.put(self.lvtable+offset,struct.unpack('<I',self.u.mem_read(self.va(0x78b4d4)+offset,4))[0])
  self.put(self.unit+0x2e0,heading);self.put(self.unit+0x2e4,heading)
 def keys(self,body,heading,y=0,speed_type=1,balloon=False):
  self.prepare_actor(heading);self.put(self.kind+0x5a4,speed_type);self.u.mem_write(self.kind+0xb1a,bytes([balloon]));self.u.mem_write(STACK,bytes(0x300));self.put(STACK+0x14,body)
  # Actual body-to-shadow seed extraction, including arithmetic shift/mask.
  before=bytes(self.u.mem_read(STACK,0x300));self.u.reg_write(UC_X86_REG_EAX,body&0xffffffff)
  self.block(0x6f4327,0x6f4346,stack_size=0x300,inputs=self.actor_inputs())
  self.preserve_locals(before,bytes(self.u.mem_read(STACK,0x300)),((0x4c,4),(0x88,4)))
  def services(u,a,n,ctx):
   if a not in (self.va(0x53b250),self.va(0x545340)):return
   self.services[hex(a)]=self.services.get(hex(a),0)+1
   sp=u.reg_read(UC_X86_REG_ESP);value=self.cell;pop=4
   if a==self.va(0x53b250):
    value=struct.unpack('<I',u.mem_read(sp+8,4))[0];self.supplied_point(value,[0,y],block=True);pop=8
   u.reg_write(UC_X86_REG_EAX,value);u.reg_write(UC_X86_REG_EIP,struct.unpack('<I',u.mem_read(sp,4))[0]);u.reg_write(UC_X86_REG_ESP,sp+4+pop)
  before=bytes(self.u.mem_read(STACK,0x300))
  hook=self.u.hook_add(UC_HOOK_CODE,services)
  try:
   self.u.reg_write(UC_X86_REG_EBP,self.unit);self.u.reg_write(UC_X86_REG_ESP,STACK);self.u.reg_write(UC_X86_REG_EBX,self.kind);self.u.reg_write(UC_X86_REG_FPCW,0xe7f)
   self.block(0x6f4d03,0x6f4dc9,stack_size=0x300,inputs=[*self.actor_inputs(),*self.heap_inputs()])
   self.preserve_locals(before,bytes(self.u.mem_read(STACK,0x300)),((0x14,4),(0x24,4),(0x3c,8),(0x90,48),(0xd0,48),(0x160,48)))
  finally:self.u.hook_del(hook)
  return [struct.unpack('<i',self.u.mem_read(STACK+0x14,4))[0],*struct.unpack('<12I',self.u.mem_read(STACK+0x90,48))]
 def speed_default(self,current,crusher):
  self.prepare_actor();self.put(self.kind+0x5a4,current);self.u.mem_write(self.kind+0xaf3,bytes([crusher]))
  self.u.reg_write(UC_X86_REG_EDI,self.kind);self.u.reg_write(UC_X86_REG_ESP,STACK)
  inputs=[(self.unit,0x800),(self.loco,0x100),(self.kind,0x5a4),(self.kind+0x5a8,0xc00-0x5a8)]
  self.block(0x6ff65a,0x6ff678,writes=[(self.kind+0x5a4,4)],inputs=inputs)
  return [struct.unpack('<i',self.u.mem_read(self.kind+0x5a4,4))[0]]
 def foot(self,location,offset,has,predicate,real_drive=False):
  self.prepare_actor();self.put(self.unit+0x564,self.loco+4 if has else 0)
  if real_drive:
   self.put(self.unit,0x1107000);self.put(0x1107000+0x1b0,0x1202420)
  else:
   self.put(self.lvtable+0x20,0x1202400);self.put(self.lvtable+0x30,0x1202410)
  loc=0x1106000;self.u.mem_write(loc,struct.pack('<2i',*location));events=[]
  supplied=[0x1106100,7,12345,0x1106200,0x1106300,loc,0x1106400,1,0x1106500,11,12]
  def services(u,a,n,ctx):
   if a not in (0x1202400,0x1202410,0x1202420,self.va(0x6c7600)):return
   self.services[hex(a)]=self.services.get(hex(a),0)+1
   sp=u.reg_read(UC_X86_REG_ESP);value=pop=0
   if a==0x1202400:value=predicate;pop=4
   elif a==0x1202410:
    value=struct.unpack('<I',u.mem_read(sp+8,4))[0];self.supplied_point(value,offset);pop=8
   elif a==0x1202420:pass # supplied healthy ground-relative actor height zero
   else:
    args=list(struct.unpack('<11I',u.mem_read(sp+4,44)));point=list(struct.unpack('<2i',u.mem_read(args[5],8)))
    assert args[:5]==supplied[:5] and args[6:]==supplied[6:],(args,supplied)
    events.extend(point);pop=44
   u.reg_write(UC_X86_REG_EAX,value);u.reg_write(UC_X86_REG_EIP,struct.unpack('<I',u.mem_read(sp,4))[0]);u.reg_write(UC_X86_REG_ESP,sp+4+pop)
  hook=self.u.hook_add(UC_HOOK_CODE,services)
  try:self.checked_call(0x4c94f0,supplied,self.unit,inputs=[*self.actor_inputs(),(loc,8),(0x1107000,0x1b4)])
  finally:self.u.hook_del(hook)
  return [1,*events] if events else [0]
