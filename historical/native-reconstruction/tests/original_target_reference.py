# SPDX-License-Identifier: GPL-3.0-or-later
"""Unmodified target roots including actual compiled sort and comparator."""
import struct
from collections import Counter
from original_presentation import PresentationOracle,STOP
from verify_target_reference import verify,RANGES,TABLES
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EIP
ARENA=0x3000000;SIZE=0x10000;OBJECT=ARENA+0x1000;TOKEN=ARENA+0x2000;PRIMARY=ARENA+0x3000;ALTERNATE=ARENA+0x4000;DETACHED=ARENA+0x5000;VT=ARENA+0x6000;SVT=ARENA+0x6100;KIND=ARENA+0x7000;ID=ARENA+0x7010
GLOBALS=((0xabff58,4),(0xabff5c,4),(0xabff64,1),(0xabff68,4),(0xb2b628,4))
def signed(v):return v if v<2**31 else v-2**32
class TargetReferenceOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(ARENA,SIZE);self.active=False;self.counts=Counter();self.u.hook_add(UC_HOOK_CODE,self.code)
 def va(self,a):return a
 def word(self,p):return struct.unpack('<I',self.u.mem_read(p,4))[0]
 def byte(self,p):return self.u.mem_read(p,1)[0]
 def change(self,p,v,n=4):self.u.mem_write(p,(v&((1<<(n*8))-1)).to_bytes(n,'little'))
 def op(self,i):return OBJECT+(i-1)*0x100 if i else 0
 def oid(self,p):
  if not p:return 0
  i=(p-OBJECT)//0x100+1;assert 1<=i<=4 and p==self.op(i);return i
 def cache(self,p=None):
  if p is None:p=self.word(0xabff68)
  if not p:return 0,0
  if p==DETACHED:return 3,0
  for b,base in ((1,PRIMARY),(2,ALTERNATE)):
   if base<=p<base+256 and (p-base)%8==0:return b,(p-base)//8
  raise AssertionError(('Foreign registry entry',hex(p)))
 def mutate(self,id,i):
  m=self.f['mutation']
  if self.changed or not m or ((m in (2,5,7))!=id):return
  self.changed=True;p=self.op(i);t=TOKEN+self.f['token']*8
  if m==1:self.change(p+8,11);self.change(p+0x24,-32768,2);self.change(p+0x26,32767,2);self.change(t,-99);self.change(t+4,255,1)
  if m==2:self.change(t+4,11,1);self.change(t,-7)
  if m==3:self.change(0xabff5c,0);self.change(0xabff64,255,1);self.change(0xb2b628,self.op(4))
  if m==4:self.change(0xabff58,ALTERNATE);self.change(0xabff5c,32);self.change(0xabff64,0,1);self.change(0xb2b628,self.op(2))
  if m==5:self.change(0xabff58,ALTERNATE);self.change(0xabff5c,8);self.change(0xabff64,0,1);self.change(0xb2b628,self.op(3));self.change(0xabff68,ALTERNATE)
  if m==6:self.change(0xabff68,DETACHED);self.change(0xabff64,0,1);self.change(0xabff5c,1);self.change(t,self.word(DETACHED));self.change(t+4,52,1)
  if m==7:self.change(p+12,-2147483647);self.u.mem_write(t+5,bytes([255,0,127]));self.change(PRIMARY,-7);self.change(PRIMARY+4,self.op(4));self.change(ALTERNATE,-7);self.change(ALTERNATE+4,self.op(2))
  if m==8:self.change(0xabff5c,-1);self.change(0xabff64,1,1);self.change(0xb2b628,0);self.change(0xabff68,0)
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  if a in (KIND,ID):
   sp=u.reg_read(UC_X86_REG_ESP)
   if a==KIND:
    i=self.oid(u.reg_read(UC_X86_REG_ECX));result=signed(self.word(self.op(i)+8));b,j=self.cache();self.trace.extend(map(str,('K',i,result,b,j,self.byte(0xabff64),signed(self.word(0xabff5c)))));self.counts['supplied_kind']+=1
   else:
    receiver=self.word(sp+4);i=self.oid(receiver-4);assert self.word(receiver)==SVT and u.reg_read(UC_X86_REG_ECX)==SVT;result=signed(self.word(self.op(i)+12));self.trace.extend(map(str,('I',i,self.byte(TOKEN+self.f['token']*8+4),result)));self.counts['supplied_secondary_ID']+=1
   self.mutate(a==ID,i);u.reg_write(UC_X86_REG_EAX,result&0xffffffff);u.reg_write(UC_X86_REG_ESP,sp+(8 if a==ID else 4));u.reg_write(UC_X86_REG_EIP,self.word(sp));return
  assert any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected target instruction',hex(a))
  if a in RANGES:self.counts[hex(a)]+=1
  if a==0x41ba10:
   sp=u.reg_read(UC_X86_REG_ESP);left=self.word(sp+4);right=self.word(sp+8);b,i=self.cache(left);c,j=self.cache(right);assert b==c and b in (1,2);self.trace.extend(map(str,('C',b,i,j,signed(self.word(left)),signed(self.word(right)))))
 def run(self,f):
  self.f=f;u=self.u;u.mem_write(ARENA,b'\xa5'*SIZE)
  self.put(VT+0x2c,KIND);self.put(SVT+0x10,ID)
  for i,row in enumerate(f['objects'],1):
   p=self.op(i);self.put(p,VT);self.put(p+4,SVT);self.put(p+8,row[0]);self.put(p+12,row[1]);self.change(p+0x24,row[2],2);self.change(p+0x26,row[3],2)
  for i,t in enumerate(f['tokens']):self.put(TOKEN+8*i,t[0]);u.mem_write(TOKEN+8*i+4,bytes(t[1:]))
  for base,name in ((PRIMARY,'primary'),(ALTERNATE,'alternate'),(DETACHED,'detached')):
   for i,(key,obj) in enumerate(f[name]):self.put(base+8*i,key);self.put(base+8*i+4,self.op(obj))
  cached=(0,PRIMARY,ALTERNATE,DETACHED)[f['cacheBacking']]+(8*f['cacheIndex'] if f['cacheBacking'] in (1,2) else 0)
  for (p,n),v in zip(GLOBALS,((PRIMARY,ALTERNATE)[f['backing']-1],f['count'],f['sorted'],cached,self.op(f['fallback']))):self.change(p,v,n)
  writes=[*GLOBALS,(PRIMARY,256),(ALTERNATE,256),(TOKEN,16)]
  before=bytes(u.mem_read(ARENA,SIZE));self.trace=[];self.changed=False;self.active=True
  def call(a,args,ecx):
   self.checked_call(a,args,ecx,writes=writes,inputs=[*RANGES.items(),*TABLES.items()]);return u.reg_read(UC_X86_REG_EAX)
  def make():
   p=TOKEN+8*f['token'];assert call(0x6b54a0,[self.op(f['object'])],p)==p;self.trace.extend(('R',str(f['token']+1)))
  def resolve(t):self.trace.extend(('R',str(self.oid(call(0x6b5910,[],TOKEN+8*t)))))
  try:
   if f['root']==0:make()
   if f['root']==1:resolve(0);resolve(1);resolve(0)
   if f['root']==2:self.trace.extend(('R',str(self.oid(call(0x40dc20,[],self.op(f['object']))))))
   if f['root']==3:make();resolve(f['token']);resolve(f['token'])
  finally:self.active=False
  # Full arena projection, including supplied mutation slots; all unlisted bytes
  # and vtables remain byte-identical. Original instruction writes are narrower.
  after=bytearray(u.mem_read(ARENA,SIZE));expected=bytearray(before)
  mutable=[(PRIMARY,256),(ALTERNATE,256),(TOKEN,16)]+[(self.op(i)+8,8) for i in range(1,5)]+[(self.op(i)+0x24,4) for i in range(1,5)]
  for p,n in mutable:after[p-ARENA:p-ARENA+n]=expected[p-ARENA:p-ARENA+n]
  assert after==expected
  b,j=self.cache();self.trace.extend(map(str,('F',signed(self.word(0xabff5c)),self.byte(0xabff64),1 if self.word(0xabff58)==PRIMARY else 2,b,j,self.oid(self.word(0xb2b628)),int(self.changed))))
  for i in range(2):p=TOKEN+8*i;self.trace.extend(map(str,(signed(self.word(p)),*u.mem_read(p+4,4))))
  for i in range(1,5):p=self.op(i);self.trace.extend(map(str,(signed(self.word(p+8)),signed(self.word(p+12)),*struct.unpack('<hh',u.mem_read(p+0x24,4)))))
  for base,n in ((PRIMARY,32),(ALTERNATE,32),(DETACHED,1)):
   for i in range(n):self.trace.extend(map(str,(signed(self.word(base+8*i)),self.oid(self.word(base+8*i+4)))))
  return self.trace
