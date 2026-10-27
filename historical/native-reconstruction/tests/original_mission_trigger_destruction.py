# SPDX-License-Identifier: GPL-3.0-or-later
"""Actual Trigger destruction, Tag detachment and Trigger-then-Tag cleanup."""
from collections import Counter
from original_presentation import PresentationOracle
from original_foot_lit import words,ret
from verify_mission_trigger_destruction import verify,RANGES,TABLES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_ECX,UC_X86_REG_EDX,UC_X86_REG_EIP,UC_X86_REG_ESP
ARENA=0x2b00000;SIZE=0x10000;TRIGGER=ARENA+0x1000;TAG=ARENA+0x2000;TYPE=ARENA+0x3000;TYPEINFO=ARENA+0x3100
QBUF=ARENA+0x4000;RBUFS=[ARENA+0x5000+i*0x100 for i in range(4)];QUEUE=0xac0cd8;REGS=[0xa40aa0,0xac0cb0,0xac0d48,0xabfe48]
class MissionTriggerDestructionOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(ARENA,SIZE);self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.store);self.active=False;self.counts=Counter();self.stores=Counter()
 def va(self,a):return a
 def word(self,p):return words(self.u,p,1)[0]
 def identity(self,p):return {0:0,TRIGGER:1,TAG:2}[p]
 def subject(self,p):
  if p==TAG:return 2
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
 def manual(self,p,n,value,subject,offset,pointer=False):
  raw=(value&((1<<(8*n))-1)).to_bytes(n,'little');self.u.mem_write(p,raw);self.update(p,raw);out=self.identity(value) if pointer else value&((1<<(n*8))-1);self.trace.extend(('W',str(subject),str(offset),str(out)))
 def apply_expiration(self):
  if self.word(TAG+0x24)==TRIGGER:self.manual(TAG+0x24,4,0,2,0x24,True)
  if self.word(TAG+0x28)==TRIGGER:self.manual(TAG+0x28,4,self.word(TRIGGER+0x28),2,0x28,True)
  if not self.word(TAG+0x24):
   self.manual(TAG+0x34,1,1,2,0x34)
   count=self.word(QUEUE+16);self.manual(QUEUE+16,4,(count+1)&0xffffffff,40,0x10);self.manual(QBUF+count*4,4,TAG,40,0x100+count*4,True)
 def code(self,u,a,n,_):
  if not self.active:return
  if any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()):
   if a in RANGES:self.counts[hex(a)]+=1
   if a==0x40ff90:
    who=self.identity(u.reg_read(UC_X86_REG_ECX));self.trace.extend(('B',str(who)));self.base[who]+=1
   return
  sp=u.reg_read(UC_X86_REG_ESP);receiver=u.reg_read(UC_X86_REG_ECX)
  if a==0x6ecb90:
   who=self.identity(receiver);assert u.reg_read(UC_X86_REG_EDX)&255==1;self.trace.extend(('N',str(who)));self.counts['supplied_expiration']+=1
   if receiver==TRIGGER:self.apply_expiration()
   ret(u,0)
  elif a==0x783c05:
   assert words(u,sp+4,1)[0] in (TRIGGER,TAG);ret(u,0,TYPEINFO)
  elif a==0x781cd1:
   assert words(u,sp+4,1)==[TYPEINFO];self.counts['supplied_rtti']+=1;ret(u,4,0)
  elif a==0x781d3b:
   who=self.identity(words(u,sp+4,1)[0]);self.trace.extend(('F',str(who)));self.freed[who]+=1;ret(u,0)
  else:raise AssertionError('Uninspected Trigger destruction instruction '+hex(a))
 def store(self,u,access,p,n,value,_):
  if not self.active:return
  pc=u.reg_read(UC_X86_REG_EIP);owner=None;off=None;out=value&((1<<(n*8))-1);pointer=False
  for v in [QUEUE,*REGS]:
   if p==v+16 and n==4:owner=v;off=16
  found=self.buffer(p)
  if found and n==4:owner,index=found;off=0x100+index*4;pointer=True
  if TAG+0x24<=p<=TAG+0x34:
   mapping={TAG+0x24:0x24,TAG+0x28:0x28,TAG+0x34:0x34}
   if p in mapping:owner=TAG;off=mapping[p];pointer=p!=TAG+0x34
  if owner is not None:
   if pointer:out=self.identity(value&0xffffffff)
   self.trace.extend(('W',str(self.subject(owner)),str(off),str(out)));self.stores[hex(pc)]+=1;self.update(p,(value&((1<<(n*8))-1)).to_bytes(n,'little'))
  elif (TRIGGER<=p<TRIGGER+16 or TAG<=p<TAG+16) and n==4:self.update(p,(value&0xffffffff).to_bytes(4,'little'))
 def setup_vector(self,base,buffer,count,values,capacity):
  self.put(base,0x79e868);self.put(base+4,buffer);self.put(base+8,capacity);self.u.mem_write(base+12,bytes([1,1,0,0]));self.put(base+16,count);self.put(base+20,1);self.u.mem_write(buffer,bytes(capacity*4))
  for i,v in enumerate(values):self.put(buffer+i*4,{0:0,1:TRIGGER,2:TAG}[v])
 def run(self,f):
  u=self.u;u.mem_write(ARENA,b'\0'*SIZE);self.trace=[];self.base=Counter();self.freed=Counter()
  self.put(TRIGGER,0x7ad9e0);self.put(TRIGGER+4,0x7ad9c4);self.put(TRIGGER+8,0x7ad9bc);self.put(TRIGGER+12,0x7ad9b4);self.put(TRIGGER+0x28,0)
  self.put(TAG,0x7ac700);self.put(TAG+4,0x7ac6e4);self.put(TAG+8,0x7ac6dc);self.put(TAG+12,0x7ac6d4);self.put(TAG+0x24,0 if f['typeMode']==0 else TRIGGER if f['typeMode']==2 else TYPE);self.put(TAG+0x28,TRIGGER if f['firstPresent'] else 0);u.mem_write(TAG+0x34,bytes([f['destroyed'],0]));self.put(TAG+0x2c,0)
  self.setup_vector(QUEUE,QBUF,f['qcount'],f['q'],12)
  for j,r in enumerate(REGS):self.setup_vector(r,RBUFS[j],f['rcount'][j],f['r'][j],8)
  u.mem_write(0xa40958,b'\0');self.expected={ARENA:bytearray(u.mem_read(ARENA,SIZE)),QUEUE:bytearray(u.mem_read(QUEUE,24)),**{r:bytearray(u.mem_read(r,24)) for r in REGS}}
  self.active=True
  try:
   if f['op']=='P':root,args,receiver=0x6b4040,[TRIGGER,f['removed']],TAG
   elif f['op']=='D':root,args,receiver=0x6edba0,[f['deleting']],TRIGGER
   else:root,args,receiver=0x6ecf10,[],0
   self.checked_call(root,args,receiver,writes=[(ARENA,SIZE),(QUEUE,24),*[(r,24) for r in REGS]],inputs=[*RANGES.items(),*TABLES.items(),(0xa40958,1)])
  finally:self.active=False
  for base,raw in self.expected.items():assert bytes(u.mem_read(base,len(raw)))==raw,hex(base)
  self.trace.extend(('state',str(f['typeMode']),str(int(bool(self.word(TAG+0x24)))),str(int(bool(self.word(TAG+0x28)))),str(u.mem_read(TAG+0x34,1)[0]),str(self.word(QUEUE+16))))
  self.trace.extend(str(self.identity(x)) for x in words(u,QBUF,12))
  for j,r in enumerate(REGS):self.trace.append(str(self.word(r+16)));self.trace.extend(str(self.identity(x)) for x in words(u,RBUFS[j],8))
  self.trace.extend((str(self.base[1]),str(self.freed[1]),str(self.base[2]),str(self.freed[2])))
  return self.trace
