# SPDX-License-Identifier: GPL-3.0-or-later
"""Execute actual Infantry dispatch through unchanged complete Mark roots."""
from original_unit_mark import UnitMarkOracle,ARENA,ACTOR,TYPE,HOUSE,LOCO,TACTICAL,MAP,SERVICES
from original_presentation import STACK,STOP
from verify_infantry_mark import verify,RANGES,DISPATCH
from unicorn import UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX

class InfantryMarkOracle(UnitMarkOracle):
 def __init__(self,exe):
  inspection=verify(exe.read_bytes());super().__init__(exe)
  self.inspection=inspection;self.entries={hex(a):0 for a in RANGES}
 def block(self,u,a,n,ctx):
  if a not in (STOP,*SERVICES) and not any(p<=a and a+n<=p+size for p,size in RANGES.items()):
   raise AssertionError(f'Uninspected Infantry Mark block {a:#x}/{n}')
 def observe(self,u,a,n,ctx):
  if self.active and a in (0x509800,0x506950,0x71faa0):self.entries[hex(a)]+=1
  super().observe(u,a,n,ctx)
 def run_infantry_mark(self,header,rows):
  root,present,image,owner,tp,mm,counter,tactical,marked,redraw=header
  # Actor, InfantryType, House, Walk interface and Tactical have distinct
  # supplied storage. Never replace the actual vtable or execute lifted code.
  self.u.mem_write(ARENA,b'\xa5'*0x10000);self.put(ACTOR,0x7a3540)
  self.put(ACTOR+0x5a8,TYPE if present else 0)
  self.put(ACTOR+0x1b4,HOUSE);self.put(ACTOR+0x564,LOCO);self.put(LOCO,0x7aead8)
  self.put(TYPE+0x598,image);self.put(HOUSE+0x30,owner)
  self.u.mem_write(ACTOR+0x74,bytes([marked,redraw]));self.u.mem_write(TACTICAL+0xd7d,bytes([tactical]))
  self.put(0x83996c,TACTICAL if tp else 0);self.put(MAP+0xc,mm);self.u.mem_write(MAP+0x1154,bytes([counter]));self.events=[]
  for mode,x,y,z,limbo,special,reset in rows:
   self.u.mem_write(ACTOR+0x88,b''.join((n&0xffffffff).to_bytes(4,'little') for n in (x,y,z)))
   self.u.mem_write(ACTOR+0x76,bytes([limbo]));self.u.mem_write(ACTOR+0x370,bytes([special]))
   if reset>=0:self.u.mem_write(ACTOR+0x75,bytes([reset]))
   before=bytes(self.u.mem_read(ARENA,0x10000))
   def stores(u,access,p,n,value,ctx):
    assert p in (ACTOR+0x74,ACTOR+0x75,TACTICAL+0xd7d) or STACK-0x2000<=p<STACK+8,(hex(p),n)
    if p in (ACTOR+0x74,ACTOR+0x75):
     assert n==1;self.event('W',p-ACTOR,value&255);self.stores+=1
    elif p==TACTICAL+0xd7d:
     assert n==1;self.event('T',value&255);self.stores+=1
   writes=[(ACTOR+0x74,2),(TACTICAL+0xd7d,1)]
   inputs=[*RANGES.items(),(0x40dc4c,23),*[(p,4) for p in DISPATCH],
    (MAP+0xc,4),(MAP+0x1154,1),(0x83996c,4)]
   hook=self.u.hook_add(UC_HOOK_MEM_WRITE,stores);self.active=True
   try:self.checked_call((0x5d4160,0x6c2550,0x4c2e60)[root],[mode],ACTOR,writes=writes,inputs=inputs)
   finally:self.active=False;self.u.hook_del(hook)
   after=bytearray(self.u.mem_read(ARENA,0x10000))
   for p,n in writes:k=p-ARENA;after[k:k+n]=before[k:k+n]
   assert bytes(after)==before,'Infantry Mark changed remaining actor/type/House/Walk/Tactical arena'
   self.event('S',self.u.reg_read(UC_X86_REG_EAX)&255,*self.u.mem_read(ACTOR+0x74,3),special,
    self.u.mem_read(TACTICAL+0xd7d,1)[0],mm,counter)
  return self.events
