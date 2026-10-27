# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact-base Terrain strength prefix and complete theater image reload.
The base ObjectType loader, image loader and successful free are fixture services.
Original _makepath and the reload's iteration/guards/writes execute unchanged.
"""
import struct
from original_presentation import PresentationOracle,STACK,STOP
from scenery_profiles import address
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import *

class TerrainTypeOracle(PresentationOracle):
 def __init__(self,exe,*,allow_patched=False):
  super().__init__(exe,allow_patched=allow_patched);self.u.mem_map(0x1e00000,0x20000)
 def va(self,disc_va):return address(self.profile,disc_va)
 def string(self,p):return bytes(self.u.mem_read(p,128)).split(b'\0')[0].decode('ascii')
 def strength(self,current,stock):
  actor=0x1e00000;rules=0x1e10000;ini=0x1e18000
  self.u.mem_write(actor,bytes([0x5a])*0x300);self.put(actor+0xa0,current)
  before=bytes(self.u.mem_read(actor,0x300));self.put(self.va(0x821b68),rules);self.put(rules+0xe1c,stock)
  def service(u,a,n,ctx):
   if a!=self.va(0x5cfd50):return
   assert u.reg_read(UC_X86_REG_ECX)==actor
   sp=u.reg_read(UC_X86_REG_ESP);assert struct.unpack('<I',u.mem_read(sp+4,4))[0]==ini
   u.reg_write(UC_X86_REG_EAX,1);u.reg_write(UC_X86_REG_EIP,struct.unpack('<I',u.mem_read(sp,4))[0]);u.reg_write(UC_X86_REG_ESP,sp+8)
  guard=bytes([0xa7])*64;self.u.mem_write(STACK+8,guard)
  stack=struct.pack('<2I',STOP,ini);rules_before=bytes(self.u.mem_read(rules,0xe20))
  regs={UC_X86_REG_EBX:0x12345678,UC_X86_REG_EDI:0x3456789a,UC_X86_REG_EBP:0x456789ab,UC_X86_REG_ESI:0x23456789}
  for reg,value in regs.items():self.u.reg_write(reg,value)
  def audit(u,access,p,n,value,ctx):
   if not (STACK-0x214<=p and p+n<=STACK or (p,n)==(actor+0xa0,4)):
    raise AssertionError('Unexpected Terrain strength-prefix write')
  hooks=[self.u.hook_add(UC_HOOK_CODE,service),self.u.hook_add(UC_HOOK_MEM_WRITE,audit)]
  try:
   self.u.mem_write(STACK,struct.pack('<2I',STOP,ini));self.u.reg_write(UC_X86_REG_ESP,STACK);self.u.reg_write(UC_X86_REG_ECX,actor)
   self.u.emu_start(self.va(0x6da7a0),self.va(0x6da7d9),count=100)
   assert self.u.reg_read(UC_X86_REG_EIP)==self.va(0x6da7d9)
  finally:
   for hook in hooks:self.u.hook_del(hook)
  assert self.u.reg_read(UC_X86_REG_ESP)==STACK-0x20c
  assert self.u.reg_read(UC_X86_REG_EBX)==regs[UC_X86_REG_EBX] and self.u.reg_read(UC_X86_REG_EDI)==regs[UC_X86_REG_EDI]
  assert self.u.reg_read(UC_X86_REG_EBP)==ini and self.u.reg_read(UC_X86_REG_ESI)==actor
  assert bytes(self.u.mem_read(STACK,8))==stack and bytes(self.u.mem_read(STACK+8,64))==guard
  assert bytes(self.u.mem_read(rules,0xe20))==rules_before
  self.audit_blocks+=1
  after=bytes(self.u.mem_read(actor,0x300));assert before[:0xa0]==after[:0xa0] and before[0xa4:]==after[0xa4:]
  return [struct.unpack('<i',after[0xa0:0xa4])[0]]
 def reload(self,force,requested,previous,items):
  types=0x1e00000;array=0x1e10000;events=[];before=[]
  self.u.mem_write(self.va(0xa28933),bytes([force]));self.put(self.va(0x7c396c),previous)
  self.put(self.va(0xa27f54),array);self.put(self.va(0xa27f60),len(items))
  for i,(name,theater,owned,image,loaded) in enumerate(items):
   p=types+i*0x300;self.put(array+i*4,p);self.u.mem_write(p,bytes([0x5a])*0x300)
   self.u.mem_write(p+0x24,name.encode()+b'\0');self.u.mem_write(p+0x1fc,bytes([theater]));self.u.mem_write(p+0xa8,bytes([owned]));self.put(p+0xa4,image)
   before.append(bytes(self.u.mem_read(p,0x300)))
  def service(u,a,n,ctx):
   if a not in (self.va(0x76d2d5),self.va(0x592370)):return
   sp=u.reg_read(UC_X86_REG_ESP);kind=u.reg_read(UC_X86_REG_ESI);i=(kind-types)//0x300;assert kind==types+i*0x300 and 0<=i<len(items)
   if a==self.va(0x76d2d5):
    image=struct.unpack('<I',u.mem_read(sp+4,4))[0];assert image==items[i][3] and items[i][2];events.extend(['F',str(i),str(image)]);value=0
   else:
    assert bytes(u.mem_read(kind+0xa4,5))==bytes(5)
    events.extend(['L',str(i),self.string(u.reg_read(UC_X86_REG_ECX))]);value=items[i][4]
   u.reg_write(UC_X86_REG_EAX,value);u.reg_write(UC_X86_REG_EIP,struct.unpack('<I',u.mem_read(sp,4))[0]);u.reg_write(UC_X86_REG_ESP,sp+4)
  def write(u,access,address,size,value,ctx):
   if STACK-0x2000<=address and address+size<=STACK:return
   if not types<=address<types+len(items)*0x300:raise AssertionError(f'Unexpected reload write {address:#x}/{size}')
   i=(address-types)//0x300;off=(address-types)%0x300
   assert (off,size) in ((0xa4,4),(0xa8,1)),(hex(address),size)
   events.extend(['W',str(i),str(int(off==0xa8)),str(value&((1<<(size*8))-1))])
  hooks=[self.u.hook_add(UC_HOOK_CODE,service),self.u.hook_add(UC_HOOK_MEM_WRITE,write)]
  try:self.checked_call(0x6da5d0,ecx=requested,
   writes=[(types+i*0x300+0xa4,5) for i in range(len(items))],
   inputs=[(array,len(items)*4),(self.va(0xa28933),1),(self.va(0x7c396c),4),
           (self.va(0xa27f54),4),(self.va(0xa27f60),4)])
  finally:
   for hook in hooks:self.u.hook_del(hook)
  result=[]
  for i,old in enumerate(before):
   after=bytes(self.u.mem_read(types+i*0x300,0x300));assert old[:0xa4]==after[:0xa4] and old[0xa9:]==after[0xa9:]
   result.extend([str(struct.unpack('<I',after[0xa4:0xa8])[0]),str(after[0xa8])])
  assert struct.unpack('<i',self.u.mem_read(self.va(0x7c396c),4))[0]==previous # caller owns current theater
  return result+events
