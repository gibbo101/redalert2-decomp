# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin the complete Cell parent and its late scenario/global and flag gates."""
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_cell_visibility_change import verify as verify_parent,RANGES

def verify(data):
 result=verify_parent(data);p=pefile.PE(data=data)
 ops={i.address:(i.mnemonic,i.op_str) for i in Cs(CS_ARCH_X86,CS_MODE_32).disasm(p.get_data(0x99fc0,0x129),0x499fc0)}
 for address,op in {0x49a0b4:('call','0x568520'),0x49a0bd:('test','byte ptr [esi + 0x140], 2'),0x49a0c6:('test','bl, bl'),0x49a0ca:('mov','ecx, dword ptr [0xa3d290]'),0x49a0d0:('mov','edx, dword ptr [ecx]'),0x49a0d2:('test','dh, 0x10'),0x49a0d9:('call','0x47be00')}.items():
  if ops.get(address)!=op:raise ValueError('Late visibility scenario association differs')
 return dict(result,late_scenario_flags_load_after_discovery=True)
