# SPDX-License-Identifier: GPL-3.0-or-later
"""Unchanged decoded IsoMap reader and resident TMP helpers, supplied storage."""
import hashlib,struct
from original_presentation import PresentationOracle,STACK
from original_foot_lit import words,ret
from verify_map_cell_inputs import verify,RANGES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EAX
CELLS=0x2400000;TABLE=0x2c00000;TYPE=0x2d00000;IMAGE=TYPE+0x1000;SUBS=TYPE+0x2000;SHIFTS=TYPE+0x3000;SHIFT_TABLE=TYPE+0x4000
FALLBACK=0xa6f9f8
FIELDS=((0x24,4),(0x38,4),(0x116,2),(0xec,4),(0x119,1),(0x11a,1),(0x11b,1),(0x11c,1),(0x140,4))
def initial(seed,i):
    v=((i+1)*2654435761+seed*2246822519)&0xffffffff
    return [v,v^0x12345678,v&65535,v,(v>>16)&255,(v>>8)&255,v>>24,v&255,v]
def projection(u,p):return [int.from_bytes(u.mem_read(p+off,n),'little') for off,n in FIELDS]
def digest_words(values):return hashlib.sha256(b''.join(struct.pack('<I',v&0xffffffff) for v in values)).hexdigest()
class MapCellInputOracle(PresentationOracle):
    def __init__(self,exe):
        self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True)
        self.u.mem_map(CELLS,0xe00000);self.services={0x53efb0,0x69b050,0x53f050,0x53f010}
        self.u.hook_add(UC_HOOK_CODE,self.service);self.read_calls=0;self.store_count=0;self.tile_calls=0
    def va(self,a):return a
    def service(self,u,a,n,ctx):
        if a in self.services:
            sp=u.reg_read(UC_X86_REG_ESP);ecx=u.reg_read(UC_X86_REG_ECX)
            if a==0x53efb0:
                assert words(u,sp+4,2)==[1,8192];self.stream=ecx;ret(u,8,ecx)
            elif a==0x69b050:
                assert ecx==self.stream and words(u,sp+4,1)==[0x1234];ret(u,4)
            elif a==0x53f010:
                assert ecx==self.stream;ret(u,0)
            else:
                out,count=words(u,sp+4,2);assert ecx==self.stream and count in (1,4,7)
                assert self.cursor+count<=len(self.data),'Truncated exploratory original stream'
                assert STACK-0x2000<=out and out+count<=STACK or CELLS<=out and out+count<=CELLS+self.count*512
                chunk=self.data[self.cursor:self.cursor+count]
                u.mem_write(out,chunk)
                # Unicorn API service writes do not invoke the guest write hook.
                if CELLS<=out<CELLS+self.count*512:
                    i=(out-CELLS)//512;field=((out-CELLS)%512,count)
                    assert field in FIELDS
                    self.events.extend([i,FIELDS.index(field),int.from_bytes(chunk,'little')]);self.store_count+=1
                self.cursor+=count;self.read_calls+=1;ret(u,8,count)
            return
        if a==0x52b560:raise AssertionError('Unexpected lazy TMP load')
        if not any(start<=a and a+n<=start+size for start,size in RANGES.items()):raise AssertionError(f'Uninspected map input instruction {a:#x}')
    def prepare(self,seed,count,term,invalid):
        self.count=count;self.events=[]
        self.u.mem_write(FALLBACK,b'\xa5'*0x148)
        for i,p in [(i,CELLS+i*512) for i in range(count)]+[(99999,FALLBACK)]:
            if i!=99999:self.u.mem_write(p,b'\xa5'*512)
            for (off,n),v in zip(FIELDS,initial(seed,i)):self.u.mem_write(p+off,(v&((1<<(8*n))-1)).to_bytes(n,'little'))
        for p,v in ((0xa6f238,term),(0x850bd8,invalid),(0xa3d290,0)):self.put(p,v)
    def run_map(self,op,seed,term,invalid,shifts=(),indices=(),data=b''):
        self.prepare(seed,len(indices),term,invalid);self.data=data;self.cursor=0
        table=bytearray(0x100000)
        for i,index in enumerate(indices):struct.pack_into('<I',table,index*4,CELLS+i*512)
        self.u.mem_write(TABLE,bytes(table));self.put(0x832618,TABLE)
        self.put(0xa52ed8,len(shifts));self.put(0xa52ecc,SHIFT_TABLE)
        for i,(first,delta) in enumerate(shifts):
            self.put(SHIFT_TABLE+i*4,SHIFTS+i*8);self.u.mem_write(SHIFTS+i*8,struct.pack('<II',first&0xffffffff,delta&0xffffffff))
        def stores(u,access,p,n,v,ctx):
            if FALLBACK<=p<FALLBACK+0x148:i=0xffffffff;off=p-FALLBACK
            elif CELLS<=p<CELLS+len(indices)*512:i=(p-CELLS)//512;off=(p-CELLS)%512
            else:return
            if (off,n) in FIELDS:
                self.events.extend([i,FIELDS.index((off,n)),v&((1<<(8*n))-1)]);self.store_count+=1
            elif i!=0xffffffff:raise AssertionError(f'Unmodeled ordinary cell write {p:#x}/{n}')
        hook=self.u.hook_add(UC_HOOK_MEM_WRITE,stores)
        before=bytes(self.u.mem_read(CELLS,len(indices)*512))
        try:self.checked_call(0x470f10 if op=='C' else 0x54e1e0,[] if op=='C' else [0x1234],
              FALLBACK if op=='C' else 0x8324e0,writes=[(CELLS,len(indices)*512),(FALLBACK,0x148)],
              inputs=[(TABLE,0x100000),(SHIFTS,len(shifts)*8),(SHIFT_TABLE,len(shifts)*4),(0xa3d290,4),(0x850bd8,4),(0xa6f238,4)])
        finally:self.u.hook_del(hook)
        # All undeclared record bytes retain their caller-supplied values.
        after=bytearray(self.u.mem_read(CELLS,len(indices)*512))
        for i in range(len(indices)):
            for off,n in FIELDS:after[i*512+off:i*512+off+n]=before[i*512+off:i*512+off+n]
        assert bytes(after)==before
        values=[v for p in [*(CELLS+i*512 for i in range(len(indices))),FALLBACK] for v in projection(self.u,p)]
        return [self.cursor,digest_words(values),digest_words(self.events)]
    def tile(self,v):
        present,cols,rows,w,h,sub,iw,ih,*rest=v;count=cols*rows
        samples=[rest[i*6:i*6+6] for i in range(count)];mapping=rest[count*6:]
        assert len(mapping)==16
        self.u.mem_write(TYPE,bytes(0x5000));self.put(TYPE,0x7a51a8);self.put(TYPE+0xa4,IMAGE if present else 0)
        self.u.mem_write(IMAGE,struct.pack('<4i',cols,rows,w,h))
        for i,(has,land,ramp,extra,y,ey) in enumerate(samples):
            p=SUBS+i*64;self.put(IMAGE+16+i*4,p if has else 0)
            self.u.mem_write(p+0x29,bytes([land&255,ramp&255]));self.put(p+0x24,extra)
            self.put(p+4,y);self.put(p+0x18,ey)
        self.u.mem_write(0x7de4ec,struct.pack('<16I',*[x&0xffffffff for x in mapping]))
        before=bytes(self.u.mem_read(TYPE,0x5000));inputs=[(TYPE,0x5000),(0x7de4ec,64)]
        result=[]
        for root in (0x529300,0x52b6f0):
            self.checked_call(root,[sub],TYPE,inputs=inputs);result.append(self.u.reg_read(UC_X86_REG_EAX)&0xffffffff);self.tile_calls+=1
        self.put(STACK+128,iw);self.put(STACK+132,ih)
        self.checked_call(0x52b690,[sub,STACK+128,STACK+132],TYPE,writes=[(STACK+128,8)],inputs=inputs)
        result.extend([self.u.reg_read(UC_X86_REG_EAX)&255,*words(self.u,STACK+128,2)]);self.tile_calls+=1
        assert bytes(self.u.mem_read(TYPE,0x5000))==before
        return [struct.unpack('<i',struct.pack('<I',x))[0] for x in result]
