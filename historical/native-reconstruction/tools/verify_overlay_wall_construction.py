#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin complete wall construction/Unlimbo/Mark and actual wall-update children."""
from verify_overlay_placement import verify as placement, RANGES as PLACEMENT
from verify_overlay_wall_placement import verify as wall, RANGES as WALL
from verify_map_wall_update import verify as update, RANGES as UPDATE
RANGES={**PLACEMENT,**WALL,**UPDATE}
def verify(data):
    p,w,u=placement(data),wall(data),update(data)
    return {'ranges':{**p['ranges'],**w['ranges'],**u['ranges']},'visits':u['visits'],
      'inspection_only':p['inspection_only'],
      'scope':'Complete Overlay constructor/Object Unlimbo/loaded wall Mark with actual wall-update, connection, permission, word/neighbor and rectangle numeric children sharing evolving Cells. Base Object construction, identity provider initialization, vector growth/heap, image bounds/camera, lookup/occupant kinds, redraw/map/zone/expiration queues, Cell recalculation and retirement effects remain supplied. No decoded reader, complete map startup, lifetime, runtime or whole-frame claim.'}
