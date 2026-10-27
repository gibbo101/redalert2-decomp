#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete base glyph raster and its inclusive intersection child."""
import hashlib,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_string_lookup import EXPECTED
RANGES={0x4318e0:0x3dd,0x432000:0xa2}
TABLES={}
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=EXPECTED:raise ValueError('Glyph raster requires exact supplied base')
 p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ops={};ranges={}
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(cs.disasm(raw,a))
  if sum(i.size for i in ins)!=n:raise ValueError('Incomplete glyph inspection')
  ranges[hex(a)]=dict(bytes=n,sha256=hashlib.sha256(raw).hexdigest());ops.update({i.address:(i.mnemonic,i.op_str) for i in ins})
 for a,op in {0x431908:('idiv','ecx'),0x431960:('xor','dword ptr [esp + 0x44], 0x5555'),0x431995:('mov','edi, dword ptr [ecx + 8]'),0x4319ca:('call','dword ptr [0x79a4a8]'),0x4319e4:('call','0x432000'),0x431bf8:('sub','eax, 8'),0x431c02:('mov','word ptr [ecx], si'),0x432055:('mov','dword ptr [eax + 4], ecx')}.items():
  if ops.get(a)!=op:raise ValueError('Glyph association differs '+hex(a))
 imports={i.address:(d.dll.decode(),i.name.decode() if i.name else '') for d in p.DIRECTORY_ENTRY_IMPORT for i in d.imports}
 if imports.get(0x79a4a8)!=('USER32.dll','SetRect'):raise ValueError('Glyph rectangle import differs')
 return dict(executable_sha256=EXPECTED,ranges=ranges,scope='Complete4318E0 and432000, supplied SetRect and initial font/surface associations; text, surface binding, message drawing and production UI remain open.')
