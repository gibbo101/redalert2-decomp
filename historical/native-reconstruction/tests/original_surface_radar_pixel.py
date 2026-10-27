# SPDX-License-Identifier: GPL-3.0-or-later
"""Unchanged632000 parent, optional634030 caller; named children remain supplied."""
import struct
from collections import Counter
from original_presentation import PresentationOracle,STOP,STACK
from verify_surface_radar_pixel import verify,RANGES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_EDX,UC_X86_REG_ESP
ARENA=0x3900000;SIZE=0x80000;CONTEXT=ARENA;SURF=ARENA+0x3000;TABLES=[ARENA+0x4000,ARENA+0x4200];HOLDER=ARENA+0x5000;ROOTS=[ARENA+0x6000,ARENA+0x8000];ENTRIES=ARENA+0xa000;ACTORS=[ARENA+0xb000+i*0x800 for i in range(3)];TYPES=ARENA+0xe000;HOUSES=[ARENA+0x10000+i*0x16000 for i in range(3)];SCHEME=ARENA+0x60000;SERVICE=ARENA+0x65000;POINT=ARENA+0x66000;RULES=ARENA+0x67000
SHIFTS=[(11,3,0,3,5,2),(10,3,0,3,5,3),(31,31,33,-1,-32,40)]
SCALES=[1.,.5,2.,.75,-1.,2.**-149,3.]
def signed(v):return v if v<2**31 else v-2**32
class SurfaceRadarPixelOracle(PresentationOracle):
 context=CONTEXT
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(ARENA,SIZE);self.active=False;self.counts=Counter();self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.write)
 def execute_prepared(self,root,args=(),ecx=0,**kw):
  PresentationOracle.checked_call(self,root,args,ecx,**kw)
 def checked_call(self,root,args=(),ecx=0,**kw):
  self.execute_prepared(root,args,ecx,**kw)
 def va(self,a):return a
 def word(self,p):return int.from_bytes(self.u.mem_read(p,4),'little')
 def put(self,p,v):super().put(p,v)
 def emit(self,*v):self.trace.extend(map(str,v))
 def aid(self,p):return ACTORS.index(p)
 def hid(self,p):return -1 if not p else HOUSES.index(p)
 def sid(self,p):assert p in (SURF,SURF+0x100);return (p-SURF)//0x100
 def change(self,p,v):
  self.put(p,v)
  if ARENA<=p<ARENA+SIZE:self.expected[p-ARENA:p-ARENA+4]=struct.pack('<I',v&0xffffffff)
  elif p in self.globals:self.globals[p]=v&0xffffffff
  else:assert STACK-0x2000<=p<STACK
 def mutate(self,stage):
  f=self.f
  if self.changed or f[31]!=stage:return
  self.changed=True;m=f[32];point=self.pointaddr
  if m&1:self.change(point,1);self.change(point+4,1)
  if m&2:self.change(self.context+0x1218,SURF+0x100)
  if m&4:self.change(self.context+0x121c,SURF)
  if m&8:self.change(0xb263d8,0 if self.word(0xb263d8) else 1)
  if m&16:self.change(ENTRIES,ACTORS[2]);self.change(ENTRIES+4,self.word(point));self.change(ENTRIES+8,self.word(point+4))
  if m&32:self.change(0xa35db4,HOUSES[2])
  if m&64:
   for i,v in enumerate((100,100,0,0)):self.change(self.context+0x1208+i*4,v)
  if m&128:self.change(ACTORS[0]+0x13c,-1);self.change(ACTORS[0]+0x144,3)
  if m&256:
   for i,v in enumerate(SHIFTS[2]):self.change(0x852fb8+i*4,v)
  if m&512:self.change(self.context+0x1498,2147483647);self.change(self.context+0x149c,-2147483648)
  if m&1024:self.change(HOLDER,ROOTS[1])
  if m&2048:self.change(SURF,TABLES[1])
  if m&4096:self.change(ACTORS[0]+0x1b4,HOUSES[2])
  if m&8192:
   for i in range(256):self.change(ROOTS[0]+i*24+0x10,0)
  if m&16384:self.change(SCHEME+0x330,0xabc)
  if m&32768:
   assert self.mapaddr is not None
   for i,v in enumerate((111,222,333)):self.change(self.mapaddr+i*4,v)
 def ret(self,value=0,args=0):
  u=self.u;sp=u.reg_read(UC_X86_REG_ESP);u.reg_write(UC_X86_REG_EAX,value&0xffffffff);u.reg_write(UC_X86_REG_ESP,sp+4+args);u.reg_write(UC_X86_REG_EDX,0xcccccccc);u.reg_write(UC_X86_REG_ECX,0xdddddddd)
  from unicorn.x86_const import UC_X86_REG_EIP
  u.reg_write(UC_X86_REG_EIP,self.word(sp))
 def write(self,u,access,p,n,value,_):
  if not self.active or not ARENA<=p<ARENA+SIZE:return
  assert self.context+0x1208<=p<self.context+0x1218 and n==4,('Unexpected radar parent write',hex(p),n)
  v=value&0xffffffff;self.expected[p-ARENA:p-ARENA+4]=struct.pack('<I',v);self.emit('D',(p-self.context-0x1208)//4,signed(v))
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  sp=u.reg_read(UC_X86_REG_ESP);ecx=u.reg_read(UC_X86_REG_ECX);f=self.f
  if a in self.pending:
   who=self.pending.pop(a);self.emit('G',who,signed(self.word(SURF+who*0x100+4)),signed(self.word(SURF+who*0x100+8)));self.mutate(1)
  if a==0x632000:self.pointaddr=self.word(sp+4)
  if a==0x411290:self.pending[self.word(sp)]=self.sid(ecx)
  if a==0x55a280:
   assert ecx==0x8324e0;self.mapaddr=self.word(sp+4);self.emit('F',*[signed(self.word(self.mapaddr+i*4)) for i in range(3)]);self.mutate(2);self.counts['supplied_floor']+=1;self.ret(-37,4);return
  if a in (0x568140,0x568280):
   assert ecx==0x8324e0 and self.word(sp+4)==self.mapaddr;which=int(a==0x568280);v=f[10+which];self.emit('I' if which else 'H',*[signed(self.word(self.mapaddr+i*4)) for i in range(3)],v);self.mutate(4 if which else 3);self.counts['supplied_discovery'+str(which)]+=1;self.ret(v,4);return
  if a==0x4f52b0:
   h=self.hid(ecx);v=f[14]>>h&1;self.emit('L',h,v);self.mutate(5);self.counts['supplied_local']+=1;self.ret(v);return
  if a==SERVICE:
   who=self.aid(ecx);self.emit('T',who);self.mutate(6);self.counts['supplied_type80']+=1;self.ret(TYPES+who*0x400);return
  if a==0x4e5580:
   who=self.aid(self.word(sp+4));v=f[16]>>who&1;self.emit('A',self.hid(ecx),who,v);self.mutate(7);self.counts['supplied_alliedObject']+=1;self.ret(v,4);return
  if a==SERVICE+0x10:
   who=self.aid(ecx);v=255 if f[17]>>who&1 else 0;self.emit('C',who,v);self.mutate(8);self.counts['supplied_C0']+=1;self.ret(v);return
  if a==SERVICE+0x20:
   assert self.word(sp+4)==0;self.emit('O',self.aid(ecx),f[18]);self.mutate(9);self.counts['supplied_CC']+=1;self.ret(0 if f[18]<0 else HOUSES[f[18]],4);return
  if a==0x663d30:
   assert ecx==0x7ebfc4 and u.reg_read(UC_X86_REG_EDX)==1;self.emit('S');self.mutate(10);self.counts['supplied_resolver']+=1;self.ret(SCHEME);return
  if a==0x632373:self.emit('B',signed(self.word(RULES+0x90)))
  if a in (SERVICE+0x30,SERVICE+0x40,SERVICE+0x50,SERVICE+0x60):
   get=a in (SERVICE+0x30,SERVICE+0x40);table=int(a in (SERVICE+0x40,SERVICE+0x60));p=self.word(sp+4);assert p==self.pointaddr;v=f[23] if get else self.word(sp+8);self.emit('V' if get else 'W',table,self.sid(ecx),signed(self.word(p)),signed(self.word(p+4)),v);self.mutate(11 if get else 12);self.counts['supplied_get28' if get else 'supplied_set24']+=1;self.ret(v if get else 255,4 if get else 8);return
  assert any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected radar pixel path',hex(a))
  if a in RANGES:self.counts[hex(a)]+=1
 def run(self,f):
  self.f=f;u=self.u;u.mem_write(ARENA,b'\xa5'*SIZE);self.globals={0xa35db4:0 if f[1]<0 else HOUSES[f[1]],0xb263d8:f[9]&0xffffffff,0xa40d2c:f[21]&0xffffffff,0x839848:RULES}
  self.globals.update({0x852fb8+i*4:v&0xffffffff for i,v in enumerate(SHIFTS[f[24]])})
  for p,v in self.globals.items():self.put(p,v)
  for i,v in enumerate((f[4],f[5],123,456)):self.put(POINT+i*4,v)
  for i,v in enumerate(f[25:29]):self.put(self.context+0x1208+i*4,v)
  for off,v in ((0x1218,SURF),(0x121c,SURF+0x100),(0x1254,HOLDER),(0x148c,f[7]),(0x1494,f[8]),(0x1498,f[29]),(0x149c,f[30])):self.put(self.context+off,v)
  u.mem_write(self.context+0x1484,struct.pack('<f',SCALES[f[6]]));self.put(HOLDER,ROOTS[0]);self.put(SCHEME+0x330,0x1234);self.put(RULES+0x90,f[22])
  for i,(w,h) in enumerate(((f[2],f[3]),(5,2))):
   for off,v in ((0,TABLES[i]),(4,w),(8,h)):self.put(SURF+i*0x100+off,v)
   for off,v in ((0x78,0x411290),(0x7c,0x4112c0),(0x80,0x4112d0),(0x28,SERVICE+0x30+i*0x10),(0x24,SERVICE+0x50+i*0x10)):self.put(TABLES[i]+off,v)
  for i,actor in enumerate(ACTORS):
   for off,v in ((0,TABLES[0]+0x100),(0x1b4,HOUSES[i]),(0x13c,f[19]),(0x144,f[20])):self.put(actor+off,v)
   self.put(TYPES+i*0x400+0x1fc,(f[15]>>i&1)<<24)
   x,y=f[4:6]
   if f[13]==1 and i==0:x=signed((x+1)&0xffffffff)
   if f[13]==2:x=signed((x+10)&0xffffffff)
   if f[13]==3:x,y=((0,0),(1,0),(2,1))[i]
   for k,v in enumerate((actor,x,y,0xabc000+i)):self.put(ENTRIES+i*16+k*4,v)
   for k,v in enumerate((19+i*77,37+i*33,251-i*61)):u.mem_write(HOUSES[i]+0x55e9+k,bytes([v]))
  for off,v in ((0x80,SERVICE),(0xc0,SERVICE+0x10),(0xcc,SERVICE+0x20)):self.put(TABLES[0]+0x100+off,v)
  for root,entry,count in ((ROOTS[0],ENTRIES,f[12]),(ROOTS[1],ENTRIES+16,2)):
   for i in range(256):self.put(root+i*24+4,entry);self.put(root+i*24+0x10,count)
  # Match the native caller's explicitly supplied zeroed scratch. The
  # original caller writes x/y only; its other words must not inherit a
  # previous Unicorn call's private stack contents.
  if f[0]:u.mem_write(STACK-0x20,bytes(16))
  self.expected=bytearray(u.mem_read(ARENA,SIZE));self.trace=[];self.changed=False;self.pending={};self.pointaddr=POINT;self.mapaddr=None;self.active=True
  try:self.checked_call(0x634030 if f[0] else 0x632000,[] if f[0] else [POINT],self.context,writes=[(self.context+0x1208,16)],inputs=[*RANGES.items(),(0x79dd80,4),(0x79a728,8),(0x7ebfc4,10)])
  finally:self.active=False
  assert not self.pending and bytes(u.mem_read(ARENA,SIZE))==self.expected and all(self.word(p)==v for p,v in self.globals.items())
  self.emit('R',self.hid(self.word(0xa35db4)),signed(self.word(0xb263d8)),self.sid(self.word(self.context+0x1218)),self.sid(self.word(self.context+0x121c)),int(self.word(HOLDER)==ROOTS[1]),int(self.changed),int(self.word(SURF)==TABLES[1]))
  self.emit(*[signed(self.word(self.pointaddr+i*4)) for i in range(4)],*[signed(self.word(self.context+0x1208+i*4)) for i in range(4)],signed(self.word(self.context+0x1498)),signed(self.word(self.context+0x149c)),self.word(SCHEME+0x330),*[signed(self.word(0x852fb8+i*4)) for i in range(6)])
  self.emit(*[self.hid(self.word(a+0x1b4)) for a in ACTORS])
  for a in ACTORS:self.emit(signed(self.word(a+0x13c)),signed(self.word(a+0x144)))
  for i in range(3):p=ENTRIES+i*16;self.emit(self.aid(self.word(p)),signed(self.word(p+4)),signed(self.word(p+8)))
  self.emit(signed(self.word(ROOTS[0]+0x10)));return self.trace
