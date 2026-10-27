#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin complete overlay recalculation with actual resident metadata/classifier children."""
from verify_map_cell_attributes import verify as attribute_verify,RANGES as ATTRIBUTE_RANGES
from verify_map_overlay import verify as overlay_verify,RANGES as OVERLAY_RANGES
RANGES={**ATTRIBUTE_RANGES,**OVERLAY_RANGES}
def verify(data):
    return {'attributes':attribute_verify(data),'overlay_children':overlay_verify(data),
      'scope':'Complete Cell recalculation with supplied overlay records, actual classifier and resident TMP/index/validation children. Actual no-occupant passability/permission execute; LAT and cliff neighbors remain supplied services. No type/default/INI/registry construction, allocation, actors, map parent/runtime integration or whole-frame parity.'}
