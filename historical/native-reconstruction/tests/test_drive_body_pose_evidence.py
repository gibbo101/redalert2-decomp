# SPDX-License-Identifier: GPL-3.0-or-later
import unittest
from unittest.mock import Mock,patch
import test_voxel_part_evidence as base
from compare_drive_body_pose import command,parse,validate,fbits,dbits
from prepare_ramp_pose_data import extract
from prepared_data_profiles import PATCHED
from verify_drive_body_pose import verify
class DriveBodyPoseEvidenceGuards(unittest.TestCase):
 def fixture(self):
  e,r,c=base.VoxelPartEvidenceGuards().fixture();e['commands']=[command()];return e,r,c
 def test_rebuilt_runner_can_replay(self):
  e,r,c=self.fixture();validate(e,r,'fingerprint',c)
 def test_changed_source_data_and_inspection_refused(self):
  for field in ('sources','inspection','prepared_inputs'):
   e,r,c=self.fixture();c[field]='changed'
   with self.assertRaisesRegex(ValueError,'identity'):validate(e,r,'fingerprint',c)
 def test_changed_engine_and_profile_refused(self):
  for field in ('executable_sha256','profile'):
   e,r,c=self.fixture();e[field]='changed'
   with self.assertRaisesRegex(ValueError,'engine/profile'):validate(e,r,'fingerprint',c)
 def test_counts_and_fingerprint_refused(self):
  e,r,c=self.fixture();e['expected']=[]
  with self.assertRaisesRegex(ValueError,'counts'):validate(e,r,'fingerprint',c)
  e,r,c=self.fixture()
  with self.assertRaisesRegex(ValueError,'fingerprint'):validate(e,r,'wrong',c)
 def test_malformed_commands_and_nonfinite_fields_refused(self):
  for cmd in ('','B 0','Q','Q 4','Q 0 trailing',command(op=3),command(current=21),command(previous=-1),
   command(nextRamp=21),command(present=2),command(mode=4),command(tick=2147483648),
   command(rx=fbits(float('nan'))),command(ry=fbits(float('inf'))),command(rx=fbits(1.1)),
   command(dx=dbits(float('nan'))),command(dy=dbits(1e7)),command()+' trailing'):
   e,r,c=self.fixture();e['commands']=[cmd]
   with self.assertRaisesRegex(ValueError,'command'):validate(e,r,'fingerprint',c)
 def test_signed_timer_edges_and_zero_sign_retained(self):
  v=parse(command(start=-2147483648,duration=2147483647,rx=fbits(-0.),dx=dbits(-0.),present=0,key=-1))
  self.assertEqual(v[4],-2147483648);self.assertEqual(v[6],2147483647)
  self.assertEqual(v[8],fbits(-0.));self.assertEqual(v[10],dbits(-0.));self.assertEqual(v[17:19],[0,-1])
  self.assertEqual(parse('Q 3'),['Q',3])
 def test_wrong_executable_refused_before_extraction_or_inspection(self):
  with self.assertRaisesRegex(ValueError,'engine'):verify(b'unsupported')
  with self.assertRaisesRegex(ValueError,'engine'):extract(b'unsupported')
 def test_extraction_is_limited_to_checked_private_tables(self):
  actual=Mock(side_effect=lambda a,n:bytes([a&255])*n)
  with patch('prepare_ramp_pose_data.hashlib.sha256') as digest,patch('prepare_ramp_pose_data.readers') as readers:
   digest.return_value.hexdigest.return_value=PATCHED
   readers.return_value=(PATCHED,Mock(side_effect=AssertionError('No disc mapping')),actual)
   blob=extract(b'synthetic')
  self.assertEqual(actual.call_args_list,[((0x80bdd4,4097*4),),((0x7a0f88,4),),((0x79b630,8),),((0x7a8660,8),),((0x79c520,8),)])
  self.assertEqual(len(blob),16456);self.assertEqual(blob[:8],b'RA2RPO1\0');self.assertEqual(blob[8:40],bytes.fromhex(PATCHED))
if __name__=='__main__':unittest.main()
