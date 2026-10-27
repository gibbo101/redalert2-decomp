# SPDX-License-Identifier: GPL-3.0-or-later
from verify_radar_resident_color import verify as parent_verify
from verify_overlay_radar_color import verify as overlay_verify
def verify(data):return dict(parent=parent_verify(data),overlay=overlay_verify(data),scope='Actual overlay5DD000 and initialized5DD150 below Cell colors/resident search/terrain/projection. Authored alternate getter/image bindings, resource/image installation/brightness remain supplied; no production claim.')
