# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
import compare_house_actor_threat as c
class HouseActorThreatEvidence(unittest.TestCase):
 def row(self,cmd):return ['R','0','S']+list(map(str,[8,3,0,-32768,-32768,0]+[0]*73))+['G','0','0']
 def test_domain(self):
  rows=list(c.scenarios([0]*18));self.assertGreater(len(rows),700)
  for _,cmd in rows:self.assertEqual(c.command(c.parse(cmd)),cmd);c.validate_row(cmd,self.row(cmd))
 def test_inputs(self):
  for key,value in [('rule',2**31),('root',1),('mutation',2),('threats',[[0,1,0]]*3),('types',[0,0,-2**31-1])]:
   f=c.fixture([0]*18);f[key]=value
   with self.assertRaises(ValueError):c.parse(c.command(f))
  with self.assertRaises(ValueError):c.verify(b'wrong')
 def test_trace_guards(self):
  cmd=c.command(c.fixture([0]*18));row=self.row(cmd)
  c.validate_row(cmd,['E','1',str(0x6d3e50)]+row)
  for bad in (['E','0',str(0x6d3e50)]+row,['E','1','1']+row,['V','1','672','5']+row,row+['0']):
   with self.assertRaises(ValueError):c.validate_row(cmd,bad)
 def test_reuse(self):
  tables=[0]*18;rows=list(c.scenarios(tables));identity=dict(original={'engine':'one'},native_sources={'native':'old'});meta=dict(c.FLAGS,identities=identity,evidence_mode='fresh-original');e=dict(executable_sha256=c.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[cmd for _,cmd in rows],labels=[label for label,_ in rows],expected=[self.row(cmd) for _,cmd in rows],evidence=meta);r=dict(meta,expectations_sha256='receipt')
  c.validate(e,r,'receipt',dict(identity,native_sources={'native':'new'}),tables)
  for change in ('identity','flag','commands','trace','receipt'):
   bad=copy.deepcopy(e);report=copy.deepcopy(r);current=copy.deepcopy(identity);fingerprint='receipt'
   if change=='identity':current['original']['engine']='changed'
   if change=='flag':bad['evidence']['production_and_diplomacy_adoption']=True;report['production_and_diplomacy_adoption']=True
   if change=='commands':bad['commands'][0]=bad['commands'][1]
   if change=='trace':bad['expected'][0][0]='X'
   if change=='receipt':fingerprint='wrong'
   with self.assertRaises(ValueError):c.validate(bad,report,fingerprint,current,tables)
if __name__=='__main__':unittest.main()
