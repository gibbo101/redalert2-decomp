# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete unchanged map reader with decoded-stream/temporary-object services."""
import hashlib,struct
from original_presentation import PresentationOracle,OBJ,STACK
from original_foot_lit import words,ret
from verify_map_overlay_loading import verify,RANGES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EAX
CELLS=0x2400000;TABLE=0x2c00000;TYPES=0x2d00000;SCRATCH=0x2e00000;TEMP=0x2f00000
MAP=0x8324e0;FALLBACK=0xa6f9f8;ROOT=0x5db670
def pack(values):return b''.join(struct.pack('<I',v&0xffffffff) for v in values)
def digest(values):return hashlib.sha256(pack(values)).hexdigest()
def packed(index):return (index%512)|((index//512)<<16)
class MapOverlayLoadingOracle(PresentationOracle):
    def __init__(self,exe):
        self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True)
        self.u.mem_map(CELLS,0x1000000);self.u.hook_add(UC_HOOK_CODE,self.code)
        self.roots={hex(a):0 for a in RANGES};self.stores=self.service_calls=0
    def va(self,a):return a
    def call(self,address,args=(),ecx=0,edx=0,budget=50000000):super().call(address,args,ecx,edx,budget)
    def cell_id(self,p):
        if p==FALLBACK:return 0xffffffff
        assert CELLS<=p<CELLS+self.count*512 and (p-CELLS)%512==0
        return (p-CELLS)//512
    def target(self,index):return CELLS+self.binding[index]*512 if index in self.binding else FALLBACK
    def code(self,u,a,n,ctx):
        # The full parent dominates this measured oracle's instruction count.
        if ROOT<=a and a+n<=ROOT+RANGES[ROOT]:
            if a==ROOT:self.roots[hex(a)]+=1
            return
        if 0x54aab0<=a and a+n<=0x54aaf5:
            if a==0x54aab0:
                self.roots[hex(a)]+=1
                if self.op=='M':self.events.extend([3,words(u,words(u,u.reg_read(UC_X86_REG_ESP)+4,1)[0],1)[0]])
            elif a in (0x54aaeb,0x54aaf2) and self.op=='M':self.events.extend([4,u.reg_read(UC_X86_REG_EAX)&255])
            return
        if 0x5dd150<=a and a+n<=0x5dd25f:
            if a==0x5dd150:
                self.roots[hex(a)]+=1;receiver=u.reg_read(UC_X86_REG_ECX);index=(receiver-TYPES)//1024
                assert receiver==TYPES+index*1024 and 0<=index<len(self.types)
                assert self.types[index][0] or not self.types[index][3]
                self.events.extend([2,index])
            elif a==0x5dd25e:self.events.extend([5,u.reg_read(UC_X86_REG_EAX)&0xffffffff])
            return
        if 0x548070<=a and a+n<=0x5480a8:
            if a==0x548070:
                self.roots[hex(a)]+=1;assert u.reg_read(UC_X86_REG_ECX)==MAP
                self.events.extend([6,words(u,words(u,u.reg_read(UC_X86_REG_ESP)+4,1)[0],1)[0]])
            return
        for lo,size in RANGES.items():
            if lo<=a and a+n<=lo+size:
                if a==lo:
                    self.roots[hex(a)]+=1
                    if a==0x6ecf10:self.events.append(11)
                return
        self.service_calls+=1;sp=u.reg_read(UC_X86_REG_ESP);receiver=u.reg_read(UC_X86_REG_ECX)
        caller=words(u,sp,1)[0];assert ROOT<=caller<ROOT+RANGES[ROOT]
        if a==0x4382c0:
            pointer,size=words(u,sp+4,2);assert STACK-0x2000<=receiver<STACK-12
            if not pointer:
                assert size==512000;pointer=SCRATCH
            else:assert pointer==SCRATCH and size>0
            self.put(receiver,pointer);self.put(receiver+4,size);u.mem_write(receiver+8,b'\0');ret(u,8,receiver)
        elif a==0x774e20:
            assert words(u,sp+4,1)==[0] and STACK-0x2000<=receiver<STACK-16;ret(u,4)
        elif a==0x50d0f0:
            key,output,capacity=words(u,sp+4,3);assert receiver==OBJ and output==SCRATCH
            assert key in (0x7e8b54,0x7e8b44);self.pass_index=int(key==0x7e8b44)
            assert capacity==(512000 if not self.pass_index else 256000)
            result=self.results[self.pass_index];self.events.extend([0,self.pass_index,capacity,result&0xffffffff]);ret(u,12,result&0xffffffff)
        elif a==0x5352d0:
            assert words(u,sp+4,2)==[1,8192] and STACK-0x2000<=receiver<STACK-36
            self.stream=receiver;ret(u,8,receiver)
        elif a==0x69b050:
            assert receiver==self.stream;pointer=words(u,sp+4,1)[0];assert STACK-0x2000<=pointer<STACK-16;ret(u,4)
        elif a==0x535380:
            output,count=words(u,sp+4,2);assert receiver==self.stream and count==1 and STACK-0x2000<=output<STACK
            i=self.cursors[self.pass_index];self.cursors[self.pass_index]+=1;has=i<self.limits[self.pass_index]
            value=(0 if self.data_mode else (self.seed+i*37)&255) if self.pass_index else 255
            value=self.overrides[self.pass_index].get(i,value)
            self.events.extend([1,self.pass_index,i,int(has),value if has else 0])
            if has:u.mem_write(output,bytes([value]))
            ret(u,8,int(has))
        elif a in (0x535340,0x438410,0x69b010):
            assert STACK-0x2000<=receiver<STACK-12
            if a==0x535340:assert receiver==self.stream
            ret(u,0)
        elif a==0x782017:
            assert words(u,sp+4,1)==[0x9c]
            attempt=self.attempts;self.attempts+=1;ok=not self.divisor or attempt%self.divisor!=0
            self.events.extend([8,attempt,int(ok)]);ret(u,0,TEMP if ok else 0)
        elif a==0x5da7d0:
            type_pointer,position,flag=words(u,sp+4,3);assert receiver==TEMP and flag==0xffffffff
            index=(type_pointer-TYPES)//1024;assert type_pointer==TYPES+index*1024 and 0<=index<len(self.types)
            p=words(u,position,1)[0];x,y=struct.unpack('<hh',struct.pack('<I',p));linear=y*512+x
            self.events.extend([9,index,p,flag]);cell=self.target(linear);h=self.cell_id(cell)
            self.put(cell+0x44,index);self.events.extend([10,h,0,index])
            value=(index*13+self.seed)&255;u.mem_write(cell+0x11e,bytes([value]));self.events.extend([10,h,1,value]);ret(u,12,TEMP)
        else:raise AssertionError(f'Uninspected map overlay loading instruction {a:#x}')
    def run(self,op,v):
        self.op=op;self.events=[];self.cursors=[0,0];self.attempts=0
        if op=='B':
            p,w,h=v;self.put(MAP+0xf0,w);self.put(MAP+0xf4,h);self.put(OBJ,p)
            self.checked_call(0x54aab0,[OBJ],MAP,inputs=[(MAP+0xf0,8),(OBJ,4)])
            return [str(self.u.reg_read(UC_X86_REG_EAX)&255)]
        self.seed,version,w,h,filter_crates,r0,r1,l0,l1,self.divisor,self.data_mode,type_count=v[:12];at=12
        self.results=[r0,r1];self.limits=[l0,l1];self.types=[v[i:i+4] for i in range(at,at+type_count*4,4)];at+=type_count*4
        self.u.mem_write(TYPES,bytes(0x40000))
        for i,(image,animation,crate,demand) in enumerate(self.types):
            p=TYPES+i*1024;self.put(p,0x7a7a08);self.put(p+0xa4,image);self.put(p+0x26c,animation)
            u=self.u;u.mem_write(p+0x27a,bytes([crate&255]));u.mem_write(p+0x27f,bytes([demand&255]));self.put(TYPES+0x40000+i*4,p)
        self.put(0xa35dec,TYPES+0x40000)
        self.count=v[at];at+=1;indices=v[at:at+self.count];at+=self.count;self.binding={index:i for i,index in enumerate(indices)}
        table=bytearray(0x100000)
        for i,index in enumerate(indices):
            p=CELLS+i*512;struct.pack_into('<I',table,index*4,p);self.u.mem_write(p,b'\xa5'*512)
            self.put(p+0x24,packed(index));self.put(p+0x44,self.seed+i*2654435761);self.u.mem_write(p+0x11e,bytes([(self.seed+i*37)&255]))
        self.u.mem_write(TABLE,bytes(table));self.put(0x832618,TABLE)
        self.u.mem_write(FALLBACK,b'\xa5'*0x148);self.put(FALLBACK+0x24,0x12345678);self.put(FALLBACK+0x44,self.seed^0x87654321)
        self.u.mem_write(FALLBACK+0x11e,bytes([(self.seed^0xa5)&255]))
        self.overrides=[]
        for _ in range(2):
            count=v[at];at+=1;self.overrides.append({v[i]:v[i+1] for i in range(at,at+count*2,2)});at+=count*2
        assert at==len(v)
        for p,value in ((0xa40d24,version),(MAP+0xf0,w),(MAP+0xf4,h),(0xa3d298,filter_crates),(0xac0ce8,0)):self.put(p,value)
        before=bytes(self.u.mem_read(CELLS,self.count*512));fallback=bytes(self.u.mem_read(FALLBACK,0x148))
        def stores(u,access,p,n,value,ctx):
            value&=(1<<(8*n))-1
            if FALLBACK<=p<FALLBACK+0x148:cell=FALLBACK;off=p-FALLBACK
            elif CELLS<=p<CELLS+self.count*512:cell=CELLS+((p-CELLS)//512)*512;off=(p-CELLS)%512
            else:return
            if off==0x24 and n==4 and cell==FALLBACK:self.events.extend([7,value])
            else:
                assert off==0x11e and n==1;self.events.extend([10,self.cell_id(cell),1,value])
            self.stores+=1
        hook=self.u.hook_add(UC_HOOK_MEM_WRITE,stores)
        try:self.checked_call(ROOT,[],OBJ,writes=[(CELLS,self.count*512),(FALLBACK,0x148)],
            inputs=[(TABLE,0x100000),(TYPES,0x41000),(SCRATCH,512000),(MAP+0xf0,8),(0xa40d24,4),
             (0xa3d298,4),(0xac0ce8,4),(0xa35dec,4),(0x832618,4),(0x7e8b44,16),(0x7e8b54,12)])
        finally:self.u.hook_del(hook)
        after=bytearray(self.u.mem_read(CELLS,self.count*512));other=bytearray(self.u.mem_read(FALLBACK,0x148))
        for i in range(self.count):
            for off,n in ((0x44,4),(0x11e,1)):after[i*512+off:i*512+off+n]=before[i*512+off:i*512+off+n]
        for off,n in ((0x24,4),(0x44,4),(0x11e,1)):other[off:off+n]=fallback[off:off+n]
        assert bytes(after)==before and bytes(other)==fallback
        state=[*self.cursors,self.attempts]
        for p in [*(CELLS+i*512 for i in range(self.count)),FALLBACK]:state.extend([words(self.u,p+0x24,1)[0],words(self.u,p+0x44,1)[0],self.u.mem_read(p+0x11e,1)[0]])
        return [digest(state),digest(self.events)]
