# SPDX-License-Identifier: GPL-3.0-or-later
"""Actual idle Process interior with unmodified null Unit/Foot/Drive children."""
import struct
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from unicorn import UC_HOOK_MEM_READ,UC_HOOK_MEM_WRITE
from unicorn.x86_const import *
from original_unit_destination import UnitDestinationOracle,ARENA,SIZE,ACTOR,DRIVE,CELLS,SLOTS,FALLBACK,PLANES,INC,DEC,DISPOSE,pack
from original_presentation import STACK,STOP
from verify_ground_drive_idle_target import verify,RANGES,TABLES,EXTRA,BLOCK,CONTINUE

class GroundDriveIdleTargetOracle(UnitDestinationOracle):
 def __init__(self,exe):
  super().__init__(exe);self.inspection=verify(exe.read_bytes())
  cs=Cs(CS_ARCH_X86,CS_MODE_32)
  self.allowed={(i.address,i.size) for a,n in RANGES.items() for i in cs.disasm(bytes(self.u.mem_read(a,n)),a)}
  self.u.hook_add(UC_HOOK_MEM_READ,self.read)
 def run(self,c):
  self.c=c;self.prepared=False;self.pending=None
  return super().run(c)
 def code(self,u,a,n,context):
  if not self.active:return
  if a==STOP:u.emu_stop();return
  if a in (INC,DEC,DISPOSE):
   # Keep the parent's exact named import boundary and argument/state checks.
   super().code(u,a,n,context);return
  sp=u.reg_read(UC_X86_REG_ESP)
  if self.pending and self.pending[:2]==(a,sp):
   _,_,out=self.pending;self.pending=None
   assert u.reg_read(UC_X86_REG_EAX)==out
   self.event('C',*struct.unpack('<2h',u.mem_read(out,4)),0)
  if a==0x6fd630:
   assert u.reg_read(UC_X86_REG_ECX)==ACTOR and [self.word(sp+4),self.word(sp+8)]==[0,1]
   assert self.word(ACTOR+0x490)==self.word(ACTOR+0x494)==0
   self.event('B',0,1,self.c['effect']);self.counts['supplied.mission414']+=1
   self.ret(8,self.c['effect']);return
  assert (a,n) in self.allowed,('Uninspected idle instruction',hex(a),n)
  if any(lo<=a and a+n<=lo+size for lo,size in EXTRA.items()):
   self.instructions.add(a)
   if a in EXTRA:self.counts[hex(a)]+=1
   if a==0x41b320:
    assert u.reg_read(UC_X86_REG_ECX)==ACTOR
    self.pending=(self.word(sp),sp+8,self.word(sp+4))
   if a in (0x4a07c7,0x4a0848):self.counts['actual.destination410']+=1
   if a==0x4a07b3:self.counts['cell_match']+=1
   if a==0x4a0838:self.counts['raw5_xyz_match']+=1
   return
  super().code(u,a,n,context)
 def read(self,u,access,p,n,value,context):
  if not self.active:return
  a=u.reg_read(UC_X86_REG_EIP)
  if a in (0x4a07a3,0x4a07ad):
   axis=int(a==0x4a07ad);target=u.reg_read(UC_X86_REG_EBP)-0x24
   assert (p,n)==(target+0x24+2*axis,2)
   self.event('W',axis,self.target_id(target),struct.unpack('<h',u.mem_read(p,2))[0]);self.counts['target_word.'+str(axis)]+=1
 def store(self,u,access,p,n,v,context):
  if not self.active:return
  a=u.reg_read(UC_X86_REG_EIP)
  if a in (0x4cd9b2,0x4cd9b8):
   off=0x490 if a==0x4cd9b2 else 0x494
   assert (p,n,v)==(ACTOR+off,4,0)
   self.event('a',off,n,v);self.expected[p-ARENA:p-ARENA+n]=bytes(n);self.writes[hex(a)]+=1
  else:super().store(u,access,p,n,v,context)
 def checked_call(self,root,args,ecx,**unused):
  assert root==0x7053f0 and list(args)==[0,1] and ecx==ACTOR
  u=self.u
  if not self.prepared:
   self.put(DRIVE+0x58,self.c['track']);u.mem_write(DRIVE+0x63,bytes([self.c['driving']]))
   for i,kind in enumerate(self.c['kinds']):self.put(CELLS+0x200*i,0x79db04 if kind==11 else 0x7addf8)
   self.expected=bytearray(u.mem_read(ARENA,SIZE));self.prepared=True
  # The original Process frame is supplied, including its four saved registers.
  # Continuation stops BEFORE rotation; early paths execute their real epilogue.
  sp=STACK-32;u.mem_write(STACK-0x2000,b'\xa7'*0x2100)
  saved=(0x3456789a,0x23456789,0x456789ab,0x12345678)
  u.mem_write(sp,pack(*saved));self.put(STACK,STOP);self.put(STACK+4,DRIVE+4)
  for reg,v in ((UC_X86_REG_ESP,sp),(UC_X86_REG_ESI,DRIVE+4),(UC_X86_REG_EDI,DRIVE),
   (UC_X86_REG_EBX,0),(UC_X86_REG_EBP,0xffffffff),(UC_X86_REG_FPCW,0xe7f)):u.reg_write(reg,v)
  inputs=[*RANGES.items(),*TABLES.items(),(SLOTS,0x100000),(0x8324e0+0x138,8),(0x852998,12),
   (0x839848,4),(0x850c40,4),(0xa40d2c,4),(FALLBACK,0x148),(PLANES,800),(0x850bb8,1),(0x850ba8,8),(0x850bd0,8)]
  before=[bytes(u.mem_read(p,n)) for p,n in inputs];stack=bytes(u.mem_read(sp,0x120))
  outputs=[(STACK-0x2000,sp),(STACK+4,STACK+8),(ARENA,ARENA+SIZE),(0xa6eb14,0xa6eb18)]
  def audit(u,access,p,n,v,_):assert any(lo<=p and p+n<=hi for lo,hi in outputs),('Idle output outside declared boundary',hex(p),n)
  hook=u.hook_add(UC_HOOK_MEM_WRITE,audit)
  try:u.emu_start(BLOCK,CONTINUE,count=100000)
  finally:u.hook_del(hook)
  end=u.reg_read(UC_X86_REG_EIP);assert end in (CONTINUE,STOP) and self.pending is None
  if end==STOP:
   assert u.reg_read(UC_X86_REG_ESP)==STACK+8 and u.reg_read(UC_X86_REG_EAX)&255==0
   assert [u.reg_read(r) for r in (UC_X86_REG_EDI,UC_X86_REG_ESI,UC_X86_REG_EBP,UC_X86_REG_EBX)]==list(saved)
   self.event('flow','return-false');self.counts['return_false']+=1
  else:
   assert u.reg_read(UC_X86_REG_ESP)==sp and u.reg_read(UC_X86_REG_EDI)==DRIVE and u.reg_read(UC_X86_REG_ESI)==DRIVE+4 and u.reg_read(UC_X86_REG_EBX)==0
   self.event('flow','continue');self.counts['continue']+=1
  after=bytearray(u.mem_read(sp,0x120));after[36:40]=stack[36:40]
  assert bytes(after)==stack,'Idle frame/caller canary differs'
  assert all(bytes(u.mem_read(p,n))==old for (p,n),old in zip(inputs,before)),'Idle immutable input differs'
  assert bytes(u.mem_read(ARENA,SIZE))==bytes(self.expected),'Idle whole arena differs'
  self.audit_blocks+=1
