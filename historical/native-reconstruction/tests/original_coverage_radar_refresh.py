# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete stock coverage parents and both refresh branches on shared owners."""
from original_coverage_radar import CoverageRadarOracle
from original_radar_refresh import RadarRefreshOracle
from original_surface_radar_pixel import ACTORS,HOUSES,signed
from original_radar_discovery import CELLS
from verify_coverage_radar_refresh import verify
class CoverageRadarRefreshOracle(CoverageRadarOracle,RadarRefreshOracle):
 def __init__(self,exe):verify(exe.read_bytes());super().__init__(exe)
 def prepared_root(self,root,stage):
  assert root in (0x6c83f0,0x6c86f0)
  return root if not stage else 0x6c86f0 if root==0x6c83f0 else 0x6c83f0
 def run(self,f):
  self.coverageFixture=f[60:73];self.coveragePending={};self.coveragePhase=True
  row=RadarRefreshOracle.run(self,f[:60]+f[73:]);bitmap=row[-513:];del row[-513:]
  assert not self.coveragePending
  self.emit('Q',self.u.mem_read(ACTORS[0]+0x1fd,1)[0],signed(self.word(ACTORS[0]+0x200)),*[self.u.mem_read(h+0x188,1)[0] for h in HOUSES])
  for p in CELLS:
   for off in (0x12c,0x130,0x134,0x13c):self.emit(signed(self.word(p+off)))
  row.extend(bitmap);return self.trace
