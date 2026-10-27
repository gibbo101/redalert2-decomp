# SPDX-License-Identifier: GPL-3.0-or-later
import hashlib,pefile
from verify_building_ordinary import verify as parent
ADDRESS=0x548070;SIZE=56
def verify(data):
 inherited=parent(data);p=pefile.PE(data=data);raw=p.get_data(ADDRESS-0x400000,SIZE)
 expected=bytes.fromhex('8b542404560fbf42020fbf32c1e00903c65e78143d000004007d0d8b89380100008b048185c0750d8b12b8f8f9a60089151cfaa600c20400')
 if raw!=expected:raise ValueError('Building map lookup differs')
 return dict(parent=inherited,lookup=dict(bytes=56,instructions=18,sha256=hashlib.sha256(raw).hexdigest()),scope='Complete43A5E0 with actual548070/signed Cell10A; other named services supplied')
