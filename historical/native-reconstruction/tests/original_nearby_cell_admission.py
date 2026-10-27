# SPDX-License-Identifier: GPL-3.0-or-later
"""Unmodified complete Cell/rectangle/permission; only zone resolver supplied."""
import struct
from collections import Counter
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from original_presentation import PresentationOracle,STOP
from verify_nearby_cell_admission import verify,RANGES,TABLES,SERVICES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_EIP,UC_X86_REG_ESP
ARENA=0x2800000;SIZE=0x20000;SLOTS=0x2900000;REGISTRY=ARENA+0x800;ORIGIN=ARENA;CELLS=[ARENA+0x1000+i*0x200 for i in range(127)];FALLBACK=0xa6f9f8;MAP=0x8324e0
TYPES=[ARENA+0x11000+i*0x300 for i in range(4)]
def signed(v):return (v+0x80000000)%0x100000000-0x80000000
def pack(*v):return struct.pack('<'+'I'*len(v),*[n&0xffffffff for n in v])
class NearbyCellAdmissionOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True)
  self.u.mem_map(ARENA,SIZE);self.u.mem_map(SLOTS,0x100000)
  cs=Cs(CS_ARCH_X86,CS_MODE_32);self.allowed={(i.address,i.size):i.mnemonic for a,n in RANGES.items() for i in cs.disasm(bytes(self.u.mem_read(a,n)),a)}
  self.active=False;self.counts=Counter();self.instructions=set();self.writes=Counter();self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.store)
 def va(self,a):return a
 def word(self,p):return int.from_bytes(self.u.mem_read(p,4),'little')
 def point(self,p):return struct.unpack('<2h',self.u.mem_read(p,4))
 def event(self,*v):self.events.extend(map(str,v))
 def ret(self,n,value):
  u=self.u;sp=u.reg_read(UC_X86_REG_ESP);target=self.word(sp);u.reg_write(UC_X86_REG_EAX,value&0xffffffff);u.reg_write(UC_X86_REG_ESP,sp+4+n);u.reg_write(UC_X86_REG_EIP,target)
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  sp=u.reg_read(UC_X86_REG_ESP);arg=lambda i:self.word(sp+4+4*i);ecx=u.reg_read(UC_X86_REG_ECX)
  if a==0x54f8f0:
   assert ecx==MAP;cell=arg(0)-0x24;i=self.ptrs.index(cell)
   self.event('Z',i,*self.point(arg(0)),signed(arg(1)),arg(2),self.c['zone_result']);self.counts['zone_service']+=1
   if self.c['mutation']:
    row=self.rows[i];row[3]=-2;row[5]^=0x100;row[7]^=0xe0;row[8]^=0x1f;row[6]=1;row[9]=3;row[1]=(row[1]+1+32768)%65536-32768
    self.writecell(cell,row);self.event('X',i);self.counts['diagnostic_mutation']+=1
   self.ret(12,self.c['zone_result']);return
  assert (a,n) in self.allowed,('Uninspected Cell admission instruction',hex(a))
  self.instructions.add(a);self.counts[hex(a)]+=1
  if a==0x478760:
   self.event('C',self.ptrs.index(ecx),signed(arg(0)),arg(1)&255,arg(2)&255,signed(arg(3)),signed(arg(4)),signed(arg(5)),arg(6));self.counts['Cell_calls']+=1
  if 0x478760<=a<0x4788c3 and self.allowed[a,n]=='ret':self.event('c',u.reg_read(UC_X86_REG_EAX)&255);self.counts['Cell_return.'+str(u.reg_read(UC_X86_REG_EAX)&255)]+=1
  if a==0x55a740:self.event('P',self.ptrs.index(arg(0)),arg(1)&255);self.counts['permission_calls']+=1
  if a==0x4788a8:
   ah=(u.reg_read(UC_X86_REG_EAX)>>8)&255
   self.counts['speed_compare.'+('unordered' if ah&4 else 'zero' if ah&64 else 'negative' if ah&1 else 'positive')]+=1
  if a in (0x478804,0x478810):self.counts['elevated_occupation' if a==0x478804 else 'primary_occupation']+=1
  if a==0x550d62:
   self.event('L',*self.point(sp+0x2c),self.ptrs.index(ecx));self.counts['rectangle_lookups']+=1
 def writecell(self,p,row):
  _,x,y,level,slope,flags,land,occupation,elevated,overlay=row
  self.u.mem_write(p+0x24,struct.pack('<2h',x,y));self.u.mem_write(p+0x11b,bytes([level&255,slope]));self.put(p+0x140,flags);self.put(p+0xec,land);self.put(p+0x124,occupation);self.put(p+0x128,elevated);self.put(p+0x44,overlay)
  if self.active:self.expected[p]=bytes(self.u.mem_read(p,0x148))
 def store(self,u,access,p,n,value,_):
  if not self.active:return
  a=u.reg_read(UC_X86_REG_EIP);self.writes[hex(a)]+=1
  if p==FALLBACK+0x24:
   assert a==0x550d5d and n==4;self.event('W',*struct.unpack('<2h',pack(value)))
   row=self.rows[-1];row[1:3]=struct.unpack('<2h',pack(value));old=bytearray(self.expected[FALLBACK]);old[0x24:0x28]=pack(value);self.expected[FALLBACK]=bytes(old)
 def run(self,c):
  import copy
  self.c=c;self.rows=copy.deepcopy(c['cells']);self.ptrs=CELLS[:len(self.rows)-1]+[FALLBACK];self.events=[];u=self.u
  u.mem_write(ARENA,b'\xa5'*SIZE);u.mem_write(SLOTS,bytes(0x100000));u.mem_write(ORIGIN,struct.pack('<2h',c['x'],c['y']))
  for p,row in zip(self.ptrs,self.rows):
   u.mem_write(p,b'\xa5'*0x148);self.writecell(p,row)
   if row[0]!=-1:self.put(SLOTS+row[0]*4,p)
  for i,(present,wall,crush) in enumerate(c['overlays']):
   self.put(REGISTRY+i*4,TYPES[i] if present else 0);u.mem_write(TYPES[i]+0x278,bytes([wall]));u.mem_write(TYPES[i]+0x1fd,bytes([crush]))
  self.put(0xa35dec,REGISTRY);u.mem_write(0x850ea0,pack(*c['speeds']));self.put(MAP+0x138,SLOTS)
  for off,k in ((0xf0,'dimension0'),(0xf8,'origin_x'),(0xfc,'origin_y'),(0x100,'shape_width'),(0x104,'shape_height')):self.put(MAP+off,c[k])
  args=[c['speed'],c['ignore_low'],c['ignore_middle'],c['zone'],c['movement'],c['level'],c['alternate']];root=0x478760;obj=self.ptrs[0]
  if c['op']==1:root=0x550cf0;obj=MAP;args=[ORIGIN,c['width'],c['height'],c['speed'],c['zone'],c['movement'],c['level'],c['alternate'],c['disallow']]
  if c['op']==2:root=0x55a740;obj=MAP;args=[self.ptrs[0],c['elevation']]
  self.expected={p:bytes(u.mem_read(p,0x148)) for p in self.ptrs};before=bytes(u.mem_read(ARENA,SIZE))
  inputs=[*RANGES.items(),*TABLES.items(),(SLOTS,0x100000),(0xa35dec,4),(0x850ea0,4*len(c['speeds'])),(MAP+0xf0,0x18),(MAP+0x138,4)]
  self.active=True
  try:self.checked_call(root,args,obj,writes=[(FALLBACK+0x24,4)],inputs=inputs)
  finally:self.active=False
  after=bytearray(u.mem_read(ARENA,SIZE));wanted=bytearray(before)
  for p in self.ptrs:
   assert bytes(u.mem_read(p,0x148))==self.expected[p],('Cell record changed',hex(p))
   if ARENA<=p<ARENA+SIZE:wanted[p-ARENA:p-ARENA+0x148]=self.expected[p]
  assert bytes(after)==bytes(wanted),'Whole arena/registry/type/coordinate changed'
  result=u.reg_read(UC_X86_REG_EAX)&255;assert result in (0,1);self.event('R',result);self.counts['top.'+str(c['op'])]+=1;self.counts['top_return.'+str(c['op'])+'.'+str(result)]+=1
  self.event('state')
  for row in self.rows:self.event(row[1],row[2],row[3],row[5],row[6],row[7],row[8],row[9])
  return self.events
