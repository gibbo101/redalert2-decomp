#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin complete wall-update/connection and rectangle numeric children."""
import hashlib,struct
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_terrain_visibility import PATCHED_EXPECTED
RANGES={0x475960:0x3f7,0x475840:0x114,0x42add0:0x29,
        0x45efe0:0xf0,0x47d040:0x20,0x453e40:0x21}
def verify(data):
    if hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact supplied engine required')
    pe=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ranges={}
    if pe.OPTIONAL_HEADER.ImageBase!=0x400000 or pe.FILE_HEADER.Machine!=0x14c:raise ValueError('PE layout differs')
    for a,n in RANGES.items():
        blob=pe.get_data(a-0x400000,n);ins=list(cs.disasm(blob,a))
        if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Incomplete wall-update range '+hex(a))
        ranges[hex(a)]={'bytes':n,'instructions':len(ins),'sha256':hashlib.sha256(blob).hexdigest()}
    visits=list(struct.unpack('<5i',pe.get_data(0x7d2b58-0x400000,20)))
    if visits!=[0,2,4,6,-1]:raise ValueError('Wall visit table differs')
    return {'ranges':ranges,'visits':visits,
      'scope':'Complete wall update/connection with actual word addition, asymmetric union, wrapped point subtraction and rectangle constructor. Cell/image bounds/camera, lookup, virtual occupant kinds/storage, map/zone/dirty notifications, pointer broadcasts and recalculation are supplied. Native union binds earlier recovered rendering kernel. No complete image/camera/queue/zone/Cell preparation, ownership/runtime or whole-frame claim.'}
