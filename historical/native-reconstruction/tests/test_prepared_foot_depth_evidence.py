# SPDX-License-Identifier: GPL-3.0-or-later
import unittest
import test_resident_map_floor_evidence as base
import compare_resident_map_floor as floor
from compare_prepared_foot_depth import command,parse,validate
from compare_map_floor_height import bits
from verify_prepared_foot_depth import verify
class PreparedFootDepthEvidenceGuards(unittest.TestCase):
 def fixture(self):
  e,r,c=base.MapFloorFinalizationEvidenceGuards().fixture()
  e['commands']=[command(floor.parse(e['commands'][0]),[[384,640,416,0,0,0,0,0,0,bits(.125),-1,-1,3,0,0,1,0,-32768,-32768,8,13,10,0]])]
  return e,r,c
 def test_rebuilt_runner_allowed(self):
  e,r,c=self.fixture();validate(e,r,'fingerprint',c)
 def test_identity_refused(self):
  for key in ('sources','inspection','render_data_sha256','terrain_input_snapshot_sha256','overlay_input_snapshot_sha256','parent_input_snapshot_sha256','floor_input_snapshot_sha256'):
   e,r,c=self.fixture();c[key]='changed'
   with self.assertRaisesRegex(ValueError,'identity'):validate(e,r,'fingerprint',c)
 def test_engine_profile_refused(self):
  for key in ('executable_sha256','profile'):
   e,r,c=self.fixture();e[key]='changed'
   with self.assertRaisesRegex(ValueError,'engine/profile'):validate(e,r,'fingerprint',c)
 def test_receipt_counts_refused(self):
  e,r,c=self.fixture();e['expected']=[]
  with self.assertRaisesRegex(ValueError,'counts'):validate(e,r,'fingerprint',c)
  e,r,c=self.fixture()
  with self.assertRaisesRegex(ValueError,'fingerprint'):validate(e,r,'wrong',c)
 def test_malformed_refused(self):
  for cmd in ('','E','E bad','D 0 0','E | 0','E | 1 '+'0 '*23):
   e,r,c=self.fixture();e['commands']=[cmd]
   with self.assertRaisesRegex(ValueError,'command'):validate(e,r,'fingerprint',c)
 def test_query_domains_refused(self):
  for index,value in ((0,2147483648),(3,65536),(7,65536),(9,bits(float('nan'))),(9,bits(0)),(9,bits(1.1)),(14,1),(13,1),(15,2),(17,32768),(19,2147483648)):
   e,r,c=self.fixture();f,q=parse(e['commands'][0]);q[0][index]=value;e['commands']=[command(f,q)]
   with self.assertRaisesRegex(ValueError,'command'):validate(e,r,'fingerprint',c)
 def test_old_floor_scope_refuses_depth(self):
  e,_,_=self.fixture()
  with self.assertRaises(AssertionError):floor.parse(e['commands'][0])
 def test_wrong_engine_refused(self):
  with self.assertRaisesRegex(ValueError,'engine'):verify(b'unsupported')
if __name__=='__main__':unittest.main()
