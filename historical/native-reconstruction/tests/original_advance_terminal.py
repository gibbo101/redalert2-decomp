# SPDX-License-Identifier: GPL-3.0-or-later
"""Unpatched terminal interior block, real child routines, supplied mission effects."""
import struct
from collections import Counter
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import *
from original_presentation import PresentationOracle,STACK,STOP
from verify_advance_terminal import verify,RANGES,TABLES,STORES,BLOCK
BASE=0x3000000;SIZE=0x10000;ACTOR=BASE+0x1000;DRIVE=BASE+0x4000
CELL=BASE+0x5000;REGISTRY=BASE+0x9000;POINT=BASE+0xa000;PLANES=0x7d27e8
def pack(*v):return struct.pack('<'+'I'*len(v),*[x&0xffffffff for x in v])
def signed(v):return (v+0x80000000)%0x100000000-0x80000000
class AdvanceTerminalOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True)
  self.u.mem_map(BASE,SIZE);self.active=False;self.counts=Counter();self.instructions=set()
  cs=Cs(CS_ARCH_X86,CS_MODE_32)
  self.allowed={(i.address,i.size) for a,n in RANGES.items() for i in cs.disasm(bytes(self.u.mem_read(a,n)),a)}
  self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.store)
 def word(self,p):return int.from_bytes(self.u.mem_read(p,4),'little')
 def coord(self,p):return struct.unpack('<3i',self.u.mem_read(p,12))
 def event(self,*v):self.events.extend(map(str,v))
 def ret(self,n,v):
  u=self.u;sp=u.reg_read(UC_X86_REG_ESP);target=self.word(sp)
  u.reg_write(UC_X86_REG_EAX,v);u.reg_write(UC_X86_REG_ESP,sp+4+n);u.reg_write(UC_X86_REG_EIP,target)
 def supplied(self,values):
  # Deliberately diagnostic late-service mutations, not recovered gameplay.
  if values[0]<0:return
  for off,v in zip((0x7d,0x76,0x7a),values):
   self.u.mem_write(ACTOR+off,bytes([v]));self.expected[0x1000+off]=v
  self.event('effect',*values)
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  sp=u.reg_read(UC_X86_REG_ESP);arg=lambda i:self.word(sp+4+4*i);ecx=u.reg_read(UC_X86_REG_ECX)
  if self.pending and self.pending[-1][:2]==(a,sp):
   _,_,kind,out=self.pending.pop();assert u.reg_read(UC_X86_REG_EAX)==out
   self.event(kind,*((*struct.unpack('<2h',u.mem_read(out,4)),0) if kind=='C' else self.coord(out)))
  if a in (0x6fe610,0x6fd630,0x4ca2b0):
   assert ecx==ACTOR
   if a==0x6fe610:
    assert arg(0)==2;self.event('N',2);self.supplied(self.c['notify_flags']);self.ret(4,0)
   elif a==0x6fd630:
    assert [arg(0),arg(1)]==[0,1];self.event('B',0,1,self.c['mission_return']);self.ret(8,self.c['mission_return'])
   else:
    self.event('P',self.c['post_return']);self.supplied(self.c['post_flags']);self.ret(0,self.c['post_return'])
   self.counts['supplied.'+hex(a)]+=1;return
  assert (a,n) in self.allowed,('Uninspected terminal instruction',hex(a))
  self.instructions.add(a)
  if a in RANGES:self.counts[hex(a)]+=1
  if a in (0x410290,0x4ca6f0,0x41b320):
   if a==0x410290:assert ecx==CELL and arg(1)==ACTOR;self.event('Q',0);kind='q';size=8
   elif a==0x4ca6f0:assert ecx==ACTOR and arg(1)==ACTOR;self.event('U');kind='u';size=8
   else:assert ecx==ACTOR;kind='C';size=4
   self.pending.append((self.word(sp),sp+4+size,kind,arg(0)))
  if a==0x594770:
   mission=signed(self.word(ACTOR+0x98));self.event('M',signed(self.word(ACTOR+0xa0)) if mission==-1 else mission)
  if a==0x4a21ed:self.counts['arrived']+=1
  if a==0x4a227a:self.counts['clears']+=1
  if a in (0x4a22b2,0x4a22d0):self.counts['true_return']+=1
 def store(self,u,access,p,n,v,_):
  if not self.active:return
  a=u.reg_read(UC_X86_REG_EIP);v&=(1<<(8*n))-1
  if BASE<=p and p+n<=BASE+SIZE:
   owner,off,width=STORES[a];assert (p,n)==((DRIVE if owner=='d' else ACTOR)+off,width),(hex(a),hex(p),n)
   self.event(owner,off,n,v);self.expected[p-BASE:p-BASE+n]=v.to_bytes(n,'little')
  elif p in (0x850bb8,0x850ba8,0x850bac,0x850bd0,0x850bd4) or PLANES<=p and p+n<=PLANES+800:
   assert 0x4706c0<=a<0x470e7b and n in (1,4,8)
 def run(self,c):
  self.c=c;u=self.u;u.mem_write(BASE,b'\xa5'*SIZE);self.events=[];self.pending=[]
  self.put(ACTOR,0x7addf8);self.put(ACTOR+0x564,DRIVE+4);self.put(DRIVE+4,0x7a04cc);self.put(DRIVE+0xc,ACTOR)
  self.put(ACTOR+0x494,CELL if c['target'] else 0);self.put(ACTOR+0x490,c['field490'])
  for off,v in zip((0x7d,0x76,0x7a),c['flags']):u.mem_write(ACTOR+off,bytes([v]))
  u.mem_write(ACTOR+0x574,bytes([c['registry']&255]));self.put(ACTOR+0x98,c['mission']);self.put(ACTOR+0xa0,c['queued'])
  u.mem_write(ACTOR+0x88,pack(*c['position']));u.mem_write(ACTOR+0x4d0,pack(*c['queue']))
  u.mem_write(DRIVE+0x34,pack(*c['destination']));u.mem_write(DRIVE+0x40,pack(*c['head']))
  self.put(DRIVE+0x4c,c['acc']);self.put(DRIVE+0x58,-1);self.put(DRIVE+0x5c,0);u.mem_write(DRIVE+0x63,bytes([c['driving']]))
  self.put(CELL,0x79db04);x,y,level,ramp=c['cell'];u.mem_write(CELL+0x24,struct.pack('<2h',x,y));u.mem_write(CELL+0x11b,bytes([level&255,ramp]))
  self.put(0x8661cc,REGISTRY)
  for i in range(128):self.put(REGISTRY+4*i,POINT)
  u.mem_write(POINT+0x28,struct.pack('<2h',*c['pool']))
  u.mem_write(0x852998,bytes(12));self.put(0x8529d0,c['divisor']);self.put(0x850c40,c['height'])
  u.mem_write(0x850bb8,b'\0');u.mem_write(0x850ba8,bytes(8));u.mem_write(0x850bd0,bytes(8));u.mem_write(PLANES,struct.pack('<100d',1.,*([0.]*99)))
  sp=STACK-0xf4;u.mem_write(STACK-0x2000,b'\xa7'*0x2100)
  saved=(0x3456789a,0x23456789,0x456789ab,0x12345678)
  u.mem_write(sp,pack(*saved));self.put(STACK,STOP);self.put(STACK+4,0);self.put(sp+0x3c,c['residual']);u.mem_write(sp+0x13,b'\0')
  for reg,v in ((UC_X86_REG_ESP,sp),(UC_X86_REG_EAX,ACTOR),(UC_X86_REG_EBP,DRIVE),(UC_X86_REG_ESI,DRIVE+0x40),(UC_X86_REG_FPCW,0xe7f)):u.reg_write(reg,v)
  inputs=[*RANGES.items(),*TABLES.items(),(0x8661cc,4),(0x852998,12),(0x8529d0,4),(0x850c40,4)]
  before=[bytes(u.mem_read(p,n)) for p,n in inputs];stack=bytes(u.mem_read(sp,0x1f4));self.expected=bytearray(u.mem_read(BASE,SIZE))
  outputs=[(sp-0x1000,sp),(sp+0x13,sp+0x14),(sp+0x24,sp+0x28),(sp+0x5c,sp+0x68),
   (BASE,BASE+SIZE),(0x850bb8,0x850bb9),(0x850ba8,0x850bb0),(0x850bd0,0x850bd8),(PLANES,PLANES+800)]
  def audit(u,access,p,n,v,_):assert any(lo<=p and p+n<=hi for lo,hi in outputs),('Terminal output outside declared boundary',hex(p),n)
  hook=u.hook_add(UC_HOOK_MEM_WRITE,audit);self.active=True
  try:u.emu_start(BLOCK,STOP,count=100000)
  finally:self.active=False;u.hook_del(hook)
  assert u.reg_read(UC_X86_REG_EIP)==STOP and u.reg_read(UC_X86_REG_ESP)==STACK+8
  assert [u.reg_read(r) for r in (UC_X86_REG_EDI,UC_X86_REG_ESI,UC_X86_REG_EBP,UC_X86_REG_EBX)]==list(saved)
  assert all(bytes(u.mem_read(p,n))==old for (p,n),old in zip(inputs,before))
  after=bytearray(u.mem_read(sp,0x1f4))
  for off,n in ((0x13,1),(0x24,4),(0x5c,12)):after[off:off+n]=stack[off:off+n]
  assert bytes(after)==stack and not self.pending and bytes(u.mem_read(BASE,SIZE))==bytes(self.expected)
  result=u.reg_read(UC_X86_REG_EAX)&255;assert result in (0,1);self.event('return',result)
  self.event('state',*self.coord(DRIVE+0x34),*self.coord(DRIVE+0x40),signed(self.word(DRIVE+0x4c)),u.mem_read(DRIVE+0x63,1)[0],signed(self.word(ACTOR+0x490)),int(self.word(ACTOR+0x494)!=0),*struct.unpack('<24i',u.mem_read(ACTOR+0x4d0,96)),*u.mem_read(ACTOR+0x76,1),*u.mem_read(ACTOR+0x7a,1),*u.mem_read(ACTOR+0x7d,1))
  self.event('floor',u.mem_read(0x850bb8,1)[0],*struct.unpack('<Q',u.mem_read(0x850ba8,8)),*struct.unpack('<Q',u.mem_read(0x850bd0,8)),*struct.unpack('<100Q',u.mem_read(PLANES,800)))
  self.audit_blocks+=1;return self.events
