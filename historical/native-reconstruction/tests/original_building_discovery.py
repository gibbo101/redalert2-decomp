# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete unmodified Building discovery with explicit activation leaf."""
from original_unit_discovery import UnitDiscoveryOracle,ACTOR,HOUSES,TAG,house_ptr,house_id
from original_map_floor_height import CELL
from original_presentation import STOP
from original_foot_lit import words,ret,signed
from verify_building_discovery import verify,RANGES,DISPATCH
from unicorn import UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EAX
TYPE=0x2611000
class BuildingDiscoveryOracle(UnitDiscoveryOracle):
 def __init__(self,exe):
  super().__init__(exe);self.inspection=verify(exe.read_bytes());self.building=False;self.counts={'root':0,'radio':0,'activation':0}
 def block(self,u,a,n,ctx):
  if a not in (STOP,0x6b3df0,0x4426d0) and not any(p<=a and a+n<=p+size for p,size in RANGES.items()):raise AssertionError(f'Uninspected Building block {a:#x}/{n}')
 def observe(self,u,a,n,ctx):
  super().observe(u,a,n,ctx)
  if not self.active:return
  if a==0x448fe0:self.counts['root']+=1
  elif a==0x636f10:self.event('r');self.counts['radio']+=1
  elif a==0x4426d0:
   assert u.reg_read(UC_X86_REG_ECX)==ACTOR and words(u,u.reg_read(UC_X86_REG_ESP)+4,1)==[0]
   self.event('a',0);self.counts['activation']+=1;ret(u,4,0)
 def checked_call(self,address,*args,**kwargs):
  if address!=0x6c2440 or not self.building:return super().checked_call(address,*args,**kwargs)
  def stores(u,access,p,n,v,ctx):
   for i,h in enumerate(HOUSES):
    for off,size in ((0x1b4,4),(0x18d,1),(0x144,1)):
     if p==h+off:assert n==size;self.event('W',i+1,off,v&0xffffffff)
  hook=self.u.hook_add(UC_HOOK_MEM_WRITE,stores)
  try:return super().checked_call(0x448fe0,*args,**dict(kwargs,writes=kwargs['writes'],inputs=kwargs['inputs']+[(TYPE,0x1000),(0x448fe0,0xce),(0x636f10,0x25),*[(0x79cbbc+o,4) for o in DISPATCH]]))
  finally:self.u.hook_del(hook)
 def run(self,f):
  self.type_index,self.radio_count,self.links=f['type'],f['count'],f['links'];self.building=True
  # Whole-arena accounting includes the wrapper's actual House stores.
  return self.discovery(f['header'],f['houses'],f['discoverers'])
 def discovery(self,h,houses,discoverers):
  mode,loading,self.context,current,owner,b372,b373,b374,mission,queued,a4,tag,self.mutation=h;u=self.u;self.events=[]
  u.mem_write(CELL,b'\xa5'*0x10000);u.mem_write(HOUSES[0],b'\xa5'*0xc000)
  self.put(ACTOR,0x79cbbc);self.put(ACTOR+0x1b4,house_ptr(owner));self.put(ACTOR+0x34,TAG if tag else 0)
  u.mem_write(ACTOR+0x372,bytes([b372,b373,b374]));self.put(ACTOR+0x98,mission);self.put(ACTOR+0xa0,queued);u.mem_write(ACTOR+0xa4,bytes([a4]))
  self.put(0xa3d298,mode);self.put(0xa40774,loading);self.put(0xac0148,self.context);self.put(0xa35db4,house_ptr(current))
  for p,values in zip(HOUSES,houses):
   for off,v in zip((0x134,0x135,0x13c,0x13d,0x5668,0x5669),values):u.mem_write(p+off,bytes([v]))
  self.put(ACTOR+0x418,TYPE);self.put(TYPE+0xb90,self.type_index)
  self.put(ACTOR+0xcc,ACTOR+0x900);self.put(ACTOR+0xd0,self.radio_count)
  for i,v in enumerate(self.links):self.put(ACTOR+0x900+4*i,v)
  for p in HOUSES:
   self.put(p+0x1b4,-1);u.mem_write(p+0x18d,b'\x7f');u.mem_write(p+0x144,b'\xff')
  writes=[(p+off,n) for p in HOUSES for off,n in ((0x1b4,4),(0x18d,1),(0x144,1))]
  writes_base=[(ACTOR+0x373,2),(ACTOR+0xa0,4),(ACTOR+0xa4,1),*[(p+off,n) for p in HOUSES for off,n in ((0x13c,1),(0x5668,2))]]
  writes+=writes_base
  if self.mutation:writes.append((ACTOR+0x1b4,4))
  def stores(u,access,p,n,v,ctx):
   if ACTOR+0x373<=p<ACTOR+0x375 or p==ACTOR+0xa4:assert n==1;self.event('W',0,p-ACTOR,v&255);self.selected_stores+=1
   elif ACTOR+0xa0<=p<ACTOR+0xa4:assert p==ACTOR+0xa0 and n==4;self.event('W',0,0xa0,v&0xffffffff);self.selected_stores+=1
   for i,hp in enumerate(HOUSES):
    if p==hp+0x13c or hp+0x5668<=p<hp+0x566a:assert n==1;self.event('W',i+1,p-hp,v&255);self.selected_stores+=1
  for discoverer in discoverers:
   arena=bytes(u.mem_read(CELL,0x10000));hs=bytes(u.mem_read(HOUSES[0],0xc000));hook=u.hook_add(UC_HOOK_MEM_WRITE,stores);self.active=True
   try:self.checked_call(0x6c2440,[house_ptr(discoverer)],ACTOR,writes=writes,inputs=[*RANGES.items(),*[(0x79cbbc+p,4) for p in DISPATCH],(0xa3d298,4),(0xa40774,4),(0xac0148,4),(0xa35db4,4)])
   finally:self.active=False;u.hook_del(hook)
   for base,size,before in ((CELL,0x10000,arena),(HOUSES[0],0xc000,hs)):
    after=bytearray(u.mem_read(base,size))
    for p,n in writes:
     if base<=p and p+n<=base+size:after[p-base:p-base+n]=before[p-base:p-base+n]
    assert bytes(after)==before,'Discovery changed unselected storage'
   self.event('R',u.reg_read(UC_X86_REG_EAX)&255,house_id(words(u,ACTOR+0x1b4,1)[0]),*u.mem_read(ACTOR+0x373,2),signed(words(u,ACTOR+0xa0,1)[0]),u.mem_read(ACTOR+0xa4,1)[0])
   for p in HOUSES:self.event(u.mem_read(p+0x13c,1)[0],*u.mem_read(p+0x5668,2))
   for p in HOUSES:self.event('B',signed(words(u,p+0x1b4,1)[0]),u.mem_read(p+0x18d,1)[0],u.mem_read(p+0x144,1)[0])
  return self.events
