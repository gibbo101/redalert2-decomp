#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact-base complete font measurement, width wrapper and prefix fitting."""
import hashlib,struct,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_string_lookup import EXPECTED
RANGES={0x4314b0:0x1b5,0x431690:0x1d,0x431710:0x14b}
TABLES={0x431668:16,0x431678:24}
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=EXPECTED:raise ValueError('Font metrics require exact supplied base')
 p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ops={};ranges={}
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(cs.disasm(raw,a))
  if sum(i.size for i in ins)!=n:raise ValueError('Incomplete message font inspection')
  ranges[hex(a)]=dict(bytes=n,sha256=hashlib.sha256(raw).hexdigest());ops.update({i.address:(i.mnemonic,i.op_str) for i in ins})
 for a,op in {0x4314b3:('mov','eax, dword ptr [ecx + 4]'),0x43151c:('jmp','dword ptr [ecx*4 + 0x431668]'),0x431550:('idiv','edi'),0x431574:('mov','dx, word ptr [ecx + edi*2]'),0x431587:('add','eax, dword ptr [ecx + 0x1c]'),0x4315c9:('mov','ebx, ecx'),0x43162f:('mov','dword ptr [eax], ecx'),0x43163d:('mov','dword ptr [eax], edx'),0x431650:('mov','dword ptr [eax], edx'),0x43165a:('mov','dword ptr [eax], edx'),0x4316a1:('call','0x4314b0'),0x43176e:('mov','dx, word ptr [ecx + esi*2]'),0x4317ac:('idiv','esi'),0x4317bb:('mov','dword ptr [esp + 0x10], edx'),0x43181f:('cmp','word ptr [ecx], 0x20')}.items():
  if ops.get(a)!=op:raise ValueError('Message font association differs '+hex(a))
 jumps=struct.unpack('<4I',p.get_data(0x431668-0x400000,16));dispatch=p.get_data(0x431678-0x400000,24)
 if any(v>=4 or jumps[v]!=(0x431544 if i+9==9 else 0x431523 if i+9 in (10,13) else 0x431559 if i+9==32 else 0x431565) for i,v in enumerate(dispatch)):raise ValueError('Message font control dispatch differs')
 return dict(executable_sha256=EXPECTED,ranges=ranges,tables={hex(a):hashlib.sha256(p.get_data(a-0x400000,n)).hexdigest() for a,n in TABLES.items()},scope='Complete4314B0/431690/431710; actual index/glyph/fallback byte reads. Font loading/initial associations, message insertion and drawing remain unjoined. Faulting tab division and host work bound explicitly refuse.')
