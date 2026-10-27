#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compose independently inspected complete Cell root and actual children."""
from verify_map_cell_attributes import verify as attributes_verify,RANGES as ATTRIBUTE_RANGES
from verify_map_cell_children import verify as children_verify,RANGES as CHILD_RANGES
RANGES={**ATTRIBUTE_RANGES,**CHILD_RANGES}
def verify(data):
    return {'attributes':attributes_verify(data),'children':children_verify(data),'scope':'Complete ordinary nonfallback Cell recalculation with actual resident TMP, LAT, empty passability, permission, pointer lookup and word-add children. Supplied registry/type/record/geometry/directions/tile globals/land speed construction; no overlay/new tube/animation/shadow-casting/lazy loading/runtime initialization or full-frame parity.'}
