# SPDX-License-Identifier: GPL-3.0-or-later
"""Unchanged complete overlay roots, with explicit base/INI/CRT/file/heap services."""
import hashlib,struct
from original_presentation import PresentationOracle,STACK,OBJ
from original_foot_lit import words,ret
from verify_overlay_type_inputs import verify,RANGES,KEYS
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_ECX,UC_X86_REG_EAX,UC_X86_REG_ESP
ARENA=0x2300000;BUFFER=0x2380000;VTABLE=BUFFER+0x1000;GROW=BUFFER+0x2000;REGISTRY=0xa35de8
FIELDS=((0x264,4),(0x268,4),(0x26c,4),(0x270,4),(0x274,4),(0x9c,4),(0xa4,4),
 (0x1fc,1),(0x1fd,1),(0x1ff,1),(0x200,1),(0x202,1),(0x205,1),
 *[(i,1) for i in range(0x278,0x286)])
BOOL_KEYS=['Wall','Tiberium','Crate','CrateTrigger','Explodes','Overrides','DemandLoad',
 'NoUseTileLandType','IsVeinholeMonster','IsVeins','ChainReaction','DrawFlat','IsARock','IsRubble']
def pack(values):return b''.join(struct.pack('<I',v&0xffffffff) for v in values)
def digest(values):return hashlib.sha256(pack(values)).hexdigest()
def text(values,s):values.extend([len(s),*s.encode('ascii')])
def initial(seed,h):
    v=((h+1)*2654435761+seed*2246822519)&0xffffffff
    return [v,v^0x12345678,v^0x87654321,(v+1)&0xffffffff,(v+2)&0xffffffff,(v+3)&0xffffffff,(v+4)&0xffffffff,
      *[(v+i*37)&255 for i in range(20)]]
def decode(s):return '' if s=='-' else s
class OverlayTypeInputOracle(PresentationOracle):
    def __init__(self,exe):
        self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True)
        self.u.mem_map(ARENA,0x90000);self.u.hook_add(UC_HOOK_CODE,self.code)
        self.roots={hex(a):0 for a in RANGES};self.stores=self.services=0
    def va(self,a):return a
    def pointer(self,h):return ARENA+h*1024
    def handle(self,p):
        if not p:return 0xffffffff
        assert ARENA<=p<ARENA+512*1024 and (p-ARENA)%1024==0
        return (p-ARENA)//1024
    def string(self,p):
        assert ARENA<=p<ARENA+0x90000 or OBJ<=p<OBJ+0x60000 or 0x400000<=p<0xb00000
        blob=bytes(self.u.mem_read(p,256));assert b'\0' in blob
        return blob.split(b'\0')[0].decode('ascii')
    def write_string(self,p,s,size):
        blob=s.encode('ascii');assert len(blob)<size
        self.u.mem_write(p,blob+b'\0')
    def code(self,u,a,n,ctx):
        if a in RANGES:self.roots[hex(a)]+=1
        if any(lo<=a and a+n<=lo+size for lo,size in RANGES.items()):return
        self.services+=1;sp=u.reg_read(UC_X86_REG_ESP);receiver=u.reg_read(UC_X86_REG_ECX)
        caller=words(u,sp,1)[0];assert any(lo<=caller<lo+size for lo,size in RANGES.items())
        if a==0x5d57f0:
            assert caller==0x5dc5ae
            h=self.handle(receiver);id=self.string(words(u,sp+4,1)[0]);self.events.extend([0,h]);text(self.events,id)
            self.write_string(receiver+0x24,id,64);self.write_string(receiver+0x1c8,id[:24],25)
            ret(u,4,receiver)
        elif a==0x5d7810:
            assert caller==0x5dcab7
            assert receiver==ARENA and words(u,sp+4,1)==[OBJ]
            self.events.extend([10,0,self.base&0xffffffff]);ret(u,4,self.base&0xffffffff)
        elif a in (0x46a970,0x50d7f0,0x50f410):
            section,key,default=words(u,sp+4,3);assert key in KEYS;key=KEYS[key]
            art=receiver==0x8397f0;assert receiver in (OBJ,0x8397f0)
            assert self.string(section)==self.string(ARENA+(0x1c8 if art else 0x24))
            if a==0x50f410:
                i=BOOL_KEYS.index(key);default&=255;result=self.flags[i] if self.mask&(1<<(i+3)) else default;tag=12
                assert art==(key=='DemandLoad')
            else:
                i=['Land','Strength','DamageLevels'].index(key);result=self.integers[i] if self.mask&(1<<i) else default;tag=11
                assert art==(key=='DamageLevels') and (a==0x46a970)==(key=='Land')
            self.events.extend([tag,int(art)]);text(self.events,key);self.events.extend([default,result]);ret(u,12,result)
        elif a==0x7831f0:
            output,drive,directory,filename,ext=words(u,sp+4,5)
            assert drive==directory==0 and self.string(ext)=='.SHP' and STACK-0x2000<=output<STACK-256
            self.write_string(output,self.string(filename)+'.SHP',256);ret(u,0,0)
        elif a==0x5956c0:
            assert STACK-0x2000<=receiver<STACK-256
            name=self.string(receiver);self.events.append(16);text(self.events,name);self.events.append(self.image);ret(u,0,self.image)
        elif a==0x4264a0:
            assert STACK-0x2000<=receiver<STACK-128
            self.events.append(14);text(self.events,self.string(receiver));self.events.append(self.animation);ret(u,0,self.animation)
        elif a==0x50cb00:
            assert receiver==OBJ and self.string(words(u,sp+4,1)[0])=='OverlayTypes'
            self.events.extend([4,self.list_count&0xffffffff]);ret(u,4,self.list_count&0xffffffff)
        elif a==0x50ce00:
            section,index=words(u,sp+4,2);assert receiver==OBJ and self.string(section)=='OverlayTypes' and index<len(self.entries)
            self.current=index;self.write_string(OBJ+0x1000,str(index+1),64);ret(u,8,OBJ+0x1000)
        elif a==0x50e9a0:
            section,key,default,output,size=words(u,sp+4,5)
            assert receiver==OBJ and self.string(default)=='' and STACK-0x2000<=output and output+size<=STACK
            if self.op=='L':
                assert self.string(section)=='OverlayTypes' and self.string(key)==str(self.current+1) and size==32
                length,s=self.entries[self.current];self.events.extend([5,self.current,length&0xffffffff]);text(self.events,s)
            else:
                assert self.string(section)==self.string(ARENA+0x24) and self.string(key)=='CellAnim' and size==128
                length,s=self.length,self.text;self.events.extend([13,length&0xffffffff]);text(self.events,s)
            self.write_string(output,s,size);ret(u,20,length&0xffffffff)
        elif a==0x781f20:
            first,second=words(u,sp+4,2);x,y=self.string(first),self.string(second);equal=x.lower()==y.lower()
            self.events.append(3);text(self.events,x);text(self.events,y);self.events.append(int(equal));ret(u,0,0 if equal else 1)
        elif a==0x782017:
            assert caller==0x5dcfd0
            assert words(u,sp+4,1)==[0x288]
            h=8+self.attempts;ok=self.attempts!=self.fail;self.attempts+=1
            self.events.extend([1,0x288,h if ok else 0xffffffff])
            if ok:self.used.add(h)
            ret(u,0,self.pointer(h) if ok else 0)
        elif a==GROW:
            assert caller==0x5dc69f
            capacity,zero=words(u,sp+4,2);assert receiver==REGISTRY and zero==0 and 0<=capacity<=512
            self.events.extend([2,capacity,self.success&0xffffffff])
            if self.success&255:
                old=words(u,REGISTRY+8,1)[0];assert capacity>=old
                self.put(REGISTRY+8,capacity)
            ret(u,8,self.success&0xffffffff)
        else:raise AssertionError(f'Uninspected overlay input instruction {a:#x}')
    def run(self,op,v):
        self.op=op;self.events=[];self.used=set();self.attempts=0;seed=int(v[0]);v=v[1:]
        self.u.mem_write(ARENA,b'\xa5'*0x80000)
        for h in range(512):
            p=self.pointer(h)
            for (off,n),value in zip(FIELDS,initial(seed,h)):self.u.mem_write(p+off,(value&((1<<(8*n))-1)).to_bytes(n,'little'))
            self.write_string(p+0x24,'Existing'+str(h),64);self.write_string(p+0x1c8,'Art'+str(h),25)
        self.u.mem_write(BUFFER,bytes(0x2000));self.put(VTABLE+8,GROW);self.put(0xa3d290,0)
        self.capacity=self.count=0
        if op=='I':
            self.base,self.mask,theater,crushable=map(int,v[:4]);self.integers=list(map(int,v[4:7]));self.flags=list(map(int,v[7:21]))
            self.length=int(v[21]);self.text=decode(v[22]);self.animation,self.image=map(int,v[23:25]);self.used.add(0)
            self.u.mem_write(ARENA+0x1fc,bytes([theater&255,crushable&255]));root=0x5dcaa0;args=[OBJ];receiver=ARENA
        else:
            self.capacity,owns,growth,self.success,self.fail,self.count=map(int,v[:6]);at=6+self.count
            self.u.mem_write(REGISTRY,pack([VTABLE,BUFFER,self.capacity,0, self.count,growth]))
            self.u.mem_write(REGISTRY+13,bytes([owns&255]));self.slots=list(map(int,v[6:at]));self.used.update(self.slots)
            for i,h in enumerate(self.slots):self.put(BUFFER+i*4,self.pointer(h))
            if op=='C':
                h=int(v[at]);self.used.add(h);self.write_string(OBJ+0x2000,decode(v[at+1]),64)
                root=0x5dc5a0;args=[OBJ+0x2000];receiver=self.pointer(h)
            else:
                self.list_count=int(v[at]);rest=v[at+1:];self.entries=[(int(rest[i]),decode(rest[i+1])) for i in range(0,len(rest),2)]
                root=0x64c010;args=[OBJ];receiver=OBJ
        before=bytes(self.u.mem_read(ARENA,0x80000))
        def stores(u,access,p,n,value,ctx):
            value&=(1<<(8*n))-1
            if ARENA<=p<ARENA+0x80000:
                h,off=divmod(p-ARENA,1024)
                if (off,n) in FIELDS or (off,n)==(0x10,4):
                    self.events.extend([20,h,off,n,value]);self.stores+=1
                else:assert (off,n) in ((0,4),(4,4),(8,4),(12,4)),f'Unmodeled overlay record store {off:#x}/{n}'
            elif p==REGISTRY+16:
                assert n==4;self.events.extend([21,0,value]);self.stores+=1
            elif BUFFER<=p<BUFFER+512*4:
                assert n==4 and (p-BUFFER)%4==0;self.events.extend([21,1,(p-BUFFER)//4,self.handle(value)]);self.stores+=1
            else:assert STACK-0x2000<=p and p+n<=STACK+4+len(args)*4
        hook=self.u.hook_add(UC_HOOK_MEM_WRITE,stores)
        try:self.checked_call(root,args,receiver,writes=[(ARENA,0x80000),(BUFFER,512*4),(REGISTRY,24)],
            inputs=[(VTABLE,12),(0xa3d290,4),(0x7a908c,4),*[(p,len(s)+1) for p,s in KEYS.items()]])
        finally:self.u.hook_del(hook)
        result=self.u.reg_read(UC_X86_REG_EAX)&0xffffffff
        if op=='C':result=self.handle(result)
        else:result&=255
        # Audit every nonselected object byte, including capacity outside used
        # records. Base-service string writes are separately constrained above.
        after=bytearray(self.u.mem_read(ARENA,0x80000))
        for h in self.used:
            for off,n in (*FIELDS,(0,16),(0x10,4),(0x24,64),(0x1c8,25)):
                start=h*1024+off;after[start:start+n]=before[start:start+n]
        assert bytes(after)==before
        capacity=words(self.u,REGISTRY+8,1)[0] if op!='I' else 0
        count=words(self.u,REGISTRY+16,1)[0] if op!='I' else 0
        state=[count,capacity,*[self.handle(p) for p in words(self.u,BUFFER,capacity)]]
        assert bytes(self.u.mem_read(BUFFER+capacity*4,(512-capacity)*4))==bytes((512-capacity)*4)
        for h in sorted(self.used):
            p=self.pointer(h);state.append(h)
            state.extend(int.from_bytes(self.u.mem_read(p+off,n),'little') for off,n in FIELDS)
            text(state,self.string(p+0x24));text(state,self.string(p+0x1c8))
        return list(map(str,[result,digest(state),digest(self.events)]))
