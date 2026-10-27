# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete original Drive pose, actual map/Facing, and initialized ramp table."""
import struct
from original_ramp_geometry import RampGeometryOracle
from original_presentation import STOP,STACK
from verify_drive_shadow_pose import verify,RANGES,EXTRA
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_EDX,UC_X86_REG_ESP
ARENA=0x2600000;ACTOR=ARENA;LOCO=ARENA+0x1000;OUT=ARENA+0x2000;KEY=ARENA+0x2100
TABLE=0x2700000;CELL=0x2800000;MAP=0x8324e0;FALLBACK=0xa6f9f8
class DriveShadowPoseOracle(RampGeometryOracle):
 def __init__(self,exe):
  super().__init__(exe);self.inspection=verify(exe.read_bytes());self.active=False
  self.entries.update({hex(a):0 for a in EXTRA})
  for a in EXTRA:self.u.hook_add(UC_HOOK_CODE,self.entry,begin=a,end=a)
  self.u.hook_add(UC_HOOK_CODE,self.observe)
  self.u.mem_map(ARENA,0x3000);self.u.mem_map(TABLE,0x101000);self.lastIndex=None
  self.stock(0) # Actual unchanged numeric chains/matrix initializer in this guest.
  self.put(MAP+0x138,TABLE);self.put(MAP+0x13c,262144)
  self.pose_calls=0;self.key_writes=0;self.fallback_stores=0
 def block(self,u,a,n,ctx):
  if a!=STOP and not any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()):
   raise AssertionError(f'Uninspected Drive shadow block {a:#x}/{n}')
 def observe(self,u,a,n,ctx):
  if not self.active:return
  if a==0x548000:
   assert u.reg_read(UC_X86_REG_ECX)==MAP
   sp=u.reg_read(UC_X86_REG_ESP);p=int.from_bytes(u.mem_read(sp+4,4),'little')
   self.events.extend(['M',*map(str,struct.unpack('<3i',u.mem_read(p,12)))])
  elif a==0x718d60:self.events.extend(['R',str(u.reg_read(UC_X86_REG_EDX))])
  elif a==0x4b8be0:
   assert u.reg_read(UC_X86_REG_ECX)==ACTOR+0x2e0;self.events.append('F')
 def pose(self,v):
  kind,x,y,z,resident,ramp,desired,start,fstart,fduration,rate,tick,sstart,sremain,sduration,rx,ry,present,key,mode=v
  self.u.mem_write(ARENA,b'\xa5'*0x3000)
  self.put(LOCO+8,ACTOR);self.u.mem_write(ACTOR+0x88,struct.pack('<3i',x,y,z))
  self.u.mem_write(ACTOR+0x280,struct.pack('<2I',rx,ry))
  for off,n in ((0x2e0,desired),(0x2e4,start),(0x2e8,fstart),(0x2f0,fduration),(0x2f4,rate)):
   self.put(ACTOR+off,n)
  for off,n in ((0x20,sstart),(0x28,sremain),(0x2c,sduration)):self.put(LOCO+off,n)
  self.put(0xa40d2c,tick);self.put(KEY,key)
  if self.lastIndex is not None:self.put(TABLE+4*self.lastIndex,0)
  def div(n):return n//256 if n>=0 else -((-n)//256)
  index=(div(y)*512+div(x))&0xffffffff
  self.lastIndex=index if resident and index<262144 else None
  if self.lastIndex is not None:self.put(TABLE+4*index,CELL)
  self.u.mem_write(CELL,b'\xa5'*0x200);self.u.mem_write(FALLBACK,b'\xa7'*0x148)
  self.put(FALLBACK+0x24,(-30000&65535)|(29000<<16))
  self.u.mem_write(CELL+0x11c,bytes([ramp]));self.u.mem_write(FALLBACK+0x11c,bytes([ramp]))
  fallback=bytes(self.u.mem_read(FALLBACK,0x148));arena=bytes(self.u.mem_read(ARENA,0x3000));self.events=[]
  def store(u,access,a,n,value,ctx):
   if a==KEY:
    assert n==4;self.events.extend(['K',str(value&0xffffffff)]);self.key_writes+=1
   elif a==FALLBACK+0x24:
    assert n==4;self.fallback_stores+=1
  hook=self.u.hook_add(UC_HOOK_MEM_WRITE,store);self.active=True
  try:self.checked_call(0x4a0500 if kind else 0x53d0d0,[LOCO,OUT,KEY if present else 0],
   writes=[(OUT,48),(KEY,4),(FALLBACK+0x24,4)],
   inputs=self.inputs+[(MAP+0x138,8),(CELL,0x200),(0xaf8608,21*48),(0xa40d2c,4)])
  finally:self.active=False;self.u.hook_del(hook)
  assert self.u.reg_read(UC_X86_REG_EAX)==OUT
  after=bytearray(self.u.mem_read(ARENA,0x3000))
  after[OUT-ARENA:OUT-ARENA+48]=arena[OUT-ARENA:OUT-ARENA+48]
  after[KEY-ARENA:KEY-ARENA+4]=arena[KEY-ARENA:KEY-ARENA+4]
  assert bytes(after)==arena
  after=bytearray(self.u.mem_read(FALLBACK,0x148));after[0x24:0x28]=fallback[0x24:0x28]
  assert bytes(after)==fallback
  self.pose_calls+=1
  return list(map(str,struct.unpack('<12I',self.u.mem_read(OUT,48))))+[
   str(int.from_bytes(self.u.mem_read(KEY,4),'little')),str(int.from_bytes(self.u.mem_read(FALLBACK+0x24,4),'little'))]+self.events
