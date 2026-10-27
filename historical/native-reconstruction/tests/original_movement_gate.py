# SPDX-License-Identifier: GPL-3.0-or-later
"""Unchanged complete base gate helpers, with audited actual children and writes."""
import struct
from original_presentation import PresentationOracle,STACK,STOP
from verify_movement_gate import verify,RANGES,DISPATCH
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP
ARENA=0x2600000;OBJECTS=[ARENA+i*0x1000 for i in range(5)]
TYPES=[ARENA+0x10000+i*0x2000 for i in range(5)]
HOUSES=[ARENA+0x20000+i*0x6000 for i in range(3)]
SLOTS=0x2700000;CELLS=[ARENA+0x3f000,ARENA+0x3f200,0xa6f9f8]
INPUT=ARENA+0x3f400;ARENA_SIZE=0x40000
def ptr(i):return 0 if i==-1 else OBJECTS[i]
def hid(p):return -1 if not p else HOUSES.index(p)
def oid(p):return -1 if not p else OBJECTS.index(p)
def signed(n):return n if n<0x80000000 else n-0x100000000
class MovementGateOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True)
  self.u.mem_map(ARENA,ARENA_SIZE);self.u.mem_map(SLOTS,0x100000)
  self.entries={hex(a):0 for a in RANGES};self.selected_stores=0;self.supplied_padding_stores=0
  self.kind_return_checks={1:0,6:0,36:0};self.supplied_animation_transitions=0;self.instructions=set();self.active=False;self.events=[]
  self.u.hook_add(UC_HOOK_CODE,self.code)
 def va(self,a):return a
 def event(self,*values):self.events.extend(map(str,values))
 def word(self,p):return int.from_bytes(self.u.mem_read(p,4),'little')
 def code(self,u,a,n,ctx):
  if not self.active or a==STOP:return
  assert any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()),f'Uninspected gate instruction {a:#x}/{n}'
  self.instructions.add(a)
  if a in RANGES:self.entries[hex(a)]+=1
  ecx=u.reg_read(UC_X86_REG_ECX);sp=u.reg_read(UC_X86_REG_ESP)
  if a in (0x70a2d0,0x453c40,0x6e4b00):self.event('K',oid(ecx))
  elif a in (0x70a2d5,0x453c45,0x6e4b05):
   value=u.reg_read(UC_X86_REG_EAX);id_=oid(ecx)
   assert value==self.object_kinds[id_],('Kind return differs',id_,value,self.object_kinds[id_])
   self.kind_return_checks[value]+=1;self.event('V',id_,value)
  elif a==0x4e5580:self.event('A',hid(ecx))
  elif a in (0x6c7430,0x410240):self.event('O',oid(ecx))
  elif a==0x44d7d0:self.event('G',oid(ecx))
  elif a==0x44d880:self.event('I',oid(ecx))
  elif a==0x594770:self.event('M',oid(ecx))
  elif a in (0x496ab0,0x496b50,0x496b30):self.event({0x496ab0:'B',0x496b50:'C',0x496b30:'D'}[a],oid(ecx-0x2a8))
  elif a==0x594cb0:
   assert (self.word(sp+4),self.word(sp+8))==(24,0);self.event('Q',oid(ecx))
  elif a in (0x594710,0x594c50):
   self.event('S' if a==0x594710 else 'E',oid(ecx))
   if a==0x594710:assert self.word(sp+4)==0xffffffff
   # Original copies an opaque uninitialized temporary word. Supply and count
   # it at the actual child entry, separately from original object writes.
   self.put(sp-8,self.set_padding if a==0x594710 else self.commence_padding)
   self.supplied_padding_stores+=1
 def run(self,h,houses,objects,steps):
  tick,self.set_padding,self.commence_padding,slot0,slot1,head0,head1,headf,fx,fy=h
  u=self.u;u.mem_write(ARENA,b'\xa5'*ARENA_SIZE);u.mem_write(SLOTS,bytes(0x100000));u.mem_write(CELLS[2],b'\xa5'*0x148)
  self.put(0x832618,SLOTS);self.put(0xa40d2c,tick)
  for i,slot in enumerate((slot0,slot1)):
   if slot!=-1:self.put(SLOTS+4*slot,CELLS[i])
  for cell,head in zip(CELLS,(head0,head1,headf)):
   self.put(cell+0xe4,ptr(head));self.put(cell+0xe8,ptr(4));self.put(cell+0xec,ptr(4)) # Elevated list and unrelated decoy must be ignored.
  u.mem_write(CELLS[2]+0x24,struct.pack('<hh',fx,fy))
  for p,(index,mask) in zip(HOUSES,houses):self.put(p+0x30,index);self.put(p+0x5674,mask)
  for i,(kind,next_,owner,gate,current,queued,a4,b18,b19,status,last,start,padding,remaining) in enumerate(objects):
   p=OBJECTS[i];self.put(p,{1:0x7addf8,6:0x79cbbc,36:0x7ad3cc}[kind]);self.put(p+0x30,ptr(next_))
   self.put(p+0x1b4,0 if owner==-1 else HOUSES[owner]);self.put(p+0x418,TYPES[i]);u.mem_write(TYPES[i]+0x1351,bytes([gate]))
   self.put(p+0x98,current);self.put(p+0xa0,queued);u.mem_write(p+0xa4,bytes([a4]))
   for off,value in ((0xa8,status),(0xac,last),(0xb0,start),(0xb4,padding),(0xb8,remaining)):self.put(p+off,value)
   u.mem_write(p+0x2c0,bytes([b18,b19]))
  self.events=[];self.object_kinds=[o[0] for o in objects]
  ranges=[*RANGES.items(),*[(vt+off,4) for vt,slots in DISPATCH.items() for off in slots],(0x832618,4),(0xa40d2c,4),(SLOTS,0x100000)]
  for action,a,b,c in steps:
   if action=='T':
    u.mem_write(OBJECTS[a]+0x2c0,bytes([b,c]));self.supplied_animation_transitions+=1;self.event('U',a,b,c);result=-1
   else:
    if action=='C':
     u.mem_write(INPUT,struct.pack('<hh',b,c));root,args,ecx=0x55acd0,[ptr(a),INPUT],0x8324e0
    elif action=='A':root,args,ecx=0x4e5580,[ptr(b)],HOUSES[a]
    else:root,args,ecx=(0x44d7d0 if action=='G' else 0x44d880),[],OBJECTS[a]
    before=bytes(u.mem_read(ARENA,ARENA_SIZE));fallback=bytes(u.mem_read(CELLS[2],0x148))
    permitted={}
    for p in OBJECTS:
     for off,n in ((0x98,4),(0xa0,4),(0xa4,1),(0xa8,4),(0xac,4),(0xb0,4),(0xb4,4),(0xb8,4)):permitted[p+off]=n
    def stores(u,access,p,n,v,ctx):
     if p==CELLS[2]+0x24:
      assert n==4;self.event('F',*struct.unpack('<hh',struct.pack('<I',v&0xffffffff)));self.selected_stores+=1
     elif ARENA<=p<ARENA+ARENA_SIZE:
      assert permitted.get(p)==n,(hex(p),n);i=(p-ARENA)//0x1000;self.event('W',i,p-OBJECTS[i],n,v&0xffffffff);self.selected_stores+=1
    writes=[*permitted.items(),(CELLS[2]+0x24,4)]
    hook=u.hook_add(UC_HOOK_MEM_WRITE,stores);self.active=True
    try:self.checked_call(root,args,ecx,writes=writes,inputs=ranges)
    finally:self.active=False;u.hook_del(hook)
    after=bytearray(u.mem_read(ARENA,ARENA_SIZE))
    for p,n in permitted.items():after[p-ARENA:p-ARENA+n]=before[p-ARENA:p-ARENA+n]
    assert bytes(after)==before,'Gate changed unselected arena storage'
    after=bytearray(u.mem_read(CELLS[2],0x148));after[0x24:0x28]=fallback[0x24:0x28]
    assert bytes(after)==fallback,'Gate changed unselected fallback storage'
    result=u.reg_read(UC_X86_REG_EAX)&255
   self.event('R',result,*struct.unpack('<hh',u.mem_read(CELLS[2]+0x24,4)))
   for p in OBJECTS:
    self.event(signed(self.word(p+0x98)),signed(self.word(p+0xa0)),u.mem_read(p+0xa4,1)[0],
     *[signed(self.word(p+off)) for off in (0xa8,0xac,0xb0,0xb4,0xb8)],*u.mem_read(p+0x2c0,2))
  return self.events
