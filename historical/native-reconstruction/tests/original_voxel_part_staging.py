# SPDX-License-Identifier: GPL-3.0-or-later
"""Nest original byte Convert selector and BSurface copy inside the part root."""
import hashlib,struct
from original_voxel_part import VoxelPartOracle,animation,ACTOR,VT,MODEL,HVA,TRANSFORMS,STAGE,V2C0,V2C4,PREDICATE,ADJUST
from original_presentation import ARG
from original_foot_lit import words,ints,signed
from original_staging import StagingOracle
from original_composition import CompositionOracle
from staging_profiles import address
from unicorn.x86_const import UC_X86_REG_ECX,UC_X86_REG_EDX,UC_X86_REG_ESP
CONVERTER=0x1600600;DEST=0x1700000;SOURCE=0xae0db8
class VoxelPartStagingOracle(VoxelPartOracle):
    surface=CompositionOracle.surface
    guarded_heap_write=StagingOracle.guarded_heap_write
    indexed_converter=StagingOracle.indexed_converter
    def va(self,a):
        if a in (0x6d24e0,0x717040):return a
        return address(self.profile,a)
    def call(self,guest_va,args=(),ecx=0,edx=0,budget=4000000):
        if guest_va==self.va(0x483430):budget=12000000
        return super().call(guest_va,args,ecx,edx,budget)
    def __init__(self,exe,assets,palette):
        super().__init__(exe,assets);self.u.mem_map(0x1600000,0x400000)
        colors=[b<<2 for b in palette];self.mapping=self.indexed_converter(colors,colors)
        self.selected=[];self.draws=0;self.spans=0
    def service(self,u,a,n,ctx):
        if not self.active:return
        if a==0x485aa0:
            assert u.reg_read(UC_X86_REG_ECX)==CONVERTER
            assert words(u,u.reg_read(UC_X86_REG_ESP)+4,1)==[0]
            self.selected.append(a);return
        if a==0x49f3a0:
            assert u.reg_read(UC_X86_REG_ECX)==STAGE and u.reg_read(UC_X86_REG_EDX)==CONVERTER
            source,box,point,clip,zero,blitter,c0,c4,brightness,remainder=words(u,u.reg_read(UC_X86_REG_ESP)+4,10)
            assert source==SOURCE and zero==remainder==0 and blitter==self.index_blitter
            self.draws+=1;return
        if a==0x486310:self.spans+=1
        super().service(u,a,n,ctx)
    def draw_staging(self,v):
        seed,part,mode,frame,x,y,bx,by,bw,bh,brightness,*pose=v
        assert len(pose)==12
        self.u.mem_write(ACTOR,bytes(0x10000));self.u.mem_write(VT,bytes(self.u.mem_read(0x7addf8,0x600)))
        self.put(ACTOR,VT);self.put(ACTOR+0x5bb,1)
        for off,target in ((0xc0,PREDICATE),(0x3d0,ADJUST),(0x2c0,V2C0),(0x2c4,V2C4)):self.put(VT+off,target)
        self.house=0;self.predicate=0;self.adjusted=0;self.c0=-1;self.c4=2
        transforms=animation(mode)
        for p,value in ((MODEL,self.models[part]),(MODEL+4,HVA if mode else 0),(HVA+4,1),(HVA+8,len(transforms)),(HVA+12,TRANSFORMS),
                        (0x83995c,STAGE),(0xad0604,STAGE),(0xad0608,CONVERTER)):
            self.put(p,value)
        self.u.mem_write(TRANSFORMS,struct.pack('<'+'f'*12*len(transforms),*[a for m in transforms for a in m]))
        self.u.mem_write(ARG,struct.pack('<12I',*pose));self.u.mem_write(ARG+0x200,struct.pack('<6i',x,y,bx,by,bw,bh))
        self.u.mem_write(0x839a70,struct.pack('<12f',1,0,0,0,0,1,0,0,0,0,1,0))
        self.u.mem_write(self.va(0xadc068),self.vpl[784:]);self.put(self.va(0xade070),0);self.put(self.va(0xade074),1);self.put(self.va(0x7e35d0),1)
        self.surface(STAGE,256,256,1,DEST);self.surface(SOURCE,256,256,1,self.va(0xacae68))
        initial=bytes((i*37+seed*19)&255 for i in range(65536));self.u.mem_write(DEST,initial)
        angle=words(self.u,self.va(0x785cf0),1)[0]
        self.checked_call(0x70ca10,[angle],writes=[(self.va(0x821d80),12),(self.va(0x821dcc),16)])
        outputs=[(self.va(p),size) for p,size in ((0x7e35d0,4),(0xab84d0,65548),(0xac8710,8),(0xac8838,12),
                 (0xac8848,136),(0xacaa50,20),(0xacae68,65536),(0xae0470,48),(0xae0870,256))]
        self.events=[];self.active=True
        immutable=[(ACTOR,0x3000),(STAGE,12),(STAGE+16,0x10000-0x3010),
                   (SOURCE,12),(SOURCE+16,12),(CONVERTER,0x17c),
                   (ARG,48),(ARG+0x200,24),(0x839a70,48),*self.heap_inputs()]
        try:self.checked_call(0x6d24e0,[ARG+0x100,MODEL,ARG,ARG+0x200,ARG+0x208,frame,0,brightness],ACTOR,
              writes=[(ARG+0x100,24),*outputs,(DEST,65536),(STAGE+12,4),(SOURCE+12,4),(CONVERTER+0x17c,4)],inputs=immutable)
        finally:self.active=False
        self.check_heap()
        assert words(self.u,STAGE+12,1)==words(self.u,SOURCE+12,1)==[0]
        assert words(self.u,CONVERTER+0xc,1)==[self.index_blitter]
        crop=ints(self.u,ARG+0x100,6);walk=signed(words(self.u,self.va(0xac8848)+12,1)[0]);corners=words(self.u,self.va(0xac8848)+0x28,24)
        return ['result',*crop,walk,*corners,
                hashlib.sha256(bytes(self.u.mem_read(self.va(0xacae68),65536))).hexdigest(),
                hashlib.sha256(bytes(self.u.mem_read(DEST,65536))).hexdigest()]
