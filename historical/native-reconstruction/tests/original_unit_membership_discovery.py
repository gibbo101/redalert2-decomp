# SPDX-License-Identifier: GPL-3.0-or-later
"""Actual visibility/discovery nested in complete Unit Mark and membership."""
from original_unit_membership import UnitMembershipOracle,ACTOR,CELLS,SERVICES
from original_map_floor_height import FALLBACK,MAP
from original_unit_discovery import UnitDiscoveryOracle,HOUSES,house_ptr,house_id,shorts
from original_foot_lit import words,signed
from original_presentation import STOP
from verify_unit_discovery import verify,RANGES,NUMERIC,OUTPUTS,COMPLETE,DISPATCH
from verify_unit_membership import RANGES as MEMBERSHIP
from verify_ramp_geometry import CONSTANTS,TABLES
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_ECX,UC_X86_REG_ESP
class UnitMembershipDiscoveryOracle(UnitMembershipOracle):
 def __init__(self,exe):
  super().__init__(exe);self.inspection=verify(exe.read_bytes());self.u.mem_map(HOUSES[0],0x12000)
  self.entries.update({hex(a):0 for a in RANGES if a not in MEMBERSHIP})
  self.inputs=list(RANGES.items())+[(p,8) for p in CONSTANTS]+list(TABLES.items())+[(0xb2af94,4)]
  self.put(0xb2af94,0);self.u.hook_add(UC_HOOK_CODE,self.observe_discovery)
  self.stock=UnitDiscoveryOracle.stock_visibility(self,0)
 def block(self,u,a,n,ctx):
  if a not in (STOP,*SERVICES) and not any(p<=a and a+n<=p+size for p,size in RANGES.items()):raise AssertionError(f'Uninspected joined discovery block {a:#x}/{n}')
 def observe_discovery(self,u,a,n,ctx):
  if a in RANGES and a not in MEMBERSHIP:self.entries[hex(a)]+=1
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
 def membership_service(self,u,a,sp,ecx):
  if a in (0x568140,0x5683c0):
   self.service_counts[hex(a)]+=1
   from original_foot_lit import ints
   self.event('V',int(a==0x5683c0),*ints(u,words(u,sp+4,1)[0],3));return True
  if a==0x6c2440:
   self.service_counts[hex(a)]+=1;self.event('N',self.actor(ecx),house_id(words(u,sp+4,1)[0]));return True
  return False
 def configure_membership(self):
  f=self.joined;u=self.u
  for cp,flags in zip(CELLS,f[:4]):self.put(cp+0x12c,flags)
  self.u.mem_write(HOUSES[0],b'\0'*0xc000)
  for i,p in enumerate(HOUSES):u.mem_write(p+0x134,bytes(f[4+i*2:6+i*2]))
  current=self.current;self.put(0xa35db4,house_ptr(current));u.mem_write(HOUSES[current]+0x13d,bytes([f[8]]));self.put(0xa3d548,f[9])
  self.put(ACTOR+0x1b4,house_ptr(f[10]));self.put(ACTOR+0x98,f[11]);self.put(ACTOR+0xa0,f[12]);u.mem_write(ACTOR+0xa4,b'\xff');u.mem_write(ACTOR+0x372,bytes(f[13:16]));self.put(ACTOR+0x34,0);self.put(0xa40774,1)
  self.house_before=bytes(u.mem_read(HOUSES[0],0xc000))
 def membership_writes(self):return [(ACTOR+0x373,2),(ACTOR+0xa0,4),(ACTOR+0xa4,1),*[(p+off,n) for p in HOUSES for off,n in ((0x13c,1),(0x5668,2))]]
 def membership_inputs(self):return [*RANGES.items(),*[(p,4) for p in DISPATCH],(0x851a70,32),(0xa6fc30,4),(0xa3d548,4),(0xa40774,4)]
 def membership_store(self,u,p,n,v):
  if ACTOR+0x373<=p<ACTOR+0x375 or p==ACTOR+0xa4:assert n==1;self.event('w',0,p-ACTOR,v&255);self.selected_stores+=1
  elif ACTOR+0xa0<=p<ACTOR+0xa4:assert p==ACTOR+0xa0 and n==4;self.event('w',0,0xa0,v&0xffffffff);self.selected_stores+=1
  for i,hp in enumerate(HOUSES):
   if p==hp+0x13c or hp+0x5668<=p<hp+0x566a:assert n==1;self.event('w',i+1,p-hp,v&255);self.selected_stores+=1
 def membership_result(self):
  u=self.u;self.event('X',*u.mem_read(ACTOR+0x373,2),signed(words(u,ACTOR+0xa0,1)[0]),u.mem_read(ACTOR+0xa4,1)[0])
  for p in HOUSES:self.event(u.mem_read(p+0x13c,1)[0],*u.mem_read(p+0x5668,2))
  after=bytearray(u.mem_read(HOUSES[0],0xc000))
  for p,n in self.membership_writes():
   if HOUSES[0]<=p and p+n<=HOUSES[0]+0xc000:after[p-HOUSES[0]:p-HOUSES[0]+n]=self.house_before[p-HOUSES[0]:p-HOUSES[0]+n]
  assert bytes(after)==self.house_before,'Joined discovery changed unselected House storage'
 def run_joined(self,f,h,records,links,planes,rows):
  self.joined=f;self.current=h[6];assert self.current in (0,1) and h[8]==0
  return self.run_membership(h,records,links,planes,rows)
