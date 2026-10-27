# SPDX-License-Identifier: GPL-3.0-or-later
"""Original complete Unit root with supplied overlay associations, no patches."""
import struct
from collections import Counter
from original_unit_admission import UnitAdmissionOracle,ARENA,CELLS,HOUSES,WEAPON
from original_presentation import STOP
from unicorn.x86_const import UC_X86_REG_EBX,UC_X86_REG_ECX
from verify_overlay_unit_admission import verify,HOUSE,HOUSE_SIZE
TABLE=ARENA+0x36800
TYPES=[ARENA+0x37000+i*0x400 for i in range(3)]
WARHEAD=ARENA+0x38000
class OverlayUnitAdmissionOracle(UnitAdmissionOracle):
 def __init__(self,exe):
  self.overlay_inspection=verify(exe.read_bytes());super().__init__(exe);self.overlay_counts=Counter()
 def prepare_motion(self):
  override,houses,weapon,cells,types=self.overlay
  self.put(0xa35dec,TABLE);self.put(0xa3d298,override)
  for p,flags in zip(HOUSES,houses):self.u.mem_write(p+0x134,bytes(flags))
  for p,(index,owner) in zip(CELLS,cells):self.put(p+0x44,index);self.put(p+0x50,owner)
  for i,(flag27a,wall,crushable,armor) in enumerate(types):
   self.put(TABLE+4*i,TYPES[i]);self.put(TYPES[i]+0x9c,armor)
   for off,value in [(0x27a,flag27a),(0x278,wall),(0x1fd,crushable)]:self.u.mem_write(TYPES[i]+off,bytes([value]))
  self.put(WEAPON+0xac,WARHEAD)
  for off,value in zip((0x144,0x146),weapon):self.u.mem_write(WARHEAD+off,bytes([value]))
 def extra_inputs(self):return [(HOUSE,HOUSE_SIZE),(0xa35dec,4),(0xa3d298,4)]
 def code(self,u,a,n,ctx):
  if not self.active or a==STOP:return super().code(u,a,n,ctx)
  if HOUSE<=a and a+n<=HOUSE+HOUSE_SIZE:
   self.instructions.add(a)
   if a==HOUSE:self.event('u',HOUSES.index(u.reg_read(UC_X86_REG_ECX)));self.overlay_counts['House_control']+=1
   return
  if a==0x703331:
   p=u.reg_read(UC_X86_REG_EBX);self.event('o',CELLS.index(p),struct.unpack('<i',u.mem_read(p+0x44,4))[0])
  if a==0x70333d:
   self.instructions.add(a);self.overlay_counts['overlay_registry']+=1;return
  if a in (0x703368,0x70338f,0x7033c1,0x703406,0x703428,0x703451):self.overlay_counts[hex(a)]+=1
  return super().code(u,a,n,ctx)
