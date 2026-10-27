# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
import compare_house_infantry_accounting as d
class HouseInfantryEvidence(unittest.TestCase):
 def test_scenarios(self):
  rows=list(d.scenarios());self.assertEqual(len(rows),1136)
  for _,cmd in rows:self.assertEqual(len(d.parse(cmd)),12)
 def test_invalid_inputs(self):
  for cmd in ('',d.command(index=-1),d.command(index=16),d.command(capacity=-1),d.command(historyCount=33),d.command(type202=256),d.command(root=6),d.command(mutation=4),d.command()+' tail'):
   with self.assertRaises(ValueError):d.parse(cmd)
  with self.assertRaises(ValueError):d.verify(b'wrong binary')
 def test_rows(self):
  row=['F']+['0']*102;d.validate_row(row)
  for bad in ([],['F'],['7']*5+row,row+['R'],row+['R','-1'],row+['extra'],row[:5]+['-1']+row[6:]):
   with self.assertRaises(ValueError):d.validate_row(bad)
 def test_replay_provenance(self):
  rows=list(d.scenarios());current={'original':{'pin':'expected'}}
  evidence=dict(d.FLAGS,identities=current,original_instructions_executed=True,original_instructions_modified=False)
  receipt=dict(executable_sha256=d.PATCHED_EXPECTED,profile='supplied-ra2-1006',evidence=evidence,labels=[x[0] for x in rows],commands=[x[1] for x in rows],expected=[['F']+['0']*102 for _ in rows])
  # Receipt structural/hash checking is tested by its shared owner; isolate the
  # driver's additional immutable expectation/provenance and scenario guards.
  from unittest.mock import patch
  with patch.object(d,'validate_receipt'):
   d.validate(receipt,{},'ignored',current)
   for mutate in (lambda e:e['evidence'].update(ownership_transfer_unjoined=False),lambda e:e['evidence'].update(original_instructions_modified=True),lambda e:e['commands'].pop(),lambda e:e['evidence']['identities'].update(original={})):
    bad=copy.deepcopy(receipt);mutate(bad)
    with self.assertRaises((ValueError,KeyError)):d.validate(bad,{},'ignored',current)
if __name__=='__main__':unittest.main()
