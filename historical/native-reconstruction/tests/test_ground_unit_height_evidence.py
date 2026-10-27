# SPDX-License-Identifier: GPL-3.0-or-later
import unittest
from compare_ground_unit_height import validate,parse
import test_ground_unit_world_evidence as base
from verify_ground_unit_height import verify
class GroundUnitHeightEvidenceGuards(unittest.TestCase):
 def fixture(self):
  e,r,c=base.GroundUnitWorldEvidenceGuards().fixture()
  e['evidence']['height_aware_native_entry']=True;r['height_aware_native_entry']=True
  return e,r,c
 def test_rebuilt_runner_allowed(self):
  e,r,c=self.fixture();validate(e,r,'fingerprint',c)
 def test_source_and_input_identity_refused(self):
  for key in ('ground','inspection','sources','input_snapshot_sha256'):
   e,r,c=self.fixture();c[key]='changed'
   with self.assertRaisesRegex(ValueError,'identity'):validate(e,r,'fingerprint',c)
 def test_earlier_native_entry_refused(self):
  e,r,c=self.fixture();e['evidence']['height_aware_native_entry']=False;r['height_aware_native_entry']=False
  with self.assertRaisesRegex(ValueError,'entry differs'):validate(e,r,'fingerprint',c)
 def test_counts_and_receipt_refused(self):
  e,r,c=self.fixture();e['expected']=[]
  with self.assertRaisesRegex(ValueError,'counts'):validate(e,r,'fingerprint',c)
  e,r,c=self.fixture()
  with self.assertRaisesRegex(ValueError,'fingerprint'):validate(e,r,'wrong',c)
 def test_map_and_reset_required(self):
  q='W '+' '.join(map(str,base.GroundUnitWorldEvidenceGuards().query()))
  e,r,c=self.fixture();e['commands']=[q]
  with self.assertRaisesRegex(ValueError,'lacks'):validate(e,r,'fingerprint',c)
 def test_malformed_command_refused(self):
  for cmd in ('','W','W bad','D 0','P F','O 0 1 2'):
   e,r,c=self.fixture();e['commands']=[cmd]
   with self.assertRaisesRegex(ValueError,'command'):validate(e,r,'fingerprint',c)
 def test_absolute_height_branch_inputs_allowed(self):
  for z in (-2147483648,-1,0,1,416,2147483647):
   q=base.GroundUnitWorldEvidenceGuards().query();q[2]=z
   self.assertEqual(parse('W '+' '.join(map(str,q)))[1][2],z)
 def test_wrong_engine_refused(self):
  with self.assertRaisesRegex(ValueError,'engine'):verify(b'unsupported',b'unsupported')
if __name__=='__main__':unittest.main()
