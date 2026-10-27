# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete nonzero radar with actual map, actors, Houses and schemes."""
from original_radar_map_pixels import RadarMapPixelsOracle
from original_surface_radar_pixel import ARENA,ACTORS,TYPES,HOUSES,SCHEME,STOP,signed
from verify_radar_actor_pixels import verify,RANGES
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_ESI
ACTORVT=[ARENA+0x70000,ARENA+0x70400];SCHEMES=[SCHEME,ARENA+0x71400,ARENA+0x71800];REGISTRIES=[ARENA+0x71000,ARENA+0x71100];NAMES=ARENA+0x72000
class RadarActorPixelsOracle(RadarMapPixelsOracle):
 def __init__(self,exe):verify(exe.read_bytes());super().__init__(exe)
 def cid(self,p):return SCHEMES.index(p)
 def checked_call(self,root,args=(),ecx=0,**kw):
  mode,control,pattern,mask,indexPattern,mutation,resolverPattern,at,resolverMask=self.actorFixture
  for k,v in ((0xa3d298,mode),(0xab6efc,REGISTRIES[0]),(0xab6f08,3),(0xb2b098,0)):self.globals[k]=v&0xffffffff;self.put(k,v)
  for i,vt in enumerate(ACTORVT):
   for off,v in ((0x3c,0x6c7430),(0x80,0x6c12c0),(0x84,0x453c60 if i else 0x506950),(0xc0,0x41b410),(0xcc,0x41b2e0 if i else 0x509270)):self.change(vt+off,v)
  for i,p in enumerate(ACTORS):
   kind=int(pattern==1 or pattern>=2 and (i+pattern)&1)
   for off,v in ((0,ACTORVT[kind]),(0x170,255 if self.f[17]>>i&1 else 0),(0x410,0 if self.f[18]<0 else HOUSES[self.f[18]]),(0x418 if kind else 0x5a8,TYPES+i*0x400)):self.change(p+off,v)
  indexes=((0,1,2),(-1,31,32),(7,7,7),(-2**31,2**31-1,-1))[indexPattern]
  for i,p in enumerate(HOUSES):
   for off,v in ((0x30,indexes[i]),(0x5674,mask)):self.change(p+off,v)
   for off,value in ((0x134,self.f[14]>>i&1),(0x135,control>>i&1)):
    self.u.mem_write(p+off,bytes([value]));self.expected[p+off-ARENA]=value
  for r,items in zip(REGISTRIES,((0,1,2),(2,1,0))):
   for i,v in enumerate(items):self.change(r+4*i,SCHEMES[v])
  for i,p in enumerate(SCHEMES):
   name=b'Other' if i==1 and resolverPattern else b'LightGrey';raw=name+b'\0';self.u.mem_write(NAMES+i*0x100,raw);self.expected[NAMES+i*0x100-ARENA:NAMES+i*0x100-ARENA+len(raw)]=raw
   for off,v in ((0x304,NAMES+i*0x100),(0x310,0 if i==0 else 1),(0x330,(0x1234,0x2345,0x3456)[i])):self.change(p+off,v)
  self.u.mem_write(NAMES+0x300,b'Other\0');self.expected[NAMES+0x300-ARENA:NAMES+0x306-ARENA]=b'Other\0'
  kw['inputs']=[*kw.get('inputs',()),*RANGES.items()];super().checked_call(root,args,ecx,**kw)
 def resolver_mutate(self,stage,index):
  mask=self.actorFixture[8];bits=mask&7 if stage==1 else mask>>3&7
  if self.resolverChanged or not bits or index!=self.actorFixture[7]:return
  self.resolverChanged=True
  if bits&1:self.change(0xab6efc,REGISTRIES[1])
  if bits&2:self.change(SCHEMES[1]+0x310,-1)
  if bits&4:self.change(SCHEMES[1]+0x304,NAMES+0x300)
 def code(self,u,a,n,ctx):
  if not self.active or a==STOP:return
  sp=u.reg_read(UC_X86_REG_ESP);ecx=u.reg_read(UC_X86_REG_ECX)
  if a in self.actorPending:
   kind,who,arg=self.actorPending.pop(a);value=u.reg_read(UC_X86_REG_EAX)
   if kind=='T':self.emit('T',who);self.mutate(6)
   elif kind=='L':self.emit('L',who,value&255);self.mutate(5)
   elif kind=='A':self.emit('A',who,arg,value&255);self.mutate(7)
   elif kind=='C':self.emit('C',who,value&255);self.mutate(8)
   elif kind=='O':self.emit('O',who,self.hid(value));self.mutate(9)
   elif kind=='S':self.emit('r',self.cid(value),'S');self.mutate(10)
  if a==0x6c12c0:self.actorPending[self.word(sp)]=('T',self.aid(ecx),0)
  elif a==0x4f52b0:self.actorPending[self.word(sp)]=('L',self.hid(ecx),0)
  elif a==0x4e5580:self.actorPending[self.word(sp)]=('A',self.hid(ecx),self.aid(self.word(sp+4)))
  elif a==0x41b410:self.actorPending[self.word(sp)]=('C',self.aid(ecx),0)
  elif a in (0x509270,0x41b2e0):self.radarActor=ecx;self.actorPending[self.word(sp)]=('O',self.aid(ecx),self.word(sp+4));assert self.word(sp+4)==0
  elif a==0x4e5540:self.savedAlliance=(ecx,self.word(sp+4))
  elif a==0x509284:
   self.emit('j',self.aid(self.radarActor),self.hid(self.savedAlliance[0]),self.hid(self.savedAlliance[1]),u.reg_read(UC_X86_REG_EAX)&255);m=self.actorFixture[5]
   if m and not self.radarChanged:
    self.radarChanged=True
    if m&1:self.change(self.radarActor+0x1b4,HOUSES[2])
    if m&2:self.change(0xa35db4,HOUSES[2])
    if m&4:self.change(self.radarActor+0x410,HOUSES[2])
    if m&8:self.change(HOUSES[2]+0x30,-1);self.change(HOUSES[0]+0x5674,self.word(HOUSES[0]+0x5674)^0xffffffff)
  if a==0x663d30:self.actorPending[self.word(sp)]=('S',0,0)
  elif a==0x663d4a:self.savedScheme=u.reg_read(UC_X86_REG_EAX)
  elif a==0x663d57:
   i=u.reg_read(UC_X86_REG_ESI);self.emit('q',i,self.cid(self.savedScheme),signed(u.reg_read(UC_X86_REG_EAX)));self.resolver_mutate(1,i)
  elif a==0x663d66:self.savedCategoryScheme=self.word(u.reg_read(UC_X86_REG_EAX)+u.reg_read(UC_X86_REG_ESI)*4);self.savedCategory=self.word(self.savedCategoryScheme+0x310)
  elif a==0x663d6c:
   i=u.reg_read(UC_X86_REG_ESI);self.emit('v',i,self.cid(self.savedCategoryScheme),signed(self.savedCategory));self.resolver_mutate(2,i)
  if any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()):
   assert a!=0x781f73
   if a in RANGES:self.counts[hex(a)]+=1
   return
  super().code(u,a,n,ctx)
 def run(self,f):
  self.actorFixture=f[51:];self.actorPending={};self.radarChanged=False;self.resolverChanged=False;super().run(f[:51]);assert not self.actorPending
  self.emit('X',signed(self.word(0xa3d298)),int(self.radarChanged),int(self.resolverChanged),int(self.word(0xab6efc)==REGISTRIES[1]));pattern=self.actorFixture[2]
  for i,p in enumerate(ACTORS):self.emit(int(pattern==1 or pattern>=2 and (i+pattern)&1),self.word(p+0x170)&255,self.hid(self.word(p+0x410)))
  for p in HOUSES:self.emit(signed(self.word(p+0x30)),self.word(p+0x5674),*self.u.mem_read(p+0x134,2))
  for p in SCHEMES:self.emit(int(bytes(self.u.mem_read(self.word(p+0x304),10))==b'LightGrey\0'),signed(self.word(p+0x310)),self.word(p+0x330))
  return self.trace
