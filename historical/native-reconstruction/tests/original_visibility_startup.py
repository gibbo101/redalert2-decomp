# SPDX-License-Identifier: GPL-3.0-or-later
"""Unmodified base visibility startup constructors and projection setup."""
import struct
from original_presentation import PresentationOracle
from verify_visibility_startup import verify

OFFSETS=0xa6f248;HEIGHTS=0xa6ed18;COUNTS=0x7a5908
class VisibilityStartupOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True)
  # These roots are already the supplied-1.006 virtual addresses.
  self.va=lambda address:address
 def run(self):
  self.u.mem_write(OFFSETS,b'\xa5'*(369*4));self.u.mem_write(HEIGHTS,b'\xa5'*(309*4))
  self.u.mem_write(0xabe4c0,b'\xa5'*8);self.u.mem_write(0xabe4d0,b'\xa5'*8);self.u.mem_write(0xabe550,b'\xa5'*8);self.u.mem_write(0xabe490,b'\xa5'*8)
  self.checked_call(0x5441e0,writes=[(OFFSETS,369*4)])
  self.checked_call(0x5461a0,writes=[(HEIGHTS,309*4)])
  self.checked_call(0x6a20e0,writes=[(0xabe4c0,8)])
  self.checked_call(0x6a2170,writes=[(0xabe4d0,8)])
  self.checked_call(0x6a2440,writes=[(0xabe550,8),(0xabe490,8)])
  counts=struct.unpack('<11i',self.u.mem_read(COUNTS,44))
  offsets=struct.unpack('<738h',self.u.mem_read(OFFSETS,369*4))
  heights=struct.unpack('<618h',self.u.mem_read(HEIGHTS,309*4))
  scale=struct.unpack('<Q',self.u.mem_read(0xabe490,8))[0]
  return ['V',*map(str,counts),*map(str,offsets),*map(str,heights),str(scale)]
