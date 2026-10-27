#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact base restriction default/store blocks and missing-key string/enum children."""
import hashlib
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_unit_model_inputs import verify as strings,COMPLETE as STRINGS
from verify_unit_metadata import COMPLETE as INDEX
COMPLETE={**INDEX,**STRINGS,0x46a970:0x5f,0x482eb0:0x4b,0x482f00:0x13,0x781f20:0xd0}
BLOCKS={0x70a607:3,0x70a61b:6,0x70ad45:0x20}
def verify(data):
    parent=strings(data);p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ranges={};instructions={}
    for a,n in {**COMPLETE,**BLOCKS}.items():
        raw=p.get_data(a-0x400000,n);ins=list(cs.disasm(raw,a))
        if sum(i.size for i in ins)!=n or (a in COMPLETE and ins[-1].mnemonic!='ret'):raise ValueError('Incomplete restriction range')
        instructions.update({i.address:(i.mnemonic,i.op_str) for i in ins})
        ranges[hex(a)]={'bytes':n,'instructions':len(ins),'sha256':hashlib.sha256(raw).hexdigest(),'scoped_block':a in BLOCKS}
    for a,op in {0x70a607:('or','edi, 0xffffffff'),0x70a61b:('mov','dword ptr [esi + 0xb94], edi'),
        0x70ad45:('mov','edx, dword ptr [edi + 0xb94]'),0x70ad4e:('push','0x7f9328'),
        0x70ad5a:('call','0x46a970'),0x70ad5f:('mov','dword ptr [edi + 0xb94], eax')}.items():
        if instructions.get(a)!=op:raise ValueError('Restriction association differs')
    if p.get_data(0x7f9328-0x400000,21)!=b'MovementRestrictedTo\0':raise ValueError('Restriction key differs')
    return {'string_index_parent':parent,'ranges':ranges,
        'enum_name_table_sha256':hashlib.sha256(p.get_data(0x7d3878-0x400000,48)).hexdigest(),
        'scope':'Scoped constructor/default and missing-section/key loader blocks with actual ReadString, trim, copy and locale-zero enum helpers. Supplied decoded hot indexes and live registers; no full constructor, text parser, present-value enum or startup proof.'}
