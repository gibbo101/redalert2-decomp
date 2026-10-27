# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
from unittest.mock import patch
import compare_team_observer_loading as d
class TeamObserverLoadingEvidence(unittest.TestCase):
 def row(self):return ['F']+['0']*87
 def test_matrix_and_domain(self):
  rows=list(d.scenarios());self.assertEqual(len(rows),372)
  for _,c in rows:self.assertEqual(len(d.parse(c)),8)
  for c in ('',d.command(techProfile=9),d.command(object=4),d.command(mutation=5),d.command(alternate=5),d.command(repeats=0),d.command(country=2**31),d.command()+' tail'):
   with self.assertRaises(ValueError):d.parse(c)
  with self.assertRaises(ValueError):d.verify(b'wrong binary')
 def test_rows(self):
  d.validate_row(self.row());d.validate_row(['1','184','8','0']+self.row())
  for row in ([],['F'],self.row()+['0'],['99','0','0','0']+self.row(),['1','-1','0','0']+self.row()):
   with self.assertRaises(ValueError):d.validate_row(row)
 def test_reuse_scope_and_native_identity_separation(self):
  rows=list(d.scenarios());current={'original':{'pin':'exact'},'native_sources':{'new':'hash'}}
  receipt=dict(executable_sha256=d.PATCHED_EXPECTED,profile='supplied-ra2-1006',evidence=dict(d.FLAGS,identities={'original':{'pin':'exact'},'native_sources':{'old':'hash'}},original_instructions_executed=True,original_instructions_modified=False),labels=[x[0] for x in rows],commands=[x[1] for x in rows],expected=[self.row() for _ in rows])
  with patch.object(d,'validate_receipt'):
   d.validate(receipt,{},'hash',current)
   for change in (lambda e:e['evidence'].update(Team_lookup_TaskForce_trim_FTOL_actual=False),lambda e:e['evidence'].update(CRT_locale_zero=False),lambda e:e['evidence'].update(production_scheduling=True),lambda e:e['commands'].pop(),lambda e:e['evidence']['identities'].update(original={})):
    altered=copy.deepcopy(receipt);change(altered)
    with self.assertRaises((ValueError,KeyError)):d.validate(altered,{},'hash',current)
if __name__=='__main__':unittest.main()
