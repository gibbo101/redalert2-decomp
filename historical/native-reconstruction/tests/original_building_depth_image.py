# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete original458510; explicit file/heap/cache children and full write audit."""
import hashlib,struct
from original_presentation import PresentationOracle,STOP
from verify_building_depth_image import verify,ENTRY,SIZE
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EIP
BASE=0x4b00000;ARENA=0x100000;SOURCE=BASE+0x10000;ALLOC=BASE+0x50000;REPLACE=BASE+0x90000;OLD=BASE+0xd0000;VT=BASE+0xe0000;STUB=BASE+0xe1000;GLOBAL=0x85029c
class BuildingDepthImageOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(BASE,ARENA);self.active=False
  self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.write)
 def va(self,a):return a
 def word(self,p):return int.from_bytes(self.u.mem_read(p,4),'little')
 def ident(self,p):return {0:0,OLD:1,ALLOC:2,REPLACE:3}[p]
 def event(self,*v):self.trace.extend(map(str,v))
 def ret(self,pop,value=0):
  sp=self.u.reg_read(UC_X86_REG_ESP);self.u.reg_write(UC_X86_REG_EAX,value&0xffffffff);self.u.reg_write(UC_X86_REG_EIP,self.word(sp));self.u.reg_write(UC_X86_REG_ESP,sp+4+pop)
 def code(self,u,a,n,_):
  if not self.active or a==STOP or ENTRY<=a<ENTRY+SIZE:return
  sp=u.reg_read(UC_X86_REG_ESP);receiver=u.reg_read(UC_X86_REG_ECX);arg=lambda:self.word(sp+4)
  if a==0x781d3b:
   assert arg()==OLD and self.word(GLOBAL)==OLD;self.event(1,1);self.ret(0);return
  if a==0x468f50:
   assert arg()==0x7cfdb0;self.file=receiver;self.put(receiver,VT);self.event(3,self.ident(self.word(GLOBAL)));self.ret(4,receiver);return
  if a==STUB:
   assert receiver==self.file;self.event(4,len(self.source));self.ret(0,len(self.source));return
  if a==0x438410:
   assert receiver==self.file+0x54;self.event(5,0);self.ret(0);return
  if a==0x42f350:
   assert receiver==self.file;self.event(6,0);self.ret(0);return
  if a==0x782017:
   assert arg()==len(self.source);self.event(7,len(self.source));self.ret(0,ALLOC);return
  if a==0x5956c0:
   assert receiver==0x7cfdb0;self.event(8,self.ident(self.word(GLOBAL)))
   if self.mutation==1:self.put(GLOBAL,REPLACE);self.global_expected=REPLACE
   if self.mutation==2:
    self.source[-1]^=0x81;self.u.mem_write(SOURCE,bytes(self.source));self.expected[SOURCE-BASE:SOURCE-BASE+len(self.source)]=self.source
   self.ret(0,SOURCE);return
  raise AssertionError(('Uninspected depth initializer instruction',hex(a)))
 def write(self,u,access,p,n,v,_):
  if not self.active:return
  if p==GLOBAL:
   assert n==4;self.event(2,self.ident(v));self.global_expected=v;return
  for base in (ALLOC,REPLACE):
   if base<=p and p+n<=base+len(self.source):
    assert n in (1,4);self.stores+=struct.pack('<4I',self.ident(base),p-base,n,v&((1<<(8*n))-1));self.expected[p-BASE:p-BASE+n]=(v&((1<<(8*n))-1)).to_bytes(n,'little');return
 def run(self,source,old,mutation):
  self.source=bytearray(source);self.mutation=mutation;self.trace=[];self.stores=bytearray();self.file=0
  self.u.mem_write(BASE,b'\x5a'*ARENA);self.u.mem_write(SOURCE,source);self.u.mem_write(ALLOC,b'\xa5'*len(source));self.u.mem_write(REPLACE,b'\x55'*len(source));self.u.mem_write(OLD,b'\x44'*32);self.put(VT+0x2c,STUB);self.put(GLOBAL,OLD if old else 0)
  self.global_expected=self.word(GLOBAL);self.expected=bytearray(self.u.mem_read(BASE,ARENA));self.active=True
  try:self.checked_call(ENTRY,writes=[(GLOBAL,4),(ALLOC,len(source)),(REPLACE,len(source))],inputs=[(ENTRY,SIZE),(VT,0x100),(OLD,32),(0x7cfdb0,13)])
  finally:self.active=False
  assert self.u.mem_read(BASE,ARENA)==self.expected,'Unrelated depth initializer arena changed'
  assert self.word(GLOBAL)==self.global_expected
  digest=lambda p,n:hashlib.sha256(bytes(self.u.mem_read(p,n))).hexdigest()
  final=self.word(GLOBAL);width,height=struct.unpack('<hh',self.u.mem_read(final+2,4));offset=self.word(final+28)
  self.payload_hash=digest(final+offset,width*height) if width>0 and height>0 else None
  self.trace+=['F',str(self.ident(self.word(GLOBAL))),digest(ALLOC,len(source)),digest(REPLACE,len(source)),digest(OLD,32),hashlib.sha256(self.stores).hexdigest(),str(len(self.stores)//16)];return self.trace
