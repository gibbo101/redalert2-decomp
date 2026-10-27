# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
import compare_techno_type_cost as d
class TechnoTypeCostEvidence(unittest.TestCase):
 def row(self):
  return ['F']+['0','0','0','1']
 def test_scenarios(self):
  rows=list(d.scenarios());self.assertEqual(len(rows),950)
  for _,cmd in rows:self.assertEqual(len(d.parse(cmd)),9)
 def test_invalid_inputs(self):
  for cmd in ('',d.command(house=2),d.command(kind=2**31),d.command(base=-2**31-1),d.command(f114=-1),d.command(f114=2**32),d.command()+' tail'):
   with self.assertRaises(ValueError):d.parse(cmd)
  with self.assertRaises(ValueError):d.verify(b'wrong binary')
 def test_rows(self):
  row=self.row();d.validate_row(row)
  for bad in ([],['F'],['7','0']+row,row+['extra'],['F','0','0','2','1'],['F','0','0','0','0']):
   with self.assertRaises(ValueError):d.validate_row(bad)
 def test_replay_provenance(self):
  rows=list(d.scenarios());current={'original':{'pin':'expected'}}
  evidence=dict(d.FLAGS,identities=current,original_instructions_executed=True,original_instructions_modified=False)
  receipt=dict(executable_sha256=d.PATCHED_EXPECTED,profile='supplied-ra2-1006',evidence=evidence,labels=[x[0] for x in rows],commands=[x[1] for x in rows],expected=[self.row() for _ in rows])
  from unittest.mock import patch
  with patch.object(d,'validate_receipt'):
   d.validate(receipt,{},'ignored',current)
   for mutate in (lambda e:e['evidence'].update(live_transfer_unjoined=False),lambda e:e['evidence'].update(original_instructions_modified=True),lambda e:e['commands'].pop(),lambda e:e['evidence']['identities'].update(original={})):
    bad=copy.deepcopy(receipt);mutate(bad)
    with self.assertRaises((ValueError,KeyError)):d.validate(bad,{},'ignored',current)
if __name__=='__main__':unittest.main()
