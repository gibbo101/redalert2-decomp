# SPDX-License-Identifier: GPL-3.0-or-later
"""Hash-pinned ordinary cell lighting and actual INI numeric conversion blocks."""
import struct
from original_presentation import PresentationOracle,OBJ,ARG,STACK,STOP
from map_light_profiles import address
from original_staging import StagingOracle
from unicorn import UC_HOOK_CODE, UC_HOOK_MEM_WRITE
from unicorn.x86_const import *

class MapLightOracle(PresentationOracle):
    def __init__(self,exe,*,allow_patched=False):
        super().__init__(exe,allow_patched=allow_patched)
        self.getter_calls=0
        self.u.hook_add(UC_HOOK_CODE,self.getter)

    def va(self,disc_va):return address(self.profile,disc_va)

    def getter(self,u,guest_va,size,ctx):
        if guest_va!=self.va(0x4702c0):return
        # Explicit world-height service. The cell routine computes its own X/Y;
        # this returned coordinate's Z never enters the tested radial falloff.
        self.getter_calls+=1
        sp=u.reg_read(UC_X86_REG_ESP);out=struct.unpack('<I',u.mem_read(sp+4,4))[0]
        u.mem_write(out,bytes(12));u.reg_write(UC_X86_REG_EAX,out)
        u.reg_write(UC_X86_REG_EIP,struct.unpack('<I',u.mem_read(sp,4))[0]);u.reg_write(UC_X86_REG_ESP,sp+8)

    def quantize(self,values):
        result=[]
        for i,v in enumerate(values):
            self.u.ctl_remove_cache(self.va(0x4b9f30),self.va(0x4b9fa0))
            self.u.mem_write(STACK,struct.pack('<Id',STOP,v))
            self.u.reg_write(UC_X86_REG_ESP,STACK);self.u.reg_write(UC_X86_REG_FPCW,0xe7f)
            self.u.reg_write(UC_X86_REG_FPSW,0);self.u.reg_write(UC_X86_REG_FPTAG,0xffff)
            guard=bytes([0xa7])*64;self.u.mem_write(STACK+12,guard)
            before=bytes(self.u.mem_read(STACK,12))
            def audit(u,access,p,n,value,ctx):
                if not STACK-0x2000<=p or p+n>STACK:raise AssertionError("Unexpected map numeric-block write")
            hook=self.u.hook_add(UC_HOOK_MEM_WRITE,audit)
            try:
                # Load the explicit double with one existing original instruction,
                # then execute the actual map-loader multiply + conversion block.
                self.u.emu_start(self.va(0x4b9f30),self.va(0x4b9f34),count=10)
                if self.u.reg_read(UC_X86_REG_EIP)!=self.va(0x4b9f34):raise RuntimeError('Explicit FP input load did not stop')
                begin=0x659071 if i<4 else 0x659160
                end=0x65907c if i<4 else 0x65916b
                self.u.emu_start(self.va(begin),self.va(end),count=100)
                if self.u.reg_read(UC_X86_REG_EIP)!=self.va(end):raise RuntimeError('INI conversion block failed')
            finally:self.u.hook_del(hook)
            if self.u.reg_read(UC_X86_REG_ESP)!=STACK or bytes(self.u.mem_read(STACK,12))!=before or bytes(self.u.mem_read(STACK+12,64))!=guard:
                raise AssertionError("Map numeric-block stack/input changed")
            self.audit_blocks+=2
            result.append(struct.unpack('<i',struct.pack('<I',self.u.reg_read(UC_X86_REG_EAX)))[0])
        return result

    def normalize(self,brightness,tint):
        self.u.mem_write(ARG,struct.pack('<5i',0,brightness,*tint))
        self.checked_call(0x536450,[ARG+8,ARG+12,ARG+16],ARG,ARG+4,writes=[(ARG,20)])
        return list(struct.unpack('<5i',self.u.mem_read(ARG,20)))

    def cell(self,settings,x,y,elevation,sources=(),clock=0):
        scenario=OBJ+0x1000;array=OBJ+0x5000;objects=OBJ+0x10000
        self.u.mem_write(OBJ,bytes(0x200))
        self.u.mem_write(OBJ+0x24,struct.pack('<2h',x,y));self.u.mem_write(OBJ+0x11b,bytes([elevation]))
        self.put(self.va(0xa255a0),scenario)
        for off,v in zip([0x22ac,0x22b4,0x22b8,0x22bc,0x22c0,0x22c4],settings):self.put(scenario+off,v)
        self.u.mem_write(self.va(0xa39554),b'\x00');self.put(self.va(0xa3955c),0)
        self.put(self.va(0xa5642c),array);self.put(self.va(0xa56438),len(sources));self.put(self.va(0xa2874c),clock)
        for i,s in enumerate(sources):
            # Ordered explicit original LightSource fields: position/radius,
            # intensity/tint, activation flag and threshold. No world actors.
            sx,sy,sz,radius,intensity,red,green,blue,active,activation=s
            at=objects+i*0x80;self.put(array+i*4,at)
            for off,v in zip([0x38,0x3c,0x40,0x44,0x24,0x28,0x2c,0x30,0x34],[sx,sy,sz,radius,intensity,red,green,blue,activation]):self.put(at+off,v)
            self.u.mem_write(at+0x48,bytes([active]))
        self.u.mem_write(ARG,bytes(32))
        inputs=[(OBJ,0x200),(scenario,0x22c8),(array,len(sources)*4),(objects,len(sources)*0x80)]
        inputs += [(self.va(p),n) for p,n in [(0xa255a0,4),(0xa39554,1),(0xa3955c,4),(0xa5642c,4),(0xa56438,4),(0xa2874c,4)]]
        self.checked_call(0x479040,[ARG+i*4 for i in range(8)],OBJ,writes=[(ARG,32)],inputs=inputs)
        return list(struct.unpack('<8i',self.u.mem_read(ARG,32)))

class MapLightSurfaceOracle(StagingOracle):
    """Local migrated surface fixture; other staging descendants retain their gates."""
    def va(self,disc_va):return address(self.profile,disc_va)
    def visible_alpha(self,w,h):
        prior=self.heap_inputs()
        hook=self.u.hook_add(UC_HOOK_MEM_WRITE,self.guarded_heap_write)
        try:self.checked_call(0x410a60,[0,0,w,h],0x1600000,
             writes=[(0x1600000,48),(0x1300000,0x300000)],inputs=prior)
        finally:self.u.hook_del(hook)
        self.check_heap()
        surface=struct.unpack('<I',self.u.mem_read(0x1600014,4))[0]
        if self.u.mem_read(surface+12,4)!=bytes(4):raise AssertionError('Alpha surface lock count not restored')
        ptr=struct.unpack('<I',self.u.mem_read(0x1600018,4))[0]
        return list(struct.unpack('<'+'H'*(w*h),self.u.mem_read(ptr,w*h*2)))
