# SPDX-License-Identifier: GPL-3.0-or-later
"""Unmodified634030 and stock geometry; explicit supplied surface/effect probes."""
import struct
from collections import Counter
from original_presentation import PresentationOracle,STACK,STOP
from verify_surface_refresh import verify,RANGES
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EIP
ARENA=0x3900000;SIZE=0x10000;CONTEXT=ARENA;SURFACES=ARENA+0x2000;TABLES=ARENA+0x3000;ALT=ARENA+0x4000;SERVICE=ARENA+0x5000
RECTS=(STACK-0x20,STACK-0x10,ALT)
def signed(v):return v if v<2**31 else v-2**32
class SurfaceRefreshOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(ARENA,SIZE);self.active=False;self.counts=Counter();self.u.hook_add(UC_HOOK_CODE,self.code)
 def va(self,a):return a
 def word(self,p):return struct.unpack('<I',self.u.mem_read(p,4))[0]
 def emit(self,*v):self.trace.extend(map(str,v))
 def sid(self,p):
  assert p in [SURFACES+0x100*i for i in range(4)],('foreign surface',hex(p));return (p-SURFACES)//0x100
 def rect(self,p):
  assert p==0 or p in RECTS,('foreign rectangle',hex(p));self.emit(0 if not p else RECTS.index(p)+1)
  if p:self.emit(*struct.unpack('<4i',self.u.mem_read(p,16)))
 def change(self,p,v):
  self.put(p,v)
  if ARENA<=p<p+4<=ARENA+SIZE:self.expected[p-ARENA:p-ARENA+4]=struct.pack('<I',v&0xffffffff)
  else:assert p==0xb263d8;self.expectedMode=v&0xffffffff
 def mutate(self,stage):
  f=self.f
  if self.changed or f[6]!=stage:return
  self.changed=True
  if f[7]&1:self.change(CONTEXT+0x1218,SURFACES+0x200)
  if f[7]&2:self.change(CONTEXT+0x121c,SURFACES+0x300)
  if f[7]&4:self.change(SURFACES,TABLES+0x100)
  if f[7]&8:self.change(TABLES+8,SERVICE+0x20)
  if f[7]&16:
   for i in range(4):self.change(SURFACES+0x100*i+4,4);self.change(SURFACES+0x100*i+8,3)
  if f[7]&32:self.change(0xb263d8,0 if self.word(0xb263d8) else 1)
 def ret(self,value=0,args=0):
  u=self.u;sp=u.reg_read(UC_X86_REG_ESP);u.reg_write(UC_X86_REG_EAX,value&0xffffffff);u.reg_write(UC_X86_REG_ESP,sp+4+args);u.reg_write(UC_X86_REG_EIP,self.word(sp))
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  sp=u.reg_read(UC_X86_REG_ESP);ecx=u.reg_read(UC_X86_REG_ECX)
  if a in self.pending:
   kind,tag,who=self.pending.pop(a);result=u.reg_read(UC_X86_REG_EAX)
   if kind=='G':self.emit('O');self.rect(result);self.mutate(self.getters)
   else:self.emit(kind,tag,who,signed(result));self.mutate(3 if kind=='W' else 4)
  if a in (0x411290,0x4112c0,0x4112d0) or SERVICE+0x100<=a<=SERVICE+0x150:
   if a in (0x411290,0x4112c0,0x4112d0):
    kind={0x411290:'G',0x4112c0:'W',0x4112d0:'H'}[a];tag=(self.word(ecx)-TABLES)//0x100;actual=True
   else:
    off=a-SERVICE-0x100;tag=off//0x30;kind={0:'G',0x10:'W',0x20:'H'}[off%0x30];actual=False
   who=self.sid(ecx);self.counts[hex(a) if actual else 'supplied_'+kind]+=1
   if kind=='G':
    self.getters+=1;out=self.word(sp+4);self.emit('G',tag,who);self.rect(out)
    if not actual:
     self.put(out+8,self.word(ecx+4));self.put(out+12,self.word(ecx+8));sel=self.f[8 if self.getters==1 else 9];result=out if sel==0 else ALT if sel==1 else RECTS[1 if self.getters==1 else 0] if sel==2 else 0
     self.emit('O');self.rect(result);self.mutate(self.getters);self.ret(result,4);return
   elif not actual:
    result=self.word(ecx+(4 if kind=='W' else 8));self.emit(kind,tag,who,signed(result));self.mutate(3 if kind=='W' else 4);self.ret(result);return
   self.pending[self.word(sp)]=(kind,tag,who)
  elif a in (SERVICE,SERVICE+0x10,SERVICE+0x20):
   self.counts['supplied_copy8']+=1;self.emit('C',(a-SERVICE)//16,self.sid(ecx));self.rect(self.word(sp+4));self.emit(self.sid(self.word(sp+8)));self.rect(self.word(sp+12));self.emit(self.word(sp+16),self.word(sp+20));self.mutate(6);self.ret(255,20);return
  elif a==0x6324a0:
   assert ecx==CONTEXT;self.counts['supplied_6324A0']+=1;self.emit('F');self.ret();return
  elif a==0x632000:
   assert ecx==CONTEXT;self.counts['supplied_632000']+=1;self.emit('P');p=self.word(sp+4);self.rect(p);self.mutate(5);self.put(p,-99);self.put(p+4,-98);self.ret(args=4);return
  assert any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected refresh instruction',hex(a))
  if a==0x634030:self.counts[hex(a)]+=1
 def run(self,f):
  self.f=f;u=self.u;u.mem_write(ARENA,b'\xa5'*SIZE);self.put(0xb263d8,f[0])
  self.put(CONTEXT+0x1218,SURFACES);self.put(CONTEXT+0x121c,SURFACES+(0 if f[10] else 0x100))
  for i,(w,h) in enumerate(((f[2],f[3]),(f[4],f[5]),(3,2),(2,3))):
   for off,v in ((0,TABLES+(0 if i<2 else 0x100)),(4,w),(8,h)):self.put(SURFACES+0x100*i+off,v)
  for t in (0,1):
   for off,a in {8:SERVICE+t*16,0x78:0x411290 if f[1] else SERVICE+0x100+t*0x30,0x7c:0x4112c0 if f[1] else SERVICE+0x110+t*0x30,0x80:0x4112d0 if f[1] else SERVICE+0x120+t*0x30}.items():self.put(TABLES+t*0x100+off,a)
  for p,start in zip(RECTS,(10,20,30)):u.mem_write(p,struct.pack('<4i',*[f[11]+start+i for i in range(4)]))
  self.expected=bytearray(u.mem_read(ARENA,SIZE));self.expectedMode=f[0]&0xffffffff;self.trace=[];self.pending={};self.changed=False;self.getters=0;self.active=True
  try:self.checked_call(0x634030,ecx=CONTEXT,inputs=RANGES.items())
  finally:self.active=False
  assert not self.pending and bytes(u.mem_read(ARENA,SIZE))==self.expected and self.word(0xb263d8)==self.expectedMode
  self.emit('R',signed(self.word(0xb263d8)),self.sid(self.word(CONTEXT+0x1218)),self.sid(self.word(CONTEXT+0x121c)),int(self.changed))
  for i in range(4):
   p=SURFACES+0x100*i;self.emit(int(self.word(p)==TABLES+0x100),signed(self.word(p+4)),signed(self.word(p+8)))
  for p in RECTS:self.rect(p)
  return self.trace
