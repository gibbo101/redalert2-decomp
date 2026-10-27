# SPDX-License-Identifier: GPL-3.0-or-later
"""Unchanged Unit Scatter parent; explicit unjoined world/service boundaries."""
import struct
from collections import Counter
from original_presentation import PresentationOracle,STOP,STACK
from verify_unit_scatter import verify,RANGES,SERVICES,TABLES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_EIP,UC_X86_REG_ECX,UC_X86_REG_ESP
ARENA=0x2800000;SIZE=0x10000;ACTOR=ARENA+0x1000;TYPE=ARENA+0x3000
DRIVE=ARENA+0x4000;POINT=ARENA+0x5000;STATE=ARENA+0x6000;CELLS=ARENA+0x7000
ATOMIC_INC=0x3c7594;ATOMIC_DEC=0x3c757c
def signed(v):return v if v<0x80000000 else v-0x100000000
def short(v):return (v+32768)%65536-32768
class UnitScatterOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True)
  self.u.mem_map(ARENA,SIZE);self.u.mem_map(0x3c7000,0x1000)
  self.active=False;self.counts=Counter();self.instructions=set();self.writes=Counter()
  self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.store)
 def va(self,a):return a
 def word(self,p):return int.from_bytes(self.u.mem_read(p,4),'little')
 def coord(self,p):return struct.unpack('<3i',self.u.mem_read(p,12))
 def cell(self,p):return struct.unpack('<2h',self.u.mem_read(p,4))
 def event(self,*v):self.events.extend(map(str,v))
 def supplied_write(self,p,data):
  self.u.mem_write(p,data)
  if ARENA<=p and p+len(data)<=ARENA+SIZE:self.expected[p-ARENA:p-ARENA+len(data)]=data
 def ret(self,n,value=0):
  sp=self.u.reg_read(UC_X86_REG_ESP);target=self.word(sp);self.u.reg_write(UC_X86_REG_EAX,value&0xffffffff)
  self.u.reg_write(UC_X86_REG_ESP,sp+4+n);self.u.reg_write(UC_X86_REG_EIP,target)
 def service(self,a):
  u=self.u;sp=u.reg_read(UC_X86_REG_ESP);arg=lambda i:self.word(sp+4+4*i);name=SERVICES[a];self.counts[name]+=1
  if name=='coordinates':
   assert u.reg_read(UC_X86_REG_ECX)==ACTOR and arg(1)==0
   assert STACK-0x2000<=arg(0) and arg(0)+12<=STACK
   self.event('Q',*self.coordinates);self.supplied_write(arg(0),struct.pack('<3i',*self.coordinates));self.ret(8,arg(0))
  elif name=='lookup':
   assert u.reg_read(UC_X86_REG_ECX)==0x8324e0;p=self.cell(arg(0));self.event('L',*p,0)
   if p not in self.cell_ids:
    idx=len(self.cell_ids);assert idx<16;self.cell_ids[p]=idx;address=CELLS+idx*0x200
    # Supplied map records, not new parent writes.
    self.supplied_write(address+0x11b,bytes([self.current_level&255]));self.supplied_write(address+0x140,struct.pack('<I',self.flags_for(p)))
   self.ret(4,CELLS+self.cell_ids[p]*0x200)
  elif name=='layer':self.event('Y',self.layer,0,0);self.ret(4,self.layer)
  elif name=='bounds':
   p=self.cell(arg(0));assert arg(1)==1;d=self.direction_for(p);v=self.bounds[d];self.event('N',*p,v);self.ret(8,v)
  elif name=='level':self.event('V',self.level,0,0);self.ret(0,self.level)
  elif name=='admission':
   target,d,level,previous,consult=[arg(i) for i in range(5)]
   assert previous==0 and consult==1 and signed(level)==self.level
   p=next(p for p,i in self.cell_ids.items() if target==CELLS+i*0x200);assert self.direction_for(p)==d
   self.event('A',d,self.level,self.admissions[d]);self.ret(20,self.admissions[d])
  elif name=='projection':
   point=self.coord(arg(1));p=tuple(short((n-128)//256) for n in point[:2]);d=self.direction_for(p)
   self.event('P',*point);out=p if self.projections[d] else (short(p[0]+17),p[1])
   u.mem_write(arg(0),struct.pack('<2h',*out));self.ret(8,arg(0))
  elif name=='pathfinder':
   args=[arg(i) for i in range(14)];start=self.cell(args[1]);zero=self.cell(args[12])
   rawbridge=(int(self.coordinates[1]/256)&0xffffff00)|self.bridge
   assert len({args[0],args[1],args[12]})==3
   assert all(STACK-0x2000<=p and p+4<=STACK+16 for p in (args[0],args[1],args[12]))
   assert args[2:12]==[self.type5a4&0xffffffff,0xffffffff,0,rawbridge,1,1,0,1,0,1] and args[13]==0 and zero==(0,0)
   self.event('p',*start,self.type5a4,rawbridge);u.mem_write(args[0],struct.pack('<2h',*self.path_result));self.ret(56,args[0])
  elif name=='destination':
   target=arg(0);assert arg(1)==1
   p=next(p for p,i in self.cell_ids.items() if target==CELLS+i*0x200);self.event('S',*p,1);self.ret(8)
  else:raise AssertionError(name)
 def direction_for(self,p):
  center=tuple(short(int(n/256)) for n in self.coordinates[:2])
  return next(i for i,(x,y) in enumerate(self.neighbors) if (short(center[0]+x),short(center[1]+y))==p)
 def flags_for(self,p):
  try:return self.flags[self.direction_for(p)]
  except StopIteration:return 0
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  if a in SERVICES:self.service(a);return
  if a in (ATOMIC_INC,ATOMIC_DEC):
   sp=u.reg_read(UC_X86_REG_ESP);p=self.word(sp+4);assert p==DRIVE+0x14
   value=(self.word(p)+(1 if a==ATOMIC_INC else -1))&0xffffffff
   assert value>0;self.supplied_write(p,struct.pack('<I',value));self.event('I',value,0,0);self.counts['atomic_inc' if a==ATOMIC_INC else 'atomic_dec']+=1;self.ret(4,value);return
  assert any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected Scatter instruction',hex(a))
  self.instructions.add(a)
  if a in RANGES:self.counts[hex(a)]+=1
  if a==0x594770:self.event('M',signed(self.word(ACTOR+0xa0) if self.word(ACTOR+0x98)==0xffffffff else self.word(ACTOR+0x98)),0,0)
  elif a==0x705020:self.event('T',0,0,0)
  elif a==0x70733e:self.event('G',0,0,0)
  elif a in (0x707375,0x7074f5):
   off=9 if a==0x707375 else 7;control=u.reg_read(UC_X86_REG_EAX);raw=signed(self.word(ACTOR+0x98))
   assert control==((0xa403b0+(raw<<5))&0xffffffff);self.event('H',raw,off,int.from_bytes(u.mem_read(control+off,1),'little'))
   if off==7 and self.mutate_point:self.supplied_write(POINT,struct.pack('<3i',0,0,0));self.event('m',0,0,0)
  elif a==0x707391:self.event('F',u.reg_read(UC_X86_REG_EAX)&255,0,0)
  elif a==0x70a2d0:self.event('K',1,0,0)
  elif a in (0x7075fd,0x70763b):self.event('B' if a==0x7075fd else 'J',u.reg_read(UC_X86_REG_EAX)&65535 if a==0x7075fd else self.word(u.reg_read(UC_X86_REG_EAX))&65535,0,0)
  elif a==0x6388a0:
   sp=u.reg_read(UC_X86_REG_ESP);self.range=(signed(self.word(sp+4)),signed(self.word(sp+8)))
  elif a==0x63893e:self.event('D',u.reg_read(UC_X86_REG_EAX),signed(self.word(STATE+4)),signed(self.word(STATE+8)))
  elif a in (0x707579,0x707618,0x70765b):self.event('R',*self.range,signed(u.reg_read(UC_X86_REG_EAX)))
  elif a==0x594cb0:
   sp=u.reg_read(UC_X86_REG_ESP);assert self.word(sp+4)==2 and self.word(sp+8)==0;self.event('q',2,0,0)
 def store(self,u,access,p,n,v,_):
  if not self.active:return
  a=u.reg_read(UC_X86_REG_EIP)
  if p==0xa6eb14:
   assert n==4 and a in (0x53d25f,0x53d280)
   assert v&0xffffffff==(self.word(p)+(1 if a==0x53d25f else -1))&0xffffffff
   self.event('C',v&0xffffffff,0,0)
  if a in (0x594ce4,0x594cea):
   assert (p,n)==(ACTOR+(0xa0 if a==0x594ce4 else 0xa4),4 if a==0x594ce4 else 1)
   assert v==(2 if a==0x594ce4 else 0);self.event('W',p-ACTOR,v,0)
  if ARENA<=p and p+n<=ARENA+SIZE:
   if a in SERVICES or a in (ATOMIC_INC,ATOMIC_DEC):pass # named supplied service writes, checked at call site
   elif 0x6388a0<=a<0x63894d:
    assert n==4
    if a==0x63890b:
     first,second=self.word(STATE+4),self.word(STATE+8)
     assert p==STATE+12+4*first and v==self.word(STATE+12+4*first)^self.word(STATE+12+4*second)
    elif a in (0x63891e,0x638921):assert p==STATE+(4 if a==0x63891e else 8) and v==self.word(p)+1
    elif a in (0x638926,0x638935):assert p==STATE+(4 if a==0x638926 else 8) and self.word(p)==250 and v==0
    else:raise AssertionError(('Unexpected Scatter RNG store',hex(a),hex(p),n))
   elif a in (0x594ce4,0x594cea):pass
   else:raise AssertionError(('Unexpected Scatter arena store',hex(a),hex(p),n))
   self.expected[p-ARENA:p-ARENA+n]=int(v&((1<<(8*n))-1)).to_bytes(n,'little');self.writes[hex(a)]+=1
 def run(self,c):
  u=self.u;u.mem_write(ARENA,b'\xa5'*SIZE);self.events=[];self.cell_ids={}
  self.coordinates=c['coordinates'];self.neighbors=c['neighbors'];self.current_level=c['current_level'];self.layer=c['layer'];self.level=c['level'];self.flags=c['flags'];self.bounds=c['bounds'];self.admissions=c['admissions'];self.projections=c['projections'];self.path_result=c['path_result'];self.type5a4=c['type5a4'];self.bridge=c['bridge'];self.mutate_point=c['mutate_point']
  self.put(ACTOR,0x7addf8);self.put(ACTOR+0x5ac,TYPE);self.put(ACTOR+0x564,DRIVE+4)
  for off,key in ((0x98,'mission'),(0xa0,'queued')):self.put(ACTOR+off,c[key])
  for off,key in ((0xa4,'queued_byte'),(0x5c8,'field5c8'),(0x5b9,'field5b9'),(0x599,'field599'),(0x79,'bridge')):u.mem_write(ACTOR+off,bytes([c[key]]))
  self.put(ACTOR+0x494,ARENA if c['destination'] else 0);self.put(ACTOR+0x228,ARENA if c['target'] else 0)
  u.mem_write(ACTOR+0x88,struct.pack('<3i',*c['position']));u.mem_write(ACTOR+0x2e0,struct.pack('<IIiiii',c['desired'],c['start'],c['timer'],0,c['duration'],c['rate']))
  u.mem_write(TYPE+0xaa0,bytes([c['train']]));self.put(TYPE+0x5a4,c['type5a4'])
  self.put(DRIVE,0x7a0594);self.put(DRIVE+4,0x7a04cc);self.put(DRIVE+0x18,0x7a04a8);self.put(DRIVE+0x14,c['references']);self.put(DRIVE+0xc,ACTOR)
  self.put(0xa6eb14,c['global_references']);self.put(0xa40d2c,c['tick']);self.put(0xad0588,c['height'])
  u.mem_write(0x851a70,struct.pack('<16h',*[n for p in c['neighbors'] for n in p]));u.mem_write(0xad0488,struct.pack('<2h',*c['empty_cell']));u.mem_write(0xad04c0,bytes(12));u.mem_write(POINT,struct.pack('<3i',*c['away']))
  control=0xa403b0+32*c['mission'];u.mem_write(control+9,bytes([c['control9']]));u.mem_write(control+7,bytes([c['control7']]))
  self.put(0xa3d290,STATE-0x218);u.mem_write(STATE,bytes([c['disabled']])+b'\xa5'*3+struct.pack('<ii250I',c['next1'],c['next2'],*c['table']))
  self.expected=bytearray(u.mem_read(ARENA,SIZE));self.active=True
  try:
   for call in range(c['repeats']):
    self.checked_call(0x7072d0,[POINT,c['ignore_mission'],c['ignore_destination']],ACTOR,
     writes=[(ARENA,SIZE),(0xa6eb14,4)],inputs=[*RANGES.items(),*TABLES.items(),(0x851a70,32),(0xad0488,4),(0xad04c0,12),(control,32),(0xa40d2c,4),(0xad0588,4),(0xa3d290,4)])
  finally:self.active=False
  assert bytes(u.mem_read(ARENA,SIZE))==bytes(self.expected),'Unexpected whole Scatter arena change'
  self.event('state',signed(self.word(ACTOR+0xa0)),int.from_bytes(u.mem_read(ACTOR+0xa4,1),'little'),self.word(0xa6eb14),self.word(DRIVE+0x14),signed(self.word(STATE+4)),signed(self.word(STATE+8)),*self.coord(POINT),*struct.unpack('<250I',u.mem_read(STATE+12,1000)))
  return self.events
