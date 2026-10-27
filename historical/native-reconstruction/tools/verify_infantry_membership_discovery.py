# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin actual Infantry membership/visibility/discovery, including late globals."""
import struct
import pefile
from verify_infantry_membership import verify as infantry,RANGES as INFANTRY,DISPATCH as INFANTRY_DISPATCH
from verify_unit_discovery import verify as discovery,RANGES as DISCOVERY,DISPATCH as DISCOVERY_DISPATCH
RANGES={**DISCOVERY,**INFANTRY}
DISPATCH={**DISCOVERY_DISPATCH,**INFANTRY_DISPATCH,0x7a3540+0x16c:0x594770,0x7a3540+0x1d0:0x594cb0}
def verify(data):
 result=dict(infantry=infantry(data),discovery=discovery(data));p=pefile.PE(data=data)
 for slot,target in DISPATCH.items():
  if p.get_data(slot-0x400000,4)!=struct.pack('<I',target):raise ValueError('Infantry discovery dispatch differs')
 for address,raw in ((0x473c58,'a198d2a30085c07411'),(0x473c61,'a1b45da3008b5500508bcdff9280010000')):
  if p.get_data(address-0x400000,len(bytes.fromhex(raw)))!=bytes.fromhex(raw):raise ValueError('Membership late-global read/notification differs')
 return dict(result,scope='Complete Infantry Mark/map/Cell insertion with actual visibility, Techno discovery and House/Mission children. Null Tag, initial associations, recalculation and atexit supplied; no full Walk/sight scheduling/frame proof.')
