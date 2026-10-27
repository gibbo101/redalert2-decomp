# SPDX-License-Identifier: GPL-3.0-or-later
import unittest
import test_resident_map_floor_evidence as base
from compare_prepared_unit_world import parse,validate
from compare_map_floor_height import bits
from verify_prepared_unit_world import verify
class PreparedUnitWorldEvidenceGuards(unittest.TestCase):
 def fixture(self):
  e,r,c=base.MapFloorFinalizationEvidenceGuards().fixture();e['commands']=['P '+e['commands'][0]]
  return e,r,c
 def test_rebuilt_runner_allowed(self):
  e,r,c=self.fixture();validate(e,r,'fingerprint',c)
 def test_sources_or_inputs_refused(self):
  for key in ('world','prepared','inspection','sources','depth_input_snapshot_sha256'):
   e,r,c=self.fixture();c[key]='changed'
   with self.assertRaisesRegex(ValueError,'identity'):validate(e,r,'fingerprint',c)
 def test_engine_profile_refused(self):
  for key in ('executable_sha256','profile'):
   e,r,c=self.fixture();e[key]='changed'
   with self.assertRaisesRegex(ValueError,'engine/profile'):validate(e,r,'fingerprint',c)
 def test_receipt_and_counts_refused(self):
  e,r,c=self.fixture();e['expected']=[]
  with self.assertRaisesRegex(ValueError,'counts'):validate(e,r,'fingerprint',c)
  e,r,c=self.fixture()
  with self.assertRaisesRegex(ValueError,'fingerprint'):validate(e,r,'wrong',c)
 def test_malformed_refused(self):
  for cmd in ('','W','W bad','D 0','P F','O 0 1 2','W '+'0 '*24):
   e,r,c=self.fixture();e['commands']=[cmd]
   with self.assertRaisesRegex(ValueError,'command|lacks'):validate(e,r,'fingerprint',c)
 def query(self):return [1664,1664,416,bits(.125),3,0,0,8192,14336,1,0,7,1,0,1312,0,0,0,80,72,0,0,160,144]
 def test_draw_domains(self):
  for index,value in ((0,2147483648),(3,bits(float('nan'))),(3,bits(0)),(3,bits(-.125)),(3,bits(1.1)),(4,-1),(5,2),(6,65536),(9,256),(10,2),(11,8),(12,2),(14,65536),(15,2),(16,2),(17,3),(20,-1),(22,161)):
   v=self.query();v[index]=value
   with self.assertRaises((AssertionError,ValueError)):parse('W '+' '.join(map(str,v)))
 def test_map_and_reset_required(self):
  q='W '+' '.join(map(str,self.query()))
  e,r,c=self.fixture();e['commands']=[q]
  with self.assertRaisesRegex(ValueError,'lacks'):validate(e,r,'fingerprint',c)
  e,r,c=self.fixture();e['commands']=[q]
  # Valid parsing does not imply valid ordering or initialize persistent state.
  self.assertEqual(parse(q)[0],'W')
 def test_wrong_engine_refused(self):
  with self.assertRaisesRegex(ValueError,'engine'):verify(b'unsupported',b'unsupported')
if __name__=='__main__':unittest.main()
