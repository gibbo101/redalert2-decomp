#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin decoded overlay reader nested with complete temporary lifetime and walls."""
from verify_map_overlay_loading import verify as reader,RANGES as READER
from verify_overlay_object_lifetime import verify as lifetime,RANGES as LIFETIME
from verify_overlay_wall_construction import verify as wall,RANGES as WALL
RANGES={**READER,**LIFETIME,**WALL}
def verify(data):
    r,l,w=reader(data),lifetime(data),wall(data)
    return {'ranges':{**r['ranges'],**l['ranges'],**w['ranges']},'all_three_dispatch_verifiers_executed':True,
      'scope':'Complete decoded reader, actual Overlay/Abstract/Object construction, ordinary/wall placement, wall update, retirement/nonempty cleanup and Overlay destructor on shared Cells. Decoding, image availability, type/Cell initial state, heap/growth, queues/bounds, resource/recalculation effects, RTTI/broadcasts/base destruction are supplied. No complete map startup, original parsing, full ownership/runtime or whole-frame claim.'}
