# SPDX-License-Identifier: GPL-3.0-or-later
"""Actual original row encoder/pool/cached part, with bounded supplied storage."""
import hashlib,struct
from original_voxel_part_staging import VoxelPartStagingOracle,CONVERTER,DEST,SOURCE
from original_voxel_part import ACTOR,VT,STAGE,V2C0,V2C4
from original_presentation import ARG
from original_foot_lit import words,ints
from verify_voxel_snapshot import verify,RANGES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_READ
from unicorn.x86_const import UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EAX
POOL=0x1800000;POOL_OBJ=0x1602000;PADDED_SOURCE=0x1880000;SCRATCH=0xabd548
def pixels(seed,mode,w,h):
    if mode==0:b=bytes((i*37+seed*19)%255+1 for i in range(w*h))
    elif mode==1:b=bytes(w*h)
    elif mode==2:b=bytes(0 if i%w<min(w,7) or i%w>=w-3 else (i*13+seed)%255+1 for i in range(w*h))
    elif mode==3:b=bytes(0 if i%257!=256 else 93 for i in range(w*h))
    else:raise ValueError('Unknown snapshot pattern')
    return b+bytes([seed%256,(seed*3)%256])
class VoxelSnapshotOracle(VoxelPartStagingOracle):
    def va(self,a):return a if a in RANGES else super().va(a)
    def __init__(self,exe,assets,palette):
        self.cache_active=False;self.snapshot_active=False
        self.inspection=verify((exe.parents[1]/'disc-allied/game.exe').read_bytes(),exe.read_bytes())
        super().__init__(exe,assets,palette)
        self.cache_counts={};self.source_reads=0;self.max_source_read=0
        inherited=self.inspection['inherited'];self.allowed=[(a,a+n) for a,n in RANGES.items()]
        for key in ('composition','staging','cache'):
            self.allowed.extend((int(r['patched_va'],16),int(r['patched_va'],16)+r['bytes']) for r in inherited[key]['ranges'])
        self.allowed.extend((int(a,16),int(a,16)+r['bytes']) for a,r in inherited['part']['ranges'].items())
        # Supplied read-only actor scalar getters are fixture services.
    def service(self,u,a,n,ctx):
        if self.cache_active:
            if a not in (V2C0,V2C4) and not any(lo<=a and a+n<=hi for lo,hi in self.allowed):raise AssertionError(f'Uninspected cached instruction {a:#x}')
            if a in (0x63d150,0x63d1b0,0x63d260,0x69a1d0,0x6d29d0,0x485d60,0x4350c0,0x4864f0):
                self.cache_counts[hex(a)]=self.cache_counts.get(hex(a),0)+1
            if a==0x485d60:
                assert u.reg_read(UC_X86_REG_ECX)==CONVERTER
                assert words(u,u.reg_read(UC_X86_REG_ESP)+4,1)==[0]
                self.event('select',0)
            if a==0x4350c0:
                assert u.reg_read(UC_X86_REG_ECX)==STAGE
                assert words(u,0x839c6c,1)==words(u,0x8315b4,1)==[0]
        super().service(u,a,n,ctx)
    def padded_read_guard(self,u,access,p,n,value,ctx):
        if PADDED_SOURCE<=p<PADDED_SOURCE+0x20000:
            assert p+n<=PADDED_SOURCE+self.source_size,'Original encoder read beyond supplied padding'
            self.source_reads+=1;self.max_source_read=max(self.max_source_read,p+n-PADDED_SOURCE)
    def row(self,width,source):
        assert len(source)==width+2
        self.source_size=len(source);self.u.mem_write(PADDED_SOURCE,source);self.u.mem_write(DEST,bytes([0xa5])*16384)
        guard=self.u.hook_add(UC_HOOK_MEM_READ,self.padded_read_guard);self.cache_active=True
        try:
            self.checked_call(0x63d1b0,[PADDED_SOURCE,0,width],inputs=[(PADDED_SOURCE,len(source))]);count=self.u.reg_read(UC_X86_REG_EAX)
            self.checked_call(0x63d1b0,[PADDED_SOURCE,DEST,width],writes=[(DEST,16384)],inputs=[(PADDED_SOURCE,len(source))])
            assert self.u.reg_read(UC_X86_REG_EAX)==count
            encoded=bytes(self.u.mem_read(DEST,count));self.u.mem_write(DEST+0x8000,bytes([0xa5])*16384)
            self.checked_call(0x63d260,[DEST,DEST+0x8000],writes=[(DEST+0x8000,16384)],inputs=[(DEST,count)])
            decoded_count=self.u.reg_read(UC_X86_REG_EAX);decoded=bytes(self.u.mem_read(DEST+0x8000,decoded_count))
            assert bytes(self.u.mem_read(DEST+count,16))==bytes([0xa5])*16
            assert bytes(self.u.mem_read(DEST+0x8000+decoded_count,16))==bytes([0xa5])*16
        finally:self.cache_active=False;self.u.hook_del(guard)
        return ['row',count,encoded.hex(),decoded_count,decoded.hex() or '-']
    def snapshot(self,source,w,h,crop,capacity,cursor):
        assert len(source)==w*h+2 and 0<=cursor<=capacity<=65536
        self.surface(SOURCE,w,h,1,PADDED_SOURCE);self.u.mem_write(PADDED_SOURCE,source);self.source_size=len(source)
        self.u.mem_write(POOL,bytes([0xa5])*65568)
        self.u.mem_write(POOL_OBJ,struct.pack('<3I',POOL,capacity,POOL+cursor));self.u.mem_write(ARG+0x400,struct.pack('<6i',*crop))
        guard=self.u.hook_add(UC_HOOK_MEM_READ,self.padded_read_guard);self.cache_active=True
        try:self.checked_call(0x69a1d0,[SOURCE,ARG+0x400],POOL_OBJ,
            writes=[(POOL,capacity),(POOL_OBJ+8,4),(SCRATCH,16384),(SOURCE+12,4)],
            inputs=[(PADDED_SOURCE,len(source)),(POOL_OBJ,8),(SOURCE,12),(SOURCE+16,12),(ARG+0x400,24)])
        finally:self.cache_active=False;self.u.hook_del(guard)
        result=self.u.reg_read(UC_X86_REG_EAX);end=words(self.u,POOL_OBJ+8,1)[0]-POOL
        assert words(self.u,SOURCE+12,1)==[0]
        assert bytes(self.u.mem_read(POOL+capacity,32))==bytes([0xa5])*32
        data=bytearray(self.u.mem_read(POOL,capacity))
        if end>=cursor+12:struct.pack_into('<I',data,cursor+8,words(self.u,POOL+cursor+8,1)[0]-POOL)
        return result,['snapshot',int(bool(result)),end,hashlib.sha256(data).hexdigest()]
    def cached(self,snapshot,v):
        seed,x,y,bx,by,bw,bh,dx,dy,dw,dh,flags,brightness=v
        self.u.mem_write(ACTOR,bytes(0x3000));self.u.mem_write(VT,bytes(self.u.mem_read(0x7addf8,0x600)))
        self.put(ACTOR,VT);self.put(ACTOR+0x5bb,1);self.put(VT+0x2c0,V2C0);self.put(VT+0x2c4,V2C4)
        self.c0=-1;self.c4=2;self.surface(STAGE,256,256,1,DEST)
        self.put(0x83995c,STAGE);self.put(0xad0608,CONVERTER);self.put(0x839c6c,0);self.put(0x8315b4,0)
        initial=bytes((i*37+seed*19)&255 for i in range(65536));self.u.mem_write(DEST,initial)
        self.u.mem_write(ARG+0x500,struct.pack('<6i',x,y,bx,by,bw,bh));self.u.mem_write(0xad0490,struct.pack('<4i',dx,dy,dw,dh))
        self.events=[];self.cache_active=self.active=True
        try:self.checked_call(0x6d29d0,[snapshot,ARG+0x500,ARG+0x508,flags,brightness],ACTOR,
            writes=[(DEST,65536),(STAGE+12,4),(CONVERTER+0x17c,4),(0xad0490,16)],
            inputs=[(POOL,65536),(ACTOR,0x3000),(STAGE,12),(STAGE+16,12),(CONVERTER,0x17c),(ARG+0x500,24),*self.heap_inputs()])
        finally:self.cache_active=self.active=False
        assert words(self.u,STAGE+12,1)==[0];self.check_heap()
        return [*self.events,'draw',*ints(self.u,0xad0490,4),hashlib.sha256(bytes(self.u.mem_read(DEST,65536))).hexdigest()]
