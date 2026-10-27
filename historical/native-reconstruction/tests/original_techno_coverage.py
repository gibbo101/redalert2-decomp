# SPDX-License-Identifier: GPL-3.0-or-later
"""Unmodified complete coverage parents around named supplied leaf services."""
import struct
from collections import Counter
from original_presentation import PresentationOracle,STOP
from verify_techno_coverage import verify,RANGES,LEAVES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EIP
ARENA=0x3000000;SIZE=0x20000;HOUSE=ARENA+0x1000;ACTOR=ARENA+0xd000;TYPE=ARENA+0xe000;VT=ARENA+0xf000;CELLS=ARENA+0x10000;SERVICE=ARENA+0x11000
VIRTUAL={0x30c:SERVICE,0x80:SERVICE+16,0x3c:SERVICE+32}
def signed(v):return v if v<2**31 else v-2**32
class TechnoCoverageOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(ARENA,SIZE);self.active=False;self.counts=Counter();self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.write)
 def va(self,a):return a
 def word(self,p):return struct.unpack('<I',self.u.mem_read(p,4))[0]
 def hp(self,i):return HOUSE+(i-1)*0x6000 if i else 0
 def hid(self,p):
  if not p:return 0
  for i in (1,2):
   if p==self.hp(i):return i
  raise AssertionError('foreign House')
 def emit(self,*args):self.trace.extend(map(str,args))
 def change(self,p,v,n=4):
  b=int(v&((1<<(8*n))-1)).to_bytes(n,'little');self.u.mem_write(p,b)
  if self.active:
   if ARENA<=p<p+n<=ARENA+SIZE:self.expected[p-ARENA:p-ARENA+n]=b
   else:assert p==0xa35db4 and n==4;self.expectedCurrent=b
 def mutate(self,leaf):
  if self.changed or self.f[20]!=leaf:return
  self.changed=True
  if leaf==1:
   for off,v,n in [(0x1fd,255,1),(0x200,1,4),(0x88,65535,4),(0x8c,-65535,4),(0x90,728,4)]:self.change(ACTOR+off,v,n)
  if leaf==2:self.change(ACTOR+0x200,7)
  if leaf==3:
   for off,v in [(0x200,2),(0x88,17),(0x8c,19),(0x90,999)]:self.change(ACTOR+off,v)
   self.change(0xa35db4,self.hp(2))
  if leaf==4:self.change(ACTOR+0x1b4,self.hp(2));self.change(0xa35db4,self.hp(2))
  if leaf==5:self.change(0xa35db4,self.hp(2))
 def ret(self,value=0,args=0):
  u=self.u;sp=u.reg_read(UC_X86_REG_ESP);u.reg_write(UC_X86_REG_EAX,value&0xffffffff);u.reg_write(UC_X86_REG_ESP,sp+4+args);u.reg_write(UC_X86_REG_EIP,self.word(sp))
 def write(self,u,access,p,n,value,_):
  if not self.active or not ARENA<=p<ARENA+SIZE:return
  if p in (ACTOR+0x1fd,ACTOR+0x200):kind='A';identity=0;off=p-ACTOR;assert n==(1 if off==0x1fd else 4)
  elif any(p==self.hp(i)+0x188 for i in (1,2)):kind='H';identity=self.hid(p-0x188);off=0x188;assert n==1
  else:
   identity=(p-CELLS)//0x200;off=(p-CELLS)%0x200;kind='C';assert 0<=identity<3 and off in (0x12c,0x130,0x134,0x13c) and n==4
  b=int(value&((1<<(8*n))-1)).to_bytes(n,'little');self.expected[p-ARENA:p-ARENA+n]=b;self.emit('W',kind,identity,off,signed(value&0xffffffff) if n==4 else value&255)
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  sp=u.reg_read(UC_X86_REG_ESP);ecx=u.reg_read(UC_X86_REG_ECX);f=self.f
  if a in VIRTUAL.values():
   assert ecx==ACTOR
   slot=next(k for k,v in VIRTUAL.items() if v==a);self.counts['supplied_'+hex(slot)]+=1
   if slot==0x30c:self.emit('E','P',f[4]);self.mutate(1);self.ret(f[4])
   if slot==0x80:self.emit('E','T',f[3]);self.mutate(2);self.ret(TYPE)
   if slot==0x3c:self.emit('E','O',f[22]);self.mutate(4);self.ret(self.hp(f[22]))
   return
  if a in LEAVES:
   self.counts['supplied_'+hex(a)]+=1
   if a==0x6a2970:
    result=f[13+min(self.heights,1)];self.heights+=1;self.emit('E','Z',signed(ecx),result);self.mutate(3);self.ret(result)
   if a==0x4f52b0:
    h=self.hid(ecx);result=f[6]^(h==2);self.emit('E','L',h,result);self.ret(result)
   if a==0x4e5540:
    self.emit('E','B',self.hid(ecx),self.hid(self.word(sp+4)),f[7]);self.ret(f[7],4)
   if a==0x548070:
    assert ecx==0x8324e0;point=struct.unpack('<2h',u.mem_read(self.word(sp+4),4));identity=self.queries%3 if f[19] else 0;self.queries+=1;self.emit('E','C',*point,identity);self.mutate(5);self.ret(CELLS+identity*0x200,4)
   if a==0x634030:assert ecx==0x8324e0;self.emit('E','F');self.ret()
   if a==0x4e09a0:assert ecx==0x8324e0;self.emit('E','D',signed(self.word(sp+4)));self.ret(args=4)
   return
  assert any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected coverage instruction',hex(a))
  if a in RANGES:self.counts[hex(a)]+=1
 def run(self,f):
  self.f=f;u=self.u;u.mem_write(ARENA,b'\xa5'*SIZE);self.put(ACTOR,VT)
  for slot,target in VIRTUAL.items():self.put(VT+slot,target)
  u.mem_write(ACTOR+0x1fd,bytes([f[1]]));self.put(ACTOR+0x200,f[2]);u.mem_write(TYPE+0xade,bytes([f[3]&255]));self.put(ACTOR+0x1b4,self.hp(f[21]))
  for off,v in zip((0x88,0x8c,0x90),f[10:13]):self.put(ACTOR+off,v)
  for i in (1,2):
   for off,v in [(0x13d,f[8]^(i==2)),(0x566a,f[9]^(i==2)),(0x188,256-i)]:u.mem_write(self.hp(i)+off,bytes([v]))
  for i in range(3):
   for off,v in zip((0x12c,0x130,0x134,0x13c),f[15:19]):self.put(CELLS+i*0x200+off,v)
  self.put(0xa35db4,self.hp(f[5]));self.expected=bytearray(u.mem_read(ARENA,SIZE));self.expectedCurrent=bytes(u.mem_read(0xa35db4,4));self.trace=[];self.changed=False;self.heights=0;self.queries=0;self.active=True
  writes=[(ACTOR+0x1fd,1),(ACTOR+0x200,4)]+[(self.hp(i)+0x188,1) for i in (1,2)]+[(CELLS+i*0x200+0x12c,20) for i in range(3)]
  try:self.checked_call(0x6c83f0 if f[0] else 0x6c86f0,[],ACTOR,writes=writes,inputs=RANGES.items())
  finally:self.active=False
  assert bytes(u.mem_read(ARENA,SIZE))==self.expected and bytes(u.mem_read(0xa35db4,4))==self.expectedCurrent
  self.emit('R',u.mem_read(ACTOR+0x1fd,1)[0],signed(self.word(ACTOR+0x200)),*[signed(self.word(ACTOR+off)) for off in (0x88,0x8c,0x90)],self.hid(self.word(0xa35db4)),self.hid(self.word(ACTOR+0x1b4)),*[u.mem_read(self.hp(i)+0x188,1)[0] for i in (1,2)],int(self.changed))
  for i in range(3):
   for off in (0x12c,0x130,0x134,0x13c):self.emit(signed(self.word(CELLS+i*0x200+off)))
  return self.trace
