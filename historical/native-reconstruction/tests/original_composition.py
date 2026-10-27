# SPDX-License-Identifier: GPL-3.0-or-later
"""Original world projection and complete flat unit/TMP composition on original BSurface methods."""
import struct
from original_raster import RasterOracle
from original_presentation import ARG,STACK
from composition_profiles import address
from unicorn import UC_HOOK_CODE, UC_HOOK_MEM_WRITE
from unicorn.x86_const import *
class CompositionOracle(RasterOracle):
 def __init__(self,exe,*,allow_patched=False):
  super().__init__(exe,allow_patched=allow_patched);self.u.mem_map(0x1600000,0x400000)
  for fn,p in [(0x6975d0,0xaa5fa0),(0x697660,0xaa5fb0),(0x697930,0xaa5f70)]:
   self.checked_call(fn,writes=[(self.va(p),8),(self.va(0xaa6038),8)])
  self.scale=struct.unpack('<d',self.u.mem_read(self.va(0xaa5f70),8))[0]
  # Run original alpha table creation up to registration; allocator is research fixture.
  self.u.reg_write(UC_X86_REG_ESP,STACK);self.u.reg_write(UC_X86_REG_EDI,53)
  self.composition_block(0x41e40e,0x41e475,writes=[(0x1300000,0x300000)],budget=2000000,heap=True)
  self.alpha_map=self.u.reg_read(UC_X86_REG_EBP)
  self.check_heap()

 def va(self,disc_va):return address(self.profile,disc_va)
 def composition_block(self,start,stop,*,writes=(),inputs=(),stack_size=0,budget=100000,heap=False):
  before=[bytes(self.u.mem_read(p,n)) for p,n in inputs]
  guard=bytes([0xa7])*64;self.u.mem_write(STACK+stack_size,guard)
  self.u.reg_write(UC_X86_REG_ESP,STACK);self.u.reg_write(UC_X86_REG_FPCW,0xe7f)
  allowed=[(STACK-0x2000,STACK+stack_size),*[(p,p+n) for p,n in writes]]
  def audit(u,access,p,n,value,context):
   if not any(lo<=p and p+n<=hi for lo,hi in allowed):raise AssertionError(f'Unexpected composition block write {p:#x}/{n}')
   if heap and p>=0x1300000 and not any(lo<=p and p+n<=lo+size for lo,size in self.allocations):
    raise AssertionError('Alpha-map write outside guarded allocation')
  hook=self.u.hook_add(UC_HOOK_MEM_WRITE,audit)
  try:self.u.emu_start(self.va(start),self.va(stop),count=budget)
  finally:self.u.hook_del(hook)
  if self.u.reg_read(UC_X86_REG_EIP)!=self.va(stop) or self.u.reg_read(UC_X86_REG_ESP)!=STACK:
   raise AssertionError('Composition block EIP/ESP differs')
  if bytes(self.u.mem_read(STACK+stack_size,64))!=guard:raise AssertionError('Composition block caller stack changed')
  if any(bytes(self.u.mem_read(p,n))!=old for (p,n),old in zip(inputs,before)):raise AssertionError('Composition block input changed')
  self.audit_blocks+=1

 def surface(self,obj,w,h,bpp,data):
  for off,v in [(0,self.va(0x785ef8)),(4,w),(8,h),(12,0),(16,bpp),(20,data),(24,w*h*bpp)]:self.put(obj+off,v)
 def blit(self,w,h,source,src_width,src_height,srcbox,location,clip,zshift,brightness,colors,depth,alpha,palette):
  DEST=0x1600000;SOURCE=DEST+0x100;ZSURF=DEST+0x200;ASURF=DEST+0x300;Z=DEST+0x400;A=DEST+0x500;CVT=DEST+0x600;BLIT=DEST+0x900
  COLOR=0x1700000;ZDATA=0x1780000;ADATA=0x1800000;SDATA=0x1880000;PAL=0x1900000
  self.surface(DEST,w,h,2,COLOR);self.surface(SOURCE,src_width,src_height,1,SDATA);self.surface(ZSURF,w,h,2,ZDATA);self.surface(ASURF,w,h,2,ADATA)
  for obj,surface,data in [(Z,ZSURF,ZDATA),(A,ASURF,ADATA)]:
   for off,v in [(4,0),(16,0),(20,surface),(24,data),(28,data+w*h*2),(32,w*h*2),(36,32768),(40,w),(44,h)]:self.put(obj+off,v)
  self.put(self.va(0x821f8c),Z);self.put(self.va(0x8198d4),A)
  self.u.mem_write(COLOR,struct.pack('<'+'H'*len(colors),*colors));self.u.mem_write(ZDATA,struct.pack('<'+'H'*len(depth),*depth));self.u.mem_write(ADATA,struct.pack('<'+'H'*len(alpha),*alpha));self.u.mem_write(SDATA,bytes(source))
  self.u.mem_write(PAL,struct.pack('<'+'H'*len(palette),*palette));self.put(BLIT,self.va(0x78920c));self.put(BLIT+4,PAL);self.put(BLIT+8,self.alpha_map)
  self.put(CVT+8,1);self.put(CVT+0x98,BLIT);self.checked_call(0x485880,[0x2800],CVT,inputs=[(CVT,0x200)]);assert self.u.reg_read(UC_X86_REG_EAX)==BLIT
  self.u.mem_write(ARG,struct.pack('<10i',*srcbox,*location,*clip));
  surfaces=[(obj,28) for obj in (DEST,SOURCE,ZSURF,ASURF)]
  self.checked_call(0x49ef70,[SOURCE,ARG,ARG+16,ARG+24,0,BLIT,zshift,2,brightness,0],DEST,CVT,
                    writes=[(COLOR,w*h*2),(CVT+0x17c,4),*[(obj+12,4) for obj,n in surfaces]],
                    inputs=[(SDATA,len(source)),(ZDATA,w*h*2),(ADATA,w*h*2),(PAL,len(palette)*2),
                            (ARG,40),(Z,48),(A,48),(CVT,0x17c),(CVT+0x180,0x80),(BLIT,12),*surfaces,*self.heap_inputs()])
  for obj,n in surfaces:
   if self.u.mem_read(obj+12,4)!=bytes(4):raise AssertionError('BSurface lock count not restored')
  return list(struct.unpack('<'+'H'*(w*h),self.u.mem_read(COLOR,w*h*2))),list(struct.unpack('<'+'H'*(w*h),self.u.mem_read(ZDATA,w*h*2)))

 def projection(self,x,y,z):
  self.u.mem_write(ARG,struct.pack('<3i',x,y,z));self.checked_call(0x697c90,[ARG+16,ARG],writes=[(ARG+16,8)],inputs=[(ARG,12)])
  return list(struct.unpack('<2i',self.u.mem_read(ARG+16,8)))
 def order(self,heading):
  unit=0x1100000;typeaddr=0x1101000;vt=0x1102000
  self.u.mem_write(unit,bytes(0x700));self.u.mem_write(typeaddr,bytes(0x700));self.put(unit,vt)
  self.put(vt+0x3d8,0x1202200)
  for off,angle in [(0x2f8,heading)]:self.put(unit+off,angle);self.put(unit+off+4,angle)
  for off in (0xb8,0xbc,0xc0,0xc4):self.put(typeaddr+off,1)
  calls=[]
  def record(u,address,n,ctx):
   if address!=0x1202200:return
   sp=u.reg_read(UC_X86_REG_ESP);model=struct.unpack('<I',u.mem_read(sp+4,4))[0];calls.append(model-typeaddr)
   u.reg_write(UC_X86_REG_EIP,struct.unpack('<I',u.mem_read(sp,4))[0]);u.reg_write(UC_X86_REG_ESP,sp+4+36)
  hook=self.u.hook_add(UC_HOOK_CODE,record)
  self.u.reg_write(UC_X86_REG_EBP,unit);self.u.reg_write(UC_X86_REG_EBX,typeaddr);self.u.reg_write(UC_X86_REG_ESI,unit+0x2f8);self.u.reg_write(UC_X86_REG_ESP,STACK)
  self.u.reg_write(UC_X86_REG_FPCW,0xe7f)
  self.u.mem_write(STACK,bytes(0x1e0))
  try:self.composition_block(0x6f4a38,0x6f4b57,stack_size=0x1e0,inputs=[(unit,0x700),(typeaddr,0x700),(vt,0x400)])
  finally:self.u.hook_del(hook)
  if calls not in ([0xb8,0xc0],[0xc0,0xb8]):raise RuntimeError(f'Unexpected part dispatch: {calls}')
  return int(calls==[0xb8,0xc0])


class TmpOracle(CompositionOracle):
 def __init__(self,exe,*,allow_patched=False):
  super().__init__(exe,allow_patched=allow_patched);self.tmpheader=0x16e0000
  self.u.hook_add(UC_HOOK_CODE,self.getter)
 def getter(self,u,a,n,ctx):
  if a!=0x1202100:return
  sp=u.reg_read(UC_X86_REG_ESP);u.reg_write(UC_X86_REG_EAX,self.tmpheader);u.reg_write(UC_X86_REG_EIP,struct.unpack('<I',u.mem_read(sp,4))[0]);u.reg_write(UC_X86_REG_ESP,sp+4)
 def tmp(self,blob,x,y,level,sub=0):
  # Establish real surfaces, palette and alpha buffer through the unit fixture.
  w=h=96;palette=[(s<<8)|i for s in range(53) for i in range(256)]
  self.blit(w,h,[0],1,1,[0,0,1,1],[0,0],[0,0,w,h],-1,1000,[0]*(w*h),[65535]*(w*h),[128]*(w*h),palette)
  TYPE=0x1601000;VT=TYPE+0x400;CVT=0x1600600
  self.put(TYPE,VT);self.put(VT+0x9c,0x1202100);self.put(TYPE+0x2c0,1)
  self.put(CVT+0x16c,53);self.put(CVT+0x170,0x1900000)
  self.u.mem_write(self.tmpheader,blob)
  cols,rows=struct.unpack_from('<II',blob)
  for i in range(cols*rows):
   p=struct.unpack_from('<I',blob,16+4*i)[0]
   if p:self.put(self.tmpheader+16+4*i,self.tmpheader+p)
  self.put(self.alpha_map+0x20004,100);self.put(self.va(0x824910),1);self.put(self.va(0x824904),TYPE+0x600);self.put(TYPE+0x600,self.alpha_map)
  self.put(self.va(0x821954),0);self.put(self.va(0x83b2e0),0xffff)
  args=[CVT,sub,0x1600000,x,y,0,0,w,h,level,1000,1,0,0,0,0,0]
  # Original lazy diamond preparation: 30*60 byte offsets, 30*60*60
  # byte span lengths and 30*60 word offsets. The 29 populated rows and
  # overlapping a540b4 interior reference are not separate small arrays.
  globals=[(self.va(p),n) for p,n in [(0xa3ab20,0x6a),(0xa3a1ac,1800),(0xa3afb0,108000),(0xa54b80,3600),(0xa55fa5,1)]]
  self.checked_call(0x52a340,args,TYPE,writes=[(0x1700000,w*h*2),(0x1780000,w*h*2),
                    (0x160000c,4),(0x160020c,4),(0x160030c,4),(self.alpha_map+0x20004,4),*globals],
                    inputs=[(self.tmpheader,len(blob)),(0x1800000,w*h*2),(0x1900000,len(palette)*2),(TYPE,0x604)])
  self.check_heap()
  out=list(struct.unpack('<'+'H'*(w*h),self.u.mem_read(0x1700000,w*h*2)));z=list(struct.unpack('<'+'H'*(w*h),self.u.mem_read(0x1780000,w*h*2)))
  return out,z

class FlatDepthOracle:
 def __init__(self,exe,*,allow_patched=False):
  from original_movement import Oracle,UNIT,TYPE,VT
  # This local fixture uses only composition's inspected metadata; no broader
  # movement gate is enabled for other callers.
  class DepthFixture(Oracle):
   def va(self,disc_va):return address(self.profile,disc_va)
  self.o=DepthFixture(exe,allow_patched=allow_patched,audit_calls=True);o=self.o;o.begin(2688,2688,0,5,6)
  for fn in [0x6975d0,0x697660,0x697930]:o.call(fn,this=0)
  o.put(VT+0x1b8,o.va(0x5ccd40));o.put(o.va(0xa288f4),TYPE+0xd00);o.put(o.va(0xa3ab18),0);o.put(TYPE+0xd00,TYPE+0xc00)
  def dims():o.u.mem_write(o.arg(2),bytes(12));return o.arg(2)
  o.bind(0x5297a0,12,dims,'flat tile dimensions')
 def adjustment(self,height):
  from original_movement import UNIT,TYPE,LOCO,STACK as DEPTH_STACK
  o=self.o;o.put(UNIT+0x90,height)
  inputs=[(UNIT,0x1000),(TYPE,0x1000),(LOCO,0x100)];before=[bytes(o.u.mem_read(p,n)) for p,n in inputs]
  def audit(u,access,p,n,value,ctx):
   if not DEPTH_STACK-0x2000<=p or p+n>DEPTH_STACK:raise AssertionError(f'Unexpected flat depth write {p:#x}/{n}')
  hook=o.u.hook_add(UC_HOOK_MEM_WRITE,audit)
  try:v=o.call(0x6c52c0,this=UNIT,budget=150000)
  finally:o.u.hook_del(hook)
  if any(bytes(o.u.mem_read(p,n))!=old for (p,n),old in zip(inputs,before)):raise AssertionError('Flat depth fixture input changed')
  return struct.unpack('<i',struct.pack('<I',v))[0]
