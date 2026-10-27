#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact discovery-to-Tag/Trigger/event/deferred-queue join."""
from verify_mission_waypoint_objects import verify as verify_parent,RANGES as PARENT,TABLES as PARENT_TABLES
from verify_mission_tag import verify as verify_tag,RANGES as TAG,TABLES as TAG_TABLES
RANGES={**PARENT,**TAG}
TABLES={**PARENT_TABLES,**TAG_TABLES}
def verify(data):
 parent=verify_parent(data)
 return dict(parent=parent,tag=verify_tag(data),counts=parent['counts'],scope='Actual waypoint/visibility/mixed discovery/Tag/Trigger/event/retirement joins. Action/expiration/notification/activation/redraw/refresh and startup supplied.')
