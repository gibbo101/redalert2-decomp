#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin complete Cell recalculation and ordinary resident validation/index children."""
import hashlib
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import pefile
from verify_map_cell_inputs import verify as input_verify,RANGES as INPUT_RANGES
RANGES={**INPUT_RANGES,0x472540:0xab2,0x529340:0x53,0x54fab0:0x36}
def verify(data):
    inputs=input_verify(data);pe=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ranges={}
    for a,n in RANGES.items():
        b=pe.get_data(a-0x400000,n);ins=list(cs.disasm(b,a))
        if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Incomplete Cell attribute range '+hex(a))
        ranges[hex(a)]={'bytes':n,'instructions':len(ins),'sha256':hashlib.sha256(b).hexdigest()}
    return {'inputs':inputs,'ranges':ranges,'scope':'Complete Cell recalculation, no overlay, resident TMP, no new tube/animation allocation or shadow-casting neighbor writes. Actual validation/getter/land/ramp/dimensions and clamped map buffer index execute. LAT and passability, immutable neighbor records, construction/registry/buffers are supplied services. No runtime initialization, original decompression, LAT/passability recovery, allocation/ownership or full-frame parity.'}
