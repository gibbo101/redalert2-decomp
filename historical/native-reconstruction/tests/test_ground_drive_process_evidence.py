# SPDX-License-Identifier: GPL-3.0-or-later
import unittest
import test_voxel_part_evidence as base
from compare_ground_drive_process import command,parse,validate
from verify_ground_drive_process import verify
class GroundDriveProcessEvidenceGuards(unittest.TestCase):
 def fixture(self):
  e,r,c=base.VoxelPartEvidenceGuards().fixture();e['commands']=[command()];return e,r,c
 def test_current_runner_can_replay(self):
  e,r,c=self.fixture();validate(e,r,'fingerprint',c)
 def test_source_inspection_and_owned_inputs_must_match(self):
  for key in ('sources','inspection','owned_rules','render_data'):
   e,r,c=self.fixture();c[key]='changed'
   with self.assertRaisesRegex(ValueError,'identity'):validate(e,r,'fingerprint',c)
 def test_engine_and_profile_must_match(self):
  for key in ('executable_sha256','profile'):
   e,r,c=self.fixture();e[key]='changed'
   with self.assertRaisesRegex(ValueError,'engine/profile'):validate(e,r,'fingerprint',c)
 def test_result_counts_and_fingerprint_must_match(self):
  e,r,c=self.fixture();e['expected']=[]
  with self.assertRaisesRegex(ValueError,'counts'):validate(e,r,'fingerprint',c)
  e,r,c=self.fixture()
  with self.assertRaisesRegex(ValueError,'fingerprint'):validate(e,r,'wrong',c)
 def test_unsupported_commands_refused(self):
  for cmd in ('','P 0',command(track=64),command(index=128),command(speed=256),command(marked=256),command(steps=257),command(steps=0),
   command(route=(2,-1,2)),command(route=(8,)),command(route=(2,)*24),command(rot=0),command(heading=65536),command(dest=2),
   command(initial_ramp=21),command(resident=2),command(pattern=2),command(ramp=21),command(mode=4),command(percentage=float('nan')),command()+' trailing'):
   e,r,c=self.fixture();e['commands']=[cmd]
   with self.assertRaisesRegex(ValueError,'command'):validate(e,r,'fingerprint',c)
 def test_supplied_queue_and_signed_clock_preserved(self):
  v,extra,route,numeric,planes=parse(command(tick=-1,marked=255,route=(2,3,4),heading=65535,downhill=1.2))
  self.assertEqual((v[5],v[8],extra[0],route[:4],numeric[3]),(-1,255,65535,[2,3,4,-1],1.2))
 def test_exact_engine_required(self):
  with self.assertRaisesRegex(ValueError,'engine'):verify(b'unsupported')
if __name__=='__main__':unittest.main()
