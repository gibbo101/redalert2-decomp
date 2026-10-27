# SPDX-License-Identifier: GPL-3.0-or-later
"""Unmodified base reveal-area parent with supplied startup tables/effects."""
import struct
from collections import Counter
from original_presentation import PresentationOracle,STOP
from verify_reveal_area import verify,RANGES,TABLES
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_EBX,UC_X86_REG_ECX,UC_X86_REG_EDX,UC_X86_REG_EIP,UC_X86_REG_ESP,UC_X86_REG_ESI

ARENA=0x3400000;SIZE=0x240000;MAP=ARENA;RULES=ARENA+0x1000;CURRENT=ARENA+0x3000;OTHER=ARENA+0x9000;COUNTRY=ARENA+0xf000
PRIMARY=ARENA+0x20000;SECONDARY=ARENA+0x120000;CELLS=ARENA+0x220000;POINT=ARENA+0x23f000
FALLBACK=0xa6f9f8
def signed(v):return v if v<2**31 else v-2**32
def point(raw):return struct.unpack('<hh',raw)
class RevealAreaOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(ARENA,SIZE);self.active=False;self.counts=Counter();self.u.hook_add(UC_HOOK_CODE,self.code)
 def va(self,a):return a
 def word(self,p):return struct.unpack('<I',self.u.mem_read(p,4))[0]
 def ret(self,n,value=0):
  u=self.u;sp=u.reg_read(UC_X86_REG_ESP);target=self.word(sp);u.reg_write(UC_X86_REG_ESP,sp+4+n);u.reg_write(UC_X86_REG_EAX,value&0xffffffff);u.reg_write(UC_X86_REG_EIP,target)
 def cid(self,p):
  if p==FALLBACK:return 16
  assert CELLS<=p<CELLS+16*0x200 and (p-CELLS)%0x200==0;return (p-CELLS)//0x200
 def hid(self,p):assert p in (CURRENT,OTHER);return 1 if p==CURRENT else 2
 def p(self,address):return point(self.u.mem_read(address,4))
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  sp=u.reg_read(UC_X86_REG_ESP);ecx=u.reg_read(UC_X86_REG_ECX)
  if a==0x4e5540:
   assert ecx==OTHER and self.word(sp+4)==CURRENT;self.trace.extend(('A','2',str(self.f['predicate'])));self.counts['supplied.housePredicate']+=1;self.ret(4,self.f['predicate']);return
  if a in (0x49a0f0,0x62fca0):
   p=self.p(self.word(sp+4));house=self.hid(self.word(sp+8))
   if a==0x49a0f0:self.trace.extend(('F',str(p[0]),str(p[1]),str(house)));self.counts['supplied.fog49A0F0']+=1;self.ret(8)
   else:self.trace.extend(('R',str(p[0]),str(p[1]),str(house),str(self.word(sp+12))));self.counts['supplied.reveal62FCA0']+=1;self.ret(12)
   return
  assert any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected reveal-area instruction',hex(a))
  if a in RANGES:self.counts[hex(a)]+=1
  if a==0x6a29ab:self.trace.extend(('H',str(signed(u.reg_read(UC_X86_REG_EAX)))))
  elif a==0x54a413:self.trace.extend(('D',str(struct.unpack('<h',struct.pack('<H',u.reg_read(UC_X86_REG_EAX)&0xffff))[0])))
  elif a==0x54a44c:
   p=point(struct.pack('<I',u.reg_read(UC_X86_REG_EAX)&0xffffffff));self.trace.extend(('L','C',str(p[0]),str(p[1])))
  elif a==0x54a456:
   p=self.p(sp+0x30);self.trace.extend(('C',str(p[0]),str(p[1]),str(self.cid(u.reg_read(UC_X86_REG_ESI)))))
  elif a==0x54a4bc:
   p=point(struct.pack('<I',u.reg_read(UC_X86_REG_EAX)&0xffffffff));self.trace.extend(('L','G',str(p[0]),str(p[1])))
  elif a==0x54a4c6:
   p=self.p(sp+0x58);self.trace.extend(('G',str(p[0]),str(p[1]),str(self.cid(u.reg_read(UC_X86_REG_EAX)))))
  elif a==0x54a4e7:
   cell=u.reg_read(UC_X86_REG_ESI);old=self.word(cell+0x140);new=u.reg_read(UC_X86_REG_EDX);self.trace.extend(('W',str(self.cid(cell)),str(signed(old)),str(signed(new))))
 def fill_table(self,base,mode,rawx,rawy):
  u=self.u;u.mem_write(base,bytes(0x100000))
  if mode==2:return
  for y in range(rawy-24,rawy+25):
   for x in range(rawx-24,rawx+25):
    index=y*512+x
    if not 0<=index<262144 or (mode==1 and ((x+y)&1)):continue
    cid=(x&3)|((y&3)<<2);self.put(base+index*4,CELLS+cid*0x200)
 def run(self,f):
  self.f=f;u=self.u;u.mem_write(ARENA,b'\xa5'*SIZE);u.mem_write(FALLBACK,b'\xa5'*0x148)
  self.put(MAP+0x138,PRIMARY);self.put(MAP+0xf0,f['origin']);self.put(MAP+0xf4,f['extent']);self.put(0x832618,SECONDARY);self.put(0x839848,RULES);self.put(0xa35db4,CURRENT)
  self.put(CURRENT+0x34,COUNTRY);self.put(COUNTRY+0xb8,2);self.put(OTHER+0x5414,(1<<2) if f['allied'] else 0)
  u.mem_write(RULES+0x1432,bytes([f['rule1432']]));u.mem_write(RULES+0x142b,bytes([f['rule142b']]));u.mem_write(0xa6fc30,struct.pack('<i',f['divisor']));u.mem_write(0xabe490,struct.pack('<Q',f['scaleBits']))
  u.mem_write(POINT,struct.pack('<iii',f['x'],f['y'],f['z']))
  u.mem_write(0xa6f248,b''.join(struct.pack('<hh',*p) for p in f['offsets']));u.mem_write(0xa6ed18,b''.join(struct.pack('<hh',*p) for p in f['heightOffsets']))
  rawx=int(f['x']/256);rawy=int(f['y']/256);self.fill_table(PRIMARY,f['primaryMode'],rawx,rawy);self.fill_table(SECONDARY,f['secondaryMode'],rawx,rawy)
  for i in range(17):
   cell=FALLBACK if i==16 else CELLS+i*0x200;u.mem_write(cell+0x11b,struct.pack('<b',((f['levelSeed']+i*3)%15)-7));self.put(cell+0x12c,8 if ((f['flagsSeed']+i)&1) else 0);self.put(cell+0x140,(f['flagsSeed']+i*17)&0xff)
  before=bytearray(u.mem_read(ARENA,SIZE));before_fallback=bytearray(u.mem_read(FALLBACK,0x148));self.trace=[];self.active=True
  writes=[(0xa6fa1c,4)]+[(CELLS+i*0x200+0x140,4) for i in range(16)]+[(FALLBACK+0x140,4)]
  inputs=[*RANGES.items(),*TABLES.items(),(0x832618,4),(0x839848,4),(0xa35db4,4),(0xa6fc30,4),(0xabe490,8),(0xa6f248,len(f['offsets'])*4),(0xa6ed18,len(f['heightOffsets'])*4),(MAP,0x200),(RULES,0x2000),(CURRENT,0x6000),(OTHER,0x6000),(COUNTRY,0x1000),(PRIMARY,0x100000),(SECONDARY,0x100000),(POINT,12)]
  for i in range(16):inputs.extend(((CELLS+i*0x200,0x140),(CELLS+i*0x200+0x144,0xbc)))
  inputs.extend(((FALLBACK,0x24),(FALLBACK+0x28,0x118),(FALLBACK+0x144,4)))
  house=(0,CURRENT,OTHER)[f['house']]
  try:self.checked_call(0x54a110,[POINT,f['range']&0xffffffff,house,f['trim'],f['unused'],f['fog'],f['heightCheck'],f['child']],MAP,writes=writes,inputs=inputs)
  finally:self.active=False
  after=bytearray(u.mem_read(ARENA,SIZE));after_fallback=bytearray(u.mem_read(FALLBACK,0x148))
  for p,n in writes:
   if ARENA<=p<ARENA+SIZE:before[p-ARENA:p-ARENA+n]=after[p-ARENA:p-ARENA+n]
  before_fallback[0x24:0x28]=after_fallback[0x24:0x28];before_fallback[0x140:0x144]=after_fallback[0x140:0x144]
  assert after==before and after_fallback==before_fallback
  self.trace.append('S')
  for i in range(17):self.trace.append(str(signed(self.word((FALLBACK if i==16 else CELLS+i*0x200)+0x140))))
  self.trace.extend(map(str,self.p(FALLBACK+0x24)));return self.trace
