# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact-base waypoint discovery with full typed Tag-expiration recipients."""
import hashlib,pefile
from verify_mission_waypoint_expiration import verify as verify_parent,RANGES as PARENT,TABLES as PARENT_TABLES
from verify_mission_typed_tag_expiration import verify as verify_typed,RANGES as TYPED,TABLES as TYPED_TABLES
RANGES={**PARENT,**TYPED,0x410260:0x23}
TABLES={**PARENT_TABLES,**TYPED_TABLES}
def verify(data):
 parent=verify_parent(data);typed=verify_typed(data);p=pefile.PE(data=data)
 raw=p.get_data(0x410260-0x400000,0x23)
 if hashlib.sha256(raw).hexdigest()!='1f46dc853db4fa22772ce283d15f67a34fef847ea8efe0da566e5047b325e8be':raise ValueError('Tag default coordinate root differs')
 if p.get_data(0x7ac700+0x48-0x400000,4)!=(0x410260).to_bytes(4,'little'):raise ValueError('Stock Tag coordinate virtual differs')
 return dict(parent=parent,typed=typed,tag_coordinates=dict(address=0x410260,bytes=35,sha256=hashlib.sha256(raw).hexdigest(),global_address=0x839ca8),counts=parent['counts'],scope='Actual waypoint/discovery/Tag/Trigger/generic broadcast reaches full Infantry/Building inherited expiration on shared owner, mission, radio, resident Next and Cell/map/fallback owners. Named effects and initial associations remain supplied. No production adoption.')
