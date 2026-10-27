# SPDX-License-Identifier: GPL-3.0-or-later
"""Original loader and full bounded section pipeline. Only file/heap services are substituted."""
import hashlib,struct
from pathlib import Path
from original_presentation import PresentationOracle,ARG,STACK
from raster_profiles import address
from unicorn import UC_HOOK_CODE, UC_HOOK_MEM_WRITE
from unicorn.x86_const import *
class RasterOracle(PresentationOracle):
 def __init__(self,exe,*,allow_patched=False):
  super().__init__(exe,allow_patched=allow_patched);self.u.mem_map(0x1200000,0x400000)
  self.alloc=0x1300000;self.file=b'';self.pos=0;self.counts={};self.allocations=[]
  self.put(0x1200000,0x1200100)
  for off,a in [(0x1c,0x1201000),(0x24,0x1201010),(0x28,0x1201020),(0x34,0x1201030)]:self.put(0x1200100+off,a)
  self.u.hook_add(UC_HOOK_CODE,self.hook)
 def va(self,disc_va):return address(self.profile,disc_va)
 def allocate(self,size):
  if not 0<size<=0x100000:raise ValueError('Allocation outside loader fixture')
  start=self.alloc+32;end=start+size;self.alloc=(end+47)&~15
  if self.alloc>0x1600000:raise ValueError('Loader fixture heap exhausted')
  self.u.mem_write(start-32,bytes([0xa7])*32);self.u.mem_write(end,bytes([0xa7])*32)
  self.allocations.append((start,size));return start
 def check_heap(self):
  for start,size in self.allocations:
   if bytes(self.u.mem_read(start-32,32))+bytes(self.u.mem_read(start+size,32))!=bytes([0xa7])*64:
    raise AssertionError('Original loader heap canary changed')
 def heap_inputs(self):return [(0x1300000,self.alloc-0x1300000)]
 def block(self,start,stop,*,writes=(),inputs=(),stack_size=0):
  before=[bytes(self.u.mem_read(p,n)) for p,n in inputs]
  guard=bytes([0xa7])*64;self.u.mem_write(STACK+stack_size,guard)
  self.u.reg_write(UC_X86_REG_ESP,STACK);self.u.reg_write(UC_X86_REG_FPCW,0xe7f)
  allowed=[(STACK-0x2000,STACK+stack_size),*[(p,p+n) for p,n in writes]]
  def audit(u,access,p,n,value,context):
   if not any(lo<=p and p+n<=hi for lo,hi in allowed):raise AssertionError(f'Unexpected raster block write {p:#x}/{n}')
  hook=self.u.hook_add(UC_HOOK_MEM_WRITE,audit)
  try:self.u.emu_start(self.va(start),self.va(stop),count=50000)
  finally:self.u.hook_del(hook)
  if self.u.reg_read(UC_X86_REG_EIP)!=self.va(stop) or self.u.reg_read(UC_X86_REG_ESP)!=STACK:
   raise AssertionError('Original raster block EIP/ESP differs')
  if bytes(self.u.mem_read(STACK+stack_size,64))!=guard:raise AssertionError('Raster block caller stack changed')
  if any(bytes(self.u.mem_read(p,n))!=old for (p,n),old in zip(inputs,before)):raise AssertionError('Raster block input changed')
  self.audit_blocks+=1
 def hook(self,u,a,n,ctx):
  if a not in (self.va(0x76d5a7),self.va(0x76d2d5),0x1201000,0x1201010,0x1201020,0x1201030):return
  sp=u.reg_read(UC_X86_REG_ESP)
  def arg(n):return struct.unpack('<I',u.mem_read(sp+4+4*n,4))[0]
  nargs=0;value=0
  if a==self.va(0x76d5a7):
   value=self.allocate(arg(0))
  elif a==self.va(0x76d2d5):
   if arg(0) and not any(p==arg(0) for p,n in self.allocations):raise AssertionError('Invalid fixture free')
  elif a==0x1201000:self.pos=0;value=1;nargs=4
  elif a==0x1201010:
   size=arg(1);destination=arg(0)
   if not (STACK-0x2000<=destination and destination+size<=STACK or any(p<=destination and destination+size<=p+n for p,n in self.allocations)):
    raise AssertionError('Loader file read outside allocated/stack output')
   data=self.file[self.pos:self.pos+size];self.pos+=len(data);u.mem_write(destination,data);value=len(data);nargs=8
  elif a==0x1201020:
   offset=struct.unpack('<i',struct.pack('<I',arg(0)))[0];self.pos=offset+(self.pos if arg(1)==1 else 0);value=self.pos;nargs=8
  elif a==0x1201030:pass
  else:return
  self.counts[hex(a)]=self.counts.get(hex(a),0)+1
  u.reg_write(UC_X86_REG_EAX,value);u.reg_write(UC_X86_REG_EIP,struct.unpack('<I',u.mem_read(sp,4))[0]);u.reg_write(UC_X86_REG_ESP,sp+4+nargs)
 def load(self,path):
  model=self.allocate(32);self.file=Path(path).read_bytes()
  def audit(u,access,p,n,value,context):
   if p>=0x1300000 and not any(lo<=p and p+n<=lo+size for lo,size in self.allocations):
    raise AssertionError('Original loader write outside allocated blocks')
  hook=self.u.hook_add(UC_HOOK_MEM_WRITE,audit)
  try:self.checked_call(0x70dbc0,[0x1200000,0],model,writes=[(0x1300000,0x300000)],inputs=[(0x1200000,0x104)])
  finally:self.u.hook_del(hook)
  self.check_heap()
  assert self.u.reg_read(UC_X86_REG_EAX)==1
  return model
 def metadata(self,model):
  count,tailers=struct.unpack('<2I',self.u.mem_read(model+4,8))
  if count!=tailers or count!=1:raise ValueError('Stock single-section loader profile only')
  tail=struct.unpack('<I',self.u.mem_read(model+0x14,4))[0];result=[count]
  for section in range(count):
   p=tail+section*0xa4;size=list(self.u.mem_read(p+0xa0,4));result+=size
   result+=list(struct.unpack('<13I',self.u.mem_read(p+12,52)))
   result+=list(struct.unpack('<24I',self.u.mem_read(p+0x40,96)))
   starts,ends,spans=struct.unpack('<3I',self.u.mem_read(p,12));blob=bytearray()
   for col in range(size[0]*size[1]):
    lo=struct.unpack('<i',self.u.mem_read(starts+4*col,4))[0];hi=struct.unpack('<i',self.u.mem_read(ends+4*col,4))[0]
    if lo==hi==-1:data=b''
    else:data=bytes(self.u.mem_read(spans+lo,hi-lo+1))
    blob+=struct.pack('<I',len(data))+data
   result.append(hashlib.sha256(blob).hexdigest())
  return list(map(str,result))
 def draw(self,model,matrix,vpl,shades):
  self.put(self.va(0xade070),0);self.put(self.va(0xade074),1);self.put(self.va(0x7e35d0),1)
  self.u.mem_write(self.va(0xadc068),vpl[784:])
  self.u.mem_write(self.va(0xae0870),bytes(shades))
  outputs=[(self.va(p),n) for p,n in [(0x7e35d0,4),(0xab84d0,65548),(0xac8710,8),(0xac8838,12),(0xac8848,136),(0xacaa50,20),(0xacae68,65536),(0xae0470,48)]]
  self.checked_call(0x70bc30,writes=outputs,inputs=self.heap_inputs())
  self.u.mem_write(ARG,struct.pack('<12f',*matrix))
  self.checked_call(0x70bf20,[0,ARG],model,0,writes=outputs,inputs=[(ARG,48),*self.heap_inputs()])
  self.checked_call(0x70c340,ecx=ARG+128,writes=[*outputs,(ARG+128,24)],inputs=[(ARG,48),*self.heap_inputs(),(self.va(0xadc068),len(vpl)-784),(self.va(0xae0870),256)])
  words=struct.unpack('<24I',self.u.mem_read(self.va(0xac8848)+0x28,96));walk=struct.unpack('<i',self.u.mem_read(self.va(0xac8848)+12,4))[0]
  return bytes(self.u.mem_read(self.va(0xacae68),65536)),[*struct.unpack('<6i',self.u.mem_read(ARG+128,24)),walk,*words]
 def matrices(self,body,turret):
  unit=0x1100000;loco=0x1101000;key=0x1102000;out=ARG+512
  self.u.mem_write(unit,bytes(0x600));self.u.mem_write(loco,bytes(0x100));self.put(loco+12,unit)
  for offset,heading in [(0x2e0,body),(0x2f8,turret)]:self.put(unit+offset,heading);self.put(unit+offset+4,heading)
  self.put(key,0);self.checked_call(0x49fc20,[loco+4,out,key],writes=[(out,48),(key,4)],inputs=[(unit,0x600),(loco,0x100)]);bodybytes=bytes(self.u.mem_read(out,48))
  cache=struct.unpack('<I',self.u.mem_read(key,4))[0]
  self.u.mem_write(STACK+0x90,bodybytes);self.u.reg_write(UC_X86_REG_EBP,unit);self.u.reg_write(UC_X86_REG_ESP,STACK)
  self.block(0x6f4744,0x6f47b4,stack_size=0xc0,inputs=[(unit,0x600),(loco,0x100)])
  turretbytes=bytes(self.u.mem_read(STACK+0x90,48))
  # Exact camera-init tail; its two degree constants are initialized by original routines.
  self.checked_call(0x70c7b0,writes=[(self.va(0xadf388),8)])
  self.checked_call(0x70c7d0,writes=[(self.va(0xadedf0),8)])
  self.block(0x70d6de,0x70d714,writes=[(self.va(0xadf208),48)],inputs=[(unit,0x600),(loco,0x100)])
  camerabytes=bytes(self.u.mem_read(self.va(0xadf208),48))
  return [struct.unpack('<12f',v) for v in (bodybytes,turretbytes,camerabytes)],list(struct.unpack('<36I',bodybytes+turretbytes+camerabytes)),cache
 def multiply(self,a,b):
  self.u.mem_write(ARG,struct.pack('<24f',*a,*b));self.checked_call(0x58de30,[ARG+48],ARG+96,ARG,writes=[(ARG+96,48)],inputs=[(ARG,96)])
  return struct.unpack('<12f',self.u.mem_read(ARG+96,48))
 def shades(self,model,matrix):
  self.u.mem_write(ARG,struct.pack('<12f',*matrix));self.checked_call(0x58cd10,ecx=ARG+48,writes=[(ARG+48,48)])
  # The default light is initialized by the original helper, with its original angle.
  angle=struct.unpack('<I',self.u.mem_read(self.va(0x785cf0),4))[0]
  self.checked_call(0x70ca10,[angle],writes=[(self.va(0x821d80),12),(self.va(0x821dcc),16)])
  self.checked_call(0x710740,writes=[(self.va(0xae0870),256)])
  self.checked_call(0x70bb30,[0,ARG,ARG+48,self.va(0x821dd0),0x40400000],model,0,writes=[(self.va(0xae0870),256)],inputs=[(ARG,96),*self.heap_inputs()])
  return list(self.u.mem_read(self.va(0xae0870),256))
