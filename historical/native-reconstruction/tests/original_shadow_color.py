# SPDX-License-Identifier: GPL-3.0-or-later
"""Original palette-remap prefix, shadow projection/plot and complete shadow blit."""
import struct
from original_composition import CompositionOracle
from original_presentation import ARG,STACK,STOP
from shadow_color_profiles import address
from unicorn import UC_HOOK_CODE, UC_HOOK_MEM_WRITE
from unicorn.x86_const import *

class ShadowColorOracle(CompositionOracle):
 def __init__(self,exe,*,allow_patched=False):
  super().__init__(exe,allow_patched=allow_patched)
  # Original initialization builds the flat/ramp shadow matrix table too.
  self.checked_call(0x70cac0,writes=[(self.va(p),n) for p,n in
   [(0xade078,0x150),(0xade1c8,0xc00),(0xadee00,0x3f0),(0xadf208,48),(0xadf248,0x140),(0xadf390,0xc00),(0xadff98,0x4c0)]],
   inputs=[(self.va(p),8) for p in (0xadedf8,0xadf200,0xadedf0,0xadf388)])
  # Avoid a previously translated block crossing the raster fixture's partial
  # camera-setup stop address (Unicorn cache detail, no instruction patch).
  self.u.ctl_remove_cache(self.va(0x70cac0),self.va(0x70d740))
 def va(self,disc_va):return address(self.profile,disc_va)
 def hsv(self,color):
  self.u.mem_write(ARG,bytes(color));self.checked_call(0x4fe400,[ARG+16],ARG,writes=[(ARG+16,3)],inputs=[(ARG,3)])
  return list(self.u.mem_read(ARG+16,3))
 def remap(self,color,palette):
  self.u.mem_write(ARG,bytes(color));self.u.mem_write(ARG+1024,bytes(palette))
  # This prefix stops with an open frame. Audit its own block contract,
  # preserving the return address, arguments and caller stack, rather than
  # imposing a callable-return ESP/register contract.
  caller=struct.pack('<3I',STOP,0,ARG+2048);guard=bytes([0xa7])*64
  self.u.mem_write(STACK,caller+guard)
  before=bytes(self.u.mem_read(ARG,3))+bytes(self.u.mem_read(ARG+1024,768))
  for reg,val in [(UC_X86_REG_ESP,STACK),(UC_X86_REG_ECX,ARG),(UC_X86_REG_EDX,ARG+1024),(UC_X86_REG_FPCW,0xe7f)]:self.u.reg_write(reg,val)
  def audit(u,access,p,n,value,ctx):
   if not (STACK-0x2000<=p and p+n<=STACK or ARG+2048<=p and p+n<=ARG+2816):
    raise AssertionError(f'Unexpected ColorScheme prefix write {p:#x}/{n}')
  hook=self.u.hook_add(UC_HOOK_MEM_WRITE,audit)
  try:self.u.emu_start(self.va(0x65a4f0),self.va(0x65a5ed),count=100000)
  finally:self.u.hook_del(hook)
  if self.u.reg_read(UC_X86_REG_EIP)!=self.va(0x65a5ed):raise RuntimeError('ColorScheme prefix did not finish')
  if self.u.reg_read(UC_X86_REG_ESP)!=STACK-0x40 or self.u.reg_read(UC_X86_REG_EBP)!=STACK-4:
   raise AssertionError('ColorScheme prefix open frame changed')
  if bytes(self.u.mem_read(STACK,len(caller)+len(guard)))!=caller+guard:raise AssertionError('ColorScheme prefix caller stack changed')
  if bytes(self.u.mem_read(ARG,3))+bytes(self.u.mem_read(ARG+1024,768))!=before:raise AssertionError('ColorScheme prefix input changed')
  self.audit_blocks+=1
  return list(self.u.mem_read(ARG+2048,768))
 def offset(self,angle):
  self.checked_call(0x70ca10,[struct.unpack('<I',struct.pack('<f',angle))[0]],writes=[(self.va(0x821d80),12),(self.va(0x821dcc),16)])
  return list(struct.unpack('<3I',self.u.mem_read(self.va(0x821d80),12)))
 def shadow_pose(self,heading):
  unit=0x1100000;loco=0x1101000;key=0x1102000;cell=0x1103000
  self.u.mem_write(unit,bytes(0x700));self.u.mem_write(loco,bytes(0x100));self.u.mem_write(cell,bytes(0x180))
  self.put(loco+12,unit);self.put(unit+0x2e0,heading);self.put(unit+0x2e4,heading);self.put(key,0)
  def flat(u,a,n,ctx):
   if a!=self.va(0x545340):return
   sp=u.reg_read(UC_X86_REG_ESP);u.reg_write(UC_X86_REG_EAX,cell);u.reg_write(UC_X86_REG_EIP,struct.unpack('<I',u.mem_read(sp,4))[0]);u.reg_write(UC_X86_REG_ESP,sp+8)
  hook=self.u.hook_add(UC_HOOK_CODE,flat)
  try:self.checked_call(0x4a00d0,[loco+4,ARG,key],writes=[(ARG,48),(key,4)],inputs=[(unit,0x700),(loco,0x100),(cell,0x180),*self.heap_inputs()])
  finally:self.u.hook_del(hook)
  return [*struct.unpack('<12I',self.u.mem_read(ARG,48)),struct.unpack('<I',self.u.mem_read(key,4))[0]]
 def shadow(self,model,pose,camera,offset,style,x,y):
  stencil=0
  if style>=0:
   stencil=0x1608000;pixels=0x1610000
   self.surface(stencil,256,256,1,pixels)
   self.u.mem_write(pixels,bytes(37 if (i*3+j*7+style)%5<2 else 0 for j in range(256) for i in range(256)))
  outputs=[(self.va(p),n) for p,n in [(0x7e35d0,4),(0xab84d0,65548),(0xac8710,8),
   (0xac8838,12),(0xac8848,136),(0xacaa50,20),(0xacae68,65536),(0xadae68,72),(0xae0470,48)]]
  self.put(self.va(0x7e35d0),1);self.checked_call(0x70bc30,writes=outputs,inputs=self.heap_inputs())
  self.u.mem_write(ARG,struct.pack('<24f',*pose,*camera));self.u.mem_write(ARG+128,struct.pack('<3f',*offset))
  # Original argument order is camera, then model; the model transform runs
  # first, its Z is flattened, then the camera transform runs.
  self.checked_call(0x70bdc0,[0,ARG+48,ARG,ARG+128,stencil,x,y],model,0,writes=outputs,inputs=[(ARG,96),(ARG+128,12),*self.heap_inputs()])
  corners=list(struct.unpack('<12I',self.u.mem_read(self.va(0xadae68)+12,48)))
  self.checked_call(0x70c340,ecx=ARG+192,writes=[*outputs,(ARG+192,24),*([(stencil+12,4)] if stencil else [])],inputs=[(ARG,96),(ARG+128,12),*self.heap_inputs(),*([(stencil,28),(pixels,65536)] if stencil else [])])
  if stencil and self.u.mem_read(stencil+12,4)!=bytes(4):raise AssertionError('Stencil lock count not restored')
  return bytes(self.u.mem_read(self.va(0xacae68),65536)),[*struct.unpack('<6i',self.u.mem_read(ARG+192,24)),*corners]
 def shadow_blit(self,w,h,source,sw,sh,srcbox,loc,clip,z,colors,depth):
  # Reuse real surface/depth construction, then select the original shadow span.
  self.blit(w,h,source,sw,sh,srcbox,loc,clip,z,1000,colors,depth,[128]*(w*h),[0]*(53*256))
  self.u.mem_write(0x1700000,struct.pack('<'+'H'*len(colors),*colors))
  self.put(0x1600900,self.va(0x78939c));self.put(0x1600904,0x7bef);self.put(0x1600600+0x2c,0x1600900)
  self.checked_call(0x485880,[0x2001],0x1600600,inputs=[(0x1600600,0x200)]);assert self.u.reg_read(UC_X86_REG_EAX)==0x1600900
  self.u.mem_write(ARG,struct.pack('<10i',*srcbox,*loc,*clip))
  surfaces=[(obj,28) for obj in (0x1600000,0x1600100,0x1600200,0x1600300)]
  self.checked_call(0x49ef70,[0x1600100,ARG,ARG+16,ARG+24,0,0x1600900,z,2,1000,0],0x1600000,0x1600600,
   writes=[(0x1700000,w*h*2),(0x160077c,4),*[(obj+12,4) for obj,n in surfaces]],
   inputs=[(0x1880000,len(source)),(0x1780000,w*h*2),(0x1800000,w*h*2),(ARG,40),
    (0x1600400,48),(0x1600500,48),(0x1600600,0x17c),(0x1600780,0x80),(0x1600900,8),*surfaces,*self.heap_inputs()])
  for obj,n in surfaces:
   if self.u.mem_read(obj+12,4)!=bytes(4):raise AssertionError('Shadow BSurface lock count not restored')
  return list(struct.unpack('<'+'H'*(w*h),self.u.mem_read(0x1700000,w*h*2))),list(struct.unpack('<'+'H'*(w*h),self.u.mem_read(0x1780000,w*h*2)))
