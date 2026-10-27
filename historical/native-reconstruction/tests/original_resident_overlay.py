# SPDX-License-Identifier: GPL-3.0-or-later
"""Actual shared resident Cell children inside decoded overlay placement."""
from original_overlay_map_resources import OverlayMapResourceOracle
from original_overlay_map_preparation import CELL_FIELDS
from original_map_overlay_loading import ROOT,CELLS,TYPES,MAP,FALLBACK,pack
from original_foot_lit import words
from verify_resident_cell import RANGES as CELL_RANGES
from verify_map_cell_children import LAT_GLOBALS
from verify_resident_overlay import verify
from verify_map_overlay_loading import RANGES as READER_RANGES
from unicorn import UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_ECX,UC_X86_REG_ESP
BASE=0x3600000;TILE0=BASE;TILE1=BASE+0x1000;ALTERNATE=BASE+0x2000
TILES=BASE+0x4000;BUFFER4=BASE+0x10000;BUFFER10=BASE+0x50000;CAPACITY=65536
EXTRA_FIELDS=((0x38,4),(0xec,4),(0x116,2),(0x11a,1),(0x11b,1),(0x11c,1),(0x140,4),(0x11d,1),(0x119,1))
class ResidentOverlayOracle(OverlayMapResourceOracle):
    cell_fields=tuple(dict.fromkeys((*CELL_FIELDS,*EXTRA_FIELDS)))
    def __init__(self,exe):
        super().__init__(exe);self.inspection=verify(exe.read_bytes());self.u.mem_map(BASE,0x100000)
        self.roots.update({hex(a):0 for a in CELL_RANGES if hex(a) not in self.roots})
        self.recalculations=self.lat_entries=self.passability_entries=self.buffer_stores=0
    def code(self,u,a,n,ctx):
        # The reader byte loop dominates this suite. Delegate its already
        # inspected complete range before scanning the unrelated Cell ranges.
        if ROOT<=a and a+n<=ROOT+READER_RANGES[ROOT]:return super().code(u,a,n,ctx)
        if 0x5dc0b0<=a and a+n<=0x5dc16e:return super().code(u,a,n,ctx)
        if any(lo<=a and a+n<=lo+size for lo,size in CELL_RANGES.items()):
            if a in CELL_RANGES:self.roots[hex(a)]+=1
            sp=u.reg_read(UC_X86_REG_ESP);receiver=u.reg_read(UC_X86_REG_ECX)
            if a==0x472540:
                assert words(u,sp+4,1)==[0xffffffff];self.cell_id(receiver);self.recalc_cell=receiver
                self.events.extend([52,self.cell_id(receiver),0xffffffff]);self.recalculations+=1
            elif a==0x471d10:self.lat_entries+=1
            elif a==0x478f40:self.passability_entries+=1
            elif a==0x548070:
                assert receiver==MAP;self.events.extend([6,words(u,words(u,sp+4,1)[0],1)[0]])
            elif a==0x55a660:
                assert receiver==MAP;self.permission_position=words(u,words(u,sp+4,1)[0],1)[0]
            elif a==0x55a679:self.events.extend([6,self.permission_position])
            return
        return super().code(u,a,n,ctx)
    def configure_cells(self):
        u=self.u;p=self.resident_profile
        for i,cell in enumerate([*(CELLS+i*512 for i in range(self.count)),FALLBACK]):
            i=7 if cell==FALLBACK else i
            for off,value in ((0x38,777 if cell==FALLBACK else 200 if i%2 else 100),(0xec,0),(0x140,0)):
                self.put(cell+off,value)
            u.mem_write(cell+0x116,b'\xff\xff');u.mem_write(cell+0x119,bytes([0,0,i%7,i%5,0]))
        for address,ramp,land,height in ((TILE0,5 if p==1 else 1,0,45),(TILE1,0,2,60),(ALTERNATE,4,6,77)):
            u.mem_write(address,bytes(0x1000));self.put(address,0x7a51a8);self.put(address+0xa4,0 if p==2 else address+0x500)
            self.put(address+0x298,-1);u.mem_write(address+0x500,pack([1,1,60,height,address+0x600]))
            u.mem_write(address+0x600+0x29,bytes([land,ramp]))
        table=[ALTERNATE]*1024;table[100]=TILE0;table[200]=TILE1;u.mem_write(TILES,pack(table))
        for address,value in ((0xa40cd4,TILES),(0xa40ce0,1024),(0x8661d8,0),
             (MAP+0x64,BUFFER4),(MAP+0x68,CAPACITY),(MAP+0x6c,BUFFER10),
             (MAP+0xf8,0),(MAP+0xfc,0),(MAP+0x100,words(u,MAP+0xf0,1)[0]),(MAP+0x104,words(u,MAP+0xf4,1)[0])):
            self.put(address,value)
        u.mem_write(BUFFER4,b'\xa5'*(CAPACITY*4));u.mem_write(BUFFER10,b'\xa5'*(CAPACITY*10))
        u.mem_write(0x7de4ec,pack([i%10 for i in range(16)]))
        for address,value in zip(LAT_GLOBALS,(10,20,100,200,300,400,450,500,550,600,700,90,190,290,390)):
            self.put(address,value)
        for i in range(11):self.put(0x850ea8+i*36,0 if i==3 else 0x3f800000)
        u.mem_write(0x2f01000+0x584,bytes([2 if p==3 else 0]))
        for i in range(len(self.types)):
            u.mem_write(TYPES+i*1024+0x27c,bytes([p%2]));u.mem_write(TYPES+i*1024+0x1fd,bytes([int(i%3==0)]))
        def stores(u,access,address,n,value,ctx):
            for kind,base,stride,size in ((0,BUFFER4,4,CAPACITY*4),(1,BUFFER10,10,CAPACITY*10)):
                if not base<=address<base+size:continue
                assert n==1
                index,off=divmod(address-base,stride);assert off in ((0,1) if not kind else (8,))
                pos=words(u,self.recalc_cell+0x24,1)[0];x=(pos&65535);x=x-65536 if x&32768 else x;y=pos>>16;y=y-65536 if y&32768 else y
                width,height=words(u,MAP+0xf0,2);expected=((width+height+1)*y+x)&0xffffffff;expected=expected-0x100000000 if expected&0x80000000 else expected
                assert index==min(CAPACITY-1,max(0,expected))
                self.events.extend([68,kind,index,off,value&255]);self.buffer_stores+=1
        self.buffer_hook=u.hook_add(UC_HOOK_MEM_WRITE,stores)
    def extra_inputs(self):
        return [(BASE,0x10000),(0xa40cd4,4),(0xa40ce0,4),(0x8661d8,4),(0x7de4ec,64),
          (MAP,0x140),(0x850ea8,396),*[(a,4) for a in LAT_GLOBALS]]
    def extra_writes(self):return [(BUFFER4,CAPACITY*4),(BUFFER10,CAPACITY*10)]
    def extra_output(self):
        result=[]
        for cell in [*(CELLS+i*512 for i in range(self.count)),FALLBACK]:
            result.extend(int.from_bytes(self.u.mem_read(cell+off,n),'little') for off,n in EXTRA_FIELDS)
        return [*result,*words(self.u,BUFFER4,CAPACITY),*words(self.u,BUFFER10,CAPACITY*10//4)]
    def run(self,op,v,profile):
        assert 0<=profile<=3;self.resident_profile=profile;self.buffer_hook=None
        try:return super().run(op,v)
        finally:
            if self.buffer_hook is not None:self.u.hook_del(self.buffer_hook)
