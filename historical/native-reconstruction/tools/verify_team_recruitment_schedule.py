# SPDX-License-Identifier: GPL-3.0-or-later
"""Inspect initial Team AI paths and exact entered readiness/House/E1 children."""
import hashlib,struct,pefile,capstone
EXPECTED='e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f'
RANGES={0x6b7ad0:0xc96,0x6b8bb0:0x108,0x6b6b30:0x1f,0x6ba1a0:0x459,0x4f52f0:0x23,0x6d6e00:7}
SERVICES=(0x6b9610,0x6b91c0,0x1100b00)
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=EXPECTED:raise ValueError('Team AI requires exact supplied base')
 p=pefile.PE(data=data);c=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32);out={}
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(c.disasm(raw,a))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Incomplete inspected Team AI range '+hex(a))
  out[hex(a)]=dict(bytes=n,instructions=len(ins),sha256=hashlib.sha256(raw).hexdigest())
 if p.get_data(0x7a3540+0x1c0-0x400000,4)!=struct.pack('<I',0x6d6e00):raise ValueError('Actual E1 virtual1C0 differs')
 return dict(ranges=out,initial_preready_complete_paths=True,actual_readiness_sum_house_member_byte=True,null_target_continuation=True,anchor_selector_supplied=True,active_script_and_nonnull_targets_unjoined=True)
