# SPDX-License-Identifier: GPL-3.0-or-later
"""Unchanged base overlay children; only the missing-resource logger is supplied."""
import hashlib,struct
from original_presentation import PresentationOracle
from original_foot_lit import words,ret
from verify_map_overlay import verify,RANGES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP
CELL=0x2400000;NEIGHBORS=CELL+0x1000;TYPE=CELL+0x3000;TYPES=CELL+0x4000
RESOURCES=CELL+0x5000;RECORDS=CELL+0x6000;IMAGES=CELL+0x7000;POSITION=CELL+0x8000
TABLE=0x2500000;MAP=0x8324e0;FALLBACK=0xa6f9f8
NAME=b'TEST_OVERLAY'+bytes(49-len('TEST_OVERLAY'))
def pack(v):return b''.join(struct.pack('<I',n&0xffffffff) for n in v)
def position(p):return struct.unpack('<hh',pack([p]))
def packed(x,y):return (x&65535)|((y&65535)<<16)
def resources(v,start):
    n=v[start];assert 0<=n<=8
    return [v[i:i+6] for i in range(start+1,start+1+n*6,6)],start+1+n*6
class MapOverlayOracle(PresentationOracle):
    def __init__(self,exe):
        self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True)
        self.u.mem_map(CELL,0x200000);self.u.hook_add(UC_HOOK_CODE,self.code)
        self.roots={};self.stores=0;self.queries=0;self.logs=0
        self.frames=list(self.u.mem_read(0x7d2c10,36))[::4]
    def va(self,a):return a
    def event(self,tag,value):self.events.extend([tag,value&0xffffffff])
    def code(self,u,a,n,ctx):
        ecx=u.reg_read(UC_X86_REG_ECX);sp=u.reg_read(UC_X86_REG_ESP)
        if a==0x4068f0:
            assert words(u,sp+4,1)[0]==0x7e8b60
            assert bytes(u.mem_read(sp+8,49))==NAME
            self.event(2,self.current_overlay);self.logs+=1;ret(u,0,0);return
        if a in RANGES:self.roots[hex(a)]=self.roots.get(hex(a),0)+1
        if a==0x5dc0b0:self.current_overlay=ecx;self.event(1,ecx)
        elif a in (0x476ba0,0x478f40):
            assert ecx==CELL
            if a==0x476ba0:assert words(u,sp+4,1)[0]==0
        elif a==0x55a660:
            assert ecx==MAP and words(u,sp+8,1)[0]==1
            assert words(u,sp+4,1)[0]==CELL+0x24
        elif a==0x55a679:
            self.event(3,self.p);self.queries+=1
        elif a==0x548070:
            assert ecx==MAP;q=words(u,words(u,sp+4,1)[0],1)[0]
            self.event(3,q);self.queries+=1
        if not any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()):
            raise AssertionError(f'Uninspected overlay instruction {a:#x}')
    def run(self,op,v):
        self.events=[];self.p=0
        self.u.mem_write(CELL,b'\xa5'*0x3000);self.put(CELL+0xe4,0)
        self.u.mem_write(TYPE,bytes(0x500));self.u.mem_write(TYPE+0x64,NAME)
        self.u.mem_write(TYPES,pack([TYPE]*64));self.put(0xa35dec,TYPES)
        self.u.mem_write(RECORDS,b'\xa5'*0x1000);self.u.mem_write(IMAGES,b'\xa5'*0x1000)
        self.u.mem_write(RESOURCES,pack([RECORDS+i*0x180 for i in range(8)]));self.put(0xac0b34,RESOURCES)
        self.u.mem_write(FALLBACK,b'\xa5'*0x148);self.put(FALLBACK+0x24,0x12345678);self.put(FALLBACK+0x44,-1)
        self.u.mem_write(FALLBACK+0x11b,bytes([249,3]));table=bytearray(0x100000)
        self.put(MAP+0x138,TABLE)
        def insert(q,address):
            x,y=position(q);index=y*512+x
            if 0<=index<262144:struct.pack_into('<I',table,index*4,address)
        if op=='C':
            overlay,flag=v[:2];rs,end=resources(v,2);assert end==len(v)
            self.u.mem_write(TYPE+0x279,bytes([flag&255]));root=0x5dc0b0;args=[];ecx=overlay
        elif op=='P':
            assert len(v)==30
            self.p,level,slope,land,overlay,overlay_land,*rest=v
            flags=rest[:6];dim,ox,oy,w,h,present=rest[6:12];speeds=rest[12:];assert len(speeds)==12
            self.put(CELL+0x24,self.p);self.put(CELL+0x44,overlay);self.put(CELL+0xec,land)
            self.u.mem_write(CELL+0x11b,bytes([level&255,slope&255]));self.put(TYPE+0x268,overlay_land)
            for off,value in zip((0x1fd,0x278,0x279,0x27c,0x284,0x285),flags):self.u.mem_write(TYPE+off,bytes([value&255]))
            for off,value in zip((0xf0,0xf8,0xfc,0x100,0x104),(dim,ox,oy,w,h)):self.put(MAP+off,value)
            for i,bits in enumerate(speeds):self.put(0x850ea8+i*36,bits)
            if present:insert(self.p,CELL)
            rs=[];root=0x478f40;args=[];ecx=CELL
        else:
            assert op=='R'
            self.p,overlay,flag,initial=v[:4];rs,end=resources(v,4)
            directions=v[end:end+8];overlays=v[end+8:end+16];frames=v[end+16:];assert len(frames)==9 and frames==self.frames
            self.put(CELL+0x24,self.p);self.put(CELL+0x44,overlay);self.u.mem_write(CELL+0x11e,bytes([initial&255]))
            self.u.mem_write(TYPE+0x279,bytes([flag&255]));self.u.mem_write(0x851a70,pack(directions))
            x,y=position(self.p)
            for i,(d,ov) in enumerate(zip(directions,overlays)):
                dx,dy=position(d);q=packed(x+dx,y+dy);address=NEIGHBORS+i*0x180
                self.put(address+0x24,q);self.put(address+0x44,ov);insert(q,address)
            root=0x476ba0;args=[0];ecx=CELL
        assert overlay==-1 or 0<=overlay<64
        self.put(0xac0b40,len(rs))
        for i,(index,image,images,slopes,frames,value) in enumerate(rs):
            r=RECORDS+i*0x180;t=IMAGES+i*0x180
            for off,n in ((0x98,index),(0xb8,value),(0xe0,t),(0xe4,frames),(0xe8,images),(0xec,slopes)):self.put(r+off,n)
            self.put(t+0x264,image)
        self.u.mem_write(TABLE,bytes(table))
        before=bytes(self.u.mem_read(CELL,0x3000));fallback=bytes(self.u.mem_read(FALLBACK,0x148))
        def stores(u,access,p,n,value,ctx):
            if p==FALLBACK+0x24:assert n==4;self.event(4,value)
            elif p==CELL+0x11e:assert n==1 and op=='R';self.event(5,value)
            elif p==CELL+0x4c:assert n==4 and op=='P';self.event(6,value)
            else:return
            self.stores+=1
        inputs=[(TYPE,0x500),(TYPES,256),(RECORDS,0x1000),(IMAGES,0x1000),(RESOURCES,32),(TABLE,0x100000),
                (MAP,0x140),(0xa35dec,4),(0xac0b34,16),(0x7d2c10,36)]
        if op=='P':inputs.append((0x850ea8,432))
        if op=='R':inputs.append((0x851a70,32))
        writes=[(FALLBACK+0x24,4)]
        if op=='P':writes.append((CELL+0x4c,4))
        if op=='R':writes.append((CELL+0x11e,1))
        hook=self.u.hook_add(UC_HOOK_MEM_WRITE,stores)
        try:self.checked_call(root,args,ecx,writes=writes,inputs=inputs)
        finally:self.u.hook_del(hook)
        after=bytearray(self.u.mem_read(CELL,0x3000))
        if op=='P':after[0x4c:0x50]=before[0x4c:0x50]
        if op=='R':after[0x11e]=before[0x11e]
        assert bytes(after)==before,'Unmodeled Cell/neighbor bytes changed'
        after=bytearray(self.u.mem_read(FALLBACK,0x148));after[0x24:0x28]=fallback[0x24:0x28]
        assert bytes(after)==fallback,'Unmodeled fallback bytes changed'
        result=self.u.reg_read(UC_X86_REG_EAX);tail=hashlib.sha256(pack(self.events)).hexdigest()
        if op=='C':return [result,tail]
        f=words(self.u,FALLBACK+0x24,1)[0]
        if op=='P':return [words(self.u,CELL+0x4c,1)[0],f,tail]
        return [result,bytes(self.u.mem_read(CELL+0x11e,1))[0],f,tail]
