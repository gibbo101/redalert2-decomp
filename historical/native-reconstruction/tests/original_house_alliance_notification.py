# SPDX-License-Identifier: GPL-3.0-or-later
"""Unmodified complete4EC5E0 with explicit supplied session/diplomacy leaves."""
import struct
from collections import Counter
from original_presentation import PresentationOracle,STOP
from verify_house_alliance_notification import verify,RANGES
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESI,UC_X86_REG_ESP,UC_X86_REG_EIP
ARENA=0x3000000;SIZE=0x10000;HOUSE=ARENA+0x1000;RULES=ARENA+0x4000;SESSION=ARENA+0x6000;VTABLE=ARENA+0x6100;VIRTUAL=ARENA+0x6200;SLOTS=ARENA+0x7000;ALT=ARENA+0x7100
GLOBALS=(0x839848,0xa3d29c,0xa3d298,0xa322a8,0xa3229c)
class HouseAllianceNotificationOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(ARENA,SIZE);self.active=False;self.counts=Counter();self.u.hook_add(UC_HOOK_CODE,self.code)
 def va(self,a):return a
 def word(self,p):return struct.unpack('<I',self.u.mem_read(p,4))[0]
 def byte(self,p):return self.u.mem_read(p,1)[0]
 def hp(self,i):return HOUSE+(i-1)*0x400 if i else 0
 def hid(self,p):
  i=(p-HOUSE)//0x400+1;assert 1<=i<=4 and p==self.hp(i);return i
 def change(self,p,v,n=4):
  data=int(v&((1<<(n*8))-1)).to_bytes(n,'little');self.u.mem_write(p,data)
  if ARENA<=p and p+n<=ARENA+SIZE:self.expected[p-ARENA:p-ARENA+n]=data
  else:
   assert p in GLOBALS and n==4;self.expectedGlobals[p]=data
 def mutate(self,query):
  m=self.f['mutation']
  if self.changed or not m or query!=(m<=2):return
  self.changed=True
  if m==1:self.change(RULES+0x111d,0,1);self.change(0xa3d29c,0);self.change(0xa3d298,1)
  if m==2:self.change(RULES+0x111d,1,1);self.change(0xa322a8,3);self.change(0xa3229c,ALT)
  if m==3:self.change(0xa322a8,1);self.change(0xa3229c,ALT);self.change(0xa3d298,1)
  if m==4:self.change(0xa322a8,6);self.change(0xa3229c,ALT);self.change(self.hp(2)+0x134,1,1);self.change(self.hp(3)+0x13d,255,1)
  if m==5:self.change(0xa3d298,0 if self.word(0xa3d298) else 1);self.change(self.hp(1)+0x134,255,1);self.change(self.hp(2)+0x135,255,1)
  if m==6:self.change(0xa322a8,0);self.change(self.hp(1)+0x191,239,1)
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  if a in (VIRTUAL,0x4e5660,0x4e5a70):
   self.counts[hex(a)]+=1;sp=u.reg_read(UC_X86_REG_ESP)
   if a==VIRTUAL:
    assert u.reg_read(UC_X86_REG_ECX)==SESSION;self.trace.extend(('Q',str(self.f['result'])));self.mutate(True);result=self.f['result'];args=0
   else:
    current=self.hid(u.reg_read(UC_X86_REG_ECX));target=self.hid(self.word(sp+4));announce=self.word(sp+8);assert announce==0
    self.trace.extend(map(str,('A' if a==0x4e5660 else 'E',current,target,announce)));self.mutate(False);result=0;args=8
   u.reg_write(UC_X86_REG_EAX,result);u.reg_write(UC_X86_REG_ESP,sp+4+args);u.reg_write(UC_X86_REG_EIP,self.word(sp));return
  assert any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected notification instruction',hex(a))
  if a==0x4ec5e0:self.counts[hex(a)]+=1
  if a==0x4ec661:self.trace.extend(map(str,('W',self.hid(u.reg_read(UC_X86_REG_ESI)),1)))
 def run(self,f):
  self.f=f;u=self.u;u.mem_write(ARENA,b'\xa5'*SIZE)
  for i,h in enumerate(f['houses'],1):
   for offset,value in zip((0x13d,0x134,0x135,0x191),h):u.mem_write(self.hp(i)+offset,bytes([value]))
  u.mem_write(RULES+0x111d,bytes([f['enabled']]));self.put(SESSION,VTABLE);self.put(VTABLE+4,VIRTUAL)
  for i,v in enumerate(f['slots']):self.put(SLOTS+4*i,self.hp(v));self.put(ALT+4*i,self.hp(4-i%4))
  for p,v in zip(GLOBALS,(RULES,SESSION if f['session'] else 0,f['mode'],f['count'],SLOTS)):self.put(p,v)
  self.expected=bytearray(u.mem_read(ARENA,SIZE));self.expectedGlobals={p:bytes(u.mem_read(p,4)) for p in GLOBALS};self.trace=[];self.changed=False;self.active=True
  effects=[(self.hp(i)+0x191,1) for i in range(1,5)]
  try:self.checked_call(0x4ec5e0,[],0,writes=effects,inputs=list(RANGES.items()))
  finally:self.active=False
  observed=bytearray(u.mem_read(ARENA,SIZE))
  for p,n in effects:observed[p-ARENA:p-ARENA+n]=self.expected[p-ARENA:p-ARENA+n]
  assert observed==self.expected and all(bytes(u.mem_read(p,4))==v for p,v in self.expectedGlobals.items())
  signed=lambda v:v if v<2**31 else v-2**32
  self.trace.extend(map(str,('S',self.byte(RULES+0x111d),int(bool(self.word(0xa3d29c))),signed(self.word(0xa3d298)),signed(self.word(0xa322a8)),int(self.word(0xa3229c)==ALT))))
  for i in range(1,5):self.trace.extend(str(self.byte(self.hp(i)+offset)) for offset in (0x13d,0x134,0x135,0x191))
  return self.trace
