#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin the complete scoped Scatter join and actual world/destination children."""
import hashlib,struct
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_unit_scatter import verify as verify_scatter,RANGES as SCATTER,TABLES as ST
from verify_unit_destination import verify as verify_destination,RANGES as DEST,TABLES as DT
from verify_foot_layer import verify as verify_layer,RANGES as LAYER,TABLES as LT
from verify_unit_admission import verify as verify_admission,RANGES as ADMISSION
from verify_terrain_visibility import PATCHED_EXPECTED
RANGES={}
for group in (SCATTER,DEST,LAYER,ADMISSION,{0x6a6a50:0x17b,0x55a660:0xd7,0x548070:0x38,0x5d47d0:0x22,0x5d51e0:0x57,0x40dc20:0x29}):
 for a,n in group.items():RANGES[a]=max(n,RANGES.get(a,0))
TABLES={}
for group in (ST,DT,LT,{0x40dc4c:23,0x40dbfc:23,0x79a708:8,0x79a6f8:8,0x79a738:4,0x7a1fd0:16,0x79cbbc:0x414}):
 for a,n in group.items():TABLES[a]=max(n,TABLES.get(a,0))
def verify(data):
 if hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact supplied Scatter world engine required')
 inherited=[fn(data) for fn in (verify_scatter,verify_destination,verify_layer,verify_admission)]
 p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ranges={};ops={}
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(cs.disasm(raw,a))
  if sum(i.size for i in ins)!=n:raise ValueError('Incomplete Scatter world range '+hex(a))
  ranges[hex(a)]=dict(bytes=n,instructions=len(ins),sha256=hashlib.sha256(raw).hexdigest())
  ops.update((i.address,(i.mnemonic,i.op_str)) for i in ins)
 for a,op in {0x6a6a68:('mov','eax, dword ptr [esi + 4]'),0x6a6aae:('call','0x548070'),
  0x6a6ac9:('call','0x548070'),0x6a6af1:('sub','edi, 8'),0x6a6b01:('sub','ebp, 8'),
  0x6a6b33:('call','0x548070'),0x6a6b53:('lea','ecx, [ecx + eax*4]'),
  0x6a6b56:('shl','ecx, 7'),0x6a6b81:('cmp','cx, dx'),0x6a6b8e:('jle','0x6a6ba7'),
  0x6a6baf:('pop','edi'),0x5d520a:('call','0x548000'),0x5d522d:('call','0x548000'),
  0x705687:('call','0x40dc20'),0x7057cd:('test','byte ptr [ebx + 0x14], 1'),
  0x7057d1:('je','0x705822'),0x70581c:('mov','dword ptr [ebp + 0x4d0], edi')}.items():
  if ops.get(a)!=op:raise ValueError('Scatter world association differs '+hex(a))
 if p.get_data(0x7addf8+0x1a4-0x400000,4)!=struct.pack('<I',0x5d51e0):raise ValueError('Current Cell dispatch differs')
 table=p.get_data(0x40dc4c-0x400000,23)
 if struct.unpack_from('<I',table,4*table[8+10])[0]!=0x40dc45:raise ValueError('Cell Techno cast differs')
 return dict(inherited=inherited,ranges=ranges,tables={hex(a):dict(bytes=n,sha256=hashlib.sha256(p.get_data(a-0x400000,n)).hexdigest()) for a,n in TABLES.items()},
  scope='Complete nonzero-point ordinary Scatter with actual coordinates/layer/map/permission/level/Unit admission/projection/Cell destination and shared actor/Drive/Cells/fallback/RNG/lifetime. Mission7 Abstract Cell bit0 clear supported; mission16, zero-point pathfinder, bridge-adjusted commands, owned disposal and prior special profiles refused. Initial records/globals/associations supplied; no Cell dispatch/Advance6/Process/owned runtime join.')
