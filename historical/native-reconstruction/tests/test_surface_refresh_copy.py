# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
import compare_surface_refresh_copy as c
class SurfaceRefreshCopyEvidence(unittest.TestCase):
 def row(self):return ['F','R','1','0','0'*64,'0','0'*64]
 def test_domain(self):
  rows=list(c.scenarios());self.assertEqual(len(rows),642)
  for _,cmd in rows:self.assertEqual(c.command(c.parse(cmd)),cmd);c.validate_row(cmd,self.row())
 def test_inputs(self):
  for cmd in ('C 1','J 1',c.command().replace('J ','C ',1)):
   with self.assertRaises(ValueError):c.parse(cmd)
  with self.assertRaises(ValueError):c.verify(b'wrong')
 def test_traces(self):
  for row in (self.row()[1:],self.row()+['F'],['F']+self.row(),self.row()[:-1]):
   with self.assertRaises(ValueError):c.validate_row(c.command(),row)
 def test_reuse(self):
  rows=list(c.scenarios());identity=dict(original={'engine':'one'},native_sources={'native':'old'});meta=dict(c.FLAGS,identities=identity,evidence_mode='fresh-original');e=dict(executable_sha256=c.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[cmd for _,cmd in rows],labels=[label for label,_ in rows],expected=[self.row() for _ in rows],evidence=meta);r=dict(meta,expectations_sha256='receipt')
  c.validate(e,r,'receipt',dict(identity,native_sources={'native':'new'}))
  for change in ('identity','flag','commands','trace','receipt'):
   bad=copy.deepcopy(e);report=copy.deepcopy(r);current=copy.deepcopy(identity);fingerprint='receipt'
   if change=='identity':current['original']['engine']='changed'
   if change=='flag':bad['evidence']['production_or_SDL_adoption']=True;report['production_or_SDL_adoption']=True
   if change=='commands':bad['commands'][0]='J 0'
   if change=='trace':bad['expected'][0][0]='X'
   if change=='receipt':fingerprint='wrong'
   with self.assertRaises(ValueError):c.validate(bad,report,fingerprint,current)
if __name__=='__main__':unittest.main()
