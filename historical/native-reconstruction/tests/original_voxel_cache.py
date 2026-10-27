# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact-build Unit keys and complete healthy lit wrapper/index decisions.

Patched execution is local and opt-in. Bounded caller/input/heap/write audits
exclude ordered native-original writes, real snapshot encoding/pool/lifetime,
full actor/type initialization, alternate status branches and full-frame parity.
"""
import struct
from original_staging import StagingOracle
from original_presentation import STACK
from voxel_cache_profiles import address
from unicorn import UC_HOOK_CODE, UC_HOOK_MEM_WRITE
from unicorn.x86_const import *

class VoxelCacheOracle(StagingOracle):
 def __init__(self,exe,*,allow_patched=False):
  super().__init__(exe,allow_patched=allow_patched);self.services={};self.host_writes=0;self.begin()
 def va(self,disc_va):return address(self.profile,disc_va)
 def begin(self):
  self.actor=0x1601000;self.kind=0x1602000;self.vtable=0x1603000;self.index=0x1604000;self.model=0x1605000
  self.u.mem_write(self.actor,bytes(0x800));self.u.mem_write(self.kind,bytes(0xc00));self.u.mem_write(self.index,bytes(0xc0))
  self.u.mem_write(self.vtable,bytes(0x400));self.u.mem_write(0x1606000,bytes(0x2000))
  self.put(self.actor,self.vtable)
  for off in [0x64,0x1bc,0x1c0,0x32c,0x80,0x2c]:self.put(self.vtable+off,0x1202200+off)
  self.put(self.vtable+0x3f8,self.va(0x6ccdf0))
  self.serial=0;self.events=[]
 def host_write(self,p,data):
  # Unicorn's guest-write hook does not audit Python mem_write services.
  # Explicitly permit only the current render local or next logical snapshot.
  if not any(lo<=p and p+len(data)<=hi for lo,hi in self.host_outputs):
   raise AssertionError(f'Voxel-cache supplied service write outside output {p:#x}/{len(data)}')
  self.u.mem_write(p,data);self.host_writes+=1
 def service(self,u,a,n,ctx):
  methods={0x1202200+off:off for off in [0x64,0x1bc,0x1c0,0x32c,0x80,0x2c]}
  if a not in methods and a not in tuple(self.va(p) for p in (0x4f4660,0x6c7900,0x70baa0,0x68f720,0x6c7df0)):return
  self.services[hex(a)]=self.services.get(hex(a),0)+1
  sp=u.reg_read(UC_X86_REG_ESP);args=struct.unpack('<9I',u.mem_read(sp+4,36));value=pop=0
  if a in methods:
   if u.reg_read(UC_X86_REG_ECX)!=self.actor:raise AssertionError('Supplied virtual predicate/type receiver differs')
   off=methods[a];pop=8 if off==0x64 else 0
   value=self.kind if off==0x80 else 1 if off==0x2c else 0
  elif a==self.va(0x4f4660):
   if u.reg_read(UC_X86_REG_ECX)!=0:raise AssertionError('Supplied healthy house query receiver differs')
  elif a==self.va(0x6c7900):
   if not STACK-0x2000<=args[0] or args[0]+24>STACK:raise AssertionError('Supplied render rectangle outside callee locals')
   self.events.append(['render',args[5],args[6],args[7]])
   self.host_write(args[0],struct.pack('<6i',-3,-4,120,119,12,11));value=args[0];pop=32
  elif a==self.va(0x70baa0):value=0x1700000;pop=4
  elif a==self.va(0x68f720):
   self.serial+=1;value=0x1606000+self.serial*16
   self.host_write(value,struct.pack('<I',self.serial));self.events.append(['snapshot',self.serial]);pop=4
  elif a==self.va(0x6c7df0):
   if not 0x1606010<=args[0]<0x1608000 or (args[0]-0x1606000)%16:raise AssertionError('Cached logical snapshot outside fixture')
   self.events.append(['cached',struct.unpack('<I',u.mem_read(args[0],4))[0],args[3],args[4]]);pop=20
  u.reg_write(UC_X86_REG_EAX,value);u.reg_write(UC_X86_REG_EIP,struct.unpack('<I',u.mem_read(sp,4))[0]);u.reg_write(UC_X86_REG_ESP,sp+4+pop)
 def keys(self,loco,frame,heading,offset):
  # Nonzero supplied locals expose the original 48-byte body-pose copy.
  self.u.mem_write(STACK,bytes((i*37+11)&255 for i in range(0x200)))
  self.put(STACK+0x14,loco);self.put(STACK+0x38,frame)
  before=bytes(self.u.mem_read(STACK,0x200))
  self.block(0x6f42f1,0x6f4327,stack_size=0x200)
  after=bytes(self.u.mem_read(STACK,0x200))
  if after[0x90:0xc0]!=before[0xd0:0x100]:raise AssertionError('Body key pose copy differs')
  self.check_locals(before,after,((0x14,4),(0x90,48)))
  body=struct.unpack('<i',self.u.mem_read(STACK+0x14,4))[0]
  self.u.mem_write(self.actor+0x2f8,struct.pack('<6i',heading,heading,-1,0,0,1280));self.put(self.kind+0x63c,offset)
  before=bytes(self.u.mem_read(STACK,0x200))
  hook=self.u.hook_add(UC_HOOK_CODE,self.service)
  try:
   self.u.reg_write(UC_X86_REG_EBP,self.actor)
   self.block(0x6f445b,0x6f44ab,stack_size=0x200,inputs=[(self.actor,0x800),(self.kind,0xc00),(self.vtable,0x400)])
   self.check_locals(before,bytes(self.u.mem_read(STACK,0x200)),((0x18,4),(0x1c,4)))
   turret=struct.unpack('<i',self.u.mem_read(STACK+0x1c,4))[0]
  finally:self.u.hook_del(hook)
  return [body,turret]
 @staticmethod
 def check_locals(before,after,outputs):
  a,b=bytearray(before),bytearray(after)
  for p,n in outputs:a[p:p+n]=b[p:p+n]
  if a!=b:raise AssertionError('Voxel-cache unrelated caller locals changed')
 def dispatch(self,key,available,disabled,valid,frame=0,brightness=1312):
  self.events=[];self.put(self.model,1 if valid else 0);self.put(self.model+4,1 if valid else 0)
  self.u.mem_write(self.kind+0xb5a,bytes([disabled]));self.u.mem_write(self.va(0xab7ef0),bytes(16))
  self.u.mem_write(0x1608000,struct.pack('<4i',0,0,256,256));self.u.mem_write(0x1608010,struct.pack('<2i',128,128))
  entries=struct.unpack('<I',self.u.mem_read(self.index,4))[0]
  immutable_heap=[(p,n) for p,n in self.allocations if p!=entries]
  next_snapshot=0x1606000+(self.serial+1)*16
  if next_snapshot+4>0x1608000:raise ValueError('Logical snapshot fixture exhausted')
  snapshots=bytes(self.u.mem_read(0x1606000,0x2000))
  self.host_outputs=[(STACK-0x2000,STACK),(next_snapshot,next_snapshot+4)]
  hook=self.u.hook_add(UC_HOOK_CODE,self.service)
  audit=self.u.hook_add(UC_HOOK_MEM_WRITE,self.guarded_heap_write)
  try:self.checked_call(0x6c7120,[self.model,frame,key,self.index if available else 0,0x1608000,0x1608010,0x1608020,brightness,0x2800],self.actor,
   writes=[(self.index,20),(self.va(0xab7ef0),16),(0x1300000,0x300000)],
   inputs=[(self.actor,0x800),(self.kind,0xc00),(self.vtable,0x400),(self.model,8),
           (self.index+20,0x16040c0-self.index-20),(0x1604000,self.index-0x1604000),
           (0x1608000,32),*immutable_heap])
  finally:self.u.hook_del(hook);self.u.hook_del(audit)
  self.check_heap()
  self.check_locals(snapshots,bytes(self.u.mem_read(0x1606000,0x2000)),((next_snapshot-0x1606000,4),))
  pointer,count,capacity=struct.unpack('<3I',self.u.mem_read(self.index,12));hot=struct.unpack('<I',self.u.mem_read(self.index+16,4))[0]
  keys=[struct.unpack('<i',self.u.mem_read(pointer+i*8,4))[0] for i in range(count)]
  return self.events+[['state',count,capacity,self.u.mem_read(self.index+12,1)[0],struct.unpack('<i',self.u.mem_read(hot,4))[0] if hot else None,*keys]]
