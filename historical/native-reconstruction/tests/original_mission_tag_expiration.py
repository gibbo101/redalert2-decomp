# SPDX-License-Identifier: GPL-3.0-or-later
"""Unmodified Tag44 expiration roots, with named RTTI/recipient/selection services."""
import struct
from collections import Counter
from original_presentation import PresentationOracle,STACK,STOP
from verify_mission_tag_expiration import verify,RANGES,TABLES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_EDX,UC_X86_REG_ESP,UC_X86_REG_EIP
ARENA=0x2a00000;SIZE=0x10000;SLOTS=0x2b00000
TAGS=(ARENA+0x1000,ARENA+0x1100);CELLS=[ARENA+0x2000+i*256 for i in range(4)];FALLBACK=0xa6f9f8
RECIPIENTS=[ARENA+0x3000+i*256 for i in range(3)];VTABLE=ARENA+0x4000
BUFFERS=[ARENA+0x5000+i*256 for i in range(5)]
VECTORS=(0x833638,0x866238,0x866160,0xac0c58);GLOBALS=(0x833680,0x833684)
RECIPIENT_STUB=0x3000000
def signed(v):return v if v<2**31 else v-2**32
class MissionTagExpirationOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True)
  self.u.mem_map(ARENA,SIZE);self.u.mem_map(SLOTS,0x100000);self.u.mem_map(RECIPIENT_STUB,4096)
  self.active=False;self.counts=Counter();self.stores=Counter()
  self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.store)
 def va(self,a):return a
 def word(self,p):return int.from_bytes(self.u.mem_read(p,4),'little')
 def event(self,*values):self.trace.extend(map(str,values))
 def identity(self,p):
  if not p:return 0
  if p in TAGS:return 10+TAGS.index(p)
  if p in CELLS:return 30+CELLS.index(p)
  if p==FALLBACK:return 39
  if p in VECTORS:return 40+VECTORS.index(p)
  if p in GLOBALS:return 50+GLOBALS.index(p)
  if p in RECIPIENTS:return 60+RECIPIENTS.index(p)
  raise AssertionError(('Unknown expiration identity',hex(p)))
 def update(self,p,raw):
  for base,expected in self.expected.items():
   if base<=p and p+len(raw)<=base+len(expected):expected[p-base:p-base+len(raw)]=raw;return
  raise AssertionError(('Write outside expiration owners',hex(p),len(raw)))
 def supplied(self,p,value,n=4):
  raw=(value&((1<<(n*8))-1)).to_bytes(n,'little');self.u.mem_write(p,raw);self.update(p,raw)
 def ret(self,n,value=0):
  u=self.u;sp=u.reg_read(UC_X86_REG_ESP);target=self.word(sp);u.reg_write(UC_X86_REG_ESP,sp+4+n);u.reg_write(UC_X86_REG_EAX,value&0xffffffff);u.reg_write(UC_X86_REG_EIP,target)
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  sp=u.reg_read(UC_X86_REG_ESP);arg=lambda i:self.word(sp+4+i*4);receiver=u.reg_read(UC_X86_REG_ECX)
  if a==0x498f10:
   assert self.word(sp)==0x6ecbce and receiver==0x8324e0 and arg(0)==0
   self.counts['supplied_selection']+=1;self.event('S')
   if self.f['selection']:self.supplied(GLOBALS[0],TAGS[1]);self.supplied(GLOBALS[1],TAGS[0])
   self.ret(4);return
  if a==0x783ce4:
   assert self.word(sp)==0x6ecd01 and [arg(i) for i in range(5)]==[self.subject,0,0x7ce240,0x7ce260,0]
   self.counts['supplied_RTTI']+=1;self.event('D',self.identity(self.subject));self.ret(0);return
  if a==RECIPIENT_STUB:
   assert self.word(sp)==0x6ecd76 and receiver in RECIPIENTS and arg(0)==self.subject and arg(1)==self.removed
   self.counts['supplied_recipient']+=1;self.event('C',RECIPIENTS.index(receiver)+1,self.identity(self.subject),arg(1))
   if not self.changed:
    self.changed=True;mode=self.f['mode']
    if mode==1:self.supplied(VECTORS[3]+16,0)
    if mode==2:
     for i,recipient in enumerate((RECIPIENTS[2],RECIPIENTS[1],RECIPIENTS[0])):self.supplied(BUFFERS[4]+i*4,recipient)
     self.supplied(VECTORS[3]+4,BUFFERS[4]);self.supplied(VECTORS[3]+16,3)
    if mode==3:self.supplied(BUFFERS[3]+4,RECIPIENTS[2])
    if mode==4:
     if self.f['cells']:self.supplied(CELLS[0]+0x3c,TAGS[1])
     self.supplied(FALLBACK+0x3c,self.subject)
    if mode==5:self.supplied(VECTORS[0]+16,0)
   self.ret(8);return
  assert any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected expiration instruction',hex(a))
  if a in RANGES:self.counts[hex(a)]+=1
  if a==0x6b42d0:assert receiver in TAGS
  if a==0x559d80:assert receiver==0x8324e0 and arg(0)==self.subject
  if a==0x53e110:assert receiver==0x832470 and arg(0) in (0,self.subject)
  if a==0x47a460:assert arg(0)==0 and receiver in (*CELLS,FALLBACK)
  if a==0x47a340:assert receiver in (*CELLS,FALLBACK) and arg(0)==self.subject
  if a in (0x42d120,0x4d5b40):assert receiver in (VECTORS[0],VECTORS[1])
 def store(self,u,access,p,n,value,_):
  if not self.active or not any(base<=p and p+n<=base+len(raw) for base,raw in self.expected.items()):return
  pc=u.reg_read(UC_X86_REG_EIP);v=value&((1<<(n*8))-1);subject=offset=None;out=v
  assert n==4,('Unexpected expiration width',hex(pc),n)
  if p in GLOBALS:
   assert pc in (0x6ecbab,0x6ecbc3) and v==0;subject=p;offset=0
  elif p in [t+0x2c for t in TAGS]:
   assert pc in (0x47a46a,0x47a353);subject=p-0x2c;offset=0x2c
  elif any(c<=p<c+64 for c in (*CELLS,FALLBACK)):
   subject=next(c for c in (*CELLS,FALLBACK) if c<=p<c+64);offset=p-subject
   allowed={0x559de2:0x24,0x47a473:0x3c,0x47a356:0x3c,0x47a3a6:0x2c,0x47a3b2:0x30}
   assert allowed.get(pc)==offset
   if offset!=0x24:out=self.identity(v)
  elif p in [r+16 for r in VECTORS]:
   subject=p-16;offset=16
   assert pc in (0x559e1d,0x559e8a,0x47a381,0x53e146)
  elif any(b<=p<b+128 for b in BUFFERS[:3]):
   role=next(i for i,b in enumerate(BUFFERS[:3]) if b<=p<b+128);subject=VECTORS[role];offset=0x100+p-BUFFERS[role]
   assert offset%4==0 and pc in (0x559e29,0x559e9c,0x47a393,0x53e152)
   if role:out=self.identity(v)
  assert subject is not None,('Unexpected expiration store',hex(pc),hex(p),n)
  self.event('W',self.identity(subject),offset,out);self.stores[hex(pc)]+=1;self.update(p,v.to_bytes(n,'little'))
 def run(self,f):
  self.f=f;u=self.u;u.mem_write(ARENA,b'\xa5'*SIZE);u.mem_write(SLOTS,bytes(0x100000));self.trace=[];self.changed=False
  tag=lambda id:0 if id==0 else TAGS[id-1]
  for i,t in enumerate(TAGS):self.put(t,0x7ac700);self.put(t+0x2c,f['instances'][i])
  for i,g in enumerate(GLOBALS):self.put(g,tag(f['globals'][i]))
  for i,row in enumerate(f['cells']+[f['fallback']]):
   if i<len(f['cells']):point,slot,old,a,b,content=row;cell=CELLS[i]
   else:point,old,a,b,content=row;slot=-1;cell=FALLBACK
   u.mem_write(cell,b'\xa5'*64)
   for off,value in ((0x24,point),(0x28,ARENA+0x8000 if content else 0),(0x2c,tag(a)),(0x30,tag(b)),(0x3c,tag(old))):self.put(cell+off,value)
   if slot>=0:self.put(SLOTS+slot*4,cell)
  for i,recipient in enumerate(RECIPIENTS):self.put(recipient,VTABLE)
  self.put(VTABLE+0x28,RECIPIENT_STUB)
  for i,values in enumerate((f['points'],f['maps'],f['logic'],f['recipients'])):
   self.put(VECTORS[i],0x79c5a0 if i==0 else 0x7a2ae4);self.put(VECTORS[i]+4,BUFFERS[i]);self.put(VECTORS[i]+16,len(values))
   u.mem_write(BUFFERS[i],bytes(128))
   for j,value in enumerate(values):self.put(BUFFERS[i]+4*j,value if i==0 else RECIPIENTS[value-1] if i==3 else tag(value))
  u.mem_write(BUFFERS[4],bytes(128));self.put(0x8324e0+0x138,SLOTS)
  owners=[(ARENA,SIZE),(FALLBACK,64),*[(r,24) for r in VECTORS],*[(g,4) for g in GLOBALS]]
  self.expected={p:bytearray(u.mem_read(p,n)) for p,n in owners}
  for root,subject,self.removed in f['operations']:
   self.subject=TAGS[(subject-1) if root!=3 else 0];self.event('O',root);u.mem_write(STACK-0x400,b'\xa5'*0x400)
   if root==0:address=0x6ecb90;receiver=self.subject;args=[];edx=self.removed
   elif root==1:address=0x559d80;receiver=0x8324e0;args=[self.subject,self.removed];edx=0
   elif root in (2,4):address=0x53e110;receiver=0x832470;args=[self.subject if root==2 else 0,self.removed];edx=0
   else:address=0x47a340;receiver=CELLS[subject] if subject<len(f['cells']) else FALLBACK;args=[self.subject];edx=0
   self.active=True
   try:self.checked_call(address,args,receiver,edx,writes=owners,inputs=[*RANGES.items(),*TABLES.items(),(SLOTS,0x100000),(0x8324e0+0x138,4)])
   finally:self.active=False
   for p,raw in self.expected.items():assert bytes(u.mem_read(p,len(raw)))==raw,('Expiration whole owner change',hex(p))
   self.event('R')
  self.event('state',*(signed(self.word(t+0x2c)) for t in TAGS),*(self.identity(self.word(g)) for g in GLOBALS),int(self.changed))
  for c in CELLS[:len(f['cells'])]+[FALLBACK]:self.event(self.word(c+0x24),*(self.identity(self.word(c+off)) for off in (0x3c,0x2c,0x30)),int(bool(self.word(c+0x28))))
  self.event(*(signed(self.word(r+16)) for r in VECTORS),int(self.word(VECTORS[3]+4)==BUFFERS[4]))
  for i,b in enumerate(BUFFERS):self.event(*(v if i==0 else self.identity(v) for v in struct.unpack('<32I',u.mem_read(b,128))))
  return self.trace
