# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
import compare_scheme_resolver as c
class SchemeResolverEvidence(unittest.TestCase):
 def row(self):return ['R','-1','R','-1','F','0','6','0']+['0']*24
 def test_domain(self):
  rows=list(c.scenarios());self.assertEqual(len(rows),2352)
  for _,cmd in rows:self.assertEqual(c.command(c.parse(cmd)),cmd);c.validate_row(cmd,self.row())
 def test_inputs(self):
  for at,v in ((0,8),(1,2**31),(2,7),(3,2),(4,3),(5,6),(6,64),(7,-3),(8,-2**31-1),(9,8),(10,6),(11,2)):
   f=c.parse(c.command());f[at]=v
   with self.assertRaises(ValueError):c.parse(c.command(f))
  with self.assertRaises(ValueError):c.verify(b'wrong')
 def test_traces(self):
  c.validate_row(c.command(),['T','0','1','-1','U','0','1','1']+self.row())
  for row in (self.row()[:-1],self.row()+['0'],['T','6','0','0']+self.row(),['T','0','0','2']+self.row(),['H']+self.row()):
   with self.assertRaises(ValueError):c.validate_row(c.command(),row)
 def test_reuse(self):
  rows=list(c.scenarios());identity=dict(original={'engine':'one'},native_sources={'native':'old'});meta=dict(c.FLAGS,identities=identity,evidence_mode='fresh-original');e=dict(executable_sha256=c.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[cmd for _,cmd in rows],labels=[label for label,_ in rows],expected=[self.row() for _ in rows],evidence=meta);r=dict(meta,expectations_sha256='receipt')
  c.validate(e,r,'receipt',dict(identity,native_sources={'native':'new'}))
  for change in ('identity','flag','commands','trace','receipt'):
   bad=copy.deepcopy(e);report=copy.deepcopy(r);current=copy.deepcopy(identity);fingerprint='receipt'
   if change=='identity':current['original']['engine']='changed'
   if change=='flag':bad['evidence']['production_or_SDL_adoption']=True;report['production_or_SDL_adoption']=True
   if change=='commands':bad['commands'][0]='S 0'
   if change=='trace':bad['expected'][0][0]='X'
   if change=='receipt':fingerprint='wrong'
   with self.assertRaises(ValueError):c.validate(bad,report,fingerprint,current)
if __name__=='__main__':unittest.main()
