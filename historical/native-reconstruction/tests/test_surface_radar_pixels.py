# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
import compare_surface_radar_pixels as c
class SurfaceRadarPixelsEvidence(unittest.TestCase):
 def row(self):return ['R']+['0']*43+['Z','0','0','0'*64,'0'*64]
 def test_domain(self):
  rows=list(c.scenarios());self.assertEqual(len(rows),2409)
  for _,cmd in rows:self.assertEqual(c.command(c.parse(cmd)),cmd);c.validate_row(cmd,self.row())
 def test_inputs(self):
  for at,v in ((33,3),(34,260),(35,2**31),(0,2),(1,3),(2,9),(3,-3),(6,7),(10,256),(11,-1),(12,4),(13,4),(14,8),(15,-1),(16,8),(17,8),(18,-2),(22,0),(23,-1),(23,2**32),(24,3),(31,13),(32,65536)):
   f=c.parse(c.command());f[at]=v
   with self.assertRaises(ValueError):c.parse(c.command(f))
  f=c.parse(c.command());f[0]=1;f[9]=0
  with self.assertRaises(ValueError):c.parse(c.command(f))
  f=c.parse(c.command());f[31]=1;f[32]=32768
  with self.assertRaises(ValueError):c.parse(c.command(f))
  with self.assertRaises(ValueError):c.verify(b'wrong')
 def test_traces(self):
  c.validate_row(c.command(),['G','0','4','3','S','D','3','0']+self.row())
  for row in (self.row()[:-1],self.row()+['0'],['G','2','4','3']+self.row(),['H','0','0','0','256']+self.row(),['V','2','0','0','0','1']+self.row(),['D','4','0']+self.row()):
   with self.assertRaises(ValueError):c.validate_row(c.command(),row)
 def test_reuse(self):
  rows=list(c.scenarios());identity=dict(original={'engine':'one'},native_sources={'native':'old'});meta=dict(c.FLAGS,identities=identity,evidence_mode='fresh-original');e=dict(executable_sha256=c.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[cmd for _,cmd in rows],labels=[label for label,_ in rows],expected=[self.row() for _ in rows],evidence=meta);r=dict(meta,expectations_sha256='receipt')
  c.validate(e,r,'receipt',dict(identity,native_sources={'native':'new'}))
  for change in ('identity','flag','commands','trace','receipt'):
   bad=copy.deepcopy(e);report=copy.deepcopy(r);current=copy.deepcopy(identity);fingerprint='receipt'
   if change=='identity':current['original']['engine']='changed'
   if change=='flag':bad['evidence']['production_or_SDL_adoption']=True;report['production_or_SDL_adoption']=True
   if change=='commands':bad['commands'][0]='R 0'
   if change=='trace':bad['expected'][0][0]='X'
   if change=='receipt':fingerprint='wrong'
   with self.assertRaises(ValueError):c.validate(bad,report,fingerprint,current)
if __name__=='__main__':unittest.main()
