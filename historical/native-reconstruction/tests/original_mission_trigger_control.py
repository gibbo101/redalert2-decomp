# SPDX-License-Identifier: GPL-3.0-or-later
"""Unmodified action53/54 dispatcher branches over supplied live owners."""
import struct
from collections import Counter
from original_presentation import PresentationOracle,STOP,STACK
from verify_mission_trigger_control import verify,RANGES,TABLES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_EIP,UC_X86_REG_ESP
ARENA=0x2c00000;SIZE=0x20000;ACTION=ARENA+0x100;SCENARIO=ARENA+0x1000
TYPES=[ARENA+0x2000,ARENA+0x3000,ARENA+0x4000];EVENT=ARENA+0x5000
TRIGGERS=[ARENA+0x8000+i*0x200 for i in range(4)];BACKING=ARENA+0xd000
def signed(v):return v if v<2**31 else v-2**32
class MissionTriggerControlOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(ARENA,SIZE);self.active=False;self.counts=Counter();self.stores=Counter()
  self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.store)
 def va(self,a):return a
 def word(self,p):return struct.unpack('<I',self.u.mem_read(p,4))[0]
 def update(self,p,raw):self.expected[p-ARENA:p-ARENA+len(raw)]=raw
 def trigger_id(self,p):
  for i,t in enumerate(TRIGGERS):
   if t<=p<t+0x200:return i,t
  return None
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  assert any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected Trigger control instruction',hex(a))
  if a in RANGES:self.counts[hex(a)]+=1
  if a==0x6ed680:
   sp=u.reg_read(UC_X86_REG_ESP);assert signed(self.word(sp-8))==self.scratch;self.counts['reset_scratch']+=1
 def store(self,u,access,p,n,value,_):
  if not self.active or not ARENA<=p<ARENA+SIZE:return
  found=self.trigger_id(p);assert found is not None,('Trigger control write owner',hex(p));i,base=found;pc=u.reg_read(UC_X86_REG_EIP)
  if p==base+0x40:assert n==1 and pc in (0x6edb60,0x6edb70);off=0x40
  else:
   off={0x6ed6b1:0x30,0x6ed6ba:0x34,0x6ed6bf:0x38,0x6ed6d0:0x3c}.get(pc);assert off is not None and n==4 and p==base+off,(hex(pc),hex(p),n)
  raw=(value&((1<<(8*n))-1)).to_bytes(n,'little');self.update(p,raw);self.trace.extend(('W',str(i),str(off),str(value&((1<<(8*n))-1))));self.stores[hex(pc)]+=1
 def run(self,f):
  u=self.u;u.mem_write(ARENA,b'\xa5'*SIZE);self.trace=[];self.scratch=f['scratch']
  u.mem_write(TYPES[0]+0x9c,bytes(f['allowed']));self.put(TYPES[0]+0xac,EVENT if f['eventMode'] else 0);self.put(TYPES[1]+0xac,0);self.put(TYPES[2]+0xac,0)
  self.put(EVENT+0x28,0);self.put(EVENT+0x2c,13);self.put(EVENT+0x34,f['timerValue'])
  for i,r in enumerate(f['records']):
   t=TRIGGERS[i];self.put(t+0x24,TYPES[r['type']-1]);u.mem_write(t+0x40,bytes([r['enabled']]))
   for off,key in ((0x30,'start'),(0x34,'padding'),(0x38,'remaining'),(0x3c,'mask')):self.put(t+off,r[key])
   self.put(BACKING+i*4,t)
  self.put(0xa40aa4,BACKING);self.put(0xa40ab0,f['count']);self.put(0xa3d290,SCENARIO);self.put(SCENARIO+0x60c,f['difficulty']);self.put(0xa40d2c,f['frame'])
  self.put(ACTION+0x2c,53 if f['op']=='E' else 54);self.put(ACTION+0x50,0 if f['targetMode']==0 else TYPES[0] if f['targetMode']==1 else TYPES[2])
  self.expected=bytearray(u.mem_read(ARENA,SIZE));u.mem_write(STACK-0x400,b'\xa5'*0x400);self.put(STACK-0x26c,f['scratch'])
  self.active=True
  try:self.checked_call(0x6adae0,[0,0,TRIGGERS[0],ACTION+0x80],ACTION,writes=[(TRIGGERS[0],0x800)],inputs=[*RANGES.items(),*TABLES.items(),(0xa40aa4,4),(0xa40ab0,4),(0xa3d290,4),(0xa40d2c,4)])
  finally:self.active=False
  assert bytes(u.mem_read(ARENA,SIZE))==self.expected
  self.trace.extend(('R',str(u.reg_read(UC_X86_REG_EAX)&255),'state',str(f['count'])))
  for i,r in enumerate(f['records']):
   t=TRIGGERS[i];self.trace.extend((str(r['type']),str(u.mem_read(t+0x40,1)[0]),str(signed(self.word(t+0x30))),str(signed(self.word(t+0x34))),str(signed(self.word(t+0x38))),str(self.word(t+0x3c))))
  return self.trace
