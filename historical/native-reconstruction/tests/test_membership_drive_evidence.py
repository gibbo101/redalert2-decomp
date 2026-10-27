# SPDX-License-Identifier: GPL-3.0-or-later
import unittest
import test_prepared_drive_state_evidence as base
from compare_membership_drive import command,parse,validate
from compare_prepared_drive_state import command as older_command
from verify_membership_drive import verify
class MembershipDriveEvidenceGuards(unittest.TestCase):
 def fixture(self):
  e,r,c=base.PreparedDriveStateEvidenceGuards().fixture()
  e['commands'].append(command());e['expected'].append(['0']);e['labels'].append('movement')
  return e,r,c
 def test_valid_preparation_and_movement_receipt(self):
  e,r,c=self.fixture();validate(e,r,'fingerprint',c)
 def test_unprepared_actor_refused(self):
  e,r,c=self.fixture();e['commands']=[command()];e['expected']=e['expected'][:1];e['labels']=e['labels'][:1]
  with self.assertRaisesRegex(ValueError,'prepared map'):validate(e,r,'fingerprint',c)
 def test_counts_receipt_and_malformed_map_refused(self):
  e,r,c=self.fixture();e['expected']=[]
  with self.assertRaisesRegex(ValueError,'counts'):validate(e,r,'fingerprint',c)
  e,r,c=self.fixture()
  with self.assertRaisesRegex(ValueError,'fingerprint'):validate(e,r,'wrong',c)
  e,r,c=self.fixture();e['commands'][0]='P placeholder'
  with self.assertRaisesRegex(ValueError,'command'):validate(e,r,'fingerprint',c)
 def test_source_engine_and_snapshot_identity_refused(self):
  e,r,c=self.fixture();c['sources']='changed'
  with self.assertRaisesRegex(ValueError,'identity'):validate(e,r,'fingerprint',c)
  e,r,c=self.fixture();e['executable_sha256']='changed'
  with self.assertRaisesRegex(ValueError,'engine/profile'):validate(e,r,'fingerprint',c)
  with self.assertRaisesRegex(ValueError,'engine'):verify(b'unsupported')
 def test_actual_initial_mark_profile_and_route_sentinel(self):
  _,(v,route,numbers)=parse(command());self.assertEqual(v[11:13],[0,1]);self.assertEqual(route[-1],-1)
 def test_supplied_false_mark_effect_and_nonzero_initial_onmap_refused(self):
  for c in (older_command(marked=1),command(effect=0),command()+' trailing','M 0'):
   with self.assertRaises((AssertionError,ValueError)):parse(c)
 def test_gapped_routes_and_nonfinite_inputs_refused(self):
  for c in (command(route=(2,-1,4)),command(numeric=(float('nan'),1.,.7,1.2))):
   with self.assertRaises(AssertionError):parse(c)
if __name__=='__main__':unittest.main()
