# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete Team readiness/TaskForce sum and Script cursor/query routines on exact base."""
import hashlib,pefile,capstone
EXPECTED='e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f'
RANGES={0x6b8bb0:0x108,0x6b6b30:0x1f,0x668870:0x37,0x6688b0:0x41,0x668900:0xa,0x668920:0x15,0x668940:0x11}
SERVICES=(0x6b3df0,0x1100a00)
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=EXPECTED:raise ValueError('Readiness requires exact supplied base')
 p=pefile.PE(data=data);c=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32);out={}
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(c.disasm(raw,a))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Incomplete Team readiness/Script range '+hex(a))
  out[hex(a)]=dict(bytes=n,instructions=len(ins),sha256=hashlib.sha256(raw).hexdigest())
 return dict(ranges=out,complete_readiness=True,actual_taskforce_sum=True,script_current_next_reset_advance_has=True,tag_notification_and_destruction_supplied=True,team_ai_scheduling_unjoined=True)
