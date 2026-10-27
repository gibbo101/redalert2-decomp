#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact shared visibility-to-discovery/resident chain."""
from verify_mission_waypoint_visibility import verify as verify_visibility,RANGES as VISIBILITY_RANGES,TABLES
from verify_cell_visibility_discovery import verify as verify_discovery,RANGES as DISCOVERY_RANGES
RANGES={**VISIBILITY_RANGES,**DISCOVERY_RANGES}
def verify(data):
 visibility=verify_visibility(data)
 return dict(visibility=visibility,discovery=verify_discovery(data),counts=visibility['counts'],scope='Actual waypoint/map/area/change/mask/discovery/closest/coordinate/numeric join. Initial associations and redraw/notify/DiscoveredBy/refresh leaves supplied.')
