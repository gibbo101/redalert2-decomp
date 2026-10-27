# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete E1 discovery through actual Tag/event7 mismatch; no action effects."""
import hashlib,struct,pefile,capstone
from verify_mission_tag import verify as tag_verify,RANGES as TAG_RANGES,TABLES
RANGES={**TAG_RANGES,0x6c2440:0xdf,0x5d4230:14,0x4f52f0:0x23,0x594770:18,0x594cb0:0x65}
def verify(data):
 parent=tag_verify(data);p=pefile.PE(data=data);c=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32);out={};ops={}
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(c.disasm(raw,a));assert sum(i.size for i in ins)==n and ins[-1].mnemonic=='ret',hex(a)
  ops.update({i.address:(i.mnemonic,i.op_str) for i in ins});out[hex(a)]=dict(bytes=n,instructions=len(ins),sha256=hashlib.sha256(raw).hexdigest())
 for off,target in ((0x180,0x6c2440),(0x16c,0x594770),(0x1d0,0x594cb0)):
  if p.get_data(0x7a3540+off-0x400000,4)!=struct.pack('<I',target):raise ValueError('E1 discovery vtable differs')
 for a,op in {0x6c24f6:('push','4'),0x6c24f8:('call','0x6b3df0'),0x6c24fd:('mov','eax, dword ptr [esi + 0x1b4]'),0x4ed77a:('cmp','dword ptr [ebx + 0xb8], ecx')}.items():
  if ops.get(a)!=op:raise ValueError('Tagged discovery operation differs '+hex(a))
 return dict(tag=parent,ranges=out,complete_E1_discovery=True,actual_tag_trigger_event7_mismatch=True,startup_and_country_association_supplied=True,matching_event7_and_live_transfer_unjoined=True)
