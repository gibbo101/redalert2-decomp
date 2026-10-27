# SPDX-License-Identifier: GPL-3.0-or-later
"""Unchanged patched redraw/region routines; explicit allocation and atexit services."""
import hashlib
from pathlib import Path
import struct
from original_presentation import PresentationOracle,STACK
from compare_original import PATCHED_EXPECTED
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_EIP,UC_X86_REG_ESP
ARENA=0x2900000;TACTICAL=ARENA+0x100;ACTOR=ARENA+0x2100
SLOTS=ARENA+0x3000;GROWN=ARENA+0x6000;INPUT=ARENA+0x9000;RESULT=ARENA+0x9100
VECTOR=0xabe5b0;MAP=0x8324e0
class RedrawOracle(PresentationOracle):
    def __init__(self,exe):
        if hashlib.sha256(Path(exe).read_bytes()).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact patched engine required')
        super().__init__(exe,allow_patched=True);self.u.mem_map(ARENA,0x10000)
        self.events=[];self.mode=None
        self.hooks=[self.u.hook_add(UC_HOOK_CODE,self.service,begin=a,end=a) for a in [0x6acbe0,0x78298a]]
        self.checked_call(0x6e2fe0,writes=[(0xac0358,16)])
        assert bytes(self.u.mem_read(0xac0358,16))==bytes(16)
    def va(self,a):return a
    def ints(self,p,values):self.u.mem_write(p,struct.pack('<'+'I'*len(values),*[v&0xffffffff for v in values]))
    @staticmethod
    def signed(v):return struct.unpack('<i',struct.pack('<I',v&0xffffffff))[0]
    def result(self,p,n):return list(struct.unpack('<'+'i'*n,self.u.mem_read(p,4*n)))
    def event(self,k,value,index=-1,field=-1):self.events.extend([k,index,field,value])
    def ret(self,pop,value=0):
        sp=self.u.reg_read(UC_X86_REG_ESP)
        self.u.reg_write(UC_X86_REG_EAX,value&0xffffffff);self.u.reg_write(UC_X86_REG_ESP,sp+4+pop)
        self.u.reg_write(UC_X86_REG_EIP,struct.unpack('<I',self.u.mem_read(sp,4))[0])
    def service(self,u,a,n,ctx):
        sp=u.reg_read(UC_X86_REG_ESP);arg=lambda i:struct.unpack('<I',u.mem_read(sp+4+4*i,4))[0]
        if a==0x78298a:
            assert self.mode=='I' and arg(0)==0x6a2330
            self.atexit+=1;self.ret(0);return
        assert self.mode=='Q' and u.reg_read(UC_X86_REG_ECX)==VECTOR and arg(1)==0
        requested=arg(0);assert requested==self.capacity+self.growth and 0<requested<=128
        self.event('g',requested)
        if self.growth_success:
            # Supplied allocation, retaining the entire old capacity, not only live entries.
            old=bytes(u.mem_read(self.pointer,self.capacity*20))
            for i in range(requested):self.ints(GROWN+i*20,[90,91,92,93,94|0x5c5b5a00])
            u.mem_write(GROWN,old)
            self.put(VECTOR+4,GROWN);self.put(VECTOR+8,requested)
            self.pointer=GROWN;self.capacity=requested;self.event('a',requested)
        self.ret(8,int(self.growth_success))
    def setup(self):
        self.u.mem_write(ARENA,bytes([0x5a])*0x10000)
        self.u.mem_write(MAP,bytes([0x5a])*0x2000)
        self.u.mem_write(VECTOR,bytes([0x5a])*32);self.events=[]
    def snapshot(self):return [bytes(self.u.mem_read(p,n)) for p,n in [(ARENA,0x10000),(MAP,0x2000),(VECTOR,32)]]
    def check(self,before,allowed):
        for (p,n),old in zip([(ARENA,0x10000),(MAP,0x2000),(VECTOR,32)],before):
            after=bytearray(self.u.mem_read(p,n))
            for a,s in allowed:
                if p<=a and a+s<=p+n:after[a-p:a-p+s]=old[a-p:a-p+s]
            assert bytes(after)==old,'Redraw arena/metadata/guards changed outside contract'
    def initial(self):
        self.mode='I';self.setup();self.atexit=0
        self.checked_call(0x6a22f0,writes=[(VECTOR,0x18)])
        assert self.atexit==1 and self.u.mem_read(VECTOR+12,1)[0]==1
        assert self.result(VECTOR,3)==[0x7ac4c4,0,0]
        return [self.result(VECTOR+16,1)[0],self.result(VECTOR+8,1)[0],self.result(VECTOR+20,1)[0],self.u.mem_read(VECTOR+13,1)[0]]
    def request(self,command,map_mode,counter,tactical,present,needs,mode):
        self.mode=command;self.setup();self.put(MAP+12,map_mode)
        self.u.mem_write(MAP+0x1154,bytes([counter]));self.u.mem_write(TACTICAL+0xd7d,bytes([tactical]))
        self.u.mem_write(ACTOR+0x75,bytes([needs]));self.put(ACTOR,0x7addf8)
        self.put(0x83996c,TACTICAL if present else 0)
        locations={TACTICAL+0xd7d:'t',MAP+12:'m',MAP+0x1154:'c',ACTOR+0x75:'r'}
        def write(u,access,p,n,v,ctx):
            if p in locations:
                assert n==(4 if p==MAP+12 else 1)
                self.event(locations[p],self.signed(v) if n==4 else v&255)
        allowed=[(p,4 if p==MAP+12 else 1) for p in locations];before=self.snapshot()
        hook=self.u.hook_add(UC_HOOK_MEM_WRITE,write)
        try:self.checked_call(0x4e09a0 if command=='M' else 0x5d36e0,[mode] if command=='M' else [],
                              MAP if command=='M' else ACTOR,writes=allowed)
        finally:self.u.hook_del(hook)
        self.check(before,allowed)
        return [self.result(MAP+12,1)[0],self.u.mem_read(MAP+0x1154,1)[0],
                self.u.mem_read(TACTICAL+0xd7d,1)[0],self.u.mem_read(ACTOR+0x75,1)[0],*self.events]
    def union(self,first,second):
        self.mode='U';self.setup();self.ints(INPUT,[*first,*second]);before=self.snapshot()
        self.checked_call(0x45efe0,[INPUT+16],RESULT,INPUT,writes=[(RESULT,16)],inputs=[(INPUT,32)])
        assert self.u.reg_read(UC_X86_REG_EAX)==RESULT;self.check(before,[(RESULT,16)])
        return self.result(RESULT,4)
    def queue(self,count,slots,growth,owns,success,incoming):
        self.mode='Q';self.setup();self.capacity=len(slots);self.growth=growth;self.growth_success=success
        assert 0<=count<=len(slots)<=128
        self.pointer=SLOTS
        for i,slot in enumerate(slots):self.ints(SLOTS+i*20,[*slot[:4],slot[4]|0x5c5b5a00])
        self.ints(VECTOR,[0x7ac4c4,SLOTS,len(slots),1|(int(owns)<<8),count,growth])
        before=self.snapshot()
        # Only original instruction writes are traced. Allocator callback mutations
        # have their explicit g/a events. Entry padding is not a native semantic field.
        writes=[]
        def write(u,access,p,n,v,ctx):
            if p==VECTOR+16:
                assert n==4;self.event('n',self.signed(v))
            elif self.pointer<=p<self.pointer+self.capacity*20:
                assert n==4 and (p-self.pointer)%4==0
                index,offset=divmod(p-self.pointer,20);field=offset//4
                self.event('s',v&255 if field==4 else self.signed(v),index,field)
                writes.append((p,n))
        allowed=[(VECTOR+16,4),(SLOTS,len(slots)*20)]
        if success and growth>0 and len(slots)+growth<=128:
            allowed.extend([(VECTOR+4,8),(GROWN,(len(slots)+growth)*20)])
        hook=self.u.hook_add(UC_HOOK_MEM_WRITE,write)
        try:self.checked_call(0x6a3020,incoming,TACTICAL,writes=allowed)
        finally:self.u.hook_del(hook)
        self.check(before,allowed)
        # Capacity tail is compared too, including old last entries after removal.
        result=[self.result(VECTOR+16,1)[0],self.capacity]
        for i in range(self.capacity):
            result.extend(self.result(self.pointer+i*20,4));result.append(self.u.mem_read(self.pointer+i*20+16,1)[0])
        return [*result,*self.events]
