# SPDX-License-Identifier: GPL-3.0-or-later
"""Actual complete LAT, empty passability and map permission; supplied records only."""
import hashlib,struct
from original_presentation import PresentationOracle,STACK
from original_foot_lit import words
from verify_map_cell_children import verify,RANGES,LAT_GLOBALS
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP
CELL=0x2400000;NEIGHBORS=CELL+0x1000;TYPE=CELL+0x3000;IMAGE=CELL+0x4000;TYPES=CELL+0x5000;POSITION=CELL+0x7000;TABLE=0x2500000
MAP=0x8324e0;FALLBACK=0xa6f9f8
def pack(v):return b''.join(struct.pack('<I',x&0xffffffff) for x in v)
def position(p):return struct.unpack('<hh',struct.pack('<I',p&0xffffffff))
def packed(x,y):return (x&65535)|((y&65535)<<16)
class MapCellChildOracle(PresentationOracle):
    def __init__(self,exe):
        self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True)
        self.u.mem_map(CELL,0x200000);self.u.hook_add(UC_HOOK_CODE,self.code)
        self.roots={};self.stores=0;self.queries=0
    def va(self,a):return a
    def code(self,u,a,n,ctx):
        if a in RANGES:self.roots[hex(a)]=self.roots.get(hex(a),0)+1
        if a==0x548070:
            sp=u.reg_read(UC_X86_REG_ESP);assert u.reg_read(UC_X86_REG_ECX)==MAP
            p=words(u,words(u,sp+4,1)[0],1)[0];self.events.extend([1,p]);self.queries+=1
        elif a==0x55a660:
            sp=u.reg_read(UC_X86_REG_ESP);assert u.reg_read(UC_X86_REG_ECX)==MAP
            self.permission_position=words(u,words(u,sp+4,1)[0],1)[0]
        elif a==0x55a679:self.events.extend([1,self.permission_position]);self.queries+=1
        if not any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()):raise AssertionError(f'Uninspected map child {a:#x}')
    def run(self,op,v):
        self.events=[];p=v[0];x,y=position(p)
        self.u.mem_write(CELL,b'\xa5'*0x3000);self.put(CELL+0x24,p);self.put(CELL+0x44,-1);self.put(CELL+0xe4,0)
        self.u.mem_write(FALLBACK,b'\xa5'*0x148);self.put(FALLBACK+0x24,0x12345678);self.put(FALLBACK+0x38,777)
        self.u.mem_write(FALLBACK+0x11b,bytes([249,3]));self.put(POSITION,p)
        table=bytearray(0x100000)
        def insert(q,address):
            a,b=position(q);index=b*512+a
            if 0<=index<262144:struct.pack_into('<I',table,index*4,address)
        self.put(MAP+0x138,TABLE)
        self.u.mem_write(TYPE,bytes(0x500));self.put(TYPE,0x7a51a8);self.u.mem_write(TYPES,pack([TYPE]*1024));self.put(0xa40cd4,TYPES)
        if op=='L':
            p,tile,slope,image,*rest=v;settings=rest[:15];directions=rest[15:23];tiles=rest[23:31];slopes=rest[31:];assert len(slopes)==8
            self.put(CELL+0x38,tile);self.u.mem_write(CELL+0x11c,bytes([slope&255]));self.put(TYPE+0xa4,IMAGE if image else 0)
            for address,value in zip(LAT_GLOBALS,settings):self.put(address,value)
            self.u.mem_write(0x851a70,pack(directions));insert(p,CELL)
            for i,(d,t,s) in enumerate(zip(directions,tiles,slopes)):
                dx,dy=position(d);q=packed(x+dx,y+dy);n=NEIGHBORS+i*512
                self.put(n+0x24,q);self.put(n+0x38,t);self.u.mem_write(n+0x11c,bytes([s&255]));insert(q,n)
            root=0x471d10;args=[];ecx=CELL
        else:
            p,level,slope,value,dim,ox,oy,w,h,present,*speeds=v
            self.u.mem_write(CELL+0x11b,bytes([level&255,slope&255]))
            for off,n in ((0xf0,dim),(0xf8,ox),(0xfc,oy),(0x100,w),(0x104,h)):self.put(MAP+off,n)
            if present:insert(p,CELL)
            if op=='P':
                assert len(speeds)==11;self.put(CELL+0xec,value)
                for i,bits in enumerate(speeds):self.put(0x850ea8+i*36,bits)
                root=0x478f40;args=[];ecx=CELL
            else:assert op=='E' and not speeds;root=0x55a660;args=[POSITION,value];ecx=MAP
        self.u.mem_write(TABLE,bytes(table));before=bytes(self.u.mem_read(CELL,0x3000));old_fallback=bytes(self.u.mem_read(FALLBACK,0x148))
        def stores(u,access,address,n,value,ctx):
            if address==FALLBACK+0x24:assert n==4;self.events.extend([2,value&0xffffffff])
            elif address==CELL+0x38:assert n==4 and op=='L';self.events.extend([3,value&0xffffffff])
            elif address==CELL+0x4c:assert n==4 and op=='P';self.events.extend([4,value&0xffffffff])
            else:return
            self.stores+=1
        hook=self.u.hook_add(UC_HOOK_MEM_WRITE,stores)
        inputs=[(TABLE,0x100000),(TYPE,0x500),(TYPES,4096),(MAP,0x140),(POSITION,4)]
        if op=='L':inputs.extend([(a,4) for a in LAT_GLOBALS]);inputs.append((0x851a70,32))
        if op=='P':inputs.append((0x850ea8,396))
        try:self.checked_call(root,args,ecx,writes=[(CELL+0x38,4)] if op=='L' else [(CELL+0x4c,4)] if op=='P' else [],inputs=inputs)
        finally:self.u.hook_del(hook)
        # Fallback lookup writes are original guest stores, separately permitted.
        # checked_call's write list is extended below by the overridden method.
        after=bytearray(self.u.mem_read(CELL,0x3000));off=0x38 if op=='L' else 0x4c
        if op in ('L','P'):after[off:off+4]=before[off:off+4]
        assert bytes(after)==before,'Unmodeled actor/neighbor byte changed'
        f=bytearray(self.u.mem_read(FALLBACK,0x148));f[0x24:0x28]=old_fallback[0x24:0x28];assert bytes(f)==old_fallback
        fallback=words(self.u,FALLBACK+0x24,1)[0];events=hashlib.sha256(pack(self.events)).hexdigest()
        if op=='L':return [self.u.reg_read(UC_X86_REG_EAX)&255,words(self.u,CELL+0x38,1)[0],fallback,events]
        return [words(self.u,CELL+0x4c,1)[0] if op=='P' else self.u.reg_read(UC_X86_REG_EAX)&255,fallback,events]
    def checked_call(self,*args,writes=(),**kwargs):
        return super().checked_call(*args,writes=[*writes,(FALLBACK+0x24,4)],**kwargs)
