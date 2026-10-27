# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
import compare_house_make_enemy as c
class EnemyEvidence(unittest.TestCase):
 def row(self,cmd):
  f=c.parse(cmd);return ['S',str(f['mode']),str(f['unrestricted']),str(f['currentHouse']),str(f['delayBits']),'0',*[str(v) for name in ('houses','types','scores') for h in f[name] for v in h]]
 def test_domain(self):
  rows=list(c.scenarios());self.assertGreater(len(rows),2000)
  for _,cmd in rows:self.assertEqual(c.command(c.parse(cmd)),cmd);c.validate_row(cmd,self.row(cmd))
  self.assertFalse(c.FLAGS['production_adoption'])
 def test_input_guards(self):
  f=c.fixture()
  for key,value in [('current',0),('target',4),('announce',256),('mode',2**31),('mutation',13),('delayBits',c.bits(float('inf')))]:
   bad=copy.deepcopy(f);bad[key]=value
   with self.assertRaises(ValueError):c.parse(c.command(bad))
  with self.assertRaises(ValueError):c.verify(b'wrong')
  with self.assertRaises(ValueError):c.parse(c.command(f)+' 0')
 def test_trace_guards(self):
  cmd=c.command(c.fixture());row=self.row(cmd)
  c.validate_row(cmd,['W','1','288','0']+row)
  for bad in (row+['0'],['W','0','288','0']+row,['W','1','289','0']+row,['E','3','0','0','0','0','0','0']+row):
   with self.assertRaises(ValueError):c.validate_row(cmd,bad)
 def test_reuse_guards(self):
  rows=list(c.scenarios());identity=dict(original={'engine':'one'},native_sources={'native':'old'});meta=dict(c.FLAGS,identities=identity,evidence_mode='fresh-original');e=dict(executable_sha256=c.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[cmd for _,cmd in rows],labels=[label for label,_ in rows],expected=[self.row(cmd) for _,cmd in rows],evidence=meta);r=dict(meta,expectations_sha256='receipt')
  c.validate(e,r,'receipt',dict(identity,native_sources={'native':'new'}))
  for change in ('identity','flag','command','trace','binary','receipt'):
   bad=copy.deepcopy(e);report=copy.deepcopy(r);current=copy.deepcopy(identity);fingerprint='receipt'
   if change=='identity':current['original']['engine']='changed'
   if change=='flag':bad['evidence']['production_adoption']=True;report['production_adoption']=True
   if change=='command':bad['commands'][0]=bad['commands'][1]
   if change=='trace':bad['expected'][0][0]='X'
   if change=='binary':bad['executable_sha256']='wrong'
   if change=='receipt':fingerprint='wrong'
   with self.assertRaises(ValueError):c.validate(bad,report,fingerprint,current)
if __name__=='__main__':unittest.main()
