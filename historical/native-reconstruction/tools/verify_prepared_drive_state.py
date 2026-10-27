#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin the complete prepared map -> Drive Process -> body/shadow state join."""
from verify_ground_drive_process import verify as process,RANGES as PROCESS
from verify_prepared_foot_depth import verify as prepared,RANGES as PREPARED
from verify_drive_body_pose import verify as body,RANGES as BODY
from verify_drive_shadow_pose import verify as shadow,RANGES as SHADOW
RANGES={}
for group in (PROCESS,PREPARED,BODY,SHADOW):
 for a,n in group.items():RANGES[a]=max(n,RANGES.get(a,0))
def verify(data):
 return {'process':process(data),'prepared':prepared(data),'body':body(data),'shadow':shadow(data),
  'scope':'Shared finalized map and actual stock initialization, relative SetHeight and Drive Unlimbo, complete ordinary Process/preparation/Advance, stored-ramp body and current-Cell shadow pose/key and final relative height in one guest. Supplied initial records/routes/speeds and Mark/admission/occupation/mission effects; overlay-free traversed Cells, nonbridge, Accelerates=IsTrain=Passive=0. Complete Unit drawing/startup/runtime/frames excluded.'}
