# SPDX-License-Identifier: GPL-3.0-or-later
"""Bounded unchanged-original MIX parsing/registration/lookup and CCFile decisions.
Plaintext stream/heap/OS services are supplied; CRC and list operations execute.
"""
import struct
from pathlib import Path
import pefile
from unicorn import Uc, UC_ARCH_X86, UC_MODE_32, UC_HOOK_CODE, UC_HOOK_MEM_WRITE
from unicorn.x86_const import *
from archive_profiles import archive_profile,address

ARENA=0x1100000;STACK=ARENA+0x50000;STOP=ARENA+0x60000
NODES=ARENA;INDEX=ARENA+0x10000;NAME=ARENA+0x30000
OUTPUT=ARENA+0x31000;FILE=ARENA+0x32000;VTABLE=ARENA+0x33000
HEAP=ARENA+0x40000
# Fixture entry points never replace original instruction bytes.
S_CLOSE=STOP+0x10;S_NAME=STOP+0x20;S_OPENEX=STOP+0x30
S_SETNAME=STOP+0x40;S_SEEK=STOP+0x50;S_HANDLE=STOP+0x60

class ArchiveOracle:
 def __init__(self,exe):
  data=Path(exe).read_bytes();self.digest,self.profile=archive_profile(data)
  pe=pefile.PE(data=data);assert pe.FILE_HEADER.Machine==0x14c and pe.OPTIONAL_HEADER.ImageBase==0x400000
  self.u=Uc(UC_ARCH_X86,UC_MODE_32);self.u.mem_map(0x400000,(pe.OPTIONAL_HEADER.SizeOfImage+4095)&~4095)
  for s in pe.sections:self.u.mem_write(0x400000+s.VirtualAddress,s.get_data())
  self.u.mem_map(ARENA,0x80000);self.calls=0;self.audit_writes=0;self.services={};self.events=[]
  # The actual ASCII CRT uppercase fast path has no OS/locale dependencies.
  self.u.hook_add(UC_HOOK_CODE,self.service)
  self.reset_list()
 def va(self,a):return address(self.profile,a)
 def put(self,p,x):self.u.mem_write(p,struct.pack('<I',x&0xffffffff))
 def get(self,p):return struct.unpack('<I',self.u.mem_read(p,4))[0]
 def string(self,p):
  assert p
  return bytes(self.u.mem_read(p,512)).split(b'\0')[0].decode('ascii')
 def ret(self,pop=0,value=0):
  sp=self.u.reg_read(UC_X86_REG_ESP);self.u.reg_write(UC_X86_REG_EAX,value&0xffffffff)
  self.u.reg_write(UC_X86_REG_EIP,self.get(sp));self.u.reg_write(UC_X86_REG_ESP,sp+4+pop)
 def service(self,u,p,n,context):
  if p in self.services:self.services[p]()
 def call(self,entry,args=(),ecx=0,edx=0,*,writes=(),inputs=(),cdecl=False):
  caller=STACK+4+4*len(args);guards=bytes([0xa7])*64
  self.u.mem_write(STACK,struct.pack('<'+'I'*(len(args)+1),STOP,*[x&0xffffffff for x in args]));self.u.mem_write(caller,guards)
  regs={UC_X86_REG_EBX:0x12345678,UC_X86_REG_ESI:0x23456789,UC_X86_REG_EDI:0x3456789a,UC_X86_REG_EBP:0x456789ab}
  for r,v in regs.items():self.u.reg_write(r,v)
  self.u.reg_write(UC_X86_REG_ECX,ecx);self.u.reg_write(UC_X86_REG_EDX,edx);self.u.reg_write(UC_X86_REG_ESP,STACK)
  before=[bytes(self.u.mem_read(p,n)) for p,n in inputs]
  allowed=[(STACK-0x4000,STACK),(STACK+4,caller),*[(p,p+n) for p,n in writes]]
  def audit(u,access,p,n,v,context):
   assert any(a<=p and p+n<=b for a,b in allowed),(hex(p),n)
   self.audit_writes+=1
  hook=self.u.hook_add(UC_HOOK_MEM_WRITE,audit)
  try:self.u.emu_start(self.va(entry),STOP,count=2000000)
  finally:self.u.hook_del(hook)
  assert self.u.reg_read(UC_X86_REG_EIP)==STOP,'Instruction budget'
  assert self.u.reg_read(UC_X86_REG_ESP)==(STACK+4 if cdecl else caller)
  assert bytes(self.u.mem_read(STACK,4))==struct.pack('<I',STOP)
  assert bytes(self.u.mem_read(caller,64))==guards
  assert all(self.u.reg_read(r)==v for r,v in regs.items())
  assert all(bytes(self.u.mem_read(p,n))==old for (p,n),old in zip(inputs,before))
  self.calls+=1
  return self.u.reg_read(UC_X86_REG_EAX)
 def reset_list(self):
  self.services={self.va(0x76df1a):lambda:self.ret()}
  self.call(0x591e40,writes=[(self.va(0xa588b8),28)])
  self.services={};self.nodes=[]
 def register(self,node):
  # Actual aligned constructor insertion block and actual unlink, with explicit
  # node inputs. Preserve constructor ESI/EBX live-in and stop without ABI claim.
  self.u.reg_write(UC_X86_REG_ESI,node);self.u.reg_write(UC_X86_REG_ECX,node)
  self.u.reg_write(UC_X86_REG_EBX,0);self.u.reg_write(UC_X86_REG_ESP,STACK)
  # A prior full constructor translation can cross this isolated stop. Flush
  # only translated blocks; original instruction bytes remain unchanged.
  self.u.ctl_remove_cache(self.va(0x591fa0),self.va(0x591fa0)+619)
  guards=bytes([0xa7])*64;self.u.mem_write(STACK,guards)
  events=[]
  allowed=[(node+4,node+12),(self.va(0xa588b8),self.va(0xa588b8)+28),*[(p+4,p+12) for p in self.nodes],(STACK-16,STACK)]
  def write(u,access,p,n,v,context):
   assert any(a<=p and p+n<=b for a,b in allowed),(hex(p),n)
   if not STACK-16<=p<STACK:events.append((p,n,v&0xffffffff))
  h=self.u.hook_add(UC_HOOK_MEM_WRITE,write)
  try:self.u.emu_start(self.va(0x592162),self.va(0x592183),count=100)
  finally:self.u.hook_del(h)
  assert self.u.reg_read(UC_X86_REG_EIP)==self.va(0x592183)
  assert self.u.reg_read(UC_X86_REG_ESP)==STACK and bytes(self.u.mem_read(STACK,64))==guards
  self.nodes.append(node)
  return events
 def setup(self,archives):
  self.reset_list();self.u.mem_write(NODES,bytes([0x5a])*0x2000);self.u.mem_write(INDEX,bytes([0x69])*0x10000)
  self.archive_inputs=[]
  for i,(origin,cached,entries) in enumerate(archives):
   node=NODES+i*0x40;idx=INDEX+i*0x2000
   filename=NAME+0x800+i*64
   self.u.mem_write(filename,f'archive{i}.mix'.encode()+b'\0');self.put(node+0xc,filename)
   self.put(node+4,0);self.put(node+8,0);self.put(node+0x14,len(entries));self.put(node+0x1c,origin)
   self.put(node+0x20,idx);self.put(node+0x24,cached)
   if entries:self.u.mem_write(idx,b''.join(struct.pack('<3I',*e) for e in entries))
   self.register(node)
   self.archive_inputs.extend([(node,0x40),(idx,len(entries)*12)])
 def lookup(self,name,mask=15):
  self.u.mem_write(NAME,(name or '').encode('ascii')+b'\0');self.u.mem_write(OUTPUT,struct.pack('<4I',0xa1a1a1a1,0xb2b2b2b2,0xc3c3c3c3,0xd4d4d4d4))
  destinations=[OUTPUT+i*4 if mask&(1<<i) else 0 for i in range(4)]
  events=[]
  def write(u,access,p,n,v,context):
   if OUTPUT<=p<OUTPUT+16:
    assert n==4;value=v&0xffffffff
    if p==OUTPUT+4:value=(value-NODES)//0x40 if NODES<=value<NODES+0x2000 else value
    events.extend([(p-OUTPUT)//4,value])
  h=self.u.hook_add(UC_HOOK_MEM_WRITE,write)
  try:result=self.call(0x592750,destinations[1:],NAME if name is not None else 0,destinations[0],
                        writes=[(OUTPUT,16),(NAME,len(name or '')+1)],inputs=self.archive_inputs+[(self.va(0xa588b8),28)])
  finally:self.u.hook_del(h)
  values=list(struct.unpack('<4I',self.u.mem_read(OUTPUT,16)))
  if mask&2 and result&255:values[1]=(values[1]-NODES)//0x40
  return [result&255,*values,*events]
 def hash(self,name):
  self.u.mem_write(NAME,name.upper().encode('ascii')+b'\0');self.u.mem_write(OUTPUT,bytes(16))
  return [self.call(0x493c50,[NAME,len(name)],OUTPUT,writes=[(OUTPUT,13)],inputs=[(NAME,len(name)+1)])]
 def file_decision(self,name,loose=False,handle=False,mode=1,raw_result=1,exists=False):
  self.u.mem_write(NAME,name.encode()+b'\0');self.u.mem_write(FILE,bytes([0x5a])*0x80);self.u.mem_write(VTABLE,bytes(0x40))
  self.put(FILE,VTABLE);self.put(FILE+0x60,0x1234);self.events=[]
  def event(kind,pop,value=0,*params):self.events.append([kind,*params]);self.ret(pop,value)
  self.services={S_CLOSE:lambda:event('close',0),S_NAME:lambda:event('name',0,NAME),
   S_HANDLE:lambda:event('handle',0,int(handle)),
   S_OPENEX:lambda:event('archive-open',8,1,self.string(self.get(self.u.reg_read(UC_X86_REG_ESP)+4))),
   S_SETNAME:lambda:event('restore-name',4,NAME),S_SEEK:lambda:event('seek',8,0),
   self.va(0x42f5e0):lambda:event('raw-exists',4,int(loose)),
   self.va(0x46fa10):lambda:event('raw-open',4,raw_result,mode),
   self.va(0x778d96):lambda:event('duplicate',0,NAME),
   self.va(0x76db78):lambda:event('free',0),
   self.va(0x6307b0):lambda:event('bias',8,0,self.get(self.u.reg_read(UC_X86_REG_ESP)+4),self.get(self.u.reg_read(UC_X86_REG_ESP)+8)),
   self.va(0x438140):lambda:event('memory',8,0,self.get(self.u.reg_read(UC_X86_REG_ESP)+4),self.get(self.u.reg_read(UC_X86_REG_ESP)+8))}
  for off,target in [(4,S_NAME),(8,S_SETNAME),(0x18,S_HANDLE),(0x20,S_OPENEX),(0x28,S_SEEK),(0x34,S_CLOSE)]:self.put(VTABLE+off,target)
  result=self.call(0x468dc0 if exists else 0x468e40,[mode],FILE,writes=[(FILE+0x50,1),(FILE+0x60,4),(NAME,len(name)+1)],inputs=self.archive_inputs)
  self.services={}
  return [result&255,self.events,self.get(FILE+0x60)]
 def constructor(self,blob,origin=0,available=True,allocate=True):
  self.reset_list();self.u.mem_write(NODES,bytes([0x5a])*0x40)
  self.u.mem_write(NAME,b'fixture.mix\0');self.u.mem_write(HEAP,bytes([0x69])*0x10000)
  self.events=[];position=[0];fileobj=[0]
  def constructor_file():
   sp=self.u.reg_read(UC_X86_REG_ESP);fileobj[0]=self.u.reg_read(UC_X86_REG_ECX)
   assert self.string(self.get(sp+4))=='fixture.mix'
   self.u.mem_write(fileobj[0],bytes(0x64));self.put(fileobj[0]+8,origin);self.put(fileobj[0]+0x14,NAME)
   self.ret(4,fileobj[0])
  def read_stream():
   sp=self.u.reg_read(UC_X86_REG_ESP);p,n=self.get(sp+4),self.get(sp+8)
   assert self.get(self.u.reg_read(UC_X86_REG_ECX)+0xc)==fileobj[0]
   assert position[0]+n<=len(blob)
   assert STACK-0x4000<=p and p+n<=STACK or HEAP<=p and p+n<=HEAP+0x10000
   self.u.mem_write(p,blob[position[0]:position[0]+n]);position[0]+=n
   self.events.append(['read',n]);self.ret(8,n)
  def malloc():
   n=self.get(self.u.reg_read(UC_X86_REG_ESP)+4);self.events.append(['allocate',n])
   assert n<=0x10000 or not allocate
   self.ret(0,HEAP if allocate else 0)
  def bf_init():
   p=self.u.reg_read(UC_X86_REG_ECX);self.u.mem_write(p,bytes(0x80));self.ret(8,p)
  self.services={self.va(0x46e0f0):lambda:self.ret(4,1),
   self.va(0x468b70):constructor_file,self.va(0x778d96):lambda:self.ret(0,NAME),
   self.va(0x6078c0):bf_init,self.va(0x468dc0):lambda:self.ret(4,int(available)),
   self.va(0x75ee40):read_stream,self.va(0x76d5a7):malloc,
   self.va(0x468d10):lambda:self.ret(8,position[0]),
   self.va(0x690560):lambda:self.ret(),self.va(0x75eea0):lambda:self.ret(),
   self.va(0x438290):lambda:self.ret(),self.va(0x42f250):lambda:self.ret()}
  writes=[(NODES,0x28),(self.va(0xa588b8),28)]
  # Explicit supplied file/stream writes are checked separately in services;
  # actual guest parsing/index/list writes obey the root audit.
  self.call(0x591fa0,[NAME,self.va(0x821330)],NODES,writes=writes)
  self.services={}
  fields=[self.get(NODES+off) for off in (0x14,0x18,0x1c)]
  index=self.get(NODES+0x20)
  records=[]
  if index and fields[0]<=32767:records=list(struct.unpack('<'+'I'*(fields[0]*3),self.u.mem_read(index,fields[0]*12)))
  assert bytes(self.u.mem_read(NODES+0x28,0x18))==bytes([0x5a])*0x18
  assert bytes(self.u.mem_read(HEAP+max(0,fields[0]*12 if index and fields[0]<=32767 else 0),32))==bytes([0x69])*32
  registered=self.get(self.va(0xa588c0))==NODES
  flags=list(self.u.mem_read(NODES+0x10,3))
  return [int(registered),*fields,*flags,*records],self.events
 def bootstrap(self,expansions):
  # Complete original bootstrap executes. Constructor, successful allocation,
  # file checks, cache loading, media selector and logger are explicit services.
  self.events=[];checked=[];current=[''];allocated=[HEAP]
  self.put(self.va(0x81f778),100);self.put(self.va(0x81f780),0);self.put(self.va(0x81f774),INDEX)
  def construct_file():
   sp=self.u.reg_read(UC_X86_REG_ESP);obj=self.u.reg_read(UC_X86_REG_ECX)
   current[0]=self.string(self.get(sp+4)).lower();self.put(obj,VTABLE);self.ret(4,obj)
  def check():
   checked.append(current[0]);self.ret(4,int(current[0] in {f'expand{i:02d}.mix' for i in expansions}))
  def allocate():
   assert self.get(self.u.reg_read(UC_X86_REG_ESP)+4)==0x28
   p=allocated[0];allocated[0]+=0x40;self.ret(0,p)
  def mix():
   sp=self.u.reg_read(UC_X86_REG_ESP);name=self.string(self.get(sp+4)).lower()
   self.events.append(name);self.ret(8,self.u.reg_read(UC_X86_REG_ECX))
  def format_name():
   sp=self.u.reg_read(UC_X86_REG_ESP);p,fmt,value=(self.get(sp+i) for i in (4,8,12))
   assert self.string(fmt).lower()=='expand%02d.mix';self.u.mem_write(p,(f'expand{value:02d}.mix'+'\0').encode());self.ret()
  self.put(VTABLE+0x14,S_HANDLE)
  self.services={self.va(0x46e0d0):lambda:self.ret(),self.va(0x76d684):format_name,
   self.va(0x62ff90):construct_file,S_HANDLE:check,self.va(0x62ff10):lambda:self.ret(),
   self.va(0x76d5a7):allocate,self.va(0x591fa0):mix,self.va(0x4960f0):lambda:self.ret(),
   self.va(0x592420):lambda:self.ret(0,1)}
  self.call(0x5150e0,writes=[(self.va(0x81f780),4),(self.va(0x81f7d8),4),
                           (self.va(0x81f808),8),(INDEX,400)])
  self.services={}
  assert checked==[f'expand{i:02d}.mix' for i in range(99,-1,-1)]
  return self.events
