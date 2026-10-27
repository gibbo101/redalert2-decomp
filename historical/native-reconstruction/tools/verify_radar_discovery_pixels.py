# SPDX-License-Identifier: GPL-3.0-or-later
from verify_surface_radar_pixels import verify as pixels_verify
from verify_radar_discovery import verify as discovery_verify
def verify(data):return dict(pixels=pixels_verify(data),discovery=discovery_verify(data),scope='Complete632000/634030 with actual shared568140/568280/neighbor/map and actual pixel children; floor/House/actor/resolver/initial records supplied, no runtime adoption.')
