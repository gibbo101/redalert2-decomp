# SPDX-License-Identifier: GPL-3.0-or-later
from verify_surface_radar_pixel import verify as parent_verify,RANGES as PARENT
from verify_surface_get_pixel import verify as pixel_verify,RANGES as PIXELS
RANGES={**PARENT,**PIXELS}
def verify(data):return dict(parent=parent_verify(data),pixels=pixel_verify(data),scope='Complete632000/634030 nonzero caller with actual stock GetPixel/SetPixel/lock/format/pitch/width/unlock on shared borrowed fields/backing. Other named children/startup remain supplied; no production/SDL adoption.')
