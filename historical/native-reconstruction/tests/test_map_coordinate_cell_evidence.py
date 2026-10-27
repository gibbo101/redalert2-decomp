# SPDX-License-Identifier: GPL-3.0-or-later
import unittest
import test_voxel_part_evidence as base
from compare_map_coordinate_cell import command,parse,validate
from verify_map_coordinate_cell import verify
class CoordinateCellEvidenceGuards(unittest.TestCase):
 def fixture(self):
  e,r,c=base.VoxelPartEvidenceGuards().fixture();e['commands']=[command(262144,[0,511,65536],[[0,0,0],[-256,256,17],[16777216,0,-1]])];return e,r,c
 def test_rebuilt_runner_allowed(self):
  e,r,c=self.fixture();validate(e,r,'fingerprint',c)
 def test_sources_inspection_refused(self):
  for k in ('sources','inspection'):
   e,r,c=self.fixture();c[k]='changed'
   with self.assertRaisesRegex(ValueError,'identity'):validate(e,r,'fingerprint',c)
 def test_engine_profile_refused(self):
  for k in ('executable_sha256','profile'):
   e,r,c=self.fixture();e[k]='changed'
   with self.assertRaisesRegex(ValueError,'engine/profile'):validate(e,r,'fingerprint',c)
 def test_counts_and_receipt_refused(self):
  e,r,c=self.fixture();e['expected']=[]
  with self.assertRaisesRegex(ValueError,'counts'):validate(e,r,'fingerprint',c)
  e,r,c=self.fixture()
  with self.assertRaisesRegex(ValueError,'fingerprint'):validate(e,r,'wrong',c)
 def test_malformed_refused(self):
  for cmd in ('','C','C bad','D 0','C -1 0 1 0 0 0','C 262145 0 1 0 0 0','C 1 2 0 0 1 0 0 0','C 1 0 1 2147483648 0 0'):
   e,r,c=self.fixture();e['commands']=[cmd]
   with self.assertRaisesRegex(ValueError,'command'):validate(e,r,'fingerprint',c)
 def test_signed_alias_queries_preserved(self):
  e,_,_=self.fixture();count,indexes,queries=parse(e['commands'][0]);self.assertEqual(count,262144);self.assertEqual(indexes,[0,511,65536]);self.assertEqual(queries[1:], [[-256,256,17],[16777216,0,-1]])
 def test_wrong_engine_refused(self):
  with self.assertRaisesRegex(ValueError,'engine'):verify(b'unsupported')
if __name__=='__main__':unittest.main()
