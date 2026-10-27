# SPDX-License-Identifier: GPL-3.0-or-later
"""Unmodified Object pointer-expiration callback with Tag subjects."""
from collections import Counter
from original_presentation import PresentationOracle
from verify_mission_tag_object_expiration import verify,RANGES
from unicorn import UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EIP
ARENA=0x2c00000;SIZE=0x1000;OBJECT=ARENA;TAGS=(ARENA+0x100,ARENA+0x200)
def signed(v):return v if v<2**31 else v-2**32
class MissionTagObjectExpirationOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(ARENA,SIZE);self.counts=Counter();self.stores=Counter()
 def va(self,a):return a
 def word(self,p):return int.from_bytes(self.u.mem_read(p,4),'little')
 def identity(self,p):return 0 if not p else 20 if p==OBJECT else 10+TAGS.index(p)
 def run(self,f):
  u=self.u;u.mem_write(ARENA,b'\xa5'*SIZE);trace=[];tag=lambda i:0 if not i else TAGS[i-1]
  for i,t in enumerate(TAGS):self.put(t+0x2c,f['instances'][i]);self.put(t+0x30,tag(f['next']))
  self.put(OBJECT+0x34,tag(f['object_tag']));self.put(OBJECT+0x30,tag(f['object_link']))
  expected=bytearray(u.mem_read(ARENA,SIZE))
  def store(u,access,p,n,value,_):
   if not ARENA<=p<p+n<=ARENA+SIZE:return
   pc=u.reg_read(UC_X86_REG_EIP);v=value&0xffffffff;self.stores[hex(pc)]+=1
   if p in (TAGS[0]+0x2c,TAGS[1]+0x2c):assert pc==0x5d3be4 and n==4;trace.extend(('W',str(self.identity(p-0x2c)),'44',str(v)))
   elif p==OBJECT+0x34:assert pc==0x5d3be7 and n==4;trace.extend(('W','20','52','0'))
   elif p==OBJECT+0x30:assert pc==0x5d3c05 and n==4;trace.extend(('W','20','48',str(self.identity(v))))
   else:raise AssertionError(('Unexpected Object expiration store',hex(pc),hex(p),n))
   expected[p-ARENA:p-ARENA+n]=v.to_bytes(n,'little')
  hook=u.hook_add(UC_HOOK_MEM_WRITE,store)
  try:
   for removed in f['operations']:
    trace.append('O');self.checked_call(0x5d3bd0,[tag(f['subject']),removed],OBJECT,writes=[(ARENA,SIZE)],inputs=list(RANGES.items()));self.counts['0x5d3bd0']+=1;trace.append('R')
    assert bytes(u.mem_read(ARENA,SIZE))==expected
  finally:u.hook_del(hook)
  trace.extend(('state',str(signed(self.word(TAGS[0]+0x2c))),str(signed(self.word(TAGS[1]+0x2c))),str(self.identity(self.word(OBJECT+0x34))),str(self.identity(self.word(OBJECT+0x30)))))
  return trace
