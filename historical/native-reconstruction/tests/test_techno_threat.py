# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
import compare_techno_threat as c
class TechnoThreatEvidence(unittest.TestCase):
 def row(self,cmd):
  f=c.parse(cmd);return ([] if f['root'] else ['E','128']+(['E','44'] if f['present'] else []))+['R','0']
 def test_domain(self):
  rows=list(c.scenarios());self.assertGreater(len(rows),3000)
  for _,cmd in rows:self.assertEqual(c.command(c.parse(cmd)),cmd);c.validate_row(cmd,self.row(cmd))
  self.assertFalse(c.FLAGS['House_grid_or_runtime_adoption'])
 def test_input_guards(self):
  for key,value in [('root',2),('kind',7),('present',2),('value',2**31),('field',-2**31-1),('multiplier',2**31)]:
   f=c.fixture();f[key]=value
   with self.assertRaises(ValueError):c.parse(c.command(f))
  with self.assertRaises(ValueError):c.verify(b'wrong')
 def test_trace_guards(self):
  cmd=c.command(c.fixture());row=self.row(cmd)
  for bad in (row+['0'],row[2:],row[:-1]+[str(2**31)],['R','0']):
   with self.assertRaises(ValueError):c.validate_row(cmd,bad)
 def test_reuse_guards(self):
  rows=list(c.scenarios());identity=dict(original={'engine':'one'},native_sources={'native':'old'});meta=dict(c.FLAGS,identities=identity,evidence_mode='fresh-original');e=dict(executable_sha256=c.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[cmd for _,cmd in rows],labels=[label for label,_ in rows],expected=[self.row(cmd) for _,cmd in rows],evidence=meta);r=dict(meta,expectations_sha256='receipt')
  c.validate(e,r,'receipt',dict(identity,native_sources={'native':'new'}))
  for change in ('identity','flag','commands','trace','receipt'):
   bad=copy.deepcopy(e);report=copy.deepcopy(r);current=copy.deepcopy(identity);fingerprint='receipt'
   if change=='identity':current['original']['engine']='changed'
   if change=='flag':bad['evidence']['House_grid_or_runtime_adoption']=True;report['House_grid_or_runtime_adoption']=True
   if change=='commands':bad['commands'][0]=bad['commands'][1]
   if change=='trace':bad['expected'][0][0]='X'
   if change=='receipt':fingerprint='wrong'
   with self.assertRaises(ValueError):c.validate(bad,report,fingerprint,current)
if __name__=='__main__':unittest.main()
