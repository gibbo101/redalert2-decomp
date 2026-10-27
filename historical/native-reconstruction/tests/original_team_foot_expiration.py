# SPDX-License-Identifier: GPL-3.0-or-later
"""Existing unchanged complete inherited roots, with a distinct actual Team subject."""
from original_mission_typed_tag_expiration import MissionTypedTagExpirationOracle,TAGS
from verify_team_foot_expiration import verify
class TeamFootExpirationOracle(MissionTypedTagExpirationOracle):
 def __init__(self,exe):
  self.team_inspection=verify(exe.read_bytes());super().__init__(exe)
 def checked_call(self,address,args=(),ecx=0,edx=0,**kw):
  # The inherited arena labels are historical fixture IDs, not object types.
  # Subject1 is now a Team with the exact Team vtable. Subject2 remains a real
  # Tag. Its instance field and ObjectTag identity must survive expiration.
  assert self.f['subject']==1 and self.f['objectTag']!=1 and not self.f['flags']&3
  self.put(TAGS[0],0x7ac950)
  kw['inputs']=[*kw['inputs'],(0x7ac950,0x48)]
  return super().checked_call(address,args,ecx,edx,**kw)
