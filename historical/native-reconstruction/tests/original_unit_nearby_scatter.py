# SPDX-License-Identifier: GPL-3.0-or-later
"""Unchanged Unit -> nearby search -> actual destination, in one original guest."""
import struct
from original_unit_scatter_world import UnitScatterWorldOracle,ACTOR,TYPES,MAP,FALLBACK,CELLS,ARENA,SIZE,pack,signed
from verify_unit_nearby_scatter import verify,RANGES,TABLES
from unicorn.x86_const import UC_X86_REG_EIP,UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_ESI,UC_X86_REG_EBP
class UnitNearbyScatterOracle(UnitScatterWorldOracle):
 ranges=RANGES;tables=TABLES;inspection_verify=staticmethod(verify)
 def checked_call(self,*args,**kw):
  kw["inputs"] += [(0x83996c,4),(0xa6f238,4)]
  return super().checked_call(*args,**kw)
 def prepare_join(self,c):
  self.c=c;self.nearby_pending=[];self.nearby_return=None
  self.put(TYPES[0]+0x5a4,c['speed_type']);self.put(MAP+0xf4,c['dimension1'])
  self.put(0x83996c,MAP);self.put(0xa6f238,0)
  # The exact same authored land speeds, now indexed by the borrowed type input.
  self.u.mem_write(0x850ea0,bytes(108*4))
  for land,bits in enumerate(c['speeds']):self.put(0x850ea0+4*(land*9+c['speed_type']),bits)
 def code(self,u,a,n,_):
  if not self.active:return
  sp=u.reg_read(UC_X86_REG_ESP)
  if self.nearby_return==(a,sp):
   result=self.cell(u.reg_read(UC_X86_REG_EAX));self.counts['chosen.'+('empty' if result==(0,0) else 'nonempty')]+=1
   self.event('n','R',*result);self.nearby_return=None;self.context='s'
  if a==0x5502e0:
   assert (a,n) in self.allowed;self.instructions.add(a);self.counts[hex(a)]+=1
   arg=lambda i:self.word(sp+4+4*i)
   assert u.reg_read(UC_X86_REG_ECX)==MAP
   self.source=self.cell(arg(1));self.alternate=arg(5);self.search_output=arg(0)
   assert [signed(arg(j)) for j in (2,3,4,6,7,8,9,10,11,13)]==[self.c['speed_type'],-1,0,1,1,0,1,0,1,0]
   assert self.cell(arg(12))==(0,0) and arg(1)!=arg(12)
   self.event('n','S',*self.source,signed(arg(2)));self.event('n','A',0,0,signed(self.alternate))
   self.nearby_return=(self.word(sp),sp+60);self.context='n';self.counts['nearby_calls']+=1;return
  if self.context!='n':return super().code(u,a,n,_)
  assert (a,n) in self.allowed,('Uninspected Unit nearby child',hex(a))
  assert a not in (0x54f8f0,0x47c200)
  self.instructions.add(a)
  if a in self.ranges:self.counts[hex(a)]+=1
  arg=lambda i:self.word(sp+4+4*i);ecx=u.reg_read(UC_X86_REG_ECX)
  if self.nearby_pending and self.nearby_pending[-1][:2]==(a,sp):
   _,_,kind,out=self.nearby_pending.pop();eax=u.reg_read(UC_X86_REG_EAX)
   if kind=='b':self.event('n','b',self.cid(out),eax&255);self.counts['permission.'+str(eax&255)]+=1
   elif kind=='t':self.event('n','t',eax&255);self.counts['rectangle.'+str(eax&255)]+=1
   else:assert eax==out;self.event('n','p',*self.cell(out))
  def enter(k,n,out=0):self.nearby_pending.append((self.word(sp),sp+4+n,k,out))
  if a in (0x55032b,0x550368):self.emit('w','L',*self.source)
  elif a in (0x550418,0x5505c3,0x55079b,0x550934):self.emit('w','L',*self.cell(sp+{0x550418:0x48,0x5505c3:0x4c,0x55079b:0x3c,0x550934:0x20}[a]))
  elif a==0x550d2f:self.emit('w','L',*self.cell(sp+0x2c))
  elif a==0x548070:self.emit('w','L',*self.cell(arg(0)))
  if a in (0x550352,0x550396):self.event('n','L',*self.source,self.cid(u.reg_read(UC_X86_REG_EAX)))
  elif a in (0x55044c,0x5505f7,0x5507cf,0x550968):self.event('n','L',*self.cell(sp+0x10),self.cid(u.reg_read(UC_X86_REG_ESI)))
  elif a==0x55a740:self.event('n','B',self.cid(arg(0)),*self.cell(arg(0)+0x24),arg(1)&255);enter('b',8,arg(0))
  elif a==0x550cf0:
   assert [signed(arg(j)) for j in range(1,7)]+[arg(7),arg(8)&255]==[1,1,self.c['speed_type'],-1,0,-1,self.alternate,0]
   self.event('n','T',*self.cell(arg(0)));enter('t',36)
  elif a==0x478760:self.event('n','C',self.cid(ecx),signed(arg(0)),arg(1)&255,arg(2)&255,signed(arg(3)),signed(arg(4)),signed(arg(5)),arg(6))
  elif a==0x6a6a50:
   x,y,z=self.coord(arg(1));assert x%256==y%256==128 and z==0
   self.event('n','P',(x-128)//256,(y-128)//256);enter('p',8,arg(0))
  elif a==0x4ba410:
   self.square=struct.unpack('<d',u.mem_read(sp+4,8))[0];self.square_result=0.;self.counts['sqrt.'+('negative' if self.square<0 else 'positive' if self.square else 'zero')]+=1
  elif a==0x550c95:self.event('n','D',int(self.square),struct.unpack('<Q',struct.pack('<d',self.square_result))[0])
  elif a in (0x5503ea,0x55076d):self.counts['radius.'+str(self.word(sp+0x1c))]+=1
  elif a==0x550ae7:
   retained=self.word(sp+0x18);assert retained==u.reg_read(UC_X86_REG_EBP);self.counts['retained.'+str(retained)]+=1
  if 0x478760<=a<0x4788c3 and bytes(u.mem_read(a,n))[0] in (0xc2,0xc3):
   self.event('n','c',u.reg_read(UC_X86_REG_EAX)&255);self.counts['Cell_return.'+str(u.reg_read(UC_X86_REG_EAX)&255)]+=1
 def store(self,u,access,p,n,value,_):
  if self.active and self.context=='n':
   a=u.reg_read(UC_X86_REG_EIP)
   if a==0x4ba475:self.square_result=struct.unpack('<f',pack(value))[0]
   if p==FALLBACK+0x24:
    assert n==4 and any(lo<=a<lo+size for lo,size in ((0x5502e0,0xa0a),(0x550cf0,0xce),(0x548070,0x38)))
    self.emit('w','W',value&0xffffffff);self.writes[hex(a)]+=1;return
   assert not(ARENA<=p and p+n<=ARENA+SIZE),('Nearby search wrote caller arena',hex(a),hex(p))
  return super().store(u,access,p,n,value,_)
 def append_join_state(self,c):
  assert not self.nearby_pending and self.nearby_return is None
  self.event('nearby-retained',signed(self.word(TYPES[0]+0x5a4)),signed(self.word(MAP+0xf4)))
  for p in CELLS:
   self.event(*self.cell(p+0x24),struct.unpack('<b',self.u.mem_read(p+0x11b,1))[0],self.byte(p+0x11c),self.word(p+0x140),signed(self.word(p+0xec)),self.word(p+0x124),self.word(p+0x128))
