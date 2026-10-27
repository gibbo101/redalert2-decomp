# SPDX-License-Identifier: GPL-3.0-or-later
"""Actual temporary Overlay lifecycle with explicit external/heap services."""
import struct
from original_presentation import PresentationOracle,STACK,OBJ
from original_foot_lit import words,ret
from original_overlay_type_inputs import digest
from original_overlay_placement import ACTOR,TYPE,CELL,PROVIDER,FLAG
from verify_overlay_object_lifetime import verify,RANGES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EDX,UC_X86_REG_EIP,UC_X86_REG_EAX
EXTRA=0x2340000;TAG=EXTRA+0x7000;TYPEINFO=EXTRA+0x8000
REGS=(0xa40368,0xac0d60,0xac0cb0,0xac0c58,0xac0cd8,0xa40c00)
FIELDS=((0x10,4),(0x14,4),(0x18,4),(0x1c,4),(0x20,1),
 *[(p,4) for p in (0x24,0x28,0x2c,0x30,0x34,0x38,0x3c,0x40,0x44,0x48,0x50,0x54,0x58,0x5c,0x64)],
 (0x68,1),(0x6c,4),(0x70,4),*[(p,1) for p in range(0x74,0x7e)],
 (0x80,4),(0x84,1),(0x85,1),*[(p,4) for p in (0x88,0x8c,0x90,0x94,0x98)])
BASE_RANGES={0x40ff10:0x47,0x5d22e0:529,0x405bf0:18,0x5d4e90:124,0x5dc300:0xa7}
RTTI=(0x7cf6a8,0x7f6d68,0x7daec0,0x7ce5e0)
VTABLE_STORES={0:{0x79add8,0x7a7498,0x7a77f4},4:{0x79adbc,0x7a747c,0x7a77d0},
 8:{0x79ae44,0x79adb4,0x7a7474,0x7a77ec},12:{0x79ae3c,0x79adac,0x7a746c,0x7a77c8}}
class OverlayObjectLifetimeOracle(PresentationOracle):
    def __init__(self,exe):
        self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True)
        self.u.mem_map(ACTOR,0x50000);self.u.hook_add(UC_HOOK_CODE,self.code)
        self.roots={hex(a):0 for a in RANGES};self.stores=self.services=0
    def va(self,a):return a
    def identity(self,p):
        assert ACTOR<=p<ACTOR+self.count_actors*256 and (p-ACTOR)%256==0,hex(p)
        return (p-ACTOR)//256+1
    def slot(self,p):return 0 if not p else self.identity(p)
    def pointer(self,id):return 0 if not id else ACTOR+(id-1)*256
    def code(self,u,a,n,ctx):
        if any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()):
            if a in RANGES:self.roots[hex(a)]+=1
            return
        self.services+=1;sp=u.reg_read(UC_X86_REG_ESP);receiver=u.reg_read(UC_X86_REG_ECX)
        caller=words(u,sp,1)[0];assert any(lo<=caller<lo+size for lo,size in RANGES.items()),hex(caller)
        if a==0x40cd40:
            role=REGS.index(receiver);amount,zero=words(u,sp+4,2)
            assert zero==0 and amount==self.capacities[role]+self.growth and 0<amount<=256
            self.events.extend([50,role+1,amount,self.grow_result])
            if self.grow_result&255:
                for i in range(self.capacities[role],amount):self.put(EXTRA+role*4096+i*4,0)
                self.capacities[role]=amount;self.put(receiver+8,amount);u.mem_write(receiver+13,b'\1')
            ret(u,8,self.grow_result)
        elif a==0x40dc20:self.identity(receiver);self.events.append(2);ret(u,0,0)
        elif a==0x4e09a0:
            assert receiver==0x8324e0 and words(u,sp+4,1)==[0];self.events.append(3);ret(u,4)
        elif a==0x548070:
            assert receiver==0x8324e0;pointer=words(u,sp+4,1)[0];assert STACK-0x2000<=pointer<STACK
            self.events.extend([4,words(u,pointer,1)[0]]);ret(u,4,CELL)
        elif a==0x476ba0:
            assert receiver==CELL and words(u,sp+4,1)==[0]
            self.events.extend([5,21,0x11e,1,self.resource]);u.mem_write(CELL+0x11e,bytes([self.resource]));ret(u,4,0)
        elif a==0x472540:
            assert receiver==CELL and words(u,sp+4,1)==[0xffffffff];self.events.extend([6,0xffffffff]);ret(u,4)
        elif a==0x435fb0:
            assert receiver==TAG;self.events.extend([60,1]);ret(u,0)
        elif a==0x6ecb90:
            id=self.identity(receiver);assert u.reg_read(UC_X86_REG_EDX)&255==1;self.events.extend([61,id]);ret(u,0)
        elif a==0x783c05:
            pointer=words(u,sp+4,1)[0];self.rtti_actor=self.identity(pointer);ret(u,0,TYPEINFO)
        elif a==0x781cd1:
            assert words(u,sp+4,1)==[TYPEINFO];kind=RTTI.index(receiver)
            self.events.extend([64,self.rtti_actor,kind]);ret(u,4,0)
        elif a==0x5d2530:
            self.events.extend([62,self.identity(receiver)]);ret(u,0)
        elif a==0x781d3b:
            id=self.identity(words(u,sp+4,1)[0]);self.freed[id-1]+=1;self.events.extend([63,id]);ret(u,0)
        else:raise AssertionError(f'Uninspected Overlay lifetime instruction {a:#x}')
    def run(self,op,v):
        (seed,p,invalid,incoming,flag,capacity,count,self.growth,owns,self.grow_result,self.resource,self.count_actors,mode)=v
        u=self.u;self.events=[];self.freed=[0]*self.count_actors
        u.mem_write(ACTOR,b'\xa5'*(self.count_actors*256));u.mem_write(TYPE,b'\xb6'*1024);u.mem_write(CELL,b'\xc7'*512)
        for i in range(self.count_actors):
            actor=ACTOR+i*256
            for off,size in FIELDS:u.mem_write(actor+off,bytes(size))
            for off,value in ((0,0x7a77f4),(4,0x7a77d0),(8,0x7a77ec),(12,0x7a77c8),(0x10,seed+i),(0x14,seed+i),(0x88,13),(0x8c,17),(0x90,19),(0x98,TYPE)):
                self.put(actor+off,value)
            u.mem_write(actor+0x76,b'\1');u.mem_write(actor+0x7d,bytes([(seed>>i)&1]))
            if op=='R' and mode&32:self.put(actor+0x38,TAG)
        self.put(TYPE,0x7a7a08);self.put(TYPE+0x264,102);self.put(TYPE+0x268,5 if mode&8 else 0);self.put(TYPE+0x26c,0)
        u.mem_write(TYPE+0x278,b'\0');u.mem_write(TYPE+0x27a,bytes([255 if mode&16 else 0]))
        self.put(CELL+0x44,seed^0x76543210);u.mem_write(CELL+0x11e,bytes([seed&255]));u.mem_write(CELL+0x11c,bytes([5 if mode&4 else 0]))
        self.capacities=[capacity]*6
        for role,registry in enumerate(REGS):
            buffer=EXTRA+role*4096;u.mem_write(buffer,b'\xd8'*1024)
            self.put(registry,0x79e868);self.put(registry+4,buffer);self.put(registry+8,capacity)
            u.mem_write(registry+12,bytes([1,owns]));self.put(registry+16,0 if role==4 and op!='K' else count);self.put(registry+20,self.growth)
            for i in range(capacity):self.put(buffer+i*4,self.pointer(i%self.count_actors+1))
        self.put(0xa40774,1);u.mem_write(0xa40958,b'\1');self.put(0xa73088,invalid);self.put(FLAG,flag)
        self.put(0xa3d290,PROVIDER if seed else 0);self.put(PROVIDER+0x214,seed^0xfedcba98)
        self.put(OBJ,p);u.mem_write(0xa72f00,struct.pack('<Iii',seed,17,-19))
        before=bytes(u.mem_read(ACTOR,self.count_actors*256));before_cell=bytes(u.mem_read(CELL,512))
        before_buffers=[bytes(u.mem_read(EXTRA+i*4096,1024)) for i in range(6)]
        def store(u,access,address,size,value,ctx):
            value&=(1<<(size*8))-1;pc=u.reg_read(UC_X86_REG_EIP)
            if ACTOR<=address<ACTOR+self.count_actors*256:
                id=(address-ACTOR)//256+1;off=(address-ACTOR)%256
                if off in VTABLE_STORES:assert size==4 and value in VTABLE_STORES[off];return
                if off==0x14:assert size==1
                else:assert (off,size) in FIELDS,(hex(pc),hex(off),size)
                if off in (0x48,0x5c):assert value==0x830fac;value=1
                if off==0x98:assert value in (0,TYPE);value=int(bool(value))
                prefix=30 if any(a<=pc<a+n for a,n in BASE_RANGES.items()) else 20
                self.events.extend([prefix,id,off,size,value])
            elif CELL<=address<CELL+512:
                assert (address-CELL,size) in ((0x44,4),(0x11e,1));self.events.extend([21,address-CELL,size,value])
            elif address==FLAG:self.events.extend([23,0,size,value])
            elif address==PROVIDER+0x214:self.events.extend([24,0,size,value])
            elif any(reg<=address<reg+24 for reg in REGS):
                role=next(i for i,reg in enumerate(REGS) if reg<=address<reg+24);assert address==REGS[role]+16 and size==4
                prefix=22 if role==5 and 0x5da7d0<=pc<0x5da8cf else 31+role;self.events.extend([prefix,0,4,value])
            elif EXTRA<=address<EXTRA+6*4096:
                role=(address-EXTRA)//4096;off=(address-EXTRA)%4096;assert off%4==0 and off<self.capacities[role]*4 and size==4
                prefix=22 if role==5 and 0x5da7d0<=pc<0x5da8cf else 31+role;self.events.extend([prefix,off//4+1,4,self.slot(value)])
            else:return
            self.stores+=1
        hook=u.hook_add(UC_HOOK_MEM_WRITE,store)
        writes=[(ACTOR,self.count_actors*256),(CELL,512),(FLAG,4),(PROVIDER+0x214,4),*[(reg,24) for reg in REGS],*[(EXTRA+i*4096,1024) for i in range(6)]]
        inputs=[(TYPE,1024),(OBJ,4),(0xa40774,4),(0xa40958,1),(0xa73088,4),(0xa3d290,4),(0xa72f00,12)]
        try:
            if op=='C':
                for i in range(self.count_actors):
                    self.checked_call(0x5da7d0,[TYPE,OBJ,incoming],ACTOR+i*256,writes=writes,inputs=inputs)
                    assert u.reg_read(UC_X86_REG_EAX)==ACTOR+i*256
            elif op=='R':
                for i in range(self.count_actors):
                    self.checked_call(0x5d4e90,[],ACTOR+i*256,writes=writes,inputs=inputs)
                    if mode&64:self.checked_call(0x5d4e90,[],ACTOR+i*256,writes=writes,inputs=inputs)
            else:assert op=='K'
            if op=='K' or mode&1:self.checked_call(0x6ecf10,[],0,writes=writes,inputs=inputs)
        finally:u.hook_del(hook)
        after=bytearray(u.mem_read(ACTOR,self.count_actors*256));changed_cell=bytearray(u.mem_read(CELL,512))
        for i in range(self.count_actors):
            for off,size in ((0,16),*FIELDS):after[i*256+off:i*256+off+size]=before[i*256+off:i*256+off+size]
        assert after==before
        for off,size in ((0x44,4),(0x11e,1)):changed_cell[off:off+size]=before_cell[off:off+size]
        assert changed_cell==before_cell
        output=[words(u,PROVIDER+0x214,1)[0],words(u,FLAG,1)[0],words(u,CELL+0x44,1)[0],u.mem_read(CELL+0x11e,1)[0],u.mem_read(CELL+0x11c,1)[0]]
        for i in range(self.count_actors):
            actor=ACTOR+i*256
            for off,size in FIELDS:
                value=int.from_bytes(u.mem_read(actor+off,size),'little')
                if off in (0x48,0x5c) and value:value=1
                if off==0x38 and value:assert value==TAG;value=1
                if off==0x98:assert value in (0,TYPE);value=int(bool(value))
                output.append(value)
        for role,reg in enumerate(REGS):
            cap=self.capacities[role];output.extend([words(u,reg+16,1)[0],cap,u.mem_read(reg+13,1)[0]])
            output.extend(self.slot(value) for value in words(u,EXTRA+role*4096,cap))
            tail=max(capacity,cap)*4;assert bytes(u.mem_read(EXTRA+role*4096+tail,1024-tail))==before_buffers[role][tail:]
        output.extend(self.freed)
        return [digest(output),digest(self.events)]
