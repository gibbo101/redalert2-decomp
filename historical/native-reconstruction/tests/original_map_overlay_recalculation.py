# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete Cell/classifier/passability/permission; supplied LAT and cliff neighbors."""
import hashlib,struct
from original_presentation import PresentationOracle,STACK
from original_foot_lit import words,ret
from verify_map_overlay_recalculation import verify,RANGES
from original_map_overlay import NAME
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP
CELL=0x2400000;TYPE=0x2401000;IMAGE=0x2402000;SUB=0x2403000;TYPES=0x2404000
BUFF4=0x2405000;BUFF10=0x2406000;NEIGHBOR=0x2407000;POSITION=0x2408000;RULES=0x2409000
OVERLAY=0x240a000;OVERLAYS=0x240b000;RESOURCES=0x240c000;RESOURCE=0x240d000;RESOURCE_IMAGE=0x240e000;TABLE=0x2500000
FALLBACK=0xa6f9f8;MAP=0x8324e0
FIELD_MAP={0x38:(0,4),0x11a:(1,1),0xec:(2,4),0x11c:(3,1),0x11b:(4,1),0x11d:(5,1),0x44:(8,4),0x11e:(9,1),0x4c:(10,4)}
STATE=((0x38,4),(0xec,4),(0x116,2),(0x11a,1),(0x11b,1),(0x11c,1),(0x140,4),(0x11d,1),(0x11e,1),(0x119,1),(0x4c,4))
def digest(b):return hashlib.sha256(b).hexdigest()
def pack(values):return b''.join(struct.pack('<I',v&0xffffffff) for v in values)
class MapOverlayRecalculationOracle(PresentationOracle):
    def __init__(self,exe):
        self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True)
        self.u.mem_map(CELL,0x10000);self.u.mem_map(TABLE,0x100000);self.u.hook_add(UC_HOOK_CODE,self.service)
        self.neighbor_calls=self.lat_calls=self.passability_calls=self.selected_stores=0
        self.classifier_calls=self.log_calls=0
    def va(self,a):return a
    def service(self,u,a,n,ctx):
        sp=u.reg_read(UC_X86_REG_ESP);ecx=u.reg_read(UC_X86_REG_ECX)
        if a==0x5dc0b0:
            self.events.extend([103,ecx]);self.classifier_calls+=1
        if a==0x4068f0:
            assert words(u,sp+4,1)[0]==0x7e8b60 and bytes(u.mem_read(sp+8,49))==NAME
            self.events.extend([104,self.overlay]);self.log_calls+=1;ret(u,0,0);return
        if a==0x55a660:
            assert ecx==MAP and words(u,sp+4,1)[0]==self.cell+0x24 and words(u,sp+8,1)[0]==1
        if a==0x55a679:self.events.extend([105,words(u,self.cell+0x24,1)[0]])
        if a==0x548070:
            assert ecx==MAP;arg=words(u,sp+4,1)[0];q=words(u,arg,1)[0]
            assert self.query<6
            self.events.extend([100,q]);u.mem_write(NEIGHBOR+0x11b,bytes([self.neighbors[self.query]&255]))
            self.query+=1;self.neighbor_calls+=1;ret(u,4,NEIGHBOR);return
        if a in (0x471d10,0x478f40):
            assert ecx==self.cell
            self.events.extend([101 if a==0x471d10 else 102,*[int.from_bytes(u.mem_read(ecx+off,n),'little') for off,n in ((0x38,4),(0xec,4),(0x11c,1),(0x11b,1),(0x11d,1),(0x4c,4))]])
            if a==0x471d10:
                self.put(ecx+0x38,self.lat_tile);self.lat_calls+=1;ret(u,0,1);return
            self.passability_calls+=1
        if not any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()):raise AssertionError(f'Uninspected Cell recalculation instruction {a:#x}')
    def index(self,p,a,b,count):
        self.put(POSITION,p);self.put(MAP+0xf0,a);self.put(MAP+0xf4,b);self.put(MAP+0x68,count)
        self.checked_call(0x54fab0,[POSITION],MAP,inputs=[(POSITION,4),(MAP,0x100)])
        return [self.u.reg_read(UC_X86_REG_EAX)]
    def run(self,v,overlay,overlay_land,tiberium,no_use,image_index,num_images,num_slopes,flag1fd,wall,rubble,rock,dimension,ox,oy,width,permission_height,cell_present,*speeds):
        (pos,tile,land,tube,sub,level,slope,flags,extra,overlay_data,ice,override,fallback,cliff,tube_count,lat_tile,passability,
         present,valid,ramp,tmp_land,height,y,ey,has_extra,*rest)=v
        mapping=rest[:16];self.neighbors=rest[16:];assert len(self.neighbors)==6
        self.events=[];self.query=0;self.lat_tile=lat_tile;self.passability=passability
        c=FALLBACK if fallback else CELL;self.cell=c
        self.u.mem_write(c,b'\xa5'*0x148);self.put(c+0x24,pos);self.put(c+0x44,overlay);self.put(c+0xe4,0);self.overlay=overlay
        initial=[tile,land,tube,sub,level,slope,flags,extra,overlay_data,ice,passability^0x13572468]
        for (off,n),value in zip(STATE,initial):self.u.mem_write(c+off,(value&((1<<(8*n))-1)).to_bytes(n,'little'))
        self.u.mem_write(OVERLAY,bytes(0x500));self.u.mem_write(OVERLAY+0x64,NAME);self.put(OVERLAY+0x268,overlay_land)
        self.u.mem_write(OVERLAY+0x279,bytes([tiberium&255]));self.u.mem_write(OVERLAY+0x27c,bytes([no_use&255]))
        for off,value in zip((0x1fd,0x278,0x284,0x285),(flag1fd,wall,rubble,rock)):self.u.mem_write(OVERLAY+off,bytes([value&255]))
        assert len(speeds)==12
        for i,bits in enumerate(speeds):self.put(0x850ea8+i*36,bits)
        if c!=FALLBACK:
            self.u.mem_write(FALLBACK,b'\xa5'*0x148);self.put(FALLBACK+0x24,0x12345678);self.u.mem_write(FALLBACK+0x11b,bytes([249,3]))
        table=bytearray(0x100000);cell_x,cell_y=struct.unpack('<hh',pack([pos]));slot=cell_y*512+cell_x
        if cell_present and 0<=slot<262144:struct.pack_into('<I',table,slot*4,c)
        self.u.mem_write(TABLE,bytes(table));self.put(MAP+0x138,TABLE)
        for off,value in zip((0xf8,0xfc,0x100,0x104),(ox,oy,width,permission_height)):self.put(MAP+off,value)
        self.u.mem_write(OVERLAYS,pack([OVERLAY]*64));self.put(0xa35dec,OVERLAYS)
        self.put(0xac0b34,RESOURCES);self.put(0xac0b40,1);self.put(RESOURCES,RESOURCE)
        self.u.mem_write(RESOURCE,bytes(0x100));self.put(RESOURCE+0x98,0);self.put(RESOURCE+0xe0,RESOURCE_IMAGE)
        self.put(RESOURCE+0xe8,num_images);self.put(RESOURCE+0xec,num_slopes);self.put(RESOURCE_IMAGE+0x264,image_index)
        self.u.mem_write(TYPE,bytes(0x500));self.put(TYPE,0x7a51a8);self.put(TYPE+0xa4,IMAGE if present else 0)
        self.put(TYPE+0x298,-1);self.u.mem_write(IMAGE,struct.pack('<4I',1,1,60,height&0xffffffff));self.put(IMAGE+16,SUB if valid else 0)
        self.u.mem_write(SUB,bytes(64));self.put(SUB+4,y);self.put(SUB+0x18,ey);self.put(SUB+0x24,has_extra)
        self.u.mem_write(SUB+0x29,bytes([tmp_land&255,ramp&255]))
        self.u.mem_write(TYPES,pack([TYPE]*3));self.put(0xa40cd4,TYPES);self.put(0xa40ce0,3)
        self.u.mem_write(0x7de4ec,pack(mapping));self.put(0x8661d8,tube_count);self.put(0x839848,RULES)
        self.u.mem_write(RULES,bytes(0x600));self.u.mem_write(RULES+0x584,bytes([cliff&255]))
        self.u.mem_write(NEIGHBOR,b'\xa5'*0x148)
        self.put(MAP+0xf0,dimension);self.put(MAP+0xf4,5);self.put(MAP+0x68,17)
        self.put(MAP+0x64,BUFF4);self.put(MAP+0x6c,BUFF10)
        self.u.mem_write(BUFF4,b'\xa5'*(17*4));self.u.mem_write(BUFF10,b'\xa5'*(17*10))
        self.put(POSITION,pos);self.checked_call(0x54fab0,[POSITION],MAP,inputs=[(POSITION,4),(MAP,0x100)])
        index=self.u.reg_read(UC_X86_REG_EAX);b4=BUFF4+index*4;b10=BUFF10+index*10
        fallback_before=bytes(self.u.mem_read(FALLBACK,0x148))
        before=bytes(self.u.mem_read(c,0x148));buffers=[bytes(self.u.mem_read(p,n)) for p,n in ((BUFF4,68),(BUFF10,170))]
        def stores(u,access,p,n,value,ctx):
            if p==FALLBACK+0x24 and c!=FALLBACK:
                assert n==4;self.events.extend([106,value&0xffffffff]);self.selected_stores+=1;return
            if c<=p<c+0x148:
                assert p-c in FIELD_MAP and FIELD_MAP[p-c][1]==n,(hex(p),n)
                self.events.extend([FIELD_MAP[p-c][0],value&((1<<(8*n))-1)])
            elif b4<=p<b4+4:
                assert n==1 and p-b4 in (0,1);self.events.extend([6,((p-b4)<<8)|(value&255)])
            elif b10<=p<b10+10:
                assert n==1 and p-b10==8;self.events.extend([7,0x800|(value&255)])
            else:return
            self.selected_stores+=1
        hook=self.u.hook_add(UC_HOOK_MEM_WRITE,stores)
        inputs=[(TABLE,0x100000),(0x850ea8,432),(OVERLAY,0x500),(OVERLAYS,256),(0xa35dec,4),(0xac0b34,16),(RESOURCES,4),(RESOURCE,0x100),(RESOURCE_IMAGE,0x300),(TYPE,0x500),(IMAGE,20),(SUB,64),(TYPES,12),(0x7de4ec,64),(RULES,0x600),(MAP,0x140),
                (0xa40cd4,4),(0xa40ce0,4),(0x8661d8,4),(0x839848,4)]
        try:self.checked_call(0x472540,[override],c,writes=[(c,0x148),(b4,4),(b10,10),(FALLBACK+0x24,4)],inputs=inputs)
        finally:self.u.hook_del(hook)
        after=bytearray(self.u.mem_read(c,0x148))
        for off,n in [*STATE,(0x4c,4),(0x44,4)]:after[off:off+n]=before[off:off+n]
        assert bytes(after)==before,'Unmodeled Cell byte changed'
        if c!=FALLBACK:
            other=bytearray(self.u.mem_read(FALLBACK,0x148));other[0x24:0x28]=fallback_before[0x24:0x28]
            assert bytes(other)==fallback_before,'Unmodeled fallback byte changed'
        for (base,total,stride),old in zip(((BUFF4,68,4),(BUFF10,170,10)),buffers):
            after=bytearray(self.u.mem_read(base,total));after[index*stride:(index+1)*stride]=old[index*stride:(index+1)*stride];assert bytes(after)==old,'Buffer capacity tail changed'
        state=pack([int.from_bytes(self.u.mem_read(c+off,n),'little') for off,n in (*STATE,(0x44,4))])+bytes(self.u.mem_read(b4,4))+bytes(self.u.mem_read(b10,10))
        return [digest(state),digest(pack(self.events))]
