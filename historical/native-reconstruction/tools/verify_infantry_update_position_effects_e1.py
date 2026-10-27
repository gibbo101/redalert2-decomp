#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin the complete500AA0 -> complete4C7220 -> complete6C2B40 join."""
import verify_infantry_update_position_e1 as parent
import verify_infantry_position_effects_e1 as child
import verify_actor_ground_state as ground
import verify_map_coordinate_cell as coordinate
import verify_map_floor_height as floor
import verify_movement_gate as gate
import verify_techno_sight as sight
import verify_techno_sight_removal as removal
import verify_post_sight_refresh as post
def verify(data):
 ground_result=ground.verify(data)
 return dict(parent=parent.verify(data),child=child.verify(data),
  coordinate=coordinate.verify(data),floor=floor.verify(data),mission=gate.verify(data),
  sight=sight.verify(data),sight_removal=removal.verify(data),post_sight=post.verify(data),
  current_cell=ground_result['ranges']['0x5d51e0'],
  scope='Complete bounded base500AA0 ordinary-E1 argument2 path entering actual complete base4C7220 and base6C2B40 with three complete current-Cell getters, nine actual full-coordinate map lookups, actual Cell-center/floor target coordinates, verified null-target weapon selection, initialized empty resident search, packed map associations, position-cloak Cell-mask exit, Cell dirty overlay exit, Mission Commence, complete sight removal/addition roots, two complete post-sight roots, permission-success bypass and tail active32D store. Remaining post-sight calls plus reveal/mask/redraw leaves are supplied; production scheduling remains separate.')
