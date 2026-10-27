# SPDX-License-Identifier: GPL-3.0-or-later
import unittest
from compare_ground_drive_stores import validate
from compare_ground_drive_advance import command
import test_ground_drive_advance_evidence as base
from verify_ground_drive_stores import verify

class DriveStoresEvidence(unittest.TestCase):
 def fixture(self):
  e,r,c=base.GroundDriveAdvanceEvidenceGuards().fixture()
  e['evidence']['selected_Drive_stores_and_actor_query_service_order']=True
  r['selected_Drive_stores_and_actor_query_service_order']=True
  return e,r,c
 def test_rebuilt_runner_can_replay_matching_sources(self):
  e,r,c=self.fixture();validate(e,r,'fingerprint',c)
 def test_changed_input_source_and_fingerprint_refused(self):
  for key in ('inspection','sources','owned_rules'):
   e,r,c=self.fixture();c[key]='changed'
   with self.subTest(key=key),self.assertRaisesRegex(ValueError,'identity'):validate(e,r,'fingerprint',c)
  e,r,c=self.fixture()
  with self.assertRaisesRegex(ValueError,'fingerprint'):validate(e,r,'wrong',c)
 def test_missing_order_and_incomplete_stream_refused(self):
  e,r,c=self.fixture()
  e['evidence']['selected_Drive_stores_and_actor_query_service_order']=False
  r['selected_Drive_stores_and_actor_query_service_order']=False
  with self.assertRaisesRegex(ValueError,'ordered'):validate(e,r,'fingerprint',c)
  for key in ('commands','expected','labels'):
   e,r,c=self.fixture();e[key]=[]
   with self.subTest(key=key),self.assertRaisesRegex(ValueError,'counts'):validate(e,r,'fingerprint',c)
 def test_malformed_commands_refused(self):
  for cmd in ('','A 0',command(track=64),command()+' trailing'):
   e,r,c=self.fixture();e['commands']=[cmd]
   with self.subTest(cmd=cmd[:20]),self.assertRaisesRegex(ValueError,'command'):validate(e,r,'fingerprint',c)
 def test_exact_engine_required(self):
  with self.assertRaises(ValueError):verify(b'unsupported')

if __name__=='__main__':unittest.main()
