# SPDX-License-Identifier: GPL-3.0-or-later
"""Actual ordinary visibility/DrawIt caller around frozen complete Unit pixels."""
import hashlib,struct
from original_unit_voxel_shadow_world import UnitVoxelShadowWorldOracle
from original_unit_voxel_world import (MAP,HOUSE,ARRAY,SCHEME,CONTACTS,CONTACT,CTYPE,CONTACT_VT,TILES,TILE,
    WORLD,COLOR,ZDATA,ADATA,PAL,CVT,BLIT,ZSURF,ASURF,ZOBJ,AOBJ,W,H)
from original_cached_voxel_shadow import RLE_BLIT
from original_shadow_voxel_world import RAW_BLIT
from original_foot_voxel_staging import TYPE,ranges
from original_voxel_part import ACTOR,VT
from original_presentation import PresentationOracle,STACK
from original_foot_lit import words,ints,signed,ret
from verify_unit_caller_world import verify
from unicorn import UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EAX
RULES=0x2240000;TACTICAL=0x2250000;INPUT=0x2260000;TABLE=0x2400000
REGISTRY=0xabe5f8;FLAGS=0xad0578;SHAPE=0xad0468
class UnitCallerWorldOracle(UnitVoxelShadowWorldOracle):
    def __init__(self,*args):
        self.caller_mode=False;self.in_child=False;self.caller_events=[];self.caller_counts={}
        super().__init__(*args)
        self.caller_inspection=verify((args[0].parents[1]/'disc-allied/game.exe').read_bytes(),args[0].read_bytes())
        self.allowed=sorted(set(self.allowed+[(a,a+n) for key in ('caller','map_copy') for a,n in ranges(self.caller_inspection[key])]),reverse=True)
        self.u.mem_map(TABLE,0x100000)
        self.checked_call(0x6e2fe0,writes=[(0xac0358,16)])
    def va(self,a):
        return a if a in (0x700e70,0x6ff350,0x6e2fe0) else super().va(a)
    def prepare_world(self):
        super().prepare_world()
        if not self.caller_mode:return
        nested,offset,index,layer,count,ambient,extra,flags,predicate=self.caller_values
        assert not flags&0x100 and -32768<=ambient<=32767 and 0<=count<=500
        self.u.mem_write(ACTOR+0x59e,bytes([offset&255]));self.u.mem_write(ACTOR+0x574,bytes([index&255]))
        self.put(ACTOR+0x5b4,-1);self.put(ACTOR+0x314,-1);self.put(ACTOR+0x31c,0)
        self.u.mem_write(TYPE+0x206,b'\1')
        self.u.mem_write(ACTOR+0x74,bytes([1,0,0]));self.put(ACTOR+0x370,0)
        self.u.mem_write(FLAGS,bytes([self.seed&3]));self.put(SHAPE,0x11223344);self.put(0xad057c,0)
        self.put(0x839848,RULES);self.put(RULES+0x1418,extra)
        self.u.mem_write(0x839630,struct.pack('<4i',0,0,W,H));self.put(0x83996c,TACTICAL)
        self.u.mem_write(TACTICAL,bytes(0x2000));self.put(TACTICAL+0xdb0,count)
        self.u.mem_write(TACTICAL+0xb0,struct.pack('<2i',7,-9));self.u.mem_write(REGISTRY,b'\xa7'*6000)
        self.put(0xb263d8,TYPE)
        table=bytearray(0x100000)
        for (x,y),p in self.cells.items():struct.pack_into('<I',table,(y*512+x)*4,p)
        self.table=bytes(table);self.u.mem_write(TABLE,self.table)
        self.put(0x8324e0+0x138,TABLE);self.put(0x8324e0+0x13c,262144)
        center=self.cells[(10,11)];self.put(center+0x140,flags);self.u.mem_write(center+0x10a,struct.pack('<h',ambient))
    def service(self,u,a,n,ctx):
        if not(self.caller_mode and self.unit_mode):return super().service(u,a,n,ctx)
        sp=u.reg_read(UC_X86_REG_ESP);ecx=u.reg_read(UC_X86_REG_ECX);arg=lambda i:words(u,sp+4+i*4,1)[0]
        event=lambda *v:self.caller_events.extend(v)
        if a in (0x700e70,0x6ff350,0x5d34e0,0x5d4810,0x548000,0x548070,0x6aa510):
            self.caller_counts[hex(a)]=self.caller_counts.get(hex(a),0)+1
        if a==0x6ff690:
            assert not self.in_child;self.in_child=True
            event('v',*[signed(v) for v in words(u,sp+4,7)])
        if a==0x7012b9:self.in_child=False
        if a==0x5956c0:
            assert ecx==0x7f8f80;event('L');ret(u,0,0x1234);return
        if a==0x6a29d0:
            assert ecx==TACTICAL and ints(u,arg(0),3)==[2560,2816,0]
            assert STACK-0x2000<=arg(1) and arg(1)+8<=STACK
            u.mem_write(arg(1),struct.pack('<2i',*self.projected));ret(u,8,int(self.caller_values[0]!=2));return
        if a==0x55a280:
            assert ecx==0x8324e0 and ints(u,arg(0),3)==[2560,2816,0]
            ret(u,4,0);return
        # Execute the actual height wrapper, including within the voxel root.
        if a==0x5d4810:return
        if not self.in_child:
            if a==0x41b320:event('C',10,'C',11)
            elif a==0x4c8fa0:
                assert ecx==ACTOR and arg(0)==arg(1)==0;event('Y');ret(u,8,self.caller_values[3]);return
            elif a==0x6aa510:event('R',signed(arg(1)),signed(arg(2)))
            elif a in (0x548000,0x548070):
                assert ecx==0x8324e0
                # Parent map instructions execute. Child neighbor services retain
                # the earlier scoped oracle boundary against these same cells.
                if a==0x548000:event('A')
                else:event('c')
                return
            elif a==0x4cce70:
                assert ecx==ACTOR;event('p');ret(u,0,self.caller_values[8]);return
            elif a==0x6d8ce0:
                assert ecx==ACTOR and arg(0)==0x2468;event('V');ret(u,4,1);return
            elif a==0x4c9bc0:
                assert ecx==ACTOR and arg(1)==INPUT+8
                event('F',*ints(u,arg(0),2),*ints(u,arg(1),4));ret(u,8);return
            elif a in (0x7005b0,0x709bb0,0x6cc020):raise AssertionError('Unrecovered caller branch entered')
        super().service(u,a,n,ctx)
    def checked_call(self,a,args=(),ecx=0,edx=0,*,writes=(),inputs=()):
        if not(self.caller_mode and self.world_mode and a==0x6ff690):
            return super().checked_call(a,args,ecx,edx,writes=writes,inputs=inputs)
        x,y,bx,by,bw,bh,_=args;self.projected=(x,y);self.u.mem_write(INPUT,struct.pack('<6i',x,y,bx,by,bw,bh))
        self.caller_events=[];self.in_child=False;count=self.caller_values[4];entries=bytes(self.u.mem_read(REGISTRY,6000))
        self.put(self.va(0x821f8c),ZOBJ);self.put(self.va(0x8198d4),AOBJ)
        slot=[(REGISTRY+count*12,12)] if count<500 else []
        writes=[*writes,(COLOR,W*H*2),(CVT+0x17c,4),*[(p+12,4) for p in (WORLD,ZSURF,ASURF)],
                (FLAGS,1),(SHAPE,4),(ACTOR+0x5ac,4),(ACTOR+0x75,1),(INPUT+8,16),(TACTICAL+0xdb0,4),*slot]
        inputs=[*inputs,(MAP,0x20000),(HOUSE,0x16000),(ARRAY,4),(SCHEME,0x310),(CONTACTS,4),(CONTACT,0x500),
                (CTYPE,0x1360),(CONTACT_VT,0x30),(TILES,128),(TILE,64),(ZDATA,W*H*2),(ADATA,W*H*2),
                (PAL,53*512),(CVT,0x17c),(CVT+0x180,0x80),(BLIT,12),(RLE_BLIT,8),(RAW_BLIT,8),
                (ZOBJ,48),(AOBJ,48),(self.alpha_map,0x20008),(self.va(0x821f8c),4),(self.va(0x8198d4),4),
                (TABLE,0x100000),(RULES,0x2000),(TACTICAL,0xdb0),(TACTICAL+0xdb4,0x2000-0xdb4),(INPUT,8)]
        def stores(u,access,p,n,v,ctx):
            if p==FLAGS:assert n==1;self.caller_events.extend(['i',v&255])
            elif p==SHAPE:assert n==4;self.caller_events.extend(['h',signed(v)])
            elif p==ACTOR+0x5ac:assert n==4 and v==TYPE;self.caller_events.extend(['T',0])
            elif REGISTRY<=p<REGISTRY+6000:
                assert n==4 and (p-REGISTRY)//12==count
                self.caller_events.extend(['rxy'[(p-REGISTRY)%12//4],17 if p==REGISTRY+count*12 else signed(v)])
            elif p==TACTICAL+0xdb0:assert n==4;self.caller_events.extend(['n',signed(v)])
        hook=self.u.hook_add(UC_HOOK_MEM_WRITE,stores)
        nested=self.caller_values[0]
        try:
            if nested:
                PresentationOracle.checked_call(self,0x6ff350,[INPUT+8,0 if nested==3 else 1,0x1234],ecx,edx,writes=writes,inputs=inputs)
                self.gate_result=[self.u.reg_read(UC_X86_REG_EAX)&255,self.u.mem_read(ACTOR+0x75,1)[0],*ints(self.u,INPUT+8,4)]
            else:
                PresentationOracle.checked_call(self,0x700e70,[INPUT,INPUT+8],ecx,edx,writes=writes,inputs=inputs)
                self.gate_result=[]
        finally:self.u.hook_del(hook)
        assert not self.in_child
        tail=bytearray(self.u.mem_read(REGISTRY,6000))
        for p,n in slot:tail[p-REGISTRY:p-REGISTRY+n]=entries[p-REGISTRY:p-REGISTRY+n]
        assert bytes(tail)==entries,'Unit caller registry tail changed'
    def draw_caller(self,v):
        self.caller_values=v[:9];self.caller_mode=True
        try:result=self.draw_complete(v[9:])
        finally:self.caller_mode=False
        registry=bytearray(self.u.mem_read(REGISTRY,6000));count=self.caller_values[4]
        if count<500 and words(self.u,REGISTRY+count*12,1)[0]==ACTOR:struct.pack_into('<I',registry,count*12,17)
        return [*result,'caller',*self.gate_result,self.u.mem_read(FLAGS,1)[0],words(self.u,SHAPE,1)[0],
                words(self.u,TACTICAL+0xdb0,1)[0],hashlib.sha256(registry).hexdigest(),*self.caller_events]
