# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
from unittest.mock import patch
import compare_team_vehicle_expiration as v
import compare_team_foot_expiration as f
class TeamVehicleEvidence(unittest.TestCase):
 def test_matrix_and_domain(self):
  rows=list(v.scenarios());self.assertEqual(len(rows),708)
  for _,cmd in rows:v.parse(cmd)
  for c in ('',v.command(f.command(root=5)),v.command(f.command(root=4),vehicle=2),v.command(f.command(root=4),derived=17),v.command(f.command(root=4),mutation=3),v.command(f.command(root=4,subject=2))):
   with self.assertRaises((ValueError,AssertionError)):v.parse(c)
  with self.assertRaises(ValueError):v.verify(b'wrong target')
 def test_reuse_scope_and_inputs(self):
  rows=list(v.scenarios());e=dict(executable_sha256=v.PATCHED_EXPECTED,profile='supplied-ra2-1006',evidence=dict(v.FLAGS,identities={'original':{'pin':'exact'}},original_instructions_executed=True,original_instructions_modified=False),labels=[x[0] for x in rows],commands=[x[1] for x in rows],expected=[['state','TYPED','VEHICLE','R'] for _ in rows]);current={'original':{'pin':'exact'},'native_sources':{'current':'hash'}}
  with patch.object(v,'validate_receipt'):
   v.validate(e,{},'hash',current)
   for change in (lambda a:a['evidence'].update(production_scheduling=True),lambda a:a['evidence']['identities'].update(original={}),lambda a:a['commands'].pop(),lambda a:a['expected'][0].remove('VEHICLE')):
    altered=copy.deepcopy(e);change(altered)
    with self.assertRaises((ValueError,KeyError)):v.validate(altered,{},'hash',current)
if __name__=='__main__':unittest.main()
