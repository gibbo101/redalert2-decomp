# SPDX-License-Identifier: GPL-3.0-or-later
"""Isolated original presentation kernels; no instruction patches or API stubs.

Patched selection is explicit and limited to these primitive methods. Subclasses
retain the disc-only constructor default until their own mappings are migrated.
"""
import struct
from pathlib import Path
import pefile
from unicorn import Uc, UC_ARCH_X86, UC_MODE_32, UC_HOOK_MEM_WRITE
from unicorn.x86_const import (UC_X86_REG_ESP, UC_X86_REG_ECX, UC_X86_REG_EDX,
    UC_X86_REG_EBX, UC_X86_REG_ESI, UC_X86_REG_EDI, UC_X86_REG_EBP,
    UC_X86_REG_EIP, UC_X86_REG_FPCW)
from presentation_profiles import presentation_profile, address

OBJ=0x1100000;PAL=OBJ+0x1000;MASK=OBJ+0x1400;SRC=OBJ+0x2000
FRAME=OBJ+0x4000;DEPTH=OBJ+0x7000;ZOBJ=OBJ+0xa000;OUT=OBJ+0x10000
ARG=OBJ+0x30000;STACK=OBJ+0x40000;STOP=OBJ+0x50000

class PresentationOracle:
    def __init__(self,exe,*,allow_patched=False):
        data=Path(exe).read_bytes()
        self.digest,self.profile=presentation_profile(data,allow_patched=allow_patched)
        pe=pefile.PE(data=data);self.u=Uc(UC_ARCH_X86,UC_MODE_32)
        base=pe.OPTIONAL_HEADER.ImageBase
        if base!=0x400000 or pe.FILE_HEADER.Machine!=0x14c:raise ValueError('Unsupported PE layout')
        self.u.mem_map(base,(pe.OPTIONAL_HEADER.SizeOfImage+4095)&~4095)
        for section in pe.sections:self.u.mem_write(base+section.VirtualAddress,section.get_data())
        self.u.mem_map(OBJ,0x60000)
        self.audit_calls=0;self.audit_blocks=0
    def va(self,disc_va):return address(self.profile,disc_va)
    def put(self,address,value):self.u.mem_write(address,struct.pack('<I',value&0xffffffff))
    def call(self,address,args=(),ecx=0,edx=0,budget=4000000):
        # This generic loader/call service deliberately accepts actual guest VAs.
        # Primitive methods below select explicit mappings. Other suites default
        # to their retained disc gate and do not inherit patched actor addresses.
        self.u.mem_write(STACK,struct.pack('<'+'I'*(len(args)+1),STOP,*[x&0xffffffff for x in args]))
        self.u.reg_write(UC_X86_REG_ESP,STACK);self.u.reg_write(UC_X86_REG_ECX,ecx);self.u.reg_write(UC_X86_REG_EDX,edx)
        self.u.reg_write(UC_X86_REG_FPCW,0xe7f)
        self.u.emu_start(address,STOP,count=budget)
        if self.u.reg_read(UC_X86_REG_EIP)!=STOP:raise RuntimeError('Original routine exceeded instruction bound')
    def checked_call(self,disc_va,args=(),ecx=0,edx=0,*,writes=(),inputs=()):
        preserved={UC_X86_REG_EBX:0x12345678,UC_X86_REG_ESI:0x23456789,
                   UC_X86_REG_EDI:0x3456789a,UC_X86_REG_EBP:0x456789ab}
        caller_end=STACK+4+4*len(args)
        guard=bytes([0xa7])*64;self.u.mem_write(caller_end,guard)
        before=[bytes(self.u.mem_read(p,n)) for p,n in inputs]
        for reg,value in preserved.items():self.u.reg_write(reg,value)
        # Consumed argument slots are scratch in palette/span routines. The
        # return address and stack beyond those slots are separately preserved.
        allowed=[(STACK-0x2000,STACK),(STACK+4,caller_end),*[(p,p+n) for p,n in writes]]
        def audit(u,access,p,n,value,context):
            if not any(lo<=p and p+n<=hi for lo,hi in allowed):
                raise AssertionError(f'Unexpected original presentation write {p:#x}/{n}')
        hook=self.u.hook_add(UC_HOOK_MEM_WRITE,audit)
        try:self.call(self.va(disc_va),args,ecx,edx)
        finally:self.u.hook_del(hook)
        if self.u.reg_read(UC_X86_REG_ESP)!=caller_end:raise AssertionError('Original caller ESP changed')
        if bytes(self.u.mem_read(STACK,4))!=struct.pack('<I',STOP):raise AssertionError('Original return address changed')
        if bytes(self.u.mem_read(caller_end,64))!=guard:raise AssertionError('Original caller stack changed')
        if any(self.u.reg_read(reg)!=v for reg,v in preserved.items()):raise AssertionError('Original callee-saved register changed')
        if any(bytes(self.u.mem_read(p,n))!=old for (p,n),old in zip(inputs,before)):raise AssertionError('Original primitive input changed')
        self.audit_calls+=1
    def lighting(self,kind,light,view,intensity,single=False):
        self.u.mem_write(ARG,struct.pack('<6f',*light,*view))
        shades=self.va(0xae0870)
        self.checked_call(0x710740,writes=[(shades,256)])
        if single:self.checked_call(0x710480,ecx=ARG,edx=kind,writes=[(shades,256)],inputs=[(ARG,24)])
        else:self.checked_call(0x710500,[struct.unpack('<I',struct.pack('<f',intensity))[0],kind],ARG,ARG+12,
                              writes=[(shades,256)],inputs=[(ARG,24)])
        return list(self.u.mem_read(shades,256))
    def palette(self,shades,tint,palette,mask):
        for off,value in [(0x16c,shades),(0x170,OUT),(0x188,PAL),(0x190,MASK)]:self.put(OBJ+off,value)
        self.u.mem_write(PAL,bytes(palette));self.u.mem_write(MASK,bytes(mask));self.put(self.va(0x7ca490),4)
        # Scalar channel consumers identify these globals: R, B, G (not R,G,B).
        for p,value in [(0x83b2c8,11),(0x83b2cc,3),(0x83b2d0,0),(0x83b2d4,3),(0x83b2d8,5),(0x83b2dc,2)]:self.put(self.va(p),value)
        self.checked_call(0x536b30,[*tint,0],OBJ,writes=[(OUT,shades*512),(OBJ+0x198,12),(OBJ+0x1b0,1)],
                          inputs=[(PAL,768),(MASK,256),(OBJ,0x198),(OBJ+0x1b1,15)])
        return list(struct.unpack('<'+'H'*(shades*256),self.u.mem_read(OUT,shades*512)))
    def vpl(self,blob,color,shade):
        # Original scalar rasterizer lookup block only; no callable ABI claim.
        vpl=self.va(0xadc068);shades=self.va(0xae0870)
        self.u.mem_write(vpl,blob[784:]);self.u.mem_write(shades,bytes([shade]))
        guards=bytes([0xa7])*128;self.u.mem_write(STACK,guards)
        for reg,value in [(UC_X86_REG_EDX,0),(UC_X86_REG_EBX,color),(UC_X86_REG_EDI,0),(UC_X86_REG_EBP,0),(UC_X86_REG_ESP,STACK)]:self.u.reg_write(reg,value)
        def audit(u,access,p,n,value,context):
            if (p,n)!=(STACK+0x3c,1):raise AssertionError('Unexpected original VPL lookup write')
        hook=self.u.hook_add(UC_HOOK_MEM_WRITE,audit)
        try:self.u.emu_start(self.va(0x70f4c9),self.va(0x70f4fc),count=100)
        finally:self.u.hook_del(hook)
        if self.u.reg_read(UC_X86_REG_EIP)!=self.va(0x70f4fc):raise RuntimeError('Lookup block did not finish')
        after=bytes(self.u.mem_read(STACK,128))
        if self.u.reg_read(UC_X86_REG_ESP)!=STACK or after[:0x3c]!=guards[:0x3c] or after[0x3d:]!=guards[0x3d:]:raise AssertionError('VPL block stack changed')
        self.audit_blocks+=1
        return [self.u.reg_read(UC_X86_REG_EDX)&255]
    def span(self,candidate,palette,source,destination,depth,start):
        self.put(OBJ+4,PAL);self.u.mem_write(PAL,struct.pack('<256H',*palette))
        if source:self.u.mem_write(SRC,bytes(source));self.u.mem_write(FRAME,struct.pack('<'+'H'*len(destination),*destination))
        self.u.mem_write(DEPTH,struct.pack('<'+'H'*len(depth),*depth))
        self.put(self.va(0x821f8c),ZOBJ);self.put(ZOBJ+0x1c,DEPTH+len(depth)*2);self.put(ZOBJ+0x20,len(depth)*2)
        self.checked_call(0x487750,[FRAME,SRC,len(source),candidate,DEPTH+start*2,0,0,0],OBJ,
                          writes=[(FRAME,len(destination)*2),(DEPTH,len(depth)*2)],
                          inputs=[(PAL,512),(SRC,len(source)),(OBJ,0x200),(ZOBJ,0x24)])
        return list(struct.unpack('<'+'H'*len(destination),self.u.mem_read(FRAME,2*len(destination))))+list(struct.unpack('<'+'H'*len(depth),self.u.mem_read(DEPTH,2*len(depth))))
