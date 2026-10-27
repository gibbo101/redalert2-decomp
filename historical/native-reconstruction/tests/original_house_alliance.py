# SPDX-License-Identifier: GPL-3.0-or-later
"""Unmodified complete House roots; only781F20 comparison is supplied."""
import struct
from collections import Counter
from original_presentation import PresentationOracle,STOP
from verify_house_alliance import verify,RANGES,TABLES
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EIP
ARENA=0x3000000;SIZE=0x30000;HOUSE=ARENA+0x1000;TYPE=ARENA+0x20000;HS=ARENA+0x22000;TS=ARENA+0x22100;AH=ARENA+0x22200;AT=ARENA+0x22300
GLOBALS=(0xa3d298,0xa40774,0xa322a8,0xa3229c,0x8661c0,0x8661b4)
def signed(v):return v if v<2**31 else v-2**32
class HouseAllianceOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(ARENA,SIZE);self.active=False;self.counts=Counter();self.u.hook_add(UC_HOOK_CODE,self.code)
 def va(self,a):return a
 def word(self,p):return struct.unpack('<I',self.u.mem_read(p,4))[0]
 def hp(self,i):return HOUSE+(i-1)*0x6000 if i else 0
 def tp(self,i):return TYPE+(i-1)*0x200 if i else 0
 def hid(self,p):
  if not p:return 0
  result=(p-HOUSE)//0x6000+1;assert 1<=result<=5 and p==self.hp(result);return result
 def tid(self,p):
  if not p:return 0
  result=(p-TYPE)//0x200+1;assert 1<=result<=4 and p==self.tp(result);return result
 def change(self,p,v,n=4):
  data=int(v&((1<<(n*8))-1)).to_bytes(n,'little');self.u.mem_write(p,data)
  if self.active:
   if ARENA<=p and p+n<=ARENA+SIZE:self.expected[p-ARENA:p-ARENA+n]=data
   else:self.expectedGlobals[p]=data
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  if a==0x781f20:
   sp=u.reg_read(UC_X86_REG_ESP);name=self.word(sp+4);wanted=self.word(sp+8);i=self.tid(name-0x24);assert wanted==0x7ceb30
   result=self.f['types'][i-1][3];self.trace.extend(('C',str(i),str(result)));self.counts['supplied_compare']+=1
   if not self.comparisons:
    f=self.f;current=self.hp(f['current']);target=self.hp(f['target']);mode=f['mutation'];t=self.word(target+0x34)
    if mode==1:self.change(t+0xbc,-1);self.change(0xa3d298,1);self.change(0xa40774,1);self.change(current+0x13d,0,1)
    if mode==2:self.change(0x8661b4,AT);self.change(0x8661c0,4);self.change(0xa322a8,2);self.change(current+0x5674,self.word(current+0x5674)^0xffffffff);self.change(target+0x34,self.tp(4));self.change(0xa3d298,0);self.change(0xa40774,0)
    if mode==3:self.change(0x8661c0,-1);self.change(current+0x30,self.word(target+0x30))
    if mode==4:self.change(0xa3229c,AH);self.change(0xa322a8,5);self.change(current+0x30,-32);self.change(t+0x1a6,u.mem_read(t+0x1a6,1)[0]^1,1)
   self.comparisons+=1;u.reg_write(UC_X86_REG_EAX,result&0xffffffff);u.reg_write(UC_X86_REG_ESP,sp+4);u.reg_write(UC_X86_REG_EIP,self.word(sp));return
  assert any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected House alliance instruction',hex(a))
  if a in RANGES:self.counts[hex(a)]+=1
 def run(self,f):
  self.f=f;u=self.u;u.mem_write(ARENA,b'\xa5'*SIZE)
  for i,t in enumerate(f['types'],1):
   p=self.tp(i);self.put(p+0xb8,t[0]);self.put(p+0xbc,t[1]);u.mem_write(p+0x1a6,bytes([t[2]]));u.mem_write(p+0x24,('Type'+str(i-1)).encode()+b'\0')
  for i,h in enumerate(f['houses'],1):
   p=self.hp(i);self.put(p+0x30,h[0]);self.put(p+0x34,self.tp(h[1]));u.mem_write(p+0x13d,bytes([h[2]]));self.put(p+0x5674,h[3])
  for i,v in enumerate(f['houseSlots']):self.put(HS+4*i,self.hp(v));self.put(AH+4*i,self.hp(5-i%5))
  for i,v in enumerate(f['typeSlots']):self.put(TS+4*i,self.tp(v));self.put(AT+4*i,self.tp(4-i))
  for p,v in zip(GLOBALS,(f['mode'],f['unrestricted'],f['houseCount'],HS,f['typeCount'],TS)):self.put(p,v)
  self.expected=bytearray(u.mem_read(ARENA,SIZE));self.expectedGlobals={p:bytes(u.mem_read(p,4)) for p in GLOBALS};self.trace=[];self.comparisons=0;self.active=True
  writes=[(p,4) for p in GLOBALS]+[(self.hp(i)+offset,n) for i in range(1,6) for offset,n in ((0x30,4),(0x34,4),(0x13d,1),(0x5674,4))]+[(self.tp(i)+offset,n) for i in range(1,5) for offset,n in ((0xbc,4),(0x1a6,1))]
  root=f['root'];address=(0x4ec4e0,0x4ed760,0x67af90)[root];ecx=self.hp(f['current']) if root==0 else f['country'] if root==1 else 0x7ceb30;args=[self.hp(f['target'])] if root==0 else []
  try:self.checked_call(address,args,ecx,writes=writes,inputs=[*RANGES.items(),*TABLES.items()])
  finally:self.active=False
  assert bytes(u.mem_read(ARENA,SIZE))==bytes(self.expected)
  assert all(bytes(u.mem_read(p,4))==v for p,v in self.expectedGlobals.items())
  value=u.reg_read(UC_X86_REG_EAX);result=value&255 if root==0 else self.hid(value) if root==1 else signed(value);self.trace.extend(('R',str(result),'S',str(signed(self.word(GLOBALS[0]))),str(signed(self.word(GLOBALS[1]))),str(signed(self.word(GLOBALS[2]))),str(signed(self.word(GLOBALS[4]))),str(int(self.word(GLOBALS[3])==AH)),str(int(self.word(GLOBALS[5])==AT))))
  for i in range(1,6):
   p=self.hp(i);self.trace.extend(map(str,(signed(self.word(p+0x30)),self.tid(self.word(p+0x34)),u.mem_read(p+0x13d,1)[0],self.word(p+0x5674))))
  for i in range(1,5):p=self.tp(i);self.trace.extend(map(str,(signed(self.word(p+0xbc)),u.mem_read(p+0x1a6,1)[0])))
  return self.trace
