# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete resource subtype/list/INI instructions around declared services."""
import hashlib,struct
from original_presentation import PresentationOracle,STACK,OBJ
from original_foot_lit import words,ret
from original_land_characteristics import push_double
from verify_resource_type_inputs import verify,RANGES,KEYS
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_ECX,UC_X86_REG_ESP,UC_X86_REG_EAX,UC_X86_REG_FPTAG,UC_X86_REG_FPSW
ARENA=0x2300000;BUFFERS=ARENA+0x40000;VTABLE=ARENA+0x50000;GROW=VTABLE+0x1000
OVERLAYS=ARENA+0x80000;TOKENS=ARENA+0x60000;VECTORS=ARENA+0x100000
REGISTRIES=(0xac0b30,0xac0cb0)
FIELDS=((0x98,4),(0x9c,4),(0xa0,8),(0xa8,4),(0xb0,8),(0xb8,4),(0xbc,4),(0xc0,4),
 (0xc8,4),(0xcc,4),(0xd1,1),(0xd4,4),(0xd8,4),(0xdc,4),(0xe0,4),(0xe4,4),(0xe8,4),(0xec,4),*[(o,4) for o in range(0xf0,0x128,4)])
INT_KEYS=('Spread','Growth','Value','Power','Color','Image')
def pack(v):return b''.join(struct.pack('<I',n&0xffffffff) for n in v)
def digest(v):return hashlib.sha256(pack(v)).hexdigest()
def text(v,s):v.extend([len(s),*s.encode('ascii')])
def decode(s):return '' if s=='-' else s
def initial(seed,h):
    v=((h+1)*2654435761+seed*2246822519)&0xffffffff
    return [v,v^0x12345678,((0x3fd00000+(h%3))<<32)|v,v^0x87654321,
      ((0xbfe00000+(h%3))<<32)|v,(v+1)&0xffffffff,(v+2)&0xffffffff,(v+3)&0xffffffff,
      h*3+3,4,h&1,2,v,v^0xabcdef01,(h+153)%256+1,(v+4)&0xffffffff,(v+5)&0xffffffff,(v+6)&0xffffffff,
      *[(v+i*37)&0xffffffff for i in range(14)]]
def profile(tokens):
    v=list(map(int,tokens[:13]));v.append(decode(tokens[13]));return v
class ResourceTypeInputOracle(PresentationOracle):
    def __init__(self,exe):
        self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True)
        self.u.mem_map(ARENA,0x200000);self.u.hook_add(UC_HOOK_CODE,self.code)
        self.roots={hex(a):0 for a in RANGES};self.stores=self.services=0;self.image_branches={}
    def va(self,a):return a
    def pointer(self,h):return ARENA+h*512
    def handle(self,p):
        if not p:return 0xffffffff
        assert ARENA<=p<ARENA+512*512 and (p-ARENA)%512==0
        return (p-ARENA)//512
    def vector_pointer(self,id):return VECTORS+id*256 if id else 0
    def vector_id(self,p):
        if not p:return 0
        assert VECTORS<=p<VECTORS+0x80000 and (p-VECTORS)%256==0
        return (p-VECTORS)//256
    def string(self,p):
        assert STACK-0x2000<=p<STACK or ARENA<=p<ARENA+0x200000 or OBJ<=p<OBJ+0x60000 or 0x400000<=p<0xb00000
        b=bytes(self.u.mem_read(p,256));assert b'\0' in b;return b.split(b'\0')[0].decode('ascii')
    def write_string(self,p,s,size):assert len(s)<size;self.u.mem_write(p,s.encode()+b'\0')
    def vector(self,p):
        buffer,capacity=words(self.u,p+4,2);owns=self.u.mem_read(p+13,1)[0];count,growth,extra=words(self.u,p+16,3)
        assert count<=capacity<=32
        return [self.vector_id(buffer),capacity,owns,count,growth,extra,list(words(self.u,buffer,count)) if count else []]
    def put_vector(self,p,v):
        buffer,capacity,owns,count,growth,extra,items=v
        self.put(p+4,self.vector_pointer(buffer));self.put(p+8,capacity);self.u.mem_write(p+13,bytes([owns]));
        self.put(p+16,count);self.put(p+20,growth);self.put(p+24,extra)
        if buffer:self.u.mem_write(self.vector_pointer(buffer),pack(items))
    def event_vector(self,tag,h,v):self.events.extend([tag,h,*v[:6],len(v[6]),*v[6]])
    def ini_profile(self):return self.config if self.op=='I' else self.entries[self.current][4]
    def code(self,u,a,n,ctx):
        if a in RANGES:self.roots[hex(a)]+=1
        if a==0x6e8d30:self.ini_handle=self.handle(u.reg_read(UC_X86_REG_ECX))
        if a in (0x6e8fb3,0x6e8f33,0x6e8f5f,0x6e8f73,0x6e8f87):self.image_branches[hex(a)]=self.image_branches.get(hex(a),0)+1
        if any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()):return
        self.services+=1;sp=u.reg_read(UC_X86_REG_ESP);receiver=u.reg_read(UC_X86_REG_ECX);caller=words(u,sp,1)[0]
        assert any(lo<=caller<lo+size for lo,size in RANGES.items()),hex(caller)
        if a==0x410580:
            h=self.handle(receiver);id=self.string(words(u,sp+4,1)[0]);self.used.add(h);self.events.extend([0,h]);text(self.events,id)
            self.write_string(receiver+0x24,id,25);ret(u,4,receiver)
        elif a==0x50b860:
            h=self.handle(receiver-0xc4);assert words(u,sp+4,2)==[0,0];self.events.extend([2,h]);self.put_vector(receiver,[0,0,1,0,0,0,[]]);ret(u,8,receiver)
        elif a==0x50b110:
            h=self.handle(receiver-0xc4);self.events.extend([3,h]);self.put(receiver+16,0);ret(u,0)
        elif a in (GROW,GROW+16):
            role=(a-GROW)//16;assert receiver==REGISTRIES[role];amount,zero=words(u,sp+4,2);assert zero==0 and 0<=amount<=512
            self.events.extend([4,role+1,amount,self.success[role]])
            if self.success[role]&255:self.put(receiver+8,amount)
            ret(u,8,self.success[role])
        elif a==0x4107e0:
            h=self.handle(receiver);self.ini_handle=h;assert words(u,sp+4,1)==[OBJ]
            base=self.ini_profile()[0];self.events.extend([10,h,base]);ret(u,4,base)
        elif a in (0x50d7f0,0x469f50,0x50e3a0):
            assert receiver==OBJ;h=self.ini_handle;section,key=words(u,sp+4,2);key=KEYS[key]
            assert self.string(section)==self.string(self.pointer(h)+0x24)
            conf=self.ini_profile();mask=conf[1];self.events.extend([11 if a!=0x50e3a0 else 12,h]);text(self.events,key)
            if a==0x50e3a0:
                # Direct register injection defines this supplied result service.
                # Signaling-NaN transfers here are emulator diagnostics, not proof
                # of original parser/CRT or physical x87 exception/quieting rules.
                low,high=words(u,sp+12,2);i=('SpreadPercentage','GrowthPercentage').index(key)
                value=(conf[8+i*2]|(conf[9+i*2]<<32)) if mask&(1<<(6+i)) else low|(high<<32)
                self.events.extend([low,high,value&0xffffffff,value>>32]);push_double(u,value);ret(u,16,0)
            else:
                default=words(u,sp+12,1)[0];i=INT_KEYS.index(key);assert (a==0x469f50)==(key=='Color')
                value=conf[2+i] if mask&(1<<i) else default;self.events.extend([default,value]);ret(u,12,value)
        elif a==0x50e9a0:
            assert receiver==OBJ;section,key,default,out,size=words(u,sp+4,5);assert self.string(default)=='' and STACK-0x2000<=out and out+size<=STACK
            if self.op=='L' and size==24:
                assert self.string(section)=='Tiberiums' and self.string(key)==self.entries[self.current][0]
                _,_,length,value,_=self.entries[self.current];self.events.extend([8,self.current,length&0xffffffff]);text(self.events,value)
            else:
                assert size==128 and self.string(section)==self.string(self.pointer(self.ini_handle)+0x24) and self.string(key)=='Debris'
                length,value=self.ini_profile()[12:];self.events.extend([13,self.ini_handle,length&0xffffffff]);text(self.events,value)
            self.write_string(out,value,size);ret(u,20,length)
        elif a==0x50b480:
            assert words(u,sp+4,2)==[0,0] and STACK-0x2000<=receiver<STACK;h=self.ini_handle
            self.parsed=receiver;v=[h*3+1,4,1,0,3,9,[]];self.event_vector(14,h,v);self.put_vector(receiver,v);ret(u,8,receiver)
        elif a==0x782ec2:
            source,delimiters=words(u,sp+4,2);assert self.string(delimiters)==',';h=self.ini_handle
            if source:self.tokens=[part for part in self.string(source).split(',') if part];self.token_index=0
            item=self.tokens[self.token_index] if self.token_index<len(self.tokens) else None;self.token_index+=1
            self.events.extend([15,h,int(bool(source)),int(item is not None)])
            if item is not None:text(self.events,item);self.write_string(TOKENS,item,128)
            ret(u,0,TOKENS if item is not None else 0)
        elif a==0x4264a0:
            h=self.ini_handle;token=self.string(receiver);value=0 if token=='MISSING' else (sum(token.encode())*17+self.seed)&0xffffffff
            self.events.extend([16,h]);text(self.events,token);self.events.append(value);ret(u,0,value)
        elif a==0x50b590:
            assert receiver==self.parsed;h=self.ini_handle;value=words(u,words(u,sp+4,1)[0],1)[0]
            self.events.extend([17,h,value]);v=self.vector(receiver);v[6].append(value);v[3]+=1;v[1]=max(v[1],v[3]);self.put_vector(receiver,v);ret(u,4,1)
        elif a==0x50b7d0:
            source=words(u,sp+4,1)[0];h=self.ini_handle;v=self.vector(source);self.event_vector(18,h,v)
            v[0]=h*3+2 if v[1] else 0;v[2]=1;self.copy=receiver;self.put_vector(receiver,v);ret(u,4,receiver)
        elif a==0x50b3f0:
            assert receiver==self.parsed;self.events.extend([19,self.ini_handle,self.vector(receiver)[0]]);ret(u,0)
        elif a==0x6534d0:
            h=self.ini_handle;source=words(u,sp+4,1)[0];assert source==self.copy and receiver==self.pointer(h)+0xc4
            v=self.vector(source);self.event_vector(22,h,v)
            self.put(receiver+4,self.vector_pointer(h*3+3) if v[0] else 0);self.put(receiver+8,v[1]);self.u.mem_write(receiver+13,b'\1')
            if v[6]:self.u.mem_write(self.vector_pointer(h*3+3),pack(v[6]))
            ret(u,4,receiver)
        elif a==0x781d3b:
            id=self.vector_id(words(u,sp+4,1)[0]);assert id==self.ini_handle*3+2
            self.events.extend([23,self.ini_handle,id]);ret(u,0)
        elif a==0x50cb00:
            assert receiver==OBJ and self.string(words(u,sp+4,1)[0])=='Tiberiums';self.events.extend([5,self.list_count&0xffffffff]);ret(u,4,self.list_count)
        elif a==0x50ce00:
            section,index=words(u,sp+4,2);assert receiver==OBJ and self.string(section)=='Tiberiums' and index<len(self.entries)
            self.current=index;key=self.entries[index][0];self.events.extend([6,index]);text(self.events,key);self.write_string(OBJ+0x1000,key,64);ret(u,8,OBJ+0x1000)
        elif a==0x782dfd:
            key=self.string(words(u,sp+4,1)[0]);assert key==self.entries[self.current][0];value=self.entries[self.current][1]
            self.events.append(7);text(self.events,key);self.events.append(value&0xffffffff);ret(u,0,value)
        elif a==0x782017:
            assert words(u,sp+4,1)==[0x128];h=8+self.attempts;self.attempts+=1;assert h<512
            self.used.add(h);self.events.extend([9,h]);ret(u,0,self.pointer(h))
        else:raise AssertionError(f'Uninspected resource input instruction {a:#x}')
    def run(self,op,tokens):
        self.op=op;self.seed=int(tokens[0]);self.events=[];self.used=set();self.attempts=0;u=self.u
        u.mem_write(ARENA,b'\xa5'*0x40000);u.mem_write(BUFFERS,bytes(0x2000));u.mem_write(VECTORS,b'\xd8'*0x80000)
        for h in range(512):
            p=self.pointer(h);self.put(p,0x7ad8b0)
            for (off,n),v in zip(FIELDS,initial(self.seed,h)):
                if off==0xc8:v=self.vector_pointer(v)
                if off==0xe0:v=OVERLAYS+(v-1)*1024
                u.mem_write(p+off,v.to_bytes(n,'little'))
            self.write_string(p+0x24,'Existing'+str(h),25)
            u.mem_write(self.vector_pointer(h*3+3),pack([h+11,h+22]))
        for i in range(256):self.put(OVERLAYS+i*1024+0x264,i)
        self.put(0xa35dec,OVERLAYS+0x40000)
        for i in range(256):self.put(OVERLAYS+0x40000+i*4,OVERLAYS+i*1024)
        self.put(0xa40d2c,self.seed);self.put(VTABLE+8,GROW);self.put(VTABLE+40,GROW+16)
        args=[];receiver=OBJ;self.success=[0,0]
        if op=='I':self.config=profile(tokens[1:]);self.used.add(0);root=0x6e8d30;args=[OBJ];receiver=ARENA
        else:
            at=1
            for role,reg in enumerate(REGISTRIES):
                capacity,owns,growth,success,count=map(int,tokens[at:at+5]);at+=5;handles=list(map(int,tokens[at:at+count]));at+=count
                self.success[role]=success;self.used.update(handles)
                u.mem_write(reg,pack([VTABLE+role*32,BUFFERS+role*0x1000,capacity,0,count,growth]));u.mem_write(reg+13,bytes([owns]))
                for i,h in enumerate(handles):self.put(BUFFERS+role*0x1000+i*4,self.pointer(h))
            if op=='C':
                h=int(tokens[at]);self.used.add(h);self.write_string(OBJ+0x2000,decode(tokens[at+1]),25)
                root=0x6e89a0;args=[OBJ+0x2000];receiver=self.pointer(h)
            else:
                assert op=='L';self.list_count=int(tokens[at]);at+=1;self.entries=[]
                for i in range(max(0,self.list_count)):
                    key=tokens[at];index,length=map(int,tokens[at+1:at+3]);value=decode(tokens[at+3]);conf=profile(tokens[at+4:at+18]);at+=18
                    self.entries.append((key,index,length,value,conf))
                assert at==len(tokens);root=0x6e8ff0;receiver=OBJ
        before=bytes(u.mem_read(ARENA,0x40000));u.reg_write(UC_X86_REG_FPSW,0);u.reg_write(UC_X86_REG_FPTAG,0xffff)
        def stores(u,access,p,n,value,ctx):
            value&=(1<<(8*n))-1
            if ARENA<=p<ARENA+0x40000:
                h,off=divmod(p-ARENA,512)
                if off<16:assert n==4;return
                assert (off,n) in FIELDS or (off,n) in ((0xa0,4),(0xa4,4),(0xb0,4),(0xb4,4),(0xc4,4)),(hex(p),n)
                if off==0xc4:assert value==0x7a3b3c;return
                if off==0xe0:assert not value or OVERLAYS<=value<OVERLAYS+256*1024;value=(value-OVERLAYS)//1024+1 if value else 0
                self.events.extend([20,h,off,n,value&0xffffffff,value>>32]);self.stores+=1
            elif any(reg<=p<reg+24 for reg in REGISTRIES):
                role=next(i for i,reg in enumerate(REGISTRIES) if reg<=p<reg+24);assert p==REGISTRIES[role]+16 and n==4
                self.events.extend([21,role+1,0,value]);self.stores+=1
            elif BUFFERS<=p<BUFFERS+0x2000:
                role=(p-BUFFERS)//0x1000;slot=(p-BUFFERS)%0x1000//4;assert n==4 and slot<words(u,REGISTRIES[role]+8,1)[0]
                self.events.extend([21,role+1,slot+1,self.handle(value)]);self.stores+=1
        hook=u.hook_add(UC_HOOK_MEM_WRITE,stores)
        try:self.checked_call(root,args,receiver,writes=[(ARENA,0x40000),(BUFFERS,0x2000),*[(p,24) for p in REGISTRIES]],
            inputs=[(VTABLE,64),(OVERLAYS,0x40400),(0xa35dec,4),(0xa40d2c,4),(0x6e8fd0,24),(0x7ad8b0,0x68),
              (0x7a3b3c,28),*[(p,len(s)+1) for p,s in KEYS.items()]])
        finally:u.hook_del(hook)
        assert (u.reg_read(UC_X86_REG_FPSW)>>11)&7==0 and u.reg_read(UC_X86_REG_FPTAG)==0xffff
        result=u.reg_read(UC_X86_REG_EAX)&0xffffffff;result=self.handle(result) if op=='C' else result&255
        after=bytearray(u.mem_read(ARENA,0x40000))
        for h in self.used:
            for off,n in (*FIELDS,(0,16),(0x24,25),(0xc4,4)):
                start=h*512+off;after[start:start+n]=before[start:start+n]
        assert bytes(after)==before,'Nonselected resource bytes changed'
        state=[]
        for role,reg in enumerate(REGISTRIES):
            cap=words(u,reg+8,1)[0] if op!='I' else 0;count=words(u,reg+16,1)[0] if op!='I' else 0
            owns=u.mem_read(reg+13,1)[0] if op!='I' else 1
            state.extend([count,cap,owns,*[self.handle(p) for p in words(u,BUFFERS+role*0x1000,cap)]])
            assert bytes(u.mem_read(BUFFERS+role*0x1000+cap*4,0x1000-cap*4))==bytes(0x1000-cap*4)
        for h in sorted(self.used):
            p=self.pointer(h);state.append(h)
            for off,n in FIELDS:
                value=int.from_bytes(u.mem_read(p+off,n),'little')
                if off==0xc8:value=self.vector_id(value)
                if off==0xe0:value=(value-OVERLAYS)//1024+1 if value else 0
                state.extend([value&0xffffffff,value>>32])
            text(state,self.string(p+0x24));v=self.vector(p+0xc4);state.extend([len(v[6]),*v[6]])
        self.last_state=state;self.last_events=self.events
        return list(map(str,[result,digest(state),digest(self.events)]))
