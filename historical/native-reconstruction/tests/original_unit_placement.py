# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete unchanged Techno placement wrapper with actual Facing/type leaves.

Object placement and map/house effects are explicit read-only services. The
post-base-placement coordinates/on-map byte are supplied, not constructed here.
"""
import struct
from original_unit_metadata import UnitMetadataOracle,OBJ,TYPE,INI,SECTION_NAME
from original_presentation import STACK,ARG
from original_foot_lit import words,ints,signed,ret
from original_unit_drawing_state import fields
from verify_unit_placement import verify,COMPLETE,TAILS,BLOCKS
from verify_unit_metadata import COMPLETE as INI_HELPERS
from verify_unit_model_inputs import COMPLETE as STRING_HELPERS
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_EBX,UC_X86_REG_ECX,UC_X86_REG_ESI,UC_X86_REG_EBP,UC_X86_REG_ESP,UC_X86_REG_EIP
UNIT=OBJ+0x8000;HOUSE=OBJ+0xa000;INPUT=OBJ+0xb000;CELL=OBJ+0xc000;RULES=OBJ+0xd000
SCALARS={0x32d:1,0x3ec:4,0x3f0:4,0x190:1,0x378:1,0x373:1,0x400:4,0x1a0:4,0x1a4:4,0x114:4}
SERVICES={0x55a660,0x5d3890,0x6d5c30,0x54a550,0x436680,0x4ed610,0x6fd630,0x707a40,
          0x594c50,0x5d51e0,0x6d3e50,0x6c7420,0x476b20,0x631ba0}
class UnitPlacementOracle(UnitMetadataOracle):
    def __init__(self,exe):
        verify(exe.read_bytes());super().__init__(exe);self.hashes['FireAngle']=self.crc('FireAngle')
        self.mode=None;self.events=[];self.facing_writes=0;self.scalar_writes=0;self.host_writes=0
        self.present_integer_calls=0;self.missing_integer_calls=0
        self.u.hook_add(UC_HOOK_CODE,self.route);self.u.hook_add(UC_HOOK_MEM_WRITE,self.store)
    def event(self,*v):self.events.extend(v)
    def route(self,u,a,n,ctx):
        if self.mode is None:return
        ranges={**COMPLETE,**TAILS,**BLOCKS,**INI_HELPERS,**STRING_HELPERS}
        assert a in SERVICES or any(p<=a<p+n for p,n in ranges.items()),f'Unexpected placement execution {a:#x}'
        sp=u.reg_read(UC_X86_REG_ESP);ecx=u.reg_read(UC_X86_REG_ECX)
        args=lambda n:words(u,sp+4,n)
        if self.mode=='metadata':
            if a==0x50d7f0:
                section,key,default=args(3)
                assert ecx==INI and bytes(u.mem_read(section,5))==b'HTNK\0'
                assert bytes(u.mem_read(key,10))==b'FireAngle\0' and signed(default)==self.default
                if self.present:self.present_integer_calls+=1;ret(u,12,self.value)
                else:self.missing_integer_calls+=1
            return
        if self.mode!='placement':return
        if a in (0x6c12c0,0x70a2d0):
            assert ecx==UNIT;self.event('type' if a==0x6c12c0 else 'kind');return
        if a in (0x4b8b10,0x4b8a30):
            assert ecx in (UNIT+0x2c8,UNIT+0x2e0);return
        if a==0x55a660:
            p,flag=args(2);assert ecx==0x8324e0 and flag==1
            x,y=struct.unpack('<hh',u.mem_read(p,4));self.event('bridge',x,y)
            v=self.bridge_values[self.bridge_calls];self.bridge_calls+=1;ret(u,8,v)
        elif a==0x5d3890:
            p,direction=args(2);assert ecx==UNIT and p==INPUT and signed(direction)==self.direction
            assert ints(u,p,3)==self.requested;self.event('object',*self.requested,self.direction);ret(u,8,self.accept)
        elif a==0x6d5c30:
            assert ecx==UNIT and args(4)==[0]*4;self.event('reset');ret(u,16)
        elif a==0x54a550:
            p,zero,distance,flag=args(4);assert ecx==0x8324e0 and zero==flag==0
            assert ints(u,p,3)==self.position;self.event('map',*self.position,signed(distance));ret(u,16)
        elif a==0x436680:
            assert ecx==0x8322e0 and args(1)==[UNIT];self.event('effect');ret(u,4)
        elif a==0x4ed610:
            assert ecx==HOUSE and args(2)==[UNIT,0];self.event('owner');ret(u,8)
        elif a==0x6fd630:
            assert ecx==UNIT and args(2)==[1,1];self.event('notify414');ret(u,8)
        elif a==0x707a40:
            assert ecx==UNIT;self.event('predicate');ret(u,0,self.predicate)
        elif a==0x594c50:
            assert ecx==UNIT;self.event('notify1d4');ret(u,0)
        elif a==0x5d51e0:
            assert ecx==UNIT;self.event('cell');ret(u,0,CELL if self.has_cell else 0)
        elif a==0x6d3e50:
            assert ecx==UNIT;self.event('value');ret(u,0,self.cell_value)
        elif a==0x6c7420:
            assert ecx==UNIT and signed(args(1)[0])==self.cell_value
            self.event('cellkind',self.cell_value);ret(u,4,self.cell_kind)
        elif a==0x476b20:
            assert ecx==CELL and signed(args(1)[0])==self.cell_kind;self.event('associate',self.cell_kind);ret(u,4)
        elif a==0x631ba0:
            out,p,flag=args(3);assert ecx==0x8324e0 and flag==1 and ints(u,p,3)==self.position
            assert STACK-0x2000<=out and out+8<=STACK;self.event('locate',*self.position)
            u.mem_write(out,struct.pack('<2i',*self.location));self.host_writes+=1;ret(u,12,out)
    def store(self,u,access,p,n,v,ctx):
        if self.mode!='placement' or not UNIT<=p<UNIT+0x600:return
        off=p-UNIT;v&=(1<<(8*n))-1
        if off in SCALARS:
            assert n==SCALARS[off];self.scalar_writes+=1;self.event('w',off,n,signed(v) if n==4 else v)
        else:
            assert any(base<=off and off+n<=base+24 for base in (0x2c8,0x2e0)),f'Unexpected actor write {off:#x}/{n}'
            self.facing_writes+=1
    def metadata(self,default,present,value):
        # Supplied decoded HTNK section exists; FireAngle's key index is empty.
        self.setup(1,key='FireAngle');self.put(TYPE+0x3a0,default)
        self.u.reg_write(UC_X86_REG_ESI,TYPE);self.block(0x6d9d68,10,[(0x3a0,4,8)])
        initial=signed(words(self.u,TYPE+0x3a0,1)[0])
        self.default=default;self.present=present;self.value=value;self.put(TYPE+0x3a0,default)
        for reg,v in ((UC_X86_REG_EBP,TYPE),(UC_X86_REG_ESI,INI),(UC_X86_REG_EBX,SECTION_NAME)):self.u.reg_write(reg,v)
        self.mode='metadata'
        try:self.block(0x6dcfdf,0x1a,[(0x3a0,4,(value if present else default)&0xffffffff)])
        finally:self.mode=None
        return [initial,signed(words(self.u,TYPE+0x3a0,1)[0])]
    def placement(self,v,construct=False):
        (frame,self.direction,fire_angle,self.accept,on_map,b0,b1,self.predicate,effect,self.has_cell,
         divisor,*tail)=v
        self.requested=tail[:3];self.position=tail[3:6]
        (field1f4,field114,field373,field190,field400,field3ec,field3f0,loc0,loc1,
         self.cell_value,self.cell_kind,self.owner_default,*facings)=tail[6:]
        self.location=[loc0,loc1];self.bridge_values=[b0,b1];self.bridge_calls=0
        self.u.mem_write(OBJ,b'\xa7'*0x10000);self.put(0xa40d2c,frame)
        for p,value in ((UNIT,0x7addf8),(UNIT+0x5ac,TYPE),(UNIT+0x1b4,HOUSE),(TYPE+0x3a0,fire_angle),
                        (TYPE+0x540,effect),(UNIT+0x1f4,field1f4),(UNIT+0x114,field114),(UNIT+0x400,field400),
                        (UNIT+0x3ec,field3ec),(UNIT+0x3f0,field3f0),(HOUSE+0x130,self.owner_default),
                        (0x839848,RULES),(RULES+0x1324,divisor)):
            self.put(p,value)
        for off,value in ((0x7d,on_map),(0x373,field373),(0x190,field190)):self.u.mem_write(UNIT+off,bytes([value&255]))
        self.u.mem_write(UNIT+0x88,struct.pack('<3i',*self.position));self.u.mem_write(INPUT,struct.pack('<3i',*self.requested))
        assert len(facings)==10
        for off,f in ((0x2e0,facings[:5]),(0x2c8,facings[5:])):
            for delta,value in zip((0,4,8,16,20),f):
                self.u.mem_write(UNIT+off+delta,struct.pack('<H' if delta in (0,4,20) else '<I',value& (65535 if delta in (0,4,20) else 0xffffffff)))
        if construct:
            assert fire_angle==8 and effect==0
            assert self.metadata(8,False,0)==[8,8]
            self.put(TYPE+0x540,0) # Supplied type-effect field, not a constructor claim.
            self.mode='construct'
            try:
                self.checked_call(0x4b89d0,ecx=UNIT+0x2e0,writes=[(UNIT+0x2e0,24)],inputs=[(0xa40d2c,4)])
                self.checked_call(0x4b89f0,[3],UNIT+0x2c8,writes=[(UNIT+0x2c8,24)],inputs=[(0xa40d2c,4)])
            finally:self.mode=None
            assert fields(self.u,UNIT+0x2e0)==facings[:5] and fields(self.u,UNIT+0x2c8)==facings[5:]
        before=bytes(self.u.mem_read(OBJ,0x10000));self.events=[];self.mode='placement'
        try:self.checked_call(0x6c4610,[INPUT,self.direction],UNIT,
                writes=[(UNIT,0x600)],inputs=[(0x839848,4),(0xa40d2c,4)])
        finally:self.mode=None
        accepted=self.u.reg_read(UC_X86_REG_EAX)&255
        after=bytearray(self.u.mem_read(OBJ,0x10000))
        for off,n in [*SCALARS.items(),(0x2c8,24),(0x2e0,24)]:
            p=UNIT-OBJ+off;after[p:p+n]=before[p:p+n]
        assert bytes(after)==before,'Placement input arena changed'
        state=[accepted,*fields(self.u,UNIT+0x2e0),*fields(self.u,UNIT+0x2c8),
               *[self.u.mem_read(UNIT+off,1)[0] for off in (0x7d,0x32d,0x190,0x373,0x378)],
               *[signed(words(self.u,UNIT+off,1)[0]) for off in (0x3ec,0x3f0,0x400,0x114,0x1a0,0x1a4)]]
        if accepted and (on_map&255):
            # Two actual original type queries and the actual Unit-kind leaf ran.
            assert self.events.count('type')==2 and self.events.count('kind')==1
        samples=[]
        for delta in (0,1,2,3,10):
            self.put(0xa40d2c,signed((frame+delta)&0xffffffff));self.mode='sample'
            try:self.checked_call(0x4b8be0,[ARG],UNIT+0x2c8,writes=[(ARG,4)],inputs=[(UNIT,0x600)])
            finally:self.mode=None
            samples.append(struct.unpack('<H',self.u.mem_read(ARG,2))[0])
        return self.events+['state',*state,'pitch',*samples]
