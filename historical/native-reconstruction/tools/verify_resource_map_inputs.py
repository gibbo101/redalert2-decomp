#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin two actual phases and label their selected-record snapshot transfer."""
from verify_overlay_map_resources import verify as overlay
from verify_resource_type_inputs import verify as types

def verify(data):
    a,b=overlay(data),types(data)
    return {'overlay':a,'resource_types':b,
      'scope':'Actual resource construction/INI/list phase followed by actual shared decoded overlay/resource phase. Selected initialized resource fields cross an explicit host snapshot boundary between independently audited guests. No original startup parent/order, full parser/heap/type defaults, Cell recalculation, runtime or frame claim.'}
