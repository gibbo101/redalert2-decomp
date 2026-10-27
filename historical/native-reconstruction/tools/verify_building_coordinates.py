# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact Building coordinate dispatch, type helpers and immutable table spans."""
import hashlib,struct
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_cell_visibility_discovery import verify as verify_parent,RANGES as PARENT
RANGES={**PARENT,0x444080:0x54,0x458930:14,0x458940:0x3d}
TABLES={0x7cfc70:88,0x7cfcc8:88}
def tables(data):
 p=pefile.PE(data=data)
 return [list(struct.unpack('<22i',p.get_data(a-0x400000,n))) for a,n in TABLES.items()]
def verify(data):
 parent=verify_parent(data);p=pefile.PE(data=data);ops={};ranges={}
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(raw,a))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Incomplete Building coordinate range')
  ranges[hex(a)]=dict(bytes=n,sha256=hashlib.sha256(raw).hexdigest());ops.update((i.address,(i.mnemonic,i.op_str)) for i in ins)
 for vt,target in ((0x79cbbc,0x444080),(0x7a3540,0x5d4e40)):
  if p.get_data(vt+0x48-0x400000,4)!=struct.pack('<I',target):raise ValueError('Building/Infantry coordinate dispatch differs')
 for a,op in {0x44408c:('call','0x458940'),0x4440a2:('call','0x458930'),0x4440a7:('add','edi, 0x88'),0x444099:('shl','esi, 7'),0x4440ad:('shl','eax, 7'),0x458930:('mov','eax, dword ptr [ecx + 0xc78]'),0x458936:('mov','eax, dword ptr [eax*4 + 0x7cfc70]'),0x458948:('mov','al, byte ptr [ecx + 0x1214]'),0x458971:('mov','eax, dword ptr [eax*4 + 0x7cfcc8]')}.items():
  if ops.get(a)!=op:raise ValueError('Building coordinate association differs '+hex(a))
 return dict(parent=parent,ranges=ranges,table_spans={hex(a):dict(bytes=n,sha256=hashlib.sha256(p.get_data(a-0x400000,n)).hexdigest()) for a,n in TABLES.items()},scope='Complete444080/458930/458940 and closest471660 with actual Building/Infantry coordinate dispatch; 22 supplied type-table indices; startup/foundation mapping supplied.')
