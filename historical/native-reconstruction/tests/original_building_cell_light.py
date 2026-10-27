# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete ordinary parent joined to actual shared table/fallback548070."""
import struct
from original_building_ordinary import BuildingOrdinaryOracle,BASE,SIZE,ACTOR,CELL
from verify_building_cell_light import verify,ADDRESS,SIZE as LOOKUP_SIZE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EIP
TABLE=BASE+0x30000;ALIAS=CELL+0x200;FALLBACK=0xa6f9f8
class BuildingCellLightOracle(BuildingOrdinaryOracle):
 def __init__(self,exe):
  super().__init__(exe);self.inspection=verify(exe.read_bytes());self.u.mem_map(TABLE,0x100000)
 def run(self,f):
  self.lookupMode=f[0];return super().run(f[1:])
 def checked_call(self,address,*args,**kw):
  self.u.mem_write(TABLE,bytes(0x100000));self.put(0x832618,TABLE)
  def w(v):return ((v+32768)%65536)-32768
  x,y=w(int(self.f[31]/256)),w(int(self.f[32]/256));index=y*512+x
  if 0<=index<262144 and self.lookupMode!=1:self.put(TABLE+index*4,ALIAS if self.lookupMode==2 else CELL)
  self.change(CELL+0x24,12*65536+11);self.change(ALIAS+0x24,22*65536+21);self.change(ALIAS+0x10a,w(self.f[30]+17),2)
  self.u.mem_write(FALLBACK,b'\x5a'*0x148);self.put(FALLBACK+0x24,0x12345678);self.u.mem_write(FALLBACK+0x10a,struct.pack('<h',w(self.f[30]+31)))
  before=bytearray(self.u.mem_read(FALLBACK,0x148));kw['writes']=[*kw['writes'],(FALLBACK+0x24,4)]
  kw['inputs']=[*kw['inputs'],(ADDRESS,LOOKUP_SIZE),(TABLE,0x100000),(0x832618,4)]
  result=super().checked_call(address,*args,**kw)
  after=bytearray(self.u.mem_read(FALLBACK,0x148));before[0x24:0x28]=after[0x24:0x28];assert before==after,'Unrelated fallback bytes changed'
  return result
 def code(self,u,a,n,context):
  if self.active and ADDRESS<=a and a+n<=ADDRESS+LOOKUP_SIZE:
   if a==ADDRESS:
    assert u.reg_read(UC_X86_REG_ECX)==0x8324e0;sp=u.reg_read(UC_X86_REG_ESP);self.event(3,13,self.signed(self.word(self.word(sp+4))));self.mutate(5);self.counts[hex(a)]+=1
   if a==0x5480a5:
    sp=u.reg_read(UC_X86_REG_ESP);packed=self.word(self.word(sp+4));selected=u.reg_read(UC_X86_REG_EAX);assert selected in (CELL,ALIAS,FALLBACK)
    self.event(9,self.signed(packed),(CELL,ALIAS,FALLBACK).index(selected),self.signed(self.word(selected+0x24)))
   return
  return super().code(u,a,n,context)
 def read(self,u,access,p,n,v,context):
  if self.active and p in (ALIAS+0x10a,FALLBACK+0x10a) and 0x43a5e0<=u.reg_read(UC_X86_REG_EIP)<0x43abc1:
   assert n==2;self.event(1,1,0x10a,struct.unpack('<h',u.mem_read(p,2))[0])
  return super().read(u,access,p,n,v,context)
 def store(self,u,access,p,n,v,context):
  if self.active and p==FALLBACK+0x24:assert n==4;self.event(10,self.signed(v))
  return super().store(u,access,p,n,v,context)
