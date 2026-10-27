# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact complete House grid with stock actor threat/type/kind children."""
from verify_house_threat import verify as grid_verify,RANGES as GRID,TABLES,table_values
from verify_techno_threat import verify as actor_verify,RANGES as ACTOR
RANGES={**GRID,**ACTOR}
def verify(data):
 return dict(grid=grid_verify(data),actor=actor_verify(data),scope='Complete4F3420/54E370 joined to actual stock6D3E50/4532F0/type/kind children. Object Cell1A4, initial records/rules/table associations remain supplied; no production/diplomacy/runtime adoption.')
