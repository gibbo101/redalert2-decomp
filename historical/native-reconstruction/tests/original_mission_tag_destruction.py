# SPDX-License-Identifier: GPL-3.0-or-later
"""Deferred cleanup entering the actual ordinary-session Tag deleting destructor."""
from collections import Counter
from original_presentation import PresentationOracle,STACK
from original_foot_lit import words,ret
from verify_mission_tag_destruction import verify,RANGES,TABLES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_ECX,UC_X86_REG_EDX,UC_X86_REG_EIP,UC_X86_REG_ESP
ARENA=0x2a00000;SIZE=0x10000;TAG=ARENA+0x1000;ACTIVE2=ARENA+0x2000;ACTIVE3=ARENA+0x2100;ZERO=ARENA+0x2200
ACTIVE_VT=ARENA+0x3000;ZERO_VT=ARENA+0x3100;TYPEINFO=ARENA+0x3200;ZERO_RELEASE=ARENA+0x3210
QBUF=ARENA+0x4000;RBUFS=[ARENA+0x5000+i*0x100 for i in range(3)]
QUEUE=0xac0cd8;REGS=[0xac0cb0,0xac0d48,0xabfe48]
class MissionTagDestructionOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(ARENA,SIZE);self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.store);self.active=False;self.counts=Counter();self.stores=Counter()
 def va(self,a):return a
 def word(self,p):return words(self.u,p,1)[0]
 def identity(self,p):return {0:0,TAG:1,ACTIVE2:2,ACTIVE3:3,ZERO:4}[p]
 def subject(self,p):
  if p==QUEUE:return 40
  for i,r in enumerate(REGS):
   if p==r:return 50+i
  raise AssertionError(hex(p))
 def buffer(self,p):
  if QBUF<=p<QBUF+48:return QUEUE,(p-QBUF)//4
  for i,b in enumerate(RBUFS):
   if b<=p<b+32:return REGS[i],(p-b)//4
  return None
 def update(self,p,raw):
  for base,expected in self.expected.items():
   if base<=p and p+len(raw)<=base+len(expected):expected[p-base:p-base+len(raw)]=raw;return
  raise AssertionError(('write outside owners',hex(p),len(raw)))
 def code(self,u,a,n,_):
  if not self.active:return
  if any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()):
   if a in RANGES:self.counts[hex(a)]+=1
   if a==0x40ff90:self.trace.extend(('B','1'))
   return
  sp=u.reg_read(UC_X86_REG_ESP);receiver=u.reg_read(UC_X86_REG_ECX)
  if a==0x6ecb90:
   assert receiver==TAG and u.reg_read(UC_X86_REG_EDX)&255==1;self.trace.extend(('N','1'));self.counts['supplied_expiration']+=1;ret(u,0)
  elif a==0x783c05:
   actual=words(u,sp+4,1);assert actual==[TAG],tuple(hex(x) for x in words(u,sp,5));ret(u,0,TYPEINFO)
  elif a==0x781cd1:
   assert words(u,sp+4,1)==[TYPEINFO];self.counts['supplied_rtti']+=1;ret(u,4,0)
  elif a==0x781d3b:
   assert words(u,sp+4,1)==[TAG];self.trace.extend(('F','1'));self.counts['supplied_free']+=1;ret(u,0)
  elif a==ZERO_RELEASE:
   self.counts['supplied_release_zero']+=1;ret(u,4,0)
  else:raise AssertionError('Uninspected Tag destruction instruction '+hex(a))
 def store(self,u,access,p,n,value,_):
  if not self.active:return
  pc=u.reg_read(UC_X86_REG_EIP);raw=(value&((1<<(n*8))-1)).to_bytes(n,'little')
  owner=None;off=None;out=value&0xffffffff
  for v in [QUEUE,*REGS]:
   if p==v+16 and n==4:owner=v;off=16
  found=self.buffer(p)
  if found and n==4:owner,index=found;off=0x100+index*4;out=self.identity(value&0xffffffff)
  if owner is not None:
   self.trace.extend(('W',str(self.subject(owner)),str(off),str(out)));self.stores[hex(pc)]+=1
  elif TAG<=p<TAG+0x100:
   assert p in (TAG,TAG+4,TAG+8,TAG+12) and n==4
  else:return
  self.update(p,raw)
 def setup_vector(self,base,buffer,count,values):
  self.put(base,0x79e868);self.put(base+4,buffer);self.put(base+8,12 if base==QUEUE else 8);self.u.mem_write(base+12,bytes([1,1,0,0]));self.put(base+16,count);self.put(base+20,1)
  slots=12 if base==QUEUE else 8;self.u.mem_write(buffer,bytes(slots*4))
  for i,v in enumerate(values):self.put(buffer+i*4,{0:0,1:TAG,2:ACTIVE2,3:ACTIVE3,4:ZERO}[v])
 def run(self,f):
  u=self.u;u.mem_write(ARENA,b'\0'*SIZE);self.trace=[]
  self.put(TAG,0x7ac700);self.put(TAG+4,0x7ac6e4);self.put(TAG+8,0x7ac6dc);self.put(TAG+12,0x7ac6d4);self.put(TAG+0x24,ARENA+0x3300);self.put(TAG+0x28,{0:0,2:ACTIVE2,3:ACTIVE3}[f['first']]);self.put(TAG+0x2c,f['instances']);u.mem_write(TAG+0x34,b'\1\0')
  for obj,nextid in ((ACTIVE2,f['next2']),(ACTIVE3,f['next3'])):
   self.put(obj,ACTIVE_VT);self.put(obj+0x28,{0:0,2:ACTIVE2,3:ACTIVE3}[nextid])
  self.put(ZERO,ZERO_VT)
  for vt,predicate,release in ((ACTIVE_VT,0x410240,0x4100b0),(ZERO_VT,0x4101e0,ZERO_RELEASE)):
   self.put(vt+8,release);self.put(vt+0x20,0);self.put(vt+0x44,predicate)
  self.setup_vector(QUEUE,QBUF,f['qcount'],f['q'])
  for j,r in enumerate(REGS):self.setup_vector(r,RBUFS[j],f['rcount'][j],f['r'][j])
  u.mem_write(0xa40958,b'\0');self.expected={ARENA:bytearray(u.mem_read(ARENA,SIZE)),QUEUE:bytearray(u.mem_read(QUEUE,24)),REGS[0]:bytearray(u.mem_read(REGS[0],24)),REGS[1]:bytearray(u.mem_read(REGS[1],24)),REGS[2]:bytearray(u.mem_read(REGS[2],24))}
  self.active=True
  try:self.checked_call(0x6ecf10,[],0,writes=[(ARENA,SIZE),(QUEUE,24),*[(r,24) for r in REGS]],inputs=[*RANGES.items(),*TABLES.items(),(0xa40958,1)])
  finally:self.active=False
  for base,raw in self.expected.items():assert bytes(u.mem_read(base,len(raw)))==raw,hex(base)
  self.trace.extend(('state',str(f['instances']),str(self.word(QUEUE+16))))
  self.trace.extend(str(self.identity(x)) for x in words(u,QBUF,12))
  for j,r in enumerate(REGS):self.trace.append(str(self.word(r+16)));self.trace.extend(str(self.identity(x)) for x in words(u,RBUFS[j],8))
  return self.trace
