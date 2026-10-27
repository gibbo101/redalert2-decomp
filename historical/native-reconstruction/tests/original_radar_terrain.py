# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete original terrain traversal and joined projection; color leaf supplied."""
from collections import Counter
import struct
from original_presentation import PresentationOracle,STOP,STACK
from original_radar_projection import BASE,SIZE,OUT,SOURCE,REGION,SURFACE,RGB,PIXELS,BITMAP,VT,SPANS,signed,digest
from verify_radar_terrain import verify,RANGES,DATA
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EIP
MAP=0x8324e0;CELLS=BASE+0x18000;SLOTS=0x3c00000
class RadarTerrainOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(BASE,SIZE);self.u.mem_map(SLOTS,0x100000);self.active=False;self.counts=Counter();self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.write)
 def va(self,a):return a
 def word(self,p):return struct.unpack('<I',self.u.mem_read(p,4))[0]
 def emit(self,*v):self.trace.extend(map(str,v))
 def ret(self,args,result=0):
  sp=self.u.reg_read(UC_X86_REG_ESP);self.u.reg_write(UC_X86_REG_EAX,result);self.u.reg_write(UC_X86_REG_ESP,sp+4+args);self.u.reg_write(UC_X86_REG_EIP,self.word(sp))
 def cursor(self):return [signed(self.word(MAP+o)) for o in (0x108,0x10c,0x110)]+[(self.word(MAP+0x114)-SLOTS)//4]
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  sp=u.reg_read(UC_X86_REG_ESP);ecx=u.reg_read(UC_X86_REG_ECX)
  if a==0x4712c0:
   assert ecx in self.ids;id=self.ids[ecx];p,q=self.word(sp+4),self.word(sp+8);assert STACK-0x1000<=p<=STACK-3 and STACK-0x1000<=q<=STACK-3 and abs(p-q)>=3
   self.emit('Q',id);self.counts['supplied_colors']+=1
   u.mem_write(p,bytes((id*37+self.seed+k*29)&255 for k in range(3)));u.mem_write(q,bytes((id*53+self.seed+101+k*17)&255 for k in range(3)));self.ret(8);return
  assert any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected terrain instruction',hex(a))
  if a==0x631250:assert ecx==MAP;self.emit('U');self.counts['terrain']+=1
  if a==0x630b70:assert ecx==MAP;self.counts['projection']+=1
  if a in (0x55a490,0x55a550):assert ecx==MAP;self.counts[hex(a)]+=1
  if a in (0x631289,0x6313e0):self.emit('V',self.ids.get(u.reg_read(UC_X86_REG_EAX),-1),*self.cursor());self.counts['visits']+=1
  if a==0x41fdf0:self.counts['intersections']+=1;assert self.word(sp+8)==self.word(sp+12)==0
  if a in (0x4112c0,0x4112d0):
   assert ecx==SURFACE;self.emit('W' if a==0x4112c0 else 'H',signed(self.word(SURFACE+(4 if a==0x4112c0 else 8))));self.counts['getter']+=1
  if a==0x411370:assert ecx==SURFACE;self.emit('K',signed(self.word(sp+4)),signed(self.word(sp+8)));self.counts['lock']+=1
  if a==0x4112f0:assert ecx==SURFACE;self.emit('N');self.counts['unlock']+=1
 def write(self,u,access,p,n,value,_):
  if not self.active:return
  value&=(1<<(8*n))-1
  if MAP<=p and p+n<=MAP+0x1600:
   assert n==4 and p-MAP in (0x108,0x10c,0x110,0x114);self.mapExpected[p-MAP:p-MAP+n]=value.to_bytes(n,'little');return
  if not BASE<=p<BASE+SIZE:return
  if p==SURFACE+12:assert n==4;self.emit('S',12,4,value)
  elif OUT<=p and p+n<=OUT+16 or REGION<=p and p+n<=REGION+16:assert n==4
  else:
   matches=[(lo,k) for lo,size,k in SPANS if lo<=p and p+n<=lo+size];assert len(matches)==1,(hex(p),n)
   lo,k=matches[0];self.emit(k,p-lo,n,value);self.counts[k+'_stores']+=1
  self.expected[p-BASE:p-BASE+n]=value.to_bytes(n,'little')
 def run(self,f):
  joined,width,origin,minimum,sw,sh,rx,ry,rw,rh,seed,hole,cells=f;u=self.u;self.seed=seed;u.mem_write(BASE,b'\xa5'*SIZE);u.mem_write(MAP,b'\xa5'*0x1600);u.mem_write(SLOTS,bytes(0x100000));self.ids={}
  for id,(slot,x,y) in enumerate(cells):
   p=CELLS+id*512;self.ids[p]=id;u.mem_write(p+0x24,struct.pack('<2h',x,y))
   if id!=hole:self.put(SLOTS+slot*4,p)
  for p,v in ((MAP+0xf0,width),(MAP+0xf8,origin),(MAP+0x138,SLOTS),(MAP+0x1494,minimum),(MAP+0x121c,SURFACE),(MAP+0x1238,RGB),(MAP+0x123c,sw),(MAP+0x1240,sh),(MAP+0x1270,BITMAP),(MAP+0x1484,0x3f000000),(SURFACE,VT),(SURFACE+4,7),(SURFACE+8,5),(SURFACE+12,0),(SURFACE+16,2),(SURFACE+20,PIXELS)):self.put(p,v)
  for p,v in ((OUT,(9,8,7,6)),(SOURCE,(0,0,sw,sh)),(REGION,(rx,ry,rw,rh))):u.mem_write(p,struct.pack('<4i',*v))
  u.mem_write(RGB,bytes((i*29+seed)&255 for i in range(sw*sh*3)))
  for i,v in enumerate((11,3,0,3,5,2)):self.put(0x852fb8+i*4,v)
  self.expected=bytearray(u.mem_read(BASE,SIZE));self.mapExpected=bytearray(u.mem_read(MAP,0x1600));self.trace=[];self.active=True
  args=[OUT,SOURCE,REGION,1] if joined else [SOURCE,REGION]
  try:self.checked_call(0x630b70 if joined else 0x631250,args,MAP,writes=[(MAP+0x108,16),(SURFACE+12,4),(OUT,16),(REGION,16),*[(p,n) for p,n,_ in SPANS]],inputs=[*RANGES.items(),*[(p,len(v)) for p,v in DATA.items()],(VT,136),(0x852fb8,24),(SOURCE,16),(SLOTS,0x100000),(CELLS,len(cells)*512)])
  finally:self.active=False
  assert bytes(u.mem_read(BASE,SIZE))==self.expected and bytes(u.mem_read(MAP,0x1600))==self.mapExpected
  if joined:assert u.reg_read(UC_X86_REG_EAX)==OUT
  self.emit('R',*struct.unpack('<4i',u.mem_read(OUT,16)),*struct.unpack('<4i',u.mem_read(REGION,16)),*self.cursor(),self.word(SURFACE+12),*[digest(u.mem_read(p,n)) for p,n,_ in SPANS]);return self.trace
