# SPDX-License-Identifier: GPL-3.0-or-later
"""Hash-pinned source constructor, immediate update and terrain factory decisions."""
import hashlib,struct
from original_map_light import MapLightOracle
from static_light_profiles import address
from original_presentation import OBJ,ARG,STACK,STOP
from unicorn import UC_HOOK_CODE, UC_HOOK_MEM_WRITE
from unicorn.x86_const import *

class StaticLightOracle(MapLightOracle):
 def __init__(self,exe,*,allow_patched=False):
  super().__init__(exe,allow_patched=allow_patched);self.u.mem_map(0x2000000,0x1000000)
  self.visits=[];self.services={};self.factory_record=None
  self.u.hook_add(UC_HOOK_CODE,self.service)
 def va(self,disc_va):return address(self.profile,disc_va)
 def audit_write(self,u,access,p,n,value,ctx):
  allowed=getattr(self,'static_writes',())
  if any(lo<=p and p+n<=hi for lo,hi in allowed):return
  if getattr(self,'allow_cell_writes',False) and 0x2100000<=p and p+n<=0x2100000+len(self.cells)*0x200:
   offset=(p-0x2100000)%0x200
   if (offset,n)==(0x34,4) or 0x104<=offset and offset+n<=0x116:return
  raise AssertionError(f'Unexpected static-light write {p:#x}/{n}')
 def checked_static(self,disc_va,args=(),ecx=0,edx=0,*,writes=(),inputs=(),cells=False):
  end=STACK+4+len(args)*4;guard=bytes([0xa7])*64
  self.u.mem_write(end,guard)
  before=[bytes(self.u.mem_read(p,n)) for p,n in inputs]
  preserved={UC_X86_REG_EBX:0x12345678,UC_X86_REG_ESI:0x23456789,
             UC_X86_REG_EDI:0x3456789a,UC_X86_REG_EBP:0x456789ab}
  for reg,value in preserved.items():self.u.reg_write(reg,value)
  self.static_writes=[(STACK-0x2000,STACK),(STACK+4,end),*[(p,p+n) for p,n in writes]]
  self.allow_cell_writes=cells
  hook=self.u.hook_add(UC_HOOK_MEM_WRITE,self.audit_write)
  try:self.call(self.va(disc_va),args,ecx,edx,budget=12000000)
  finally:self.u.hook_del(hook);self.allow_cell_writes=False
  if self.u.reg_read(UC_X86_REG_ESP)!=end or bytes(self.u.mem_read(STACK,4))!=struct.pack('<I',STOP):
   raise AssertionError('Static-light caller ESP/return changed')
  if bytes(self.u.mem_read(end,64))!=guard:raise AssertionError('Static-light caller stack changed')
  if any(self.u.reg_read(reg)!=value for reg,value in preserved.items()):raise AssertionError('Static-light callee-saved register changed')
  if any(bytes(self.u.mem_read(p,n))!=old for (p,n),old in zip(inputs,before)):raise AssertionError('Static-light input changed')
  self.audit_calls+=1
 def cell_inputs(self):
  scenario=OBJ+0x1000
  return [(scenario,0x22c8),(0x2000000,512*512*4),
          (self.va(0x81a938),4),*[(self.va(p),n) for p,n in
           [(0xa255a0,4),(0xa39554,1),(0xa3955c,4),(0xa2874c,4),(0x7ca258,1),
            (0xa5642c,4),(0xa56430,4),(0xa56438,4)]],(OBJ+0x5000,4)]
 def service(self,u,a,n,ctx):
  if a==self.va(0x478cf0):
   cell=u.reg_read(UC_X86_REG_ECX)
   self.visits.append(struct.unpack('<2h',u.mem_read(cell+0x24,4)))
   return # Execute the complete original cell installation routine.
  if a==self.va(0x5276a0) and getattr(self,'factory_running',False):return
  if a not in (self.va(0x5276a0),self.va(0x4dfee0),self.va(0x76d5a7),self.va(0x5368f0)):return
  sp=u.reg_read(UC_X86_REG_ESP);args=struct.unpack('<10I',u.mem_read(sp+4,40));value=0;pop=0
  self.services[hex(a)]=self.services.get(hex(a),0)+1
  if a==self.va(0x5276a0):
   # Null converter factory for cell installation isolates numeric field writes;
   # its full factory decisions are tested independently by factory().
   pop=4
  elif a==self.va(0x4dfee0):pop=4 # Record-only map redraw notification, not original renderer.
  elif a==self.va(0x76d5a7):value=OBJ+0x10000 if args[0]==0x4c else 0x2080200
  elif a==self.va(0x5368f0):
   self.factory_record=[args[3],args[4],args[5],args[8]]
   value=u.reg_read(UC_X86_REG_ECX);pop=36
  u.reg_write(UC_X86_REG_EAX,value);u.reg_write(UC_X86_REG_EIP,struct.unpack('<I',u.mem_read(sp,4))[0]);u.reg_write(UC_X86_REG_ESP,sp+4+pop)
 def type_value(self,v):
  self.u.ctl_remove_cache(self.va(0x4b9f30),self.va(0x4b9fa0))
  self.u.mem_write(STACK,struct.pack('<Id',STOP,v));self.u.reg_write(UC_X86_REG_ESP,STACK)
  for reg,value in [(UC_X86_REG_FPCW,0xe7f),(UC_X86_REG_FPSW,0),(UC_X86_REG_FPTAG,0xffff)]:self.u.reg_write(reg,value)
  before=bytes(self.u.mem_read(STACK,12));guard=bytes([0xa7])*64;self.u.mem_write(STACK+12,guard)
  self.static_writes=[(STACK-0x2000,STACK)];self.allow_cell_writes=False
  hook=self.u.hook_add(UC_HOOK_MEM_WRITE,self.audit_write)
  try:
   self.u.emu_start(self.va(0x4b9f30),self.va(0x4b9f34),count=10)
   if self.u.reg_read(UC_X86_REG_EIP)!=self.va(0x4b9f34):raise AssertionError('Type numeric input load did not stop')
   self.u.emu_start(self.va(0x45a1d0),self.va(0x45a1e1),count=100)
   if self.u.reg_read(UC_X86_REG_EIP)!=self.va(0x45a1e1):raise AssertionError('Type numeric block did not stop')
  finally:self.u.hook_del(hook)
  if self.u.reg_read(UC_X86_REG_ESP)!=STACK or bytes(self.u.mem_read(STACK,12))!=before or bytes(self.u.mem_read(STACK+12,64))!=guard:
   raise AssertionError('Type numeric input/caller stack changed')
  self.audit_blocks+=2
  return struct.unpack('<i',struct.pack('<I',self.u.reg_read(UC_X86_REG_EAX)))[0]
 def construct(self,type_values,position):
  radius,intensity,*tint=type_values;source=OBJ+0x10000
  self.put(self.va(0xa5642c),OBJ+0x5000);self.put(self.va(0xa56430),1);self.put(self.va(0xa56438),0)
  self.u.mem_write(source,bytes(0x4c));self.checked_static(0x5352d0,[*position,radius,intensity,*tint],source,
   writes=[(source,0x4c),(self.va(0xa56438),4),(OBJ+0x5000,4)],
   inputs=[(self.va(0xa5642c),8),(self.va(0xa5643c),4)])
  assert self.u.reg_read(UC_X86_REG_EAX)==source
  assert struct.unpack('<I',self.u.mem_read(self.va(0xa56438),4))[0]==1
  assert struct.unpack('<I',self.u.mem_read(OBJ+0x5000,4))[0]==source
  return self.source_fields()
 def source_fields(self):
  return [*struct.unpack('<9i',self.u.mem_read(OBJ+0x10024,36)),self.u.mem_read(OBJ+0x10048,1)[0]]
 def prepare_cells(self,settings,cells,detail,enabled):
  self.u.mem_write(0x2000000,bytes(512*512*4));self.put(self.va(0x81a938),0x2000000)
  scenario=OBJ+0x1000;self.put(self.va(0xa255a0),scenario)
  for off,v in zip([0x22ac,0x22b4,0x22b8,0x22bc,0x22c0,0x22c4],settings):self.put(scenario+off,v)
  self.u.mem_write(self.va(0xa39554),b'\0');self.put(self.va(0xa3955c),0);self.put(self.va(0xa2874c),detail)
  self.u.mem_write(self.va(0x7ca258),bytes([enabled]));self.put(self.va(0xa56468),0);self.visits=[]
  self.cells=cells
  for i,(x,y,z) in enumerate(cells):
   cell=0x2100000+i*0x200;self.u.mem_write(cell,bytes(0x200))
   self.u.mem_write(cell+0x24,struct.pack('<2h',x,y));self.u.mem_write(cell+0x11b,bytes([z]))
   self.u.mem_write(cell+0x104,struct.pack('<I7h',65536,0,1000,1000,1000,1000,1000,1000))
   if 0<=x<512 and 0<=y<512:self.put(0x2000000+(y*512+x)*4,cell)
 def update(self,type_values,position,settings,cells,initial,active,detail,enabled):
  self.prepare_cells(settings,cells,detail,enabled);self.construct(type_values,position)
  self.u.mem_write(OBJ+0x10048,bytes([initial]))
  self.checked_static(0x5355d0 if active else 0x5355f0,[0],OBJ+0x10000,
   writes=[(OBJ+0x10048,1)],inputs=[(OBJ+0x10000,0x48),(OBJ+0x10049,3),*self.cell_inputs()],cells=True)
  return self.result()
 def building(self,type_values,position,settings,cells,detail):
  self.prepare_cells(settings,cells,detail,True)
  source=OBJ+0x10000;actor=0x2f00000;kind=0x2f01000
  self.u.mem_write(source,bytes(0x4c))
  self.put(self.va(0xa5642c),OBJ+0x5000);self.put(self.va(0xa56430),1);self.put(self.va(0xa56438),0)
  self.u.mem_write(actor,bytes(0x800));self.u.mem_write(kind,bytes(0x1400))
  self.put(actor,self.va(0x787bbc));self.put(actor+0x418,kind)
  self.u.mem_write(actor+0x88,struct.pack('<3i',*position))
  for off,v in zip([0xbc8,0xbcc,0xbd0,0xbd4,0xbd8],type_values):self.put(kind+off,v)
  # Foundation index 0 is the original 1x1 entry. Full original coordinate
  # getter and both dimension helpers execute, not fixture coordinate math.
  self.put(kind+0xc78,0)
  self.u.reg_write(UC_X86_REG_EBP,actor);self.u.reg_write(UC_X86_REG_ESP,STACK)
  self.u.reg_write(UC_X86_REG_FPCW,0xe7f)
  guard=bytes([0xa7])*64;self.u.mem_write(STACK+0x40,guard)
  inputs=[(actor,0x4e8),(actor+0x4ec,0x800-0x4ec),(kind,0x1400),*self.cell_inputs()]
  # The registry count and first slot are outputs of successful source creation.
  inputs=[(p,n) for p,n in inputs if p not in (self.va(0xa56438),OBJ+0x5000)]
  before=[bytes(self.u.mem_read(p,n)) for p,n in inputs]
  self.static_writes=[(STACK-0x2000,STACK+0x40),(source,source+0x4c),
                      (actor+0x4e8,actor+0x4ec),(self.va(0xa56438),self.va(0xa56438)+4),(OBJ+0x5000,OBJ+0x5004)]
  self.allow_cell_writes=True
  hook=self.u.hook_add(UC_HOOK_MEM_WRITE,self.audit_write)
  try:self.u.emu_start(self.va(0x442b3f),self.va(0x442bd6),count=12000000)
  finally:self.u.hook_del(hook);self.allow_cell_writes=False
  if self.u.reg_read(UC_X86_REG_EIP)!=self.va(0x442bd6) or self.u.reg_read(UC_X86_REG_ESP)!=STACK:
   raise AssertionError('Building source block did not restore its frame')
  if bytes(self.u.mem_read(STACK+0x40,64))!=guard:raise AssertionError('Building source block caller changed')
  for (p,n),old in zip(inputs,before):
   if bytes(self.u.mem_read(p,n))!=old:raise AssertionError(f'Building source block input changed {p:#x}/{n}')
  self.audit_blocks+=1
  assert struct.unpack('<I',self.u.mem_read(actor+0x4e8,4))[0]==(source if type_values[1] else 0)
  assert struct.unpack('<I',self.u.mem_read(self.va(0xa56438),4))[0]==int(type_values[1]!=0)
  return self.result()
 def result(self):
  rows=[]
  for i in range(len(self.cells)):
   rows.extend(struct.unpack('<I7h',self.u.mem_read(0x2100104+i*0x200,18)))
  fields=hashlib.sha256(struct.pack('<'+'i'*len(rows),*rows)).hexdigest()
  visits=hashlib.sha256(b''.join(struct.pack('<2i',*p) for p in self.visits)).hexdigest()
  return [*self.source_fields(),len(self.visits),visits,fields]
 def factory(self,tint,detail):
  # Execute the full ordinary terrain factory. Neutral pool entry, successful
  # allocation and LightConvert construction are explicit storage fixtures.
  # Its clamp/mask, lookup, shade-count choice and registration run unchanged.
  self.put(self.va(0xa2874c),detail);self.put(self.va(0x821c70),1)
  self.put(self.va(0x81a6bc),0x2080000);self.put(self.va(0x81a6c0),8);self.put(self.va(0x81a6c8),1)
  self.put(0x2080000,0x2080100)
  for off in (0x198,0x19c,0x1a0):self.put(0x2080100+off,1000)
  self.factory_record=None
  # The service callback is guarded by a flag for this complete factory call.
  self.factory_running=True
  try:self.checked_static(0x5276a0,[tint[2]],tint[0],tint[1],
   writes=[(self.va(0x81a6c8),4),(0x2080004,4)],
   inputs=[(0x2080100,0x1b4),(self.va(0x81a6bc),8),(self.va(0xa2874c),4),(self.va(0x821c70),4)])
  finally:self.factory_running=False
  return self.factory_record or [1000,1000,1000,53]
