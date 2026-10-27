# SPDX-License-Identifier: GPL-3.0-or-later
"""Original commands/finalization plus admitted Process on both genuine actors."""
from original_owned_orders_world import OwnedOrdersWorldOracle
from original_owned_advance_world import AttachedAdvanceProcesses

class OwnedAdvanceRuntimeOracle(OwnedOrdersWorldOracle):
    movement_type = AttachedAdvanceProcesses
