#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact base rectangle/Cell admission and direct-Cell permission roots."""
import hashlib
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_terrain_visibility import PATCHED_EXPECTED
RANGES={0x478760:0x163,0x550cf0:0xce,0x55a740:0xaf}
TABLES={0x79a738:4}
SERVICES={0x54f8f0:'supplied movement-zone resolver'}
ASSOCIATIONS={0x478767:('cmp','eax, 4'),0x47878f:('call','0x54f8f0'),
 0x478808:('mov','al, byte ptr [esi + 0x128]'),0x478812:('mov','al, byte ptr [esi + 0x124]'),
 0x478820:('and','eax, 0xe0'),0x47882d:('and','eax, 0x5f'),
 0x478899:('fld','dword ptr [eax*4 + 0x850ea0]'),0x4788a8:('test','ah, 0x40'),
 0x550d5d:('mov','dword ptr [0xa6fa1c], eax'),0x550d89:('call','0x478760'),
 0x55a760:('movsx','esi, byte ptr [eax + 0x11b]'),0x55a7ec:('ret','8')}
def verify(data):
 if hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact supplied Cell admission engine required')
 p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ranges={};ops={}
 if p.FILE_HEADER.Machine!=0x14c or p.OPTIONAL_HEADER.ImageBase!=0x400000:raise ValueError('Cell admission PE differs')
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(cs.disasm(raw,a))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Incomplete Cell admission range '+hex(a))
  ranges[hex(a)]=dict(bytes=n,instructions=len(ins),sha256=hashlib.sha256(raw).hexdigest())
  ops.update((i.address,(i.mnemonic,i.op_str)) for i in ins)
 for a,op in ASSOCIATIONS.items():
  if ops.get(a)!=op:raise ValueError('Cell admission association differs '+hex(a))
 return dict(ranges=ranges,tables={hex(a):dict(bytes=n,sha256=hashlib.sha256(p.get_data(a-0x400000,n)).hexdigest()) for a,n in TABLES.items()},
  services={hex(a):v for a,v in SERVICES.items()},
  scope='Complete rectangle550CF0, Cell478760 policy and direct Cell permission55A740. Zone54F8F0 is supplied; zone-1 bypasses it. Initial Cells/occupation/overlay/types/speeds/geometry/slots supplied. No nearby parent, Unit Scatter, Advance6, Process or runtime join.')
