# SPDX-License-Identifier: GPL-3.0-or-later
"""Unchanged complete wall parent/connection with declared presentation/map services."""
import struct
from original_presentation import PresentationOracle,STACK
from original_foot_lit import words,ret
from original_overlay_type_inputs import digest
from verify_map_wall_update import verify,RANGES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_ECX,UC_X86_REG_EDX,UC_X86_REG_ESP,UC_X86_REG_EAX
CELL=0x2600000;TYPES=CELL+0x4000;REGISTRY=CELL+0x34000;NODES=CELL+0x40000
RULES=CELL+0x70000;KIND=CELL+0x72000;VTABLE=KIND+0x100;TACTICAL=CELL+0x73000
FIELDS=((0x44,4),(0x4c,4),(0x50,4),(0x11e,1),(0x122,1))
def pack(values):return b''.join(struct.pack('<I',v&0xffffffff) for v in values)
def signed(v):return struct.unpack('<i',pack([v]))[0]
def point(p):return struct.unpack('<hh',pack([p]))
def packed(x,y):return (x&65535)|((y&65535)<<16)
class MapWallUpdateOracle(PresentationOracle):
    def __init__(self,exe):
        self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True)
        self.u.mem_map(CELL,0x80000);self.u.hook_add(UC_HOOK_CODE,self.code)
        self.roots={hex(a):0 for a in RANGES};self.stores=self.services=0
        self.branches={name:0 for name in ('old_bounds','compose_bounds','remove_2','remove_26','remove_0','remove_1','remove_22','remove_3','zone_add','zone_remove','neighbor_decrements')}
    def va(self,a):return a
    def cell_id(self,p):
        assert CELL<=p<CELL+self.count*512 and (p-CELL)%512==0,hex(p)
        return (p-CELL)//512
    def query(self,p):
        x,y=point(p)
        if self.alias==1:return 0
        if self.alias==2:return ((x&65535)^(y&65535))%min(self.count,2)
        return (((x&65535)+3*(y&65535)+self.seed)&0xffffffff)%self.count
    def bounds(self,id,kind):
        mode=self.seed&3
        if mode==0:return [0,0,0,0]
        if mode==1:return [id*37-100,kind*41-77,17+id,13+kind]
        if mode==2:return [signed(self.seed^(id*0x1234567)),signed(self.seed+kind*0x7654321),signed(self.seed^(kind*0x40000000)),signed(self.seed+id*0x11111111)]
        return [signed(self.seed-id*53),signed(self.seed+kind*7),-1 if kind==0 else 23,0 if kind==2 else 17]
    def code(self,u,a,n,ctx):
        sp=u.reg_read(UC_X86_REG_ESP);receiver=u.reg_read(UC_X86_REG_ECX)
        if any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()):
            if a in RANGES:self.roots[hex(a)]+=1
            branch={0x4759cf:'old_bounds',0x475a2d:'compose_bounds',0x475c04:'remove_0',0x475c2b:'remove_1',0x475c57:'remove_22',0x475c7e:'remove_3',
                    0x475d23:'zone_add',0x475cb7:'zone_remove',0x475cc7:'neighbor_decrements'}.get(a)
            if a==0x475bd2:
                from unicorn.x86_const import UC_X86_REG_ESI
                branch='remove_'+str(words(u,u.reg_read(UC_X86_REG_ESI)+0x44,1)[0])
            if branch:self.branches[branch]+=1
            if a==0x475840:self.events.extend([6,self.cell_id(receiver),*words(u,sp+4,2)])
            if a==0x45efe0:self.events.extend([2,*words(u,u.reg_read(UC_X86_REG_EDX),4),*words(u,words(u,sp+4,1)[0],4)])
            return
        self.services+=1;caller=words(u,sp,1)[0]
        assert any(lo<=caller<lo+size for lo,size in RANGES.items()),hex(caller)
        if a in (0x474eb0,0x475100,0x4752b0):
            id=self.cell_id(receiver);kind={0x474eb0:0,0x475100:1,0x4752b0:2}[a];output=words(u,sp+4,1)[0]
            assert STACK-0x2000<=output<STACK
            values=self.bounds(id,kind);self.events.extend([1,id,kind,*values]);u.mem_write(output,pack(values));ret(u,4,output)
        elif a==0x6a3020:
            assert receiver==TACTICAL and words(u,sp+20,1)==[0]
            self.events.extend([3,*words(u,sp+4,4)]);ret(u,20)
        elif a in (0x631570,0x54fb20,0x54fc60,0x566340):
            assert receiver==0x8324e0;p=words(u,sp+4,1)[0];self.cell_id(p-0x24);q=words(u,p,1)[0]
            self.events.extend([4,q] if a==0x631570 else [10,{0x54fb20:0,0x54fc60:1,0x566340:2}[a],q]);ret(u,4)
        elif a==0x548070:
            assert receiver==0x8324e0;p=words(u,sp+4,1)[0];assert STACK-0x2000<=p<STACK
            q=words(u,p,1)[0];id=self.query(q);self.events.extend([5,q,id]);ret(u,4,CELL+id*512)
        elif a==KIND:
            assert NODES<=receiver<NODES+16*8*0x500 and (receiver-NODES)%0x500==0
            slot=(receiver-NODES)//0x500;id,index=divmod(slot,8);kind=words(u,receiver+0x64,1)[0]
            self.events.extend([7,id,index,kind]);ret(u,0,kind)
        elif a==0x6ecb90:
            id=self.cell_id(receiver);assert u.reg_read(UC_X86_REG_EDX)&255==1;self.events.extend([9,id]);ret(u,0)
        elif a==0x472540:
            id=self.cell_id(receiver);assert words(u,sp+4,1)==[0xffffffff];self.events.extend([8,id,0xffffffff])
            before=words(u,receiver+0x4c,1)[0];overlay=words(u,receiver+0x44,1)[0]
            value=before if self.recalc==0 else (before^((overlay+1)&7) if self.recalc==1 else (before^1 if self.recalc==2 else int(overlay!=0xffffffff)))
            self.put(receiver+0x4c,value);self.events.extend([12,id,0x4c,4,value]);ret(u,4)
        else:raise AssertionError(f'Uninspected map wall-update instruction {a:#x}')
    def run(self,op,v):
        self.events=[];self.seed=self.alias=self.recalc=0
        if op=='C':
            requested,facing,overlay=v[:3];gates=v[3:8];n=v[8];data=[overlay,0,0,0,0,n,*v[9:]];self.count=1;p=0;sx=sy=0;directions=[0]*8;skip=0
        else:
            self.seed,skip,p,sx,sy,self.recalc,self.alias,all_walls=v[:8];gates=v[8:13];assert v[13:18]==self.inspection['visits'];directions=v[18:26];self.count=v[26];data=v[27:]
        u=self.u;u.mem_write(CELL,b'\xa5'*(16*512));u.mem_write(NODES,b'\xb6'*(16*8*0x500));u.mem_write(TYPES,b'\xc7'*(256*0x300))
        u.mem_write(REGISTRY,pack([TYPES+i*0x300 for i in range(256)]));self.put(0xa35dec,REGISTRY)
        for i in range(256):u.mem_write(TYPES+i*0x300+0x278,bytes([int(op=='C' or all_walls or ((i+self.seed)&0xffffffff)%5!=0)]))
        u.mem_write(RULES,b'\xd8'*0x1000);self.put(0x839848,RULES)
        # Supplied gate handles are normalized through native identities.
        for off,t in zip((0x77c,0x780,0x78c,0x784,0x788),gates):self.put(RULES+off,t)
        self.put(VTABLE+0x2c,KIND);self.put(0x83996c,TACTICAL);self.put(0x839630,sx);self.put(0x839634,sy);u.mem_write(0x851a70,pack(directions))
        cursor=0;x,y=point(p)
        for i in range(self.count):
            c=CELL+i*512;overlay,amount,neighbors,passability,owner,n=data[cursor:cursor+6];cursor+=6
            q=p if i==0 else packed(x+i-4,y+(i*3)%5-2)
            for off,value in ((0x24,q),(0x44,overlay),(0x4c,passability),(0x50,owner),(0xe4,NODES+i*8*0x500 if n else 0)):self.put(c+off,value)
            u.mem_write(c+0x11e,bytes([amount]));u.mem_write(c+0x122,bytes([neighbors]))
            for j in range(n):
                kind,health,t=data[cursor:cursor+3];cursor+=3;node=NODES+(i*8+j)*0x500
                for off,value in ((0,VTABLE),(0x30,node+0x500 if j+1<n else 0),(0x64,kind),(0x6c,health),(0x418,t)):self.put(node+off,value)
        assert cursor==len(data)
        before=bytes(u.mem_read(CELL,16*512))
        def store(u,access,address,size,value,ctx):
            if not CELL<=address<CELL+16*512:return
            id=(address-CELL)//512;off=(address-CELL)%512;assert id<self.count and (off,size) in FIELDS
            value&=(1<<(size*8))-1;self.events.extend([12,id,off,size,value]);self.stores+=1
        hook=u.hook_add(UC_HOOK_MEM_WRITE,store)
        try:self.checked_call(0x475840 if op=='C' else 0x475960,[requested,facing] if op=='C' else [skip],CELL,
            writes=[(CELL,16*512)] if op=='U' else [],inputs=[(TYPES,256*0x300),(REGISTRY,1024),(NODES,16*8*0x500),(RULES,0x1000),
             (0xa35dec,4),(0x839848,4),(0x83996c,4),(0x839630,8),(0x851a70,32),(VTABLE,0x30),(0x7d2b58,20)])
        finally:u.hook_del(hook)
        after=bytearray(u.mem_read(CELL,16*512))
        for i in range(self.count):
            for off,size in FIELDS:after[i*512+off:i*512+off+size]=before[i*512+off:i*512+off+size]
        assert bytes(after)==before
        if op=='C':return [str(u.reg_read(UC_X86_REG_EAX)&255),digest(self.events)]
        output=[]
        for i in range(self.count):
            c=CELL+i*512;output.extend([words(u,c+0x24,1)[0],words(u,c+0x44,1)[0],words(u,c+0x4c,1)[0],words(u,c+0x50,1)[0],u.mem_read(c+0x11e,1)[0],u.mem_read(c+0x122,1)[0]])
        return [digest(output),digest(self.events)]
