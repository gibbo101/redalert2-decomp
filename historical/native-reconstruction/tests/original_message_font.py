# SPDX-License-Identifier: GPL-3.0-or-later
"""Actual original font metrics without replaced children or instructions."""
import struct
from collections import Counter
from original_presentation import PresentationOracle,STOP
from verify_message_font import verify,RANGES,TABLES
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_EDX,UC_X86_REG_ESI,UC_X86_REG_EDI
ARENA=0x3700000;SIZE=0x40000;PRIMARY=ARENA+0x100;FONT=ARENA+0x200;TEXT=ARENA+0x1000;INDICES=ARENA+0x10000;OUT=ARENA+0x30000;GLYPHS=ARENA+0x32000;FALLBACK=ARENA+0x34000
def signed(v):return v if v<2**31 else v-2**32
class MessageFontOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(ARENA,SIZE);self.active=False;self.counts=Counter();self.u.hook_add(UC_HOOK_CODE,self.code)
 def va(self,a):return a
 def word(self,p):return struct.unpack('<I',self.u.mem_read(p,4))[0]
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  assert any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected font instruction',hex(a))
  if a in RANGES:self.counts[hex(a)]+=1
  if a in (0x431574,0x43176e):
   code=u.reg_read(UC_X86_REG_EDI if a==0x431574 else UC_X86_REG_ESI);index=struct.unpack('<H',u.mem_read(INDICES+code*2,2))[0];self.trace.extend(('I',str(code),str(index)))
  if a in (0x431599,0x431793):
   address=u.reg_read(UC_X86_REG_EAX)
   if address==FALLBACK:self.trace.extend(('F','1',str(u.mem_read(address,1)[0])))
   else:self.trace.extend(('G',str(address),str(u.mem_read(address,1)[0])))
  if a in (0x431595,0x43178f) and not u.reg_read(UC_X86_REG_EAX):self.trace.extend(('F','0','0'))
  if a in (0x43162f,0x43163d,0x431650,0x43165a):
   kind='W' if a in (0x43162f,0x43165a) else 'H';value=u.reg_read(UC_X86_REG_ECX if a==0x43162f else UC_X86_REG_EDX);self.trace.extend((kind,str(value),'0'))
 def run(self,f):
  u=self.u;u.mem_write(ARENA,b'\xa5'*SIZE);u.mem_write(INDICES,bytes(131072));self.put(FONT+4,PRIMARY if f['present'] else 0);self.put(FONT+8,FALLBACK if f['fallback']>=0 else 0)
  u.mem_write(FALLBACK,bytes([f['fallback']&255]));self.put(FONT+0x1c,f['line']);self.put(FONT+0x28,f['tab']);self.put(FONT+0x2c,f['spacing']);self.put(PRIMARY+0x14,f['stride']);self.put(PRIMARY+0x18,INDICES);self.put(PRIMARY+0x1c,f['base'])
  for code,index,width in f['rows']:
   u.mem_write(INDICES+code*2,struct.pack('<H',index));address=(f['base']+f['stride']*(index-1))&0xffffffff if index else 0
   if address:assert GLYPHS<=address<GLYPHS+0x1000;u.mem_write(address,bytes([width]))
  u.mem_write(TEXT,f['text']+b'\0\0');self.put(OUT,0x11223344);self.put(OUT+4,0x55667788);before=bytes(u.mem_read(ARENA,SIZE));self.trace=[];self.active=True
  text=TEXT if f['hasText'] else 0;kind=f['output'];width=OUT if kind in (1,3,4) else 0;height=OUT+4 if kind in (2,3) else OUT if kind==4 else 0
  try:
   if f['op']=='M':self.checked_call(0x4314b0,[text,width,height,f['limit']],FONT,writes=list({(p,4) for p in (width,height) if p}),inputs=[*RANGES.items(),*TABLES.items()])
   elif f['op']=='W':self.checked_call(0x431690,[text,f['limit']],FONT,inputs=[*RANGES.items(),*TABLES.items()])
   else:self.checked_call(0x431710,[text,f['limit'],f['max'],f['wrap']],FONT,inputs=[*RANGES.items(),*TABLES.items()])
  finally:self.active=False
  after=bytearray(u.mem_read(ARENA,SIZE))
  if f['op']=='M':
   for p in set((width,height))-{0}:after[p-ARENA:p-ARENA+4]=before[p-ARENA:p-ARENA+4]
  assert after==before,'Original font changed input arena'
  result=u.reg_read(UC_X86_REG_EAX);result=result&255 if f['op']=='M' else signed(result)
  self.trace.extend(('R',str(result),'FW',str(signed(self.word(OUT))),'FH',str(signed(self.word(OUT+4)))));return self.trace
