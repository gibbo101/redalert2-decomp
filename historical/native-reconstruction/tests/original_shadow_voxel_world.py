# SPDX-License-Identifier: GPL-3.0-or-later
"""Actual shadow parent -> fresh raster/pool/recursive cached or raw world draw."""
import hashlib,struct
from original_cached_voxel_shadow import CachedVoxelShadowOracle,HOUSE_CONVERTER,RLE_BLIT
from original_unit_voxel_world import WORLD,COLOR,ZDATA,ADATA,PAL,CVT,ZSURF,ASURF,ZOBJ,AOBJ,W,H
from original_voxel_part_staging import SOURCE,DEST
from original_voxel_part import ACTOR,VT,MODEL,HVA,TRANSFORMS,STAGE,V2C0,V2C4,animation
from original_voxel_snapshot import POOL,SCRATCH
from original_foot_voxel_staging import TYPE,INDEX,POOL_OBJ,CAPACITY,RASTER,ranges
from original_presentation import ARG
from original_foot_lit import words,ints
from verify_shadow_voxel_world import verify
from unicorn import UC_HOOK_MEM_WRITE,UC_HOOK_MEM_READ
from unicorn.x86_const import UC_X86_REG_ECX,UC_X86_REG_EDX,UC_X86_REG_ESP
RAW_BLIT=0x160c500
class ShadowVoxelWorldOracle(CachedVoxelShadowOracle):
    def __init__(self,*args):
        self.full_shadow=False
        super().__init__(*args)
        self.full_shadow_inspection=verify((args[0].parents[1]/'disc-allied/game.exe').read_bytes(),args[0].read_bytes())
        self.allowed=sorted(set(self.allowed+[(a,a+n) for a,n in ranges(self.full_shadow_inspection)]),reverse=True)
        self.shadow_calls={};self.raw_spans=0
    def va(self,a):return a if a in (0x6d21e0,0x6d2810) else super().va(a)
    def service(self,u,a,n,ctx):
        if self.full_shadow:
            ecx=u.reg_read(UC_X86_REG_ECX);sp=u.reg_read(UC_X86_REG_ESP)
            if a in (0x6d21e0,0x6d2810,0x69a1d0,0x6d29d0,0x717360,0x7178e0,0x719c10,0x781d46,0x6d9900):
                self.shadow_calls[hex(a)]=self.shadow_calls.get(hex(a),0)+1
            if a==0x6d2365:self.in_snapshot=False
            if a in (0x6d2438,0x6d244f,0x6d2488):raise AssertionError('Unrecovered shadow heap/pool failure branch entered')
            if a==0x485aa0:
                assert ecx==CVT and words(u,sp+4,1)==[0x2001]
                self.event('select',0x2001);return
            if a==0x49f3a0:
                assert ecx==WORLD and u.reg_read(UC_X86_REG_EDX)==CVT
                source,box,point,clip,zero,blitter,z,gradient,brightness,extra=words(u,sp+4,10)
                assert source==SOURCE and blitter==RAW_BLIT and zero==extra==0 and gradient==2 and brightness==1000
                assert any(lo<=a and a+n<=hi for lo,hi in self.allowed);return
            if a==0x487390:
                assert ecx==RAW_BLIT;self.raw_spans+=1
        super().service(u,a,n,ctx)
    def draw_full_shadow(self,v):
        self.seed,part,key,available,disabled,bad,suppressed,no_shadow,allow,mode,stencil,x,y,bx,by,bw,bh,z,dx,dy,dw,dh,*pose=v
        assert len(pose)==12 and part in range(3) and mode in (0,1,2)
        self.world_mode=True;self.map_mode=self.contact_mode=0
        self.u.mem_write(ACTOR,bytes(0x3000));self.u.mem_write(VT,bytes(self.u.mem_read(0x7addf8,0x600)))
        self.u.mem_write(TYPE,bytes(0xc00));self.put(ACTOR,VT);self.put(ACTOR+0x5ac,TYPE);self.put(ACTOR+0x1b8,suppressed)
        self.u.mem_write(TYPE+0xb48,bytes([no_shadow]));self.u.mem_write(TYPE+0xb5b,bytes([disabled]))
        self.surface(STAGE,256,256,1,DEST);self.surface(SOURCE,256,256,1,RASTER)
        for off,target in ((0x1cc,HOUSE_CONVERTER),(0x2c0,V2C0),(0x2c4,V2C4)):self.put(VT+off,target)
        self.put(0x83995c,WORLD);self.put(0x8323c4,CVT);self.put(CVT+0xf0,RLE_BLIT);self.put(CVT+0x2c,RAW_BLIT)
        self.put(RLE_BLIT,0x79e0e0);self.put(RLE_BLIT+4,0x7bef);self.put(RAW_BLIT,0x79e39c);self.put(RAW_BLIT+4,0x7bef)
        self.put(MODEL,self.models[part]);self.put(MODEL+4,HVA if mode else 0)
        self.u.mem_write(self.models[part],bytes([bad]));transforms=animation(mode)
        self.put(HVA+4,1);self.put(HVA+8,len(transforms));self.put(HVA+12,TRANSFORMS)
        self.u.mem_write(TRANSFORMS,struct.pack('<'+'f'*12*len(transforms),*[f for m in transforms for f in m]))
        self.u.mem_write(0x839a70,struct.pack('<12f',1,0,0,0,0,1,0,0,0,0,1,0))
        self.u.mem_write(DEST,bytes(37 if (i*3+(i//256)*7+self.seed)%5<2 else 0 for i in range(65536)))
        self.u.mem_write(RASTER+65536,bytes(2));self.c0=z;self.c4=2
        self.u.mem_write(ARG,struct.pack('<12I',*pose));self.u.mem_write(ARG+0x500,struct.pack('<6i',x,y,bx,by,bw,bh))
        self.u.mem_write(0xad0490,struct.pack('<4i',dx,dy,dw,dh))
        angle=words(self.u,self.va(0x785cf0),1)[0]
        self.checked_call(0x70ca10,[angle],writes=[(self.va(0x821d80),12),(self.va(0x821dcc),16)])
        outputs=[(self.va(p),n) for p,n in ((0x7e35d0,4),(0xab84d0,65548),(0xac8710,8),(0xac8838,12),
                 (0xac8848,136),(0xacaa50,20),(0xacae68,65536),(0xadae68,72),(0xae0470,48))]
        entries=words(self.u,INDEX,1)[0];old_cursor=words(self.u,POOL_OBJ+8,1)[0]-POOL
        immutable=[(p,n) for p,n in self.allocations if p!=entries]
        before=dict(self.shadow_calls);self.events=[];self.active=self.cache_active=self.shadow_active=self.foot_mode=self.full_shadow=True
        heap_guard=self.u.hook_add(UC_HOOK_MEM_WRITE,self.guarded_heap_write);source_guard=self.u.hook_add(UC_HOOK_MEM_READ,self.guard_source)
        try:self.checked_call(0x6d21e0,[MODEL,0,key,INDEX if available else 0,ARG+0x508,ARG+0x500,ARG,allow,STAGE if stencil else 0,0,0],ACTOR,
            writes=[*outputs,(COLOR,W*H*2),(CVT+0x17c,4),(0xad0490,16),(INDEX,20),(POOL_OBJ+8,4),(POOL+old_cursor,CAPACITY-old_cursor),
                    (SCRATCH,16384),(0x1300000,0x300000),*[(p+12,4) for p in (STAGE,SOURCE,WORLD,ZSURF,ASURF)]],
            inputs=[(ACTOR,0x3000),(TYPE,0xc00),(VT,0x600),(MODEL,8),(HVA,32),(TRANSFORMS,len(transforms)*48),
                    (ARG,48),(ARG+0x500,24),(0x839a70,48),(0x839a60,12),(DEST,65536),(POOL,old_cursor),(POOL_OBJ,8),(CVT,0x17c),(CVT+0x180,0x80),(RLE_BLIT,8),(RAW_BLIT,8),
                    (ZDATA,W*H*2),(ADATA,W*H*2),(PAL,53*512),(ZOBJ,48),(AOBJ,48),*immutable])
        finally:
            self.active=self.cache_active=self.shadow_active=self.foot_mode=self.full_shadow=self.world_mode=False
            self.u.hook_del(heap_guard);self.u.hook_del(source_guard)
        self.check_heap();assert not self.in_snapshot
        for p in (STAGE,SOURCE,WORLD,ZSURF,ASURF):assert words(self.u,p+12,1)==[0]
        assert bytes(self.u.mem_read(POOL+CAPACITY,32))==bytes([0xa5])*32
        fresh=self.shadow_calls.get('0x6d2810',0)-before.get('0x6d2810',0)
        hit=self.shadow_calls.get('0x6d29d0',0)-before.get('0x6d29d0',0)
        kind=(3 if key==-1 or not available or disabled else 1) if fresh else 2 if hit else 0
        raster=hashlib.sha256(bytes(self.u.mem_read(RASTER,65536))).hexdigest() if fresh else '-'
        data=bytearray(self.u.mem_read(POOL,CAPACITY))
        for off in self.snapshot_offsets:struct.pack_into('<I',data,off+8,words(self.u,POOL+off+8,1)[0]-POOL)
        pointer,n,capacity=words(self.u,INDEX,3);hot=words(self.u,INDEX+16,1)[0]
        return [*self.events,'draw',kind,*ints(self.u,0xad0490,4),raster,
                hashlib.sha256(bytes(self.u.mem_read(COLOR,W*H*2))).hexdigest(),hashlib.sha256(bytes(self.u.mem_read(ZDATA,W*H*2))).hexdigest(),
                'pool',words(self.u,POOL_OBJ+8,1)[0]-POOL,hashlib.sha256(data).hexdigest(),
                'state',n,capacity,self.u.mem_read(INDEX+12,1)[0],ints(self.u,hot,1)[0] if hot else 'None',*[ints(self.u,pointer+i*8,1)[0] for i in range(n)]]
