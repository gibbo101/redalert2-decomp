# SPDX-License-Identifier: GPL-3.0-or-later
"""Unchanged Foot depth/gradient and cell predicates on immutable supplied maps.

Actual direction initialization, coordinates/type/Drive/cell leaves execute.
Map association, type/global metadata and flat tile dimensions are supplied.
"""
import struct
from original_unit_surface import UnitSurfaceOracle,ARENA,UNIT,TYPE,LOCO,VT
from original_foot_lit import words,ints,ret,signed
from original_presentation import STACK
from verify_foot_depth import verify,RANGES,TAILS
from unicorn.x86_const import UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EAX
MAP=0x2700000;LD=MAP+0x1f000;LG=LD+16;LVT=LD+0x100;TILES=MAP+0x1e000
PREDICATES=(0x6cf9d0,0x6cfb60,0x6cfda0,0x6cf670,0x6cf820)
class FootDepthOracle(UnitSurfaceOracle):
    def __init__(self,exe):
        verify(exe.read_bytes());super().__init__(exe);self.u.mem_map(MAP,0x20000)
        self.depth_active=False;self.with_depth_pixels=False;self.base_return=None
        self.new_roots=0;self.map_calls=0;self.base_calls=0;self.dimension_writes=0
        self.checked_call(0x491620,writes=[(0x851a70,32)])
        assert list(struct.unpack('<16h',self.u.mem_read(0x851a70,32)))==[0,-1,1,-1,1,0,1,1,0,1,-1,1,-1,0,-1,-1]
    def va(self,a):
        if a in RANGES or a in TAILS:return a
        return super().va(a)
    def route(self,u,a,n,ctx):
        if not getattr(self,'depth_active',False):return super().route(u,a,n,ctx)
        sp=u.reg_read(UC_X86_REG_ESP);ecx=u.reg_read(UC_X86_REG_ECX)
        if self.base_return==a:self.base_return=None
        suppress=self.base_return is not None
        if a==0x548070:
            assert ecx==0x8324e0;p=words(u,sp+4,1)[0];x,y=struct.unpack('<2h',u.mem_read(p,4))
            if not suppress:self.event('cell',x,y)
            self.map_calls+=1;ret(u,4,self.cells.get((x,y),0));return
        if a==0x52b690:
            assert self.base_return is not None and ecx==TYPE+0xc00
            sub,unused,out=words(u,sp+4,3);assert sub==0
            assert STACK-0x2000<=out and out+12<=STACK
            u.mem_write(out,bytes(12));self.dimension_writes+=1;ret(u,12,out);return
        if suppress:return
        if a in PREDICATES:
            index=PREDICATES.index(a);self.event('p'+str(index))
            if self.capture_predicates:ret(u,0,self.predicates[index]);return
        elif a in (LD,0x4a4830):
            self.event('loco_depth')
            if a==LD:ret(u,4,self.ld);return
        elif a in (LG,0x4a4840):
            self.event('loco_gradient')
            if a==LG:ret(u,4,self.lg);return
        elif a==0x41b320:self.event('coords')
        elif a==0x479cc0:
            assert MAP<=ecx<MAP+81*0x200;self.event('cellpred',*struct.unpack('<2h',u.mem_read(ecx+0x24,4)))
        elif a==0x6cfea0:
            self.event('base')
            if self.actual_base:
                self.base_calls+=1;self.base_return=words(u,sp,1)[0]
            else:ret(u,0,self.base);return
        super().route(u,a,n,ctx)
    def world(self,v):
        seed,x,y,bridge,tilebase,ix,iy,count=v
        self.u.mem_write(MAP,bytes(0x20000));self.cells={}
        self.u.mem_write(UNIT+0x88,struct.pack('<3i',x,y,0));self.u.mem_write(UNIT+0x79,bytes([bridge&255]))
        self.put(0xa52c74,tilebase);self.put(0x8661d8,count)
        self.u.mem_write(0xac0148,struct.pack('<2H',ix&65535,iy&65535))
        def word(n):return struct.unpack('<h',struct.pack('<H',n&65535))[0]
        cx,cy=word(int(x/256)),word(int(y/256))
        for i in range(81):
            bits=((i+1)*2654435761+seed*2246822519)&0xffffffff;p=MAP+i*0x200
            cell=(word(cx+i%9-4),word(cy+i//9-4));present=not seed or i==40 or bits&3!=0
            flags=(bits>>8)&0x10d00 if seed else 0
            tile=(65535 if bits%8==1 else 255 if bits%8==2 else signed(tilebase+(bits>>16)%22)) if seed else 65535
            level=struct.unpack('<b',bytes([(bits>>20)&255]))[0] if seed else 0
            field116=int((bits>>10)%7)-2 if seed else -1;field_ec=10 if seed and bits&4 else 0
            self.u.mem_write(p+0x24,struct.pack('<2h',*cell));self.put(p+0x38,tile);self.put(p+0x140,flags)
            self.u.mem_write(p+0x11b,struct.pack('<b',level));self.u.mem_write(p+0x116,struct.pack('<h',field116));self.put(p+0xec,field_ec)
            if present:self.cells[cell]=p
        self.put(TILES,TYPE+0xc00);self.put(0xa40cd4,TILES);self.put(0xa52f00,0)
    def prepare(self,world,has=1,mode=1,ld=0,lg=2,factors=(0,0,0,0)):
        # Parent owns ordinary actor/type/house/surface fixtures; complete stock
        # initialization is not claimed by these selected record assignments.
        UnitSurfaceOracle.setup(self,[0,0,0,0,0,0,0,0,0,0,0,-1,0,0,0,0,2,0,*([0]*11)])
        self.world(world)
        self.put(UNIT+0x564,LOCO+4 if has else 0)
        self.u.mem_write(LVT,bytes(self.u.mem_read(0x7a04cc,0x60)))
        self.put(LVT+0x38,LD);self.put(LVT+0x3c,LG);self.put(LOCO+4,0x7a04cc if mode else LVT)
        for off,value in zip((0xb60,0xb64,0xb5c,0xb68),factors):self.put(TYPE+off,value)
        self.ld=ld;self.lg=lg;self.events=[];self.capture_predicates=False;self.actual_base=False;self.base_return=None
    def depth_inputs(self):
        return [(ARENA,0x40000),(MAP,0x20000),(0x851a70,32),(0xa52c74,4),(0x8661d8,4),
                (0xac0148,4),(0xa40cd4,4),(0xa52f00,4),(0xa40d2c,4)]
    def inputs(self):
        return [*super().inputs(),(MAP,0x20000),(0x851a70,32),(0xa52c74,4),
                (0x8661d8,4),(0xac0148,4),(0xa40cd4,4),(0xa52f00,4)]
    def query(self,kind,world):
        self.prepare(world);self.active=True;self.depth_active=True
        try:self.checked_call(PREDICATES[kind],ecx=UNIT,inputs=self.depth_inputs())
        finally:self.active=False;self.depth_active=False
        self.new_roots+=1
        value=self.u.reg_read(UC_X86_REG_EAX);value=value&255 if kind>=3 else signed(value)
        return self.events+['value',value]
    def wrapper(self,v,op):
        world=v[:8] if op!='F' else [0,0,0,0,0,-32768,-32768,4]
        rest=v[8:] if op!='F' else v
        has,mode,ld,lg,*other=rest;factors=other[:4]
        self.prepare(world,has,mode,ld,lg,factors)
        self.capture_predicates=op=='F';self.predicates=other[4:8]+[0] if op=='F' else [0]*5
        self.base=other[-1];self.actual_base=op=='K'
        if self.actual_base:assert world[0]==0 and world[3]==0 and self.base==-1
        self.active=True;self.depth_active=True
        try:
            self.checked_call(0x4c9930,ecx=UNIT,inputs=self.depth_inputs());z=signed(self.u.reg_read(UC_X86_REG_EAX))
            self.event('depth',z,'gradient')
            self.checked_call(0x4c9a10,ecx=UNIT,inputs=self.depth_inputs());self.event(signed(self.u.reg_read(UC_X86_REG_EAX)))
        finally:self.active=False;self.depth_active=False
        assert self.base_return is None;self.new_roots+=2;return self.events
    def setup(self,values,pixels=False):
        result=super().setup(values,pixels)
        if self.with_depth_pixels:
            self.world([0,0,0,0,0,-32768,-32768,4]);self.put(UNIT+0x564,LOCO+4)
            self.put(VT+0x2c0,0x4c9930);self.put(VT+0x2c4,0x4c9a10)
            self.capture_predicates=False;self.actual_base=True;self.base_return=None
        return result
    def pixels(self,values):
        assert values[-3]==-1
        self.with_depth_pixels=True;self.depth_active=True
        try:result=super().pixels(values)
        finally:self.with_depth_pixels=False;self.depth_active=False
        assert self.base_return is None;self.new_roots+=1;return result
