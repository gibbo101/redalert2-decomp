# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin complete Cell dispatch, Unit Scatter/world and live moving admission."""
from verify_unit_scatter_world import verify as world,RANGES as WR,TABLES as WT
from verify_cell_scatter import verify as cell,RANGES as CR
from verify_moving_unit_admission import verify as moving,RANGES as MR,TABLES as MT
RANGES={};TABLES={}
for group in (WR,CR,MR):
 for a,n in group.items():RANGES[a]=max(n,RANGES.get(a,0))
for group in (WT,MT,{0x79db7c:12,0x79a708:8,0x79a6f8:8}):
 for a,n in group.items():TABLES[a]=max(n,TABLES.get(a,0))
def verify(data):
 return dict(inherited=[f(data) for f in (world,cell,moving)],
  scope='Complete Unit-only Cell snapshot/dispatch to actual nonzero-point Unit Scatter/world and Cell destination; later admission consumes live distinct actors/Drives/targets. Heap growth/disposal and initial records/associations supplied. No Advance6/Process/production owned map/preview/drawing/SDL runtime join.')
