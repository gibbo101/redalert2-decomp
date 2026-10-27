# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin the complete queued Walk / Infantry admission / speed composition."""
import verify_walk_admission as movement
import verify_infantry_speed as speed
def verify(data):
 return dict(movement=movement.verify(data),speed=speed.verify(data),
  scope='Complete queued Walk Process with actual Infantry admission and speed; same borrowed actor/percentage/type/House/Cells. Actual Foot/country/promotion0/FTOL, head/subcells/interpolation/arrival/Stop. Map/floor/Mark/notification/destination/reset and initialization supplied. No production/SDL/objective claim.')
