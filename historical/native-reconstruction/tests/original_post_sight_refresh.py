# SPDX-License-Identifier: GPL-3.0-or-later
"""Unmodified complete base post-sight parent with supplied mask/redraw children."""
import struct
from collections import Counter
from original_presentation import PresentationOracle,STOP
from verify_post_sight_refresh import verify,RANGES,COUNTS
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_EBX,UC_X86_REG_ECX,UC_X86_REG_EDX,UC_X86_REG_EIP,UC_X86_REG_ESP
ARENA=0x3900000;SIZE=0x140000;MAP=ARENA;TABLE=ARENA+0x10000;CELLS=ARENA+0x120000;POINT=ARENA+0x13f000
FALLBACK=0xa6f9f8;FALLBACK_POINT=0xa6fa1c;OFFSETS=0xa6f248;SCALE=0xabe490
def signed(v):return v if v<2**31 else v-2**32
def point(raw):return struct.unpack('<hh',raw)
class PostSightRefreshOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(ARENA,SIZE);self.active=False;self.counts=Counter();self.u.hook_add(UC_HOOK_CODE,self.code)
 def va(self,a):return a
 def word(self,p):return struct.unpack('<I',self.u.mem_read(p,4))[0]
 def p(self,address):return point(self.u.mem_read(address,4))
 def cid(self,p):
  if p==FALLBACK:return 16
  assert CELLS<=p<CELLS+16*0x200 and (p-CELLS)%0x200==0;return (p-CELLS)//0x200
 def ret(self,n,value=0):
  u=self.u;sp=u.reg_read(UC_X86_REG_ESP);u.reg_write(UC_X86_REG_EIP,self.word(sp));u.reg_write(UC_X86_REG_ESP,sp+4+n);u.reg_write(UC_X86_REG_EAX,value&0xffffffff)
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  sp=u.reg_read(UC_X86_REG_ESP)
  if a==0x6a8d40:
   q=self.p(self.word(sp+4));value=(self.f['maskSeed']+q[0]*3+q[1]*5)&255;self.trace.extend(('M',str(q[0]),str(q[1]),str(value)));self.counts['supplied.mask6A8D40']+=1;self.ret(8,value);return
  if a==0x6aadd0:
   cell=self.word(sp+4);self.trace.extend(('D',str(self.cid(cell))));self.counts['supplied.redraw6AADD0']+=1;self.ret(4);return
  assert any(start<=a and a+n<=start+size for start,size in RANGES.items()),('Uninspected post-sight instruction',hex(a))
  if a in RANGES:self.counts[hex(a)]+=1
  if a==0x6a29ab:self.trace.extend(('H',str(signed(u.reg_read(UC_X86_REG_EAX)))))
  elif a==0x54a6bf:
   q=point(struct.pack('<I',u.reg_read(UC_X86_REG_EDX)&0xffffffff));self.trace.extend(('F',str(q[0]),str(q[1])))
  elif a==0x54a6ca:
   q=self.p(sp+0x24);self.trace.extend(('L',str(q[0]),str(q[1]),str(self.cid(u.reg_read(UC_X86_REG_EBX)))))
  elif a==0x54a6e4:self.trace.extend(('P',str(self.cid(u.reg_read(UC_X86_REG_EBX))),str(u.reg_read(UC_X86_REG_EAX)&255)))
  elif a==0x54a6ea:self.trace.extend(('B',str(self.cid(u.reg_read(UC_X86_REG_EBX))),'1'))
 def fill_table(self,mode,rawx,rawy):
  self.u.mem_write(TABLE,bytes(0x100000))
  if mode==2:return
  for y in range(rawy-32,rawy+33):
   for x in range(rawx-32,rawx+33):
    index=y*512+x
    if not 0<=index<262144 or (mode==1 and ((x+y)&1)):continue
    self.put(TABLE+index*4,CELLS+((x&3)|((y&3)<<2))*0x200)
 def run(self,f):
  self.f=f;u=self.u;u.mem_write(ARENA,b'\xa5'*SIZE);u.mem_write(FALLBACK,b'\xa5'*0x148);self.put(MAP+0x138,TABLE);self.put(0x83996c,MAP)
  u.mem_write(POINT,struct.pack('<iii',f['x'],f['y'],f['z']));u.mem_write(OFFSETS,b''.join(struct.pack('<hh',*q) for q in f['offsets']));u.mem_write(SCALE,struct.pack('<Q',f['scaleBits']))
  self.fill_table(f['mode'],int(f['x']/256),int(f['y']/256))
  for i in range(17):
   cell=FALLBACK if i==16 else CELLS+i*0x200;u.mem_write(cell+0x120,bytes([(f['primarySeed']+i*17)&255]));u.mem_write(cell+0x138,bytes([(f['primarySeed']+i)&1]))
  self.trace=[];self.active=True
  writes=[(FALLBACK_POINT,4)]+[(CELLS+i*0x200+0x120,1) for i in range(16)]+[(CELLS+i*0x200+0x138,1) for i in range(16)]+[(FALLBACK+0x120,1),(FALLBACK+0x138,1)]
  inputs=[*RANGES.items(),COUNTS,(OFFSETS,len(f['offsets'])*4),(SCALE,8),(0x83996c,4),(MAP,0x200),(TABLE,0x100000),(POINT,12)]
  for i in range(16):
   cell=CELLS+i*0x200;inputs.extend(((cell,0x120),(cell+0x121,0x17),(cell+0x139,0xc7)))
  inputs.extend(((FALLBACK,0x24),(FALLBACK+0x28,0xf8),(FALLBACK+0x121,0x17),(FALLBACK+0x139,0xf)))
  try:self.checked_call(0x54a550,[POINT,f['inner'],f['outer'],f['disabled']],MAP,writes=writes,inputs=inputs)
  finally:self.active=False
  self.trace.append('S')
  for i in range(17):
   cell=FALLBACK if i==16 else CELLS+i*0x200;self.trace.extend((str(u.mem_read(cell+0x120,1)[0]),str(u.mem_read(cell+0x138,1)[0])))
  self.trace.extend(map(str,self.p(FALLBACK_POINT)));return self.trace
