#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin actual floor height nested in the overlay-bearing later map parent."""
from verify_resident_map_finalization import verify as parent,RANGES as PARENT_RANGES
from verify_map_floor_height import verify as floor,RANGES as FLOOR_RANGES
RANGES={**PARENT_RANGES,**FLOOR_RANGES}
def verify(data):
 return {'parent':parent(data),'floor':floor(data),'allowed_ranges':[hex(a) for a in RANGES],
  'scope':'Complete later two-pass map parent with actual shared resource/Cell/LAT/passability/permission/TMP, factory-disabled lighting and wall-owner/Cell-target distance/center/floor/lazy planes. Empty transient list/no tags/no occupants. Initial template/live height/type/actor/house/registry/terrain/geometry/table storage supplied; no earlier reader, original startup, runtime depth or whole-frame claim. Initializer split-store order is not compared.'}
