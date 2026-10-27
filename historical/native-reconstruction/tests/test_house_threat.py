# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
import compare_house_threat as c
class HouseThreatEvidence(unittest.TestCase):
 def setUp(self):self.tables=[0]*18
 def row(self,cmd):
  f=c.parse(cmd);values=[f['count'],f['registryCount'],f['mode'],f['ix'],f['iy'],0]+[v for name in ('houses','scores','actors') for row in f[name] for v in row]
  return ['R','0','S',*map(str,values),'G',str(0 if f['root']==0 else 0x77777777),'0']
 def test_scenarios_and_scope(self):
  rows=list(c.scenarios(self.tables));self.assertGreater(len(rows),1000)
  for _,cmd in rows:self.assertEqual(c.command(c.parse(cmd)),cmd);c.validate_row(cmd,self.row(cmd))
  self.assertEqual({c.parse(cmd)['root'] for _,cmd in rows},{0,1,2});self.assertFalse(c.FLAGS['MakeAlly_parent_and_production_adoption'])
  self.assertIn('CMakeLists.txt',c.NATIVE)
 def test_input_and_binary_guards(self):
  f=c.fixture(self.tables);cmd=c.command(f)
  for bad in ('',cmd+' 0',cmd.replace('T ','X ',1)):
   with self.assertRaises(ValueError):c.parse(bad)
  for key,value in [('root',3),('current',0),('target',5),('count',9),('registryCount',-3),('mutation',7),('px',32768),('delta',2**31)]:
   bad=copy.deepcopy(f);bad[key]=value
   with self.assertRaises(ValueError):c.parse(c.command(bad))
  bad=copy.deepcopy(f);bad['houses'][0][4]=-1
  with self.assertRaises(ValueError):c.parse(c.command(bad))
  bad=copy.deepcopy(f);bad.update(root=1,target=0);bad['scores'][0]=[0,1]
  with self.assertRaises(ValueError):c.parse(c.command(bad))
  with self.assertRaises(ValueError):c.verify(b'wrong executable')
 def test_trace_guards(self):
  cmd=c.command(c.fixture(self.tables));row=self.row(cmd);c.validate_row(cmd,row)
  for bad in (row+['0'],['V','0','44','1']+row,['V','1','999','1']+row,['R','1']+row[2:],row[:-1]+['1']):
   with self.assertRaises(ValueError):c.validate_row(cmd,bad)
  c.validate_row(cmd,row[:-1]+['1','0','1'])
  with self.assertRaises(ValueError):c.validate_row(cmd,row[:-1]+['2','0','1','0','2'])
 def test_reuse_guards(self):
  rows=list(c.scenarios(self.tables));identity=dict(original={'engine':'one'},native_sources={'native':'old'});meta=dict(c.FLAGS,identities=identity,evidence_mode='fresh-original');e=dict(executable_sha256=c.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[cmd for _,cmd in rows],labels=[label for label,_ in rows],expected=[self.row(cmd) for _,cmd in rows],evidence=meta);r=dict(meta,expectations_sha256='receipt')
  c.validate(e,r,'receipt',dict(identity,native_sources={'native':'new'}),self.tables)
  for change in ('flag','identity','commands','trace','binary','receipt','tables'):
   bad=copy.deepcopy(e);report=copy.deepcopy(r);current=copy.deepcopy(identity);fingerprint='receipt';tables=self.tables[:]
   if change=='flag':bad['evidence']['MakeAlly_parent_and_production_adoption']=True;report['MakeAlly_parent_and_production_adoption']=True
   if change=='identity':current['original']['engine']='changed'
   if change=='commands':bad['commands'][0]=bad['commands'][1]
   if change=='trace':bad['expected'][0][0]='X'
   if change=='binary':bad['executable_sha256']='wrong'
   if change=='receipt':fingerprint='wrong'
   if change=='tables':tables[0]=1
   with self.assertRaises(ValueError):c.validate(bad,report,fingerprint,current,tables)
if __name__=='__main__':unittest.main()
