# SPDX-License-Identifier: GPL-3.0-or-later
"""Actual unchanged lazy TMP loader, color preparation and resident consumers."""
import struct,hashlib
from original_presentation import PresentationOracle,STACK,ARG
from original_foot_lit import words,ret
from verify_tile_image import verify,RANGES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_ESP,UC_X86_REG_ECX,UC_X86_REG_EAX
TYPE=0x2400000;IMAGE=TYPE+0x10000;COLORS=TYPE+0x200000;POINTERS=TYPE+0x400000;OLD=TYPE+0x500000
VTABLE=ARG+0x1000;CLEAR=ARG+0x2000
PACKING_GLOBALS=(0x852fb8,0x852fbc,0x852fc0,0x852fc4,0x852fc8,0x852fcc)
class TileImageOracle(PresentationOracle):
    def __init__(self,exe):
        self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True)
        self.u.mem_map(TYPE,0x600000)
        self.services={0x468f50,0x469150,0x469060,0x782017,0x781d3b,0x438410,0x42f350,CLEAR}
        self.u.hook_add(UC_HOOK_CODE,self.code);self.entries={hex(a):0 for a in RANGES};self.stores=0;self.service_calls=0
    def va(self,a):return a
    def service_write(self,p,data):
        assert any(lo<=p and p+len(data)<=lo+n for lo,n in self.allowed),f'Unexpected service write {p:#x}/{len(data)}'
        self.u.mem_write(p,data)
    def code(self,u,a,n,ctx):
        if a in self.services:
            sp=u.reg_read(UC_X86_REG_ESP);caller=words(u,sp,1)[0];ecx=u.reg_read(UC_X86_REG_ECX);self.service_calls+=1
            if a==0x468f50:
                assert caller==0x52b578 and STACK-0x2000<=ecx<STACK
                filename=words(u,sp+4,1)[0];assert filename==TYPE+0x2c5
                assert bytes(u.mem_read(filename,14))==b'TEST.TEM\0'.ljust(14,b'\0')
                self.file=ecx;ret(u,4,ecx)
            elif a==0x469150:
                assert caller==0x52b581 and ecx==self.file;ret(u,0,len(self.data))
            elif a==0x469060:
                p,size=words(u,sp+4,2);assert caller==0x52b5b0 and ecx==self.file and p==IMAGE and size==len(self.data)
                self.service_write(p,self.data);ret(u,8,size)
            elif a==0x782017:
                size=words(u,sp+4,1)[0]
                if caller==0x52b59c:
                    assert size==len(self.data);p=IMAGE;self.allocated_image=True
                else:
                    assert caller==0x52e44e and size==52;p=COLORS+self.color_allocations*64;self.color_allocations+=1
                    assert self.color_allocations<=self.count
                self.allocations.append((p,size));self.service_write(p,b'\xa5'*size);ret(u,0,p)
            elif a==0x781d3b:
                p=words(u,sp+4,1)[0]
                if caller==0x52b593:assert self.old_image and p==OLD
                else:assert caller==0x52e401 and p in [OLD+0x1000+i*64 for i in range(self.old_colors)]
                self.frees.append(p);ret(u,0)
            elif a==CLEAR:
                assert caller==0x52e420 and ecx==TYPE+0x274
                self.service_write(TYPE+0x284,bytes(4));ret(u,0)
            elif a==0x438410:
                assert caller==0x52b62d and ecx==self.file+0x54;ret(u,0)
            elif a==0x42f350:
                assert caller==0x52b63e and ecx==self.file;ret(u,0)
            else:raise AssertionError(hex(a))
            return
        if not any(start<=a and a+n<=start+size for start,size in RANGES.items()):raise AssertionError(f'Uninspected tile image instruction {a:#x}')
        if a in RANGES:self.entries[hex(a)]+=1
    def run(self,op,data,seed,old_image,packing,mapping):
        self.data=data;self.old_image=old_image;self.old_colors=seed%4;self.allocated_image=False
        cols,rows=struct.unpack_from('<2i',data);self.count=cols*rows;assert 0<=self.count<=16384 and len(data)<0x1f0000
        self.color_allocations=0;self.allocations=[];self.frees=[]
        self.u.mem_write(TYPE,b'\xa5'*0x2dc);self.put(TYPE,0x7a51a8)
        self.put(TYPE+0xa4,OLD if old_image else 0);self.u.mem_write(TYPE+0xa8,b'\x00');self.u.mem_write(TYPE+0x2c4,b'\x01')
        self.u.mem_write(TYPE+0x2c5,b'TEST.TEM\0'.ljust(14,b'\0'))
        self.put(TYPE+0x274,VTABLE);self.put(VTABLE+12,CLEAR);self.put(TYPE+0x278,POINTERS)
        self.put(TYPE+0x27c,max(self.count,self.old_colors));self.put(TYPE+0x284,self.old_colors)
        self.put(TYPE+0x288,0);self.u.mem_write(POINTERS,b'\xa7'*(4*max(self.count,self.old_colors)+64))
        for i in range(self.old_colors):self.put(POINTERS+i*4,OLD+0x1000+i*64)
        for a,v in zip(PACKING_GLOBALS,packing):self.put(a,v)
        self.u.mem_write(0x7de4ec,struct.pack('<16I',*[v&0xffffffff for v in mapping]))
        self.u.mem_write(IMAGE+len(data),b'\xa7'*64)
        self.allowed=[(STACK-0x2000,0x2000),(TYPE+0xa4,5),(TYPE+0x2b4,8),(TYPE+0x284,4),
          (IMAGE,len(data)),(COLORS,self.count*64),(POINTERS,self.count*4)]
        immutable=[(TYPE+0x274,16),(TYPE+0x288,4),(VTABLE+12,4),*[(a,4) for a in PACKING_GLOBALS],(0x7de4ec,64)]
        before=bytes(self.u.mem_read(TYPE,0x2dc));pointers_before=bytes(self.u.mem_read(POINTERS,4*max(self.count,self.old_colors)+64))
        def stores(u,access,p,n,v,ctx):
            self.stores+=1
            if COLORS<=p<COLORS+self.count*64:
                assert (p-COLORS)//64<self.color_allocations and (p-COLORS)%64+n<=52,'Color write outside allocation'
        hook=self.u.hook_add(UC_HOOK_MEM_WRITE,stores)
        try:self.checked_call(0x5293d0 if op=='G' else 0x52b560,ecx=TYPE,writes=self.allowed,inputs=immutable)
        finally:self.u.hook_del(hook)
        assert self.allocated_image
        assert self.frees==([OLD] if old_image else [])+[OLD+0x1000+i*64 for i in range(self.old_colors)]
        after=bytearray(self.u.mem_read(TYPE,0x2dc))
        for p,n in self.allowed:
            if TYPE<=p and p+n<=TYPE+0x2dc:after[p-TYPE:p-TYPE+n]=before[p-TYPE:p-TYPE+n]
        assert bytes(after)==before
        assert words(self.u,TYPE+0xa4,1)==[IMAGE] and bytes(self.u.mem_read(TYPE+0xa8,1))==b'\x01'
        count=words(self.u,TYPE+0x284,1)[0];assert count==self.count
        normalized=bytearray(self.u.mem_read(IMAGE,len(data)));refs=[];ramps=[];nonempty=0
        for i in range(self.count):
            p=words(self.u,IMAGE+16+i*4,1)[0];relative=p-IMAGE if p else 0;refs.append(relative)
            struct.pack_into('<I',normalized,16+i*4,relative)
            color=words(self.u,POINTERS+i*4,1)[0]
            if p:
                assert color==COLORS+nonempty*64;nonempty+=1
                ramps.append(bytes(self.u.mem_read(color,52)))
            else:assert color==0;ramps.append(None)
        assert bytes(normalized)==data,'Loader changed non-reference bytes'
        assert bytes(self.u.mem_read(IMAGE+len(data),64))==b'\xa7'*64
        assert bytes(self.u.mem_read(POINTERS+self.count*4,len(pointers_before)-self.count*4))==pointers_before[self.count*4:]
        values=[*words(self.u,TYPE+0x2b4,2),*struct.unpack_from('<4I',data)]
        payload=b''.join(struct.pack('<I',n&0xffffffff) for n in values)
        for ref,ramp in zip(refs,ramps):payload+=struct.pack('<I',ref)+(ramp or b'')
        consumer=[]
        image_before=bytes(self.u.mem_read(IMAGE,len(data)))
        for i,ref in enumerate(refs):
            for root in (0x529300,0x52b6f0):
                self.checked_call(root,[i],TYPE,inputs=[(IMAGE,len(data)),(TYPE,0x2dc),(0x7de4ec,64)])
                consumer.append(self.u.reg_read(UC_X86_REG_EAX))
            self.put(ARG,0x12345678);self.put(ARG+4,0x87654321)
            self.checked_call(0x52b690,[i,ARG,ARG+4],TYPE,writes=[(ARG,8)],inputs=[(IMAGE,len(data)),(TYPE,0x2dc)])
            consumer.extend([self.u.reg_read(UC_X86_REG_EAX)&255,*words(self.u,ARG,2)])
        assert bytes(self.u.mem_read(IMAGE,len(data)))==image_before
        return [self.count,hashlib.sha256(payload).hexdigest(),hashlib.sha256(b''.join(struct.pack('<I',v&0xffffffff) for v in consumer)).hexdigest()]
