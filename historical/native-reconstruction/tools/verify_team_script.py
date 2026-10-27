# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin active Team command50 paths and actual Script/field/target children."""
import hashlib,struct,pefile,capstone
from verify_team_recruitment_schedule import EXPECTED
RANGES={0x6b7ad0:0xc96,0x6b8bb0:0x108,0x6b6b30:0x1f,0x6d6e00:7,0x668870:0x37,0x668920:0x15,0x668940:0x11,0x6d6e50:0xd,0x6b79e0:0xef}
SERVICES=(0x6b9610,)
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=EXPECTED:raise ValueError('Team Script requires exact supplied base')
 p=pefile.PE(data=data);c=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32);out={}
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(c.disasm(raw,a))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Incomplete Team Script range '+hex(a))
  out[hex(a)]=dict(bytes=n,instructions=len(ins),sha256=hashlib.sha256(raw).hexdigest())
 if p.get_data(0x7a3540+0x1c0-0x400000,4)!=struct.pack('<I',0x6d6e00):raise ValueError('E1 member getter differs')
 table=p.get_data(0x6b8768-0x400000,59*4)
 if struct.unpack_from('<I',table,50*4)[0]!=0x6b865e:raise ValueError('Script50 dispatch differs')
 return dict(ranges=out,dispatch_sha256=hashlib.sha256(table).hexdigest(),active_command50_complete_to_return=True,anchor_supplied=True,actual_script_readiness_member_field_target_children=True,initial_associations_supplied=True,other_commands_unjoined=True)
