# SPDX-License-Identifier: GPL-3.0-or-later
"""Unmodified complete6D1510 with explicit child services and actual Building brightness/predicates/Type getter/height/FTOL."""
import struct
from collections import Counter
from original_presentation import PresentationOracle,STOP
from techno_sprite_fields import FIELDS
from verify_techno_sprite import verify,RANGES,TABLES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_READ,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_EDX,UC_X86_REG_ESP,UC_X86_REG_EIP
BASE=0x4900000;SIZE=0x60000;ACTOR=BASE+0x1000;TYPE=BASE+0x4000;FOOT=BASE+0x6000;CELLS=[BASE+0x8000,BASE+0x8200];IMAGE=BASE+0xa000;POINT=BASE+0x10000;CLIP=BASE+0x10100;OBJECTS=[BASE+0x12000,BASE+0x12200];VT=BASE+0x14000;STUB=BASE+0x15000;HOUSES=[BASE+0x18000,BASE+0x30000];SCHEMES=[BASE+0x50000,BASE+0x51000];SCHEME_TABLE=BASE+0x54000;CONVERTERS=[0]+[BASE+0x56000+i*0x100 for i in range(1,5)];SURFACE=BASE+0x57000
class TechnoSpriteOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(BASE,SIZE);self.active=False;self.counts=Counter()
  self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_READ,self.read);self.u.hook_add(UC_HOOK_MEM_WRITE,self.store)
 def va(self,a):return a
 def word(self,p):return int.from_bytes(self.u.mem_read(p,4),'little')
 def signed(self,v):return (v+2**31)%2**32-2**31
 def event(self,*v):self.trace.extend(map(str,(*v,*([0]*(4-len(v))))))
 def ret(self,pop=0,value=0):
  sp=self.u.reg_read(UC_X86_REG_ESP);self.u.reg_write(UC_X86_REG_EAX,value&0xffffffff);self.u.reg_write(UC_X86_REG_EIP,self.word(sp));self.u.reg_write(UC_X86_REG_ESP,sp+4+pop)
 def conv(self,p):return CONVERTERS.index(p)
 def change(self,p,v,n=4):
  b=(v&((1<<(n*8))-1)).to_bytes(n,'little');self.u.mem_write(p,b)
  if BASE<=p<BASE+SIZE:self.expected[p-BASE:p-BASE+n]=b
  else:self.globals[p]=b
 def mutate(self,mode,local=None):
  if self.mutated or self.f['mutation']!=mode:return
  self.mutated=True;self.event(8,mode)
  if mode==1:self.change(0x7d88d5,0,1);self.change(ACTOR+0x1bc,1)
  if mode==2:self.kind=2;self.change(TYPE+0xb48,128,1)
  if mode==3:self.change(CELLS[0]+0x34,0)
  if mode==4:
   assert local;self.u.mem_write(local,struct.pack('<ii',71,72));self.change(CLIP,99);self.change(CLIP+4,98);self.change(CLIP+8,97);self.change(CLIP+12,96)
   self.change(IMAGE+6,-3,2);self.change(ACTOR+0x37c,255,1);self.change(0x7d88d5,0,1);self.change(TYPE+0xb48,255,1);self.change(CELLS[0]+0x34,CONVERTERS[4])
  if mode==5:self.change(SCHEMES[0]+0x30c,CONVERTERS[4]);self.change(TYPE+0xb48,255,1)
  if mode==6:self.change(0x7d88d5,0,1);self.change(ACTOR+0x37c,128,1)
  if mode==7:self.height=self.signed(self.height+104)
  if mode==8:self.change(CELLS[0]+0x10c,-32768,2)
 def read(self,u,access,p,n,v,_):
  if not self.active or not 0x6d1510<=u.reg_read(UC_X86_REG_EIP)<0x6d1ccb:return
  def value(signed=False):return int.from_bytes(u.mem_read(p,n),'little',signed=signed)
  if p in (ACTOR+0x1bc,ACTOR+0x5bb,ACTOR+0x37c):self.event(1,1,p-ACTOR,value(n==4))
  if p in (TYPE+0x1386,TYPE+0xb48):self.event(1,0,p-TYPE,value())
  if p in (FOOT+0xbb0,FOOT+0xbb1):self.event(1,3,p-FOOT,value())
  if p in [c+0x10c for c in CELLS]:self.event(1,2,0x10c,value(True))
  if p in (IMAGE+2,IMAGE+4,IMAGE+6):self.event(1,4,p-IMAGE,value(True))
  if IMAGE+8<=p<IMAGE+8+32*24 and (p-IMAGE-8)%24 in (0,2,4,6):self.event(1,5,p-IMAGE-8,value(True))
  if 0xac0138<=p<=0xac0144:self.event(1,6,p-0xac0138,value(True))
  if 0xad0490<=p<=0xad049c:self.event(1,7,p-0xad0490,value(True))
  if p==0x7d88d5:self.event(1,8,p,value())
  if p==0xad0608:self.event(1,8,p,self.conv(value()))
  if p==0xa35db4:self.event(1,8,p,HOUSES.index(value())+1)
  if p==0x83995c:assert value()==SURFACE;self.event(1,8,p,1)
  if p in [s+0x30c for s in SCHEMES]:self.event(1,9,SCHEMES.index(p-0x30c)+1,self.conv(value()))
 def store(self,u,access,p,n,v,_):
  if self.active and 0xad0490<=p<=0xad049c:
   assert n==4;self.event(2,7,p-0xad0490,self.signed(v));self.globals[p]=struct.pack('<I',v&0xffffffff)
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  sp=u.reg_read(UC_X86_REG_ESP);arg=lambda i:self.word(sp+4+4*i);receiver=u.reg_read(UC_X86_REG_ECX);f=self.f
  if any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()):
   if a in RANGES:self.counts[hex(a)]+=1
   if a==0x4521b0:
    assert receiver==ACTOR;self.brightnessInput=self.signed(arg(0))
   if a in (0x4521cd,0x4521d5):
    self.event(3,0x3f8,self.brightnessInput,self.signed(u.reg_read(UC_X86_REG_EAX)));self.mutate(6)
   for target,slot,key in ((0x6d6df0,0x1bc,'p1bc'),(0x6d6e00,0x1c0,'p1c0'),(0x41b410,0xc0,'pC0')):
    if a==target:assert receiver==ACTOR;self.event(3,slot,0,f[key])
   if a==0x6c12c0:assert receiver==ACTOR;self.event(3,0x80)
   if a==0x6a2970:self.event(3,a,self.signed(receiver))
   return
  self.counts[hex(a)]+=1
  if a==0x44f600:assert receiver==ACTOR and arg(0)==arg(1)==0;self.event(3,0x64,0,f['mode']);self.mutate(1);self.ret(8,f['mode']);return
  for target,slot,key in ((0x41b390,0x32c,'p32c'),):
   if a==target:assert receiver==ACTOR;self.event(3,slot,0,f[key]);self.ret(value=f[key]);return
  if a==0x453c40:assert receiver==ACTOR;self.event(3,0x2c,0,self.kind);self.ret(value=self.kind);return
  if a==self.coordinates:
   assert receiver==ACTOR;self.event(3,0x48);self.mutate(3);u.mem_write(arg(0),struct.pack('<iii',*[f[k] for k in ('coordX','coordY','coordZ')]));self.ret(4,arg(0));return
  if a==0x548070:assert receiver==0x8324e0;self.event(3,a,self.signed(self.word(arg(0))),0);self.ret(4,CELLS[0]);return
  if a==0x4790f0:
   index=CELLS.index(receiver);assert [arg(i) for i in range(6)]==[0,65536,0,1000,1000,1000];self.event(3,a,index,f['initConverter']);self.mutate(8);self.change(receiver+0x34,CONVERTERS[f['initConverter']]);self.ret(24);return
  if a==0x6d1480:assert receiver==ACTOR;self.event(3,0x1cc,0,f['converter']);self.mutate(2);self.ret(value=CONVERTERS[f['converter']]);return
  if a==0x5d4800:
   assert receiver==ACTOR;v=self.height;self.event(3,0x1b8,self.heightCalls,v);self.heightCalls+=1;self.mutate(7);self.ret(value=v);return
  if a==self.target:
   assert receiver==ACTOR;self.event(3,0x1b0,0,f['target']);self.ret(value=f['target']);return
  if a==self.depth:assert receiver==ACTOR;self.event(3,0x2c0,0,f['depth']);self.ret(value=f['depth']);return
  if a==0x6d8ce0:assert receiver==ACTOR and arg(0)==HOUSES[0];self.event(3,0x3d4,1,f['ownerPredicate']);self.mutate(5);self.ret(4,f['ownerPredicate']);return
  if a==0x41b2d0:
   assert receiver==ACTOR and arg(0)==1;index=min(self.objectCalls,1);self.objectCalls+=1;self.event(3,0xc8,1,index+1);self.ret(4,OBJECTS[index]);return
  if a==STUB:
   index=OBJECTS.index(receiver);k=f['objectKind1' if index==0 else 'objectKind2'];self.event(3,0x2c,index+1,k);self.ret(value=k);return
  if a==0x41b2e0:assert receiver==ACTOR and arg(0)==1;self.event(3,0xcc,1,2);self.ret(4,HOUSES[1]);return
  if a==0x5d51e0:assert receiver==ACTOR;self.event(3,0x1a4,0,1);self.ret(value=CELLS[1]);return
  if a==0x4f52b0:assert receiver==HOUSES[1];self.event(3,a,2,f['ownedHousePredicate']);self.ret(value=f['ownedHousePredicate']);return
  if a==0x6d8c30:
   value=self.signed(arg(0));result=self.signed(arg(0)^f['flagsXor']);self.event(3,0x3d0,value,result);self.ret(4,result);return
  if a==0x6d86f0:
   value=self.signed(arg(0));result=self.signed(value+f['statusAdd']);self.event(3,a,value,result);self.ret(4,result);return
  if a==0x49eea0:
   assert receiver==SURFACE and arg(0)==IMAGE and arg(2)!=POINT and arg(3)==CLIP
   args=[1,self.signed(arg(1)),101,102,*[self.signed(arg(i)) for i in range(4,13)],self.conv(u.reg_read(UC_X86_REG_EDX))]
   for i,v in enumerate(args):self.event(4,i,v)
   for i,v in enumerate(struct.unpack('<ii',u.mem_read(arg(2),8))+struct.unpack('<iiii',u.mem_read(CLIP,16))):self.event(7,i,v)
   if not self.draws:self.mutate(4,arg(2))
   self.draws+=1;self.ret(52);return
  raise AssertionError(('Uninspected Techno sprite instruction',hex(a)))
 def run(self,values):
  self.f=f=dict(zip(FIELDS,values));self.kind=f['kind'];self.height=f['height'];self.trace=[];self.draws=self.objectCalls=self.heightCalls=0;self.mutated=False
  self.u.mem_write(BASE,b'\x5a'*SIZE);self.put(ACTOR,0x79cbbc);self.put(ACTOR+0x418,TYPE);self.put(ACTOR+0x5ac,FOOT);self.put(ACTOR+0x1bc,f['field1bc']);self.put(ACTOR+0x1b4,HOUSES[1])
  self.put(ACTOR+0xd8,f['flagsD8'])
  for off,k in ((0x204,'p1bc'),(0x205,'p1c0'),(0x170,'pC0'),(0x5bb,'flag5bb'),(0x37c,'flag37c')):self.u.mem_write(ACTOR+off,bytes([f[k]]))
  for p,k in ((TYPE+0x1386,'building1386'),(TYPE+0xb48,'typeB48'),(FOOT+0xbb0,'footBB0'),(FOOT+0xbb1,'footBB1')):self.u.mem_write(p,bytes([f[k]]))
  for i,c in enumerate(CELLS):self.put(c+0x34,CONVERTERS[f['cellConverter']]);self.u.mem_write(c+0x10c,struct.pack('<H',(f['cellTerrain']+i*17)&65535))
  self.u.mem_write(IMAGE,struct.pack('<4H',0,f['width']&65535,f['heightCanvas']&65535,f['count']&65535))
  for i in range(32):self.u.mem_write(IMAGE+8+i*24,struct.pack('<4h',*[f[k] for k in ('rectX','rectY','rectW','rectH')]))
  self.u.mem_write(POINT,struct.pack('<ii',f['pointX'],f['pointY']));self.u.mem_write(CLIP,struct.pack('<iiii',*[f[k] for k in ('clipX','clipY','clipW','clipH')]))
  self.u.mem_write(0xac0138,struct.pack('<iiii',*[f[k] for k in ('emptyX','emptyY','emptyW','emptyH')]));self.u.mem_write(0xad0490,struct.pack('<iiii',*[f[k] for k in ('boundX','boundY','boundW','boundH')]))
  self.u.mem_write(0x7d88d5,bytes([f['shadow']]));self.put(0xad0608,CONVERTERS[4]);self.put(0x83995c,SURFACE);self.put(0xa35db4,HOUSES[0]);self.put(0xab6efc,SCHEME_TABLE);self.u.mem_write(0xabe490,struct.pack('<d',.125))
  for i in range(2):self.put(OBJECTS[i],VT);self.put(HOUSES[i]+0x15f40,i);self.put(SCHEME_TABLE+4*i,SCHEMES[i]);self.put(SCHEMES[i]+0x30c,CONVERTERS[f['currentConverter' if i==0 else 'houseConverter']])
  self.put(VT+0x2c,STUB)
  self.coordinates=self.word(0x79cbbc+0x48);self.target=self.word(0x79cbbc+0x1b0);self.depth=self.word(0x79cbbc+0x2c0)
  self.expected=bytearray(self.u.mem_read(BASE,SIZE));self.globals={p:bytes(self.u.mem_read(p,n)) for p,n in [(0x7d88d5,1),(0xad0490,4),(0xad0494,4),(0xad0498,4),(0xad049c,4)]}
  args=[IMAGE if f['image'] else 0,f['frame'],POINT,CLIP,0,f['flags'],f['adjust'],f['gradient'],f['raw8'],f['light'],f['extra'],f['tail0'],f['tailX'],f['tailY'],f['mask']]
  self.active=True
  try:self.checked_call(0x6d1510,args,ACTOR,writes=[(0xad0490,16)],inputs=[*RANGES.items(),*TABLES.items(),(0x79cbbc,0x400)])
  finally:self.active=False
  assert self.u.mem_read(BASE,SIZE)==self.expected,'Unrelated sprite arena changed'
  for p,b in self.globals.items():assert self.u.mem_read(p,len(b))==b,('Unrelated global changed',hex(p))
  tail=[*struct.unpack('<ii',self.u.mem_read(POINT,8)),*struct.unpack('<iiii',self.u.mem_read(CLIP,16)),*struct.unpack('<iiii',self.u.mem_read(0xad0490,16)),self.draws,self.signed(self.word(ACTOR+0x1bc)),self.u.mem_read(ACTOR+0x5bb,1)[0],self.u.mem_read(ACTOR+0x37c,1)[0],self.kind,self.height,struct.unpack('<h',self.u.mem_read(IMAGE+6,2))[0],self.u.mem_read(0x7d88d5,1)[0],self.u.mem_read(TYPE+0xb48,1)[0],self.conv(self.word(SCHEMES[0]+0x30c)),*[self.conv(self.word(c+0x34)) for c in CELLS],*[struct.unpack('<h',self.u.mem_read(c+0x10c,2))[0] for c in CELLS]]
  self.trace+=['F',*map(str,tail)];return self.trace
