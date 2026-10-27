# SPDX-License-Identifier: GPL-3.0-or-later
import copy,json,unittest
import compare_mission_control as d
class MissionControlEvidence(unittest.TestCase):
 def test_scenarios(self):
  rows=list(d.scenarios());self.assertEqual(len(rows),1028)
  for _,cmd in rows:self.assertEqual(len(d.parse(cmd)),13)
 def test_domain(self):
  for key,value in (('root',4),('index',30),('index',-2),('present',-1),('diag',6),('aa',2**64)):
   with self.assertRaises(ValueError):d.parse(d.command(**{key:value}))
 def test_row(self):
  d.validate_row(['F','1']+['0']*32)
  for row in (['F','256']+['0']*32,['F','1']+['256']*32,['F','1']+['0']*31):
   with self.assertRaises(ValueError):d.validate_row(row)
 def test_reuse_guards_and_native_independence(self):
  from unittest.mock import patch
  rows=list(d.scenarios());current={'original':{'pin':'expected'},'native_sources':{'new':'version'}}
  evidence=dict(d.FLAGS,identities={'original':{'pin':'expected'},'native_sources':{'old':'version'}},original_instructions_executed=True,original_instructions_modified=False)
  receipt=dict(executable_sha256=d.PATCHED_EXPECTED,profile='supplied-ra2-1006',evidence=evidence,labels=[r[0] for r in rows],commands=[r[1] for r in rows],expected=[['F','0']+['0']*32 for _ in rows])
  receipt=json.loads(json.dumps(receipt))
  with patch.object(d,'validate_receipt'):
   d.validate(receipt,{},'ignored',current)
   for mutate in (lambda e:e['evidence'].update(complete_ini_parent=False),lambda e:e['evidence'].update(original_instructions_modified=True),lambda e:e['commands'].pop(),lambda e:e['evidence']['identities'].update(original={})):
    bad=copy.deepcopy(receipt);mutate(bad)
    with self.assertRaises((ValueError,KeyError)):d.validate(bad,{},'ignored',current)
if __name__=='__main__':unittest.main()
