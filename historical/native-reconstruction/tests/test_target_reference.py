# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
import compare_target_reference as c
class TargetReferenceEvidence(unittest.TestCase):
 def row(self,cmd):
  f=c.parse(cmd);v=[f['count'],f['sorted'],f['backing'],f['cacheBacking'],f['cacheIndex'],f['fallback'],0]+[x for name in ('tokens','objects','primary','alternate','detached') for row in f[name] for x in row]
  return (['R','0']*(3 if f['root'] in (1,3) else 1))+['F',*map(str,v)]
 def test_sequences_and_scope(self):
  rows=list(c.scenarios());self.assertGreater(len(rows),1000)
  for _,cmd in rows:self.assertEqual(c.command(c.parse(cmd)),cmd);c.validate_row(cmd,self.row(cmd))
  self.assertEqual({c.parse(cmd)['root'] for _,cmd in rows},set(range(4)));self.assertIn('CMakeLists.txt',c.NATIVE);self.assertFalse(c.FLAGS['MakeAlly_parent_and_production_adoption']);self.assertTrue(c.FLAGS['actual_compiled_sort_and_signed_comparator'])
 def test_input_and_binary_guards(self):
  f=c.fixture();cmd=c.command(f)
  for bad in ('',cmd+' 0',cmd.replace('J ','X ',1)):
   with self.assertRaises(ValueError):c.parse(bad)
  for key,value in [('root',4),('token',2),('object',5),('sorted',256),('count',33),('cacheBacking',4),('cacheIndex',32),('fallback',5),('mutation',9)]:
   bad=copy.deepcopy(f);bad[key]=value
   with self.assertRaises(ValueError):c.parse(c.command(bad))
  for name,index,value in [('tokens',0,2**31),('tokens',1,256),('objects',2,-32769),('primary',1,5)]:
   bad=copy.deepcopy(f);bad[name][0][index]=value
   with self.assertRaises(ValueError):c.parse(c.command(bad))
  with self.assertRaises(ValueError):c.verify(b'wrong executable')
 def test_trace_guards(self):
  cmd=c.command(c.fixture());row=self.row(cmd);c.validate_row(cmd,['K','1','6','1','0','255','32','I','1','52','7','C','1','0','1','-2147483648','2147483647']+row)
  for bad in (row+['0'],['K','0','6','0','0','0','0']+row,['I','1','256','7']+row,['C','3','0','0','0','0']+row,['R','5']+row,['X']+row,row[2:]):
   with self.assertRaises(ValueError):c.validate_row(cmd,bad)
 def test_reuse_guards(self):
  rows=list(c.scenarios());identity=dict(original={'engine':'one'},native_sources={'native':'old'});meta=dict(c.FLAGS,identities=identity,evidence_mode='fresh-original');e=dict(executable_sha256=c.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[cmd for _,cmd in rows],labels=[label for label,_ in rows],expected=[self.row(cmd) for _,cmd in rows],evidence=meta);r=dict(meta,expectations_sha256='receipt')
  c.validate(e,r,'receipt',dict(identity,native_sources={'native':'new'}))
  for change in ('flag','identity','commands','trace','binary','receipt'):
   bad=copy.deepcopy(e);report=copy.deepcopy(r);current=copy.deepcopy(identity);fingerprint='receipt'
   if change=='flag':bad['evidence']['MakeAlly_parent_and_production_adoption']=True;report['MakeAlly_parent_and_production_adoption']=True
   if change=='identity':current['original']['engine']='changed'
   if change=='commands':bad['commands'][0]=bad['commands'][1]
   if change=='trace':bad['expected'][0][0]='X'
   if change=='binary':bad['executable_sha256']='wrong'
   if change=='receipt':fingerprint='wrong'
   with self.assertRaises(ValueError):c.validate(bad,report,fingerprint,current)
if __name__=='__main__':unittest.main()
