# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
from unittest.mock import patch
import compare_team_observer_weight as d
class TeamObserverWeightEvidence(unittest.TestCase):
 def row(self):return ['F']+['0']*6
 def test_matrix_and_domain(self):
  rows=list(d.scenarios());self.assertEqual(len(rows),580)
  for _,c in rows:self.assertEqual(len(d.parse(c)),13)
  for c in ('',d.command(success=2),d.command(rounding=2),d.command(total=2**31),d.command(alias=2),d.command(mutation=4),d.command(repeats=0),d.command(weight=float('nan')),d.command(weight=float('inf')),d.command(coefficient=1e-200),d.command()+' tail'):
   with self.assertRaises(ValueError):d.parse(c)
  with self.assertRaises(ValueError):d.verify(b'wrong binary')
 def test_rows(self):
  d.validate_row(self.row());d.validate_row(['184','8','0']+self.row())
  for row in ([],['F'],self.row()+['0'],['185','4','0']+self.row(),['184','4',str(2**32)]+self.row()):
   with self.assertRaises(ValueError):d.validate_row(row)
 def receipt(self):
  rows=list(d.scenarios());return dict(executable_sha256=d.PATCHED_EXPECTED,profile='supplied-ra2-1006',evidence=dict(d.FLAGS,identities={'original':{'pin':'exact'},'native_sources':{'old':'hash'}},original_instructions_executed=True,original_instructions_modified=False),labels=[x[0] for x in rows],commands=[x[1] for x in rows],expected=[self.row() for _ in rows])
 def test_reuse_identity_and_scope(self):
  current={'original':{'pin':'exact'},'native_sources':{'new':'hash'}};receipt=self.receipt()
  with patch.object(d,'validate_receipt'):
   d.validate(receipt,{},'hash',current)
   for change in (lambda e:e['evidence'].update(arithmetic_children_supplied=True),lambda e:e['evidence'].update(precision_bits=64),lambda e:e['evidence'].update(original_instructions_modified=True),lambda e:e['commands'].pop(),lambda e:e['evidence']['identities'].update(original={})):
    altered=copy.deepcopy(receipt);change(altered)
    with self.assertRaises((ValueError,KeyError)):d.validate(altered,{},'hash',current)
if __name__=='__main__':unittest.main()
