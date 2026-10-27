#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact waypoint visibility through mixed coordinates and actual discovery."""
from verify_mission_waypoint_discovery import verify as verify_parent,RANGES as PARENT,TABLES as PARENT_TABLES
from verify_building_coordinates import verify as verify_coordinates,RANGES as COORDINATES,TABLES as COORDINATE_TABLES
from verify_building_discovery import verify as verify_objects,RANGES as OBJECTS
# Only the actual entered complete discovery children, not unrelated verifier ranges.
RANGES={**PARENT,**COORDINATES,**{a:OBJECTS[a] for a in (0x448fe0,0x636f10,0x6c2440,0x5d4230,0x4f52f0,0x594770,0x594cb0)}}
TABLES={**PARENT_TABLES,**COORDINATE_TABLES}
def verify(data):
 parent=verify_parent(data)
 return dict(parent=parent,coordinates=verify_coordinates(data),objects=verify_objects(data),counts=parent['counts'],scope='Actual waypoint/visibility/Cell discovery/mixed coordinates/Unit and Building discovery. Tag, activation, notification, redraw, refresh and startup supplied.')
