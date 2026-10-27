# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact-base waypoint typed recipients with actual stock Building target services."""
from verify_mission_waypoint_typed import verify as verify_parent,RANGES as PARENT,TABLES as PARENT_TABLES
from verify_mission_building_expiration_services import verify as verify_services,RANGES as SERVICES,TABLES as SERVICE_TABLES
RANGES={**PARENT,**SERVICES}
TABLES={**PARENT_TABLES,**SERVICE_TABLES}
def verify(data):
 parent=verify_parent(data);services=verify_services(data)
 return dict(parent=parent,building_services=services,counts=parent['counts'],scope='Complete waypoint discovery and Tag broadcast reaches actual Building null-target/availability/pending mission/getters on the same live actor/type/House/vector owners. House power/service/weapon/release and earlier effects/startup supplied. No production adoption or runtime reads.')
