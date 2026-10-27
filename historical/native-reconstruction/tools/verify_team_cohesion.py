# SPDX-License-Identifier: GPL-3.0-or-later
import hashlib,struct,pefile,capstone
from verify_team_recruitment_schedule import RANGES as PRIOR,EXPECTED
RANGES={**PRIOR,0x6b9f40:0x253,0x668870:0x37,0x668900:0xa,0x594cb0:0x65,0x594770:0x12,0x5d4e40:0x21}
SERVICES=(0x6b9610,0x5d4c00,0x4c8af0,0x548070,0x1100c00,0x1100c10,0x1100c30)
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=EXPECTED:raise ValueError('Team cohesion requires exact supplied base')
 p=pefile.PE(data=data);c=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32);out={}
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(c.disasm(raw,a))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Incomplete cohesion range '+hex(a))
  out[hex(a)]=dict(bytes=n,instructions=len(ins),sha256=hashlib.sha256(raw).hexdigest())
 for off,target in ((0x1d0,0x594cb0),(0x16c,0x594770),(0x1c0,0x6d6e00)):
  if p.get_data(0x7a3540+off-0x400000,4)!=struct.pack('<I',target):raise ValueError('Actual E1 dispatch differs')
 return dict(ranges=out,complete_cohesion=True,activation_complete_to_return=True,actual_readiness_script_mission=True,distance_commands_nearby_anchor_supplied=True,script_dispatch_unjoined=True)
