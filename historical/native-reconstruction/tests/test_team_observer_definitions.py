# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
from unittest.mock import patch
import compare_team_observer_definitions as d
class TeamObserverDefinitionsEvidence(unittest.TestCase):
 def row(self):return ['F']+['0']*45
 def test_matrix_and_domain(self):
  rows=list(d.scenarios());self.assertEqual(len(rows),390)
  for _,c in rows:self.assertEqual(len(d.parse(c)),9)
  for c in ('',d.command(mode=1,profile=3),d.command(mode=1,allocation=1),d.command(profile=2,registry=3),d.command(mutation=6,repeats=2),d.command(profile=9),d.command(boolean=2**32)):
   with self.assertRaises(ValueError):d.parse(c)
  with self.assertRaises(ValueError):d.verify(b'wrong binary')
 def test_rows(self):
  d.validate_row(self.row());d.validate_row(['8','1','156','0']+self.row())
  for row in ([],['F'],self.row()+['0'],['99','0','0','0']+self.row(),['1','-1','0','0']+self.row()):
   with self.assertRaises(ValueError):d.validate_row(row)
 def test_reuse_scope_and_native_identity_separation(self):
  rows=list(d.scenarios());current={'original':{'pin':'exact'},'native_sources':{'new':'hash'}}
  receipt=dict(executable_sha256=d.PATCHED_EXPECTED,profile='supplied-ra2-1006',evidence=dict(d.FLAGS,identities={'original':{'pin':'exact'},'native_sources':{'old':'hash'}},original_instructions_executed=True,original_instructions_modified=False),labels=[x[0] for x in rows],commands=[x[1] for x in rows],expected=[self.row() for _ in rows])
  with patch.object(d,'validate_receipt'):
   d.validate(receipt,{},'hash',current)
   for change in (lambda e:e['evidence'].update(locale_zero_actual=False),lambda e:e['evidence'].update(production_scheduling=True),lambda e:e['commands'].pop(),lambda e:e['evidence']['identities'].update(original={})):
    altered=copy.deepcopy(receipt);change(altered)
    with self.assertRaises((ValueError,KeyError)):d.validate(altered,{},'hash',current)
if __name__=='__main__':unittest.main()
