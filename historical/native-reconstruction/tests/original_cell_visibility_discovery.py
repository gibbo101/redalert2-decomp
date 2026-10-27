# SPDX-License-Identifier: GPL-3.0-or-later
"""Unmodified base visibility-change projection with actual resident selection."""
import struct
from collections import Counter
from original_presentation import PresentationOracle,STOP
from verify_cell_visibility_discovery import verify,RANGES
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_EIP,UC_X86_REG_ESP,UC_X86_REG_ESI
ARENA=0x3200000;SIZE=0x200000;SLOTS=ARENA;CELLS=ARENA+0x100000;OBJECTS=ARENA+0x120000;VT=ARENA+0x140000;START=ARENA+0x150000;DISCOVER=ARENA+0x1f0000
FALLBACK=0xa6f9f8
def put16(u,p,v):u.mem_write(p,struct.pack('<H',v&0xffff))
class CellVisibilityDiscoveryOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(ARENA,SIZE);self.active=False;self.counts=Counter();self.u.hook_add(UC_HOOK_CODE,self.code)
 def va(self,a):return a
 def word(self,p):return struct.unpack('<I',self.u.mem_read(p,4))[0]
 def point(self,p):return struct.unpack('<hh',self.u.mem_read(p,4))
 def ret(self,n,value=0):
  u=self.u;sp=u.reg_read(UC_X86_REG_ESP);target=self.word(sp);u.reg_write(UC_X86_REG_ESP,sp+4+n);u.reg_write(UC_X86_REG_EAX,value&0xffffffff);u.reg_write(UC_X86_REG_EIP,target)
 def cell_id(self,p):
  if p==FALLBACK:return 7
  assert CELLS<=p<CELLS+7*0x200 and (p-CELLS)%0x200==0;return (p-CELLS)//0x200
 def object_id(self,p):assert OBJECTS<=p<OBJECTS+16*0x200 and (p-OBJECTS)%0x200==0;return (p-OBJECTS)//0x200
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  assert a in (0x6328f0,DISCOVER) or any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected Cell visibility discovery instruction',hex(a))
  if a in RANGES:self.counts[hex(a)]+=1
  sp=u.reg_read(UC_X86_REG_ESP);ecx=u.reg_read(UC_X86_REG_ECX)
  if a==0x568573:
   cell=u.reg_read(UC_X86_REG_ESI);p=self.point(cell+0x24);cid=self.cell_id(cell);self.events.extend(('C',str(p[0]),str(p[1]),str(cid),'L',str(cid),str(struct.unpack('<b',u.mem_read(cell+0x11b,1))[0])))
  elif a==0x6328f0:
   p=self.point(self.word(sp+4));self.events.extend(('N',str(p[0]),str(p[1])));self.counts['supplied.notify']+=1;self.ret(4)
  elif a==0x5d4e40:self.events.extend(('P',str(self.object_id(ecx))))
  elif a==DISCOVER:
   self.events.extend(('D',str(self.object_id(ecx)),str(struct.unpack('<i',struct.pack('<I',self.word(sp+4)))[0])));self.counts['supplied.DiscoveredBy']+=1;self.ret(4,1)
 def run(self,f):
  u=self.u;u.mem_write(ARENA,b'\xa5'*SIZE);u.mem_write(SLOTS,bytes(0x100000));u.mem_write(FALLBACK,b'\xa5'*0x148);u.mem_write(START,b'\xa5'*0x148)
  self.put(0x832618,SLOTS);self.put(VT+0x48,0x5d4e40);self.put(VT+0x180,DISCOVER);put16(u,START+0x24,f['sx']);put16(u,START+0x26,f['sy'])
  records=f['records']
  for i,q in enumerate(records):
   cell=FALLBACK if i==7 else CELLS+i*0x200
   if i<7:
    put16(u,cell+0x24,f['sx']+i);put16(u,cell+0x26,f['sy']+i)
    index=(f['sy']+i)*512+f['sx']+i
    if q['present']:self.put(SLOTS+index*4,cell)
   u.mem_write(cell+0x11b,struct.pack('<b',q['level']));members=[m for m in range(2) if q['members']&(1<<m)];self.put(cell+0xe4,OBJECTS+(i*2+members[0])*0x200 if members else 0)
   for pos,m in enumerate(members):
    obj=OBJECTS+(i*2+m)*0x200;self.put(obj,VT);u.mem_write(obj+0x14,bytes([(q['active']>>m)&1]));self.put(obj+0x30,OBJECTS+(i*2+members[pos+1])*0x200 if pos+1<len(members) else 0)
    xyz=(q['bx'],q['by'],0) if m else (q['ax'],q['ay'],0);u.mem_write(obj+0x88,struct.pack('<iii',*xyz))
  before_slots=bytes(u.mem_read(SLOTS,0x100000));before_cells=bytes(u.mem_read(CELLS,7*0x200));before_objects=bytes(u.mem_read(OBJECTS,16*0x200));before_fallback=bytearray(u.mem_read(FALLBACK,0x148));self.events=[];self.active=True
  try:self.checked_call(0x568520,[START,f['house']&0xffffffff,f['notify']],0x8324e0,writes=[(FALLBACK+0x24,4)],inputs=[*RANGES.items(),(SLOTS,0x100000),(CELLS,7*0x200),(OBJECTS,16*0x200),(VT,0x184),(START,0x148),(0x832618,4)])
  finally:self.active=False
  assert bytes(u.mem_read(SLOTS,0x100000))==before_slots and bytes(u.mem_read(CELLS,7*0x200))==before_cells and bytes(u.mem_read(OBJECTS,16*0x200))==before_objects
  after=bytearray(u.mem_read(FALLBACK,0x148));after[0x24:0x28]=before_fallback[0x24:0x28];assert after==before_fallback
  self.events.append('R');return self.events
