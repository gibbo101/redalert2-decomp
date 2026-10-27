# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact wall selection with actual Cell-target numeric/getter children.

Only the terrain-height call is supplied in W. S deliberately supplies the
distance child to cover selector-only signed/tie sentinels, separately labeled.
"""
import hashlib,struct
from original_presentation import PresentationOracle,STOP
from original_foot_lit import words
from verify_map_wall_owner import verify,RANGES
from unicorn import UC_HOOK_CODE,UC_HOOK_BLOCK,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EIP
BUILD=0x2400000;TYPE=0x2800000;HOUSE=0x2c00000;COUNTRY=0x3000000
REGISTRY=0x3400000;CELL=0x3500000;OVERLAYS=CELL+0x1000;OVERLAY_TYPE=CELL+0x2000
def packed(values):return struct.pack('<'+'I'*len(values),*[v&0xffffffff for v in values])
class MapWallOwnerOracle(PresentationOracle):
    def __init__(self,exe):
        self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True)
        self.u.mem_map(BUILD,0x1200000);self.entries={hex(a):0 for a in RANGES};self.service_calls=0;self.stores=0
        self.negative_distances=0;self.zero_distances=0
        self.u.hook_add(UC_HOOK_BLOCK,self.block)
        for a in {*RANGES,0x4706c0,0x5d4c8b}:self.u.hook_add(UC_HOOK_CODE,self.code,begin=a,end=a)
    def va(self,a):return a
    def block(self,u,a,n,ctx):
        if a in (STOP,0x4706c0) or (self.mode=='S' and a==0x5d4c00):return
        if not any(p<=a and a+n<=p+size for p,size in RANGES.items()):raise AssertionError(f'Uninspected wall owner block {a:#x}/{n}')
    def event(self,*v):self.events.extend(v)
    def returned(self,value):
        sp=self.u.reg_read(UC_X86_REG_ESP);ret=words(self.u,sp,1)[0]
        self.u.reg_write(UC_X86_REG_EAX,value&0xffffffff);self.u.reg_write(UC_X86_REG_ESP,sp+8);self.u.reg_write(UC_X86_REG_EIP,ret)
    def index(self,p):
        assert BUILD<=p<BUILD+len(self.rows)*4096 and (p-BUILD)%4096==0
        return (p-BUILD)//4096
    def code(self,u,a,n,ctx):
        ecx=u.reg_read(UC_X86_REG_ECX);sp=u.reg_read(UC_X86_REG_ESP)
        if a in RANGES and not(self.mode=='S' and a==0x5d4c00):self.entries[hex(a)]+=1
        if a==0x5d4c00:
            self.current=self.index(ecx);assert words(u,sp+4,1)==[CELL];self.event(1,self.current)
            if self.mode=='S':
                value=self.rows[self.current][-1];self.event(10,value);self.service_calls+=1;self.returned(value)
        elif a==0x47ba50:
            assert ecx==CELL;self.event(2,self.position)
        elif a==0x4706c0:
            ptr=words(u,sp+4,1)[0];xy=words(u,ptr,2);self.event(3,*xy);self.service_calls+=1;self.returned(self.height)
        elif a==0x444080:self.event(4,self.index(ecx))
        elif a in (0x458930,0x458940):
            assert TYPE<=ecx<TYPE+len(self.rows)*4096 and (ecx-TYPE)%4096==0
            if a==0x458940:assert words(u,sp+4,1)==[0]
            self.event(5 if a==0x458940 else 6,words(u,ecx+0xc78,1)[0])
        elif a==0x5d4c8b:
            value=u.reg_read(UC_X86_REG_EAX);self.event(10,value)
            self.negative_distances+=bool(value&0x80000000);self.zero_distances+=value==0
        elif a==0x47cf80:assert ecx==CELL;self.event(7,11)
        elif a==0x6c7420:self.event(8,self.index(ecx))
    def run(self,mode,overlay,wall,owner,position,height,rows):
        self.mode=mode;self.rows=rows;self.position=position;self.height=height;self.events=[]
        self.u.mem_write(CELL,b'\xa5'*0x148);self.put(CELL,0x79db04);self.put(CELL+0x24,position)
        self.put(CELL+0x44,overlay);self.put(CELL+0x50,owner);self.put(OVERLAY_TYPE+0x278,wall)
        for i in range(8):self.put(OVERLAYS+i*4,OVERLAY_TYPE)
        self.put(0xa35dec,OVERLAYS);self.put(0xa40afc,REGISTRY);self.put(0xa40b08,len(rows))
        immutable=[(CELL,0x50),(CELL+0x54,0xf4),(OVERLAYS,32),(OVERLAY_TYPE,0x280),
          (0xa35dec,4),(0xa40afc,4),(0xa40b08,4),(0x7cfc70,176),(0x817dfc,65536)]
        for i,row in enumerate(rows):
            active,onmap,eligible,owner=row[:4];b=BUILD+i*4096;t=TYPE+i*4096;h=HOUSE+i*4096;c=COUNTRY+i*4096
            for p,size in ((b,0x420),(t,0xc80),(h,0x40),(c,0x1b0)):self.u.mem_write(p,b'\xa5'*size);immutable.append((p,size))
            self.put(REGISTRY+i*4,b);self.put(b,0x79cbbc)
            self.u.mem_write(b+0x7d,bytes([active]));self.u.mem_write(b+0x74,bytes([onmap]));self.put(b+0x1b4,h);self.put(b+0x418,t)
            self.put(h+0x30,owner);self.put(h+0x34,c);self.u.mem_write(c+0x1a7,bytes([eligible]))
            if mode=='W':
                foundation,width,height,x,y,z=row[4:];assert 0<=foundation<22
                assert words(self.u,0x7cfc70+foundation*4,1)==[width]
                assert words(self.u,0x7cfcc8+foundation*4,1)==[height]
                self.put(t+0xc78,foundation);self.u.mem_write(b+0x88,packed([x,y,z]))
        self.u.mem_write(REGISTRY+len(rows)*4,b'\xa7'*64);immutable.append((REGISTRY,len(rows)*4+64))
        def store(u,access,p,n,v,ctx):
            if p==CELL+0x50:assert n==4;self.event(9,v);self.stores+=1
        hook=self.u.hook_add(UC_HOOK_MEM_WRITE,store)
        try:self.checked_call(0x4724a0,ecx=CELL,writes=[(CELL+0x50,4)],inputs=immutable)
        finally:self.u.hook_del(hook)
        return [str(words(self.u,CELL+0x50,1)[0]),hashlib.sha256(packed(self.events)).hexdigest()]
