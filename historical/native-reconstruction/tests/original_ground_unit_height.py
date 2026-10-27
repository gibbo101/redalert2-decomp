# SPDX-License-Identifier: GPL-3.0-or-later
"""Observe actual complete Unit draws on both relative-height shadow branches."""
from original_ground_unit_world import GroundUnitWorldOracle
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX
class GroundUnitHeightOracle(GroundUnitWorldOracle):
 def __init__(self,exe,assets,palette):
  self.relative_heights=[]
  super().__init__(exe,assets,palette)
  self.height_branches={hex(a):0 for a in (0x70042e,0x700489,0x7004e6)}
  self.u.hook_add(UC_HOOK_CODE,self.height_branch,begin=0x700415,end=0x700585)
 def height_branch(self,u,a,n,ctx):
  if self.world_mode and self.unit_mode and hex(a) in self.height_branches:self.height_branches[hex(a)]+=1
 def service(self,u,a,n,ctx):
  if self.world_mode and self.unit_mode and a==self.height_return:
   v=u.reg_read(UC_X86_REG_EAX);self.relative_heights.append(v-2**32 if v>=2**31 else v)
  super().service(u,a,n,ctx)
