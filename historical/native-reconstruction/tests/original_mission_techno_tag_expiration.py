# SPDX-License-Identifier: GPL-3.0-or-later
"""Unmodified shared Radio/Techno expiration on private mutable owners."""
import struct
from collections import Counter
from original_presentation import PresentationOracle,STOP,STACK
from verify_mission_techno_tag_expiration import verify,RANGES,TABLES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EIP
ARENA=0x3800000;SIZE=0x10000;ACTOR=ARENA;TAGS=(ARENA+0x1000,ARENA+0x2000);NODE=ARENA+0x3000;OWNER=ARENA+0x4000;CONTROL=ARENA+0x5000;SERVICEA=ARENA+0x6000;SERVICEB=ARENA+0x7000;EXTRA=ARENA+0x8000
VT=ARENA+0x9000;TAG_VT=ARENA+0xa000;BUFFERS=[ARENA+0xb000+i*0x100 for i in range(4)];ALTERNATE=ARENA+0xb800;STUBS=ARENA+0xc000;SCENARIO=ARENA+0xd000
POINTERS=(0,*TAGS,NODE,ACTOR,OWNER,CONTROL,SERVICEA,SERVICEB,EXTRA)
OFFSETS=(0xfc,0x108,0x1b0,0x1b4,0x208,0x20c,0x228,0x22c,0x230,0x238,0x23c,0x27c,0x384,0x3f8,0x30)
VECTORS=(ACTOR+0xc8,ACTOR+0x390,ACTOR+0x3a8,ACTOR+0x3c0)
# Radio count is +D0 (8 from this view); the three DynamicVectors use +10.
COUNTS=(ACTOR+0xd0,ACTOR+0x3a0,ACTOR+0x3b8,ACTOR+0x3d0)
NUMERIC=(0x148,0x14c,0x150,0x98,0xa8)
SERVICES=('owner','target','predicate1','action1','kind','predicateC','query','action400')
def signed(v):return v if v<2**31 else v-2**32
class MissionTechnoTagExpirationOracle(PresentationOracle):
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
  if not self.active or not ARENA<=p<p+n<=ARENA+SIZE:return
  pc=u.reg_read(UC_X86_REG_EIP);self.stores[hex(pc)]+=1;v=value&((1<<(8*n))-1);identity=offset=None;out=v
  if p in (TAGS[0]+0x2c,TAGS[1]+0x2c):assert pc==0x5d3be4 and n==4;identity=self.identity(p-0x2c);offset=0x2c
  elif p==ACTOR+0x34:assert pc==0x5d3be7 and n==4;identity=4;offset=0x34;out=self.identity(v)
  elif p in (TAGS[0]+0x30,TAGS[1]+0x30,NODE+0x30):assert pc==0x468aab and n==4;identity=self.identity(p-0x30);offset=0x30;out=self.identity(v)
  elif p in (CONTROL+0x24,CONTROL+0x28):assert n==4 and pc in (0x46812d,0x468130);identity=6;offset=p-CONTROL;out=self.identity(v)
  elif p in COUNTS[1:]:assert n==4;identity=20+COUNTS.index(p);offset=16
  elif any(base<=p<base+32 for base in (*BUFFERS,ALTERNATE)):
   base=next(base for base in (*BUFFERS,ALTERNATE) if base<=p<base+32);assert n==4 and (p-base)%4==0;identity=22 if base==ALTERNATE else 20+BUFFERS.index(base);offset=0x100+p-base;out=self.identity(v)
  elif ACTOR<=p<ACTOR+0x800:
   identity=4;offset=p-ACTOR
   if offset in (*OFFSETS,0x25c,0x260,0x264,0x268,0x26c,0x270,0x274,0x278):assert n==4;out=self.identity(v)
   else:assert offset in (0x148,0x14c,0x150,0xa8,0x372,0x5ba) and n==(1 if offset in (0x372,0x5ba) else 4)
  assert identity is not None,('unexpected Techno store',hex(pc),hex(p),n)
  self.trace.extend(('W',str(identity),str(offset),str(out)));self.expected[p-ARENA:p-ARENA+n]=v.to_bytes(n,'little')
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  sp=u.reg_read(UC_X86_REG_ESP);ecx=u.reg_read(UC_X86_REG_ECX);arg=lambda i:self.word(sp+4+i*4);f=self.f
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
  self.expected=bytearray(u.mem_read(ARENA,SIZE));self.active=True
  addresses=(0x636ba0,0x6d2d10,0x468a70,0x468120)
  inputs=[*RANGES.items(),*TABLES.items(),(VT,0x404),(TAG_VT,0x40),(0xa40774,4),(0xa3d290,4)]
  try:
   for removed in f['operations']:
    self.put(STACK-8,f['scratch']);self.trace.extend(('O',str(f['root'])))
    receiver=ACTOR if f['root']<2 else ACTOR+0xf8 if f['root']==2 else CONTROL;args=[TAGS[f['subject']-1],removed] if f['root']<2 else [TAGS[f['subject']-1]]
    self.checked_call(addresses[f['root']],args,receiver,writes=[(ARENA,SIZE),(0xa40d2c,4)],inputs=inputs)
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
  return self.trace
