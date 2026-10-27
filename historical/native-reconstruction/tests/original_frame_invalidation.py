# SPDX-License-Identifier: GPL-3.0-or-later
"""Unmodified complete invalidation/cache/projection/dirty parents; explicit Type bounds/heap services."""
import struct
from original_redraw import RedrawOracle,ARENA,TACTICAL,SLOTS,GROWN,VECTOR
from original_presentation import STOP
from verify_frame_invalidation import verify,RANGES
from verify_redraw import RANGES as DIRTY_RANGES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_READ,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_ECX,UC_X86_REG_EAX,UC_X86_REG_ESP
ACTORS=[ARENA+0xa000+i*0x1000 for i in range(3)]
BACKINGS=[ARENA+0xd000,ARENA+0xd100];OUT=ARENA+0xe000;INPUT=OUT+0x100;VTABLE=OUT+0x200
class FrameInvalidationOracle(RedrawOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe);self.active=False;self.total_types=0;self.total_dirty=0;self.total_cache=0;self.total_project=0
  self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_READ,self.read);self.u.hook_add(UC_HOOK_MEM_WRITE,self.write)
 def emit(self,k,id=-1,field=-1,value=0):self.trace.extend(map(str,(k,id,field,value)))
 def event(self,k,value,index=-1,field=-1):self.emit({'n':20,'s':21,'g':22,'a':23}[k],index,field,value)
 def word(self,p):return struct.unpack('<I',self.u.mem_read(p,4))[0]
 def mutate(self):
  if self.mutated or not self.mutation:return
  self.mutated=True;m=self.mutation;self.emit(14,value=m)
  if m in (1,6):self.put(0x8525b8,0 if m==1 else -1)
  if m==2:self.put(0x8525b8,3);self.put(0x8525ac,BACKINGS[1])
  if m==3:self.ints(TACTICAL+0xb0,[17,-23]);self.ints(0x839630,[9,-11])
  if m==4:self.u.mem_write(ACTORS[1]+0x75,b'\0')
  if m==5:self.ints(ACTORS[1]+0x88,[512,256,728]);self.ints(0xabe568,[-360,-180])
 def read(self,u,access,p,n,v,_):
  if not self.active:return
  if p==0x8525b8:self.emit(1,value=self.signed(self.word(p)))
  if p==0x8525ac:self.emit(2,value=BACKINGS.index(self.word(p)))
  if p in (TACTICAL+0xb0,TACTICAL+0xb4):self.emit(8,self.current,p-TACTICAL-0xb0,self.signed(self.word(p)))
  for i,a in enumerate(ACTORS):
   if p==a+0x75:self.emit(4,i,value=u.mem_read(p,1)[0])
 def write(self,u,access,p,n,v,_):
  if not self.active:return
  if self.project_output is not None and self.project_output<=p<self.project_output+8:
   assert n==4;self.emit(7,self.current,p-self.project_output,self.signed(v))
  for i,a in enumerate(ACTORS):
   if a+0x50c<=p<a+0x530:assert n==4;self.emit(10,i,p-a,self.signed(v))
   if p==a+0x75:assert n==1;self.emit(13,i,value=v&255)
  if p==VECTOR+16:self.event('n',self.signed(v))
  elif self.pointer<=p<self.pointer+self.capacity*20:
   assert n==4 and (p-self.pointer)%4==0
   i,off=divmod(p-self.pointer,20);self.event('s',v&255 if off==16 else self.signed(v),i,off//4)
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  if a==0x45e290:
   self.total_types+=1;self.emit(9,self.current);sp=u.reg_read(UC_X86_REG_ESP);out=self.word(sp+4)
   assert u.reg_read(UC_X86_REG_ECX)==ACTORS[self.current]+0x800
   self.ints(out,self.rows[self.current][14:18]);self.mutate();self.project_output=None;self.ret(4,out);return
  if a==0x6acbe0:return # Existing allocator hook supplies its exact documented service.
  assert any(lo<=a and a+n<=lo+size for lo,size in {**RANGES,**DIRTY_RANGES}.items()),('Uninspected frame instruction',hex(a))
  if a in (0x453c40,0x509800):
   id=ACTORS.index(u.reg_read(UC_X86_REG_ECX));self.emit(3,id,value=6 if a==0x453c40 else 15)
  if a==0x450dd0:self.current=ACTORS.index(u.reg_read(UC_X86_REG_ECX));self.total_cache+=1
  if a==0x453c70:self.emit(5,self.current)
  if a==0x6a29d0:
   self.total_project+=1;self.emit(6,self.current);sp=u.reg_read(UC_X86_REG_ESP);self.project_output=self.word(sp+8)
  if a==0x450e67:self.project_output=None
  if a==0x6a3020:
   self.total_dirty+=1;sp=u.reg_read(UC_X86_REG_ESP)
   for j,v in enumerate(self.result(sp+4,5)):self.emit(11,field=j,value=v if j<4 else v&255)
 def run(self,f):
  kind,self.mutation,ox,oy,sx,sy,width,height,scale,count,capacity,growth,owns,success,qcount,*_=f
  self.mode='Q';self.setup();self.trace=[];self.current=0;self.project_output=None;self.mutated=False
  self.capacity=capacity;self.growth=growth;self.growth_success=success;self.pointer=SLOTS
  self.rows=[f[22+i*18:40+i*18] for i in range(3)]
  self.ints(TACTICAL+0xb0,[ox,oy]);self.put(0x83996c,TACTICAL);self.ints(0x839630,[sx,sy]);self.ints(0xabe568,[width,height]);self.u.mem_write(0xabe490,struct.pack('<Q',scale))
  for i,row in enumerate(self.rows):
   a=ACTORS[i];self.put(a,0x79cbbc if row[0]==6 else 0x7a3540);self.u.mem_write(a+0x75,bytes([row[1]]));self.ints(a+0x88,row[2:5]);self.ints(a+0x51c,row[5:8]);self.ints(a+0x528,row[8:10]);self.ints(a+0x50c,row[10:14]);self.put(a+0x418,a+0x800)
  self.ints(BACKINGS[0],[ACTORS[i] for i in f[19:22]]);self.ints(BACKINGS[1],list(reversed(ACTORS)));self.put(0x8525ac,BACKINGS[0]);self.put(0x8525b8,count)
  for i in range(capacity):
   slot=f[76+i*5:81+i*5];self.ints(SLOTS+i*20,[*slot[:4],slot[4]|0x5c5b5a00])
  self.ints(VECTOR,[0x7ac4c4,SLOTS,capacity,1|(owns<<8),qcount,growth]);self.ints(INPUT,self.rows[0][2:5])
  allowed=[(OUT,16),(VECTOR+4,20),(SLOTS,capacity*20)]
  if success and growth>0:allowed.append((GROWN,(capacity+3*growth)*20))
  for a in ACTORS:allowed.extend([(a+0x75,1),(a+0x50c,0x24)])
  # Mutations at the supplied Type boundary are included in the private arena snapshot audit.
  if self.mutation==3:allowed.append((TACTICAL+0xb0,8))
  if self.mutation==5:allowed.append((ACTORS[1]+0x88,12))
  before=self.snapshot();self.active=True
  try:
   if kind==0:
    self.checked_call(0x6a29d0,[INPUT,OUT],TACTICAL,writes=allowed,inputs=[*RANGES.items(),(0x79cbbc,0x128),(0x79a728,8)])
    self.emit(15,value=self.u.reg_read(UC_X86_REG_EAX)&255)
   elif kind==1:
    self.checked_call(0x450dd0,[OUT],ACTORS[0],writes=allowed,inputs=[*RANGES.items(),(0x79cbbc,0x128),(0x79a728,8)])
    for j,v in enumerate(self.result(OUT,4)):self.emit(16,field=j,value=v)
   else:self.checked_call(0x6aa090,f[15:19],TACTICAL,writes=allowed,inputs=[*RANGES.items(),*DIRTY_RANGES.items(),(0x79cbbc,0x128),(0x79a728,8)])
  finally:self.active=False;self.project_output=None
  self.check(before,allowed)
  self.trace.append('F')
  for a in ACTORS:self.trace.extend(map(str,[self.u.mem_read(a+0x75,1)[0],*self.result(a+0x51c,3),*self.result(a+0x528,2),*self.result(a+0x50c,4)]))
  self.trace.extend(map(str,[self.result(VECTOR+16,1)[0],self.capacity]))
  for i in range(self.capacity):self.trace.extend(map(str,[*self.result(self.pointer+i*20,4),self.u.mem_read(self.pointer+i*20+16,1)[0]]))
  return self.trace
