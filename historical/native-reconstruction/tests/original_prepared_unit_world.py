# SPDX-License-Identifier: GPL-3.0-or-later
"""Actual prepared map and complete lit Unit drawing in one guest, without copies."""
import hashlib,struct
from original_unit_voxel_world import (UnitVoxelWorldOracle,COLOR,ZDATA,ADATA,PAL,CVT,BLIT,ZOBJ,AOBJ,W,H,HOUSE,ARRAY,SCHEME,CONTACTS,CONTACT,CTYPE,CONTACT_VT,ZSURF,ASURF)
from original_unit_voxel_staging import UnitVoxelStagingOracle,WORLD
from original_voxel_part import ACTOR,STAGE
from original_map_preparation import (MapPreparationOracle,MAP,FALLBACK,CELLS,TYPES,REGISTRY,SLOTS,BUFF4,BUFF10)
from original_resident_map_preparation import IMAGES
from original_resident_map_floor import ResidentMapFloorOracle
from original_resident_map_finalization import OVERLAYS,OVERLAY_REG
from original_presentation import PresentationOracle,STOP
from original_foot_lit import words
from original_foot_voxel_staging import ranges
from verify_prepared_foot_depth import RANGES
from verify_prepared_unit_world import verify,LOOKUP,LOOKUP_SIZE
from unicorn import UC_HOOK_CODE,UC_HOOK_BLOCK,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_ECX,UC_X86_REG_ESP

class AttachedMap(ResidentMapFloorOracle):
 def __init__(self,owner):
  # Attach host bookkeeping and fresh disjoint arenas to the existing guest.
  # No second guest is created and no prepared records are transferred.
  self.u=owner.u;self.enabled=False;self.drawing=False;self.entries={hex(a):0 for a in RANGES}
  self.stores=self.logs=self.owner_calls=self.distances=self.buffer_stores=0;self.resource_returns=[]
  self.floor_calls=self.flag_stores=self.plane_stores=0;self.floor_samples=[];self.audit_calls=self.audit_blocks=0
  self.frames=list(self.u.mem_read(0x7d2c10,36))[::4]
  for p,n in ((CELLS,0xe00000),(IMAGES,0x400000),(OVERLAYS,0x600000)):self.u.mem_map(p,n)
  self.u.hook_add(UC_HOOK_BLOCK,self.gated_block)
  for a in {*RANGES,0x55a679,0x54b505,0x5d4c8b,0x4068f0}:self.u.hook_add(UC_HOOK_CODE,self.gated_code,begin=a,end=a)
 def gated_block(self,u,a,n,ctx):
  if self.enabled:self.block(u,a,n,ctx)
 def gated_code(self,u,a,n,ctx):
  if self.enabled:self.code(u,a,n,ctx)
  elif self.drawing and a in RANGES:self.entries[hex(a)]+=1
 def prepare(self,floor):
  self.type_count=len(floor[7]);self.overlay_count=len(floor[9]);self.enabled=True
  try:return self.run_floor(*floor)
  finally:self.enabled=False

class PreparedUnitWorldOracle(UnitVoxelWorldOracle):
 def __init__(self,exe,assets,palette):
  self.prepared=None
  super().__init__(exe,assets,palette)
  self.prepared_inspection=verify((exe.parents[1]/'disc-allied/game.exe').read_bytes(),exe.read_bytes())
  self.allowed=sorted(set(self.allowed+[(a,a+n) for a,n in RANGES.items()]+[(LOOKUP,LOOKUP+LOOKUP_SIZE)]),reverse=True)
  self.prepared=AttachedMap(self);self.prepared_calls={};self.prepared_ready=False
 def va(self,a):return a if a in RANGES or a==LOOKUP else super().va(a)
 def prepare_map(self,floor):
  self.prepared_ready=False;result=self.prepared.prepare(floor);self.prepared_ready=True
  return result
 def prepare_world(self):
  super().prepare_world()
  assert self.prepared_ready
  # Restore the actual prepared-map registry, not the synthetic old world fixture.
  for p,v in ((0xa40cd4,REGISTRY),(0xa40ce0,self.prepared.type_count),(0x8661d8,0),(MAP+0x13c,262144)):
   self.put(p,v)
  self.u.mem_write(ACTOR+0x88,struct.pack('<3i',*self.location))
  self.u.mem_write(0xabe490,struct.pack('<d',self.height_scale));self.put(0xa52f00,0)
 def checked_call(self,a,args=(),ecx=0,edx=0,*,writes=(),inputs=()):
  if a!=0x6ff690 or not self.world_mode:return super().checked_call(a,args,ecx,edx,writes=writes,inputs=inputs)
  p=self.prepared
  self.put(self.va(0x821f8c),ZOBJ);self.put(self.va(0x8198d4),AOBJ)
  writes=[*writes,(COLOR,W*H*2),(FALLBACK+0x24,4),*[(q+12,4) for q in (WORLD,ZSURF,ASURF)]]
  inputs=[*inputs,(CELLS,p.count*512),(SLOTS,0x100000),(TYPES,p.type_count*1024),(IMAGES,p.type_count*4096),(REGISTRY,p.type_count*4+64),
   (MAP+0x138,8),(OVERLAYS,p.overlay_count*1024),(OVERLAY_REG,p.overlay_count*4+64),
   (0xa35dec,4),(0xa40cd4,4),(0xa52f00,4),(0xa40d2c,4),(0xabe490,8),(0x7f7124,12),(0x851a70,32),(0xa52c74,4),(0x8661d8,4),(0xac0148,4),
   (HOUSE,0x16000),(ARRAY,4),(SCHEME,0x310),(CONTACTS,4),(CONTACT,0x500),(CTYPE,0x1360),(CONTACT_VT,0x30),
   (ZDATA,W*H*2),(ADATA,W*H*2),(PAL,53*512),(CVT,0x200),(BLIT,12),(ZOBJ,48),(AOBJ,48),(self.alpha_map,0x20008),(self.va(0x821f8c),4),(self.va(0x8198d4),4)]
  old=bytes(self.u.mem_read(FALLBACK,0x148));p.drawing=True
  try:result=PresentationOracle.checked_call(self,a,args,ecx,edx,writes=writes,inputs=inputs)
  finally:p.drawing=False
  final=bytearray(self.u.mem_read(FALLBACK,0x148));final[0x24:0x28]=old[0x24:0x28];assert bytes(final)==old
  return result
 def service(self,u,a,n,ctx):
  if self.world_mode and self.unit_mode and a in (0x548070,LOOKUP,0x52b690):
   assert any(lo<=a and a+n<=hi for lo,hi in self.allowed)
   self.prepared_calls[hex(a)]=self.prepared_calls.get(hex(a),0)+1
   sp=u.reg_read(UC_X86_REG_ESP);arg=words(u,sp+4,1)[0]
   if a==0x548070:self.map_events.extend([304,words(u,arg,1)[0]])
   elif a==LOOKUP:self.map_events.extend([405,*words(u,arg,3)])
   else:self.map_events.extend([404,(u.reg_read(UC_X86_REG_ECX)-TYPES)//1024,arg])
   # Observe only; skip old synthetic lookup/dimension replacements.
   return
  super().service(u,a,n,ctx)
 def draw_prepared(self,location,scale,v):
  assert self.prepared_ready
  x,y,_=location
  assert 0<=x<512*256 and 0<=y<512*256
  p=words(self.u,SLOTS+((y//256)*512+x//256)*4,1)[0]
  assert p and self.u.mem_read(p+0x11c,1)==b'\0','Nonflat current Drive shadow pose requires ramp-matrix initialization'
  self.location=location;self.height_scale=scale
  self.map_events=[]
  def store(u,access,p,n,value,ctx):
   if p==FALLBACK+0x24:assert n==4;self.map_events.extend([0xffffffff,0,value&0xffffffff])
  hook=self.u.hook_add(UC_HOOK_MEM_WRITE,store)
  try:result=self.draw_world(v)
  finally:self.u.hook_del(hook)
  return [*result,'queries',words(self.u,FALLBACK+0x24,1)[0],hashlib.sha256(struct.pack('<'+'I'*len(self.map_events),*self.map_events)).hexdigest()]
