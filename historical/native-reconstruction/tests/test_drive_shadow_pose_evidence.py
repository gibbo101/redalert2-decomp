# SPDX-License-Identifier: GPL-3.0-or-later
import unittest
import test_voxel_part_evidence as base
from compare_drive_shadow_pose import command,fbits,parse,validate
from verify_drive_shadow_pose import verify
class DriveShadowEvidenceGuards(unittest.TestCase):
 def fixture(self):
  e,r,c=base.VoxelPartEvidenceGuards().fixture();e['commands']=[command()];return e,r,c
 def test_rebuilt_runner_allowed(self):
  e,r,c=self.fixture();validate(e,r,'fingerprint',c)
 def test_source_input_inspection_refused(self):
  for field in ('sources','inspection','prepared_inputs'):
   e,r,c=self.fixture();c[field]='changed'
   with self.assertRaisesRegex(ValueError,'identity'):validate(e,r,'fingerprint',c)
 def test_engine_profile_refused(self):
  for field in ('executable_sha256','profile'):
   e,r,c=self.fixture();e[field]='changed'
   with self.assertRaisesRegex(ValueError,'engine/profile'):validate(e,r,'fingerprint',c)
 def test_counts_and_receipt_refused(self):
  e,r,c=self.fixture();e['expected']=[]
  with self.assertRaisesRegex(ValueError,'counts'):validate(e,r,'fingerprint',c)
  e,r,c=self.fixture()
  with self.assertRaisesRegex(ValueError,'fingerprint'):validate(e,r,'wrong',c)
 def test_bad_commands_refused(self):
  for cmd in ('','bad','D 0',command(ramp=21),command(kind=2),command(present=2),command(mode=4),
    command(x=2147483648),command(key=-2147483649),command(rate=65536),
    command(rx=fbits(float('nan'))),command(ry=fbits(float('inf'))),command()+' trailing'):
   e,r,c=self.fixture();e['commands']=[cmd]
   with self.assertRaisesRegex(ValueError,'command'):validate(e,r,'fingerprint',c)
 def test_signed_edges_and_null_key_retained(self):
  v=parse(command(sstart=-2147483648,sduration=2147483647,rx=fbits(-0.),present=0,key=-1))
  self.assertEqual(v[12],-2147483648);self.assertEqual(v[14],2147483647)
  self.assertEqual(v[15],fbits(-0.));self.assertEqual(v[17:19],[0,-1])
 def test_wrong_engine_refused(self):
  with self.assertRaisesRegex(ValueError,'engine'):verify(b'unsupported')
if __name__=='__main__':unittest.main()
