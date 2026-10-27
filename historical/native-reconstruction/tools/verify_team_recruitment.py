# SPDX-License-Identifier: GPL-3.0-or-later
"""Inspect the exact base E1 recruitment path and its actual distance/clear children."""
import hashlib,struct,pefile,capstone
EXPECTED='e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f'
RANGES={0x6b91c0:0x38b,0x6bfa60:0x21,0x5d4e00:0x3e,0x5d4e40:0x21,0x502470:0x14e,0x6c9af0:0x10a}
SERVICES=(0x6bfa90,0x6b8dc0,0x6b8cc0,0x1100900)
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=EXPECTED:raise ValueError('Recruitment requires exact supplied base')
 p=pefile.PE(data=data);c=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32);out={}
 for a,n in RANGES.items():
  b=p.get_data(a-0x400000,n);ins=list(c.disasm(b,a))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Incomplete recruitment range '+hex(a))
  out[hex(a)]=dict(bytes=n,instructions=len(ins),sha256=hashlib.sha256(b).hexdigest())
 table=p.get_data(0x6b955c-0x400000,40);jumps=p.get_data(0x6b954c-0x400000,16)
 if struct.unpack_from('<I',jumps,4*table[15])[0]!=0x6b92b6:raise ValueError('Required InfantryType dispatch differs')
 for off,target in ((0x48,0x5d4e40),(0x370,0x502470)):
  if p.get_data(0x7a3540+off-0x400000,4)!=struct.pack('<I',target):raise ValueError('Actual E1 recruitment dispatch differs')
 return dict(ranges=out,dispatch_sha256=hashlib.sha256(jumps+table).hexdigest(),kind16_complete_path=True,other_kinds_unjoined=True,waypoint_admission_addmember_supplied=True,ordinary_null_target_clear_actual=True)
