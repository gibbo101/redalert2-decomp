# SPDX-License-Identifier: GPL-3.0-or-later
"""Execute actual Foot/cache root with original raster/pool/cached pixel children."""
import hashlib,struct
from original_voxel_snapshot import VoxelSnapshotOracle,POOL,SCRATCH
from original_voxel_part_staging import CONVERTER,DEST,SOURCE
from original_voxel_part import ACTOR,VT,MODEL,HVA,TRANSFORMS,STAGE,V2C0,V2C4,PREDICATE,ADJUST
from original_presentation import ARG,STACK
from original_foot_lit import words,ints,ret
from verify_foot_voxel_staging import verify,RANGES
from unicorn import UC_HOOK_MEM_WRITE,UC_HOOK_MEM_READ
from unicorn.x86_const import UC_X86_REG_ESP,UC_X86_REG_ECX
INDEX=0x1604000;TYPE=0x1605000;LOCO=0x1609000;POOL_OBJ=0x839aa0;CAPACITY=0x80000;RASTER=0xae3408
def ranges(value):
    if isinstance(value,dict):
        if 'patched_va' in value and 'bytes' in value and 'instructions' in value:yield (int(value['patched_va'],16),value['bytes'])
        for key,v in value.items():
            if isinstance(key,str) and key.startswith('0x') and isinstance(v,dict) and 'bytes' in v and 'instructions' in v:yield int(key,16),v['bytes']
            yield from ranges(v)
    elif isinstance(value,list):
        for v in value:yield from ranges(v)
class FootVoxelStagingOracle(VoxelSnapshotOracle):
    def __init__(self,exe,assets,palette):
        self.foot_mode=False;self.in_snapshot=False
        super().__init__(exe,assets,palette)
        self.joined_inspection=verify((exe.parents[1]/'disc-allied/game.exe').read_bytes(),exe.read_bytes())
        self.allowed.extend((a,a+n) for a,n in ranges(self.joined_inspection))
        self.joined_calls={};self.snapshot_offsets=[];self.pool_source_reads=0;self.begin()
    def va(self,a):return a if a in (0x4c9880,0x53d4d0,0x6d1d00) or a in RANGES else super().va(a)
    def begin(self):
        self.u.mem_write(INDEX,bytes(32));self.u.mem_write(POOL,bytes([0xa5])*(CAPACITY+32));self.snapshot_offsets=[]
        self.u.mem_write(POOL_OBJ,struct.pack('<3I',POOL,CAPACITY,POOL))
    def service(self,u,a,n,ctx):
        if self.foot_mode:
            if a in (0x782017,0x781d3b):return # Successful guarded allocator/free fixture, handled by RasterOracle.
            if a==0x4f52b0:
                assert u.reg_read(UC_X86_REG_ECX)==0;ret(u,0,0);return
            if a in (0x4c9880,0x53d4d0,0x6d1d00,0x6d24e0,0x69a1d0,0x6d29d0,0x781d46,0x6d9850):
                self.joined_calls[hex(a)]=self.joined_calls.get(hex(a),0)+1
            if a==0x69a1d0:
                assert u.reg_read(UC_X86_REG_ECX)==POOL_OBJ
                cursor=words(u,POOL_OBJ+8,1)[0]-POOL;self.snapshot_offsets.append(cursor);self.in_snapshot=True
            if a==0x6d2030:
                self.in_snapshot=False
            if a in (0x6d20ed,0x6d2104,0x6d211d):raise AssertionError('Unrecovered pool/allocator failure branch entered')
        super().service(u,a,n,ctx)
    def guard_source(self,u,access,p,n,value,ctx):
        if self.in_snapshot and RASTER<=p<RASTER+65536+256:
            assert p+n<=RASTER+65538,'Snapshot encoder read beyond padded original raster'
            self.pool_source_reads+=1
    def draw_joined(self,v):
        seed,part,key,available,disabled,valid,has,frame,brightness,x,y,bx,by,bw,bh,dx,dy,dw,dh,*pose=v
        assert len(pose)==12 and part in range(3)
        self.u.mem_write(ACTOR,bytes(0x3000));self.u.mem_write(VT,bytes(self.u.mem_read(0x7addf8,0x600)))
        self.u.mem_write(TYPE,bytes(0xc00));self.u.mem_write(TYPE+0xb5a,bytes([disabled]))
        self.put(ACTOR,VT);self.put(ACTOR+0x5bb,1);self.put(ACTOR+0x5ac,TYPE);self.put(ACTOR+0x154,-1)
        self.put(ACTOR+0x564,LOCO+4 if has else 0);self.put(LOCO+4,0x7a04cc)
        for off,target in ((0xc0,PREDICATE),(0x3d0,ADJUST),(0x2c0,V2C0),(0x2c4,V2C4)):self.put(VT+off,target)
        self.house=self.predicate=self.adjusted=0;self.c0=-1;self.c4=2
        for p,value in ((MODEL,self.models[part] if valid else 0),(MODEL+4,HVA if valid else 0),(HVA+4,1),(HVA+8,1),(HVA+12,TRANSFORMS),
                        (0x83995c,STAGE),(0xad0604,STAGE),(0xad0608,CONVERTER)):
            self.put(p,value)
        self.u.mem_write(TRANSFORMS,struct.pack('<12f',1,0,0,0,0,1,0,0,0,0,1,0));self.u.mem_write(0x839a70,struct.pack('<12f',1,0,0,0,0,1,0,0,0,0,1,0))
        self.u.mem_write(ARG,struct.pack('<12I',*pose));self.u.mem_write(ARG+0x200,struct.pack('<6i',x,y,bx,by,bw,bh));self.u.mem_write(0xad0490,struct.pack('<4i',dx,dy,dw,dh))
        self.u.mem_write(self.va(0xadc068),self.vpl[784:]);self.put(self.va(0xade070),0);self.put(self.va(0xade074),1);self.put(self.va(0x7e35d0),1)
        self.u.mem_write(RASTER+65536,bytes(2));self.surface(STAGE,256,256,1,DEST);self.surface(SOURCE,256,256,1,RASTER)
        self.put(0x839c6c,0);self.put(0x8315b4,0)
        self.u.mem_write(DEST,bytes((i*37+seed*19)&255 for i in range(65536)))
        angle=words(self.u,self.va(0x785cf0),1)[0]
        self.checked_call(0x70ca10,[angle],writes=[(self.va(0x821d80),12),(self.va(0x821dcc),16)])
        outputs=[(self.va(p),size) for p,size in ((0x7e35d0,4),(0xab84d0,65548),(0xac8710,8),(0xac8838,12),
                 (0xac8848,136),(0xacaa50,20),(0xacae68,65536),(0xae0470,48),(0xae0870,256))]
        entry=words(self.u,INDEX,1)[0];old_cursor=words(self.u,POOL_OBJ+8,1)[0]-POOL
        immutable=[(p,n) for p,n in self.allocations if p!=entry]
        before=dict(self.joined_calls);self.events=[];self.cache_active=self.active=self.foot_mode=True
        heap_guard=self.u.hook_add(UC_HOOK_MEM_WRITE,self.guarded_heap_write);source_guard=self.u.hook_add(UC_HOOK_MEM_READ,self.guard_source)
        try:self.checked_call(0x4c9880,[MODEL,frame,key,INDEX if available else 0,ARG+0x208,ARG+0x200,ARG,brightness,0x2800],ACTOR,
              writes=[*outputs,(DEST,65536),(STAGE+12,4),(SOURCE+12,4),(CONVERTER+0x17c,4),(0xad0490,16),
                      (POOL_OBJ+8,4),(POOL+old_cursor,CAPACITY-old_cursor),(SCRATCH,16384),(INDEX,20),(0x1300000,0x300000)],
              inputs=[(ACTOR,0x3000),(TYPE,0xc00),(LOCO,8),(ARG,48),(ARG+0x200,24),(POOL_OBJ,8),(POOL,old_cursor),*immutable])
        finally:
            self.cache_active=self.active=self.foot_mode=False;self.u.hook_del(heap_guard);self.u.hook_del(source_guard)
        self.check_heap();assert words(self.u,STAGE+12,1)==words(self.u,SOURCE+12,1)==[0]
        assert bytes(self.u.mem_read(POOL+CAPACITY,32))==bytes([0xa5])*32
        count=self.joined_calls.get('0x6d24e0',0)-before.get('0x6d24e0',0);hit=self.joined_calls.get('0x6d29d0',0)-before.get('0x6d29d0',0)
        kind=(3 if key==-1 or not available or disabled else 1) if count else 2 if hit else 0
        raster=hashlib.sha256(bytes(self.u.mem_read(RASTER,65536))).hexdigest() if count else '-'
        data=bytearray(self.u.mem_read(POOL,CAPACITY))
        for off in self.snapshot_offsets:struct.pack_into('<I',data,off+8,words(self.u,POOL+off+8,1)[0]-POOL)
        pointer,n,capacity=words(self.u,INDEX,3);hot=words(self.u,INDEX+16,1)[0]
        keys=[ints(self.u,pointer+i*8,1)[0] for i in range(n)]
        return ['draw',kind,*ints(self.u,0xad0490,4),raster,hashlib.sha256(bytes(self.u.mem_read(DEST,65536))).hexdigest(),
                'pool',words(self.u,POOL_OBJ+8,1)[0]-POOL,hashlib.sha256(data).hexdigest(),
                'state',n,capacity,self.u.mem_read(INDEX+12,1)[0],ints(self.u,hot,1)[0] if hot else 'None',*keys]
