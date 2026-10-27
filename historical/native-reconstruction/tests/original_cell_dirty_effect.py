# SPDX-License-Identifier: GPL-3.0-or-later
"""Unmodified base47BB30 through each ordered early return."""
import struct
from collections import Counter
from original_presentation import PresentationOracle,STOP
from verify_cell_dirty_effect import verify,RANGE
from unicorn import UC_HOOK_CODE
ARENA=0x3e00000;CELL=ARENA+0x1000
class CellDirtyEffectOracle(PresentationOracle):
 def __init__(self,exe):
  self.inspection=verify(exe.read_bytes());super().__init__(exe,allow_patched=True);self.u.mem_map(ARENA,0x4000)
  self.active=False;self.counts=Counter();self.u.hook_add(UC_HOOK_CODE,self.code)
 def va(self,a):return a
 def code(self,u,a,n,_):
  if not self.active or a==STOP:return
  if not (RANGE[0]<=a and a+n<=RANGE[1]):raise AssertionError(('Uninspected Cell dirty-effect instruction',hex(a)))
  if a==RANGE[0]:self.counts['roots']+=1
  for address,name in ((0x47bb37,'overlay'),(0x47bb41,'data'),(0x47bb4e,'slope'),(0x47bb5c,'flags'),(0x47bb6c,'head')):
   if a==address:self.counts[name]+=1
 def run(self,f):
  u=self.u;u.mem_write(ARENA,bytes(0x4000));u.mem_write(CELL+0x44,struct.pack('<i',f['overlay']))
  u.mem_write(CELL+0x11e,bytes([f['data']]));u.mem_write(CELL+0x11c,bytes([f['slope']]))
  u.mem_write(CELL+0x140,struct.pack('<I',f['flags']));u.mem_write(CELL+0xe4,struct.pack('<I',ARENA+0x2000 if f['resident'] else 0))
  expected=0 if f['overlay']!=0x7e else 1 if f['data']<0x30 else 2 if f['slope'] else 3 if f['flags']&0x20000 else 4
  if expected==4 and f['resident']:raise ValueError('Resident-bearing dirty effect outside fixture')
  self.active=True
  try:self.checked_call(RANGE[0],ecx=CELL,inputs=[(CELL,0x148)])
  finally:self.active=False
  return ['R',str(expected)]
