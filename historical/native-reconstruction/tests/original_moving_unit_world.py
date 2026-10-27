# SPDX-License-Identifier: GPL-3.0-or-later
"""One original guest: finalized terrain, actual Process and complete posed drawing.

The explicit draw setup below is adapted from our own frozen four-index fixture;
actor coordinates, body Facing and locomotor state are never reset by drawing.
"""
import hashlib,struct
from original_unit_voxel_shadow_world import (ALL_INDEXES,ACTOR,VT,TYPE,LOCO,HVA,TRANSFORMS,STAGE,
    PREDICATE,ADJUST,V2C0,V2C4,WORLD,CONVERTER,RASTER,HOUSE_CONVERTER,CVT,RLE_BLIT,RAW_BLIT,
    POOL_OBJ,CAPACITY,POOL,SCRATCH,DEST,SOURCE,UC_HOOK_MEM_WRITE,UC_HOOK_MEM_READ,words,ints,signed)
from original_ground_unit_height import GroundUnitHeightOracle
from original_ground_unit_world import REGISTRY,MAP,CELLS,SLOTS,TYPES,IMAGES,OVERLAYS,OVERLAY_REG
from original_unit_voxel_world import UnitVoxelWorldOracle
from original_moving_unit_movement import AttachedMovement
from verify_moving_unit_world import RANGES
from unicorn.x86_const import UC_X86_REG_ESP
class MovingUnitWorldOracle(GroundUnitHeightOracle):
    def __init__(self,exe,assets,palette):
        self.movement=None;self.body_return=None;self.body_calls=0;self.part_calls=0;self.live_entries={}
        super().__init__(exe,assets,palette)
        self.allowed=sorted(set(self.allowed+[(a,a+n) for a,n in RANGES.items()]),reverse=True)
        self.movement=AttachedMovement(self)
    def va(self,a):return a if a in RANGES or a==0x4916d0 else super().va(a)
    def map_inputs(self):
        p=self.prepared
        return [(CELLS,p.count*512),(SLOTS,0x100000),(TYPES,p.type_count*1024),(IMAGES,p.type_count*4096),(REGISTRY,p.type_count*4+64),
            (OVERLAYS,p.overlay_count*1024),(OVERLAY_REG,p.overlay_count*4+64),(MAP+0x138,8)]
    def prepare_map(self,f):
        result=super().prepare_map(f)
        # The complete map parent binds the slot pointer, while its count is an
        # explicit fixture input. Movement needs it before the first draw setup.
        self.put(MAP+0x13c,262144)
        self.geometry_active=True
        try:self.numeric.stock(0)
        finally:self.geometry_active=False
        # The earlier movement fixture already executed both actual direction
        # initializers. This graphics guest needs the second one explicitly too.
        self.checked_call(0x4916d0,writes=[(0x851ac0,64)])
        self.movement.ready=False
        return result
    def prepare_world(self):
        # Bind surfaces/house/contact only. Do not use the older ground profile's
        # flat locomotor reset or overwrite the live actor location/Facing.
        UnitVoxelWorldOracle.prepare_world(self)
        for p,v in ((0xa40cd4,REGISTRY),(0xa40ce0,self.prepared.type_count),(0x8661d8,0),(MAP+0x13c,262144)):self.put(p,v)
        self.u.mem_write(0xabe490,struct.pack('<d',self.height_scale));self.put(0xa52f00,0)
    def service(self,u,a,n,ctx):
        if self.movement and self.movement.active:return
        if self.world_mode and self.unit_mode:
            if a in RANGES:self.live_entries[hex(a)]=self.live_entries.get(hex(a),0)+1
            if a==0x4a0050:
                sp=u.reg_read(UC_X86_REG_ESP);self.body_return=words(u,sp,1)[0]
                _,self.body_out,self.body_key=words(u,sp+4,3);self.map_events.extend([501]);self.body_calls+=1
            elif a==self.body_return:
                self.body_return=None
                self.observed.extend(['body',*words(u,self.body_out,12),words(u,self.body_key,1)[0]])
            elif a==0x4c9880:
                args=words(u,u.reg_read(UC_X86_REG_ESP)+4,9)
                # Compare the exact matrices forwarded to Foot, even on warm
                # shortcut branches whose geometry is unused by cached images.
                self.observed.extend(['part',(args[0]-TYPE-0xb0)//8,signed(args[2]),*words(u,args[6],12)])
                self.part_calls+=1
        super().service(u,a,n,ctx)
    def draw_live(self,v):
        scale,seed,contact,no_shadow,disable_shadow,*unit=v
        self.height_scale=struct.unpack('<d',struct.pack('<Q',scale))[0]
        # Movement supplies class-ID services. Drawing uses the already audited
        # original Unit vtable; only fixture dispatch changes between phases.
        table=bytes(self.u.mem_read(VT,0x600))
        self.u.mem_write(VT,bytes(self.u.mem_read(0x7addf8,0x600)))
        try:return self.draw_ground(struct.unpack('<3i',self.u.mem_read(ACTOR+0x88,12)),self.height_scale,
            [seed,0,contact,no_shadow,disable_shadow,0,*unit])
        finally:self.u.mem_write(VT,table)
    def draw_unit(self,v):
        body,turret,pitch,gate,disabled,valid,barrel,frame,brightness,self.shadow_predicate,camera,template,x,y,bx,by,bw,bh=v
        assert 0<=valid<=7 and barrel in (0,1) and template in range(3)
        assert self.movement.ready, "Live actor must be initialized before drawing"
        for p,value in ((ACTOR,VT),(ACTOR+0x5ac,TYPE),(ACTOR+0x154,-1),(ACTOR+0x564,LOCO+4),
              (LOCO+4,0x7a04cc),(LOCO+12,ACTOR),(TYPE+0x5a4,1),(ACTOR+0x430,frame),(0xa35db4,0x2468),
              (HVA+4,1),(HVA+8,1),(HVA+12,TRANSFORMS),(0x83995c,WORLD),(0xad0604,STAGE),(0xad0608,CONVERTER)):
            self.put(p,value)
        for off,target in ((0xc0,PREDICATE),(0x3d0,ADJUST),(0x2c0,V2C0),(0x2c4,V2C4)):self.put(VT+off,target)
        self.house=self.predicate=self.adjusted=0;self.c0=-1;self.c4=2
        for part,off in enumerate((0xb0,0xb8,0xc0)):
            present=bool(valid&(1<<part)) and (part!=2 or barrel)
            self.put(TYPE+off,self.models[part] if present else 0)
            self.put(TYPE+off+4,HVA if part!=2 or barrel else 0)
        self.u.mem_write(TYPE+0xb48,bytes([self.no_shadow]));self.u.mem_write(TYPE+0xb5b,bytes([self.disable_shadow]))
        self.u.mem_write(TYPE+0xb5a,bytes([disabled]));self.u.mem_write(TYPE+0xaab,b'\1')
        for off,heading in ((0x2f8,turret),(0x2c8,pitch)):
            self.put(ACTOR+off,heading);self.put(ACTOR+off+4,heading)
        self.u.mem_write(0x839a58,bytes([gate]))
        empty=((0,0,0,0),(9,11,13,15),(248,249,24,23))[template]
        self.u.mem_write(0xad0478,struct.pack('<4i',*empty));self.u.mem_write(0xad0490,b'\xa7'*16)
        ident=(1,0,0,0,0,1,0,0,0,0,1,0)
        camera_matrix=ident if camera==0 else (.5,.25,-.5,.125,-.25,.5,.25,-.25,.25,-.5,.5,.5)
        for p,m in ((TRANSFORMS,ident),(0x839a70,ident),(0xaf77a8,camera_matrix)):self.u.mem_write(p,struct.pack('<12f',*m))
        self.u.mem_write(0xad04e0,struct.pack('<d',.09375))
        self.u.mem_write(self.va(0xadc068),self.vpl[784:]);self.put(self.va(0xade070),0);self.put(self.va(0xade074),1);self.put(self.va(0x7e35d0),1)
        self.u.mem_write(RASTER+65536,bytes(2));self.surface(STAGE,256,256,1,DEST);self.surface(SOURCE,256,256,1,RASTER)
        self.put(VT+0x1cc,HOUSE_CONVERTER);self.put(0x8323c4,CVT)
        self.put(CVT+0xf0,RLE_BLIT);self.put(CVT+0x2c,RAW_BLIT)
        self.put(RLE_BLIT,0x79e0e0);self.put(RLE_BLIT+4,0x7bef);self.put(RAW_BLIT,0x79e39c);self.put(RAW_BLIT+4,0x7bef)
        self.put(0x839c6c,0);self.put(0x8315b4,0);self.put(0xb2b624,0)
        angle=words(self.u,self.va(0x785cf0),1)[0]
        self.checked_call(0x70ca10,[angle],writes=[(self.va(0x821d80),12),(self.va(0x821dcc),16)])
        outputs=[(self.va(p),size) for p,size in ((0x7e35d0,4),(0xab84d0,65548),(0xac8710,8),(0xac8838,12),
                 (0xac8848,136),(0xacaa50,20),(0xacae68,65536),(0xadae68,72),(0xae0470,48),(0xae0870,256))]
        entries=[words(self.u,p,1)[0] for p in ALL_INDEXES];old_cursor=words(self.u,POOL_OBJ+8,1)[0]-POOL
        immutable=[(p,n) for p,n in self.allocations if p not in entries]
        self.observed=[];self.events=[];self.cache_active=self.active=self.foot_mode=self.unit_mode=True
        heap_guard=self.u.hook_add(UC_HOOK_MEM_WRITE,self.guarded_heap_write);source_guard=self.u.hook_add(UC_HOOK_MEM_READ,self.guard_source)
        before=bytes(self.u.mem_read(ACTOR,0x1000));type_before=bytearray(self.u.mem_read(TYPE,0xc00))
        try:self.checked_call(0x6ff690,[x,y,bx,by,bw,bh,brightness],ACTOR,
              writes=[*outputs,(DEST,65536),(STAGE+12,4),(SOURCE+12,4),(CONVERTER+0x17c,4),(0xad0490,16),(0x83995c,4),
                      (ACTOR+0x5bb,1),(POOL_OBJ+8,4),(POOL+old_cursor,CAPACITY-old_cursor),(SCRATCH,16384),
                      *[(p,20) for p in ALL_INDEXES],(0x1300000,0x300000)],
              inputs=[(ACTOR,0x5bb),(ACTOR+0x5bc,0x1000-0x5bc),(VT,0x600),(LOCO,16),(HVA,32),(TRANSFORMS,48),
                      (STAGE,12),(STAGE+16,12),(SOURCE,12),(SOURCE+16,12),(POOL_OBJ,8),(POOL,old_cursor),*immutable])
        finally:
            self.cache_active=self.active=self.foot_mode=self.unit_mode=False;self.u.hook_del(heap_guard);self.u.hook_del(source_guard)
        self.check_heap();assert bytes(self.u.mem_read(ACTOR,0x1000))==before
        type_after=bytearray(self.u.mem_read(TYPE,0xc00))
        for p in ALL_INDEXES:type_after[p-TYPE:p-TYPE+20]=type_before[p-TYPE:p-TYPE+20]
        assert type_after==type_before,'Unit type changed outside indexes'
        assert words(self.u,STAGE+12,1)==words(self.u,SOURCE+12,1)==[0] and words(self.u,0x83995c,1)==[WORLD]
        assert bytes(self.u.mem_read(POOL+CAPACITY,32))==bytes([0xa5])*32
        data=bytearray(self.u.mem_read(POOL,CAPACITY))
        for off in self.snapshot_offsets:struct.pack_into('<I',data,off+8,words(self.u,POOL+off+8,1)[0]-POOL)
        result=[*self.observed,'after',*self.stage(),'pool',words(self.u,POOL_OBJ+8,1)[0]-POOL,hashlib.sha256(data).hexdigest()]
        for p in ALL_INDEXES:
            pointer,n,capacity=words(self.u,p,3);hot=words(self.u,p+16,1)[0]
            result.extend(['index',n,capacity,self.u.mem_read(p+12,1)[0],ints(self.u,hot,1)[0] if hot else 'None',*[ints(self.u,pointer+i*8,1)[0] for i in range(n)]])
        return result
