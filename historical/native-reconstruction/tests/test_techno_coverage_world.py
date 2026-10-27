# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
import compare_techno_coverage_world as c
class CoverageWorldEvidence(unittest.TestCase):
 def row(self):return ['R']+list(map(str,[0,1,0,0,0,1,1,255,254,0]+[0]*12))+['F','-30000','29000','0']
 def test_domain(self):
  rows=list(c.scenarios(c.fixture()['scale']));self.assertEqual(len(rows),378)
  for _,cmd in rows:self.assertEqual(c.command(c.parse(cmd)),cmd);c.validate_row(cmd,self.row())
 def test_input_guards(self):
  for at,value in [(0,2**31),(1,-2**31-1),(2,256),(4,2**32)]:
   f=c.fixture();f['houses'][at]=value
   with self.assertRaises(ValueError):c.parse(c.command(f))
  f=c.fixture();f['scale']=2**64-1
  with self.assertRaises(ValueError):c.parse(c.command(f))
  with self.assertRaises(ValueError):c.verify(b'wrong')
 def test_trace_guards(self):
  cmd=c.command(c.fixture());row=self.row()
  for bad in (row+['0'],row[:-1],['W','F','0','37','0']+row,row[:-3]+['32768','0','0'],['E','X']+row):
   with self.assertRaises(ValueError):c.validate_row(cmd,bad)
 def test_reuse_guards(self):
  scale=c.fixture()['scale'];rows=list(c.scenarios(scale));identity=dict(original={'engine':'one'},native_sources={'native':'old'});meta=dict(c.FLAGS,identities=identity,evidence_mode='fresh-original');e=dict(executable_sha256=c.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[cmd for _,cmd in rows],labels=[label for label,_ in rows],expected=[self.row() for _ in rows],evidence=meta);r=dict(meta,expectations_sha256='receipt')
  c.validate(e,r,'receipt',dict(identity,native_sources={'native':'new'}),scale)
  for change in ('identity','flag','commands','trace','receipt'):
   bad=copy.deepcopy(e);report=copy.deepcopy(r);current=copy.deepcopy(identity);fingerprint='receipt'
   if change=='identity':current['original']['engine']='changed'
   if change=='flag':bad['evidence']['production_or_SDL_adoption']=True;report['production_or_SDL_adoption']=True
   if change=='commands':bad['commands'][0]=bad['commands'][1]
   if change=='trace':bad['expected'][0][0]='X'
   if change=='receipt':fingerprint='wrong'
   with self.assertRaises(ValueError):c.validate(bad,report,fingerprint,current,scale)
if __name__=='__main__':unittest.main()
