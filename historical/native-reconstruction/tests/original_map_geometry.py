# SPDX-License-Identifier: GPL-3.0-or-later
"""Unchanged initial Map creation/visible/buffer roots; explicit host services."""
import hashlib,struct
from original_presentation import PresentationOracle,STACK,ARG,STOP
from original_foot_lit import words,ret
from original_map_cell_inputs import FIELDS,initial,projection,digest_words,FALLBACK
from verify_map_geometry import verify,RANGES
from unicorn import UC_HOOK_BLOCK,UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_ECX,UC_X86_REG_ESP
MAP=0x8324e0;CELLS=0x2400000;TABLE=0x4400000;BUFFERS=0x4500000
VTABLE=ARG+0x1000;CLEAR=ARG+0x2000
class MapGeometryOracle(PresentationOracle):
    def __init__(self,exe):
        self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True)
        self.u.mem_map(CELLS,0x2400000)
        self.services={0x782017,0x781d3b,0x4e09a0,0x4284e0,0x54b2e0,0x54fda0,0x54ebd0,0x563d80,0x429a90,CLEAR}
        self.u.hook_add(UC_HOOK_BLOCK,self.block)
        for a in self.services:self.u.hook_add(UC_HOOK_CODE,self.service,begin=a,end=a)
        for a in RANGES:self.u.hook_add(UC_HOOK_CODE,self.entry,begin=a,end=a)
        self.entries={hex(a):0 for a in RANGES};self.store_count=0;self.service_count=0
    def va(self,a):return a
    def call(self,a,args=(),ecx=0,edx=0,budget=40000000):super().call(a,args,ecx,edx,budget)
    def entry(self,u,a,n,ctx):self.entries[hex(a)]+=1
    def block(self,u,a,n,ctx):
        if a==STOP or a in self.services:return
        if not any(start<=a and a+n<=start+size for start,size in RANGES.items()):
            raise AssertionError(f'Uninspected geometry block {a:#x}/{n}')
    def service(self,u,a,n,ctx):
        sp=u.reg_read(UC_X86_REG_ESP);ecx=u.reg_read(UC_X86_REG_ECX);caller=words(u,sp,1)[0]
        self.service_count+=1
        if a==0x782017:
            size=words(u,sp+4,1)[0]
            if caller==0x548c9d:
                assert self.operation=='G' and size==0x148
                p=CELLS+self.cell_count*512
                assert p+size<=TABLE
                u.mem_write(p,b'\xa5'*512)
                for (off,n),v in zip(FIELDS,initial(self.seed,self.cell_count)):
                    u.mem_write(p+off,(v&((1<<(8*n))-1)).to_bytes(n,'little'))
                self.allocations.append((p,size));self.cell_count+=1
            else:
                assert caller in (0x549a11,0x549a43)
                cap=words(u,MAP+0x68,1)[0];assert cap<=66049
                expected=cap*(4 if caller==0x549a11 else 10);assert size==expected
                p=BUFFERS+(0 if caller==0x549a11 else 0x100000)
                assert size<=0x100000
                u.mem_write(p,bytes([self.fill])*size+b'\xa7'*64)
                self.allocations.append((p,size));self.buffer_allocations.append((p,size))
            ret(u,0,p)
        elif a==0x781d3b:
            p=words(u,sp+4,1)[0]
            assert (caller==0x5499aa and p==0) or (caller==0x5499d5 and p==BUFFERS+0x200000) or (caller==0x5499e8 and p==BUFFERS+0x201000)
            ret(u,0)
        elif a==0x4e09a0:
            assert caller in (0x549979,0x549b88) and ecx==MAP and words(u,sp+4,1)==[2];ret(u,4)
        elif a==0x4284e0:
            assert caller==0x549a5a and ecx==0x8315c8 and words(u,sp+4,1)==[MAP+0xe8];ret(u,4)
        elif a in (0x54b2e0,0x54fda0,0x54ebd0):
            assert caller=={0x54b2e0:0x549a98,0x54fda0:0x549a9f,0x54ebd0:0x549aa6}[a] and ecx==MAP;ret(u,0)
        elif a==CLEAR:
            assert caller==0x549ab9 and ecx in (MAP+0xb8,MAP+0xa0,MAP+0x88);ret(u,0)
        elif a==0x563d80:
            zone=words(u,sp+4,1)[0];assert caller==0x549ac1 and ecx==MAP and zone in (0,1,2);ret(u,4)
        elif a==0x429a90:
            assert caller==0x549ad3 and ecx==0x8315c8;ret(u,0)
        else:raise AssertionError(hex(a))
    def prepare(self,seed=0,invalid=0):
        self.seed=seed;self.cell_count=0;self.allocations=[];self.buffer_allocations=[];self.events=[];self.fill=(seed*37+0x93)&255
        self.u.mem_write(MAP,b'\xa5'*0x200);self.u.mem_write(FALLBACK,b'\xa5'*0x148)
        for (off,n),v in zip(FIELDS,initial(seed,99999)):self.u.mem_write(FALLBACK+off,(v&((1<<(8*n))-1)).to_bytes(n,'little'))
        self.u.mem_write(TABLE,bytes(0x100000));self.put(MAP+0x138,TABLE);self.put(MAP+0x13c,262144)
        self.put(MAP+0xf0,5);self.put(MAP+0xf4,6)
        for off in (0x64,0x68,0x6c):self.put(MAP+off,0)
        for off in (0x88,0xa0,0xb8):self.put(MAP+off,VTABLE)
        self.put(VTABLE+12,CLEAR)
        for p in (0xa40378,0xa40970,0x8661d8,0xa40c30,0xa3d290):self.put(p,0)
        self.put(0x850bd8,invalid);self.put(0xa6f238,0x7fff7fff);self.put(0x833968,seed)
    def buffer_result(self):
        cap=words(self.u,MAP+0x68,1)[0];a,b=words(self.u,MAP+0x64,1)[0],words(self.u,MAP+0x6c,1)[0]
        if not a:return '-'
        assert (a,cap*4) in self.allocations and (b,cap*10) in self.allocations
        for p,n in ((a,cap*4),(b,cap*10)):
            assert bytes(self.u.mem_read(p+n,64))==b'\xa7'*64
        assert bytes(self.u.mem_read(b,cap*10))==bytes([self.fill])*(cap*10)
        return hashlib.sha256(bytes(self.u.mem_read(a,cap*4))+bytes(self.u.mem_read(b,cap*10))).hexdigest()
    def run(self,op,v):
        self.operation=op
        seed,invalid=(v[:2] if op=='G' else (v[-1],0))
        self.prepare(seed,invalid)
        if op=='G':
            _,_,x,y,w,h,level,rebuild=v
            self.u.mem_write(ARG,struct.pack('<4I',x&0xffffffff,y&0xffffffff,w,h))
            root=0x5484e0;args=[ARG,1,level,rebuild]
            allowed=[(MAP+0xe8,16),(MAP+0x120,16),(0xa70a1c,8),(0x833968,4),(FALLBACK,0x148)]
        elif op=='B':
            w,h,old,_=v;self.put(MAP+0xf0,w);self.put(MAP+0xf4,h)
            if old:self.put(MAP+0x64,BUFFERS+0x200000);self.put(MAP+0x6c,BUFFERS+0x201000)
            root=0x5499c0;args=[];allowed=[]
        else:
            full,requested=v[:4],v[4:8]
            self.u.mem_write(MAP+0xe8,struct.pack('<4I',*[n&0xffffffff for n in full]));self.u.mem_write(ARG,struct.pack('<4I',*[n&0xffffffff for n in requested]))
            root=0x549ae0;args=[ARG];allowed=[(MAP+0xf8,16)]
        if op in ('G','B'):
            allowed += [(MAP+0x64,12),*[(MAP+off,4) for off in (0x9c,0xb4,0xcc)],(CELLS,TABLE-CELLS),(TABLE,0x100000),(BUFFERS,0x200000)]
        immutable=[(MAP+0x138,8),(0x850bd8,4),(0xa6f238,4),(0xa3d290,4),(VTABLE+12,4),(ARG,16)]
        map_before=bytes(self.u.mem_read(MAP,0x200))
        def stores(u,access,p,n,value,ctx):
            self.store_count+=1
            if CELLS<=p<TABLE:
                i=(p-CELLS)//512;off=(p-CELLS)%512
                assert i<self.cell_count and off+n<=0x148,'Guest write outside supplied Cell allocation'
                if (off,n) in FIELDS:self.events.extend([i,FIELDS.index((off,n)),value&((1<<(8*n))-1)])
            elif FALLBACK<=p<FALLBACK+0x148:
                if (p-FALLBACK,n) in FIELDS:self.events.extend([0xffffffff,FIELDS.index((p-FALLBACK,n)),value&((1<<(8*n))-1)])
            elif BUFFERS<=p<BUFFERS+0x200000:
                assert any(lo<=p and p+n<=lo+size for lo,size in self.buffer_allocations),'Buffer write outside allocation'
            elif TABLE<=p<TABLE+0x100000:
                assert n==4 and value==CELLS+(self.cell_count-1)*512,'Invalid created Cell pointer'
        hook=self.u.hook_add(UC_HOOK_MEM_WRITE,stores)
        try:self.checked_call(root,args,MAP,writes=allowed,inputs=immutable)
        finally:self.u.hook_del(hook)
        # Preserve every unselected Map byte, not just the supplied pointer header.
        map_after=bytearray(self.u.mem_read(MAP,0x200))
        for p,n in allowed:
            if MAP<=p and p+n<=MAP+0x200:map_after[p-MAP:p-MAP+n]=map_before[p-MAP:p-MAP+n]
        assert bytes(map_after)==map_before
        if op=='V':return [*struct.unpack('<4i',self.u.mem_read(MAP+0xf8,16))]
        if op=='B':
            return [words(self.u,MAP+0x68,1)[0],*[struct.unpack('<i',self.u.mem_read(MAP+off,4))[0] for off in (0x9c,0xb4,0xcc)],self.buffer_result()]
        ptrs=words(self.u,TABLE,262144);assert sum(bool(p) for p in ptrs)==self.cell_count
        values=[]
        for i in range(self.cell_count):
            p=CELLS+i*512;values.extend(projection(self.u,p));pos=words(self.u,p+0x24,1)[0]
            x,y=struct.unpack('<hh',struct.pack('<I',pos));assert ptrs[y*512+x]==p
            assert bytes(self.u.mem_read(p+0x148,512-0x148))==b'\xa5'*(512-0x148)
        values.extend(projection(self.u,FALLBACK))
        geometry=[*words(self.u,MAP+0xe8,4),*words(self.u,MAP+0x120,4),*words(self.u,0xa70a1c,2),words(self.u,0x833968,1)[0]]
        return [self.cell_count,digest_words(values),digest_words(self.events),digest_words(geometry),self.buffer_result()]
