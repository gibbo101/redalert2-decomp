#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact waypoint/area/Cell-change/mask chain on shared records."""
from verify_mission_waypoint_area import verify as verify_area,RANGES as AREA_RANGES,TABLES as AREA_TABLES
from verify_cell_visibility_change import verify as verify_change,RANGES as CHANGE_RANGES
from verify_cell_visibility_mask import verify as verify_mask,RANGES as MASK_RANGES,TABLE
RANGES={**AREA_RANGES,**CHANGE_RANGES,**MASK_RANGES}
TABLES={**AREA_TABLES,TABLE:256}
def verify(data):
 return dict(area=verify_area(data),change=verify_change(data),mask=verify_mask(data),counts=verify_area(data)['counts'],scope='Actual waypoint/map/area/counter-change/mask chain, shared Cells/fallback. Startup and redraw/discovery/refresh leaves supplied; no live runtime adoption.')
