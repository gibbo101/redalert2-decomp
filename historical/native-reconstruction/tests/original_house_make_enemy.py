# SPDX-License-Identifier: GPL-3.0-or-later
"""Unmodified full MakeEnemy, actual score/conversion and supplied effects."""
import struct
from collections import Counter
from original_presentation import PresentationOracle,STOP
from verify_house_make_enemy import verify,RANGES,TABLES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_EDX,UC_X86_REG_ESP,UC_X86_REG_EIP
ARENA=0x3000000;SIZE=0x50000;HOUSE=ARENA;TYPE=ARENA+0x43000;SCORES=ARENA+0x44000;RULES=ARENA+0x45000;TEXT=ARENA+0x47000
GLOBALS=(0xa3d298,0xa40774,0xa35db4,0x839848)
def signed(v):return v if v<2**31 else v-2**32
class HouseMakeEnemyOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(ARENA,SIZE);self.active=False;self.counts=Counter();self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.store)
 def va(self,a):return a
 def word(self,p):return struct.unpack('<I',self.u.mem_read(p,4))[0]
 def byte(self,p):return self.u.mem_read(p,1)[0]
 def hp(self,i):return HOUSE+(i-1)*0x16000 if i else 0
 def hid(self,p):
  if not p:return 0
  i=(p-HOUSE)//0x16000+1;assert 1<=i<=3 and p==self.hp(i);return i
 def tp(self,i):return TYPE+(i-1)*0x200
 def tid(self,p):
  i=(p-TYPE)//0x200+1;assert 1<=i<=3 and p==self.tp(i);return i
 def change(self,p,v,n=4):
  data=int(v&((1<<(n*8))-1)).to_bytes(n,'little');self.u.mem_write(p,data)
  if self.active:
   if ARENA<=p and p+n<=ARENA+SIZE:self.expected[p-ARENA:p-ARENA+n]=data
   else:assert p in GLOBALS and n==4;self.expectedGlobals[p]=data
 def event(self,k,a=0,b=0):
  s=self.hp(self.f['current']);o=self.hp(self.f['target']);self.trace.extend(map(str,('E',k,a,b,self.word(s+0x5674),self.word(s+0x120),self.word(o+0x5674) if o else 0,self.word(o+0x120) if o else 0)))
 def mutate(self,k):
  m=self.f['mutation'];wanted=[0,1,2,2,4,5,6,8,6,2,1,8,6]
  if self.changed or not m or k!=wanted[m]:return
  self.changed=True;s=self.hp(self.f['current']);o=self.hp(self.f['target']) or s;put=self.change
  if m==1:put(o+0x30,-33);put(s+0x5674,0xffffffff)
  if m==2:put(o+0x5674,0xffffffff);put(s+0x30,-1);put(0xa40774,1)
  if m==3:put(0xa3d298,1);put(0xa40774,0);put(s+0x134,255,1);put(o+0x5674,0xffffffff)
  if m==4:put(0xa3d298,0);put(s+0x134,0,1);put(s+0x135,0,1);put(o+0x134,0,1);put(o+0x135,255,1)
  if m==5:put(RULES+0x1128,struct.unpack('<Q',struct.pack('<d',.6))[0],8);put(self.word(s+0x34)+0xc0,-7)
  if m==6:put(0xa3d298,0);put(s+0x134,0,1);put(s+0x135,0,1);put(o+0x134,0,1);put(o+0x135,255,1)
  if m==7:put(0xa3d298,0);put(s+0x134,0,1);put(s+0x135,0,1);put(o+0x134,0,1);put(o+0x135,0,1)
  if m==8:put(0xa35db4,self.hp(3));put(0xa3d298,1)
  if m==9:put(o+0x30,31);put(o+0x5674,0)
  if m==10:
   put(s+0x5504,2);p=self.word(s+0x54f8)
   for i,v in enumerate((0x7fffffff,7)):put(p+8*i,self.hp(self.f['target']));put(p+8*i+4,v)
  if m==11:put(0xa3d298,1);put(0xa35db4,self.hp(self.f['target']))
  if m==12:put(0xa3d298,0);put(s+0x134,255,1)
 def store(self,u,access,p,n,value,_):
  if not self.active:return
  for i in range(1,4):
   off=p-self.hp(i)
   if off in (0x5674,0x120):assert n==4;self.trace.extend(map(str,('W',i,off,value)))
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  sp=u.reg_read(UC_X86_REG_ESP);ecx=u.reg_read(UC_X86_REG_ECX)
  services={0x49e000:(1,8),0x49de00:(9,8),0x4f3420:(2,0),0x6f9ec0:(4,8),0x783764:(5,0),0x5b4da0:(6,28),0x715b40:(7,4),0x4e09a0:(8,4)}
  if a in services:
   k,pops=services[a];result=0;self.counts['supplied_'+str(k)]+=1
   if k in (1,9):assert ecx==0x8324e0 and self.word(sp+4)==0 and self.word(sp+8)==0;self.event(k)
   if k==2:self.event(k,self.hid(ecx))
   if k==4:assert ecx==0x7da34c and u.reg_read(UC_X86_REG_EDX)==0 and self.word(sp+4)==0x7da270 and self.word(sp+8)==0xcc8;self.event(k);result=TEXT
   if k==5:
    assert self.word(sp+8)==TEXT;self.formatted=self.word(sp+4);self.event(k,self.hid(self.word(sp+12)-0x15f16),self.hid(self.word(sp+16)-0x15f16))
   if k==6:
    args=struct.unpack('<7I',u.mem_read(sp+4,28));assert ecx==0xa3dc70 and args[:2]==(0,0) and args[2]==self.formatted and args[4]==0x4046 and args[6]==0;self.event(k,signed(args[3]),args[5])
   if k==7:assert u.reg_read(UC_X86_REG_EDX)==0xffffffff and self.word(sp+4)==0xffffffff;self.event(k,ecx)
   if k==8:assert ecx==0x8324e0 and self.word(sp+4)==0;self.event(k)
   self.mutate(k);u.reg_write(UC_X86_REG_EAX,result);u.reg_write(UC_X86_REG_ESP,sp+4+pops);u.reg_write(UC_X86_REG_EIP,self.word(sp));return
  assert any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected MakeEnemy instruction',hex(a))
  if a in RANGES:self.counts[hex(a)]+=1
  if a==0x4e5cd4:self.counts['out_of_line_tail']+=1
 def run(self,f):
  self.f=f;u=self.u;u.mem_write(ARENA,b'\xa5'*SIZE);self.active=False
  for i,h in enumerate(f['houses'],1):
   p=self.hp(i)
   for off,v,n in ((0x30,h[0],4),(0x34,self.tp(h[1]),4),(0x13d,h[2],1),(0x5674,h[3],4),(0x120,h[4],4),(0x134,h[5],1),(0x135,h[6],1),(0x54f0,h[7],4),(0x5504,h[8],4),(0x54f8,SCORES+(i-1)*16,4)):self.change(p+off,v,n)
  for i,t in enumerate(f['types'],1):self.change(self.tp(i)+0x1a6,t[0],1);self.change(self.tp(i)+0xc0,t[1])
  for i,(h,v) in enumerate(f['scores']):self.change(SCORES+8*i,self.hp(h));self.change(SCORES+8*i+4,v)
  self.change(RULES+0x1128,f['delayBits'],8)
  for p,v in zip(GLOBALS,(f['mode'],f['unrestricted'],self.hp(f['currentHouse']),RULES)):self.change(p,v)
  self.expected=bytearray(u.mem_read(ARENA,SIZE));self.expectedGlobals={p:bytes(u.mem_read(p,4)) for p in GLOBALS};self.trace=[];self.changed=False;self.active=True
  effects=[(SCORES+8*i+4,4) for i in range(6)]+[(self.hp(i)+off,4) for i in range(1,4) for off in (0x5674,0x120,0x54f0)]
  try:self.checked_call(0x4e5a70,[self.hp(f['target']),f['announce']],self.hp(f['current']),writes=effects,inputs=[*RANGES.items(),*TABLES.items()])
  finally:self.active=False
  observed=bytearray(u.mem_read(ARENA,SIZE))
  for p,n in effects:observed[p-ARENA:p-ARENA+n]=self.expected[p-ARENA:p-ARENA+n]
  assert observed==self.expected and all(bytes(u.mem_read(p,4))==v for p,v in self.expectedGlobals.items())
  self.trace.extend(map(str,('S',signed(self.word(0xa3d298)),signed(self.word(0xa40774)),self.hid(self.word(0xa35db4)),struct.unpack('<Q',u.mem_read(RULES+0x1128,8))[0],int(self.changed))))
  for i in range(1,4):
   p=self.hp(i);self.trace.extend(map(str,(signed(self.word(p+0x30)),self.tid(self.word(p+0x34)),self.byte(p+0x13d),self.word(p+0x5674),self.word(p+0x120),self.byte(p+0x134),self.byte(p+0x135),signed(self.word(p+0x54f0)),signed(self.word(p+0x5504)))))
  for i in range(1,4):p=self.tp(i);self.trace.extend(map(str,(self.byte(p+0x1a6),signed(self.word(p+0xc0)))))
  for i in range(6):p=SCORES+8*i;self.trace.extend(map(str,(self.hid(self.word(p)),signed(self.word(p+4)))))
  return self.trace
