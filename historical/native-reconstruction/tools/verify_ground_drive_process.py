#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin complete ordinary Process/preparation and joined terrain children."""
import hashlib,struct,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_ground_drive_advance import verify as advance_verify,RANGES as ADVANCE
EXTRA={0x4a05f0:0x5cb,0x4a2670:0x20b5,0x4a0bc0:0x16e,0x4a0fd0:0x22,
 0x5d51e0:0x57,0x5d4e40:0x21,0x5d4800:7,0x475d60:0x4d,0x476ac0:0x56,
 0x5d4540:0x20,0x4b8a30:0xdf,0x4b8c90:0x2d,0x463f80:0x14,0x49fc70:0x96,0x49fd10:0x67,0x41b630:0x19,0x4ba410:0x6e,0x5d47d0:0x22}
RANGES={**ADVANCE,**EXTRA}
def verify(data):
 parent=advance_verify(data);p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ranges={}
 for a,n in EXTRA.items():
  raw=p.get_data(a-0x400000,n);ins=list(cs.disasm(raw,a))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Incomplete ground Process range '+hex(a))
  ranges[hex(a)]={'bytes':n,'instructions':len(ins),'sha256':hashlib.sha256(raw).hexdigest()}
 for off,target in ((0x48,0x5d4e40),(0x1a4,0x5d51e0),(0x1b8,0x5d4800)):
  if p.get_data(0x7addf8+off-0x400000,4)!=struct.pack('<I',target):raise ValueError('Ground Process dispatch differs')
 return {'sqrt_table_sha256':hashlib.sha256(p.get_data(0x817dfc-0x400000,65536)).hexdigest(),'advance_ancestor':parent,'ranges':ranges,'scope':'Complete ordinary Process/preparation/Advance with shared empty nonbridge overlay-free Cells; supplied queue, healthy type/actor state, track speed and slope factors. Admission/reservation/occupation/mission and failed pathfinder are supplied; zero retry delay and opaque temporary padding supplied. No original actor/map startup, prepared map, body draw or runtime integration.'}
