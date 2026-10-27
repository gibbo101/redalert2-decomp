#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin the actual complete full-coordinate Cell lookup in the supplied base engine."""
import hashlib,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from compare_original import PATCHED_EXPECTED
ROOT=0x548000;SIZE=0x68
def verify(data):
 if hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact supplied engine required')
 p=pefile.PE(data=data)
 if p.FILE_HEADER.Machine!=0x14c or p.OPTIONAL_HEADER.ImageBase!=0x400000:raise ValueError('Coordinate lookup PE layout differs')
 raw=p.get_data(ROOT-0x400000,SIZE);ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(raw,ROOT))
 if sum(i.size for i in ins)!=SIZE or ins[-1].mnemonic!='ret' or ins[-1].op_str!='4':raise ValueError('Incomplete coordinate lookup')
 return {'root':hex(ROOT),'bytes':SIZE,'instructions':len(ins),'sha256':hashlib.sha256(raw).hexdigest(),
  'scope':'Complete signed full-world-coordinate Cell lookup, wrapped combined index, supplied table/count and shared fallback word-position store. Initial map/Cell/storage construction supplied; no startup, floor height, actor placement/update or malformed pointer parity.'}
