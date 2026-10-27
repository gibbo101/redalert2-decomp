# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete unchanged Foot forwarding, actual Drive offset, nested lit-cache child."""
import struct
from original_presentation import PresentationOracle,STACK
from original_voxel_cache import VoxelCacheOracle
from verify_foot_lit_draw import verify
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_EIP,UC_X86_REG_ESP
ARENA=0x2300000;ACTOR=ARENA;LOCO=ARENA+0x1000;VTABLE=ARENA+0x1100
POINT=ARENA+0x2000;MATRIX=ARENA+0x2100;CLIP=ARENA+0x2200;OTHER=ARENA+0x2300
OFFSET_SERVICE=ARENA+0xf000
def signed(v):return struct.unpack('<i',struct.pack('<I',v&0xffffffff))[0]
def ints(u,p,n):return list(struct.unpack('<'+'i'*n,u.mem_read(p,n*4)))
def words(u,p,n):return list(struct.unpack('<'+'I'*n,u.mem_read(p,n*4)))
def ret(u,pop,value=0):
    sp=u.reg_read(UC_X86_REG_ESP);target=words(u,sp,1)[0]
    u.reg_write(UC_X86_REG_EAX,value);u.reg_write(UC_X86_REG_ESP,sp+4+pop);u.reg_write(UC_X86_REG_EIP,target)
def forwarded(u,sp,original):
    args=words(u,sp+4,9)
    assert args[:5]==original[:5] and args[7:]==original[7:]
    for pointer,size in ((args[5],8),(args[6],48)):
        assert STACK-0x2000<=pointer and pointer+size<=STACK
    assert args[5]!=original[5] and args[6]!=original[6]
    return ['draw',args[0],signed(args[1]),signed(args[2]),args[3],
            *ints(u,args[4],4),*ints(u,args[5],2),signed(args[7]),args[8],*words(u,args[6],12)]
class FootLitOracle(PresentationOracle):
    def __init__(self,exe):
        verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(ARENA,0x20000)
        self.host_point_writes=0;self.forward_service=None
        # Install before any execution: adding/removing code hooks after an
        # uninstrumented zero-method translation can omit its entry event.
        self.code_hook=self.u.hook_add(UC_HOOK_CODE,self.route)
    def va(self,a):return a
    def route(self,u,a,n,ctx):
        if self.forward_service is not None:self.forward_service(u,a,n,ctx)
    def forward(self,values):
        has,mode,x,y,dx,dy,model,frame,key,cache,bx,by,bw,bh,brightness,flags,*pose=values
        assert len(pose)==12 and mode in (0,1,2)
        self.u.mem_write(ARENA,b'\x93'*0x20000)
        self.put(ACTOR+0x564,LOCO+4 if has else 0);self.put(LOCO+4,VTABLE)
        self.put(VTABLE+0x2c,0x53d4d0 if mode==1 else OFFSET_SERVICE)
        self.u.mem_write(POINT,struct.pack('<2i',x,y));self.u.mem_write(CLIP,struct.pack('<4i',bx,by,bw,bh))
        self.u.mem_write(MATRIX,struct.pack('<12I',*pose));self.u.mem_write(OTHER,struct.pack('<2i',dx,dy))
        original=[model,frame&0xffffffff,key&0xffffffff,cache,CLIP,POINT,MATRIX,brightness&0xffffffff,flags]
        events=[]
        def service(u,a,n,ctx):
            if a not in (OFFSET_SERVICE,0x53d4d0,0x6d1d00):return
            sp=u.reg_read(UC_X86_REG_ESP)
            if a==0x6d1d00:
                assert u.reg_read(UC_X86_REG_ECX)==ACTOR
                events.extend(forwarded(u,sp,original));ret(u,36,0x12345678)
            else:
                interface,output=words(u,sp+4,2);assert interface==LOCO+4
                assert STACK-0x2000<=output and output+8<=STACK
                events.append('offset')
                if a==OFFSET_SERVICE:
                    if mode==0:
                        u.mem_write(output,struct.pack('<2i',dx,dy));self.host_point_writes+=1;ret(u,8,output)
                    else:ret(u,8,OTHER)
                # Actual Drive zero method executes unchanged in mode 1.
        self.forward_service=service
        try:self.checked_call(0x4c9880,original,ACTOR,inputs=[(ARENA,0x20000)])
        finally:self.forward_service=None
        assert self.u.reg_read(UC_X86_REG_EAX)==0x12345678
        return events
    def zero(self,x,y):
        self.u.mem_write(ARENA,b'\x93'*0x20000);self.u.mem_write(POINT,struct.pack('<2i',x,y));seen=[]
        def audit(u,access,p,n,v,ctx):
            if p in (POINT,POINT+4):seen.append((p-POINT,n,v&0xffffffff))
        hook=self.u.hook_add(UC_HOOK_MEM_WRITE,audit)
        try:self.checked_call(0x53d4d0,[LOCO+4,POINT],writes=[(POINT,8)],
                              inputs=[(ARENA,POINT-ARENA),(POINT+8,ARENA+0x20000-POINT-8)])
        finally:self.u.hook_del(hook)
        assert seen==[(0,4,0),(4,4,0)] and self.u.reg_read(UC_X86_REG_EAX)==POINT
        return ints(self.u,POINT,2)

class FootLitCacheOracle(VoxelCacheOracle):
    """Use the established successful cache fixture under the actual Foot root.

    Rectangle/point/matrix inputs and locomotor records are immutable. Existing
    bounded render/snapshot/pool/allocator services remain supplied, not pixels.
    """
    def __init__(self,exe):
        verify(exe.read_bytes());self.foot_mode=False
        super().__init__(exe,allow_patched=True)
    def va(self,a):
        if a in (0x4c9880,0x53d4d0):return a
        return super().va(a)
    def checked_call(self,address,args=(),ecx=0,edx=0,**kwargs):
        if address==0x6c7120 and self.foot_mode:
            self.original=[value&0xffffffff for value in args]
            self.u.mem_write(args[5],struct.pack('<2i',*self.location))
            self.u.mem_write(args[6],struct.pack('<12I',*self.pose))
            self.put(self.actor+0x564,0x1609004 if self.has else 0)
            self.put(0x1609004,0x1609100);self.put(0x160912c,0x53d4d0 if self.mode==1 else 0x1202500)
            kwargs['inputs']=[*kwargs.get('inputs',()),(args[6],48),(0x1609000,0x200)]
            return super().checked_call(0x4c9880,args,ecx,edx,**kwargs)
        return super().checked_call(address,args,ecx,edx,**kwargs)
    def service(self,u,a,n,ctx):
        if self.foot_mode:
            sp=u.reg_read(UC_X86_REG_ESP)
            if a in (0x53d4d0,0x1202500):
                interface,output=words(u,sp+4,2)
                assert interface==0x1609004 and STACK-0x2000<=output and output+8<=STACK
                self.forward_events.append('offset')
                if a==0x1202500:
                    self.host_write(output,struct.pack('<2i',*self.offset));ret(u,8,output)
                return # Actual zero method executes when selected.
            if a==super().va(0x6c7120):
                assert u.reg_read(UC_X86_REG_ECX)==self.actor
                row=forwarded(u,sp,self.original);row[1]=1;row[4]=int(bool(self.original[3]))
                self.forward_events.extend(row)
                return # Complete Techno cache child executes; do not redirect.
        super().service(u,a,n,ctx)
    def nested(self,values):
        key,available,disabled,valid,frame,brightness,self.has,self.mode,x,y,dx,dy,*self.pose=values
        assert len(self.pose)==12 and self.mode in (0,1)
        self.location=(x,y);self.offset=(dx,dy);self.forward_events=[];self.foot_mode=True
        try:result=super().dispatch(key,available,disabled,valid,frame,brightness)
        finally:self.foot_mode=False
        return [*self.forward_events,*[v for row in result for v in row]]
