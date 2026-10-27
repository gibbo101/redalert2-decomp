#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin stock Infantry/Building sight virtuals before production association."""
import hashlib,struct
import pefile
from presentation_profiles import PATCHED_EXPECTED

def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:
  raise ValueError('Exact supplied Boot Camp sight target required')
 p=pefile.PE(data=data)
 if p.FILE_HEADER.Machine!=0x14c or p.OPTIONAL_HEADER.ImageBase!=0x400000:
  raise ValueError('Boot Camp sight PE differs')
 tables={0x7a3540:{0x2c:0x509800,0x80:0x6c12c0,0x84:0x506950,0x418:0x6d5c30,0x41c:0x6d5e90},
         0x79cbbc:{0x2c:0x453c40,0x80:0x6c12c0,0x84:0x453c60,0x418:0x6d5c30,0x41c:0x6d5e90}}
 for table,slots in tables.items():
  for offset,target in slots.items():
   if p.get_data(table+offset-0x400000,4)!=struct.pack('<I',target):raise ValueError('Stock sight vtable differs')
 roots={0x509800:bytes.fromhex('b80f000000c3'),0x453c40:bytes.fromhex('b806000000c3'),
        0x6c12c0:bytes.fromhex('8b01ffa084000000'),0x506950:bytes.fromhex('8b81a8050000c3'),0x453c60:bytes.fromhex('8b8118040000c3')}
 for address,expected in roots.items():
  if p.get_data(address-0x400000,len(expected))!=expected:raise ValueError('Stock sight getter differs')
 return dict(executable_sha256=PATCHED_EXPECTED,tables={hex(t):{hex(o):hex(a) for o,a in slots.items()} for t,slots in tables.items()},roots={hex(a):hashlib.sha256(b).hexdigest() for a,b in roots.items()},scope='Inspected stock kind/type/sight associations; no scenario/type startup recovery or original whole-chain execution')
