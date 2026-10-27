# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
from unittest.mock import patch
import compare_team_member_removal as d
class TeamRemovalEvidence(unittest.TestCase):
 def row(self):return ['F']+['0']*49
 def test_matrix_and_domain(self):
  rows=list(d.scenarios());self.assertEqual(len(rows),465)
  for _,c in rows:self.assertEqual(len(d.parse(c)),21)
  for c in ('',d.command(members=0),d.command(target=4),d.command(slot=6,taskCount=-1),d.command(onMap=256),d.command(mutation=6),d.command()+' tail'):
   with self.assertRaises(ValueError):d.parse(c)
  with self.assertRaises(ValueError):d.verify(b'wrong binary')
 def test_rows(self):
  d.validate_row(self.row())
  for row in ([],['F'],self.row()+['0'],['8']+['0']*5+self.row()):
   with self.assertRaises(ValueError):d.validate_row(row)
 def test_reuse_identity_and_scope(self):
  rows=list(d.scenarios());current={'original':{'pin':'exact'}}
  receipt=dict(executable_sha256=d.PATCHED_EXPECTED,profile='supplied-ra2-1006',evidence=dict(d.FLAGS,identities=copy.deepcopy(current),original_instructions_executed=True,original_instructions_modified=False),labels=[x[0] for x in rows],commands=[x[1] for x in rows],expected=[self.row() for _ in rows])
  with patch.object(d,'validate_receipt'):
   d.validate(receipt,{},'hash',current)
   for change in (lambda e:e['evidence'].update(named_children_supplied=False),lambda e:e['evidence'].update(original_instructions_modified=True),lambda e:e['commands'].pop(),lambda e:e['evidence']['identities'].update(original={})):
    altered=copy.deepcopy(receipt);change(altered)
    with self.assertRaises((ValueError,KeyError)):d.validate(altered,{},'hash',current)
if __name__=='__main__':unittest.main()
