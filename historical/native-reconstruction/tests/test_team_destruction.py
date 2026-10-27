# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
from unittest.mock import patch
import compare_team_destruction as d
class TeamDestructionEvidence(unittest.TestCase):
 def row(self):return ['F']+['0']*56
 def test_matrix_and_domain(self):
  rows=list(d.scenarios());self.assertEqual(len(rows),266)
  for _,c in rows:self.assertEqual(len(d.parse(c)),15)
  for c in ('',d.command(type=2),d.command(members=5),d.command(tag=3),d.command(active=256),d.command(observers=5),d.command(mutation=6),d.command()+' tail'):
   with self.assertRaises(ValueError):d.parse(c)
  with self.assertRaises(ValueError):d.verify(b'wrong binary')
 def test_rows(self):
  d.validate_row(self.row())
  for row in ([],['F'],self.row()+['0'],['11']+['0']*5+self.row()):
   with self.assertRaises(ValueError):d.validate_row(row)
 def test_reuse_identity_and_scope(self):
  rows=list(d.scenarios());current={'original':{'pin':'exact'}}
  receipt=dict(executable_sha256=d.PATCHED_EXPECTED,profile='supplied-ra2-1006',evidence=dict(d.FLAGS,identities=copy.deepcopy(current),original_instructions_executed=True,original_instructions_modified=False),labels=[x[0] for x in rows],commands=[x[1] for x in rows],expected=[self.row() for _ in rows])
  with patch.object(d,'validate_receipt'):
   d.validate(receipt,{},'hash',current)
   for change in (lambda e:e['evidence'].update(named_children_supplied=False),lambda e:e['evidence'].update(complete_deleting_wrapper=False),lambda e:e['evidence'].update(original_instructions_modified=True),lambda e:e['commands'].pop(),lambda e:e['evidence']['identities'].update(original={})):
    altered=copy.deepcopy(receipt);change(altered)
    with self.assertRaises((ValueError,KeyError)):d.validate(altered,{},'hash',current)
 def test_native_identity_is_not_an_original_dependency(self):
  # Current native code is always rerun; original-source equality alone gates
  # answer reuse, so native-only edits must not force original regeneration.
  rows=list(d.scenarios());current={'original':{'pin':'exact'},'native_sources':{'new':'hash'}}
  receipt=dict(executable_sha256=d.PATCHED_EXPECTED,profile='supplied-ra2-1006',evidence=dict(d.FLAGS,identities={'original':{'pin':'exact'},'native_sources':{'old':'hash'}},original_instructions_executed=True,original_instructions_modified=False),labels=[x[0] for x in rows],commands=[x[1] for x in rows],expected=[self.row() for _ in rows])
  with patch.object(d,'validate_receipt'):d.validate(receipt,{},'hash',current)
if __name__=='__main__':unittest.main()
