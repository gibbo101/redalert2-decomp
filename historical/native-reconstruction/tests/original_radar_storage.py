# SPDX-License-Identifier: GPL-3.0-or-later
"""Original startup and projection on the same map/rectangles/storage."""
import struct
from original_radar_projection import RadarProjectionOracle,BASE,SIZE,MAP,OUT,SURFACE,RGB,PIXELS,BITMAP,VT,SPANS,RANGES,DATA,signed,digest
from original_presentation import STOP
from verify_radar_storage import verify
from unicorn.x86_const import UC_X86_REG_ECX,UC_X86_REG_ESP
FIRST=BASE+0x12000;DESC=FIRST+0x100;DEVICE=FIRST+0x200;DEVICE_SURFACE=FIRST+0x300;DEVICE_TABLE=FIRST+0x400;CREATE=FIRST+0x500;DESCRIBE=FIRST+0x600;FIRST_PIXELS=BASE+0x18000
class RadarStorageOracle(RadarProjectionOracle):
 def __init__(self,exe):
  self.joinedInspection=verify(exe.read_bytes());super().__init__(exe)
  self.firstClear=self.word(0x7a0be4+24);self.firstDestroy=self.word(0x7a0be4);self.secondDestroy=self.word(VT)
 def record(self,p,n,v):
  self.u.mem_write(p,int(v&((1<<(8*n))-1)).to_bytes(n,'little'));self.write(self.u,0,p,n,v,None)
 def code(self,u,a,n,ctx):
  if not self.active or a==STOP:return
  sp=u.reg_read(UC_X86_REG_ESP);ecx=u.reg_read(UC_X86_REG_ECX)
  if a==0x630a00:self.counts['startup']+=1
  if a==0x630b70:
   assert ecx==MAP and [self.word(sp+4*i) for i in range(2,5)]==[MAP+0x1498,MAP+0x1498,1]
   self.counts['projection']+=1
  if a==0x4aa4a0:self.counts['device_initializer']+=1
  if a in (self.firstDestroy,self.secondDestroy):
   assert ecx in (FIRST,SURFACE) and self.word(sp+4)==1
   self.emit('X',1 if ecx==FIRST else 2,1);self.counts['supplied_destroy']+=1;self.ret(4);return
  if a==0x781d3b:
   p=self.word(sp+4);assert p in (RGB,BITMAP);self.emit('F',3 if p==RGB else 4);self.counts['supplied_release']+=1;self.ret(0);return
  if a==0x782017:
   size=self.word(sp+4);caller=self.word(sp)
   if caller==0x630b17:assert size==36;self.emit('A',36);self.ret(0,FIRST);return
   if 0x4aa4a0<=caller<0x4aa59d:assert size==108;self.emit('A',108);self.ret(0,DESC);return
  if a==CREATE:
   assert [self.word(sp+i*4) for i in range(1,5)]==[DEVICE,DESC,FIRST+28,0]
   self.emit('C',*[self.word(DESC+o) for o in (0,4,8,12,104)]);self.record(FIRST+28,4,DEVICE_SURFACE)
   self.supply(FIRST_PIXELS,b'\xa5'*(self.word(FIRST+4)*self.word(FIRST+8)*2));self.counts['supplied_create']+=1;self.ret(16,0x80004005);return
  if a==DESCRIBE:
   assert [self.word(sp+4),self.word(sp+8)]==[DEVICE_SURFACE,DESC];self.emit('G',1)
   self.record(DESC+84,4,16);self.record(DESC+104,4,0x2040);self.counts['supplied_describe']+=1;self.ret(8,0x80004005);return
  if a==self.firstClear and ecx==FIRST:
   assert ecx==FIRST and self.word(sp+4)==0;self.emit('L',0)
   self.supply(FIRST_PIXELS,bytes(self.word(FIRST+4)*self.word(FIRST+8)*2));self.counts['supplied_first_clear']+=1;self.ret(4,1);return
  if a==0x632700:assert ecx==MAP;self.emit('Z');self.counts['supplied_finish']+=1;self.ret(0);return
  if a==0x631250:
   assert ecx==MAP and [self.word(sp+4),self.word(sp+8)]==[MAP+0x1498]*2;self.emit('U');self.counts['supplied_colors']+=1
   w,h,_,_,seed,*_=self.joined;self.supply(RGB,bytes((i*29+seed)&255 for i in range(w*h*3)));self.ret(8);return
  if 0x630a00<=a and a+n<=0x630b69 or 0x4aa4a0<=a and a+n<=0x4aa59d:return
  return super().code(u,a,n,ctx)
 def write(self,u,access,p,n,value,ctx):
  if not self.active or not BASE<=p<BASE+SIZE:return
  value&=(1<<(8*n))-1
  if FIRST<=p and p+n<=FIRST+36:
   off=p-FIRST;v={0:3,28:int(value!=0),32:2 if value else 0}.get(off,value);self.emit('O',off,n,v)
  elif DESC<=p and p+n<=DESC+108:assert n==4;self.emit('D',p-DESC,n,value)
  elif MAP<=p and p+n<=MAP+0x1500:
   off=p-MAP;assert n==4 and off in (0x1218,0x121c,0x1238,0x123c,0x1240,0x1270,0x1484,0x1498,0x149c,0x14a0,0x14a4)
   v=value
   if off in (0x1218,0x121c,0x1238,0x1270):assert value in (0,FIRST,SURFACE,RGB,BITMAP);v=int(value!=0)
   if off in (0x1498,0x149c,0x14a0,0x14a4):v=signed(value)
   self.emit('M',off,v)
  else:return super().write(u,access,p,n,value,ctx)
  self.expected[p-BASE:p-BASE+n]=value.to_bytes(n,'little')
 def run(self,f):
  self.joined=f;w,h,x,y,seed,fmt,forced,repeats=f;u=self.u;u.mem_write(BASE,b'\xa5'*SIZE)
  for p,v in ((MAP+0x1218,0),(MAP+0x121c,0),(MAP+0x1238,0),(MAP+0x123c,0),(MAP+0x1240,0),(MAP+0x1270,0),(MAP+0x1484,0),(DEVICE,DEVICE_TABLE),(DEVICE_SURFACE,DEVICE_TABLE),(DEVICE_TABLE+24,CREATE),(DEVICE_TABLE+88,DESCRIBE)):
   self.put(p,v)
  self.put(0x8523cc,DEVICE);u.mem_write(0x852fd7,bytes([forced]))
  for i,v in enumerate((11,3,0,3,5,2) if not fmt else (10,3,0,3,5,3)):self.put(0x852fb8+i*4,v)
  self.trace=[]
  for iteration in range(repeats):
   for p,v in ((MAP+0x1498,17),(MAP+0x149c,19),(MAP+0x14a0,w),(MAP+0x14a4,h),(MAP+0x11ec,x),(MAP+0x11f0,y)):self.put(p,v)
   self.expected=bytearray(u.mem_read(BASE,SIZE));self.emit('I',iteration);self.active=True
   try:self.checked_call(0x630a00,[],MAP,writes=[(MAP,0x1500),(SURFACE,32),(FIRST,36),(DESC,108),*[(p,n) for p,n,_ in SPANS]],inputs=[(0x630a00,0x169),(0x4aa4a0,0xfd),*RANGES.items(),*[(p,len(v)) for p,v in DATA.items()],(VT,136),(0x7a0be4,136),(0x852fb8,24),(0x8523cc,4),(0x852fd7,1),(DEVICE,4),(DEVICE_SURFACE,4),(DEVICE_TABLE,108)])
   finally:self.active=False
   assert bytes(u.mem_read(BASE,SIZE))==self.expected
   self.emit('R',*[signed(self.word(MAP+o)) for o in (0x1498,0x149c,0x14a0,0x14a4)],signed(self.word(SURFACE+4)),signed(self.word(SURFACE+8)),self.word(MAP+0x1484),signed(self.word(MAP+0x123c)),signed(self.word(MAP+0x1240)),self.word(FIRST+16),u.mem_read(FIRST+25,1)[0],*[digest(u.mem_read(p,n)) for p,n,_ in SPANS],digest(u.mem_read(FIRST_PIXELS,32768)))
  return self.trace
