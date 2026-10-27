#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact generic Tag44 broadcast with explicit base-Object recipients."""
import pefile,struct
from verify_mission_waypoint_tag import verify as verify_parent,RANGES as PARENT,TABLES as PARENT_TABLES
from verify_mission_tag_expiration import verify as verify_expiration,RANGES as EXPIRATION,TABLES as EXPIRATION_TABLES
from verify_mission_tag_object_expiration import verify as verify_object,RANGES as OBJECT
RANGES={**PARENT,**EXPIRATION,**OBJECT}
TABLES={**PARENT_TABLES,**EXPIRATION_TABLES}
def verify(data):
 parent=verify_parent(data);p=pefile.PE(data=data)
 typed={0x7a3540:0x501cb0,0x79cbbc:0x449e40}
 for vt,target in typed.items():
  if p.get_data(vt+0x28-0x400000,4)!=struct.pack('<I',target):raise ValueError('Typed expiration dispatch differs')
 return dict(typed_expiration_inspected_only={hex(k):hex(v) for k,v in typed.items()},base_Object_recipient_association_supplied=True,parent=parent,expiration=verify_expiration(data),object=verify_object(data),counts=parent['counts'],scope='Actual waypoint/discovery/Tag/Trigger/generic Tag44 broadcast/map/logic/Cell expiration with supplied base-Object recipient association. Actual typed Infantry/Building override chains, action/RTTI/selection/activation/notification/redraw/refresh and startup remain outside this proof.')
