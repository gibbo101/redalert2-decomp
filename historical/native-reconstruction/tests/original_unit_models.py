# SPDX-License-Identifier: GPL-3.0-or-later
"""Unchanged complete original model root; bounded file/heap/parser services."""
import struct
from original_presentation import PresentationOracle,STACK
from original_foot_lit import words,ret,signed
from verify_unit_models import verify,RANGES
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_ECX,UC_X86_REG_ESP
ARENA=0x2400000;TYPE=ARENA;SIZE=0x20000
def model(h):return ARENA+0x4000+h*0x100 if h else 0
def token(p):
    if not p:return 0
    if ARENA+0x4100<=p<=ARENA+0x4c00 and (p-ARENA-0x4000)%0x100==0:return (p-ARENA-0x4000)//0x100
    if ARENA+0x1e000<=p<=ARENA+0x1e300 and (p-ARENA-0x1e000)%0x100==0:return 100+(p-ARENA-0x1e000)//0x100
    raise AssertionError(f'Unexpected model/cache pointer {p:#x}')
def cache(h):return ARENA+0x1e000+(h-100)*0x100 if h else 0
class UnitModelOracle(PresentationOracle):
    def __init__(self,exe):
        verify(exe.read_bytes());super().__init__(exe,allow_patched=True)
        self.u.mem_map(ARENA,SIZE);self.active=False;self.service_writes=0;self.section_calls=0
        self.kinds=0;self.multiples=0;self.store_count=0;self.service_calls=0
        self.u.hook_add(UC_HOOK_CODE,self.route)
    def va(self,a):return a
    def text(self,p):
        b=bytes(self.u.mem_read(p,80));assert b'\0' in b;return b.split(b'\0',1)[0].decode('ascii')
    def event(self,*v):self.events.extend(v)
    def host_stack(self,p,b):
        assert STACK-0x2000<=p and p+len(b)<=STACK
        self.u.mem_write(p,b);self.service_writes+=1
    def route(self,u,a,n,ctx):
        if not self.active:return
        services={0x7831f0,0x7820f4,0x468f50,0x4691a0,0x438410,0x42f350,
                  0x7190c0,0x59eba0,0x781d3b,0x782017,0x719080,0x59eb70,0x59ed30}
        assert a in services or any(start<=a<start+size for start,size in RANGES.items()),f'Unmodeled original execution {a:#x}'
        sp=u.reg_read(UC_X86_REG_ESP);ecx=u.reg_read(UC_X86_REG_ECX)
        if a==0x70b5e0:
            assert ecx==TYPE;self.event('kind');self.kinds+=1;return
        if a==0x6df680:
            assert ecx==TYPE;self.event('multiple');self.multiples+=1;return
        if a==0x719860:
            index,zero=words(u,sp+4,2);h=token(ecx)
            assert h and zero==0 and index<self.count
            self.event('section',h,index);self.section_calls+=1;return
        if a==0x7831f0:
            out,drive,directory,stem,extension=words(u,sp+4,5)
            assert drive==directory==0 and self.text(extension) in ('.VXL','.HVA')
            value=self.text(stem)+self.text(extension);self.host_stack(out,value.encode()+b'\0');ret(u,0);self.service_calls+=1
        elif a==0x7820f4:
            out,fmt,stem=words(u,sp+4,3);form=self.text(fmt)
            assert form in ('%sTUR','%sBARL') and stem==TYPE+0x1c8
            value=self.text(stem)+form[2:];self.host_stack(out,value.encode()+b'\0');ret(u,0,len(value));self.service_calls+=1
        elif a==0x468f50:
            name=self.text(words(u,sp+4,1)[0]);part=0
            if name.startswith(self.image+'TUR.'):part=1
            elif name.startswith(self.image+'BARL.'):part=2
            assert name in [self.image+s+e for s in ('','TUR','BARL') for e in ('.VXL','.HVA')]
            # Stack addresses are reused; file IDs count constructions, not slots.
            self.file_count+=1;f=self.file_count;self.files[ecx]=(f,part*2+int(name.endswith('.HVA')))
            self.event('open',name,f);ret(u,4,ecx);self.service_calls+=1
        elif a==0x4691a0:
            assert words(u,sp+4,1)==[0];f,slot=self.files[ecx];assert slot%2==0
            self.allocating=slot;self.event('available',f);ret(u,4,self.available[slot//2]);self.service_calls+=1
        elif a==0x438410:
            p=ecx-0x54;assert p in self.files
            assert words(u,p,1)==[0x79a6a0] and words(u,p+0x60,1)==[0]
            self.closing=p;ret(u,0);self.service_calls+=1
        elif a==0x42f350:
            assert self.closing==ecx and words(u,ecx,1)==[0x79a658]
            self.event('close',self.files[ecx][0]);self.closing=None;ret(u,0);self.service_calls+=1
        elif a in (0x7190c0,0x59eba0):
            self.event('destroy',int(a==0x59eba0),token(ecx));ret(u,0);self.service_calls+=1
        elif a==0x781d3b:
            self.event('free',token(words(u,sp+4,1)[0]));ret(u,0);self.service_calls+=1
        elif a==0x782017:
            length=words(u,sp+4,1)[0];assert length in (28,16)
            k=int(length==16);slot=self.allocating+k;h=7+slot if self.allocmask&(1<<slot) else 0
            self.event('allocate',k,h);ret(u,0,model(h));self.service_calls+=1
        elif a in (0x719080,0x59eb70):
            k=int(a==0x59eb70);file=words(u,sp+4,1)[0];f,slot=self.files[file]
            if not k:assert words(u,sp+8,1)==[0]
            assert token(ecx)==7+slot and slot%2==k
            self.event('construct',k,token(ecx),f,'previous',token(words(u,TYPE+0xb0+slot*4,1)[0]))
            ret(u,4 if k else 8,ecx);self.service_calls+=1
        elif a==0x59ed30:
            h=token(ecx);value=words(u,sp+4,1)[0];assert value==0x100000+h-1
            self.event('associate',h,value);ret(u,4);self.service_calls+=1
    def run(self,image,oldmask,available,allocmask,errors,dimensions,maximum,seed):
        self.image=image;self.available=available;self.allocmask=allocmask;self.count=len(dimensions)
        self.u.mem_write(ARENA,b'\xa7'*SIZE);self.put(TYPE,0x7ae328)
        self.u.mem_write(TYPE+0x1c8,image.encode()+b'\0');self.u.mem_write(TYPE+0xaab,b'\x01');self.put(TYPE+0x704,0)
        fields={}
        for i in range(6):self.put(TYPE+0xb0+i*4,model(1+i) if oldmask&(1<<i) else 0);fields[0xb0+i*4]=4
        self.put(TYPE+0x1bc,maximum);fields[0x1bc]=4
        for i in range(4):
            p=TYPE+0x214+i*20;self.put(p,cache(100+i) if seed&(1<<i) else 0)
            self.put(p+4,seed+i);self.put(p+8,~seed-i);self.u.mem_write(p+12,bytes([(seed+i)&255]));self.put(p+16,seed^i)
            for j in (0,4,8,12,16):fields[p-TYPE+j]=1 if j==12 else 4
        for h in range(1,13):
            p=model(h);table=ARENA+0x6000+h*0x80;data=ARENA+0x8000+h*0x1000
            self.u.mem_write(p,bytes([errors[h-7]&255 if h>=7 else 0]));self.put(p+4,self.count)
            self.put(p+0x10,table);self.put(p+0x14,data)
            for i,d in enumerate(dimensions):
                self.put(table+i*12,i);self.put(data+i*164+0xc,0x100000+h)
                self.u.mem_write(data+i*164+0xa0,bytes(d))
        self.events=[];self.files={};self.file_count=0;self.closing=None;self.allocating=-1
        before=bytes(self.u.mem_read(ARENA,SIZE));expected=bytearray(before)
        def store(u,access,p,n,value,ctx):
            if not ARENA<=p<ARENA+SIZE:return
            off=p-TYPE;assert fields.get(off)==n
            expected[off:off+n]=int(value).to_bytes(n,'little')
            translated=token(value) if off in (0xb0,0xb4,0xb8,0xbc,0xc0,0xc4) or off in (0x214,0x228,0x23c,0x250) else value
            self.event('store',off,n,translated);self.store_count+=1
        hook=self.u.hook_add(UC_HOOK_MEM_WRITE,store);self.active=True
        try:self.checked_call(0x5d6730,ecx=TYPE,writes=[(TYPE+off,n) for off,n in fields.items()])
        finally:self.active=False;self.u.hook_del(hook)
        assert bytes(self.u.mem_read(ARENA,SIZE))==bytes(expected)
        self.event('state',*[token(x) for x in words(self.u,TYPE+0xb0,6)],signed(words(self.u,TYPE+0x1bc,1)[0]))
        for i in range(4):
            p=TYPE+0x214+i*20;v=words(self.u,p,3)
            self.event(token(v[0]),*v[1:],self.u.mem_read(p+12,1)[0],words(self.u,p+16,1)[0])
        return self.events
