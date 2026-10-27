# SPDX-License-Identifier: GPL-3.0-or-later
"""Join actual Infantry Mark/membership with shared original visibility/discovery."""
from original_infantry_membership import InfantryMembershipOracle,SERVICES
from original_unit_membership_discovery import UnitMembershipDiscoveryOracle as Joined
from original_unit_discovery import UnitDiscoveryOracle,HOUSES
from original_presentation import STOP
from verify_infantry_membership_discovery import verify,RANGES,DISPATCH
from verify_infantry_membership import RANGES as INFANTRY
from verify_ramp_geometry import CONSTANTS,TABLES
from unicorn import UC_HOOK_CODE
class InfantryMembershipDiscoveryOracle(InfantryMembershipOracle):
 def __init__(self,exe):
  super().__init__(exe);self.inspection=verify(exe.read_bytes());self.u.mem_map(HOUSES[0],0x12000)
  self.entries.update({hex(a):0 for a in RANGES if a not in INFANTRY})
  self.inputs=list(RANGES.items())+[(p,8) for p in CONSTANTS]+list(TABLES.items())+[(0xb2af94,4)]
  self.put(0xb2af94,0);self.u.hook_add(UC_HOOK_CODE,self.observe_discovery)
  self.stock=UnitDiscoveryOracle.stock_visibility(self,0)
 def block(self,u,a,n,ctx):
  if a not in (STOP,*SERVICES) and not any(p<=a and a+n<=p+s for p,s in RANGES.items()):raise AssertionError(f'Uninspected Infantry discovery block {a:#x}/{n}')
 # Reuse the authored shared House/Mission observation and arena audits. These
 # methods use the same logical actor/Cell addresses as the Infantry fixture.
 observe_discovery=Joined.observe_discovery
 membership_service=Joined.membership_service
 configure_membership=Joined.configure_membership
 membership_writes=Joined.membership_writes
 membership_store=Joined.membership_store
 membership_result=Joined.membership_result
 run_joined=Joined.run_joined
 def membership_inputs(self):return [*Joined.membership_inputs(self),*RANGES.items(),*[(p,4) for p in DISPATCH]]
