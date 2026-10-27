#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin decoded overlay preparation with actual argument-zero resource children."""
from verify_overlay_map_preparation import verify as preparation,RANGES as PREPARATION
from verify_map_overlay import verify as resources,RANGES as RESOURCE_RANGES
CHILDREN={a:RESOURCE_RANGES[a] for a in (0x5dc0b0,0x476ba0)}
RANGES={**PREPARATION,**CHILDREN}
def verify(data):
    p,r=preparation(data),resources(data)
    return {'ranges':{**p['ranges'],**{hex(a):r['ranges'][hex(a)] for a in CHILDREN}},
      'frame_table_sha256':r['frame_table_sha256'],
      'scope':'Complete decoded reader/base lifetime/ordinary-wall placement/wall update/cleanup with actual resource classifier and argument-zero update over the same Cells. Type/resource/image associations, frame/direction tables and initial state supplied. Decoding, recalculation/passability, bounds/queues/heap/broadcast/RTTI/base destruction remain services. No growth/random replacement, full startup, runtime or frame claim.'}
