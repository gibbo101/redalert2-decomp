# SPDX-License-Identifier: GPL-3.0-or-later
"""Unmodified base6B0670 with explicit waypoint/Cell/reveal children."""
import struct
from collections import Counter
from original_presentation import PresentationOracle,STOP
from verify_scenario_waypoint import verify,RANGES
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_EIP,UC_X86_REG_ESP
ARENA=0x3000000;SIZE=0x10000;ACTION=ARENA+0x100;HOUSES=[ARENA+0x1000,ARENA+0x2000];RULES=[ARENA+0x3000,ARENA+0x4000];CELLS=[ARENA+0x5000+i*0x400 for i in range(3)];POINT=ARENA+0x7000;SCENARIO=ARENA+0x8000
GLOBALS=(0xa35db4,0x839848,0xabfe08,0xa3d290)
class MissionWaypointLookupOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(ARENA,SIZE);self.active=False;self.counts=Counter();self.u.hook_add(UC_HOOK_CODE,self.code)
 def va(self,a):return a
 def word(self,p):return struct.unpack('<I',self.u.mem_read(p,4))[0]
 def ret(self,n,value=0):
  u=self.u;sp=u.reg_read(UC_X86_REG_ESP);target=self.word(sp);u.reg_write(UC_X86_REG_ESP,sp+4+n);u.reg_write(UC_X86_REG_EAX,value&0xffffffff);u.reg_write(UC_X86_REG_EIP,target)
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  sp=u.reg_read(UC_X86_REG_ESP);f=self.f
  if a==0x663180:
   assert u.reg_read(UC_X86_REG_ECX)==SCENARIO
   assert self.word(sp+8)==(f['waypoint']&0xffffffff)
   self.trace.extend(('W',str(f['waypoint'])));self.counts['0x663180']+=1
   return # Execute all five original getter instructions, including its store.
  if 0x663180<a<0x663194:return
  if a==0x548070:
   assert u.reg_read(UC_X86_REG_ECX)==0x8324e0
   p=struct.unpack('<hh',u.mem_read(self.word(sp+4),4));assert p==(f['x'],f['y'])
   self.trace.extend(('L',str(p[0]),str(p[1])));assert self.lookups<3
   cell=CELLS[self.lookups];self.lookups+=1;self.counts['supplied.cell']+=1;self.ret(4,cell);return
  if a==0x54a110:
   assert u.reg_read(UC_X86_REG_ECX)==0x8324e0
   args=[self.word(sp+4+i*4) for i in range(8)];p=struct.unpack('<iii',u.mem_read(args[0],12))
   signed=lambda v:v if v<2**31 else v-2**32
   self.trace.extend(('A',*[str(v) for v in p],str(signed(args[1])),str(HOUSES.index(args[2])),*[str(v) for v in args[3:]]))
   self.reveals+=1;self.counts['supplied.reveal']+=1
   if self.reveals==1 and f['mutation']:
    self.put(0xabfe08,(f['scale']&0xffffffff)^0x80000001)
    if f['mutation']==1:self.put(0xa35db4,HOUSES[1]);self.put(0x839848,RULES[1])
    else:self.put(RULES[0]+0x54c,(f['range']+0x80000001)&0xffffffff)
   self.ret(32,0xdeadbeef);return
  assert any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected waypoint reveal instruction',hex(a))
  if a in RANGES:self.counts[hex(a)]+=1
 def getter(self,f):
  self.f=f;u=self.u;u.mem_write(ARENA,b'\xa5'*SIZE);memory=bytes((i*37+17)&255 for i in range(0x1000));u.mem_write(SCENARIO,memory)
  source=(0x632+f['waypoint']*4)&0xffffffff;out=f['out'];assert source+4<=0x1000 and out+4<=0x1000
  expected=bytearray(u.mem_read(ARENA,SIZE));expected[SCENARIO+out-ARENA:SCENARIO+out-ARENA+4]=memory[source:source+4]
  self.trace=[];self.active=True
  try:self.checked_call(0x663180,[SCENARIO+out,f['waypoint']],SCENARIO,writes=[(SCENARIO+out,4)],inputs=list(RANGES.items()))
  finally:self.active=False
  assert u.reg_read(UC_X86_REG_EAX)==SCENARIO+out
  assert bytes(u.mem_read(ARENA,SIZE))==bytes(expected)
  self.trace.extend(('D',str(out),*[str(v) for v in u.mem_read(SCENARIO,0x1000)],'R','1'));return self.trace
 def run(self,f):
  if f.get('getter'):return self.getter(f)
  self.f=f;u=self.u;u.mem_write(ARENA,b'\xa5'*SIZE);self.put(ACTION+0x74,f['waypoint']);u.mem_write(HOUSES[0]+0x188,bytes([f['disabled']]));u.mem_write(HOUSES[1]+0x188,b'\xff')
  self.put(RULES[0]+0x54c,f['range']);self.put(RULES[1]+0x54c,f['range']+0x80000001)
  for i,c in enumerate(CELLS):self.put(c+0x140,f['flags'][i]);u.mem_write(c+0x11b,bytes([f['levels'][i]&255]))
  u.mem_write(POINT,struct.pack('<hh',f['x'],f['y']))
  offset=(0x632+f['waypoint']*4)&0xffffffff;assert offset+4<=0x1000
  u.mem_write(SCENARIO+offset,struct.pack('<hh',f['x'],f['y']))
  for p,v in zip(GLOBALS,(HOUSES[0],RULES[0],f['scale'],SCENARIO)):self.put(p,v)
  before=bytearray(u.mem_read(ARENA,SIZE));self.trace=[];self.lookups=0;self.reveals=0;self.active=True
  try:self.checked_call(0x6b0670,[0xffffffff,0xabcdef01,0x12345678,0x76543210],ACTION,inputs=list(RANGES.items()))
  finally:self.active=False
  if not f['disabled'] and f['mutation']==2:struct.pack_into('<I',before,RULES[0]+0x54c-ARENA,(f['range']+0x80000001)&0xffffffff)
  assert bytes(u.mem_read(ARENA,SIZE))==bytes(before)
  mutate=not f['disabled'] and f['mutation']
  values=(HOUSES[1] if mutate and f['mutation']==1 else HOUSES[0],RULES[1] if mutate and f['mutation']==1 else RULES[0],((f['scale']&0xffffffff)^0x80000001) if mutate else f['scale']&0xffffffff,SCENARIO)
  assert tuple(self.word(p) for p in GLOBALS)==values
  assert self.reveals==(0 if f['disabled'] else 2)
  self.trace.extend(('R',str(u.reg_read(UC_X86_REG_EAX)&255)));return self.trace
