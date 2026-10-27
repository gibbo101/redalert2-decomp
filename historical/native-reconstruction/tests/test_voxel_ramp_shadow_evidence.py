# SPDX-License-Identifier: GPL-3.0-or-later
import unittest
import test_voxel_part_evidence as base
from compare_voxel_ramp_shadow import bits,parse,validate
from verify_voxel_ramp_shadow import verify
class VoxelRampShadowEvidenceGuards(unittest.TestCase):
 def fixture(self):
  e,r,c=base.VoxelPartEvidenceGuards().fixture();e['commands']=[f'{bits(.25)} {bits(.5)} 0'];return e,r,c
 def test_rebuilt_runner_allowed(self):
  e,r,c=self.fixture();validate(e,r,'fingerprint',c)
 def test_source_input_identity_refused(self):
  for key in ('sources','inspection','raster_data_sha256'):
   e,r,c=self.fixture();c[key]='changed'
   with self.assertRaisesRegex(ValueError,'identity'):validate(e,r,'fingerprint',c)
 def test_engine_profile_refused(self):
  for key in ('executable_sha256','profile'):
   e,r,c=self.fixture();e[key]='changed'
   with self.assertRaisesRegex(ValueError,'engine/profile'):validate(e,r,'fingerprint',c)
 def test_counts_and_receipt_refused(self):
  e,r,c=self.fixture();e['expected']=[]
  with self.assertRaisesRegex(ValueError,'counts'):validate(e,r,'fingerprint',c)
  e,r,c=self.fixture()
  with self.assertRaisesRegex(ValueError,'fingerprint'):validate(e,r,'wrong',c)
 def test_bad_commands_refused(self):
  for cmd in ('','bad','0 0','0 0 0 0','-1 0 0',f'{1<<64} 0 0',f'{bits(float("nan"))} 0 0',f'0 {bits(float("inf"))} 0',f'{bits(3.001)} 0 0','0 0 4'):
   e,r,c=self.fixture();e['commands']=[cmd]
   with self.assertRaisesRegex(ValueError,'command'):validate(e,r,'fingerprint',c)
 def test_signed_zero_and_FP_mode_retained(self):
  self.assertEqual(parse(f'{bits(-0.)} {bits(0.)} 3'),[bits(-0.),bits(0.),3])
 def test_wrong_engine_refused(self):
  with self.assertRaisesRegex(ValueError,'engine'):verify(b'unsupported')
if __name__=='__main__':unittest.main()
