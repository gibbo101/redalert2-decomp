# SPDX-License-Identifier: GPL-3.0-or-later
"""Compose the unchanged command and queued Walk inspections."""
import verify_walk_commands as commands
import verify_walk_speed as movement
def verify(data):
 return dict(commands=commands.verify(data),movement=movement.verify(data),
  scope='Actual Walk interface Move_To and optional Stop followed by complete queued Process on the same Infantry/Walk/Cells. Actual admission/speed/head/arrival. Route, map/floor/Mark/notification/destination/reset inside Process, initial records/scale supplied. Not Infantry/Foot SetDestination, production walking or objectives.')
