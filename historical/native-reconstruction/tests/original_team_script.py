# SPDX-License-Identifier: GPL-3.0-or-later
"""Unchanged complete-to-return active Team50 calls, supplied anchor only."""
from collections import Counter
from original_presentation import PresentationOracle,STOP
from verify_team_script import RANGES,SERVICES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EIP
BASE=0x5a00000;SIZE=0x10000;TEAM=BASE+0x1000;TYPE=BASE+0x2000;TASK=BASE+0x3000;SCRIPT=BASE+0x4000;STYPE=BASE+0x5000;TOKEN=BASE+0x6000;FEET=tuple(BASE+0x8000+i*0x1000 for i in range(4));VT=BASE+0xc000
class TeamScriptOracle(PresentationOracle):
 def __init__(self,exe):
  super().__init__(exe,allow_patched=True);self.u.mem_map(BASE,SIZE);self.active=False;self.counts=Counter();self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.write)
 def va(self,a):return a
 def word(self,a):return int.from_bytes(self.u.mem_read(a,4),'little')
 def signed(self,a):return (self.word(a)+2**31)%2**32-2**31
 def event(self,k,a=0,b=0,c=0,d=0,e=0):self.trace.extend(map(str,(k,a,b,c,d,e)))
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  assert a in SERVICES or any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected Script instruction',hex(a))
  assert a not in (0x6b7b31,0x6b7b4b,0x6b7bd2,0x6b7c36,0x6b8747,0x6b7d30,0x6b807a),('Unjoined Team Script path',hex(a))
  if a in RANGES:self.counts[hex(a)]+=1
  sp=u.reg_read(UC_X86_REG_ESP);ecx=u.reg_read(UC_X86_REG_ECX)
  if a==0x6b8bb0:assert ecx==TEAM;self.event(2)
  elif a==0x6b9610:
   assert ecx==TEAM and [self.word(sp+4),self.word(sp+8)]==[TEAM+0x34,TEAM+0x38];self.event(3)
   u.reg_write(UC_X86_REG_EIP,self.word(sp));u.reg_write(UC_X86_REG_ESP,sp+12)
  elif a==0x6d6e00:self.event(4,FEET.index(ecx))
  elif a==0x668920:assert ecx==SCRIPT;self.event(5)
  elif a==0x668940:assert ecx==SCRIPT;self.event(6)
  elif a==0x668870:assert ecx==SCRIPT;self.event(7)
  elif a==0x6d6e50:assert self.word(sp+4)==0;self.event(8,FEET.index(ecx))
  elif a==0x6b79e0:assert ecx==TEAM and self.word(sp+4)==0
 def write(self,u,access,a,n,v,_):
  if not self.active or not BASE<=a<BASE+SIZE:return
  v&=(1<<(n*8))-1
  if TEAM<=a<a+n<=TEAM+156:
   off=a-TEAM;assert (n==1 and 0x74<=off<0x84) or (n==4 and off in (0x3c,0x40));self.event(1,99,off,v)
  elif a==SCRIPT+0x2c and n==4:self.event(1,98,0x2c,v)
  else:
   i=next((i for i,p in enumerate(FEET) if p<=a<a+n<=p+0x600),None)
   assert i is not None,('Unexpected Script arena store',hex(a),n)
   off=a-FEET[i];assert n==4 and off in (0xd8,0x1b0);self.event(1,i,off,v)
  self.expected[a-BASE:a-BASE+n]=v.to_bytes(n,'little')
 def run(self,f):
  self.trace=[];u=self.u;u.mem_write(BASE,b'\x5a'*SIZE)
  for off,value in ((0x24,TYPE),(0x28,SCRIPT),(0x3c,0),(0x40,0),(0x48,f[0]),(0x54,FEET[f[0]-1 if f[6] else 0])):self.put(TEAM+off,value)
  u.mem_write(TEAM+0x74,bytes(16))
  for off,value in ((0x78,1),(0x79,1),(0x7f,1),(0x80,f[2]),(0x7d,f[1])):u.mem_write(TEAM+off,bytes([value]))
  self.put(TYPE+0xdc,TASK);self.put(TASK+0x9c,1);self.put(TASK+0xa4,f[0]);u.mem_write(TYPE+0xab,bytes([f[7]]));u.mem_write(TYPE+0xa7,b'\0');u.mem_write(TYPE+0xec,b'\0')
  self.put(SCRIPT+0x24,STYPE);self.put(SCRIPT+0x2c,f[8]);self.put(STYPE+0xa0,2)
  for i in range(2):self.put(STYPE+0xa4+i*8,50);self.put(STYPE+0xa8+i*8,f[3])
  self.put(VT+0x1c0,0x6d6e00)
  order=list(range(f[0]));order=order[::-1] if f[6] else order
  for i,p in enumerate(FEET):
   self.put(p,VT);self.put(p+0x4c8,0);self.put(p+0xd8,f[4]);self.put(p+0x1b0,TOKEN if f[5] else 0);u.mem_write(p+0x205,b'\0')
  for i,j in zip(order,order[1:]):self.put(FEET[i]+0x4c8,FEET[j])
  self.expected=bytearray(u.mem_read(BASE,SIZE));self.active=True
  try:self.checked_call(0x6b7ad0,[],TEAM,writes=[(TEAM,156),(SCRIPT+0x2c,4),*[(p,0x600) for p in FEET]],inputs=[*RANGES.items(),(0x6b8768,59*4),(VT,0x1c4),(TYPE,0xf0),(TASK,0xe0),(STYPE,0xb4),(TOKEN,4)])
  finally:self.active=False
  assert bytes(u.mem_read(BASE,SIZE))==self.expected,'Unrelated Team Script arena changed'
  final=[self.signed(SCRIPT+0x2c),*u.mem_read(TEAM+0x74,16),self.word(TEAM+0x3c),self.word(TEAM+0x40)]
  for p in FEET:final.extend((self.word(p+0xd8),int(bool(self.word(p+0x1b0)))))
  return self.trace+['F',*map(str,final)]
