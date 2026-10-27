# SPDX-License-Identifier: GPL-3.0-or-later
from verify_coverage_radar import verify as coverage_verify
from verify_radar_refresh import verify as refresh_verify

def verify(data):
 return dict(coverage=coverage_verify(data),refresh=refresh_verify(data),scope='Complete stock add/remove callers with both actual refresh branches and shared Cell/actor/House/scheme/software surfaces. Alternating operation/mode schedule and initialization/redraw supplied; no runtime adoption.')
