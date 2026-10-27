# SPDX-License-Identifier: GPL-3.0-or-later
"""Unchanged supplied-1.006 reverse ground-layer static Terrain region scan.

Actual alive predicate, complete eligibility and nested coordinates execute.
Type IDs for non-Terrain, render bounds, projection and final drawing are services.
"""
import struct
from original_terrain_visibility import TerrainVisibilityOracle,STACK
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_ECX,UC_X86_REG_ESP

BASE=0x2200000;TYPES=BASE+0x100000;LAYER=BASE+0x1e0000;INPUT=BASE+0x1f1000
class StaticTerrainOracle(TerrainVisibilityOracle):
    def __init__(self,exe):
        super().__init__(exe);self.u.mem_map(BASE,0x200000)
        self.active=False;self.gate_actor=None
        for address in [0x6e4b00,0x5d4f10,0x6e4430,0x6e4561,0x6e456d]:
            self.service_hooks.append(self.u.hook_add(UC_HOOK_CODE,self.service,begin=address,end=address))
    @staticmethod
    def actor(id):return BASE+0x100+id*0x300
    def identity(self,p):
        assert (p-BASE-0x100)%0x300==0 and 0<=p-BASE-0x100<self.count*0x300,hex(p)
        return (p-BASE-0x100)//0x300
    def event(self,kind,id,*values):self.events.extend([kind,id,*values])
    def service(self,u,address,size,ctx):
        if not getattr(self,'active',False):return
        if address in [0x6e4561,0x6e456d]:self.gate_actor=None;return
        sp=u.reg_read(UC_X86_REG_ESP)
        arg=lambda n:struct.unpack('<I',u.mem_read(sp+4+4*n,4))[0]
        if address==0x6a29d0:
            id=self.gate_actor;assert id is not None
            coords=self.actors[id][11:14]
            assert self.result(arg(0),3)==list(coords)
            assert STACK-0x2000<=arg(1)<=STACK-8
            self.event('P',id,*coords);self.ints(arg(1),self.actors[id][14:16]);self.ret(8,0)
            return
        id=self.identity(u.reg_read(UC_X86_REG_ECX));a=self.actors[id]
        if address==0x6e4b00:
            self.event('T',id)
            if a[0]!=0x24:self.ret(0,a[0])
        elif address==0x5d4f10:self.event('A',id) # Actual byte-zero predicate executes.
        elif address==0x6e4910:
            assert STACK-0x2000<=arg(0)<=STACK-16
            self.event('B',id);self.ints(arg(0),a[7:11]);self.ret(4,arg(0))
        elif address==0x6e4430:
            assert self.gate_actor is None
            self.gate_actor=id;self.gate_bounds=arg(0)
            self.event('V',id,arg(1)&255,arg(2),*self.result(arg(0),4))
        elif address==0x41b270:self.event('C',id,*a[11:14])
        elif address==0x6e3990:
            self.event('D',id,*self.result(arg(0),2),*self.result(arg(1),4));self.ret(8)
    def scan(self,actors,layer,force,bypass,context,dirty,clip,viewport):
        self.count=len(actors);self.actors=actors;self.events=[];self.gate_actor=None
        assert len(actors)<=1024 and len(layer)<=2048 and all(0<=i<len(actors) for i in layer)
        regions=[(BASE,len(actors)*0x300+0x120),(TYPES,len(actors)*0x300+32),
                 (LAYER,len(layer)*4+32),(INPUT,64)]
        for p,n in regions:self.u.mem_write(p,bytes([0x5a])*n)
        for id,a in enumerate(actors):
            p=self.actor(id);t=TYPES+id*0x300
            self.put(p,0x7ad3cc);self.put(p+0xb0,t);self.u.mem_write(p+0x7d,bytes([a[1]]))
            self.u.mem_write(p+0x74,bytes(a[4:7]));self.u.mem_write(p+0xb5,bytes([a[3]]))
            self.put(t,0x7ad5e0);self.u.mem_write(t+0x283,bytes([a[2]]));self.ints(p+0x88,a[11:14])
        self.u.mem_write(LAYER,struct.pack('<'+'I'*len(layer),*[self.actor(id) for id in layer]))
        self.put(0x8525ac,LAYER);self.put(0x8525b8,len(layer))
        self.ints(INPUT,[*dirty,*clip]);self.ints(0x839630,viewport)
        self.u.mem_write(0xa40d13,bytes([bypass]));self.put(0xb263d8,TYPES if context else 0)
        before=[bytes(self.u.mem_read(p,n)) for p,n in regions];self.active=True
        def write(u,access,p,n,v,ctx):
            if BASE<=p<TYPES:
                id=self.identity(p-0x75);assert n==1
                self.event('r',id,v&255)
            elif self.gate_actor is not None and self.gate_bounds<=p<self.gate_bounds+16:
                assert n==4 and (p-self.gate_bounds)%4==0
                self.event('xywh'[(p-self.gate_bounds)//4],self.gate_actor,self.signed(v))
        hook=self.u.hook_add(UC_HOOK_MEM_WRITE,write)
        try:self.checked_call(0x6a9e10,[force,INPUT,INPUT+16],writes=[(self.actor(id)+0x75,1) for id in range(len(actors))])
        finally:self.u.hook_del(hook);self.active=False
        redraw=[]
        for (p,n),old in zip(regions,before):
            after=bytearray(self.u.mem_read(p,n))
            if p==BASE:
                for id in range(len(actors)):
                    offset=self.actor(id)+0x75-BASE;redraw.append(after[offset]);after[offset]=old[offset]
            assert bytes(after)==old,'Static Terrain scan changed fixture arena outside redraw bytes'
        return [*redraw,*self.events]
