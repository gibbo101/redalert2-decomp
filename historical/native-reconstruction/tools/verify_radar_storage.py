# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact base startup/projection/device-init composition; no new code ranges."""
from verify_radar_surface_startup import verify as startup
from verify_radar_projection import verify as projection

def verify(data):
 return dict(startup=startup(data),projection=projection(data),scope='Complete630A00 -> aliased630B70 and4AA4A0; original software buffer/lock/numeric children. Terrain/platform/device/destruction/clear/finish supplied; no production or SDL adoption.')
