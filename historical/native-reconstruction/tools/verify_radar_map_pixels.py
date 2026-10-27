# SPDX-License-Identifier: GPL-3.0-or-later
from verify_radar_discovery_pixels import verify as parent_verify
from verify_map_floor_height import verify as floor_verify
def verify(data):return dict(parent=parent_verify(data),floor=floor_verify(data),scope='Complete radar parent/caller, actual floor/Cell cache/discovery/map/neighbor and surface pixels on shared table/Cell/fallback owners. Other actor/House/resolver effects and initial state supplied; no runtime adoption.')
