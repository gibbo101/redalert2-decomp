# SPDX-License-Identifier: GPL-3.0-or-later
"""Unmodified patched per-frame caller on actual Unit and Terrain vtables.

Inverse-camera, Foot +4C, map predicate, +FC and extras are explicit services.
Actual +48 coordinates, projection, type leaves and Unit behind exit execute.
"""
import hashlib
import struct
from pathlib import Path
from original_presentation import PresentationOracle,STACK
from compare_original import PATCHED_EXPECTED
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_EDX,UC_X86_REG_ESI,UC_X86_REG_EBX,UC_X86_REG_EIP,UC_X86_REG_ESP
BASE=0x2400000;TYPES=BASE+0x140000;LAYERS=BASE+0x280000;TACTICAL=BASE+0x300000;SCENARIO=BASE+0x302000
VIEWPORT=0x839630
class DynamicTraversalOracle(PresentationOracle):
    def __init__(self,exe):
        if hashlib.sha256(Path(exe).read_bytes()).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact patched engine required')
        super().__init__(exe,allow_patched=True);self.u.mem_map(BASE,0x400000)
        self.active=False
        self.hooks=[self.u.hook_add(UC_HOOK_CODE,self.service,begin=a,end=a) for a in
                    [0x591380,0x4ca6f0,0x5683c0,0x5d4e40,0x6ff350,0x6e4430,
                     0x6c3b30,0x6c2c40,0x70a2d0,0x6e4b00]]
        for a,p in [(0x6a20e0,0xabe4c0),(0x6a2170,0xabe4d0),(0x6a2440,0xabe490)]:
            self.checked_call(a,writes=[(p,8),(0xabe550,8)])
        self.scale=struct.unpack('<d',self.u.mem_read(0xabe490,8))[0]
    def va(self,a):return a
    @staticmethod
    def actor(id):return BASE+0x1000+id*0x800
    def identity(self,p):
        assert (p-BASE-0x1000)%0x800==0 and 0<=p-BASE-0x1000<self.count*0x800,hex(p)
        return (p-BASE-0x1000)//0x800
    def ints(self,p,values):self.u.mem_write(p,struct.pack('<'+'i'*len(values),*values))
    def result(self,p,n):return list(struct.unpack('<'+'i'*n,self.u.mem_read(p,4*n)))
    def ret(self,pop,value=0):
        sp=self.u.reg_read(UC_X86_REG_ESP)
        self.u.reg_write(UC_X86_REG_EAX,value&0xffffffff);self.u.reg_write(UC_X86_REG_ESP,sp+4+pop)
        self.u.reg_write(UC_X86_REG_EIP,struct.unpack('<I',self.u.mem_read(sp,4))[0])
    def event(self,k,id,*values):self.events.extend([k,id,*values])
    def service(self,u,a,n,ctx):
        if not self.active:return
        sp=u.reg_read(UC_X86_REG_ESP);arg=lambda i:struct.unpack('<I',u.mem_read(sp+4+4*i,4))[0]
        if a==0x591380:
            assert u.reg_read(UC_X86_REG_EDX)==TACTICAL+0xde4
            output=u.reg_read(UC_X86_REG_ECX)
            assert STACK-0x2000<=arg(0)<=STACK-12 and STACK-0x2000<=output<=STACK-12
            self.event('I',self.inv,*self.result(arg(0),3))
            self.ints(output,self.inverse[self.inv]);self.inv+=1;self.ret(4,output);return
        if a==0x5683c0:
            assert u.reg_read(UC_X86_REG_ECX)==0x8324e0
            caller=struct.unpack('<I',u.mem_read(sp,4))[0]
            reg={0x6a961f:UC_X86_REG_ESI,0x6a98e4:UC_X86_REG_ESI,0x6a9ca2:UC_X86_REG_EBX}[caller]
            id=self.identity(u.reg_read(reg));coords=self.actors[id][5:8]
            assert self.result(arg(0),3)==list(coords)
            self.event('M',id,*coords);self.ret(4,self.actors[id][8]);return
        id=self.identity(u.reg_read(UC_X86_REG_ECX));actor=self.actors[id]
        if a in [0x70a2d0,0x6e4b00]:self.event('T',id) # Actual type leaf executes.
        elif a==0x4ca6f0:
            assert actor[0]==0 and arg(1)==0 and STACK-0x2000<=arg(0)<=STACK-12
            self.event('F',id,arg(1));self.ints(arg(0),actor[5:8]);self.ret(8,arg(0))
        elif a==0x5d4e40:
            assert STACK-0x2000<=arg(0)<=STACK-12
            self.event('C',id,*actor[5:8]) # Actual coordinate stores execute.
        elif a in [0x6ff350,0x6e4430]:
            assert arg(0)==VIEWPORT
            self.event('D',id,self.signed(arg(1)),self.signed(arg(2)),*self.result(VIEWPORT,4))
            if actor[9]:
                self.ints(VIEWPORT,actor[10:14]);self.event('S',id,*actor[10:14])
            self.ret(12,0) # Return is discarded by this caller.
        elif a in [0x6c3b30,0x6c2c40]:
            assert arg(1)==VIEWPORT and STACK-0x2000<=arg(0)<=STACK-8
            self.event('B' if a==0x6c3b30 else 'E',id,*self.result(arg(0),2),*self.result(VIEWPORT,4))
            if a==0x6c2c40:self.ret(8)
    @staticmethod
    def signed(v):return struct.unpack('<i',struct.pack('<I',v&0xffffffff))[0]
    def scan(self,actors,layers,force,scenario,context,bypass,origin,surface,viewport,inverse):
        self.actors=actors;self.count=len(actors);self.events=[];self.inv=0;self.inverse=inverse
        assert len(actors)<=600 and len(layers)==5 and all(len(layer)<=1200 for layer in layers)
        assert all(0<=id<len(actors) for layer in layers for id in layer)
        regions=[(BASE,0x1000+len(actors)*0x800+64),(TYPES,len(actors)*0x800+64),
                 (LAYERS,5*0x2000),(TACTICAL,0x4000)]
        for p,n in regions:self.u.mem_write(p,bytes([0x5a])*n)
        for id,a in enumerate(actors):
            p=self.actor(id);t=TYPES+id*0x800
            assert (a[0]==0 and a[1]&4) or (a[0]==1 and not a[1]&5)
            self.put(p,0x7ad3cc if a[0] else 0x7addf8);self.put(p+0xb0,t)
            self.u.mem_write(p+0x14,bytes([a[1]]));self.u.mem_write(p+0x85,bytes([a[2]]))
            self.u.mem_write(p+0xb5,bytes([a[4]]));self.u.mem_write(t+0x283,bytes([a[3]]))
            self.ints(p+0x88,a[5:8])
        for i,layer in enumerate(layers):
            p=LAYERS+i*0x2000
            self.u.mem_write(p,struct.pack('<'+'I'*len(layer),*[self.actor(id) for id in layer]))
            self.put(0x85257c+i*24,p);self.put(0x852588+i*24,len(layer))
        self.put(0xa40b08,0);self.put(0x83996c,TACTICAL);self.put(0xa3d290,SCENARIO)
        self.put(SCENARIO,scenario);self.ints(TACTICAL+0xb0,origin);self.ints(VIEWPORT,viewport)
        self.ints(0xabe568,surface);self.put(0xb263d8,TYPES if context else 0);self.u.mem_write(0xa40d13,bytes([bypass]))
        before=[bytes(self.u.mem_read(p,n)) for p,n in regions]
        def write(u,access,p,n,value,ctx):
            if BASE<=p<TYPES:
                id=self.identity(p-0x85);assert n==1
                self.event('v',id,value&255)
        hook=self.u.hook_add(UC_HOOK_MEM_WRITE,write);self.active=True
        try:self.checked_call(0x6a93f0,[force],TACTICAL,
                              writes=[(self.actor(id)+0x85,1) for id in range(len(actors))]+[(VIEWPORT,16)])
        finally:self.active=False;self.u.hook_del(hook)
        assert self.inv==3
        visible=[]
        for (p,n),old in zip(regions,before):
            after=bytearray(self.u.mem_read(p,n))
            if p==BASE:
                for id in range(len(actors)):
                    offset=self.actor(id)+0x85-BASE;visible.append(after[offset]);after[offset]=old[offset]
            assert bytes(after)==old,'Dynamic traversal mutated fixture arena outside visible bytes'
        return [*visible,*self.result(VIEWPORT,4),*self.events]
