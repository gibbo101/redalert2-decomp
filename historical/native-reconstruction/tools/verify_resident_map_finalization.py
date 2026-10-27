#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin the later map parent with actual shared overlay/Cell/wall children."""
from verify_map_preparation import verify as parent,RANGES as PARENT_RANGES
from verify_resident_cell import verify as cell,RANGES as CELL_RANGES
from verify_map_wall_owner import verify as owner,RANGES as OWNER_RANGES
RANGES={**PARENT_RANGES,**CELL_RANGES,**OWNER_RANGES}
def verify(data):
 return {'parent':parent(data),'resident_cell':cell(data),'wall_owner':owner(data),
  'allowed_ranges':[hex(a) for a in RANGES],
  'scope':'Complete later two-pass map parent, transient list empty, no tags/no occupants. Actual lighting numeric/normalization/factory-disabled, resource/classifier, shared resident Cell/LAT/passability/permission/TMP and wall owner/Cell-target distance/getters. Terrain height, registry/type/house/actor/initial map/land/geometry/table inputs supplied. No earlier reader/actor loading/full startup/palette allocation/runtime/frame claim.'}
