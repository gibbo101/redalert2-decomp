# SPDX-License-Identifier: GPL-3.0-or-later
"""Unmodified Building coordinates and mixed closest-resident execution."""
import struct
from collections import Counter
from original_presentation import PresentationOracle,STOP,OUT,ARG
from verify_building_coordinates import verify,RANGES,TABLES
from original_foot_lit import ret
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_ESI
ARENA=0x3200000;ACTORS=[ARENA,ARENA+0x2000];TYPE=ARENA+0x4000;CELL=ARENA+0x6000;SLOTS=ARENA+0x10000;FALLBACK=0xa6f9f8
class BuildingCoordinatesOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(ARENA,0x110000);self.active=False;self.counts=Counter();self.u.hook_add(UC_HOOK_CODE,self.code)
 def va(self,a):return a
 def word(self,p):return struct.unpack('<I',self.u.mem_read(p,4))[0]
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  assert a in (0x448fe0,0x6c2440) or any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected Building coordinates',hex(a))
  if a in RANGES:self.counts[hex(a)]+=1
  if a==0x568573:
   cell=u.reg_read(UC_X86_REG_ESI);point=struct.unpack('<hh',u.mem_read(cell+0x24,4));cid=0 if cell==CELL else -1
   self.events+=['C',*map(str,point),str(cid),'L',str(cid),str(struct.unpack('<b',u.mem_read(cell+0x11b,1))[0])]
  elif a in (0x448fe0,0x6c2440):
   actor=ACTORS.index(u.reg_read(UC_X86_REG_ECX));self.events+=['D',str(actor),str(self.word(u.reg_read(UC_X86_REG_ESP)+4))];self.counts['supplied.discovery']+=1;ret(u,4,1);return

  if a in (0x444080,0x5d4e40):self.events+=['P',str(ACTORS.index(u.reg_read(UC_X86_REG_ECX)))]
  elif a==0x458930:self.events+=['W']
  elif a==0x458940:self.events+=['H',str(self.word(u.reg_read(UC_X86_REG_ESP)+4)&255)]
 def run(self,f):
  u=self.u;u.mem_write(ARENA,b'\xa5'*0x8000);u.mem_write(OUT,b'\xa7'*12);self.events=[]
  self.put(ACTORS[0],0x7a3540);self.put(ACTORS[1],0x79cbbc);self.put(ACTORS[1]+0x418,TYPE)
  self.put(TYPE+0xc78,f['index']);u.mem_write(TYPE+0x1214,bytes([f['extra']]))
  for p,xyz in zip(ACTORS,(f['common'],f['point'])):u.mem_write(p+0x88,struct.pack('<iii',*xyz))
  for i,p in enumerate(ACTORS):u.mem_write(p+0x14,bytes([f['flags'][i]]));self.put(p+0x30,ACTORS[1] if i==0 else 0)
  self.put(CELL+0x24,9|(11<<16));u.mem_write(CELL+0x11b,b'\x00');self.put(CELL+0xe4,ACTORS[0]);self.put(CELL+0xe8,ACTORS[1]);u.mem_write(ARG,struct.pack('<ii',*f['query']))
  op=f['op'];extra_inputs=[];extra_writes=[]
  if op=='V':
   u.mem_write(SLOTS,bytes(0x100000));self.put(SLOTS+(11*512+9)*4,CELL);self.put(0x832618,SLOTS)
   u.mem_write(FALLBACK,b'\xa5'*0x148);u.mem_write(FALLBACK+0x11b,b'\x7f')
   extra_inputs=[(SLOTS,0x100000),(0x832618,4),*[(vt+0x180,4) for vt in (0x79cbbc,0x7a3540)]];extra_writes=[(FALLBACK+0x24,4)]
  root={'C':0x444080,'H':0x458940,'W':0x458930,'R':0x471660,'V':0x568520}[op]
  args={'C':[OUT],'H':[f['include']],'W':[],'R':[ARG,f['elevated'],0 if f['ignore']==-1 else ACTORS[f['ignore']]],'V':[CELL,17,0]}[op]
  ecx=0x8324e0 if op=='V' else CELL if op=='R' else TYPE if op in ('H','W') else ACTORS[1]
  def stores(u,access,p,n,v,_):
   if p==FALLBACK+0x24:assert op=='V' and n==4;self.events+=['F',*map(str,struct.unpack('<hh',struct.pack('<I',v&0xffffffff)))]
   if OUT<=p<OUT+12:assert op=='C' and n==4;self.events+=['O',str(p-OUT),str(v&0xffffffff)]
  hook=u.hook_add(UC_HOOK_MEM_WRITE,stores);self.active=True
  try:self.checked_call(root,args,ecx,writes=([(OUT,12)] if op=='C' else [])+extra_writes,inputs=[*extra_inputs,*RANGES.items(),*TABLES.items(),(ARENA,0x8000),(ARG,8),*[(vt+0x48,4) for vt in (0x79cbbc,0x7a3540)]])
  finally:self.active=False;u.hook_del(hook)
  value=u.reg_read(UC_X86_REG_EAX)
  if op=='C':assert value==OUT;self.events+=['R',*map(str,struct.unpack('<iii',u.mem_read(OUT,12)))]
  elif op=='V':self.events+=['R']
  elif op=='R':self.events+=['R',str(-1 if value==0 else ACTORS.index(value))]
  else:self.events+=['R',str(struct.unpack('<i',struct.pack('<I',value))[0])]
  return self.events
