# SPDX-License-Identifier: GPL-3.0-or-later
"""Unmodified complete Trigger roots; only action dispatcher effects supplied."""
import struct
from collections import Counter
from original_presentation import PresentationOracle,STOP,STACK
from verify_mission_trigger import verify,RANGES,TABLES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_EIP,UC_X86_REG_ESP
ARENA=0x2800000;SIZE=0x10000;TRIGGER=ARENA;TYPES=[ARENA+0x100,ARENA+0x200]
COUNTRIES=[ARENA+0x400,ARENA+0x600];EVENTS=ARENA+0x1000;ACTIONS=ARENA+0x4000
HOUSE_LIST=ARENA+0x5000;OBJECTS=[0,ARENA+0x9000,ARENA+0x9100]
def signed(v):return v if v<2**31 else v-2**32
class MissionTriggerOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True)
  self.u.mem_map(ARENA,SIZE);self.active=False;self.counts=Counter();self.stores=Counter()
  self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.store)
 def va(self,a):return a
 def word(self,p):return int.from_bytes(self.u.mem_read(p,4),'little')
 def house_id(self,p):return self.houses.index(p) if p else -1
 def supplied_write(self,p,v,n=4):
  raw=(v&((1<<(n*8))-1)).to_bytes(n,'little');self.u.mem_write(p,raw);self.expected[p-ARENA:p-ARENA+n]=raw
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  if a==0x6adae0:
   sp=u.reg_read(UC_X86_REG_ESP);ret,house,owner,trigger,loc=struct.unpack('<6I',u.mem_read(sp,24))[:5]
   # Four arguments, original thiscall ret16. The Cell pointer refers to the
   # FireActions caller's saved by-value argument, not an actor coordinate.
   assert ret==0x6ed87a and trigger==TRIGGER and loc==STACK+8
   ptr=u.reg_read(UC_X86_REG_ECX);index=(ptr-ACTIONS)//0x80;assert ptr==ACTIONS+0x80*index and 0<=index<len(self.actions)
   link,result,mode=self.actions[index];self.trace.extend(map(str,('A',index,self.house_id(house),OBJECTS.index(owner),self.word(loc))))
   if mode==1:self.supplied_write(TRIGGER+0x40,0,1);self.supplied_write(TRIGGER+0x2c,255,1)
   if mode==2:
    self.supplied_write(TRIGGER+0x24,TYPES[1]);link=len(self.actions)-1 if index+1<len(self.actions) else -1
    self.actions[index][0]=link;self.supplied_write(ptr+0x28,ACTIONS+link*0x80 if link>=0 else 0)
   if mode==3:u.mem_write(loc,struct.pack('<I',self.word(loc)^0x8001ffff))
   if mode==4:self.supplied_write(TRIGGER+0x40,0,1)
   if mode==5:self.supplied_write(TYPES[0]+0xa4,COUNTRIES[1])
   u.reg_write(UC_X86_REG_EAX,0xdead0000|result);u.reg_write(UC_X86_REG_ESP,sp+20);u.reg_write(UC_X86_REG_EIP,ret)
   self.counts['supplied_action']+=1;return
  assert any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),('Uninspected trigger instruction',hex(a))
  if a in RANGES:self.counts[hex(a)]+=1
  if a==0x4ed760:self.trace.extend(('H',str(signed(u.reg_read(UC_X86_REG_ECX)))))
  if a==0x4ed78c:self.trace.extend(('I',str(self.house_id(u.reg_read(UC_X86_REG_EAX)))))
  if a==0x6e6050:
   pulse,house,owner,timer,persistent,source=struct.unpack('<6I',u.mem_read(u.reg_read(UC_X86_REG_ESP)+4,24))
   assert timer==TRIGGER+0x30 and persistent==STACK+16
   event=u.reg_read(UC_X86_REG_ECX);index=(event-EVENTS)//0x80;assert event==EVENTS+index*0x80
   self.trace.extend(map(str,('E',index,signed(pulse),self.house_id(house),OBJECTS.index(owner),self.word(persistent),OBJECTS.index(source))))
  if a==0x6ed680:
   sp=u.reg_read(UC_X86_REG_ESP);self.counts['padding_'+hex(self.word(sp-8))]+=1
 def store(self,u,access,p,n,v,_):
  if not self.active or not ARENA<=p<ARENA+SIZE:return
  pc=u.reg_read(UC_X86_REG_EIP)
  offset={0x6ed6b1:0x30,0x6ed6ba:0x34,0x6ed6bf:0x38,0x6ed6d0:0x3c,0x6ed7ed:0x3c}.get(pc)
  assert offset is not None and n==4 and p==TRIGGER+offset,('Unexpected trigger store',hex(pc),hex(p),n)
  self.expected[p-ARENA:p-ARENA+n]=struct.pack('<I',v&0xffffffff);self.trace.extend(map(str,('W',offset,v&0xffffffff)));self.stores[hex(pc)]+=1
 def run(self,f):
  u=self.u;u.mem_write(ARENA,b'\xa5'*SIZE);self.trace=[];self.actions=[list(a) for a in f['actions']]
  for p,v in ((TRIGGER+0x24,TYPES[0]),(TRIGGER+0x30,f['start']),(TRIGGER+0x34,f['padding']),
              (TRIGGER+0x38,f['remaining']),(TRIGGER+0x3c,f['mask'])):self.put(p,v)
  u.mem_write(TRIGGER+0x2c,bytes([f['destroyed']]));u.mem_write(TRIGGER+0x40,bytes([f['enabled']]))
  for i,t in enumerate(TYPES):
   self.put(t+0xa4,COUNTRIES[i]);self.put(COUNTRIES[i]+0xb4,f['countries'][i])
   self.put(t+0xac,EVENTS if f['events'] else 0);self.put(t+0xb0,ACTIONS if self.actions else 0)
  for i,(kind,value,link) in enumerate(f['events']):
   p=EVENTS+i*0x80;self.put(p+0x2c,kind);self.put(p+0x34,value);self.put(p+0x28,EVENTS+link*0x80 if link>=0 else 0)
  for i,(link,result,mode) in enumerate(self.actions):self.put(ACTIONS+i*0x80+0x28,ACTIONS+link*0x80 if link>=0 else 0)
  self.houses=[ARENA+0x5100+i*0x100 for i in range(len(f['houses']))]
  for i,(ptr,index) in enumerate(zip(self.houses,f['houses'])):
   self.put(HOUSE_LIST+i*4,ptr);self.put(ptr+0x34,ARENA+0x7000+i*0x100);self.put(ARENA+0x7000+i*0x100+0xb8,index)
  self.put(0xa3229c,HOUSE_LIST);self.put(0xa322a8,len(self.houses));self.expected=bytearray(u.mem_read(ARENA,SIZE))
  for op,frame,suppress,a,b,c,d,e in f['operations']:
   self.put(0xa40d2c,frame);u.mem_write(0xa40d13,bytes([suppress]));u.mem_write(STACK-0x100,b'\xa5'*0x100)
   self.put(STACK-8 if op==0 else STACK-28,f['scratch']);self.trace.extend(('O',str(op)))
   if op==0:root=0x6ed680;args=[]
   elif op==1:root=0x6ed740;args=[a,OBJECTS[b],c,d,OBJECTS[e]]
   else:root=0x6ed830;args=[OBJECTS[a],b]
   self.active=True
   try:self.checked_call(root,args,TRIGGER,writes=[(TRIGGER+0x30,16)],
     inputs=[*RANGES.items(),*TABLES.items(),(0xa40d2c,4),(0xa40d13,1),(0xa3229c,4),(0xa322a8,4)])
   finally:self.active=False
   assert bytes(u.mem_read(ARENA,SIZE))==self.expected,'Unexpected complete trigger arena change'
   self.trace.extend(('R','reset' if op==0 else str(u.reg_read(UC_X86_REG_EAX)&255)))
  self.trace.extend(map(str,('state',u.mem_read(TRIGGER+0x40,1)[0],u.mem_read(TRIGGER+0x2c,1)[0],self.word(TRIGGER+0x3c),
    signed(self.word(TRIGGER+0x30)),signed(self.word(TRIGGER+0x34)),signed(self.word(TRIGGER+0x38)),TYPES.index(self.word(TRIGGER+0x24)),COUNTRIES.index(self.word(TYPES[0]+0xa4)),
    *(a[0] for a in self.actions))))
  return self.trace
