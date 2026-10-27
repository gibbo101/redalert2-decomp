# SPDX-License-Identifier: GPL-3.0-or-later
"""Unchanged original mission-control instructions with named INI-return services."""
import struct
from collections import Counter
from original_presentation import PresentationOracle,OBJ,STOP
from original_foot_lit import words,ret
from original_land_characteristics import push_double
from verify_mission_control import verify,RANGES,SERVICES,KEYS
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_FPCW,UC_X86_REG_FPSW,UC_X86_REG_FPTAG
TABLE=0xa403b0
class MissionControlOracle(PresentationOracle):
 def __init__(self,exe):
  verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.active=False;self.fixture=False;self.counts=Counter();self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.write)
  self.names={p:i for i,p in enumerate(words(self.u,0x7cd774,30))};self.names[0x7cdecc]=0xffffffff
 def va(self,a):return a
 def event(self,*values):self.events.extend(str(v&0xffffffff) for v in values)
 def mutate(self,off,n,v):
  self.fixture=True
  try:self.u.mem_write(TABLE+off,(v&((1<<(n*8))-1)).to_bytes(n,'little'))
  finally:self.fixture=False
  self.event(5,off,n,v&0xffffffff,v>>32)
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  assert a in SERVICES or any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),hex(a)
  if a in RANGES or a in SERVICES:self.counts[hex(a)]+=1
  if a==0x594dd0 and self.root==2:self.event(6,(u.reg_read(UC_X86_REG_ECX)-TABLE)//32)
  if a not in SERVICES:return
  sp=u.reg_read(UC_X86_REG_ESP);assert u.reg_read(UC_X86_REG_ECX)==OBJ
  section=self.names[words(u,sp+4,1)[0]]
  if a==0x50c9b0:self.event(1,section,self.present);ret(u,4,self.present);return
  key=KEYS[words(u,sp+8,1)[0]];k=list(KEYS.values()).index(key)
  if a==0x50f410:
   default=words(u,sp+12,1)[0]&255;self.event(2,section,k,default,self.flags[k])
   if self.diag==1:self.mutate(0,4,(k*7+3)%30)
   if self.diag==2 and k<5:self.mutate(k+5,1,128+k)
   ret(u,12,self.flags[k])
  else:
   lo,hi=words(u,sp+12,2);value=self.rate if k==6 else self.aa
   self.event(3,section,k,lo,hi,value&0xffffffff,value>>32)
   if self.diag==1 and k==6:self.mutate(0,4,17)
   if self.diag==3 and k==7:self.mutate(16,8,0x3ff8000012345678)
   push_double(u,value);ret(u,16,0)
 def write(self,u,access,p,n,v,_):
  if not self.active or self.fixture or not TABLE<=p<TABLE+960:return
  assert n in (1,4,8) and p+n<=TABLE+960
  v&=(1<<(n*8))-1
  off=(p-TABLE)%32;self.event(4,off,n,v&0xffffffff,(v>>32)&0xffffffff)
  # Unicorn's write hook precedes the guest store. Mutate disjoint fields only.
  if self.root==1 and self.diag==4 and off==24 and n==4:self.mutate(20,4,0x40080000)
  if self.root==1 and self.diag==5 and off==16 and n==8:self.mutate(0,4,29)
 def run(self,f):
  self.root,index,self.present,*rest=f;self.flags=rest[:6];self.rate,self.aa,initial,self.diag=rest[6:]
  u=self.u;u.mem_write(TABLE-32,b'\xa7'*1024);self.put(TABLE,index);u.mem_write(TABLE+16,struct.pack('<Q',initial));u.mem_write(OBJ,b'\xa5'*128)
  u.reg_write(UC_X86_REG_FPSW,0);u.reg_write(UC_X86_REG_FPTAG,0xffff)
  self.events=[];self.active=True
  inputs=[*[(a,n) for a,n in RANGES.items()],(0x7cd774,120),(0x79b610,8),(OBJ,128),*[(p,len(u.mem_read(p,100).split(b'\0')[0])+1) for p in (*self.names,*KEYS)]]
  result=0
  try:
   if self.root==3:
    self.active=False
    for i in range(30):self.put(TABLE+i*32,i);u.mem_write(TABLE+i*32+6,bytes([(self.flags[0]+i)&255]))
    self.active=True
    raw=index|0x80000000 if self.diag==1 and index>=0 else index
    self.checked_call(0x594db0,ecx=raw,inputs=inputs+[(TABLE,960)]);result=u.reg_read(UC_X86_REG_EAX)&255;self.event(7,result)
    if index!=-1:
     #5950D0 reads a supplied actor raw mission;594E10 reads the actual record.
     self.active=False;self.put(OBJ+0x98,raw);self.active=True
     self.checked_call(0x5950d0,ecx=OBJ,inputs=[*RANGES.items(),(TABLE,960),(OBJ,0x9c)]);self.event(8,u.reg_read(UC_X86_REG_EAX)-TABLE)
     self.checked_call(0x594e10,ecx=TABLE+index*32,inputs=inputs+[(TABLE,960)]);assert self.names[u.reg_read(UC_X86_REG_EAX)]==index
   else:
    root=(0x594dd0,0x594e30,0x4d4520)[self.root]
    self.checked_call(root,[OBJ] if self.root==1 else [],ecx=TABLE,writes=[(TABLE,960 if self.root==2 else 32)],inputs=inputs)
    result=u.reg_read(UC_X86_REG_EAX)&255 if self.root==1 else 0
  finally:self.active=False
  assert bytes(u.mem_read(TABLE-32,32))==b'\xa7'*32 and bytes(u.mem_read(TABLE+960,32))==b'\xa7'*32
  assert (u.reg_read(UC_X86_REG_FPSW)>>11)&7==0 and u.reg_read(UC_X86_REG_FPTAG)==0xffff
  return self.events+['F',str(result),*[str(v) for v in u.mem_read(TABLE,960 if self.root>=2 else 32)]]
