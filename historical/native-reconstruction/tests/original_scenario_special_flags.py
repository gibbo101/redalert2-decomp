# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete original scenario flag parents with supplied registry and INI leaves."""
import struct
from collections import Counter
from original_presentation import PresentationOracle,STOP
from verify_scenario_special_flags import verify,RANGES,KEYS
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_EIP,UC_X86_REG_ESP
ARENA=0x3600000;SIZE=0x10000;FLAGS=ARENA;INI=ARENA+0x1000
class ScenarioSpecialFlagsOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(ARENA,SIZE);self.active=False;self.counts=Counter();self.u.hook_add(UC_HOOK_CODE,self.code)
 def va(self,a):return a
 def word(self,p):return struct.unpack('<I',self.u.mem_read(p,4))[0]
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  sp=u.reg_read(UC_X86_REG_ESP);f=self.f
  if a==0x50f410:
   ret,section,key,fallback=(self.word(sp+4*k) for k in range(4));i=self.index
   assert u.reg_read(UC_X86_REG_ECX)==INI and section==0x7f43f8 and key==KEYS[i][0]
   self.trace.extend(('B',str(i),str(fallback),str(self.word(FLAGS))))
   answer=f['answers'][i];answer=fallback if answer<0 else answer
   if i==f['mutation']:
    self.put(FLAGS,f['mutationFlags']);self.put(0xa3d298,f['mutationSession']);u.mem_write(0xa40d13,bytes([f['mutationOverride']]));self.mutated=True
    self.trace.extend(('M',str(f['mutationFlags']),str(f['mutationSession']),str(f['mutationOverride'])))
   self.index+=1;self.counts['supplied.GetBool']+=1;u.reg_write(UC_X86_REG_EAX,answer);u.reg_write(UC_X86_REG_ESP,sp+16);u.reg_write(UC_X86_REG_EIP,ret);return
  assert any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected scenario flag instruction',hex(a))
  if a in RANGES:self.counts[hex(a)]+=1
  if a==0x68b37a:
   args=[self.word(sp+4*i) for i in range(5)];assert args[:4]==[0x80000002,sp+0x34,0,0xf003f]
   assert bytes(u.mem_read(args[1],len(b'SOFTWARE\\Westwood\\Red Alert 2\\\0')))==b'SOFTWARE\\Westwood\\Red Alert 2\\\0'
   self.put(args[4],0x1234);self.trace.extend(('O',str(self.word(FLAGS))));u.reg_write(UC_X86_REG_EAX,f['open']&0xffffffff);u.reg_write(UC_X86_REG_ESP,sp+20);u.reg_write(UC_X86_REG_EIP,a+6);self.counts['supplied.RegOpen']+=1
  elif a==0x68b3a2:
   args=[self.word(sp+4*i) for i in range(6)];assert args[:3]==[0x1234,0x7f4408,0] and self.word(args[4])==0 and self.word(args[5])==4
   self.put(args[3],f['type']);self.put(args[4],f['data']);self.trace.extend(('Q',str(args[0])));u.reg_write(UC_X86_REG_EAX,f['query']&0xffffffff);u.reg_write(UC_X86_REG_ESP,sp+24);u.reg_write(UC_X86_REG_EIP,a+6);self.counts['supplied.RegQuery']+=1
  elif a==0x68b3bf:
   assert self.word(sp)==0x1234;self.trace.extend(('C',str(self.word(sp))));u.reg_write(UC_X86_REG_EAX,0xfeedbeef);u.reg_write(UC_X86_REG_ESP,sp+4);u.reg_write(UC_X86_REG_EIP,a+6);self.counts['supplied.RegClose']+=1
 def run(self,f):
  self.f=f;self.index=0;self.mutated=False;self.trace=[];u=self.u;u.mem_write(ARENA,b'\xa5'*SIZE);self.put(FLAGS,f['flags']);self.put(0xa3d298,f['session']);u.mem_write(0xa40d13,bytes([f['override']]))
  before=bytearray(u.mem_read(ARENA,SIZE));self.active=True
  inputs=[*RANGES.items(),(0x7f43f0,0xd0),(0x7f1508,10)]
  for a,key in KEYS:inputs.append((a,len(key)+1))
  try:
   if f['op']!=1:self.checked_call(0x68b320,ecx=FLAGS,writes=[(FLAGS,4)],inputs=inputs)
   if f['op']!=0:self.checked_call(0x68b5a0,[INI],FLAGS,writes=[(FLAGS,4)],inputs=inputs)
  finally:self.active=False
  after=bytearray(u.mem_read(ARENA,SIZE));before[:4]=after[:4];assert before==after
  session=f['mutationSession'] if self.mutated else f['session'];override=f['mutationOverride'] if self.mutated else f['override']
  assert self.word(0xa3d298)==session&0xffffffff and u.mem_read(0xa40d13,1)[0]==override
  self.trace.extend(('Z',str(self.word(FLAGS)),str(session),str(override)));return self.trace
