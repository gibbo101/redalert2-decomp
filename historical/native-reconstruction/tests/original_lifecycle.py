# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact-base ordinary Terrain placement/removal and actual layer/vector operations.
No instruction patches. World height, map lookup/redraw, logic, global pointer
cleanup and allocator outcomes are explicit services. No alpha/radial resources.
"""
import struct
from original_occupation import OccupationOracle
from original_occupation import SCENARIO
from original_presentation import STACK
from unicorn import UC_HOOK_CODE, UC_HOOK_MEM_WRITE
from unicorn.x86_const import *

ACTORS=0x2300000; TYPES=0x2400000; CELLS=0x2500000
TABLE=0x2c00000; INPUT=0x2d00000; TACTICAL=0x2d01000; BUFFERS=0x2d10000
LAYERS=0x83a888

class LifecycleOracle(OccupationOracle):
    def __init__(self, exe, *, allow_patched=False):
        super().__init__(exe,allow_patched=allow_patched)
        self.layers=self.va(LAYERS)
        self.u.mem_map(ACTORS, 0x1000000)
        self.call(self.va(0x491400))
        self.neighbors=list(struct.iter_unpack('<2h',self.u.mem_read(self.va(0x839d80),32)))
        assert self.neighbors==[(0,-1),(1,-1),(1,0),(1,1),(0,1),(-1,1),(-1,0),(-1,-1)]
        for fn in [self.va(0x6975d0),self.va(0x697660),self.va(0x697930)]:self.call(fn)
        self.scale=struct.unpack('<d',self.u.mem_read(self.va(0xaa5f70),8))[0]
        self.put(self.va(0x821c8c),TACTICAL)
        self.put(self.va(0x8192d8),0) # no resource handle registry
        self.put(self.va(0x81a800)+0x138,TABLE)
        self.put(self.va(0x81a800)+0x13c,0x40000)
        self.put(self.va(0xaa6050),1024);self.put(self.va(0xaa6054),720)
    @staticmethod
    def actor(id):return 0 if id==-1 else ACTORS+id*0x300
    @staticmethod
    def identity(ptr):
        if ptr==0:return -1
        if ptr==0xa5a5a5a5:return -2
        if ptr==0xb6b6b6b6:return -3
        assert ACTORS<=ptr<TYPES and (ptr-ACTORS)%0x300==0,hex(ptr)
        return (ptr-ACTORS)//0x300
    @classmethod
    def slot(cls,id):return 0xa5a5a5a5 if id==-2 else 0xb6b6b6b6 if id==-3 else cls.actor(id)
    @staticmethod
    def signed(value):return struct.unpack('<i',struct.pack('<I',value&0xffffffff))[0]
    def buffer(self,storage):return BUFFERS+storage*0x10000
    def prepare(self, actors, layers):
        # Preserve whole configured arenas, including unused capacity slots.
        assert len(actors)<=1024
        self.actor_count=len(actors)
        self.u.mem_write(ACTORS,bytes([0x5a])*(len(actors)*0x300+32))
        self.u.mem_write(TYPES,bytes([0x69])*(len(actors)*0x300+32))
        self.buffers={};self.buffer_expected={};self.next_storage=5;self.events=[];self.target=0
        self.put(self.va(0xa5aa88),104);self.u.mem_write(self.va(0xa28588),b'\1')
        for id,values in enumerate(actors):
            x,y,z,last=values[:4];p=self.actor(id);t=TYPES+id*0x300
            self.put(p,self.va(0x79827c));self.put(p+0xb0,t);self.put(p+0x80,last)
            self.u.mem_write(p+0x88,struct.pack('<3i',x,y,z))
            self.u.mem_write(p+0x74,bytes([0,0,1,0,0,0])) # raw layer actor is off-map
            self.put(t,self.va(0x798490));self.put(t+0x288,self.va(0xaa7f18))
        self.u.mem_write(self.layers,bytes([0x7c])*120)
        for index,(slots,count,grow,valid,owned,storage) in enumerate(layers):
            p=self.layers+index*24
            self.put(p,self.va(0x789870));self.put(p+4,0 if storage==-1 else self.buffer(storage))
            self.put(p+8,len(slots));self.u.mem_write(p+12,bytes([valid,owned]))
            self.put(p+16,count);self.put(p+20,grow)
            if storage!=-1:
                self.make_buffer(storage,index,len(slots),0xa5)
                for i,id in enumerate(slots):self.put(self.buffer(storage)+i*4,self.slot(id))
                self.buffer_expected[storage]=bytearray(self.u.mem_read(self.buffer(storage),len(slots)*4+32))
    def make_buffer(self,storage,index,capacity,fill):
        assert 0<=storage<90 and capacity*4+32<=0x10000
        if not hasattr(self,'buffer_expected'):self.buffer_expected={}
        self.buffers[storage]=(index,capacity)
        self.u.mem_write(self.buffer(storage),bytes([fill])*(capacity*4+32))
        self.buffer_expected[storage]=bytearray(self.u.mem_read(self.buffer(storage),capacity*4+32))
    def audit_buffers(self):
        for storage,expected in self.buffer_expected.items():
            if storage in self.buffers:
                assert bytes(self.u.mem_read(self.buffer(storage),len(expected)))==bytes(expected),('buffer',storage)
    def storage(self,ptr):
        if ptr==0:return -1
        assert ptr>=BUFFERS and (ptr-BUFFERS)%0x10000==0,hex(ptr)
        return (ptr-BUFFERS)//0x10000
    def layer_result(self,n):
        result=[*[self.signed(struct.unpack('<I',self.u.mem_read(self.actor(id)+0x80,4))[0]) for id in range(n)]]
        for index in range(5):
            p=self.layers+index*24
            ptr,cap=struct.unpack('<2I',self.u.mem_read(p+4,8))
            valid,owned=self.u.mem_read(p+12,2);count,grow=struct.unpack('<2i',self.u.mem_read(p+16,8))
            result.extend([cap,count,grow,valid,owned,self.storage(ptr)])
            if cap:result.extend(self.identity(v) for v in struct.unpack('<'+str(cap)+'I',self.u.mem_read(ptr,cap*4)))
        return result
    def layer(self, op, actors, layers, target, index=2, sorted=True, allocation=True):
        self.prepare(actors,layers);self.allocation=allocation
        regions=[(ACTORS,len(actors)*0x300+32),(TYPES,len(actors)*0x300+32),(self.layers,120)]
        before=[bytes(self.u.mem_read(p,n)) for p,n in regions]
        hooks=self.hooks(regions,lifecycle=False)
        try:
            if op=='I':self.checked_call(self.va(0x5329b0),[self.actor(target),int(sorted)],self.layers+index*24);result=self.u.reg_read(UC_X86_REG_EAX)&255
            elif op=='S':self.checked_call(self.va(0x4996d0),[self.actor(target)],self.va(0x81a800));result=1
            elif op=='R':self.checked_call(self.va(0x499720),[self.actor(target)],self.va(0x81a800));result=1
            else:raise ValueError(op)
        finally:
            for h in hooks:self.u.hook_del(h)
        for (p,n),old in zip(regions,before):
            new=bytearray(self.u.mem_read(p,n));old=bytearray(old)
            if p==ACTORS:
                for id in range(len(actors)):new[id*0x300+0x80:id*0x300+0x84]=old[id*0x300+0x80:id*0x300+0x84]
            elif p==self.layers:
                for index in range(5):
                    for off,size in [(4,10),(16,4)]:new[index*24+off:index*24+off+size]=old[index*24+off:index*24+off+size]
            assert new==old,hex(p)
        self.audit_buffers()
        return [result,*self.layer_result(len(actors)),*self.events]
    def hooks(self,regions,lifecycle):
        def event(kind,a=0,b=0,c=0):self.events.extend([kind,a,b,c])
        def service(u,address,size,ctx):
            sp=u.reg_read(UC_X86_REG_ESP)
            arg=lambda i:struct.unpack('<I',u.mem_read(sp+4+4*i,4))[0]
            ecx=u.reg_read(UC_X86_REG_ECX)
            if address==self.va(0x76d5a7):
                layer=(self.resize_layer-self.layers)//24;requested=arg(0)//4
                assert arg(0)%4==0 and 0<requested<16384
                event('A',layer,arg(0))
                ptr=0
                if self.allocation:
                    storage=self.next_storage;self.next_storage+=1;ptr=self.buffer(storage)
                    self.make_buffer(storage,layer,requested,0xb6)
                self.ret(0,ptr)
            elif address==self.va(0x76d2d5):
                storage=self.storage(arg(0));event('F',self.buffers[storage][0],storage);self.ret(0)
            elif address==self.va(0x40cd40):self.resize_layer=ecx # original successful/failed resize executes
            elif address==self.va(0x5cb100):event('I',self.identity(ecx),2) # original ground layer getter
            elif address==self.va(0x41b270):event('c',self.identity(ecx)) # actual center-coordinate getter
            elif lifecycle:self.lifecycle_service(address,sp,ecx,arg,event)
        def write(u,access,address,size,value,ctx):
            if ACTORS<=address<ACTORS+self.actor_count*0x300:
                id=(address-ACTORS)//0x300;off=(address-ACTORS)%0x300
                fields={0x80:('S',4),0x30:('N',4),0x74:('M',1),0x75:('B',1),0x76:('l',1),0x44:('a',4),0x58:('r',4),0x88:('X',4),0x8c:('Y',4),0x90:('Z',4),0xc0:('x',4),0xc4:('y',4)}
                assert off in fields and size==fields[off][1],(hex(address),size)
                assert lifecycle or off==0x80
                out=self.identity(value) if off==0x30 else value&255 if size==1 else self.signed(value)
                event(fields[off][0],id,out)
            elif self.layers<=address<self.layers+120:
                index=(address-self.layers)//24;off=(address-self.layers)%24
                fields={4:('P',4),8:('K',4),12:('v',1),13:('o',1),16:('N',4)}
                assert off in fields and size==fields[off][1],(hex(address),size)
                event(fields[off][0],index,self.storage(value) if off==4 else value&255 if size==1 else self.signed(value))
            elif BUFFERS<=address<ACTORS+0x1000000:
                storage=(address-BUFFERS)//0x10000;off=(address-BUFFERS)%0x10000
                assert storage in self.buffers and size==4 and off%4==0 and off<self.buffers[storage][1]*4,(hex(address),size)
                event('W',self.buffers[storage][0],off//4,self.identity(value))
                self.buffer_expected[storage][off:off+4]=struct.pack('<I',value&0xffffffff)
            elif lifecycle and CELLS<=address<TABLE:self.cell_write(address,size,value,event)
            elif any(p<=address<p+n for p,n in regions):raise AssertionError((hex(address),size))
        # Hook only actual service/getter entries, avoiding a Python callback for
        # every comparison instruction in the 565-actor sorted-layer sequence.
        entries=[self.va(0x76d5a7),self.va(0x76d2d5),self.va(0x40cd40),self.va(0x5cb100),self.va(0x41b270)]
        if lifecycle:entries += [self.va(0x40dc20),self.va(0x76df1a),self.va(0x41b320),self.va(0x545340),self.va(0x5453b0),
            self.va(0x4714b0),self.va(0x556f20),self.va(0x4702c0),self.va(0x564de0),self.va(0x4dfee0),self.va(0x472140),
            self.va(0x54ce60),self.va(0x562fe0),self.va(0x628aa0),self.va(0x6e1d00),self.va(0x53c3c0),self.va(0x53c400)]
        return [*[self.u.hook_add(UC_HOOK_CODE,service,begin=address,end=address) for address in entries],
                self.u.hook_add(UC_HOOK_MEM_WRITE,write)]

    def ground_adjust(self,position,first,second):
        self.u.mem_write(INPUT,struct.pack('<3i',*position)+bytes([0x4b])*44)
        before=bytes(self.u.mem_read(INPUT,56));events=[];calls=[]
        def service(u,address,size,ctx):
            if address!=self.va(0x556f20):return
            sp=u.reg_read(UC_X86_REG_ESP);ptr=struct.unpack('<I',u.mem_read(sp+4,4))[0]
            assert tuple(struct.unpack('<3i',u.mem_read(ptr,12)))==tuple(position)
            assert u.reg_read(UC_X86_REG_ECX)==self.va(0x81a800)
            events.extend(['g',*position]);calls.append(1)
            self.ret(4,first if len(calls)==1 else second)
        hook=self.u.hook_add(UC_HOOK_CODE,service)
        try:self.checked_call(self.va(0x6da9c0),[INPUT+16,INPUT],TYPES)
        finally:self.u.hook_del(hook)
        after=bytes(self.u.mem_read(INPUT,56))
        assert after[:16]==before[:16] and after[28:]==before[28:]
        assert self.u.reg_read(UC_X86_REG_EAX)==INPUT+16
        return [*struct.unpack('<3i',after[16:28]),*events]

    def lifecycle_service(self,address,sp,ecx,arg,event):
        self.service_counts[address]=self.service_counts.get(address,0)+1
        if address==self.va(0x40dc20):
            assert ecx==self.actor(self.target);self.ret(0,0)
        elif address==self.va(0x76df1a):self.ret(0,0)
        elif address==self.va(0x41b320):event('C',self.identity(ecx))
        elif address==self.va(0x545340):
            assert ecx==self.va(0x81a800)
            point=struct.unpack('<3i',self.u.mem_read(arg(0),12))
            event('O',*point) # Actual full-coordinate map lookup executes.
        elif address==self.va(0x5453b0):
            assert ecx==self.va(0x81a800)
            point=struct.unpack('<2h',self.u.mem_read(arg(0),4))
            assert point in self.cell_pointers,point
            event('L',*point) # Actual packed-coordinate map lookup executes.
        elif address==self.va(0x4714b0):
            assert ecx in self.cell_points and [arg(i) for i in range(3)]==[1,0,0]
            event('Q',1,0,0);self.ret(12,int(self.cell_allowed[self.cell_points[ecx]]))
        elif address==self.va(0x556f20):
            assert ecx==self.va(0x81a800)
            position=struct.unpack('<3i',self.u.mem_read(arg(0),12))
            point=tuple(self.signed(v)//256 if v>=0 else -((-v)//256) for v in position[:2])
            assert point in self.cell_ground,point
            if struct.unpack('<I',self.u.mem_read(sp,4))[0] in [self.va(0x6da9ea),self.va(0x6daa01)]:event('g',*position)
            self.ret(4,self.cell_ground[point])
        elif address==self.va(0x4702c0):
            assert ecx in self.cell_points and STACK-0x10000<=arg(0)<STACK
            self.ret(4,0) # Supplied flat height at caller's coordinate argument.
        elif address==self.va(0x564de0):
            assert ecx==self.va(0x81a800)
            position=struct.unpack('<3i',self.u.mem_read(arg(0),12))
            p=struct.unpack('<3i',self.u.mem_read(self.actor(self.target)+0x88,12))
            assert position==(int(p[0]/256)*256+128,int(p[1]/256)*256+128,0),position
            event('V',self.target);self.ret(4,1)
        elif address==self.va(0x4dfee0):
            assert ecx==self.va(0x81a800) and arg(0)==0
            event('R',self.target);self.ret(4)
        elif address==self.va(0x472140):
            assert ecx in self.cell_points and arg(0)==0xffffffff
            event('D',*self.cell_points[ecx]);self.ret(4)
        elif address in [self.va(0x54ce60),self.va(0x562fe0),self.va(0x628aa0)]:
            assert ecx==self.va(0x81a800)
            point=struct.unpack('<2h',self.u.mem_read(arg(0),4))
            assert point in self.cell_pointers
            event({self.va(0x54ce60):'u',self.va(0x562fe0):'t',self.va(0x628aa0):'h'}[address],*point);self.ret(4)
        elif address==self.va(0x6e1d00):
            assert ecx==self.actor(self.target) and self.u.reg_read(UC_X86_REG_EDX)&255==1
            event('!',self.target,1);self.ret(0)
        elif address==self.va(0x53c3c0):
            assert ecx==self.va(0x81a790) and arg(0)==self.actor(self.target) and arg(1)==0
            event('+',self.target);self.ret(8,1)
        elif address==self.va(0x53c400):
            assert ecx==self.va(0x81a790) and arg(0)==self.actor(self.target)
            event('-',self.target);self.ret(4,1)

    def cell_write(self,address,size,value,event):
        index=(address-CELLS)//0x200;off=(address-CELLS)%0x200
        assert index<len(self.cell_order),(hex(address),size)
        point=self.cell_order[index]
        if (off,size)==(0x122,1):event('n',*point,value&255)
        elif (off,size)==(0x124,4):event('b',*point,value&0xffffffff)
        elif (off,size)==(0x124,1):event('W',0,value&255)
        elif off in [0xe4,0xe8] and size==4:event('H',int(off==0xe8),self.identity(value))
        elif (off,size)==(0x44,4):event('e',*point,self.signed(value))
        elif (off,size)==(0x11e,1):event('f',*point,value&255)
        else:raise AssertionError((hex(address),size))

    def lifecycle(self,actors,cells,layers,steps,theater=0,enabled=1,loading=0,allocation=True,origin=(0,0)):
        self.prepare([(*a[:3],a[9]) for a in actors],layers)
        self.allocation=allocation;self.service_counts={}
        self.put(self.va(0xa283a4),loading);self.u.mem_write(self.va(0xa28588),bytes([enabled]))
        self.put(SCENARIO+0x838,theater)
        self.u.mem_write(TACTICAL,bytes([0x81])*0x200)
        self.u.mem_write(TACTICAL+0xb0,struct.pack('<2i',*origin))
        self.u.mem_write(INPUT,bytes([0x4b])*64)
        self.u.mem_write(TABLE,bytes(0x100000))
        self.cell_order=sorted(cells);self.cell_points={};self.cell_pointers={};self.cell_ground={};self.cell_allowed={}
        self.u.mem_write(CELLS,bytes([0x3c])*(len(cells)*0x200+32))
        for index,point in enumerate(self.cell_order):
            x,y=point;assert 0<=x<512 and 0<=y<512
            ground,allowed,flags,head,alt,neighbors,overlay,frame=cells[point]
            ptr=CELLS+index*0x200;self.cell_points[ptr]=point;self.cell_pointers[point]=ptr
            self.cell_ground[point]=ground;self.cell_allowed[point]=allowed
            self.put(TABLE+(y*512+x)*4,ptr);self.put(ptr+0x24,(y<<16)|x)
            self.put(ptr+0x124,flags);self.put(ptr+0xe4,self.actor(head));self.put(ptr+0xe8,self.actor(alt))
            self.u.mem_write(ptr+0x122,bytes([neighbors]));self.put(ptr+0x44,overlay)
            self.u.mem_write(ptr+0x11e,bytes([frame]));self.put(ptr+0x140,0)
        for id,a in enumerate(actors):
            x,y,z,temperate,snow,nxt,onMap,redraw,limbo,last,active,logic,vein,countA,countB,sx,sy=a
            ptr=self.actor(id);t=TYPES+id*0x300
            self.put(ptr+0x30,self.actor(nxt));self.u.mem_write(ptr+0x74,bytes([onMap,redraw,limbo]))
            self.u.mem_write(ptr+0x77,bytes(3));self.u.mem_write(ptr+0x7d,bytes([active]))
            self.put(ptr+0x94,0);self.put(ptr+0x44,countA);self.put(ptr+0x58,countB)
            self.u.mem_write(ptr+0xc0,struct.pack('<2i',sx,sy))
            self.put(t+0x278,temperate);self.put(t+0x27c,snow)
            self.put(t+0xac,0);self.u.mem_write(t+0x204,bytes([logic,1]))
            self.u.mem_write(t+0x20a,b'\0');self.u.mem_write(t+0x280,bytes([0,vein]))
        regions=[(ACTORS,len(actors)*0x300+32),(TYPES,len(actors)*0x300+32),
                 (CELLS,len(cells)*0x200+32),(TABLE,0x100000),(self.layers,120),
                 (SCENARIO,0x900),(TACTICAL,0x200),(INPUT,64)]
        before=[bytes(self.u.mem_read(p,n)) for p,n in regions]
        hooks=self.hooks(regions,lifecycle=True);results=[]
        try:
            for action,id,position in steps:
                self.target=id
                if action=='U':
                    self.u.mem_write(INPUT,struct.pack('<3i',*position))
                    self.checked_call(self.va(0x6d9940),[INPUT,0],self.actor(id))
                elif action=='R':self.checked_call(self.va(0x6d9290),[],self.actor(id))
                else:raise ValueError(action)
                results.append(self.u.reg_read(UC_X86_REG_EAX)&255)
        finally:
            for hook in hooks:self.u.hook_del(hook)
        for (ptr,size),old in zip(regions,before):
            after=bytearray(self.u.mem_read(ptr,size));old=bytearray(old)
            mutable=[]
            if ptr==ACTORS:
                mutable=[(id*0x300+off,n) for id in range(len(actors)) for off,n in
                         [(0x30,4),(0x74,3),(0x80,4),(0x44,4),(0x58,4),(0x88,12),(0xc0,8)]]
            elif ptr==CELLS:
                mutable=[(id*0x200+off,n) for id in range(len(cells)) for off,n in
                         [(0xe4,8),(0x122,1),(0x124,4),(0x44,4),(0x11e,1)]]
            elif ptr==self.layers:mutable=[(id*24+off,n) for id in range(5) for off,n in [(4,10),(16,4)]]
            elif ptr==INPUT:mutable=[(0,12)] # host writes each root input
            for off,n in mutable:after[off:off+n]=old[off:off+n]
            assert after==old,hex(ptr)
        self.audit_buffers()
        for id in range(len(actors)):
            ptr=self.actor(id)
            results.extend(struct.unpack('<3i',self.u.mem_read(ptr+0x88,12)))
            results.append(self.identity(struct.unpack('<I',self.u.mem_read(ptr+0x30,4))[0]))
            results.extend(self.u.mem_read(ptr+0x74,3))
            for off in [0x44,0x58,0xc0,0xc4]:results.append(struct.unpack('<i',self.u.mem_read(ptr+off,4))[0])
        for point in self.cell_order:
            ptr=self.cell_pointers[point]
            results.extend([struct.unpack('<I',self.u.mem_read(ptr+0x124,4))[0],
                            self.identity(struct.unpack('<I',self.u.mem_read(ptr+0xe4,4))[0]),
                            self.identity(struct.unpack('<I',self.u.mem_read(ptr+0xe8,4))[0]),
                            self.u.mem_read(ptr+0x122,1)[0],struct.unpack('<i',self.u.mem_read(ptr+0x44,4))[0],
                            self.u.mem_read(ptr+0x11e,1)[0]])
        return [*results,*self.layer_result(len(actors)),*self.events]
