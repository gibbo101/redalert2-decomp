# SPDX-License-Identifier: GPL-3.0-or-later
"""Two actual actor addresses, shared type indexes and global staging in one guest.

Final-world/shadow drawing and height/visibility remain supplied observations.
No actor record is copied to the other actor's address for execution.
"""
import hashlib,struct
from original_unit_voxel_staging import UnitVoxelStagingOracle,WORLD,CELL,INDEXES
from original_foot_voxel_staging import FootVoxelStagingOracle,TYPE,LOCO,POOL_OBJ,CAPACITY,RASTER
from original_voxel_part import ACTOR,VT,HVA,TRANSFORMS,STAGE,V2C0,V2C4,PREDICATE,ADJUST
from original_voxel_part_staging import CONVERTER,DEST,SOURCE
from original_voxel_snapshot import POOL,SCRATCH
from original_foot_lit import words,ints,signed,ret
from unicorn import UC_HOOK_MEM_WRITE,UC_HOOK_MEM_READ
from unicorn.x86_const import UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EIP
SECOND=0x4100000
SUBJECTS=(ACTOR,SECOND)
DRIVES=(LOCO,SECOND+0x4000)
class SharedUnitStagingOracle(UnitVoxelStagingOracle):
 def __init__(self,*args):
  self.subject=None;self.identity=None;self.shared_calls=0;self.selected_writes=0;self.part_calls=0
  super().__init__(*args);self.u.mem_map(SECOND,0x10000)
  self.cache_owners={};self.cross_actor_hits=0;self.warm_shortcuts=0;self.cold_transforms=0
 def reset_shared(self,seed):
  self.begin_unit(seed)
  self.cache_owners={}
  self.u.mem_write(TYPE,bytes(0xc00));self.u.mem_write(VT,bytes(self.u.mem_read(0x7addf8,0x600)))
  for off,target in ((0xc0,PREDICATE),(0x3d0,ADJUST),(0x2c0,V2C0),(0x2c4,V2C4)):self.put(VT+off,target)
  self.u.mem_write(SECOND,bytes(0x10000))
  for actor,drive in zip(SUBJECTS,DRIVES):
   self.u.mem_write(actor,bytes(0x1000));self.u.mem_write(drive,bytes(0x100))
   for off,value in ((0,VT),(0x5ac,TYPE),(0x154,-1),(0x564,drive+4)):self.put(actor+off,value)
   self.put(drive+4,0x7a04cc);self.put(drive+12,actor)
  for p,value in ((TYPE+0x5a4,1),(HVA+4,1),(HVA+8,1),(HVA+12,TRANSFORMS),
    (0x83995c,WORLD),(0xad0604,STAGE),(0xad0608,CONVERTER),(0xa35db4,0x2468)):self.put(p,value)
  self.u.mem_write(TYPE+0xaab,b'\1');self.house=self.predicate=self.adjusted=0;self.c0=-1;self.c4=2
  ident=(1,0,0,0,0,1,0,0,0,0,1,0)
  for p in (TRANSFORMS,0x839a70,0xaf8608):self.u.mem_write(p,struct.pack('<12f',*ident))
  self.u.mem_write(0xad04e0,struct.pack('<d',.09375));self.u.mem_write(0xad0490,bytes(16))
  self.u.mem_write(self.va(0xadc068),self.vpl[784:]);self.put(self.va(0xade070),0);self.put(self.va(0xade074),1);self.put(self.va(0x7e35d0),1)
  self.u.mem_write(RASTER+65536,bytes(2));self.surface(STAGE,256,256,1,DEST);self.surface(SOURCE,256,256,1,RASTER)
  self.put(0x839c6c,0);self.put(0x8315b4,0);self.put(0xb2b624,0)
  angle=words(self.u,self.va(0x785cf0),1)[0]
  self.checked_call(0x70ca10,[angle],writes=[(self.va(0x821d80),12),(self.va(0x821dcc),16)])
 def set_actor(self,identity,v):
  body,turret,pitch,x,y,z=v;actor=SUBJECTS[identity]
  for off,heading in ((0x2e0,body),(0x2f8,turret),(0x2c8,pitch)):
   self.u.mem_write(actor+off,struct.pack('<IIiiiI',heading,heading,0,0,0,0))
  self.u.mem_write(actor+0x88,struct.pack('<3i',x,y,z))
 def q(self,k):self.observed.extend(['q',k,self.identity])
 def service(self,u,a,n,ctx):
  if self.unit_mode:
   ecx=u.reg_read(UC_X86_REG_ECX);sp=u.reg_read(UC_X86_REG_ESP);arg=lambda i:words(u,sp+4+4*i,1)[0]
   if a==0x6ff690:assert ecx==self.subject;self.shared_calls+=1
   if a==0x6ffbd2:self.warm_shortcuts+=1
   if a==0x6ffbf8:self.cold_transforms+=1
   if a==0x6d8ce0:
    assert ecx==self.subject and arg(0)==0x2468;self.q('V');ret(u,4,1);return
   if a in (0x4a0050,0x4a0500):
    # These COM slots pass their interface pointer on the stack. ECX still
    # contains a dispatch temporary and is not the Drive's this pointer.
    assert arg(0)==DRIVES[self.identity]+4,(hex(a),hex(arg(0)),hex(DRIVES[self.identity]+4))
    self.q('B' if a==0x4a0050 else 'S')
   if a==0x6d83e0:self.q('M')
   if a==0x6d79d0 and 0x6ff690<=words(u,sp,1)[0]<0x7005a5:self.q('L')
   if a==0x41b390 and 0x6ff690<=words(u,sp,1)[0]<0x7005a5:self.q('T')
   if a==0x5d4810:
    assert ecx==self.subject
    if 0x6ff690<=words(u,sp,1)[0]<0x7005a5:self.q('H')
    ret(u,0,0);return
   if a==0x548000:
    assert ecx==0x8324e0 and bytes(u.mem_read(arg(0),12))==bytes(u.mem_read(self.subject+0x88,12))
    self.q('C');self.observed.extend(ints(u,arg(0),3));ret(u,4,CELL);return
   if a==0x4cce70:
    assert ecx==self.subject;self.q('P');ret(u,0,self.shadow_predicate);return
   if a==0x4c9880:
    assert ecx==self.subject and words(u,0x83995c,1)==[STAGE] and u.mem_read(ecx+0x5bb,1)==b'\1'
    v=words(u,sp+4,9);part=(v[0]-TYPE-0xb0)//8;assert part in range(3) and v[3]==INDEXES[part]
    self.current_part=(part,signed(v[2]))
    self.observed.extend(['part',self.identity,part,signed(v[2]),*words(u,v[6],12)]);self.part_calls+=1
   if a==0x6ff3e0:
    assert ecx==self.subject and words(u,0x83995c,1)==[STAGE] and u.mem_read(ecx+0x5bb,1)==b'\1'
    v=words(u,sp+4,8);assert v[0]==WORLD
    self.observed.extend(['final',self.identity,*map(signed,v[1:]),*self.stage()]);ret(u,32);return
   if a==0x6d21e0:
    assert ecx==self.subject and words(u,0x83995c,1)==[WORLD] and u.mem_read(ecx+0x5bb,1)==b'\0'
    v=words(u,sp+4,11);assert v[0]==TYPE+0xb0 and v[1]==0 and v[3]==TYPE+0x23c and v[7]==1 and v[9:]==[0,0]
    self.observed.extend(['shadow',self.identity,signed(v[2]),*ints(u,v[4],4),*ints(u,v[5],2),*words(u,v[6],12),int(v[8]==STAGE),*self.stage()]);ret(u,44);return
   if a in (0x6d6df0,0x6d6e00,0x70a2d0):
    assert ecx==self.subject;return # Execute actual flag/kind leaves.
   if a in (PREDICATE,ADJUST,V2C0,V2C4):
    assert ecx==self.subject
    ret(u,4 if a==ADJUST else 0,{PREDICATE:self.predicate,ADJUST:self.adjusted,V2C0:self.c0,V2C4:self.c4}[a]);return
   if a in (0x70a350,0x70a3f0):assert ecx in INDEXES[1:]
   if a==0x69a1d0:self.cache_owners[self.current_part]=self.identity
   if a==0x6d29d0 and self.cache_owners.get(self.current_part,self.identity)!=self.identity:self.cross_actor_hits+=1
  # Skip only the old single-actor Unit service layer. All cache/raster/heap/
  # selector/encoder guards and actual instructions remain enabled below it.
  FootVoxelStagingOracle.service(self,u,a,n,ctx)
 def writes(self,u,access,a,n,value,ctx):
  # The raster and Fill produce many unrelated pixel writes. Only these three
  # storage classes need the caller-PC test; the independent whole-call write
  # audit still checks every write, including all pixels and heap/index records.
  if not self.unit_mode or not (a==0x83995c or a==self.subject+0x5bb or 0xad0490<=a<0xad04a0):return
  pc=u.reg_read(UC_X86_REG_EIP)
  if self.unit_mode and 0x6ff690<=pc<0x7005a5:
   value&=(1<<(8*n))-1
   if a==0x83995c:
    assert n==4 and value in (STAGE,WORLD);self.observed.extend(['w','s',int(value==STAGE)]);self.selected_writes+=1
   elif a==self.subject+0x5bb:
    assert n==1;self.observed.extend(['w','f',value]);self.selected_writes+=1
   elif 0xad0490<=a<0xad04a0:
    assert n==4 and (a-0xad0490)%4==0
    self.observed.extend(['w',str((a-0xad0490)//4),signed(value)]);self.selected_writes+=1
 def draw_actor(self,identity,v):
  gate,disabled,valid,barrel,frame,brightness,self.shadow_predicate,camera,template,x,y,bx,by,bw,bh=v
  self.identity=identity;self.subject=SUBJECTS[identity]
  for p,value in ((self.subject+0x430,frame),(0x839a58,gate)):self.put(p,value)
  self.u.mem_write(TYPE+0xb5a,bytes([disabled]));self.u.mem_write(0xad0478,struct.pack('<4i',*((0,0,0,0),(9,11,13,15),(248,249,24,23))[template]))
  for part,off in enumerate((0xb0,0xb8,0xc0)):
   present=bool(valid&(1<<part)) and (part!=2 or barrel)
   self.put(TYPE+off,self.models[part] if present else 0);self.put(TYPE+off+4,HVA if part!=2 or barrel else 0)
  matrix=(1,0,0,0,0,1,0,0,0,0,1,0) if not camera else (.5,.25,-.5,.125,-.25,.5,.25,-.25,.25,-.5,.5,.5)
  self.u.mem_write(0xaf77a8,struct.pack('<12f',*matrix))
  outputs=[(self.va(p),size) for p,size in ((0x7e35d0,4),(0xab84d0,65548),(0xac8710,8),(0xac8838,12),
    (0xac8848,136),(0xacaa50,20),(0xacae68,65536),(0xae0470,48),(0xae0870,256))]
  entries=[words(self.u,p,1)[0] for p in INDEXES];cursor=words(self.u,POOL_OBJ+8,1)[0]-POOL
  immutable=[(p,n) for p,n in self.allocations if p not in entries]
  self.observed=[];self.events=[];self.cache_active=self.active=self.foot_mode=self.unit_mode=True
  guards=[self.u.hook_add(UC_HOOK_MEM_WRITE,self.guarded_heap_write),self.u.hook_add(UC_HOOK_MEM_READ,self.guard_source),self.u.hook_add(UC_HOOK_MEM_WRITE,self.writes)]
  actors_before=[bytes(self.u.mem_read(p,0x1000)) for p in SUBJECTS];type_before=bytearray(self.u.mem_read(TYPE,0xc00))
  actor_inputs=[(p,0x5bb) for p in SUBJECTS]+[(p+0x5bc,0x1000-0x5bc) for p in SUBJECTS]+[(SUBJECTS[1-identity]+0x5bb,1),
    (SECOND+0x1000,0xf000),*[(p,0x100) for p in DRIVES]]
  try:self.checked_call(0x6ff690,[x,y,bx,by,bw,bh,brightness],self.subject,
   writes=[*outputs,(DEST,65536),(STAGE+12,4),(SOURCE+12,4),(CONVERTER+0x17c,4),(0xad0490,16),(0x83995c,4),
    (self.subject+0x5bb,1),(POOL_OBJ+8,4),(POOL+cursor,CAPACITY-cursor),(SCRATCH,16384),*[(p,20) for p in INDEXES],(0x1300000,0x300000)],
   inputs=[*actor_inputs,(VT,0x600),(HVA,32),(TRANSFORMS,48),(STAGE,12),(STAGE+16,12),(SOURCE,12),(SOURCE+16,12),
    (POOL_OBJ,8),(POOL,cursor),*immutable])
  finally:
   self.cache_active=self.active=self.foot_mode=self.unit_mode=False
   for g in guards:self.u.hook_del(g)
  assert all(bytes(self.u.mem_read(p,0x1000))==old for p,old in zip(SUBJECTS,actors_before))
  after=bytearray(self.u.mem_read(TYPE,0xc00))
  for p in INDEXES:after[p-TYPE:p-TYPE+20]=type_before[p-TYPE:p-TYPE+20]
  assert after==type_before;self.check_heap()
  assert words(self.u,STAGE+12,1)==words(self.u,SOURCE+12,1)==[0] and words(self.u,0x83995c,1)==[WORLD]
  assert bytes(self.u.mem_read(POOL+CAPACITY,32))==b'\xa5'*32
  data=bytearray(self.u.mem_read(POOL,CAPACITY))
  for off in self.snapshot_offsets:struct.pack_into('<I',data,off+8,words(self.u,POOL+off+8,1)[0]-POOL)
  result=[*self.observed,'after',*self.stage(),'actors',*[self.u.mem_read(p+0x5bb,1)[0] for p in SUBJECTS],
    'pool',words(self.u,POOL_OBJ+8,1)[0]-POOL,hashlib.sha256(data).hexdigest()]
  for p in INDEXES:
   pointer,count,capacity=words(self.u,p,3);hot=words(self.u,p+16,1)[0]
   result.extend(['index',count,capacity,self.u.mem_read(p+12,1)[0],ints(self.u,hot,1)[0] if hot else 'None',*[ints(self.u,pointer+i*8,1)[0] for i in range(count)]])
  self.subject=self.identity=None
  return result
