# SPDX-License-Identifier: GPL-3.0-or-later
import struct
from collections import Counter
from original_presentation import PresentationOracle,STOP
from verify_scheme_resolver import verify,RANGES
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ESI,UC_X86_REG_ESP
ARENA=0x3900000;SIZE=0x10000;RECORDS=ARENA+0x1000;TABLES=[ARENA+0x4000,ARENA+0x4100];STRINGS=ARENA+0x5000
NAMES=[b'LightGrey',b'lightgrey',b'Other',b'',b'A\0x',b'a\0y',b'\x80Z',b'\x80z']
def signed(v):return v if v<2**31 else v-2**32
class SchemeResolverOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(ARENA,SIZE);self.active=False;self.counts=Counter();self.u.hook_add(UC_HOOK_CODE,self.code)
 def va(self,a):return a
 def word(self,p):return int.from_bytes(self.u.mem_read(p,4),'little')
 def rid(self,p):
  if not p:return -1
  assert RECORDS<=p<RECORDS+6*0x400 and (p-RECORDS)%0x400==0;return (p-RECORDS)//0x400
 def change(self,p,v):
  self.put(p,v)
  if ARENA<=p<ARENA+SIZE:self.expected[p-ARENA:p-ARENA+4]=struct.pack('<I',v&0xffffffff)
  else:assert p in self.globals;self.globals[p]=v&0xffffffff
 def mutate(self,stage,index):
  f=self.f
  if self.changed or f[4]!=stage or f[5]!=index:return
  self.changed=True;m=f[6]
  if m&1:self.change(0xab6efc,TABLES[1])
  if m&2:self.change(0xab6f08,f[7])
  if m&4:self.change(RECORDS+0x400+0x310,f[8])
  if m&8:self.change(RECORDS+0x400+0x304,STRINGS+f[9]*0x100)
  if m&16:self.change(TABLES[0]+index*4,RECORDS+f[10]*0x400)
  if m&32:self.change(TABLES[1]+index*4,RECORDS+f[10]*0x400)
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  assert any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()) and a!=0x781f73,('Uninspected/locale scheme path',hex(a))
  if a in RANGES:self.counts[hex(a)]+=1
  if a==0x663d4a:self.savedRecord=self.rid(u.reg_read(UC_X86_REG_EAX))
  if a==0x663d57:
   i=u.reg_read(UC_X86_REG_ESI);self.trace+=list(map(str,('T',i,self.savedRecord,signed(u.reg_read(UC_X86_REG_EAX)))));self.mutate(1,i)
  if a==0x663d66:self.categoryRecord=self.word(u.reg_read(UC_X86_REG_EAX)+u.reg_read(UC_X86_REG_ESI)*4);self.categoryValue=signed(self.word(self.categoryRecord+0x310))
  if a==0x663d6c:
   i=u.reg_read(UC_X86_REG_ESI);self.trace+=list(map(str,('U',i,self.rid(self.categoryRecord),self.categoryValue)));self.mutate(2,i)
 def run(self,f):
  self.f=f;u=self.u;u.mem_write(ARENA,b'\xa5'*SIZE);self.globals={0xab6efc:TABLES[f[3]],0xab6f08:f[2]&0xffffffff,0xb2b098:0}
  for p,v in self.globals.items():self.put(p,v)
  for i,name in enumerate(NAMES):u.mem_write(STRINGS+i*0x100,name+b'\0')
  for i,(name,cat) in enumerate(zip((0,1,2,3,4,6),(0,1,-1,1,2,-2147483648))):self.put(RECORDS+i*0x400+0x304,STRINGS+name*0x100);self.put(RECORDS+i*0x400+0x310,cat)
  for k,table in enumerate(TABLES):
   for i in range(6):self.put(table+i*4,RECORDS+(5-i if k else i)*0x400)
  self.expected=bytearray(u.mem_read(ARENA,SIZE));self.trace=[];self.changed=False;self.active=True
  try:
   for _ in range(1+f[11]):
    self.checked_call(0x663d30,[],STRINGS+f[0]*0x100,f[1],inputs=RANGES.items());assert bytes(u.mem_read(ARENA,SIZE))==self.expected and all(self.word(p)==v for p,v in self.globals.items());self.trace+=['R',str(self.rid(u.reg_read(UC_X86_REG_EAX)))]
  finally:self.active=False
  self.trace+=list(map(str,('F',int(self.word(0xab6efc)==TABLES[1]),signed(self.word(0xab6f08)),int(self.changed))))
  self.trace += [str((self.word(RECORDS+i*0x400+0x304)-STRINGS)//0x100) for i in range(6)]+[str(signed(self.word(RECORDS+i*0x400+0x310))) for i in range(6)]+[str(self.rid(self.word(table+i*4))) for table in TABLES for i in range(6)];return self.trace
