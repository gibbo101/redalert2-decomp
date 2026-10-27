# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete Team regroup plus complete-to-return activation, supplied spatial/command children."""
from collections import Counter
from original_presentation import PresentationOracle,STOP
from verify_team_cohesion import RANGES,SERVICES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EIP
BASE=0x5900000;SIZE=0x10000;TEAM=BASE+0x1000;TYPE=BASE+0x2000;TASK=BASE+0x3000;SCRIPT=BASE+0x4000;STYPE=BASE+0x5000;RULES=BASE+0x6000;ANCHOR=BASE+0x7000;NEAR=BASE+0x7800;FEET=tuple(BASE+0x8000+i*0x1000 for i in range(4));VT=BASE+0xc000
class TeamCohesionOracle(PresentationOracle):
 def __init__(self,exe):
  super().__init__(exe,allow_patched=True);self.u.mem_map(BASE,SIZE);self.active=False;self.counts=Counter();self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.write)
 def va(self,a):return a
 def word(self,a):return int.from_bytes(self.u.mem_read(a,4),'little')
 def signed(self,a):return (self.word(a)+2**31)%2**32-2**31
 def event(self,k,a=0,b=0,c=0,d=0,e=0):self.trace.extend(map(str,(k,a,b,c,d,e)))
 def index(self,p):assert p in FEET;return FEET.index(p)
 def ret(self,sp,n,v=0):
  self.u.reg_write(UC_X86_REG_EAX,v&0xffffffff);self.u.reg_write(UC_X86_REG_EIP,self.word(sp));self.u.reg_write(UC_X86_REG_ESP,sp+4+n)
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  assert a in SERVICES or any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected cohesion instruction',hex(a))
  assert a not in (0x6b7b28,0x6b7bd2,0x6b7d08,0x6b807a),'Unjoined active/empty Team path'
  if a in RANGES:self.counts[hex(a)]+=1
  sp=u.reg_read(UC_X86_REG_ESP);ecx=u.reg_read(UC_X86_REG_ECX);f=self.f
  if a==0x6b8bb0:assert ecx==TEAM;self.event(12)
  if a==0x668900:assert ecx==SCRIPT;self.event(13)
  if a==0x6b9f40 and not f[0]:assert ecx==TEAM;self.event(16)
  if a==0x6d6e00:self.event(15,self.index(ecx))
  if a==0x668870:assert ecx==SCRIPT;self.event(2)
  if a==0x594770:self.event(5,self.index(ecx))
  if a==0x594cb0:assert self.word(sp+8)==0;self.event(6,self.index(ecx),self.word(sp+4),0)
  if a==0x5d4e40:assert ecx==ANCHOR;self.event(9)
  if a==0x6b9610:assert ecx==TEAM and [self.word(sp+4),self.word(sp+8)]==[TEAM+0x34,TEAM+0x38];self.event(14);self.ret(sp,8)
  elif a==0x5d4c00:assert self.word(sp+4)==ANCHOR;self.event(3,self.index(ecx));self.ret(sp,4,f[6])
  elif a==0x1100c30:self.event(4,self.index(ecx));self.ret(sp,0,f[11])
  elif a==0x1100c00:assert self.word(sp+4)==0;self.event(7,self.index(ecx));self.ret(sp,4)
  elif a==0x1100c10:
   target=self.word(sp+4);assert target in (0,ANCHOR,NEAR) and self.word(sp+8)==1;self.event(8,self.index(ecx),0 if not target else 100 if target==ANCHOR else 101,1);self.ret(sp,8)
  elif a==0x4c8af0:
   out,point=self.word(sp+4),self.word(sp+8);packed=self.word(point);x=(packed&65535);y=packed>>16;x=x-65536 if x&32768 else x;y=y-65536 if y&32768 else y;self.event(10,self.index(ecx),x&0xffffffff,y&0xffffffff);self.put(out,0xfff80007);self.ret(sp,8,out)
  elif a==0x548070:
   assert ecx==0x8324e0;point=self.word(sp+4);assert self.word(point)==0xfff80007;self.event(11,7,0xfffffff8);self.ret(sp,4,NEAR)
 def write(self,u,access,a,n,v,_):
  if not self.active or not BASE<=a<BASE+SIZE:return
  v&=(1<<(8*n))-1
  if TEAM<=a<a+n<=TEAM+156:
   off=a-TEAM;assert n==1 and 0x74<=off<0x84;self.event(1,99,off,v)
  elif a==SCRIPT+0x2c and n==4:self.event(1,98,0x2c,v)
  else:
   i=next((i for i,p in enumerate(FEET) if p<=a<a+n<=p+0x600),None)
   if i is not None:
    off=a-FEET[i];assert (off,n) in ((0x579,1),(0xa0,4),(0xa4,1));self.event(1,i,off,v)
   else:raise AssertionError(('Unexpected cohesion arena store',hex(a),n))
  self.expected[a-BASE:a-BASE+n]=v.to_bytes(n,'little')
 def run(self,f):
  self.f=f;self.trace=[];u=self.u;u.mem_write(BASE,b'\x5a'*SIZE);self.put(TEAM+0x24,TYPE);self.put(TYPE+0xdc,TASK);self.put(TASK+0x9c,1);self.put(TASK+0xa4,f[1]);self.put(TEAM+0x48,f[1]);self.put(TEAM+0x54,FEET[0] if f[1] else 0);self.put(TEAM+0x34,ANCHOR);self.put(TEAM+0x38,FEET[0] if f[1] else 0);self.put(TEAM+0x28,SCRIPT)
  u.mem_write(TEAM+0x74,bytes(16));u.mem_write(TEAM+0x75,bytes([f[17]]));u.mem_write(TEAM+0x7a,b'\1');u.mem_write(TEAM+0x7b,bytes([f[19]]));u.mem_write(TEAM+0x7d,b'\1');u.mem_write(TYPE+0xab,b'\0');u.mem_write(TYPE+0xa7,b'\0')
  self.put(0xa40774,f[10]);self.put(0x839848,RULES);self.put(RULES+0x1384,f[7]);self.put(RULES+0x1388,f[8]);self.put(SCRIPT+0x24,STYPE);self.put(SCRIPT+0x2c,-1 if f[9]==-1 else 0);self.put(STYPE+0xa0,1);self.put(STYPE+0xa4,f[9]);self.put(STYPE+0xa8,70)
  for off,target in ((0x1d0,0x594cb0),(0x16c,0x594770),(0x1c0,0x6d6e00),(0x2c,0x1100c30),(0x370,0x1100c00),(0x410,0x1100c10),(0x48,0x5d4e40)):self.put(VT+off,target)
  for i,p in enumerate(FEET):
   self.put(p,VT);self.put(p+0x4c8,FEET[i+1] if i+1<f[1] else 0);self.put(p+0x6c,f[3]);u.mem_write(p+0x7d,bytes([f[2]]));u.mem_write(p+0x76,bytes([f[4]]));u.mem_write(p+0x579,bytes([128 if f[5]&(1<<i) else 0]));self.put(p+0x494,NEAR if f[15] else 0);self.put(p+0x228,NEAR if f[16] else 0);self.put(p+0x98,f[12]);self.put(p+0xa0,f[13]);u.mem_write(p+0xa4,bytes([f[14]]));u.mem_write(p+0x205,bytes([f[18]]))
  self.put(ANCHOR,VT)
  for i,v in enumerate((-513,767,208)):self.put(ANCHOR+0x88+4*i,v)
  self.expected=bytearray(u.mem_read(BASE,SIZE));self.active=True
  try:self.checked_call(0x6b9f40 if f[0] else 0x6b7ad0,[],TEAM,writes=[(TEAM,156),(SCRIPT+0x2c,4),*[(p,0x600) for p in FEET]],inputs=[*RANGES.items(),(VT,0x414),(TYPE,0xe0),(TASK,0xe0),(STYPE,0xac),(RULES,0x138c),(ANCHOR,0x94)])
  finally:self.active=False
  result=u.reg_read(UC_X86_REG_EAX)&255 if f[0] else -1
  assert bytes(u.mem_read(BASE,SIZE))==self.expected,'Unrelated cohesion arena changed'
  final=[result,self.signed(SCRIPT+0x2c),*u.mem_read(TEAM+0x74,16)]
  for p in FEET:final.extend([*u.mem_read(p+0x579,1),self.word(p+0x98),self.word(p+0xa0),*u.mem_read(p+0xa4,1),int(bool(self.word(p+0x494)))])
  return self.trace+['F',*map(str,final)]
