# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
import compare_techno_coverage as c
class TechnoCoverageEvidence(unittest.TestCase):
 def row(self):return ['R']+list(map(str,[0,1,0,0,0,1,1,255,254,0]+[0]*12))
 def test_domain(self):
  rows=list(c.scenarios());self.assertGreater(len(rows),250)
  for _,cmd in rows:self.assertEqual(c.command(c.parse(cmd)),cmd);c.validate_row(cmd,self.row())
  self.assertFalse(c.FLAGS['production_or_SDL_adoption'])
 def test_input_guards(self):
  for k,v in [(0,2),(1,256),(2,63),(3,-129),(5,3),(19,2),(20,6),(21,0),(22,3),(10,2**31)]:
   f=c.fixture();f[k]=v
   with self.assertRaises(ValueError):c.parse(c.command(f))
  with self.assertRaises(ValueError):c.verify(b'wrong')
 def test_trace_guards(self):
  cmd=c.command(c.fixture());row=self.row()
  for bad in (row+['0'],row[:-1],['X']+row,['W','C','0','299','0']+row,['E','C','32768','0','0']+row,['E','D','0']+row):
   with self.assertRaises(ValueError):c.validate_row(cmd,bad)
 def test_reuse_guards(self):
  rows=list(c.scenarios());identity=dict(original={'engine':'one'},native_sources={'native':'old'});meta=dict(c.FLAGS,identities=identity,evidence_mode='fresh-original');e=dict(executable_sha256=c.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[cmd for _,cmd in rows],labels=[label for label,_ in rows],expected=[self.row() for _ in rows],evidence=meta);r=dict(meta,expectations_sha256='receipt')
  c.validate(e,r,'receipt',dict(identity,native_sources={'native':'new'}))
  for change in ('identity','flag','commands','trace','receipt'):
   bad=copy.deepcopy(e);report=copy.deepcopy(r);current=copy.deepcopy(identity);fingerprint='receipt'
   if change=='identity':current['original']['engine']='changed'
   if change=='flag':bad['evidence']['production_or_SDL_adoption']=True;report['production_or_SDL_adoption']=True
   if change=='commands':bad['commands'][0]=bad['commands'][1]
   if change=='trace':bad['expected'][0][0]='X'
   if change=='receipt':fingerprint='wrong'
   with self.assertRaises(ValueError):c.validate(bad,report,fingerprint,current)
if __name__=='__main__':unittest.main()
