# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete scoped Scatter with unchanged nested world/admission/destination code."""
import struct
from collections import Counter
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from original_presentation import PresentationOracle,STOP,STACK
from verify_unit_scatter_world import verify,RANGES,TABLES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_EIP,UC_X86_REG_ESP
ARENA=0x2600000;SIZE=0x40000;OBJECTS=[ARENA+i*0x1000 for i in range(5)];ACTOR=OBJECTS[0]
TYPES=[ARENA+0x10000+i*0x2000 for i in range(5)];HOUSES=[ARENA+0x20000+i*0x6000 for i in range(3)]
DRIVES=[ARENA+0x32000+i*0x200 for i in range(5)];DRIVE=DRIVES[0]
CELLS=[ARENA+0x34000+i*0x200 for i in range(9)]+[0xa6f9f8];FALLBACK=CELLS[-1]
STATE=ARENA+0x38000;POINT=ARENA+0x39000;REG_TABLE=ARENA+0x3a000;REGS=ARENA+0x3b000
WEAPON=ARENA+0x3e000;PROJECTILE=ARENA+0x3e400;SLOTS=0x2700000;MAP=0x8324e0;PLANES=0x7d27e8
INC=0x3c7594;DEC=0x3c757c
def signed(v):return (v+0x80000000)%0x100000000-0x80000000
def pack(*v):return struct.pack('<'+'I'*len(v),*[n&0xffffffff for n in v])
def ptr(i,table):return table[i] if i!=-1 else 0
class UnitScatterWorldOracle(PresentationOracle):
 ranges=RANGES;tables=TABLES;inspection_verify=staticmethod(verify)
 def __init__(self,exe):
  self.inspection=self.inspection_verify(exe.read_bytes());super().__init__(exe,allow_patched=True)
  self.u.mem_map(ARENA,SIZE);self.u.mem_map(SLOTS,0x100000);self.u.mem_map(0x3c7000,0x1000);self.u.mem_map(0x2800000,0x4000)
  self.actor=ACTOR;self.drive=DRIVE
  self.active=False;self.counts=Counter();self.instructions=set();self.writes=Counter();self.pending=[];self.context='s'
  cs=Cs(CS_ARCH_X86,CS_MODE_32)
  self.allowed={(i.address,i.size) for lo,size in self.ranges.items() for i in cs.disasm(bytes(self.u.mem_read(lo,size)),lo)}
  self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.store)
 def va(self,a):return a
 def word(self,p):return int.from_bytes(self.u.mem_read(p,4),'little')
 def byte(self,p):return self.u.mem_read(p,1)[0]
 def coord(self,p):return struct.unpack('<3i',self.u.mem_read(p,12))
 def cell(self,p):return struct.unpack('<2h',self.u.mem_read(p,4))
 def event(self,*v):self.events.extend(map(str,v))
 def emit(self,group,k,a=0,b=0,c=0):self.event(group,k,a,b,c)
 def cid(self,p):return CELLS.index(p)
 def tid(self,p):return self.cid(p)+1 if p else 0
 def oid(self,p):return OBJECTS.index(p) if p else -1
 def hid(self,p):return HOUSES.index(p) if p else -1
 def ret(self,n,value):
  u=self.u;sp=u.reg_read(UC_X86_REG_ESP);target=self.word(sp)
  u.reg_write(UC_X86_REG_EAX,value&0xffffffff);u.reg_write(UC_X86_REG_ESP,sp+4+n);u.reg_write(UC_X86_REG_EIP,target)
 def returned(self,a,sp):
  if self.pending and self.pending[-1][0:2]==(a,sp):
   _,_,kind,out,previous=self.pending.pop();eax=self.u.reg_read(UC_X86_REG_EAX)
   if kind in ('q','p'):
    assert eax==out
    self.emit('w',kind,*(self.coord(out) if kind=='q' else (*self.cell(out),0)))
   elif kind in ('y','n'):self.emit('w',kind,eax&255)
   elif kind in ('f','v','a'):self.emit('w',kind,signed(eax))
   if kind in ('y','n','a'):self.counts[kind+'.'+str(eax&255 if kind!='a' else signed(eax))]+=1
   self.context=previous
 def enter(self,kind,n,out=0,context=None):
  sp=self.u.reg_read(UC_X86_REG_ESP);self.pending.append((self.word(sp),sp+4+n,kind,out,self.context))
  if context:self.context=context
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  sp=u.reg_read(UC_X86_REG_ESP);self.returned(a,sp);arg=lambda i:self.word(sp+4+4*i);ecx=u.reg_read(UC_X86_REG_ECX)
  if a in (INC,DEC):
   p=arg(0);assert p==self.drive+0x14;value=(self.word(p)+(1 if a==INC else -1))&0xffffffff;assert 0<value<0x80000000
   u.mem_write(p,pack(value));self.expected[p-ARENA:p-ARENA+4]=pack(value);self.emit('d','I',0,0,value) if self.context=='d' else self.emit('s','I',value);self.counts['atomic_inc' if a==INC else 'atomic_dec']+=1;self.ret(4,value);return
  assert (a,n) in self.allowed,('Uninspected joined Scatter instruction',hex(a))
  self.instructions.add(a)
  if a in self.ranges:self.counts[hex(a)]+=1
  if a==0x4706c0:self.counts['ramp.'+str(self.byte(ecx+0x11c))]+=1
  if a==0x4ca6f0:self.emit('w','Q',signed(arg(1)));self.enter('q',8,arg(0))
  elif a==0x4cc4b0:assert arg(0)==0;self.emit('w','Y');self.enter('y',4)
  elif a==0x55a280:self.emit('w','F',*self.coord(arg(0)));self.enter('f',4)
  elif a==0x548000:self.emit('w','K',*self.coord(arg(0)))
  elif a==0x548070:self.emit('w','L',*self.cell(arg(0)))
  elif a==0x55a660:assert arg(1)==1;self.emit('w','N',*self.cell(arg(0)));self.enter('n',8)
  elif a==0x5d47d0:self.emit('w','V');self.enter('v',0)
  elif a==0x6a6a50:self.emit('w','P',*self.coord(arg(1)));self.enter('p',8,arg(0))
  elif a==0x703040:
   assert arg(3)==0 and arg(4)==1
   self.emit('w','A',self.cid(arg(0)),signed(arg(1)),signed(arg(2)));self.enter('a',20,context='a')
  elif a==0x7053f0:
   assert arg(1)==1;self.destination_target=arg(0);self.current_target=arg(0);self.current_padding=self.padding;self.emit('w','S',self.cid(arg(0)),arg(1));self.enter('S',8,context='d')
  elif a==0x5502e0:raise AssertionError('Unjoined zero-point pathfinder entered')
  if self.context=='a':self.admission_code(a,ecx,arg);return
  if self.context=='d':self.destination_code(a,ecx,arg,sp);return
  if a==0x594770:self.emit('s','M',signed(self.word(self.actor+0xa0) if self.word(self.actor+0x98)==0xffffffff else self.word(self.actor+0x98)))
  elif a==0x705020:self.emit('s','T')
  elif a==0x70733e:self.emit('s','G')
  elif a in (0x707375,0x7074f5):
   off=9 if a==0x707375 else 7;control=u.reg_read(UC_X86_REG_EAX);raw=signed(self.word(self.actor+0x98))
   assert control==((0xa403b0+(raw<<5))&0xffffffff);self.emit('s','H',raw,off,self.byte(control+off))
  elif a==0x707391:self.emit('s','F',u.reg_read(UC_X86_REG_EAX)&255)
  elif a==0x70a2d0:self.emit('s','K',1)
  elif a in (0x7075fd,0x70763b):self.emit('s','B' if a==0x7075fd else 'J',u.reg_read(UC_X86_REG_EAX)&65535 if a==0x7075fd else self.word(u.reg_read(UC_X86_REG_EAX))&65535)
  elif a==0x6388a0:self.range=(signed(arg(0)),signed(arg(1)))
  elif a==0x63893e:self.emit('s','D',u.reg_read(UC_X86_REG_EAX),signed(self.word(STATE+4)),signed(self.word(STATE+8)))
  elif a in (0x707579,0x707618,0x70765b):self.emit('s','R',*self.range,signed(u.reg_read(UC_X86_REG_EAX)))
  elif a==0x594cb0:assert arg(0)==2 and arg(1)==0;self.emit('s','q',2)
 def admission_code(self,a,ecx,arg):
  u=self.u;emit=lambda k,x=0,y=0,z=0:self.emit('a',k,x,y,z)
  assert a not in (0x7030c5,0x7032bf,0x70333d,0x70347d,0x7034d6,0x703506,0x7035c0,0x7035ef,0x703601,0x703623,0x703649,0x70371e,0x703748,0x7039df,0x703a23,0x703b7a,0x6d7931,0x6d8563),('Unsupported admission branch',hex(a))
  if a==0x47a130:self.registry_cell=self.cid(ecx)
  elif a in (0x47a152,0x47a155):assert u.reg_read(UC_X86_REG_EAX)==0;emit('r',self.registry_cell,-1)
  elif a==0x476ac0:emit('N',self.cid(ecx),signed(arg(0)))
  elif a==0x4c8730:emit('H',self.cid(arg(0)),signed(arg(1)),-1 if not arg(4) else self.cid(arg(4)))
  elif a==0x4c86e0:emit('l',self.oid(ecx),arg(4)&255)
  elif a==0x53d4f0:emit('d',next(i for i,p in enumerate(DRIVES) if p+4==arg(0)))
  elif a==0x636e30:emit('P',self.oid(ecx),self.oid(arg(0)))
  elif a in (0x70a2d5,0x453c45):emit('K',self.oid(ecx),u.reg_read(UC_X86_REG_EAX))
  elif a==0x44d880:emit('I',self.oid(ecx))
  elif a==0x594770:emit('M',self.oid(ecx))
  elif a==0x496b30:emit('D',self.oid(ecx-0x2a8))
  elif a==0x4e5540:emit('h',self.hid(ecx),self.hid(arg(0)))
  elif a==0x4e5580:emit('A',self.hid(ecx))
  elif a==0x4e5500:emit('i',self.hid(ecx),signed(arg(0)))
  elif a==0x6c7430:emit('O',self.oid(ecx))
  elif a==0x40dbd0:emit('X',self.oid(ecx))
  elif a==0x6d7910:assert arg(0)==17;emit('b',self.oid(ecx),17)
  elif a in (0x7133a0,0x713420):emit('v',self.oid(ecx-0x118),1 if a==0x7133a0 else 2)
  elif a==0x6cd670:emit('C',self.oid(ecx))
  elif a==0x6d85a0:emit('s',self.oid(ecx))
  elif a==0x6df680:emit('c',TYPES.index(ecx))
  elif a==0x6d8540:assert arg(0)==0;emit('w',self.oid(ecx),0)
  elif a==0x6c12c0:emit('T',self.oid(ecx))
  elif a in (0x705020,0x453c60):emit('t',self.oid(ecx))
  elif a==0x6df5c0:assert arg(0)==0;emit('p',TYPES.index(ecx),0)
  elif a==0x4b8c90:emit('f',self.oid(ecx-0x2e0))
  elif a==0x49fc70:emit('m',next(i for i,p in enumerate(DRIVES) if p+4==arg(0)))
 def destination_code(self,a,ecx,arg,sp):
  u=self.u;emit=lambda k,x=0,y=0,z=0:self.emit('d',k,x,y,z)
  if a==0x4c8030:self.current_target=arg(0);self.current_padding=self.padding;u.mem_write(sp-0x18,pack(self.padding))
  elif a==0x594770:emit('M',0,0,signed(self.word(self.actor+0xa0) if self.word(self.actor+0x98)==0xffffffff else self.word(self.actor+0x98)))
  elif a in (0x47cf80,0x70a2d0):emit('k',0,0,11 if a==0x47cf80 else 1)
  elif a==0x4a47f0:emit('G')
  elif a==0x4a4c40:emit('r')
  elif a in (0x49fca7,0x49fcf9,0x49fd03):emit('v',0,0,u.reg_read(UC_X86_REG_EAX)&255)
  elif a==0x53d230:emit('P',0,0,self.byte(self.drive+0x10))
  elif a==0x49fe30:emit('m',0,0,a)
  elif a in (0x49fe41,0x49fe54,0x49fe67,0x49fe76):emit('b',{0x49fe41:0x324,0x49fe54:0x328,0x49fe67:0x1bc,0x49fe76:0x1c0}[a],0,u.reg_read(UC_X86_REG_EAX)&255)
  elif a==0x4102ba:
   p=self.coord(u.reg_read(UC_X86_REG_EAX));self.current_padding=p[1];self.observed_point=p;emit('Q',*p)
  elif a==0x40dc20:emit('x',0,0,self.tid(ecx))
  elif a==0x7057cd:
   emit('f',0,0,self.byte(self.destination_target+0x14))
  assert a not in (0x7055bc,0x7056bb,0x7056e0,0x7057d3),('Unjoined destination mission/type branch',hex(a))
 def store(self,u,access,p,n,v,_):
  if not self.active:return
  a=u.reg_read(UC_X86_REG_EIP);value=v&((1<<(8*n))-1)
  if p==0xa6eb14:
   assert n==4 and a in (0x53d25f,0x53d280);assert value==(self.word(p)+(1 if a==0x53d25f else -1))&0xffffffff
   self.emit('d','C',0,0,value) if self.context=='d' else self.emit('s','C',value)
  elif p==FALLBACK+0x24:
   assert n==4 and any(lo<=a<lo+size for lo,size in ((0x548000,0x68),(0x548070,0x38),(0x55a280,0x79),(0x55a660,0xd7)))
   self.emit('w','W',value)
  if p in (0x850bb8,0x850ba8,0x850bac,0x850bd0,0x850bd4) or PLANES<=p and p+n<=PLANES+800:
   assert 0x4706c0<=a<0x470e7b and n in (1,4,8)
  if self.context=='a' and a in (0x4c87c4,0x4c892c,0x4c889f):self.emit('a','W',1 if n==1 else 0,n,signed(value))
  if ARENA<=p and p+n<=ARENA+SIZE:
   if 0x6388a0<=a<0x63894d:
    if a==0x63890b:assert p==STATE+12+4*self.word(STATE+4) and value==self.word(STATE+12+4*self.word(STATE+4))^self.word(STATE+12+4*self.word(STATE+8))
    elif a in (0x63891e,0x638921):assert p==STATE+(4 if a==0x63891e else 8) and value==self.word(p)+1
    elif a in (0x638926,0x638935):assert p==STATE+(4 if a==0x638926 else 8) and self.word(p)==250 and value==0
    else:raise AssertionError('Unexpected joined RNG store')
   elif a in (0x594ce4,0x594cea):
    assert (p,n,value)==(self.actor+(0xa0 if a==0x594ce4 else 0xa4),4 if a==0x594ce4 else 1,2 if a==0x594ce4 else 0)
    self.emit('s','W',p-self.actor,value)
   elif self.context=='d':
    fields={0x705491:(0x190,1,0),0x70581c:(0x4d0,4,0xffffffff),0x4cde39:(0x488,4,0),0x4cde4e:(0x47c,4,0),0x4cde51:(0x485,1,0),0x4cde54:(0x480,4,0),0x4c8041:(0x490,4,0),0x4c8047:(0x494,4,self.current_target),0x4c8119:(0x598,1,0),0x4c81ca:(0x5a1,1,0),0x4c81ea:(0x558,4,self.action[5]&0xffffffff),0x4c81f0:(0x55c,4,self.current_padding&0xffffffff),0x4c81f3:(0x560,4,self.delay&0xffffffff),0x4c8207:(0x530,4,self.action[5]&0xffffffff),0x4c820a:(0x534,4,self.current_padding&0xffffffff),0x4c820d:(0x538,4,0)}
    if a in fields:
     off,size,want=fields[a];assert (p,n,value)==(self.actor+off,size,want),(hex(a),hex(p),value,want)
     self.emit('d','a',off,n,self.tid(value) if off==0x494 else value)
    elif a in (0x49fe89,0x49fe8c,0x49fe8f):
     off={0x49fe89:0x34,0x49fe8c:0x38,0x49fe8f:0x3c}[a];assert (p,n,value)==(self.drive+off,4,self.observed_point[(off-0x34)//4]&0xffffffff);self.emit('d','d',off,n,value)
    else:raise AssertionError(('Unexpected joined destination store',hex(a),hex(p),n))
   else:raise AssertionError(('Unexpected joined arena store',hex(a),hex(p),n))
   self.expected[p-ARENA:p-ARENA+n]=value.to_bytes(n,'little')
  self.writes[hex(a)]+=1
 def prepare_join(self,c):pass
 def append_join_state(self,c):pass
 def original_entry(self,c):
  return (0x6a6a50,[STACK-0x1f00,POINT],MAP) if c["projection"] else (0x7072d0,[POINT,self.action[3],self.action[4]],ACTOR)
 def run(self,c):
  u=self.u;u.mem_write(ARENA,b'\xa5'*SIZE);u.mem_write(SLOTS,bytes(0x100000));u.mem_write(FALLBACK,b'\xa5'*0x148);self.actor=ACTOR;self.drive=DRIVE;self.events=[];self.context='s';self.pending=[];self.delay=c['delay'];self.padding=c['padding']
  for p,(index,mask) in zip(HOUSES,((0,1),(1,2),(33,0))):self.put(p+0x30,index);self.put(p+0x5674,mask)
  self.put(WEAPON+0xa0,PROJECTILE)
  for i,row in enumerate(c['objects']):
   kind,next_,owner,gate,mission,b18,b19,flags,crushable,crusher,train,b1350,state,target,dest,weapon,projectile=row;p=OBJECTS[i];t=TYPES[i];d=DRIVES[i]
   u.mem_write(t,bytes(0x2000));self.put(p,0x7addf8 if kind==1 else 0x79cbbc)
   for off,v in ((0x30,ptr(next_,OBJECTS)),(0x1b4,HOUSES[owner]),(0x418,t),(0x5ac,t),(0x98,mission),(0xa0,c['queued'] if not i else 7),(0x588,0),(0xcc,ARENA+0x3f100),(0xd0,0),(0x25c,0),(0x494,ptr(target,OBJECTS)),(0x1b0,ptr(dest,OBJECTS)),(0x1b8,state),(0x564,d+4),(0x10c,0)):
    self.put(p+off,v)
   u.mem_write(p+0x118,bytes(8));u.mem_write(p+0x2c0,bytes([b18,b19]));u.mem_write(p+0x14,bytes([flags]));u.mem_write(p+0x2e0,bytes(24));u.mem_write(p+0x88,bytes(12))
   self.put(t+0xb94,-1);self.put(t+0x5a4,1);self.put(t+0x74c,WEAPON if weapon else 0)
   for off,v in ((0x1351,gate),(0x1fd,crushable),(0xaf3,crusher),(0xaa0,train),(0x1350,b1350)):u.mem_write(t+off,bytes([v]))
   self.put(d+4,0x7a04cc);self.put(d+12,p);u.mem_write(d+0x34,bytes(24))
   if not i:u.mem_write(PROJECTILE+0x275,bytes([projectile]))
  for p,row in zip(CELLS,c['cells']):
   slot,x,y,level,ramp,flags,land,head,ehead,occ,eocc,owner,eowner,abstract=row
   self.put(p,0x79db04);u.mem_write(p+0x14,bytes([abstract]));u.mem_write(p+0x24,struct.pack('<2h',x,y));u.mem_write(p+0x116,struct.pack('<h',-1));u.mem_write(p+0x11b,bytes([level&255,ramp]))
   for off,v in ((0x140,flags),(0x124,occ),(0x128,eocc),(0x54,owner),(0x58,eowner),(0xec,land),(0x44,-1),(0xe4,ptr(head,OBJECTS)),(0xe8,ptr(ehead,OBJECTS))):self.put(p+off,v)
   if slot!=-1:self.put(SLOTS+4*slot,p)
  self.put(MAP+0x138,SLOTS);self.put(MAP+0x13c,262144)
  for off,key in ((0xf0,'dimension0'),(0xf8,'originX'),(0xfc,'originY'),(0x100,'width'),(0x104,'height')):self.put(MAP+off,c['shape'][('dimension0','originX','originY','width','height').index(key)])
  self.put(0x8661cc,REG_TABLE);self.put(0x8661d8,0)
  for i in range(128):self.put(REG_TABLE+4*i,REGS+i*0x40);u.mem_write(REGS+i*0x40+0x28,struct.pack('<2h',c['poolx'],c['pooly']))
  self.put(0xa40774,1);u.mem_write(0x851a70,struct.pack('<16h',0,-1,1,-1,1,0,1,1,0,1,-1,1,-1,0,-1,-1));u.mem_write(0x850ea0,bytes(12*9*4))
  for land,bits in enumerate(c['speeds']):self.put(0x850ea0+4*(land*9+1),bits)
  self.put(DRIVE,0x7a0594);self.put(DRIVE+0x18,0x7a04a8);self.put(DRIVE+0x14,c['references']);u.mem_write(DRIVE+0x10,bytes([c['powered']]));self.put(0xa6eb14,c['global_references'])
  u.mem_write(ACTOR+0x88,pack(*c['position']));u.mem_write(DRIVE+0x40,pack(*c['head']));u.mem_write(DRIVE+0x34,pack(*c['destination']));u.mem_write(DRIVE+0x50,struct.pack('<d',1.));self.put(DRIVE+0x4c,33);self.put(DRIVE+0x58,2);self.put(DRIVE+0x5c,9);u.mem_write(DRIVE+0x63,b'\x01')
  for off,key in ((0xa4,'queued_byte'),(0x190,'forced'),(0x598,'suspended'),(0x5b9,'field5b9'),(0x599,'field599'),(0x79,'bridge'),(0x5c8,'field5c8'),(0x485,'owned')):u.mem_write(ACTOR+off,bytes([c[key]]))
  u.mem_write(ACTOR+0x574,bytes([c['registry']&255]));u.mem_write(ACTOR+0x5a1,bytes([173]));u.mem_write(ACTOR+0x4d0,pack(*c['queue']))
  self.put(ACTOR+0x228,OBJECTS[1] if c['target'] else 0);self.put(ACTOR+0x494,CELLS[c['initial_target']-1] if c['initial_target'] else 0)
  for off,key in ((0x490,'field490'),(0x480,'capacity'),(0x488,'count'),(0x5c0,'field5c0'),(0x3fc,'field3fc'),(0x58c,'guard_start'),(0x594,'guard_remaining')):self.put(ACTOR+off,c[key])
  self.put(ACTOR+0x478,0x7a177c);self.put(ACTOR+0x47c,ARENA+0x3f000 if c['buffer'] else 0);self.put(ARENA+0x3f100,0)
  for address,key in ((0x6d6df0,'disabled1bc'),(0x6d6e00,'disabled1c0')):self.u.mem_write(ACTOR+int.from_bytes(u.mem_read(address+2,4),'little'),bytes([c[key]]))
  for off in (0x530,0x558):u.mem_write(ACTOR+off,pack(123,-91,17))
  u.mem_write(ACTOR+0x2e0,struct.pack('<IIiiii',c['desired'],c['start'],c['timer'],0,c['duration'],c['rate']))
  self.put(0x839848,0x2800000);self.put(0x2800000+0x13d0,c['delay'])
  # Rules storage must not overlap the bounded arena's guard. Separate supplied block.
  u.mem_write(0x852998,bytes(12));u.mem_write(0x865f20,bytes(12));u.mem_write(0xad04c0,bytes(12));u.mem_write(0xad0488,bytes(4));self.put(0xad0588,c['project_height']);self.put(0x850c40,c['floor_height']);self.put(0xa72f40,c['layer_height'])
  u.mem_write(0x850bb8,b'\0');u.mem_write(0x850ba8,bytes(8));u.mem_write(0x850bd0,bytes(8));u.mem_write(PLANES,struct.pack('<100d',1.,*([0.]*99)))
  raw=c['objects'][0][4];control=0xa403b0+32*raw;u.mem_write(control+9,bytes([c['control9']]));u.mem_write(control+7,bytes([c['control7']]))
  self.put(0xa3d290,STATE-0x218);u.mem_write(STATE,bytes([c['disabled']])+b'\xa5'*3+struct.pack('<ii250I',c['next1'],c['next2'],*c['table']))
  self.prepare_join(c)
  self.expected=bytearray(u.mem_read(ARENA,SIZE))
  for self.action in c['actions']:
   awayx,awayy,awayz,ignoreMission,ignoreDestination,tick=self.action;u.mem_write(POINT,pack(awayx,awayy,awayz));self.expected[POINT-ARENA:POINT-ARENA+12]=pack(awayx,awayy,awayz);self.put(0xa40d2c,tick);before=bytes(u.mem_read(FALLBACK,0x148));self.active=True
   try:
    self.checked_call(*self.original_entry(c),writes=[(ARENA,SIZE),(0xa6eb14,4),(FALLBACK+0x24,4),(0x850bb8,1),(0x850ba8,8),(0x850bd0,8),(PLANES,800)],inputs=[*self.ranges.items(),*self.tables.items(),(SLOTS,0x100000),(MAP+0xf0,24),(MAP+0x138,8),(0x8661cc,16),(0xa40774,4),(0x851a70,32),(0x850ea0,12*9*4),(0x852998,12),(0x865f20,12),(0xad04c0,12),(0xad0488,4),(0xad0588,4),(0x850c40,4),(0xa72f40,4),(control,32),(0xa3d290,4),(0xa40d2c,4),(0x839848,4),(0x2800000,0x4000)])
    if c['projection']:self.returned(STOP,STACK+12)
   finally:self.active=False
   assert not self.pending and self.context=='s'
   assert bytes(u.mem_read(ARENA,SIZE))==bytes(self.expected),'Joined Scatter whole arena changed'
   after=bytearray(u.mem_read(FALLBACK,0x148));after[0x24:0x28]=before[0x24:0x28];assert bytes(after)==before
  self.event('state',signed(self.word(ACTOR+0xa0)),self.byte(ACTOR+0xa4),self.word(0xa6eb14),self.word(DRIVE+0x14),self.byte(ACTOR+0x190),signed(self.word(ACTOR+0x490)),self.tid(self.word(ACTOR+0x494)),self.byte(ACTOR+0x598),self.byte(ACTOR+0x5a1),int(self.word(ACTOR+0x47c)!=0),signed(self.word(ACTOR+0x480)),signed(self.word(ACTOR+0x488)),self.byte(ACTOR+0x485),*self.coord(DRIVE+0x34),*struct.unpack('<24i',u.mem_read(ACTOR+0x4d0,96)),*self.coord(ACTOR+0x530),*self.coord(ACTOR+0x558),*self.cell(FALLBACK+0x24),self.byte(0x850bb8),*struct.unpack('<Q',u.mem_read(0x850ba8,8)),*struct.unpack('<Q',u.mem_read(0x850bd0,8)),*struct.unpack('<100Q',u.mem_read(PLANES,800)),signed(self.word(STATE+4)),signed(self.word(STATE+8)),*struct.unpack('<250I',u.mem_read(STATE+12,1000)))
  self.event('retained',*self.coord(ACTOR+0x88),*self.coord(DRIVE+0x40),signed(self.word(DRIVE+0x58)),signed(self.word(DRIVE+0x5c)),signed(self.word(DRIVE+0x4c)),self.byte(DRIVE+0x63),*struct.unpack('<Q',u.mem_read(DRIVE+0x50,8)))
  self.append_join_state(c)
  return self.events
