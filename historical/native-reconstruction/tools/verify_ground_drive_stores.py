#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Inspect the selected ordinary Advance Drive-store instructions."""
import hashlib
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_ground_drive_advance import verify as advance_verify

# Actual dword/byte destination offsets, relative to the complete Drive object.
# Other Advance branches remain outside the existing ordinary profile.
STORE_SITES={
 0x4a2139:(0x40,4),0x4a2141:(0x44,4),0x4a214d:(0x48,4),
 0x4a1fa9:(0x4c,4),0x4a2633:(0x4c,4),0x4a2153:(0x58,4),
 0x4a1f98:(0x5c,4),0x4a215a:(0x5c,4),0x4a2149:(0x63,1),
}
FIELDS={off:width for off,width in STORE_SITES.values()}

def verify(data):
 parent=advance_verify(data)
 p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32)
 instructions={i.address:i for i in cs.disasm(p.get_data(0x4a1000-0x400000,0x1649),0x4a1000)}
 stores={}
 for address,(offset,width) in STORE_SITES.items():
  i=instructions.get(address)
  if i is None or i.mnemonic!='mov' or not i.op_str.startswith(('dword ptr [','byte ptr [')):
   raise ValueError('Advance Drive store instruction differs at '+hex(address))
  stores[hex(address)]={'offset':offset,'width':width,'instruction_bytes':i.size,
   'sha256':hashlib.sha256(bytes(i.bytes)).hexdigest()}
 return {'advance_ancestor':parent,'selected_store_instructions':stores,
  'scope':'Selected ordinary Advance head/accumulator/track/index/driving stores, with existing actor/query/service order. Does not cover every original internal store or expand movement domain.'}
