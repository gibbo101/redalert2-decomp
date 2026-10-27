# SPDX-License-Identifier: GPL-3.0-or-later
"""Actual patched static request caller with nested Terrain scan/eligibility."""
import struct
from original_static_terrain import StaticTerrainOracle,BASE,TYPES,LAYER,INPUT,STACK
from original_terrain_visibility import TACTICAL
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_ECX,UC_X86_REG_ESP
AREA=0x2b00000;CELLS=AREA+0x1000;REGIONS=AREA+0x10000
class StaticRedrawOracle(StaticTerrainOracle):
    def __init__(self,exe):
        super().__init__(exe);self.u.mem_map(AREA,0x20000)
        for a,p in [(0x6a20e0,0xabe4c0),(0x6a2170,0xabe4d0),(0x6a2440,0xabe490)]:
            self.checked_call(a,writes=[(p,8),(0xabe550,8)])
        self.scale=struct.unpack('<d',self.u.mem_read(0xabe490,8))[0]
        for a in [0x6a27a0,0x6a9e10]:self.service_hooks.append(self.u.hook_add(UC_HOOK_CODE,self.service,begin=a,end=a))
    def service(self,u,a,n,ctx):
        if not getattr(self,'active',False):return
        sp=u.reg_read(UC_X86_REG_ESP);arg=lambda i:struct.unpack('<I',u.mem_read(sp+4+4*i,4))[0]
        if a==0x6a27a0:
            assert u.reg_read(UC_X86_REG_ECX)==TACTICAL
            assert STACK-0x2000<=arg(0)<=STACK-8 and STACK-0x2000<=arg(1)<=STACK-12
            coords=self.result(arg(1),3);self.event('G',*coords);return
        if a==0x6a9e10:
            assert u.reg_read(UC_X86_REG_ECX)==TACTICAL and arg(0)==1
            assert arg(1)==arg(2) or (STACK-0x2000<=arg(1)<=STACK-16 and STACK-0x2000<=arg(2)<=STACK-16)
            self.event('S',arg(0),int(arg(1)==arg(2)),*self.result(arg(1),4),*self.result(arg(2),4));return
        super().service(u,a,n,ctx)
    def scan(self,cells,regions,full,origin,viewport,first,second,actors):
        self.count=len(actors);self.actors=[[0x24,*a] for a in actors];self.events=[];self.gate_actor=None
        assert len(cells)<=800 and len(regions)<=128 and self.count<=600
        arenas=[(BASE,self.count*0x300+0x120),(TYPES,self.count*0x300+32),(LAYER,self.count*4+32),
                (INPUT,64),(TACTICAL,0x1000),(AREA,0x20000)]
        for p,n in arenas:self.u.mem_write(p,bytes([0x5a])*n)
        for id,a in enumerate(self.actors):
            p=self.actor(id);t=TYPES+id*0x300
            self.put(p,0x7ad3cc);self.put(p+0xb0,t);self.u.mem_write(p+0x7d,bytes([a[1]]))
            self.u.mem_write(p+0x74,bytes(a[4:7]));self.u.mem_write(p+0xb5,bytes([a[3]]))
            self.put(t,0x7ad5e0);self.u.mem_write(t+0x283,bytes([a[2]]));self.ints(p+0x88,a[11:14])
        for id in range(self.count):self.put(LAYER+id*4,self.actor(id))
        self.put(0x8525ac,LAYER);self.put(0x8525b8,self.count)
        self.put(0x83996c,TACTICAL);self.ints(TACTICAL+0xb0,origin);self.put(TACTICAL+0xe0,len(cells))
        for i,(x,y) in enumerate(cells):
            self.put(TACTICAL+0xe4+i*4,CELLS+i*64)
            self.u.mem_write(CELLS+i*64+0x24,struct.pack('<hh',x,y))
        for i,r in enumerate(regions):self.ints(REGIONS+i*20,r)
        self.put(0xabe5b4,REGIONS);self.put(0xabe5c0,len(regions))
        self.ints(INPUT,[*first,*second]);self.ints(0x839630,viewport)
        self.u.mem_write(0xa40d13,b'\0');self.put(0xb263d8,TYPES)
        before=[bytes(self.u.mem_read(p,n)) for p,n in arenas]
        def write(u,access,p,n,v,ctx):
            if BASE<=p<BASE+self.count*0x300+0x120:
                id=self.identity(p-0x75);assert n==1;self.event('r',id,v&255)
            elif self.gate_actor is not None and self.gate_bounds<=p<self.gate_bounds+16:
                assert n==4 and (p-self.gate_bounds)%4==0
                self.event('xywh'[(p-self.gate_bounds)//4],self.gate_actor,self.signed(v))
        hook=self.u.hook_add(UC_HOOK_MEM_WRITE,write);self.active=True
        try:self.checked_call(0x6a4350,[INPUT,INPUT+16,full],TACTICAL,
                              writes=[(self.actor(id)+0x75,1) for id in range(self.count)])
        finally:self.u.hook_del(hook);self.active=False
        redraw=[]
        for (p,n),old in zip(arenas,before):
            after=bytearray(self.u.mem_read(p,n))
            if p==BASE:
                for id in range(self.count):
                    off=self.actor(id)+0x75-BASE;redraw.append(after[off]);after[off]=old[off]
            assert bytes(after)==old,'Static request arena changed outside redraw fields'
        assert self.result(0x839630,4)==list(viewport)
        return [*redraw,*self.events]
