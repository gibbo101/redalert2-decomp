# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
from unittest.mock import patch
import compare_team_command20 as d
class TeamCommand20Evidence(unittest.TestCase):
 def row(self):return ['F']+['0']*27+['X']+['0']*11
 def test_scenarios(self):
  rows=list(d.scenarios());self.assertEqual(len(rows),588)
  for _,c in rows:self.assertEqual(len(d.parse(c)),12)
 def test_invalid(self):
  for c in ('',d.command(members=0),d.command(complete=0,cursor=-1),d.command(argument=2**31),d.command(mutation=8),d.command()+' tail'):
   with self.assertRaises(ValueError):d.parse(c)
  with self.assertRaises(ValueError):d.verify(b'wrong binary')
 def test_rows(self):
  d.validate_row(self.row())
  for row in ([],['F'],self.row()+['0'],['14']+['0']*5+self.row(),self.row()[:28]+['bad']+self.row()[29:]):
   with self.assertRaises(ValueError):d.validate_row(row)
 def test_reuse_identity_and_scope(self):
  rows=list(d.scenarios());current={'original':{'pin':'exact'}}
  receipt=dict(executable_sha256=d.PATCHED_EXPECTED,profile='supplied-ra2-1006',evidence=dict(d.FLAGS,identities=copy.deepcopy(current),original_instructions_executed=True,original_instructions_modified=False),labels=[x[0] for x in rows],commands=[x[1] for x in rows],expected=[self.row() for _ in rows])
  with patch.object(d,'validate_receipt'):
   d.validate(receipt,{},'receipt-hash',current)
   for change in (lambda e:e['evidence'].update(saved_next_and_callee=False),lambda e:e['evidence'].update(original_instructions_modified=True),lambda e:e['commands'].pop(),lambda e:e['evidence']['identities'].update(original={})):
    altered=copy.deepcopy(receipt);change(altered)
    with self.assertRaises((ValueError,KeyError)):d.validate(altered,{},'receipt-hash',current)
if __name__=='__main__':unittest.main()
