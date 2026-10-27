# SPDX-License-Identifier: GPL-3.0-or-later
"""Unmodified Infantry Mark/map/Cell/subcell occupation on distinct actual owners."""
import hashlib,struct
from original_map_floor_height import MapFloorHeightOracle,CELL,INPUT,SLOTS,FALLBACK,MAP,PLANES,packed
from original_presentation import STOP
from original_foot_lit import words,ints,ret,signed
from verify_infantry_membership import verify,RANGES,COMPLETE,DISPATCH
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EAX
ACTOR=CELL+0x2000;TYPE=CELL+0x6000;LOCO=CELL+0x8000;HOUSE=CELL+0x9000;TACTICAL=CELL+0xa000
CELLS=[CELL,CELL+0x400,CELL+0x800,FALLBACK]
SERVICES={0x568140:4,0x5683c0:4,0x6c2440:4,0x472540:4,0x78298a:0}
GLOBALS={0xa72f0c:(0,1),0xa72f18:(4,4),0xa411a0:(8,1),0xa4117c:(12,4),0xa41180:(16,4)}
class InfantryMembershipOracle(MapFloorHeightOracle):
 def __init__(self,exe):
  super().__init__(exe);self.inspection=verify(exe.read_bytes());self.active=False
  self.floor_ranges=set(__import__('verify_map_floor_height').RANGES)
  self.entries.update({hex(a):0 for a in RANGES});self.selected_stores=0;self.service_counts={hex(a):0 for a in SERVICES}
  self.u.hook_add(UC_HOOK_CODE,self.observe)
 def block(self,u,a,n,ctx):
  if a not in (STOP,*SERVICES) and not any(p<=a and a+n<=p+size for p,size in RANGES.items()):raise AssertionError(f'Uninspected Infantry membership block {a:#x}/{n}')
 def event(self,*v):self.events.extend(map(str,v))
 def actor(self,p):
  if not p:return -1
  assert ACTOR<=p<ACTOR+0x4000 and (p-ACTOR)%0x1000==0,hex(p)
  return (p-ACTOR)//0x1000
 def cell(self,p):return CELLS.index(p)
 def configure_membership(self):pass
 def membership_writes(self):return []
 def membership_inputs(self):return []
 def membership_store(self,u,p,n,v):pass
 def membership_result(self):pass
 def membership_service(self,u,a,sp,ecx):return False
 def observe(self,u,a,n,ctx):
  if not self.active:return
  if a in RANGES and a not in self.floor_ranges:self.entries[hex(a)]+=1
  sp=u.reg_read(UC_X86_REG_ESP);ecx=u.reg_read(UC_X86_REG_ECX)
  if self.membership_service(u,a,sp,ecx):return
  if a in SERVICES:
   self.service_counts[hex(a)]+=1;args=words(u,sp+4,1)
   if a==0x78298a:
    self.event('A',(0x5d44f0,0x50a060).index(args[0]),0);value=0
   elif a in (0x568140,0x5683c0):
    assert ecx==MAP;selector=int(a==0x5683c0);self.event('V',selector,*ints(u,args[0],3));value=self.visibility[selector]
   elif a==0x6c2440:
    self.event('N',self.actor(ecx),signed(args[0]));value=0
    if self.mutation:
     self.event('Z',self.mutation)
     if self.mutation&1:
      x,y,z=ints(u,ACTOR+0x88,3);u.mem_write(ACTOR+0x88,packed([x+512,y,z+37]));u.mem_write(ACTOR+0x5a0,bytes([0 if u.mem_read(ACTOR+0x5a0,1)[0] else 255]))
     if self.mutation&6:self.put(SLOTS+(72*512+51)*4,0 if self.mutation&4 else CELLS[2])
   else:self.event('R',self.cell(ecx),signed(args[0]));assert args==[0xffffffff];value=0
   ret(u,SERVICES[a],value);return
  if a in (0x54ab70,0x54af70):self.event('M',int(a==0x54ab70),self.actor(words(u,sp+8,1)[0]))
  elif a in (0x473b30,0x473d20):self.event('C',int(a==0x473b30),self.cell(ecx))
  elif a==0x5d4470:self.event('F',0,0)
  elif a==0x50a000:self.event('U',0,0)
  elif a==0x482e10:self.event('B',32,0)
 def run_membership(self,h,records,links,planes,rows):
  of,uf,tf,gate,v1,v2,param,threshold,self.mutation=h;self.visibility=(v1,v2)
  u=self.u
  self.u.mem_write(CELL,b'\xa5'*0x10000);self.u.mem_write(FALLBACK,b'\xa5'*0x148);self.u.mem_write(SLOTS,bytes(0x100000))
  self.put(MAP+0x138,SLOTS);self.put(MAP+0x13c,262144);self.put(0xa3d298,gate);self.put(0xa35db4,param);self.put(0xad057c,threshold)
  self.u.mem_write(0x850bb8,b'\0');self.u.mem_write(0x850ba8,struct.pack('<d',0));self.u.mem_write(0x850bd0,struct.pack('<d',0));self.u.mem_write(PLANES,struct.pack('<100Q',*planes));self.put(0x850c40,104)
  for p,flag in ((0xa72f0c,of),(0xa411a0,uf)):self.u.mem_write(p,bytes([flag]))
  self.put(0xa72f18,0x7fff7fff if of&1 else 0xa5a5a5a5);self.put(0xa4117c,0 if uf&1 else 0xa5a5a5a5);self.put(0xa41180,0x7fff7fff if uf&1 else 0xa5a5a5a5)
  for i,(p,rec) in enumerate(zip(CELLS,records)):
   level,ramp,flags,g,e,head,alt=rec;self.u.mem_write(p+0x11b,bytes([level&255,ramp]));self.put(p+0x140,flags);self.put(p+0x124,g);self.put(p+0x128,e);self.put(p+0x54,0xffffffff);self.put(p+0x58,0xffffffff)
   self.put(p+0x24,((51+i)&65535)|(72<<16) if i<3 else ((-7)&65535)|(5<<16))
   for off,id in ((0xe4,head),(0xe8,alt)):self.put(p+off,0 if id==-1 else ACTOR+id*0x1000)
   if i<3:self.put(SLOTS+(72*512+51+i)*4,p)
  for i in range(4):
   p=ACTOR+i*0x1000;self.put(p,0x7a3540);self.put(p+0x30,0 if links[i]==-1 else ACTOR+links[i]*0x1000)
   self.put(p+0x5a8,TYPE);self.put(p+0x564,LOCO);self.put(p+0x1b4,HOUSE);self.u.mem_write(p+0x74,b'\0\0\0');self.u.mem_write(p+0x370,b'\0')
  self.put(TYPE,0x7a3a78);self.u.mem_write(TYPE+0x205,bytes([tf]));self.put(TYPE+0x598,17);self.put(LOCO,0x7aead8);self.put(HOUSE+0x30,0)
  self.put(0x83996c,TACTICAL);self.u.mem_write(TACTICAL+0xd7d,b'\0');self.put(MAP+0xc,2);self.u.mem_write(MAP+0x1154,b'\xff')
  self.configure_membership()
  self.events=[]
  for root,mode,actor,cell,x,y,z,alt,eligible in rows:
   self.u.mem_write(ACTOR+0x88,packed([x,y,z]));self.u.mem_write(ACTOR+0x79,bytes([alt]));self.u.mem_write(ACTOR+0x5a0,bytes([eligible]));self.u.mem_write(INPUT,struct.pack('<hh',*((int(n/256)+32768)%65536-32768 for n in (x,y))))
   before=bytes(self.u.mem_read(CELL,0x10000));fb=bytes(self.u.mem_read(FALLBACK,0x148))
   def stores(u,access,p,n,v,ctx):
    self.membership_store(u,p,n,v)
    for base,(_,width) in GLOBALS.items():
     if base<=p<base+width:assert p==base and n==width
    if p in GLOBALS:
     off,width=GLOBALS[p];assert n==width;self.event('W',200,off,n,v&((1<<(8*n))-1));self.selected_stores+=1
    for i,cp in enumerate(CELLS):
     if cp+0xe4<=p<cp+0xec:assert p in (cp+0xe4,cp+0xe8) and n==4
     if cp+0x124<=p<cp+0x12c:assert p in (cp+0x124,cp+0x128) and n==1
     if i==3 and cp+0x24<=p<cp+0x28:assert p==cp+0x24 and n==4
     if p in (cp+0xe4,cp+0xe8,cp+0x124,cp+0x128,cp+0x54,cp+0x58) or (i==3 and p==cp+0x24):
      assert n==(1 if p in (cp+0x124,cp+0x128) else 4);value=self.actor(v&0xffffffff) if p in (cp+0xe4,cp+0xe8) else v&0xffffffff
      self.event('W',100+i,p-cp,n,value);self.selected_stores+=1
    for i in range(4):
     ap=ACTOR+i*0x1000
     if ap+0x30<=p<ap+0x34:assert p==ap+0x30 and n==4
     if ap+0x74<=p<ap+0x76:assert n==1
     if p==ap+0x30:assert n==4;self.event('W',i,0x30,n,self.actor(v&0xffffffff));self.selected_stores+=1
     elif p in (ap+0x74,ap+0x75):assert n==1;self.event('W',i,p-ap,n,v&255);self.selected_stores+=1
    if p==TACTICAL+0xd7d:assert n==1;self.event('W',201,0,n,v&255);self.selected_stores+=1
   writes=[(p,n) for p,(_,n) in GLOBALS.items()]+[(0x850bb8,1),(0x850ba8,8),(0x850bd0,8),(PLANES,800),(FALLBACK+0x24,4),(TACTICAL+0xd7d,1)]
   for p in CELLS:writes.extend([(p+0xe4,8),(p+0x124,1),(p+0x128,1),(p+0x54,8)])
   for i in range(4):writes.extend([(ACTOR+i*0x1000+0x30,4),(ACTOR+i*0x1000+0x74,2)])
   if self.mutation&1:writes.extend([(ACTOR+0x88,12),(ACTOR+0x5a0,1)])
   slot=SLOTS+(72*512+51)*4
   if self.mutation&6:writes.append((slot,4))
   writes.extend(self.membership_writes())
   inputs=[*RANGES.items(),*[(p,4) for p in DISPATCH],(0x40dc4c,23),(0x817dfc,65536),(0x79a738,4),(0x79d578,8),*([(SLOTS,slot-SLOTS),(slot+4,SLOTS+0x100000-slot-4)] if self.mutation&6 else [(SLOTS,0x100000)]),(MAP+0x138,8),(0xad057c,4),(0xa3d298,4),(0xa35db4,4),(0x850c40,4),(0x83996c,4)]
   inputs.extend(self.membership_inputs())
   if root<2:a,args,ecx=(0x473b30,0x473d20)[root],[ACTOR if actor==0 else 0,alt],CELLS[cell]
   elif root<4:a,args,ecx=(0x54ab70,0x54af70)[root-2],[INPUT,ACTOR if actor==0 else 0],MAP
   else:a,args,ecx=0x4c2e60,[mode],ACTOR
   hook=self.u.hook_add(UC_HOOK_MEM_WRITE,stores);self.active=True
   try:self.checked_call(a,args,ecx,writes=writes,inputs=inputs)
   finally:self.active=False;self.u.hook_del(hook)
   after=bytearray(self.u.mem_read(CELL,0x10000))
   for p,n in writes:
    if CELL<=p and p+n<=CELL+0x10000:off=p-CELL;after[off:off+n]=before[off:off+n]
   assert bytes(after)==before,'Infantry membership arena changed outside selected fields'
   after=bytearray(self.u.mem_read(FALLBACK,0x148))
   for off,n in ((0x24,4),(0xe4,8),(0x124,1),(0x128,1),(0x54,8)):after[off:off+n]=fb[off:off+n]
   assert bytes(after)==fb,'Infantry membership fallback changed outside selected fields'
   self.event('S',u.reg_read(UC_X86_REG_EAX)&255 if root==4 else -1,*u.mem_read(ACTOR+0x74,2),u.mem_read(TACTICAL+0xd7d,1)[0])
   for cp in CELLS:self.event(*[self.actor(v) for v in words(u,cp+0xe4,2)],*words(u,cp+0x124,2),*ints(u,cp+0x54,2))
   self.event(*[self.actor(words(u,ACTOR+i*0x1000+0x30,1)[0]) for i in range(4)],hashlib.sha256(self.state()).hexdigest())
   self.membership_result()
  return self.events
