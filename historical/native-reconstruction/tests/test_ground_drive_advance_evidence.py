# SPDX-License-Identifier: GPL-3.0-or-later
import unittest
import test_voxel_part_evidence as base
from compare_ground_drive_advance import command,parse,validate
from verify_ground_drive_advance import verify
class GroundDriveAdvanceEvidenceGuards(unittest.TestCase):
 def fixture(self):
  e,r,c=base.VoxelPartEvidenceGuards().fixture();e['commands']=[command()];return e,r,c
 def test_current_runner_can_replay(self):
  e,r,c=self.fixture();validate(e,r,'fingerprint',c)
 def test_source_inspection_and_owned_inputs_must_match(self):
  for key in ('sources','inspection','owned_rules'):
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
  for cmd in ('','A 0',command(track=-2),command(track=64),command(speed=256),command(marked=-1),command(marked=256),
   command(index=128),command(acc=-2147483649),command(acc=2147483648),command(steps=65),command(steps=0),command(x=2147483648),
   command(resident=2),command(pattern=2),command(ramp=21),command(mode=4),command(percentage=float('nan')),command()+' trailing'):
   e,r,c=self.fixture();e['commands']=[cmd]
   with self.assertRaisesRegex(ValueError,'command'):validate(e,r,'fingerprint',c)
 def test_signed_world_and_nonzero_marked_byte_preserved(self):
  v,percentage,_=parse(command(x=-2147483648,hx=2147483647,marked=255,percentage=-1.))
  self.assertEqual((v[8],v[10],v[13],percentage),(255,2147483647,-2147483648,-1.))
 def test_exact_engine_required(self):
  with self.assertRaisesRegex(ValueError,'engine'):verify(b'unsupported')
if __name__=='__main__':unittest.main()
