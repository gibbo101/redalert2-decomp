# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete unchanged theater binding with actual loaded-image preparation."""
import hashlib,struct
from original_theater_tile_inputs import TheaterTileInputOracle,ARENA,PRIMARY,ALL_TYPES,SHIFTS,FIELDS,GLOBAL_WRITES
from original_presentation import STACK
from original_foot_lit import words,ret
from original_tile_image import PACKING_GLOBALS
from verify_theater_tile_files import verify,RANGES
from unicorn import UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_ECX,UC_X86_REG_ESP
IMAGES=0x3000000;VECTORS=0x4000000
class TheaterTileFileOracle(TheaterTileInputOracle):
    def __init__(self,exe):
        super().__init__(exe);self.inspection=verify(exe.read_bytes())
        self.u.mem_map(IMAGES,0x1000000);self.u.mem_map(VECTORS,0x800000)
        self.entries={hex(a):0 for a in RANGES};self.service_calls=0
    def service(self,u,a,n,ctx):
        if a not in self.services:
            if not any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()):raise AssertionError(f'Uninspected loaded theater instruction {a:#x}')
            if a in RANGES:self.entries[hex(a)]+=1
            return
        self.service_calls+=1;sp=u.reg_read(UC_X86_REG_ESP);caller=words(u,sp,1)[0];ecx=u.reg_read(UC_X86_REG_ECX)
        if a==0x5956c0:
            assert caller in (0x52ae70,0x52af41)
            name=self.string(ecx);self.image_requests.append(name)
            ret(u,0,self.image_pointers.get(name,0))
        elif a==0x782017:
            size=words(u,sp+4,1)[0];assert size in (8,16,52,0x2dc)
            expected={0x52995b:16,0x529a49:16,0x529a9e:16,0x529af4:16,0x529b4a:16,
              0x52a721:8,0x52aa98:0x2dc,0x52af79:0x2dc,0x52e44e:52}
            assert expected.get(caller)==size,f'Unexpected allocation {caller:#x}/{size}'
            p=self.cursor;self.cursor+=(size+15)&~15;assert self.cursor<PRIMARY
            self.allocations.append((p,size));self.write(p,bytes(size));ret(u,0,p)
        elif a==self.vector_clear:
            if caller in (0x52abe7,0x52b0b0,0x52e420):
                assert (ecx-0x274,0x2dc) in self.allocations
                if ecx not in self.vector_pointers:
                    p=self.vector_cursor;self.vector_cursor+=self.vector_capacity*4+64
                    assert self.vector_cursor<VECTORS+0x800000
                    self.vector_pointers[ecx]=p
                    self.write(ecx+4,struct.pack('<II',p,self.vector_capacity))
                    self.write(p,b'\xa7'*(self.vector_capacity*4+64))
                self.write(ecx+16,bytes(4));ret(u,0)
            else:ret(u,0,ecx)
        elif a==0x50e9a0:
            section,key,default,p,size=words(u,sp+4,5)
            if self.string(key)=='FileName':
                assert caller==0x52a7f4 and size==64
                value=self.prefixes[int(self.string(section)[7:])].encode();self.write(p,value+b'\0');ret(u,20,len(value))
            else:super().service(u,a,n,ctx)
        else:super().service(u,a,n,ctx)
    def write(self,p,data):
        if VECTORS<=p<VECTORS+0x800000:
            assert any(lo<=p and p+len(data)<=lo+self.vector_capacity*4+64 for lo in self.vector_pointers.values())
            self.u.mem_write(p,data)
        else:super().write(p,data)
    def run(self,theater,numbers,sets,prefixes,files):
        self.numbers=numbers;self.sets=sets;self.prefixes=prefixes;self.cursor=ARENA;self.allocations=[];self.requests=[];self.image_requests=[]
        self.vector_pointers={};self.vector_cursor=VECTORS
        self.vector_capacity=max([1,*[struct.unpack_from('<i',b)[0]*struct.unpack_from('<i',b,4)[0] for b in files.values()]])
        self.image_pointers={};self.image_ids={};self.raw_images={};cursor=IMAGES
        for i,(name,data) in enumerate(files.items()):
            self.image_pointers[name]=cursor;self.image_ids[cursor]=i;self.raw_images[cursor]=data
            self.u.mem_write(cursor,data);self.u.mem_write(cursor+len(data),b'\xa7'*64);cursor+=(len(data)+79)&~15
            assert cursor<IMAGES+0x1000000
        capacity=max(1,sum(max(0,r[0]) for r in sets));all_capacity=capacity+len(files)
        self.allowed=[(STACK-0x2000,STACK),(ARENA,PRIMARY),(PRIMARY,PRIMARY+capacity*4),
          (ALL_TYPES,ALL_TYPES+all_capacity*4),(SHIFTS,SHIFTS+len(sets)*4),(0xa52f90,len(sets)*4+0xa52f90),
          (VECTORS,VECTORS+0x800000),*[(p,p+len(b)) for p,b in self.raw_images.items()],*[(p,p+4) for p in GLOBAL_WRITES]]
        self.u.mem_write(ARENA,bytes(0x900000))
        for p in GLOBAL_WRITES:self.put(p,0x13572468)
        for p,value in ((0xa52ed8,0),(0xa40ce0,0),(0xac0cc0,0),(0xa52ecc,SHIFTS),(0xa52ed0,len(sets)),
          (0xa40cd4,PRIMARY),(0xa40cd8,capacity),(0xac0cb4,ALL_TYPES),(0xac0cb8,all_capacity),
          (0xa6e38c,0),(0xa52eb0,0),(0xa52eb4,0),(0xa52eb8,0),(0xa52ebc,0)):self.put(p,value)
        for p,n in ((PRIMARY,capacity*4),(ALL_TYPES,all_capacity*4),(SHIFTS,len(sets)*4),(0xa52f90,len(sets)*4)):
            self.u.mem_write(p,b'\xa7'*(n+64))
        for a,v in zip(PACKING_GLOBALS,(11,3,0,3,5,2)):self.put(a,v)
        def stores(u,access,p,n,v,ctx):
            if ARENA<=p<PRIMARY:assert any(lo<=p and p+n<=lo+size for lo,size in self.allocations),'Guest write outside allocation'
            if VECTORS<=p<VECTORS+0x800000:assert any(lo<=p and p+n<=lo+self.vector_capacity*4 for lo in self.vector_pointers.values()),'Guest vector overflow'
            self.store_count+=1
        hook=self.u.hook_add(UC_HOOK_MEM_WRITE,stores)
        try:self.checked_call(0x529870,ecx=theater,edx=0,writes=[(lo,hi-lo) for lo,hi in self.allowed if lo!=STACK-0x2000],
          inputs=[(0xa52ecc,8),(0xa40cd4,8),(0xac0cb4,8),*[(a,4) for a in PACKING_GLOBALS]])
        finally:self.u.hook_del(hook)
        count=words(self.u,0xa40ce0,1)[0];all_count=words(self.u,0xac0cc0,1)[0]
        assert count==sum(max(0,r[0]) for r in sets);assert count<=all_count<=all_capacity
        primary=words(self.u,PRIMARY,count);all_types=words(self.u,ALL_TYPES,all_count);indices={p:i for i,p in enumerate(all_types)}
        values=[count,all_count,*[indices[p] for p in primary]];payload=bytearray(struct.pack('<'+'I'*len(values),*values))
        for p in all_types:
            assert (p,0x2dc) in self.allocations
            values=[int.from_bytes(self.u.mem_read(p+off,n),'little') for off,n in FIELDS]
            nxt,variants=words(self.u,p+0x28c,1)[0],words(self.u,p+0x2c0,1)[0];image=words(self.u,p+0xa4,1)[0]
            assert not image or image in self.image_ids
            assert bytes(self.u.mem_read(p+0xa8,1))==b'\0' and bytes(self.u.mem_read(p+0x2c4,15))==bytes(15)
            values += [indices[nxt] if nxt else 0xffffffff,variants,self.image_ids[image] if image else 0xffffffff,*words(self.u,p+0x2b4,2)]
            payload.extend(struct.pack('<'+'I'*len(values),*values))
            if image:
                data=self.raw_images[image];cols,rows,w,h=struct.unpack_from('<4I',data);payload.extend(struct.pack('<4I',cols,rows,w,h))
                colors=words(self.u,p+0x278,1)[0];assert colors==self.vector_pointers[p+0x274]
                assert words(self.u,p+0x284,1)==[cols*rows]
                for i in range(cols*rows):
                    ref=words(self.u,image+16+i*4,1)[0];payload.extend(struct.pack('<I',ref-image if ref else 0))
                    color=words(self.u,colors+i*4,1)[0]
                    if ref:assert (color,52) in self.allocations;payload.extend(bytes(self.u.mem_read(color,52)))
                    else:assert color==0
                assert bytes(self.u.mem_read(colors+cols*rows*4,(self.vector_capacity-cols*rows)*4+64))==b'\xa7'*((self.vector_capacity-cols*rows)*4+64)
            record=bytearray(self.u.mem_read(p,0x2dc))
            for lo,hi in ((0,16),(0x64,0x95),(0xa4,0xa9),(0x1ff,0x204),(0x205,0x206),(0x264,0x2dc)):record[lo:hi]=bytes(hi-lo)
            assert not any(record),'Unmodeled type bytes changed'
        for p,data in self.raw_images.items():
            after=bytearray(self.u.mem_read(p,len(data)));cols,rows=struct.unpack_from('<2i',data)
            for i in range(cols*rows):
                ref=struct.unpack_from('<I',after,16+i*4)[0]
                if ref>=p:struct.pack_into('<I',after,16+i*4,ref-p)
            assert bytes(after)==data and bytes(self.u.mem_read(p+len(data),64))==b'\xa7'*64
        for p,n in ((PRIMARY,count*4),(ALL_TYPES,all_count*4),(SHIFTS,words(self.u,0xa52ed8,1)[0]*4),(0xa52f90,len(sets)*4)):
            assert bytes(self.u.mem_read(p+n,64))==b'\xa7'*64,'Capacity tail changed'
        return [count,all_count,hashlib.sha256(payload).hexdigest(),hashlib.sha256(b''.join(s.encode()+b'\0' for s in self.image_requests)).hexdigest()]
