# SPDX-License-Identifier: GPL-3.0-or-later
"""Unmodified original localization roots with actual CRT search/comparison."""
import struct
from collections import Counter
from original_presentation import PresentationOracle,STOP,STACK
from verify_string_lookup import verify,RANGES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_EDX,UC_X86_REG_ESP,UC_X86_REG_EBX,UC_X86_REG_ESI,UC_X86_REG_EDI,UC_X86_REG_EBP
ARENA=0x3600000;SIZE=0x10000;LABELS=ARENA+0x1000;KEY=ARENA+0x3000;TEXT=ARENA+0x5000;EXTRA=ARENA+0x6000;OUT=ARENA+0x7000
class StringLookupOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(ARENA,SIZE);self.active=False;self.counts=Counter();self.u.hook_add(UC_HOOK_CODE,self.code)
 def va(self,a):return a
 def word(self,p):return struct.unpack('<I',self.u.mem_read(p,4))[0]
 def checked_search(self,args,inputs):
  # CRT bsearch is cdecl: the caller retains all five argument slots. Keep the
  # same write/register/return/caller guards without pretending ret20 cleanup.
  u=self.u;end=STACK+4+4*len(args);guard=b'\xa7'*64;u.mem_write(end,guard)
  preserved={UC_X86_REG_EBX:0x12345678,UC_X86_REG_ESI:0x23456789,UC_X86_REG_EDI:0x3456789a,UC_X86_REG_EBP:0x456789ab}
  before=[bytes(u.mem_read(p,n)) for p,n in inputs]
  for reg,value in preserved.items():u.reg_write(reg,value)
  def audit(u,access,p,n,value,context):
   assert STACK-0x2000<=p and p+n<=STACK or STACK+4<=p and p+n<=end,('Unexpected CRT search write',hex(p),n)
  hook=u.hook_add(UC_HOOK_MEM_WRITE,audit)
  try:self.call(0x782025,args)
  finally:u.hook_del(hook)
  assert u.reg_read(UC_X86_REG_ESP)==STACK+4,'Original CRT caller ESP changed'
  assert bytes(u.mem_read(STACK,4))==struct.pack('<I',STOP) and bytes(u.mem_read(end,64))==guard,'Original CRT caller stack changed'
  assert all(u.reg_read(reg)==value for reg,value in preserved.items()),'Original CRT callee-saved register changed'
  assert all(bytes(u.mem_read(p,n))==old for (p,n),old in zip(inputs,before)),'Original CRT input changed'
  self.audit_calls+=1
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  assert any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected string lookup path',hex(a))
  if a in RANGES:self.counts[hex(a)]+=1
  sp=u.reg_read(UC_X86_REG_ESP)
  if a==0x6f9ed5:self.trace.extend(('L',str(int(bool(u.reg_read(UC_X86_REG_EAX))))))
  elif a==0x782025:self.trace.extend(('B',str(self.word(sp+12))))
  elif a==0x781f20:
   label=self.word(sp+8);assert LABELS<=label<LABELS+40*self.n and (label-LABELS)%40==0;self.trace.extend(('C',str((label-LABELS)//40)))
  elif a==0x6f9f0c:self.trace.extend(('E',str(u.reg_read(UC_X86_REG_EDX))))
  elif a==0x6f9f1c:self.trace.extend(('T',str(u.reg_read(UC_X86_REG_EAX))))
 def run(self,f):
  u=self.u;self.n=len(f['rows']);u.mem_write(ARENA,b'\xa5'*SIZE);self.put(0xad0440,LABELS if f['present'] else 0);self.put(0xad0438,self.n);self.put(0xad0444,TEXT);self.put(0xad0448,EXTRA);self.put(0xb2b098,0)
  u.mem_write(KEY,f['key']+b'\0')
  for i,(key,index,text,extra) in enumerate(f['rows']):
   u.mem_write(LABELS+i*40,bytes(40));u.mem_write(LABELS+i*40,key+b'\0');self.put(LABELS+i*40+36,index);self.put(TEXT+4*i,text);self.put(EXTRA+4*i,extra)
  self.put(OUT,0xcccccccc);kind,alias=f['outKind'],f['alias'];output=0 if kind==0 else OUT if kind==1 else LABELS+40*alias+36 if kind==2 else TEXT+4*alias if kind==3 else EXTRA+4*alias
  before=bytes(u.mem_read(ARENA,SIZE));self.trace=[];self.active=True
  def stores(u,access,p,n,v,_):
   if p==output and output:assert n==4;self.trace.extend(('O',str(v&0xffffffff)))
  hook=u.hook_add(UC_HOOK_MEM_WRITE,stores)
  try:
   if f['op']=='L':self.checked_call(0x6f9ec0,[0,0],KEY,output,writes=[(output,4)] if output else [],inputs=[*RANGES.items(),(0xad0438,20),(0xb2b098,4)])
   else:self.checked_search([KEY,LABELS,self.n,40,0x781f20],[*RANGES.items(),(0xad0438,20),(0xb2b098,4)])
  finally:self.active=False;u.hook_del(hook)
  after=bytearray(u.mem_read(ARENA,SIZE))
  if output and f['op']=='L':after[output-ARENA:output-ARENA+4]=before[output-ARENA:output-ARENA+4]
  assert after==before,'String lookup changed unselected input storage'
  result=u.reg_read(UC_X86_REG_EAX)
  if f['op']=='B':result=-1 if result==0 else (result-LABELS)//40
  self.trace.extend(('R',str(result),'F',str(self.word(output) if output else 0)))
  self.trace.extend(str(self.word(LABELS+i*40+36)) for i in range(self.n));self.trace.extend(str(self.word(TEXT+i*4)) for i in range(self.n));self.trace.extend(str(self.word(EXTRA+i*4)) for i in range(self.n));return self.trace
