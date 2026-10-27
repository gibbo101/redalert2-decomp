#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin complete base RA2 post-sight primary-mask refresh."""
import hashlib,struct
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_terrain_visibility import PATCHED_EXPECTED
RANGES={0x54a550:0x1c4,0x6a2970:0x3c,0x77f110:0x3e}
COUNTS=(0x7a5908,48)
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact supplied post-sight engine required')
 p=pefile.PE(data=data);d=Cs(CS_ARCH_X86,CS_MODE_32);out={}
 for start,size in RANGES.items():
  raw=p.get_data(start-0x400000,size);ins=list(d.disasm(raw,start))
  if sum(i.size for i in ins)!=size:raise ValueError('Incomplete post-sight range '+hex(start))
  out[hex(start)]=dict(bytes=size,instructions=len(ins),sha256=hashlib.sha256(raw).hexdigest())
 root={i.address:(i.mnemonic,i.op_str) for i in d.disasm(p.get_data(0x54a550-0x400000,0x1c4),0x54a550)}
 expected={0x54a5cf:('call','0x6a2970'),0x54a5f0:('call','0x6a2970'),0x54a632:('sar','esi, 8'),0x54a635:('sar','edi, 8'),0x54a6d7:('call','0x6a8d40'),0x54a6e4:('mov','byte ptr [ebx + 0x120], al'),0x54a6ea:('mov','byte ptr [ebx + 0x138], 1'),0x54a6f8:('call','0x6aadd0'),0x54a711:('ret','0x10')}
 for address,op in expected.items():
  if root.get(address)!=op:raise ValueError('Post-sight instruction differs '+hex(address))
 counts=p.get_data(COUNTS[0]-0x400000,COUNTS[1]);values=struct.unpack('<12i',counts)
 if values!=(1,9,21,37,61,89,121,161,205,253,309,369):raise ValueError('Post-sight radius counts differ')
 return dict(ranges=out,counts_sha256=hashlib.sha256(counts).hexdigest(),scope='Complete base54A550..54A711 plus unchanged height projection6A2970; mask6A8D40 and redraw6AADD0 supplied at this boundary.')
