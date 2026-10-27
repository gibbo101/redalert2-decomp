# SPDX-License-Identifier: GPL-3.0-or-later
from verify_surface_refresh_marks import verify as marks_verify,RANGES as MARKS
from verify_surface_pixel import verify as pixel_verify,RANGES as PIXEL
RANGES={**MARKS,**PIXEL}
def verify(data):
 return dict(marks=marks_verify(data),pixel=pixel_verify(data),scope='Complete6324A0 and zero-mode634030 with actual774220 stock pixel/lock/bpp/pitch/width/unlock on shared surface fields. Copy8,C0,CC,663D30 and initialization supplied. No production/SDL adoption.')
