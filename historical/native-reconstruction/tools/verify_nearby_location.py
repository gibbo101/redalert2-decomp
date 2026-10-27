#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Fingerprint complete nearby-Cell policy and inspect its actual callers."""
import hashlib,struct
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_terrain_visibility import PATCHED_EXPECTED
RANGES={0x5502e0:0xa0a,0x4ba410:0x6e,0x49f600:0x12}
TABLES={0x817dfc:16384*4,0x79a738:4,0x79d578:8}
SERVICES={0x55a740:'Cell permission',0x550cf0:'rectangle admission',
 0x47c200:'burrowable predicate',0x6a6a50:'Cell-center projection'}
ASSOCIATIONS={0x550303:('cmp','edi, 0xffff'),0x5503b5:('cmp','eax, 0x20'),
 0x550525:('test','bl, bl'),0x550584:('cmp','dword ptr [esp + 0x18], 0x18'),
 0x550bc4:('mov','eax, dword ptr [0xa6f238]'),0x550bdc:('mov','eax, dword ptr [0xa40d2c]'),
 0x550be6:('idiv','ecx'),0x550c05:('idiv','esi'),0x550c90:('call','0x4ba410'),
 0x550ca1:('je','0x550cad'),0x550ce7:('ret','0x38')}
def verify(data):
 if hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact supplied nearby-location engine required')
 p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ranges={};ops={}
 if p.FILE_HEADER.Machine!=0x14c or p.OPTIONAL_HEADER.ImageBase!=0x400000:raise ValueError('Nearby-location PE differs')
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(cs.disasm(raw,a))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Incomplete nearby-location range '+hex(a))
  ranges[hex(a)]=dict(bytes=n,instructions=len(ins),sha256=hashlib.sha256(raw).hexdigest())
  ops.update((i.address,(i.mnemonic,i.op_str)) for i in ins)
 for a,op in ASSOCIATIONS.items():
  if ops.get(a)!=op:raise ValueError('Nearby-location association differs '+hex(a))
 callers={}
 for a,n,checks in ((0x4a1000,0x1649,{0x4a1bf6:('lea','esi, [ebp + 0x40]'),
   0x4a1f7b:('push','0x852998'),0x4a1f88:('call','0x476920')}),
  (0x7072d0,0x617,{0x7074ba:('call','0x5502e0'),0x7074aa:('lea','eax, [esp + 0x50]')})):
  raw=p.get_data(a-0x400000,n);ins={i.address:(i.mnemonic,i.op_str) for i in cs.disasm(raw,a)}
  for at,op in checks.items():
   if ins.get(at)!=op:raise ValueError('Nearby-location caller differs '+hex(at))
  callers[hex(a)]=dict(bytes=n,sha256=hashlib.sha256(raw).hexdigest(),inspection_only=True)
 if p.get_data(0x49f600-0x400000,0x12)!=bytes.fromhex('33c0a398298500a39c298500a3a0298500c3'):
  raise ValueError('Advance empty-coordinate initializer differs')
 return dict(ranges=ranges,tables={hex(a):dict(bytes=n,sha256=hashlib.sha256(p.get_data(a-0x400000,n)).hexdigest()) for a,n in TABLES.items()},
  services={hex(a):v for a,v in SERVICES.items()},caller_inspection=callers,
  scope='Complete 5502E0 nearby Cell enumeration/selection and actual table square root. Inline shared slot/fallback lookup executed. Permission, rectangle admission, burrowable predicate and projection are supplied services. Sentinel/frame/dimensions/Cells are supplied. Caller inspection is not execution of Unit Scatter, Advance6, Process or runtime.')
