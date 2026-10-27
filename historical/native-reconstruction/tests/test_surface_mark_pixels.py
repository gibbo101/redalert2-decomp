# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
import compare_surface_mark_pixels as c
class SurfaceMarkPixelEvidence(unittest.TestCase):
 def row(self):return ['R']+['0']*193+['Z','0','0','0'*64,'0'*64]
 def test_domain(self):
  rows=list(c.scenarios());self.assertEqual(len(rows),950)
  for _,cmd in rows:self.assertEqual(c.command(c.parse(cmd)),cmd);c.validate_row(cmd,self.row())
 def test_inputs(self):
  for at,v in ((0,2),(1,17),(3,5),(4,256),(5,2),(6,3),(7,10),(8,512),(9,5),(10,5),(11,256),(12,8),(13,3),(14,3),(15,260),(16,2**31)):
   f=c.parse(c.command());f[at]=v
   with self.assertRaises(ValueError):c.parse(c.command(f))
  with self.assertRaises(ValueError):c.verify(b'wrong')
 def test_traces(self):
  for row in (self.row()[:-1],self.row()+['0'],['B','2','0','1','1']+self.row(),['P','0','16','0','0','0']+self.row(),['C']+['0']*12+self.row()):
   with self.assertRaises(ValueError):c.validate_row(c.command(),row)
 def test_reuse(self):
  rows=list(c.scenarios());identity=dict(original={'engine':'one'},native_sources={'native':'old'});meta=dict(c.FLAGS,identities=identity,evidence_mode='fresh-original');e=dict(executable_sha256=c.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[cmd for _,cmd in rows],labels=[label for label,_ in rows],expected=[self.row() for _ in rows],evidence=meta);r=dict(meta,expectations_sha256='receipt')
  c.validate(e,r,'receipt',dict(identity,native_sources={'native':'new'}))
  for change in ('identity','flag','commands','trace','receipt'):
   bad=copy.deepcopy(e);report=copy.deepcopy(r);current=copy.deepcopy(identity);fingerprint='receipt'
   if change=='identity':current['original']['engine']='changed'
   if change=='flag':bad['evidence']['production_or_SDL_adoption']=True;report['production_or_SDL_adoption']=True
   if change=='commands':bad['commands'][0]='M 0'
   if change=='trace':bad['expected'][0][0]='X'
   if change=='receipt':fingerprint='wrong'
   with self.assertRaises(ValueError):c.validate(bad,report,fingerprint,current)
if __name__=='__main__':unittest.main()
