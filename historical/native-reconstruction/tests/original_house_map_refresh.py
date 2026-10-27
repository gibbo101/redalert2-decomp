# SPDX-License-Identifier: GPL-3.0-or-later
"""Unmodified map sight scans and House children around named supplied effects."""
import struct
from collections import Counter
from original_presentation import PresentationOracle,STOP
from verify_house_map_refresh import verify,RANGES
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EIP
ARENA=0x3000000;SIZE=0x30000;HOUSE=ARENA+0x1000;TYPE=ARENA+0x15000;ACTOR=ARENA+0x19000;VTABLE=ARENA+0x1d000;SLOTS=ARENA+0x1e000;ALT=ARENA+0x1e100;RULES=ARENA+0x20000;SERVICE=ARENA+0x24000
SLOTS_BY_SERVICE={44:SERVICE,128:SERVICE+16,1048:SERVICE+32,1052:SERVICE+48,940:SERVICE+64,944:SERVICE+80}
GLOBALS=(0xa3d298,0xa35db4,0xa40c30,0xa40c24,0x839848)
def signed(v):return v if v<2**31 else v-2**32
class HouseMapRefreshOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(ARENA,SIZE);self.active=False;self.counts=Counter();self.u.hook_add(UC_HOOK_CODE,self.code)
 def va(self,a):return a
 def word(self,p):return struct.unpack('<I',self.u.mem_read(p,4))[0]
 def hp(self,i):return HOUSE+(i-1)*0x6000 if i else 0
 def ap(self,i):return ACTOR+(i-1)*0x1000 if i else 0
 def tp(self,i):return TYPE+(i-1)*0x1000
 def hid(self,p):
  if not p:return 0
  i=(p-HOUSE)//0x6000+1;assert 1<=i<=3 and p==self.hp(i);return i
 def aid(self,p):
  i=(p-ACTOR)//0x1000+1;assert 1<=i<=3 and p==self.ap(i);return i
 def tid(self,p):
  i=(p-TYPE)//0x1000+1;assert 1<=i<=3 and p==self.tp(i);return i
 def change(self,p,v,n=4):
  data=int(v&((1<<(n*8))-1)).to_bytes(n,'little');self.u.mem_write(p,data)
  if self.active:
   if ARENA<=p and p+n<=ARENA+SIZE:self.expected[p-ARENA:p-ARENA+n]=data
   else:assert p in GLOBALS and n==4;self.expectedGlobals[p]=data
 def mutate(self,i,service):
  if self.changed:return
  mode=self.f['mutation'];entered=service==44 if mode in (1,2,6) else service in (1048,1052) if mode==3 else service==128 if mode==4 else service==0 if mode==5 else service in (940,944) if mode==7 else False
  if not entered:return
  self.changed=True;a=self.ap(i)
  if mode==1:self.change(a+0x76,1,1);self.change(a+0x373,0,1)
  if mode==2:self.change(0xa40c24,ALT);self.change(0xa40c30,0);self.change(0xa3d298,1);self.change(0xa35db4,self.hp(3));self.change(a+0x1b4,self.hp(3))
  if mode==3:
   for p,v in [(a+0x88,-2**31),(a+0x8c,2**31-1),(a+0x90,-7),(a+0x1f4,2**31-1),(a+0x900,self.tp(2)),(0xa35db4,self.hp(2))]:self.change(p,v)
   self.change(RULES+0x142b,0,1)
  if mode==4:
   t=self.word(a+0x900);self.change(a+0x900,self.tp(3));self.change(t+0xadd,self.u.mem_read(t+0xadd,1)[0]^255,1);self.change(t+0x534,self.u.mem_read(t+0x534,1)[0]^1,1);self.change(0xa3d298,1);self.change(0xa35db4,self.word(a+0x1b4))
  if mode==5:
   for p,v in [(a+0x88,17),(a+0x8c,-19),(a+0x90,23),(a+0x1b4,self.hp(1)),(0xa40c30,-2)]:self.change(p,v)
   self.change(RULES+0x142b,255,1)
  if mode==6:
   h=self.hp(2);self.change(a+0x1b4,h);self.change(h+0x5674,self.word(h+0x5674)^0xffffffff);self.change(h+0x134,0,1);self.change(h+0x135,1,1);self.change(RULES+0x142b,1,1);self.change(0xa3d298,0);self.change(0xa35db4,self.hp(1))
  if mode==7:self.change(self.ap(i%3+1)+0x76,255,1);self.change(self.ap(i%3+1)+0x1b4,self.hp(3));self.change(0xa40c24,ALT);self.change(0xa40c30,4)
 def ret(self,value=0,args=0):
  u=self.u;sp=u.reg_read(UC_X86_REG_ESP);u.reg_write(UC_X86_REG_EAX,value&0xffffffff);u.reg_write(UC_X86_REG_ESP,sp+4+args);u.reg_write(UC_X86_REG_EIP,self.word(sp))
 def emit(self,*v):self.trace.extend(map(str,v))
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  if a in SLOTS_BY_SERVICE.values():
   slot=next(k for k,v in SLOTS_BY_SERVICE.items() if v==a);i=self.aid(u.reg_read(UC_X86_REG_ECX));actor=self.ap(i);sp=u.reg_read(UC_X86_REG_ESP);self.counts['supplied_'+str(slot)]+=1
   if slot==44:
    result=self.f['actors'][i-1][4+min(self.kindCalls[i-1],2)];self.kindCalls[i-1]+=1;self.emit('K',i,result);self.mutate(i,slot);self.ret(result)
   elif slot==128:
    result=self.word(actor+0x900);self.emit('T',i,self.tid(result));self.mutate(i,slot);self.ret(result)
   elif slot in (1048,1052):
    self.lastActor=i;args=[self.word(sp+4+j*4) for j in range(4)];self.emit('S',i,slot,*map(signed,args[:3]),self.hid(args[3]));self.mutate(i,slot);self.ret(args=16)
   else:self.emit('I',i,slot);self.mutate(i,slot);self.ret()
   return
  if a==0x54a550:
   assert u.reg_read(UC_X86_REG_ECX)==0x8324e0 and self.lastActor
   sp=u.reg_read(UC_X86_REG_ESP);point=self.word(sp+4);coords=struct.unpack('<3i',u.mem_read(point,12));inner,outer,disabled=[self.word(sp+8+j*4) for j in range(3)];self.emit('P',self.lastActor,*coords,signed(inner),signed(outer),disabled);self.counts['supplied_post_sight']+=1;self.mutate(self.lastActor,0);self.ret(args=16);return
  assert any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected House map refresh instruction',hex(a))
  if a in RANGES:
   self.counts[hex(a)]+=1
   if a==0x4f52b0:self.emit('H',self.hid(u.reg_read(UC_X86_REG_ECX)))
   if a==0x4e5540:self.emit('A',self.hid(u.reg_read(UC_X86_REG_ECX)),self.hid(self.word(u.reg_read(UC_X86_REG_ESP)+4)))
 def run(self,f):
  self.f=f;u=self.u;u.mem_write(ARENA,b'\xa5'*SIZE)
  for i,h in enumerate(f['houses'],1):
   p=self.hp(i);self.put(p+0x30,h[0]);u.mem_write(p+0x134,bytes(h[1:3]));self.put(p+0x5674,h[3])
  for i,t in enumerate(f['types'],1):u.mem_write(self.tp(i)+0x534,bytes([t[0]]));u.mem_write(self.tp(i)+0xadd,bytes([t[1]]))
  for i,a in enumerate(f['actors'],1):
   p=self.ap(i);self.put(p,VTABLE);u.mem_write(p+0x76,bytes([a[0]]));u.mem_write(p+0x373,bytes([a[1]]));self.put(p+0x1b4,self.hp(a[2]));self.put(p+0x900,self.tp(a[3]));self.put(p+0x1f4,a[7]);u.mem_write(p+0x88,struct.pack('<3i',*a[8:11]))
  for slot,p in SLOTS_BY_SERVICE.items():self.put(VTABLE+slot,p)
  for i,v in enumerate(f['slots']):self.put(SLOTS+4*i,self.ap(v));self.put(ALT+4*i,self.ap(3-i%3))
  u.mem_write(RULES+0x142b,bytes([f['rule']]));
  for p,v in zip(GLOBALS,(f['mode'],self.hp(f['current']),f['count'],SLOTS,RULES)):self.put(p,v)
  self.expected=bytearray(u.mem_read(ARENA,SIZE));self.expectedGlobals={p:bytes(u.mem_read(p,4)) for p in GLOBALS};self.trace=[];self.changed=False;self.kindCalls=[0]*3;self.lastActor=0;self.active=True
  try:self.checked_call(0x49de00 if f['addition'] else 0x49e000,[f['skip'],f['argument']],0x8324e0,inputs=RANGES.items())
  finally:self.active=False
  assert bytes(u.mem_read(ARENA,SIZE))==self.expected
  assert all(bytes(u.mem_read(p,4))==v for p,v in self.expectedGlobals.items())
  self.emit('R',0,'F',signed(self.word(0xa40c30)),signed(self.word(0xa3d298)),self.hid(self.word(0xa35db4)),u.mem_read(RULES+0x142b,1)[0],int(self.word(0xa40c24)==ALT))
  for i in range(1,4):
   p=self.hp(i);self.emit(signed(self.word(p+0x30)),u.mem_read(p+0x134,1)[0],u.mem_read(p+0x135,1)[0],self.word(p+0x5674))
  for i in range(1,4):self.emit(u.mem_read(self.tp(i)+0x534,1)[0],u.mem_read(self.tp(i)+0xadd,1)[0])
  for i in range(1,4):
   p=self.ap(i);self.emit(u.mem_read(p+0x76,1)[0],u.mem_read(p+0x373,1)[0],self.hid(self.word(p+0x1b4)),self.tid(self.word(p+0x900)),*f['actors'][i-1][4:7],signed(self.word(p+0x1f4)),*struct.unpack('<3i',u.mem_read(p+0x88,12)))
  return self.trace
