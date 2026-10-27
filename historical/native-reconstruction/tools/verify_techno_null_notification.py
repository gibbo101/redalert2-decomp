# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact E1 null-attacker notification, actual Tag/Trigger/event mismatch and map children."""
import hashlib,struct,pefile,capstone
from verify_mission_tag import verify as tag_verify,RANGES as TAG_RANGES,TABLES as TAG_TABLES
RANGES={**TAG_RANGES,0x6ced90:0x373,0x509800:6,0x6331a0:0x1b,0x6331e0:0x28}
TABLES={**TAG_TABLES,0x6cf104:35}
TYPE80=0x5d2f000;COST84=0x5d2f010
SERVICES=(TYPE80,COST84)
def verify(data):
 parent=tag_verify(data);p=pefile.PE(data=data);c=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32);out={};ops={}
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(c.disasm(raw,a));assert sum(i.size for i in ins)==n and ins[-1].mnemonic=='ret',hex(a)
  ops.update({i.address:(i.mnemonic,i.op_str) for i in ins});out[hex(a)]=dict(bytes=n,instructions=len(ins),sha256=hashlib.sha256(raw).hexdigest())
 table=p.get_data(0x6cf104-0x400000,35)
 if struct.unpack_from('<I',table,4*table[20+14])[0]!=0x6cf059:raise ValueError('E1 notification switch differs')
 # Event7 follows the normal pulse-match gate; mismatches return before any
 # matching-event effects. Do not extend this claim to matching7 behavior.
 t=p.get_data(0x6e67ac-0x400000,54)
 if struct.unpack('<I',p.get_data(0x6e67a4+4*t[6]-0x400000,4))[0]!=0x6e6256:raise ValueError('Event7 mismatch dispatch differs')
 for off,target in ((0xdc,0x6ced90),(0x2c,0x509800)):
  if p.get_data(0x7a3540+off-0x400000,4)!=struct.pack('<I',target):raise ValueError('E1 notification vtable differs')
 for a,expected in {0x6cf0c4:('mov','dword ptr [eax + 0x5360], ecx'),0x6331ed:('mov','byte ptr [ecx + 0x14d5], al'),0x6331ff:('mov','byte ptr [ecx + 0x14d6], al')}.items():
  if ops.get(a)!=expected:raise ValueError('Notification/map store differs '+hex(a))
 return dict(tag=parent,ranges=out,tables={hex(a):hashlib.sha256(p.get_data(a-0x400000,n)).hexdigest() for a,n in TABLES.items()},complete_to_return_E1_null_attacker=True,actual_tag_trigger_event7_mismatch=True,actual_map_mode_dirty_children=True,type_cost_and_startup_supplied=True,matching_event7_and_live_transfer_unjoined=True)
