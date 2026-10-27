# SPDX-License-Identifier: GPL-3.0-or-later
"""Focused authored x87 return ABI, shared convention with land-characteristic probes.

Kept free of unrelated verifier/oracle imports for dependency-scoped proofs.
"""
from unicorn.x86_const import UC_X86_REG_FP0,UC_X86_REG_FPSW,UC_X86_REG_FPTAG

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
