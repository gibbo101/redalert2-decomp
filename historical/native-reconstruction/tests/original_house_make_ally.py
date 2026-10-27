# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete unmodified MakeAlly with actual score/eligibility/target children."""
import struct
from collections import Counter
from original_presentation import PresentationOracle,STOP,STACK
from original_target_reference import TargetReferenceOracle,PRIMARY,ALTERNATE,ARENA,SIZE,VT,SVT,KIND,ID,signed
from verify_house_make_ally import verify,RANGES,TABLES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_EDX,UC_X86_REG_ESP,UC_X86_REG_EIP
EXTRA=0x3100000;ESIZE=0x90000;HOUSE=EXTRA;TYPE=EXTRA+0x70000;OBJECT=EXTRA+0x74000;HS=EXTRA+0x77000;TS=EXTRA+0x77100;AS=EXTRA+0x77200;ALT=EXTRA+0x77300;SCORES=EXTRA+0x77400;RULES=EXTRA+0x78000;LOCALIZED=EXTRA+0x7a000
SCRATCH=STACK-0xa8;COUNTRY=ARENA+0x7020;OWNER=ARENA+0x7030;WEAPON=ARENA+0x7040;PERMISSION=ARENA+0x7050;RELEASE=ARENA+0x7060
GLOBALS=((0xabff58,4),(0xabff5c,4),(0xabff64,1),(0xabff68,4),(0xb2b628,4),(0xa3d298,4),(0xa40774,4),(0xa322a8,4),(0xa3229c,4),(0x8661c0,4),(0x8661b4,4),(0x832480,4),(0x832474,4),(0xa35db4,4),(0xa3d548,4),(0x839848,4))
class HouseMakeAllyOracle(TargetReferenceOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());PresentationOracle.__init__(self,exe,allow_patched=True);self.u.mem_map(ARENA,SIZE);self.u.mem_map(EXTRA,ESIZE);self.active=False;self.counts=Counter();self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.store)
 def op(self,i):return OBJECT+(i-1)*0x800 if i else 0
 def oid(self,p):
  if not p:return 0
  i=(p-OBJECT)//0x800+1;assert 1<=i<=4 and p==self.op(i);return i
 def hp(self,i):return HOUSE+(i-1)*0x16000 if i else 0
 def hid(self,p):
  if not p:return 0
  i=(p-HOUSE)//0x16000+1;assert 1<=i<=5 and p==self.hp(i);return i
 def tp(self,i):return TYPE+(i-1)*0x200
 def tid(self,p):
  i=(p-TYPE)//0x200+1;assert 1<=i<=4 and p==self.tp(i);return i
 def event(self,service,a=0,b=0):self.trace.extend(map(str,('E',service,a,b,self.word(self.hp(self.f['current'])+0x5674),self.word(self.hp(self.f['current'])+0x120))))
 def ret(self,n,value=0):
  u=self.u;sp=u.reg_read(UC_X86_REG_ESP);u.reg_write(UC_X86_REG_EAX,value&0xffffffff);u.reg_write(UC_X86_REG_ESP,sp+4+n);u.reg_write(UC_X86_REG_EIP,self.word(sp))
 def mutate(self,service,id):
  m=self.f['mutation'];wanted=[0,1,2,44,56,16,44,60,10,848,240,5,6,3,0x781f20,60]
  if self.changed or not m or service!=wanted[m] or (m==6 and self.phase!=1):return
  self.changed=True;s=self.hp(self.f['current']);o=self.hp(self.f['target']);a=self.op(id);put=self.change
  if m==1:put(o+0x30,-33);put(0xa3d298,4);put(0xa40774,0);put(0x832474,ALT);put(0x832480,8);put(0xabff58,ALTERNATE);put(0xabff5c,32);put(0xabff64,0,1)
  if m==2:
   put(s+0x5504,3);p=self.word(s+0x54f8)
   for i,(h,v) in enumerate(((self.f['target'],-2**31),(self.f['target'],7),(5,99))):put(p+8*i,self.hp(h));put(p+8*i+4,v)
  if m==3:put(a+8,0);put(a+0x76,255,1);put(0x832474,ALT);put(0x832480,8)
  if m==4:put(s+0x30,self.word(a+0x18)+1);put(a+0x228,self.op(4))
  if m==5:put(SCRATCH+4,0,1)
  if m==6:put(0xabff5c,0);put(0xabff64,1,1);put(0xabff68,0);put(0xb2b628,self.op(4))
  if m==7:
   owner=self.word(a+0x1b4)
   if owner:put(owner+0x30,-1)
   put(s+0x5674,0)
  if m==8:put(a+0x228,self.op(4))
  if m==9:put(a+0x25c,self.op(4))
  if m==10:
   for i in range(1,5):put(self.op(i)+0x25c,self.op(3))
  if m==11:put(0xa3d298,0);put(s+0x134,0,1);put(s+0x135,0,1);put(o+0x135,255,1);self.u.mem_write(RULES+0x1128,struct.pack('<d',.6));put(self.word(s+0x34)+0xc0,-7)
  if m==12:put(0xa35db4,o);put(0xa3d548,255);put(o+0x5674,0)
  if m==13:put(s+0x134,0,1);put(s+0x135,0,1);put(0x832480,-1);put(0x832474,ALT);put(self.word(o+0x34)+0x1a6,255,1)
  if m==14:put(o+0x34,self.tp(4));put(0xa3d298,4);put(0xa40774,1);put(s+0x30,-1)
  if m==15:put(self.sourceActor+0x228,0)
 def store(self,u,access,p,n,value,_):
  if not self.active:return
  for i in range(1,5):
   offset=p-self.op(i)
   if offset in (0x404,0x228,0x310,0x25c):self.event(offset,i,self.oid(value) if offset in (0x228,0x25c) else value);return
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  sp=u.reg_read(UC_X86_REG_ESP);ecx=u.reg_read(UC_X86_REG_ECX)
  if a==KIND:
   i=self.oid(ecx);result=signed(self.word(ecx+8));self.event(44,i,result);self.mutate(44,i);self.ret(0,result);return
  if a==ID:
   receiver=self.word(sp+4);i=self.oid(receiver-4);assert ecx==SVT and self.word(receiver)==SVT;result=signed(self.word(self.op(i)+12));self.event(16,i,result);self.phase=1;self.mutate(16,i);self.ret(4,result);return
  if a in (COUNTRY,OWNER,WEAPON,PERMISSION,RELEASE):
   i=self.oid(ecx)
   if a==COUNTRY:self.sourceActor=ecx;service=56;result=signed(self.word(ecx+0x18));self.event(service,i,result);pops=0
   if a==OWNER:service=60;result=self.word(ecx+0x1b4);self.event(service,i,self.hid(result));pops=0
   if a==WEAPON:service=696;assert self.word(sp+4)==0;result=signed(self.word(ecx+0x28));self.event(service,i,result);pops=4
   if a==PERMISSION:service=848;assert self.word(sp+4)==0 and self.word(sp+8)==self.word(ecx+0x28);result=signed(self.word(ecx+0x2c));self.event(service,i,result);pops=8
   if a==RELEASE:service=240;result=0;self.event(service,i);pops=0
   self.mutate(service,i);self.ret(pops,result);return
  services={0x49e000:(1,8),0x49de00:(9,8),0x4f3420:(2,0),0x4ec5e0:(3,0),0x6f9ec0:(4,8),0x783764:(5,0),0x5b4da0:(6,28),0x715b40:(7,4),0x4e09a0:(8,4),0x68a490:(10,4),0x781f20:(0x781f20,0)}
  if a in services:
   service,pops=services[a];result=0;id=0
   if service in (1,9):assert ecx==0x8324e0 and self.word(sp+4)==0 and self.word(sp+8)==0;self.event(service)
   if service==2:self.event(service,self.hid(ecx))
   if service in (3,):self.event(service)
   if service==4:assert ecx==0x7da328 and u.reg_read(UC_X86_REG_EDX)==0 and self.word(sp+4)==0x7da270 and self.word(sp+8)==0xc4d;self.event(service);result=LOCALIZED
   if service==5:
    dest=self.word(sp+4);assert self.word(sp+8)==LOCALIZED;left=self.hid(self.word(sp+12)-0x15f16);right=self.hid(self.word(sp+16)-0x15f16);self.formatted=dest;self.event(service,left,right)
   if service==6:
    args=struct.unpack('<7I',u.mem_read(sp+4,28));assert ecx==0xa3dc70 and args[0:2]==(0,0) and args[2]==self.formatted and args[4]==0x4046 and args[6]==0;self.event(service,signed(args[3]),args[5])
   if service==7:assert u.reg_read(UC_X86_REG_EDX)==0xffffffff and self.word(sp+4)==0xffffffff;self.event(service,ecx)
   if service==8:assert ecx==0x8324e0 and self.word(sp+4)==0;self.event(service)
   if service==10:assert ecx==self.op(1) and self.word(sp+4)==0;id=self.clearing;self.event(service,id)
   if service==0x781f20:
    id=self.tid(self.word(sp+4)-0x24);assert self.word(sp+8)==0x7ceb30;result=self.f['types'][id-1][3];self.event(service,id,result)
   self.mutate(service,id);self.ret(pops,result);return
  assert any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected MakeAlly instruction',hex(a))
  if a in RANGES:self.counts[hex(a)]+=1
  if a==0x6c9af0:self.clearing=self.oid(ecx);assert self.word(sp+4)==0
  if a==0x6b54a0:assert ecx==SCRATCH
  if a==0x41ba10:
   b,i=self.cache(self.word(sp+4));c,j=self.cache(self.word(sp+8));assert b==c;self.event(a,b*32+i,j)
 def run(self,f):
  self.f=f;u=self.u;u.mem_write(ARENA,b'\xa5'*SIZE);u.mem_write(EXTRA,b'\xa5'*ESIZE);put=self.change
  for offset,address in ((0x2c,KIND),(0x38,COUNTRY),(0x3c,OWNER),(0x370,0x6c9af0),(0x354,0x6c5070),(0x2b8,WEAPON),(0x350,PERMISSION),(0xf0,RELEASE)):put(VT+offset,address)
  put(SVT+0x10,ID)
  for i,t in enumerate(f['types'],1):
   p=self.tp(i);put(p+0xb8,t[0]);put(p+0xbc,t[1]);put(p+0x1a6,t[2],1);put(p+0xc0,t[4]);u.mem_write(p+0x24,('Type'+str(i)).encode()+b'\0')
  for i,h in enumerate(f['houses'],1):
   p=self.hp(i)
   for offset,v,n in ((0x30,h[0],4),(0x34,self.tp(h[1]),4),(0x13d,h[2],1),(0x5674,h[3],4),(0x120,h[4],4),(0x134,h[5],1),(0x135,h[6],1),(0x54f0,h[7],4),(0x5504,h[8],4),(0x54f8,SCORES+(i-1)*32,4)):put(p+offset,v,n)
  for i,(h,v) in enumerate(f['scores']):put(SCORES+8*i,self.hp(h));put(SCORES+8*i+4,v)
  for i,row in enumerate(f['actors'],1):
   p=self.op(i);k,uid,x,y,flag,country,owner,target,clear,timer,service,attached,index,permission=row
   for off,v,n in ((0,VT,4),(4,SVT,4),(8,k,4),(12,uid,4),(0x24,x,2),(0x26,y,2),(0x76,flag,1),(0x18,country,4),(0x1b4,self.hp(owner),4),(0x228,self.op(target),4),(0x404,clear,1),(0x310,timer,4),(0x238,self.op(1) if service else 0,4),(0x25c,self.op(attached),4),(0x28,index,4),(0x2c,permission,4)):put(p+off,v,n)
  for i,(k,o) in enumerate(f['registry']):p=(PRIMARY if i<32 else ALTERNATE)+(i%32)*8;put(p,k);put(p+4,self.op(o))
  for i,v in enumerate(f['houseSlots'][0]):put(HS+4*i,self.hp(v))
  for i,v in enumerate(f['typeSlots'][0]):put(TS+4*i,self.tp(v))
  for b,row in zip((AS,ALT),f['actorSlots']):
   for i,v in enumerate(row):put(b+4*i,self.op(v))
  n,s,b,c,j,o=f['registryConfig'][0];values=((PRIMARY,ALTERNATE)[b-1],n,s,(0,PRIMARY,ALTERNATE)[c]+8*j if c else 0,self.op(o),f['mode'],f['unrestricted'],f['houseCount'],HS,f['typeCount'],TS,f['actorCount'],(AS,ALT)[f['actorBacking']-1],self.hp(f['currentHouse']),f['quiet'],RULES)
  for (p,width),v in zip(GLOBALS,values):put(p,v,width)
  put(RULES+0x1424,f['rule'],1);u.mem_write(RULES+0x1128,struct.pack('<Q',f['delayBits']));token=f['scratch'][0];put(SCRATCH,token[0]);u.mem_write(SCRATCH+4,bytes(token[1:]));before=[bytes(u.mem_read(ARENA,SIZE)),bytes(u.mem_read(EXTRA,ESIZE))]
  self.trace=[];self.changed=False;self.phase=0;self.active=True
  writes=[*GLOBALS,(PRIMARY,256),(ALTERNATE,256),(SCORES,160)]+[(self.hp(i)+off,n) for i in range(1,6) for off,n in ((0x5674,4),(0x120,4),(0x54f0,4))]+[(self.op(i)+off,n) for i in range(1,5) for off,n in ((0x404,1),(0x228,4),(0x310,4),(0x25c,4))]
  try:self.checked_call(0x4e5660,[self.hp(f['target']),f['announce']],self.hp(f['current']),writes=writes,inputs=[*RANGES.items(),*TABLES.items()])
  finally:self.active=False
  # All padding/unlisted bytes remain original. Supplied callbacks have their
  # own explicit mutable fields; original CPU writes are guarded more narrowly.
  mutable=[(PRIMARY,256),(ALTERNATE,256),(SCORES,160),(RULES+0x1128,8)]
  mutable += [(self.hp(i)+off,n) for i in range(1,6) for off,n in ((0x30,4),(0x34,4),(0x5674,4),(0x120,4),(0x134,2),(0x54f0,4),(0x5504,4))]
  mutable += [(self.tp(i)+off,n) for i in range(1,5) for off,n in ((0x1a6,1),(0xc0,4))]
  mutable += [(self.op(i)+off,n) for i in range(1,5) for off,n in ((8,4),(0x76,1),(0x228,4),(0x310,4),(0x404,1),(0x25c,4))]
  for base,size,old in ((ARENA,SIZE,before[0]),(EXTRA,ESIZE,before[1])):
   after=bytearray(u.mem_read(base,size))
   for p,n in mutable:
    if base<=p and p+n<=base+size:after[p-base:p-base+n]=old[p-base:p-base+n]
   assert after==old
  cb,ci=self.cache();header=[signed(self.word(0xa3d298)),signed(self.word(0xa40774)),signed(self.word(0x832480)),1 if self.word(0x832474)==AS else 2,self.hid(self.word(0xa35db4)),signed(self.word(0xa3d548)),self.byte(RULES+0x1424),struct.unpack('<Q',u.mem_read(RULES+0x1128,8))[0],int(self.changed),self.phase,signed(self.word(0xabff5c)),self.byte(0xabff64),1 if self.word(0xabff58)==PRIMARY else 2,cb,ci,self.oid(self.word(0xb2b628))]
  self.trace.extend(map(str,('R',0,'F',*header,signed(self.word(SCRATCH)),*u.mem_read(SCRATCH+4,4))))
  for i in range(1,6):p=self.hp(i);self.trace.extend(map(str,(signed(self.word(p+0x30)),self.tid(self.word(p+0x34)),self.byte(p+0x13d),self.word(p+0x5674),self.word(p+0x120),self.byte(p+0x134),self.byte(p+0x135),signed(self.word(p+0x54f0)),signed(self.word(p+0x5504)))))
  for i,t in enumerate(f['types'],1):p=self.tp(i);self.trace.extend(map(str,(signed(self.word(p+0xb8)),signed(self.word(p+0xbc)),self.byte(p+0x1a6),t[3],signed(self.word(p+0xc0)))))
  for i in range(20):p=SCORES+8*i;self.trace.extend(map(str,(self.hid(self.word(p)),signed(self.word(p+4)))))
  for i in range(1,5):
   p=self.op(i);self.trace.extend(map(str,(signed(self.word(p+8)),signed(self.word(p+12)),*struct.unpack('<hh',u.mem_read(p+0x24,4)),self.byte(p+0x76),signed(self.word(p+0x18)),self.hid(self.word(p+0x1b4)),self.oid(self.word(p+0x228)),self.byte(p+0x404),signed(self.word(p+0x310)),int(bool(self.word(p+0x238))),self.oid(self.word(p+0x25c)),signed(self.word(p+0x28)),signed(self.word(p+0x2c)))))
  for base in (PRIMARY,ALTERNATE):
   for i in range(32):self.trace.extend(map(str,(signed(self.word(base+8*i)),self.oid(self.word(base+8*i+4)))))
  return self.trace
