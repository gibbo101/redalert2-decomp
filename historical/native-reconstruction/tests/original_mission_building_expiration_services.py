# SPDX-License-Identifier: GPL-3.0-or-later
"""Unmodified shared Radio/Techno expiration on private mutable owners."""
import struct
from collections import Counter
from original_land_characteristics import push_double
from original_presentation import PresentationOracle,STOP,STACK
from verify_mission_building_expiration_services import verify,RANGES,TABLES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EIP
ARENA=0x3800000;SIZE=0x120000;ACTOR=ARENA;TAGS=(ARENA+0x1000,ARENA+0x2000);NODE=ARENA+0x3000;OWNER=ARENA+0x4000;CONTROL=ARENA+0x5000;SERVICEA=ARENA+0x6000;SERVICEB=ARENA+0x7000;EXTRA=ARENA+0x8000
VT=ARENA+0x9000;TAG_VT=ARENA+0xa000;BUFFERS=[ARENA+0xb000+i*0x100 for i in range(4)];ALTERNATE=ARENA+0xb800;STUBS=ARENA+0xc000;SCENARIO=ARENA+0xd000
MAP_TABLE=ARENA+0x10000;CELLS=ARENA+0x111000;FALLBACK=0xa6f9f8;TYPE15=ARENA+0x114000;TYPE16=ARENA+0x116000;RULES=ARENA+0x118000;EXTRA_BUFFERS=[ARENA+0xe000+i*0x100 for i in range(3)]
POINTERS=(0,*TAGS,NODE,ACTOR,OWNER,CONTROL,SERVICEA,SERVICEB,EXTRA,*[CELLS+i*0x200 for i in range(4)],FALLBACK,TYPE15,TYPE16)
TYPED_OFFSETS=(0x418,0x41c,0x438,0x440,0x474,0x490,0x494,0x498,0x4b8,0x4bc,0x4c0,0x4c4,0x4c8,0x4d4,0x4e8,0x580,0x5a8)
EXTRA_VECTORS=(ACTOR+0x49c,ACTOR+0x478,ACTOR+0x53c)
EXTRA_COUNTS=(ACTOR+0x4ac,ACTOR+0x488,ACTOR+0x54c)
TYPE_IDS=(1,2,9,15,16)
OFFSETS=(0xfc,0x108,0x1b0,0x1b4,0x208,0x20c,0x228,0x22c,0x230,0x238,0x23c,0x27c,0x384,0x3f8,0x30)
VECTORS=(ACTOR+0xc8,ACTOR+0x390,ACTOR+0x3a8,ACTOR+0x3c0)
# Radio count is +D0 (8 from this view); the three DynamicVectors use +10.
COUNTS=(ACTOR+0xd0,ACTOR+0x3a0,ACTOR+0x3b8,ACTOR+0x3d0)
NUMERIC=(0x148,0x14c,0x150,0x98,0xa8)
SERVICES=('owner','target','predicate1','action1','kind','predicateC','query','action400')
def signed(v):return v if v<2**31 else v-2**32
class MissionBuildingExpirationServicesOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(ARENA,SIZE);self.active=False;self.counts=Counter();self.stores=Counter();self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.store)
 def va(self,a):return a
 def word(self,p):return int.from_bytes(self.u.mem_read(p,4),'little')
 def identity(self,p):assert p in POINTERS,hex(p);return POINTERS.index(p)
 def put(self,p,value):
  super().put(p,value)
  if getattr(self,'active',False) and ARENA<=p<=ARENA+SIZE-4:self.expected[p-ARENA:p-ARENA+4]=struct.pack('<I',value&0xffffffff)
 def ret(self,n,value=0):
  sp=self.u.reg_read(UC_X86_REG_ESP);target=self.word(sp);self.u.reg_write(UC_X86_REG_ESP,sp+4+n);self.u.reg_write(UC_X86_REG_EAX,value&0xffffffff);self.u.reg_write(UC_X86_REG_EIP,target)
 def store(self,u,access,p,n,value,_):
  if self.active and self.f['profile'] and p-ACTOR in (0x98,0x9c,0xa4,0x404,0x310):
   assert n==(1 if p-ACTOR in (0xa4,0x404) else 4);v=value&((1<<(8*n))-1);self.stores[hex(u.reg_read(UC_X86_REG_EIP))]+=1
   self.trace.extend(('W','4',str(p-ACTOR),str(v)));self.expected[p-ARENA:p-ARENA+n]=v.to_bytes(n,'little');return
  if not self.active:return
  if p==FALLBACK+0x24:
   assert n==4 and u.reg_read(UC_X86_REG_EIP)==0x54809f;x,y=struct.unpack('<hh',struct.pack('<I',value&0xffffffff));self.trace.extend(('MAPF',str(x),str(y)));return
  if not ARENA<=p<p+n<=ARENA+SIZE:return
  pc=u.reg_read(UC_X86_REG_EIP);self.stores[hex(pc)]+=1;v=value&((1<<(8*n))-1);identity=offset=None;out=v
  if p in (TAGS[0]+0x2c,TAGS[1]+0x2c):assert pc==0x5d3be4 and n==4;identity=self.identity(p-0x2c);offset=0x2c
  elif p==ACTOR+0x34:assert pc==0x5d3be7 and n==4;identity=4;offset=0x34;out=self.identity(v)
  elif p in (TAGS[0]+0x30,TAGS[1]+0x30,NODE+0x30):assert pc==0x468aab and n==4;identity=self.identity(p-0x30);offset=0x30;out=self.identity(v)
  elif p in (CONTROL+0x24,CONTROL+0x28):assert n==4 and pc in (0x46812d,0x468130);identity=6;offset=p-CONTROL;out=self.identity(v)
  elif p in EXTRA_COUNTS:assert n==4;identity=30+EXTRA_COUNTS.index(p);offset=16
  elif any(base<=p<base+32 for base in EXTRA_BUFFERS):
   base=next(base for base in EXTRA_BUFFERS if base<=p<base+32);assert n==4 and (p-base)%4==0;identity=30+EXTRA_BUFFERS.index(base);offset=0x100+p-base;out=self.identity(v)
  elif p in COUNTS[1:]:assert n==4;identity=20+COUNTS.index(p);offset=16
  elif any(base<=p<base+32 for base in (*BUFFERS,ALTERNATE)):
   base=next(base for base in (*BUFFERS,ALTERNATE) if base<=p<base+32);assert n==4 and (p-base)%4==0;identity=22 if base==ALTERNATE else 20+BUFFERS.index(base);offset=0x100+p-base;out=self.identity(v)
  elif ACTOR<=p<ACTOR+0x800:
   identity=4;offset=p-ACTOR
   if offset in (*OFFSETS,*TYPED_OFFSETS,0x25c,0x260,0x264,0x268,0x26c,0x270,0x274,0x278):assert n==4;out=self.identity(v)
   else:assert offset in (0x148,0x14c,0x150,0xa8,0x372,0x5ba) and n==(1 if offset in (0x372,0x5ba) else 4)
  assert identity is not None,('unexpected Techno store',hex(pc),hex(p),n)
  self.trace.extend(('W',str(identity),str(offset),str(out)));self.expected[p-ARENA:p-ARENA+n]=v.to_bytes(n,'little')
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  sp=u.reg_read(UC_X86_REG_ESP);ecx=u.reg_read(UC_X86_REG_ECX);arg=lambda i:self.word(sp+4+i*4);f=self.f
  if f['profile']:
   if a==0x4e8330:
    self.trace.extend(('B','power',str(self.identity(ecx))));self.counts['supplied.power']+=1
    if f['effectMode']==1:self.put(ACTOR+0x418,TYPE16)
    if f['effectMode']==2:self.put(ACTOR+0x54c,2)
    if f['effectMode']==3:self.put(ACTOR+0x6c,0)
    if f['effectMode']==4:self.put(ACTOR+0x9c,19)
    push_double(u,f['powerBits']);self.ret(0);return
   if a==0x68a490:
    assert ecx==SERVICEA and arg(0)==0;self.trace.extend(('B','clear','7'));self.counts['supplied.clear68A490']+=1
    if f['effectMode']==1:self.put(ACTOR+0x228,TAGS[1])
    if f['effectMode']==2:self.put(ACTOR+0x25c,0)
    if f['effectMode']==3:self.put(ACTOR+0x25c,EXTRA);self.put(ACTOR+0x418,TYPE16)
    if f['effectMode']==4:self.put(ACTOR+0x9c,19);self.put(ACTOR+0x22c,0)
    self.ret(4);return
   if a==STUBS+0x230:
    assert ecx==ACTOR and arg(0)==0;self.trace.extend(('B','index'));self.counts['supplied.weaponIndex']+=1
    if f['effectMode']==3:self.put(ACTOR+0x54c,2)
    self.ret(4,f['policyIndex']);return
   if a==STUBS+0x240:
    assert ecx==ACTOR and arg(0)==0 and arg(1)==f['policyIndex']&0xffffffff;self.trace.extend(('B','permission',str(f['policyIndex'])));self.counts['supplied.weaponPermission']+=1
    if f['effectMode']==4:self.put(ACTOR+0x228,TAGS[1])
    self.ret(8,f['policyByte']);return
   if a==STUBS+0x250:
    assert ecx==EXTRA;self.trace.extend(('B','release','9'));self.counts['supplied.release']+=1
    if f['effectMode']==3:self.put(ACTOR+0x25c,EXTRA);self.put(ACTOR+0x418,TYPE16)
    self.ret(0);return
  if a==STUBS+0x100:
   assert ecx==EXTRA and (arg(0),arg(1))==(TAGS[f['subject']-1],1);self.counts['supplied.nested']+=1;self.trace.extend(('S','nested','9',str(f['subject']),'1'))
   if f['childMode']==3:self.put(ACTOR+0x5a8,TAGS[f['subject']-1]);self.put(ACTOR+0x4bc,TAGS[f['subject']-1])
   self.ret(8);return
  if a==0x6d6e50:
   assert ecx==ACTOR and arg(0)==0;self.counts['supplied.clear1B0']+=1;self.trace.extend(('S','clear1B0','0'))
   if f['childMode']==1:self.put(ACTOR+0x498,TAGS[f['subject']-1])
   self.ret(4);return
  if a==STUBS+0x110:
   assert ecx==ACTOR;self.counts['supplied.strength84']+=1;self.trace.extend(('S','strength',str(f['strengthType'])))
   if f['childMode']==1:self.put(ACTOR+0x6c,99);self.counts['supplied.strength.mode1']+=1
   if f['childMode']==2:self.put(ACTOR+0x418,TYPE16);self.put(RULES+0x1368,0);self.put(RULES+0x136c,0xbff00000);self.counts['supplied.strength.mode2']+=1
   self.ret(0,POINTERS[f['strengthType']]);return
  if a==0x44ca60:
   assert ecx==ACTOR and arg(1)==17 and arg(3)==arg(4)==0;damaged=arg(2);assert damaged in (0,1);off=0x1168 if damaged else 0x1158;ids=[i for i in TYPE_IDS if POINTERS[i]+off==arg(0)];assert len(ids)==1;self.counts['supplied.animation']+=1;self.counts['supplied.animation.'+str(damaged)]+=1;self.trace.extend(('S','animation',str(ids[0]),str(off),str(damaged)))
   if f['childMode']==3:self.put(ACTOR+0x418,TAGS[f['subject']-1])
   self.ret(20);return
  if a==0x4c85a7 and signed(self.word(u.reg_read(UC_X86_REG_EAX)+0x6c))>0:self.counts['retained_Infantry_destination']+=1
  if a in (0x509800,0x453c40):self.trace.extend(('S','kind','15' if a==0x509800 else '6'))
  if a==0x5480a5:
   self.counts['map_fallback' if u.reg_read(UC_X86_REG_EAX)==FALLBACK else 'map_normal']+=1
   x,y=struct.unpack('<hh',self.u.mem_read(arg(0),4));self.trace.extend(('MAP',str(x),str(y),str(self.identity(u.reg_read(UC_X86_REG_EAX)))))
  if STUBS<=a<STUBS+0x80 and (a-STUBS)%16==0:
   service=SERVICES[(a-STUBS)//16];self.counts['supplied.'+service]+=1;self.trace.extend(('S',service))
   if service=='owner':
    assert ecx==TAGS[f['subject']-1]
    if f['mode']==2:self.put(ACTOR+0x1b4,OWNER);self.counts['supplied.owner.mode2']+=1
    self.ret(0,POINTERS[f['ownerResult']]);return
   assert ecx==ACTOR
   if service=='target':
    assert arg(0)==0;self.trace.append('0')
    if f['mode']:
     self.put(ACTOR+0x228,0)
     if f['mode']==2:self.put(ACTOR+0x1b4,TAGS[f['subject']-1]);self.put(ACTOR+0x98,25)
    self.ret(4);return
   if service in ('predicate1','predicateC','kind'):
    key={'predicate1':'predicate1','predicateC':'predicateC','kind':'kind'}[service];self.trace.append(str(f[key]))
    if service=='predicateC' and f['mode']==3:self.put(ACTOR+0x3ac,ALTERNATE);self.put(ACTOR+0x3b8,4);self.put(ACTOR+0x3a0,2)
    self.ret(0,f[key]);return
   if service=='query':assert arg(0)==1;self.trace.append('1');self.ret(4,POINTERS[f['queryResult']]);return
   if service=='action400' and f['mode']==2:self.put(ACTOR+0x230,0)
   self.ret(0);return
  if a==0x6388a0:
   assert ecx==SCENARIO+0x218 and (arg(0),arg(1))==(4,8);self.counts['supplied.range']+=1;self.trace.extend(('S','range','4','8'))
   if f['mode']==2:self.put(0xa40d2c,self.word(0xa40d2c)+3);self.counts['supplied.range.mode2']+=1
   self.ret(8,f['retry']);return
  if a in (0x68a560,0x6e24c0):
   identity=7 if a==0x68a560 else 8;assert ecx==POINTERS[identity] and arg(0)==TAGS[f['subject']-1];self.counts['supplied.service'+str(identity)]+=1;self.trace.extend(('S','serviceA' if identity==7 else 'serviceB',str(identity),str(f['subject'])))
   if identity==7 and f['mode']==2:self.put(ACTOR+0x208,0);self.put(ACTOR+0x384,TAGS[f['subject']-1]);self.counts['supplied.serviceA.mode2']+=1
   self.ret(4);return
  assert any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected Techno instruction',hex(a))
  if a in RANGES:self.counts[hex(a)]+=1
 def run(self,f):
  self.f=f;u=self.u;u.mem_write(ARENA,b'\xa5'*SIZE);self.trace=[]
  for t,value,nxt in zip(TAGS,f['instances'],f['next'][:2]):self.put(t+0x2c,value);self.put(t+0x30,POINTERS[nxt]);self.put(t,TAG_VT);u.mem_write(t+0x14,bytes([f['flags']]))
  self.put(NODE+0x30,POINTERS[f['next'][2]]);self.put(ACTOR,VT);self.put(ACTOR+0x34,POINTERS[f['objectTag']])
  for off,value in zip(OFFSETS,f['fields']):self.put(ACTOR+off,POINTERS[value])
  for i,value in enumerate(f['weapons']):self.put(ACTOR+0x25c+i*4,POINTERS[value])
  for off,value in zip(NUMERIC,f['numbers']):self.put(ACTOR+off,value)
  u.mem_write(ACTOR+0x372,bytes([f['byte372']]));u.mem_write(ACTOR+0x5ba,bytes([f['byte5BA']]))
  self.put(0xa40d2c,f['frame']);self.put(0xa40774,f['session']);self.put(0xa3d290,SCENARIO)
  self.put(CONTROL+0x24,POINTERS[f['control'][0]]);self.put(CONTROL+0x28,POINTERS[f['control'][1]])
  for i,(vector,count,buffer) in enumerate(zip(VECTORS,COUNTS,BUFFERS)):
   self.put(vector,0x7a2ae4);self.put(vector+4,buffer);self.put(count,f['counts'][i]);u.mem_write(buffer,b''.join(struct.pack('<I',POINTERS[v]) for v in f['buffers'][i]))
  u.mem_write(ALTERNATE,struct.pack('<I',TAGS[f['subject']-1])*8)
  for offset,service in ((0x370,'target'),(0x1e4,'predicate1'),(0x1e0,'action1'),(0x2c,'kind'),(0xc0,'predicateC'),(0xcc,'query'),(0x400,'action400')):self.put(VT+offset,STUBS+SERVICES.index(service)*16)
  self.put(TAG_VT+0x3c,STUBS)
  for off,value in zip(TYPED_OFFSETS,f['typed']):self.put(ACTOR+off,POINTERS[value])
  for p,health,b7d,nxt in zip((*TAGS,NODE),f['recordHealth'],f['recordByte7D'],f['recordNext4C8']):
   self.put(p+0x6c,health);u.mem_write(p+0x7d,bytes([b7d]));self.put(p+0x4c8,POINTERS[nxt]);self.put(p+0x588,EXTRA);u.mem_write(p+0x88,struct.pack('<iii',*f['point']))
  self.put(NODE+0x14,0);self.put(EXTRA,ARENA+0xa100);self.put(ARENA+0xa128,STUBS+0x100)
  for id,c08,strength,anims in zip(TYPE_IDS,f['typeBytes'],f['strengths'],f['animations']):
   p=POINTERS[id];u.mem_write(p+0xc08,bytes([c08]));self.put(p+0xa0,strength)
   for off,value in zip((0x1158,0x1168),anims):u.mem_write(p+off,bytes([value]))
  self.put(ACTOR+0xa0,f['queuedA0']);self.put(ACTOR+0x6c,f['actorHealth']);u.mem_write(0xa40d04,bytes([f['globalByte']]))
  self.put(0x839848,RULES);u.mem_write(RULES+0x1368,struct.pack('<Q',f['thresholdBits']))
  for vector,count,buffer,n,values in zip(EXTRA_VECTORS,EXTRA_COUNTS,EXTRA_BUFFERS,f['extraCounts'],f['extraBuffers']):
   self.put(vector,0x7a2ae4);self.put(vector+4,buffer);self.put(count,n);u.mem_write(buffer,b''.join(struct.pack('<I',POINTERS[v]) for v in values))
  u.mem_write(FALLBACK,b'\xa5'*0x148);u.mem_write(FALLBACK+0x24,struct.pack('<hh',-91,123));self.put(0x832618,MAP_TABLE);u.mem_write(MAP_TABLE,bytes(0x100000))
  if f['mapMode']!=2:
   for i in range(4):
    if f['mapMode']!=1 or i&1:self.put(MAP_TABLE+((19+(i>>1))*512+19+(i&1))*4,CELLS+i*0x200)
  self.put(VT+0x28,0x501cb0 if f['root']==5 else 0x449e40 if f['root']==6 else 0x4c8460);self.put(VT+0x16c,0x594770);self.put(VT+0x84,STUBS+0x110)
  if f['root'] in (5,6):self.put(VT+0x2c,0x509800 if f['root']==5 else 0x453c40)
  for p in TAGS:self.put(p+4,0x7ac6e4)
  self.put(TAG_VT+0x2c,0x6b42d0);self.put(TAG_VT+0x48,0x5d4e40)

  if f['profile']:
   for off,value in ((0x9c,f['pending9C']),(0x3fc,f['word3FC']),(0x310,f['word310'])):self.put(ACTOR+off,value)
   for off,value in ((0xa4,f['queuedA4']),(0x530,f['byte530']),(0x59c,f['byte59C']),(0x404,f['byte404']),(0x170,f['byte170'])):u.mem_write(ACTOR+off,bytes([value]))
   for id,values in zip(TYPE_IDS,f['availabilityTypes']):
    p=POINTERS[id]
    for off,value in zip((0x1217,0xc6c,0x11fe,0x1206),values):
     if off==0xc6c:self.put(p+off,value)
     else:u.mem_write(p+off,bytes([value]))
   for off,address in ((0x370,0x440450),(0x30c,0x450360),(0x354,0x6c5070),(0x2b8,STUBS+0x230),(0x350,STUBS+0x240),(0x1e4,0x5950e0),(0x1e0,0x6cd880),(0xc0,0x41b410),(0xcc,0x41b2e0),(0x84,0x453c60)):self.put(VT+off,address)
   self.put(ARENA+0xa100+0xf0,STUBS+0x250)
  self.expected=bytearray(u.mem_read(ARENA,SIZE));self.active=True
  addresses=(0x636ba0,0x6d2d10,0x468a70,0x468120,0x4c8460,0x501cb0,0x449e40)
  inputs=[*RANGES.items(),*TABLES.items(),(VT,0x404),(TAG_VT,0x40),(0xa40774,4),(0xa3d290,4),(0xa40d04,1),(0x839848,4),(0x832618,4),(FALLBACK,0x24),(FALLBACK+0x28,0x120)]
  try:
   for removed in f['operations']:
    self.put(STACK-({4:48,5:68,6:32}.get(f['root'],8)),f['scratch']);self.trace.extend(('O',str(f['root'])))
    receiver=ACTOR if f['root'] in (0,1,4,5,6) else ACTOR+0xf8 if f['root']==2 else CONTROL;args=[TAGS[f['subject']-1],removed] if f['root'] in (0,1,4,5,6) else [TAGS[f['subject']-1]]
    if f['profile'] and f['entry']:
     address={1:0x440450,2:0x6c9af0,3:0x450360,4:0x594d80,5:0x6cd880,6:0x6c5070,7:0x453c60,8:0x5950e0,9:0x41b410,10:0x41b2e0}[f['entry']];args=[0] if f['entry'] in (1,2,6,10) else [];receiver=ACTOR
    else:address=addresses[f['root']]
    self.checked_call(address,args,receiver,writes=[(ARENA,SIZE),(0xa40d2c,4),(FALLBACK+0x24,4)],inputs=inputs)
    if f['profile'] and f['entry']>=3:self.trace.extend(('V',str(self.identity(u.reg_read(UC_X86_REG_EAX))) if f['entry']==7 else str(u.reg_read(UC_X86_REG_EAX)&255)))
    if f['root']==3:self.trace.extend(('V',str(u.reg_read(UC_X86_REG_EAX)&255)))
    self.trace.append('R');assert u.mem_read(ARENA,SIZE)==self.expected
  finally:self.active=False
  self.trace.extend(('state',*(str(signed(self.word(t+0x2c))) for t in TAGS),str(self.identity(self.word(ACTOR+0x34)))))
  self.trace.extend(str(self.identity(self.word(p+0x30))) for p in (*TAGS,NODE))
  self.trace.extend(str(self.identity(self.word(ACTOR+off))) for off in OFFSETS)
  self.trace.extend(str(self.identity(self.word(ACTOR+0x25c+i*4))) for i in range(8))
  self.trace.extend(str(signed(self.word(ACTOR+off))) for off in NUMERIC);self.trace.extend((str(u.mem_read(ACTOR+0x372,1)[0]),str(u.mem_read(ACTOR+0x5ba,1)[0]),str(signed(self.word(0xa40d2c)))))
  self.trace.extend(str(self.identity(self.word(CONTROL+off))) for off in (0x24,0x28));self.trace.extend(str(signed(self.word(p))) for p in COUNTS)
  for buffer in (*BUFFERS,ALTERNATE):self.trace.extend(str(self.identity(self.word(buffer+i*4))) for i in range(8))
  self.trace.append('TYPED');self.trace.extend(str(self.identity(self.word(ACTOR+off))) for off in TYPED_OFFSETS);self.trace.extend((str(signed(self.word(ACTOR+0x6c))),str(struct.unpack('<Q',u.mem_read(RULES+0x1368,8))[0])));self.trace.extend(str(signed(self.word(p))) for p in EXTRA_COUNTS)
  for buffer in EXTRA_BUFFERS:self.trace.extend(str(self.identity(self.word(buffer+i*4))) for i in range(8))
  self.trace.extend(str(v) for v in struct.unpack('<hh',u.mem_read(FALLBACK+0x24,4)))
  self.trace.extend(('SERVICES',str(signed(self.word(ACTOR+0x9c))) if f['profile'] else str(f['pending9C']),str(u.mem_read(ACTOR+0xa4,1)[0]) if f['profile'] else str(f['queuedA4']),str(u.mem_read(ACTOR+0x404,1)[0]) if f['profile'] else str(f['byte404']),str(signed(self.word(ACTOR+0x310))) if f['profile'] else str(f['word310']),str(u.mem_read(ACTOR+0x170,1)[0]) if f['profile'] else str(f['byte170'])))
  return self.trace
