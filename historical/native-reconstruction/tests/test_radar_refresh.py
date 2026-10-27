# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
import compare_radar_refresh as c
from test_radar_actor_pixels import RadarActorPixelsEvidence
class RadarRefreshEvidence(unittest.TestCase):
 def row(self,cmd=None):
  f=c.parse(cmd or c.command());row=RadarActorPixelsEvidence().row();del row[8:12]
  prefix=[]
  for stage in range(f[61]):prefix+=['step',str(f[60]^stage)]
  return prefix+row+['U']+['0']*512
 def test_domain(self):
  rows=list(c.scenarios());self.assertEqual(len(rows),132)
  for _,cmd in rows:self.assertEqual(c.command(c.parse(cmd)),cmd);c.validate_row(cmd,self.row(cmd))
 def test_input(self):
  for at,v in ((0,0),(2,0),(2,6),(3,4),(31,1),(56,1),(59,1),(60,2),(61,0),(61,3),(62,3),(63,2),(64,256)):
   f=c.parse(c.command());f[at]=v
   with self.assertRaises(ValueError):c.parse(c.command(f))
 def test_trace(self):
  for row in (self.row()[:-1],self.row()+['0'],['m','512','4','1']+self.row(),['P','0','3','0','0','1']+self.row(),['copy']+['0']*12+self.row()):
   with self.assertRaises(ValueError):c.validate_row(c.command(),row)
  row=self.row();row[1]='1'
  with self.assertRaises(ValueError):c.validate_row(c.command(),row)
 def test_reuse(self):
  rows=list(c.scenarios());identity=dict(original={'v':'one'},native_sources={'n':'old'});meta=dict(c.FLAGS,identities=identity,evidence_mode='fresh-original');e=dict(executable_sha256=c.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[cmd for _,cmd in rows],labels=[label for label,_ in rows],expected=[self.row(cmd) for _,cmd in rows],evidence=meta);r=dict(meta,expectations_sha256='receipt')
  c.validate(e,r,'receipt',dict(identity,native_sources={'n':'new'}))
  for k in ('identity','input','row','receipt','scope'):
   bad=copy.deepcopy(e);report=copy.deepcopy(r);current=copy.deepcopy(identity);digest='receipt'
   if k=='identity':current['original']['v']='two'
   if k=='input':bad['commands'][0]='X 0'
   if k=='row':bad['expected'][0][-513]='R'
   if k=='receipt':digest='wrong'
   if k=='scope':bad['evidence']['production_or_SDL_adoption']=True;report['production_or_SDL_adoption']=True
   with self.assertRaises(ValueError):c.validate(bad,report,digest,current)
