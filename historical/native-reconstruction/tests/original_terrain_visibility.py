# SPDX-License-Identifier: GPL-3.0-or-later
"""Unchanged supplied-1.006 Terrain bounds/eligibility and rectangle routines.

Only projection, final draw, and (for isolated gate vectors) dimensions are
supplied services. Actual type/image/coordinate getters and dispatch execute.
"""
import hashlib
import struct
from pathlib import Path
from original_presentation import PresentationOracle, STACK
from compare_original import PATCHED_EXPECTED
from unicorn import UC_HOOK_CODE, UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_ESP, UC_X86_REG_ECX, UC_X86_REG_EAX, UC_X86_REG_EIP

ARENA=0x2100000
ACTOR=ARENA+0x100;TYPE=ARENA+0x500;TACTICAL=ARENA+0x900
IMAGE=ARENA+0x1000;INPUT=ARENA+0x6000;RESULT=ARENA+0x6100

class TerrainVisibilityOracle(PresentationOracle):
    def __init__(self,exe):
        if hashlib.sha256(Path(exe).read_bytes()).hexdigest()!=PATCHED_EXPECTED:
            raise ValueError('Terrain visibility requires exact supplied 1.006 engine')
        super().__init__(exe,allow_patched=True)
        self.u.mem_map(ARENA,0x10000)
        self.checked_call(0x6e2fe0,writes=[(0xac0358,16)])
        assert bytes(self.u.mem_read(0xac0358,16))==bytes(16)
        self.put(0x83996c,TACTICAL)
        self.events=[]
        self.draw_config=None
        # Install before any dimensions/getter translation. Unicorn can retain
        # an uninstrumented translated block after a later narrow hook is added.
        self.service_hooks=[self.u.hook_add(UC_HOOK_CODE,self.service,begin=p,end=p) for p in
                            [0x6e4910,0x41b270,0x6a29d0,0x6e3990]]
    def va(self,address):return address # This class is patched-only, never relocation.
    def ret(self,pop,value=0):
        sp=self.u.reg_read(UC_X86_REG_ESP)
        self.u.reg_write(UC_X86_REG_EAX,value&0xffffffff)
        self.u.reg_write(UC_X86_REG_ESP,sp+4+pop)
        self.u.reg_write(UC_X86_REG_EIP,struct.unpack('<I',self.u.mem_read(sp,4))[0])
    def setup(self):
        self.u.mem_write(ARENA,bytes([0x5a])*0x10000)
        self.put(ACTOR,0x7ad3cc);self.put(ACTOR+0xb0,TYPE)
        self.put(TYPE,0x7ad5e0);self.put(TYPE+0xa4,0)
        self.put(0x83996c,TACTICAL)
    def ints(self,p,values):self.u.mem_write(p,struct.pack('<'+'i'*len(values),*values))
    def result(self,p,n):return list(struct.unpack('<'+'i'*n,self.u.mem_read(p,n*4)))
    def immutable_arena(self,allowed):
        # Include whole objects, metadata, input/output guards and unused tails.
        before=bytes(self.u.mem_read(ARENA,0x10000))
        def check():
            after=bytearray(self.u.mem_read(ARENA,0x10000))
            for p,n in allowed:after[p-ARENA:p-ARENA+n]=before[p-ARENA:p-ARENA+n]
            assert bytes(after)==before,'Original visibility arena changed outside contract'
        return check
    def intersection(self,a,b,mask,x,y):
        self.setup();self.ints(INPUT,[*a,*b,x,y])
        check=self.immutable_arena([(RESULT,16),(INPUT+32,8)])
        self.checked_call(0x41fdf0,[INPUT+16,INPUT+32 if mask&1 else 0,INPUT+36 if mask&2 else 0],
                          RESULT,INPUT,writes=[(RESULT,16),(INPUT+32,4),(INPUT+36,4)])
        assert self.u.reg_read(UC_X86_REG_EAX)==RESULT
        check();return self.result(RESULT,4)+self.result(INPUT+32,2)
    def shape(self,image):
        if image is None:return
        width,height,frames=image
        assert len(frames)<=512
        blob=bytearray(struct.pack('<4H',0,width&65535,height&65535,len(frames)))
        for crop in frames:blob+=struct.pack('<4H4I',*[v&65535 for v in crop],3,0,0,0)
        self.u.mem_write(IMAGE,bytes(blob));self.put(TYPE+0xa4,IMAGE)
    def bounds(self,screen,origin,image):
        self.setup();self.shape(image)
        self.ints(ACTOR+0xc0,screen);self.ints(TACTICAL+0xb0,origin)
        check=self.immutable_arena([(RESULT,16)])
        self.checked_call(0x6e4910,[RESULT],ACTOR,writes=[(RESULT,16)])
        assert self.u.reg_read(UC_X86_REG_EAX)==RESULT
        check();return self.result(RESULT,4)
    def draw(self,state,gate,unused,project_success,bounds,viewport,shape,projected,coords,actual_shape=None):
        self.setup();self.events=[]
        self.u.mem_write(ACTOR+0x74,bytes(state))
        self.ints(ACTOR+0x88,coords);self.ints(INPUT,bounds);self.ints(0x839630,viewport)
        if actual_shape is not None:
            screen,origin,image=actual_shape;self.shape(image)
            self.ints(ACTOR+0xc0,screen);self.ints(TACTICAL+0xb0,origin)
            shape=None # Actual nested render-dimensions/type/image dispatch executes.
        bypass,context,force=gate
        self.u.mem_write(0xa40d13,bytes([bypass]));self.put(0xb263d8,TYPE if context else 0)
        check=self.immutable_arena([(ACTOR+0x75,1),(INPUT,16)])
        self.draw_config=(shape,projected,coords,project_success)
        def event(k,v):self.events.extend([k,v])
        def write(u,access,p,n,value,ctx):
            if p==ACTOR+0x75:
                assert n==1;event('r',value&255)
            elif INPUT<=p<INPUT+16:
                assert n==4 and (p-INPUT)%4==0
                event('xywh'[(p-INPUT)//4],self.signed(value))
        hooks=[self.u.hook_add(UC_HOOK_MEM_WRITE,write)]
        try:
            self.checked_call(0x6e4430,[INPUT,force,unused],ACTOR,
                              writes=[(ACTOR+0x75,1),(INPUT,16)])
        finally:
            for h in hooks:self.u.hook_del(h)
            self.draw_config=None
        check()
        return [self.u.reg_read(UC_X86_REG_EAX)&255,self.u.mem_read(ACTOR+0x75,1)[0],
                *self.result(INPUT,4),*self.events]
    def service(self,u,address,size,ctx):
        if self.draw_config is None:return
        shape,projected,coords,success=self.draw_config
        sp=u.reg_read(UC_X86_REG_ESP)
        arg=lambda i:struct.unpack('<I',u.mem_read(sp+4+4*i,4))[0]
        def event(k,v):self.events.extend([k,v])
        if address==0x6e4910:
            assert u.reg_read(UC_X86_REG_ECX)==ACTOR
            assert STACK-0x2000<=arg(0)<=STACK-16
            event('B',0)
            if shape is not None:self.ints(arg(0),shape);self.ret(4,arg(0))
        elif address==0x41b270:
            assert u.reg_read(UC_X86_REG_ECX)==ACTOR
            for v in coords:event('C',v) # Actual nested coordinate getters execute.
        elif address==0x6a29d0:
            assert u.reg_read(UC_X86_REG_ECX)==TACTICAL
            assert STACK-0x2000<=arg(0)<=STACK-12 and STACK-0x2000<=arg(1)<=STACK-8
            assert self.result(arg(0),3)==list(coords)
            for v in coords:event('P',v)
            self.ints(arg(1),projected);self.ret(8,success)
        elif address==0x6e3990:
            assert u.reg_read(UC_X86_REG_ECX)==ACTOR and arg(1)==INPUT
            for v in self.result(arg(0),2)+self.result(arg(1),4):event('D',v)
            self.ret(8)
    @staticmethod
    def signed(v):return struct.unpack('<i',struct.pack('<I',v&0xffffffff))[0]
