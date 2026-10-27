# SPDX-License-Identifier: GPL-3.0-or-later
import unittest
import test_resident_map_floor_evidence as base
from compare_ground_unit_world import parse,validate
from compare_map_floor_height import bits
from verify_ground_unit_world import verify
class GroundUnitWorldEvidenceGuards(unittest.TestCase):
 def fixture(self):
  e,r,c=base.MapFloorFinalizationEvidenceGuards().fixture();e['commands']=['P '+e['commands'][0]]
  return e,r,c
 def query(self):return [1664,1664,0,bits(.125),3,0,0,0,0,8192,14336,1,0,7,1,0,1312,0,0,0,80,72,0,0,160,144]
 def test_rebuilt_runner_allowed(self):
  e,r,c=self.fixture();validate(e,r,'fingerprint',c)
 def test_sources_and_inputs_refused(self):
  for key in ('shadow','world','prepared','inspection','sources','prepared_numeric_inputs','depth_input_snapshot_sha256'):
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
 def test_malformed_commands_refused(self):
  for cmd in ('','W','W bad','D 0','P F','O 0 1 2','W '+'0 '*26):
   e,r,c=self.fixture();e['commands']=[cmd]
   with self.assertRaisesRegex(ValueError,'command|lacks'):validate(e,r,'fingerprint',c)
 def test_native_domain_commands_refused(self):
  for index,value in ((0,2147483648),(1,-1),(3,bits(float('nan'))),(3,bits(0)),(3,bits(1.1)),(4,-1),(5,2),(6,2),(7,2),(8,65536),(11,256),(12,2),(13,8),(13,0),(13,2),(14,2),(16,65536),(17,2),(18,2),(19,3),(22,-1),(24,161)):
   v=self.query();v[index]=value
   with self.assertRaises((AssertionError,ValueError)):parse('W '+' '.join(map(str,v)))
 def test_nonstock_height_refused(self):
  e,r,c=self.fixture();v=e['commands'][0].split();v[105]='208';e['commands']=[' '.join(v)]
  with self.assertRaisesRegex(ValueError,'command'):validate(e,r,'fingerprint',c)
 def test_map_and_reset_required(self):
  q='W '+' '.join(map(str,self.query()));self.assertEqual(parse(q)[0],'W')
  e,r,c=self.fixture();e['commands']=[q]
  with self.assertRaisesRegex(ValueError,'lacks'):validate(e,r,'fingerprint',c)
 def test_wrong_engine_refused(self):
  with self.assertRaisesRegex(ValueError,'engine'):verify(b'unsupported',b'unsupported')
if __name__=='__main__':unittest.main()
