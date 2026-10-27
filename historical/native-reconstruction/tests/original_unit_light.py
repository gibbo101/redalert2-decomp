# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact-build ordinary unit brightness, ColorScheme construction and selection.

Patched execution is local and opt-in. Heap/house/actor storage is supplied;
checks cover bounded callers, immutable inputs, permitted stores and canaries,
not ordered native/original writes or full actor/lifetime/frame parity.
"""
import struct
from original_staging import StagingOracle
from original_presentation import ARG, STACK, STOP
from unit_light_profiles import address
from unicorn import UC_HOOK_CODE, UC_HOOK_MEM_WRITE
from unicorn.x86_const import *

class UnitLightOracle(StagingOracle):
 def __init__(self,exe,*,allow_patched=False):
  super().__init__(exe,allow_patched=allow_patched)
  self.u.mem_map(0x1a00000,0x400000)
  self.services={};self.scheme_allocations=0;self.scheme_resets=0
  self.u.mem_write(0x1c00000,bytes(self.u.mem_read(self.alpha_map,0x20008)))
  self.alpha_map=0x1c00000
 def va(self,disc_va):return address(self.profile,disc_va)
 def checked_unit(self,disc_va,args=(),ecx=0,edx=0,*,writes=(),inputs=()):
  # Full RGB565 converter initialization needs the original 12M budget.
  # This is local to this fixture; ancestor budgets/contracts stay unchanged.
  end=STACK+4+4*len(args);guard=bytes([0xa7])*64
  self.u.mem_write(end,guard)
  before=[bytes(self.u.mem_read(p,n)) for p,n in inputs]
  preserved={UC_X86_REG_EBX:0x12345678,UC_X86_REG_ESI:0x23456789,
             UC_X86_REG_EDI:0x3456789a,UC_X86_REG_EBP:0x456789ab}
  for reg,value in preserved.items():self.u.reg_write(reg,value)
  allowed=[(STACK-0x2000,STACK),(STACK+4,end),*[(p,p+n) for p,n in writes]]
  def audit(u,access,p,n,value,ctx):
   if not any(lo<=p and p+n<=hi for lo,hi in allowed):
    raise AssertionError(f'Unexpected unit-light write {p:#x}/{n}')
  hook=self.u.hook_add(UC_HOOK_MEM_WRITE,audit)
  try:self.call(self.va(disc_va),args,ecx,edx,budget=12000000)
  finally:self.u.hook_del(hook)
  if self.u.reg_read(UC_X86_REG_ESP)!=end or bytes(self.u.mem_read(STACK,4))!=struct.pack('<I',STOP):
   raise AssertionError('Unit-light caller ESP/return changed')
  if bytes(self.u.mem_read(end,64))!=guard:raise AssertionError('Unit-light caller stack changed')
  if any(self.u.reg_read(reg)!=value for reg,value in preserved.items()):raise AssertionError('Unit-light callee-saved register changed')
  for (p,n),old in zip(inputs,before):
   if bytes(self.u.mem_read(p,n))!=old:raise AssertionError(f'Unit-light input changed {p:#x}/{n}')
  self.audit_calls+=1
 def extra(self,value):
  self.u.ctl_remove_cache(self.va(0x4b9f30),self.va(0x4b9fa0))
  self.u.mem_write(STACK,struct.pack('<Id',STOP,value))
  for reg,v in [(UC_X86_REG_ESP,STACK),(UC_X86_REG_FPCW,0xe7f),(UC_X86_REG_FPSW,0),(UC_X86_REG_FPTAG,0xffff)]:self.u.reg_write(reg,v)
  before=bytes(self.u.mem_read(STACK,12));guard=bytes([0xa7])*64;self.u.mem_write(STACK+12,guard)
  def audit(u,access,p,n,value,ctx):
   if not STACK-0x2000<=p or p+n>STACK:raise AssertionError('Unexpected ExtraUnitLight numeric write')
  hook=self.u.hook_add(UC_HOOK_MEM_WRITE,audit)
  try:
   self.u.emu_start(self.va(0x4b9f30),self.va(0x4b9f34),count=10)
   if self.u.reg_read(UC_X86_REG_EIP)!=self.va(0x4b9f34):raise AssertionError('Extra numeric input load did not stop')
   self.u.emu_start(self.va(0x63d76e),self.va(0x63d779),count=100)
   if self.u.reg_read(UC_X86_REG_EIP)!=self.va(0x63d779):raise AssertionError('Extra numeric block did not stop')
  finally:self.u.hook_del(hook)
  if self.u.reg_read(UC_X86_REG_ESP)!=STACK or bytes(self.u.mem_read(STACK,12))!=before or bytes(self.u.mem_read(STACK+12,64))!=guard:
   raise AssertionError('Extra numeric input/caller changed')
  self.audit_blocks+=2
  return struct.unpack('<i',struct.pack('<I',self.u.reg_read(UC_X86_REG_EAX)))[0]
 def coordinates(self,x,y):
  actor=0x1b11000
  self.u.mem_write(actor+0x88,struct.pack('<2i',x,y))
  self.checked_unit(0x41b320,[ARG],actor,writes=[(ARG,4)],inputs=[(actor,0x700)])
  return list(struct.unpack('<2h',self.u.mem_read(ARG,4)))
 def brightness(self,ambient,extra,flags=0,predicate=False,effects=0,x=33,y=86):
  cell=0x1b10000;actor=0x1b11000;kind=0x1b12000;rules=0x1b13000;vt=0x1b15000
  self.put(self.va(0x81a938),0x1a00000);self.put(0x1a00000+(y*512+x)*4,cell)
  self.u.mem_write(cell,bytes(0x200));self.u.mem_write(cell+0x10a,struct.pack('<h',ambient));self.put(cell+0x140,flags)
  self.put(actor,vt);self.put(vt+0x54,0x1202200);self.put(actor+0x5ac,kind);self.u.mem_write(kind+0xba6,b'\0')
  self.put(self.va(0x821b68),rules);self.put(rules+0x1418,extra);self.put(actor+0xd8,effects)
  def service(u,a,n,ctx):
   if a!=0x1202200:return
   self.services['actor virtual +0x54']=self.services.get('actor virtual +0x54',0)+1
   sp=u.reg_read(UC_X86_REG_ESP);u.reg_write(UC_X86_REG_EAX,int(predicate));u.reg_write(UC_X86_REG_EIP,struct.unpack('<I',u.mem_read(sp,4))[0]);u.reg_write(UC_X86_REG_ESP,sp+4)
  inputs=[(cell,0x200),(actor,0x700),(kind,0xc00),(rules,0x1500),(vt,0x100),
          (0x1a00000,512*512*4),(self.va(0x81a938),4),(self.va(0x821b68),4)]
  hook=self.u.hook_add(UC_HOOK_CODE,service)
  try:
   self.u.mem_write(STACK,bytes(128));self.u.mem_write(STACK+0x10,struct.pack('<2h',x,y))
   before_stack=bytes(self.u.mem_read(STACK,128))
   self.u.reg_write(UC_X86_REG_ESI,actor)
   self.block(0x6f5b21,0x6f5b8c,stack_size=128,inputs=inputs)
   after_stack=bytes(self.u.mem_read(STACK,128))
   if before_stack[:0x54]!=after_stack[:0x54] or before_stack[0x58:]!=after_stack[0x58:]:
    raise AssertionError('Brightness block unrelated locals changed')
   before=struct.unpack('<i',self.u.mem_read(STACK+0x54,4))[0]
   self.checked_unit(0x6ccdf0,[before],actor,inputs=inputs)
   after=struct.unpack('<i',struct.pack('<I',self.u.reg_read(UC_X86_REG_EAX)))[0]
  finally:self.u.hook_del(hook)
  return [before,after]
 def scheme(self,color,palette,theater):
  # Independent cases own no guest model/converter from the preceding case:
  # results are copied to host arrays. Check before discarding heap ownership.
  # The original-generated alpha table lives separately at 1C00000 and stays warm.
  self.check_heap();self.alloc=0x1300000;self.allocations=[];self.scheme_resets+=1
  scheme=0x1b40000;unit=0x1b41000;iso=0x1b42000;surface=0x1b43000
  for p,v in [(0x839468,100),(0x839470,0),(0x839464,0x16f0000),
              (0x81a6c0,100),(0x81a6c8,0),(0x81a6bc,0x16f1000),
              (0x824904,0x1b80000),(0x824908,100),(0x824910,1)]:self.put(self.va(p),v)
  self.put(0x1b80000,self.alpha_map)
  self.u.mem_write(scheme,bytes(0x400));self.u.mem_write(scheme+0x308,bytes(color));self.put(scheme+0x310,53)
  self.u.mem_write(unit,bytes(palette));self.u.mem_write(iso,bytes(theater));self.surface(surface,40,32,2,0x1700000);self.put(self.va(0x821c70),surface)
  self.u.mem_write(self.va(0xa39554),b'\0');self.put(self.va(0xa3955c),0);self.put(self.va(0x7ca490),4)
  for p,v in [(0x83b2c8,11),(0x83b2cc,3),(0x83b2d0,0),(0x83b2d4,3),(0x83b2d8,5),(0x83b2dc,2)]:self.put(self.va(p),v)
  inputs=[(unit,768),(iso,768),(surface,28),(scheme,4),(scheme+0x304,8),(scheme+0x310,0xf0),
          (self.alpha_map,0x20004),(0x1b80000,4)]
  inputs += [(self.va(p),n) for p,n in [(0x839464,8),(0x81a6bc,8),(0x824904,12),
             (0x824910,4),(0x821c70,4),(0xa39554,1),(0xa3955c,4),(0x7ca490,4),(0x83b2c8,24)]]
  writes=[(scheme+4,768),(scheme+0x30c,4),(0x1300000,0x300000),(self.alpha_map+0x20004,4),
          (self.va(0x839470),4),(self.va(0x81a6c8),4),(0x16f0000,4),(0x16f1000,4)]
  hook=self.u.hook_add(UC_HOOK_MEM_WRITE,self.guarded_heap_write)
  try:self.checked_unit(0x65a9a0,[unit,iso,1000,1000,1000],scheme,writes=writes,inputs=inputs)
  finally:self.u.hook_del(hook)
  self.check_heap();self.scheme_allocations+=len(self.allocations)
  cvt=struct.unpack('<I',self.u.mem_read(scheme+0x30c,4))[0]
  if bytes(self.u.mem_read(cvt,4))!=struct.pack('<I',self.va(0x7905c4)):raise AssertionError('LightConvert identity differs')
  blitter=struct.unpack('<I',self.u.mem_read(cvt+0x98,4))[0]
  if bytes(self.u.mem_read(blitter,4))!=struct.pack('<I',self.va(0x78920c)):raise AssertionError('Ordinary constructed blitter differs')
  shades,table=struct.unpack('<2I',self.u.mem_read(cvt+0x16c,8))
  mask=struct.unpack('<I',self.u.mem_read(cvt+0x190,4))[0]
  assert shades==53
  return list(struct.unpack('<'+str(shades*256)+'H',self.u.mem_read(table,shades*512))),list(self.u.mem_read(mask,256)),list(struct.unpack('<3i',self.u.mem_read(cvt+0x198,12)))
 def selection(self,index,identities):
  actor=0x1b11000;house=0x1b20000;array=0x1b50000
  self.put(actor+0x1b4,house);self.put(house+0x15f40,index);self.put(self.va(0xa9e9e4),array)
  for i,identity in enumerate(identities):
   scheme=0x1b51000+i*0x400;cvt=0x1b60000+identity*0x200;blitter=0x1b70000+identity*16
   self.put(array+i*4,scheme);self.put(scheme+0x30c,cvt);self.put(cvt+8,1);self.put(cvt+0x98,blitter)
  self.u.reg_write(UC_X86_REG_ESI,actor);self.u.reg_write(UC_X86_REG_EDI,0x2800)
  self.block(0x6f4013,0x6f4034,inputs=[(actor,0x700),(house,0x15f44),(array,0x5d00),
             (0x1b60000,0x3000),(self.va(0xa9e9e4),4)])
  return [(self.u.reg_read(UC_X86_REG_EAX)-0x1b70000)//16]
