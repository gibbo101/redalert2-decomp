#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin complete resident Cell recalculation with actual overlay and LAT children."""
from verify_map_cell_preparation import verify as cell,RANGES as CELL_RANGES
from verify_map_overlay import verify as overlay,RANGES as OVERLAY_RANGES
RANGES={**CELL_RANGES,0x5dc0b0:OVERLAY_RANGES[0x5dc0b0]}
def verify(data):
    a,b=cell(data),overlay(data)
    return {'cell':a,'overlay':b,'allowed_ranges':[hex(a) for a in RANGES],
      'scope':'Complete ordinary nonfallback Cell recalculation with actual LAT, overlay classifier, no-occupant passability, permission, shared lookup/word-add and resident TMP/index consumers. Supplied registry/type/resource/default/INI/initial-map/geometry/table/Wheel speed construction. No new tube/animation/shadow casting, overlay reader/map parent/runtime or frame claim.'}
