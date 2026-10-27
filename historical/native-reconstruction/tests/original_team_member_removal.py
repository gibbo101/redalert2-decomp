# SPDX-License-Identifier: GPL-3.0-or-later
"""Unchanged complete6B8FB0; named children supplied and explicitly traced."""
from original_presentation import PresentationOracle,STOP
from verify_team_member_removal import verify,RANGES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_EIP,UC_X86_REG_ESP
BASE=0x6300000;SIZE=0x12000;TEAM=BASE+0x1000;OTHER=BASE+0x1200;FEET=tuple(BASE+0x2000+i*0x1000 for i in range(4));TYPE=BASE+0x6000;TASK=BASE+0x7000;TASK2=BASE+0x8000;TAG=BASE+0x9000;OTAG=BASE+0x9200;HOUSE=BASE+0xa000;FTYPE=BASE+0xb000;VT=BASE+0xc000;CELL=BASE+0xd000;SERVICE=(0x4f52f0,0x5d4430,BASE+0xe020,BASE+0xe030,BASE+0xe040)
class TeamMemberRemovalOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(BASE,SIZE);self.active=False;self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.write)
 def va(self,a):return a
 def word(self,a):return int.from_bytes(self.u.mem_read(a,4),'little')
 def pid(self,p):
  d={0:0,TEAM:1,OTHER:2,TAG:30,OTAG:31,HOUSE:40,TYPE:50,TASK:60,TASK2:61,FTYPE:70,CELL:80,**{p:10+i for i,p in enumerate(FEET)}}
  assert p in d,hex(p);return d[p]
 def event(self,k,a=0,b=0,c=0,d=0,e=0):self.trace.extend(map(str,(k,a,b,c,d,e)))
 def change(self,a,v):
  self.put(a,v);self.expected[a-BASE:a-BASE+4]=(v&0xffffffff).to_bytes(4,'little')
 def mutate(self,where):
  if self.mutated or self.f[20]!=where:return
  self.mutated=1;self.event(9,where)
  if where==1:self.change(TASK+0x9c,0)
  if where==2:self.change(TYPE+0xdc,TASK2)
  if where==3:self.change(TEAM+0x4c,0xfffffff0)
  if where==4:self.change(TEAM+0x54,FEET[3])
  if where==5:self.change(FEET[self.f[1]]+0x34,OTAG)
 def write(self,u,access,a,n,v,_):
  if not self.active or not BASE<=a<a+n<=BASE+SIZE:return
  owner=TEAM if TEAM<=a<a+n<=TEAM+156 else next((p for p in FEET if p<=a<a+n<=p+0x600),None)
  assert owner is not None,(hex(a),n)
  off=a-owner;allowed=(0x54,0x34,0x48,0x4c,*range(0x84,0x9c,4)) if owner==TEAM else (0x4c8,0x4c4,0x9c,0x498,0x22c)
  assert (n==4 and off in allowed) or (n==1 and off in ((0x7d,0x7e) if owner==TEAM else (0x5a2,0x579)))
  pointer=off in ((0x54,0x34) if owner==TEAM else (0x4c4,0x4c8,0x498,0x22c))
  self.event(1,self.pid(owner),off,n,self.pid(v) if pointer else v&((1<<(n*8))-1));self.expected[a-BASE:a-BASE+n]=(v&((1<<(n*8))-1)).to_bytes(n,'little')
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  if any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()):return
  assert a in SERVICE,('Uninspected removal instruction',hex(a))
  k=SERVICE.index(a);sp=u.reg_read(UC_X86_REG_ESP);obj=u.reg_read(UC_X86_REG_ECX);target=FEET[self.f[1]];pop=4;result=0
  if k==0:assert obj==HOUSE;self.event(2,40,self.f[14]&0xffffffff);self.mutate(5);result=self.f[14]
  if k==1:assert obj==target and self.word(sp+4)==0;self.event(3,self.pid(obj));self.change(obj+0x34,0);pop=8
  if k==2:assert obj==target;self.event(4,self.pid(obj));self.mutate(1);self.mutate(2);result=FTYPE
  if k==3:assert obj==target;self.event(5,self.pid(obj));self.mutate(3);result=self.f[10]
  if k==4:assert obj==target and self.word(sp+4)==0 and self.word(sp+8)==1;self.event(6,self.pid(obj),0,1);self.mutate(4);pop=12
  u.reg_write(UC_X86_REG_EAX,result&0xffffffff);u.reg_write(UC_X86_REG_EIP,self.word(sp));u.reg_write(UC_X86_REG_ESP,sp+pop)
 def run(self,f):
  self.f=f;self.trace=[];self.mutated=0;u=self.u;u.mem_write(BASE,b'\x5a'*SIZE)
  self.put(TEAM+0x24,TYPE if f[7]!=0 else 0);self.put(TYPE+0xdc,TASK if f[7]==2 else 0)
  for task,count in ((TASK,f[5]),(TASK2,2)):
   self.put(task+0x9c,count)
   for i in range(6):self.put(task+0xa8+8*i,FTYPE if i==(f[6] if task==TASK else 1) else TYPE)
  order=list(range(f[0]));order=order[::-1] if f[2] else order
  for i,p in enumerate(FEET):
   for off,v in ((0,VT),(0x4c4,TEAM if f[12] else OTHER),(0x4c8,0),(0x34,(0,TAG,OTAG)[f[13]]),(0x9c,123),(0x498,CELL),(0x22c,CELL),(0x1b4,HOUSE)):self.put(p+off,v)
   for off,v in ((0x579,(f[4]>>i)&1),(0x5a2,128),(0x7d,f[16]),(0x37d,f[17]),(0x76,f[18])):u.mem_write(p+off,bytes([v]))
  for i,j in zip(order,order[1:]):self.put(FEET[i]+0x4c8,FEET[j])
  for off,v in ((0x54,FEET[order[0]]),(0x70,TAG),(0x34,CELL),(0x48,f[8]),(0x4c,f[9])):self.put(TEAM+off,v)
  u.mem_write(TEAM+0x7d,b'\0\0')
  for i in range(6):self.put(TEAM+0x84+4*i,f[11])
  for off,v in ((0x84,SERVICE[2]),(0x2a0,SERVICE[3]),(0x414,SERVICE[4])):self.put(VT+off,v)
  self.put(0xa40774,f[15])
  self.expected=bytearray(u.mem_read(BASE,SIZE));self.active=True
  try:self.checked_call(0x6b8fb0,[FEET[f[1]],f[3],f[19]],TEAM,writes=[(TEAM,156),*[(p,0x600) for p in FEET]],inputs=[*RANGES.items(),(VT,0x418),(0xa40774,4)])
  finally:self.active=False
  assert bytes(u.mem_read(BASE,SIZE))==self.expected,'Unrelated Team removal arena changed'
  final=[u.reg_read(UC_X86_REG_EAX)&255,self.mutated,self.pid(self.word(TEAM+0x54)),self.word(TEAM+0x48),self.word(TEAM+0x4c),self.pid(self.word(TEAM+0x34)),*u.mem_read(TEAM+0x7d,2),*[self.word(TEAM+0x84+4*i) for i in range(6)],self.pid(self.word(TYPE+0xdc)),self.word(TASK+0x9c),self.word(TASK2+0x9c)]
  for p in FEET:final.extend([self.pid(self.word(p+off)) for off in (0x4c4,0x4c8,0x34)]+[*u.mem_read(p+0x5a2,1),self.word(p+0x9c),self.pid(self.word(p+0x498)),self.pid(self.word(p+0x22c)),*u.mem_read(p+0x579,1)])
  return self.trace+['F',*map(str,final)]
