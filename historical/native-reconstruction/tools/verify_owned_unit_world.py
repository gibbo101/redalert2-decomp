# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin the previously inspected complete movement and shared drawing roots."""
from verify_owned_unit_resident import verify as resident
from verify_shared_ground_world import verify as drawing
from verify_unit_models import verify as models
# The shared drawing type uses the actual UnitType vtable, unlike the older
# movement fixture's supplied kind service. The stock speed query enters it.
TYPE_KIND={0x70b5e0:6}
def verify(disc,data):
 return {'resident':resident(data),'drawing':drawing(disc,data),
  'actual_type_kind':models(data)['ranges']['0x70b5e0'],
  'scope':'One guest: actual preparation, height/Unlimbo/Mark for distinct Units, complete ordinary resident Process, interleaved complete posed world/shadow drawing, then Process. Supplied initial type/House/contact/turret/route/speed/camera/heap and named mission/status services; no construction, scatter, nonzero Advance, frame scheduling or full-game claim.'}
