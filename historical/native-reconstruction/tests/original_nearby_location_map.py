# SPDX-License-Identifier: GPL-3.0-or-later
"""Unchanged complete search and actual admission/permission/projection children."""
import copy,struct
from collections import Counter
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from original_presentation import PresentationOracle,STOP
from original_nearby_cell_admission import ARENA,SIZE,SLOTS,REGISTRY,ORIGIN,CELLS,FALLBACK,MAP,TYPES,pack,signed
from verify_nearby_location_map import verify,RANGES,TABLES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_EIP,UC_X86_REG_ESP,UC_X86_REG_ESI,UC_X86_REG_EBP
SOURCE=ARENA;CLOSE=ARENA+8;OUT=ARENA+16
class NearbyLocationMapOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True)
  self.u.mem_map(ARENA,SIZE);self.u.mem_map(SLOTS,0x100000)
  cs=Cs(CS_ARCH_X86,CS_MODE_32);self.allowed={(i.address,i.size):i.mnemonic for a,n in RANGES.items() for i in cs.disasm(bytes(self.u.mem_read(a,n)),a)}
  self.active=False;self.counts=Counter();self.instructions=set();self.writes=Counter();self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.store)
 def va(self,a):return a
 def word(self,p):return int.from_bytes(self.u.mem_read(p,4),'little')
 def point(self,p):return struct.unpack('<2h',self.u.mem_read(p,4))
 def event(self,*v):self.events.extend(map(str,v))
 def enter(self,kind,n,extra=0):
  sp=self.u.reg_read(UC_X86_REG_ESP);self.pending.append((self.word(sp),sp+4+n,kind,extra))
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  sp=u.reg_read(UC_X86_REG_ESP)
  if self.pending and self.pending[-1][:2]==(a,sp):
   _,_,kind,extra=self.pending.pop();eax=u.reg_read(UC_X86_REG_EAX)
   if kind=='b':self.event('b',self.ptrs.index(extra),eax&255);self.counts['permission.'+str(eax&255)]+=1
   elif kind=='t':self.event('t',eax&255);self.counts['rectangle.'+str(eax&255)]+=1
   else:assert eax==extra;self.event('p',*self.point(extra));self.counts['projection_return']+=1
  assert a not in (0x54f8f0,0x47c200),('Unjoined nearby child entered',hex(a))
  assert (a,n) in self.allowed,('Uninspected nearby map instruction',hex(a))
  self.instructions.add(a);self.counts[hex(a)]+=1
  arg=lambda i:self.word(sp+4+4*i);ecx=u.reg_read(UC_X86_REG_ECX)
  if a in (0x550352,0x550396):self.event('L',*self.c['source'],self.ptrs.index(u.reg_read(UC_X86_REG_EAX)))
  elif a in (0x55044c,0x5505f7,0x5507cf,0x550968):self.event('L',*self.point(sp+0x10),self.ptrs.index(u.reg_read(UC_X86_REG_ESI)))
  elif a==0x55a740:
   self.event('B',self.ptrs.index(arg(0)),*self.point(arg(0)+0x24),arg(1)&255);self.enter('b',8,arg(0))
  elif a==0x550cf0:
   assert [signed(arg(j)) for j in range(1,7)]+[arg(7),arg(8)&255]==[self.c['width'],self.c['height'],self.c['speed'],-1,self.c['movement'],-1,self.c['alternate'],self.c['disallow']]
   self.event('T',*self.point(arg(0)));self.enter('t',36)
  elif a==0x550d62:self.event('J',*self.point(sp+0x2c),self.ptrs.index(ecx))
  elif a==0x478760:
   self.event('C',self.ptrs.index(ecx),signed(arg(0)),arg(1)&255,arg(2)&255,signed(arg(3)),signed(arg(4)),signed(arg(5)),arg(6));self.counts['Cell_calls']+=1
  elif a==0x548070:self.event('G',*self.point(arg(0)));self.counts['projection_lookup']+=1
  elif a==0x6a6a50:
   x,y,z=struct.unpack('<3i',u.mem_read(arg(1),12));assert z==0 and x%256==y%256==128
   self.project_input=((x-128)//256,(y-128)//256);self.event('P',*self.project_input);self.enter('p',8,arg(0));self.counts['projection_calls']+=1
  elif a in (0x5503ea,0x55076d):self.counts['radius.'+str(self.word(sp+0x1c))]+=1
  elif a in (0x55051a,0x5506c5,0x55089d,0x550a36):self.counts['candidate_store']+=1
  elif a in (0x550b83,0x550b9a):self.counts['preferred' if a==0x550b83 else 'other']+=1
  elif a==0x550ae7:
   retained=self.word(sp+0x18);assert u.reg_read(UC_X86_REG_EBP)==retained;self.counts['retained.'+str(retained)]+=1
   if retained==24:self.counts['capacity24']+=1
  elif a==0x4ba410:self.square=struct.unpack('<d',u.mem_read(sp+4,8))[0];self.square_result=0.;self.counts['sqrt.'+('negative' if self.square<0 else 'positive' if self.square>0 else 'zero')]+=1
  elif a==0x550c95:self.event('D',int(self.square),struct.unpack('<Q',struct.pack('<d',self.square_result))[0])
  if 0x478760<=a<0x4788c3 and self.allowed[a,n]=='ret':self.event('c',u.reg_read(UC_X86_REG_EAX)&255);self.counts['Cell_return.'+str(u.reg_read(UC_X86_REG_EAX)&255)]+=1
  if a==0x6a6bcb:raise AssertionError('Projection beyond complete range')
 def store(self,u,access,p,n,value,_):
  if not self.active:return
  a=u.reg_read(UC_X86_REG_EIP);value&=(1<<(8*n))-1;self.writes[hex(a)]+=1
  if a==0x4ba475:self.square_result=struct.unpack('<f',pack(value))[0]
  if p==FALLBACK+0x24:
   assert n==4 and (a in (0x550348,0x55038c,0x550441,0x5505ec,0x5507c4,0x55095d,0x550d5d) or 0x548070<=a<0x5480a8)
   self.event('W',*struct.unpack('<2h',pack(value)));old=bytearray(self.expected[FALLBACK]);old[0x24:0x28]=pack(value);self.expected[FALLBACK]=bytes(old);self.rows[-1][1:3]=struct.unpack('<2h',pack(value))
  if ARENA<=p and p+n<=ARENA+SIZE:
   assert (p,n)==(OUT,4) and a in (0x550bfa,0x550c19,0x550cc2,0x550cde)
   self.arena_expected[p-ARENA:p-ARENA+n]=value.to_bytes(n,'little')
 def run(self,c):
  self.c=c;self.rows=copy.deepcopy(c['cells']);self.ptrs=CELLS[:len(self.rows)-1]+[FALLBACK];self.events=[];self.pending=[];u=self.u
  u.mem_write(ARENA,b'\xa5'*SIZE);u.mem_write(SLOTS,bytes(0x100000));u.mem_write(SOURCE,struct.pack('<2h',*c['source']));u.mem_write(CLOSE,struct.pack('<2h',*c['close']))
  for p,row in zip(self.ptrs,self.rows):
   _,x,y,level,slope,flags,land,occupation,elevated,overlay=row;u.mem_write(p,b'\xa5'*0x148);u.mem_write(p+0x24,struct.pack('<2h',x,y));u.mem_write(p+0x11b,bytes([level&255,slope]));self.put(p+0x140,flags);self.put(p+0xec,land);self.put(p+0x124,occupation);self.put(p+0x128,elevated);self.put(p+0x44,overlay)
   if row[0]!=-1:self.put(SLOTS+row[0]*4,p)
  for i,(present,wall,crush) in enumerate(c['overlays']):self.put(REGISTRY+i*4,TYPES[i] if present else 0);u.mem_write(TYPES[i]+0x278,bytes([wall]));u.mem_write(TYPES[i]+0x1fd,bytes([crush]))
  self.put(0xa35dec,REGISTRY);u.mem_write(0x850ea0,pack(*c['speeds']));self.put(MAP+0x138,SLOTS);self.put(0x83996c,MAP);self.put(0xa40d2c,c['frame']);u.mem_write(0xa6f238,struct.pack('<2h',*c['empty']))
  for off,k in ((0xf0,'dimension0'),(0xf4,'dimension1'),(0xf8,'origin_x'),(0xfc,'origin_y'),(0x100,'shape_width'),(0x104,'shape_height')):self.put(MAP+off,c[k])
  self.expected={p:bytes(u.mem_read(p,0x148)) for p in self.ptrs};self.arena_expected=bytearray(u.mem_read(ARENA,SIZE))
  args=[OUT,SOURCE,c['speed'],c['zone'],c['movement'],c['alternate'],c['width'],c['height'],c['disallow'],c['match'],0,c['bridge'],CLOSE,c['skip']]
  self.active=True
  try:self.checked_call(0x5502e0,args,MAP,writes=[(OUT,4),(FALLBACK+0x24,4)],inputs=[*RANGES.items(),*TABLES.items(),(SLOTS,0x100000),(0xa35dec,4),(0x850ea0,4*len(c['speeds'])),(MAP+0xf0,0x18),(MAP+0x138,4),(0x83996c,4),(0xa40d2c,4),(0xa6f238,4)])
  finally:self.active=False
  assert not self.pending and u.reg_read(UC_X86_REG_EAX)==OUT
  for p in self.ptrs:assert bytes(u.mem_read(p,0x148))==self.expected[p],('Cell record changed',hex(p))
  assert bytes(u.mem_read(ARENA,SIZE))==bytes(self.arena_expected),'Whole search arena/types/registry/inputs changed'
  self.event('R',*self.point(OUT));self.event('state')
  for row in self.rows:self.event(row[1],row[2],row[3],row[5],row[6],row[7],row[8],row[9])
  return self.events
