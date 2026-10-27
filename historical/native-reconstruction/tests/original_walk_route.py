# SPDX-License-Identifier: GPL-3.0-or-later
"""Actual Infantry command -> retry/refill -> complete Walk on shared owners."""
import struct
from original_walk_speed import WalkSpeedOracle,RULES
from original_walk_admission import TYPE
from original_walk_commands import WalkCommandHooks
from original_walk_head import WALK
from original_walk_queued import identity
from original_infantry_subcell import ARENA,SIZE,ACTOR,HOUSE as OLD_HOUSE,CELLS,POINT
from original_presentation import PresentationOracle,STOP
from verify_walk_route import verify,RANGES,TABLES,SERVICES
from verify_walk_commands import RANGES as COMMANDS
from unicorn.x86_const import UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EIP
HOUSE=ARENA+0x1800;TARGET=POINT
def pack(*v):return struct.pack('<'+'I'*len(v),*[x&0xffffffff for x in v])
class WalkRouteOracle(WalkCommandHooks,WalkSpeedOracle):
 def __init__(self,exe):
  self.route_ready=False;self.in_destination=False;self.route_ftol=False
  super().__init__(exe);self.u.mem_map(ARENA+SIZE,0x2000);self.u.mem_map(0x3c7000,0x1000)
  self.route_ready=True;self.command_actor=ACTOR;self.command_walk=WALK;self.inspection=verify(exe.read_bytes())
 def put(self,p,value):
  # Older narrow fixtures could alias House with unused Infantry fields. This
  # join uses a distinct real House, before input/arena snapshots are captured.
  if p==ACTOR+0x1b4 and value==OLD_HOUSE:value=HOUSE
  if p in (OLD_HOUSE+0x30,OLD_HOUSE+0x34):p=HOUSE+p-OLD_HOUSE
  if self.route_ready and hasattr(self,'refill') and p==0xa40d2c:value+=self.refill[10]
  return super().put(p,value)
 def dest_event(self,k,x=0,y=0,z=0):self.event('d',k,x,y,z)
 def command_trace(self,k,x=0,y=0,z=0):self.dest_event(k,x,y,z)
 def command_lookup(self,point):return CELLS[identity(point)]
 def command_animation(self):raise AssertionError('Diagnostic initial reset5CC stays zero')
 def destination_code(self,u,a,n):
  assert a in SERVICES or any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected destination',hex(a))
  if a in RANGES:self.counts['destination_'+hex(a)]+=1
  sp=u.reg_read(UC_X86_REG_ESP);ecx=u.reg_read(UC_X86_REG_ECX)
  if a in (0x3c7594,0x3c757c):
   assert self.word(sp+4)==WALK+0x14;value=self.word(WALK+0x14)+(1 if a==0x3c7594 else -1)
   assert 0<value<0x80000000;u.mem_write(WALK+0x14,pack(value));self.dest_event('I',0,0,value);self.command_ret(4,value)
  elif a==0x4c8030:u.mem_write(sp-0x18,pack(self.refill[7]+17))
  elif a==0x4f52f0:assert ecx==HOUSE;self.dest_event('H',0,0,1)
  elif a==0x71dea0:self.dest_event('v',0,0,u.mem_read(WALK+0x34,1)[0])
  elif a==0x594770:self.dest_event('M',0,0,self.ints(ACTOR+(0xa0 if self.word(ACTOR+0x98)==0xffffffff else 0x98),1)[0])
  elif a==0x509800:self.dest_event('k',0,0,15)
  elif a==0x71f900:self.dest_event('G')
  elif a==0x410290:
   assert ecx==TARGET and self.word(sp+8)==ACTOR;out=self.word(sp+4)
   self.dest_event('Q',*self.v[3:6]);u.mem_write(out,pack(*self.v[3:6]));self.command_ret(8,out)
  elif a in SERVICES or any(lo<=a and a+n<=lo+size for lo,size in COMMANDS.items()):self.command_code(u,a,n)
 def code(self,u,a,n,ctx):
  if not self.route_ready or not self.active or a==STOP:return super().code(u,a,n,ctx)
  sp=u.reg_read(UC_X86_REG_ESP);ecx=u.reg_read(UC_X86_REG_ECX)
  if self.in_destination and a==self.destination_return:self.in_destination=False
  if a==0x501ce0:
   assert ecx==ACTOR and self.word(sp+4) in (0,TARGET)
   self.destination_return=self.word(sp);self.in_destination=True
  if self.in_destination:return self.destination_code(u,a,n)
  if a==0x71e220:u.mem_write(sp-8,pack(self.refill[7]))
  if a==0x6c7420:
   assert ecx==ACTOR and self.word(ACTOR+0x1b4)==HOUSE;self.counts[hex(a)]+=1;self.event('H',self.ints(HOUSE+0x30,1)[0]);return
  if self.in_speed and a==0x4f5a20:
   assert ecx==HOUSE and self.word(sp+4)==TYPE;self.counts[hex(a)]+=1;self.event('h',0);return
  if self.in_admission and a==0x4e5500:
   assert ecx==HOUSE and self.word(sp+4)==self.word(HOUSE+0x30);self.counts['admission_house']+=1;self.counts[hex(a)]+=1
   self.trace_admission('i',0,self.ints(HOUSE+0x30,1)[0]);return
  if a==0x77f110 and self.word(sp)==0x71e2e0:self.route_ftol=True
  if a==0x71e2e0:self.route_ftol=False
  if (0x71e28a<=a<0x71e65f) or (0x508730<=a<0x508750) or (0x508ab0<=a<0x508cef) or a==0x4c3000 or self.route_ftol:
   assert a in SERVICES or any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected route caller',hex(a))
   assert not (0x71e332<=a<0x71e63f or 0x508b00<=a<0x508ce5),('Unjoined failed route or JumpJet child',hex(a))
   if a in RANGES:self.counts['route_'+hex(a)]+=1
   if a==0x508730:assert ecx==ACTOR;self.trace('u')
   elif a==0x508ab0:assert ecx==ACTOR;self.trace('p');self.counts['post_route']+=1
   elif a==0x4c3000:
    assert ecx==ACTOR;point,zero,other=self.ints(sp+4,3);assert zero==other==0
    x,y=struct.unpack('<hh',pack(point));self.event('f',x,y,zero,other,self.refill[9]);self.counts['supplied_route']+=1
    # This named service is supplied, not original4C3000 pathfinding. Its writes
    # precede the actual caller's53C/484/queue rereads and retain unfilled tails.
    for i in range(self.refill[8]):
     self.u.mem_write(ACTOR+0x4d0+4*i,pack(self.v[6]));self.trace('A',0x4d0+4*i,self.v[6]&0xffffffff)
    if self.refill[8]<24:
     off=0x4d0+4*self.refill[8];u.mem_write(ACTOR+off,pack(-1));self.trace('A',off,0xffffffff)
    if self.refill[12]&2:u.mem_write(WALK+0x1c,pack(self.v[3]+257,self.v[4]-513,self.v[5]+7))
    self.ret(12,self.refill[9])
   return
  if a==0x508750:
   assert ecx==ACTOR;self.trace('X',0,0,0);self.counts['actual_process_reset']+=1;return
  if 0x508750<a<0x508770:
   assert any(lo<=a and a+n<=lo+size for lo,size in RANGES.items());return
  return super().code(u,a,n,ctx)
 def store(self,u,access,p,n,value,ctx):
  if not self.route_ready or not self.active:return super().store(u,access,p,n,value,ctx)
  value&=(1<<(8*n))-1
  if self.in_destination:
   if p==0xa6eb14:self.dest_event('C',0,0,value);return
   if ACTOR<=p<ACTOR+0x600:
    off=p-ACTOR
    assert (off,n) in ((0x490,4),(0x494,4),(0x598,1),(0x5a1,1),(0x4d0,4),(0x5cc,1),*[(x,4) for x in (0x530,0x534,0x538,0x558,0x55c,0x560)]),(hex(p),n)
    if off==0x5cc:self.command_store(p,n,value)
    else:self.dest_event('a',off,n,int(value!=0) if off==0x494 else value)
   elif WALK+0x1c<=p<WALK+0x37:self.command_store(p,n,value)
   elif ARENA<=p<ARENA+SIZE:raise AssertionError(('Unexpected destination arena store',hex(p),n))
   return
  if p-ACTOR in (0x530,0x534,0x538,0x53c,0x5ac):
   assert n==4;self.trace('A',p-ACTOR,value)
   if p==ACTOR+0x530 and self.refill[12]&1:
    u.mem_write(0xa40d2c,pack(self.word(0xa40d2c)+13));u.mem_write(RULES+0x13c8,struct.pack('<d',2.5))
   return
  return super().store(u,access,p,n,value,ctx)
 def checked_call(self,root,*args,**kwargs):
  if self.route_ready and root==0x71dff0:
   if self.prepare_route:
    f=self.refill;u=self.u
    for p,value in ((ACTOR+0x5a8,TYPE),(ACTOR+0x5ac,f[6]),(ACTOR+0x490,19),(ACTOR+0x494,TARGET if f[11] else 0),
     (ACTOR+0x25c,0),(WALK,0x7aeba0),(WALK+0x18,0x7aeab4),(WALK+0x14,3),(TARGET,0x79db04),(0xa6eb14,7),
     (0xa3d298,1),(0x839848,RULES),(RULES+0x13d0,8),(ACTOR+0x530,f[2]),(ACTOR+0x534,f[3]),
     (ACTOR+0x538,f[4]),(ACTOR+0x53c,f[5]),(ACTOR+0x4d0,-1)):self.put(p,value)
    for p in (ACTOR+0x204,ACTOR+0x205,ACTOR+0x598,ACTOR+0x5cc,TYPE+0xb44,TYPE+0xc0d,TYPE+0xc00):u.mem_write(p,b'\0')
    u.mem_write(HOUSE+0x134,b'\1\0');u.mem_write(RULES+0x13c8,struct.pack('<Q',f[1]));u.mem_write(0xabe520,struct.pack('<d',1.))
    u.mem_write(ACTOR+0x558,pack(31,37,41))
    if f[0]:
     u.mem_write(WALK+0x1c,bytes(12));u.mem_write(WALK+0x34,b'\0')
     self.in_destination=False
     writes=[(ACTOR+0x490,8),(ACTOR+0x530,12),(ACTOR+0x558,12),(ACTOR+0x4d0,4),(ACTOR+0x598,1),(ACTOR+0x5a1,1),(WALK+0x14,4),(WALK+0x1c,27),(0xa6eb14,4)]
     self.in_destination=True;self.destination_return=STOP
     cursor=ARENA;untouched=[]
     for p,n in sorted(writes):
      if not ARENA<=p<ARENA+SIZE:continue
      if cursor<p:untouched.append((cursor,p-cursor))
      cursor=max(cursor,p+n)
     if cursor<ARENA+SIZE:untouched.append((cursor,ARENA+SIZE-cursor))
     try:PresentationOracle.checked_call(self,0x501ce0,[TARGET,1],ACTOR,writes=writes,
      inputs=[*untouched,*RANGES.items(),*TABLES.items(),(0x852998,12),(0xaf9060,12),(0xa40d2c,4),
       (0xa3d298,4),(0x839848,4),(RULES+0x13c8,12),(0xabe520,8)])
     finally:self.in_destination=False
     self.event('O',1,0,0)
    self.prepare_route=False
   extra=[(ACTOR+0x530,16),(ACTOR+0x5ac,4),(ACTOR+0x490,8),(ACTOR+0x558,12),(ACTOR+0x598,1),(ACTOR+0x5cc,1),(WALK+0x14,4)]
   writes=sorted([*kwargs['writes'],*extra]);cursor=ARENA;inputs=[]
   for p,n in writes:
    if p>=ARENA+SIZE:continue
    if cursor<p:inputs.append((cursor,p-cursor))
    cursor=max(cursor,p+n)
   if cursor<ARENA+SIZE:inputs.append((cursor,ARENA+SIZE-cursor))
   inputs.extend((p,n) for p,n in kwargs['inputs'] if p<ARENA or p>=ARENA+SIZE)
   kwargs['writes']=[*writes,(0xa6eb14,4),(0xa40d2c,4),(RULES+0x13c8,8)]
   kwargs['inputs']=[*inputs,*RANGES.items(),*TABLES.items(),(0xa3d298,4),(0x839848,4),(0xabe520,8)]
   # The diagnostic may change the live clock at a timer store. It must not
   # also appear as an immutable input in the inherited root's initial list.
   kwargs['inputs']=[(p,n) for p,n in kwargs['inputs'] if p!=0xa40d2c]
  return super().checked_call(root,*args,**kwargs)
 def run_route(self,v,options,speed,refill):
  self.refill=refill;self.prepare_route=True;self.in_destination=False;self.route_ftol=False
  result=self.run_speed_join(v,options,speed)
  self.event('owners',*self.ints(ACTOR+0x53c,1),*self.ints(ACTOR+0x5ac,1),*self.ints(ACTOR+0x490,1),int(bool(self.word(ACTOR+0x494))),
   self.u.mem_read(ACTOR+0x598,1)[0],self.u.mem_read(ACTOR+0x5cc,1)[0],self.word(WALK+0x14),self.word(0xa6eb14),
   *self.ints(ACTOR+0x530,3),*self.ints(ACTOR+0x558,3),*self.ints(0xa40d2c,1),struct.unpack('<Q',self.u.mem_read(RULES+0x13c8,8))[0])
  return result
