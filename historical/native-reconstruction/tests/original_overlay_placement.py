# SPDX-License-Identifier: GPL-3.0-or-later
"""Unchanged complete Overlay/Object roots with declared placement services."""
import struct
from original_presentation import PresentationOracle, STACK, OBJ
from original_foot_lit import words, ret
from original_overlay_type_inputs import digest
from verify_overlay_placement import verify, RANGES
from unicorn import UC_HOOK_CODE, UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_ECX, UC_X86_REG_ESP, UC_X86_REG_EAX
ACTOR=0x2300000;TYPE=ACTOR+0x10000;CELL=ACTOR+0x20000
BUFFER=ACTOR+0x30000;VECTOR_VTABLE=BUFFER+0x1000;GROW=BUFFER+0x2000
REGISTRY=0xa40c00;FLAG=0x7e8a8c
PROVIDER=ACTOR+0x35000

class OverlayPlacementOracle(PresentationOracle):
    def __init__(self,exe):
        self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True)
        self.u.mem_map(ACTOR,0x40000);self.u.hook_add(UC_HOOK_CODE,self.code)
        self.roots={hex(a):0 for a in RANGES};self.stores=self.services=0
    def va(self,a):return a
    def actor_id(self,p):
        assert ACTOR<=p<ACTOR+33*256 and (p-ACTOR)%256==0
        return (p-ACTOR)//256+1
    def code(self,u,a,n,ctx):
        if any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()):
            if a in RANGES:self.roots[hex(a)]+=1
            return
        self.services+=1;sp=u.reg_read(UC_X86_REG_ESP);receiver=u.reg_read(UC_X86_REG_ECX)
        caller=words(u,sp,1)[0];assert any(lo<=caller<lo+size for lo,size in RANGES.items()),hex(caller)
        if a==0x5d22e0:
            assert receiver==ACTOR and caller==0x5da7db;self.events.append(0);ret(u,0,ACTOR)
        elif a==GROW:
            capacity,zero=words(u,sp+4,2);assert receiver==REGISTRY and zero==0 and capacity==self.capacity+self.growth and 0<capacity<=64
            self.events.extend([1,capacity,self.grow_result])
            if self.grow_result:
                for i in range(self.capacity,capacity):self.put(BUFFER+i*4,0)
                self.capacity=capacity;self.put(REGISTRY+8,capacity);u.mem_write(REGISTRY+13,b'\1')
            ret(u,8,self.grow_result)
        elif a==0x40dc20:
            assert receiver==ACTOR;self.events.append(2);ret(u,0,0)
        elif a==0x4e09a0:
            assert receiver==0x8324e0 and words(u,sp+4,1)==[0];self.events.append(3);ret(u,4)
        elif a==0x548070:
            assert receiver==0x8324e0
            pointer=words(u,sp+4,1)[0];assert STACK-0x2000<=pointer<STACK
            p=words(u,pointer,1)[0];self.events.extend([4,p]);ret(u,4,CELL)
        elif a==0x476ba0:
            assert receiver==CELL and words(u,sp+4,1)==[0]
            self.events.extend([5,21,0x11e,1,self.resource]);u.mem_write(CELL+0x11e,bytes([self.resource]));ret(u,4,0)
        elif a==0x472540:
            assert receiver==CELL and words(u,sp+4,1)==[0xffffffff];self.events.extend([6,0xffffffff]);ret(u,4)
        elif a==0x5d4e90:
            assert receiver==ACTOR;self.events.extend([7,20,0x7d,1,0]);u.mem_write(ACTOR+0x7d,b'\0');ret(u,0)
        else:raise AssertionError(f'Uninspected overlay placement instruction {a:#x}')
    def run(self,op,v):
        (seed,index,land,crate,slope,enabled,limbo,on_map,redraw,active,mode,p,invalid,
         flag,incoming,capacity,count,self.growth,owns,self.grow_result,self.resource)=v
        self.capacity=capacity;self.events=[];u=self.u
        u.mem_write(ACTOR,b'\xa5'*0xa0);u.mem_write(TYPE,b'\xb6'*1024);u.mem_write(CELL,b'\xc7'*512)
        self.put(ACTOR,0x7a77f4);self.put(ACTOR+0x98,TYPE)
        self.put(ACTOR+0x10,seed^0xaaaaaaaa);self.put(0xa3d290,PROVIDER if seed else 0)
        self.put(PROVIDER+0x214,seed^0xfedcba98)
        x,y=struct.unpack('<hh',struct.pack('<I',p));center=[x*256+128,y*256+128,0]
        position=center if op=='M' else [seed,seed^0x12345678,(seed+17)&0xffffffff]
        u.mem_write(ACTOR+0x88,b''.join(struct.pack('<I',n&0xffffffff) for n in position))
        for off,value in ((0x74,on_map),(0x75,redraw),(0x76,limbo),(0x7d,active)):u.mem_write(ACTOR+off,bytes([value]))
        self.put(TYPE,0x7a7a08);self.put(TYPE+0x264,index);self.put(TYPE+0x268,land);self.put(TYPE+0x26c,0)
        u.mem_write(TYPE+0x278,b'\0');u.mem_write(TYPE+0x27a,bytes([crate]))
        self.put(CELL+0x44,seed^0x76543210);u.mem_write(CELL+0x11c,bytes([slope]));u.mem_write(CELL+0x11e,bytes([seed&255]))
        self.put(REGISTRY,VECTOR_VTABLE);self.put(VECTOR_VTABLE+8,GROW);self.put(REGISTRY+4,BUFFER)
        self.put(REGISTRY+8,capacity);u.mem_write(REGISTRY+12,bytes([1,owns]));self.put(REGISTRY+16,count);self.put(REGISTRY+20,self.growth)
        u.mem_write(BUFFER,b'\xd8'*256)
        for i in range(capacity):self.put(BUFFER+i*4,ACTOR+(i+1)*256)
        self.put(0xa40774,1);u.mem_write(0xa40958,bytes([enabled]));self.put(0xa73088,invalid);self.put(FLAG,flag)
        self.put(OBJ,p);u.mem_write(OBJ+4,b''.join(struct.pack('<i',n) for n in center))
        before_actor=bytes(u.mem_read(ACTOR,0xa0));before_cell=bytes(u.mem_read(CELL,512));before_buffer=bytes(u.mem_read(BUFFER,256))
        def store(u,access,address,size,value,ctx):
            value&=(1<<(8*size))-1
            if ACTOR<=address<ACTOR+0xa0:
                off=address-ACTOR
                if off in (0,4,8,12):
                    assert op=='C' and size==4 and value=={0:0x7a77f4,4:0x7a77d0,8:0x7a77ec,12:0x7a77c8}[off]
                    return
                assert (off,size) in ((0x10,4),(0x98,4),(0x74,1),(0x75,1),(0x76,1),(0x88,4),(0x8c,4),(0x90,4))
                if off==0x98:assert value==TYPE;value=1
                self.events.extend([20,off,size,value])
            elif CELL<=address<CELL+512:
                assert (address-CELL,size) in ((0x44,4),(0x11e,1));self.events.extend([21,address-CELL,size,value])
            elif address==REGISTRY+16:
                assert size==4;self.events.extend([22,0,4,value])
            elif BUFFER<=address<BUFFER+256:
                assert size==4 and (address-BUFFER)%4==0
                slot=(address-BUFFER)//4;assert slot<self.capacity
                self.events.extend([22,slot+1,4,self.actor_id(value)])
            elif address==FLAG:
                assert size==4;self.events.extend([23,0,4,value])
            elif address==PROVIDER+0x214:
                assert size==4;self.events.extend([24,0,4,value])
            else:return
            self.stores+=1
        hook=u.hook_add(UC_HOOK_MEM_WRITE,store)
        try:
            root,args=(0x5da7d0,[TYPE,OBJ,incoming]) if op=='C' else ((0x5da970,[mode]) if op=='M' else (0x5d3890,[OBJ+4,0]))
            self.checked_call(root,args,ACTOR,writes=[(ACTOR,0xa0),(CELL,512),(REGISTRY,24),(BUFFER,256),(FLAG,4),(PROVIDER+0x214,4)],
                inputs=[(TYPE,1024),(OBJ,16),(0xa40774,4),(0xa3d290,4),(0xa40958,1),(0xa73088,4),(VECTOR_VTABLE,16)])
        finally:u.hook_del(hook)
        if op=='C':assert u.reg_read(UC_X86_REG_EAX)==ACTOR
        result=1 if op=='C' else u.reg_read(UC_X86_REG_EAX)&255
        actual_actor=bytearray(u.mem_read(ACTOR,0xa0));actual_cell=bytearray(u.mem_read(CELL,512))
        for off,size in ((0,16),(0x10,4),(0x98,4),(0x74,3),(0x7d,1),(0x88,12)):actual_actor[off:off+size]=before_actor[off:off+size]
        for off,size in ((0x44,4),(0x11e,1)):actual_cell[off:off+size]=before_cell[off:off+size]
        assert actual_actor==before_actor and actual_cell==before_cell
        tail=max(capacity,self.capacity)*4;assert bytes(u.mem_read(BUFFER+tail,256-tail))==before_buffer[tail:]
        state=[1,words(u,ACTOR+0x10,1)[0],words(u,PROVIDER+0x214,1)[0],*words(u,ACTOR+0x88,3),*u.mem_read(ACTOR+0x74,3),u.mem_read(ACTOR+0x7d,1)[0],
          words(u,CELL+0x44,1)[0],u.mem_read(CELL+0x11e,1)[0],slope,words(u,FLAG,1)[0],
          words(u,REGISTRY+16,1)[0],self.capacity,u.mem_read(REGISTRY+13,1)[0]]
        state.extend(0 if n==0 else self.actor_id(n) for n in words(u,BUFFER,self.capacity))
        return [str(result),digest(state),digest(self.events)]
