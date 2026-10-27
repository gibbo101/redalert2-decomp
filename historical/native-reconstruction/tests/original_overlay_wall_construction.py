# SPDX-License-Identifier: GPL-3.0-or-later
"""Unchanged wall constructor/Unlimbo/Mark nested with actual wall-update roots."""
from original_map_wall_update import (MapWallUpdateOracle,CELL,TYPES,REGISTRY,NODES,RULES,KIND,VTABLE,TACTICAL,
    FIELDS,pack,point,packed)
from original_overlay_placement import ACTOR,TYPE,BUFFER,VECTOR_VTABLE,GROW,PROVIDER,FLAG,REGISTRY as OVERLAYS
from original_presentation import STACK,OBJ
from original_foot_lit import words,ret
from original_overlay_type_inputs import digest
from verify_map_wall_update import RANGES as UPDATE
from verify_overlay_wall_construction import verify,RANGES
from unicorn import UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EAX

class OverlayWallConstructionOracle(MapWallUpdateOracle):
    def __init__(self,exe):
        super().__init__(exe);self.inspection=verify(exe.read_bytes())
        self.u.mem_map(ACTOR,0x40000);self.roots={hex(a):0 for a in RANGES}
        self.placements=0
    def actor_id(self,p):
        assert ACTOR<=p<ACTOR+33*256 and (p-ACTOR)%256==0
        return (p-ACTOR)//256+1
    def code(self,u,a,n,ctx):
        sp=u.reg_read(UC_X86_REG_ESP);receiver=u.reg_read(UC_X86_REG_ECX)
        if any(lo<=a and a+n<=lo+size for lo,size in UPDATE.items()):
            return super().code(u,a,n,ctx)
        if any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()):
            if a in RANGES:self.roots[hex(a)]+=1
            if a==0x4718b0:
                self.cell_id(receiver);assert words(u,sp+4,3)==[1,0,0]
                self.events.extend([35,1,0,0]);self.placements+=1
            return
        caller=words(u,sp,1)[0]
        assert any(lo<=caller<lo+size for lo,size in RANGES.items()),hex(caller)
        if a in (0x5d22e0,GROW,0x40dc20,0x4e09a0,0x548070,0x472540,0x5d4e90):
            self.services+=1
            if a==0x5d22e0:
                assert receiver==ACTOR and caller==0x5da7db;self.events.append(30);ret(u,0,ACTOR)
            elif a==GROW:
                capacity,zero=words(u,sp+4,2);assert receiver==OVERLAYS and zero==0 and capacity==self.capacity+self.growth and 0<capacity<=32
                self.events.extend([31,capacity,self.grow_result])
                if self.grow_result&255:
                    for i in range(self.capacity,capacity):self.put(BUFFER+i*4,0)
                    self.capacity=capacity;self.put(OVERLAYS+8,capacity);u.mem_write(OVERLAYS+13,b'\1')
                ret(u,8,self.grow_result)
            elif a==0x40dc20:
                assert receiver==ACTOR;self.events.append(32);ret(u,0,0)
            elif a==0x4e09a0:
                assert receiver==0x8324e0 and words(u,sp+4,1)==[0];self.events.append(33);ret(u,4)
            elif a==0x548070:
                assert receiver==0x8324e0;p=words(u,sp+4,1)[0];assert STACK-0x2000<=p<STACK
                q=words(u,p,1)[0];id=self.query(q);self.events.extend([5,q,id]);ret(u,4,CELL+id*512)
            elif a==0x472540:
                id=self.cell_id(receiver);assert words(u,sp+4,1)==[0xffffffff];self.events.extend([8,id,0xffffffff])
                before=words(u,receiver+0x4c,1)[0];overlay=words(u,receiver+0x44,1)[0]
                value=before if self.recalc==0 else (before^((overlay+1)&7) if self.recalc==1 else (before^1 if self.recalc==2 else int(overlay!=0xffffffff)))
                self.put(receiver+0x4c,value);self.events.extend([12,id,0x4c,4,value]);ret(u,4)
            else:
                assert receiver==ACTOR;self.events.extend([34,40,0x7d,1,0]);u.mem_write(ACTOR+0x7d,b'\0');ret(u,0)
            return
        return super().code(u,a,n,ctx)
    def run(self,op,v):
        (index,slope,enabled,limbo,on_map,redraw,active,p_actor,invalid,flag,incoming,owner,capacity,count,self.growth,owns,self.grow_result)=v[:17]
        v=v[17:];self.seed,skip,p,sx,sy,self.recalc,self.alias,all_walls=v[:8]
        gates=v[8:13];directions=v[18:26];self.count=v[26];data=v[27:]
        assert v[13:18]==self.inspection['visits'] and skip==1
        self.capacity=capacity;self.events=[];u=self.u
        u.mem_write(CELL,b'\xa5'*(16*512));u.mem_write(NODES,b'\xb6'*(16*8*0x500));u.mem_write(TYPES,b'\xc7'*(256*0x300))
        u.mem_write(REGISTRY,pack([TYPE if i==index else TYPES+i*0x300 for i in range(256)]));self.put(0xa35dec,REGISTRY)
        for i in range(256):u.mem_write(TYPES+i*0x300+0x278,bytes([int(all_walls or ((i+self.seed)&0xffffffff)%5!=0)]))
        u.mem_write(RULES,b'\xd8'*0x1000);self.put(0x839848,RULES)
        for off,t in zip((0x77c,0x780,0x78c,0x784,0x788),gates):self.put(RULES+off,t)
        self.put(VTABLE+0x2c,KIND);self.put(0x83996c,TACTICAL);self.put(0x839630,sx);self.put(0x839634,sy);u.mem_write(0x851a70,pack(directions))
        cursor=0;x,y=point(p)
        for i in range(self.count):
            c=CELL+i*512;overlay,amount,neighbors,passability,old_owner,n=data[cursor:cursor+6];cursor+=6
            q=p if i==0 else packed(x+i-4,y+(i*3)%5-2)
            for off,value in ((0x24,q),(0x44,overlay),(0x4c,passability),(0x50,old_owner),(0xe4,NODES+i*8*0x500 if n else 0)):self.put(c+off,value)
            u.mem_write(c+0x11c,bytes([slope^i]));u.mem_write(c+0x11e,bytes([amount]));u.mem_write(c+0x122,bytes([neighbors]))
            for j in range(n):
                kind,health,t=data[cursor:cursor+3];cursor+=3;node=NODES+(i*8+j)*0x500
                for off,value in ((0,VTABLE),(0x30,node+0x500 if j+1<n else 0),(0x64,kind),(0x6c,health),(0x418,t)):self.put(node+off,value)
        assert cursor==len(data)
        u.mem_write(ACTOR,b'\xa5'*0xa0);u.mem_write(TYPE,b'\xb6'*1024);self.put(ACTOR,0x7a77f4);self.put(ACTOR+0x98,TYPE)
        self.put(ACTOR+0x10,self.seed^0xaaaaaaaa);self.put(0xa3d290,PROVIDER if self.seed else 0);self.put(PROVIDER+0x214,self.seed^0xfedcba98)
        u.mem_write(ACTOR+0x88,pack([self.seed,self.seed^0x12345678,self.seed+17]));u.mem_write(ACTOR+0x74,bytes([on_map,redraw,limbo]));u.mem_write(ACTOR+0x7d,bytes([active]))
        self.put(TYPE,0x7a7a08);self.put(TYPE+0x264,index);self.put(TYPE+0x268,0);self.put(TYPE+0x26c,0);u.mem_write(TYPE+0x278,b'\1')
        self.put(OVERLAYS,VECTOR_VTABLE);self.put(VECTOR_VTABLE+8,GROW);self.put(OVERLAYS+4,BUFFER)
        self.put(OVERLAYS+8,capacity);u.mem_write(OVERLAYS+12,bytes([1,owns]));self.put(OVERLAYS+16,count);self.put(OVERLAYS+20,self.growth)
        u.mem_write(BUFFER,b'\xd8'*256)
        for i in range(capacity):self.put(BUFFER+i*4,ACTOR+(i+1)*256)
        self.put(0xa40774,1);u.mem_write(0xa40958,bytes([enabled]));self.put(0xa73088,invalid);self.put(FLAG,flag);self.put(0x833688,owner)
        x,y=point(p_actor);self.put(OBJ,p_actor);u.mem_write(OBJ+4,pack([x*256+128,y*256+128,0]))
        before=bytes(u.mem_read(CELL,16*512));before_actor=bytes(u.mem_read(ACTOR,0xa0));before_buffer=bytes(u.mem_read(BUFFER,256))
        def store(u,access,address,size,value,ctx):
            value&=(1<<(size*8))-1
            if CELL<=address<CELL+16*512:
                id=(address-CELL)//512;off=(address-CELL)%512;assert id<self.count and (off,size) in FIELDS
                self.events.extend([12,id,off,size,value])
            elif ACTOR<=address<ACTOR+0xa0:
                off=address-ACTOR
                if off in (0,4,8,12):
                    assert op=='C' and size==4 and value=={0:0x7a77f4,4:0x7a77d0,8:0x7a77ec,12:0x7a77c8}[off];return
                assert (off,size) in ((0x10,4),(0x98,4),(0x74,1),(0x75,1),(0x76,1),(0x88,4),(0x8c,4),(0x90,4))
                if off==0x98:assert value==TYPE;value=1
                self.events.extend([40,off,size,value])
            elif address==OVERLAYS+16:assert size==4;self.events.extend([42,0,4,value])
            elif BUFFER<=address<BUFFER+256:
                assert size==4 and (address-BUFFER)%4==0;slot=(address-BUFFER)//4;assert slot<self.capacity
                self.events.extend([42,slot+1,4,self.actor_id(value)])
            elif address==FLAG:assert size==4;self.events.extend([43,0,4,value])
            elif address==PROVIDER+0x214:assert size==4;self.events.extend([44,0,4,value])
            else:return
            self.stores+=1
        hook=u.hook_add(UC_HOOK_MEM_WRITE,store)
        try:self.checked_call(0x5da7d0 if op=='C' else 0x5d3890,[TYPE,OBJ,incoming] if op=='C' else [OBJ+4,0],ACTOR,
            writes=[(ACTOR,0xa0),(CELL,16*512),(OVERLAYS,24),(BUFFER,256),(FLAG,4),(PROVIDER+0x214,4)],
            inputs=[(TYPES,256*0x300),(TYPE,1024),(REGISTRY,1024),(NODES,16*8*0x500),(RULES,0x1000),
              (0xa35dec,4),(0x839848,4),(0x83996c,4),(0x839630,8),(0x851a70,32),(VTABLE,0x30),(0x7d2b58,20),
              (0xa40774,4),(0xa3d290,4),(0xa40958,1),(0xa73088,4),(0x833688,4),(OBJ,16),(VECTOR_VTABLE,16)])
        finally:u.hook_del(hook)
        if op=='C':assert u.reg_read(UC_X86_REG_EAX)==ACTOR
        result=1 if op=='C' else u.reg_read(UC_X86_REG_EAX)&255
        after=bytearray(u.mem_read(CELL,16*512));actor_after=bytearray(u.mem_read(ACTOR,0xa0))
        for i in range(self.count):
            for off,size in FIELDS:after[i*512+off:i*512+off+size]=before[i*512+off:i*512+off+size]
        for off,size in ((0,16),(0x10,4),(0x98,4),(0x74,3),(0x7d,1),(0x88,12)):actor_after[off:off+size]=before_actor[off:off+size]
        assert bytes(after)==before and bytes(actor_after)==before_actor
        tail=max(capacity,self.capacity)*4;assert bytes(u.mem_read(BUFFER+tail,256-tail))==before_buffer[tail:]
        output=[result,words(u,ACTOR+0x10,1)[0],words(u,PROVIDER+0x214,1)[0],*words(u,ACTOR+0x88,3),*u.mem_read(ACTOR+0x74,3),u.mem_read(ACTOR+0x7d,1)[0],words(u,FLAG,1)[0],words(u,OVERLAYS+16,1)[0],self.capacity,u.mem_read(OVERLAYS+13,1)[0]]
        output.extend(0 if n==0 else self.actor_id(n) for n in words(u,BUFFER,self.capacity))
        for i in range(self.count):
            c=CELL+i*512;output.extend([words(u,c+0x24,1)[0],words(u,c+0x44,1)[0],words(u,c+0x4c,1)[0],words(u,c+0x50,1)[0],u.mem_read(c+0x11e,1)[0],u.mem_read(c+0x122,1)[0],u.mem_read(c+0x11c,1)[0]])
        return [digest(output),digest(self.events)]
