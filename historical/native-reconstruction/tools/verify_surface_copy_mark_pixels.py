# SPDX-License-Identifier: GPL-3.0-or-later
from verify_surface_mark_pixels import verify as mark_verify,RANGES as MARK
from verify_surface_copy import verify as copy_verify,RANGES as COPY
RANGES={**MARK,**COPY}
def verify(data):
 return dict(mark=mark_verify(data),copy=copy_verify(data),scope='Complete6324A0/774220 and zero-mode634030 with actual774F00/clip/stock locks/blitters/CRT, then actual marks/pixels on shared owners. Zero alpha/depth; C0/CC/663D30/startup remain supplied. No production/SDL adoption.')
