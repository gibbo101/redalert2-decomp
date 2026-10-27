# SPDX-License-Identifier: GPL-3.0-or-later
"""Actual decoded-entry string routines and selected unchanged model input blocks."""
import struct
from original_unit_metadata import UnitMetadataOracle,INI,TYPE,ART_INI,OBJ,KEY_NAME,TEXT,SECTION_NAME
from original_presentation import STACK
from original_foot_lit import words,ret,signed
from verify_unit_model_inputs import verify,COMPLETE,BLOCKS
from verify_unit_metadata import COMPLETE as PARENT_COMPLETE
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_EBX,UC_X86_REG_ECX,UC_X86_REG_ESI,UC_X86_REG_EDI,UC_X86_REG_EBP,UC_X86_REG_ESP,UC_X86_REG_EIP
OUTPUT=OBJ+0x6000;FALLBACK=OBJ+0x7000;SP=STACK-0x1000
def text(u,p):return bytes(u.mem_read(p,256)).split(b'\0',1)[0]
def hx(b):return b.hex() or '-'
class UnitModelInputOracle(UnitMetadataOracle):
    def __init__(self,exe):
        verify(exe.read_bytes());super().__init__(exe)
        for key in ('Image','TurretCount','TurretOffset'):self.hashes[key]=self.crc(key)
        self.active=False;self.integer=None;self.events=None
        self.actual_strings=0;self.actual_missing_integers=0;self.supplied_integers=0;self.type_writes=0
        self.u.hook_add(UC_HOOK_CODE,self.route)
    def route(self,u,a,n,ctx):
        if not self.active:return
        assert any(start<=a<start+size for start,size in {**COMPLETE,**BLOCKS,**PARENT_COMPLETE}.items()),f'Unexpected model input execution {a:#x}'
        sp=u.reg_read(UC_X86_REG_ESP)
        if a==0x50e9a0:
            self.actual_strings+=1
            if self.events is not None:
                section,key,fallback,out,cap=words(u,sp+4,5)
                assert text(u,section)==b'HTNK' and text(u,key)==b'Image' and out==TYPE+0x1c8 and cap==25
                assert sp< fallback <SP+0x100 and fallback!=out
                self.events+=['image',hx(text(u,section)),hx(text(u,fallback))]
        elif a==0x50d7f0:
            index,present,value=self.integer
            section,key,default=words(u,sp+4,3)
            assert text(u,key)==(b'TurretCount' if index==0 else b'TurretOffset')
            assert text(u,section)==(b'HTNK' if index==0 else self.current_image)
            assert signed(default)==self.defaults[index]
            assert u.reg_read(UC_X86_REG_ECX)==(INI if index==0 else ART_INI)
            self.events+=['rules' if index==0 else 'art',hx(text(u,section)),text(u,key).decode(),signed(default)]
            if present:self.supplied_integers+=1;ret(u,12,value)
            else:self.actual_missing_integers+=1
    def string(self,mode,capacity,value,fallback):
        self.setup(min(mode,7),value,'Image');self.u.mem_write(OUTPUT,b'\x93'*64)
        self.u.mem_write(FALLBACK,(fallback or b'')+b'\0')
        section=0 if mode==6 else SECTION_NAME;key=0 if mode==7 else KEY_NAME
        args=[section,key,0 if fallback is None else FALLBACK,0 if mode==8 else OUTPUT,capacity]
        self.events=None;self.active=True
        try:self.checked_call(0x50e9a0,args,INI,writes=[(OUTPUT,64)],inputs=[(OBJ,0x4000),(FALLBACK,len(fallback or b'')+1)])
        finally:self.active=False
        return [self.u.reg_read(UC_X86_REG_EAX),bytes(self.u.mem_read(OUTPUT,64)).hex()]
    def block(self,start,size,allowed=()):
        before=bytes(self.u.mem_read(OBJ,0x8000));image=bytes(self.u.mem_read(ART_INI,0x80))
        guard=b'\xa7'*64;self.u.mem_write(SP+0x200,guard);self.u.reg_write(UC_X86_REG_ESP,SP)
        self.block_writes=[]
        def audit(u,access,p,n,v,ctx):
            if SP-0x1000<=p and p+n<=SP+0x1a4:return
            assert any(TYPE+off<=p and p+n<=TYPE+off+length for off,length in allowed),f'Unexpected model block write {p:#x}/{n}'
            self.block_writes.append((p-TYPE,n,v&((1<<(8*n))-1)));self.type_writes+=1
        hook=self.u.hook_add(UC_HOOK_MEM_WRITE,audit);self.active=True
        try:self.u.emu_start(start,start+size,count=20000)
        finally:self.active=False;self.u.hook_del(hook)
        assert self.u.reg_read(UC_X86_REG_EIP)==start+size and self.u.reg_read(UC_X86_REG_ESP)==SP
        assert bytes(self.u.mem_read(SP+0x200,64))==guard
        after=bytearray(self.u.mem_read(OBJ,0x8000))
        for off,length in allowed:after[TYPE+off-OBJ:TYPE+off-OBJ+length]=before[TYPE+off-OBJ:TYPE+off-OBJ+length]
        assert bytes(after)==before and bytes(self.u.mem_read(ART_INI,0x80))==image
        self.audit_blocks+=1
    def constructor(self,typeid):
        assert len(typeid)==25
        self.setup(1,key='Image');self.u.mem_write(TYPE+0x24,typeid)
        self.u.reg_write(UC_X86_REG_EBP,TYPE);self.u.reg_write(UC_X86_REG_ESI,TYPE)
        self.events=None;self.block(0x5d5801,2);self.block(0x5d5888,6);self.block(0x5d5970,3)
        self.block(0x5d59af,0x28,[(0,16),(0x1c8,25)])
        assert [x for x in self.block_writes if x[0]<16]==[(i*4,4,v) for i,v in enumerate((0x7a76f8,0x7a76dc,0x7a76d4,0x7a76cc))]
        self.u.reg_write(UC_X86_REG_ESI,TYPE);self.block(0x6d9b55,2)
        for p in (0x6da16c,0x6da298):self.block(p,6,[(0x63c if p==0x6da16c else 0x704,4)])
        return ['state',bytes(self.u.mem_read(TYPE+0x1c8,25)).hex(),
                signed(words(self.u,TYPE+0x704,1)[0]),signed(words(self.u,TYPE+0x63c,1)[0])]
    def metadata(self,image,count,offset,mask,values,mode,value):
        assert len(image)==25 and b'\0' in image
        self.setup(mode,value,'Image');self.u.mem_write(TYPE+0x24,b'HTNK\0');self.u.mem_write(TYPE+0x1c8,image)
        self.put(SP+0x1b8,INI);self.u.reg_write(UC_X86_REG_EBX,TYPE)
        # Field address setup is separate from the post-push-EDI live frame.
        # Supplying that frame keeps the selected read/call block balanced.
        self.events=[];self.block(0x5d782d,6);self.block(0x5d7834,0x40,[(0x1c8,25)])
        new_image=bytes(self.u.mem_read(TYPE+0x1c8,25));self.current_image=new_image.split(b'\0',1)[0]
        saved=list(self.events);self.defaults=[count,offset]
        for index,default in enumerate(self.defaults):
            # Actual GetInt's missing-entry path executes against a supplied empty
            # decoded section index. Present integer parsing remains a service.
            self.setup(0,key='TurretCount' if index==0 else 'TurretOffset',ini=INI if index==0 else ART_INI)
            self.u.mem_write(TYPE+0x24,b'HTNK\0');self.u.mem_write(TYPE+0x1c8,new_image)
            self.put(TYPE+0x704,count);self.put(TYPE+0x63c,offset)
            self.u.reg_write(UC_X86_REG_EBP,TYPE)
            self.u.reg_write(UC_X86_REG_EBX,TYPE+0x24);self.u.reg_write(UC_X86_REG_ESI,INI if index==0 else TYPE+0x1c8)
            self.events=saved;self.integer=(index,bool(mask&(1<<index)),values[index])
            p=0x6db614 if index==0 else 0x6dd9b5;off=0x704 if index==0 else 0x63c
            self.block(p,BLOCKS[p],[(off,4)])
            if index==0:count=signed(words(self.u,TYPE+off,1)[0])
            else:offset=signed(words(self.u,TYPE+off,1)[0])
            assert self.block_writes==[(off,4,(count if index==0 else offset)&0xffffffff)]
        return self.events+['state',new_image.hex(),count,offset]
