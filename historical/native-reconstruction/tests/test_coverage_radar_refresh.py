# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
import compare_coverage_radar_refresh as c
from test_radar_actor_pixels import RadarActorPixelsEvidence
class CoverageRadarRefreshEvidence(unittest.TestCase):
 def row(self,cmd=None):
  f=c.parse(cmd or c.command());row=RadarActorPixelsEvidence().row();del row[8:12]
  prefix=[]
  for stage in range(f[74]):prefix+=['step',str(f[73]^stage)]
  return prefix+row+['Q']+['0']*21+['U']+['0']*512
 def test_domain(self):
  rows=list(c.scenarios());self.assertEqual(len(rows),940)
  for _,cmd in rows:self.assertEqual(c.command(c.parse(cmd)),cmd);c.validate_row(cmd,self.row(cmd))
 def test_inputs(self):
  for at,v in ((0,0),(2,0),(3,4),(31,1),(56,1),(59,1),(60,2),(61,256),(62,3),(64,256),(72,3),(73,2),(74,3),(75,3),(76,2),(77,256)):
   f=c.parse(c.command());f[at]=v
   with self.assertRaises(ValueError):c.parse(c.command(f))
 def test_traces(self):
  for row in (self.row()[:-1],self.row()+['0'],['u','C','320','1']+self.row(),['b','0','0','2']+self.row(),['m','512','4','1']+self.row()):
   with self.assertRaises(ValueError):c.validate_row(c.command(),row)
 def test_receipts(self):
  rows=list(c.scenarios());identity=dict(original={'v':'one'},native_sources={'n':'old'});meta=dict(c.FLAGS,identities=identity,evidence_mode='fresh-original');e=dict(executable_sha256=c.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[cmd for _,cmd in rows],labels=[label for label,_ in rows],expected=[self.row(cmd) for _,cmd in rows],evidence=meta);report=dict(meta,expectations_sha256='receipt')
  c.validate(e,report,'receipt',dict(identity,native_sources={'n':'new'}))
  for k in ('identity','input','row','receipt','scope'):
   bad=copy.deepcopy(e);r=copy.deepcopy(report);current=copy.deepcopy(identity);digest='receipt'
   if k=='identity':current['original']['v']='two'
   if k=='input':bad['commands'][0]='F 0'
   if k=='row':bad['expected'][0][-535]='R'
   if k=='receipt':digest='wrong'
   if k=='scope':bad['evidence']['production_or_SDL_adoption']=True;r['production_or_SDL_adoption']=True
   with self.assertRaises(ValueError):c.validate(bad,r,digest,current)
