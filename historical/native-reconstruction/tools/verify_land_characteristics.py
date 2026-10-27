#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin the complete base land-characteristic assignment parent and INI key mapping."""
import hashlib
import struct
import pefile
from capstone import Cs, CS_ARCH_X86, CS_MODE_32
from verify_terrain_visibility import PATCHED_EXPECTED

ROOT = 0x64D610
SIZE = 0x238
SECTIONS = ('Clear','Road','Water','Rock','Wall','Tiberium','Beach','Rough','Ice','Railroad','Tunnel','Weeds')
KEYS = ('Foot','Track','Wheel','Hover','Winged','Float','Amphibious','FloatBeach')
KEY_POINTERS = {0x7D3A0C:3, 0x7D3A24:0, 0x7D3A1C:1, 0x7D3A14:2, 0x7D39FC:5, 0x7D1AE8:6, 0x7D39F0:7}

def verify(data):
    if hashlib.sha256(data).hexdigest() != PATCHED_EXPECTED:
        raise ValueError('Exact supplied engine required')
    pe = pefile.PE(data=data)
    raw = pe.get_data(ROOT-0x400000, SIZE)
    ins = list(Cs(CS_ARCH_X86, CS_MODE_32).disasm(raw, ROOT))
    if sum(i.size for i in ins) != SIZE or ins[-1].mnemonic != 'ret':
        raise ValueError('Incomplete land parent')
    pointers = struct.unpack('<12I', pe.get_data(0x7EEBBC-0x400000, 48))
    string = lambda a: pe.get_string_at_rva(a-0x400000).decode('ascii')
    if tuple(map(string, pointers)) != SECTIONS:
        raise ValueError('Land section mapping differs')
    if any(string(p) != KEYS[k] for p,k in KEY_POINTERS.items()) or string(0x7F1A10) != 'Buildable':
        raise ValueError('Land key mapping differs')
    if struct.unpack('<d', pe.get_data(0x79A708-0x400000, 8))[0] != 1.0:
        raise ValueError('Land upper bound differs')
    return {'root':hex(ROOT),'bytes':SIZE,'instructions':len(ins),'sha256':hashlib.sha256(raw).hexdigest(),
            'sections':list(SECTIONS),'keys':list(KEYS),'table':'0x850ea0, twelve 36-byte records',
            'scope':'Complete unchanged assignment parent. Section presence, double INI results, Buildable result and initial table are supplied. Caller FP rounding is supplied and preserved; no original text parsing/static initialization/rules layering/pathfinding/runtime or whole-frame parity.'}
