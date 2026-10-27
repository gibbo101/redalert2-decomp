# SPDX-License-Identifier: GPL-3.0-or-later
"""Two actual actors/Drives, one prepared map, four type indexes and world planes.

Pose records are supplied here. This does not attach Process or membership.
Neither actor is copied onto the other's address. Drawing never reinitializes
the world planes, staging image, pool or the other actor's pose.
"""
import hashlib,struct
from original_moving_unit_world import MovingUnitWorldOracle
from original_ground_unit_world import REGISTRY,MAP,PLANES
from original_map_preparation import FALLBACK
from original_unit_voxel_world import UnitVoxelWorldOracle,COLOR,ZDATA,ADATA,W,H,CVT
from original_unit_voxel_shadow_world import ALL_INDEXES
from original_shared_unit_staging import SUBJECTS,DRIVES,SECOND,SharedUnitStagingOracle
from original_foot_voxel_staging import FootVoxelStagingOracle,TYPE,POOL_OBJ,CAPACITY,RASTER
from original_voxel_part import ACTOR,VT,HVA,TRANSFORMS,STAGE
from original_voxel_part_staging import CONVERTER,DEST,SOURCE
from original_voxel_snapshot import POOL,SCRATCH
from original_unit_voxel_staging import WORLD
from original_cached_voxel_shadow import HOUSE_CONVERTER,RLE_BLIT
from original_shadow_voxel_world import RAW_BLIT
from original_foot_lit import words,ints,signed,ret
from unicorn import UC_HOOK_MEM_READ,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_ECX,UC_X86_REG_ESP
class SharedGroundWorldOracle(MovingUnitWorldOracle):
 def __init__(self,*args):
  self.subject=self.identity=None;self.shared_calls=self.selected_writes=0
  super().__init__(*args);self.u.mem_map(SECOND,0x10000)
  self.cache_owners={};self.current_part=None;self.cross_actor_hits=[0,0,0,0]
  self.warm_shortcuts=self.cold_transforms=0
  self.viewer_house=0x2468
  self.owner_house=0x2000000
 writes=SharedUnitStagingOracle.writes
 def bind_draw_associations(self):
  self.put(self.subject+0xcc,0x2030000);self.put(self.subject+0x1b4,0x2000000)
 def bind_draw_target(self,contact):
  # Historical pose-only fixtures supply both fields together. Actual-owner
  # subclasses override this boundary rather than nulling a live target.
  self.put(self.subject+0x494,contact);self.put(0x2030000,0x2030100 if contact else 0)
 def reset_shared(self,seed):
  self.begin_unit(seed);self.seed=seed;self.map_mode=self.contact_mode=0
  self.u.mem_write(TYPE,bytes(0xc00));self.u.mem_write(SECOND,bytes(0x10000))
  self.u.mem_write(VT,bytes(self.u.mem_read(0x7addf8,0x600)))
  self.world_mode=True
  try:UnitVoxelWorldOracle.prepare_world(self)
  finally:self.world_mode=False
  for p,v in ((0xa40cd4,REGISTRY),(0xa40ce0,self.prepared.type_count),(0x8661d8,0),(MAP+0x13c,262144),
   (TYPE+0x5a4,1),(0xa35db4,0x2468),(HVA+4,1),(HVA+8,1),(HVA+12,TRANSFORMS),
   (0x83995c,WORLD),(0xad0604,STAGE),(0xad0608,CONVERTER)):
   self.put(p,v)
  self.u.mem_write(TYPE+0xaab,b'\1')
  for p,v in ((TYPE+0x330,30.5),(TYPE+0x338,24.25),(0xad04e0,.09375)):self.u.mem_write(p,struct.pack('<d',v))
  for actor,drive in zip(SUBJECTS,DRIVES):
   self.u.mem_write(actor,bytes(0x1000));self.u.mem_write(drive,bytes(0x100))
   for p,v in ((actor,VT),(actor+0x5ac,TYPE),(actor+0x154,-1),(actor+0x564,drive+4),
    (drive,0x7a0594),(drive+4,0x7a04cc),(drive+8,actor),(drive+12,actor)):
    self.put(p,v)
  ident=(1,0,0,0,0,1,0,0,0,0,1,0)
  for p in (TRANSFORMS,0x839a70):self.u.mem_write(p,struct.pack('<12f',*ident))
  self.u.mem_write(0xad0490,bytes(16));self.u.mem_write(self.va(0xadc068),self.vpl[784:])
  for p,v in ((self.va(0xade070),0),(self.va(0xade074),1),(self.va(0x7e35d0),1),
   (VT+0x1cc,HOUSE_CONVERTER),(0x8323c4,CVT),(CVT+0xf0,RLE_BLIT),(CVT+0x2c,RAW_BLIT),
   (RLE_BLIT,0x79e0e0),(RLE_BLIT+4,0x7bef),(RAW_BLIT,0x79e39c),(RAW_BLIT+4,0x7bef),
   (0x839c6c,0),(0x8315b4,0),(0xb2b624,0)):self.put(p,v)
  self.u.mem_write(RASTER+65536,bytes(2))
  FootVoxelStagingOracle.surface(self,STAGE,256,256,1,DEST)
  FootVoxelStagingOracle.surface(self,SOURCE,256,256,1,RASTER)
  angle=words(self.u,self.va(0x785cf0),1)[0]
  self.checked_call(0x70ca10,[angle],writes=[(self.va(0x821d80),12),(self.va(0x821dcc),16)])
  self.cache_owners={}
 def set_actor(self,id,v):
  x,y,z,body,turret,pitch,tick,current,previous,start,padding,remaining,duration,rockx,rocky=v
  actor,drive=SUBJECTS[id],DRIVES[id]
  self.u.mem_write(actor+0x88,struct.pack('<3i',x,y,z))
  self.u.mem_write(actor+0x280,struct.pack('<2I',rockx,rocky))
  for off,heading in ((0x2e0,body),(0x2f8,turret),(0x2c8,pitch)):
   self.u.mem_write(actor+off,struct.pack('<IIiiiI',heading,heading,0,0,0,0))
  self.u.mem_write(drive+0x1c,struct.pack('<6i',current,previous,start,padding,remaining,duration))
  return ['set']
 def service(self,u,a,n,ctx):
  if self.world_mode and self.unit_mode:
   ecx=u.reg_read(UC_X86_REG_ECX);sp=u.reg_read(UC_X86_REG_ESP)
   if a==0x6ff690:assert ecx==self.subject;self.shared_calls+=1
   if a==0x6ffbd2:self.warm_shortcuts+=1
   if a==0x6ffbf8:self.cold_transforms+=1
   if a==0x6d8ce0:
    assert ecx==self.subject and words(u,sp+4,1)==[self.viewer_house];ret(u,4,1);return
   if a==0x4f52b0:
    assert ecx==self.owner_house;ret(u,0,0);return
   if a==0x4a0050:
    interface,self.body_out,self.body_key=words(u,sp+4,3)
    assert interface==DRIVES[self.identity]+4 and self.body_return is None
    self.body_return=words(u,sp,1)[0];self.map_events.extend([501]);self.body_calls+=1;return
   if a==self.body_return:
    self.body_return=None;self.observed.extend(['body',*words(u,self.body_out,12),words(u,self.body_key,1)[0]])
   if a==0x4a0500:assert words(u,sp+4,1)==[DRIVES[self.identity]+4]
   if a==0x5d4810:
    assert ecx==self.subject and self.height_return is None
    self.height_return=words(u,sp,1)[0];self.map_events.extend([502]);return
   if a==0x4cce70:assert ecx==self.subject;ret(u,0,self.shadow_predicate);return
   if a==0x4c9880:
    assert ecx==self.subject and words(u,0x83995c,1)==[STAGE] and u.mem_read(ecx+0x5bb,1)==b'\1'
    v=words(u,sp+4,9);part=(v[0]-TYPE-0xb0)//8
    assert part in range(3) and v[3]==ALL_INDEXES[part]
    self.current_part=(part,signed(v[2]));self.part_calls+=1
    self.observed.extend(['part',part,signed(v[2]),*words(u,v[6],12)])
    FootVoxelStagingOracle.service(self,u,a,n,ctx);return
   if a==0x6ff3e0:
    assert ecx==self.subject and words(u,0x83995c,1)==[STAGE] and u.mem_read(ecx+0x5bb,1)==b'\1'
    FootVoxelStagingOracle.service(self,u,a,n,ctx);return
   if a==0x6d21e0:
    assert ecx==self.subject and words(u,0x83995c,1)==[WORLD] and u.mem_read(ecx+0x5bb,1)==b'\0'
    v=words(u,sp+4,11);assert v[0]==TYPE+0xb0 and v[1]==0 and v[3]==TYPE+0x23c
    if not self.full_shadow:
     assert v[7]==1 and v[9]==0 and -1048576<=signed(v[10])<=1048576
     self.current_part=(3,signed(v[2]));self.map_events.extend([508,v[9],v[10]])
     self.shadow_return=words(u,sp,1)[0]
     self.observed.extend(['shadow',signed(v[2]),*ints(u,v[4],4),*ints(u,v[5],2),*words(u,v[6],12),int(v[8]!=0),*self.stage()])
     self.full_shadow=self.shadow_active=True
    else:assert v[9:]==[0,0]
    self.shadow_calls[hex(a)]=self.shadow_calls.get(hex(a),0)+1
    FootVoxelStagingOracle.service(self,u,a,n,ctx);return
   if a==HOUSE_CONVERTER:assert ecx==self.subject;ret(u,0,CVT);return
   if a in (0x6d6df0,0x6d6e00,0x70a2d0):assert ecx==self.subject;return
   if a==0x69a1d0:self.cache_owners[self.current_part]=self.identity
   if a==0x6d29d0 and self.cache_owners.get(self.current_part,self.identity)!=self.identity:self.cross_actor_hits[self.current_part[0]]+=1
  super().service(u,a,n,ctx)
 def draw_shared(self,id,tick,v):
  scale,contact,self.no_shadow,self.disable_shadow,gate,disabled,valid,barrel,frame,brightness,self.shadow_predicate,camera,template,x,y,bx,by,bw,bh=v
  self.identity=id;self.subject=SUBJECTS[id];self.map_events=[]
  self.height_scale=struct.unpack('<d',struct.pack('<Q',scale))[0]
  self.u.mem_write(0xabe490,struct.pack('<d',self.height_scale));self.put(0xa40d2c,tick)
  self.contact_mode=contact;self.bind_draw_associations()
  self.bind_draw_target(contact)
  self.put(self.subject+0x430,frame);self.put(0x839a58,gate)
  for off,val in ((0xb48,self.no_shadow),(0xb5b,self.disable_shadow),(0xb5a,disabled)):self.u.mem_write(TYPE+off,bytes([val]))
  for part,off in enumerate((0xb0,0xb8,0xc0)):
   present=bool(valid&(1<<part)) and (part!=2 or barrel)
   self.put(TYPE+off,self.models[part] if present else 0);self.put(TYPE+off+4,HVA if part!=2 or barrel else 0)
  self.u.mem_write(0xad0478,struct.pack('<4i',*((0,0,0,0),(9,11,13,15),(248,249,24,23))[template]))
  camera_matrix=(1,0,0,0,0,1,0,0,0,0,1,0) if not camera else (.5,.25,-.5,.125,-.25,.5,.25,-.25,.25,-.5,.5,.5)
  self.u.mem_write(0xaf77a8,struct.pack('<12f',*camera_matrix))
  outputs=[(self.va(p),size) for p,size in ((0x7e35d0,4),(0xab84d0,65548),(0xac8710,8),(0xac8838,12),
    (0xac8848,136),(0xacaa50,20),(0xacae68,65536),(0xadae68,72),(0xae0470,48),(0xae0870,256))]
  entries=[words(self.u,p,1)[0] for p in ALL_INDEXES];cursor=words(self.u,POOL_OBJ+8,1)[0]-POOL
  immutable=[(p,n) for p,n in self.allocations if p not in entries]
  self.observed=['actor',id];self.events=[];self.cache_active=self.active=self.foot_mode=self.unit_mode=self.world_mode=True
  hooks=[self.u.hook_add(UC_HOOK_MEM_WRITE,self.guarded_heap_write),self.u.hook_add(UC_HOOK_MEM_READ,self.guard_source),self.u.hook_add(UC_HOOK_MEM_WRITE,self.writes)]
  actors=[bytes(self.u.mem_read(p,0x1000)) for p in SUBJECTS];type_before=bytearray(self.u.mem_read(TYPE,0xc00))
  actor_inputs=[(p,0x5bb) for p in SUBJECTS]+[(p+0x5bc,0x1000-0x5bc) for p in SUBJECTS]+[(SUBJECTS[1-id]+0x5bb,1),
   (SECOND+0x1000,0xf000),*[(p,0x100) for p in DRIVES]]
  def fallback(u,access,p,n,value,ctx):
   if p==FALLBACK+0x24:assert n==4;self.map_events.extend([0xffffffff,0,value&0xffffffff])
  hooks.append(self.u.hook_add(UC_HOOK_MEM_WRITE,fallback))
  try:self.checked_call(0x6ff690,[x,y,bx,by,bw,bh,brightness],self.subject,
   writes=[*outputs,(DEST,65536),(STAGE+12,4),(SOURCE+12,4),(CONVERTER+0x17c,4),(0xad0490,16),(0x83995c,4),
    (self.subject+0x5bb,1),(POOL_OBJ+8,4),(POOL+cursor,CAPACITY-cursor),(SCRATCH,16384),*[(p,20) for p in ALL_INDEXES],(0x1300000,0x300000)],
   inputs=[*actor_inputs,(VT,0x600),(HVA,32),(TRANSFORMS,48),(STAGE,12),(STAGE+16,12),(SOURCE,12),(SOURCE+16,12),
    (POOL_OBJ,8),(POOL,cursor),*immutable])
  finally:
   self.cache_active=self.active=self.foot_mode=self.unit_mode=self.world_mode=False
   for hook in hooks:self.u.hook_del(hook)
  assert all(bytes(self.u.mem_read(p,0x1000))==old for p,old in zip(SUBJECTS,actors))
  after=bytearray(self.u.mem_read(TYPE,0xc00))
  for p in ALL_INDEXES:after[p-TYPE:p-TYPE+20]=type_before[p-TYPE:p-TYPE+20]
  assert after==type_before and self.body_return is self.height_return is self.shadow_return is None
  assert not self.full_shadow and not self.shadow_active and not self.in_snapshot
  self.check_heap();assert bytes(self.u.mem_read(POOL+CAPACITY,32))==b'\xa5'*32
  for p in (STAGE,SOURCE,WORLD,0x160b000,0x160b100):assert words(self.u,p+12,1)==[0]
  data=bytearray(self.u.mem_read(POOL,CAPACITY))
  for off in self.snapshot_offsets:struct.pack_into('<I',data,off+8,words(self.u,POOL+off+8,1)[0]-POOL)
  result=[*self.observed,'after',*self.stage(),'actors',*[self.u.mem_read(p+0x5bb,1)[0] for p in SUBJECTS],
   'pool',words(self.u,POOL_OBJ+8,1)[0]-POOL,hashlib.sha256(data).hexdigest()]
  for p in ALL_INDEXES:
   pointer,count,capacity=words(self.u,p,3);hot=words(self.u,p+16,1)[0]
   result.extend(['index',count,capacity,self.u.mem_read(p+12,1)[0],ints(self.u,hot,1)[0] if hot else 'None',*[ints(self.u,pointer+i*8,1)[0] for i in range(count)]])
  result.extend(['world',*[hashlib.sha256(bytes(self.u.mem_read(p,W*H*2))).hexdigest() for p in (COLOR,ZDATA,ADATA)]])
  result.extend(['queries',words(self.u,FALLBACK+0x24,1)[0],hashlib.sha256(struct.pack('<'+'I'*len(self.map_events),*self.map_events)).hexdigest()])
  state=bytes(self.u.mem_read(0x850bb8,1))+bytes(self.u.mem_read(0x850ba8,8))+bytes(self.u.mem_read(0x850bd0,8))+bytes(self.u.mem_read(PLANES,800))
  result.extend(['floor',hashlib.sha256(state).hexdigest()]);self.subject=self.identity=None
  return result
