# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact-base composed notification/MakeAlly/MakeEnemy instruction inventory."""
from verify_house_make_ally import verify as ally,RANGES as AR,TABLES as AT
from verify_house_make_enemy import verify as enemy,RANGES as ER,TABLES as ET
from verify_house_alliance_notification import verify as notification,RANGES as NR
RANGES={**AR,**ER,**NR};TABLES={**AT,**ET}
def verify(data):
 return dict(ally=ally(data),enemy=enemy(data),notification=notification(data),scope='Complete notification with actual MakeAlly/MakeEnemy, eligibility/score/target/sort/clear/numeric children on shared records. Session/map/grid/UI/virtual services/startup supplied; production unjoined.')
