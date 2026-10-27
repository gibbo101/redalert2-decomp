# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete patched per-frame caller with real Foot/Drive getters and Unit gate.

Healthy static Terrain stays in its separate pass. Inverse camera, map predicate,
tactical projection, final Unit drawing and extras are explicit services.
"""
import struct
from original_dynamic_traversal import DynamicTraversalOracle,BASE,TYPES,LAYERS,TACTICAL,SCENARIO,VIEWPORT,STACK
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_EBX,UC_X86_REG_ECX,UC_X86_REG_ESI,UC_X86_REG_EIP,UC_X86_REG_ESP
POOL=BASE+0x2c0000;RESULT=BASE+0x2e0000
class ActorTraversalOracle(DynamicTraversalOracle):
    def __init__(self,exe):
        super().__init__(exe);self.mode=None
        self.hooks.extend(self.u.hook_add(UC_HOOK_CODE,self.service,begin=a,end=a) for a in
                          [0x49fdb0,0x5d34e0,0x6a29d0,0x700e70])
        self.checked_call(0x49f600,writes=[(0x852998,12)])
        self.checked_call(0x4c2870,writes=[(0x865f20,12)])
        assert self.result(0x852998,3)==self.result(0x865f20,3)==[0,0,0]
    @staticmethod
    def loco(id):return TYPES+id*0x800+0x400
    def service(self,u,a,n,ctx):
        if not self.active:return
        sp=u.reg_read(UC_X86_REG_ESP);arg=lambda i:struct.unpack('<I',u.mem_read(sp+4+4*i,4))[0]
        if a==0x49fdb0:
            id=(arg(0)-TYPES-0x404)//0x800
            assert arg(0)==self.loco(id)+4 and 0<=id<self.count
            assert STACK-0x2000<=arg(1)<=STACK-12
            self.event('L',id);return # Actual Drive COM getter executes.
        if a==0x6a29d0:
            id=self.gate_actor;assert u.reg_read(UC_X86_REG_ECX)==TACTICAL
            assert STACK-0x2000<=arg(0)<=STACK-12 and STACK-0x2000<=arg(1)<=STACK-8
            assert self.result(arg(0),3)==self.config[id][3:6]
            self.event('P',id,*self.result(arg(0),3));self.ints(arg(1),self.config[id][15:17]);self.ret(8,self.config[id][14]);return
        if a in [0x4ca6f0,0x6ff350,0x5d34e0,0x700e70]:
            id=self.identity(u.reg_read(UC_X86_REG_ECX))
            if a==0x4ca6f0:
                assert STACK-0x2000<=arg(0)<=STACK-12 or (self.mode=='F' and arg(0)==RESULT)
                if self.mode=='D':assert arg(1)==0;self.event('F',id,0)
                return # Actual complete Foot getter executes.
            assert self.mode=='D'
            if a==0x6ff350:
                assert arg(0)==VIEWPORT;self.gate_actor=id
                self.event('D',id,self.signed(arg(1)),self.signed(arg(2)),*self.result(VIEWPORT,4))
            elif a==0x5d34e0:
                assert arg(0)==VIEWPORT and arg(2)==0;self.event('g',id,0)
            else:
                assert arg(1)==VIEWPORT and STACK-0x2000<=arg(0)<=STACK-8
                self.event('W',id,*self.result(arg(0),2),*self.result(VIEWPORT,4));self.ret(8)
            return
        super().service(u,a,n,ctx)
    def prepare(self,configs):
        self.config=configs;self.count=len(configs);self.events=[];self.inv=0;self.gate_actor=None
        assert self.count<=600
        self.actors=[[a[0],a[1],a[2],0,0,*a[3:6],a[10],0,0,0,0,0] for a in configs]
        regions=[(BASE,0x1000+self.count*0x800+64),(TYPES,self.count*0x800+64),
                 (LAYERS,5*0x2000),(POOL,0x6000),(RESULT,64),(TACTICAL,0x4000)]
        for p,n in regions:self.u.mem_write(p,bytes([0x5a])*n)
        for id,a in enumerate(configs):
            p=self.actor(id);t=TYPES+id*0x800;l=self.loco(id)
            assert (a[0]==0 and a[1]&4) or (a[0]==1 and not a[1]&5)
            self.put(p,0x7ad3cc if a[0] else 0x7addf8);self.put(p+0xb0,t)
            self.u.mem_write(p+0x14,bytes([a[1]]));self.u.mem_write(p+0x85,bytes([a[2]]));self.ints(p+0x88,a[3:6])
            self.u.mem_write(p+0x74,bytes(a[6:9]));self.u.mem_write(p+0xb5,b'\0');self.u.mem_write(t+0x283,b'\0')
            self.u.mem_write(p+0x370,b'\0');self.u.mem_write(p+0x574,bytes([a[9]&255]));self.put(p+0x564,l+4)
            self.put(l+4,0x7a04cc);self.put(l+12,p);self.ints(l+0x40,a[11:14])
        self.put(0x8661cc,POOL)
        for i in range(128):
            self.put(POOL+i*4,POOL+0x1000+i*0x80)
            self.u.mem_write(POOL+0x1000+i*0x80+0x28,struct.pack('<hh',i*13-800,i*11+1400))
        return regions
    def check_regions(self,regions,before,allowed):
        for (p,n),old in zip(regions,before):
            after=bytearray(self.u.mem_read(p,n))
            for address,size in allowed:
                if p<=address and address+size<=p+n:after[address-p:address-p+size]=old[address-p:address-p+size]
            assert bytes(after)==old,'Combined actor fixture mutated outside contract'
    def block(self,start,stop,allowed,ebx=0):
        self.u.reg_write(UC_X86_REG_ESI,self.actor(0));self.u.reg_write(UC_X86_REG_EBX,ebx)
        self.u.reg_write(UC_X86_REG_ESP,STACK);guard=bytes([0xa7])*128;self.u.mem_write(STACK,guard)
        def audit(u,access,p,n,v,ctx):assert any(a<=p and p+n<=a+s for a,s in allowed),(hex(p),n)
        hook=self.u.hook_add(UC_HOOK_MEM_WRITE,audit)
        try:self.u.emu_start(start,stop,count=100)
        finally:self.u.hook_del(hook)
        assert self.u.reg_read(UC_X86_REG_EIP)==stop and self.u.reg_read(UC_X86_REG_ESP)==STACK
        assert bytes(self.u.mem_read(STACK,128))==guard
        self.audit_blocks+=1
    def fields(self,byte):
        self.mode='G';p=self.actor(0);self.u.mem_write(p,bytes([0x5a])*0x800);self.u.mem_write(p+0x14,bytes([byte]))
        self.checked_call(0x40ff10,ecx=p,writes=[(p,20),(p+0x14,1),(p+0x18,9)])
        self.block(0x5d24e4,0x5d24ec,[(p+0x14,1)])
        self.block(0x6c1287,0x6c129a,[(p+0x14,1)])
        self.block(0x4c2bfe,0x4c2c07,[(p+0x14,1)])
        self.block(0x6c1063,0x6c1069,[(p+0x370,1)])
        self.block(0x4c2ace,0x4c2ad5,[(p+0x574,1)])
        return [self.u.mem_read(p+0x14,1)[0],self.u.mem_read(p+0x370,1)[0],struct.unpack('<b',self.u.mem_read(p+0x574,1))[0]]
    def foot(self,index,current,destination,x,y,unused):
        self.mode='F';a=[0,7,0,*current,1,1,0,index,0,*destination,1,0,0]
        regions=self.prepare([a])
        if index&255<128:self.u.mem_write(POOL+0x1000+(index&255)*0x80+0x28,struct.pack('<HH',x&65535,y&65535))
        before=[bytes(self.u.mem_read(p,n)) for p,n in regions];self.active=True
        try:self.checked_call(0x4ca6f0,[RESULT,unused],self.actor(0),writes=[(RESULT,12)])
        finally:self.active=False
        assert self.u.reg_read(UC_X86_REG_EAX)==RESULT
        self.check_regions(regions,before,[(RESULT,12)])
        return [*self.result(RESULT,3),*self.events]
    def scan(self,configs,layers,force,scenario,context,bypass,origin,surface,viewport,inverse):
        self.mode='D';regions=self.prepare(configs);self.inverse=inverse
        assert len(layers)==5 and all(len(layer)<=1200 for layer in layers)
        assert all(0<=id<self.count for layer in layers for id in layer)
        for i,layer in enumerate(layers):
            p=LAYERS+i*0x2000;self.u.mem_write(p,struct.pack('<'+'I'*len(layer),*[self.actor(id) for id in layer]))
            self.put(0x85257c+i*24,p);self.put(0x852588+i*24,len(layer))
        self.put(0xa40b08,0);self.put(0x83996c,TACTICAL);self.put(0xa3d290,SCENARIO)
        self.put(SCENARIO,scenario);self.ints(TACTICAL+0xb0,origin);self.ints(VIEWPORT,viewport)
        self.ints(0xabe568,surface);self.put(0xb263d8,TYPES if context else 0);self.u.mem_write(0xa40d13,bytes([bypass]))
        before=[bytes(self.u.mem_read(p,n)) for p,n in regions]
        def write(u,access,p,n,v,ctx):
            if BASE<=p<TYPES:
                offset=(p-BASE-0x1000)%0x800;assert n==1 and offset in [0x75,0x85]
                id=self.identity(p-offset);self.event('r' if offset==0x75 else 'v',id,v&255)
            elif VIEWPORT<=p<VIEWPORT+16:
                assert n==4 and (p-VIEWPORT)%4==0
                self.event('xywh'[(p-VIEWPORT)//4],self.gate_actor,self.signed(v))
        hook=self.u.hook_add(UC_HOOK_MEM_WRITE,write);self.active=True
        allowed=[(self.actor(id)+offset,1) for id in range(self.count) for offset in [0x75,0x85]]
        try:self.checked_call(0x6a93f0,[force],TACTICAL,writes=[*allowed,(VIEWPORT,16)])
        finally:self.active=False;self.u.hook_del(hook)
        assert self.inv==3;self.check_regions(regions,before,allowed)
        return [*[v for id in range(self.count) for offset in [0x85,0x75] for v in self.u.mem_read(self.actor(id)+offset,1)],
                *self.result(VIEWPORT,4),*self.events]
