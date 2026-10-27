# SPDX-License-Identifier: GPL-3.0-or-later
"""Actual decoded reader nested with temporary Object lifetime and wall update."""
from original_map_overlay_loading import (MapOverlayLoadingOracle,CELLS,TABLE,TYPES,SCRATCH,MAP,FALLBACK,ROOT,pack,digest,packed)
from original_overlay_object_lifetime import REGS,FIELDS,VTABLE_STORES,RTTI
from original_presentation import OBJ,STACK
from original_foot_lit import words,ret
from verify_map_overlay_loading import RANGES as READER
from verify_overlay_map_preparation import verify,RANGES
from unicorn import UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_ECX,UC_X86_REG_EDX,UC_X86_REG_ESP,UC_X86_REG_EAX,UC_X86_REG_EIP
ACTORS=0x3500000;BUFFERS=ACTORS+0x80000;PROVIDER=ACTORS+0x98000;TYPEINFO=PROVIDER+0x1000
FLAG=0x7e8a8c
CELL_FIELDS=((0x44,4),(0x4c,4),(0x50,4),(0x11e,1),(0x122,1))
class OverlayMapPreparationOracle(MapOverlayLoadingOracle):
    cell_fields=CELL_FIELDS
    def configure_cells(self):
        """Install supplied consumer fields before the audited snapshots."""
        pass
    def extra_inputs(self):return []
    def extra_writes(self):return []
    def extra_output(self):return []
    def __init__(self,exe):
        super().__init__(exe);self.inspection=verify(exe.read_bytes());self.u.mem_map(ACTORS,0x100000)
        self.roots={hex(a):0 for a in RANGES};self.constructed=0
    def identity(self,p):
        assert ACTORS<=p<ACTORS+self.allocated*256 and (p-ACTORS)%256==0,hex(p)
        return (p-ACTORS)//256+1
    def slot(self,p):return self.identity(p) if p else 0
    def code(self,u,a,n,ctx):
        if ROOT<=a and a+n<=ROOT+READER[ROOT]:return super().code(u,a,n,ctx)
        if any(lo<=a and a+n<=lo+size for lo,size in READER.items()):return super().code(u,a,n,ctx)
        if any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()):
            if a in RANGES:self.roots[hex(a)]+=1
            if a==0x5da7d0:self.constructed+=1
            return
        sp=u.reg_read(UC_X86_REG_ESP);receiver=u.reg_read(UC_X86_REG_ECX);caller=words(u,sp,1)[0]
        if a in (0x40cd40,0x40dc20,0x4e09a0,0x476ba0,0x472540,0x6ecb90,0x783c05,0x781cd1,0x5d2530,0x781d3b,
                  0x474eb0,0x475100,0x4752b0,0x6a3020,0x631570,0x54fb20,0x54fc60,0x566340,0x782017):
            assert any(lo<=caller<lo+size for lo,size in RANGES.items()),hex(caller);self.service_calls+=1
            if a==0x40cd40:
                role=REGS.index(receiver);amount,zero=words(u,sp+4,2);assert zero==0 and amount==self.capacities[role]+self.growth and 0<amount<=2048
                self.events.extend([50,role+1,amount,self.grow_result])
                if self.grow_result&255:
                    for i in range(self.capacities[role],amount):self.put(BUFFERS+role*0x3000+i*4,0)
                    self.capacities[role]=amount;self.put(receiver+8,amount);u.mem_write(receiver+13,b'\1')
                ret(u,8,self.grow_result)
            elif a==0x40dc20:self.identity(receiver);self.events.append(32);ret(u,0,0)
            elif a==0x4e09a0:
                assert receiver==MAP and words(u,sp+4,1)==[0];self.events.append(33);ret(u,4)
            elif a==0x476ba0:
                id=self.cell_id(receiver);assert words(u,sp+4,1)==[0];self.events.extend([51,id,0]);value=(words(u,receiver+0x44,1)[0]*3+self.seed)&255
                u.mem_write(receiver+0x11e,bytes([value]));self.events.extend([21,id,0x11e,1,value]);ret(u,4,0)
            elif a==0x472540:
                id=self.cell_id(receiver);assert words(u,sp+4,1)==[0xffffffff];self.events.extend([52,id,0xffffffff]);value=int(words(u,receiver+0x44,1)[0]!=0xffffffff)
                self.put(receiver+0x4c,value);self.events.extend([21,id,0x4c,4,value]);ret(u,4)
            elif a==0x6ecb90:
                assert u.reg_read(UC_X86_REG_EDX)&255==1
                self.events.extend([61,self.identity(receiver)] if ACTORS<=receiver<BUFFERS else [56,self.cell_id(receiver)]);ret(u,0)
            elif a==0x783c05:self.rtti_actor=self.identity(words(u,sp+4,1)[0]);ret(u,0,TYPEINFO)
            elif a==0x781cd1:
                assert words(u,sp+4,1)==[TYPEINFO];self.events.extend([64,self.rtti_actor,RTTI.index(receiver)]);ret(u,4,0)
            elif a==0x5d2530:self.events.extend([62,self.identity(receiver)]);ret(u,0)
            elif a==0x781d3b:
                id=self.identity(words(u,sp+4,1)[0]);self.freed[id-1]+=1;self.events.extend([63,id]);ret(u,0)
            elif a in (0x474eb0,0x475100,0x4752b0):
                id=self.cell_id(receiver);kind={0x474eb0:0,0x475100:1,0x4752b0:2}[a];out=words(u,sp+4,1)[0];assert STACK-0x2000<=out<STACK
                self.events.extend([53,id,kind]);u.mem_write(out,bytes(16));ret(u,4,out)
            elif a==0x6a3020:
                assert receiver==0x2f00000 and words(u,sp+20,1)==[0];self.events.extend([54,*words(u,sp+4,4)]);ret(u,20)
            elif a in (0x631570,0x54fb20,0x54fc60,0x566340):
                assert receiver==MAP;p=words(u,sp+4,1)[0];self.cell_id(p-0x24);q=words(u,p,1)[0]
                self.events.extend([55,q] if a==0x631570 else [57,{0x54fb20:0,0x54fc60:1,0x566340:2}[a],q]);ret(u,4)
            else:
                assert ROOT<=caller<ROOT+READER[ROOT] and words(u,sp+4,1)==[0x9c]
                attempt=self.attempts;self.attempts+=1;ok=not self.divisor or attempt%self.divisor!=0;self.events.extend([8,attempt,int(ok)])
                pointer=0
                if ok:
                    assert self.allocated<2048;pointer=ACTORS+self.allocated*256;self.allocated+=1;self.freed.append(0)
                    u.mem_write(pointer,b'\xa5'*256);self.put(pointer+0x14,self.seed)
                ret(u,0,pointer)
            return
        return super().code(u,a,n,ctx)
    def run(self,op,v):
        assert op=='M';self.op=op;self.events=[];self.cursors=[0,0];self.attempts=self.allocated=0;self.freed=[]
        self.seed,version,w,h,filter_crates,r0,r1,l0,l1,self.divisor,self.data_mode,type_count=v[:12];at=12
        self.results=[r0,r1];self.limits=[l0,l1];self.types=[v[i:i+6] for i in range(at,at+type_count*6,6)];at+=type_count*6
        u=self.u;u.mem_write(TYPES,bytes(0x40000))
        for i,(image,animation,crate,demand,land,wall) in enumerate(self.types):
            p=TYPES+i*1024;self.put(p,0x7a7a08);self.put(p+0xa4,image);self.put(p+0x264,i);self.put(p+0x268,land);self.put(p+0x26c,animation)
            u.mem_write(p+0x278,bytes([wall]));u.mem_write(p+0x27a,bytes([crate]));u.mem_write(p+0x27f,bytes([demand]));self.put(TYPES+0x40000+i*4,p)
        self.put(0xa35dec,TYPES+0x40000)
        self.count=v[at];at+=1;indices=v[at:at+self.count];at+=self.count;self.binding={index:i for i,index in enumerate(indices)}
        table=bytearray(0x100000)
        for i,index in enumerate(indices):
            p=CELLS+i*512;import struct;struct.pack_into('<I',table,index*4,p);u.mem_write(p,b'\xa5'*512)
            for off,value in ((0x24,packed(index)),(0x44,-1),(0x4c,0),(0x50,-1),(0xe4,0)):self.put(p+off,value)
            u.mem_write(p+0x11c,b'\0');u.mem_write(p+0x11e,bytes([(self.seed+i*37)&255]));u.mem_write(p+0x122,b'\0')
        u.mem_write(TABLE,bytes(table));self.put(0x832618,TABLE);u.mem_write(FALLBACK,b'\xa5'*0x148)
        for off,value in ((0x24,0x12345678),(0x44,-1),(0x4c,0),(0x50,-1),(0xe4,0)):self.put(FALLBACK+off,value)
        u.mem_write(FALLBACK+0x11c,b'\0');u.mem_write(FALLBACK+0x11e,bytes([(self.seed^0xa5)&255]));u.mem_write(FALLBACK+0x122,b'\0')
        self.overrides=[]
        for _ in range(2):
            count=v[at];at+=1;self.overrides.append({v[i]:v[i+1] for i in range(at,at+count*2,2)});at+=count*2
        enabled,capacity,self.growth,owns,self.grow_result=v[at:];self.capacities=[capacity]*6
        for role,reg in enumerate(REGS):
            buffer=BUFFERS+role*0x3000;u.mem_write(buffer,b'\xd8'*0x3000);self.put(reg,0x79e868);self.put(reg+4,buffer);self.put(reg+8,capacity)
            u.mem_write(reg+12,bytes([1,owns]));self.put(reg+16,0);self.put(reg+20,self.growth)
            for i in range(capacity):self.put(buffer+i*4,0)
        for p,value in ((0xa40d24,version),(MAP+0xf0,w),(MAP+0xf4,h),(0xa3d298,filter_crates),(0xa40774,1),(0xa73088,0x7fff7fff),
                        (0xa3d290,PROVIDER if self.seed else 0),(PROVIDER+0x214,self.seed^0xfedcba98),(FLAG,self.seed),(0x83996c,0x2f00000),
                        (0x839630,0),(0x839634,0),(0x839848,0x2f01000)):self.put(p,value)
        u.mem_write(0xa40958,bytes([enabled]));u.mem_write(0xa72f00,pack([self.seed,17,-19]))
        u.mem_write(0x851a70,pack([0xffff0000,0xffff0001,1,0x10001,0x10000,0x1ffff,0xffff,0xffffffff]))
        for off in (0x77c,0x780,0x78c,0x784,0x788):self.put(0x2f01000+off,0)
        self.configure_cells()
        before=bytes(u.mem_read(CELLS,self.count*512));fallback=bytes(u.mem_read(FALLBACK,0x148));before_actors=bytes(u.mem_read(ACTORS,0x80000))
        before_buffers=[bytes(u.mem_read(BUFFERS+i*0x3000,0x3000)) for i in range(6)]
        def stores(u,access,p,n,value,ctx):
            value&=(1<<(8*n))-1
            if FALLBACK<=p<FALLBACK+0x148 or CELLS<=p<CELLS+self.count*512:
                cell=FALLBACK if FALLBACK<=p<FALLBACK+0x148 else CELLS+((p-CELLS)//512)*512;off=p-cell
                if off==0x24 and n==4 and cell==FALLBACK:self.events.extend([7,value])
                else:assert (off,n) in self.cell_fields;self.events.extend([21,self.cell_id(cell),off,n,value])
            elif ACTORS<=p<ACTORS+self.allocated*256:
                id=(p-ACTORS)//256+1;off=(p-ACTORS)%256
                if off in VTABLE_STORES:assert n==4 and value in VTABLE_STORES[off];return
                assert (off,n) in FIELDS or (off==0x14 and n==1)
                if off in (0x48,0x5c):assert value==0x830fac;value=1
                if off==0x98:assert not value or TYPES<=value<TYPES+len(self.types)*1024;value=int(bool(value))
                self.events.extend([20,id,off,n,value])
            elif p==FLAG:self.events.extend([23,0,n,value])
            elif p==PROVIDER+0x214:self.events.extend([24,0,n,value])
            elif any(reg<=p<reg+24 for reg in REGS):
                role=next(i for i,reg in enumerate(REGS) if reg<=p<reg+24);assert p==REGS[role]+16 and n==4;self.events.extend([22,role+1,0,4,value])
            elif BUFFERS<=p<BUFFERS+6*0x3000:
                role=(p-BUFFERS)//0x3000;off=(p-BUFFERS)%0x3000;assert off%4==0 and off<self.capacities[role]*4 and n==4
                self.events.extend([22,role+1,off//4+1,4,self.slot(value)])
            else:return
            self.stores+=1
        hook=u.hook_add(UC_HOOK_MEM_WRITE,stores)
        try:self.checked_call(ROOT,[],OBJ,
            writes=[(CELLS,self.count*512),(FALLBACK,0x148),(ACTORS,0x80000),(FLAG,4),(PROVIDER+0x214,4),*[(r,24) for r in REGS],*[(BUFFERS+i*0x3000,0x3000) for i in range(6)],*self.extra_writes()],
            inputs=[(TABLE,0x100000),(TYPES,0x41000),(SCRATCH,512000),(MAP+0xf0,8),(0xa40d24,4),(0xa3d298,4),(0xa35dec,4),(0x832618,4),
             (0x7e8b44,16),(0x7e8b54,12),(0xa40774,4),(0xa40958,1),(0xa73088,4),(0xa3d290,4),(0xa72f00,12),
             (0x83996c,4),(0x839630,8),(0x839848,4),(0x851a70,32),(0x7d2b58,20),(0x2f01000,0x1000),*self.extra_inputs()])
        finally:u.hook_del(hook)
        after=bytearray(u.mem_read(CELLS,self.count*512));other=bytearray(u.mem_read(FALLBACK,0x148))
        for i in range(self.count):
            for off,n in self.cell_fields:after[i*512+off:i*512+off+n]=before[i*512+off:i*512+off+n]
        for off,n in ((0x24,4),*self.cell_fields):other[off:off+n]=fallback[off:off+n]
        assert bytes(after)==before and bytes(other)==fallback
        # Allocator supplies raw bytes. Audit nonselected bytes against that
        # allocation pattern, including the untouched tail beyond all objects.
        after_actors=bytearray(u.mem_read(ACTORS,0x80000));raw=bytearray(before_actors)
        for i in range(self.allocated):
            raw[i*256:(i+1)*256]=b'\xa5'*256
            for off,n in ((0,16),*FIELDS):after_actors[i*256+off:i*256+off+n]=raw[i*256+off:i*256+off+n]
        assert after_actors==raw
        output=[*self.cursors,self.attempts,self.allocated,words(u,PROVIDER+0x214,1)[0],words(u,FLAG,1)[0]]
        for p in [*(CELLS+i*512 for i in range(self.count)),FALLBACK]:output.extend([words(u,p+0x24,1)[0],*words(u,p+0x44,1),*words(u,p+0x4c,2),u.mem_read(p+0x11e,1)[0],u.mem_read(p+0x122,1)[0]])
        for i in range(self.allocated):
            actor=ACTORS+i*256
            for off,n in FIELDS:
                value=int.from_bytes(u.mem_read(actor+off,n),'little')
                if off in (0x48,0x5c) and value:value=1
                if off==0x98:value=int(bool(value))
                output.append(value)
        for role,reg in enumerate(REGS):
            cap=self.capacities[role];output.extend([words(u,reg+16,1)[0],cap,u.mem_read(reg+13,1)[0]]);output.extend(self.slot(p) for p in words(u,BUFFERS+role*0x3000,cap))
            tail=max(capacity,cap)*4;assert bytes(u.mem_read(BUFFERS+role*0x3000+tail,0x3000-tail))==before_buffers[role][tail:]
        output.extend(self.freed);output.extend(self.extra_output());self.last_state=output;self.last_events=self.events
        return [digest(output),digest(self.events)]
