# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact base Object pointer-expiration callback entered with Tag subjects."""
import hashlib
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from compare_original import PATCHED_EXPECTED
RANGES={0x5d3bd0:0x3b}
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Different supplied base executable')
 p=pefile.PE(data=data);raw=p.get_data(0x5d3bd0-0x400000,0x3b);ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(raw,0x5d3bd0))
 if sum(i.size for i in ins)!=len(raw) or ins[-1].mnemonic!='ret' or ins[-1].op_str!='8':raise ValueError('Incomplete Object expiration callback')
 ops={i.address:(i.mnemonic,i.op_str) for i in ins}
 for a,op in {0x5d3bd0:('mov','eax, dword ptr [ecx + 0x34]'),0x5d3be4:('mov','dword ptr [eax + 0x2c], esi'),
  0x5d3be7:('mov','dword ptr [ecx + 0x34], 0'),0x5d3bef:('mov','al, byte ptr [esp + 8]'),
  0x5d3c02:('mov','eax, dword ptr [eax + 0x30]'),0x5d3c05:('mov','dword ptr [ecx + 0x30], eax')}.items():
  if ops.get(a)!=op:raise ValueError('Object expiration association differs '+hex(a))
 return dict(ranges={'0x5d3bd0':dict(bytes=len(raw),sha256=hashlib.sha256(raw).hexdigest())},
  scope='Complete Object pointer-expiration callback with Tag subject, wrapped reference count and raw removed low-byte link splice. Initial associations supplied; no broadcast/drain/discovery/runtime.')
