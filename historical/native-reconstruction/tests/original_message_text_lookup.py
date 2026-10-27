# SPDX-License-Identifier: GPL-3.0-or-later
"""Unmodified action11 through actual color/CSF/CRT, message insertion supplied."""
import struct
from original_mission_text_action import MissionTextActionOracle,ARENA,SIZE,ACTION,SCENARIO,RULES,TEXT,encoded,signed
from original_string_lookup import StringLookupOracle,ARENA as LOOKUP,SIZE as LOOKUP_SIZE,LABELS,TEXT as SLOTS,EXTRA
from original_presentation import STOP
from verify_string_lookup import RANGES as STRING_RANGES
from verify_message_text_lookup import verify,RANGES,TABLES
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_EDX,UC_X86_REG_ESP
class MessageTextLookupOracle(MissionTextActionOracle):
 def __init__(self,exe):
  super().__init__(exe);self.inspection=verify(exe.read_bytes());self.u.mem_map(LOOKUP,LOOKUP_SIZE)
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  sp=u.reg_read(UC_X86_REG_ESP)
  if 0x6715d0<=a<0x6715f7:
   if a==0x6715d0:
    self.counts['0x6715d0']+=1
    if self.f['op']=='J':
     assert u.reg_read(UC_X86_REG_ECX)==0xa3d298
     self.trace.extend(('C',str(signed(self.word(sp+4)))))
   if a in (0x6715e5,0x6715f4) and self.f['op']=='J':self.trace.extend(('V',str(signed(u.reg_read(UC_X86_REG_EAX)))))
   return
  if any(lo<=a and a+n<=lo+size for lo,size in STRING_RANGES.items()):
   if a==0x6f9ec0:
    assert u.reg_read(UC_X86_REG_ECX)==ACTION+0x54 and u.reg_read(UC_X86_REG_EDX)==0
    self.trace.extend(('K',encoded(self.cstring(ACTION+0x54,32)),'0',str(self.word(sp+4)),str(self.word(sp+8))))
   StringLookupOracle.code(self,u,a,n,_);return
  if a==0x5b4da0:
   args=struct.unpack('<7I',u.mem_read(sp+4,28));assert u.reg_read(UC_X86_REG_ECX)==0xa3dc70 and args[2] in self.payloads
   self.trace.extend(('M',str(signed(args[0])),str(signed(args[1])),encoded(self.payloads[args[2]]),str(signed(args[3])),str(signed(args[4])),str(args[5]),str(signed(args[6]))))
   self.counts['supplied.message_insertion']+=1;self.ret(28,0xa5a5a5a5);return
  super().code(u,a,n,_)
 def run(self,f):
  self.f=f;u=self.u;u.mem_write(ARENA,b'\xa5'*SIZE);u.mem_write(LOOKUP,b'\xa5'*LOOKUP_SIZE)
  u.mem_write(0x7f3224,bytes(c&255 for c in f['colors']));self.trace=[];self.active=True
  try:
   if f['op']=='P':
    self.checked_call(0x6715d0,[f['selector']],0x87654321,inputs=[(0x6715d0,0x27),(0x7f3224,9)])
    return ['R',str(signed(u.reg_read(UC_X86_REG_EAX)))]
   self.n=len(f['rows']);self.payloads={}
   self.put(0xad0440,LABELS);self.put(0xad0438,self.n);self.put(0xad0444,SLOTS);self.put(0xad0448,EXTRA);self.put(0xb2b098,0)
   for i,(key,index,payload) in enumerate(f['rows']):
    u.mem_write(LABELS+i*40,bytes(40));u.mem_write(LABELS+i*40,key+b'\0');self.put(LABELS+i*40+36,index)
    pointer=TEXT+i*128;self.payloads[pointer]=payload;u.mem_write(pointer,payload+b'\0');self.put(SLOTS+4*i,pointer)
   u.mem_write(ACTION+0x54,bytes(32));u.mem_write(ACTION+0x54,f['key']+b'\0');self.put(ACTION+0x2c,11)
   self.put(0xa3d290,SCENARIO);u.mem_write(SCENARIO+0x2239,bytes([f['alternate']]));self.put(0x839848,RULES);u.mem_write(RULES+0x1128,struct.pack('<Q',f['delayBits']))
   before=[bytes(u.mem_read(p,n)) for p,n in ((ARENA,SIZE),(LOOKUP,LOOKUP_SIZE))]
   self.checked_call(0x6adae0,[0,0,ACTION+0xc0,ACTION+0x80],ACTION,inputs=[*RANGES.items(),*TABLES.items(),(0x7f3224,9),(0xad0438,20),(0xb2b098,4),(0x79b608,8),(0x7d8964,4),(0xa3d290,4),(0x839848,4)])
   assert [bytes(u.mem_read(p,n)) for p,n in ((ARENA,SIZE),(LOOKUP,LOOKUP_SIZE))]==before,'Joined message lookup changed arena inputs'
   self.trace.extend(('R',str(u.reg_read(UC_X86_REG_EAX)&255)));return self.trace
  finally:self.active=False
