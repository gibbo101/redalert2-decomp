# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete unchanged6324A0 alone or beneath634030; named supplied virtuals."""
import struct
from collections import Counter
from original_presentation import PresentationOracle,STACK,STOP
from verify_surface_refresh_marks import verify,RANGES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_EDX,UC_X86_REG_ESP,UC_X86_REG_EIP
ARENA=0x3900000;SIZE=0x80000;CONTEXT=ARENA;SURF=ARENA+0x2000;VT=ARENA+0x3000;HOLDER=ARENA+0x4000;ROOTS=(ARENA+0x5000,ARENA+0x7000);ENTRIES=ARENA+0x9000;MAPS=(ARENA+0xa000,ARENA+0xa100);ACTORS=ARENA+0xb000;HOUSES=ARENA+0x10000;SCHEMES=ARENA+0x60000;REGISTRIES=(ARENA+0x62000,ARENA+0x62100);PALETTES=ARENA+0x63000;DATA=ARENA+0x64000;SERVICE=ARENA+0x65000
PARENT_RECTS=(STACK-0x20,STACK-0x10)
def signed(v):return v if v<2**31 else v-2**32
class SurfaceRefreshMarksOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(ARENA,SIZE);self.active=False;self.counts=Counter();self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.write)
 def va(self,a):return a
 def word(self,p):return struct.unpack('<I',self.u.mem_read(p,4))[0]
 def emit(self,*v):self.trace.extend(map(str,v))
 def sid(self,p):assert p in (SURF,SURF+0x100);return (p-SURF)//0x100
 def aid(self,p):assert p in [ACTORS+i*0x400 for i in range(4)];return (p-ACTORS)//0x400
 def hid(self,p):
  if not p:return -1
  assert p in [HOUSES+i*0x16000 for i in range(3)];return (p-HOUSES)//0x16000
 def eid(self,p):assert ENTRIES<=p<ENTRIES+16*16 and (p-ENTRIES)%16==0;return (p-ENTRIES)//16
 def change(self,p,v):
  self.put(p,v);b=struct.pack('<I',v&0xffffffff)
  if ARENA<=p<p+4<=ARENA+SIZE:self.expected[p-ARENA:p-ARENA+4]=b
  else:assert p==0xab6efc;self.expectedRegistry=v
 def mutate(self,stage):
  f=self.f
  if self.changed or f[7]!=stage:return
  self.changed=True;m=f[8]
  if m&1:self.change(CONTEXT+0x1218,SURF+0x100)
  if m&2:self.change(HOLDER,ROOTS[1])
  if m&4:self.change(ROOTS[0]+4,ENTRIES+4*16)
  if m&8:self.change(ENTRIES,ACTORS+3*0x400);self.change(ENTRIES+4,7);self.change(ENTRIES+8,1)
  if m&16:self.change(CONTEXT+0x1270,MAPS[1]+16)
  if m&32:self.change(0xab6efc,REGISTRIES[1])
  if m&64:self.change(ACTORS+0x1b4,HOUSES+2*0x16000)
  if m&128:self.change(SCHEMES+0x30c,PALETTES+0x200);self.change(SCHEMES+0x330,2)
  if m&256:self.change(ROOTS[0]+0x10,1)
 def ret(self,value=0,args=0):
  u=self.u;sp=u.reg_read(UC_X86_REG_ESP);u.reg_write(UC_X86_REG_EAX,value&0xffffffff);u.reg_write(UC_X86_REG_ESP,sp+4+args);u.reg_write(UC_X86_REG_EIP,self.word(sp))
 def write(self,u,access,p,n,value,_):
  if not self.active or not ARENA<=p<ARENA+SIZE:return
  candidates=[i for i,b in enumerate(MAPS) if b<=p and p+n<=b+64];assert len(candidates)==1,('unexpected mark store',hex(p),n);i=candidates[0];assert n in (1,4);v=value&((1<<(8*n))-1);self.expected[p-ARENA:p-ARENA+n]=v.to_bytes(n,'little');self.emit('B',i,p-MAPS[i],n,v)
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  sp=u.reg_read(UC_X86_REG_ESP);ecx=u.reg_read(UC_X86_REG_ECX);f=self.f
  if a in self.pending:
   kind,who=self.pending.pop(a);value=signed(u.reg_read(UC_X86_REG_EAX))
   if kind!='G':self.emit(kind,who,value);self.mutate(1 if kind=='H' else (2 if self.widths==1 else 3))
  if a in (0x411290,0x4112c0,0x4112d0):
   kind={0x411290:'G',0x4112c0:'W',0x4112d0:'H'}[a];who=self.sid(ecx)
   if kind=='W':self.widths+=1
   if kind=='G':self.emit('G',who,signed(self.word(ecx+4)),signed(self.word(ecx+8)))
   self.pending[self.word(sp)]=(kind,who)
  elif a==SERVICE:
   who=self.aid(ecx);self.ccs=0;self.emit('A',who,f[4]);self.mutate(4);self.counts['supplied_C0']+=1;self.ret(f[4]);return
  elif a==SERVICE+0x10:
   who=self.aid(ecx);zero=self.word(sp+4);assert zero==0;self.ccs+=1;h=(HOUSES+0x16000 if f[5] else 0) if self.ccs%2 else HOUSES+f[6]*0x16000;self.emit('O',who,zero,self.hid(h));self.mutate(5 if self.ccs%2 else 6);self.counts['supplied_CC']+=1;self.ret(h,4);return
  elif a==SERVICE+0x20:
   who=self.sid(ecx);point=self.word(sp+4);entry=point-4;color=self.word(sp+8);self.emit('P',who,self.eid(entry),signed(self.word(point)),signed(self.word(point+4)),color);self.mutate(8);self.counts['supplied_pixel24']+=1;self.ret(255,8);return
  elif a==SERVICE+0x30:
   who=self.sid(ecx);dst,src,rect,z,one=[self.word(sp+i*4) for i in range(1,6)];assert (dst,rect)==(PARENT_RECTS[1],PARENT_RECTS[0]);self.emit('C',who,*struct.unpack('<4i',u.mem_read(dst,16)),self.sid(src),*struct.unpack('<4i',u.mem_read(rect,16)),z,one);self.mutate(9);self.counts['supplied_copy8']+=1;self.ret(255,20);return
  elif a==0x663d30:
   assert ecx==0x7ebfc4 and u.reg_read(UC_X86_REG_EDX)==1;self.emit('D',1,1);self.mutate(7);self.counts['supplied_663D30']+=1;self.ret(SCHEMES+0x400);return
  assert any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected mark instruction',hex(a))
  if a in RANGES:self.counts[hex(a)]+=1
 def run(self,f):
  self.f=f;u=self.u;u.mem_write(ARENA,b'\xa5'*SIZE);self.put(0xb263d8,0);self.put(0xab6efc,REGISTRIES[0]);self.put(CONTEXT+0x1218,SURF);self.put(CONTEXT+0x121c,SURF+0x100);self.put(CONTEXT+0x1254,HOLDER);self.put(HOLDER,ROOTS[0]);self.put(CONTEXT+0x1270,MAPS[0]+16)
  for i,(w,h) in enumerate(((f[1],f[2]),(5,2))):
   for off,v in ((0,VT),(4,w),(8,h)):self.put(SURF+i*0x100+off,v)
  for off,a in {8:SERVICE+0x30,0x24:SERVICE+0x20,0x78:0x411290,0x7c:0x4112c0,0x80:0x4112d0}.items():self.put(VT+off,a)
  for i in range(4):self.put(ACTORS+i*0x400,VT+0x100);self.put(ACTORS+i*0x400+0x1b4,HOUSES+f[13]*0x16000)
  self.put(VT+0x100+0xc0,SERVICE);self.put(VT+0x100+0xcc,SERVICE+0x10)
  for i in range(3):self.put(HOUSES+i*0x16000+0x15f40,i)
  for i in range(16):u.mem_write(ENTRIES+i*16,struct.pack('<4I',ACTORS+i%4*0x400,i%7,0,0xabc000+i))
  for i,x,y in ((0,0,0),(1,1,0),(2,0,0),(3,2,1)):self.put(ENTRIES+i*16+4,x);self.put(ENTRIES+i*16+8,y)
  if f[9]==1:self.put(ENTRIES+4,-1);self.put(ENTRIES+16+4,-8)
  if f[9]==2:self.put(ENTRIES+4,2147483647);self.put(ENTRIES+8,1)
  if f[9]==3:
   for i in range(4):self.put(ENTRIES+i*16+4,0);self.put(ENTRIES+i*16+8,0)
  if f[9]==4:self.put(ENTRIES+4,-7);self.put(ENTRIES+8,-1)
  for root in ROOTS:
   for bucket in range(256):self.put(root+bucket*24+4,ENTRIES);self.put(root+bucket*24+0x10,0)
  for root,bucket,entry,count in ((0,0,0,f[10]),(0,1,8,2),(0,255,10,1),(1,0,4,f[10]),(1,1,11,2),(1,255,13,2)):
   self.put(ROOTS[root]+bucket*24+4,ENTRIES+entry*16);self.put(ROOTS[root]+bucket*24+0x10,count)
  for i in (0,1):
   u.mem_write(MAPS[i],bytes([f[11]^(0xa5 if i else 0)])*64);self.put(PALETTES+i*0x200+4,f[3] if i==0 else 1);self.put(PALETTES+i*0x200+0x174,DATA+i*0x100);u.mem_write(DATA+i*0x100,bytes((j*17+i*41+3)&255 for j in range(32)))
  for i,(palette,index) in enumerate(((0,f[12]),(1,3),(0,5))):self.put(SCHEMES+i*0x400+0x30c,PALETTES+palette*0x200);self.put(SCHEMES+i*0x400+0x330,index)
  for i in (0,1):
   for j,k in enumerate((0,1,2) if i==0 else (2,1,0)):self.put(REGISTRIES[i]+j*4,SCHEMES+k*0x400)
  self.expected=bytearray(u.mem_read(ARENA,SIZE));self.expectedRegistry=REGISTRIES[0];self.trace=[];self.pending={};self.widths=0;self.ccs=0;self.changed=False;self.active=True
  try:self.checked_call(0x634030 if f[0] else 0x6324a0,ecx=CONTEXT,writes=[(p,64) for p in MAPS],inputs=RANGES.items())
  finally:self.active=False
  assert not self.pending and bytes(u.mem_read(ARENA,SIZE))==self.expected and self.word(0xab6efc)==self.expectedRegistry and self.word(0xb263d8)==0
  self.emit('R',self.sid(self.word(CONTEXT+0x1218)),int(self.word(CONTEXT+0x1270)==MAPS[1]+16),int(self.word(HOLDER)==ROOTS[1]),int(self.word(0xab6efc)==REGISTRIES[1]),int(self.changed))
  for p in MAPS:self.emit(*u.mem_read(p,64))
  for i in range(16):p=ENTRIES+i*16;self.emit(self.aid(self.word(p)),signed(self.word(p+4)),signed(self.word(p+8)))
  for i in range(4):self.emit(self.hid(self.word(ACTORS+i*0x400+0x1b4)))
  self.emit(signed(self.word(ROOTS[0]+0x10)),self.eid(self.word(ROOTS[0]+4)))
  for i in range(3):p=SCHEMES+i*0x400;self.emit(int(self.word(p+0x30c)==PALETTES+0x200),self.word(p+0x330))
  return self.trace
