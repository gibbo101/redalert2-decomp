# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
from unittest.mock import patch
import compare_infantry_transfer_wrapper as d
class InfantryTransferWrapperEvidence(unittest.TestCase):
 def row(self):return ['F','1','0','0','0','0','1','0','104','416']
 def test_inputs_and_case_matrix(self):
  rows=list(d.scenarios());self.assertEqual(len(rows),1392)
  for _,cmd in rows:self.assertEqual(len(d.parse(cmd)),11)
  for bad in ('',d.command(root=4),d.command(marked=256),d.command(bridge=-1),d.command(z=2**31),d.command(mutation=9),d.command()+' tail'):
   with self.assertRaises(ValueError):d.parse(bad)
  with self.assertRaises(ValueError):d.verify(b'wrong build')
 def test_result_validation(self):
  d.validate_row(['B','1','H','P','0','0','0','D','7','C','W','0']+self.row())
  for bad in (self.row()+['0'],['unknown']+self.row(),['P','1','2']+self.row(),self.row()[:6]+['256']+self.row()[7:]):
   with self.assertRaises((ValueError,KeyError)):d.validate_row(bad)
 def test_original_only_reuse_identity_and_matrix(self):
  rows=list(d.scenarios());current={'original':{'pin':'exact'}}
  receipt=dict(executable_sha256=d.PATCHED_EXPECTED,profile='supplied-ra2-1006',evidence=dict(d.FLAGS,identities=current,original_instructions_executed=True,original_instructions_modified=False),labels=[x[0] for x in rows],commands=[x[1] for x in rows],expected=[self.row() for _ in rows])
  with patch.object(d,'validate_receipt'):
   d.validate(receipt,{},'receipt-hash',current)
   for change in (lambda e:e['evidence'].update(actual_ground_query_relative_height_and_packed_cell=False),lambda e:e['evidence'].update(original_instructions_modified=True),lambda e:e['commands'].pop(),lambda e:e['evidence']['identities'].update(original={})):
    altered=copy.deepcopy(receipt);change(altered)
    with self.assertRaises((ValueError,KeyError)):d.validate(altered,{},'receipt-hash',current)
if __name__=='__main__':unittest.main()
