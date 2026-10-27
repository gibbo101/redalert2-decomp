# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete original tile usage/load sweep with actual iterator and children."""
import struct,hashlib
from original_presentation import PresentationOracle,STACK,ARG,STOP
from original_foot_lit import words,ret
from original_tile_image import PACKING_GLOBALS
from original_tile_variants import RNG,CACHE,FLAG,digest
from verify_tile_sweep import verify,RANGES
from unicorn import UC_HOOK_BLOCK,UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_ESP,UC_X86_REG_ECX,UC_X86_REG_EBP
MAP=0x8324e0;TYPES=0x2400000;CELLS=0x2600000;SLOTS=0x3000000;PRIMARY=0x3100000
IMAGES=0x3200000;COLORS=0x3a00000;VECTORS=0x4200000;VTABLE=ARG+0x1000;CLEAR=ARG+0x2000
class TileSweepOracle(PresentationOracle):
    def __init__(self,exe):
        self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True)
        self.u.mem_map(TYPES,0x2200000);self.entries={hex(p):0 for p in RANGES};self.stores=0;self.service_calls=0
        self.services={0x69a430,0x481fb0,0x4068f0,0x468f50,0x469150,0x469060,0x782017,0x781d3b,0x438410,0x42f350,CLEAR}
        self.u.hook_add(UC_HOOK_BLOCK,self.block)
        for p in self.services:self.u.hook_add(UC_HOOK_CODE,self.service,begin=p,end=p)
        for p in RANGES:self.u.hook_add(UC_HOOK_CODE,self.entry,begin=p,end=p)
    def va(self,a):return a
    def call(self,a,args=(),ecx=0,edx=0,budget=40000000):super().call(a,args,ecx,edx,budget)
    def block(self,u,a,n,ctx):
        if a==STOP or a in self.services:return
        if not any(p<=a and a+n<=p+size for p,size in RANGES.items()):raise AssertionError(f'Uninspected sweep block {a:#x}/{n}')
    def entry(self,u,a,n,ctx):
        self.entries[hex(a)]+=1
        if a==0x638840:self.rng_calls+=1
        if a==0x55a490 and self.phase=='sweep':
            p=words(u,MAP+0x114,1)[0];assert SLOTS<=p<SLOTS+0x100000
            cell=words(u,p,1)[0];self.visits.append(self.cell_ids[cell] if cell else -1)
    def put_bytes(self,p,data):self.u.mem_write(p,data)
    def string(self,p):return bytes(self.u.mem_read(p,32)).split(b'\0')[0].decode('ascii')
    def image(self,data):
        p=self.image_cursor;self.image_cursor+=(len(data)+79)&~15;assert self.image_cursor<COLORS
        self.images[p]=data;self.u.mem_write(p,data+b'\xa7'*64);return p
    def relocate(self,p,data):
        cols,rows=struct.unpack_from('<2i',data)
        for i in range(cols*rows):
            ref=struct.unpack_from('<I',data,16+i*4)[0]
            if ref:self.put(p+16+i*4,p+ref)
    def service(self,u,a,n,ctx):
        self.service_calls+=1;sp=u.reg_read(UC_X86_REG_ESP);caller=words(u,sp,1)[0];ecx=u.reg_read(UC_X86_REG_ECX)
        if a==0x69a430:
            assert caller in (0x52b2fa,0x52b40e,0x52b44e,0x52b46a) and STACK-0x100<=ecx<STACK
            self.put(ecx,0);ret(u,0,0)
        elif a==0x481fb0:assert caller==0x52b461;ret(u,0)
        elif a==0x4068f0:
            fmt,loaded,kib=words(u,sp+4,3);assert caller==0x52b552 and fmt==0x7df210
            self.summary=(loaded,u.reg_read(UC_X86_REG_EBP),kib);ret(u,0)
        elif a==0x468f50:
            p=words(u,sp+4,1)[0];assert caller==0x52b578 and STACK-0x100<=ecx<STACK
            node=(p-TYPES-0x2c5)//1024;assert p==TYPES+node*1024+0x2c5 and 0<=node<len(self.nodes)
            name=self.string(p);assert name in self.files;self.requests.append(name);self.file=ecx;self.file_data=self.files[name];self.file_node=node;ret(u,4,ecx)
        elif a==0x469150:assert caller==0x52b581 and ecx==self.file;ret(u,0,len(self.file_data))
        elif a==0x469060:
            p,size=words(u,sp+4,2);assert caller==0x52b5b0 and ecx==self.file and size==len(self.file_data)
            assert p in self.images and self.images[p]==self.file_data and words(u,TYPES+self.file_node*1024+0xa4,1)==[p]
            self.u.mem_write(p,self.file_data);ret(u,8,size)
        elif a==0x782017:
            size=words(u,sp+4,1)[0]
            if caller==0x52b59c:
                assert size==len(self.file_data);p=self.image(self.file_data)
                if self.phase=='sweep':self.loaded_bytes.append(size)
            else:
                assert caller==0x52e44e and size==52;p=self.color_cursor;self.color_cursor+=64;assert self.color_cursor<VECTORS
                self.colors[p]=size;self.u.mem_write(p,b'\xa5'*52+b'\xa7'*12)
            ret(u,0,p)
        elif a==0x781d3b:
            p=words(u,sp+4,1)[0]
            if caller==0x52b4ea:
                owners=[i for i in range(len(self.nodes)) if words(u,TYPES+i*1024+0xa4,1)[0]==p];assert len(owners)==1 and p in self.images
                self.releases.append(owners[0])
            else:assert caller==0x52e401 and p in self.colors and p not in self.freed_colors;self.freed_colors.add(p)
            ret(u,0)
        elif a==CLEAR:
            node=(ecx-TYPES-0x274)//1024;assert caller==0x52e420 and ecx==TYPES+node*1024+0x274 and 0<=node<len(self.nodes)
            self.put(ecx+16,0);ret(u,0)
        elif a==0x438410:assert caller==0x52b62d and ecx==self.file+0x54;ret(u,0)
        elif a==0x42f350:assert caller==0x52b63e and ecx==self.file;ret(u,0)
        else:raise AssertionError(hex(a))
    def run(self,width,force,keep,clear,cursor,primary,nodes,cells,files,initialized,disabled,first,second,table,cache,small,neighbors):
        self.nodes=nodes;self.files=files;self.images={};self.colors={};self.freed_colors=set();self.requests=[];self.releases=[];self.usage=[];self.visits=[];self.loaded_bytes=[]
        self.image_cursor=IMAGES;self.color_cursor=COLORS;self.rng_calls=0;self.phase='prepare';self.summary=None
        self.vector_capacity=max([1,*[struct.unpack_from('<i',b)[0]*struct.unpack_from('<i',b,4)[0] for b in files.values()]])
        self.u.mem_write(TYPES,b'\xa5'*(len(nodes)*1024));self.u.mem_write(CELLS,b'\xa5'*(len(cells)*512))
        self.put(VTABLE+12,CLEAR);self.cell_ids={CELLS+i*512:i for i in range(len(cells))}
        for i,node in enumerate(nodes):
            nxt,variants,usage,lazy,required,owned,name,file_id,resident,prepared=node;p=TYPES+i*1024
            self.put(p,0x7a51a8);self.put(p+0xa4,0);self.u.mem_write(p+0xa8,bytes([owned]));self.put(p+0x28c,TYPES+nxt*1024 if nxt!=-1 else 0)
            self.put(p+0x2c0,variants);self.put(p+0x2d8,usage);self.u.mem_write(p+0x2c4,bytes([lazy]));self.u.mem_write(p+0x2b3,bytes([required]))
            self.u.mem_write(p+0x2c5,name.encode().ljust(14,b'\0'));self.put(p+0x2b4,0);self.put(p+0x2b8,0)
            self.put(p+0x274,VTABLE);self.put(p+0x278,VECTORS+i*(self.vector_capacity*4+64));self.put(p+0x27c,self.vector_capacity);self.put(p+0x284,0);self.put(p+0x288,0)
            self.u.mem_write(VECTORS+i*(self.vector_capacity*4+64),b'\xa7'*(self.vector_capacity*4+64))
            if resident or prepared:
                data=list(files.values())[file_id];image=self.image(data);self.relocate(image,data);self.put(p+0xa4,image)
                if prepared:
                    cols,rows=struct.unpack_from('<2i',data);self.put(p+0x2b4,cols);self.put(p+0x2b8,rows)
                    for a,v in zip(PACKING_GLOBALS,(11,3,0,3,5,2)):self.put(a,v)
                    self.checked_call(0x52e3d0,ecx=p,writes=[(p+0x284,4),(COLORS,VECTORS-COLORS),(VECTORS,0x400000)])
                if not resident:self.put(p+0xa4,0)
        self.u.mem_write(SLOTS,bytes(0x100000))
        for i,(x,y,tile,sub,flags) in enumerate(cells):
            p=CELLS+i*512;self.put(p+0x24,(x&65535)|((y&65535)<<16));self.put(p+0x38,tile);self.u.mem_write(p+0x11a,bytes([sub]));self.put(p+0x140,flags)
            assert 0<=x<512 and 0<=y<512;self.put(SLOTS+(y*512+x)*4,p)
        self.u.mem_write(PRIMARY,struct.pack('<'+'I'*len(primary),*[TYPES+i*1024 if i!=-1 else 0 for i in primary])+b'\xa7'*64)
        self.put(MAP+0xf0,width);self.put(MAP+0x138,SLOTS)
        x,y,remaining,index=cursor
        for off,value in ((0x108,x),(0x10c,y),(0x110,remaining),(0x114,SLOTS+index*4)):self.put(MAP+off,value)
        self.put(0xa40cd4,PRIMARY);self.put(0xa40ce0,len(primary));self.put(0xa52f00,clear)
        self.u.mem_write(RNG,bytes([disabled,0xa5,0xa5,0xa5])+struct.pack('<252I',first,second,*table));self.u.mem_write(FLAG,bytes([initialized]));self.u.mem_write(CACHE,struct.pack('<64I',*cache))
        self.u.mem_write(0x7d2b90,struct.pack('<16i',*small));self.u.mem_write(0x7d2bd0,struct.pack('<16i',*[v for pair in neighbors for v in pair]))
        for a,v in zip(PACKING_GLOBALS,(11,3,0,3,5,2)):self.put(a,v)
        before=bytes(self.u.mem_read(TYPES,len(nodes)*1024));self.phase='sweep'
        def stores(u,access,p,n,v,ctx):
            self.stores+=1
            if TYPES<=p<TYPES+len(nodes)*1024:
                node=(p-TYPES)//1024;off=(p-TYPES)%1024
                assert any(lo<=off and off+n<=lo+size for lo,size in ((0xa4,5),(0x2b4,8),(0x284,4),(0x2d8,4))),f'Unexpected type write {off:#x}'
                if off==0x2d8:self.usage.extend([node,v&0xffffffff])
            elif IMAGES<=p<COLORS:
                assert any(lo+16<=p and p+n<=lo+16+struct.unpack_from('<i',data)[0]*struct.unpack_from('<i',data,4)[0]*4 for lo,data in self.images.items()),'Guest image write outside reference table'
            elif COLORS<=p<VECTORS:assert any(lo<=p and p+n<=lo+size for lo,size in self.colors.items()),'Guest color write outside allocation'
            elif VECTORS<=p<VECTORS+0x400000:
                relative=p-VECTORS;assert relative//(self.vector_capacity*4+64)<len(nodes) and relative%(self.vector_capacity*4+64)+n<=self.vector_capacity*4
        writes=[(MAP+0x108,16),(RNG+4,1008),(CACHE,256),(FLAG,1),(TYPES,len(nodes)*1024),(IMAGES,VECTORS+0x400000-IMAGES)]
        immutable=[(MAP+0xf0,4),(MAP+0x138,4),(CELLS,len(cells)*512),(SLOTS,0x100000),(PRIMARY,len(primary)*4+64),
          (0xa40cd4,4),(0xa40ce0,4),(0xa52f00,4),(RNG,4),(0x7d2b90,128),*[(a,4) for a in PACKING_GLOBALS]]
        hook=self.u.hook_add(UC_HOOK_MEM_WRITE,stores)
        try:self.checked_call(0x52b2e0,ecx=force,edx=keep,writes=writes,inputs=immutable)
        finally:self.u.hook_del(hook)
        assert self.summary is not None
        after=bytearray(self.u.mem_read(TYPES,len(nodes)*1024));state=[]
        for i,node in enumerate(nodes):
            p=TYPES+i*1024;image=words(self.u,p+0xa4,1)[0];count=words(self.u,p+0x284,1)[0];ptr=words(self.u,p+0x278,1)[0]
            assert not image or image in self.images;assert count<=self.vector_capacity and ptr==VECTORS+i*(self.vector_capacity*4+64)
            state.extend([words(self.u,p+0x2d8,1)[0],self.u.mem_read(p+0xa8,1)[0],int(bool(image)),*words(self.u,p+0x2b4,2),count])
            if image:state.extend(struct.unpack('<8I',hashlib.sha256(self.images[image]).digest()))
            for c in words(self.u,ptr,count):
                state.append(int(bool(c)))
                if c:assert c in self.colors and c not in self.freed_colors;state.extend(struct.unpack('<26H',self.u.mem_read(c,52)))
            assert bytes(self.u.mem_read(ptr+count*4,(self.vector_capacity-count)*4+64))==b'\xa7'*((self.vector_capacity-count)*4+64)
            for off,n in ((0xa4,5),(0x2b4,8),(0x284,4),(0x2d8,4)):after[i*1024+off:i*1024+off+n]=before[i*1024+off:i*1024+off+n]
        assert bytes(after)==before
        for p,data in self.images.items():
            normalized=bytearray(self.u.mem_read(p,len(data)));cols,rows=struct.unpack_from('<2i',data)
            for i in range(cols*rows):
                ref=struct.unpack_from('<I',normalized,16+i*4)[0]
                if ref>=p:struct.pack_into('<I',normalized,16+i*4,ref-p)
            assert bytes(normalized)==data and bytes(self.u.mem_read(p+len(data),64))==b'\xa7'*64
        for p in self.colors:assert bytes(self.u.mem_read(p+52,12))==b'\xa7'*12
        cursor=words(self.u,MAP+0x108,4);cursor[-1]=(cursor[-1]-SLOTS)//4
        return [*self.summary,digest(cursor),digest(state),digest(self.visits),digest(self.usage),digest(self.releases),
          hashlib.sha256(b''.join(s.encode()+b'\0' for s in self.requests)).hexdigest(),digest([disabled,*words(self.u,RNG+4,252)]),digest([self.u.mem_read(FLAG,1)[0],*words(self.u,CACHE,64)]),self.rng_calls]
