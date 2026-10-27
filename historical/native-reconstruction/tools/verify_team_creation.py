# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact complete TeamType factory and existing action4 entry."""
import hashlib,pefile,capstone
from verify_mission_create_team_action import verify as action_verify,RANGES as ACTION_RANGES,TABLES
RANGES={**ACTION_RANGES,0x6bec80:138}
def verify(data):
 action=action_verify(data);p=pefile.PE(data=data);raw=p.get_data(0x6bec80-0x400000,138);ins=list(capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32).disasm(raw,0x6bec80))
 if len(ins)!=47 or sum(i.size for i in ins)!=138 or ins[-1].mnemonic!='ret':raise ValueError('Incomplete Team factory body')
 return dict(action=action,factory=dict(bytes=138,instructions=len(ins),sha256=hashlib.sha256(raw).hexdigest()),constructor_and_heap_supplied=True)
