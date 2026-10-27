# SPDX-License-Identifier: GPL-3.0-or-later
"""Unchanged complete Cell recalculation; explicit LAT/passability/neighbor services."""
import hashlib,struct
from original_presentation import PresentationOracle,STACK
from original_foot_lit import words,ret
from verify_map_cell_attributes import verify,RANGES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_ESP
CELL=0x2400000;TYPE=0x2401000;IMAGE=0x2402000;SUB=0x2403000;TYPES=0x2404000
BUFF4=0x2405000;BUFF10=0x2406000;NEIGHBOR=0x2407000;POSITION=0x2408000;RULES=0x2409000
FALLBACK=0xa6f9f8;MAP=0x8324e0
FIELD_MAP={0x38:(0,4),0x11a:(1,1),0xec:(2,4),0x11c:(3,1),0x11b:(4,1),0x11d:(5,1)}
STATE=((0x38,4),(0xec,4),(0x116,2),(0x11a,1),(0x11b,1),(0x11c,1),(0x140,4),(0x11d,1),(0x11e,1),(0x119,1),(0x4c,4))
def digest(b):return hashlib.sha256(b).hexdigest()
def pack(values):return b''.join(struct.pack('<I',v&0xffffffff) for v in values)
class MapCellAttributeOracle(PresentationOracle):
    def __init__(self,exe):
        self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True)
        self.u.mem_map(CELL,0x10000);self.u.hook_add(UC_HOOK_CODE,self.service)
        self.neighbor_calls=self.lat_calls=self.passability_calls=self.selected_stores=0
    def va(self,a):return a
    def service(self,u,a,n,ctx):
        sp=u.reg_read(UC_X86_REG_ESP);ecx=u.reg_read(UC_X86_REG_ECX)
        if a==0x548070:
            assert ecx==MAP;arg=words(u,sp+4,1)[0];q=words(u,arg,1)[0]
            assert self.query<6
            self.events.extend([100,q]);u.mem_write(NEIGHBOR+0x11b,bytes([self.neighbors[self.query]&255]))
            self.query+=1;self.neighbor_calls+=1;ret(u,4,NEIGHBOR);return
        if a in (0x471d10,0x478f40):
            assert ecx==self.cell
            self.events.extend([101 if a==0x471d10 else 102,*[int.from_bytes(u.mem_read(ecx+off,n),'little') for off,n in ((0x38,4),(0xec,4),(0x11c,1),(0x11b,1),(0x11d,1),(0x4c,4))]])
            if a==0x471d10:self.put(ecx+0x38,self.lat_tile);self.lat_calls+=1
            else:self.put(ecx+0x4c,self.passability);self.passability_calls+=1
            ret(u,0,1);return
        if not any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()):raise AssertionError(f'Uninspected Cell recalculation instruction {a:#x}')
    def index(self,p,a,b,count):
        self.put(POSITION,p);self.put(MAP+0xf0,a);self.put(MAP+0xf4,b);self.put(MAP+0x68,count)
        self.checked_call(0x54fab0,[POSITION],MAP,inputs=[(POSITION,4),(MAP,0x100)])
        return [self.u.reg_read(UC_X86_REG_EAX)]
    def run(self,v):
        (pos,tile,land,tube,sub,level,slope,flags,extra,overlay_data,ice,override,fallback,cliff,tube_count,lat_tile,passability,
         present,valid,ramp,tmp_land,height,y,ey,has_extra,*rest)=v
        mapping=rest[:16];self.neighbors=rest[16:];assert len(self.neighbors)==6
        self.events=[];self.query=0;self.lat_tile=lat_tile;self.passability=passability
        c=FALLBACK if fallback else CELL;self.cell=c
        self.u.mem_write(c,b'\xa5'*0x148);self.put(c+0x24,pos);self.put(c+0x44,-1)
        initial=[tile,land,tube,sub,level,slope,flags,extra,overlay_data,ice,passability^0x13572468]
        for (off,n),value in zip(STATE,initial):self.u.mem_write(c+off,(value&((1<<(8*n))-1)).to_bytes(n,'little'))
        self.u.mem_write(TYPE,bytes(0x500));self.put(TYPE,0x7a51a8);self.put(TYPE+0xa4,IMAGE if present else 0)
        self.put(TYPE+0x298,-1);self.u.mem_write(IMAGE,struct.pack('<4I',1,1,60,height&0xffffffff));self.put(IMAGE+16,SUB if valid else 0)
        self.u.mem_write(SUB,bytes(64));self.put(SUB+4,y);self.put(SUB+0x18,ey);self.put(SUB+0x24,has_extra)
        self.u.mem_write(SUB+0x29,bytes([tmp_land&255,ramp&255]))
        self.u.mem_write(TYPES,pack([TYPE]*3));self.put(0xa40cd4,TYPES);self.put(0xa40ce0,3)
        self.u.mem_write(0x7de4ec,pack(mapping));self.put(0x8661d8,tube_count);self.put(0x839848,RULES)
        self.u.mem_write(RULES,bytes(0x600));self.u.mem_write(RULES+0x584,bytes([cliff&255]))
        self.u.mem_write(NEIGHBOR,b'\xa5'*0x148)
        self.put(MAP+0xf0,4);self.put(MAP+0xf4,5);self.put(MAP+0x68,17)
        self.put(MAP+0x64,BUFF4);self.put(MAP+0x6c,BUFF10)
        self.u.mem_write(BUFF4,b'\xa5'*(17*4));self.u.mem_write(BUFF10,b'\xa5'*(17*10))
        self.put(POSITION,pos);self.checked_call(0x54fab0,[POSITION],MAP,inputs=[(POSITION,4),(MAP,0x100)])
        index=self.u.reg_read(UC_X86_REG_EAX);b4=BUFF4+index*4;b10=BUFF10+index*10
        before=bytes(self.u.mem_read(c,0x148));buffers=[bytes(self.u.mem_read(p,n)) for p,n in ((BUFF4,68),(BUFF10,170))]
        def stores(u,access,p,n,value,ctx):
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
        inputs=[(TYPE,0x500),(IMAGE,20),(SUB,64),(TYPES,12),(0x7de4ec,64),(RULES,0x600),(MAP,0x100),
                (0xa40cd4,4),(0xa40ce0,4),(0x8661d8,4),(0x839848,4)]
        try:self.checked_call(0x472540,[override],c,writes=[(c,0x148),(b4,4),(b10,10)],inputs=inputs)
        finally:self.u.hook_del(hook)
        after=bytearray(self.u.mem_read(c,0x148))
        for off,n in [*STATE,(0x4c,4)]:after[off:off+n]=before[off:off+n]
        assert bytes(after)==before,'Unmodeled Cell byte changed'
        for (base,total,stride),old in zip(((BUFF4,68,4),(BUFF10,170,10)),buffers):
            after=bytearray(self.u.mem_read(base,total));after[index*stride:(index+1)*stride]=old[index*stride:(index+1)*stride];assert bytes(after)==old,'Buffer capacity tail changed'
        state=pack([int.from_bytes(self.u.mem_read(c+off,n),'little') for off,n in STATE])+bytes(self.u.mem_read(b4,4))+bytes(self.u.mem_read(b10,10))
        return [digest(state),digest(pack(self.events))]
