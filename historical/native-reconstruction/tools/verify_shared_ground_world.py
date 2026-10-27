#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Inspect explicit actor/type/global owners around complete posed world drawing."""
from verify_moving_unit_world import verify as posed
from verify_shared_unit_staging import verify as storage
def verify(disc,data):
 return {'posed_inspection':posed(disc,data),'storage_inspection':storage(disc,data),
  'scope':'Two distinct original actors/Drives share prepared Cells, global staging/pool/world planes and all four type indexes. Complete posed lit/final/raw/cached shadow drawing. Initial pose records, actor/type/House/camera/planes and heap supplied; no Process/membership/runtime/startup/scheduling claim.'}
