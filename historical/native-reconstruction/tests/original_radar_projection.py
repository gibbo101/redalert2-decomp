# SPDX-License-Identifier: GPL-3.0-or-later
"""Unmodified630B70; platform allocation/clear and631250 RGB inputs supplied."""
from collections import Counter
import struct
from original_presentation import PresentationOracle,STOP
from verify_radar_projection import verify,RANGES,DATA
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EIP
BASE=0x3b00000;SIZE=0x40000;MAP=BASE;OUT=BASE+0x2000;SOURCE=OUT+0x100;REGION=OUT+0x200;SURFACE=BASE+0x3000;RGB=BASE+0x4000;PIXELS=BASE+0x6000;BITMAP=BASE+0x10000;VT=0x79aef8
SPANS=((RGB,3072,'C'),(PIXELS,32768,'P'),(BITMAP,4096,'B'))
def signed(v):return (v+2**31)%2**32-2**31
def digest(raw):
 v=14695981039346656037
 for b in raw:v=((v^b)*1099511628211)&(2**64-1)
 return v
class RadarProjectionOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(BASE,SIZE);self.active=False;self.counts=Counter();self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.write);self.clearRoot=self.word(VT+24)
 def va(self,a):return a
 def word(self,p):return struct.unpack('<I',self.u.mem_read(p,4))[0]
 def emit(self,*v):self.trace.extend(map(str,v))
 def ret(self,args,result=0):
  sp=self.u.reg_read(UC_X86_REG_ESP);self.u.reg_write(UC_X86_REG_EAX,result);self.u.reg_write(UC_X86_REG_ESP,sp+4+args);self.u.reg_write(UC_X86_REG_EIP,self.word(sp))
 def supply(self,p,raw):
  self.u.mem_write(p,raw);self.expected[p-BASE:p-BASE+len(raw)]=raw
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  sp=u.reg_read(UC_X86_REG_ESP);ecx=u.reg_read(UC_X86_REG_ECX)
  if a==0x782017:
   size=self.word(sp+4);caller=self.word(sp);p={0x630bd2:RGB,0x630cf4:SURFACE,0x4382e2:PIXELS,0x6311ee:BITMAP}[caller]
   if p==SURFACE:assert size==32 # Object allocation is part of factory, not an emitted storage request.
   else:
    limit={RGB:3072,PIXELS:32768,BITMAP:4096}[p];assert size<=limit;self.emit('A',size)
   self.counts['supplied_allocations']+=1;self.ret(0,p);return
  if a==0x631250:
   assert ecx==MAP and [self.word(sp+4),self.word(sp+8)]==[SOURCE,REGION];self.emit('U');self.counts['supplied_colors']+=1
   w,h=self.f[:2];self.supply(RGB,bytes((i*29+self.f[10])&255 for i in range(w*h*3)));self.ret(8);return
  if a==self.clearRoot:
   assert ecx==SURFACE and self.word(sp+4)==0;self.emit('Z',0);self.counts['supplied_clear']+=1
   self.supply(PIXELS,bytes(self.word(SURFACE+4)*self.word(SURFACE+8)*2));self.ret(4,1);return
  assert any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()) or 0x4112d0<=a and a+n<=0x4112d4,('Uninspected projection instruction',hex(a))
  if a==0x630b70:self.counts['root']+=1
  if a in (0x4112c0,0x4112d0):
   assert ecx==SURFACE;self.emit('W' if a==0x4112c0 else 'H',signed(self.word(SURFACE+(4 if a==0x4112c0 else 8))));self.counts['getter']+=1
  if a==0x411370:assert ecx==SURFACE;self.emit('K',signed(self.word(sp+4)),signed(self.word(sp+8)));self.counts['lock']+=1
  if a==0x4112f0:assert ecx==SURFACE;self.emit('N');self.counts['unlock']+=1
 def write(self,u,access,p,n,value,_):
  if not self.active or not BASE<=p<BASE+SIZE:return
  value&=(1<<(8*n))-1;v=value
  if MAP<=p and p+n<=MAP+0x1500:
   off=p-MAP;assert n==4 and off in (0x1238,0x123c,0x1240,0x1484,0x121c,0x1270)
   if off in (0x1238,0x121c,0x1270):v={RGB:1,SURFACE:1,BITMAP:1}[value]
   self.emit('M',off,v)
  elif SURFACE<=p and p+n<=SURFACE+32:
   off=p-SURFACE
   if off==0:v={0x79af8c:2,VT:3}[value]
   if off==20:v={0:0,PIXELS:1}[value]
   self.emit('S',off,n,v)
  elif OUT<=p and p+n<=OUT+16 or REGION<=p and p+n<=REGION+16:assert n==4
  else:
   matches=[(lo,k) for lo,size,k in SPANS if lo<=p and p+n<=lo+size];assert len(matches)==1,(hex(p),n)
   lo,k=matches[0];self.emit(k,p-lo,n,value);self.counts[k+'_stores']+=1
  self.expected[p-BASE:p-BASE+n]=value.to_bytes(n,'little')
 def run(self,f):
  self.f=f;w,h,rx,ry,rw,rh,existing,colors,bitmap,update,seed,fmt=f;u=self.u;u.mem_write(BASE,b'\xa5'*SIZE)
  for p,v in ((MAP+0x121c,SURFACE if existing else 0),(MAP+0x1238,RGB if colors else 0),(MAP+0x123c,w),(MAP+0x1240,h),(MAP+0x1270,BITMAP if bitmap else 0),(MAP+0x1484,0x3f000000),(SURFACE,VT),(SURFACE+4,7),(SURFACE+8,5),(SURFACE+12,0),(SURFACE+16,2),(SURFACE+20,PIXELS)):
   self.put(p,v)
  if not existing:u.mem_write(SURFACE,b'\xa5'*32)
  for p,v in ((OUT,(9,8,7,6)),(SOURCE,(0,0,w,h)),(REGION,(rx,ry,rw,rh))):u.mem_write(p,struct.pack('<4i',*v))
  u.mem_write(RGB,bytes((i*29+seed)&255 for i in range(w*h*3)))
  for i,v in enumerate((11,3,0,3,5,2) if not fmt else (10,3,0,3,5,3)):self.put(0x852fb8+i*4,v)
  self.expected=bytearray(u.mem_read(BASE,SIZE));self.trace=[];self.active=True
  try:self.checked_call(0x630b70,[OUT,SOURCE,REGION,update],MAP,writes=[(MAP,0x1500),(SURFACE,32),(OUT,16),(REGION,16),*[(p,n) for p,n,_ in SPANS]],inputs=[*RANGES.items(),(0x4112d0,4),*[(p,len(v)) for p,v in DATA.items()],(VT,136),(0x852fb8,24),(SOURCE,16)])
  finally:self.active=False
  assert u.reg_read(UC_X86_REG_EAX)==OUT and bytes(u.mem_read(BASE,SIZE))==self.expected
  self.emit('R',*struct.unpack('<4i',u.mem_read(OUT,16)),*struct.unpack('<4i',u.mem_read(REGION,16)),signed(self.word(SURFACE+4)),signed(self.word(SURFACE+8)),self.word(MAP+0x1484),signed(self.word(MAP+0x123c)),signed(self.word(MAP+0x1240)),self.word(SURFACE+12),*[digest(u.mem_read(p,n)) for p,n,_ in SPANS])
  return self.trace
