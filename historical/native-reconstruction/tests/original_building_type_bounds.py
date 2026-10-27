# SPDX-License-Identifier: GPL-3.0-or-later
"""Unmodified Type bounds/frame/union/release parents; explicit image getters and heap."""
import struct
from original_presentation import PresentationOracle,STOP
from verify_building_type_bounds import verify,RANGES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_READ,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ESP,UC_X86_REG_EIP,UC_X86_REG_ECX
BASE=0x3e00000;SIZE=0x10000;TYPE=BASE+0x1000;IMAGES=[BASE+0x4000+i*0x1000 for i in range(3)];OUT=BASE+0x9000
class BuildingTypeBoundsOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(BASE,SIZE);self.active=False;self.gets=0;self.frames=0;self.frees=0;self.releases=0;self.parents=0
  self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_READ,self.read);self.u.hook_add(UC_HOOK_MEM_WRITE,self.write)
 def va(self,a):return a
 def word(self,p):return struct.unpack('<I',self.u.mem_read(p,4))[0]
 def ints(self,p,v):self.u.mem_write(p,struct.pack('<'+'I'*len(v),*[x&0xffffffff for x in v]))
 def signed(self,v):return (v+2**31)%2**32-2**31
 def emit(self,k,id=-1,field=-1,value=0):self.trace.extend(map(str,(k,id,field,value)))
 def pointer(self,id):return 0 if id<0 else IMAGES[id]
 def identify(self,p):return -1 if not p else IMAGES.index(p)
 def ret(self,value):
  sp=self.u.reg_read(UC_X86_REG_ESP);self.u.reg_write(UC_X86_REG_EAX,value);self.u.reg_write(UC_X86_REG_EIP,self.word(sp));self.u.reg_write(UC_X86_REG_ESP,sp+4)
 def mutate(self):
  if self.mutated or not self.f[1]:return
  self.mutated=True;m=self.f[1];self.emit(8,value=m)
  if m==1:self.put(TYPE+0xb98,self.pointer(self.f[15]))
  if m==2:self.put(TYPE+0x11cc,IMAGES[2])
  if m==3:self.u.mem_write(TYPE+0x13e2,b'\0')
  if m==4:self.u.mem_write(IMAGES[0]+2,struct.pack('<2h',32767,-32768))
  if m==5:self.put(TYPE+0x11cc,0)
  if m==6:self.put(TYPE+0xb98,IMAGES[2])
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  if a in (0x458ce0,0x45e790):
   self.gets+=1;assert u.reg_read(UC_X86_REG_ECX)==TYPE;id=self.f[14 if a==0x458ce0 else 15];self.emit(1 if a==0x458ce0 else 2,value=id)
   if a==0x45e790 and self.f[1]!=2:self.mutate()
   self.ret(self.pointer(id));return
  if a==0x781d3b:
   self.frees+=1;id=self.identify(self.word(u.reg_read(UC_X86_REG_ESP)+4));self.emit(7,value=id)
   if self.f[1]==2:self.mutate()
   self.ret(0);return
  assert any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected Type bounds instruction',hex(a))
  if a==0x45e290:self.parents+=1
  if a==0x45ed50:self.frames+=1
  if a==0x45e920:self.releases+=1
 def read(self,u,access,p,n,v,_):
  if not self.active:return
  for id,image in enumerate(IMAGES):
   off=p-image
   if off in (2,4,6):
    assert n==2;v=struct.unpack('<h',u.mem_read(p,2))[0]
    self.emit(4,id,value=v) if off==6 else self.emit(5,id,off//2-1,v)
   elif 8<=off<8+self.capacity*24 and (off-8)%24<8:
    index,field=divmod(off-8,24);assert n==2 and field%2==0
    self.emit(6,id,index*4+field//2,struct.unpack('<h',u.mem_read(p,2))[0])
 def write(self,u,access,p,n,v,_):
  if not self.active:return
  if TYPE+0x11ec<=p<TYPE+0x11fc:assert n==4;self.emit(9,field=p-TYPE,value=self.signed(v))
  if p in (TYPE+0xb98,TYPE+0xb9c):assert n==(4 if p==TYPE+0xb98 else 1);self.emit(9,field=p-TYPE,value=v)
 def run(self,f):
  self.capacity=(len(f)-26)//12;self.stride=3+self.capacity*4
  self.f=f;self.trace=[];self.mutated=False;self.u.mem_write(BASE,bytes([0x5a])*SIZE)
  self.put(TYPE,0x79d1f8);self.ints(TYPE+0x11ec,f[2:6]);self.ints(0x84ed88,f[6:10]);self.put(TYPE+0xb98,self.pointer(f[10]));self.put(TYPE+0x11cc,self.pointer(f[11]));self.u.mem_write(TYPE+0x13e2,bytes([f[12]]));self.u.mem_write(TYPE+0xb9c,bytes([f[13]]))
  for id,image in enumerate(IMAGES):
   j=17+id*self.stride;self.u.mem_write(image,struct.pack('<4h',0,*f[j:j+3]))
   for i in range(self.capacity):self.u.mem_write(image+8+i*24,struct.pack('<4h',*f[j+3+i*4:j+7+i*4]))
  allowed=[(OUT,16),(TYPE+0x11ec,16),(TYPE+0xb98,5)]
  if f[1] in (2,5):allowed.append((TYPE+0x11cc,4))
  if f[1]==3:allowed.append((TYPE+0x13e2,1))
  if f[1]==4:allowed.append((IMAGES[0]+2,4))
  before=bytes(self.u.mem_read(BASE,SIZE));self.active=True
  try:
   address=0x45e290 if f[0]==0 else 0x45ed50 if f[0]==1 else 0x45e920
   args=[OUT] if f[0]==0 else [OUT,f[16]] if f[0]==1 else []
   self.checked_call(address,args,TYPE if f[0]!=1 else self.pointer(f[14]),writes=allowed,inputs=[*RANGES.items(),(0x79d1f8,0xc4)])
  finally:self.active=False
  after=bytearray(self.u.mem_read(BASE,SIZE))
  for p,n in allowed:after[p-BASE:p-BASE+n]=before[p-BASE:p-BASE+n]
  assert after==before,'Unrelated Type/image arena bytes changed'
  if f[0]!=2:
   assert u32(self.u.reg_read(UC_X86_REG_EAX))==OUT
   for j,v in enumerate(struct.unpack('<4i',self.u.mem_read(OUT,16))):self.emit(10,field=j,value=v)
  self.trace+=['F',*map(str,struct.unpack('<4i',self.u.mem_read(TYPE+0x11ec,16))),str(self.identify(self.word(TYPE+0xb98))),str(self.identify(self.word(TYPE+0x11cc))),str(self.u.mem_read(TYPE+0x13e2,1)[0]),str(self.u.mem_read(TYPE+0xb9c,1)[0])]
  return self.trace
def u32(v):return v&0xffffffff
