# SPDX-License-Identifier: GPL-3.0-or-later
import unittest
from unittest.mock import patch,Mock
import test_voxel_part_evidence as base
from compare_ramp_geometry import bits,parse,validate
from verify_ramp_geometry import verify
from prepare_ramp_geometry_data import extract
from prepared_data_profiles import PATCHED
class RampGeometryEvidenceGuards(unittest.TestCase):
 def fixture(self):
  e,r,c=base.VoxelPartEvidenceGuards().fixture();e['commands']=['S 0'];return e,r,c
 def test_rebuilt_runner_allowed(self):
  e,r,c=self.fixture();validate(e,r,'fingerprint',c)
 def test_changed_sources_and_inputs_refused(self):
  for field in ('sources','inspection','prepared_inputs'):
   e,r,c=self.fixture();c[field]='changed'
   with self.assertRaisesRegex(ValueError,'identity'):validate(e,r,'fingerprint',c)
 def test_changed_engine_profile_refused(self):
  for field in ('executable_sha256','profile'):
   e,r,c=self.fixture();e[field]='changed'
   with self.assertRaisesRegex(ValueError,'engine/profile'):validate(e,r,'fingerprint',c)
 def test_counts_and_receipt_refused(self):
  e,r,c=self.fixture();e['expected']=[]
  with self.assertRaisesRegex(ValueError,'counts'):validate(e,r,'fingerprint',c)
  e,r,c=self.fixture()
  with self.assertRaisesRegex(ValueError,'fingerprint'):validate(e,r,'wrong',c)
 def test_bad_commands_refused(self):
  for cmd in ('','bad','S','S 4','S 0 trailing','T 0','A -1 0',f'T {1<<64} 0',
    f'A {bits(float("nan"))} 0',f'T {bits(float("inf"))} 0',f'A {bits(1e6+1)} 0'):
   e,r,c=self.fixture();e['commands']=[cmd]
   with self.assertRaisesRegex(ValueError,'command'):validate(e,r,'fingerprint',c)
 def test_leaf_signed_zero_retained(self):
  self.assertEqual(parse(f'A {bits(-0.)} 3'),['A',str(bits(-0.)),'3'])
 def test_wrong_engine_refused_before_reading_ranges(self):
  with self.assertRaisesRegex(ValueError,'engine'):verify(b'unsupported')
  with self.assertRaisesRegex(ValueError,'engine'):extract(b'unsupported')
 def test_preparation_uses_only_pinned_actual_table_ranges(self):
  actual=Mock(side_effect=lambda a,n:bytes([a&255])*n)
  with patch('prepare_ramp_geometry_data.hashlib.sha256') as digest,patch('prepare_ramp_geometry_data.readers') as readers:
   digest.return_value.hexdigest.return_value=PATCHED
   readers.return_value=(PATCHED,Mock(side_effect=AssertionError('No disc mapping')),actual)
   blob=extract(b'synthetic')
  self.assertEqual(actual.call_args_list,[((0x80fde4,16384),),((0x7a0f80,8),)])
  self.assertEqual(len(blob),16432);self.assertEqual(blob[:8],b'RA2GEO1\0')
  self.assertEqual(blob[8:40],bytes.fromhex(PATCHED))
if __name__=='__main__':unittest.main()
