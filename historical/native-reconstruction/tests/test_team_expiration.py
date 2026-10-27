# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
from unittest.mock import patch
import compare_team_expiration as b
import compare_team_foot_expiration as f
class TeamExpirationEvidence(unittest.TestCase):
 def test_broadcast_matrix_and_domain(self):
  rows=list(b.scenarios());self.assertEqual(len(rows),267)
  for _,cmd in rows:b.parse(cmd)
  for cmd in ('',b.command(flags=1),b.command(count=5),b.command(calls=2,mutation=2),b.command(mutation=6)):
   with self.assertRaises(ValueError):b.parse(cmd)
  with self.assertRaises(ValueError):b.verify(b'wrong binary')
 def test_foot_matrix_and_typed_domain(self):
  rows=list(f.scenarios());self.assertEqual(len(rows),228)
  for _,cmd in rows:f.parse(cmd)
  for cmd in ('',f.command(subject=2),f.command(objectTag=1),f.command(flags=2),f.command(root=6),f.command(operations=[0])):
   with self.assertRaises(ValueError):f.parse(cmd)
  with self.assertRaises(ValueError):f.verify(b'wrong binary')
 def receipt(self,module,row):
  rows=list(module.scenarios());return dict(executable_sha256=module.PATCHED_EXPECTED,profile='supplied-ra2-1006',evidence=dict(module.FLAGS,identities={'original':{'pin':'exact'}},original_instructions_executed=True,original_instructions_modified=False),labels=[x[0] for x in rows],commands=[x[1] for x in rows],expected=[row for _ in rows])
 def test_reuse_pins_original_and_scope(self):
  for module,row in ((b,['F']+['0']*13),(f,['state','TYPED','R'])):
   receipt=self.receipt(module,row);current={'original':{'pin':'exact'},'native_sources':{'current':'hash'}}
   with patch.object(module,'validate_receipt'):
    module.validate(receipt,{},'hash',current)
    for change in (lambda e:e['evidence'].update(production_scheduling=True),lambda e:e['evidence'].update(original_instructions_modified=True),lambda e:e['commands'].pop(),lambda e:e['evidence']['identities'].update(original={})):
     altered=copy.deepcopy(receipt);change(altered)
     with self.assertRaises((ValueError,KeyError)):module.validate(altered,{},'hash',current)
 def test_rows(self):
  for row in ([],['F'],['F']+['0']*14):
   with self.assertRaises(ValueError):b.validate_row(row)
  for row in ([],['state','R'],['state','TYPED']):
   with self.assertRaises(ValueError):f.validate_row(row)
if __name__=='__main__':unittest.main()
