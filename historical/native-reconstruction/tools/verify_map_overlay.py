#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin complete base overlay classifier, Cell resource and empty passability roots."""
import hashlib,struct
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_terrain_visibility import PATCHED_EXPECTED
RANGES={0x5dc0b0:0xbe,0x476ba0:0x112,0x478f40:0x1a9,0x55a660:0xd7,0x548070:0x38}
def verify(data):
    if hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact supplied engine required')
    pe=pefile.PE(data=data)
    if pe.OPTIONAL_HEADER.ImageBase!=0x400000 or pe.FILE_HEADER.Machine!=0x14c:raise ValueError('PE layout differs')
    cs=Cs(CS_ARCH_X86,CS_MODE_32);ranges={}
    for start,size in RANGES.items():
        blob=pe.get_data(start-0x400000,size);ins=list(cs.disasm(blob,start))
        if sum(i.size for i in ins)!=size or ins[-1].mnemonic!='ret':raise ValueError('Incomplete overlay range '+hex(start))
        ranges[hex(start)]={'bytes':size,'instructions':len(ins),'sha256':hashlib.sha256(blob).hexdigest()}
    if pe.get_data(0x79a738-0x400000,4)!=bytes(4):raise ValueError('Overlay speed zero differs')
    if struct.unpack('<d',pe.get_data(0x79c518-0x400000,8))[0]!=0.01:raise ValueError('Ordinary speed threshold differs')
    return {'ranges':ranges,'frame_table_sha256':hashlib.sha256(pe.get_data(0x7d2c10-0x400000,36)).hexdigest(),
      'scope':'Actual complete resource classifier and argument-zero resource amount/update, actual no-occupant overlay/ordinary passability nesting permission/map lookup. Resource/type registries, directions, initial Cells, Wheel speeds and frame-table inputs supplied. Missing-resource logging is an explicit service. No random replacement, original registry/INI/default construction, occupied Cells, parent recalculation/preparation, runtime or whole-frame parity.'}
