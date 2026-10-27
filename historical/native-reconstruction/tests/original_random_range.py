# SPDX-License-Identifier: GPL-3.0-or-later
"""Execute unchanged inclusive range root, including its inlined XOR generator."""
import struct
from collections import Counter
from original_presentation import PresentationOracle,STOP
from verify_random_range import verify,RANGES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_EIP,UC_X86_REG_ECX
ARENA=0x2800000;SIZE=0x4000;STATE=ARENA+0x1000
def signed(v):return v if v<0x80000000 else v-0x100000000
class RandomRangeOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True)
  self.u.mem_map(ARENA,SIZE);self.active=False;self.counts=Counter();self.instructions=set();self.writes=Counter();self.attempts=[]
  self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.store)
 def va(self,a):return a
 def word(self,p):return int.from_bytes(self.u.mem_read(p,4),'little')
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  assert any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected random-range instruction',hex(a))
  self.instructions.add(a)
  if a==0x6388a0:
   assert u.reg_read(UC_X86_REG_ECX)==STATE;self.counts['root']+=1
  if a in (0x6388b7,0x6388ee,0x6388f3,0x6388ed,0x638945):
   self.counts[{0x6388b7:'swapped',0x6388ee:'attempt',0x6388f3:'disabled_attempt',0x6388ed:'sampled_call',0x638945:'common_add'}[a]]+=1
  if a==0x6388f7:assert 0<=self.word(STATE+4)<250 and 0<=self.word(STATE+8)<250
  if a==0x63893e:
   self.events.extend(map(str,('D',u.reg_read(UC_X86_REG_EAX),signed(self.word(STATE+4)),signed(self.word(STATE+8)))))
  if a==0x638942:
   # Actual signed comparison inputs, before the rejection branch.
   from unicorn.x86_const import UC_X86_REG_EDI
   if signed(u.reg_read(UC_X86_REG_EAX))>signed(u.reg_read(UC_X86_REG_EDI)):self.counts['rejected']+=1
 def store(self,u,access,p,n,v,_):
  if not self.active or not(ARENA<=p<ARENA+SIZE):return
  a=u.reg_read(UC_X86_REG_EIP);assert n==4
  if a==0x63890b:
   first,second=self.word(STATE+4),self.word(STATE+8)
   assert p==STATE+12+4*first and v==self.word(STATE+12+4*first)^self.word(STATE+12+4*second)
  elif a in (0x63891e,0x638921):assert p==STATE+(4 if a==0x63891e else 8) and v==self.word(p)+1
  elif a in (0x638926,0x638935):assert p==STATE+(4 if a==0x638926 else 8) and self.word(p)==250 and v==0
  else:raise AssertionError(('Unexpected RNG arena store',hex(a),hex(p),n))
  self.writes[hex(a)]+=1;self.expected[p-ARENA:p-ARENA+4]=struct.pack('<I',v&0xffffffff)
 def run(self,disabled,first,second,ranges,table):
  u=self.u;u.mem_write(ARENA,b'\xa5'*SIZE);u.mem_write(STATE,bytes([disabled])+b'\xa5'*3+struct.pack('<ii250I',first,second,*table))
  self.expected=bytearray(u.mem_read(ARENA,SIZE));self.events=[]
  for low,high in ranges:
   before=self.counts['attempt'];self.active=True
   try:self.checked_call(0x6388a0,[low,high],STATE,writes=[(STATE+4,1008)],inputs=[(STATE,4),(0x6388a0,0xad)])
   finally:self.active=False
   assert bytes(u.mem_read(ARENA,SIZE))==bytes(self.expected),'Unexpected complete random arena change'
   self.attempts.append(self.counts['attempt']-before)
   self.events.extend(('R',str(signed(u.reg_read(UC_X86_REG_EAX)))))
  self.events.extend(map(str,('state',disabled,signed(self.word(STATE+4)),signed(self.word(STATE+8)),*struct.unpack('<250I',u.mem_read(STATE+12,1000)))))
  return self.events
