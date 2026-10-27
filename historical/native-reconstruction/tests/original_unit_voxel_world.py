# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete unchanged Unit with real staging, Foot/base depth and RGB565 final copy."""
import hashlib,struct
from original_unit_voxel_staging import UnitVoxelStagingOracle,WORLD,INDEXES
from original_foot_voxel_staging import FootVoxelStagingOracle,TYPE,LOCO,ranges
from original_voxel_part import ACTOR,VT,STAGE
from original_voxel_part_staging import DEST,SOURCE,VoxelPartStagingOracle
from original_composition import CompositionOracle
from original_presentation import STACK
from original_foot_lit import words,ints,signed,ret
from verify_unit_voxel_world import verify
from verify_foot_depth import RANGES as DEPTH_RANGES,TAILS
from verify_unit_surface import RANGES as SURFACE_RANGES
from unicorn.x86_const import UC_X86_REG_ECX,UC_X86_REG_EDX,UC_X86_REG_ESP,UC_X86_REG_EDI,UC_X86_REG_EBP
MAP=0x2200000;TILE=0x221e000;TILES=0x221f000
HOUSE=0x2000000;ARRAY=0x2020000;SCHEME=0x2021000
CONTACTS=0x2030000;CONTACT=0x2030100;CTYPE=0x2031000;CVT=0x160c000;BLIT=0x160c300
KIND=0x2033000;CONTACT_VT=0x2033100
ZSURF=0x160b000;ASURF=0x160b100;ZOBJ=0x160b200;AOBJ=0x160b300
COLOR=0x2100000;ZDATA=0x2120000;ADATA=0x2140000;PAL=0x2160000
W,H=160,144
class UnitVoxelWorldOracle(UnitVoxelStagingOracle):
    composition_block=CompositionOracle.composition_block
    def __init__(self,exe,assets,palette):
        self.world_ready=False;self.world_mode=False
        super().__init__(exe,assets,palette)
        self.world_inspection=verify((exe.parents[1]/'disc-allied/game.exe').read_bytes(),exe.read_bytes())
        self.allowed=sorted(set(self.allowed+[(a,a+n) for a,n in ranges(self.world_inspection)]+[(0x636e20,0x636e30)]),reverse=True)
        self.u.mem_map(0x2000000,0x400000);self.world_calls={};self.gradient_calls={0:0,2:0};self.staging_surfaces=0;self.changed_pixels=0;self.map_queries=0;self.dimension_writes=0;self.base_return=None
        self.checked_call(0x491620,writes=[(0x851a70,32)])
        for fn,p in ((0x6975d0,0xaa5fa0),(0x697660,0xaa5fb0),(0x697930,0xaa5f70)):
            self.checked_call(fn,writes=[(self.va(p),8),(self.va(0xaa6038),8)])
        self.u.reg_write(UC_X86_REG_ESP,STACK);self.u.reg_write(UC_X86_REG_EDI,53)
        self.composition_block(0x41e40e,0x41e475,writes=[(0x1300000,0x300000)],budget=2000000,heap=True)
        self.alpha_map=self.u.reg_read(UC_X86_REG_EBP);self.world_ready=True
    def va(self,a):
        if a in DEPTH_RANGES or a in TAILS or a in SURFACE_RANGES or a==0x636e20:return a
        return super().va(a)
    def surface(self,obj,w,h,bpp,data):
        super().surface(obj,w,h,bpp,data)
        if self.world_ready and self.world_mode and obj==STAGE:self.prepare_world()
    def prepare_world(self):
        # Called by the unchanged parent's setup, before its immutable snapshots.
        self.put(VT+0x2c0,0x4c9930);self.put(VT+0x2c4,0x4c9a10)
        self.put(VT+0xc0,0x41b410);self.put(VT+0x3d0,0x6d8c30)
        self.put(ACTOR+0x1b4,HOUSE);self.put(ACTOR+0xcc,CONTACTS);self.put(ACTOR+0x494,self.contact_mode)
        self.u.mem_write(TYPE+0xbae,b'\1')
        for off,value in ((0xb60,8),(0xb64,13),(0xb5c,10),(0xb68,0)):self.put(TYPE+off,value)
        self.u.mem_write(MAP,bytes(0x20000));self.cells={}
        for i in range(81):
            p=MAP+i*0x200;x,y=10+i%9-4,11+i//9-4;self.cells[(x,y)]=p
            self.u.mem_write(p+0x24,struct.pack('<2h',x,y));self.put(p+0x38,65535)
            self.u.mem_write(p+0x116,struct.pack('<h',-1))
        center=self.cells[(10,11)]
        if self.map_mode in (1,4):
            self.put(center+0x140,0x100)
            for xy in ((10,12),(11,11),(11,12)):self.put(self.cells[xy]+0x38,6)
        if self.map_mode in (2,4):
            for p in self.cells.values():self.u.mem_write(p+0x116,b'\0\0');self.put(p+0xec,10)
        if self.map_mode in (3,4):
            self.u.mem_write(self.cells[(11,12)]+0x11b,b'\5');self.u.mem_write(self.cells[(12,13)]+0x11b,b'\x0a')
        self.put(0xa52c74,0);self.put(0x8661d8,4);self.u.mem_write(0xac0148,struct.pack('<2h',-32768,-32768))
        for i in range(32):self.put(TILES+i*4,TILE)
        self.put(0xa40cd4,TILES);self.put(0xa52f00,0)
        self.put(CONTACTS,CONTACT if self.contact_mode else 0);self.put(CONTACT,CONTACT_VT)
        self.put(CONTACT_VT+0x2c,KIND);self.put(CONTACT+0x418,CTYPE);self.u.mem_write(CTYPE+0x1357,b'\1')
        super().surface(WORLD,W,H,2,COLOR);super().surface(ZSURF,W,H,2,ZDATA);super().surface(ASURF,W,H,2,ADATA)
        for obj,surface,data in ((ZOBJ,ZSURF,ZDATA),(AOBJ,ASURF,ADATA)):
            for off,value in ((4,0),(16,0),(20,surface),(24,data),(28,data+W*H*2),(32,W*H*2),(36,32768),(40,W),(44,H)):self.put(obj+off,value)
        self.put(self.va(0x821f8c),ZOBJ);self.put(self.va(0x8198d4),AOBJ)
        self.put(HOUSE+0x15f40,0);self.put(0xab6efc,ARRAY);self.put(ARRAY,SCHEME);self.put(SCHEME+0x30c,CVT)
        self.put(CVT+8,1);self.put(CVT+0x98,BLIT);self.put(BLIT,0x79e20c);self.put(BLIT+4,PAL);self.put(BLIT+8,self.alpha_map)
        self.put(0xa40d13,0)
        n=self.seed
        values=((COLOR,[(i*37+n*91)&65535 for i in range(W*H)]),
                (ZDATA,[(0,32720,32740,32760,32768,32780,65535)[(i+n)%7] for i in range(W*H)]),
                (ADATA,[(i*17+n*11)&255 for i in range(W*H)]),
                (PAL,[(n*257+row*599+i*131)&65535 for row in range(53) for i in range(256)]))
        for p,v in values:self.u.mem_write(p,struct.pack('<'+'H'*len(v),*v))
    def checked_call(self,a,args=(),ecx=0,edx=0,*,writes=(),inputs=()):
        if a==0x6ff690 and self.world_mode:
            self.put(self.va(0x821f8c),ZOBJ);self.put(self.va(0x8198d4),AOBJ)
            writes=[*writes,(COLOR,W*H*2),*[(p+12,4) for p in (WORLD,ZSURF,ASURF)]]
            inputs=[*inputs,(MAP,0x20000),(HOUSE,0x16000),(ARRAY,4),(SCHEME,0x310),(CONTACTS,4),(CONTACT,0x500),
                    (CTYPE,0x1360),(CONTACT_VT,0x30),(TILES,128),(TILE,64),(ZDATA,W*H*2),(ADATA,W*H*2),
                    (PAL,53*512),(CVT,0x200),(BLIT,12),(ZOBJ,48),(AOBJ,48),(self.alpha_map,0x20008),(self.va(0x821f8c),4),(self.va(0x8198d4),4)]
        return super().checked_call(a,args,ecx,edx,writes=writes,inputs=inputs)
    def service(self,u,a,n,ctx):
        if self.world_mode and self.unit_mode:
            ecx=u.reg_read(UC_X86_REG_ECX);sp=u.reg_read(UC_X86_REG_ESP)
            if a in (0x6ff3e0,0x4c9930,0x4c9a10,0x6cfea0,0x636e20,0x434b40,0x488870,0x4c8fa0):
                self.world_calls[hex(a)]=self.world_calls.get(hex(a),0)+1
            if self.base_return==a:self.base_return=None
            if a==0x6cfea0:self.base_return=words(u,sp,1)[0]
            if a==0x548070:
                assert ecx==0x8324e0;p=words(u,sp+4,1)[0];xy=struct.unpack('<2h',u.mem_read(p,4));self.map_queries+=1;ret(u,4,self.cells.get(xy,0));return
            if a==0x548000:
                assert ecx==0x8324e0 and ints(u,words(u,sp+4,1)[0],3)==[2560,2816,0]
                ret(u,4,self.cells[(10,11)]);return
            if a==0x52b690:
                assert self.base_return and ecx==TILE
                sub,unused,out=words(u,sp+4,3);assert sub==0 and STACK-0x2000<=out and out+12<=STACK
                u.mem_write(out,bytes(12));self.dimension_writes+=1;ret(u,12,out);return
            if a==0x4f52b0:
                assert ecx==HOUSE;ret(u,0,0);return
            if a==KIND:
                assert ecx==CONTACT;ret(u,0,6);return
            if a==0x434b40:
                assert ecx in (WORLD,STAGE)
                if ecx==STAGE:
                    args=words(u,sp+4,9);assert args[1]==SOURCE and args[4]==self.index_blitter
                    self.staging_surfaces+=1
            if a==0x434b40 and ecx==WORLD:
                dest,source,bounds,box,blitter,z,gradient,brightness,extra=words(u,sp+4,9)
                assert source==STAGE and blitter==BLIT and gradient in (0,2) and extra==0
                self.gradient_calls[gradient]+=1
                self.observed.extend(['surface',*ints(u,dest,4),*ints(u,bounds,4),*ints(u,box,4),
                                      *ints(u,u.reg_read(UC_X86_REG_EDX),4),0x98,signed(z),gradient,signed(brightness),0,*self.stage()])
            if a==0x4350c0:
                # The old byte-only fixture required null depth/alpha globals.
                # Real final surfaces need initialized planes; zero flags still
                # select byte staging. Execute unchanged code in this new domain.
                assert ecx==STAGE and any(lo<=a and a+n<=hi for lo,hi in self.allowed)
                self.cache_counts[hex(a)]=self.cache_counts.get(hex(a),0)+1
                VoxelPartStagingOracle.service(self,u,a,n,ctx);return
            # Do not let earlier fixtures replace final drawing or scalar getters.
            if a in (0x6ff3e0,0x485aa0):
                if a==0x485aa0 and ecx==CVT:
                    assert words(u,sp+4,1)==[0x2800]
                    return
                if a==0x6ff3e0:
                    FootVoxelStagingOracle.service(self,u,a,n,ctx);return
        super().service(u,a,n,ctx)
    def draw_world(self,v):
        self.seed,self.map_mode,self.contact_mode,*unit=v
        assert self.map_mode in range(5) and self.contact_mode in (0,1)
        self.world_mode=True
        try:result=self.draw_unit(unit)
        finally:self.world_mode=False
        assert self.base_return is None
        for obj in (WORLD,ZSURF,ASURF):assert words(self.u,obj+12,1)==[0]
        color=struct.unpack('<'+'H'*(W*H),self.u.mem_read(COLOR,W*H*2))
        self.changed_pixels+=sum(v!=((i*37+self.seed*91)&65535) for i,v in enumerate(color))
        return [*result,'world',*[hashlib.sha256(bytes(self.u.mem_read(p,W*H*2))).hexdigest() for p in (COLOR,ZDATA,ADATA)]]
