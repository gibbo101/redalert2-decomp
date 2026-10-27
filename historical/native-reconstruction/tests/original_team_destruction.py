# SPDX-License-Identifier: GPL-3.0-or-later
"""Unchanged complete6B7770/6BE740 with named child and search services supplied."""
from original_presentation import PresentationOracle,STOP
from verify_team_destruction import verify,RANGES,REG,VTABLES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_EDX,UC_X86_REG_EIP,UC_X86_REG_ESP
BASE=0x6500000;SIZE=0x20000;TEAM=BASE+0x1000;TYPES=(BASE+0x2000,BASE+0x2200);HOUSE=BASE+0x3000;TAG=BASE+0x9000;OTHER=BASE+0x9200
FEET=tuple(BASE+0xa000+i*0x100 for i in range(4));OBS=tuple(BASE+0xb000+i*0x100 for i in range(4))
SLOTS=tuple(BASE+0xc000+i*0x100 for i in range(5));ALT=tuple(BASE+0xd000+i*0x100 for i in range(5));OBACK=BASE+0xe000;OALT=BASE+0xe100;VT=BASE+0xf000
SEARCH=BASE+0x10000;TYPEDELETE=BASE+0x10010
SERVICES=(0x41dfb0,0x41e070,0x6b8fb0,0x6b3cc0,0x6ecb90,0x40ff90,0x781d3b,SEARCH,TYPEDELETE)
class TeamDestructionOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(BASE,SIZE);self.active=False;self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.write)
 def va(self,a):return a
 def word(self,a):return int.from_bytes(self.u.mem_read(a,4),'little')
 def pid(self,p):
  d={0:0,TEAM:1,TYPES[0]:2,TYPES[1]:3,HOUSE:4,TAG:5,OTHER:6,**{p:10+i for i,p in enumerate(FEET)},**{p:20+i for i,p in enumerate(OBS)},**{p:30+i for i,p in enumerate(REG)}}
  assert p in d,hex(p);return d[p]
 def event(self,k,a=0,b=0,c=0,d=0,e=0):self.trace.extend(map(str,(k,a,b,c,d,e)))
 def change(self,p,v):
  self.put(p,v)
  if BASE<=p<p+4<=BASE+SIZE:self.expected[p-BASE:p-BASE+4]=(v&0xffffffff).to_bytes(4,'little')
 def mutate(self,where):
  if self.mutated or self.f[13]!=where:return
  self.mutated=1;self.event(9,where)
  if where==1:self.change(TEAM+0x24,TYPES[1]);self.u.mem_write(TEAM+0x83,b'\0');self.expected[TEAM+0x83-BASE]=0;self.put(0xa3d264,OALT);self.put(0xa3d270,4)
  if where==2:self.change(TEAM+0x24,TYPES[1]);self.change(TEAM+0x70,OTHER)
  if where==3:self.change(TEAM+0x24,TYPES[1]);self.u.mem_write(TEAM+0x74,b'\x80');self.expected[TEAM+0x74-BASE]=128
  if where==4:
   self.put(REG[0]+4,ALT[0]);self.put(REG[0]+16,5)
  if where==5:self.put(REG[0]+4,ALT[0]);self.put(REG[0]+16,1)
 def write(self,u,access,a,n,v,_):
  if not self.active:return
  value=v&((1<<(8*n))-1)
  if a in tuple(r+16 for r in REG):self.event(1,self.pid(a-16),16,n,value);return
  if not BASE<=a<a+n<=BASE+SIZE:return
  if TEAM<=a<a+n<=TEAM+156:
   off=a-TEAM;assert n==4 and off in (0,4,8,12,0x70)
   value=VTABLES.index(value) if off<16 else self.pid(value);owner=1
  elif a in tuple(t+0xd4 for t in TYPES):off=0xd4;owner=self.pid(a-off);assert n==4
  elif a==HOUSE+0x555c:off=0x555c;owner=4;assert n==4
  else:
   found=next(((i,b) for i in range(5) for b in (SLOTS[i],ALT[i]) if b<=a<a+n<=b+32),None);assert found is not None,(hex(a),n)
   i,b=found;owner=30+i;off=0x100+a-b;value=self.pid(value);assert n==4
  self.event(1,owner,off,n,value);self.expected[a-BASE:a-BASE+n]=(v&((1<<(n*8))-1)).to_bytes(n,'little')
  if owner==30 and off==0x100:self.mutate(5)
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  if any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()):return
  assert a in SERVICES,('Uninspected destructor instruction',hex(a))
  sp=u.reg_read(UC_X86_REG_ESP);obj=u.reg_read(UC_X86_REG_ECX);pop=0;result=0
  if a in SERVICES[:2]:self.event(2,self.pid(obj),int(a==SERVICES[0]));self.mutate(1)
  elif a==0x6b8fb0:
   foot=self.word(sp+4);assert obj==TEAM and self.word(sp+8)==0xffffffff and self.word(sp+12)==0
   self.event(3,self.pid(foot),0xffffffff,0);self.change(TEAM+0x54,self.word(foot));self.mutate(2);pop=12;result=1
  elif a==0x6b3cc0:self.event(4,self.pid(obj));assert self.word(obj+0x2c)==0
  elif a==0x6ecb90:assert obj==TEAM and u.reg_read(UC_X86_REG_EDX)&255==1;self.event(5,1,1);self.mutate(3)
  elif a==SEARCH:
   i=REG.index(obj);assert self.word(self.word(sp+4))==TEAM
   count=self.word(obj+16);count=count if count<2**31 else count-2**32;slots=self.word(obj+4)
   result=next((j for j in range(count) if self.word(slots+4*j)==TEAM),-1)
   self.event(6,30+i,result&0xffffffff);self.mutate(4) if i==0 else None;pop=4
  elif a==TYPEDELETE:assert self.word(sp+4)==1;self.event(7,self.pid(obj),1);pop=4
  elif a==0x40ff90:assert obj==TEAM;self.event(8,1)
  elif a==0x781d3b:assert self.word(sp+4)==TEAM;self.event(10,1)
  u.reg_write(UC_X86_REG_EAX,result&0xffffffff);u.reg_write(UC_X86_REG_EIP,self.word(sp));u.reg_write(UC_X86_REG_ESP,sp+4+pop)
 def run(self,f):
  self.f=f;self.trace=[];self.mutated=0;u=self.u;u.mem_write(BASE,b'\x5a'*SIZE)
  for off,v in ((0x24,TYPES[0] if f[0] else 0),(0x2c,HOUSE if f[1] else 0),(0x54,FEET[0] if f[4] else 0),(0x70,(0,TAG,OTHER)[f[5]])):self.put(TEAM+off,v)
  u.mem_write(TEAM+0x74,bytes([f[7]]));u.mem_write(TEAM+0x83,bytes([f[8]]))
  for i,t in enumerate(TYPES):self.put(t,VT);self.put(t+0xd4,f[10] if not i else -2147483648);u.mem_write(t+0xee,bytes([f[2] if not i else 255]))
  self.put(HOUSE+0x555c,f[9]);self.put(TAG+0x2c,f[6]);self.put(OTHER+0x2c,0)
  for i,p in enumerate(FEET):self.put(p,FEET[i+1] if i+1<f[4] else 0)
  self.put(0xa3d264,OBACK);self.put(0xa3d270,f[12]);u.mem_write(0xa40958,bytes([f[3]]))
  for i,p in enumerate(OBS):self.put(p+0xdc,(TYPES[0],0,TYPES[1],TYPES[0])[i]);self.put(OBACK+4*i,p);self.put(OALT+4*i,OBS[3-i])
  self.put(VT+16,SEARCH);self.put(VT+32,TYPEDELETE)
  patterns=((OTHER,TEAM,TEAM,OTHER,TEAM,0,0,0),(TEAM,OTHER,TEAM,0,0,0,0,0),(OTHER,OTHER,0,0,0,0,0,0),(OTHER,TEAM,0,0,0,0,0,0))
  counts=(5,3,2,2)
  for i,r in enumerate(REG):
   profile=(f[11]+i)%4;self.put(r,VT);self.put(r+4,SLOTS[i]);self.put(r+16,counts[profile])
   for j,p in enumerate(patterns[profile]):self.put(SLOTS[i]+4*j,p)
   for j,p in enumerate((TEAM,OTHER,TEAM,OTHER,TEAM,0,0,0)):self.put(ALT[i]+4*j,p)
  self.expected=bytearray(u.mem_read(BASE,SIZE));self.active=True
  try:self.checked_call(0x6be740,[f[14]],TEAM,writes=[(BASE,SIZE),*((r+4,16) for r in REG),(0xa3d264,4),(0xa3d270,4)],inputs=[*RANGES.items(),(VT,36),(0xa40958,1)])
  finally:self.active=False
  assert bytes(u.mem_read(BASE,SIZE))==self.expected,'Unrelated Team destruction arena changed'
  final=[self.pid(u.reg_read(UC_X86_REG_EAX)),self.mutated,self.pid(self.word(TEAM+0x24)),self.pid(self.word(TEAM+0x54)),self.pid(self.word(TEAM+0x70)),self.word(HOUSE+0x555c),*[self.word(t+0xd4) for t in TYPES],u.mem_read(TEAM+0x74,1)[0],u.mem_read(TEAM+0x83,1)[0],self.word(0xa3d270)]
  for r in REG:final.extend([self.word(r+16),*[self.pid(self.word(self.word(r+4)+4*j)) for j in range(8)]])
  return self.trace+['F',*map(str,final)]
