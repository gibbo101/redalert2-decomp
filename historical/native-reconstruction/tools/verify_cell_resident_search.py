#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin complete471760 before using its addresses."""
import hashlib
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_terrain_visibility import PATCHED_EXPECTED
HELPER=(0x471760,0x4717a9)
DIGEST='109abad9e6cbc6937c0fd51bae3d49998934cbb22f6d842ff7da5b147c91ad90'
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact supplied resident-search engine required')
 pe=pefile.PE(data=data);raw=pe.get_data(HELPER[0]-0x400000,HELPER[1]-HELPER[0]);ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(raw,HELPER[0]))
 if hashlib.sha256(raw).hexdigest()!=DIGEST or sum(i.size for i in ins)!=len(raw):raise ValueError('Incomplete/changed resident search')
 decoded={i.address:(i.mnemonic,i.op_str) for i in ins}
 for a,op in {0x471760:('mov','al, byte ptr [0xa40958]'),0x47176b:('mov','al, byte ptr [esp + 0x10]'),0x471773:('mov','esi, dword ptr [ecx + 0xe8]'),0x47177b:('mov','esi, dword ptr [ecx + 0xe4]'),0x47178d:('call','dword ptr [eax + 0x2c]'),0x471790:('cmp','eax, edi'),0x471794:('mov','esi, dword ptr [esi + 0x30]'),0x47179f:('ret','8'),0x4717a6:('ret','8')}.items():
  if decoded.get(a)!=op:raise ValueError('Resident-search association differs')
 return dict(ranges={hex(HELPER[0]):dict(bytes=len(raw),sha256=DIGEST,instructions=len(ins))},scope='Complete471760; virtual kind supplied, stable authored resident lists and scenario gate. No constructor or production scheduling claim.')
