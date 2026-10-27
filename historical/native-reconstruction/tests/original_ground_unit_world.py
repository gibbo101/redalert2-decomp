# SPDX-License-Identifier: GPL-3.0-or-later
"""Shared finalized map, initialized ramp table, actual Unit/floor/shadow children."""
import hashlib,struct
from original_unit_voxel_shadow_world import UnitVoxelShadowWorldOracle
from original_prepared_unit_world import AttachedMap,LOOKUP,LOOKUP_SIZE
from original_unit_voxel_world import (COLOR,ZDATA,ADATA,PAL,CVT,BLIT,ZOBJ,AOBJ,W,H,HOUSE,ARRAY,SCHEME,CONTACTS,CONTACT,CTYPE,CONTACT_VT,ZSURF,ASURF)
from original_cached_voxel_shadow import RLE_BLIT
from original_shadow_voxel_world import RAW_BLIT
from original_foot_voxel_staging import LOCO,TYPE,FootVoxelStagingOracle
from original_voxel_part import ACTOR
from original_unit_voxel_staging import WORLD
from original_map_preparation import MAP,FALLBACK,CELLS,TYPES,REGISTRY,SLOTS
from original_resident_map_preparation import IMAGES
from original_resident_map_finalization import OVERLAYS,OVERLAY_REG
from original_ramp_geometry import RampGeometryOracle
from verify_ramp_geometry import RANGES as GEOMETRY,CONSTANTS,TABLES
from verify_prepared_foot_depth import RANGES as PREPARED
from verify_ground_unit_world import verify,RANGES
from original_presentation import PresentationOracle
from original_foot_lit import words,ints,signed
from unicorn import UC_HOOK_MEM_WRITE,UC_HOOK_BLOCK
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP
PLANES=0x7d27e8
class AttachedGeometry:
 stock=RampGeometryOracle.stock
 def __init__(self,owner):
  self.u=owner.u;self.put=owner.put;self.checked_call=owner.checked_call
  self.inputs=list(GEOMETRY.items())+[(a,8) for a in CONSTANTS]+list(TABLES.items())+[(0xb2af94,4)]
  self.global_stores=self.matrix_stores=0;self.put(0xb2af94,0)
class GroundUnitWorldOracle(UnitVoxelShadowWorldOracle):
 def __init__(self,exe,assets,palette):
  self.prepared=None;self.ground_calls={};self.height_return=None;self.ground_ready=False
  super().__init__(exe,assets,palette)
  self.ground_inspection=verify((exe.parents[1]/'disc-allied/game.exe').read_bytes(),exe.read_bytes())
  self.allowed=sorted(set(self.allowed+[(a,a+n) for a,n in {**RANGES,**PREPARED,LOOKUP:LOOKUP_SIZE}.items()]),reverse=True)
  self.prepared=AttachedMap(self);self.numeric=AttachedGeometry(self);self.geometry_active=False
  self.u.hook_add(UC_HOOK_BLOCK,self.geometry_block)
 def geometry_block(self,u,a,n,ctx):
  if self.geometry_active and not any(lo<=a and a+n<=lo+size for lo,size in GEOMETRY.items()):
   from original_presentation import STOP
   if a!=STOP:raise AssertionError(f"Uninspected numeric initialization block {a:#x}/{n}")
 def va(self,a):return a if a in RANGES or a in PREPARED or a==LOOKUP else super().va(a)
 def prepare_map(self,floor):
  assert floor[4]==104,'Ground profile requires stock Cell height'
  self.ground_ready=False;result=self.prepared.prepare(floor);self.ground_ready=True
  return result
 def prepare_world(self):
  super().prepare_world();assert self.ground_ready
  for p,v in ((0xa40cd4,REGISTRY),(0xa40ce0,self.prepared.type_count),(0x8661d8,0),(MAP+0x13c,262144)):
   self.put(p,v)
  self.u.mem_write(ACTOR+0x88,struct.pack('<3i',*self.location))
  self.u.mem_write(0xabe490,struct.pack('<d',self.height_scale));self.put(0xa52f00,0)
  # Supplied neutral lit locomotor state. The actual stock setup runs after the
  # older fixture's flat-table write, in this same guest; no table is transferred.
  self.u.mem_write(LOCO+16,bytes(0x100-16));self.put(LOCO+0x24,-1)
  camera=bytes(self.u.mem_read(0xaf77a8,48))
  self.geometry_active=True
  try:self.numeric.stock(0)
  finally:self.geometry_active=False
  # Other initializer outputs are outside the numeric proof. Restore the
  # explicitly supplied camera used by this rendering fixture.
  self.u.mem_write(0xaf77a8,camera)
 def checked_call(self,a,args=(),ecx=0,edx=0,*,writes=(),inputs=()):
  if a!=0x6ff690 or not self.world_mode:return super().checked_call(a,args,ecx,edx,writes=writes,inputs=inputs)
  p=self.prepared;self.put(self.va(0x821f8c),ZOBJ);self.put(self.va(0x8198d4),AOBJ)
  writes=[*writes,(COLOR,W*H*2),(CVT+0x17c,4),(FALLBACK+0x24,4),(0x850bb8,1),(0x850ba8,8),(0x850bd0,8),(PLANES,800),*[(q+12,4) for q in (WORLD,ZSURF,ASURF)]]
  # Exclude mutable lazy data from immutable inputs; guard all nonselected Cell,
  # type, actor, locomotor, planes, palette and index/pool regions explicitly.
  inputs=[*inputs,(CELLS,p.count*512),(SLOTS,0x100000),(TYPES,p.type_count*1024),(IMAGES,p.type_count*4096),(REGISTRY,p.type_count*4+64),
   (MAP+0x138,8),(OVERLAYS,p.overlay_count*1024),(OVERLAY_REG,p.overlay_count*4+64),
   (0xa35dec,4),(0xa40cd4,4),(0xa52f00,4),(0xa40d2c,4),(0xabe490,8),(0x7f7124,12),(0x851a70,32),(0xa52c74,4),(0x8661d8,4),(0xac0148,4),
   (0x850c40,4),(0xaf8608,21*48),(LOCO+16,0x100-16),
   (HOUSE,0x16000),(ARRAY,4),(SCHEME,0x310),(CONTACTS,4),(CONTACT,0x500),(CTYPE,0x1360),(CONTACT_VT,0x30),
   (ZDATA,W*H*2),(ADATA,W*H*2),(PAL,53*512),(CVT,0x17c),(CVT+0x180,0x80),(BLIT,12),(RLE_BLIT,8),(RAW_BLIT,8),
   (ZOBJ,48),(AOBJ,48),(self.alpha_map,0x20008),(self.va(0x821f8c),4),(self.va(0x8198d4),4)]
  old=bytes(self.u.mem_read(FALLBACK,0x148));p.drawing=True
  try:result=PresentationOracle.checked_call(self,a,args,ecx,edx,writes=writes,inputs=inputs)
  finally:p.drawing=False
  final=bytearray(self.u.mem_read(FALLBACK,0x148));final[0x24:0x28]=old[0x24:0x28];assert bytes(final)==old
  return result
 def service(self,u,a,n,ctx):
  if self.world_mode and self.unit_mode:
   if a==0x6d21e0:
    v=words(u,u.reg_read(UC_X86_REG_ESP)+4,11)
    assert v[0]==TYPE+0xb0 and v[1]==0 and v[3]==TYPE+0x23c and v[7] in (0,1) and v[9]==0
    if not self.full_shadow:
     assert v[7]==1
     assert -1048576<=signed(v[10])<=1048576
     self.map_events.extend([508,v[9],v[10]])
     self.shadow_return=words(u,u.reg_read(UC_X86_REG_ESP),1)[0]
     self.observed.extend(['shadow',signed(v[2]),*ints(u,v[4],4),*ints(u,v[5],2),*words(u,v[6],12),int(v[8]!=0),*self.stage()])
     self.full_shadow=self.shadow_active=True
    else:assert v[9:]==[0,0] # Recursive cached copy has no stencil/origin.
    self.shadow_calls[hex(a)]=self.shadow_calls.get(hex(a),0)+1
    FootVoxelStagingOracle.service(self,u,a,n,ctx);return
   if a==self.height_return:
    self.map_events.extend([503,u.reg_read(UC_X86_REG_EAX)]);self.height_return=None
   if a in (0x548070,LOOKUP,0x52b690,0x5d4810,0x4a0500,0x53d1c0):
    assert any(lo<=a and a+n<=hi for lo,hi in self.allowed)
    self.ground_calls[hex(a)]=self.ground_calls.get(hex(a),0)+1
    sp=u.reg_read(UC_X86_REG_ESP)
    if a==0x4a0500:self.map_events.extend([500])
    elif a==0x53d1c0:self.map_events.extend([507])
    elif a==0x5d4810:
     assert u.reg_read(UC_X86_REG_ECX)==ACTOR and self.height_return is None
     self.height_return=words(u,sp,1)[0];self.map_events.extend([502]);return
    else:
     arg=words(u,sp+4,1)[0]
     if a==0x548070:self.map_events.extend([304,words(u,arg,1)[0]])
     elif a==LOOKUP:self.map_events.extend([405,*words(u,arg,3)])
     else:self.map_events.extend([404,(u.reg_read(UC_X86_REG_ECX)-TYPES)//1024,arg])
     return # Observe only, bypass old synthetic lookups/dimensions.
  super().service(u,a,n,ctx)
 def draw_ground(self,location,scale,v):
  assert self.ground_ready
  x,y,_=location;assert 0<=x<512*256 and 0<=y<512*256
  assert words(self.u,SLOTS+((y//256)*512+x//256)*4,1)[0],'Ground draw requires resident current Cell'
  self.location=location;self.height_scale=scale;self.map_events=[]
  def store(u,access,p,n,value,ctx):
   if p==FALLBACK+0x24:assert n==4;self.map_events.extend([0xffffffff,0,value&0xffffffff])
  hook=self.u.hook_add(UC_HOOK_MEM_WRITE,store)
  try:result=self.draw_complete(v)
  finally:self.u.hook_del(hook)
  assert self.height_return is None
  state=bytes(self.u.mem_read(0x850bb8,1))+bytes(self.u.mem_read(0x850ba8,8))+bytes(self.u.mem_read(0x850bd0,8))+bytes(self.u.mem_read(PLANES,800))
  return [*result,'queries',words(self.u,FALLBACK+0x24,1)[0],hashlib.sha256(struct.pack('<'+'I'*len(self.map_events),*self.map_events)).hexdigest(),'floor',hashlib.sha256(state).hexdigest()]
