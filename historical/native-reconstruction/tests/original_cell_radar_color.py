# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete Cell colors, optionally inside actual terrain/projection owners."""
import struct
from original_radar_terrain import RadarTerrainOracle,MAP,CELLS
from original_radar_projection import BASE,SIZE,RGB
from original_presentation import STACK,STOP
from verify_cell_radar_color import verify,RANGES,DATA
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP
TYPES=0x4000000;IMAGES=TYPES+0x4000;PRIMARY=TYPES+0x6000;OVERLAYS=TYPES+0x7000;OVERLAY=TYPES+0x8000;ANIMATION=TYPES+0x9000;SCENARIO=TYPES+0xa000;OUTPUT=BASE+0x2400
class CellRadarColorOracle(RadarTerrainOracle):
 def __init__(self,exe):
  super().__init__(exe);self.inspection=verify(exe.read_bytes());self.u.mem_map(TYPES,0x10000);self.standalone=False
 def code(self,u,a,n,ctx):
  if not self.active or a==STOP:return
  sp=u.reg_read(UC_X86_REG_ESP);ecx=u.reg_read(UC_X86_REG_ECX)
  if a==0x4712c0:
   assert ecx in self.ids;self.outputs=[self.word(sp+4),self.word(sp+8)];self.counts['color_root']+=1
   if not self.standalone:self.emit('Q',self.ids[ecx])
  if a==0x471760:
   assert ecx in self.ids and [self.word(sp+4),self.word(sp+8)]==[36,0];self.emit('D',36,0);self.counts['supplied_resident']+=1;self.ret(8,1 if self.profile[0] else 0);return
  if a==0x5dd000:
   assert ecx==OVERLAY;arg=self.word(sp+8);out=self.word(sp+4);id=self.currentOverlay
   assert STACK-0x1000<=out<=STACK-3;self.emit('O',id,arg);self.counts['supplied_overlay_color']+=1
   u.mem_write(out,bytes((self.seed+id*13+arg*29+k*7)&255 for k in range(3)));self.ret(8,out);return
  if a==0x5dc0b0:
   self.emit('E',ecx);self.counts['supplied_resource']+=1;self.ret(0,self.profile[12]&0xffffffff);return
  if a==0x52b560:
   assert TYPES<=ecx<TYPES+8*0x400 and (ecx-TYPES)%0x400==0;id=(ecx-TYPES)//0x400;self.emit('L',id);self.counts['supplied_image_install']+=1
   self.put(ecx+0xa4,IMAGES+id*0x200);self.typeExpected[ecx-TYPES+0xa4:ecx-TYPES+0xa8]=struct.pack('<I',IMAGES+id*0x200);self.ret(0,1);return
  if a==0x4767a0:self.emit('J',self.word(sp+4),self.word(sp+8));self.counts['variant']+=1
  if a in (0x529520,0x52b730,0x5293d0,0x5293a0,0x63cdf0,0x432d70):self.counts[hex(a)]+=1
  if any(lo<=a and a+n<=lo+size for lo,size in RANGES.items() if lo not in self.parentRanges):return
  if self.standalone:
   assert any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected Cell color instruction',hex(a));return
  super().code(u,a,n,ctx)
 def write(self,u,access,p,n,value,ctx):
  if not self.active:return
  value&=(1<<(8*n))-1
  for id,base in enumerate(self.outputs):
   if base<=p and p+n<=base+3:
    self.emit('F',id+1,p-base,n,value)
    if BASE<=p and p+n<=BASE+SIZE:self.expected[p-BASE:p-BASE+n]=value.to_bytes(n,'little')
    return
  super().write(u,access,p,n,value,ctx)
 def setup(self):
  p=self.profile;r,flags,tile,overlay,data,sub,variants,raw,mode,frames,nulls,force,resource,lazy,scale=p;u=self.u;self.outputs=[]
  self.currentOverlay=24 if flags&0x100 else overlay
  u.mem_write(TYPES,b'\xa5'*0x10000)
  for id in range(8):
   obj=TYPES+id*0x400;image=IMAGES+id*0x200
   self.put(obj,0x7a51a8);self.put(obj+0x2c0,variants);self.put(obj+0x28c,TYPES+(id+1)*0x400);self.put(obj+0xa4,0 if lazy else image);u.mem_write(obj+0x2c4,bytes([lazy]));u.mem_write(image,bytes(288));self.put(image,4);self.put(image+4,1);self.put(image+8,60);self.put(image+12,30)
   for i in range(4):
    header=image+32+i*64;self.put(image+16+i*4,0 if nulls&(1<<i) else header);self.put(header+0x24,4 if force else 0);u.mem_write(header+0x2b,bytes((self.seed+id*41+i*17+k*53)&255 for k in range(3)))
  self.put(PRIMARY,TYPES);self.put(PRIMARY+4,TYPES+0x400)
  for i in range(251):self.put(OVERLAYS+i*4,OVERLAY)
  u.mem_write(OVERLAY+0x279,bytes([mode&1]));self.put(OVERLAY+0x26c,ANIMATION if mode&2 else 0);self.put(ANIMATION,0x7a51a8);self.put(ANIMATION+0xa4,ANIMATION+0x500)
  header=ANIMATION+0x500;u.mem_write(header,bytes(104));u.mem_write(header+6,struct.pack('<h',frames))
  for i in range(4):u.mem_write(header+20+i*24,bytes((self.seed+i*23+k*19)&255 for k in range(3)))
  for cell in self.ids:
   self.put(cell+0x38,tile);self.put(cell+0x44,overlay);self.put(cell+0x140,flags);u.mem_write(cell+0x11a,bytes([sub]));u.mem_write(cell+0x11e,bytes([data]))
  self.put(0xa40cd4,PRIMARY);self.put(0xa52f00,1);self.put(0xa35dec,OVERLAYS);self.put(0xa3d290,SCENARIO);self.put(SCENARIO+0x838,0);self.put(0x79abb8,scale)
  u.mem_write(0x850c47,b'\1')
  for i in range(16):self.put(0x7d2b90+i*4,raw)
  for i in range(64):self.put(0x850aa8+i*4,raw)
  self.expected=bytearray(u.mem_read(BASE,SIZE));self.mapExpected=bytearray(u.mem_read(MAP,0x1600));self.typeExpected=bytearray(u.mem_read(TYPES,0x10000))
 def checked_call(self,*args,**kwargs):
  self.setup();kwargs['writes']=[*kwargs.get('writes',[]),*[(TYPES+i*0x400+0xa4,4) for i in range(8)]]
  kwargs['inputs']=[*kwargs.get('inputs',[]),*RANGES.items(),*[(a,len(v)) for a,v in DATA.items()],(0x7a51a8,0xa0),(0xa40cd4,4),(0xa52f00,4),(0xa35dec,4),(0xa3d290,4),(0x79abb8,4),(0x850c47,1),(0x850aa8,256),(0x7d2b90,64)]
  from verify_radar_terrain import RANGES as PARENT
  self.parentRanges=PARENT
  super().checked_call(*args,**kwargs);assert bytes(self.u.mem_read(TYPES,0x10000))==self.typeExpected
 def run(self,f):
  self.profile=f['profile'];self.standalone=f['kind']=='K'
  if not self.standalone:return super().run(f['terrain'])
  self.seed=f['seed'];self.ids={CELLS:0};u=self.u;u.mem_write(BASE,b'\xa5'*SIZE);u.mem_write(CELLS+0x24,struct.pack('<2h',1,3));u.mem_write(OUTPUT,bytes([9,8,7,6,5,4]));self.trace=[];self.active=True
  try:self.checked_call(0x4712c0,[OUTPUT,OUTPUT if f['alias'] else OUTPUT+3],CELLS,writes=[(OUTPUT,6)])
  finally:self.active=False
  assert bytes(u.mem_read(BASE,SIZE))==self.expected and bytes(u.mem_read(MAP,0x1600))==self.mapExpected
  self.emit('R',*u.mem_read(OUTPUT,6),*[int(self.word(TYPES+i*0x400+0xa4)!=0) for i in range(8)]);return self.trace
