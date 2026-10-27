# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
import compare_house_diplomacy as c
import test_house_make_ally as parent_tests
class DiplomacyEvidence(unittest.TestCase):
 def row(self,cmd):
  f=c.parse(cmd);return parent_tests.HouseMakeAllyEvidence().row(c.parent.command(f))+['D',str(f['notifyRule']),str(f['sessionPresent']),str(f['sessionResult']),*['53']*5,str(f['houseCount']),'0']
 def test_scenarios(self):
  rows=list(c.scenarios());self.assertGreater(len(rows),500)
  for _,cmd in rows:self.assertEqual(c.command(c.parse(cmd)),cmd);c.validate_row(cmd,self.row(cmd))
  self.assertEqual({c.parse(cmd)['root'] for _,cmd in rows},{0,1,2});self.assertFalse(c.FLAGS['production_adoption'])
 def test_inputs(self):
  for key,value in [('root',3),('notifyRule',256),('sessionPresent',2),('sessionResult',-1),('mutation',5)]:
   f=c.fixture();f[key]=value
   with self.assertRaises(ValueError):c.parse(c.command(f))
  with self.assertRaises(ValueError):c.verify(b'wrong')
 def test_trace(self):
  cmd=c.command(c.fixture());row=self.row(cmd)
  c.validate_row(cmd,['J','N','0','0','E','401','2','1','0','0']+row)
  for bad in (row+['0'],['J','X','0','0']+row,['J','A','6','1']+row,['E','3','0','0','0','0']+row,row[:-3]+['256']+row[-2:]):
   with self.assertRaises(ValueError):c.validate_row(cmd,bad)
 def test_reuse(self):
  rows=list(c.scenarios());identity=dict(original={'engine':'one'},native_sources={'native':'old'});meta=dict(c.FLAGS,identities=identity,evidence_mode='fresh-original');e=dict(executable_sha256=c.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[cmd for _,cmd in rows],labels=[label for label,_ in rows],expected=[self.row(cmd) for _,cmd in rows],evidence=meta);r=dict(meta,expectations_sha256='receipt')
  c.validate(e,r,'receipt',dict(identity,native_sources={'native':'new'}))
  for change in ('identity','flag','commands','trace','receipt'):
   bad=copy.deepcopy(e);report=copy.deepcopy(r);current=copy.deepcopy(identity);fingerprint='receipt'
   if change=='identity':current['original']['engine']='changed'
   if change=='flag':bad['evidence']['production_adoption']=True;report['production_adoption']=True
   if change=='commands':bad['commands'][0]=bad['commands'][1]
   if change=='trace':bad['expected'][0][0]='X'
   if change=='receipt':fingerprint='wrong'
   with self.assertRaises(ValueError):c.validate(bad,report,fingerprint,current)
if __name__=='__main__':unittest.main()
