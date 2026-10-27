# SPDX-License-Identifier: GPL-3.0-or-later
"""Unmodified5DD000 with immutable authored image/header backing."""
from collections import Counter
from original_presentation import PresentationOracle,STACK,STOP
from verify_overlay_radar_color import verify,RANGES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX
BASE=0x4100000;SIZE=0x4000;TYPE=BASE;ANIMATION=BASE+0x400;VTABLE=BASE+0x800;FIRST=BASE+0x1000;SECOND=BASE+0x2000;OUT=BASE+0x3000
class OverlayRadarColorOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(BASE,SIZE);self.active=False;self.counts=Counter();self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.write)
 def va(self,a):return a
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  assert any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected overlay instruction',hex(a))
  if a==0x5dd000:self.counts['roots']+=1
  if a==0x5dd150:
   assert u.reg_read(UC_X86_REG_ECX)==TYPE;self.trace.append('I');self.counts['primary']+=1
   if self.mutate&1:self.put(TYPE+0x264,self.lateIndex);self.typeExpected[0x264:0x268]=(self.lateIndex&0xffffffff).to_bytes(4,'little')
   if self.mutate&2:
    v=0 if self.alternate else ANIMATION;self.put(TYPE+0x26c,v);self.typeExpected[0x26c:0x270]=v.to_bytes(4,'little')
  if a==0x5293d0:assert u.reg_read(UC_X86_REG_ECX)==ANIMATION;self.trace.extend(('A','17'));self.counts['alternate']+=1
  if a==0x432d70:self.counts['zero_constructor']+=1
 def write(self,u,access,p,n,value,_):
  if not self.active:return
  if OUT<=p and p+n<=OUT+3:self.trace.extend(map(str,('S',p-OUT,n,value&((1<<(8*n))-1))));self.counts['output_stores']+=1
 def run(self,seed,index,frame,primary,alternate,animation,frames,altFrames,mutate,lateIndex):
  self.mutate=mutate;self.lateIndex=lateIndex;self.alternate=alternate;u=self.u;u.mem_write(BASE,bytes(SIZE));self.put(TYPE,VTABLE);self.put(VTABLE+0x9c,0x5dd150);self.put(TYPE+0x264,index);self.put(TYPE+0x26c,ANIMATION if alternate else 0);self.put(TYPE+0xa4,FIRST if primary else 0);self.put(ANIMATION,VTABLE+0x100);self.put(VTABLE+0x100+0x9c,0x5293d0);self.put(ANIMATION+0xa4,SECOND if animation else 0)
  for id,(p,count) in enumerate(((FIRST,frames),(SECOND,altFrames))):
   u.mem_write(p+6,(count&65535).to_bytes(2,'little'))
   for i in range(8):u.mem_write(p+20+i*24,bytes((seed+id*71+i*23+k*19)&255 for k in range(3)))
  u.mem_write(OUT,b'\x09\x08\x07');self.typeExpected=bytearray(u.mem_read(TYPE,0x400));self.expected=bytearray(u.mem_read(BASE,SIZE));self.trace=[];self.active=True
  try:self.checked_call(0x5dd000,[OUT,frame],TYPE,writes=[(OUT,3)],inputs=[*RANGES.items(),(ANIMATION,SIZE-(ANIMATION-BASE)-0x1000)])
  finally:self.active=False
  self.expected[:0x400]=self.typeExpected;self.expected[OUT-BASE:OUT-BASE+3]=u.mem_read(OUT,3)
  assert bytes(u.mem_read(BASE,SIZE))==self.expected and u.reg_read(UC_X86_REG_EAX)==OUT
  self.trace.extend(map(str,('R',*u.mem_read(OUT,3),self.lateIndex if mutate&1 else index,17 if bool(alternate)^bool(mutate&2) else 0)));return self.trace
