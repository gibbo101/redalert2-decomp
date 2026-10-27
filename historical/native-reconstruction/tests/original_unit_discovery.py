# SPDX-License-Identifier: GPL-3.0-or-later
"""Unmodified base visibility/discovery and third stock numeric initialization."""
import struct
from original_ramp_geometry import RampGeometryOracle
from original_presentation import STOP
from original_map_floor_height import CELL,INPUT,FALLBACK,SLOTS,MAP,packed
from original_foot_lit import words,ints,ret,signed
from verify_unit_discovery import verify,RANGES,NUMERIC,OUTPUTS,DISPATCH
from verify_ramp_geometry import RANGES as GEOMETRY
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EAX
ACTOR=CELL+0x2000;HOUSES=[0x2600000,0x2606000];TAG=0x2610000
CELLS=[CELL,CELL+0x400,CELL+0x800,FALLBACK]
def house_ptr(i):return 0 if i==-1 else HOUSES[i]
def house_id(p):return -1 if p==0 else HOUSES.index(p)
def shorts(u,p):return struct.unpack('<hh',u.mem_read(p,4))
class UnitDiscoveryOracle(RampGeometryOracle):
 def __init__(self,exe):
  super().__init__(exe);self.inspection=verify(exe.read_bytes())
  self.u.mem_map(CELL,0x10000);self.u.mem_map(SLOTS,0x100000);self.u.mem_map(HOUSES[0],0x12000)
  self.entries.update({hex(a):0 for a in RANGES if a not in GEOMETRY})
  self.u.hook_add(UC_HOOK_CODE,self.observe);self.active=False;self.selected_stores=0;self.tag_calls=0
 def block(self,u,a,n,ctx):
  if a not in (STOP,0x6b3df0) and not any(p<=a and a+n<=p+size for p,size in RANGES.items()):raise AssertionError(f'Uninspected discovery block {a:#x}/{n}')
 def event(self,*v):self.events.extend(map(str,v))
 def cell(self,p):return CELLS.index(p)
 def observe(self,u,a,n,ctx):
  if a in RANGES and a not in GEOMETRY:self.entries[hex(a)]+=1
  if not self.active:return
  sp=u.reg_read(UC_X86_REG_ESP);ecx=u.reg_read(UC_X86_REG_ECX)
  if a in (0x56819f,0x56822b,0x568444,0x5684ce):self.event('i',*shorts(u,sp+0x10))
  elif a==0x476ac0:self.event('n',self.cell(ecx),words(u,sp+4,1)[0]);assert words(u,sp+4,1)==[3]
  elif a==0x548070:self.event('w',*shorts(u,words(u,sp+4,1)[0]))
  elif a==0x6c2440:self.event('d',house_id(words(u,sp+4,1)[0]));assert ecx==ACTOR
  elif a==0x5d4230:self.event('b',house_id(words(u,sp+4,1)[0]))
  elif a==0x4f52f0:self.event('h',house_id(ecx))
  elif a==0x594770:self.event('g',0)
  elif a==0x594cb0:self.event('q',signed(words(u,sp+4,1)[0]));assert words(u,sp+8,1)==[0]
  elif a==0x6b3df0:
   args=words(u,sp+4,5);assert ecx==TAG and args==[4,ACTOR,self.context&0xffffffff,0,0]
   self.event('t',4,self.context);self.tag_calls+=1
   if self.mutation:
    owner=1-house_id(words(u,ACTOR+0x1b4,1)[0]);self.put(ACTOR+0x1b4,house_ptr(owner));self.event('z',owner)
   ret(u,20,0)
 def stock_visibility(self,seed):
  for p,n in OUTPUTS.items():self.u.mem_write(p,bytes([(seed*71+0xa7)&255])*n)
  stores=[]
  def store(u,access,p,n,v,ctx):
   for base,size in OUTPUTS.items():
    if base<=p<base+size:assert p==base and n==size;stores.append((p,v&((1<<(n*8))-1)))
  hook=self.u.hook_add(UC_HOOK_MEM_WRITE,store)
  try:
   for a,(p,n) in zip(NUMERIC,OUTPUTS.items()):self.checked_call(a,writes=[(p,n)],inputs=self.inputs+[(q,s) for q,s in OUTPUTS.items() if q!=p]+[(0x7a58f8,16)])
   self.checked_call(0x491620,writes=[(0x851a70,32)],inputs=list(RANGES.items()))
  finally:self.u.hook_del(hook)
  assert [p for p,v in stores]==list(OUTPUTS)
  self.selected_stores+=len(stores)
  self.stock_divisor=words(self.u,0xa6fc30,1)[0]
  return [str(int.from_bytes(self.u.mem_read(p,n),'little')) for p,n in OUTPUTS.items()]+list(map(str,shorts(self.u,0x851a7c)))
 def visibility(self,h,records):
  secondary,divisor,mode,override,house13d,x,y,z=h;u=self.u;self.events=[]
  self.u.mem_write(CELL,b'\xa5'*0x10000);self.u.mem_write(FALLBACK,b'\xa5'*0x148);self.u.mem_write(SLOTS,bytes(0x100000))
  self.put(MAP+0x138,SLOTS);self.put(0xa6fc30,divisor);self.put(0xa3d298,mode);self.put(0xa3d548,override);self.put(0xa35db4,HOUSES[0]);u.mem_write(HOUSES[0]+0x13d,bytes([house13d]));u.mem_write(INPUT,packed([x,y,z]))
  for p,(slot,cx,cy,f,g) in zip(CELLS,records):
   self.put(p+0x24,(cx&65535)|((cy&65535)<<16));self.put(p+0x12c,f);self.put(p+0x140,g)
   if slot!=-1:self.put(SLOTS+slot*4,p)
  before=bytes(u.mem_read(CELL,0x10000));fb=bytes(u.mem_read(FALLBACK,0x148))
  def stores(u,access,p,n,v,ctx):
   if FALLBACK+0x24<=p<FALLBACK+0x28:
    assert p==FALLBACK+0x24 and n==4;self.event('f',*struct.unpack('<hh',struct.pack('<I',v&0xffffffff)));self.selected_stores+=1
  hook=u.hook_add(UC_HOOK_MEM_WRITE,stores);self.active=True
  try:self.checked_call(0x5683c0 if secondary else 0x568140,[INPUT],MAP,writes=[(FALLBACK+0x24,4)],inputs=[*RANGES.items(),(0x851a70,32),(SLOTS,0x100000),(INPUT,12),(MAP+0x138,4),(0xa6fc30,4),(0xa3d298,4),(0xa3d548,4),(0xa35db4,4),(HOUSES[0]+0x13d,1)])
  finally:self.active=False;u.hook_del(hook)
  assert bytes(u.mem_read(CELL,0x10000))==before
  after=bytearray(u.mem_read(FALLBACK,0x148));after[0x24:0x28]=fb[0x24:0x28];assert bytes(after)==fb
  self.event('R',u.reg_read(UC_X86_REG_EAX)&255,*shorts(u,FALLBACK+0x24));return self.events
 def discovery(self,h,houses,discoverers):
  mode,loading,self.context,current,owner,b372,b373,b374,mission,queued,a4,tag,self.mutation=h;u=self.u;self.events=[]
  u.mem_write(CELL,b'\xa5'*0x10000);u.mem_write(HOUSES[0],b'\xa5'*0xc000)
  self.put(ACTOR,0x7addf8);self.put(ACTOR+0x1b4,house_ptr(owner));self.put(ACTOR+0x34,TAG if tag else 0)
  u.mem_write(ACTOR+0x372,bytes([b372,b373,b374]));self.put(ACTOR+0x98,mission);self.put(ACTOR+0xa0,queued);u.mem_write(ACTOR+0xa4,bytes([a4]))
  self.put(0xa3d298,mode);self.put(0xa40774,loading);self.put(0xac0148,self.context);self.put(0xa35db4,house_ptr(current))
  for p,values in zip(HOUSES,houses):
   for off,v in zip((0x134,0x135,0x13c,0x13d,0x5668,0x5669),values):u.mem_write(p+off,bytes([v]))
  writes=[(ACTOR+0x373,2),(ACTOR+0xa0,4),(ACTOR+0xa4,1),*[(p+off,n) for p in HOUSES for off,n in ((0x13c,1),(0x5668,2))]]
  if self.mutation:writes.append((ACTOR+0x1b4,4))
  def stores(u,access,p,n,v,ctx):
   if ACTOR+0x373<=p<ACTOR+0x375 or p==ACTOR+0xa4:assert n==1;self.event('W',0,p-ACTOR,v&255);self.selected_stores+=1
   elif ACTOR+0xa0<=p<ACTOR+0xa4:assert p==ACTOR+0xa0 and n==4;self.event('W',0,0xa0,v&0xffffffff);self.selected_stores+=1
   for i,hp in enumerate(HOUSES):
    if p==hp+0x13c or hp+0x5668<=p<hp+0x566a:assert n==1;self.event('W',i+1,p-hp,v&255);self.selected_stores+=1
  for discoverer in discoverers:
   arena=bytes(u.mem_read(CELL,0x10000));hs=bytes(u.mem_read(HOUSES[0],0xc000));hook=u.hook_add(UC_HOOK_MEM_WRITE,stores);self.active=True
   try:self.checked_call(0x6c2440,[house_ptr(discoverer)],ACTOR,writes=writes,inputs=[*RANGES.items(),*[(p,4) for p in DISPATCH],(0xa3d298,4),(0xa40774,4),(0xac0148,4),(0xa35db4,4)])
   finally:self.active=False;u.hook_del(hook)
   for base,size,before in ((CELL,0x10000,arena),(HOUSES[0],0xc000,hs)):
    after=bytearray(u.mem_read(base,size))
    for p,n in writes:
     if base<=p and p+n<=base+size:after[p-base:p-base+n]=before[p-base:p-base+n]
    assert bytes(after)==before,'Discovery changed unselected storage'
   self.event('R',u.reg_read(UC_X86_REG_EAX)&255,house_id(words(u,ACTOR+0x1b4,1)[0]),*u.mem_read(ACTOR+0x373,2),signed(words(u,ACTOR+0xa0,1)[0]),u.mem_read(ACTOR+0xa4,1)[0])
   for p in HOUSES:self.event(u.mem_read(p+0x13c,1)[0],*u.mem_read(p+0x5668,2))
  return self.events
 def house(self,mode,a,b):
  self.put(0xa3d298,mode);self.u.mem_write(HOUSES[0]+0x134,bytes([a,b]))
  self.checked_call(0x4f52f0,ecx=HOUSES[0],inputs=[*RANGES.items(),(0xa3d298,4),(HOUSES[0],0x6000)])
  return [str(self.u.reg_read(UC_X86_REG_EAX)&255)]
 def queue(self,current,queued,a4,requested):
  u=self.u;u.mem_write(ACTOR,b'\xa5'*0x1000);self.put(ACTOR+0x98,current);self.put(ACTOR+0xa0,queued);u.mem_write(ACTOR+0xa4,bytes([a4]));self.events=[];before=bytes(u.mem_read(ACTOR,0x1000))
  def stores(u,access,p,n,v,ctx):
   if ACTOR+0xa0<=p<ACTOR+0xa5:
    assert (p,n) in ((ACTOR+0xa0,4),(ACTOR+0xa4,1));self.event('W',0,p-ACTOR,v&0xffffffff);self.selected_stores+=1
  hook=u.hook_add(UC_HOOK_MEM_WRITE,stores)
  try:self.checked_call(0x594cb0,[requested,0],ACTOR,writes=[(ACTOR+0xa0,5)],inputs=list(RANGES.items()))
  finally:u.hook_del(hook)
  after=bytearray(u.mem_read(ACTOR,0x1000));after[0xa0:0xa5]=before[0xa0:0xa5];assert bytes(after)==before
  self.event('R',signed(words(u,ACTOR+0xa0,1)[0]),u.mem_read(ACTOR+0xa4,1)[0]);return self.events
