# SPDX-License-Identifier: GPL-3.0-or-later
import unittest
import test_map_preparation_evidence as base
from compare_map_floor_height import bits,command,validate
from verify_map_floor_height import verify
class MapFloorHeightEvidenceGuards(unittest.TestCase):
 def fixture(self):
  e,r,c=base.MapPreparationEvidenceGuards().fixture()
  e['commands']=[command('H',0,bits(0),bits(0),[bits(1),*([0]*99)],[[104,-1,1,-1,255,0,0,416,0,1,0,0]])]
  return e,r,c
 def test_rebuilt_runner_allowed(self):
  e,r,c=self.fixture();validate(e,r,'fingerprint',c)
 def test_identity_refused(self):
  for key in ('sources','inspection'):
   e,r,c=self.fixture();c[key]='changed'
   with self.assertRaisesRegex(ValueError,'identity differs'):validate(e,r,'fingerprint',c)
 def test_engine_profile_refused(self):
  for key in ('executable_sha256','profile'):
   e,r,c=self.fixture();e[key]='changed'
   with self.assertRaisesRegex(ValueError,'engine/profile'):validate(e,r,'fingerprint',c)
 def test_missing_receipt_or_result_refused(self):
  e,r,c=self.fixture();e['expected']=[]
  with self.assertRaisesRegex(ValueError,'counts'):validate(e,r,'fingerprint',c)
  e,r,c=self.fixture()
  with self.assertRaisesRegex(ValueError,'fingerprint'):validate(e,r,'wrong',c)
 def test_malformed_refused(self):
  for cmd in ('','H','H bad','W 0 0','M '+'0 '*140):
   e,r,c=self.fixture();e['commands']=[cmd]
   with self.assertRaisesRegex(ValueError,'command'):validate(e,r,'fingerprint',c)
 def test_nonfinite_and_domains_refused(self):
  for index,value in ((1,256),(2,bits(float('nan'))),(3,bits(float('inf'))),(104,0),(106,128),(107,21),(113,262144)):
   e,r,c=self.fixture();p=e['commands'][0].split();p[index]=str(value);e['commands']=[' '.join(p)]
   with self.assertRaisesRegex(ValueError,'command'):validate(e,r,'fingerprint',c)
  e,r,c=self.fixture();e['commands'][0]+=' 0'
  with self.assertRaisesRegex(ValueError,'command'):validate(e,r,'fingerprint',c)
 def test_wrong_engine_refused(self):
  with self.assertRaisesRegex(ValueError,'engine'):verify(b'unsupported')
if __name__=='__main__':unittest.main()
