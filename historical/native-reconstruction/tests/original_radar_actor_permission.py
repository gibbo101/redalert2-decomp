# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete stock2F8, actual local/alliance/veterancy and supplied remaining children."""
import struct
from original_presentation import PresentationOracle,STOP
from verify_radar_actor_permission import verify,RANGES,DATA
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EIP
BASE=0x3e00000;SIZE=0x20000;ACTOR=BASE;TYPE=BASE+0x2000;TYPE2=TYPE+0x2000;VT=BASE+0x6000;OUT=BASE+0x7000;HOUSES=BASE+0x8000;SESSION=BASE+0x15000;STUB=BASE+0x16000
class RadarActorPermissionOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(BASE,SIZE);self.active=False;self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.write)
 def va(self,p):return p
 def word(self,p):return struct.unpack('<I',self.u.mem_read(p,4))[0]
 def ints(self,p,n):return list(struct.unpack('<'+'i'*n,self.u.mem_read(p,n*4)))
 def emit(self,*v):self.trace.extend(map(str,v))
 def ret(self,argc,value):
  sp=self.u.reg_read(UC_X86_REG_ESP);self.u.reg_write(UC_X86_REG_EAX,value&0xffffffff);self.u.reg_write(UC_X86_REG_EIP,self.word(sp));self.u.reg_write(UC_X86_REG_ESP,sp+4+argc*4)
 def mutate(self,stage):
  m=self.f[-1]
  if m==1 and stage=='P':self.u.mem_write(ACTOR+0x88,struct.pack('<3i',2147483600,-2147483600,312));self.emit('M',1)
  if m==2 and stage=='F':self.put(ACTOR+0x1b4,HOUSES);self.emit('M',2)
  if m==3 and stage=='P':self.u.mem_write(ACTOR+0x5b7,b'\xff');self.emit('M',3)
  if m==4 and stage=='H':self.put(ACTOR+0x418,TYPE2);self.currentType=TYPE2;self.emit('M',4)
  if m==5 and stage=='T' and self.typeCalls==1:self.u.mem_write(ACTOR+0x118,struct.pack('<d',2.));self.emit('M',5)
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  sp=u.reg_read(UC_X86_REG_ESP);ecx=u.reg_read(UC_X86_REG_ECX);arg=lambda i:self.word(sp+4+i*4)
  if a==STUB:
   assert ecx==ACTOR;self.typeCalls+=1;self.emit('T',int(self.currentType==TYPE2));self.mutate('T');self.ret(0,self.currentType);return
  if a==STUB+16:assert ecx==ACTOR;self.emit('H',self.f[14]);self.mutate('H');self.ret(0,self.f[14]);return
  if a==STUB+32:assert ecx==ACTOR;self.emit('F',self.f[20]);self.mutate('F');self.ret(0,self.f[20]);return
  if a in (0x458940,0x458930):
   assert ecx in (TYPE,TYPE2);which=int(ecx==TYPE2)
   if a==0x458940:assert arg(0)==0;value=self.f[22]+which;self.emit('Y',which,0,value);self.mutate('H');self.ret(1,value)
   else:value=self.f[21]+which;self.emit('X',which,value);self.ret(0,value)
   return
  if a in (0x568140,0x5683c0):
   assert ecx==0x8324e0;point=self.ints(arg(0),3)
   if a==0x568140:
    value=self.f[17 if self.primaryCalls==0 else 18];self.primaryCalls+=1;self.emit('P',*point,value);self.mutate('P')
   else:value=self.f[19];self.emit('S',*point,value)
   self.ret(1,value);return
  assert any(p<=a and a+n<=p+size for p,size in RANGES.items()),('Uninspected permission instruction',hex(a))
  if a in (0x7133a0,0x713420):assert ecx==ACTOR+0x118;self.emit('V' if a==0x7133a0 else 'E')
  elif a==0x4f52b0:assert ecx in (HOUSES,HOUSES+0x6000);self.emit('L',int(ecx!=HOUSES))
  elif a==0x4e5540:assert ecx==HOUSES and arg(0) in (HOUSES,HOUSES+0x6000);self.emit('B',int(arg(0)!=HOUSES))
 def write(self,u,access,p,n,value,_):
  if self.active and BASE<=p<BASE+SIZE:
   assert p==OUT and n==4;self.emit('W',value&0xffffffff);self.stores+=1
 def run(self,f):
  self.f=f;kind,aa6,aa7,flag325,discovered,vbits,houseMode,owner,human,control,alliance,mode,session,mission,height,v277,e289,p1,p2,secondary,eligible,width,heightDim,b5bd,b5b7,status,mutation=f
  u=self.u;u.mem_write(BASE,b'\xa5'*SIZE);self.currentType=TYPE;self.typeCalls=self.primaryCalls=self.stores=0
  for p,v in [(ACTOR,VT),(ACTOR+0x418,TYPE),(ACTOR+0x1b4,HOUSES+owner*0x6000),(ACTOR+0x1b8,mission),(VT+0x80,STUB),(VT+0x1b0,STUB+16),(VT+0x2fc,STUB+32),(OUT,status),(0xa3d298,houseMode),(0xa35db4,HOUSES),(0xb263d8,mode),(0xa3d290,SESSION),(SESSION,session)]:self.put(p,v)
  for p in (TYPE,TYPE2):
   for off,value in [(0xaa6,aa6),(0xaa7,aa7),(0x277,v277),(0x289,e289)]:u.mem_write(p+off,bytes([value]))
  for i in range(2):
   p=HOUSES+i*0x6000;self.put(p+0x30,i);self.put(p+0x5674,alliance);u.mem_write(p+0x134,bytes([human,control]))
  for off,value in [(0x325,flag325),(0x373,discovered),(0x5bd,b5bd),(0x5b7,b5b7)]:u.mem_write(ACTOR+off,bytes([value]))
  u.mem_write(ACTOR+0x118,struct.pack('<Q',vbits));u.mem_write(ACTOR+0x88,struct.pack('<3i',-513,1025,208));self.trace=[];self.active=True
  try:self.checked_call(0x452220 if kind else 0x6d7a10,[OUT],ACTOR,writes=[(OUT,4)],inputs=[*RANGES.items(),*DATA.items(),(VT,0x300)])
  finally:self.active=False
  result=u.reg_read(UC_X86_REG_EAX)&255;assert result in (0,1) and self.stores<=1
  return self.trace+['R',str(result),str(self.word(OUT))]
