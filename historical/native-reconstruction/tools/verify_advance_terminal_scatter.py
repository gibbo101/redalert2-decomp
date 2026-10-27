# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete ordinary Advance with actual terminal target children."""
from verify_advance_nearby_scatter import verify as advance_verify,RANGES as A,TABLES as AT
from verify_advance_terminal import verify as terminal_verify,RANGES as T,TABLES as TT
RANGES={a:max(A.get(a,0),T.get(a,0)) for a in A.keys()|T.keys()}
TABLES={a:max(AT.get(a,0),TT.get(a,0)) for a in AT.keys()|TT.keys()}
def verify(data):
 advance=advance_verify(data);terminal=terminal_verify(data)
 TABLES.update({a:max(TABLES.get(a,0),n) for a,n in AT.items()})
 return dict(advance=advance,terminal=terminal,root='0x4a1000',
  scope='Complete ordinary Advance/admission0/2/6/7/Cell/Unit/nearby/destinations and actual terminal coordinates/floor/clears/mission getter/returns. Mark, occupation, notification174, mission414, postCell490 and initial associations remain supplied. No Process/production world/runtime join.')
