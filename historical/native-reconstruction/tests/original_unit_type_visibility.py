# SPDX-License-Identifier: GPL-3.0-or-later
"""Unmodified patched image selection, actual house helpers and Unit cell getter.

Map/house records are synthetic. Final body/Foot/timer decorations remain services.
Constructor execution is restricted to the independently aligned field blocks.
"""
import struct
from original_unit_draw_caller import UnitDrawCallerOracle,ARENA,ACTOR,TYPE,ALT,CELL,TABLE
from original_presentation import STACK
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import (UC_X86_REG_EAX,UC_X86_REG_EBX,UC_X86_REG_ECX,
    UC_X86_REG_EDI,UC_X86_REG_ESI,UC_X86_REG_ESP,UC_X86_REG_EIP)
OWNER=ARENA+0xc000;OBSERVER=ARENA+0x12000
class UnitTypeVisibilityOracle(UnitDrawCallerOracle):
    def __init__(self,exe):
        super().__init__(exe);self.extended_state=None;self.select_argument=None;self.trace_state=False
        self.hooks.extend(self.u.hook_add(UC_HOOK_CODE,self.state_service,begin=a,end=a) for a in
                          (0x4f52b0,0x4e5540,0x41b410,0x5d51e0,0x47c300))
    def service(self,u,a,n,ctx):
        if self.active and a==0x709bb0 and self.select_argument is not None:
            sp=u.reg_read(UC_X86_REG_ESP)
            assert u.reg_read(UC_X86_REG_ECX)==ACTOR and self.result(sp+4,1)[0]==self.select_argument
            self.event('a',self.select_argument);return
        super().service(u,a,n,ctx)
    def state_service(self,u,a,n,ctx):
        if not self.active:return
        ecx=u.reg_read(UC_X86_REG_ECX);sp=u.reg_read(UC_X86_REG_ESP)
        if a==0x4f52b0:assert ecx==OWNER;key='o'
        elif a==0x4e5540:
            assert ecx==OWNER and self.result(sp+4,1)[0]==self.current_house;key='l'
        elif a==0x41b410:assert ecx==ACTOR;key='d'
        elif a==0x5d51e0:assert ecx==ACTOR;key='B'
        elif a==0x47c300:
            assert ecx==CELL and self.result(sp+4,1)[0]==self.observer_index;key='s'
        else:raise AssertionError('Unexpected image-selection child')
        if self.trace_state:self.event(key)
        # No return redirection: every routine above executes unchanged.
    def houses(self,mode,a,b,same,owner_index,observer_index,alliances,present=True):
        self.current_house=(OWNER if same else OBSERVER) if present else 0
        self.observer_index=observer_index
        self.put(ACTOR+0x1b4,OWNER);self.put(OWNER+0x30,owner_index)
        if present:self.put(self.current_house+0x30,observer_index)
        self.u.mem_write(OWNER+0x134,bytes([a&255,b&255]));self.put(OWNER+0x5674,alliances)
        self.put(0xa3d298,mode);self.put(0xa35db4,self.current_house)
    def state(self,frame,values):
        (start,duration,disguised,creation,mode,a,b,same,owner_index,observer_index,alliances,sensors)=values
        assert 0<=observer_index<24
        self.houses(mode,a,b,same,owner_index,observer_index,alliances)
        self.put(0xa40d2c,frame);self.put(ACTOR+0x184,start);self.put(ACTOR+0x18c,duration)
        self.u.mem_write(ACTOR+0x170,bytes([disguised&255]));self.put(ACTOR+0x174,creation)
        self.u.mem_write(CELL+0xac+2*observer_index,struct.pack('<h',sensors))
        self.put(ACTOR+0x40c,ALT);self.put(ACTOR+0x5ac,TYPE)
        self.real_type_state=True;self.trace_state=True
    def prepare_draw_state(self):
        if self.extended_state is not None:self.state(*self.extended_state)
    def extended_draw(self,values,timer,state=None):
        self.extended_state=None if state is None else (timer[0],state)
        self.real_type_state=False;self.trace_state=False
        try:return self.draw(values,timer=timer)
        finally:self.extended_state=None;self.real_type_state=False;self.trace_state=False
    def standalone(self,address,args=(),ecx=ACTOR):
        self.active=True
        try:self.checked_call(address,args,ecx,inputs=[(ARENA,0x20000),(TABLE,0x100000)])
        finally:self.active=False
        return self.u.reg_read(UC_X86_REG_EAX)
    def owner(self,mode,a,b,same):
        self.setup(0,(0,0),96,88);self.trace_state=False
        self.houses(mode,a,b,same,1,2,0)
        return [self.standalone(0x4f52b0,ecx=OWNER)&255]
    def allied(self,present,same,owner_index,observer_index,alliances):
        self.setup(0,(0,0),96,88);self.trace_state=False
        self.houses(0,0,0,same,owner_index,observer_index,alliances,present)
        return [self.standalone(0x4e5540,[self.current_house],OWNER)&255]
    def select(self,argument,present,same,owner_index,observer_index,alliances):
        self.setup(0,(0,0),96,88);self.trace_state=True
        self.houses(0,0,0,same,owner_index,observer_index,alliances,present)
        self.put(ACTOR+0x5ac,TYPE);self.put(ACTOR+0x40c,ALT);self.select_argument=argument
        try:value=self.standalone(0x709bb0,[argument])
        finally:self.select_argument=None
        assert value in (TYPE,ALT)
        return [1 if value==TYPE else 2,*self.events]
    def visibility(self,frame,values):
        self.setup(0,(0,0),96,88);self.coords=(18304,29312,416)
        self.put(ACTOR,0x7addf8);self.ints(ACTOR+0x88,self.coords)
        self.put(0x8324e0+0x138,TABLE);self.put(0x8324e0+0x13c,262144)
        self.state(frame,values)
        result=self.standalone(0x6d8ce0,[self.current_house])&255
        return [result,*self.events]
    def defaults(self,frame):
        self.setup(0,(0,0),96,88);self.put(0xa40d2c,frame)
        # Explicitly supplied constructor live registers. These are field blocks,
        # not callable functions or evidence for their intervening services.
        blocks=[(0x5d232b,3,[(0x79,1,0)]),(0x6c0dc9,12,[(0x170,1,0),(0x174,4,0)]),
                (0x6c0de6,22,[(0x184,4,frame),(0x18c,4,0)]),
                (0x6c0fc1,18,[(0x314,4,frame),(0x31c,4,0)]),
                (0x6c10b2,6,[(0x37c,1,0)]),(0x6c11a1,6,[(0x40c,4,0)]),
                (0x4c2b62,6,[(0x59e,1,0)]),(0x6fa432,6,[(0x5b4,4,-1)])]
        for start,size,stores in blocks:
            before=bytes(self.u.mem_read(ARENA,0x20000));guard=b'\xa7'*128;self.u.mem_write(STACK,guard)
            for reg,value in [(UC_X86_REG_ESI,ACTOR),(UC_X86_REG_EBX,0),(UC_X86_REG_EDI,0xffffffff),(UC_X86_REG_ESP,STACK)]:self.u.reg_write(reg,value)
            seen=[]
            def audit(u,access,p,n,v,ctx):seen.append((p-ACTOR,n,self.signed(v) if n==4 else v))
            hook=self.u.hook_add(UC_HOOK_MEM_WRITE,audit)
            try:self.u.emu_start(start,start+size,count=100)
            finally:self.u.hook_del(hook)
            assert seen==stores and self.u.reg_read(UC_X86_REG_EIP)==start+size
            assert self.u.reg_read(UC_X86_REG_ESP)==STACK and bytes(self.u.mem_read(STACK,128))==guard
            after=bytearray(self.u.mem_read(ARENA,0x20000))
            for off,n,v in stores:after[ACTOR+off-ARENA:ACTOR+off-ARENA+n]=before[ACTOR+off-ARENA:ACTOR+off-ARENA+n]
            assert bytes(after)==before,'Constructor block arena changed'
            self.audit_blocks+=1
        return [self.u.mem_read(ACTOR+0x79,1)[0],self.u.mem_read(ACTOR+0x170,1)[0],
                *[self.result(ACTOR+off,1)[0] for off in (0x174,0x184,0x18c,0x314,0x31c)],
                self.u.mem_read(ACTOR+0x37c,1)[0],self.result(ACTOR+0x40c,1)[0],
                self.u.mem_read(ACTOR+0x59e,1)[0],self.result(ACTOR+0x5b4,1)[0]]
