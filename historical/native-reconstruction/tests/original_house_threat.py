# SPDX-License-Identifier: GPL-3.0-or-later
"""Unmodified complete House threat roots with named supplied virtual leaves."""
import struct
from collections import Counter
from original_presentation import PresentationOracle,STOP,STACK
from verify_house_threat import verify,RANGES,TABLES
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EIP
ARENA=0x3000000;SIZE=0x80000;HOUSE=ARENA+0x1000;ACTOR=ARENA+0x62000;SCORES=ARENA+0x66000;SLOTS=ARENA+0x67000;ALT=ARENA+0x67100;VIRTUAL=ARENA+0x68000;VTABLE=ARENA+0x69000;POINT=ARENA+0x6a000
GLOBALS=(0xa3d298,0xa40c30,0xa40c24,0xa40f10)
def signed(v):return v if v<2**31 else v-2**32
class HouseThreatOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(ARENA,SIZE);self.active=False;self.counts=Counter();self.u.hook_add(UC_HOOK_CODE,self.code)
 def va(self,a):return a
 def word(self,p):return struct.unpack('<I',self.u.mem_read(p,4))[0]
 def short(self,p):return struct.unpack('<h',self.u.mem_read(p,2))[0]
 def hp(self,i):return HOUSE+(i-1)*0x18000 if i else 0
 def ap(self,i):return ACTOR+(i-1)*0x1000
 def hid(self,p):
  if not p:return 0
  i=(p-HOUSE)//0x18000+1;assert 1<=i<=4 and p==self.hp(i);return i
 def aid(self,p):
  i=(p-ACTOR)//0x1000+1;assert 1<=i<=3 and p==self.ap(i);return i
 def change(self,p,v,n=4):
  data=int(v&((1<<(n*8))-1)).to_bytes(n,'little');self.u.mem_write(p,data)
  if self.active:
   if ARENA<=p and p+n<=ARENA+SIZE:self.expected[p-ARENA:p-ARENA+n]=data
   else:
    lo=next(a for a in GLOBALS if a<=p and p+n<=a+4);b=bytearray(self.expectedGlobals[lo]);b[p-lo:p-lo+n]=data;self.expectedGlobals[lo]=bytes(b)
 def mutate(self,i,service):
  if self.changed:return
  mode=self.f['mutation'];entered=service==672 if mode in (1,4,6) else service==44 if mode in (2,5) else service==420 if mode==3 else False
  if not entered:return
  self.changed=True;a=self.ap(i);h=self.hp(self.f['current'])
  if mode==1:self.change(a+0x76,1,1);self.change(a+0x7d,0,1);self.change(a+0x1b4,h)
  if mode==2:self.change(0xa40c24,ALT);self.change(0xa40c30,0);self.change(0xa3d298,1);self.change(h+0x134,0,1);self.change(h+0x135,255,1);self.change(h+0x5674,self.word(h+0x5674)^0xffffffff)
  if mode==3:self.change(0xa3d298,1);self.change(h+0x134,255,1);self.change(h+0x5674,0xffffffff);self.change(a+0x1b4,h);self.change(a+0x454,self.short(0xa40f10),2);self.change(a+0x456,self.short(0xa40f12),2)
  if mode==4:
   x=self.short(a+0x454);y=self.short(a+0x456)
   # Diagnostic callback computes only its explicit stores, never root results.
   div=lambda v:abs(v)//4*(-1 if v<0 else 1);cell=div(x)+130*div(y)+0x83
   for k,offset in enumerate(self.f['tables'][:9]):
    slot=cell+offset;assert 0<=slot<0x4204;self.change(h+0x56d0+4*slot,0x7fffffff if k%2 else -1)
  if mode==5:self.change(0xa40f10,self.short(a+0x454),2);self.change(0xa40f12,self.short(a+0x456),2)
  if mode==6:self.change(a+0x900,7)
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  if a in (VIRTUAL,VIRTUAL+16,VIRTUAL+32):
   i=self.aid(u.reg_read(UC_X86_REG_ECX));p=self.ap(i);service={VIRTUAL:672,VIRTUAL+16:44,VIRTUAL+32:420}[a]
   if service==672:result=signed(self.word(p+0x900))
   elif service==44:result=self.f['actors'][i-1][3+min(self.kindCalls[i-1],2)];self.kindCalls[i-1]+=1
   else:result=i
   self.trace.extend(map(str,('V',i,service,result)));self.counts['supplied_'+str(service)]+=1;self.mutate(i,service)
   sp=u.reg_read(UC_X86_REG_ESP);u.reg_write(UC_X86_REG_EAX,(p+0xa00 if service==420 else result)&0xffffffff);u.reg_write(UC_X86_REG_ESP,sp+4);u.reg_write(UC_X86_REG_EIP,self.word(sp));return
  assert any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected House threat instruction',hex(a))
  if a in RANGES:self.counts[hex(a)]+=1
 def run(self,f):
  self.f=f;u=self.u;u.mem_write(ARENA,b'\xa5'*SIZE);current=self.hp(f['current'])
  for i,h in enumerate(f['houses'],1):
   p=self.hp(i)
   for offset,value in [(0x30,h[0]),(0x5674,h[4]),(0x54f0,h[5]),(0x5504,f['count']),(0x54f8,SCORES)]:self.put(p+offset,value)
   for offset,value in [(0x13d,h[1]),(0x134,h[2]),(0x135,h[3])]:u.mem_write(p+offset,bytes([value]))
   u.mem_write(p+0x56d0,struct.pack('<I',0x77777777)*(0x4205))
  for i,(house,score) in enumerate(f['scores']):self.put(SCORES+8*i,self.hp(house));self.put(SCORES+8*i+4,score)
  for i,a in enumerate(f['actors'],1):
   p=self.ap(i);self.put(p,VTABLE);u.mem_write(p+0x76,bytes([a[0]]));u.mem_write(p+0x7d,bytes([a[1]]));self.put(p+0x900,a[2]);self.put(p+0x1b4,self.hp(a[6]));u.mem_write(p+0x454,struct.pack('<hh',a[7],a[8]));u.mem_write(p+0xa24,struct.pack('<hh',a[9],a[10]))
  for offset,ptr in [(0x2a0,VIRTUAL),(0x2c,VIRTUAL+16),(0x1a4,VIRTUAL+32)]:self.put(VTABLE+offset,ptr)
  for i,v in enumerate(f['slots']):self.put(SLOTS+4*i,self.ap(v));self.put(ALT+4*i,self.ap(3-i%3))
  for p,v in zip(GLOBALS,(f['mode'],f['registryCount'],SLOTS,(f['ix']&65535)|((f['iy']&65535)<<16))):self.put(p,v)
  u.mem_write(POINT,struct.pack('<hh',f['px'],f['py']));self.expected=bytearray(u.mem_read(ARENA,SIZE));self.expectedGlobals={p:bytes(u.mem_read(p,4)) for p in GLOBALS};self.trace=[];self.changed=False;self.kindCalls=[0]*3;self.active=True
  root=f['root'];effects=[(current+0x56d0,0x4204*4)] if root==0 else [(SCORES+8*i+4,4) for i in range(max(0,f['count']))]+[(current+0x54f0,4)] if root==1 else []
  address=(0x4f3420,0x4eeba0,0x54e370)[root];args=[] if root==0 else [f['delta'],self.hp(f['target'])] if root==1 else [POINT]
  try:self.checked_call(address,args,current,writes=effects,inputs=[*RANGES.items(),*TABLES.items()])
  finally:self.active=False
  observed=bytearray(u.mem_read(ARENA,SIZE))
  for p,n in effects:observed[p-ARENA:p-ARENA+n]=self.expected[p-ARENA:p-ARENA+n]
  assert observed==self.expected
  assert all(bytes(u.mem_read(p,4))==v for p,v in self.expectedGlobals.items())
  result=signed(u.reg_read(UC_X86_REG_EAX)) if root==2 else 0
  self.trace.extend(map(str,('R',result,'S',signed(self.word(current+0x5504)),signed(self.word(0xa40c30)),signed(self.word(0xa3d298)),self.short(0xa40f10),self.short(0xa40f12),int(self.word(0xa40c24)==ALT))))
  for i in range(1,5):
   p=self.hp(i);self.trace.extend(map(str,(signed(self.word(p+0x30)),u.mem_read(p+0x13d,1)[0],u.mem_read(p+0x134,1)[0],u.mem_read(p+0x135,1)[0],self.word(p+0x5674),signed(self.word(p+0x54f0)))))
  for i in range(8):self.trace.extend(map(str,(self.hid(self.word(SCORES+8*i)),signed(self.word(SCORES+8*i+4)))))
  for i in range(1,4):
   p=self.ap(i);a=f['actors'][i-1];self.trace.extend(map(str,(u.mem_read(p+0x76,1)[0],u.mem_read(p+0x7d,1)[0],signed(self.word(p+0x900)),*a[3:6],self.hid(self.word(p+0x1b4)),self.short(p+0x454),self.short(p+0x456),self.short(p+0xa24),self.short(p+0xa26))))
  grid=struct.unpack('<'+str(0x4204)+'i',u.mem_read(current+0x56d0,0x4204*4));base=0 if root==0 else 0x77777777;changes=[(i,v) for i,v in enumerate(grid) if v!=base];self.trace.extend(map(str,('G',base,len(changes))))
  for i,v in changes:self.trace.extend(map(str,(i,v)))
  return self.trace
