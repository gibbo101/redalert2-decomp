# SPDX-License-Identifier: GPL-3.0-or-later
"""Actual land assignment with explicit INI-result/FPU-return services."""
import hashlib
import struct
from original_presentation import PresentationOracle, OBJ, STOP, STACK
from original_foot_lit import words, ret
from verify_land_characteristics import verify, ROOT, SIZE, KEY_POINTERS
from unicorn import UC_HOOK_CODE, UC_HOOK_MEM_WRITE
from unicorn.x86_const import (UC_X86_REG_ECX, UC_X86_REG_EAX, UC_X86_REG_ESP,
    UC_X86_REG_FP0, UC_X86_REG_FPCW, UC_X86_REG_FPSW, UC_X86_REG_FPTAG)

TABLE = 0x850EA0
SERVICES = {0x50C9B0, 0x50E3A0, 0x50F410}

def pack(values):
    return b''.join(struct.pack('<I', n & 0xffffffff) for n in values)

def push_double(u, bits):
    # Supply the declared double-return ABI as an extended x87 value. These are
    # host register writes, not original INI parser behavior or guest instructions.
    sign, exponent, fraction = bits >> 63, (bits >> 52) & 2047, bits & ((1 << 52)-1)
    if exponent == 2047:
        mantissa, exp80 = (1 << 63) | (fraction << 11), 0x7fff
    elif exponent:
        mantissa, exp80 = ((1 << 52) | fraction) << 11, exponent-1023+16383
    elif fraction:
        high = fraction.bit_length()-1
        mantissa, exp80 = fraction << (63-high), high-1074+16383
    else:
        mantissa = exp80 = 0
    status = u.reg_read(UC_X86_REG_FPSW)
    top = ((status >> 11)-1) & 7
    tag = 1 if not (mantissa or exp80) else 2 if exp80 == 0x7fff else 0
    tags = u.reg_read(UC_X86_REG_FPTAG)
    u.reg_write(UC_X86_REG_FP0+top, (mantissa, exp80 | (sign << 15)))
    u.reg_write(UC_X86_REG_FPSW, (status & ~0x3800) | (top << 11))
    u.reg_write(UC_X86_REG_FPTAG, (tags & ~(3 << (top*2))) | (tag << (top*2)))

class LandCharacteristicOracle(PresentationOracle):
    def __init__(self, exe):
        self.inspection = verify(exe.read_bytes())
        super().__init__(exe, allow_patched=True)
        self.sections = words(self.u, 0x7eebbc, 12)
        self.entries = self.service_calls = self.stores = 0
        self.u.hook_add(UC_HOOK_CODE, self.code)

    def va(self, a):
        return a

    def code(self, u, a, n, ctx):
        if a == ROOT:
            self.entries += 1
            u.reg_write(UC_X86_REG_FPCW, self.control)
            u.reg_write(UC_X86_REG_FPSW, 0)
            u.reg_write(UC_X86_REG_FPTAG, 0xffff)
        if ROOT <= a and a+n <= ROOT+SIZE:
            return
        if a not in SERVICES:
            raise AssertionError(f'Uninspected land instruction {a:#x}')
        sp = u.reg_read(UC_X86_REG_ESP)
        assert ROOT <= words(u,sp,1)[0] < ROOT+SIZE
        assert u.reg_read(UC_X86_REG_ECX) == OBJ
        section = self.sections.index(words(u, sp+4, 1)[0])
        row = self.rows[section]
        self.service_calls += 1
        if a == 0x50c9b0:
            self.events.extend([0,section,row[0]])
            ret(u,4,row[0])
        elif a == 0x50e3a0:
            key, lo, hi = words(u, sp+8, 3)
            assert (lo,hi) == (0,0x3ff00000)
            key = KEY_POINTERS[key]
            index = (3,0,1,2,5,6,7).index(key)
            count = self.read_counts[section][index]
            assert count < 2
            self.read_counts[section][index] += 1
            bits = row[11+index*2+count]
            self.events.extend([1,section,key,lo,hi,bits & 0xffffffff,bits >> 32])
            push_double(u,bits)
            ret(u,16,0)
        else:
            key, default = words(u, sp+8, 2)
            assert key == 0x7f1a10 and default == 0
            self.events.extend([2,section,default,row[1]])
            ret(u,12,row[1])

    def run(self, mode, rows):
        self.rows, self.events = rows, []
        self.read_counts = [[0]*7 for _ in range(12)]
        self.control = 0x27f | (mode << 10)  # supplied 53-bit precision + rounding
        blob = bytearray(b'\xa7'*(12*36+64))
        for section,row in enumerate(rows):
            struct.pack_into('<8I',blob,section*36,*row[2:10])
            blob[section*36+32] = row[10]
        self.u.mem_write(TABLE,bytes(blob))
        self.u.mem_write(OBJ,b'\xa5'*128)
        def stores(u, access, p, n, value, ctx):
            if not TABLE <= p < TABLE+12*36:
                return
            section, offset = divmod(p-TABLE,36)
            assert (offset < 32 and offset%4 == 0 and n == 4) or (offset == 32 and n == 1)
            self.events.extend([3,section,offset//4,value & ((1 << (n*8))-1)])
            self.stores += 1
        hook = self.u.hook_add(UC_HOOK_MEM_WRITE,stores)
        try:
            self.checked_call(ROOT,[OBJ],ecx=OBJ,writes=[(TABLE,12*36)],
                inputs=[(OBJ,128),(0x7eebbc,48),(0x79a708,8),
                        *[(p,len(name)+1) for p,name in zip(self.sections,self.inspection['sections'])]])
        finally:
            self.u.hook_del(hook)
        assert self.u.reg_read(UC_X86_REG_EAX) & 255 == 1
        assert self.u.reg_read(UC_X86_REG_FPCW) == self.control
        assert (self.u.reg_read(UC_X86_REG_FPSW) >> 11) & 7 == 0
        assert self.u.reg_read(UC_X86_REG_FPTAG) == 0xffff
        actual = bytes(self.u.mem_read(TABLE,len(blob)))
        for section in range(12):
            assert actual[section*36+33:section*36+36] == b'\xa7'*3
        assert actual[-64:] == b'\xa7'*64
        state = []
        for section in range(12):
            state.extend(words(self.u,TABLE+section*36,8))
            state.append(actual[section*36+32])
        return [hashlib.sha256(pack(state)).hexdigest(),hashlib.sha256(pack(self.events)).hexdigest()]
