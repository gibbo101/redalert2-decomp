# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
import compare_surface_refresh as c
class SurfaceRefreshEvidence(unittest.TestCase):
 def row(self):return ['R','0','0','1','0']+list(map(str,[0,3,2,0,2,3,1,3,2,1,2,3]))+sum(([str(i)]+['0']*4 for i in (1,2,3)),[])
 def test_domain(self):
  rows=list(c.scenarios());self.assertEqual(len(rows),1012)
  for _,cmd in rows:self.assertEqual(c.command(c.parse(cmd)),cmd);c.validate_row(cmd,self.row())
 def test_input_guards(self):
  for at,v in ((0,2**31),(1,2),(2,9),(6,7),(7,64),(8,4),(10,2),(11,-1)):
   f=c.parse(c.command());f[at]=v
   with self.assertRaises(ValueError):c.parse(c.command(f))
  with self.assertRaises(ValueError):c.verify(b'wrong')
 def test_trace_guards(self):
  for bad in (self.row()+['0'],self.row()[:-1],['X']+self.row(),['C','3','0']+self.row(),['P','4']+self.row()):
   with self.assertRaises(ValueError):c.validate_row(c.command(),bad)
 def test_reuse_guards(self):
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
