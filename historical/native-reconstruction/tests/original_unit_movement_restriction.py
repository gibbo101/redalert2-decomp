# SPDX-License-Identifier: GPL-3.0-or-later
"""Run scoped default and missing-key association without replacing original children."""
import struct
from original_unit_metadata import UnitMetadataOracle,INI,TYPE,SECTION_NAME
from verify_unit_movement_restriction import verify,COMPLETE,BLOCKS
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_EBX,UC_X86_REG_EBP,UC_X86_REG_EDI,UC_X86_REG_ESI
class UnitMovementRestrictionOracle(UnitMetadataOracle):
    def __init__(self,exe):
        self.inspection=verify(exe.read_bytes());super().__init__(exe)
        self.hashes['MovementRestrictedTo']=self.crc('MovementRestrictedTo')
        self.active=False;self.entries={hex(a):0 for a in COMPLETE};self.entered=set()
        self.u.hook_add(UC_HOOK_CODE,self.observe)
    def observe(self,u,a,n,ctx):
        if not self.active:return
        assert any(lo<=a and a+n<=lo+size for lo,size in {**COMPLETE,**BLOCKS}.items()),hex(a)
        assert a!=0x781f73,'Locale-bearing comparison excluded'
        if hex(a) in self.entries:self.entries[hex(a)]+=1
        self.entered.add(a)
    def run(self,mode,neighbor):
        assert mode in (0,1) and 0<=neighbor<=255
        self.setup(mode,key='MovementRestrictedTo');self.u.reg_write(UC_X86_REG_ESI,TYPE)
        immutable=[(a,n,bytes(self.u.mem_read(a,n))) for a,n in {**COMPLETE,**BLOCKS}.items()]
        immutable.append((0xb2b098,4,bytes(self.u.mem_read(0xb2b098,4))))
        self.active=True
        try:
            self.block(0x70a607,3);self.block(0x70a61b,6,[(0xb94,4,0xffffffff)])
            assert struct.unpack('<I',self.u.mem_read(TYPE+0xb94,4))[0]==0xffffffff
            for reg,value in ((UC_X86_REG_EBX,INI),(UC_X86_REG_EDI,TYPE),
                (UC_X86_REG_EBP,SECTION_NAME),(UC_X86_REG_EAX,neighbor)):
                self.u.reg_write(reg,value)
            self.block(0x70ad45,0x20,[(0xba4,1,neighbor),(0xb94,4,0xffffffff)])
        finally:self.active=False
        assert all(bytes(self.u.mem_read(a,n))==value for a,n,value in immutable)
        for reg,value in ((UC_X86_REG_EBX,INI),(UC_X86_REG_EDI,TYPE),
            (UC_X86_REG_EBP,SECTION_NAME),(UC_X86_REG_ESI,TYPE)):
            assert self.u.reg_read(reg)==value,'Scoped block preserved register differs'
        assert struct.unpack('<I',self.u.mem_read(TYPE+0xb94,4))[0]==0xffffffff
        return [-1]
