# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete original630A00 with actual4AA4A0 and stock geometry getters."""
from original_surface_startup import SurfaceStartupOracle,BASE,SIZE,OBJECT,DESC,TABLE,CREATE,DESCRIBE
from original_presentation import STOP
from verify_radar_surface_startup import verify
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP
MAP=BASE+0x6000;SECOND=BASE+0x800;OLD_FIRST=BASE+0x400;OLD_SECOND=BASE+0x500;COLORS=BASE+0x600;BITMAP=BASE+0x700;GEOMETRY_TABLE=BASE+0x3100;OLD_TABLE=BASE+0x3200;DESTROY=BASE+0x4200
class RadarSurfaceStartupOracle(SurfaceStartupOracle):
 def __init__(self,exe):
  self.parentInspection=verify(exe.read_bytes());super().__init__(exe);self.clearRoot=self.word(0x7a0be4+0x18)
 def code(self,u,a,n,ctx):
  if not self.active or a==STOP:return
  sp=u.reg_read(UC_X86_REG_ESP);ecx=u.reg_read(UC_X86_REG_ECX)
  if a==0x630a00:self.counts['parent']+=1
  if a==DESTROY:
   assert ecx in (OLD_FIRST,OLD_SECOND) and self.word(sp+4)==1;self.emit('X',2 if ecx==OLD_SECOND else 1,1);self.counts['supplied_destroy']+=1;self.ret(4);return
  if a==0x781d3b:
   p=self.word(sp+4);assert p in (COLORS,BITMAP);self.emit('F',3 if p==COLORS else 4);self.counts['supplied_release']+=1;self.ret(0);return
  if a==0x630b70:
   args=[self.word(sp+4*i) for i in range(1,5)];assert args[1:]==[MAP+0x1498,MAP+0x1498,1] and args[0]!=args[1]
   self.emit('B',*[self.word(MAP+o) for o in (0x1498,0x149c,0x14a0,0x14a4)],1);self.counts['supplied_projection']+=1
   self.record(MAP+0x121c,4,SECOND);self.ret(16,args[0]);return
  if a==0x782017 and self.word(sp+4)==36:
   self.emit('A',36);self.counts['supplied_object_allocation']+=1;self.ret(0,OBJECT);return
  if a==self.clearRoot:
   assert ecx==OBJECT and self.word(sp+4)==0;self.emit('L',0);self.counts['supplied_clear']+=1;self.ret(4,1);return
  if a==0x632700:
   assert ecx==MAP;self.emit('Z');self.counts['supplied_finish']+=1;self.ret(0);return
  if a in (0x4112c0,0x4112d0):
   assert ecx==SECOND;self.emit('W' if a==0x4112c0 else 'H',(self.word(SECOND+(4 if a==0x4112c0 else 8))+2**31)%2**32-2**31);self.counts['getter']+=1
  if 0x630a00<=a and a+n<=0x630b69 or 0x4112c0<=a and a+n<=0x4112c4 or 0x4112d0<=a and a+n<=0x4112d4:return
  return super().code(u,a,n,ctx)
 def write(self,u,access,p,n,value,ctx):
  if self.active and MAP<=p<MAP+0x1500:
   off=p-MAP;assert n==4 and off in (0x1218,0x121c,0x1238,0x1270,0x1498,0x149c,0x14a0,0x14a4)
   v=value&0xffffffff
   if off in (0x1218,0x121c):v={0:0,OBJECT:1,SECOND:5}[v]
   if off in (0x1498,0x149c,0x14a0,0x14a4):v=(v+2**31)%2**32-2**31
   self.emit('M',off,v);self.expected[p-BASE:p-BASE+4]=(value&0xffffffff).to_bytes(4,'little');return
  super().write(u,access,p,n,value,ctx)
 def run(self,f):
  w,h,x,y,sw,sh,old,forced,allocation,created,bits,caps=f;u=self.u
  # Reuse device-result leaves, without reinitializing anything during the parent.
  self.f=[sw,sh,1,forced,allocation,created,bits,caps];u.mem_write(BASE,b'\xa5'*SIZE)
  from original_surface_startup import DEVICE,SURFACE
  for p,v in ((DEVICE,TABLE),(SURFACE,TABLE),(TABLE+24,CREATE),(TABLE+88,DESCRIBE),(OLD_TABLE,DESTROY),(OLD_FIRST,OLD_TABLE),(OLD_SECOND,OLD_TABLE),(SECOND,GEOMETRY_TABLE),(SECOND+4,sw),(SECOND+8,sh),(GEOMETRY_TABLE+124,0x4112c0),(GEOMETRY_TABLE+128,0x4112d0),(MAP+0x1218,OLD_FIRST if old&1 else 0),(MAP+0x121c,OLD_SECOND if old&2 else 0),(MAP+0x1238,COLORS if old&4 else 0),(MAP+0x1270,BITMAP if old&8 else 0),(MAP+0x1498,17),(MAP+0x149c,19),(MAP+0x14a0,w),(MAP+0x14a4,h),(MAP+0x11ec,x),(MAP+0x11f0,y)):
   self.put(p,v)
  u.mem_write(OBJECT,bytes(36));self.put(0x8523cc,DEVICE);u.mem_write(0x852fd7,bytes([forced]));self.trace=[];self.expected=bytearray(u.mem_read(BASE,SIZE));self.active=True
  try:self.checked_call(0x630a00,[],MAP,writes=[(OBJECT,36),(DESC,108),(MAP,0x1500)],inputs=[(0x630a00,0x169),(0x4aa4a0,0xfd),(0x4112c0,4),(0x4112d0,4),(0x8523cc,4),(0x852fd7,1),(DEVICE,4),(SURFACE,4),(TABLE,108),(GEOMETRY_TABLE,132),(OLD_TABLE,4)])
  finally:self.active=False
  assert bytes(u.mem_read(BASE,SIZE))==self.expected
  signed=lambda v:(v+2**31)%2**32-2**31
  self.emit('R',*[signed(self.word(MAP+o)) for o in (0x1498,0x149c,0x14a0,0x14a4)],{0:0,OBJECT:1,OLD_FIRST:6}[self.word(MAP+0x1218)],{0:0,SECOND:5,OLD_SECOND:7}[self.word(MAP+0x121c)],int(self.word(MAP+0x1238)!=0),int(self.word(MAP+0x1270)!=0),signed(self.word(OBJECT+4)),signed(self.word(OBJECT+8)),self.word(OBJECT+16),u.mem_read(OBJECT+25,1)[0],int(self.word(OBJECT+28)!=0))
  return self.trace
