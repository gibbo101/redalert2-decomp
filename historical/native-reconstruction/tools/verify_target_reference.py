# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact-base target construction/resolution/cast and compiled registry sort."""
import hashlib,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from presentation_profiles import PATCHED_EXPECTED
RANGES={0x6b54a0:0x66,0x6b5910:0xc4,0x40dc20:0x29,0x41ba10:0x22,0x781d46:0x154,0x781e9a:0x4e,0x781ee8:0x2c}
TABLES={0x40dc4c:8,0x40dc54:15}
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact supplied target reference executable required')
 p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ops={};ranges={}
 if p.FILE_HEADER.Machine!=0x14c or p.OPTIONAL_HEADER.ImageBase!=0x400000:raise ValueError('Target reference PE differs')
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(cs.disasm(raw,a))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Incomplete target reference root')
  ops.update({i.address:(i.mnemonic,i.op_str) for i in ins});ranges[hex(a)]=dict(bytes=n,sha256=hashlib.sha256(raw).hexdigest())
 expected={0x6b54b0:('call','dword ptr [eax + 0x2c]'),0x6b54b8:('mov','byte ptr [esi + 4], al'),0x6b54df:('lea','eax, [edi + 4]'),0x6b54e2:('mov','byte ptr [esi + 4], 0x34'),0x6b54e9:('call','dword ptr [ecx + 0x10]'),0x6b5957:('call','0x781d46'),0x6b5965:('mov','dword ptr [0xabff68], 0'),0x6b596f:('mov','byte ptr [0xabff64], 1'),0x6b59bb:('mov','dword ptr [0xabff68], edx'),0x6b59c7:('call','0x40dc20'),0x781d9c:('call','0x781e9a'),0x781e31:('cmp','ecx, edx'),0x781e33:('jl','0x781e65'),0x781ec5:('jle','0x781ec9'),0x41ba1c:('cmp','eax, ecx')}
 for a,op in expected.items():
  if ops.get(a)!=op:raise ValueError('Target reference association differs '+hex(a))
 for a,raw in ((0x40dc4c,bytes.fromhex('41dc400045dc4000')),(0x40dc54,bytes.fromhex('000001010100010101010101010100'))):
  if p.get_data(a-0x400000,len(raw))!=raw:raise ValueError('Target cast table differs')
 return dict(ranges=ranges,tables={hex(a):hashlib.sha256(p.get_data(a-0x400000,n)).hexdigest() for a,n in TABLES.items()},scope='Complete target construction/resolution/cast and unchanged compiled sort/comparator; virtual kind/ID, initial objects/registry and disjoint host storage supplied. No MakeAlly/production adoption.')
