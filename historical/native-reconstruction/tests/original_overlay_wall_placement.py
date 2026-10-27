# SPDX-License-Identifier: GPL-3.0-or-later
"""Unchanged complete loaded wall Mark/permission/neighbor roots; declared services."""
import struct
from original_presentation import PresentationOracle,STACK
from original_foot_lit import words,ret
from original_overlay_type_inputs import digest
from original_overlay_placement import ACTOR,TYPE,CELL,FLAG
from verify_overlay_wall_placement import verify,RANGES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EAX
FIELDS=((0x44,4),(0x50,4),(0x11e,1),(0x122,1))
def pack(values):return b''.join(struct.pack('<I',v&0xffffffff) for v in values)
class OverlayWallPlacementOracle(PresentationOracle):
    def __init__(self,exe):
        self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True)
        self.u.mem_map(ACTOR,0x40000);self.u.hook_add(UC_HOOK_CODE,self.code)
        self.roots={hex(a):0 for a in RANGES};self.stores=self.services=0
    def va(self,a):return a
    def cell_id(self,p):
        assert CELL<=p<CELL+9*512 and (p-CELL)%512==0,hex(p)
        return (p-CELL)//512
    def code(self,u,a,n,ctx):
        if any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()):
            if a in RANGES:self.roots[hex(a)]+=1
            if a==0x4718b0:
                assert u.reg_read(UC_X86_REG_ECX)==CELL and words(u,u.reg_read(UC_X86_REG_ESP)+4,3)==[1,0,0]
                self.events.extend([5,1,0,0])
            return
        self.services+=1;sp=u.reg_read(UC_X86_REG_ESP);receiver=u.reg_read(UC_X86_REG_ECX)
        caller=words(u,sp,1)[0];assert any(lo<=caller<lo+size for lo,size in RANGES.items()),hex(caller)
        if a==0x40dc20:
            assert receiver==ACTOR;self.events.append(2);ret(u,0,0)
        elif a==0x4e09a0:
            assert receiver==0x8324e0 and words(u,sp+4,1)==[0];self.events.append(3);ret(u,4)
        elif a==0x548070:
            assert receiver==0x8324e0;pointer=words(u,sp+4,1)[0];assert STACK-0x2000<=pointer<STACK+8
            q=words(u,pointer,1)[0];id=self.aliases[self.lookups-1] if self.lookups else 0
            self.lookups+=1;self.events.extend([4,q,id]);ret(u,4,CELL+id*512)
        elif a==0x475960:
            assert receiver==CELL and words(u,sp+4,1)==[1];self.events.extend([8,1])
            if self.effect&1:
                data=(self.seed>>8)&255;u.mem_write(CELL+0x11e,bytes([data]));self.events.extend([21,0,0x11e,1,data])
            if self.effect&2:
                self.put(CELL+0x44,-1);u.mem_write(CELL+0x122,b'\xff');self.events.extend([21,0,0x44,4,0xffffffff,21,0,0x122,1,255])
            ret(u,4)
        elif a==0x472540:
            assert receiver==CELL and words(u,sp+4,1)==[0xffffffff];self.events.extend([6,0xffffffff]);ret(u,4)
        elif a==0x5d4e90:
            assert receiver==ACTOR;u.mem_write(ACTOR+0x7d,b'\0');self.events.extend([7,20,0x7d,1,0]);ret(u,0)
        else:raise AssertionError(f'Uninspected loaded wall instruction {a:#x}')
    def run(self,v):
        (self.seed,index,slope,wall,limbo,on_map,redraw,active,mode,x,y,p,flag,owner,loading,self.effect)=v[:16]
        directions=v[16:24];self.aliases=v[24:];assert len(self.aliases)==8
        self.events=[];self.lookups=0;u=self.u
        u.mem_write(ACTOR,b'\xa5'*0xa0);u.mem_write(TYPE,b'\xb6'*1024);u.mem_write(CELL,b'\xc7'*(9*512))
        self.put(ACTOR,0x7a77f4);self.put(ACTOR+0x98,TYPE)
        u.mem_write(ACTOR+0x88,pack([x,y,self.seed]));u.mem_write(ACTOR+0x74,bytes([on_map,redraw,limbo]));u.mem_write(ACTOR+0x7d,bytes([active]))
        self.put(TYPE+0x264,index);self.put(TYPE+0x268,0);self.put(TYPE+0x26c,0);u.mem_write(TYPE+0x278,bytes([wall]))
        for i in range(9):
            c=CELL+i*512;self.put(c+0x24,p);self.put(c+0x44,self.seed^(i*0x1234567));self.put(c+0x50,self.seed^(i*0x7654321))
            u.mem_write(c+0x11c,bytes([slope^i if i else slope]));u.mem_write(c+0x11e,bytes([(self.seed+i)&255]));u.mem_write(c+0x122,bytes([(self.seed+i*31)&255]))
        self.put(0xa40774,loading);self.put(FLAG,flag);self.put(0x833688,owner);u.mem_write(0x851a70,pack(directions))
        before=bytes(u.mem_read(CELL,9*512));before_actor=bytes(u.mem_read(ACTOR,0xa0))
        def store(u,access,address,size,value,ctx):
            value&=(1<<(size*8))-1
            if ACTOR<=address<ACTOR+0xa0:
                off=address-ACTOR;assert (off,size) in ((0x74,1),(0x75,1),(0x76,1));self.events.extend([20,off,size,value])
            elif CELL<=address<CELL+9*512:
                id=(address-CELL)//512;off=(address-CELL)%512;assert (off,size) in FIELDS
                self.events.extend([21,id,off,size,value])
            else:return
            self.stores+=1
        hook=u.hook_add(UC_HOOK_MEM_WRITE,store)
        try:self.checked_call(0x5da970,[mode],ACTOR,writes=[(ACTOR,0xa0),(CELL,9*512)],
            inputs=[(TYPE,1024),(0xa40774,4),(FLAG,4),(0x833688,4),(0x851a70,32)])
        finally:u.hook_del(hook)
        after=bytearray(u.mem_read(CELL,9*512));actor_after=bytearray(u.mem_read(ACTOR,0xa0))
        for i in range(9):
            for off,size in FIELDS:after[i*512+off:i*512+off+size]=before[i*512+off:i*512+off+size]
        assert bytes(after)==before
        for off,size in ((0x74,3),(0x7d,1)):actor_after[off:off+size]=before_actor[off:off+size]
        assert bytes(actor_after)==before_actor
        output=[u.reg_read(UC_X86_REG_EAX)&255,*u.mem_read(ACTOR+0x74,3),u.mem_read(ACTOR+0x7d,1)[0],*words(u,ACTOR+0x88,3)]
        for i in range(9):
            c=CELL+i*512;output.extend([words(u,c+0x44,1)[0],u.mem_read(c+0x11e,1)[0],u.mem_read(c+0x11c,1)[0],words(u,c+0x24,1)[0],words(u,c+0x50,1)[0],u.mem_read(c+0x122,1)[0]])
        output.append(self.lookups);return [digest(output),digest(self.events)]
