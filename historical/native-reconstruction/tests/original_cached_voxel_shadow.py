# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete cached Unit shadow child with actual compressed RGB565 span."""
import hashlib,struct
from original_unit_voxel_world import UnitVoxelWorldOracle,WORLD,COLOR,ZDATA,ADATA,PAL,CVT,ZSURF,ASURF,ZOBJ,AOBJ,W,H
from original_voxel_part_staging import VoxelPartStagingOracle,DEST
from original_voxel_part import ACTOR,VT,STAGE,V2C0,V2C4
from original_voxel_snapshot import POOL,pixels
from original_foot_voxel_staging import TYPE
from original_presentation import ARG
from original_foot_lit import words,ints,ret
from verify_cached_voxel_shadow import verify
from unicorn.x86_const import UC_X86_REG_ECX,UC_X86_REG_ESP
HOUSE_CONVERTER=0x160d000
RLE_BLIT=0x160c400
class CachedVoxelShadowOracle(UnitVoxelWorldOracle):
    def __init__(self,*args):
        self.shadow_active=False
        super().__init__(*args)
        self.shadow_inspection=verify((args[0].parents[1]/'disc-allied/game.exe').read_bytes(),args[0].read_bytes())
        self.allowed.append((0x489d90,0x489e5b));self.shadow_spans=0;self.shape_bytes=0
    def service(self,u,a,n,ctx):
        if self.shadow_active:
            ecx=u.reg_read(UC_X86_REG_ECX);sp=u.reg_read(UC_X86_REG_ESP)
            if a==HOUSE_CONVERTER:
                assert ecx==ACTOR;ret(u,0,CVT);return
            if a in (0x485d60,0x4350c0):
                assert any(lo<=a and a+n<=hi for lo,hi in self.allowed)
                if a==0x485d60:
                    assert ecx==CVT and words(u,sp+4,1)==[0x2001];self.event('select',0x2001)
                else:assert ecx==WORLD
                # Expand only the earlier fixture's byte-converter/receiver
                # assertion. Complete selector and surface instructions execute.
                VoxelPartStagingOracle.service(self,u,a,n,ctx);return
            if a==0x485e11:assert words(u,sp+4,1)==[0x2001]
            if a==0x489d90:
                assert ecx==RLE_BLIT;self.shadow_spans+=1
                count=words(u,sp+12,1)[0];shape=words(u,sp+40,1)[0]
                assert count<=W and bytes(u.mem_read(shape,count))==bytes(count)
                self.shape_bytes+=count
        super().service(u,a,n,ctx)
    def draw_shadow(self,v):
        self.seed,mode,w,h,ox,oy,x,y,bx,by,bw,bh,z,dx,dy,dw,dh=v
        source=pixels(self.seed,mode,w,h)
        snapshot,_=self.snapshot(source,w,h,[ox,oy,0,0,w,h],65536,0)
        assert snapshot==POOL
        self.world_mode=True;self.map_mode=self.contact_mode=0
        self.u.mem_write(ACTOR,bytes(0x3000));self.u.mem_write(VT,bytes(self.u.mem_read(0x7addf8,0x600)))
        self.put(ACTOR,VT);self.put(ACTOR+0x5ac,TYPE)
        self.surface(STAGE,256,256,1,DEST)
        for off,target in ((0x1cc,HOUSE_CONVERTER),(0x2c0,V2C0),(0x2c4,V2C4)):self.put(VT+off,target)
        self.put(0x83995c,WORLD);self.put(CVT+0xf0,RLE_BLIT)
        self.put(RLE_BLIT,0x79e0e0);self.put(RLE_BLIT+4,0x7bef)
        self.c0=z;self.c4=2;self.events=[]
        self.u.mem_write(ARG+0x500,struct.pack('<6i',x,y,bx,by,bw,bh));self.u.mem_write(0xad0490,struct.pack('<4i',dx,dy,dw,dh))
        self.active=self.cache_active=self.shadow_active=True
        try:self.checked_call(0x6d29d0,[snapshot,ARG+0x500,ARG+0x508,0x2001,1000],ACTOR,
            writes=[(COLOR,W*H*2),(0xad0490,16),*[(p+12,4) for p in (WORLD,ZSURF,ASURF)]],
            inputs=[(ACTOR,0x3000),(POOL,65568),(CVT,0x200),(RLE_BLIT,8),(ZDATA,W*H*2),(ADATA,W*H*2),
                    (PAL,53*512),(ZOBJ,48),(AOBJ,48),(ARG+0x500,24),*self.heap_inputs()])
        finally:self.active=self.cache_active=self.shadow_active=self.world_mode=False
        for obj in (WORLD,ZSURF,ASURF):assert words(self.u,obj+12,1)==[0]
        return [*self.events,'draw',*ints(self.u,0xad0490,4),
                hashlib.sha256(bytes(self.u.mem_read(COLOR,W*H*2))).hexdigest(),
                hashlib.sha256(bytes(self.u.mem_read(ZDATA,W*H*2))).hexdigest()]
