# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact Cell dispatch through zero-point Unit/search/destination children."""
from verify_cell_unit_scatter_world import verify as verify_cell,RANGES as CELL,TABLES as CT
from verify_unit_nearby_scatter import verify as verify_nearby,RANGES as NEARBY,TABLES as NT
RANGES={a:max(CELL.get(a,0),NEARBY.get(a,0)) for a in CELL.keys()|NEARBY.keys()}
TABLES={a:max(CT.get(a,0),NT.get(a,0)) for a in CT.keys()|NT.keys()}
def verify(data):
 return dict(inherited=[verify_cell(data),verify_nearby(data)],
  scope='Complete actual Cell snapshot/dispatch -> distinct Units -> zero-point nearby search and Cell destinations. Shared type aliases, actual per-type speed fields/map/fallback/floor/RNG. Prior nonzero Track profile retained. Heap/atomic/padding and initial records/associations supplied. No Advance6/Process/production owned world/preview/drawing/SDL join.')
