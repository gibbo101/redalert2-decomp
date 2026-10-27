# SPDX-License-Identifier: GPL-3.0-or-later
from verify_radar_actor_pixels import verify as radar_verify
from verify_surface_copy import verify as copy_verify,RANGES as COPY,TABLES as TABLE_DATA,DATA_RANGES
from verify_surface_refresh_marks import verify as marks_verify,RANGES as MARK

def verify(data):
 return dict(radar=radar_verify(data),copy=copy_verify(data),marks=marks_verify(data),scope='Both complete634030 branches with actual copy/marks/nonzero pixels and shared stock surface/actor/House/scheme owners. Alpha/depth zero; initial records supplied; no runtime adoption.')
