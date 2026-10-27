# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete original Tag dispatch and retirement; explicit notification/heap/action services."""
import struct
from collections import Counter
from original_presentation import PresentationOracle,STACK,STOP
from verify_mission_tag import verify,RANGES,TABLES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_EDX,UC_X86_REG_EIP,UC_X86_REG_ESP
ARENA=0x2800000;SIZE=0x20000;TAGS=[ARENA+0x10000,ARENA+0x10100];TAG_TYPES=[ARENA+0x10200,ARENA+0x10400]
TRIGGERS=[ARENA+0x12000+i*0x100 for i in range(3)];TYPES=[ARENA+0x13000+i*0x200 for i in range(3)]
EVENTS=[ARENA+0x15000+i*0x100 for i in range(3)];ACTIONS=[ARENA+0x16000+i*0x100 for i in range(3)]
COUNTRY=ARENA+0x17000;OWNER=ARENA+0x18000;SOURCE=ARENA+0x18100;CELL=ARENA+0x18200
BUFFERS=[ARENA+0x19000,ARENA+0x19400];SLOTS=0x2900000;FALLBACK=0xa6f9f8;QUEUE=0xac0cd8
def signed(v):return v if v<2**31 else v-2**32
class MissionTagOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True)
  self.u.mem_map(ARENA,SIZE);self.u.mem_map(SLOTS,0x100000);self.active=False;self.counts=Counter();self.stores=Counter()
  self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.store)
 def va(self,a):return a
 def word(self,p):return int.from_bytes(self.u.mem_read(p,4),'little')
 def event(self,*v):self.trace.extend(map(str,v))
 def identity(self,p):
  if not p:return 0
  if p in TRIGGERS:return TRIGGERS.index(p)+1
  if p in TAGS:return TAGS.index(p)+10
  return {OWNER:20,CELL:30,FALLBACK:31,QUEUE:40}[p]
 def buffer(self,p):
  for base in BUFFERS:
   if base<=p<base+512:return (p-base)//4
  return None
 def update(self,p,raw):
  for base,expected in self.expected.items():
   if base<=p and p+len(raw)<=base+len(expected):expected[p-base:p-base+len(raw)]=raw;return
  raise AssertionError(('Write outside expected owners',hex(p),len(raw)))
 def supplied(self,p,v,n=4):
  raw=(v&((1<<(8*n))-1)).to_bytes(n,'little');self.u.mem_write(p,raw);self.update(p,raw)
 def ret(self,n,value=0):
  u=self.u;sp=u.reg_read(UC_X86_REG_ESP);target=self.word(sp);u.reg_write(UC_X86_REG_ESP,sp+4+n);u.reg_write(UC_X86_REG_EAX,value&0xffffffff);u.reg_write(UC_X86_REG_EIP,target)
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  sp=u.reg_read(UC_X86_REG_ESP);arg=lambda i:self.word(sp+4+i*4);receiver=u.reg_read(UC_X86_REG_ECX)
  if a==0x40cd40:
   assert receiver==QUEUE and arg(1)==0
   requested=signed(arg(0));self.event('V',requested,self.f['grow_result']);self.counts['supplied_growth']+=1
   assert requested==signed((self.word(QUEUE+8)+self.word(QUEUE+20))&0xffffffff)
   if self.f['grow_result']&255:
    assert 0<=requested<=128;self.supplied(QUEUE+8,requested)
    if self.f['grow_mode']==1:self.supplied(QUEUE+16,0)
    if self.f['grow_mode']==2:
     raw=bytes(u.mem_read(BUFFERS[0],512));u.mem_write(BUFFERS[1],raw);self.update(BUFFERS[1],raw);self.supplied(QUEUE+4,BUFFERS[1])
   self.ret(8,self.f['grow_result']);return
  if a==0x6ecb90:
   assert receiver==TAGS[0] and u.reg_read(UC_X86_REG_EDX)&255==1
   self.event('N',u.mem_read(TAGS[0]+0x35,1)[0]);self.counts['supplied_expiration']+=1
   if self.f['notify_mode']:self.supplied(QUEUE+16,0)
   self.ret(0);return
  if a==0x6adae0:
   assert receiver in ACTIONS;index=ACTIONS.index(receiver);row=self.triggers[index];mode=row[6]
   assert self.word(sp)==0x6ed87a and arg(0)==0 and arg(1)==(OWNER if self.operation[4] else 0) and arg(2)==TRIGGERS[index]
   loc=arg(3);assert loc==STACK-24
   self.event('A',index+1,self.word(loc));self.counts['supplied_action']+=1
   if mode==1:self.supplied(TAG_TYPES[0]+0x9c,2)
   if mode==2:self.supplied(TAG_TYPES[0]+0x9c,0)
   if mode==3:self.supplied(TAGS[0]+0x2c,1)
   if mode==4:
    link=len(self.triggers)-1 if index+1<len(self.triggers) else -1;row[0]=link;self.supplied(TRIGGERS[index]+0x28,TRIGGERS[link] if link>=0 else 0)
   if mode==5:self.supplied(TAGS[0]+0x35,255,1)
   if mode==6:
    for p in (OWNER+0x34,CELL+0x3c,FALLBACK+0x3c):self.supplied(p,TAGS[1])
   if mode==7:self.supplied(TRIGGERS[index]+0x40,0,1);self.supplied(TRIGGERS[index]+0x2c,255,1)
   if mode==8:u.mem_write(loc,struct.pack('<I',self.word(loc)^0x8001ffff))
   self.ret(16,0xdead0000|row[5]);return
  assert any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected Tag instruction',hex(a))
  if a in RANGES:self.counts[hex(a)]+=1
  if a==0x4ed760:self.event('H',signed(receiver))
  if a==0x6e6050:
   index=EVENTS.index(receiver);pulse,house,owner,timer,persistent,source=struct.unpack('<6I',u.mem_read(sp+4,24))
   assert house==0 and owner==(OWNER if self.operation[4] else 0) and timer==TRIGGERS[index]+0x30 and persistent==STACK-28 and source==(SOURCE if self.operation[7] else 0)
   self.event('E',index+1,signed(pulse),self.word(persistent))
  if a==0x548070:
   assert receiver==0x8324e0 and self.word(arg(0))==self.operation[5];self.event('L',self.word(arg(0)))
 def store(self,u,access,p,n,value,_):
  if not self.active or not any(base<=p<p+n<=base+len(raw) for base,raw in self.expected.items()):return
  pc=u.reg_read(UC_X86_REG_EIP);v=value&((1<<(8*n))-1);self.stores[hex(pc)]+=1
  if p==FALLBACK+0x24:assert pc==0x54809f and n==4;self.event('B',v)
  else:
   subject=None;offset=None;out=v
   if p==QUEUE+16:assert pc in (0x6ed9db,0x6b3f6b) and n==4;subject=QUEUE;offset=16
   if self.buffer(p) is not None:assert pc in (0x6ed9e7,0x6b3f77) and n==4;subject=QUEUE;offset=0x100+self.buffer(p)*4;out=self.identity(v)
   for tag in TAGS:
    if p==tag+0x35:assert pc in (0x6b3e19,0x6b3ec4) and n==1;subject=tag;offset=0x35
    if p==tag+0x2c:assert pc in (0x5d443b,0x5d4454,0x47a46a) and n==4;subject=tag;offset=0x2c
   if p==OWNER+0x34:assert pc in (0x5d443e,0x5d444d) and n==4;subject=OWNER;offset=0x34;out=self.identity(v)
   if p in (CELL+0x3c,FALLBACK+0x3c):assert pc==0x47a473 and n==4;subject=p-0x3c;offset=0x3c;out=self.identity(v)
   for trigger in TRIGGERS:
    if trigger+0x2c<=p<trigger+0x40:
     off=p-trigger;allowed={0x6ed993:(0x2c,1),0x6ed6b1:(0x30,4),0x6ed6ba:(0x34,4),0x6ed6bf:(0x38,4),0x6ed6d0:(0x3c,4),0x6ed7ed:(0x3c,4)}
     assert allowed.get(pc)==(off,n);subject=trigger;offset=off
   assert subject is not None,('Unexpected Tag owner store',hex(pc),hex(p),n)
   self.event('W',self.identity(subject),offset,out)
  self.update(p,v.to_bytes(n,'little'))
 def run(self,f):
  self.f=f;self.triggers=[list(t) for t in f['triggers']];u=self.u;u.mem_write(ARENA,b'\xa5'*SIZE);u.mem_write(SLOTS,bytes(0x100000));self.trace=[]
  tagptr=lambda i:0 if i==0 else TAGS[i-1]
  for i,tag in enumerate(TAGS):
   self.put(tag+0x24,TAG_TYPES[i]);self.put(TAG_TYPES[i]+0x9c,f['persistence'][i]);self.put(tag+0x28,TRIGGERS[0] if i==0 and self.triggers else 0)
   self.put(tag+0x2c,f['instances'][i]);u.mem_write(tag+0x34,bytes([f['destroyed'] if i==0 else 0,f['executing'] if i==0 else 0]))
  self.put(OWNER+0x34,tagptr(f['owner']));self.put(CELL+0x3c,tagptr(f['cell']));u.mem_write(FALLBACK,b'\xa5'*0x40)
  self.put(FALLBACK+0x3c,tagptr(f['fallback']));self.put(FALLBACK+0x24,0x1234abcd)
  self.put(0x8324e0+0x138,SLOTS)
  if f['map_slot']>=0:self.put(SLOTS+f['map_slot']*4,CELL)
  self.put(COUNTRY+0xb4,-9);self.put(0xa322a8,0);self.put(0xa3229c,COUNTRY+0x100)
  for i,(link,enabled,destroyed,kind,value,result,mode) in enumerate(self.triggers):
   t=TRIGGERS[i];self.put(t+0x24,TYPES[i]);self.put(t+0x28,TRIGGERS[link] if link>=0 else 0)
   u.mem_write(t+0x2c,bytes([destroyed]));u.mem_write(t+0x40,bytes([enabled]));self.put(t+0x30,-1);self.put(t+0x34,-91);self.put(t+0x38,0);self.put(t+0x3c,0)
   self.put(TYPES[i]+0xa4,COUNTRY);self.put(TYPES[i]+0xac,EVENTS[i]);self.put(TYPES[i]+0xb0,ACTIONS[i])
   self.put(EVENTS[i]+0x2c,kind);self.put(EVENTS[i]+0x34,value);self.put(EVENTS[i]+0x28,0);self.put(ACTIONS[i]+0x28,0)
  for p in BUFFERS:u.mem_write(p,bytes(512))
  for off,v in ((0,0x79e868),(4,BUFFERS[0]),(8,f['capacity']),(16,f['count']),(20,f['growth'])):self.put(QUEUE+off,v)
  u.mem_write(QUEUE+13,bytes([f['owns']]));self.put(0xabfe28,0x7fff7fff)
  self.expected={p:bytearray(u.mem_read(p,n)) for p,n in ((ARENA,SIZE),(QUEUE,24),(FALLBACK,0x40))}
  for self.operation in f['operations']:
   op,frame,suppress,pulse,present,location,force,source,subject=self.operation
   self.put(0xa40d2c,frame);u.mem_write(0xa40d13,bytes([suppress]));u.mem_write(STACK-0x400,b'\xa5'*0x400);self.event('O',op)
   if op==0:root=0x6b3df0;receiver=TAGS[0];args=[pulse,OWNER if present else 0,location,force,SOURCE if source else 0]
   elif op==1:root=0x6ed990;receiver=TRIGGERS[subject];args=[]
   elif op==2:root=0x5d4430;receiver=OWNER;args=[tagptr(subject)]
   else:root=0x47a460;receiver=CELL if subject==0 else FALLBACK;args=[0]
   self.active=True
   try:self.checked_call(root,args,receiver,writes=[(ARENA,SIZE),(QUEUE,24),(FALLBACK,0x40)],
     inputs=[*RANGES.items(),*TABLES.items(),(SLOTS,0x100000),(0x8324e0+0x138,4),(0xabfe28,4),(0xa3229c,4),(0xa322a8,4),(0xa40d2c,4),(0xa40d13,1)])
   finally:self.active=False
   for base,raw in self.expected.items():assert bytes(u.mem_read(base,len(raw)))==raw,('Tag whole owner change',hex(base))
   self.event('R','void' if op in (1,3) else u.reg_read(UC_X86_REG_EAX)&255)
  self.event('state',*(signed(self.word(p+0x9c)) for p in TAG_TYPES),*(signed(self.word(p+0x2c)) for p in TAGS),*u.mem_read(TAGS[0]+0x35,1),*u.mem_read(TAGS[0]+0x34,1),
   self.identity(self.word(OWNER+0x34)),self.identity(self.word(CELL+0x3c)),self.identity(self.word(FALLBACK+0x3c)),self.word(FALLBACK+0x24),signed(self.word(QUEUE+8)),signed(self.word(QUEUE+16)),BUFFERS.index(self.word(QUEUE+4)))
  for i,t in enumerate(TRIGGERS[:len(self.triggers)]):self.event(*u.mem_read(t+0x40,1),*u.mem_read(t+0x2c,1),self.word(t+0x3c),signed(self.word(t+0x30)),signed(self.word(t+0x34)),signed(self.word(t+0x38)),self.triggers[i][0])
  for p in BUFFERS:self.event(*(self.identity(v) for v in struct.unpack('<128I',u.mem_read(p,512))))
  return self.trace
