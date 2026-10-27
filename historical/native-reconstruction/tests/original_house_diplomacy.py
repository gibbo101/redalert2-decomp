# SPDX-License-Identifier: GPL-3.0-or-later
"""Actual composed notification and diplomacy on one original private arena."""
import struct
from original_house_make_ally import *
from original_house_make_ally import HouseMakeAllyOracle as AllyOracle,GLOBALS as AG
from verify_house_diplomacy import verify,RANGES,TABLES
from unicorn.x86_const import UC_X86_REG_ESI
GLOBALS=AG+((0xa3d29c,4),)
SESSION=EXTRA+0x7b000;SESSION_VT=EXTRA+0x7b100;SESSION_SERVICE=EXTRA+0x7b200;HOUSE_ALT=EXTRA+0x7b300
class HouseDiplomacyOracle(AllyOracle):
 def __init__(self,exe):
  super().__init__(exe);self.inspection=verify(exe.read_bytes())
 def mutate(self,service,id):
  before=self.changed;super().mutate(service,id)
  if not before and self.changed and self.f['mutation'] in (1,2):
   self.change(0xa322a8,8 if self.f['mutation']==1 else 3);self.change(0xa3229c,HOUSE_ALT)
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  if a==SESSION_SERVICE:
   assert u.reg_read(UC_X86_REG_ECX)==SESSION
   self.counts['session4']+=1;self.event(17,0,self.f['sessionResult']);self.ret(0,self.f['sessionResult']);return
  if a in (0x4ec5e0,0x4e5660,0x4e5a70):
   kind={0x4ec5e0:'N',0x4e5660:'A',0x4e5a70:'E'}[a];sp=u.reg_read(UC_X86_REG_ESP)
   self.trace.extend(map(str,('J',kind,0 if kind=='N' else self.hid(u.reg_read(UC_X86_REG_ECX)),0 if kind=='N' else self.hid(self.word(sp+4)))))
  if 0x4ec5e0<=a<=0x4ec6db:
   if a==0x4ec5e0:self.counts[hex(a)]+=1
   if a==0x4ec661:self.event(0x191,self.hid(u.reg_read(UC_X86_REG_ESI)),1)
   assert a+n<=0x4ec6dc;return
  if 0x4e5a70<=a<=0x4e5ce9:
   if a==0x4e5a70:self.counts[hex(a)]+=1
   if a==0x4e5cd4:self.counts['enemy_tail']+=1
   assert a+n<=0x4e5cea;return
  if a==0x6f9ec0 and u.reg_read(UC_X86_REG_ECX)==0x7da34c:
   sp=u.reg_read(UC_X86_REG_ESP);assert u.reg_read(UC_X86_REG_EDX)==0 and self.word(sp+4)==0x7da270 and self.word(sp+8)==0xcc8
   self.event(4);self.mutate(4,0);self.ret(8,LOCALIZED);return
  if a==0x6b54a0:
   # Each actual MakeAlly invocation owns its own caller scratch frame.
   self.counts[hex(a)]+=1;return
  super().code(u,a,n,_)
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
  for i,v in enumerate((5,4,3,2,1,5,4,3)):put(HOUSE_ALT+4*i,self.hp(v))
  for i,v in enumerate(f['typeSlots'][0]):put(TS+4*i,self.tp(v))
  for b,row in zip((AS,ALT),f['actorSlots']):
   for i,v in enumerate(row):put(b+4*i,self.op(v))
  n,s,b,c,j,o=f['registryConfig'][0];values=((PRIMARY,ALTERNATE)[b-1],n,s,(0,PRIMARY,ALTERNATE)[c]+8*j if c else 0,self.op(o),f['mode'],f['unrestricted'],f['houseCount'],HS,f['typeCount'],TS,f['actorCount'],(AS,ALT)[f['actorBacking']-1],self.hp(f['currentHouse']),f['quiet'],RULES)
  for (p,width),v in zip(GLOBALS,values):put(p,v,width)
  put(RULES+0x111d,f['notifyRule'],1);put(0xa3d29c,SESSION if f['sessionPresent'] else 0);put(SESSION,SESSION_VT);put(SESSION_VT+4,SESSION_SERVICE);
  for i in range(1,6):put(self.hp(i)+0x191,53,1)
  put(RULES+0x1424,f['rule'],1);u.mem_write(RULES+0x1128,struct.pack('<Q',f['delayBits']));token=f['scratch'][0];put(SCRATCH,token[0]);u.mem_write(SCRATCH+4,bytes(token[1:]));before=[bytes(u.mem_read(ARENA,SIZE)),bytes(u.mem_read(EXTRA,ESIZE))]
  self.trace=[];self.changed=False;self.phase=0;self.active=True
  writes=[*GLOBALS,(PRIMARY,256),(ALTERNATE,256),(SCORES,160)]+[(self.hp(i)+off,n) for i in range(1,6) for off,n in ((0x5674,4),(0x120,4),(0x54f0,4))]+[(self.op(i)+off,n) for i in range(1,5) for off,n in ((0x404,1),(0x228,4),(0x310,4),(0x25c,4))]
  writes += [(self.hp(i)+0x191,1) for i in range(1,6)]
  try:self.checked_call((0x4ec5e0,0x4e5660,0x4e5a70)[f['root']],[] if f['root']==0 else [self.hp(f['target']),f['announce']],0 if f['root']==0 else self.hp(f['current']),writes=writes,inputs=[*RANGES.items(),*TABLES.items()])
  finally:self.active=False
  # All padding/unlisted bytes remain original. Supplied callbacks have their
  # own explicit mutable fields; original CPU writes are guarded more narrowly.
  mutable=[(self.hp(i)+0x191,1) for i in range(1,6)]+[(PRIMARY,256),(ALTERNATE,256),(SCORES,160),(RULES+0x1128,8)]
  mutable += [(self.hp(i)+off,n) for i in range(1,6) for off,n in ((0x30,4),(0x34,4),(0x5674,4),(0x120,4),(0x134,2),(0x54f0,4),(0x5504,4))]
  mutable += [(self.tp(i)+off,n) for i in range(1,5) for off,n in ((0x1a6,1),(0xc0,4))]
  mutable += [(self.op(i)+off,n) for i in range(1,5) for off,n in ((8,4),(0x76,1),(0x228,4),(0x310,4),(0x404,1),(0x25c,4))]
  for base,size,old in ((ARENA,SIZE,before[0]),(EXTRA,ESIZE,before[1])):
   after=bytearray(u.mem_read(base,size))
   for p,n in mutable:
    if base<=p and p+n<=base+size:after[p-base:p-base+n]=old[p-base:p-base+n]
   assert after==old
  cb,ci=self.cache();header=[signed(self.word(0xa3d298)),signed(self.word(0xa40774)),signed(self.word(0x832480)),1 if self.word(0x832474)==AS else 2,self.hid(self.word(0xa35db4)),signed(self.word(0xa3d548)),self.byte(RULES+0x1424),struct.unpack('<Q',u.mem_read(RULES+0x1128,8))[0],int(self.changed),self.phase,signed(self.word(0xabff5c)),self.byte(0xabff64),1 if self.word(0xabff58)==PRIMARY else 2,cb,ci,self.oid(self.word(0xb2b628))]
  self.trace.extend(map(str,('R',0,'F',*header,*( [signed(self.word(SCRATCH)),*u.mem_read(SCRATCH+4,4)] if f['root']==1 else f['scratch'][0] ))))
  for i in range(1,6):p=self.hp(i);self.trace.extend(map(str,(signed(self.word(p+0x30)),self.tid(self.word(p+0x34)),self.byte(p+0x13d),self.word(p+0x5674),self.word(p+0x120),self.byte(p+0x134),self.byte(p+0x135),signed(self.word(p+0x54f0)),signed(self.word(p+0x5504)))))
  for i,t in enumerate(f['types'],1):p=self.tp(i);self.trace.extend(map(str,(signed(self.word(p+0xb8)),signed(self.word(p+0xbc)),self.byte(p+0x1a6),t[3],signed(self.word(p+0xc0)))))
  for i in range(20):p=SCORES+8*i;self.trace.extend(map(str,(self.hid(self.word(p)),signed(self.word(p+4)))))
  for i in range(1,5):
   p=self.op(i);self.trace.extend(map(str,(signed(self.word(p+8)),signed(self.word(p+12)),*struct.unpack('<hh',u.mem_read(p+0x24,4)),self.byte(p+0x76),signed(self.word(p+0x18)),self.hid(self.word(p+0x1b4)),self.oid(self.word(p+0x228)),self.byte(p+0x404),signed(self.word(p+0x310)),int(bool(self.word(p+0x238))),self.oid(self.word(p+0x25c)),signed(self.word(p+0x28)),signed(self.word(p+0x2c)))))
  for base in (PRIMARY,ALTERNATE):
   for i in range(32):self.trace.extend(map(str,(signed(self.word(base+8*i)),self.oid(self.word(base+8*i+4)))))
  self.trace.extend(map(str,('D',self.byte(RULES+0x111d),int(bool(self.word(0xa3d29c))),f['sessionResult'],*[self.byte(self.hp(i)+0x191) for i in range(1,6)],signed(self.word(0xa322a8)),int(self.word(0xa3229c)==HOUSE_ALT))))
  return self.trace
