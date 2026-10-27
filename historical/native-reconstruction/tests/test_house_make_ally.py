# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
import compare_house_make_ally as c
class HouseMakeAllyEvidence(unittest.TestCase):
 def row(self,cmd):
  f=c.parse(cmd);n,s,b,cb,ci,o=f['registryConfig'][0]
  header=[f['mode'],f['unrestricted'],f['actorCount'],f['actorBacking'],f['currentHouse'],f['quiet'],f['rule'],f['delayBits'],0,0,n,s,b,cb,ci,o]
  return ['R','0','F',*map(str,header+[v for name in ('scratch','houses','types','scores','actors','registry') for row in f[name] for v in row])]
 def test_sequences_and_scope(self):
  rows=list(c.scenarios());self.assertGreater(len(rows),900)
  for _,cmd in rows:self.assertEqual(c.command(c.parse(cmd)),cmd);c.validate_row(cmd,self.row(cmd))
  self.assertTrue(c.FLAGS['complete_MakeAlly_parent']);self.assertFalse(c.FLAGS['production_adoption']);self.assertIn('src/sim/MissionBuildingTarget.hpp',c.NATIVE)
 def test_input_and_binary_guards(self):
  f=c.fixture();cmd=c.command(f)
  for bad in ('',cmd+' 0',cmd.replace('B ','X ',1)):
   with self.assertRaises(ValueError):c.parse(bad)
  for key,value in [('current',0),('target',6),('announce',256),('actorCount',9),('actorBacking',3),('currentHouse',0),('rule',-1),('mutation',16)]:
   bad=copy.deepcopy(f);bad[key]=value
   with self.assertRaises(ValueError):c.parse(c.command(bad))
  for name,index,value in [('houses',3,-1),('types',2,256),('actors',2,-32769),('registry',1,5),('registryConfig',0,-1),('scratch',1,256)]:
   bad=copy.deepcopy(f);bad[name][0][index]=value
   with self.assertRaises(ValueError):c.parse(c.command(bad))
  with self.assertRaises(ValueError):c.verify(b'wrong executable')
 def test_trace_guards(self):
  cmd=c.command(c.fixture());row=self.row(cmd);c.validate_row(cmd,['E','44','1','6','0','4294967295']+row)
  for bad in (row+['0'],['E','999','0','0','0','0']+row,['E','44','0','0','-1','0']+row,['R','1']+row[2:],row[1:]):
   with self.assertRaises(ValueError):c.validate_row(cmd,bad)
 def test_reuse_guards(self):
  rows=list(c.scenarios());identity=dict(original={'engine':'one'},native_sources={'native':'old'});meta=dict(c.FLAGS,identities=identity,evidence_mode='fresh-original');e=dict(executable_sha256=c.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[cmd for _,cmd in rows],labels=[label for label,_ in rows],expected=[self.row(cmd) for _,cmd in rows],evidence=meta);r=dict(meta,expectations_sha256='receipt')
  c.validate(e,r,'receipt',dict(identity,native_sources={'native':'new'}))
  for change in ('flag','identity','commands','trace','binary','receipt'):
   bad=copy.deepcopy(e);report=copy.deepcopy(r);current=copy.deepcopy(identity);fingerprint='receipt'
   if change=='flag':bad['evidence']['production_adoption']=True;report['production_adoption']=True
   if change=='identity':current['original']['engine']='changed'
   if change=='commands':bad['commands'][0]=bad['commands'][1]
   if change=='trace':bad['expected'][0][0]='X'
   if change=='binary':bad['executable_sha256']='wrong'
   if change=='receipt':fingerprint='wrong'
   with self.assertRaises(ValueError):c.validate(bad,report,fingerprint,current)
if __name__=='__main__':unittest.main()
