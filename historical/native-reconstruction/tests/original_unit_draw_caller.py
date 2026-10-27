# SPDX-License-Identifier: GPL-3.0-or-later
"""Unmodified ordinary patched Unit DrawIt caller, nested map/height/registry.

Layer, ground, virtual visibility/alternate selection, final VXL/SHP and Foot
decoration are explicit read-only services. No original instruction is patched.
"""
import hashlib,struct
from pathlib import Path
from original_presentation import PresentationOracle,STACK
from compare_original import PATCHED_EXPECTED
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_ESP,UC_X86_REG_ECX,UC_X86_REG_EAX,UC_X86_REG_EIP
ARENA=0x2300000;ACTOR=ARENA+0x100;TYPE=ARENA+0x1000;ALT=ARENA+0x2000
CELL=ARENA+0x3000;RULES=ARENA+0x4000;TACTICAL=ARENA+0x6000;INPUT=ARENA+0x8000
TABLE=0x2400000;REGISTRY=0xabe5f8;FLAGS=0xad0578;SHAPE=0xad0468
def trunc(v):return v//256 if v>=0 else -((-v)//256)
class UnitDrawCallerOracle(PresentationOracle):
    def __init__(self,exe):
        if hashlib.sha256(Path(exe).read_bytes()).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact supplied 1.006 engine required')
        super().__init__(exe,allow_patched=True)
        self.u.mem_map(ARENA,0x20000);self.u.mem_map(TABLE,0x100000)
        self.table=struct.pack('<I',CELL)*262144;self.u.mem_write(TABLE,self.table)
        self.checked_call(0x6e2fe0,writes=[(0xac0358,16)])
        self.active=False;self.in_draw=False;self.events=[]
        self.hooks=[self.u.hook_add(UC_HOOK_CODE,self.service,begin=a,end=a) for a in
                    [0x70a2d0,0x5d34e0,0x41b270,0x6a29d0,0x5956c0,0x41b320,0x4c8fa0,0x6aa510,0x55a280,0x548000,0x548070,
                     0x4cce70,0x6d8ce0,0x709bb0,0x6ff690,0x7005b0,0x4c9bc0,0x6cc020]]
        self.current_house=0x2468;self.real_type_state=False
    def va(self,a):return a
    def ints(self,p,values):self.u.mem_write(p,struct.pack('<'+'i'*len(values),*values))
    def result(self,p,n):return list(struct.unpack('<'+'i'*n,self.u.mem_read(p,n*4)))
    @staticmethod
    def signed(v):return struct.unpack('<i',struct.pack('<I',v&0xffffffff))[0]
    def event(self,k,*v):self.events.extend([k,*v])
    def ret(self,pop,value=0):
        sp=self.u.reg_read(UC_X86_REG_ESP);target=struct.unpack('<I',self.u.mem_read(sp,4))[0]
        self.u.reg_write(UC_X86_REG_EAX,value&0xffffffff);self.u.reg_write(UC_X86_REG_ESP,sp+4+pop);self.u.reg_write(UC_X86_REG_EIP,target)
    def service(self,u,a,n,ctx):
        if not self.active:return
        sp=u.reg_read(UC_X86_REG_ESP);ecx=u.reg_read(UC_X86_REG_ECX)
        arg=lambda i:struct.unpack('<I',u.mem_read(sp+4+4*i,4))[0]
        if a==0x70a2d0:
            assert ecx==ACTOR;self.event('t',1) # Actual Unit type leaf executes.
        elif a==0x5d34e0:
            assert ecx==ACTOR and arg(0)==INPUT+8 and arg(2)==0;self.event('g',0)
        elif a==0x41b270:
            assert ecx==ACTOR;self.event('Q',*self.coords)
        elif a==0x6a29d0:
            assert ecx==TACTICAL and self.result(arg(0),3)==list(self.coords)
            assert STACK-0x2000<=arg(1)<=STACK-8
            self.event('P',*self.coords);self.ints(arg(1),self.projected);self.ret(8,self.success)
        elif a==0x5956c0:
            assert ecx==0x7f8f80;self.event('L');self.ret(0,self.loaded)
        elif a==0x41b320:
            assert ecx==ACTOR;self.event('C',trunc(self.coords[0]));self.event('C',trunc(self.coords[1]))
        elif a==0x4c8fa0:
            assert ecx==ACTOR and arg(0)==arg(1)==0;self.event('Y');self.ret(8,self.layer)
        elif a==0x6aa510:
            assert ecx==TACTICAL and arg(0)==ACTOR
            if self.in_draw:self.event('R',self.signed(arg(1)),self.signed(arg(2))) # Actual registry executes.
        elif a==0x55a280:
            assert ecx==0x8324e0 and self.result(arg(0),3)==list(self.coords)
            self.event('G',*self.coords);self.ret(4,self.ground)
        elif a==0x548000:
            assert ecx==0x8324e0 and self.result(arg(0),3)==list(self.coords);self.event('A',*self.coords)
        elif a==0x548070:
            assert ecx==0x8324e0
            cell=struct.unpack('<2h',u.mem_read(arg(0),4));assert cell==(trunc(self.coords[0]),trunc(self.coords[1]))
            self.event('c',*cell) # Actual table lookup executes.
        elif a==0x4cce70:
            assert ecx==ACTOR;self.event('p');self.ret(0,self.predicate)
        elif a==0x6d8ce0:
            assert ecx==ACTOR and arg(0)==self.current_house;self.event('V')
            if not self.real_type_state:self.ret(4,self.visible)
        elif a==0x709bb0:
            assert ecx==ACTOR and arg(0)==1;self.event('a',1)
            if not self.real_type_state:self.ret(4,ALT)
        elif a in (0x6ff690,0x7005b0):
            assert ecx==ACTOR
            self.event('v' if a==0x6ff690 else 's',*[self.signed(arg(i)) for i in range(7)])
            self.ret(28)
        elif a==0x4c9bc0:
            assert ecx==ACTOR and arg(1)==INPUT+8
            self.event('F',*self.result(arg(0),2),*self.result(arg(1),4));self.ret(8)
        elif a==0x6cc020:
            assert ecx==ACTOR;self.event('Z');self.ret(0)
        else:raise AssertionError(f'Unexpected Unit caller service {a:#x}')
    def setup(self,count,origin,width,height):
        assert 0<=count<=500
        self.u.mem_write(ARENA,b'\x5a'*0x20000);self.u.mem_write(REGISTRY,b'\xa7'*6000)
        self.put(0x83996c,TACTICAL);self.put(TACTICAL+0xdb0,count);self.ints(TACTICAL+0xb0,origin)
        self.put(0x839638,width);self.put(0x83963c,height);self.events=[]
    def call_audited(self,start,args,ecx,count,arena_writes=()):
        before=bytes(self.u.mem_read(ARENA,0x20000));entries=bytes(self.u.mem_read(REGISTRY,6000))
        allowed=[(REGISTRY+count*12,12)] if count<500 else []
        writes=[(TACTICAL+0xdb0,4),*arena_writes,*allowed]
        def write(u,access,p,n,v,ctx):
            if p==FLAGS:assert n==1;self.event('i',v&255)
            elif p==SHAPE:assert n==4;self.event('h',self.signed(v))
            elif p==ACTOR+0x5ac:assert n==4 and v==TYPE;self.event('T',0)
            elif REGISTRY<=p<REGISTRY+6000:
                assert n==4 and (p-REGISTRY)//12==count
                self.event('rxy'[(p-REGISTRY)%12//4],17 if p==REGISTRY+count*12 else self.signed(v))
            elif p==TACTICAL+0xdb0:assert n==4;self.event('n',self.signed(v))
            elif p==ACTOR+0x75:assert n==1;self.event('r',v&255)
            elif INPUT+8<=p<INPUT+24:
                assert n==4 and (p-INPUT-8)%4==0;self.event('xywh'[(p-INPUT-8)//4],self.signed(v))
        hook=self.u.hook_add(UC_HOOK_MEM_WRITE,write);self.active=True
        try:self.checked_call(start,args,ecx,writes=writes)
        finally:self.active=False;self.u.hook_del(hook)
        after=bytearray(self.u.mem_read(ARENA,0x20000))
        for p,n in writes:
            if ARENA<=p and p+n<=ARENA+0x20000:after[p-ARENA:p-ARENA+n]=before[p-ARENA:p-ARENA+n]
        assert bytes(after)==before,'Unit caller fixture arena changed'
        tail=bytearray(self.u.mem_read(REGISTRY,6000))
        for p,n in allowed:tail[p-REGISTRY:p-REGISTRY+n]=entries[p-REGISTRY:p-REGISTRY+n]
        assert bytes(tail)==entries,'Unit registry capacity tail changed'
    def registry(self,count,x,y,ox,oy,width,height):
        self.in_draw=False
        self.setup(count,(ox,oy),width,height)
        self.call_audited(0x6aa510,[ACTOR,x,y],TACTICAL,count)
        accepted=self.u.reg_read(UC_X86_REG_EAX)&255;after=self.result(TACTICAL+0xdb0,1)[0]
        entry=self.result(REGISTRY+count*12,3) if accepted else [0,0,0]
        if accepted:assert entry[0]==ACTOR;entry[0]=17
        return [accepted,after,*entry,*self.events]
    def prepare_draw_state(self):pass
    def draw(self,values,nested=None,timer=None):
        self.in_draw=True
        (flags,shape,self.loaded,x,y,bx,by,bw,bh,cx,cy,cz,offset,add14,index,self.layer,self.ground,
         ambient,extra,cell_flags,self.predicate,self.visible,voxel,model,alt_voxel,alt_model,
         count,ox,oy,width,height)=values
        self.setup(count,(ox,oy),width,height);self.coords=(cx,cy,cz)
        assert 0<=trunc(cx)<512 and 0<=trunc(cy)<512 and not cell_flags&0x100
        self.put(ACTOR,0x7addf8);self.put(ACTOR+0x5ac,TYPE);self.ints(ACTOR+0x88,self.coords)
        for off,value in [(0x59e,offset),(0x37c,add14),(0x574,index),(0x79,0)]:self.u.mem_write(ACTOR+off,bytes([value&255]))
        for off,value in [(0x5b4,-1),(0x314,-1),(0x31c,0)]:self.put(ACTOR+off,value)
        frame,start,duration=timer or (0,-1,0)
        self.put(0xa40d2c,frame);self.put(ACTOR+0x314,start);self.put(ACTOR+0x31c,duration)
        for p,v,m in [(TYPE,voxel,model),(ALT,alt_voxel,alt_model)]:
            self.u.mem_write(p+0xba6,b'\0');self.u.mem_write(p+0x206,bytes([v&255]));self.put(p+0xb0,0x1234 if m else 0)
        self.u.mem_write(CELL+0x10a,struct.pack('<h',ambient));self.put(CELL+0x140,cell_flags)
        self.put(0x8324e0+0x138,TABLE);self.put(0x8324e0+0x13c,262144)
        self.put(0x839848,RULES);self.put(RULES+0x1418,extra);self.put(0xa35db4,0x2468)
        self.current_house=0x2468;self.prepare_draw_state()
        self.u.mem_write(FLAGS,bytes([flags&255]));self.put(SHAPE,shape);self.put(0xad057c,0)
        self.ints(INPUT,[x,y,bx,by,bw,bh])
        writes=[(ACTOR+0x5ac,4),(FLAGS,1),(SHAPE,4)]
        if nested is not None:
            on_map,redraw,limbo,bypass,context,force,self.success=nested;self.projected=(x,y)
            self.u.mem_write(ACTOR+0x74,bytes([on_map,redraw,limbo]));self.put(ACTOR+0x370,0)
            self.u.mem_write(0xa40d13,bytes([bypass]));self.put(0xb263d8,TYPE if context else 0)
            self.ints(0x839630,[0,0,width,height]);writes.extend([(ACTOR+0x75,1),(INPUT+8,16)])
            self.call_audited(0x6ff350,[INPUT+8,force,0x1234],ACTOR,count,writes)
            prefix=[self.u.reg_read(UC_X86_REG_EAX)&255,self.u.mem_read(ACTOR+0x75,1)[0],*self.result(INPUT+8,4)]
        else:
            self.call_audited(0x700e70,[INPUT,INPUT+8],ACTOR,count,writes);prefix=[]
        assert self.result(ACTOR+0x5ac,1)[0]==TYPE
        return [*prefix,self.u.mem_read(FLAGS,1)[0],struct.unpack('<I',self.u.mem_read(SHAPE,4))[0],
                self.result(TACTICAL+0xdb0,1)[0],*self.events]
    def check_table(self):assert bytes(self.u.mem_read(TABLE,0x100000))==self.table
