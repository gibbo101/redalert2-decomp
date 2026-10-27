# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete active Team command20 path plus actual country-House lookup."""
import hashlib,struct,pefile
from verify_team_script import verify as parent_verify,RANGES as PARENTS
from verify_house_alliance import verify as house_verify
RANGES={**PARENTS,0x4ed760:0x30}
def verify(data):
 parent=parent_verify(data);house=house_verify(data);p=pefile.PE(data=data)
 if struct.unpack('<I',p.get_data(0x6b8768+20*4-0x400000,4))[0]!=0x6b7fec:raise ValueError('Command20 dispatch differs')
 if struct.unpack('<I',p.get_data(0x7a3540+0x378-0x400000,4))[0]!=0x4ca7d0:raise ValueError('E1 transfer association differs')
 return dict(parent=parent,house_lookup=house,command20_entry='6B7FEC..6B8025',saved_next_and_vtable_before_lookup=True,transfer_child_supplied=True)
