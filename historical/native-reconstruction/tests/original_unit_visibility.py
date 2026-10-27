# SPDX-License-Identifier: GPL-3.0-or-later
"""Unchanged Unit +FC wrapper and complete Object gate, ordinary state only."""
import struct
from original_terrain_visibility import TerrainVisibilityOracle,ACTOR,TYPE,TACTICAL,INPUT,ARENA,STACK
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EAX
VIEWPORT=0x839630
class UnitVisibilityOracle(TerrainVisibilityOracle):
    def __init__(self,exe):
        super().__init__(exe);self.unit_active=False
        for a in [0x5d34e0,0x700e70,0x70a2d0]:
            self.service_hooks.append(self.u.hook_add(UC_HOOK_CODE,self.service,begin=a,end=a))
    def event(self,k,*values):self.events.extend([k,*values])
    def service(self,u,a,n,ctx):
        if not getattr(self,'unit_active',False):return
        sp=u.reg_read(UC_X86_REG_ESP);arg=lambda i:struct.unpack('<I',u.mem_read(sp+4+4*i,4))[0]
        if a==0x6a29d0:
            assert u.reg_read(UC_X86_REG_ECX)==TACTICAL
            assert STACK-0x2000<=arg(0)<=STACK-12 and STACK-0x2000<=arg(1)<=STACK-8
            assert self.result(arg(0),3)==list(self.coords)
            self.event('P',*self.coords);self.ints(arg(1),self.projected);self.ret(8,self.success);return
        assert u.reg_read(UC_X86_REG_ECX)==ACTOR
        if a==0x5d34e0:
            assert arg(0)==self.bounds and arg(2)==0
            self.event('g',arg(2)) # Unit wrapper discards supplied third argument.
        elif a==0x41b270:
            assert STACK-0x2000<=arg(0)<=STACK-12
            self.event('C',*self.coords) # Actual nested coordinate getter executes.
        elif a==0x70a2d0:self.event('t',1) # Actual Unit type leaf executes.
        elif a==0x700e70:
            assert arg(1)==self.bounds and STACK-0x2000<=arg(0)<=STACK-8
            self.event('D',*self.result(arg(0),2),*self.result(arg(1),4));self.ret(8)
        else:raise AssertionError(f'Unexpected Unit visibility service {a:#x}')
    def draw(self,state,gate,unused,success,alias,bounds,viewport,projected,coords):
        self.setup();self.put(ACTOR,0x7addf8);self.put(ACTOR+0x370,0)
        self.events=[];self.coords=coords;self.projected=projected;self.success=success
        self.bounds=VIEWPORT if alias else INPUT
        self.u.mem_write(ACTOR+0x74,bytes(state));self.ints(ACTOR+0x88,coords)
        self.ints(INPUT,bounds);self.ints(VIEWPORT,viewport)
        bypass,context,force=gate
        self.u.mem_write(0xa40d13,bytes([bypass]));self.put(0xb263d8,TYPE if context else 0)
        allowed=[(ACTOR+0x75,1)]+([] if alias else [(INPUT,16)])
        check=self.immutable_arena(allowed)
        def write(u,access,p,n,v,ctx):
            if p==ACTOR+0x75:
                assert n==1;self.event('r',v&255)
            elif self.bounds<=p<self.bounds+16:
                assert n==4 and (p-self.bounds)%4==0
                self.event('xywh'[(p-self.bounds)//4],self.signed(v))
        hook=self.u.hook_add(UC_HOOK_MEM_WRITE,write);self.unit_active=True
        try:self.checked_call(0x6ff350,[self.bounds,force,unused],ACTOR,
                              writes=[(ACTOR+0x75,1),(self.bounds,16)])
        finally:self.unit_active=False;self.u.hook_del(hook)
        check()
        return [self.u.reg_read(UC_X86_REG_EAX)&255,self.u.mem_read(ACTOR+0x75,1)[0],
                *self.result(self.bounds,4),*self.result(VIEWPORT,4),*self.events]
