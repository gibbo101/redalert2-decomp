# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
import compare_house_alliance_notification as c
class NotificationEvidence(unittest.TestCase):
 def row(self,cmd):
  f=c.parse(cmd);return ['S',str(f['enabled']),str(f['session']),str(f['mode']),str(f['count']),'0',*[str(v) for h in f['houses'] for v in h]]
 def test_domain(self):
  rows=list(c.scenarios());self.assertGreater(len(rows),1000)
  for _,cmd in rows:self.assertEqual(c.command(c.parse(cmd)),cmd);c.validate_row(cmd,self.row(cmd))
  self.assertFalse(c.FLAGS['production_adoption'])
 def test_input_guards(self):
  f=c.fixture()
  for key,value in [('enabled',256),('session',2),('result',-1),('mode',2**31),('count',9),('mutation',7)]:
   bad=copy.deepcopy(f);bad[key]=value
   with self.assertRaises(ValueError):c.parse(c.command(bad))
  for cmd in ('',c.command(f)+' 0'):
   with self.assertRaises(ValueError):c.parse(cmd)
  with self.assertRaises(ValueError):c.verify(b'wrong')
 def test_trace_guards(self):
  cmd=c.command(c.fixture());row=self.row(cmd)
  for prefix in (['Q','256'],['W','1','1'],['A','1','2','0'],['E','2','2','0']):c.validate_row(cmd,prefix+row)
  for bad in (row+['0'],['A','0','1','0']+row,['W','1','2']+row,['E','1','2','1']+row):
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
