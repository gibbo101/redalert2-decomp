# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete unchanged healthy single-turret Unit voxel root.

Flat Drive poses, Facing, matrix helpers, cache prechecks and Foot wrappers execute.
Visibility, surfaces, final Techno draws, ground height/map cell and final
brightness are bounded services. No raster pixels or actual pool execute here.
"""
import struct
from original_presentation import PresentationOracle,STACK
from original_foot_lit import words,ints,signed,ret
from verify_unit_voxel_draw import verify,RANGES,TAILS
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_ECX,UC_X86_REG_ESP
ARENA=0x2300000;UNIT=ARENA;TYPE=ARENA+0x1000;LOCO=ARENA+0x2000
VT=ARENA+0x3000;SVT=ARENA+0x4000;STAGE=ARENA+0x4100;WORLD=ARENA+0x4200
HVA=ARENA+0x5000;CELL=ARENA+0x6000;ENTRY=ARENA+0x7000
BOUNDS=ARENA+0xf000;FILL=ARENA+0xf010
SURFACE=0x83995c;DIRTY=0xad0490
SERVICES={0x6d8ce0,BOUNDS,0x6d1d00,0x6d79d0,0x41b390,0x6ff3e0,
          0x5d4810,0x548000,0x4cce70,0x6d21e0,FILL}
class UnitVoxelDrawOracle(PresentationOracle):
    def __init__(self,exe):
        verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(ARENA,0x20000)
        self.active=False;self.host_writes=0
        self.pitch_rotations=0;self.barrel_facing_reads=0;self.pose_builds=0;self.warm_pose_copies=0
        self.u.hook_add(UC_HOOK_CODE,self.service)
    def va(self,a):return a
    def write(self,p,data):
        if not (STACK-0x2000<=p and p+len(data)<=STACK or DIRTY<=p and p+len(data)<=DIRTY+16):
            raise AssertionError(f'Supplied Unit voxel write outside output {p:#x}/{len(data)}')
        self.u.mem_write(p,data);self.host_writes+=1
    def event(self,*v):self.events.extend(v)
    def part(self,p):
        assert p-TYPE in (0xb0,0xb8,0xc0,0x214,0x228,0x23c,0x250),hex(p)
        return p-TYPE
    def service(self,u,a,n,ctx):
        if not self.active:return
        assert a in SERVICES or any(p<=a<p+size for p,size in {**RANGES,**TAILS}.items()),f'Unexpected Unit voxel execution {a:#x}'
        sp=u.reg_read(UC_X86_REG_ESP);ecx=u.reg_read(UC_X86_REG_ECX)
        if a==0x590880:self.pitch_rotations+=1
        if a==0x4b8be0 and ecx==UNIT+0x2c8:self.barrel_facing_reads+=1
        if a==0x6ffbf8:self.pose_builds+=1
        if a==0x6ffbd2:self.warm_pose_copies+=1
        arg=lambda i:words(u,sp+4+4*i,1)[0]
        if a==0x6d8ce0:
            assert ecx==UNIT and arg(0)==0x2468;self.event('visible');ret(u,4,1)
        elif a==BOUNDS:
            assert ecx==STAGE;self.event('bounds')
            self.write(arg(0),struct.pack('<4i',*self.bounds));ret(u,4,arg(0))
        elif a==0x4a0050:self.event('body_pose') # Actual Drive executes.
        elif a==0x4a0500:self.event('shadow_pose') # Actual Drive executes.
        elif a==0x53d4d0:self.event('offset') # Actual Drive writes zero.
        elif a==0x70a3f0:
            assert ecx==TYPE+0x228;self.event('cache',0x228,signed(words(u,arg(0),1)[0]))
        elif a==0x70a350:
            assert ecx==TYPE+0x250;self.event('cache',0x250,signed(words(u,arg(0),1)[0]))
        elif a==0x6d83e0:self.event('multi') # Actual type query/test executes.
        elif a==0x6d1d00:
            assert ecx==UNIT and words(u,SURFACE,1)[0]==STAGE and u.mem_read(UNIT+0x5bb,1)==b'\1'
            model,frame,key,cache,clip,point,pose,brightness,flags=words(u,sp+4,9)
            assert STACK-0x2000<=pose and pose+48<=STACK
            self.event('lit',self.part(model),signed(frame),signed(key),self.part(cache),
                       *ints(u,clip,4),*ints(u,point,2),signed(brightness),flags,*words(u,pose,12))
            self.lit_count+=1
            # Explicit supplied successful draw output, not original raster/staging.
            self.write(DIRTY,struct.pack('<4i',70,80,2*self.lit_count,3*self.lit_count));ret(u,36)
        elif a==0x6d79d0:
            assert ecx==UNIT;self.event('brightness',signed(arg(0)));ret(u,4,self.brightness_result)
        elif a==0x41b390:
            assert ecx==UNIT;self.event('status');ret(u,0,0)
        elif a==0x6ff3e0:
            assert ecx==UNIT and words(u,SURFACE,1)[0]==STAGE and u.mem_read(UNIT+0x5bb,1)==b'\1'
            self.event('final',*[signed(v) if i!=0 else int(v==WORLD) for i,v in enumerate(words(u,sp+4,8))]);ret(u,32)
        elif a==0x5d4810:
            assert ecx==UNIT
            if 0x6ff690<=words(u,sp,1)[0]<0x7005a5:self.event('height')
            ret(u,0,0)
        elif a==0x548000:
            assert ecx==0x8324e0 and ints(u,arg(0),3)==self.coords
            self.event('cell',*self.coords);ret(u,4,CELL)
        elif a==0x4cce70:
            assert ecx==UNIT;self.event('predicate');ret(u,0,self.predicate)
        elif a==0x6d21e0:
            assert ecx==UNIT and words(u,SURFACE,1)[0]==WORLD and u.mem_read(UNIT+0x5bb,1)==b'\0'
            args=words(u,sp+4,11)
            self.event('shadow',self.part(args[0]),signed(args[1]),signed(args[2]),self.part(args[3]),
                       *ints(u,args[4],4),*ints(u,args[5],2),*words(u,args[6],12),signed(args[7]),
                       int(args[8]==STAGE),signed(args[9]),signed(args[10]))
            ret(u,44)
        elif a==FILL:
            assert ecx==STAGE and arg(1)==0;self.event('fill',*ints(u,arg(0),4));ret(u,8)
    def draw(self,values):
        pitched=len(values)==21
        pitch=values[-1] if pitched else 16384
        if pitched:values=values[:-1]
        body,turret,frame,frames,key_gate,warm,barrel,x,y,bx,by,bw,bh,brightness,self.brightness_result,self.predicate,camera,*self.coords=values
        assert frames>0 and warm in (range(4) if pitched else range(2)) and barrel in (0,1) and len(self.coords)==3
        warm_mask=warm if pitched else (3 if warm else 0)
        self.u.mem_write(ARENA,bytes(0x20000));self.u.mem_write(VT,bytes(self.u.mem_read(0x7addf8,0x600)))
        for p,v in [(UNIT,VT),(UNIT+0x564,LOCO+4),(UNIT+0x5ac,TYPE),(LOCO+4,0x7a04cc),(LOCO+12,UNIT),
                    (TYPE+0xb0,1),(TYPE+0xb4,HVA),(TYPE+0xb8,2),(TYPE+0xbc,HVA),(HVA+8,frames),
                    (TYPE+0xc0,3 if barrel else 0),(TYPE+0xc4,HVA if barrel else 0),
                    (TYPE+0x5a4,1),(UNIT+0x430,frame),(0xa35db4,0x2468),
                    (SURFACE,WORLD),(0xad0604,STAGE),(STAGE,SVT),(SVT+0x78,BOUNDS),(SVT+0x14,FILL)]:self.put(p,v)
        for off,heading in ((0x2e0,body),(0x2f8,turret),(0x2c8,pitch)):
            self.put(UNIT+off,heading);self.put(UNIT+off+4,heading)
        self.u.mem_write(TYPE+0xaab,b'\1');self.u.mem_write(0x839a58,bytes([key_gate]));self.bounds=[0,0,256,256]
        self.u.mem_write(UNIT+0x88,struct.pack('<3i',*self.coords))
        self.u.mem_write(0xad0478,struct.pack('<4i',9,11,13,15));self.u.mem_write(DIRTY,b'\xa7'*16)
        # Camera and ramp-zero identity are explicit supplied matrix inputs, not
        # a claim about the complete original startup or camera initialization.
        camera_matrix=([1,0,0,0,0,1,0,0,0,0,1,0] if camera==0 else
                       [0.5,0.25,-0.5,0.125,-0.25,0.5,0.25,-0.25,0.25,-0.5,0.5,0.5])
        self.u.mem_write(0xaf77a8,struct.pack('<12f',*camera_matrix))
        self.u.mem_write(0xaf8608,struct.pack('<12f',1,0,0,0,0,1,0,0,0,0,1,0))
        self.u.mem_write(0xad04e0,struct.pack('<d',0.09375))
        key=((((body>>10)+1)>>1)&31)<<5
        remainder=frame%frames if frame>=0 else -((-frame)%frames);key|=remainder&31
        turret_key=(key&0xffffffe0)|((((turret>>10)+1)>>1)&31);turret_key&=0xfffffc1f
        for off,entry,bit in ((0x228,ENTRY,1),(0x250,ENTRY+0x100,2)):
            hot=bool(warm_mask&bit)
            self.put(TYPE+off+4,hot);self.put(TYPE+off+0x10,entry if hot else 0)
            self.put(entry,turret_key);self.put(entry+4,1)
        self.put(0xb2b624,0);self.events=[];self.lit_count=0
        before=bytes(self.u.mem_read(ARENA,0x20000))
        def stores(u,access,p,n,v,ctx):
            if p==SURFACE:
                assert n==4 and v in (STAGE,WORLD);self.event('surface',int(v==STAGE))
            elif p==UNIT+0x5bb:
                assert n==1;self.event('staging',v&255)
            elif DIRTY<=p<DIRTY+16:
                assert n==4;self.event('dirty',(p-DIRTY)//4,signed(v))
        hook=self.u.hook_add(UC_HOOK_MEM_WRITE,stores);self.active=True
        try:self.checked_call(0x6ff690,[x,y,bx,by,bw,bh,brightness],UNIT,
                              writes=[(SURFACE,4),(DIRTY,16),(UNIT+0x5bb,1)])
        finally:self.active=False;self.u.hook_del(hook)
        after=bytearray(self.u.mem_read(ARENA,0x20000));after[0x5bb]=before[0x5bb]
        assert bytes(after)==before,'Unit voxel fixture arena changed'
        assert words(self.u,SURFACE,1)==[WORLD] and self.u.mem_read(UNIT+0x5bb,1)==b'\0'
        return self.events
