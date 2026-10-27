#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin actual decoded overlay placement with shared resident Cell children."""
from verify_overlay_map_resources import verify as overlay,RANGES as OVERLAY_RANGES
from verify_resident_cell import verify as cell,RANGES as CELL_RANGES
RANGES={**OVERLAY_RANGES,**CELL_RANGES}
def verify(data):
    return {'overlay':overlay(data),'cell':cell(data),'allowed_ranges':[hex(a) for a in RANGES],
      'scope':'Complete decoded reader/base lifetime/ordinary-wall placement/wall update/cleanup, resource and resident Cell/LAT/classifier/no-occupant passability/permission/lookup/TMP children on shared mutable Cells. Supplied type/resource/initial map/geometry/table/Wheel inputs, decoding, bounds/queues/heap/broadcast/RTTI/base destruction. No later two-pass map parent/startup/runtime/frame claim.'}
