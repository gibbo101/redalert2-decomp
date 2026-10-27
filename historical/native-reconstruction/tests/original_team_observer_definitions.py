# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete original enumeration; INI/allocate/construct/load/boolean supplied."""
import struct
from original_presentation import PresentationOracle,STOP
from verify_team_observer_definitions import verify,RANGES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EIP
BASE=0x6900000;SIZE=0x10000;INI=BASE+0x100;RECORDS=tuple(BASE+0x1000+i*0x200 for i in range(8));BACK=BASE+0x3000;ALT=BASE+0x3100;KEYS=BASE+0x4000;VTABLE=BASE+0x5000;LOAD=BASE+0x5100
SERVICES=(0x50cb00,0x50ce00,0x782017,0x41c5c0,0x50f410,LOAD)
KEY_PROFILES=((),('alpha',),('alpha','beta','alpha'),('<none>','none','gamma'),('1234567890123456789012345',),('ALPHA','Beta'),(),('gamma','delta'),())
ENABLE=((),('alpha',),('alpha','beta','unknown'),('none','gamma'),('1234567890123456789012345',),('ALPHA','beta'),('alpha','beta','none'),('delta','gamma'),())
def hash_text(b):
 v=2166136261
 for c in b.split(b'\0')[0]:v=((v^c)*16777619)&0xffffffff
 return v
class TeamObserverDefinitionsOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(BASE,SIZE);self.active=False;self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.write)
 def va(self,a):return a
 def word(self,a):return int.from_bytes(self.u.mem_read(a,4),'little')
 def text(self,a):
  assert a
  out=bytearray()
  for i in range(128):
   c=self.u.mem_read(a+i,1)[0]
   if not c:return bytes(out)
   out.append(c)
  raise AssertionError('Unbounded enumeration string')
 def pid(self,p):
  assert p==0 or p in RECORDS,hex(p)
  return RECORDS.index(p)+1 if p else 0
 def event(self,k,a=0,b=0,c=0):self.trace.extend(map(str,(k,a,b,c)))
 def change(self,a,raw):
  self.u.mem_write(a,raw)
  if BASE<=a<a+len(raw)<=BASE+SIZE:self.expected[a-BASE:a-BASE+len(raw)]=raw
  else:self.globals[a]=bytes(raw)
 def change_word(self,a,v):self.change(a,struct.pack('<I',v&0xffffffff))
 def mutate(self,where):
  if self.mutated or self.f[7]!=where:return
  self.mutated=1;self.event(9,where)
  if where==1:self.change_word(0xa3d264,ALT)
  if where==2:self.change_word(0xa3d298,1);self.change_word(0xa3d270,1);self.change_word(0xa3d264,ALT)
  if where==3:self.change_word(0xa3d298,1)
  if where==5:self.change_word(0xa3d270,0)
  if where==6:self.change_word(self.word(0xa3d264),0)
 def write(self,u,access,a,n,v,_):
  if not self.active or not BASE<=a<a+n<=BASE+SIZE:return
  p=next((p for p in RECORDS if p<=a<a+n<=p+0x110),None);assert p is not None,('Unexpected enumeration arena write',hex(a),n)
  off=a-p;assert (off,n) in ((0x9c,4),(0xa4,1));v&=(1<<(8*n))-1;self.expected[a-BASE:a-BASE+n]=v.to_bytes(n,'little');self.event(8,self.pid(p),off,v)
  if off==0x9c and self.f[7]==4 and not self.mutated:self.mutated=1;self.event(9,4);self.change(p+0xa4,b'M')
 def ret(self,sp,pop,value=0):
  self.u.reg_write(UC_X86_REG_EAX,value&0xffffffff);self.u.reg_write(UC_X86_REG_EIP,self.word(sp));self.u.reg_write(UC_X86_REG_ESP,sp+4+pop)
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  assert a in SERVICES or any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected enumeration instruction',hex(a))
  sp=u.reg_read(UC_X86_REG_ESP);obj=u.reg_read(UC_X86_REG_ECX)
  if a==0x781f20:
   left,right=(self.text(self.word(sp+off)) for off in (4,8));self.event(3,hash_text(left),hash_text(right))
   if left==right==b'alpha':self.mutate(1);self.mutate(6)
   if left==b'alpha' and left.lower()!=right.lower():self.mutate(5)
  elif a in (0x50cb00,0x50ce00):
   assert obj==INI;section=self.text(self.word(sp+4));assert section in (b'AITriggerTypes',b'AITriggerTypesEnable');which=int(section.endswith(b'Enable'));values=(KEY_PROFILES,ENABLE)[which][self.f[1]]
   if a==0x50cb00:
    count=-1 if self.f[1]==8 else len(values);self.event(1,which,count&0xffffffff);self.ret(sp,4,count)
   else:
    i=self.word(sp+8);key=values[i].encode();self.event(2,which,i,hash_text(key));self.ret(sp,8,KEYS+which*0x800+i*0x80)
  elif a==0x782017:
   assert self.word(sp+4)==0x110;self.allocations+=1;p=0 if self.f[3]==1 or self.f[3]==2 and self.allocations==2 else RECORDS[self.next]
   if p:self.next+=1
   self.event(4,0x110,self.pid(p));self.ret(sp,0,p)
  elif a==0x41c5c0:
   key=self.text(self.word(sp+4));self.event(5,self.pid(obj),hash_text(key));self.change(obj+0x24,key[:24].ljust(25,b'\0'));self.change_word(obj,VTABLE)
   for off in (0x9c,0xb0):self.change_word(obj+off,0)
   self.change(obj+0xa4,b'\0');count=self.word(0xa3d270);assert count<8;self.change_word(self.word(0xa3d264)+count*4,obj);self.change_word(0xa3d270,count+1);self.ret(sp,4,obj)
  elif a==LOAD:
   assert obj in RECORDS and self.word(sp+4)==INI;self.event(6,self.pid(obj),self.f[4]);self.change_word(obj+0xb0,self.word(obj+0xb0)+1);self.mutate(2);self.ret(sp,4,self.f[4])
  elif a==0x50f410:
   assert obj==INI and self.text(self.word(sp+4))==b'AITriggerTypesEnable' and self.word(sp+12)==0;key=self.text(self.word(sp+8));self.event(7,hash_text(key),self.f[5]);self.mutate(3);self.ret(sp,12,self.f[5])
 def run(self,f):
  self.f=f;self.trace=[];self.mutated=0;self.next=2;self.allocations=0;u=self.u;u.mem_write(BASE,b'\x5a'*SIZE)
  for i,p in enumerate(RECORDS):
   self.put(p,VTABLE);u.mem_write(p+0x24,(b'alpha' if i==0 else b'beta' if i==1 else b'unused').ljust(25,b'\0'));self.put(p+0x9c,0x11220000+i);u.mem_write(p+0xa4,bytes((128+i,)));self.put(p+0xb0,20+i);self.put(BACK+i*4,p);self.put(ALT+i*4,RECORDS[(1,0,2,3,4,5,6,7)[i]])
  self.put(VTABLE+0x64,LOAD)
  for which,profiles in enumerate((KEY_PROFILES,ENABLE)):
   for i,key in enumerate(profiles[f[1]]):u.mem_write(KEYS+which*0x800+i*0x80,key.encode()+b'\0')
  self.put(0xa3d264,ALT if f[2]==2 else BACK);self.put(0xa3d270,0 if f[2]==0 else -1 if f[2]==3 else 2);self.put(0xa3d298,f[6]);self.put(0xb2b098,0)
  self.expected=bytearray(u.mem_read(BASE,SIZE));self.globals={a:bytes(u.mem_read(a,4)) for a in (0xa3d264,0xa3d270,0xa3d298,0xb2b098)};self.active=True
  try:
   for _ in range(f[8]):self.checked_call(0x41d540,ecx=INI,edx=f[0],writes=[(BASE,SIZE),(0xa3d264,4),(0xa3d270,4),(0xa3d298,4)],inputs=[*RANGES.items(),(0x79b748,8),(0x7ceab0,15),(0x7cea98,21),(0x7cdecc,7),(0x7ce0ec,5)])
  finally:self.active=False
  assert bytes(u.mem_read(BASE,SIZE))==self.expected,'Unrelated enumeration arena changed'
  assert all(bytes(u.mem_read(a,len(v)))==v for a,v in self.globals.items()),'Unrelated enumeration globals changed'
  result=[self.mutated,self.word(0xa3d270),self.word(0xa3d298),self.next,self.allocations,*[self.pid(self.word(self.word(0xa3d264)+i*4)) for i in range(8)]]
  for p in RECORDS:result.extend((self.word(p+0x9c),u.mem_read(p+0xa4,1)[0],self.word(p+0xb0),hash_text(self.text(p+0x24))))
  return self.trace+['F',*map(str,result)]
