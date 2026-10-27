# SPDX-License-Identifier: GPL-3.0-or-later
"""Unmodified complete6D8120; explicitly supplied child/effect probes."""
import struct
from original_presentation import PresentationOracle,STOP
from verify_radar_actor_placement import verify,RANGES,DATA
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EIP
BASE=0x3d00000;SIZE=0x10000;ACTOR=BASE;VT=BASE+0x1000;SURFACE=BASE+0x2000;SVT=BASE+0x2200;OUT=BASE+0x3000;CELL=BASE+0x4000;RULES=BASE+0x5000;HOUSE=BASE+0x6000;STUB=BASE+0x8000
VIRTUALS={0x48:0,0x2c:1,0x2f8:2,0x1ac:3,0x420:4,0x424:5,0x428:6}
def signed(v):return (v+2**31)%2**32-2**31
class RadarActorPlacementOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(BASE,SIZE);self.active=False;self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.write)
 def va(self,p):return p
 def word(self,p):return struct.unpack('<I',self.u.mem_read(p,4))[0]
 def ints(self,p,n):return list(struct.unpack('<'+'i'*n,self.u.mem_read(p,n*4)))
 def ret(self,argc,value=0):
  sp=self.u.reg_read(UC_X86_REG_ESP);self.u.reg_write(UC_X86_REG_EAX,value&0xffffffff);self.u.reg_write(UC_X86_REG_EIP,self.word(sp));self.u.reg_write(UC_X86_REG_ESP,sp+4+argc*4)
 def emit(self,*v):self.trace.extend(map(str,v))
 def setreg(self,n):self.u.mem_write(ACTOR+0x37b,bytes([n]))
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  sp=u.reg_read(UC_X86_REG_ESP);ecx=u.reg_read(UC_X86_REG_ECX);arg=lambda i:self.word(sp+4+i*4)
  if a==STUB:
   assert ecx==ACTOR;p=arg(0);v=self.ints(ACTOR+0x88,3);u.mem_write(p,struct.pack('<3i',*v));self.emit('A',*v);self.ret(1,p);return
  if a==STUB+16:assert ecx==ACTOR;self.emit('K',self.kind);self.ret(0,self.kind);return
  if a==STUB+32:
   assert ecx==ACTOR and self.word(arg(0))==0;self.put(arg(0),self.status);self.emit('E',self.status,self.perm)
   if self.mutation==1:u.mem_write(ACTOR+0x88,struct.pack('<3i',-65537,65535,312));self.emit('M',1)
   self.ret(1,self.perm);return
  if a==STUB+48:assert ecx==ACTOR and arg(0)==1;self.emit('C',1);self.ret(1,CELL);return
  if a in (STUB+64,STUB+80,STUB+96):
   assert ecx==ACTOR;op={STUB+64:'I',STUB+80:'R',STUB+96:'D'}[a]
   self.emit(op,*self.ints(ACTOR+0x1a0,2),u.mem_read(ACTOR+0x37b,1)[0])
   if op=='I':
    self.setreg(1)
    if self.mutation==3:self.put(ACTOR+0x1b4,HOUSE+0x100);self.emit('M',3)
    if self.mutation==6:self.put(ACTOR+0x13c,-1);self.put(ACTOR+0x144,6);self.emit('M',6)
   if op=='R' and self.mutation!=4:self.setreg(0)
   self.ret(0);return
  if a==STUB+112:
   assert ecx==SURFACE;p=arg(0);u.mem_write(p,struct.pack('<4i',0,0,16,12));self.emit('G')
   if self.mutation==2:self.setreg(0);self.emit('M',2)
   self.ret(1,p);return
  if a==0x568140:
   assert ecx==0x8324e0;self.emit('V',*self.ints(arg(0),3),self.visible);self.ret(1,self.visible);return
  if a==0x631ba0:
   assert ecx==0x8324e0;out,coords,clamp=arg(0),arg(1),arg(2);x,y=self.px,self.py
   if clamp:x=min(max(x,0),15);y=min(max(y,0),11)
   self.emit('P',clamp,*self.ints(coords,3),x,y);u.mem_write(out,struct.pack('<2i',x,y));self.ret(3,out);return
  if a==0x63b5b0:assert ecx==5;self.emit('B',arg(0));self.ret(1);return
  if a==0x55a740:assert ecx==0x8324e0 and arg(0)==CELL;self.emit('U',self.allowed);self.ret(1,self.allowed);return
  assert any(p<=a and a+n<=p+size for p,size in RANGES.items()),('Uninspected placement instruction',hex(a))
 def write(self,u,access,p,n,value,_):
  if not self.active or not BASE<=p<BASE+SIZE:return
  assert (p-ACTOR,n) in ((0x373,1),(0x1a0,4),(0x1a4,4));self.emit('W',p-ACTOR,n,value&((1<<(n*8))-1));self.stores+=1
  if p==ACTOR+0x1a0 and self.mutation==5:self.setreg(255);self.emit('M',5)
 def run(self,f):
  (self.kind,argument,discovery,loading,self.perm,self.status,self.allowed,registered,x,y,self.px,self.py,flags,secondary,owner,start,remaining,frame,divisor,self.mutation,self.visible)=f
  u=self.u;u.mem_write(BASE,b'\xa5'*SIZE)
  for off,num in VIRTUALS.items():self.put(VT+off,STUB+num*16)
  for p,v in [(ACTOR,VT),(ACTOR+0x1a0,x),(ACTOR+0x1a4,y),(ACTOR+0x1b4,HOUSE+owner*0x100),(ACTOR+0x13c,start),(ACTOR+0x144,remaining),(SURFACE,SVT),(SVT+0x78,STUB+112),(0x8336f8,SURFACE),(0xa3d298,loading),(0xa35db4,HOUSE),(0xa40d2c,frame),(0x839848,RULES),(RULES+0x90,divisor)]:self.put(p,v)
  u.mem_write(ACTOR+0x88,struct.pack('<3i',-513,1025,208));u.mem_write(ACTOR+0x373,bytes([discovery]));self.setreg(registered);u.mem_write(ACTOR+0x14,bytes([flags]));u.mem_write(ACTOR+0x574,struct.pack('<b',secondary))
  self.trace=[];self.stores=0;self.active=True
  try:self.checked_call(0x6d8120,[argument],ACTOR,writes=[(ACTOR+0x373,1),(ACTOR+0x1a0,8)],inputs=[*RANGES.items(),*DATA.items(),(VT,0x42c),(SVT,0x7c)])
  finally:self.active=False
  assert self.stores==2+int(not discovery and not loading)
  return self.trace+['F',*map(str,self.ints(ACTOR+0x1a0,2)),str(u.mem_read(ACTOR+0x37b,1)[0]),str(u.mem_read(ACTOR+0x373,1)[0]),str(int(self.word(ACTOR+0x1b4)!=HOUSE))]
