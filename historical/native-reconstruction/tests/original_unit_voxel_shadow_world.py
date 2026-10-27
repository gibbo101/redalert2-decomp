# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete Unit/world root with actual shadow children and four audited indexes.

The scoped Unit setup below is copied from our own frozen three-index fixture,
then expanded explicitly; earlier oracle sources/receipts remain unchanged.
"""
import hashlib,struct
from original_shadow_voxel_world import ShadowVoxelWorldOracle,RAW_BLIT
from original_cached_voxel_shadow import HOUSE_CONVERTER,RLE_BLIT
from original_unit_voxel_staging import INDEXES,CELL
from original_unit_voxel_world import (WORLD,COLOR,ZDATA,ADATA,PAL,CVT,BLIT,ZSURF,ASURF,ZOBJ,AOBJ,W,H,
    MAP,HOUSE,ARRAY,SCHEME,CONTACTS,CONTACT,CTYPE,CONTACT_VT,TILES,TILE)
from original_foot_voxel_staging import FootVoxelStagingOracle,TYPE,LOCO,POOL_OBJ,CAPACITY,RASTER
from original_voxel_snapshot import POOL,SCRATCH
from original_voxel_part_staging import CONVERTER,DEST,SOURCE,VoxelPartStagingOracle
from original_voxel_part import ACTOR,VT,HVA,TRANSFORMS,STAGE,V2C0,V2C4,PREDICATE,ADJUST
from original_presentation import PresentationOracle
from original_foot_lit import words,ints,signed
from verify_unit_voxel_shadow_world import verify
from unicorn import UC_HOOK_MEM_WRITE,UC_HOOK_MEM_READ
from unicorn.x86_const import UC_X86_REG_ECX,UC_X86_REG_ESP
ALL_INDEXES=(*INDEXES,TYPE+0x23c)
class UnitVoxelShadowWorldOracle(ShadowVoxelWorldOracle):
    def __init__(self,*args):
        self.shadow_return=None;self.no_shadow=self.disable_shadow=0;self.foot_shadow_entries=0
        super().__init__(*args)
        self.complete_inspection=verify((args[0].parents[1]/'disc-allied/game.exe').read_bytes(),args[0].read_bytes())
    def begin_unit(self,seed):
        super().begin_unit(seed);self.u.mem_write(TYPE+0x23c,bytes(20))
    def service(self,u,a,n,ctx):
        if self.unit_mode and a==0x4c9a40:self.foot_shadow_entries+=1
        if self.unit_mode and a==self.shadow_return:
            self.shadow_return=None;self.full_shadow=self.shadow_active=False
        if self.unit_mode and a==0x6d21e0:
            ecx=u.reg_read(UC_X86_REG_ECX);sp=u.reg_read(UC_X86_REG_ESP)
            assert ecx==ACTOR and words(u,0x83995c,1)==[WORLD] and u.mem_read(ACTOR+0x5bb,1)==b'\0'
            v=words(u,sp+4,11)
            assert v[0]==TYPE+0xb0 and v[1]==0 and v[3]==TYPE+0x23c and v[9:]==[0,0]
            if not self.full_shadow:
                assert v[7]==1
                self.shadow_return=words(u,sp,1)[0]
                self.observed.extend(['shadow',signed(v[2]),*ints(u,v[4],4),*ints(u,v[5],2),*words(u,v[6],12),int(v[8]==STAGE),*self.stage()])
                self.full_shadow=self.shadow_active=True
            self.shadow_calls[hex(a)]=self.shadow_calls.get(hex(a),0)+1
            # Bypass only the older fixture's supplied-shadow interception.
            # Execute the actual root and retain Foot's heap/cache audits.
            FootVoxelStagingOracle.service(self,u,a,n,ctx);return
        if self.full_shadow and a==0x434b40:
            sp=u.reg_read(UC_X86_REG_ESP)
            dest,source,bounds,box,blitter,z,gradient,brightness,extra=words(u,sp+4,9)
            assert u.reg_read(UC_X86_REG_ECX)==WORLD and source==SOURCE and blitter==RAW_BLIT
            assert gradient==2 and brightness==1000 and extra==0
            # The generic surface also serves raw shadow drawing. Bypass the
            # older fixture's lit-only world assertion, not its instructions.
            VoxelPartStagingOracle.service(self,u,a,n,ctx);return
        super().service(u,a,n,ctx)
    def checked_call(self,a,args=(),ecx=0,edx=0,*,writes=(),inputs=()):
        if a!=0x6ff690 or not self.world_mode:return super().checked_call(a,args,ecx,edx,writes=writes,inputs=inputs)
        self.put(self.va(0x821f8c),ZOBJ);self.put(self.va(0x8198d4),AOBJ)
        writes=[*writes,(COLOR,W*H*2),(CVT+0x17c,4),*[(p+12,4) for p in (WORLD,ZSURF,ASURF)]]
        inputs=[*inputs,(MAP,0x20000),(HOUSE,0x16000),(ARRAY,4),(SCHEME,0x310),(CONTACTS,4),(CONTACT,0x500),
            (CTYPE,0x1360),(CONTACT_VT,0x30),(TILES,128),(TILE,64),(ZDATA,W*H*2),(ADATA,W*H*2),
            (PAL,53*512),(CVT,0x17c),(CVT+0x180,0x80),(BLIT,12),(RLE_BLIT,8),(RAW_BLIT,8),
            (ZOBJ,48),(AOBJ,48),(self.alpha_map,0x20008),(self.va(0x821f8c),4),(self.va(0x8198d4),4)]
        # Same complete caller/image-write audit, with the raw converter's
        # declared four-byte scratch field rather than a fully immutable CVT.
        return PresentationOracle.checked_call(self,a,args,ecx,edx,writes=writes,inputs=inputs)
    def draw_complete(self,v):
        seed,mode,contact,self.no_shadow,self.disable_shadow,*unit=v
        result=self.draw_world([seed,mode,contact,*unit])
        assert self.shadow_return is None and not self.full_shadow and not self.shadow_active and not self.in_snapshot
        return result
    def draw_unit(self,v):
        body,turret,pitch,gate,disabled,valid,barrel,frame,brightness,self.shadow_predicate,camera,template,x,y,bx,by,bw,bh=v
        assert 0<=valid<=7 and barrel in (0,1) and template in range(3)
        index_data=[bytes(self.u.mem_read(p,20)) for p in ALL_INDEXES]
        self.u.mem_write(ACTOR,bytes(0x3000));self.u.mem_write(VT,bytes(self.u.mem_read(0x7addf8,0x600)))
        self.u.mem_write(TYPE,bytes(0xc00))
        for p,b in zip(ALL_INDEXES,index_data):self.u.mem_write(p,b)
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
        for off,heading in ((0x2e0,body),(0x2f8,turret),(0x2c8,pitch)):
            self.put(ACTOR+off,heading);self.put(ACTOR+off+4,heading)
        self.u.mem_write(ACTOR+0x88,struct.pack('<3i',2560,2816,0));self.u.mem_write(0x839a58,bytes([gate]))
        empty=((0,0,0,0),(9,11,13,15),(248,249,24,23))[template]
        self.u.mem_write(0xad0478,struct.pack('<4i',*empty));self.u.mem_write(0xad0490,b'\xa7'*16)
        ident=(1,0,0,0,0,1,0,0,0,0,1,0)
        camera_matrix=ident if camera==0 else (.5,.25,-.5,.125,-.25,.5,.25,-.25,.25,-.5,.5,.5)
        for p,m in ((TRANSFORMS,ident),(0x839a70,ident),(0xaf8608,ident),(0xaf77a8,camera_matrix)):self.u.mem_write(p,struct.pack('<12f',*m))
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
