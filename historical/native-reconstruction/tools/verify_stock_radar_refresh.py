# SPDX-License-Identifier: GPL-3.0-or-later
from verify_surface_copy_mark_pixels import verify as refresh_verify,RANGES as REFRESH
from verify_actor_radar_color import verify as actor_verify,RANGES as ACTOR
RANGES={**REFRESH,**ACTOR}
def verify(data):
 return dict(refresh=refresh_verify(data),actor=actor_verify(data),scope='Complete mark/pixel and zero-mode copy-refresh with actual stock Infantry/Building C0/CC and4E5540 on shared actor/House owners. Resolver663D30/startup remain supplied. Zero alpha/depth, no production/SDL adoption.')
