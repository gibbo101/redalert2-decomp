# SPDX-License-Identifier: GPL-3.0-or-later
"""Hash-pinned healthy Terrain caller and complete ordinary format-3 SHP draws.
Heap/free, map lookup and actor virtual image are explicit isolation services.
Original shape/clipping/BSurface/RLE spans and LightConvert execute unchanged.
"""
import struct
from original_unit_light import UnitLightOracle
from original_presentation import ARG
from scenery_profiles import address
from unicorn import UC_HOOK_CODE, UC_HOOK_MEM_WRITE
from unicorn.x86_const import *

class SceneryOracle(UnitLightOracle):
 def __init__(self,exe,palette,*,allow_patched=False):
  super().__init__(exe,allow_patched=allow_patched)
  self.put(self.va(0x83b2e0),0x39e77bef) # supplied RGB565 masks, previously recovered
  self.scheme([0,0,0],palette,palette)
  self.cvt=struct.unpack('<I',self.u.mem_read(0x1b4030c,4))[0]
  self.body_blitter=struct.unpack('<I',self.u.mem_read(self.cvt+0x158,4))[0]
  self.shadow_blitter=struct.unpack('<I',self.u.mem_read(self.cvt+0x114,4))[0]
  self.put(self.shadow_blitter+4,0x7bef)
  for obj,table,target in ((self.body_blitter,0x788fa8,0x48bc60),(self.shadow_blitter,0x789074,0x48a4a0)):
   assert struct.unpack('<I',self.u.mem_read(obj,4))[0]==self.va(table)
   assert struct.unpack('<I',self.u.mem_read(self.va(table)+4,4))[0]==self.va(target)
 def va(self,disc_va):return address(self.profile,disc_va)
 def heap_except(self,writes):
  # Preserve each allocated input outside explicitly mutable converter fields.
  regions=[]
  for base,size in self.allocations:
   pieces=[(base,base+size)]
   for p,n in writes:
    pieces=[part for lo,hi in pieces for part in
            ((lo,min(hi,p)),(max(lo,p+n),hi)) if part[0]<part[1]]
   regions.extend((lo,hi-lo) for lo,hi in pieces)
  return regions
 def checked_scenery(self,va,args,actor=0,cvt=0,*,writes=(),inputs=()):
  hook=self.u.hook_add(UC_HOOK_MEM_WRITE,self.guarded_heap_write)
  try:self.checked_unit(va,args,actor,cvt,writes=writes,inputs=inputs)
  finally:self.u.hook_del(hook)
  self.check_heap()
 def draw_contract(self,w,h,blob,cvt):
  surfaces=[(p,28) for p in (0x1600000,0x1600100,0x1600200,0x1600300)]
  writes=[(0x1700000,w*h*2),(0x1780000,w*h*2),(cvt+0x17c,4),
          (self.alpha_map+0x20004,4),*[(p+12,4) for p,n in surfaces]]
  inputs=[(0x1b90000,len(blob)),(ARG,24),(0x1800000,w*h*2),(0x1600400,48),(0x1600500,48),
          (cvt,0x17c),(cvt+0x180,0x80),(self.alpha_map,0x20004),*surfaces,*self.heap_except(writes)]
  # Synthetic RGB565 lookup palette is distinct from allocated owned converters.
  inputs.append((0x1900000,53*512))
  return writes,inputs
 def inputs(self,frames,height,light,location=(13,-17),clip=(4,3,90,80),render_full=False,canvas=(155,155)):
  actor=0x1b10000;kind=0x1b11000;vt=0x1b12000;cell=0x1b13000;shape=0x1b90000
  self.u.mem_write(actor,bytes(0x200));self.u.mem_write(kind,bytes(0x400));self.u.mem_write(cell,bytes(0x200));self.u.mem_write(vt,bytes(0x200))
  self.put(actor,vt);self.put(actor+0xb0,kind);self.put(actor+0x6c,2)
  self.put(actor+0x88,10*256+128);self.put(actor+0x8c,11*256+128);self.put(actor+0x90,height)
  self.put(vt+0x1a0,self.va(0x41b320));self.put(vt+0x1b8,self.va(0x5ccd40));self.put(vt+0x68,0x1202300)
  self.put(cell+0x34,self.cvt);self.u.mem_write(cell+0x10a,struct.pack('<h',123));self.u.mem_write(cell+0x10c,struct.pack('<h',light))
  self.u.mem_write(shape,struct.pack('<4H',0,*canvas,frames));self.u.mem_write(self.va(0x7c3965),b'\1');self.put(self.va(0x821c7c),0x1600000)
  self.u.mem_write(ARG,struct.pack('<6i',*location,*clip));records=[]
  def service(u,a,n,ctx):
   if a not in (self.va(0x5453b0),0x1202300,self.va(0x49ea80)):return
   sp=u.reg_read(UC_X86_REG_ESP);args=struct.unpack('<13I',u.mem_read(sp+4,52));pop=4;value=cell
   if a==self.va(0x5453b0):
    assert u.reg_read(UC_X86_REG_ECX)==self.va(0x81a800)
    assert struct.unpack('<2h',u.mem_read(args[0],4))==(10,11)
   if a==0x1202300:
    assert u.reg_read(UC_X86_REG_ECX)==actor
    value=shape;pop=0
   elif a==self.va(0x49ea80):
    signed=lambda x:struct.unpack('<i',struct.pack('<I',x))[0]
    assert args[0]==shape and args[5]==0 and args[9:]==(0,0,0,0)
    assert u.reg_read(UC_X86_REG_EDX)==self.cvt and u.reg_read(UC_X86_REG_ECX)==0x1600000
    assert struct.unpack('<2i',u.mem_read(args[2],8))==tuple(location)
    assert struct.unpack('<4i',u.mem_read(args[3],16))==tuple(clip)
    records.append([signed(args[i]) for i in (1,4,6,7,8)]);pop=52;value=0
    if render_full:return # Execute the original shape draw, with no redirection.
   u.reg_write(UC_X86_REG_EAX,value);u.reg_write(UC_X86_REG_EIP,struct.unpack('<I',u.mem_read(sp,4))[0]);u.reg_write(UC_X86_REG_ESP,sp+4+pop)
  hook=self.u.hook_add(UC_HOOK_CODE,service)
  try:
   writes=[];immutable=[(actor,0x200),(kind,0x400),(vt,0x200),(cell,0x200),(ARG,24)]
   if render_full:
    w,h=struct.unpack('<2I',self.u.mem_read(0x1600004,8))
    row_writes,row_inputs=self.draw_contract(w,h,bytes(self.u.mem_read(shape,self.shape_size)),self.cvt)
    writes+=row_writes;immutable+=row_inputs
   else:immutable+=self.heap_inputs()+[(shape,8)]
   self.checked_scenery(0x6d8b00,[ARG,ARG+8],actor,writes=writes,inputs=immutable)
  finally:self.u.hook_del(hook)
  assert len(records)==2
  return [v for record in records for v in record]
 def scene(self,blob,w,h,location,clip,height,light,colors,depth,alpha,palette):
  self.blit(w,h,[0],1,1,[0,0,1,1],[0,0],[0,0,w,h],-1,1000,colors,depth,alpha,palette)
  self.put(self.body_blitter+4,0x1900000);self.put(self.body_blitter+8,self.alpha_map)
  self.u.mem_write(0x1b90000,blob);self.shape_size=len(blob)
  self.inputs(2,height,light,location,clip,True,struct.unpack_from('<2H',blob,2))
  return [list(struct.unpack('<'+str(w*h)+'H',self.u.mem_read(addr,w*h*2))) for addr in (0x1700000,0x1780000)]
 def converter(self,primary,secondary,tint,shades):
  cvt=0x1b60000;pal=0x1b61000;other=0x1b62000;surface=0x1b43000
  self.u.mem_write(cvt,bytes(0x200));self.u.mem_write(pal,bytes(primary));self.u.mem_write(other,bytes(secondary))
  self.surface(surface,160,160,2,0x1700000)
  # Original 41E3E0 reuses by shade count, increments +0x20004, or
  # registers one new table. The supplied array has spare capacity; no growth.
  registry,count=struct.unpack('<I',self.u.mem_read(self.va(0x824904),4))[0],struct.unpack('<I',self.u.mem_read(self.va(0x824910),4))[0]
  tables=list(struct.unpack('<'+'I'*count,self.u.mem_read(registry,count*4)))
  registries=[]
  for ptr_va,count_va in ((0x839464,0x839470),(0x81a6bc,0x81a6c8)):
   ptr=struct.unpack('<I',self.u.mem_read(self.va(ptr_va),4))[0]
   size=struct.unpack('<I',self.u.mem_read(self.va(count_va),4))[0]
   registries.append((ptr,size))
  writes=[(cvt,0x200),(0x1300000,0x300000),*[(p+0x20004,4) for p in tables],
          (self.va(0x824910),4),(registry+count*4,4),
          (self.va(0x839470),4),(self.va(0x81a6c8),4),*[(p+n*4,4) for p,n in registries]]
  self.checked_scenery(0x5368f0,[pal,other,surface,*tint,0,0,shades],cvt,
   writes=writes,inputs=[(pal,768),(other,768),(surface,28),(self.alpha_map,0x20004),(registry,count*4),
    *[(p,n*4) for p,n in registries],*self.heap_except(writes)])
  mask=struct.unpack('<I',self.u.mem_read(cvt+0x190,4))[0]
  assert set(self.u.mem_read(mask,256))=={1}
  table=struct.unpack('<I',self.u.mem_read(cvt+0x170,4))[0]
  values=list(struct.unpack('<'+str(shades*256)+'H',self.u.mem_read(table,shades*512)))
  return cvt,values
 def draw(self,blob,frame,w,h,location,clip,flags,z,gradient,brightness,colors,depth,alpha,palette,cvt=None):
  self.blit(w,h,[0],1,1,[0,0,1,1],[0,0],[0,0,w,h],-1,1000,colors,depth,alpha,palette)
  if cvt is None:
   cvt=self.cvt;self.put(self.body_blitter+4,0x1900000);self.put(self.body_blitter+8,self.alpha_map)
  shape=0x1b90000;self.u.mem_write(shape,blob);self.u.mem_write(ARG,struct.pack('<6i',*location,*clip))
  writes,inputs=self.draw_contract(w,h,blob,cvt)
  self.checked_scenery(0x49ea80,[shape,frame,ARG,ARG+8,flags,0,z,gradient,brightness,0,0,0,0],0x1600000,cvt,writes=writes,inputs=inputs)
  return [list(struct.unpack('<'+str(w*h)+'H',self.u.mem_read(addr,w*h*2))) for addr in (0x1700000,0x1780000)]
