#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact supplied base6B0670 complete waypoint reveal orchestration."""
import hashlib
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from presentation_profiles import PATCHED_EXPECTED
RANGES={0x6b0670:0x18f}
TABLES={}
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact supplied waypoint reveal target required')
 p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);a=0x6b0670;raw=p.get_data(a-0x400000,RANGES[a]);ins=list(cs.disasm(raw,a));ops={i.address:(i.mnemonic,i.op_str) for i in ins}
 if sum(i.size for i in ins)!=len(raw) or ops[0x6b07fc]!=('ret','0x10'):raise ValueError('Incomplete waypoint reveal range')
 expected={0x6b0670:('mov','eax, dword ptr [0xa35db4]'),0x6b0678:('mov','dl, byte ptr [eax + 0x188]'),0x6b0686:('mov','ecx, dword ptr [ecx + 0x74]'),0x6b0697:('call','0x663180'),0x6b06b7:('test','ch, 1'),0x6b06d1:('test','ch, 4'),0x6b06ee:('movsx','esi, byte ptr [eax + 0x11b]'),0x6b0708:('sar','edi, 1'),0x6b0730:('movsx','eax, ax'),0x6b075e:('mov','eax, dword ptr [edx + 0x54c]'),0x6b0772:('call','0x54a110'),0x6b07d4:('mov','ecx, dword ptr [eax + 0x54c]'),0x6b07e8:('call','0x54a110')}
 for a,op in expected.items():
  if ops.get(a)!=op:raise ValueError('Waypoint reveal association differs '+hex(a))
 return dict(ranges={hex(a):dict(bytes=n,sha256=hashlib.sha256(p.get_data(a-0x400000,n)).hexdigest()) for a,n in RANGES.items()},scope='Complete6B0670 around supplied663180 waypoint/548070 Cell queries/54A110 reveal. Current House/rules/divisor and initial associations supplied; no visibility mutation claim.')
