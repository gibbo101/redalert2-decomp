#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact base waypoint/map/reveal-area composition."""
import hashlib
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_scenario_waypoint import verify as verify_waypoint,RANGES as WAYPOINT_RANGES
from verify_reveal_area import verify as verify_area,RANGES as AREA_RANGES,TABLES
RANGES={**WAYPOINT_RANGES,**AREA_RANGES,0x548070:0x38}
def verify(data):
 waypoint=verify_waypoint(data);area=verify_area(data);p=pefile.PE(data=data);raw=p.get_data(0x548070-0x400000,0x38);ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(raw,0x548070));ops={i.address:(i.mnemonic,i.op_str) for i in ins}
 if sum(i.size for i in ins)!=len(raw) or ops.get(0x54809f)!=('mov','dword ptr [0xa6fa1c], edx') or ops.get(0x5480a5)!=('ret','4') or ops.get(0x54808b)!=('mov','ecx, dword ptr [ecx + 0x138]'):raise ValueError('Waypoint map lookup differs')
 area_ops={i.address:(i.mnemonic,i.op_str) for i in Cs(CS_ARCH_X86,CS_MODE_32).disasm(p.get_data(0x54a110-0x400000,0x440),0x54a110)}
 if area_ops.get(0x54a43b)!=('mov','esi, dword ptr [ebx + 0x138]') or area_ops.get(0x54a4ab)!=('mov','edx, dword ptr [0x832618]'):raise ValueError('Static map table alias differs')
 return dict(fixed_map_table_alias='8324E0+138=832618',waypoint=waypoint,area=area,map_range={'0x548070':dict(bytes=56,sha256=hashlib.sha256(raw).hexdigest())},counts=area['counts'],scope='Complete6B0670/663180/548070/54A110 with actual numeric children; shared Cell/fallback flags. Startup scenario/tables/House and final visibility children supplied.')
