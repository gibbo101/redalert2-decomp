# SPDX-License-Identifier: GPL-3.0-or-later
"""Unchanged full Unit admission in the bounded ordinary actor/type domain."""
import struct
from original_presentation import PresentationOracle,STACK,STOP
from verify_unit_admission import verify,RANGES,DISPATCH
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_EDX,UC_X86_REG_EBP,UC_X86_REG_ESP,UC_X86_REG_EIP
ARENA=0x2600000;SIZE=0x40000;OBJECTS=[ARENA+i*0x1000 for i in range(5)]
TYPES=[ARENA+0x10000+i*0x2000 for i in range(5)];HOUSES=[ARENA+0x20000+i*0x6000 for i in range(3)]
LOCOS=[ARENA+0x32000+i*0x100 for i in range(5)];CELLS=[ARENA+0x33000,ARENA+0x33200,0xa6f9f8]
REGS=[ARENA+0x34000+i*0x100 for i in range(3)];REG_TABLE=ARENA+0x34400
WEAPON=ARENA+0x35000;PROJECTILE=ARENA+0x35400;OUT=ARENA+0x36000;SLOTS=0x2700000
def ptr(i,table=OBJECTS):return 0 if i==-1 else table[i]
def idx(p,table):return -1 if not p else table.index(p)
def signed(n):return n if n<0x80000000 else n-0x100000000
LOCATIONS={'elevated_list':0x703449,'primary_list':0x70345d,'self_skip':0x703a95,
 'closed_allied_gate':0x703567,'closed_enemy_gate':0x703580,'stationary_allied':0x70394f,
 'enemy_cast':0x70397c,'speed_rejected':0x703940,'occupation_bit5':0x703bb7,
 'occupation_weapon':0x703b29,'state1b8_two':0x703990,'direction8':0x70318c,
 'level_write_from_previous':0x4c87c4,'level_write_from_target':0x4c892c,'elevated_write':0x4c889f}

class UnitAdmissionOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True)
  self.u.mem_map(ARENA,SIZE);self.u.mem_map(SLOTS,0x100000);self.active=False;self.events=[]
  self.entries={hex(a):0 for a in RANGES};self.instructions=set();self.stores=0;self.results={};self.root_results={};self.terrain_results={};self.locations={k:0 for k in LOCATIONS};self.kind_returns={1:0,6:0}
  self.u.hook_add(UC_HOOK_CODE,self.code)
 def va(self,a):return a
 def word(self,a):return int.from_bytes(self.u.mem_read(a,4),'little')
 def event(self,k,a=0,b=0,c=0):self.events.extend(map(str,(k,a,b,c)))
 def prepare_motion(self):pass
 def extra_inputs(self):return []
 def code(self,u,a,n,ctx):
  if not self.active or a==STOP:return
  assert any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),f'Uninspected admission instruction {a:#x}/{n}'
  self.instructions.add(a)
  for label,entry in LOCATIONS.items():
   if a==entry:self.locations[label]+=1
  if a in RANGES:self.entries[hex(a)]+=1
  ecx=u.reg_read(UC_X86_REG_ECX);sp=u.reg_read(UC_X86_REG_ESP);arg=lambda i:self.word(sp+4+4*i)
  oid=lambda p:idx(p,OBJECTS);cid=lambda p:idx(p,CELLS);hid=lambda p:idx(p,HOUSES)
  # These are excluded branches, not substituted callbacks. Every instruction
  # in accepted calls executes unchanged inside the inspected ranges.
  assert a not in (0x7030c5,0x7032bf,0x70333d,0x70347d,0x7034d6,0x703506,0x7035c0,
   0x7035ef,0x703601,0x703623,0x703649,0x70371e,0x703748,0x7039df,0x703a23,0x703b7a,0x6d7931,0x6d8563),f'Unsupported admission branch {a:#x}'
  if a==0x47a130:self.registry_cell=cid(ecx)
  elif a in (0x47a152,0x47a155):self.event('r',self.registry_cell,idx(u.reg_read(UC_X86_REG_EAX),REGS))
  elif a==0x476ac0:self.event('N',cid(ecx),signed(arg(0)))
  elif a==0x548070:self.event('L',*struct.unpack('<hh',u.mem_read(arg(0),4)))
  elif a==0x4c8730:self.event('H',cid(arg(0)),signed(arg(1)),cid(arg(4)))
  elif a==0x4c86e0:self.event('l',oid(ecx),arg(4)&255)
  elif a==0x53d4f0:self.event('d',idx(arg(0),LOCOS))
  elif a==0x636e30:self.event('P',oid(ecx),oid(arg(0)))
  elif a in (0x70a2d5,0x453c45):
   value=u.reg_read(UC_X86_REG_EAX);i=oid(ecx);assert value==self.object_kinds[i]
   self.kind_returns[value]+=1;self.event('K',i,value)
  elif a==0x44d880:self.event('I',oid(ecx))
  elif a==0x594770:self.event('M',oid(ecx))
  elif a==0x496b30:self.event('D',oid(ecx-0x2a8))
  elif a==0x4e5540:self.event('h',hid(ecx),hid(arg(0)))
  elif a==0x4e5580:self.event('A',hid(ecx))
  elif a==0x4e5500:self.event('i',hid(ecx),signed(arg(0)))
  elif a==0x6c7430:self.event('O',oid(ecx))
  elif a==0x40dbd0:self.event('X',oid(ecx))
  elif a==0x6d7910:assert arg(0)==17;self.event('b',oid(ecx),17)
  elif a in (0x7133a0,0x713420):self.event('v',oid(ecx-0x118),1 if a==0x7133a0 else 2)
  elif a==0x6cd670:self.event('C',oid(ecx))
  elif a==0x6d85a0:self.event('s',oid(ecx))
  elif a==0x6df680:self.event('c',idx(ecx,TYPES))
  elif a==0x6d8540:assert arg(0)==0;self.event('w',oid(ecx),0)
  elif a==0x6c12c0:self.event('T',oid(ecx))
  elif a in (0x705020,0x453c60):self.event('t',oid(ecx))
  elif a==0x6df5c0:assert arg(0)==0;self.event('p',idx(ecx,TYPES),0)
  elif a==0x4b8c90:self.event('f',oid(ecx-0x2e0))
  elif a==0x49fc70:self.event('m',idx(arg(0),LOCOS))
 def run(self,h,directions,speeds,houses,regs,cells,objects,steps):
  tick,slot0,slot1,count=h;u=self.u;u.mem_write(ARENA,b'\xa5'*SIZE);u.mem_write(SLOTS,bytes(0x100000));u.mem_write(CELLS[2],b'\xa5'*0x148)
  for p,n in ((0x832618,SLOTS),(0x8661cc,REG_TABLE),(0x8661d8,count),(0xa40774,1),(0xa40d2c,tick)):self.put(p,n)
  u.mem_write(0x851a70,struct.pack('<16h',*directions));u.mem_write(0x850ea0,bytes(12*9*4));u.mem_write(0x852998,bytes(12))
  for land,bits in enumerate(speeds):self.put(0x850ea0+4*(land*9+1),bits)
  for i,s in enumerate((slot0,slot1)):
   if s!=-1:self.put(SLOTS+4*s,CELLS[i])
  for p,(index,mask) in zip(HOUSES,houses):self.put(p+0x30,index);self.put(p+0x5674,mask)
  for i,(present,x,y,d) in enumerate(regs):self.put(REG_TABLE+4*i,REGS[i] if present else 0);self.put(REGS[i]+0x28,(x&65535)|((y&65535)<<16));self.put(REGS[i]+0x2c,d)
  for p,c in zip(CELLS,cells):
   x,y,registry,level,ramp,flags,occ,eocc,owner,eowner,land,head,ehead=c
   self.put(p+0x24,(x&65535)|((y&65535)<<16));u.mem_write(p+0x116,struct.pack('<h',registry));u.mem_write(p+0x11b,bytes([level&255,ramp]))
   for off,v in ((0x140,flags),(0x124,occ),(0x128,eocc),(0x54,owner),(0x58,eowner),(0xec,land),(0x44,-1),(0xe4,ptr(head)),(0xe8,ptr(ehead))):self.put(p+off,v)
  self.put(WEAPON+0xa0,PROJECTILE)
  for i,row in enumerate(objects):
   kind,next_,owner,gate,mission,b18,b19,flags,crushable,crusher,train,b1350,state,target,dest,weapon,projectile=row
   p=OBJECTS[i];t=TYPES[i];u.mem_write(t,bytes(0x2000));self.put(p,0x7addf8 if kind==1 else 0x79cbbc)
   for off,v in ((0x30,ptr(next_)),(0x1b4,HOUSES[owner]),(0x418,t),(0x5ac,t),(0x98,mission),(0xa0,7),(0x588,0),(0xcc,0),(0xd0,0),(0x494,ptr(target)),(0x1b0,ptr(dest)),(0x1b8,state),(0x564,LOCOS[i]),(0x10c,0)):self.put(p+off,v)
   u.mem_write(p+0x118,bytes(8));u.mem_write(p+0x2c0,bytes([b18,b19]));u.mem_write(p+0x14,bytes([flags]));u.mem_write(p+0x2e0,bytes(24))
   self.put(t+0xb94,-1);self.put(t+0x5a4,1);self.put(t+0x74c,WEAPON if weapon else 0)
   for off,v in ((0x1351,gate),(0x1fd,crushable),(0xaf3,crusher),(0xaa0,train),(0x1350,b1350)):u.mem_write(t+off,bytes([v]))
   self.put(LOCOS[i],0x7a04cc);u.mem_write(LOCOS[i]+0x30,bytes(24));self.put(LOCOS[i]+8,p)
   if i==0:u.mem_write(PROJECTILE+0x275,bytes([projectile]))
  self.object_kinds=[r[0] for r in objects];self.prepare_motion();self.events=[]
  ranges=[*RANGES.items(),*[(vt+off,4) for vt,slots in DISPATCH.items() for off in slots],(0x40dbfc,23),
   (0x79a708,8),(0x79a6f8,8),(0x79a738,4),(0x851a70,32),(0x850ea0,12*9*4),(0x852998,12),
   (0x832618,4),(0x8661cc,16),(0xa40774,4),(0xa40d2c,4),(SLOTS,0x100000),*self.extra_inputs()]
  for action,mover,target,direction,level,previous,consult,elevated in steps:
   self.put(OUT,level);u.mem_write(OUT+4,bytes([elevated]));before=bytes(u.mem_read(ARENA,SIZE));fb=bytes(u.mem_read(CELLS[2],0x148))
   def writes(u,access,p,n,v,ctx):
    if p==CELLS[2]+0x24:assert n==4;self.event('F',*struct.unpack('<hh',struct.pack('<I',v&0xffffffff)));self.stores+=1
    if u.reg_read(UC_X86_REG_EIP) in (0x4c87c4,0x4c892c,0x4c889f):
     self.event('W',1 if n==1 else 0,n,signed(v&0xffffffff));self.stores+=1
   hook=u.hook_add(UC_HOOK_MEM_WRITE,writes);self.active=True
   try:
    root,args,ecx=(0x703040,[CELLS[target],direction,level,ptr(previous,CELLS),consult],OBJECTS[mover]) if action=='U' else (0x4c8730,[CELLS[target],direction,OUT,OUT+4,ptr(previous,CELLS)],OBJECTS[mover])
    self.checked_call(root,args,ecx,writes=[(OUT,5),(CELLS[2]+0x24,4)],inputs=ranges)
   finally:self.active=False;u.hook_del(hook)
   result=u.reg_read(UC_X86_REG_EAX);self.results[result]=self.results.get(result,0)+1
   counts=self.root_results if action=='U' else self.terrain_results;counts[result]=counts.get(result,0)+1
   self.event('R',result,signed(self.word(OUT)),u.mem_read(OUT+4,1)[0]);self.event('z',*struct.unpack('<hh',u.mem_read(CELLS[2]+0x24,4)))
   after=bytearray(u.mem_read(ARENA,SIZE));after[OUT-ARENA:OUT-ARENA+5]=before[OUT-ARENA:OUT-ARENA+5]
   assert bytes(after)==before,'Admission changed actor/type/House/registry/Cell arena'
   after=bytearray(u.mem_read(CELLS[2],0x148));after[0x24:0x28]=fb[0x24:0x28];assert bytes(after)==fb,'Admission changed fallback attributes'
  return self.events
