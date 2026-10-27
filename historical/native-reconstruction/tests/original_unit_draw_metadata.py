# SPDX-License-Identifier: GPL-3.0-or-later
"""Selected unchanged loader/default blocks; integer decoding is a service."""
from original_unit_metadata import UnitMetadataOracle,INI,TYPE,SECTION_NAME
from original_foot_lit import words,ret,signed
from verify_unit_draw_metadata import verify,FIELDS
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EBX,UC_X86_REG_ECX,UC_X86_REG_ESI,UC_X86_REG_EDI,UC_X86_REG_EBP,UC_X86_REG_ESP,UC_X86_REG_EFLAGS
class UnitDrawMetadataOracle(UnitMetadataOracle):
    def __init__(self,exe):
        verify(exe.read_bytes());super().__init__(exe)
        for _,key,_,_,_ in FIELDS:self.hashes[key]=self.crc(key)
        self.active=False;self.integer_calls=0;self.selected_blocks=0;self.side_writes=0
        self.u.hook_add(UC_HOOK_CODE,self.route)
    def route(self,u,a,n,ctx):
        if not self.active or a!=0x50d7f0:return
        assert u.reg_read(UC_X86_REG_ECX)==INI
        sp=u.reg_read(UC_X86_REG_ESP);section,key,fallback=words(u,sp+4,3)
        off,name,pointer,_,_=FIELDS[self.index]
        assert section==SECTION_NAME and key==pointer
        assert signed(fallback)==self.defaults[self.index]
        self.events+=['integer',name,signed(fallback)]
        value=self.values[self.index] if self.mask&(1<<self.index) else signed(fallback)
        self.index+=1;self.integer_calls+=1;ret(u,12,value)
    def fields(self):
        return [signed(int.from_bytes(self.u.mem_read(TYPE+off,4),'little')) for off,*_ in FIELDS[:4]]+[self.u.mem_read(TYPE+0xbae,1)[0]]
    def metadata(self,defaults,mask,values,mode,text,side=0,logging=True):
        self.setup(mode,text,'TooBigToFitUnderBridge');self.defaults=defaults;self.values=values;self.mask=mask
        for (off,*_),value in zip(FIELDS[:4],defaults[:4]):self.put(TYPE+off,value)
        self.u.mem_write(TYPE+0xbae,bytes([defaults[4]&255]))
        self.u.reg_write(UC_X86_REG_EBP,TYPE);self.u.reg_write(UC_X86_REG_EBX,SECTION_NAME);self.u.reg_write(UC_X86_REG_ESI,INI)
        self.events=[];self.index=0;self.active=True
        expected=[values[i] if mask&(1<<i) else defaults[i] for i in range(4)]
        try:self.block(0x6dd5ed,0x6e,[(row[0],4,value&0xffffffff) for row,value in zip(FIELDS[:4],expected)])
        finally:self.active=False
        assert self.index==4
        self.u.reg_write(UC_X86_REG_EDI,TYPE);self.u.reg_write(UC_X86_REG_EBX,INI);self.u.reg_write(UC_X86_REG_EBP,SECTION_NAME)
        self.u.reg_write(UC_X86_REG_EFLAGS,0x246 if side else 0x202)
        self.block(0x70ac5e,0x1d,[(0xba9,1,side)])
        from unicorn.x86_const import UC_X86_REG_EAX
        result=self.u.reg_read(UC_X86_REG_EAX)&255
        self.block(0x70ac8f,6,[(0xbae,1,result)])
        self.selected_blocks+=3;self.side_writes+=1
        return (self.events+['boolean','TooBigToFitUnderBridge',defaults[4]&255] if logging else [])+['fields',*self.fields()]
    def defaults_case(self):
        self.setup(1)
        self.u.reg_write(UC_X86_REG_ESI,TYPE)
        # Execute the original register setup and selected stores separately.
        # Intervening constructor calls/writes do not execute in this fixture.
        self.block(0x6d9b55,2);self.block(0x6da211,5)
        self.block(0x6da522,0x1c,[(0xb5c,4,10),(0xb60,4,5),(0xb64,4,10),(0xb68,4,0)])
        self.block(0x70a619,2);self.block(0x70a673,6,[(0xbae,1,0)])
        self.selected_blocks+=5;return ['fields',*self.fields()]
