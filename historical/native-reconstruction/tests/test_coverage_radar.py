# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
import compare_coverage_radar as c
from test_radar_actor_pixels import RadarActorPixelsEvidence
class CoverageRadarEvidence(unittest.TestCase):
 def row(self):
  row=RadarActorPixelsEvidence().row();del row[10:12]
  return row+['Q']+['0']*21
 def test_domain(self):
  rows=list(c.scenarios());self.assertEqual(len(rows),404)
  for _,cmd in rows:self.assertEqual(c.command(c.parse(cmd)),cmd);c.validate_row(cmd,self.row())
 def test_inputs(self):
  for at,value in ((60,2),(61,256),(62,3),(63,-4),(64,-1),(65,2**31),(68,256),(69,-1),(70,2**31),(72,3),(0,0),(9,0),(31,1),(56,1),(59,1)):
   f=c.parse(c.command());f[at]=value
   with self.assertRaises(ValueError):c.parse(c.command(f))
 def test_trace(self):
  c.validate_row(c.command(),['u','C','316','-1','l','0','1','b','0','2','0','d','2']+self.row())
  for row in (self.row()[:-1],self.row()+['0'],['u','C','315','1']+self.row(),['b','0','0','2']+self.row()):
   with self.assertRaises(ValueError):c.validate_row(c.command(),row)
 def test_receipts(self):
  rows=list(c.scenarios());identity=dict(original={'version':'one'},native_sources={'n':'old'});meta=dict(c.FLAGS,identities=identity,evidence_mode='fresh-original');e=dict(executable_sha256=c.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[cmd for _,cmd in rows],labels=[label for label,_ in rows],expected=[self.row() for _ in rows],evidence=meta);report=dict(meta,expectations_sha256='receipt')
  c.validate(e,report,'receipt',dict(identity,native_sources={'n':'new'}))
  for kind in ('identity','input','row','receipt','scope'):
   bad=copy.deepcopy(e);r=copy.deepcopy(report);current=copy.deepcopy(identity);digest='receipt'
   if kind=='identity':current['original']['version']='two'
   if kind=='input':bad['commands'][0]='C 0'
   if kind=='row':bad['expected'][0][-22]='R'
   if kind=='receipt':digest='wrong'
   if kind=='scope':bad['evidence']['production_or_SDL_adoption']=True;r['production_or_SDL_adoption']=True
   with self.assertRaises(ValueError):c.validate(bad,r,digest,current)
