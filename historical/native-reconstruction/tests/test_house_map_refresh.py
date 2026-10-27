# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
import compare_house_map_refresh as c
class HouseMapRefreshEvidence(unittest.TestCase):
 def row(self,cmd):
  f=c.parse(cmd);v=[f['count'],f['mode'],f['current'],f['rule'],0]+[x for name in ('houses','types','actors') for row in f[name] for x in row]
  return ['R','0','F',*map(str,v)]
 def test_sequences_and_scope(self):
  rows=list(c.scenarios());self.assertGreater(len(rows),1000)
  for _,cmd in rows:self.assertEqual(c.command(c.parse(cmd)),cmd);c.validate_row(cmd,self.row(cmd))
  self.assertEqual({c.parse(cmd)['addition'] for _,cmd in rows},{0,1});self.assertIn('src/render/UnitTypeVisibility.cpp',c.NATIVE);self.assertIn('CMakeLists.txt',c.NATIVE);self.assertFalse(c.FLAGS['MakeAlly_parent_and_production_adoption'])
 def test_input_and_binary_guards(self):
  f=c.fixture();cmd=c.command(f)
  for bad in ('',cmd+' 0',cmd.replace('M ','X ',1)):
   with self.assertRaises(ValueError):c.parse(bad)
  for key,value in [('addition',2),('skip',256),('argument',2**31),('count',9),('current',4),('rule',-1),('mutation',8)]:
   bad=copy.deepcopy(f);bad[key]=value
   with self.assertRaises(ValueError):c.parse(c.command(bad))
  for name,index,value in [('houses',3,-1),('actors',2,0),('actors',3,4),('actors',8,2**31),('types',0,256)]:
   bad=copy.deepcopy(f);bad[name][0][index]=value
   with self.assertRaises(ValueError):c.parse(c.command(bad))
  with self.assertRaises(ValueError):c.verify(b'wrong executable')
 def test_trace_guards(self):
  cmd=c.command(c.fixture());row=self.row(cmd);c.validate_row(cmd,['K','1','6','H','1','A','2','0','T','1','2','S','1','1052','0','-1','0','0','I','1','944']+row)
  for bad in (row+['0'],['K','0','6']+row,['T','1','4']+row,['S','1','1048','0','0','0','0']+row,['P','1','0','0','0','0','3','0']+row,['R','1']+row[2:]):
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
