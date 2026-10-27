# SPDX-License-Identifier: GPL-3.0-or-later
import unittest
import test_map_preparation_evidence as base
from compare_resident_map_floor import command,parse,validate
from compare_map_floor_height import bits
from verify_resident_map_floor import verify
class MapFloorFinalizationEvidenceGuards(unittest.TestCase):
 def fixture(self):
  e,r,c=base.MapPreparationEvidenceGuards().fixture()
  common=[2,2,0,-1,0,100,100,100,100,0,28,*([0]*16),*([-1]*15),*([0]*8),*([1065353216]*11)]
  e['commands']=[command(0,bits(0),bits(0),[bits(1),*([0]*99)],104,[common,[2,0,0,2,2],[[0,1,1,60,30,0,0,0,0,0,0]],[[1,2,0,0,0,0,-1,0,0,0,0,0,17,91,0,41,0]],[[4,0,1,0,1,0,0]],[],[0]*9,[]])]
  return e,r,c
 def test_rebuilt_runner_allowed(self):
  e,r,c=self.fixture();validate(e,r,'fingerprint',c)
 def test_identity_change_refused(self):
  for key in ('sources','inspection','render_data_sha256','terrain_input_snapshot_sha256','overlay_input_snapshot_sha256','parent_input_snapshot_sha256'):
   e,r,c=self.fixture();c[key]='changed'
   with self.assertRaisesRegex(ValueError,'identity differs'):validate(e,r,'fingerprint',c)
 def test_engine_profile_refused(self):
  for key in ('executable_sha256','profile'):
   e,r,c=self.fixture();e[key]='changed'
   with self.assertRaisesRegex(ValueError,'engine/profile'):validate(e,r,'fingerprint',c)
 def test_result_receipt_refused(self):
  e,r,c=self.fixture();e['expected']=[]
  with self.assertRaisesRegex(ValueError,'counts'):validate(e,r,'fingerprint',c)
  e,r,c=self.fixture()
  with self.assertRaisesRegex(ValueError,'fingerprint'):validate(e,r,'wrong',c)
 def test_malformed_command_refused(self):
  for cmd in ('','F','F bad','G 0 0','F '+'0 '*80):
   e,r,c=self.fixture();e['commands']=[cmd]
   with self.assertRaisesRegex(ValueError,'command'):validate(e,r,'fingerprint',c)
 def test_geometry_and_trailing_refused(self):
  for index,value in ((105,1),(106,255),(109,3),(166,3),(171,0)):
   e,r,c=self.fixture();p=e['commands'][0].split();p[index]=str(value);e['commands']=[' '.join(p)]
   with self.assertRaisesRegex(ValueError,'command'):validate(e,r,'fingerprint',c)
  e,r,c=self.fixture();e['commands'][0]+=' 0'
  with self.assertRaisesRegex(ValueError,'command'):validate(e,r,'fingerprint',c)
 def test_floor_domains_and_supplied_height_refused(self):
  for index,value in ((1,256),(2,bits(float('nan'))),(3,bits(float('inf'))),(104,2147483648)):
   e,r,c=self.fixture();p=e['commands'][0].split();p[index]=str(value);e['commands']=[' '.join(p)]
   with self.assertRaisesRegex(ValueError,'command'):validate(e,r,'fingerprint',c)
  e,r,c=self.fixture();args=list(parse(e['commands'][0]));parent=list(args[5:]);parent[3][0][16]=104
  e['commands']=[command(*args[:5],parent)]
  with self.assertRaisesRegex(ValueError,'command'):validate(e,r,'fingerprint',c)
 def test_old_profile_still_rejects_new_command(self):
  from compare_resident_map_finalization import parse as old_parse
  e,_,_=self.fixture()
  with self.assertRaises(AssertionError):old_parse(e['commands'][0])
 def test_wrong_engine_refused(self):
  with self.assertRaisesRegex(ValueError,'engine'):verify(b'unsupported')
if __name__=='__main__':unittest.main()
