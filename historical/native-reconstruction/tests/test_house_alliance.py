# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
import compare_house_alliance as c
class HouseAllianceEvidence(unittest.TestCase):
 def test_sequences_and_scope(self):
  rows=list(c.scenarios());self.assertGreater(len(rows),1200)
  for _,cmd in rows:self.assertEqual(c.command(c.parse(cmd)),cmd)
  self.assertEqual({c.parse(cmd)['root'] for _,cmd in rows},{0,1,2})
  self.assertIn('CMakeLists.txt',c.NATIVE)
  self.assertFalse(c.FLAGS['MakeAlly_mutation_and_production_adoption'])
 def test_input_and_binary_guards(self):
  good=c.fixture();cmd=c.command(good)
  for bad in ('',cmd+' 0',cmd.replace('H ','X ',1)):
   with self.assertRaises(ValueError):c.parse(bad)
  for key,value in [('root',3),('current',0),('target',6),('mutation',5),('houseCount',9),('typeCount',5),('mode',2**31)]:
   bad=copy.deepcopy(good);bad[key]=value
   with self.assertRaises(ValueError):c.parse(c.command(bad))
  for key,index,value in [('houseSlots',0,0),('typeSlots',0,5)]:
   bad=copy.deepcopy(good);bad[key][index]=value
   with self.assertRaises(ValueError):c.parse(c.command(bad))
  for key,index,value in [('houses',0,-2**31-1),('houses',1,0),('houses',2,256),('houses',3,-1),('types',2,256)]:
   bad=copy.deepcopy(good);bad[key][0][index]=value
   with self.assertRaises(ValueError):c.parse(c.command(bad))
  with self.assertRaises(ValueError):c.verify(b'wrong executable')
 def row(self,cmd):
  f=c.parse(cmd)
  return ['R','0','S',*map(str,[f['mode'],f['unrestricted'],f['houseCount'],f['typeCount'],0,0]),*map(str,[v for h in f['houses'] for v in h]),*map(str,[v for t in f['types'] for v in t[1:3]])]
 def test_trace_guards(self):
  cmd=c.command(c.fixture());row=self.row(cmd);c.validate_row(cmd,row)
  for bad in (row+['0'],['C','0','1']+row,['C','1',str(2**31)]+row,['R','3']+row[2:],[*row[:2],'X',*row[3:]]):
   with self.assertRaises(ValueError):c.validate_row(cmd,bad)
 def test_reuse_guards(self):
  rows=list(c.scenarios());identity=dict(original={'engine':'one'},native_sources={'native':'old'});meta=dict(c.FLAGS,identities=identity,evidence_mode='fresh-original');e=dict(executable_sha256=c.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[cmd for _,cmd in rows],labels=[label for label,_ in rows],expected=[self.row(cmd) for _,cmd in rows],evidence=meta);r=dict(meta,expectations_sha256='receipt')
  c.validate(e,r,'receipt',dict(identity,native_sources={'native':'new'}))
  for change in ('flag','identity','commands','trace','binary','receipt'):
   bad=copy.deepcopy(e);report=copy.deepcopy(r);current=copy.deepcopy(identity);fingerprint='receipt'
   if change=='flag':bad['evidence']['MakeAlly_mutation_and_production_adoption']=True;report['MakeAlly_mutation_and_production_adoption']=True
   if change=='identity':current['original']['engine']='changed'
   if change=='commands':bad['commands'][0]=bad['commands'][1]
   if change=='trace':bad['expected'][0][0]='X'
   if change=='binary':bad['executable_sha256']='wrong'
   if change=='receipt':fingerprint='wrong'
   with self.assertRaises(ValueError):c.validate(bad,report,fingerprint,current)
if __name__=='__main__':unittest.main()
