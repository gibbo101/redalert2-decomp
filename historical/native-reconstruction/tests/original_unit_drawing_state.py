# SPDX-License-Identifier: GPL-3.0-or-later
"""Unchanged complete initializers/leaves and selected constructor field blocks."""
import struct
from original_presentation import PresentationOracle,OBJ,STACK
from original_foot_lit import words,signed
from verify_unit_drawing_state import verify,COMPLETE,BLOCKS
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ESI,UC_X86_REG_EBX,UC_X86_REG_ESP,UC_X86_REG_EIP
FRAME=0xa40d2c
def fields(u,p):
    return [struct.unpack('<H',u.mem_read(p,2))[0],struct.unpack('<H',u.mem_read(p+4,2))[0],
            signed(words(u,p+8,1)[0]),signed(words(u,p+16,1)[0]),struct.unpack('<H',u.mem_read(p+20,2))[0]]
def facing_writes(offset,frame,rate=None):
    w=[(offset,2,0),(offset+4,2,0),(offset+16,4,0),(offset+8,4,frame&0xffffffff),(offset+20,2,0)]
    if rate is not None:w.append((offset+20,2,(min(rate,127)&255)<<8))
    return w
class UnitDrawingStateOracle(PresentationOracle):
    def __init__(self,exe):
        verify(exe.read_bytes());super().__init__(exe,allow_patched=True)
        self.active=False;self.events=[];self.constructor_calls=0
        self.u.hook_add(UC_HOOK_CODE,self.route);self.u.hook_add(UC_HOOK_MEM_WRITE,self.store)
    def va(self,a):return a
    def route(self,u,a,n,ctx):
        if not self.active:return
        assert any(p<=a<p+n for p,n in {**COMPLETE,**BLOCKS}.items()),f'Unexpected drawing-state execution {a:#x}'
        if a in (0x4b89d0,0x4b89f0):self.constructor_calls+=1
    def store(self,u,access,p,n,v,ctx):
        if self.active and OBJ<=p<OBJ+0x1000:self.events.append((p-OBJ,n,v&((1<<(8*n))-1)))
    def prepare(self,frame,padding):
        self.put(FRAME,frame);self.u.mem_write(OBJ,bytes([padding&255])*0x1000);self.events=[]
    def facing(self,frame,rate,has_rate,padding):
        self.prepare(frame,padding);before=bytes(self.u.mem_read(OBJ,0x1000));self.active=True
        try:self.checked_call(0x4b89f0 if has_rate else 0x4b89d0,[rate] if has_rate else [],OBJ,
                              writes=[(OBJ,24)],inputs=[(FRAME,4)])
        finally:self.active=False
        expected=facing_writes(0,frame,rate if has_rate else None);assert self.events==expected
        self.check_arena(before,expected)
        assert self.u.reg_read(UC_X86_REG_EAX)==OBJ
        return fields(self.u,OBJ)
    def check_arena(self,before,expected):
        after=bytearray(self.u.mem_read(OBJ,0x1000))
        final=bytearray(before)
        for off,n,v in expected:final[off:off+n]=(v&((1<<(8*n))-1)).to_bytes(n,'little')
        assert bytes(after)==bytes(final),'Drawing-state final stores/padding changed'
        for off,n,v in expected:
            after[off:off+n]=before[off:off+n]
        assert bytes(after)==before,'Drawing-state arena/padding changed'
    def block(self,p,expected):
        before=bytes(self.u.mem_read(OBJ,0x1000));clock=bytes(self.u.mem_read(FRAME,4))
        sp=STACK-0x100;guard=b'\xa7'*64;self.u.mem_write(sp+4,guard)
        self.u.reg_write(UC_X86_REG_ESP,sp);self.u.reg_write(UC_X86_REG_ESI,OBJ);self.events=[]
        def audit(u,access,a,n,v,ctx):
            assert sp-0x100<=a and a+n<=sp or any(a==OBJ+off and n==size for off,size,_ in expected),f'Unexpected constructor write {a:#x}/{n}'
        hook=self.u.hook_add(UC_HOOK_MEM_WRITE,audit);self.active=True
        try:self.u.emu_start(p,p+BLOCKS[p],count=1000)
        finally:self.active=False;self.u.hook_del(hook)
        assert self.u.reg_read(UC_X86_REG_EIP)==p+BLOCKS[p] and self.u.reg_read(UC_X86_REG_ESP)==sp
        assert bytes(self.u.mem_read(sp+4,64))==guard and bytes(self.u.mem_read(FRAME,4))==clock
        assert self.events==expected,(hex(p),self.events,expected)
        self.check_arena(before,expected);self.audit_blocks+=1
    def defaults(self,frame,padding):
        self.prepare(frame,padding)
        # Setup blocks really zero EBX. Other registers/frame/ESI remain supplied.
        self.u.reg_write(UC_X86_REG_EBX,0x98765432)
        self.block(0x6c0cdb,[])
        self.block(0x6c0da5,[(0x15c,4,0),(0x154,4,frame&0xffffffff)])
        self.block(0x6c0e3e,[(0x1bc,4,0)])
        self.block(0x6c0ec8,[(0x204,1,0),(0x205,1,0)])
        self.block(0x6c0f98,facing_writes(0x2c8,frame,3)+facing_writes(0x2e0,frame)+facing_writes(0x2f8,frame))
        self.u.reg_write(UC_X86_REG_EBX,0x87654321);self.block(0x4c293f,[])
        self.block(0x4c2973,[(0x430,4,0)])
        self.u.reg_write(UC_X86_REG_EBX,0x76543210);self.block(0x6fa41d,[])
        self.block(0x6fa44a,[(0x5bb,1,0)])
        return fields(self.u,OBJ+0x2c8)+fields(self.u,OBJ+0x2e0)+fields(self.u,OBJ+0x2f8)+[
            signed(words(self.u,OBJ+0x154,1)[0]),signed(words(self.u,OBJ+0x15c,1)[0]),
            signed(words(self.u,OBJ+0x1bc,1)[0]),signed(words(self.u,OBJ+0x430,1)[0]),
            *bytes(self.u.mem_read(OBJ+0x204,2)),*bytes(self.u.mem_read(OBJ+0x5bb,1))]
    def status(self,start,duration,frame,first,second):
        self.prepare(frame,0xa7);self.put(OBJ+0x154,start);self.put(OBJ+0x15c,duration)
        self.u.mem_write(OBJ+0x204,bytes([first&255,second&255]));result=[];self.active=True
        try:
            for root in (0x41b390,0x6d6df0,0x6d6e00):
                self.checked_call(root,ecx=OBJ,inputs=[(OBJ,0x1000),(FRAME,4)])
                result.append(self.u.reg_read(UC_X86_REG_EAX)&255)
        finally:self.active=False
        assert not self.events
        return result
