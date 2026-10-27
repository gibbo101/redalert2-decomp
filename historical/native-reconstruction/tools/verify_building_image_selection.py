# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin complete44C5A0 and actual Building/Type dispatch on the supplied binary."""
import hashlib,struct,pefile
from verify_building_image import verify as getters
ADDRESS=0x44c5a0;SIZE=48
def verify(data):
 inherited=getters(data);p=pefile.PE(data=data)
 raw=p.get_data(ADDRESS-0x400000,SIZE)
 expected=bytes.fromhex('8b812c04000085c074188a81b405000084c0740e8b89180400008b01ffa09c0000008b89180400008b11ffa2c0000000')
 if raw!=expected:raise ValueError('Building image selection instructions differ')
 if p.get_data(0x79cbbc+0x68-0x400000,4)!=struct.pack('<I',ADDRESS):raise ValueError('Building image68 dispatch differs')
 return dict(getters=inherited,dispatcher=dict(bytes=SIZE,instructions=12,sha256=hashlib.sha256(raw).hexdigest()),scope='Complete44C5A0 with actual458CE0/45E790; file/CRT/startup remain supplied')
