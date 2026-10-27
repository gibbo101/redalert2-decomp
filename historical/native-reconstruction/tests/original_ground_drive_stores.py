# SPDX-License-Identifier: GPL-3.0-or-later
"""Unchanged original Advance, adding instruction-checked Drive observations."""
from collections import Counter
from original_ground_drive_advance import GroundDriveAdvanceOracle,LOCO
from verify_ground_drive_stores import STORE_SITES,FIELDS
from unicorn.x86_const import UC_X86_REG_EIP

class GroundDriveStoresOracle(GroundDriveAdvanceOracle):
 def __init__(self,exe):
  super().__init__(exe)
  self.drive_stores=Counter()
 def store(self,u,access,address,size,value,ctx):
  super().store(u,access,address,size,value,ctx)
  if not self.active:return
  offset=address-LOCO
  if offset not in FIELDS:return
  ip=u.reg_read(UC_X86_REG_EIP)
  assert STORE_SITES.get(ip)==(offset,size),('Uninspected Drive store',hex(ip),hex(offset),size)
  self.drive_stores[hex(ip)]+=1
  self.event('L',offset,value&((1<<(8*size))-1))
