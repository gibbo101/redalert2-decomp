# SPDX-License-Identifier: GPL-3.0-or-later
"""Original indexed converter/blits, dirty union and successful shadow dispatch."""
import struct
from original_shadow_color import ShadowColorOracle
from original_presentation import ARG,STACK,STOP
from staging_profiles import address
from unicorn import UC_HOOK_CODE, UC_HOOK_MEM_WRITE
from unicorn.x86_const import *

class StagingOracle(ShadowColorOracle):
 def __init__(self,exe,*,allow_patched=False):
  super().__init__(exe,allow_patched=allow_patched)
 def va(self,disc_va):return address(self.profile,disc_va)
 def call(self,guest_va,args=(),ecx=0,edx=0,budget=4000000):
  if guest_va==self.va(0x483430):budget=12000000
  return super().call(guest_va,args,ecx,edx,budget)
 def guarded_heap_write(self,u,access,p,n,value,ctx):
  if 0x1300000<=p<0x1600000 and not any(lo<=p and p+n<=lo+size for lo,size in self.allocations):
   raise AssertionError('Staging guest write outside guarded allocation')
 def indexed_converter(self,source,destination):
  self.surface(0x1600000,256,256,1,0x1700000)
  self.u.mem_write(0x1900000,bytes(source));self.u.mem_write(0x1900400,bytes(destination))
  self.put(self.va(0x839468),100);self.put(self.va(0x839470),0);self.put(self.va(0x839464),0x16f0000)
  hook=self.u.hook_add(UC_HOOK_MEM_WRITE,self.guarded_heap_write)
  try:self.checked_call(0x483430,[0x1900000,0x1900400,0x1600000,1,0],0x1600600,
   writes=[(0x1600600,0x180),(0x1300000,0x300000),(self.va(0x839470),4),(0x16f0000,4)],
   inputs=[(0x1900000,768),(0x1900400,768),(0x1600000,28),
    (self.va(0x839460),16),(self.va(0x839474),4),*self.heap_inputs()])
  finally:self.u.hook_del(hook)
  self.check_heap()
  ptr=struct.unpack('<I',self.u.mem_read(0x1600774,4))[0]
  remap=bytes(self.u.mem_read(ptr,256));assert remap[0]==0
  self.checked_call(0x485880,[0],0x1600600,inputs=[(0x1600600,0x180),*self.heap_inputs()])
  self.index_blitter=self.u.reg_read(UC_X86_REG_EAX)
  assert struct.unpack('<I',self.u.mem_read(self.index_blitter,4))[0]==self.va(0x78950c)
  return remap
 def indexed_blit(self,w,h,source,sw,sh,box,location,clip,destination):
  self.surface(0x1600000,w,h,1,0x1700000);self.surface(0x1600100,sw,sh,1,0x1880000)
  self.u.mem_write(0x1700000,bytes(destination));self.u.mem_write(0x1880000,bytes(source))
  self.u.mem_write(ARG,struct.pack('<10i',*box,*location,*clip))
  surfaces=[(obj,28) for obj in (0x1600000,0x1600100,0x1600200,0x1600300)]
  self.checked_call(0x49ef70,[0x1600100,ARG,ARG+16,ARG+24,0,self.index_blitter,0,2,1000,0],0x1600000,0x1600600,
   writes=[(0x1700000,w*h),(0x160077c,4),*[(obj+12,4) for obj,n in surfaces]],
   inputs=[(0x1880000,len(source)),(ARG,40),(0x1600600,0x17c),*surfaces,*self.heap_inputs()])
  for obj,n in surfaces:
   if self.u.mem_read(obj+12,4)!=bytes(4):raise AssertionError('Indexed surface lock count not restored')
  return bytes(self.u.mem_read(0x1700000,w*h))
 def dirty(self,a,b):
  self.u.mem_write(self.va(0xab7ef0),struct.pack('<4i',*a));self.u.mem_write(ARG,struct.pack('<2i',*b[:2]))
  self.u.mem_write(STACK,bytes(256))
  for off,val in [(0x68,ARG),(0x38,0),(0x3c,0),(0x64,b[2]),(0x74,b[3])]:self.put(STACK+off,val)
  self.u.reg_write(UC_X86_REG_ESP,STACK);self.u.reg_write(UC_X86_REG_ESI,b[2]&0xffffffff)
  # Preserve supplied locals outside the three inspected dirty-union stores.
  before=bytes(self.u.mem_read(STACK,256));point=bytes(self.u.mem_read(ARG,8))
  guard=bytes([0xa7])*64;self.u.mem_write(STACK+256,guard)
  allowed=[(STACK+0x14,STACK+0x20),(self.va(0xab7ef0),self.va(0xab7ef0)+16)]
  def audit(u,access,p,n,value,ctx):
   if not any(lo<=p and p+n<=hi for lo,hi in allowed):raise AssertionError('Unexpected dirty-union write')
  hook=self.u.hook_add(UC_HOOK_MEM_WRITE,audit)
  try:self.u.emu_start(self.va(0x6c7329),self.va(0x6c7430),count=1000)
  finally:self.u.hook_del(hook)
  if self.u.reg_read(UC_X86_REG_EIP)!=self.va(0x6c7430) or self.u.reg_read(UC_X86_REG_ESP)!=STACK:
   raise AssertionError('Dirty-union block stop/stack changed')
  after=bytes(self.u.mem_read(STACK,256))
  if after[:0x14]!=before[:0x14] or after[0x20:]!=before[0x20:] or bytes(self.u.mem_read(STACK+256,64))!=guard:
   raise AssertionError('Dirty-union input/caller stack changed')
  if bytes(self.u.mem_read(ARG,8))!=point:raise AssertionError('Dirty-union point changed')
  self.audit_blocks+=1
  return list(struct.unpack('<4i',self.u.mem_read(self.va(0xab7ef0),16)))
 def final_blit(self,w,h,source,sw,sh,box,location,clip,z,brightness,colors,depth,alpha,palette):
  self.blit(w,h,source,sw,sh,box,location,clip,z,brightness,colors,depth,alpha,palette)
  self.u.mem_write(0x1700000,struct.pack('<'+'H'*len(colors),*colors))
  # Complete original surface-to-surface path used by Unit +0x4E0.
  self.u.mem_write(ARG,struct.pack('<16i',location[0],location[1],box[2],box[3],0,0,sw,sh,*box,*clip))
  surfaces=[(obj,28) for obj in (0x1600000,0x1600100,0x1600200,0x1600300)]
  self.checked_call(0x434a00,[ARG,0x1600100,ARG+16,ARG+32,0x1600900,z,2,brightness,0],0x1600000,ARG+48,
   writes=[(0x1700000,w*h*2),*[(obj+12,4) for obj,n in surfaces]],
   inputs=[(ARG,64),(0x1880000,len(source)),(0x1780000,w*h*2),(0x1800000,w*h*2),
    (0x1900000,len(palette)*2),(0x1600400,48),(0x1600500,48),(0x1600900,12),*surfaces,*self.heap_inputs()])
  for obj,n in surfaces:
   if self.u.mem_read(obj+12,4)!=bytes(4):raise AssertionError('Final surface lock count not restored')
  return list(struct.unpack('<'+'H'*(w*h),self.u.mem_read(0x1700000,w*h*2))),list(struct.unpack('<'+'H'*(w*h),self.u.mem_read(0x1780000,w*h*2)))

class ShadowDispatchOracle(StagingOracle):
 def begin_cache(self):
  self.actor=0x1601000;self.type=0x1602000;self.vtable=0x1603000;self.index=0x1604000;self.model=0x1605000;self.modeldata=0x1605100
  self.u.mem_write(self.actor,bytes(0x800));self.u.mem_write(self.type,bytes(0xc00));self.u.mem_write(self.index,bytes(32))
  self.put(self.actor,self.vtable);self.put(self.vtable+0x80,0x1202200);self.put(self.model,self.modeldata)
  self.serial=0;self.events=[]
 def dispatch(self,key,actor,no_shadow,model_bad,available,disabled,allow):
  self.put(self.actor+0x1b8,actor);self.u.mem_write(self.type+0xb48,bytes([no_shadow]));self.u.mem_write(self.type+0xb5b,bytes([disabled]));self.u.mem_write(self.modeldata,bytes([model_bad]));self.events=[]
  def services(u,a,n,ctx):
   if a not in (0x1202200,*[self.va(p) for p in (0x6c7c30,0x70baa0,0x68f720,0x6c7df0)]):return
   sp=u.reg_read(UC_X86_REG_ESP);args=struct.unpack('<11I',u.mem_read(sp+4,44));pop=0;value=0
   if a==0x1202200:value=self.type
   elif a==self.va(0x6c7c30):
    self.events.append(['render',args[7]&255,args[6]]);u.mem_write(args[0],struct.pack('<6i',-3,-4,120,119,12,11));value=args[0];pop=44
   elif a==self.va(0x70baa0):value=0x1700000;pop=4
   elif a==self.va(0x68f720):
    self.serial+=1;value=0x1606000+self.serial*16;self.put(value,self.serial);self.events.append(['snapshot',self.serial]);pop=4
   elif a==self.va(0x6c7df0):self.events.append(['cached',struct.unpack('<I',u.mem_read(args[0],4))[0],args[3],args[4]]);pop=20
   u.reg_write(UC_X86_REG_EAX,value);u.reg_write(UC_X86_REG_EIP,struct.unpack('<I',u.mem_read(sp,4))[0]);u.reg_write(UC_X86_REG_ESP,sp+4+pop)
  entries=struct.unpack('<I',self.u.mem_read(self.index,4))[0]
  immutable_heap=[(p,n) for p,n in self.allocations if p!=entries]
  hook=self.u.hook_add(UC_HOOK_CODE,services)
  audit=self.u.hook_add(UC_HOOK_MEM_WRITE,self.guarded_heap_write)
  try:self.checked_call(0x6c7600,[self.model,0,key,self.index if available else 0,0,0,0,allow,0,0,0],self.actor,
   writes=[(self.index,20),(0x1300000,0x300000)],
   inputs=[(self.actor,0x800),(self.type,0xc00),(self.vtable,0x100),(self.model,4),(self.modeldata,1),*immutable_heap])
  finally:self.u.hook_del(hook);self.u.hook_del(audit)
  self.check_heap()
  ptr,count,capacity=struct.unpack('<3I',self.u.mem_read(self.index,12));hot=struct.unpack('<I',self.u.mem_read(self.index+16,4))[0]
  keys=[struct.unpack('<i',self.u.mem_read(ptr+8*i,4))[0] for i in range(count)]
  return self.events+[ ['state',count,capacity,self.u.mem_read(self.index+12,1)[0],struct.unpack('<i',self.u.mem_read(hot,4))[0] if hot else None,*keys] ]
 def staged_shadow(self,model,pose,camera,offset,stencil):
  self.surface(0x1608000,256,256,1,0x1610000);self.u.mem_write(0x1610000,bytes(stencil))
  outputs=[(self.va(p),n) for p,n in [(0x7e35d0,4),(0xab84d0,65548),(0xac8710,8),
   (0xac8838,12),(0xac8848,136),(0xacaa50,20),(0xacae68,65536),(0xadae68,72),(0xae0470,48)]]
  self.put(self.va(0x7e35d0),1);self.checked_call(0x70bc30,writes=outputs,inputs=self.heap_inputs())
  self.u.mem_write(ARG,struct.pack('<24f',*pose,*camera));self.u.mem_write(ARG+128,struct.pack('<3f',*offset))
  inputs=[(ARG,96),(ARG+128,12),(0x1608000,28),(0x1610000,65536),*self.heap_inputs()]
  self.checked_call(0x70bdc0,[0,ARG+48,ARG,ARG+128,0x1608000,0,0],model,0,writes=outputs,inputs=inputs)
  self.checked_call(0x70c340,ecx=ARG+192,writes=[*outputs,(ARG+192,24),(0x160800c,4)],inputs=inputs)
  if self.u.mem_read(0x160800c,4)!=bytes(4):raise AssertionError('Staged-shadow lock count not restored')
  return bytes(self.u.mem_read(self.va(0xacae68),65536)),list(struct.unpack('<6i',self.u.mem_read(ARG+192,24)))
