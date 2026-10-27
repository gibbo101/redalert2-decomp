# SPDX-License-Identifier: GPL-3.0-or-later
"""Unmodified GetBool on decoded hot-index fixtures and scoped type-loader blocks.

No original text parser, cold search, allocation or whole constructor is supplied
as recovered behavior. No original routine is replaced by a stub.
"""
import struct
from original_presentation import PresentationOracle,OBJ,ARG,STACK
from unicorn import UC_HOOK_MEM_WRITE
from unicorn.x86_const import (UC_X86_REG_EAX,UC_X86_REG_EBX,UC_X86_REG_ECX,
    UC_X86_REG_EDI,UC_X86_REG_ESI,UC_X86_REG_EBP,UC_X86_REG_ESP,UC_X86_REG_EIP)
from verify_unit_metadata import verify,FIELDS,KEY_POINTERS
INI=OBJ;SECTION=OBJ+0x1000;SECTION_INDEX=OBJ+0x1100
KEY_INDEX=OBJ+0x1200;VALUE=OBJ+0x1300;TEXT=OBJ+0x1400
SECTION_NAME=OBJ+0x1600;KEY_NAME=OBJ+0x1700;CRC=ARG
TYPE=OBJ+0x2000;ART_INI=0x8397f0
OFFSETS=[row[0] for row in FIELDS]
class UnitMetadataOracle(PresentationOracle):
    def __init__(self,exe):
        verify(exe.read_bytes());super().__init__(exe,allow_patched=True)
        self.put(0xb2b098,0) # Actual CRT locale-zero path, no Win32 service.
        self.u.mem_write(SECTION_NAME,b'HTNK\0')
        self.hashes={}
        for name in ('HTNK',*[r[1] for r in FIELDS]):self.hashes[name]=self.crc(name)
    def va(self,a):return a
    def crc(self,name):
        raw=name.encode('ascii');self.u.mem_write(KEY_NAME,raw+b'\0');self.u.mem_write(CRC,b'\0'*16)
        self.checked_call(0x493fc0,[KEY_NAME,len(raw)],CRC,writes=[(CRC,16)],inputs=[(KEY_NAME,len(raw)+1)])
        return self.u.reg_read(UC_X86_REG_EAX)
    def setup(self,mode,value=b'',key='Harvester',ini=INI):
        assert 0<=mode<=7 and b'\0' not in value
        self.u.mem_write(OBJ,b'\x93'*0x4000)
        self.u.mem_write(ini,b'\0'*0x80);self.u.mem_write(SECTION,b'\0'*0x80)
        self.u.mem_write(SECTION_NAME,b'HTNK\0');self.u.mem_write(KEY_NAME,key.encode()+b'\0')
        self.u.mem_write(TEXT,value+b'\0')
        self.put(ini+0x20,SECTION_INDEX);self.put(ini+0x24,0 if mode==0 else 1);self.put(ini+0x30,SECTION_INDEX)
        self.put(SECTION_INDEX,self.hashes['HTNK']);self.put(SECTION_INDEX+4,0 if mode==2 else SECTION)
        self.put(SECTION+0x2c,KEY_INDEX);self.put(SECTION+0x30,0 if mode==1 else 1);self.put(SECTION+0x3c,KEY_INDEX)
        self.put(KEY_INDEX,self.hashes[key]);self.put(KEY_INDEX+4,0 if mode==3 else VALUE)
        self.put(VALUE+0x10,0 if mode==4 else TEXT)
        return [0 if mode==6 else SECTION_NAME,0 if mode==7 else KEY_NAME]
    def boolean(self,mode,fallback,value):
        args=self.setup(mode,value)+[fallback]
        self.checked_call(0x50f410,args,INI,inputs=[(OBJ,0x4000)])
        return [self.u.reg_read(UC_X86_REG_EAX)&255]
    def block(self,start,size,stores=()):
        before=bytes(self.u.mem_read(OBJ,0x4000));image=bytes(self.u.mem_read(ART_INI,0x80))
        guard=b'\xa7'*64;self.u.mem_write(STACK,guard);self.u.reg_write(UC_X86_REG_ESP,STACK)
        seen=[]
        def audit(u,access,p,n,v,ctx):
            if STACK-0x2000<=p and p+n<=STACK:return
            v&=(1<<(8*n))-1 # Unicorn can expose the source register's upper bits.
            seen.append((p,n,v))
            if not any(p==TYPE+off and n==width and v==value for off,width,value in stores):
                raise AssertionError(f'Unexpected type block write {p:#x}/{n}/{v:#x}')
        hook=self.u.hook_add(UC_HOOK_MEM_WRITE,audit)
        try:self.u.emu_start(start,start+size,count=20000)
        finally:self.u.hook_del(hook)
        assert self.u.reg_read(UC_X86_REG_EIP)==start+size
        assert self.u.reg_read(UC_X86_REG_ESP)==STACK and bytes(self.u.mem_read(STACK,64))==guard
        assert seen==[(TYPE+off,n,value) for off,n,value in stores]
        after=bytearray(self.u.mem_read(OBJ,0x4000))
        for off,n,value in stores:
            assert int.from_bytes(self.u.mem_read(TYPE+off,n),'little')==value
            after[TYPE+off-OBJ:TYPE+off-OBJ+n]=before[TYPE+off-OBJ:TYPE+off-OBJ+n]
        assert bytes(after)==before and bytes(self.u.mem_read(ART_INI,0x80))==image
        self.audit_blocks+=1
    def metadata(self,field,mode,fallback,value):
        off,key,reads,store,ctor=FIELDS[field];ini=ART_INI if field==1 else INI
        assert mode in (1,5)
        self.setup(mode,value,key,ini)
        for p,v in zip(OFFSETS,[23,41,67,97,123]):self.u.mem_write(TYPE+p,bytes([v]))
        self.u.mem_write(TYPE+off,bytes([fallback&255]))
        # Supplied live registers at selected loader blocks; intervening setup
        # is skipped explicitly. Turret's CL read and push/call are separate.
        for reg,v in ((UC_X86_REG_EAX,0xc1d2e3f4),(UC_X86_REG_ECX,0x99aabbcc),
                      (UC_X86_REG_EBX,INI),(UC_X86_REG_EDI,TYPE),
                      (UC_X86_REG_EBP,SECTION_NAME),(UC_X86_REG_ESI,INI)):
            self.u.reg_write(reg,v)
        if field==1:self.u.reg_write(UC_X86_REG_EBX,TYPE);self.u.reg_write(UC_X86_REG_ESI,SECTION_NAME)
        elif field in (2,3,4):
            self.u.reg_write(UC_X86_REG_EBP,TYPE);self.u.reg_write(UC_X86_REG_EBX,SECTION_NAME)
        for start,size in reads:self.block(start,size)
        result=self.u.reg_read(UC_X86_REG_EAX)&255
        self.block(*store,[(off,1,result)])
        return [self.u.mem_read(TYPE+p,1)[0] for p in OFFSETS]
    def defaults(self):
        self.setup(1);self.u.reg_write(UC_X86_REG_EBX,0)
        self.u.reg_write(UC_X86_REG_ESI,TYPE);self.u.reg_write(UC_X86_REG_EBP,TYPE)
        for off,key,reads,store,ctor in FIELDS:self.block(ctor,6,[(off,1,0)])
        return [self.u.mem_read(TYPE+p,1)[0] for p in OFFSETS]
