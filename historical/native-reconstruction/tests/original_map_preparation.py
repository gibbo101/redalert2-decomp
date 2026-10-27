# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete ordinary map cell pass with actual lighting and recalculation children."""
import hashlib,struct
from original_presentation import PresentationOracle,STOP
from original_foot_lit import words
from original_map_cell_preparation import FIELD_MAP,STATE,pack
from verify_map_preparation import verify,RANGES
from verify_map_cell_children import LAT_GLOBALS
from unicorn import UC_HOOK_CODE,UC_HOOK_BLOCK,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_ESP,UC_X86_REG_ECX,UC_X86_REG_EAX
MAP=0x8324e0;FALLBACK=0xa6f9f8;CELLS=0x2400000;TYPES=0x2c00000;REGISTRY=0x2d00000
IMAGES=0x2d10000;SLOTS=0x2e00000;BUFF4=0x2f00000;BUFF10=0x3000000;RULES=0x3100000;SCENARIO=0x3110000
FIELDS={0x38:(1,4),0x11a:(2,1),0xec:(3,4),0x11c:(4,1),0x11b:(5,1),0x11d:(6,1),0x4c:(7,4),0x30:(8,4),0x140:(9,4),0x34:(10,4),0x104:(11,4),**{0x108+i*2:(12+i,2) for i in range(7)}}
def digest(b):return hashlib.sha256(b).hexdigest()
class MapPreparationOracle(PresentationOracle):
    def __init__(self,exe):
        self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(CELLS,0xe00000)
        self.entries={hex(p):0 for p in RANGES};self.stores=0;self.u.hook_add(UC_HOOK_BLOCK,self.block)
        for a in {*RANGES,0x55a679}:self.u.hook_add(UC_HOOK_CODE,self.code,begin=a,end=a)
        self.checked_call(0x491620,writes=[(0x851a70,32)]);self.initial_directions=words(self.u,0x851a70,8)
    def va(self,a):return a
    def call(self,a,args=(),ecx=0,edx=0,budget=60000000):super().call(a,args,ecx,edx,budget)
    def block(self,u,a,n,ctx):
        if a==STOP:return
        if not any(p<=a and a+n<=p+size for p,size in RANGES.items()):raise AssertionError(f'Uninspected map preparation block {a:#x}/{n}')
    def code(self,u,a,n,ctx):
        if a in RANGES:self.entries[hex(a)]+=1
        ecx=u.reg_read(UC_X86_REG_ECX)
        if a==0x55a490:
            slot=words(u,MAP+0x114,1)[0];assert SLOTS<=slot<SLOTS+0x100000;p=words(u,slot,1)[0];self.visits.append((p-CELLS)//512 if p else -1)
        elif a in (0x4790f0,0x476ba0,0x472540):
            assert CELLS<=ecx<CELLS+self.count*512 and (ecx-CELLS)%512==0
            self.events.extend([{0x4790f0:301,0x476ba0:302,0x472540:303}[a],(ecx-CELLS)//512])
            if a==0x4790f0:assert words(u,u.reg_read(UC_X86_REG_ESP)+4,6)==[0,65536,0,1000,1000,1000]
            elif a==0x476ba0:assert words(u,u.reg_read(UC_X86_REG_ESP)+4,1)==[0]
            else:assert words(u,u.reg_read(UC_X86_REG_ESP)+4,1)==[0xffffffff]
        elif a==0x548070:
            assert ecx==MAP;pos=words(u,words(u,u.reg_read(UC_X86_REG_ESP)+4,1)[0],1)[0];self.events.extend([304,pos])
        elif a==0x55a660:self.permission=words(u,words(u,u.reg_read(UC_X86_REG_ESP)+4,1)[0],1)[0]
        elif a==0x55a679:self.events.extend([304,self.permission])
        elif a in (0x471d10,0x478f40):
            assert CELLS<=ecx<CELLS+self.count*512;self.events.extend([305 if a==0x471d10 else 306,(ecx-CELLS)//512,*[int.from_bytes(u.mem_read(ecx+off,n),'little') for off,n in ((0x38,4),(0xec,4),(0x11c,1),(0x11b,1),(0x11d,1),(0x4c,4))]])
    def install_types(self,types):
        for i,row in enumerate(types):
            present,valid,ramp,land,h,y,ey,extra=row;p=TYPES+i*1024;image=IMAGES+i*128;sub=image+32
            self.put(p,0x7a51a8);self.put(p+0xa4,image if present else 0);self.put(p+0x298,-1);self.put(REGISTRY+i*4,p)
            self.u.mem_write(image,pack([1,1,60,h,sub if valid else 0])+bytes(12));self.u.mem_write(sub,bytes(64));self.put(sub+4,y);self.put(sub+0x18,ey);self.put(sub+0x24,extra);self.u.mem_write(sub+0x29,bytes([land,ramp]))
        self.u.mem_write(REGISTRY+len(types)*4,b'\xa7'*64)
        return IMAGES,len(types)*128
    def run(self,width,height,seed,hole,cliff,light,mapping,lat,directions,speeds,types,cells,shape=None):
        self.count=len(cells);self.events=[];self.visits=[];capacity=(width+height+1)**2
        self.u.mem_write(CELLS,b'\xa5'*(len(cells)*512));self.u.mem_write(SLOTS,bytes(0x100000));self.u.mem_write(TYPES,bytes(len(types)*1024))
        image_region=self.install_types(types)
        for i,row in enumerate(cells):
            x,y,tile,sub,level,flags,tube,land,slope,extra,data,ice,passability,field30=row;p=CELLS+i*512
            self.put(p+0x24,(x&65535)|((y&65535)<<16));self.put(p+0x3c,0);self.put(p+0x44,-1);self.put(p+0xe4,0);self.put(p+0x34,0);self.put(p+0x30,field30)
            for (off,n),v in zip(STATE,[tile,land,tube,sub,level,slope,flags,extra,data,ice,passability]):self.u.mem_write(p+off,(v&((1<<(8*n))-1)).to_bytes(n,'little'))
            if i!=hole:self.put(SLOTS+(y*512+x)*4,p)
        self.u.mem_write(FALLBACK,bytes(0x148));self.put(FALLBACK+0x24,0xffffffff);self.put(FALLBACK+0x38,65535);self.u.mem_write(FALLBACK+0x116,b'\xff\xff')
        self.put(MAP+0xf0,width);self.put(MAP+0xf4,height)
        assert shape is None or shape[0]==width
        for off,v in zip((0xf8,0xfc,0x100,0x104),(shape or [width,0,0,width,height])[1:]):self.put(MAP+off,v)
        self.put(MAP+0x138,SLOTS);self.put(MAP+0x64,BUFF4);self.put(MAP+0x68,capacity);self.put(MAP+0x6c,BUFF10)
        self.u.mem_write(BUFF4,b'\xa5'*(capacity*4)+b'\xa7'*64);self.u.mem_write(BUFF10,b'\xa5'*(capacity*10)+b'\xa7'*64)
        self.put(0xa40970,0);self.put(0xa40cd4,REGISTRY);self.put(0xa40ce0,len(types));self.put(0x8661d8,0);self.put(0x839848,RULES);self.u.mem_write(RULES,bytes(0x600));self.u.mem_write(RULES+0x584,bytes([cliff]))
        for a,v in zip(LAT_GLOBALS,lat):self.put(a,v)
        self.u.mem_write(0x851a70,pack(directions));self.u.mem_write(0x7de4ec,pack(mapping))
        for i,v in enumerate(speeds):self.put(0x850ea8+i*36,v)
        self.put(0xa3d290,SCENARIO);self.u.mem_write(SCENARIO,bytes(0x22c8))
        for off,v in zip((0x22ac,0x22b4,0x22b8,0x22bc,0x22c0,0x22c4),light):self.put(SCENARIO+off,v)
        self.u.mem_write(0xa51934,b'\0');self.put(0xa5193c,0);self.put(0xa6e828,0);self.put(0x839950,0)
        before=bytes(self.u.mem_read(CELLS,len(cells)*512));old_fallback=bytes(self.u.mem_read(FALLBACK,0x148))
        def stores(u,access,p,n,v,ctx):
            self.stores+=1
            if CELLS<=p<CELLS+len(cells)*512:
                index=(p-CELLS)//512;off=(p-CELLS)%512;assert off in FIELDS and FIELDS[off][1]==n,(hex(p),n);self.events.extend([index,FIELDS[off][0],v&((1<<(8*n))-1)])
            elif p==FALLBACK+0x24:assert n==4;self.events.extend([0xffffffff,0,v&0xffffffff])
            elif BUFF4<=p<BUFF4+capacity*4:assert n==1;self.events.extend([0xfffffffe,p-BUFF4,v&255])
            elif BUFF10<=p<BUFF10+capacity*10:assert n==1;self.events.extend([0xfffffffd,p-BUFF10,v&255])
        immutable=[(TYPES,len(types)*1024),(REGISTRY,len(types)*4+64),image_region,(SLOTS,0x100000),(MAP+0xf0,24),(MAP+0x64,16),(MAP+0x138,4),(RULES,0x600),(SCENARIO,0x22c8),(0xa3d290,4),(0x839848,4),(0xa40cd4,4),(0xa40ce0,4),(0x8661d8,4),(0xa40970,4),(0x851a70,32),(0x7de4ec,64),(0x850ea8,396),(0xa51934,1),(0xa5193c,4),(0xa6e828,4),(0x839950,4),*[(a,4) for a in LAT_GLOBALS]]
        hook=self.u.hook_add(UC_HOOK_MEM_WRITE,stores)
        try:self.checked_call(0x54b2e0,ecx=MAP,writes=[(CELLS,len(cells)*512),(MAP+0x108,16),(FALLBACK+0x24,4),(BUFF4,capacity*4),(BUFF10,capacity*10)],inputs=immutable)
        finally:self.u.hook_del(hook)
        assert self.u.reg_read(UC_X86_REG_EAX)==0
        after=bytearray(self.u.mem_read(CELLS,len(cells)*512));state=[]
        for i in range(len(cells)):
            p=CELLS+i*512;state.extend([words(self.u,p+0x24,1)[0],*[int.from_bytes(self.u.mem_read(p+off,n),'little') for off,n in ((0x38,4),(0xec,4),(0x116,2),(0x11a,1),(0x11b,1),(0x11c,1),(0x140,4),(0x11d,1),(0x11e,1),(0x119,1),(0x4c,4),(0x30,4),(0x34,4),(0x104,4),*[(0x108+j*2,2) for j in range(7)])]])
            for off,(field,n) in FIELDS.items():after[i*512+off:i*512+off+n]=before[i*512+off:i*512+off+n]
        assert bytes(after)==before
        final_fallback=bytearray(self.u.mem_read(FALLBACK,0x148));final_fallback[0x24:0x28]=old_fallback[0x24:0x28];assert bytes(final_fallback)==old_fallback
        for p,n in ((BUFF4,capacity*4),(BUFF10,capacity*10)):assert bytes(self.u.mem_read(p+n,64))==b'\xa7'*64
        cursor=words(self.u,MAP+0x108,4);cursor[-1]=(cursor[-1]-SLOTS)//4
        return [digest(pack(state)),digest(pack(self.events)),digest(pack(self.visits)),digest(bytes(self.u.mem_read(BUFF4,capacity*4))),digest(bytes(self.u.mem_read(BUFF10,capacity*10))),digest(pack([*cursor,words(self.u,FALLBACK+0x24,1)[0]]))]
