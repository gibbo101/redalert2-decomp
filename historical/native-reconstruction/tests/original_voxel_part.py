# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete staged Techno part wrapper with actual original lit raster children."""
import hashlib,struct
from original_raster import RasterOracle
from original_presentation import ARG,STACK
from original_foot_lit import words,ints,signed,ret
from verify_voxel_part import verify
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_ECX,UC_X86_REG_EDX,UC_X86_REG_ESP
ACTOR=0x1100000;VT=ACTOR+0x1000;MODEL=ACTOR+0x2000;HVA=ACTOR+0x2100;TRANSFORMS=ACTOR+0x2200
STAGE=ACTOR+0x3000;CONVERTER=ACTOR+0x3100;BLITTER=ACTOR+0x3200
V2C0=ACTOR+0xf000;V2C4=ACTOR+0xf010;PREDICATE=ACTOR+0xf020;ADJUST=ACTOR+0xf030
def animation(mode):
    result=[]
    for n in range(3 if mode==2 else 1):
        m=[1.,0.,0.,0.,0.,1.,0.,0.,0.,0.,1.,0.]
        if mode==2:m[0]=.5+.25*n;m[5]=1.25;m[3]=.375*n;m[7]=-.625*n
        result.append(m)
    return result
class VoxelPartOracle(RasterOracle):
    def __init__(self,exe,assets):
        verify(exe.read_bytes());super().__init__(exe,allow_patched=True)
        self.models=[self.load(assets/name) for name in ('htnk.vxl','htnktur.vxl','htnkbarl.vxl')]
        self.vpl=(assets/'voxels.vpl').read_bytes();self.active=False;self.events=[];self.actual_calls={}
        self.u.hook_add(UC_HOOK_CODE,self.service)
    def va(self,a):
        if a in (0x6d24e0,0x717040):return a
        return super().va(a)
    def event(self,*v):self.events.extend(v)
    def service(self,u,a,n,ctx):
        if not self.active:return
        if a in (0x7170d0,0x7171d0,0x7174c0,0x7178e0,0x591180):
            self.actual_calls[hex(a)]=self.actual_calls.get(hex(a),0)+1
        sp=u.reg_read(UC_X86_REG_ESP);ecx=u.reg_read(UC_X86_REG_ECX);args=lambda count:words(u,sp+4,count)
        if a in (0x6d6df0,0x6d6e00,0x70a2d0):
            assert ecx==ACTOR;self.event({0x6d6df0:'f204',0x6d6e00:'f205',0x70a2d0:'kind'}[a]);return
        if a==0x4f52b0:
            assert ecx==0;self.event('house');ret(u,0,self.house)
        elif a in (PREDICATE,ADJUST,V2C0,V2C4):
            assert ecx==ACTOR
            if a==PREDICATE:self.event('c0');ret(u,0,self.predicate)
            elif a==ADJUST:self.event('adjust',args(1)[0]);ret(u,4,self.adjusted)
            elif a==V2C0:self.event('v2c0');ret(u,0,self.c0)
            else:self.event('v2c4');ret(u,0,self.c4)
        elif a==0x485aa0:
            assert ecx==CONVERTER;self.event('select',args(1)[0]);ret(u,4,BLITTER)
        elif a==0x49f3a0:
            assert ecx==STAGE and u.reg_read(UC_X86_REG_EDX)==CONVERTER
            source,box,point,clip,zero,blitter,c0,c4,brightness,remainder=args(10)
            assert source==0xae0db8 and zero==remainder==0 and blitter==BLITTER
            assert STACK-0x2000<=box and box+16<=STACK and STACK-0x2000<=point and point+8<=STACK
            self.event('draw',*ints(u,box,4),*ints(u,point,2),*ints(u,clip,4),signed(c0),signed(c4),signed(brightness),0)
            ret(u,40)
    def draw(self,v):
        (part,mode,frame,x,y,bx,by,bw,bh,brightness,flags,f204,f205,self.house,self.predicate,
         self.adjusted,self.c4,self.c0,*pose)=v
        assert len(pose)==12 and flags&8==0 and self.adjusted&8==0
        self.u.mem_write(ACTOR,bytes(0x10000));self.u.mem_write(VT,bytes(self.u.mem_read(0x7addf8,0x600)))
        self.put(ACTOR,VT);self.put(ACTOR+0x5bb,1)
        self.u.mem_write(ACTOR+0x204,bytes([f204&255,f205&255]))
        for off,target in ((0xc0,PREDICATE),(0x3d0,ADJUST),(0x2c0,V2C0),(0x2c4,V2C4)):self.put(VT+off,target)
        transforms=animation(mode)
        for p,value in ((MODEL,self.models[part]),(MODEL+4,HVA if mode else 0),(HVA+4,1),(HVA+8,len(transforms)),(HVA+12,TRANSFORMS),
                        (0x83995c,STAGE),(0xad0604,STAGE),(0xad0608,CONVERTER)):
            self.put(p,value)
        self.u.mem_write(TRANSFORMS,struct.pack('<'+'f'*12*len(transforms),*[x for m in transforms for x in m]))
        self.u.mem_write(ARG,struct.pack('<12I',*pose));self.u.mem_write(ARG+0x200,struct.pack('<6i',x,y,bx,by,bw,bh))
        self.u.mem_write(0x839a70,struct.pack('<12f',1,0,0,0,0,1,0,0,0,0,1,0))
        self.u.mem_write(self.va(0xadc068),self.vpl[784:]);self.put(self.va(0xade070),0);self.put(self.va(0xade074),1);self.put(self.va(0x7e35d0),1)
        angle=words(self.u,self.va(0x785cf0),1)[0]
        self.checked_call(0x70ca10,[angle],writes=[(self.va(0x821d80),12),(self.va(0x821dcc),16)])
        outputs=[(self.va(p),size) for p,size in ((0x7e35d0,4),(0xab84d0,65548),(0xac8710,8),(0xac8838,12),
                 (0xac8848,136),(0xacaa50,20),(0xacae68,65536),(0xae0470,48),(0xae0870,256))]
        self.events=[];self.active=True
        try:self.checked_call(0x6d24e0,[ARG+0x100,MODEL,ARG,ARG+0x200,ARG+0x208,frame,flags,brightness],ACTOR,
              writes=[(ARG+0x100,24),*outputs],inputs=[(ACTOR,0x10000),(ARG,48),(ARG+0x200,24),(0x839a70,48),*self.heap_inputs()])
        finally:self.active=False
        self.check_heap();crop=ints(self.u,ARG+0x100,6)
        walk=signed(words(self.u,self.va(0xac8848)+12,1)[0]);corners=words(self.u,self.va(0xac8848)+0x28,24)
        return [*self.events,'result',*crop,walk,*corners,hashlib.sha256(bytes(self.u.mem_read(self.va(0xacae68),65536))).hexdigest()]
