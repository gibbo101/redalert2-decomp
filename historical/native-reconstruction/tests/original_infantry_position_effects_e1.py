# SPDX-License-Identifier: GPL-3.0-or-later
"""Unmodified complete4C7220 and6C2B40 on the bounded ordinary-E1 path."""
import struct
from collections import Counter
from original_presentation import PresentationOracle,STACK,STOP
from verify_infantry_position_effects_e1 import verify,RANGES,HELPERS
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_EIP,UC_X86_REG_ESP

ARENA=0x3b00000;SIZE=0x110000;SLOTS=ARENA+0x10000;ACTOR=ARENA+0x1000;TYPE=ARENA+0x3000;CELL=ARENA+0x5000;HOUSE=ARENA+0x7000;MAP=0x8324e0;FALLBACK=0xa6f9f8
NORMAL=(ARENA+0x8000,ARENA+0x9000);ELITE=(ARENA+0xa000,ARENA+0xb000)
def pack(*v):return struct.pack('<'+'I'*len(v),*[x&0xffffffff for x in v])
def word16(v):return ((int(v/256)+0x8000)&0xffff)-0x8000

class InfantryPositionEffectsE1Oracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True)
  self.u.mem_map(ARENA,SIZE);self.active=False;self.trace=[];self.counts=Counter();self.stores=[]
  self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.store)
 def va(self,a):return a
 def word(self,p):return struct.unpack('<I',self.u.mem_read(p,4))[0]
 def signed(self,v):return v if v<2**31 else v-2**32
 def point(self,p):return struct.unpack('<hh',self.u.mem_read(p,4))
 def ret(self,n,value=0):
  u=self.u;sp=u.reg_read(UC_X86_REG_ESP);u.reg_write(UC_X86_REG_EAX,value&0xffffffff)
  u.reg_write(UC_X86_REG_EIP,self.word(sp));u.reg_write(UC_X86_REG_ESP,sp+4+n)
 def store(self,u,access,p,n,value,_):
  if not self.active:return
  if p in (ACTOR+0x59c,ACTOR+0x59a,ACTOR+0x32d,0xa35e24):
   value&=(1<<(8*n))-1;self.stores.append((p,n,value))
   if p==0xa35e24:self.trace.extend(('G',str(value)))
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  allowed={**RANGES,**HELPERS}
  if not any(lo<=a<lo+size for lo,size in allowed.items()):
   raise AssertionError(('Uninspected Infantry position-effects instruction',hex(a),'from',hex(self.word(u.reg_read(UC_X86_REG_ESP)))))
  if a in RANGES:self.counts[hex(a)]+=1
  if a==0x508530:self.trace.extend(('Q',str(self.word(u.reg_read(UC_X86_REG_ESP)+4))))
  elif a==0x6c2990:self.trace.append('E')
  elif a==0x548070:
   q=self.point(self.word(u.reg_read(UC_X86_REG_ESP)+4));self.trace.extend(('C',*map(str,q)));self.counts['map']+=1
  elif a==0x47bb30:
   if u.reg_read(UC_X86_REG_ECX)!=self.expected_cell:raise AssertionError('Dirty Cell identity differs')
   self.trace.extend(('D','7'))
  elif a==0x506950:
   self.counts['type']+=1;ret=self.word(u.reg_read(UC_X86_REG_ESP))
   if 0x6c1380<=ret<0x6c15d0 or 0x6d8540<=ret<0x6d8595:self.counts['selector_type']+=1
  elif a==0x6d8540:self.counts['selector_weapon']+=1
  elif a==0x594770:self.trace.extend(('m',str(self.signed(self.word(ACTOR+0x98)))));self.counts['mission']+=1
  elif a==0x41b320:
   self.trace.extend(('P',str(word16(self.signed(self.word(ACTOR+0x88)))),str(word16(self.signed(self.word(ACTOR+0x8c))))))
  elif a==0x4717b0:
   if u.reg_read(UC_X86_REG_ECX)!=self.expected_cell:raise AssertionError('Resident Cell identity differs')
   self.trace.extend(('6','7'))
  elif a==0x47c2c0:
   if u.reg_read(UC_X86_REG_ECX)!=self.expected_cell:raise AssertionError('Cloak Cell identity differs')
  elif a==0x55a660:
   q=self.point(self.word(u.reg_read(UC_X86_REG_ESP)+4));high=self.word(u.reg_read(UC_X86_REG_ESP)+8)&255
   self.trace.extend(('B',*map(str,q),str(high)))
  elif a==0x4cafe0:self.counts['active']+=1
 def run(self,f):
  u=self.u;u.mem_write(ARENA,bytes(SIZE));u.mem_write(ACTOR,bytes(0x700));u.mem_write(TYPE,bytes(0xc00));u.mem_write(CELL,bytes(0x200))
  self.put(ACTOR,0x7a3540);self.put(ACTOR+0x5a8,TYPE);self.put(TYPE,0x7a3a78);self.put(TYPE+0x538,0)
  self.put(ACTOR+0x5ac,0);self.put(ACTOR+0x10c,-1);u.mem_write(ACTOR+0x118,struct.pack('<d',0.));self.put(TYPE+0x704,0)
  for i,p in enumerate(NORMAL):self.put(TYPE+0x74c+i*28,p)
  for i,p in enumerate(ELITE):self.put(TYPE+0x8f4+i*28,p)
  u.mem_write(NORMAL[1]+0x112,b'\0');u.mem_write(NORMAL[1]+0x126,b'\0');u.mem_write(ELITE[1]+0x112,b'\0');u.mem_write(ELITE[1]+0x126,b'\0')
  u.mem_write(ACTOR+0x88,pack(f['x'],f['y'],f['z']));self.put(ACTOR+0x98,2);self.put(ACTOR+0x1b8,0);self.put(ACTOR+0x228,0)
  self.put(ACTOR+0x1b4,HOUSE);self.put(HOUSE+0x30,0)
  self.put(ACTOR+0x418,-1);self.put(ACTOR+0x454,0);u.mem_write(ACTOR+0x79,bytes([0]));u.mem_write(ACTOR+0x7d,bytes([f['onMap']]))
  u.mem_write(ACTOR+0x77,b'\0');u.mem_write(ACTOR+0x32d,b'\0');u.mem_write(ACTOR+0x373,b'\0')
  u.mem_write(ACTOR+0x59a,bytes([f['state59a']]));u.mem_write(ACTOR+0x59c,bytes([f['state59c']]))
  self.put(CELL+0x140,0);u.mem_write(CELL+0x12c,b'\0');self.put(CELL+0x3c,0);self.put(CELL+0xe4,0);self.put(CELL+0x78,0);self.put(CELL+0x44,-1)
  self.put(FALLBACK+0x140,0);u.mem_write(FALLBACK+0x12c,b'\0');self.put(FALLBACK+0x3c,0);self.put(FALLBACK+0xe4,0);self.put(FALLBACK+0x78,0);self.put(FALLBACK+0x44,-1)
  shape=(56,3,19,50,44) if f['permission'] else (0,0,0,0,0)
  for off,value in zip((0xf0,0xf8,0xfc,0x100,0x104),shape):self.put(MAP+off,value)
  self.put(MAP+0x138,SLOTS);self.put(0x832618,SLOTS)
  qx,qy=word16(f['x']),word16(f['y']);index=qy*512+qx
  self.expected_cell=CELL if 0<=index<262144 else FALLBACK
  if self.expected_cell==CELL:self.put(SLOTS+index*4,CELL)
  self.put(0xa40958,1);self.put(0xa35e24,0x12345678);self.put(0xa6fa1c,0x12345678)
  self.trace=[];self.stores=[];self.active=True
  try:self.checked_call(0x4c7220,[2],ACTOR,writes=[(ACTOR+0x59a,1),(ACTOR+0x59c,1),(ACTOR+0x32d,1),(0xa35e24,4),(0xa6fa1c,4)],inputs=[(TYPE,0xc00),(CELL,0x200),(HOUSE,0x40),(FALLBACK,0x24),(FALLBACK+0x28,0x120),*((p,0x200) for p in (*NORMAL,*ELITE))])
  finally:self.active=False
  expected=[(ACTOR+0x59c,1,0),(ACTOR+0x59a,1,0),(0xa35e24,4,0)]+([(ACTOR+0x32d,1,1)] if f['onMap'] and f['permission'] else [])
  if self.stores!=expected:raise AssertionError(('Infantry position-effects stores differ',self.stores))
  if u.mem_read(ACTOR+0x59a,1)!=b'\0' or u.mem_read(ACTOR+0x59c,1)!=b'\0':raise AssertionError('Infantry position-effects state clear differs')
  self.trace.extend(('X',str(self.u.mem_read(ACTOR+0x32d,1)[0])));return self.trace
