# SPDX-License-Identifier: GPL-3.0-or-later
"""Unchanged full nearby-Cell parent; explicit supplied decision services."""
import struct
from collections import Counter
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from original_presentation import PresentationOracle,STOP,STACK
from verify_nearby_location import verify,RANGES,TABLES,SERVICES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_EIP,UC_X86_REG_ESP,UC_X86_REG_ESI
ARENA=0x2800000;SIZE=0x20000;SLOTS=0x2900000;CELLS=[ARENA+0x1000+i*0x200 for i in range(127)];FALLBACK=0xa6f9f8
SOURCE=ARENA;CLOSE=ARENA+8;OUT=ARENA+16;MAP=0x8324e0
def signed(v):return (v+0x80000000)%0x100000000-0x80000000
def pack(*v):return struct.pack('<'+'I'*len(v),*[n&0xffffffff for n in v])
class NearbyLocationOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True)
  self.u.mem_map(ARENA,SIZE);self.u.mem_map(SLOTS,0x100000)
  self.active=False;self.counts=Counter();self.instructions=set();self.writes=Counter()
  cs=Cs(CS_ARCH_X86,CS_MODE_32);self.allowed={(i.address,i.size) for a,n in RANGES.items() for i in cs.disasm(bytes(self.u.mem_read(a,n)),a)}
  self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.store)
  self.checked_call(0x49f600,writes=[(0x852998,12)],inputs=[*RANGES.items(),*TABLES.items()])
  assert self.u.mem_read(0x852998,12)==bytes(12)
 def va(self,a):return a
 def word(self,p):return int.from_bytes(self.u.mem_read(p,4),'little')
 def point(self,p):return struct.unpack('<2h',self.u.mem_read(p,4))
 def event(self,*v):self.events.extend(map(str,v))
 def ret(self,n,value):
  u=self.u;sp=u.reg_read(UC_X86_REG_ESP);target=self.word(sp)
  u.reg_write(UC_X86_REG_EAX,value&0xffffffff);u.reg_write(UC_X86_REG_ESP,sp+4+n);u.reg_write(UC_X86_REG_EIP,target)
 def find(self,point):
  x,y=point;index=signed((y<<9)+x)
  return self.slots.get(index,self.size-1) if 0<=index<262144 else self.size-1
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  sp=u.reg_read(UC_X86_REG_ESP);arg=lambda i:self.word(sp+4+4*i);ecx=u.reg_read(UC_X86_REG_ECX)
  if a in SERVICES:
   self.counts[hex(a)]+=1
   if a==0x55a740:
    assert ecx==MAP and arg(1)==1
    i=self.ptrs.index(arg(0));row=self.c['cells'][i];self.event('B',i,*self.point(arg(0)+0x24),1,row[5]);self.ret(8,row[5])
   elif a==0x550cf0:
    assert ecx==MAP;point=self.point(arg(0));i=self.find(point);row=self.c['cells'][i]
    values=[signed(arg(j)) for j in range(1,7)]+[arg(7),arg(8)&255]
    assert values==[self.c['width'],self.c['height'],self.c['speed'],(-1 if self.c['zone']==65535 else self.c['zone']),self.c['movement'],-1,self.c['alternate'],self.c['overlay']]
    self.event('C',*point,*values,row[6]);self.ret(36,row[6])
   elif a==0x47c200:
    i=self.ptrs.index(ecx);value=self.c['cells'][i][7];self.event('b',i,value);self.ret(0,value)
   else:
    assert ecx==MAP;out,p=arg(0),arg(1);x,y,z=struct.unpack('<3i',u.mem_read(p,12));assert z==0 and x%256==y%256==128
    point=((x-128)//256,(y-128)//256);i=self.find(point);self.projections+=1
    good=self.c['cells'][i][8]^bool(self.c['flip_at'] and self.projections>=self.c['flip_at'])
    self.event('P',*point,int(good))
    if self.projections==1 and self.c['mutation']:
     self.put(0xa40d2c,self.c['mutation_frame']);self.event('X',self.c['mutation_frame'])
     if self.c['mutation']==2:
      u.mem_write(CLOSE,struct.pack('<2h',*self.c['mutation_close']));self.expected[8:12]=u.mem_read(CLOSE,4);self.event('T',*self.c['mutation_close'])
    chosen=point if good else (signed((point[0]+17+32768)%65536-32768),point[1])
    u.mem_write(out,struct.pack('<2h',*chosen));self.ret(8,out)
   return
  assert (a,n) in self.allowed,('Uninspected nearby-location instruction',hex(a))
  self.instructions.add(a)
  if a in RANGES:self.counts[hex(a)]+=1
  if a in (0x550352,0x550396):
   p=u.reg_read(UC_X86_REG_EAX);self.event('L',*self.c['source'],self.ptrs.index(p))
  elif a in (0x55044c,0x5505f7,0x5507cf,0x550968):
   self.event('L',*self.point(sp+0x10),self.ptrs.index(u.reg_read(UC_X86_REG_ESI)))
  elif a in (0x5503ea,0x55076d):self.counts['radius.'+str(self.word(sp+0x1c))]+=1
  elif a in (0x55051a,0x5506c5,0x55089d,0x550a36):self.counts['candidate_store']+=1
  elif a in (0x550b83,0x550b9a):self.counts['preferred' if a==0x550b83 else 'other']+=1
  elif a in (0x550be6,0x550c05):self.counts['frame_preferred' if a==0x550be6 else 'frame_other']+=1
  elif a==0x550ae3:self.counts['capacity24']+=1
  elif a==0x550320:self.counts['zone65535_normalized']+=1
  elif a in (0x5504dc,0x550687,0x55085f,0x5509f8):
   self.counts['level_difference.'+str(signed(u.reg_read(UC_X86_REG_EAX)))]+=1
  elif a==0x4ba410:
   self.square=struct.unpack('<d',u.mem_read(sp+4,8))[0];self.square_result=0.
   self.counts['sqrt.'+('negative' if self.square<0 else 'positive' if self.square>0 else 'zero')]+=1
  elif a==0x550c95:
   self.event('D',int(self.square),struct.unpack('<Q',struct.pack('<d',self.square_result))[0]);self.counts['distance']+=1
  elif a in (0x550c02,0x550c21,0x550ccb,0x550ce7):self.counts['return.'+hex(a)]+=1
 def store(self,u,access,p,n,value,_):
  if not self.active:return
  a=u.reg_read(UC_X86_REG_EIP);value&=(1<<(8*n))-1;self.writes[hex(a)]+=1
  if a==0x4ba475:self.square_result=struct.unpack('<f',pack(value))[0]
  if p==FALLBACK+0x24:
   assert n==4 and a in (0x550348,0x55038c,0x550441,0x5505ec,0x5507c4,0x55095d)
   self.event('W',*struct.unpack('<2h',pack(value)))
  if ARENA<=p and p+n<=ARENA+SIZE:
   assert (p,n)==(OUT,4) and a in (0x550bfa,0x550c19,0x550cc2,0x550cde)
   self.expected[p-ARENA:p-ARENA+n]=value.to_bytes(n,'little')
 def run(self,c):
  self.c=c;self.size=len(c['cells']);self.ptrs=CELLS[:self.size-1]+[FALLBACK];self.slots={};self.events=[];self.projections=0
  u=self.u;u.mem_write(ARENA,b'\xa5'*SIZE);u.mem_write(SLOTS,bytes(0x100000));u.mem_write(SOURCE,struct.pack('<2h',*c['source']));u.mem_write(CLOSE,struct.pack('<2h',*c['close']))
  for p,row in zip(self.ptrs,c['cells']):
   slot,x,y,level,flags,*_=row;u.mem_write(p,b'\xa5'*0x148);u.mem_write(p+0x24,struct.pack('<2h',x,y));u.mem_write(p+0x11b,bytes([level&255]));self.put(p+0x140,flags)
   if slot!=-1:self.slots[slot]=self.ptrs.index(p);self.put(SLOTS+4*slot,p)
  self.put(MAP+0x138,SLOTS);self.put(MAP+0xf0,c['dimension0']);self.put(MAP+0xf4,c['dimension1']);self.put(0x83996c,MAP);self.put(0xa40d2c,c['frame']);u.mem_write(0xa6f238,struct.pack('<2h',*c['empty']))
  self.expected=bytearray(u.mem_read(ARENA,SIZE));fallback=bytes(u.mem_read(FALLBACK,0x148))
  args=[OUT,SOURCE,c['speed'],c['zone'],c['movement'],c['alternate'],c['width'],c['height'],c['overlay'],c['match'],c['burrow'],c['bridge'],CLOSE,c['skip']]
  self.active=True
  try:self.checked_call(0x5502e0,args,MAP,writes=[(OUT,4),(FALLBACK+0x24,4)],
   inputs=[*RANGES.items(),*TABLES.items(),(SLOTS,0x100000),(MAP+0xf0,8),(MAP+0x138,4),(0x83996c,4),(0xa6f238,4),(0x852998,12)])
  finally:self.active=False
  assert u.reg_read(UC_X86_REG_EAX)==OUT
  assert bytes(u.mem_read(ARENA,SIZE))==bytes(self.expected),'Whole nearby-location arena changed'
  retained=bytearray(u.mem_read(FALLBACK,0x148));retained[0x24:0x28]=fallback[0x24:0x28];assert bytes(retained)==fallback,'Unexpected fallback mutation'
  self.event('R',*self.point(OUT));self.event('state',*self.point(FALLBACK+0x24),signed(self.word(0xa40d2c)),*self.point(CLOSE),self.projections)
  return self.events
