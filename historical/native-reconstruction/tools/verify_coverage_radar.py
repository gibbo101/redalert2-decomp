# SPDX-License-Identifier: GPL-3.0-or-later
from verify_stock_techno_coverage import verify as stock_verify,EXTRA as STOCK
from verify_radar_actor_pixels import verify as radar_verify
from verify_techno_coverage_world import verify as coverage_verify,RANGES

def verify(data):
 return dict(radar=radar_verify(data),coverage=coverage_verify(data),stock=stock_verify(data),scope='Complete add/remove -> actual nonzero634030/632000 on shared Map/Cell/House/surface owners. Stock permission/type/Owner joined; redraw/initialization supplied; Building power path unentered; no zero-mode or runtime adoption.')
