#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin complete663180 and its complete6B0670 caller."""
import hashlib
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_mission_waypoint_reveal import verify as verify_parent,RANGES as PARENT_RANGES
RANGES={**PARENT_RANGES,0x663180:0x14}
def verify(data):
 parent=verify_parent(data);p=pefile.PE(data=data);raw=p.get_data(0x663180-0x400000,0x14);ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(raw,0x663180));ops=[(i.mnemonic,i.op_str) for i in ins]
 if ops!=[('mov','eax, dword ptr [esp + 8]'),('mov','ecx, dword ptr [ecx + eax*4 + 0x632]'),('mov','eax, dword ptr [esp + 4]'),('mov','dword ptr [eax], ecx'),('ret','8')]:raise ValueError('Scenario waypoint663180 differs')
 return dict(parent=parent,range={'0x663180':dict(bytes=20,sha256=hashlib.sha256(raw).hexdigest())},scope='Complete663180 and6B0670 join. Scenario bytes/initial associations and map548070/reveal54A110 children remain supplied.')
