# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete Unit Mark/membership with actual occupied resident Cell recalculation."""
import struct
from original_unit_membership_discovery import UnitMembershipDiscoveryOracle
from original_unit_membership import ACTOR,CELLS,SERVICES
from original_map_floor_height import MAP,FALLBACK
from original_unit_discovery import shorts
from original_foot_lit import words,signed
from original_presentation import STOP
from verify_occupied_cell import verify,RANGES
from verify_unit_discovery import RANGES as PREVIOUS
from verify_map_cell_children import LAT_GLOBALS
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_ECX
TYPES=0x2800000;BUFF4=0x2900000;BUFF10=BUFF4+0x40000
FIELDS={0x38:4,0xec:4,0x11a:1,0x11b:1,0x11c:1,0x11d:1,0x4c:4}
class OccupiedMembershipOracle(UnitMembershipDiscoveryOracle):
 def __init__(self,exe):
  super().__init__(exe);self.inspection=verify(exe.read_bytes());self.u.mem_map(TYPES,0x10000);self.u.mem_map(BUFF4,0x100000)
  self.entries.update({hex(a):0 for a in RANGES if a not in PREVIOUS});self.in_pass=False;self.pass_kind_calls=0;self.recalculations=0
  self.u.hook_add(UC_HOOK_CODE,self.observe_cell)
 def block(self,u,a,n,ctx):
  if a not in (STOP,*SERVICES) and not any(p<=a and a+n<=p+s for p,s in RANGES.items()):raise AssertionError(f'Uninspected occupied membership block {a:#x}/{n}')
 def membership_service(self,u,a,sp,ecx):
  if a==0x472540:
   assert words(u,sp+4,1)==[0xffffffff];self.event('R',self.cell(ecx),-1);self.recalculations+=1;return True
  return super().membership_service(u,a,sp,ecx)
 def observe_cell(self,u,a,n,ctx):
  if a in RANGES and a not in PREVIOUS:self.entries[hex(a)]+=1
  if not self.active:return
  ecx=u.reg_read(UC_X86_REG_ECX)
  if a==0x478f40:self.in_pass=True;self.event('p',self.cell(ecx))
  elif a==0x471d10:self.event('l',self.cell(ecx))
  elif a==0x70a2d0 and self.in_pass:self.event('k',self.actor(ecx),1);self.pass_kind_calls+=1
  if 0x478f40<=a<0x4790e9 and bytes(u.mem_read(a,1))==b'\xc3':self.in_pass=False
 def configure_membership(self):
  super().configure_membership();u=self.u;u.mem_write(TYPES,bytes(0x10000));u.mem_write(BUFF4,b'\xa5'*0x100000)
  self.put(MAP+0x64,BUFF4);self.put(MAP+0x68,65536);self.put(MAP+0x6c,BUFF10)
  for off,v in zip((0xf0,0xf4,0xf8,0xfc,0x100,0x104),(80,85,0,0,80,85)):self.put(MAP+off,v)
  self.put(0xa40cd4,TYPES);self.put(0xa40ce0,3);self.put(0x8661d8,1);self.put(0x839848,TYPES+0x8000)
  u.mem_write(0x7de4ec,struct.pack('<16i',*range(16)))
  for p in LAT_GLOBALS:self.put(p,-1)
  for i in range(11):self.put(0x850ea8+i*36,0x3f800000)
  self.indices=[]
  for i,(cp,profile) in enumerate(zip(CELLS,self.prepared)):
   tile,land,sub,extra,present,valid,tmp_land,height=profile
   self.put(cp+0x38,tile);self.put(cp+0xec,land);u.mem_write(cp+0x116,b'\0\0');u.mem_write(cp+0x11a,bytes([sub]));u.mem_write(cp+0x11d,bytes([extra]));u.mem_write(cp+0x119,b'\0');self.put(cp+0x44,-1);self.put(cp+0x4c,17)
   if i<3:
    t=TYPES+0x1000+i*0x1000;image=t+0x500;section=t+0x600;self.put(TYPES+i*4,t);self.put(t,0x7a51a8);self.put(t+0x298,-1);self.put(t+0xa4,image if present else 0)
    u.mem_write(image,struct.pack('<5I',1,1,60,height&0xffffffff,section if valid else 0));u.mem_write(section+0x29,bytes([tmp_land,u.mem_read(cp+0x11c,1)[0]]))
   x,y=shorts(u,cp+0x24);self.indices.append(max(0,min(65535,y*166+x)))
  self.buffer_before=bytes(u.mem_read(BUFF4,0x100000))
 def membership_inputs(self):return [*super().membership_inputs(),*RANGES.items(),(TYPES,0x10000),(MAP+0x64,12),(MAP+0xf0,24),(0xa40cd4,4),(0xa40ce0,4),(0x8661d8,4),(0x839848,4),(0x7de4ec,64),(0x850ea8,396),*[(p,4) for p in LAT_GLOBALS]]
 def membership_writes(self):return [*super().membership_writes(),*[(p+off,n) for p in CELLS[:3] for off,n in FIELDS.items()],(BUFF4,0x100000)]
 def membership_store(self,u,p,n,v):
  super().membership_store(u,p,n,v)
  for i,cp in enumerate(CELLS):
   for off,size in FIELDS.items():
    if cp+off<=p<cp+off+size:assert p==cp+off and n==size;self.event('a',i,off,v&((1<<(8*n))-1));self.selected_stores+=1
  for i,index in enumerate(self.indices[:3]):
   if BUFF4+index*4<=p<BUFF4+index*4+4:
    assert n==1 and p-(BUFF4+index*4) in (0,1);self.event('b',i,p-(BUFF4+index*4),v&255);self.selected_stores+=1
   elif BUFF10+index*10<=p<BUFF10+index*10+10:
    assert n==1 and p-(BUFF10+index*10)==8;self.event('c',i,8,v&255);self.selected_stores+=1
 def membership_result(self):
  super().membership_result();u=self.u
  for i,p in enumerate(CELLS):
   vals=[words(u,p+0x38,1)[0],signed(words(u,p+0xec,1)[0]),u.mem_read(p+0x11a,1)[0],int.from_bytes(u.mem_read(p+0x11b,1),'little',signed=True),u.mem_read(p+0x11c,1)[0],u.mem_read(p+0x11d,1)[0],signed(words(u,p+0x4c,1)[0])]
   self.event('Y',*vals,*u.mem_read(BUFF4+self.indices[i]*4,4),*u.mem_read(BUFF10+self.indices[i]*10,10))
  after=bytearray(u.mem_read(BUFF4,0x100000))
  for index in self.indices[:3]:
   for p,n in ((BUFF4+index*4,2),(BUFF10+index*10+8,1)):after[p-BUFF4:p-BUFF4+n]=self.buffer_before[p-BUFF4:p-BUFF4+n]
  assert bytes(after)==self.buffer_before,'Occupied membership buffer capacity or unselected byte changed'
 def run_occupied(self,prepared,*args):
  self.prepared=prepared;return self.run_joined(*args)
