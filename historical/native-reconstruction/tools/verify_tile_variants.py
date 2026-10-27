#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin complete Cell variant selector, actual RNG step and resident image getter."""
import hashlib
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_terrain_visibility import PATCHED_EXPECTED
from verify_map_cell_inputs import RANGES as INPUT_RANGES
RANGES={0x4767a0:0x179,0x638840:0x51,0x5293d0:INPUT_RANGES[0x5293d0]}
def verify(data):
    if hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact supplied engine required')
    p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ranges={}
    for a,n in RANGES.items():
        raw=p.get_data(a-0x400000,n);ins=list(cs.disasm(raw,a))
        if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Incomplete variant range')
        ranges[hex(a)]={'bytes':n,'instructions':len(ins),'sha256':hashlib.sha256(raw).hexdigest()}
    tables={hex(a):hashlib.sha256(p.get_data(a-0x400000,64)).hexdigest() for a in (0x7d2b90,0x7d2bd0)}
    return {'ranges':ranges,'table_sha256':tables,
      'scope':'Complete Cell variant selector with actual 250-word XOR generator and resident/null GetImage. Supplied original pattern/direction tables, initial RNG/cache state, coordinates/sub/type count and resident header. Compare raw result, full RNG/cache state and RNG call count. No RNG seeding/global lifetime, parent usage/count reduction, lazy image loading, complete map initialization, runtime or whole-frame claim.'}
