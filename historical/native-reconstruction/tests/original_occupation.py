# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact-base Terrain occupation, Object/Terrain Mark and normal cell membership.
Map lookup, no attached animation, redraw, cell height and visibility are fixtures.
Original marking, list traversal/writes and foundation dispatch execute unchanged.
"""
import struct
import pefile
from terrain_lifecycle_profiles import address
from original_presentation import PresentationOracle,STACK,STOP
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import *

ACTORS=0x1e00000;TYPES=0x1e06000;SCENARIO=0x1e10000;CELL=0x1e14000
COORD=0x1e15000;TABLE=0x1f00000
class OccupationOracle(PresentationOracle):
 def __init__(self,exe,*,allow_patched=False):
  super().__init__(exe,allow_patched=allow_patched);self.u.mem_map(ACTORS,0x220000)
  self.image_end=0x400000+pefile.PE(str(exe)).OPTIONAL_HEADER.SizeOfImage
  self.audit_image_writes=0
  # Actual startup foundation initializer, coordinate constructors and vector
  # constructors. No replacement table; stock 1x1 occupies the origin only.
  self.call(self.va(0x6d9ed0),budget=200000)
  assert bytes(self.u.mem_read(self.va(0xaa7f18),8))==struct.pack('<4h',0,0,32767,32767)
  # Original Foundation name/enum metadata used by 0x469E80. The actual type
  # loader uses 40-byte foundation stride; 1x1 selects the first initialized row.
  name,index=struct.unpack('<2I',self.u.mem_read(self.va(0x7bc950),8))
  assert bytes(self.u.mem_read(name,4))==b'1x1\0' and index==0
  self.put(self.va(0xa255a0),SCENARIO);self.put(self.va(0x81a800)+0x138,TABLE)
  self.u.mem_write(self.va(0xa255a8),bytes(4))
  self.put(self.va(0xa5aa88),104) # supplied positive height threshold; actors are ground-relative zero
 def va(self,disc_va):return address(self.profile,disc_va)
 def ret(self,pop,value=0):
  sp=self.u.reg_read(UC_X86_REG_ESP)
  self.u.reg_write(UC_X86_REG_EAX,value)
  self.u.reg_write(UC_X86_REG_EIP,struct.unpack('<I',self.u.mem_read(sp,4))[0])
  self.u.reg_write(UC_X86_REG_ESP,sp+4+pop)
 def checked_call(self,address,args,actor):
  # Audit caller-owned stack above arguments and all callee-saved registers.
  guards=bytes([0xa7])*64;self.u.mem_write(STACK+4+4*len(args),guards)
  regs=[UC_X86_REG_EBX,UC_X86_REG_ESI,UC_X86_REG_EDI,UC_X86_REG_EBP]
  values=[0x12345678,0x89abcdef,0x76543210,0xfedcba98]
  for reg,value in zip(regs,values):self.u.reg_write(reg,value)
  # Original image writes are limited to lazy foundation initialization and
  # selected layer fields, whose ordered address/size audit lives in hooks().
  allowed=[(self.va(0xa5aa60),4),(self.va(0xa5aa64),1)]
  if hasattr(self,'layers'):allowed.append((self.layers,120))
  def image_write(u,access,p,n,value,ctx):
   if 0x400000<=p<self.image_end:
    assert any(lo<=p and p+n<=lo+length for lo,length in allowed),(hex(p),n)
    self.audit_image_writes+=1
  hook=self.u.hook_add(UC_HOOK_MEM_WRITE,image_write)
  try:self.call(address,args,actor,budget=100000)
  finally:self.u.hook_del(hook)
  assert self.u.reg_read(UC_X86_REG_ESP)==STACK+4+4*len(args)
  assert bytes(self.u.mem_read(STACK,4))==struct.pack('<I',STOP)
  assert bytes(self.u.mem_read(STACK+4+4*len(args),64))==guards
  assert [self.u.reg_read(reg) for reg in regs]==values
  self.audit_calls+=1
 def occupation(self,x,y,z,theater,temperate,snow,flags,mark):
  self.u.mem_write(ACTORS,bytes([0x5a])*0x300);self.put(ACTORS+0xb0,TYPES)
  self.u.mem_write(TYPES,bytes([0x69])*0x300);self.put(TYPES+0x278,temperate);self.put(TYPES+0x27c,snow)
  self.u.mem_write(SCENARIO,bytes([0x7d])*0x900);self.put(SCENARIO+0x838,theater)
  self.u.mem_write(CELL,bytes([0x3c])*0x200);self.put(CELL+0x124,flags)
  self.u.mem_write(COORD,struct.pack('<3i',x,y,z));events=[];point=[]
  regions=[(ACTORS,0x300),(TYPES,0x300),(SCENARIO,0x900),(CELL,0x200),(COORD,12)]
  before=[bytes(self.u.mem_read(p,n)) for p,n in regions]
  def service(u,a,n,ctx):
   if a!=self.va(0x5453b0):return
   assert u.reg_read(UC_X86_REG_ECX)==self.va(0x81a800)
   sp=u.reg_read(UC_X86_REG_ESP);p=struct.unpack('<I',u.mem_read(sp+4,4))[0]
   point.extend(struct.unpack('<2h',u.mem_read(p,4)));events.extend(['L',*point]);self.ret(4,CELL)
  def write(u,access,a,size,value,ctx):
   if any(p<=a<p+n for p,n in regions):
    assert (a,size)==(CELL+0x124,1),(hex(a),size)
    events.extend(['W',0,value&255])
  hooks=[self.u.hook_add(UC_HOOK_CODE,service),self.u.hook_add(UC_HOOK_MEM_WRITE,write)]
  try:self.checked_call(self.va(0x6d8a60) if mark else self.va(0x6d89c0),[COORD],ACTORS)
  finally:
   for h in hooks:self.u.hook_del(h)
  for (p,n),old in zip(regions,before):
   new=bytes(self.u.mem_read(p,n))
   if p==CELL:assert new[:0x124]==old[:0x124] and new[0x125:]==old[0x125:]
   else:assert new==old,hex(p)
  assert len(point)==2
  return [*point,struct.unpack('<I',self.u.mem_read(CELL+0x124,4))[0],*events]
 def state(self,op,theater,cx,cy,flags,head,alt,items,target,mode,alternate):
  assert 0<=cx<512 and 0<=cy<512 and 0<=target<len(items)
  self.u.mem_write(ACTORS,bytes([0x5a])*0x6000);self.u.mem_write(TYPES,bytes([0x69])*0x6000)
  self.u.mem_write(SCENARIO,bytes([0x7d])*0x900);self.put(SCENARIO+0x838,theater)
  self.u.mem_write(CELL,bytes([0x3c])*0x200);self.put(CELL+0x24,(cy<<16)|cx)
  self.put(CELL+0x124,flags);self.put(CELL+0xe4,self.ptr(head));self.put(CELL+0xe8,self.ptr(alt))
  self.u.mem_write(TABLE,bytes(0x100000));self.put(TABLE+(cy*512+cx)*4,CELL)
  for id,(x,y,z,temperate,snow,nxt,onMap,redraw,limbo) in enumerate(items):
   p=self.ptr(id);t=TYPES+id*0x300
   self.put(p,self.va(0x79827c));self.put(p+0xb0,t);self.put(p+0x30,self.ptr(nxt))
   self.u.mem_write(p+0x88,struct.pack('<3i',x,y,z));self.u.mem_write(p+0x74,bytes([onMap,redraw,limbo]))
   self.u.mem_write(p+0x79,b'\0') # ordinary ground layer, no bridge
   self.put(t,self.va(0x798490));self.put(t+0x278,temperate);self.put(t+0x27c,snow);self.put(t+0x288,self.va(0xaa7f18))
   self.u.mem_write(t+0x205,b'\1')
  events=[];actor=self.ptr(target)
  regions=[(ACTORS,0x6000),(TYPES,0x6000),(SCENARIO,0x900),(CELL,0x200),(TABLE,0x100000)]
  before=[bytes(self.u.mem_read(p,n)) for p,n in regions]
  def service(u,a,n,ctx):
   sp=u.reg_read(UC_X86_REG_ESP)
   if a==self.va(0x40dc20):
    assert u.reg_read(UC_X86_REG_ECX)==actor;self.ret(0,0) # no attached animation
   elif a==self.va(0x76df1a):self.ret(0,0) # successful CRT atexit registration, cdecl
   elif a==self.va(0x4dfee0):
    assert u.reg_read(UC_X86_REG_ECX)==self.va(0x81a800)
    assert struct.unpack('<I',u.mem_read(sp+4,4))[0]==0
    events.extend(['R',target,0]);self.ret(4)
   elif a==self.va(0x41b320):
    events.extend(['C',target,0]) # execute actual word-coordinate getter
   elif a==self.va(0x4702c0):
    assert u.reg_read(UC_X86_REG_ECX)==CELL,hex(u.reg_read(UC_X86_REG_ECX));self.ret(4,0) # flat cell-height service
   elif a==self.va(0x556f20):
    assert u.reg_read(UC_X86_REG_ECX)==self.va(0x81a800)
    self.ret(4,items[target][2]) # supplied world ground height, zero relative height
   elif a==self.va(0x564de0):
    assert u.reg_read(UC_X86_REG_ECX)==self.va(0x81a800)
    p=struct.unpack('<I',u.mem_read(sp+4,4))[0]
    assert struct.unpack('<3i',u.mem_read(p,12))==(cx*256+128,cy*256+128,0)
    events.extend(['V',target,0]);self.ret(4,1) # visible, no visibility side effects
   elif a==self.va(0x472140):
    assert u.reg_read(UC_X86_REG_ECX)==CELL
    assert struct.unpack('<I',u.mem_read(sp+4,4))[0]==0xffffffff
    events.extend(['D',cx,cy]);self.ret(4)
   elif a==self.va(0x5453b0):
    assert u.reg_read(UC_X86_REG_ECX)==self.va(0x81a800)
    p=struct.unpack('<I',u.mem_read(sp+4,4))[0];x,y=struct.unpack('<2h',u.mem_read(p,4))
    assert (x,y)==(cx,cy) # state fixtures use an existing in-bounds cell
    events.extend(['L',x,y]);self.ret(4,CELL)
  def write(u,access,a,size,value,ctx):
   if ACTORS<=a<ACTORS+0x6000:
    id=(a-ACTORS)//0x300;off=(a-ACTORS)%0x300
    assert 0<=id<len(items) and (off,size) in [(0x30,4),(0x74,1),(0x75,1)]
    events.extend(['N' if off==0x30 else 'M' if off==0x74 else 'B',id,self.id(value) if off==0x30 else value&255])
   elif CELL<=a<CELL+0x200:
    assert (a-CELL,size) in [(0xe4,4),(0xe8,4),(0x124,1)]
    if a==CELL+0x124:events.extend(['W',0,value&255])
    else:events.extend(['H',int(a==CELL+0xe8),self.id(value)])
   elif any(p<=a<p+n for p,n in regions[1:]):raise AssertionError((hex(a),size))
  hooks=[self.u.hook_add(UC_HOOK_CODE,service),self.u.hook_add(UC_HOOK_MEM_WRITE,write)]
  try:
   if op=='S':self.checked_call(self.va(0x473730) if mode==4 else self.va(0x473920),[actor,alternate],CELL);result=1
   else:self.checked_call(self.va(0x6d8950),[mode],actor);result=self.u.reg_read(UC_X86_REG_EAX)&255
  finally:
   for h in hooks:self.u.hook_del(h)
  for (p,n),old in zip(regions,before):
   new=bytearray(self.u.mem_read(p,n));expected=bytearray(old)
   if p==ACTORS:
    for id in range(len(items)):
     for off,length in [(0x30,4),(0x74,2)]:new[id*0x300+off:id*0x300+off+length]=expected[id*0x300+off:id*0x300+off+length]
   if p==CELL:
    for off,length in [(0xe4,4),(0xe8,4),(0x124,1)]:new[off:off+length]=expected[off:off+length]
   assert new==expected,hex(p)
  result=[result,self.id(struct.unpack('<I',self.u.mem_read(CELL+0xe4,4))[0]),self.id(struct.unpack('<I',self.u.mem_read(CELL+0xe8,4))[0]),struct.unpack('<I',self.u.mem_read(CELL+0x124,4))[0]]
  for id in range(len(items)):result.extend([self.id(struct.unpack('<I',self.u.mem_read(self.ptr(id)+0x30,4))[0]),*self.u.mem_read(self.ptr(id)+0x74,2)])
  return [*result,*events]
 @staticmethod
 def ptr(id):return 0 if id==-1 else ACTORS+id*0x300
 @staticmethod
 def id(ptr):
  if ptr==0:return -1
  assert ptr>=ACTORS and (ptr-ACTORS)%0x300==0
  return (ptr-ACTORS)//0x300
