# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete unchanged Cell -> distinct Unit Scatter/world/moving admission."""
import struct
from original_unit_scatter_world import UnitScatterWorldOracle,ARENA,ACTOR,OBJECTS,DRIVES,CELLS,HOUSES,TYPES,POINT,STOP,STACK,pack,signed
from verify_cell_unit_scatter_world import verify,RANGES,TABLES
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_ESI,UC_X86_REG_EDI,UC_X86_REG_EIP
HEAP=0x2a00000;HEAP_SIZE=0x10000;RULES=0x2800000
class CellUnitScatterWorldOracle(UnitScatterWorldOracle):
 ranges=RANGES;tables=TABLES;inspection_verify=staticmethod(verify)
 def __init__(self,exe):
  super().__init__(exe);self.u.mem_map(HEAP,HEAP_SIZE)
 def prepare_join(self,c):
  u=self.u;self.c=c;self.unit_stack=[];self.put(RULES+0x10b4,c['threshold']);u.mem_write(RULES+0x1431,bytes([c['rule']]))
  u.mem_write(HEAP,b'\xa5'*HEAP_SIZE);self.heap_expected=bytearray(u.mem_read(HEAP,HEAP_SIZE))
  for p,n in zip(HOUSES,c['houses']):self.put(p+0x194,n)
  for i,(p,d,t) in enumerate(zip(OBJECTS,DRIVES,TYPES)):
   u.mem_write(p+0x118,struct.pack('<Q',c['ranks'][i]));u.mem_write(t+0x26f,bytes([c['types'][i][0]]));u.mem_write(t+0x281,bytes([c['types'][i][1]]))
   u.mem_write(p+0x5a0,bytes([c['eligibility'][i]]));u.mem_write(d+0x60,bytes([c['short'][i]]));self.put(d+0x58,c['track'][i]);self.put(d+0x5c,c['index'][i])
   if not i:continue
   a=c['secondary'][i-1]
   for off,key in ((0xa0,'queued'),(0x490,'field490'),(0x480,'capacity'),(0x488,'count'),(0x5c0,'field5c0'),(0x3fc,'field3fc'),(0x58c,'guard_start'),(0x594,'guard_remaining')):self.put(p+off,a[key])
   for off,key in ((0xa4,'queued_byte'),(0x190,'forced'),(0x598,'suspended'),(0x5b9,'field5b9'),(0x599,'field599'),(0x79,'bridge'),(0x5c8,'field5c8'),(0x485,'owned')):u.mem_write(p+off,bytes([a[key]]))
   u.mem_write(p+0x574,bytes([a['registry']&255]));u.mem_write(p+0x5a1,b'\xad');u.mem_write(p+0x4d0,pack(*a['queue']));self.put(p+0x228,OBJECTS[0] if a['target'] else 0)
   self.put(p+0x494,CELLS[a['initial_target']-1] if a['initial_target'] else 0);self.put(p+0x478,0x7a177c);self.put(p+0x47c,ARENA+0x3f000 if a['buffer'] else 0)
   u.mem_write(p+0x88,pack(*a['position']));u.mem_write(d+0x40,pack(*a['head']));u.mem_write(d+0x34,pack(*a['destination']));u.mem_write(d+0x50,struct.pack('<d',1.));self.put(d+0x4c,33);u.mem_write(d+0x63,b'\x01')
   self.put(d,0x7a0594);self.put(d+0x18,0x7a04a8);self.put(d+0x14,a['references']);u.mem_write(d+0x10,bytes([a['powered']]))
   for address,key in ((0x6d6df0,'disabled1bc'),(0x6d6e00,'disabled1c0')):u.mem_write(p+int.from_bytes(u.mem_read(address+2,4),'little'),bytes([a[key]]))
   for off in (0x530,0x558):u.mem_write(p+off,pack(123,-91,17))
   u.mem_write(p+0x2e0,struct.pack('<IIiiii',a['desired'],a['start'],a['timer'],0,a['duration'],a['rate']))
  # All supported raw mission control records are immutable throughout the call.
  for row in c['objects']:
   raw=row[4];u.mem_write(0xa403b0+32*raw+9,bytes([c['control9']]));u.mem_write(0xa403b0+32*raw+7,bytes([c['control7']]))
 def original_entry(self,c):
  self.context='c';self.capacity=self.buffer=self.successes=self.grows=0
  return 0x476920,[POINT,self.action[3],self.action[4],c['elevated']],CELLS[c['cell']]
 def checked_call(self,root,args=(),ecx=0,edx=0,**kw):
  if root==0x476920:
   kw['writes']=[*kw['writes'],(HEAP,HEAP_SIZE)]
   kw['inputs']=[*kw['inputs'],*[(0xa403b0+32*row[4],32) for row in self.c['objects']]]
  result=super().checked_call(root,args,ecx,edx,**kw)
  if root==0x476920:
   assert not self.unit_stack and self.context=='c';self.context='s';self.actor=ACTOR;self.drive=DRIVES[0]
   assert bytes(self.u.mem_read(HEAP,HEAP_SIZE))==bytes(self.heap_expected),'Cell joined heap changed'
  return result
 def code(self,u,a,n,ctx):
  if not self.active or a==STOP:return
  sp=u.reg_read(UC_X86_REG_ESP);ecx=u.reg_read(UC_X86_REG_ECX);arg=lambda i:self.word(sp+4+4*i)
  if self.unit_stack and self.unit_stack[-1][:2]==(a,sp):
   _,_,self.actor,self.drive,self.padding=self.unit_stack.pop();assert not self.pending;self.context='c'
  if a==0x7072d0 and self.context=='c':
   id=self.oid(ecx);assert self.word(sp)==0x476a89 and arg(0)==POINT
   self.unit_stack.append((self.word(sp),sp+16,self.actor,self.drive,self.padding));self.actor=ecx;self.drive=DRIVES[id];self.padding=self.c['padding'] if not id else self.c['secondary'][id-1]['padding'];self.context='s'
   self.emit('c','S',id,arg(1),arg(2));self.emit('c','P',*self.coord(POINT));self.counts['dispatch.'+str(id)]+=1
  if self.context!='c':return super().code(u,a,n,ctx)
  if a==0x40cd40:
   amount=arg(0);assert self.word(sp)==0x4769e6 and arg(1)==0 and amount==self.capacity+10
   result=self.c['growth'][self.grows%len(self.c['growth'])];self.grows+=1;self.emit('c','G',amount,result);self.counts['growth.'+str(result)]+=1
   if result&255:
    buffer=HEAP+self.successes*0x400;self.successes+=1;count=self.word(ecx+16)
    if count:
     raw=bytes(u.mem_read(self.word(ecx+4),count*4));u.mem_write(buffer,raw);self.heap_expected[buffer-HEAP:buffer-HEAP+len(raw)]=raw
    self.put(ecx+4,buffer);self.put(ecx+8,amount);u.mem_write(ecx+13,b'\1');self.capacity=amount;self.buffer=buffer
   self.ret(8,result);return
  if a==0x781d3b:
   assert self.word(sp)==0x476ab4 and arg(0)==self.buffer;self.emit('c','F',self.capacity);self.counts['release']+=1;self.ret(0,0);return
  assert (a,n) in self.allowed,('Uninspected Cell join',hex(a));self.instructions.add(a)
  if a in self.ranges:self.counts[hex(a)]+=1
  if a in (0x476930,0x476938,0x476980,0x476988):
   assert u.reg_read(UC_X86_REG_EDI)==CELLS[self.c['cell']];self.emit('c','H',self.c['cell'],int(a in (0x476930,0x476980)))
  elif a in (0x47696b,0x476a00):
   p=u.reg_read(UC_X86_REG_ESI);self.emit('c','N',self.oid(p),self.oid(self.word(p+0x30)))
  elif a==0x40dc20:self.emit('c','X',self.oid(ecx))
  elif a==0x70a2d5:self.emit('c','K',self.oid(ecx),u.reg_read(UC_X86_REG_EAX))
  elif a in (0x7133a0,0x713420):self.emit('c','V' if a==0x7133a0 else 'E',self.oid(ecx-0x118))
  elif a==0x6d7910:assert arg(0)==3;self.emit('c','B',self.oid(ecx),3)
  elif a==0x6c12c0:self.emit('c','T',self.oid(ecx))
  elif a==0x705020:self.emit('c','t',self.oid(ecx),TYPES.index(self.word(ecx+0x5ac)))
 def admission_code(self,a,ecx,arg):
  u=self.u;emit=lambda k,x=0,y=0,z=0:self.emit('a',k,x,y,z)
  if a in (0x70371e,0x703748):self.counts[hex(a)]+=1;return
  if a==0x70374c:self.resident=self.oid(u.reg_read(UC_X86_REG_ESI))
  elif a in (0x70375c,0x703777):emit('J',self.oid(self.actor) if a==0x70375c else self.resident,int.from_bytes(u.mem_read(u.reg_read(UC_X86_REG_EAX),2),'little'))
  elif a==0x7037fb:emit('B',0,u.reg_read(UC_X86_REG_EAX)&65535)
  elif a==0x5d4e40:emit('Q',self.oid(ecx))
  elif a==0x703879:emit('Z',0,signed(u.reg_read(UC_X86_REG_EAX)));self.counts['distance']+=1
  elif a==0x4a4ac0:self.switch=next(i for i,p in enumerate(DRIVES) if p+4==arg(0));emit('Y',self.switch)
  elif a==0x7038d2:
   result=u.reg_read(UC_X86_REG_EAX)&255;emit('y',self.switch,result);self.counts['switch.'+str(result)]+=1
  return super().admission_code(a,ecx,arg)
 def store(self,u,access,p,n,v,ctx):
  if self.active and HEAP<=p and p+n<=HEAP+HEAP_SIZE:
   assert u.reg_read(UC_X86_REG_EIP)==0x4769f9 and n==4 and self.buffer<=p<self.buffer+self.capacity*4
   self.emit('c','W',(p-self.buffer)//4,self.oid(v&0xffffffff));self.heap_expected[p-HEAP:p-HEAP+n]=pack(v);self.writes['0x4769f9']+=1;return
  return super().store(u,access,p,n,v,ctx)
 def append_join_state(self,c):
  u=self.u
  for i in range(1,5):
   p=OBJECTS[i];d=DRIVES[i]
   self.event('actor',i,signed(self.word(p+0xa0)),self.byte(p+0xa4),self.word(d+0x14),self.byte(p+0x190),signed(self.word(p+0x490)),self.tid(self.word(p+0x494)),self.byte(p+0x598),self.byte(p+0x5a1),int(self.word(p+0x47c)!=0),signed(self.word(p+0x480)),signed(self.word(p+0x488)),self.byte(p+0x485),*self.coord(d+0x34),*struct.unpack('<24i',u.mem_read(p+0x4d0,96)),*self.coord(p+0x530),*self.coord(p+0x558),*self.coord(p+0x88),*self.coord(d+0x40),signed(self.word(d+0x58)),signed(self.word(d+0x5c)),signed(self.word(d+0x4c)),self.byte(d+0x63),*struct.unpack('<Q',u.mem_read(d+0x50,8)))
  p=CELLS[c['cell']];self.event('cell',self.oid(self.word(p+0xe4)),self.oid(self.word(p+0xe8)))
  for i,p in enumerate(OBJECTS):self.event(i,self.oid(self.word(p+0x30)),*struct.unpack('<Q',u.mem_read(p+0x118,8)))
