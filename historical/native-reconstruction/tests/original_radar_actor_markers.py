# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete original actor callers; supplied child probes, original shape selector."""
import struct
from original_presentation import PresentationOracle,STOP,STACK
from verify_radar_actor_markers import verify,RANGES,DATA
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EIP
BASE=0x3c00000;SIZE=0x10000;ACTOR=BASE;TYPE=BASE+0x1000;MAP=0x8324e0;POINTS=BASE+0x3000;OTHER=POINTS+0x100
ROOTS=list(RANGES)[:6]
def signed(n):return (n+2**31)%2**32-2**31
class RadarActorMarkersOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(BASE,SIZE);self.active=False;self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.write)
 def va(self,a):return a
 def word(self,p):return struct.unpack('<I',self.u.mem_read(p,4))[0]
 def ret(self,argc,result=0):
  sp=self.u.reg_read(UC_X86_REG_ESP);self.u.reg_write(UC_X86_REG_EAX,result);self.u.reg_write(UC_X86_REG_EIP,self.word(sp));self.u.reg_write(UC_X86_REG_ESP,sp+4+argc*4)
 def mutate(self):
  self.calls+=1
  if self.calls!=1 or not self.mutation:return
  m=self.mutation;self.trace+=['M',str(m)]
  if m==1:self.put(ACTOR+0x1a0,0x7fffffff);self.put(ACTOR+0x1a4,0x80000000)
  elif m==2:self.put(self.shape+16,0)
  elif m==3:self.put(self.shape+4,OTHER);self.put(self.shape+16,4)
  elif m==4:self.put(TYPE+0xc78,(self.index+1)%22)
  elif m==5:self.u.mem_write(ACTOR+0x37b,b'\xfe')
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  sp=u.reg_read(UC_X86_REG_ESP);ecx=u.reg_read(UC_X86_REG_ECX)
  if a in (0x631910,0x631af0):
   assert ecx==MAP and self.word(sp+4)==ACTOR
   self.trace+=['I' if a==0x631910 else 'D',str(signed(self.word(sp+8))),str(signed(self.word(sp+12))),str(u.mem_read(ACTOR+0x37b,1)[0])];self.mutate();self.ret(3);return
  if a==0x632620:
   assert ecx==MAP;p=self.word(sp+4);alias=p==ACTOR+0x1a0
   assert alias==(self.op==2)
   self.trace+=['Q',str(int(alias)),str(signed(self.word(p))),str(signed(self.word(p+4))),str(u.mem_read(ACTOR+0x37b,1)[0])]
   self.mutate();self.trace+=['L',str(signed(self.word(p))),str(signed(self.word(p+4)))];self.ret(1);return
  assert any(p<=a and a+n<=p+size for p,size in RANGES.items()),('Uninspected actor marker instruction',hex(a))
  if a==0x6328d0:
   assert ecx==MAP and self.word(sp+4)==TYPE;self.trace+=['S',str(signed(self.word(TYPE+0xc78)))];self.selects+=1
 def write(self,u,access,p,n,v,_):
  if self.active and (BASE<=p<BASE+SIZE or MAP+0x1274<=p<MAP+0x1274+22*24):
   assert p==ACTOR+0x37b and n==1;self.trace+=['W',str(v&255)];self.stores+=1
 def run(self,f):
  self.op,self.index,count,x,y,reg,self.mutation=f;u=self.u;u.mem_write(BASE,b'\xa5'*SIZE)
  u.mem_write(MAP+0x1274,bytes(22*24));self.shape=MAP+0x1274+self.index*24
  for p,v in ((ACTOR+0x1a0,x),(ACTOR+0x1a4,y),(ACTOR+0x418,TYPE),(TYPE+0xc78,self.index),(self.shape+4,POINTS),(self.shape+16,count)):self.put(p,v)
  u.mem_write(ACTOR+0x37b,bytes([reg]))
  for i in range(8):
   u.mem_write(POINTS+i*8,struct.pack('<ii',i-2,3-i));u.mem_write(OTHER+i*8,struct.pack('<ii',20+i,-20-i))
  self.trace=[];self.calls=self.selects=self.stores=0;self.active=True
  # Only the37B store is native instruction output. Supplied child probes mutate
  # the arena via host writes; every other original store is rejected.
  try:self.checked_call(ROOTS[self.op],ecx=ACTOR,writes=[(ACTOR+0x37b,1)],inputs=[*RANGES.items(),*DATA.items()])
  finally:self.active=False
  expectedStores=0 if self.op%3==2 else 1
  assert self.stores==expectedStores and self.selects==int(self.op>=3)
  return self.trace+['R',str(signed(self.word(ACTOR+0x1a0))),str(signed(self.word(ACTOR+0x1a4))),str(u.mem_read(ACTOR+0x37b,1)[0]),str(signed(self.word(self.shape+16))),str(int(self.word(self.shape+4)==OTHER)),str(self.word(TYPE+0xc78))]
